#ifndef EFI_ARM_EFIBIND_H_
#define EFI_ARM_EFIBIND_H_

#include <stdint.h>

/* UEFI enumerations are 32-bit; bare-metal Arm toolchains default to short ones. */
#if defined(__ARM_SIZEOF_MINIMAL_ENUM) && __ARM_SIZEOF_MINIMAL_ENUM != 4
#error "UEFI enumerations are 32-bit: compile with -fno-short-enums"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t EFI_UINT8;
typedef int8_t EFI_INT8;
typedef uint16_t EFI_UINT16;
typedef int16_t EFI_INT16;
typedef uint32_t EFI_UINT32;
typedef int32_t EFI_INT32;
typedef uint64_t EFI_UINT64;
typedef int64_t EFI_INT64;

/* No 128-bit integer type on AArch32. */
typedef struct __attribute__((__aligned__(16))) {
    EFI_UINT64 Lo;
    EFI_UINT64 Hi;
} EFI_INT128;

typedef struct __attribute__((__aligned__(16))) {
    EFI_UINT64 Lo;
    EFI_UINT64 Hi;
} EFI_UINT128;

typedef uint32_t EFI_UINTN;
typedef int32_t EFI_INTN;

typedef unsigned char EFI_CHAR8;
typedef uint16_t EFI_CHAR16;

#undef EFI_VOID
typedef void EFI_VOID;

/* Base standard: floating-point values go in core registers, whatever the program's float ABI. */
#ifndef EFI_API
#define EFI_API __attribute__((__pcs__("aapcs")))
#endif

#define EFI_ERROR_MASK ((EFI_UINTN)0x80000000)
#define EFI_ERR(a) ((EFI_STATUS)(EFI_ERROR_MASK | (a)))
#define EFI_ERR_OEM(a) ((EFI_STATUS)(0xc0000000 | (a)))

#ifdef __cplusplus
}
#endif

#endif
