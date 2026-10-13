#ifndef EFI_LOONGARCH64_EFIBIND_H_
#define EFI_LOONGARCH64_EFIBIND_H_

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
typedef uint64_t EFI_UINT64;
typedef int64_t EFI_INT64;

__extension__ typedef __int128 EFI_INT128;
__extension__ typedef unsigned __int128 EFI_UINT128;

typedef uint64_t EFI_UINTN;
typedef int64_t EFI_INTN;

typedef unsigned char EFI_CHAR8;
typedef uint16_t EFI_CHAR16;

#undef EFI_VOID
typedef void EFI_VOID;

/* The platform's standard calling convention is the UEFI one. */
#ifndef EFI_API
#define EFI_API
#endif

#define EFI_ERROR_MASK ((EFI_UINTN)0x8000000000000000)
#define EFI_ERR(a) ((EFI_STATUS)(EFI_ERROR_MASK | (a)))
#define EFI_ERR_OEM(a) ((EFI_STATUS)(0xc000000000000000 | (a)))

#ifdef __cplusplus
}
#endif

#endif
