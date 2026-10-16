#include <stdbool.h>
#include <stdint.h>
#include <efi/elf.h>

/* EFI_LOAD_ERROR, the status _start returns to the firmware unchanged, as it does 0 (success). */
#define LOAD_ERROR (~(UINTPTR_MAX >> 1) | 1)

/* The PE headers' page: a relocation there would be a header field turned into a dynamic one. */
#define HEADER_PAGE_SIZE 0x1000

/*
 * A relocation target need not be aligned (a pointer in a packed structure), and not every
 * processor can store a word at an unaligned address.
 */
struct unaligned_addr {
    Elf32_Addr value;
} __attribute__((__packed__));

/* The convention _start calls this with, whatever the user's compiler flags. */
uintptr_t __picoefi_relocate(
    uintptr_t image_base,
    const Elf32_Dyn *dynamic
);

/*
 * This runs before the image is relocated, so it depends on no relocated value: no function
 * pointers, no initialised pointers, no calls, and no tables, which compilers make for a switch
 * or for a chain of comparisons of one value.
 */
uintptr_t __picoefi_relocate(
    uintptr_t image_base,
    const Elf32_Dyn *dynamic
) {
    bool has_table = false;
    bool has_size = false;
    bool has_entry_size = false;
    Elf32_Addr table = 0;
    Elf32_Word size = 0;
    Elf32_Word entry_size = 0;
    Elf32_Word offset;

    for (; dynamic->d_tag != DT_NULL; dynamic++) {
        /* Read anew by every test, so that the tests cannot become a jump table. */
        volatile Elf32_Sword tag = dynamic->d_tag;

        if (tag == DT_REL) {
            table = dynamic->d_un.d_ptr;
            has_table = true;
        } else if (tag == DT_RELSZ) {
            size = dynamic->d_un.d_val;
            has_size = true;
        } else if (tag == DT_RELENT) {
            entry_size = dynamic->d_un.d_val;
            has_entry_size = true;
        } else if (tag == DT_RELA || tag == DT_RELASZ || tag == DT_RELAENT || tag == DT_JMPREL ||
                tag == DT_RELRSZ || tag == DT_RELR || tag == DT_RELRENT) {
            /* A table this does not apply: refuse the image rather than run it unrelocated. */
            return LOAD_ERROR;
        }
    }

    if (!has_table && !has_size && !has_entry_size) {
        return 0;
    }
    if (!has_table || !has_size || !has_entry_size || entry_size < sizeof(Elf32_Rel)) {
        return LOAD_ERROR;
    }

    /* Every entry is checked before any is applied, so that a refused image is left as it was. */
    for (offset = 0; size - offset >= entry_size; offset += entry_size) {
        const Elf32_Rel *entry = (const Elf32_Rel *)(image_base + table + offset);
        Elf32_Word type = ELF32_R_TYPE(entry->r_info);

        if (type == R_ARM_NONE) {
            continue;
        }
        if (type != R_ARM_RELATIVE || entry->r_offset < HEADER_PAGE_SIZE) {
            return LOAD_ERROR;
        }
    }
    /* A partial last entry, found without a division, which may be a library call. */
    if (offset != size) {
        return LOAD_ERROR;
    }
    for (offset = 0; size - offset >= entry_size; offset += entry_size) {
        const Elf32_Rel *entry = (const Elf32_Rel *)(image_base + table + offset);
        struct unaligned_addr *target = (struct unaligned_addr *)(image_base + entry->r_offset);

        if (ELF32_R_TYPE(entry->r_info) == R_ARM_RELATIVE) {
            target->value += image_base;
        }
    }
    return 0;
}
