#ifndef EFI_ELF_H_
#define EFI_ELF_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Word;
typedef int32_t Elf32_Sword;

typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Xword;
typedef int64_t Elf64_Sxword;

typedef struct {
    Elf32_Sword d_tag;
    union {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;

typedef struct {
    Elf64_Sxword d_tag;
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
} Elf64_Dyn;

typedef struct {
    Elf32_Addr r_offset;
    Elf32_Word r_info;
} Elf32_Rel;

typedef struct {
    Elf32_Addr r_offset;
    Elf32_Word r_info;
    Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct {
    Elf64_Addr r_offset;
    Elf64_Xword r_info;
    Elf64_Sxword r_addend;
} Elf64_Rela;

typedef Elf32_Word Elf32_Relr;
typedef Elf64_Xword Elf64_Relr;

#define DT_NULL 0
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_JMPREL 23
#define DT_RELRSZ 35
#define DT_RELR 36
#define DT_RELRENT 37

#define ELF32_R_TYPE(i) ((unsigned char)(i))
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

#ifdef __cplusplus
}
#endif

#endif
