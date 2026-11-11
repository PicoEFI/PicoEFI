#ifndef EFI_EFIDEF_H_
#define EFI_EFIDEF_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if !defined(__x86_64__) && !defined(__amd64__) && !defined(__i386__) && \
    !defined(__aarch64__) && !defined(__arm__) && !defined(__riscv) && !defined(__loongarch__)
#error "PicoEFI does not support the target architecture."
#endif

/* UEFI enumerations are 32-bit; bare-metal Arm toolchains default to short ones. */
#if defined(__ARM_SIZEOF_MINIMAL_ENUM) && __ARM_SIZEOF_MINIMAL_ENUM != 4
#error "UEFI enumerations are 32-bit: compile with -fno-short-enums."
#endif

#ifndef EFI_API
#if defined(__x86_64__) || defined(__amd64__)
#define EFI_API __attribute__((__ms_abi__))
#elif defined(__i386__)
/*
 * Plain cdecl, whatever -mrtd or -mregparm the rest of the program uses. regparm(0) comes first:
 * Clang 9 crashes on the other order when a macro supplies it.
 */
#define EFI_API __attribute__((__regparm__(0), __cdecl__))
#elif defined(__arm__)
/* Base standard: floating-point values go in core registers, whatever the program's float ABI. */
#define EFI_API __attribute__((__pcs__("aapcs")))
#else
/* The platform's standard calling convention is the UEFI one. */
#define EFI_API
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SIZEOF_INT128__)
__extension__ typedef __int128 EFI_INT128;
__extension__ typedef unsigned __int128 EFI_UINT128;
#else
/* No 128-bit integer type on 32-bit targets. */
typedef struct __attribute__((__aligned__(16))) {
    uint64_t Lo;
    uint64_t Hi;
} EFI_INT128;

typedef struct __attribute__((__aligned__(16))) {
    uint64_t Lo;
    uint64_t Hi;
} EFI_UINT128;
#endif

typedef uintptr_t EFI_STATUS;

#define EFI_ERROR_MASK (~((uintptr_t)-1 >> 1))
#define EFI_ERR(a) ((EFI_STATUS)(EFI_ERROR_MASK | (a)))
#define EFI_ERR_OEM(a) ((EFI_STATUS)(~((uintptr_t)-1 >> 2) | (a)))

typedef void *EFI_HANDLE;
typedef void *EFI_EVENT;
typedef uint64_t EFI_LBA;
typedef uintptr_t EFI_TPL;

typedef struct {
    uint8_t Addr[32];
} EFI_MAC_ADDRESS;

typedef struct {
    uint8_t Addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
    uint8_t Addr[16];
} EFI_IPv6_ADDRESS;

typedef union {
    uint32_t Addr[4];
    EFI_IPv4_ADDRESS v4;
    EFI_IPv6_ADDRESS v6;
} EFI_IP_ADDRESS;

/* Natural 4-byte alignment: the specification's 64-bit boundary is about buffers, not the type. */
typedef struct {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
} EFI_GUID;

typedef struct {
    uint16_t Year;
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
    uint8_t Pad1;
    uint32_t Nanosecond;
    int16_t TimeZone;
    uint8_t Daylight;
    uint8_t Pad2;
} EFI_TIME;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02

#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

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
    uint32_t Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} EFI_MEMORY_DESCRIPTOR;

/* UEFI aligns 64-bit fields to 8 bytes, which the IA-32 ABI does only with -malign-double. */
#if (defined(__cplusplus) && __cplusplus >= 201103L) || \
    (!defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
static_assert(sizeof(EFI_MEMORY_DESCRIPTOR) == 40, "Build with -malign-double on IA-32.");
#elif !defined(__cplusplus) && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
_Static_assert(sizeof(EFI_MEMORY_DESCRIPTOR) == 40, "Build with -malign-double on IA-32.");
#endif

#define EFI_OS_INDICATIONS_BOOT_TO_FW_UI 0x0000000000000001
#define EFI_OS_INDICATIONS_TIMESTAMP_REVOCATION 0x0000000000000002
#define EFI_OS_INDICATIONS_FILE_CAPSULE_DELIVERY_SUPPORTED 0x0000000000000004
#define EFI_OS_INDICATIONS_FMP_CAPSULE_SUPPORTED 0x0000000000000008
#define EFI_OS_INDICATIONS_CAPSULE_RESULT_VAR_SUPPORTED 0x0000000000000010
#define EFI_OS_INDICATIONS_START_OS_RECOVERY 0x0000000000000020
#define EFI_OS_INDICATIONS_START_PLATFORM_RECOVERY 0x0000000000000040
#define EFI_OS_INDICATIONS_JSON_CONFIG_DATA_REFRESH 0x0000000000000080

typedef struct {
    uint32_t ReceivedQueueTimeoutValue;
    uint32_t TransmitQueueTimeoutValue;
    uint16_t ProtocolTypeFilter;
    uint8_t EnableUnicastReceive;
    uint8_t EnableMulticastReceive;
    uint8_t EnableBroadcastReceive;
    uint8_t EnablePromiscuousReceive;
    uint8_t FlushQueuesOnReset;
    uint8_t EnableReceiveTimestamps;
    uint8_t DisableBackgroundPolling;
} EFI_MANAGED_NETWORK_CONFIG_DATA;

#define EFI_PAGE_SIZE 4096
#define EFI_PAGE_MASK 0xFFF
#define EFI_PAGE_SHIFT 12

/* Rounds up without computing a + EFI_PAGE_MASK, which could overflow. */
#define EFI_SIZE_TO_PAGES(a) (((a) >> EFI_PAGE_SHIFT) + (((a) & EFI_PAGE_MASK) ? 1 : 0))

#define EFI_SIGNATURE_16(A, B) ((uint16_t)((uint8_t)(A) | ((uint8_t)(B) << 8)))
#define EFI_SIGNATURE_32(A, B, C, D) \
    ((uint32_t)(EFI_SIGNATURE_16(A, B) | ((uint32_t)EFI_SIGNATURE_16(C, D) << 16)))
#define EFI_SIGNATURE_64(A, B, C, D, E, F, G, H) \
    ((uint64_t)(EFI_SIGNATURE_32(A, B, C, D) | ((uint64_t)EFI_SIGNATURE_32(E, F, G, H) << 32)))

#ifdef __cplusplus
}
#endif

#endif
