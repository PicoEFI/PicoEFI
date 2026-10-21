#include <stdbool.h>
#include <stdint.h>
#include <efi/elf.h>

/* EFI_LOAD_ERROR, the status _start returns to the firmware unchanged, as it does 0 (success). */
#define LOAD_ERROR (~(UINTPTR_MAX >> 1) | 1)

/*
 * A relocation target need not be aligned (a pointer in a packed structure), and not every
 * processor can store a word at an unaligned address. It may hold an object of any type, hence
 * __may_alias__.
 */
struct unaligned_addr {
    Elf32_Addr value;
} __attribute__((__packed__, __may_alias__));

/* The convention _start calls this with, whatever the user's compiler flags. */
__attribute__((__regparm__(0), __cdecl__)) uintptr_t picoefi_relocate(
    uintptr_t image_base,
    const Elf32_Dyn *dynamic,
    uintptr_t data_start,
    uintptr_t data_end
);

/*
 * This runs before the image is relocated, so it depends on no relocated value: no function
 * pointers, no initialised pointers, no calls, and no tables, which compilers make for a switch
 * or for a chain of comparisons of one value.
 */
__attribute__((__regparm__(0), __cdecl__)) uintptr_t picoefi_relocate(
    uintptr_t image_base,
    const Elf32_Dyn *dynamic,
    uintptr_t data_start,
    uintptr_t data_end
) {
    bool has_table = false;
    bool has_size = false;
    bool has_entry_size = false;
    bool has_relr_table = false;
    bool has_relr_size = false;
    bool has_relr_entry_size = false;
    Elf32_Addr table = 0;
    Elf32_Word size = 0;
    Elf32_Word entry_size = 0;
    Elf32_Addr relr_table = 0;
    Elf32_Word relr_size = 0;
    Elf32_Word relr_entry_size = 0;
    Elf32_Addr data_lo;
    Elf32_Addr data_hi;
    Elf32_Addr next;
    Elf32_Word offset;
    Elf32_Word other_offset;
    Elf32_Addr last = 0;

    /* _start passes the bounds of the data, which is all that relocations may change. */
    if (data_start < image_base || data_end < data_start || (uintptr_t)dynamic < data_start ||
            (uintptr_t)dynamic > data_end ||
            ((uintptr_t)dynamic & (__alignof__(Elf32_Dyn) - 1)) != 0) {
        return LOAD_ERROR;
    }
    data_lo = data_start - image_base;
    data_hi = data_end - image_base;

    for (;; dynamic++) {
        /* Read anew by every test, so that the tests cannot become a jump table. */
        volatile Elf32_Sword tag;

        /* DT_NULL must come before the data ends. */
        if (data_end - (uintptr_t)dynamic < sizeof(Elf32_Dyn)) {
            return LOAD_ERROR;
        }
        tag = dynamic->d_tag;
        if (tag == DT_NULL) {
            break;
        }
        if (tag == DT_REL && !has_table) {
            table = dynamic->d_un.d_ptr;
            has_table = true;
        } else if (tag == DT_RELSZ && !has_size) {
            size = dynamic->d_un.d_val;
            has_size = true;
        } else if (tag == DT_RELENT && !has_entry_size) {
            entry_size = dynamic->d_un.d_val;
            has_entry_size = true;
        } else if (tag == DT_RELR && !has_relr_table) {
            relr_table = dynamic->d_un.d_ptr;
            has_relr_table = true;
        } else if (tag == DT_RELRSZ && !has_relr_size) {
            relr_size = dynamic->d_un.d_val;
            has_relr_size = true;
        } else if (tag == DT_RELRENT && !has_relr_entry_size) {
            relr_entry_size = dynamic->d_un.d_val;
            has_relr_entry_size = true;
        } else if (tag != DT_RELCOUNT && tag != DT_HASH && tag != DT_GNU_HASH &&
                tag != DT_STRTAB && tag != DT_SYMTAB && tag != DT_STRSZ && tag != DT_SYMENT &&
                tag != DT_PLTGOT && tag != DT_DEBUG && tag != DT_SYMBOLIC && tag != DT_BIND_NOW &&
                tag != DT_FLAGS && tag != DT_FLAGS_1 && tag != DT_INIT && tag != DT_FINI &&
                tag != DT_INIT_ARRAY && tag != DT_INIT_ARRAYSZ && tag != DT_FINI_ARRAY &&
                tag != DT_FINI_ARRAYSZ && tag != DT_PREINIT_ARRAY && tag != DT_PREINIT_ARRAYSZ) {
            /* Any other tag, or a table given twice, may mean relocations not applied here. */
            return LOAD_ERROR;
        }
    }

    /* Either table may be left out, but not in part, and must lie aligned before the data. */
    if (has_table != has_size || has_table != has_entry_size ||
            (has_table && (entry_size != sizeof(Elf32_Rel) || size > data_lo ||
            table > data_lo - size ||
            ((image_base + table) & (__alignof__(Elf32_Rel) - 1)) != 0))) {
        return LOAD_ERROR;
    }
    if (has_relr_table != has_relr_size || has_relr_table != has_relr_entry_size ||
            (has_relr_table && (relr_entry_size != sizeof(Elf32_Relr) || relr_size > data_lo ||
            relr_table > data_lo - relr_size ||
            ((image_base + relr_table) & (__alignof__(Elf32_Relr) - 1)) != 0))) {
        return LOAD_ERROR;
    }

    /* Every entry is checked before any is applied, so that a refused image is left as it was. */
    if (has_table) {
        next = data_lo;
        for (offset = 0; size - offset >= entry_size; offset += entry_size) {
            const Elf32_Rel *entry = (const Elf32_Rel *)(image_base + table + offset);
            Elf32_Word type = ELF32_R_TYPE(entry->r_info);

            if (type == R_386_NONE) {
                continue;
            }
            /* Relative only, each in the data and after the last, as linkers sort them. */
            if (type != R_386_RELATIVE || ELF32_R_SYM(entry->r_info) != 0 ||
                    entry->r_offset < next || entry->r_offset > data_hi - sizeof(Elf32_Addr)) {
                return LOAD_ERROR;
            }
            next = entry->r_offset + sizeof(Elf32_Addr);
        }
        /* A partial last entry, found without a division, which may be a library call. */
        if (offset != size) {
            return LOAD_ERROR;
        }
    }
    /*
     * An even RELR entry is the address of a word to relocate, and an odd one is a bitmap of the
     * words after the last that an entry covered, bit n standing for the nth. Nor may a word
     * overlap the other table's, which is walked alongside.
     */
    if (has_relr_table) {
        next = data_lo;
        other_offset = 0;
        for (offset = 0; relr_size - offset >= relr_entry_size; offset += relr_entry_size) {
            Elf32_Relr entry = *(const Elf32_Relr *)(image_base + relr_table + offset);
            Elf32_Addr word;
            Elf32_Relr bits;

            if ((entry & 1) == 0) {
                word = entry;
                bits = 1;
                last = entry;
            } else {
                /* A bitmap carries on from an address in the data, so it cannot come first. */
                if (offset == 0 || last >= data_hi) {
                    return LOAD_ERROR;
                }
                word = last + sizeof(Elf32_Addr);
                bits = entry >> 1;
                last += (sizeof(entry) * 8 - 1) * sizeof(Elf32_Addr);
            }
            for (; bits != 0; bits >>= 1, word += sizeof(Elf32_Addr)) {
                if ((bits & 1) == 0) {
                    continue;
                }
                if (word < next || word > data_hi - sizeof(Elf32_Addr)) {
                    return LOAD_ERROR;
                }
                next = word + sizeof(Elf32_Addr);
                for (; has_table && size - other_offset >= entry_size;
                        other_offset += entry_size) {
                    const Elf32_Rel *other =
                        (const Elf32_Rel *)(image_base + table + other_offset);

                    if (ELF32_R_TYPE(other->r_info) != R_386_NONE &&
                            other->r_offset + sizeof(Elf32_Addr) > word) {
                        if (other->r_offset < next) {
                            return LOAD_ERROR;
                        }
                        break;
                    }
                }
            }
        }
        if (offset != relr_size) {
            return LOAD_ERROR;
        }
    }

    if (has_table) {
        for (offset = 0; size - offset >= entry_size; offset += entry_size) {
            const Elf32_Rel *entry = (const Elf32_Rel *)(image_base + table + offset);

            if (ELF32_R_TYPE(entry->r_info) == R_386_RELATIVE) {
                struct unaligned_addr *target =
                    (struct unaligned_addr *)(image_base + entry->r_offset);

                target->value += image_base;
            }
        }
    }
    if (has_relr_table) {
        for (offset = 0; relr_size - offset >= relr_entry_size; offset += relr_entry_size) {
            Elf32_Relr entry = *(const Elf32_Relr *)(image_base + relr_table + offset);
            Elf32_Addr word;
            Elf32_Relr bits;

            if ((entry & 1) == 0) {
                word = entry;
                bits = 1;
                last = entry;
            } else {
                word = last + sizeof(Elf32_Addr);
                bits = entry >> 1;
                last += (sizeof(entry) * 8 - 1) * sizeof(Elf32_Addr);
            }
            for (; bits != 0; bits >>= 1, word += sizeof(Elf32_Addr)) {
                if ((bits & 1) != 0) {
                    struct unaligned_addr *target = (struct unaligned_addr *)(image_base + word);

                    target->value += image_base;
                }
            }
        }
    }
    return 0;
}
