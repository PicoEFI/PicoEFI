#ifndef EFI_EFICPER_H
#define EFI_EFICPER_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ERROR_RECORD_SIGNATURE_START EFI_SIGNATURE_32('C', 'P', 'E', 'R')
#define EFI_ERROR_RECORD_SIGNATURE_END 0xffffffff

#define EFI_ERROR_RECORD_REVISION 0x0101

#define EFI_GENERIC_ERROR_RECOVERABLE 0
#define EFI_GENERIC_ERROR_FATAL 1
#define EFI_GENERIC_ERROR_CORRECTED 2
#define EFI_GENERIC_ERROR_INFO 3

#define EFI_ERROR_RECORD_HEADER_PLATFORM_ID_VALID 0x00000001
#define EFI_ERROR_RECORD_HEADER_TIME_STAMP_VALID 0x00000002
#define EFI_ERROR_RECORD_HEADER_PARTITION_ID_VALID 0x00000004

struct efi_error_time_stamp {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t flag;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t century;
} __attribute__((__packed__));

#define EFI_ERROR_TIME_STAMP_PRECISE 0x01

#define EFI_EVENT_NOTIFICATION_TYPE_CMC_GUID \
    {0x2dce8bb1, 0xbdd7, 0x450e, {0xb9, 0xad, 0x9c, 0xf4, 0xeb, 0xd4, 0xf8, 0x90}}

#define EFI_EVENT_NOTIFICATION_TYPE_CPE_GUID \
    {0x4e292f96, 0xd843, 0x4a55, {0xa8, 0xc2, 0xd4, 0x81, 0xf2, 0x7e, 0xbe, 0xee}}

#define EFI_EVENT_NOTIFICATION_TYPE_MCE_GUID \
    {0xe8f56ffe, 0x919c, 0x4cc5, {0xba, 0x88, 0x65, 0xab, 0xe1, 0x49, 0x13, 0xbb}}

#define EFI_EVENT_NOTIFICATION_TYPE_PCIE_GUID \
    {0xcf93c01f, 0x1a16, 0x4dfc, {0xb8, 0xbc, 0x9c, 0x4d, 0xaf, 0x67, 0xc1, 0x04}}

#define EFI_EVENT_NOTIFICATION_TYPE_INIT_GUID \
    {0xcc5263e8, 0x9308, 0x454a, {0x89, 0xd0, 0x34, 0x0b, 0xd3, 0x9b, 0xc9, 0x8e}}

#define EFI_EVENT_NOTIFICATION_TYPE_NMI_GUID \
    {0x5bad89ff, 0xb7e6, 0x42c9, {0x81, 0x4a, 0xcf, 0x24, 0x85, 0xd6, 0xe9, 0x8a}}

