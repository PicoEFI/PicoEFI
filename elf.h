#ifndef EFI_ELF_H_
#define EFI_ELF_H_

#include <stdint.h>

struct elf32_dyn {
    int32_t d_tag;
    union {
        uint32_t d_val;
        uint32_t d_ptr;
    } d_un;
};

struct elf64_dyn {
    int64_t d_tag;
    union {
        uint64_t d_val;
        uint64_t d_ptr;
    } d_un;
};

struct elf32_rel {
    uint32_t r_offset;
    uint32_t r_info;
};

struct elf32_rela {
    uint32_t r_offset;
    uint32_t r_info;
    int32_t r_addend;
};

struct elf64_rela {
    uint64_t r_offset;
    uint64_t r_info;
    int64_t r_addend;
};

#define DT_NULL 0
#define DT_PLTGOT 3
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_STRSZ 10
#define DT_SYMENT 11
#define DT_INIT 12
#define DT_FINI 13
#define DT_SYMBOLIC 16
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_DEBUG 21
#define DT_JMPREL 23
#define DT_BIND_NOW 24
#define DT_INIT_ARRAY 25
#define DT_FINI_ARRAY 26
#define DT_INIT_ARRAYSZ 27
#define DT_FINI_ARRAYSZ 28
#define DT_FLAGS 30
#define DT_PREINIT_ARRAY 32
#define DT_PREINIT_ARRAYSZ 33
#define DT_RELRSZ 35
#define DT_RELR 36
#define DT_RELRENT 37
#define DT_GNU_HASH 0x6ffffef5
#define DT_RELACOUNT 0x6ffffff9
#define DT_RELCOUNT 0x6ffffffa
#define DT_FLAGS_1 0x6ffffffb

#define ELF32_R_SYM(i) ((i) >> 8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i) & 0xffffffffL)

#define R_386_NONE 0
#define R_386_RELATIVE 8

#define R_X86_64_NONE 0
#define R_X86_64_RELATIVE 8

#define R_AARCH64_NONE 0
#define R_AARCH64_RELATIVE 1027

#define R_RISCV_NONE 0
#define R_RISCV_RELATIVE 3

#define R_LARCH_NONE 0
#define R_LARCH_RELATIVE 3

#define R_ARM_NONE 0
#define R_ARM_RELATIVE 23

#endif
