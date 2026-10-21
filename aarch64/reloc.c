#include <stdbool.h>
#include <stdint.h>
#include <efi/elf.h>

/* EFI_LOAD_ERROR, the status _start returns to the firmware unchanged, as it does 0 (success). */
#define LOAD_ERROR (~(UINTPTR_MAX >> 1) | 1)

/* The PE headers' page: a relocation there would be a header field turned into a dynamic one. */
#define HEADER_PAGE_SIZE 0x1000

/*
 * A relocation target need not be aligned (a pointer in a packed structure), and not every
 * processor can store a word at an unaligned address. It may hold an object of any type, hence
 * __may_alias__.
 */
struct unaligned_addr {
    Elf64_Addr value;
} __attribute__((__packed__, __may_alias__));

/* The convention _start calls this with, whatever the user's compiler flags. */
uintptr_t picoefi_relocate(
    uintptr_t image_base,
    const Elf64_Dyn *dynamic
);

/*
 * This runs before the image is relocated, so it depends on no relocated value: no function
 * pointers, no initialised pointers, no calls, and no tables, which compilers make for a switch
 * or for a chain of comparisons of one value.
 */
uintptr_t picoefi_relocate(
    uintptr_t image_base,
    const Elf64_Dyn *dynamic
) {
    bool has_table = false;
    bool has_size = false;
    bool has_entry_size = false;
    bool has_relr_table = false;
    bool has_relr_size = false;
    bool has_relr_entry_size = false;
    Elf64_Addr table = 0;
    Elf64_Xword size = 0;
    Elf64_Xword entry_size = 0;
    Elf64_Addr relr_table = 0;
    Elf64_Xword relr_size = 0;
    Elf64_Xword relr_entry_size = 0;
    Elf64_Xword offset;
    Elf64_Addr last = 0;

    for (; dynamic->d_tag != DT_NULL; dynamic++) {
        /* Read anew by every test, so that the tests cannot become a jump table. */
        volatile Elf64_Sxword tag = dynamic->d_tag;

        if (tag == DT_RELA) {
            table = dynamic->d_un.d_ptr;
            has_table = true;
        } else if (tag == DT_RELASZ) {
            size = dynamic->d_un.d_val;
            has_size = true;
        } else if (tag == DT_RELAENT) {
            entry_size = dynamic->d_un.d_val;
            has_entry_size = true;
        } else if (tag == DT_RELR) {
            relr_table = dynamic->d_un.d_ptr;
            has_relr_table = true;
        } else if (tag == DT_RELRSZ) {
            relr_size = dynamic->d_un.d_val;
            has_relr_size = true;
        } else if (tag == DT_RELRENT) {
            relr_entry_size = dynamic->d_un.d_val;
            has_relr_entry_size = true;
        } else if (tag == DT_REL || tag == DT_RELSZ || tag == DT_RELENT || tag == DT_JMPREL) {
            /* A table this does not apply: refuse the image rather than run it unrelocated. */
            return LOAD_ERROR;
        }
    }

    /* Either table may be left out, but not in part. */
    if (has_table != has_size || has_table != has_entry_size ||
            (has_table && entry_size != sizeof(Elf64_Rela))) {
        return LOAD_ERROR;
    }
    if (has_relr_table != has_relr_size || has_relr_table != has_relr_entry_size ||
            (has_relr_table && relr_entry_size != sizeof(Elf64_Relr))) {
        return LOAD_ERROR;
    }

    /* Every entry is checked before any is applied, so that a refused image is left as it was. */
    if (has_table) {
        for (offset = 0; size - offset >= entry_size; offset += entry_size) {
            const Elf64_Rela *entry = (const Elf64_Rela *)(image_base + table + offset);
            Elf64_Xword type = ELF64_R_TYPE(entry->r_info);

            if (type == R_AARCH64_NONE) {
                continue;
            }
            if (type != R_AARCH64_RELATIVE || entry->r_offset < HEADER_PAGE_SIZE) {
                return LOAD_ERROR;
            }
        }
        /* A partial last entry, found without a division, which may be a library call. */
        if (offset != size) {
            return LOAD_ERROR;
        }
    }
    /*
     * An even RELR entry is the address of a word to relocate, and an odd one is a bitmap of the
     * words after the last that an entry covered, bit n standing for the nth.
     */
    if (has_relr_table) {
        for (offset = 0; relr_size - offset >= relr_entry_size; offset += relr_entry_size) {
            Elf64_Relr entry = *(const Elf64_Relr *)(image_base + relr_table + offset);

            if ((entry & 1) == 0) {
                if (entry < HEADER_PAGE_SIZE) {
                    return LOAD_ERROR;
                }
            } else if (offset == 0) {
                /* A bitmap carries on from an address, so it cannot come first. */
                return LOAD_ERROR;
            }
        }
        if (offset != relr_size) {
            return LOAD_ERROR;
        }
    }
    if (has_table) {
        for (offset = 0; size - offset >= entry_size; offset += entry_size) {
            const Elf64_Rela *entry = (const Elf64_Rela *)(image_base + table + offset);
            struct unaligned_addr *target = (struct unaligned_addr *)(image_base + entry->r_offset);

            if (ELF64_R_TYPE(entry->r_info) == R_AARCH64_RELATIVE) {
                target->value = image_base + (uintptr_t)entry->r_addend;
            }
        }
    }
    if (has_relr_table) {
        for (offset = 0; relr_size - offset >= relr_entry_size; offset += relr_entry_size) {
            Elf64_Relr entry = *(const Elf64_Relr *)(image_base + relr_table + offset);
            unsigned int bit;

            if ((entry & 1) == 0) {
                struct unaligned_addr *target = (struct unaligned_addr *)(image_base + entry);

                target->value += image_base;
                last = entry;
                continue;
            }
            for (bit = 1; bit < sizeof(entry) * 8; bit++) {
                last += sizeof(Elf64_Addr);
                if (((entry >> bit) & 1) != 0) {
                    struct unaligned_addr *target = (struct unaligned_addr *)(image_base + last);

                    target->value += image_base;
                }
            }
        }
    }
    return 0;
}