#define EFI_EVENT_NOTIFICATION_TYPE_BOOT_GUID \
    {0x3d61a466, 0xab40, 0x409a, {0xa6, 0x98, 0xf3, 0x62, 0xd4, 0x64, 0xb3, 0x8f}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_GUID \
    {0x667dd791, 0xc6b3, 0x4c27, {0x8a, 0x6b, 0x0f, 0x8e, 0x72, 0x2d, 0xeb, 0x41}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_SEA \
    {0x9a78788a, 0xbbe8, 0x11e4, {0x80, 0x9e, 0x67, 0x61, 0x1e, 0x5d, 0x46, 0xb0}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_SEI \
    {0x5c284c81, 0xb0ae, 0x4e87, {0xa3, 0x22, 0xb0, 0x4c, 0x85, 0x62, 0x43, 0x23}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_PEI \
    {0x09a9d5ac, 0x5204, 0x4214, {0x96, 0xe5, 0x94, 0x99, 0x2e, 0x75, 0x2b, 0xcd}}

#define EFI_EVENT_NOTIFICATION_TYPE_CXL_COMPONENT_GUID \
    {0x69293bc9, 0x41df, 0x49a3, {0xb4, 0xbd, 0x4f, 0xb0, 0xdb, 0x30, 0x41, 0xf6}}

#define EFI_HW_ERROR_FLAGS_RECOVERED 0x00000001
#define EFI_HW_ERROR_FLAGS_PREVERR 0x00000002
#define EFI_HW_ERROR_FLAGS_SIMULATED 0x00000004

// section_count struct efi_error_section_descriptor follow, then the section
// bodies.
struct efi_common_error_record_header {
    uint32_t signature_start;
    uint16_t revision;
    uint32_t signature_end;
    uint16_t section_count;
    uint32_t error_severity;
    uint32_t validation_bits;
    uint32_t record_length;
    struct efi_error_time_stamp time_stamp;
    struct efi_guid platform_id;
    struct efi_guid partition_id;
    struct efi_guid creator_id;
    struct efi_guid notification_type;
    uint64_t record_id;
    uint32_t flags;
    uint64_t persistence_info;
    uint8_t resv1[12];
} __attribute__((__packed__));

struct efi_generic_error_status {
    uint64_t status;
} __attribute__((__packed__));

#define EFI_GENERIC_ERROR_STATUS_TYPE_SHIFT 8
#define EFI_GENERIC_ERROR_STATUS_TYPE_MASK 0x000000000000ff00
#define EFI_GENERIC_ERROR_STATUS_ADDRESS_SIGNAL 0x0000000000010000
#define EFI_GENERIC_ERROR_STATUS_CONTROL_SIGNAL 0x0000000000020000
#define EFI_GENERIC_ERROR_STATUS_DATA_SIGNAL 0x0000000000040000
#define EFI_GENERIC_ERROR_STATUS_DETECTED_BY_RESPONDER 0x0000000000080000
#define EFI_GENERIC_ERROR_STATUS_DETECTED_BY_REQUESTER 0x0000000000100000
#define EFI_GENERIC_ERROR_STATUS_FIRST_ERROR 0x0000000000200000
#define EFI_GENERIC_ERROR_STATUS_OVERFLOW_NOT_LOGGED 0x0000000000400000

#define EFI_ERROR_INTERNAL ((uint32_t)1)
#define EFI_ERROR_BUS ((uint32_t)16)
#define EFI_ERROR_MEM_STORAGE ((uint32_t)4)
#define EFI_ERROR_TLB_STORAGE ((uint32_t)5)
#define EFI_ERROR_CACHE_STORAGE ((uint32_t)6)
#define EFI_ERROR_FUNCTIONAL_UNIT ((uint32_t)7)
#define EFI_ERROR_SELFTEST ((uint32_t)8)
#define EFI_ERROR_OVERFLOW ((uint32_t)9)
#define EFI_ERROR_VIRTUAL_MAP ((uint32_t)17)
#define EFI_ERROR_ACCESS_INVALID ((uint32_t)18)
#define EFI_ERROR_UNIMPL_ACCESS ((uint32_t)19)
#define EFI_ERROR_LOSS_OF_LOCKSTEP ((uint32_t)20)
#define EFI_ERROR_RESPONSE_INVALID ((uint32_t)21)
#define EFI_ERROR_PARITY ((uint32_t)22)
#define EFI_ERROR_PROTOCOL ((uint32_t)23)
#define EFI_ERROR_PATH ((uint32_t)24)
#define EFI_ERROR_TIMEOUT ((uint32_t)25)
#define EFI_ERROR_POISONED ((uint32_t)26)

#define EFI_ERROR_SECTION_REVISION 0x0100

#define EFI_ERROR_SECTION_FRU_ID_VALID 0x01
#define EFI_ERROR_SECTION_FRU_STRING_VALID 0x02

#define EFI_ERROR_SECTION_FLAGS_PRIMARY 0x00000001
#define EFI_ERROR_SECTION_FLAGS_CONTAINMENT_WARNING 0x00000002
#define EFI_ERROR_SECTION_FLAGS_RESET 0x00000004
#define EFI_ERROR_SECTION_FLAGS_ERROR_THRESHOLD_EXCEEDED 0x00000008
#define EFI_ERROR_SECTION_FLAGS_RESOURCE_NOT_ACCESSIBLE 0x00000010
#define EFI_ERROR_SECTION_FLAGS_LATENT_ERROR 0x00000020
#define EFI_ERROR_SECTION_FLAGS_PROPAGATED 0x00000040
#define EFI_ERROR_SECTION_FLAGS_OVERFLOW 0x00000080

#define EFI_ERROR_SECTION_PROCESSOR_GENERIC_GUID \
    {0x9876ccad, 0x47b4, 0x4bdb, {0xb6, 0x5e, 0x16, 0xf1, 0x93, 0xc4, 0xf3, 0xdb}}

#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_IA32X64_GUID \
    {0xdc3ea0b0, 0xa144, 0x4797, {0xb9, 0x5b, 0x53, 0xfa, 0x24, 0x2b, 0x6e, 0x1d}}

// Misprinted with nine trailing bytes; this is the SAL processor device error
// section GUID.
#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_IPF_GUID \
    {0xe429faf1, 0x3cb7, 0x11d4, {0xbc, 0xa7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}

#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_ARM_GUID \
    {0xe19e3d16, 0xbc11, 0x11e4, {0x9c, 0xaa, 0xc2, 0x05, 0x1d, 0x5d, 0x46, 0xb0}}

#define EFI_ERROR_SECTION_PLATFORM_MEMORY_GUID \
    {0xa5bc1114, 0x6f64, 0x4ede, {0xb8, 0x63, 0x3e, 0x83, 0xed, 0x7c, 0x83, 0xb1}}

#define EFI_ERROR_SECTION_PLATFORM_MEMORY2_GUID \
    {0x61ec04fc, 0x48e6, 0xd813, {0x25, 0xc9, 0x8d, 0xaa, 0x44, 0x75, 0x0b, 0x12}}

#define EFI_ERROR_SECTION_PCIE_GUID \
    {0xd995e954, 0xbbc1, 0x430f, {0xad, 0x91, 0xb4, 0x4d, 0xcb, 0x3c, 0x6f, 0x35}}

#define EFI_ERROR_SECTION_FW_ERROR_RECORD_GUID \
    {0x81212a96, 0x09ed, 0x4996, {0x94, 0x71, 0x8d, 0x72, 0x9c, 0x8e, 0x69, 0xed}}

#define EFI_ERROR_SECTION_PCI_PCIX_BUS_GUID \
    {0xc5753963, 0x3b84, 0x4095, {0xbf, 0x78, 0xed, 0xda, 0xd3, 0xf9, 0xc9, 0xdd}}

#define EFI_ERROR_SECTION_PCI_DEVICE_GUID \
    {0xeb5e4685, 0xca66, 0x4769, {0xb6, 0xa2, 0x26, 0x06, 0x8b, 0x00, 0x13, 0x26}}

#define EFI_ERROR_SECTION_DMAR_GENERIC_GUID \
    {0x5b51fef7, 0xc79d, 0x4434, {0x8f, 0x1b, 0xaa, 0x62, 0xde, 0x3e, 0x2c, 0x64}}

#define EFI_ERROR_SECTION_DIRECTED_IO_DMAR_GUID \
    {0x71761d37, 0x32b2, 0x45cd, {0xa7, 0xd0, 0xb0, 0xfe, 0xdd, 0x93, 0xe8, 0xcf}}

#define EFI_ERROR_SECTION_IOMMU_DMAR_GUID \
    {0x036f84e1, 0x7f37, 0x428c, {0xa7, 0x9e, 0x57, 0x5f, 0xdf, 0xaa, 0x84, 0xec}}

#define EFI_ERROR_SECTION_CCIX_PER_LOG_GUID \
    {0x91335ef6, 0xebfb, 0x4478, {0xa6, 0xa6, 0x88, 0xb7, 0x28, 0xcf, 0x75, 0xd7}}

#define EFI_ERROR_SECTION_CXL_PROTOCOL_ERROR_GUID \
    {0x80b9efb4, 0x52b5, 0x4de3, {0xa7, 0x77, 0x68, 0x78, 0x4b, 0x77, 0x10, 0x48}}

#define EFI_ERROR_SECTION_FRU_MEMORY_POISON_GUID \
    {0x5e4706c1, 0x5356, 0x48c6, {0x93, 0x0b, 0x52, 0xf2, 0x12, 0x0a, 0x44, 0x58}}

struct efi_error_section_descriptor {
    uint32_t section_offset;
    uint32_t section_length;
    uint16_t revision;
    uint8_t sec_valid_mask;
    uint8_t resv1;
    uint32_t section_flags;
    struct efi_guid section_type;
    struct efi_guid fru_id;
    uint32_t severity;
    char fru_string[20];
} __attribute__((__packed__));

#define EFI_GENERIC_ERROR_PROC_TYPE_VALID 0x0000000000000001
#define EFI_GENERIC_ERROR_PROC_ISA_VALID 0x0000000000000002
#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_VALID 0x0000000000000004
#define EFI_GENERIC_ERROR_PROC_OPERATION_VALID 0x0000000000000008
#define EFI_GENERIC_ERROR_PROC_FLAGS_VALID 0x0000000000000010
#define EFI_GENERIC_ERROR_PROC_LEVEL_VALID 0x0000000000000020
#define EFI_GENERIC_ERROR_PROC_VERSION_VALID 0x0000000000000040
#define EFI_GENERIC_ERROR_PROC_BRAND_VALID 0x0000000000000080
#define EFI_GENERIC_ERROR_PROC_ID_VALID 0x0000000000000100
#define EFI_GENERIC_ERROR_PROC_TARGET_ADDR_VALID 0x0000000000000200
#define EFI_GENERIC_ERROR_PROC_REQUESTER_ID_VALID 0x0000000000000400
#define EFI_GENERIC_ERROR_PROC_RESPONDER_ID_VALID 0x0000000000000800
#define EFI_GENERIC_ERROR_PROC_INST_IP_VALID 0x0000000000001000

#define EFI_GENERIC_ERROR_PROC_TYPE_IA32_X64 0x00
#define EFI_GENERIC_ERROR_PROC_TYPE_IA64 0x01
#define EFI_GENERIC_ERROR_PROC_TYPE_ARM 0x02

#define EFI_GENERIC_ERROR_PROC_ISA_IA32 0x00
#define EFI_GENERIC_ERROR_PROC_ISA_IA64 0x01
#define EFI_GENERIC_ERROR_PROC_ISA_X64 0x02
#define EFI_GENERIC_ERROR_PROC_ISA_ARM_A32_T32 0x03
#define EFI_GENERIC_ERROR_PROC_ISA_ARM_A64 0x04

#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_UNKNOWN 0x00
#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_CACHE 0x01
#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_TLB 0x02
#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_BUS 0x04
#define EFI_GENERIC_ERROR_PROC_ERROR_TYPE_MICRO_ARCH 0x08

#define EFI_GENERIC_ERROR_PROC_OPERATION_GENERIC 0x00
#define EFI_GENERIC_ERROR_PROC_OPERATION_DATA_READ 0x01
#define EFI_GENERIC_ERROR_PROC_OPERATION_DATA_WRITE 0x02
#define EFI_GENERIC_ERROR_PROC_OPERATION_INSTRUCTION_EXEC 0x03

#define EFI_GENERIC_ERROR_PROC_FLAGS_RESTARTABLE 0x01
#define EFI_GENERIC_ERROR_PROC_FLAGS_PRECISE_IP 0x02
#define EFI_GENERIC_ERROR_PROC_FLAGS_OVERFLOW 0x04
#define EFI_GENERIC_ERROR_PROC_FLAGS_CORRECTED 0x08

struct efi_processor_generic_error_data {
    uint64_t valid_fields;
    uint8_t type;
    uint8_t isa;
    uint8_t error_type;
    uint8_t operation;
    uint8_t flags;
    uint8_t level;
    uint16_t resv1;
    uint64_t version_info;
    char brand_string[128];
    uint64_t apic_id;
    uint64_t target_addr;
    uint64_t requestor_id;
    uint64_t responder_id;
    uint64_t instruction_ip;
} __attribute__((__packed__));

#define EFI_IA32_X64_PROCESSOR_ERROR_APIC_ID_VALID 0x0000000000000001
#define EFI_IA32_X64_PROCESSOR_ERROR_CPU_ID_INFO_VALID 0x0000000000000002

struct efi_ia32_x64_valid_bits {
    uint64_t valid_bits;
} __attribute__((__packed__));

#define EFI_IA32_X64_VALID_BITS_APIC_ID_VALID 0x0000000000000001
#define EFI_IA32_X64_VALID_BITS_CPU_ID_INFO_VALID 0x0000000000000002
#define EFI_IA32_X64_VALID_BITS_ERROR_INFO_NUM_SHIFT 2
#define EFI_IA32_X64_VALID_BITS_ERROR_INFO_NUM_MASK 0x00000000000000fc
#define EFI_IA32_X64_VALID_BITS_CONTEXT_NUM_SHIFT 8
#define EFI_IA32_X64_VALID_BITS_CONTEXT_NUM_MASK 0x0000000000003f00

// The error information and context structures that valid_fields counts
// follow.
struct efi_ia32_x64_processor_error_record {
    uint64_t valid_fields;
    uint64_t apic_id;
    uint8_t cpu_id_info[48];
} __attribute__((__packed__));

#define EFI_IA32_X64_ERROR_TYPE_CACHE_CHECK_GUID \
    {0xa55701f5, 0xe3ef, 0x43de, {0xac, 0x72, 0x24, 0x9b, 0x57, 0x3f, 0xad, 0x2c}}

#define EFI_IA32_X64_ERROR_TYPE_TLB_CHECK_GUID \
    {0xfc06b535, 0x5e1f, 0x4562, {0x9f, 0x25, 0x0a, 0x3b, 0x9a, 0xdb, 0x63, 0xc3}}

#define EFI_IA32_X64_ERROR_TYPE_BUS_CHECK_GUID \
    {0x1cf3f8b3, 0xc5b1, 0x49a2, {0xaa, 0x59, 0x5e, 0xef, 0x92, 0xff, 0xa6, 0x3c}}

#define EFI_IA32_X64_ERROR_TYPE_MS_CHECK_GUID \
    {0x48ab7f57, 0xdc34, 0x4f6c, {0xa7, 0xd3, 0xb0, 0xb5, 0xb0, 0xa7, 0x43, 0x14}}

#define EFI_IA32_X64_ERROR_PROC_CHECK_INFO_VALID 0x0000000000000001
#define EFI_IA32_X64_ERROR_PROC_TARGET_ADDR_VALID 0x0000000000000002
#define EFI_IA32_X64_ERROR_PROC_REQUESTER_ID_VALID 0x0000000000000004
#define EFI_IA32_X64_ERROR_PROC_RESPONDER_ID_VALID 0x0000000000000008
#define EFI_IA32_X64_ERROR_PROC_INST_IP_VALID 0x0000000000000010

#define EFI_CACHE_CHECK_TRANSACTION_TYPE_VALID 0x0001
#define EFI_CACHE_CHECK_OPERATION_VALID 0x0002
#define EFI_CACHE_CHECK_LEVEL_VALID 0x0004
#define EFI_CACHE_CHECK_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_CACHE_CHECK_UNCORRECTED_VALID 0x0010
#define EFI_CACHE_CHECK_PRECISE_IP_VALID 0x0020
#define EFI_CACHE_CHECK_RESTARTABLE_VALID 0x0040
#define EFI_CACHE_CHECK_OVERFLOW_VALID 0x0080

#define EFI_CACHE_CHECK_ERROR_TYPE_INSTRUCTION 0
#define EFI_CACHE_CHECK_ERROR_TYPE_DATA_ACCESS 1
#define EFI_CACHE_CHECK_ERROR_TYPE_GENERIC 2

#define EFI_CACHE_CHECK_OPERATION_TYPE_GENERIC 0
#define EFI_CACHE_CHECK_OPERATION_TYPE_GENERIC_READ 1
#define EFI_CACHE_CHECK_OPERATION_TYPE_GENERIC_WRITE 2
#define EFI_CACHE_CHECK_OPERATION_TYPE_DATA_READ 3
#define EFI_CACHE_CHECK_OPERATION_TYPE_DATA_WRITE 4
#define EFI_CACHE_CHECK_OPERATION_TYPE_INSTRUCTION_FETCH 5
#define EFI_CACHE_CHECK_OPERATION_TYPE_PREFETCH 6
#define EFI_CACHE_CHECK_OPERATION_TYPE_EVICTION 7
#define EFI_CACHE_CHECK_OPERATION_TYPE_SNOOP 8

struct efi_ia32_x64_cache_check_info {
    uint64_t check_info;
} __attribute__((__packed__));

#define EFI_IA32_X64_CACHE_CHECK_INFO_VALID_FIELDS_SHIFT 0
#define EFI_IA32_X64_CACHE_CHECK_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_IA32_X64_CACHE_CHECK_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_IA32_X64_CACHE_CHECK_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_IA32_X64_CACHE_CHECK_INFO_OPERATION_SHIFT 18
#define EFI_IA32_X64_CACHE_CHECK_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_IA32_X64_CACHE_CHECK_INFO_LEVEL_SHIFT 22
#define EFI_IA32_X64_CACHE_CHECK_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_IA32_X64_CACHE_CHECK_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_IA32_X64_CACHE_CHECK_INFO_ERROR_UNCORRECTED 0x0000000004000000
#define EFI_IA32_X64_CACHE_CHECK_INFO_PRECISE_IP 0x0000000008000000
#define EFI_IA32_X64_CACHE_CHECK_INFO_RESTARTABLE_IP 0x0000000010000000
#define EFI_IA32_X64_CACHE_CHECK_INFO_OVERFLOW 0x0000000020000000

#define EFI_TLB_CHECK_TRANSACTION_TYPE_VALID 0x0001
#define EFI_TLB_CHECK_OPERATION_VALID 0x0002
#define EFI_TLB_CHECK_LEVEL_VALID 0x0004
#define EFI_TLB_CHECK_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_TLB_CHECK_UNCORRECTED_VALID 0x0010
#define EFI_TLB_CHECK_PRECISE_IP_VALID 0x0020
#define EFI_TLB_CHECK_RESTARTABLE_VALID 0x0040
#define EFI_TLB_CHECK_OVERFLOW_VALID 0x0080

#define EFI_TLB_CHECK_ERROR_TYPE_INSTRUCTION 0
#define EFI_TLB_CHECK_ERROR_TYPE_DATA_ACCESS 1
#define EFI_TLB_CHECK_ERROR_TYPE_GENERIC 2

#define EFI_TLB_CHECK_OPERATION_TYPE_GENERIC 0
#define EFI_TLB_CHECK_OPERATION_TYPE_GENERIC_READ 1
#define EFI_TLB_CHECK_OPERATION_TYPE_GENERIC_WRITE 2
#define EFI_TLB_CHECK_OPERATION_TYPE_DATA_READ 3
#define EFI_TLB_CHECK_OPERATION_TYPE_DATA_WRITE 4
#define EFI_TLB_CHECK_OPERATION_TYPE_INST_FETCH 5
#define EFI_TLB_CHECK_OPERATION_TYPE_PREFETCH 6

struct efi_ia32_x64_tlb_check_info {
    uint64_t check_info;
} __attribute__((__packed__));

#define EFI_IA32_X64_TLB_CHECK_INFO_VALID_FIELDS_SHIFT 0
#define EFI_IA32_X64_TLB_CHECK_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_IA32_X64_TLB_CHECK_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_IA32_X64_TLB_CHECK_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_IA32_X64_TLB_CHECK_INFO_OPERATION_SHIFT 18
#define EFI_IA32_X64_TLB_CHECK_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_IA32_X64_TLB_CHECK_INFO_LEVEL_SHIFT 22
#define EFI_IA32_X64_TLB_CHECK_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_IA32_X64_TLB_CHECK_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_IA32_X64_TLB_CHECK_INFO_ERROR_UNCORRECTED 0x0000000004000000
#define EFI_IA32_X64_TLB_CHECK_INFO_PRECISE_IP 0x0000000008000000
#define EFI_IA32_X64_TLB_CHECK_INFO_RESTARTABLE_IP 0x0000000010000000
#define EFI_IA32_X64_TLB_CHECK_INFO_OVERFLOW 0x0000000020000000

#define EFI_BUS_CHECK_TRANSACTION_TYPE_VALID 0x0001
#define EFI_BUS_CHECK_OPERATION_VALID 0x0002
#define EFI_BUS_CHECK_LEVEL_VALID 0x0004
#define EFI_BUS_CHECK_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_BUS_CHECK_UNCORRECTED_VALID 0x0010
#define EFI_BUS_CHECK_PRECISE_IP_VALID 0x0020
#define EFI_BUS_CHECK_RESTARTABLE_VALID 0x0040
#define EFI_BUS_CHECK_OVERFLOW_VALID 0x0080
#define EFI_BUS_CHECK_PARTICIPATION_TYPE_VALID 0x0100
#define EFI_BUS_CHECK_TIME_OUT_VALID 0x0200
#define EFI_BUS_CHECK_ADDRESS_SPACE_VALID 0x0400

#define EFI_BUS_CHECK_ERROR_TYPE_INSTRUCTION 0
#define EFI_BUS_CHECK_ERROR_TYPE_DATA_ACCESS 1
#define EFI_BUS_CHECK_ERROR_TYPE_GENERIC 2

#define EFI_BUS_CHECK_OPERATION_TYPE_GENERIC 0
#define EFI_BUS_CHECK_OPERATION_TYPE_GENERIC_READ 1
#define EFI_BUS_CHECK_OPERATION_TYPE_GENERIC_WRITE 2
#define EFI_BUS_CHECK_OPERATION_TYPE_DATA_READ 3
#define EFI_BUS_CHECK_OPERATION_TYPE_DATA_WRITE 4
#define EFI_BUS_CHECK_OPERATION_TYPE_INST_FETCH 5
#define EFI_BUS_CHECK_OPERATION_TYPE_PREFETCH 6

#define EFI_BUS_CHECK_PARTICIPATION_TYPE_REQUEST 0
#define EFI_BUS_CHECK_PARTICIPATION_TYPE_RESPONDED 1
#define EFI_BUS_CHECK_PARTICIPATION_TYPE_OBSERVED 2
#define EFI_BUS_CHECK_PARTICIPATION_TYPE_GENERIC 3

#define EFI_BUS_CHECK_ADDRESS_SPACE_TYPE_MEMORY 0
#define EFI_BUS_CHECK_ADDRESS_SPACE_TYPE_RESERVED 1
#define EFI_BUS_CHECK_ADDRESS_SPACE_TYPE_IO 2
#define EFI_BUS_CHECK_ADDRESS_SPACE_TYPE_OTHER 3

struct efi_ia32_x64_bus_check_info {
    uint64_t check_info;
} __attribute__((__packed__));

#define EFI_IA32_X64_BUS_CHECK_INFO_VALID_FIELDS_SHIFT 0
#define EFI_IA32_X64_BUS_CHECK_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_IA32_X64_BUS_CHECK_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_IA32_X64_BUS_CHECK_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_IA32_X64_BUS_CHECK_INFO_OPERATION_SHIFT 18
#define EFI_IA32_X64_BUS_CHECK_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_IA32_X64_BUS_CHECK_INFO_LEVEL_SHIFT 22
#define EFI_IA32_X64_BUS_CHECK_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_IA32_X64_BUS_CHECK_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_IA32_X64_BUS_CHECK_INFO_ERROR_UNCORRECTED 0x0000000004000000
#define EFI_IA32_X64_BUS_CHECK_INFO_PRECISE_IP 0x0000000008000000
#define EFI_IA32_X64_BUS_CHECK_INFO_RESTARTABLE_IP 0x0000000010000000
#define EFI_IA32_X64_BUS_CHECK_INFO_OVERFLOW 0x0000000020000000
#define EFI_IA32_X64_BUS_CHECK_INFO_PARTICIPATION_TYPE_SHIFT 30
#define EFI_IA32_X64_BUS_CHECK_INFO_PARTICIPATION_TYPE_MASK 0x00000000c0000000
#define EFI_IA32_X64_BUS_CHECK_INFO_TIME_OUT 0x0000000100000000
#define EFI_IA32_X64_BUS_CHECK_INFO_ADDRESS_SPACE_SHIFT 33
#define EFI_IA32_X64_BUS_CHECK_INFO_ADDRESS_SPACE_MASK 0x0000000600000000

#define EFI_MS_CHECK_ERROR_TYPE_VALID 0x0001
#define EFI_MS_CHECK_CONTEXT_CORRUPT_VALID 0x0002
#define EFI_MS_CHECK_UNCORRECTED_VALID 0x0004
#define EFI_MS_CHECK_PRECISE_IP_VALID 0x0008
#define EFI_MS_CHECK_RESTARTABLE_VALID 0x0010
#define EFI_MS_CHECK_OVERFLOW_VALID 0x0020

#define EFI_MS_CHECK_ERROR_TYPE_NO 0
#define EFI_MS_CHECK_ERROR_TYPE_UNCLASSIFIED 1
#define EFI_MS_CHECK_ERROR_TYPE_MICROCODE_PARITY 2
#define EFI_MS_CHECK_ERROR_TYPE_EXTERNAL 3
#define EFI_MS_CHECK_ERROR_TYPE_FRC 4
#define EFI_MS_CHECK_ERROR_TYPE_INTERNAL_UNCLASSIFIED 5

struct efi_ia32_x64_ms_check_info {
    uint64_t check_info;
} __attribute__((__packed__));

#define EFI_IA32_X64_MS_CHECK_INFO_VALID_FIELDS_SHIFT 0
#define EFI_IA32_X64_MS_CHECK_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_IA32_X64_MS_CHECK_INFO_ERROR_TYPE_SHIFT 16
#define EFI_IA32_X64_MS_CHECK_INFO_ERROR_TYPE_MASK 0x0000000000070000
#define EFI_IA32_X64_MS_CHECK_INFO_CONTEXT_CORRUPT 0x0000000000080000
#define EFI_IA32_X64_MS_CHECK_INFO_ERROR_UNCORRECTED 0x0000000000100000
#define EFI_IA32_X64_MS_CHECK_INFO_PRECISE_IP 0x0000000000200000
#define EFI_IA32_X64_MS_CHECK_INFO_RESTARTABLE_IP 0x0000000000400000
#define EFI_IA32_X64_MS_CHECK_INFO_OVERFLOW 0x0000000000800000

union efi_ia32_x64_check_info_item {
    struct efi_ia32_x64_cache_check_info cache_check;
    struct efi_ia32_x64_tlb_check_info tlb_check;
    struct efi_ia32_x64_bus_check_info bus_check;
    struct efi_ia32_x64_ms_check_info ms_check;
    uint64_t data64;
} __attribute__((__packed__));

struct efi_ia32_x64_process_error_info {
    struct efi_guid error_type;
    uint64_t valid_fields;
    union efi_ia32_x64_check_info_item check_info;
    uint64_t target_id;
    uint64_t requestor_id;
    uint64_t responder_id;
    uint64_t instruction_ip;
} __attribute__((__packed__));

#define EFI_REG_CONTEXT_TYPE_UNCLASSIFIED 0x0000
#define EFI_REG_CONTEXT_TYPE_MSR 0x0001
#define EFI_REG_CONTEXT_TYPE_IA32 0x0002
#define EFI_REG_CONTEXT_TYPE_X64 0x0003
#define EFI_REG_CONTEXT_TYPE_FXSAVE 0x0004
#define EFI_REG_CONTEXT_TYPE_DR_IA32 0x0005
#define EFI_REG_CONTEXT_TYPE_DR_X64 0x0006
#define EFI_REG_CONTEXT_TYPE_MEM_MAP 0x0007

// The register array follows: array_size bytes, zero-padded to a multiple of
// 16.
struct efi_ia32_x64_processor_context_info {
    uint16_t register_type;
    uint16_t array_size;
    uint32_t msr_address;
    uint64_t mm_register_address;
} __attribute__((__packed__));

struct efi_context_ia32_register_state {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint16_t cs;
    uint16_t ds;
    uint16_t ss;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint32_t eflags;
    uint32_t eip;
    uint32_t cr0;
    uint32_t cr1;
    uint32_t cr2;
    uint32_t cr3;
    uint32_t cr4;
    uint32_t gdtr[2];
    uint32_t idtr[2];
    uint16_t ldtr;
    uint16_t tr;
} __attribute__((__packed__));

// The instruction pointer is misprinted EIP.
struct efi_context_x64_register_state {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint16_t cs;
    uint16_t ds;
    uint16_t ss;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint32_t resv1;
    uint64_t rflags;
    uint64_t rip;
    uint64_t cr0;
    uint64_t cr1;
    uint64_t cr2;
    uint64_t cr3;
    uint64_t cr4;
    uint64_t cr8;
    uint64_t gdtr[2];
    uint64_t idtr[2];
    uint16_t ldtr;
    uint16_t tr;
} __attribute__((__packed__));

#define EFI_ARM_PROC_ERROR_MPIDR_VALID 0x00000001
#define EFI_ARM_PROC_ERROR_ERROR_AFFINITY_LVL_VALID 0x00000002
#define EFI_ARM_PROC_ERROR_RUNNING_STATE_VALID 0x00000004
#define EFI_ARM_PROC_ERROR_VENDOR_INFO_VALID 0x00000008

#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_0 0x00
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_1 0x01
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_2 0x02
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_3 0x03

// err_info_num struct efi_arm_processor_error_information follow, then
// context_info_num struct efi_arm_processor_context_information, then any
// vendor-specific information.
struct efi_arm_processor_error_record {
    uint32_t valid_fields;
    uint16_t err_info_num;
    uint16_t context_info_num;
    uint32_t section_length;
    uint8_t err_affinity_lvl;
    uint8_t reserved[3];
    uint64_t mpidr_el1;
    uint64_t midr_el1;
    uint32_t run_state;
    uint32_t psci_state;
} __attribute__((__packed__));

#define EFI_ARM_PROCESSOR_ERROR_INFO_STRUCTURE_REVISION 0

#define EFI_ARM_PROC_ERROR_INFO_MULTIPLE_ERROR_VALID 0x0001
#define EFI_ARM_PROC_ERROR_INFO_FLAGS_VALID 0x0002
#define EFI_ARM_PROC_ERROR_INFO_ERROR_INFO_VALID 0x0004
#define EFI_ARM_PROC_ERROR_INFO_VIRT_FAULT_ADDR_VALID 0x0008
#define EFI_ARM_PROC_ERROR_INFO_PHY_FAULT_ADDR_VALID 0x0010

#define EFI_ARM_PROC_ERROR_INFO_TYPE_CACHE 0x01
#define EFI_ARM_PROC_ERROR_INFO_TYPE_TLB 0x02
#define EFI_ARM_PROC_ERROR_INFO_TYPE_BUS 0x04
#define EFI_ARM_PROC_ERROR_INFO_TYPE_MICRO_ARCH 0x08

#define EFI_ARM_PROC_ERROR_INFO_FLAG_FIRST_ERROR_CAPTURED_FLAG 0x01
#define EFI_ARM_PROC_ERROR_INFO_FLAG_LAST_ERROR_CAPTURED_FLAG 0x02
#define EFI_ARM_PROC_ERROR_INFO_FLAG_PROPAGATED_FLAG 0x04
#define EFI_ARM_PROC_ERROR_INFO_FLAG_OVERFLOW_FLAG 0x08

#define EFI_ARM_CACHE_ERROR_TRANSACTION_TYPE_VALID 0x0001
#define EFI_ARM_CACHE_ERROR_OPERATION_VALID 0x0002
#define EFI_ARM_CACHE_ERROR_LEVEL_VALID 0x0004
#define EFI_ARM_CACHE_ERROR_PROCESSOR_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_ARM_CACHE_ERROR_CORRECTED_VALID 0x0010
#define EFI_ARM_CACHE_ERROR_PRECISE_PC_VALID 0x0020
#define EFI_ARM_CACHE_ERROR_RESTARTABLE_PC_VALID 0x0040

#define EFI_ARM_CACHE_ERROR_TYPE_INSTRUCTION 0
#define EFI_ARM_CACHE_ERROR_TYPE_DATA_ACCESS 1
#define EFI_ARM_CACHE_ERROR_TYPE_GENERIC 2

#define EFI_ARM_CACHE_ERROR_OPERATION_GENERIC_ERROR 0
#define EFI_ARM_CACHE_ERROR_OPERATION_GENERIC_READ 1
#define EFI_ARM_CACHE_ERROR_OPERATION_GENERIC_WRITE 2
#define EFI_ARM_CACHE_ERROR_OPERATION_DATA_READ 3
#define EFI_ARM_CACHE_ERROR_OPERATION_DATA_WRITE 4
#define EFI_ARM_CACHE_ERROR_OPERATION_INSTRUCTION_FETCH 5
#define EFI_ARM_CACHE_ERROR_OPERATION_PREFETCH 6
#define EFI_ARM_CACHE_ERROR_OPERATION_EVICTION 7
#define EFI_ARM_CACHE_ERROR_OPERATION_SNOOPING 8
#define EFI_ARM_CACHE_ERROR_OPERATION_SNOOPED 9
#define EFI_ARM_CACHE_ERROR_OPERATION_MANAGEMENT 10

struct efi_arm_cache_error_info {
    uint64_t error_info;
} __attribute__((__packed__));

#define EFI_ARM_CACHE_ERROR_INFO_VALID_FIELDS_SHIFT 0
#define EFI_ARM_CACHE_ERROR_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_ARM_CACHE_ERROR_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_ARM_CACHE_ERROR_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_ARM_CACHE_ERROR_INFO_OPERATION_SHIFT 18
#define EFI_ARM_CACHE_ERROR_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_ARM_CACHE_ERROR_INFO_LEVEL_SHIFT 22
#define EFI_ARM_CACHE_ERROR_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_ARM_CACHE_ERROR_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_ARM_CACHE_ERROR_INFO_ERROR_CORRECTED 0x0000000004000000
#define EFI_ARM_CACHE_ERROR_INFO_PRECISE_PC 0x0000000008000000
#define EFI_ARM_CACHE_ERROR_INFO_RESTARTABLE_PC 0x0000000010000000

#define EFI_ARM_TLB_ERROR_TRANSACTION_TYPE_VALID 0x0001
#define EFI_ARM_TLB_ERROR_OPERATION_VALID 0x0002
#define EFI_ARM_TLB_ERROR_LEVEL_VALID 0x0004
#define EFI_ARM_TLB_ERROR_PROCESSOR_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_ARM_TLB_ERROR_CORRECTED_VALID 0x0010
#define EFI_ARM_TLB_ERROR_PRECISE_PC_VALID 0x0020
#define EFI_ARM_TLB_ERROR_RESTARTABLE_PC_VALID 0x0040

#define EFI_ARM_TLB_ERROR_TYPE_INSTRUCTION 0
#define EFI_ARM_TLB_ERROR_TYPE_DATA_ACCESS 1
#define EFI_ARM_TLB_ERROR_TYPE_GENERIC 2

#define EFI_ARM_TLB_ERROR_OPERATION_GENERIC_ERROR 0
#define EFI_ARM_TLB_ERROR_OPERATION_GENERIC_READ 1
#define EFI_ARM_TLB_ERROR_OPERATION_GENERIC_WRITE 2
#define EFI_ARM_TLB_ERROR_OPERATION_DATA_READ 3
#define EFI_ARM_TLB_ERROR_OPERATION_DATA_WRITE 4
#define EFI_ARM_TLB_ERROR_OPERATION_INSTRUCTION_FETCH 5
#define EFI_ARM_TLB_ERROR_OPERATION_PREFETCH 6
#define EFI_ARM_TLB_ERROR_OPERATION_LOCAL_MANAGEMENT_OPERATION 7
#define EFI_ARM_TLB_ERROR_OPERATION_EXTERNAL_MANAGEMENT_OPERATION 8

struct efi_arm_tlb_error_info {
    uint64_t error_info;
} __attribute__((__packed__));

#define EFI_ARM_TLB_ERROR_INFO_VALID_FIELDS_SHIFT 0
#define EFI_ARM_TLB_ERROR_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_ARM_TLB_ERROR_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_ARM_TLB_ERROR_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_ARM_TLB_ERROR_INFO_OPERATION_SHIFT 18
#define EFI_ARM_TLB_ERROR_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_ARM_TLB_ERROR_INFO_LEVEL_SHIFT 22
#define EFI_ARM_TLB_ERROR_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_ARM_TLB_ERROR_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_ARM_TLB_ERROR_INFO_ERROR_CORRECTED 0x0000000004000000
#define EFI_ARM_TLB_ERROR_INFO_PRECISE_PC 0x0000000008000000
#define EFI_ARM_TLB_ERROR_INFO_RESTARTABLE_PC 0x0000000010000000

#define EFI_ARM_BUS_ERROR_TRANSACTION_TYPE_VALID 0x0001
#define EFI_ARM_BUS_ERROR_OPERATION_VALID 0x0002
#define EFI_ARM_BUS_ERROR_LEVEL_VALID 0x0004
#define EFI_ARM_BUS_ERROR_CONTEXT_CORRUPT_VALID 0x0008
#define EFI_ARM_BUS_ERROR_CORRECTED_VALID 0x0010
#define EFI_ARM_BUS_ERROR_PRECISE_PC_VALID 0x0020
#define EFI_ARM_BUS_ERROR_RESTARTABLE_PC_VALID 0x0040
#define EFI_ARM_BUS_ERROR_PARTICIPATION_TYPE_VALID 0x0080
#define EFI_ARM_BUS_ERROR_TIME_OUT_VALID 0x0100
#define EFI_ARM_BUS_ERROR_ADDRESS_SPACE_VALID 0x0200
#define EFI_ARM_BUS_ERROR_MEMORY_ATTRIBUTE_VALID 0x0400
#define EFI_ARM_BUS_ERROR_ACCESS_MODE_VALID 0x0800

#define EFI_ARM_BUS_ERROR_ERROR_TYPE_INSTRUCTION 0
#define EFI_ARM_BUS_ERROR_ERROR_TYPE_DATA_ACCESS 1
#define EFI_ARM_BUS_ERROR_ERROR_TYPE_GENERIC 2

#define EFI_ARM_BUS_ERROR_OPERATION_GENERIC_ERROR 0
#define EFI_ARM_BUS_ERROR_OPERATION_GENERIC_READ 1
#define EFI_ARM_BUS_ERROR_OPERATION_GENERIC_WRITE 2
#define EFI_ARM_BUS_ERROR_OPERATION_DATA_READ 3
#define EFI_ARM_BUS_ERROR_OPERATION_DATA_WRITE 4
#define EFI_ARM_BUS_ERROR_OPERATION_INSTRUCTION_FETCH 5
#define EFI_ARM_BUS_ERROR_OPERATION_PREFETCH 6

#define EFI_ARM_BUS_ERROR_PARTICIPATION_TYPE_REQUEST 0
#define EFI_ARM_BUS_ERROR_PARTICIPATION_TYPE_RESPONDED 1
#define EFI_ARM_BUS_ERROR_PARTICIPATION_TYPE_OBSERVED 2
#define EFI_ARM_BUS_ERROR_PARTICIPATION_TYPE_GENERIC 3

#define EFI_ARM_BUS_CHECK_ADDRESS_SPACE_TYPE_EXTERNAL_MEMORY 0
#define EFI_ARM_BUS_CHECK_ADDRESS_SPACE_TYPE_INTERNAL_MEMORY 1
#define EFI_ARM_BUS_CHECK_ADDRESS_SPACE_TYPE_DEVICE_MEMORY 3

struct efi_arm_bus_error_info {
    uint64_t error_info;
} __attribute__((__packed__));

#define EFI_ARM_BUS_ERROR_INFO_VALID_FIELDS_SHIFT 0
#define EFI_ARM_BUS_ERROR_INFO_VALID_FIELDS_MASK 0x000000000000ffff
#define EFI_ARM_BUS_ERROR_INFO_TRANSACTION_TYPE_SHIFT 16
#define EFI_ARM_BUS_ERROR_INFO_TRANSACTION_TYPE_MASK 0x0000000000030000
#define EFI_ARM_BUS_ERROR_INFO_OPERATION_SHIFT 18
#define EFI_ARM_BUS_ERROR_INFO_OPERATION_MASK 0x00000000003c0000
#define EFI_ARM_BUS_ERROR_INFO_LEVEL_SHIFT 22
#define EFI_ARM_BUS_ERROR_INFO_LEVEL_MASK 0x0000000001c00000
#define EFI_ARM_BUS_ERROR_INFO_CONTEXT_CORRUPT 0x0000000002000000
#define EFI_ARM_BUS_ERROR_INFO_ERROR_CORRECTED 0x0000000004000000
#define EFI_ARM_BUS_ERROR_INFO_PRECISE_PC 0x0000000008000000
#define EFI_ARM_BUS_ERROR_INFO_RESTARTABLE_PC 0x0000000010000000
#define EFI_ARM_BUS_ERROR_INFO_PARTICIPATION_TYPE_SHIFT 29
#define EFI_ARM_BUS_ERROR_INFO_PARTICIPATION_TYPE_MASK 0x0000000060000000
#define EFI_ARM_BUS_ERROR_INFO_TIME_OUT 0x0000000080000000
#define EFI_ARM_BUS_ERROR_INFO_ADDRESS_SPACE_SHIFT 32
#define EFI_ARM_BUS_ERROR_INFO_ADDRESS_SPACE_MASK 0x0000000300000000
#define EFI_ARM_BUS_ERROR_INFO_MEMORY_ACCESS_ATTRIBUTE_SHIFT 34
#define EFI_ARM_BUS_ERROR_INFO_MEMORY_ACCESS_ATTRIBUTE_MASK 0x000007fc00000000
#define EFI_ARM_BUS_ERROR_INFO_ACCESS_MODE 0x0000080000000000

union efi_arm_error_information {
    struct efi_arm_cache_error_info cache_error_info;
    struct efi_arm_tlb_error_info tlb_error_info;
    struct efi_arm_bus_error_info bus_error_info;
} __attribute__((__packed__));

struct efi_arm_processor_error_information {
    uint8_t version;
    uint8_t length;
    uint16_t valid_fields;
    uint8_t type;
    uint16_t error_count;
    uint8_t flags;
    union efi_arm_error_information error_info;
    uint64_t virtual_fault_address;
    uint64_t physical_fault_address;
} __attribute__((__packed__));

#define EFI_ARM_REG_CONTEXT_TYPE_AARCH32_GPRS 0
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH32_EL1 1
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH32_EL2 2
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH32_SECURE 3
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH64_GPRS 4
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH64_EL1 5
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH64_EL2 6
#define EFI_ARM_REG_CONTEXT_TYPE_AARCH64_EL3 7
#define EFI_ARM_REG_CONTEXT_TYPE_MISC_SYS_REG 8
#define EFI_ARM_REG_CONTEXT_TYPE_TTBR128 9

struct efi_arm_aarch32_context_gpr {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t r13_sp;
    uint32_t r14_lr;
    uint32_t r15_pc;
} __attribute__((__packed__));

struct efi_arm_aarch32_el1_context_system_registers {
    uint32_t dfar;
    uint32_t dfsr;
    uint32_t ifar;
    uint32_t isr;
    uint32_t mair0;
    uint32_t mair1;
    uint32_t midr;
    uint32_t mpidr;
    uint32_t nmrr;
    uint32_t prrr;
    uint32_t sctlr;
    uint32_t spsr;
    uint32_t spsr_abt;
    uint32_t spsr_fiq;
    uint32_t spsr_irq;
    uint32_t spsr_svc;
    uint32_t spsr_und;
    uint32_t tpidrprw;
    uint32_t tpidruro;
    uint32_t tpidrurw;
    uint32_t ttbcr;
    uint32_t ttbr0;
    uint32_t ttbr1;
    uint32_t dacr;
} __attribute__((__packed__));

struct efi_arm_aarch32_el2_context_system_registers {
    uint32_t elr_hyp;
    uint32_t hamair0;
    uint32_t hamair1;
    uint32_t hcr;
    uint32_t hcr2;
    uint32_t hdfar;
    uint32_t hifar;
    uint32_t hpfar;
    uint32_t hsr;
    uint32_t htcr;
    uint32_t htpidr;
    uint32_t httbr;
    uint32_t spsr_hyp;
    uint32_t vtcr;
    uint32_t vttbr;
    uint32_t dacr32_el2;
} __attribute__((__packed__));

struct efi_arm_aarch32_secure_context_system_registers {
    uint32_t sctlr;
    uint32_t spsr_mon;
} __attribute__((__packed__));

struct efi_arm_aarch64_context_gpr {
    uint64_t x0;
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
    uint64_t x5;
    uint64_t x6;
    uint64_t x7;
    uint64_t x8;
    uint64_t x9;
    uint64_t x10;
    uint64_t x11;
    uint64_t x12;
    uint64_t x13;
    uint64_t x14;
    uint64_t x15;
    uint64_t x16;
    uint64_t x17;
    uint64_t x18;
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t x29;
    uint64_t x30;
    uint64_t sp;
} __attribute__((__packed__));

struct efi_arm_aarch64_el1_context_system_registers {
    uint64_t elr_el1;
    uint64_t esr_el1;
    uint64_t far_el1;
    uint64_t isr_el1;
    uint64_t mair_el1;
    uint64_t midr_el1;
    uint64_t mpidr_el1;
    uint64_t sctlr_el1;
    uint64_t sp_el0;
    uint64_t sp_el1;
    uint64_t spsr_el1;
    uint64_t tcr_el1;
    uint64_t tpidr_el0;
    uint64_t tpidr_el1;
    uint64_t tpidrro_el0;
    uint64_t ttbr0_el1;
    uint64_t ttbr1_el1;
} __attribute__((__packed__));

struct efi_arm_aarch64_el2_context_system_registers {
    uint64_t elr_el2;
    uint64_t esr_el2;
    uint64_t far_el2;
    uint64_t hacr_el2;
    uint64_t hcr_el2;
    uint64_t hpfar_el2;
    uint64_t mair_el2;
    uint64_t sctlr_el2;
    uint64_t sp_el2;
    uint64_t spsr_el2;
    uint64_t tcr_el2;
    uint64_t tpidr_el2;
    uint64_t ttbr0_el2;
    uint64_t vtcr_el2;
    uint64_t vttbr_el2;
} __attribute__((__packed__));

struct efi_arm_aarch64_el3_context_system_registers {
    uint64_t elr_el3;
    uint64_t esr_el3;
    uint64_t far_el3;
    uint64_t mair_el3;
    uint64_t sctlr_el3;
    uint64_t sp_el3;
    uint64_t spsr_el3;
    uint64_t tcr_el3;
    uint64_t tpidr_el3;
    uint64_t ttbr0_el3;
} __attribute__((__packed__));

struct efi_arm_misc_context_system_register {
    uint16_t mrs_encoding;
    uint64_t register_val;
} __attribute__((__packed__));

#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_OP2_SHIFT 0
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_OP2_MASK 0x0007
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_C_RM_SHIFT 3
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_C_RM_MASK 0x0078
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_C_RN_SHIFT 7
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_C_RN_MASK 0x0780
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_OP1_SHIFT 11
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_OP1_MASK 0x3800
#define EFI_ARM_MISC_CONTEXT_SYSTEM_REGISTER_MRS_O0 0x4000

struct efi_arm_ttbr128_context_system_registers {
    uint64_t ttbr0_el1[2];
    uint64_t ttbr0_el2[2];
    uint64_t ttbr0_el3[2];
    uint64_t ttbr1_el1[2];
    uint64_t ttbr1_el2[2];
    uint64_t vttbr_el2[2];
} __attribute__((__packed__));

union efi_context_register_array_info {
    struct efi_arm_aarch32_context_gpr type0_sys_regs;
    struct efi_arm_aarch32_el1_context_system_registers type1_sys_regs;
    struct efi_arm_aarch32_el2_context_system_registers type2_sys_regs;
    struct efi_arm_aarch32_secure_context_system_registers type3_sys_regs;
    struct efi_arm_aarch64_context_gpr type4_sys_regs;
    struct efi_arm_aarch64_el1_context_system_registers type5_sys_regs;
    struct efi_arm_aarch64_el2_context_system_registers type6_sys_regs;
    struct efi_arm_aarch64_el3_context_system_registers type7_sys_regs;
    struct efi_arm_misc_context_system_register sys_reg_info;
    struct efi_arm_ttbr128_context_system_registers type9_sys_regs;
} __attribute__((__packed__));

struct efi_arm_processor_context_information {
    uint16_t version;
    uint16_t register_context_type;
    uint32_t register_array_size;
    union efi_context_register_array_info register_array;
} __attribute__((__packed__));

#define EFI_PLATFORM_MEMORY_ERROR_STATUS_VALID 0x0000000000000001
#define EFI_PLATFORM_MEMORY_PHY_ADDRESS_VALID 0x0000000000000002
#define EFI_PLATFORM_MEMORY_PHY_ADDRESS_MASK_VALID 0x0000000000000004
#define EFI_PLATFORM_MEMORY_NODE_VALID 0x0000000000000008
#define EFI_PLATFORM_MEMORY_CARD_VALID 0x0000000000000010
#define EFI_PLATFORM_MEMORY_MODULE_VALID 0x0000000000000020
#define EFI_PLATFORM_MEMORY_BANK_VALID 0x0000000000000040
#define EFI_PLATFORM_MEMORY_DEVICE_VALID 0x0000000000000080
#define EFI_PLATFORM_MEMORY_ROW_VALID 0x0000000000000100
#define EFI_PLATFORM_MEMORY_COLUMN_VALID 0x0000000000000200
#define EFI_PLATFORM_MEMORY_BIT_POS_VALID 0x0000000000000400
#define EFI_PLATFORM_MEMORY_REQUESTOR_ID_VALID 0x0000000000000800
#define EFI_PLATFORM_MEMORY_RESPONDER_ID_VALID 0x0000000000001000
#define EFI_PLATFORM_MEMORY_TARGET_ID_VALID 0x0000000000002000
#define EFI_PLATFORM_MEMORY_ERROR_TYPE_VALID 0x0000000000004000
#define EFI_PLATFORM_MEMORY_ERROR_RANK_NUM_VALID 0x0000000000008000
#define EFI_PLATFORM_MEMORY_ERROR_CARD_HANDLE_VALID 0x0000000000010000
#define EFI_PLATFORM_MEMORY_ERROR_MODULE_HANDLE_VALID 0x0000000000020000
#define EFI_PLATFORM_MEMORY_ERROR_EXTENDED_ROW_BIT_16_17_VALID 0x0000000000040000
#define EFI_PLATFORM_MEMORY_ERROR_BANK_GROUP_VALID 0x0000000000080000
#define EFI_PLATFORM_MEMORY_ERROR_BANK_ADDRESS_VALID 0x0000000000100000
#define EFI_PLATFORM_MEMORY_ERROR_CHIP_IDENTIFICATION_VALID 0x0000000000200000

#define EFI_PLATFORM_MEMORY_ERROR_UNKNOWN 0
#define EFI_PLATFORM_MEMORY_ERROR_NONE 1
#define EFI_PLATFORM_MEMORY_ERROR_SINGLEBIT_ECC 2
#define EFI_PLATFORM_MEMORY_ERROR_MULTIBIT_ECC 3
#define EFI_PLATFORM_MEMORY_ERROR_SINGLESYMBOL_CHIPKILL 4
#define EFI_PLATFORM_MEMORY_ERROR_MULTISYMBOL_CHIPKILL 5
#define EFI_PLATFORM_MEMORY_ERROR_MASTER_ABORT 6
#define EFI_PLATFORM_MEMORY_ERROR_TARGET_ABORT 7
#define EFI_PLATFORM_MEMORY_ERROR_PARITY 8
#define EFI_PLATFORM_MEMORY_ERROR_WDT 9
#define EFI_PLATFORM_MEMORY_ERROR_INVALID_ADDRESS 10
#define EFI_PLATFORM_MEMORY_ERROR_MIRROR_FAILED 11
#define EFI_PLATFORM_MEMORY_ERROR_SPARING 12
#define EFI_PLATFORM_MEMORY_ERROR_SCRUB_CORRECTED 13
#define EFI_PLATFORM_MEMORY_ERROR_SCRUB_UNCORRECTED 14
#define EFI_PLATFORM_MEMORY_ERROR_MEMORY_MAP_EVENT 15

struct efi_platform_memory_error_data {
    uint64_t valid_fields;
    struct efi_generic_error_status error_status;
    uint64_t physical_address;
    uint64_t physical_address_mask;
    uint16_t node;
    uint16_t card;
    uint16_t module_rank;
    uint16_t bank;
    uint16_t device;
    uint16_t row;
    uint16_t column;
    uint16_t bit_position;
    uint64_t requestor_id;
    uint64_t responder_id;
    uint64_t target_id;
    uint8_t error_type;
    uint8_t extended;
    uint16_t rank_num;
    uint16_t card_handle;
    uint16_t module_handle;
} __attribute__((__packed__));

#define EFI_PLATFORM_MEMORY2_ERROR_STATUS_VALID 0x0000000000000001
#define EFI_PLATFORM_MEMORY2_PHY_ADDRESS_VALID 0x0000000000000002
#define EFI_PLATFORM_MEMORY2_PHY_ADDRESS_MASK_VALID 0x0000000000000004
#define EFI_PLATFORM_MEMORY2_NODE_VALID 0x0000000000000008
#define EFI_PLATFORM_MEMORY2_CARD_VALID 0x0000000000000010
#define EFI_PLATFORM_MEMORY2_MODULE_VALID 0x0000000000000020
#define EFI_PLATFORM_MEMORY2_BANK_VALID 0x0000000000000040
#define EFI_PLATFORM_MEMORY2_DEVICE_VALID 0x0000000000000080
#define EFI_PLATFORM_MEMORY2_ROW_VALID 0x0000000000000100
#define EFI_PLATFORM_MEMORY2_COLUMN_VALID 0x0000000000000200
#define EFI_PLATFORM_MEMORY2_RANK_VALID 0x0000000000000400
#define EFI_PLATFORM_MEMORY2_BIT_POS_VALID 0x0000000000000800
#define EFI_PLATFORM_MEMORY2_CHIP_ID_VALID 0x0000000000001000
#define EFI_PLATFORM_MEMORY2_MEMORY_ERROR_TYPE_VALID 0x0000000000002000
#define EFI_PLATFORM_MEMORY2_STATUS_VALID 0x0000000000004000
#define EFI_PLATFORM_MEMORY2_REQUESTOR_ID_VALID 0x0000000000008000
#define EFI_PLATFORM_MEMORY2_RESPONDER_ID_VALID 0x0000000000010000
#define EFI_PLATFORM_MEMORY2_TARGET_ID_VALID 0x0000000000020000
#define EFI_PLATFORM_MEMORY2_CARD_HANDLE_VALID 0x0000000000040000
#define EFI_PLATFORM_MEMORY2_MODULE_HANDLE_VALID 0x0000000000080000
#define EFI_PLATFORM_MEMORY2_BANK_GROUP_VALID 0x0000000000100000
#define EFI_PLATFORM_MEMORY2_BANK_ADDRESS_VALID 0x0000000000200000

#define EFI_PLATFORM_MEMORY2_ERROR_UNKNOWN 0
#define EFI_PLATFORM_MEMORY2_ERROR_NONE 1
#define EFI_PLATFORM_MEMORY2_ERROR_SINGLEBIT_ECC 2
#define EFI_PLATFORM_MEMORY2_ERROR_MULTIBIT_ECC 3
#define EFI_PLATFORM_MEMORY2_ERROR_SINGLESYMBOL_CHIPKILL 4
#define EFI_PLATFORM_MEMORY2_ERROR_MULTISYMBOL_CHIPKILL 5
#define EFI_PLATFORM_MEMORY2_ERROR_MASTER_ABORT 6
#define EFI_PLATFORM_MEMORY2_ERROR_TARGET_ABORT 7
#define EFI_PLATFORM_MEMORY2_ERROR_PARITY 8
#define EFI_PLATFORM_MEMORY2_ERROR_WDT 9
#define EFI_PLATFORM_MEMORY2_ERROR_INVALID_ADDRESS 10
#define EFI_PLATFORM_MEMORY2_ERROR_MIRROR_BROKEN 11
#define EFI_PLATFORM_MEMORY2_ERROR_MEMORY_SPARING 12
#define EFI_PLATFORM_MEMORY2_ERROR_SCRUB_CORRECTED 13
#define EFI_PLATFORM_MEMORY2_ERROR_SCRUB_UNCORRECTED 14
#define EFI_PLATFORM_MEMORY2_ERROR_MEMORY_MAP_EVENT 15

struct efi_platform_memory2_error_data {
    uint64_t valid_fields;
    struct efi_generic_error_status error_status;
    uint64_t physical_address;
    uint64_t physical_address_mask;
    uint16_t node;
    uint16_t card;
    uint16_t module;
    uint16_t bank;
    uint32_t device;
    uint32_t row;
    uint32_t column;
    uint32_t rank;
    uint32_t bit_position;
    uint8_t chip_id;
    uint8_t mem_error_type;
    uint8_t status;
    uint8_t reserved;
    uint64_t requestor_id;
    uint64_t responder_id;
    uint64_t target_id;
    uint32_t card_handle;
    uint32_t module_handle;
} __attribute__((__packed__));

#define EFI_PCIE_ERROR_PORT_TYPE_VALID 0x0000000000000001
#define EFI_PCIE_ERROR_VERSION_VALID 0x0000000000000002
#define EFI_PCIE_ERROR_COMMAND_STATUS_VALID 0x0000000000000004
#define EFI_PCIE_ERROR_DEVICE_ID_VALID 0x0000000000000008
#define EFI_PCIE_ERROR_SERIAL_NO_VALID 0x0000000000000010
#define EFI_PCIE_ERROR_BRIDGE_CRL_STS_VALID 0x0000000000000020
#define EFI_PCIE_ERROR_CAPABILITY_INFO_VALID 0x0000000000000040
#define EFI_PCIE_ERROR_AER_INFO_VALID 0x0000000000000080
#define EFI_PCIE_ERROR_DEVICE_ID_RCRB_VALID 0x0000000000000100
#define EFI_PCIE_ERROR_RCRB_HIGH_ADDRESS_VALID 0x0000000000000200

#define EFI_PCIE_ERROR_PORT_PCIE_ENDPOINT 0x00000000
#define EFI_PCIE_ERROR_PORT_PCI_ENDPOINT 0x00000001
#define EFI_PCIE_ERROR_PORT_ROOT_PORT 0x00000004
#define EFI_PCIE_ERROR_PORT_UPSWITCH_PORT 0x00000005
#define EFI_PCIE_ERROR_PORT_DOWNSWITCH_PORT 0x00000006
#define EFI_PCIE_ERROR_PORT_PCIE_TO_PCI_BRIDGE 0x00000007
#define EFI_PCIE_ERROR_PORT_PCI_TO_PCIE_BRIDGE 0x00000008
#define EFI_PCIE_ERROR_PORT_ROOT_INT_ENDPOINT 0x00000009
#define EFI_PCIE_ERROR_PORT_ROOT_EVENT_COLLECTOR 0x0000000a

struct efi_generic_error_pci_slot {
    uint16_t slot;
} __attribute__((__packed__));

#define EFI_GENERIC_ERROR_PCI_SLOT_NUMBER_SHIFT 3
#define EFI_GENERIC_ERROR_PCI_SLOT_NUMBER_MASK 0xfff8

struct efi_generic_error_pcie_dev_bridge_id {
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t class_code[3];
    uint8_t function;
    uint8_t device;
    uint16_t segment;
    uint8_t primary_or_device_bus;
    uint8_t secondary_bus;
    struct efi_generic_error_pci_slot slot;
    uint8_t resv1;
} __attribute__((__packed__));

struct efi_pcie_error_data_capability {
    uint8_t pcie_cap[60];
} __attribute__((__packed__));

struct efi_pcie_error_data_aer {
    uint8_t pcie_aer[96];
} __attribute__((__packed__));

struct efi_pcie_error_data {
    uint64_t valid_fields;
    uint32_t port_type;
    uint32_t version;
    uint32_t command_status;
    uint32_t rcrb_high_address;
    struct efi_generic_error_pcie_dev_bridge_id dev_bridge;
    uint64_t serial_no;
    uint32_t bridge_control_status;
    struct efi_pcie_error_data_capability capability;
    struct efi_pcie_error_data_aer aer_info;
} __attribute__((__packed__));

#define EFI_PCI_PCIX_BUS_ERROR_STATUS_VALID 0x0000000000000001
#define EFI_PCI_PCIX_BUS_ERROR_TYPE_VALID 0x0000000000000002
#define EFI_PCI_PCIX_BUS_ERROR_BUS_ID_VALID 0x0000000000000004
#define EFI_PCI_PCIX_BUS_ERROR_BUS_ADDRESS_VALID 0x0000000000000008
#define EFI_PCI_PCIX_BUS_ERROR_BUS_DATA_VALID 0x0000000000000010
#define EFI_PCI_PCIX_BUS_ERROR_COMMAND_VALID 0x0000000000000020
#define EFI_PCI_PCIX_BUS_ERROR_REQUESTOR_ID_VALID 0x0000000000000040
#define EFI_PCI_PCIX_BUS_ERROR_COMPLETER_ID_VALID 0x0000000000000080
#define EFI_PCI_PCIX_BUS_ERROR_TARGET_ID_VALID 0x0000000000000100

#define EFI_PCI_PCIX_BUS_ERROR_UNKNOWN 0x0000
#define EFI_PCI_PCIX_BUS_ERROR_DATA_PARITY 0x0001
#define EFI_PCI_PCIX_BUS_ERROR_SYSTEM 0x0002
#define EFI_PCI_PCIX_BUS_ERROR_MASTER_ABORT 0x0003
#define EFI_PCI_PCIX_BUS_ERROR_BUS_TIMEOUT 0x0004
#define EFI_PCI_PCIX_BUS_ERROR_MASTER_DATA_PARITY 0x0005
#define EFI_PCI_PCIX_BUS_ERROR_ADDRESS_PARITY 0x0006
#define EFI_PCI_PCIX_BUS_ERROR_COMMAND_PARITY 0x0007

struct efi_pci_pcix_bus_error_data {
    uint64_t valid_fields;
    struct efi_generic_error_status error_status;
    uint16_t type;
    uint16_t bus_id;
    uint32_t resv2;
    uint64_t bus_address;
    uint64_t bus_data;
    uint64_t bus_command;
    uint64_t requestor_id;
    uint64_t responder_id;
    uint64_t target_id;
} __attribute__((__packed__));

#define EFI_PCI_PCIX_DEVICE_ERROR_STATUS_VALID 0x0000000000000001
#define EFI_PCI_PCIX_DEVICE_ERROR_ID_INFO_VALID 0x0000000000000002
#define EFI_PCI_PCIX_DEVICE_ERROR_MEM_NUM_VALID 0x0000000000000004
#define EFI_PCI_PCIX_DEVICE_ERROR_IO_NUM_VALID 0x0000000000000008
#define EFI_PCI_PCIX_DEVICE_ERROR_REG_DATA_PAIR_VALID 0x0000000000000010

struct efi_generic_error_pci_device_id {
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t class_code[3];
    uint8_t function;
    uint8_t device;
    uint8_t bus;
    uint8_t segment;
    uint8_t resv1;
    uint32_t resv2;
} __attribute__((__packed__));

// memory_number + io_number register address/data pairs, two uint64_t each,
// follow.
struct efi_pci_pcix_device_error_data {
    uint64_t valid_fields;
    struct efi_generic_error_status error_status;
    struct efi_generic_error_pci_device_id id_info;
    uint32_t memory_number;
    uint32_t io_number;
} __attribute__((__packed__));

#define EFI_FIRMWARE_ERROR_TYPE_IPF_SAL 0x00
#define EFI_FIRMWARE_ERROR_TYPE_SOC_TYPE1 0x01
#define EFI_FIRMWARE_ERROR_TYPE_SOC_TYPE2 0x02

// The reserved bytes are misprinted at offset 1, over revision: they are
// offsets 2 to 7.
struct efi_firmware_error_data {
    uint8_t error_type;
    uint8_t revision;
    uint8_t resv1[6];
    uint64_t record_id;
    struct efi_guid record_id_guid;
} __attribute__((__packed__));

#define EFI_DMA_FAULT_REASON_TABLE_ENTRY_NOT_PRESENT 0x01
#define EFI_DMA_FAULT_REASON_TABLE_ENTRY_INVALID 0x02
#define EFI_DMA_FAULT_REASON_ACCESS_MAPPING_TABLE_ERROR 0x03
#define EFI_DMA_FAULT_REASON_RESV_BIT_ERROR_IN_MAPPING_TABLE 0x04
#define EFI_DMA_FAULT_REASON_ACCESS_ADDR_OUT_OF_SPACE 0x05
#define EFI_DMA_FAULT_REASON_INVALID_ACCESS 0x06
#define EFI_DMA_FAULT_REASON_INVALID_REQUEST 0x07
#define EFI_DMA_FAULT_REASON_ACCESS_TRANSLATE_TABLE_ERROR 0x08
#define EFI_DMA_FAULT_REASON_RESV_BIT_ERROR_IN_TRANSLATE_TABLE 0x09
#define EFI_DMA_FAULT_REASON_INVALID_COMMAND 0x0a
#define EFI_DMA_FAULT_REASON_ACCESS_COMMAND_BUFFER_ERROR 0x0b

#define EFI_DMA_ACCESS_TYPE_WRITE 0x00
#define EFI_DMA_ACCESS_TYPE_READ 0x01

#define EFI_DMA_ADDRESS_UNTRANSLATED 0x00
#define EFI_DMA_ADDRESS_TRANSLATION 0x01

#define EFI_DMA_ARCH_TYPE_VT 0x01
#define EFI_DMA_ARCH_TYPE_IOMMU 0x02

struct efi_dmar_generic_error_data {
    uint16_t requester_id;
    uint16_t segment_number;
    uint8_t fault_reason;
    uint8_t access_type;
    uint8_t address_type;
    uint8_t arch_type;
    uint64_t device_addr;
    uint8_t resv1[16];
} __attribute__((__packed__));

struct efi_directed_io_dmar_error_data {
    uint8_t version;
    uint8_t revision;
    uint8_t oem_id[6];
    uint64_t capability;
    uint64_t capability_ex;
    uint32_t global_command;
    uint32_t global_status;
    uint32_t fault_status;
    uint8_t resv1[12];
    uint64_t fault_record[2];
    uint64_t root_entry[2];
    uint64_t context_entry[2];
    uint64_t pte_l6;
    uint64_t pte_l5;
    uint64_t pte_l4;
    uint64_t pte_l3;
    uint64_t pte_l2;
    uint64_t pte_l1;
} __attribute__((__packed__));

struct efi_iommu_dmar_error_data {
    uint8_t revision;
    uint8_t resv1[7];
    uint64_t control;
    uint64_t status;
    uint8_t resv2[8];
    uint64_t event_log_entry[2];
    uint8_t resv3[16];
    uint64_t device_table_entry[4];
    uint64_t pte_l6;
    uint64_t pte_l5;
    uint64_t pte_l4;
    uint64_t pte_l3;
    uint64_t pte_l2;
    uint64_t pte_l1;
} __attribute__((__packed__));

#define EFI_CCIX_PER_LOG_SOURCE_ID_VALID 0x0000000000000001
#define EFI_CCIX_PER_LOG_PORT_ID_VALID 0x0000000000000002
#define EFI_CCIX_PER_LOG_VALID 0x0000000000000004

// The CCIX PER log follows, up to length bytes in all.
struct efi_ccix_per_log_error_data {
    uint32_t length;
    uint64_t valid_fields;
    uint8_t ccix_source_id;
    uint8_t ccix_port_id;
    uint16_t resv1;
} __attribute__((__packed__));

#define EFI_CXL_CACHEMEM_AGENT_TYPE 0x0000000000000001
#define EFI_CXL_CACHEMEM_AGENT_ADDRESS 0x0000000000000002
#define EFI_CXL_CACHEMEM_DEVICE_ID 0x0000000000000004
#define EFI_CXL_CACHEMEM_DEVICE_SER_NUM 0x0000000000000008
#define EFI_CXL_CACHEMEM_CAP_STRUCT 0x0000000000000010
#define EFI_CXL_CACHEMEM_DVSEC 0x0000000000000020
#define EFI_CXL_CACHEMEM_ERROR_LOG 0x0000000000000040

#define EFI_CXL_AGENT_CXL11_DEV 0
#define EFI_CXL_AGENT_CXL11_DSP 1
#define EFI_CXL_AGENT_CXL20_DEV 2
#define EFI_CXL_AGENT_CXL20_LOGICAL_DEV 3
#define EFI_CXL_AGENT_CXL20_FMLD 4
#define EFI_CXL_AGENT_CXL20_RP 5
#define EFI_CXL_AGENT_CXL20_DSP 6
#define EFI_CXL_AGENT_CXL20_USP 7

union efi_cxl_agent_address {
    uint64_t bits;
    struct __attribute__((__packed__)) {
        uint32_t low;
        uint32_t high;
    } rcrb_base;
} __attribute__((__packed__));

#define EFI_CXL_AGENT_ADDRESS_FUNCTION_SHIFT 0
#define EFI_CXL_AGENT_ADDRESS_FUNCTION_MASK 0x00000000000000ff
#define EFI_CXL_AGENT_ADDRESS_DEVICE_SHIFT 8
#define EFI_CXL_AGENT_ADDRESS_DEVICE_MASK 0x000000000000ff00
#define EFI_CXL_AGENT_ADDRESS_BUS_SHIFT 16
#define EFI_CXL_AGENT_ADDRESS_BUS_MASK 0x0000000000ff0000
#define EFI_CXL_AGENT_ADDRESS_SEGMENT_SHIFT 24
#define EFI_CXL_AGENT_ADDRESS_SEGMENT_MASK 0x000000ffff000000

struct efi_cxl_agent_device_id {
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t svid;
    uint16_t sid;
    uint16_t class_code;
    uint16_t slot;
    uint32_t rsvd;
} __attribute__((__packed__));

#define EFI_CXL_AGENT_DEVICE_ID_SLOT_NUM_SHIFT 3
#define EFI_CXL_AGENT_DEVICE_ID_SLOT_NUM_MASK 0xfff8

struct efi_cxl_device_serial_num {
    uint32_t lower;
    uint32_t upper;
} __attribute__((__packed__));

// The CXL DVSEC (cxl_dvsec_length bytes) follows, then the CXL error log
// (cxl_error_log_length).
struct efi_cxl_protocol_error_data {
    uint64_t valid_fields;
    uint8_t cxl_agent_type;
    uint8_t resv1[7];
    union efi_cxl_agent_address cxl_agent_address;
    struct efi_cxl_agent_device_id device_id;
    struct efi_cxl_device_serial_num device_serial_number;
    uint8_t capability_structure[60];
    uint16_t cxl_dvsec_length;
    uint16_t cxl_error_log_length;
    uint32_t resv2;
} __attribute__((__packed__));

#define EFI_CXL_MEM_DEVICE_ID 0x0000000000000001
#define EFI_CXL_MEM_DEVICE_SER_NUM 0x0000000000000002
#define EFI_CXL_MEM_COMP_ERROR_LOG 0x0000000000000004

struct efi_cxl_error_pcie_dev_id {
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t function;
    uint8_t device;
    uint8_t bus;
    uint16_t segment;
    struct efi_generic_error_pci_slot slot;
    uint8_t resvd;
} __attribute__((__packed__));

// The CXL component event log follows, up to length bytes in all.
struct efi_cxl_component_event_log {
    uint32_t length;
    uint64_t valid_fields;
    struct efi_cxl_error_pcie_dev_id cxl_device_id;
    uint64_t device_serial_no;
} __attribute__((__packed__));

#define EFI_FRU_MEMORY_POISON_ARCH_TYPE_VALID 0x0000000000000001
#define EFI_FRU_MEMORY_POISON_ARCH_VALUE_VALID 0x0000000000000002
#define EFI_FRU_MEMORY_POISON_ID_TYPE_VALID 0x0000000000000004
#define EFI_FRU_MEMORY_POISON_ID_VALUE_VALID 0x0000000000000008
#define EFI_FRU_MEMORY_POISON_LIST_ENTRIES_VALID 0x0000000000000010
#define EFI_FRU_MEMORY_POISON_LIST_VALID 0x0000000000000020

#define EFI_FRU_MEMORY_POISON_ARCH_TYPE_X86_CPUID 0
#define EFI_FRU_MEMORY_POISON_ID_TYPE_X86_PPIN 0
#define EFI_FRU_MEMORY_POISON_HW_ID_TYPE_MCA_IPID 0
#define EFI_FRU_MEMORY_POISON_ADDRESS_TYPE_MCA_ADDR 0

// poison_list_entries struct efi_fru_memory_poison_descriptor follow.
struct efi_fru_memory_poison_data {
    uint32_t checksum;
    uint64_t valid_fields;
    uint32_t fru_arch_type;
    uint64_t fru_arch_value;
    uint32_t fru_id_type;
    uint64_t fru_id_value;
    uint32_t poison_list_entries;
} __attribute__((__packed__));

struct efi_fru_memory_poison_descriptor {
    uint64_t poison_timestamp;
    uint32_t hw_id_type;
    uint64_t hw_id_value;
    uint32_t address_type;
    uint64_t address_value;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
