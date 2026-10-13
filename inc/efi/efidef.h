#ifndef EFI_EFIDEF_H_
#define EFI_EFIDEF_H_

#if defined(__x86_64__) || defined(__amd64__)
#include "x86_64/efibind.h"
#elif defined(__i386__)
#include "ia32/efibind.h"
#elif defined(__aarch64__)
#include "aarch64/efibind.h"
#elif defined(__arm__)
#include "arm/efibind.h"
#elif defined(__riscv) && __riscv_xlen == 64
#include "riscv64/efibind.h"
#elif defined(__riscv) && __riscv_xlen == 32
#include "riscv32/efibind.h"
#elif defined(__loongarch64) || (defined(__loongarch__) && __loongarch_grlen == 64)
#include "loongarch64/efibind.h"
#elif defined(__loongarch__) && __loongarch_grlen == 32
#include "loongarch32/efibind.h"
#else
#error "efidef.h: unsupported target architecture"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
typedef bool EFI_BOOLEAN;
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
typedef _Bool EFI_BOOLEAN;
#else
typedef unsigned char EFI_BOOLEAN;
#endif

#ifndef EFI_TRUE
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#define EFI_TRUE true
#else
#define EFI_TRUE ((EFI_BOOLEAN)1)
#endif
#endif

#ifndef EFI_FALSE
#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#define EFI_FALSE false
#else
#define EFI_FALSE ((EFI_BOOLEAN)0)
#endif
#endif

#ifndef NULL
#if (defined(__cplusplus) && __cplusplus >= 201103L) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
#define NULL nullptr
#elif defined(__cplusplus)
#define NULL 0
#else
#define NULL ((EFI_VOID *)0)
#endif
#endif

#ifndef EFI_CONST
#define EFI_CONST const
#endif

#ifndef EFI_IN
#define EFI_IN
#endif

#ifndef EFI_OUT
#define EFI_OUT
#endif

#ifndef EFI_OPTIONAL
#define EFI_OPTIONAL
#endif

typedef EFI_UINTN EFI_STATUS;
typedef EFI_VOID *EFI_HANDLE;
typedef EFI_VOID *EFI_EVENT;
typedef EFI_UINT64 EFI_LBA;
typedef EFI_UINTN EFI_TPL;

typedef struct {
    EFI_UINT8 Addr[32];
} EFI_MAC_ADDRESS;

typedef struct {
    EFI_UINT8 Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
    EFI_UINT8 Addr[16];
} EFI_IPv6_ADDRESS;

typedef union {
    EFI_UINT32 Addr[4];
    EFI_IPv4_ADDRESS v4;
    EFI_IPv6_ADDRESS v6;
} EFI_IP_ADDRESS;

/* Natural 4-byte alignment: the specification's 64-bit boundary is about buffers, not the type. */
typedef struct {
    EFI_UINT32 Data1;
    EFI_UINT16 Data2;
    EFI_UINT16 Data3;
    EFI_UINT8 Data4[8];
} EFI_GUID;

typedef struct {
    EFI_UINT16 Year;
    EFI_UINT8 Month;
    EFI_UINT8 Day;
    EFI_UINT8 Hour;
    EFI_UINT8 Minute;
    EFI_UINT8 Second;
    EFI_UINT8 Pad1;
    EFI_UINT32 Nanosecond;
    EFI_INT16 TimeZone;
    EFI_UINT8 Daylight;
    EFI_UINT8 Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef EFI_UINT64 EFI_PHYSICAL_ADDRESS;
typedef EFI_UINT64 EFI_VIRTUAL_ADDRESS;

typedef enum {
    EfiAllocateAnyPages,
    EfiAllocateMaxAddress,
    EfiAllocateAddress,
    EfiMaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

#define EFI_MEMORY_UC 0x0000000000000001
#define EFI_MEMORY_WC 0x0000000000000002
#define EFI_MEMORY_WT 0x0000000000000004
#define EFI_MEMORY_WB 0x0000000000000008
#define EFI_MEMORY_UCE 0x0000000000000010
#define EFI_MEMORY_WP 0x0000000000001000
#define EFI_MEMORY_RP 0x0000000000002000
#define EFI_MEMORY_XP 0x0000000000004000
#define EFI_MEMORY_NV 0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_RO 0x0000000000020000
#define EFI_MEMORY_SP 0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO 0x0000000000080000
#define EFI_MEMORY_HOT_PLUGGABLE 0x0000000000100000
#define EFI_MEMORY_RUNTIME 0x8000000000000000
#define EFI_MEMORY_ISA_VALID 0x4000000000000000
#define EFI_MEMORY_ISA_MASK 0x0FFFF00000000000

#define EFI_MEMORY_DESCRIPTOR_VERSION 1

typedef struct {
    EFI_UINT32 Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    EFI_UINT64 NumberOfPages;
    EFI_UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI 0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION 0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED 0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED 0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED 0x0000000000000010
#define EFI_OS_INDICATIONS_START_OS_RECOVERY 0x0000000000000020
#define EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY 0x0000000000000040
#define EFI_OS_INDICATIONS_JSON_CONFIG_DATA_REFRESH 0x0000000000000080

typedef struct {
    EFI_UINT32 ReceivedQueueTimeoutValue;
    EFI_UINT32 TransmitQueueTimeoutValue;
    EFI_UINT16 ProtocolTypeFilter;
    EFI_BOOLEAN EnableUnicastReceive;
    EFI_BOOLEAN EnableMulticastReceive;
    EFI_BOOLEAN EnableBroadcastReceive;
    EFI_BOOLEAN EnablePromiscuousReceive;
    EFI_BOOLEAN FlushQueuesOnReset;
    EFI_BOOLEAN EnableReceiveTimestamps;
    EFI_BOOLEAN DisableBackgroundPolling;
} EFI_MANAGED_NETWORK_CONFIG_DATA;

#define EFI_PAGE_SIZE 4096
#define EFI_PAGE_MASK 0xFFF
#define EFI_PAGE_SHIFT 12

/* Rounds up without computing a + EFI_PAGE_MASK, which could overflow. */
#define EFI_SIZE_TO_PAGES(a) (((a) >> EFI_PAGE_SHIFT) + (((a) & EFI_PAGE_MASK) ? 1 : 0))

#define EFI_SIGNATURE_16(A, B) ((EFI_UINT16)((EFI_UINT8)(A) | ((EFI_UINT8)(B) << 8)))
#define EFI_SIGNATURE_32(A, B, C, D) \
    ((EFI_UINT32)(EFI_SIGNATURE_16(A, B) | ((EFI_UINT32)EFI_SIGNATURE_16(C, D) << 16)))
#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    ((EFI_UINT64)(EFI_SIGNATURE_32(A, B, C, D) | ((EFI_UINT64)EFI_SIGNATURE_32(E, F, G, H) << 32)))

#ifdef __cplusplus
}
#endif

#endif
