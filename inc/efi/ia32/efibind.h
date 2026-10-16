#ifndef EFI_IA32_EFIBIND_H_
#define EFI_IA32_EFIBIND_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t EFI_UINT8;
typedef int8_t EFI_INT8;
typedef uint16_t EFI_UINT16;
typedef int16_t EFI_INT16;
typedef uint32_t EFI_UINT32;
typedef int32_t EFI_INT32;

/* UEFI wants 64-bit members naturally aligned; the i386 ABI aligns them to 4 in structures. */
typedef uint64_t EFI_UINT64 __attribute__((__aligned__(8)));
typedef int64_t EFI_INT64 __attribute__((__aligned__(8)));

/* No 128-bit integer type on ia32. */
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

/*
 * Plain cdecl, whatever -mrtd or -mregparm the rest of the program uses. regparm(0) comes first:
 * Clang 9 crashes on the other order when a macro supplies it.
 */
#ifndef EFI_API
#define EFI_API __attribute__((__regparm__(0), __cdecl__))
#endif

#define EFI_ERROR_MASK ((EFI_UINTN)0x80000000)
#define EFI_ERR(a) ((EFI_STATUS)(EFI_ERROR_MASK | (a)))
#define EFI_ERR_OEM(a) ((EFI_STATUS)(0xc0000000 | (a)))

#ifdef __cplusplus
}
#endif

#endif
