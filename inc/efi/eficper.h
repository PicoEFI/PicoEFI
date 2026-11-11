#ifndef EFI_EFICPER_H_
#define EFI_EFICPER_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ERROR_RECORD_SIGNATURE_START EFI_SIGNATURE_32('C', 'P', 'E', 'R')
#define EFI_ERROR_RECORD_SIGNATURE_END 0xFFFFFFFF

#define EFI_ERROR_RECORD_REVISION 0x0101

#define EFI_GENERIC_ERROR_RECOVERABLE 0
#define EFI_GENERIC_ERROR_FATAL 1
#define EFI_GENERIC_ERROR_CORRECTED 2
#define EFI_GENERIC_ERROR_INFO 3

#define EFI_ERROR_RECORD_HEADER_PLATFORM_ID_VALID 0x00000001
#define EFI_ERROR_RECORD_HEADER_TIME_STAMP_VALID 0x00000002
#define EFI_ERROR_RECORD_HEADER_PARTITION_ID_VALID 0x00000004

struct efi_error_time_stamp {
    uint8_t Seconds;
    uint8_t Minutes;
    uint8_t Hours;
    uint8_t Flag;
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
    uint8_t Century;
} __attribute__((__packed__));

#define EFI_ERROR_TIME_STAMP_PRECISE 0x01

#define EFI_EVENT_NOTIFICATION_TYPE_CMC_GUID \
    {0x2DCE8BB1, 0xBDD7, 0x450e, {0xB9, 0xAD, 0x9C, 0xF4, 0xEB, 0xD4, 0xF8, 0x90}}

#define EFI_EVENT_NOTIFICATION_TYPE_CPE_GUID \
    {0x4E292F96, 0xD843, 0x4a55, {0xA8, 0xC2, 0xD4, 0x81, 0xF2, 0x7E, 0xBE, 0xEE}}

#define EFI_EVENT_NOTIFICATION_TYPE_MCE_GUID \
    {0xE8F56FFE, 0x919C, 0x4cc5, {0xBA, 0x88, 0x65, 0xAB, 0xE1, 0x49, 0x13, 0xBB}}

#define EFI_EVENT_NOTIFICATION_TYPE_PCIE_GUID \
    {0xCF93C01F, 0x1A16, 0x4dfc, {0xB8, 0xBC, 0x9C, 0x4D, 0xAF, 0x67, 0xC1, 0x04}}

#define EFI_EVENT_NOTIFICATION_TYPE_INIT_GUID \
    {0xCC5263E8, 0x9308, 0x454a, {0x89, 0xD0, 0x34, 0x0B, 0xD3, 0x9B, 0xC9, 0x8E}}

#define EFI_EVENT_NOTIFICATION_TYPE_NMI_GUID \
    {0x5BAD89FF, 0xB7E6, 0x42c9, {0x81, 0x4A, 0xCF, 0x24, 0x85, 0xD6, 0xE9, 0x8A}}

#define EFI_EVENT_NOTIFICATION_TYPE_BOOT_GUID \
    {0x3D61A466, 0xAB40, 0x409a, {0xA6, 0x98, 0xF3, 0x62, 0xD4, 0x64, 0xB3, 0x8F}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_GUID \
    {0x667DD791, 0xC6B3, 0x4c27, {0x8A, 0x6B, 0x0F, 0x8E, 0x72, 0x2D, 0xEB, 0x41}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_SEA \
    {0x9A78788A, 0xBBE8, 0x11E4, {0x80, 0x9E, 0x67, 0x61, 0x1E, 0x5D, 0x46, 0xB0}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_SEI \
    {0x5C284C81, 0xB0AE, 0x4E87, {0xA3, 0x22, 0xB0, 0x4C, 0x85, 0x62, 0x43, 0x23}}

#define EFI_EVENT_NOTIFICATION_TYPE_DMAR_PEI \
    {0x09A9D5AC, 0x5204, 0x4214, {0x96, 0xE5, 0x94, 0x99, 0x2E, 0x75, 0x2B, 0xCD}}

#define EFI_EVENT_NOTIFICATION_TYPE_CXL_COMPONENT_GUID \
    {0x69293BC9, 0x41DF, 0x49A3, {0xB4, 0xBD, 0x4F, 0xB0, 0xDB, 0x30, 0x41, 0xF6}}

#define EFI_HW_ERROR_FLAGS_RECOVERED 0x00000001
#define EFI_HW_ERROR_FLAGS_PREVERR 0x00000002
#define EFI_HW_ERROR_FLAGS_SIMULATED 0x00000004

/* SectionCount struct efi_error_section_descriptor follow, then the section bodies. */
struct efi_common_error_record_header {
    uint32_t SignatureStart;
    uint16_t Revision;
    uint32_t SignatureEnd;
    uint16_t SectionCount;
    uint32_t ErrorSeverity;
    uint32_t ValidationBits;
    uint32_t RecordLength;
    struct efi_error_time_stamp TimeStamp;
    struct efi_guid PlatformID;
    struct efi_guid PartitionID;
    struct efi_guid CreatorID;
    struct efi_guid NotificationType;
    uint64_t RecordID;
    uint32_t Flags;
    uint64_t PersistenceInfo;
    uint8_t Resv1[12];
} __attribute__((__packed__));

struct efi_generic_error_status {
    uint64_t Resv1:8;
    uint64_t Type:8;
    uint64_t AddressSignal:1;
    uint64_t ControlSignal:1;
    uint64_t DataSignal:1;
    uint64_t DetectedByResponder:1;
    uint64_t DetectedByRequester:1;
    uint64_t FirstError:1;
    uint64_t OverflowNotLogged:1;
    uint64_t Resv2:41;
} __attribute__((__packed__));

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
    {0x9876CCAD, 0x47B4, 0x4bdb, {0xB6, 0x5E, 0x16, 0xF1, 0x93, 0xC4, 0xF3, 0xDB}}

#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_IA32X64_GUID \
    {0xDC3EA0B0, 0xA144, 0x4797, {0xB9, 0x5B, 0x53, 0xFA, 0x24, 0x2B, 0x6E, 0x1D}}

/* Misprinted with nine trailing bytes; this is the SAL processor device error section GUID. */
#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_IPF_GUID \
    {0xe429faf1, 0x3cb7, 0x11d4, {0xbc, 0xa7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}

#define EFI_ERROR_SECTION_PROCESSOR_SPECIFIC_ARM_GUID \
    {0xE19E3D16, 0xBC11, 0x11E4, {0x9C, 0xAA, 0xC2, 0x05, 0x1D, 0x5D, 0x46, 0xB0}}

#define EFI_ERROR_SECTION_PLATFORM_MEMORY_GUID \
    {0xA5BC1114, 0x6F64, 0x4EDE, {0xB8, 0x63, 0x3E, 0x83, 0xED, 0x7C, 0x83, 0xB1}}

#define EFI_ERROR_SECTION_PLATFORM_MEMORY2_GUID \
    {0x61EC04FC, 0x48E6, 0xD813, {0x25, 0xC9, 0x8D, 0xAA, 0x44, 0x75, 0x0B, 0x12}}

#define EFI_ERROR_SECTION_PCIE_GUID \
    {0xD995E954, 0xBBC1, 0x430F, {0xAD, 0x91, 0xB4, 0x4D, 0xCB, 0x3C, 0x6F, 0x35}}

#define EFI_ERROR_SECTION_FW_ERROR_RECORD_GUID \
    {0x81212A96, 0x09ED, 0x4996, {0x94, 0x71, 0x8D, 0x72, 0x9C, 0x8E, 0x69, 0xED}}

#define EFI_ERROR_SECTION_PCI_PCIX_BUS_GUID \
    {0xC5753963, 0x3B84, 0x4095, {0xBF, 0x78, 0xED, 0xDA, 0xD3, 0xF9, 0xC9, 0xDD}}

#define EFI_ERROR_SECTION_PCI_DEVICE_GUID \
    {0xEB5E4685, 0xCA66, 0x4769, {0xB6, 0xA2, 0x26, 0x06, 0x8B, 0x00, 0x13, 0x26}}

#define EFI_ERROR_SECTION_DMAR_GENERIC_GUID \
    {0x5B51FEF7, 0xC79D, 0x4434, {0x8F, 0x1B, 0xAA, 0x62, 0xDE, 0x3E, 0x2C, 0x64}}

#define EFI_ERROR_SECTION_DIRECTED_IO_DMAR_GUID \
    {0x71761D37, 0x32B2, 0x45cd, {0xA7, 0xD0, 0xB0, 0xFE, 0xDD, 0x93, 0xE8, 0xCF}}

#define EFI_ERROR_SECTION_IOMMU_DMAR_GUID \
    {0x036F84E1, 0x7F37, 0x428c, {0xA7, 0x9E, 0x57, 0x5F, 0xDF, 0xAA, 0x84, 0xEC}}

#define EFI_ERROR_SECTION_CCIX_PER_LOG_GUID \
    {0x91335EF6, 0xEBFB, 0x4478, {0xA6, 0xA6, 0x88, 0xB7, 0x28, 0xCF, 0x75, 0xD7}}

#define EFI_ERROR_SECTION_CXL_PROTOCOL_ERROR_GUID \
    {0x80B9EFB4, 0x52B5, 0x4DE3, {0xA7, 0x77, 0x68, 0x78, 0x4B, 0x77, 0x10, 0x48}}

#define EFI_ERROR_SECTION_FRU_MEMORY_POISON_GUID \
    {0x5E4706C1, 0x5356, 0x48C6, {0x93, 0x0B, 0x52, 0xF2, 0x12, 0x0A, 0x44, 0x58}}

struct efi_error_section_descriptor {
    uint32_t SectionOffset;
    uint32_t SectionLength;
    uint16_t Revision;
    uint8_t SecValidMask;
    uint8_t Resv1;
    uint32_t SectionFlags;
    struct efi_guid SectionType;
    struct efi_guid FruId;
    uint32_t Severity;
    char FruString[20];
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
    uint64_t ValidFields;
    uint8_t Type;
    uint8_t Isa;
    uint8_t ErrorType;
    uint8_t Operation;
    uint8_t Flags;
    uint8_t Level;
    uint16_t Resv1;
    uint64_t VersionInfo;
    char BrandString[128];
    uint64_t ApicId;
    uint64_t TargetAddr;
    uint64_t RequestorId;
    uint64_t ResponderId;
    uint64_t InstructionIP;
} __attribute__((__packed__));

#define EFI_IA32_X64_PROCESSOR_ERROR_APIC_ID_VALID 0x0000000000000001
#define EFI_IA32_X64_PROCESSOR_ERROR_CPU_ID_INFO_VALID 0x0000000000000002

struct efi_ia32_x64_valid_bits {
    uint64_t ApicIdValid:1;
    uint64_t CpuIdInfoValid:1;
    uint64_t ErrorInfoNum:6;
    uint64_t ContextNum:6;
    uint64_t Resv1:50;
} __attribute__((__packed__));

/* The error information and context structures that ValidFields counts follow. */
struct efi_ia32_x64_processor_error_record {
    uint64_t ValidFields;
    uint64_t ApicId;
    uint8_t CpuIdInfo[48];
} __attribute__((__packed__));

#define EFI_IA32_X64_ERROR_TYPE_CACHE_CHECK_GUID \
    {0xA55701F5, 0xE3EF, 0x43de, {0xAC, 0x72, 0x24, 0x9B, 0x57, 0x3F, 0xAD, 0x2C}}

#define EFI_IA32_X64_ERROR_TYPE_TLB_CHECK_GUID \
    {0xFC06B535, 0x5E1F, 0x4562, {0x9F, 0x25, 0x0A, 0x3B, 0x9A, 0xDB, 0x63, 0xC3}}

#define EFI_IA32_X64_ERROR_TYPE_BUS_CHECK_GUID \
    {0x1CF3F8B3, 0xC5B1, 0x49a2, {0xAA, 0x59, 0x5E, 0xEF, 0x92, 0xFF, 0xA6, 0x3C}}

#define EFI_IA32_X64_ERROR_TYPE_MS_CHECK_GUID \
    {0x48AB7F57, 0xDC34, 0x4f6c, {0xA7, 0xD3, 0xB0, 0xB5, 0xB0, 0xA7, 0x43, 0x14}}

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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorUncorrected:1;
    uint64_t PreciseIp:1;
    uint64_t RestartableIp:1;
    uint64_t Overflow:1;
    uint64_t Resv1:34;
} __attribute__((__packed__));

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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorUncorrected:1;
    uint64_t PreciseIp:1;
    uint64_t RestartableIp:1;
    uint64_t Overflow:1;
    uint64_t Resv1:34;
} __attribute__((__packed__));

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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorUncorrected:1;
    uint64_t PreciseIp:1;
    uint64_t RestartableIp:1;
    uint64_t Overflow:1;
    uint64_t ParticipationType:2;
    uint64_t TimeOut:1;
    uint64_t AddressSpace:2;
    uint64_t Resv1:29;
} __attribute__((__packed__));

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
    uint64_t ValidFields:16;
    uint64_t ErrorType:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorUncorrected:1;
    uint64_t PreciseIp:1;
    uint64_t RestartableIp:1;
    uint64_t Overflow:1;
    uint64_t Resv1:40;
} __attribute__((__packed__));

union efi_ia32_x64_check_info_item {
    struct efi_ia32_x64_cache_check_info CacheCheck;
    struct efi_ia32_x64_tlb_check_info TlbCheck;
    struct efi_ia32_x64_bus_check_info BusCheck;
    struct efi_ia32_x64_ms_check_info MsCheck;
    uint64_t Data64;
} __attribute__((__packed__));

struct efi_ia32_x64_process_error_info {
    struct efi_guid ErrorType;
    uint64_t ValidFields;
    union efi_ia32_x64_check_info_item CheckInfo;
    uint64_t TargetId;
    uint64_t RequestorId;
    uint64_t ResponderId;
    uint64_t InstructionIP;
} __attribute__((__packed__));

#define EFI_REG_CONTEXT_TYPE_UNCLASSIFIED 0x0000
#define EFI_REG_CONTEXT_TYPE_MSR 0x0001
#define EFI_REG_CONTEXT_TYPE_IA32 0x0002
#define EFI_REG_CONTEXT_TYPE_X64 0x0003
#define EFI_REG_CONTEXT_TYPE_FXSAVE 0x0004
#define EFI_REG_CONTEXT_TYPE_DR_IA32 0x0005
#define EFI_REG_CONTEXT_TYPE_DR_X64 0x0006
#define EFI_REG_CONTEXT_TYPE_MEM_MAP 0x0007

/* The register array follows: ArraySize bytes, zero-padded to a multiple of 16. */
struct efi_ia32_x64_processor_context_info {
    uint16_t RegisterType;
    uint16_t ArraySize;
    uint32_t MsrAddress;
    uint64_t MmRegisterAddress;
} __attribute__((__packed__));

struct efi_context_ia32_register_state {
    uint32_t Eax;
    uint32_t Ebx;
    uint32_t Ecx;
    uint32_t Edx;
    uint32_t Esi;
    uint32_t Edi;
    uint32_t Ebp;
    uint32_t Esp;
    uint16_t Cs;
    uint16_t Ds;
    uint16_t Ss;
    uint16_t Es;
    uint16_t Fs;
    uint16_t Gs;
    uint32_t Eflags;
    uint32_t Eip;
    uint32_t Cr0;
    uint32_t Cr1;
    uint32_t Cr2;
    uint32_t Cr3;
    uint32_t Cr4;
    uint32_t Gdtr[2];
    uint32_t Idtr[2];
    uint16_t Ldtr;
    uint16_t Tr;
} __attribute__((__packed__));

/* The instruction pointer is misprinted EIP. */
struct efi_context_x64_register_state {
    uint64_t Rax;
    uint64_t Rbx;
    uint64_t Rcx;
    uint64_t Rdx;
    uint64_t Rsi;
    uint64_t Rdi;
    uint64_t Rbp;
    uint64_t Rsp;
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
    uint16_t Cs;
    uint16_t Ds;
    uint16_t Ss;
    uint16_t Es;
    uint16_t Fs;
    uint16_t Gs;
    uint32_t Resv1;
    uint64_t Rflags;
    uint64_t Rip;
    uint64_t Cr0;
    uint64_t Cr1;
    uint64_t Cr2;
    uint64_t Cr3;
    uint64_t Cr4;
    uint64_t Cr8;
    uint64_t Gdtr[2];
    uint64_t Idtr[2];
    uint16_t Ldtr;
    uint16_t Tr;
} __attribute__((__packed__));

#define EFI_ARM_PROC_ERROR_MPIDR_VALID 0x00000001
#define EFI_ARM_PROC_ERROR_ERROR_AFFINITY_LVL_VALID 0x00000002
#define EFI_ARM_PROC_ERROR_RUNNING_STATE_VALID 0x00000004
#define EFI_ARM_PROC_ERROR_VENDOR_INFO_VALID 0x00000008

#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_0 0x00
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_1 0x01
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_2 0x02
#define EFI_ARM_PROC_ERROR_AFFINITY_LVL_3 0x03

/*
 * ErrInfoNum struct efi_arm_processor_error_information follow, then ContextInfoNum
 * struct efi_arm_processor_context_information, then any vendor-specific information.
 */
struct efi_arm_processor_error_record {
    uint32_t ValidFields;
    uint16_t ErrInfoNum;
    uint16_t ContextInfoNum;
    uint32_t SectionLength;
    uint8_t ErrAffinityLvl;
    uint8_t Reserved[3];
    uint64_t MPIDR_EL1;
    uint64_t MIDR_EL1;
    uint32_t RunState;
    uint32_t PsciState;
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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorCorrected:1;
    uint64_t PrecisePc:1;
    uint64_t RestartablePc:1;
    uint64_t Reserved:35;
} __attribute__((__packed__));

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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorCorrected:1;
    uint64_t PrecisePc:1;
    uint64_t RestartablePc:1;
    uint64_t Reserved:35;
} __attribute__((__packed__));

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
    uint64_t ValidFields:16;
    uint64_t TransactionType:2;
    uint64_t Operation:4;
    uint64_t Level:3;
    uint64_t ContextCorrupt:1;
    uint64_t ErrorCorrected:1;
    uint64_t PrecisePc:1;
    uint64_t RestartablePc:1;
    uint64_t ParticipationType:2;
    uint64_t TimeOut:1;
    uint64_t AddressSpace:2;
    uint64_t MemoryAccessAttribute:9;
    uint64_t AccessMode:1;
    uint64_t Reserved:20;
} __attribute__((__packed__));

union efi_arm_error_information {
    struct efi_arm_cache_error_info CacheErrorInfo;
    struct efi_arm_tlb_error_info TlbErrorInfo;
    struct efi_arm_bus_error_info BusErrorInfo;
} __attribute__((__packed__));

struct efi_arm_processor_error_information {
    uint8_t Version;
    uint8_t Length;
    uint16_t ValidFields;
    uint8_t Type;
    uint16_t ErrorCount;
    uint8_t Flags;
    union efi_arm_error_information ErrorInfo;
    uint64_t VirtualFaultAddress;
    uint64_t PhysicalFaultAddress;
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
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;
    uint32_t R12;
    uint32_t R13_SP;
    uint32_t R14_LR;
    uint32_t R15_PC;
} __attribute__((__packed__));

struct efi_arm_aarch32_el1_context_system_registers {
    uint32_t DFAR;
    uint32_t DFSR;
    uint32_t IFAR;
    uint32_t ISR;
    uint32_t MAIR0;
    uint32_t MAIR1;
    uint32_t MIDR;
    uint32_t MPIDR;
    uint32_t NMRR;
    uint32_t PRRR;
    uint32_t SCTLR;
    uint32_t SPSR;
    uint32_t SPSR_abt;
    uint32_t SPSR_fiq;
    uint32_t SPSR_irq;
    uint32_t SPSR_svc;
    uint32_t SPSR_und;
    uint32_t TPIDRPRW;
    uint32_t TPIDRURO;
    uint32_t TPIDRURW;
    uint32_t TTBCR;
    uint32_t TTBR0;
    uint32_t TTBR1;
    uint32_t DACR;
} __attribute__((__packed__));

struct efi_arm_aarch32_el2_context_system_registers {
    uint32_t ELR_hyp;
    uint32_t HAMAIR0;
    uint32_t HAMAIR1;
    uint32_t HCR;
    uint32_t HCR2;
    uint32_t HDFAR;
    uint32_t HIFAR;
    uint32_t HPFAR;
    uint32_t HSR;
    uint32_t HTCR;
    uint32_t HTPIDR;
    uint32_t HTTBR;
    uint32_t SPSR_hyp;
    uint32_t VTCR;
    uint32_t VTTBR;
    uint32_t DACR32_EL2;
} __attribute__((__packed__));

struct efi_arm_aarch32_secure_context_system_registers {
    uint32_t SCTLR;
    uint32_t SPSR_mon;
} __attribute__((__packed__));

struct efi_arm_aarch64_context_gpr {
    uint64_t X0;
    uint64_t X1;
    uint64_t X2;
    uint64_t X3;
    uint64_t X4;
    uint64_t X5;
    uint64_t X6;
    uint64_t X7;
    uint64_t X8;
    uint64_t X9;
    uint64_t X10;
    uint64_t X11;
    uint64_t X12;
    uint64_t X13;
    uint64_t X14;
    uint64_t X15;
    uint64_t X16;
    uint64_t X17;
    uint64_t X18;
    uint64_t X19;
    uint64_t X20;
    uint64_t X21;
    uint64_t X22;
    uint64_t X23;
    uint64_t X24;
    uint64_t X25;
    uint64_t X26;
    uint64_t X27;
    uint64_t X28;
    uint64_t X29;
    uint64_t X30;
    uint64_t SP;
} __attribute__((__packed__));

struct efi_arm_aarch64_el1_context_system_registers {
    uint64_t ELR_EL1;
    uint64_t ESR_EL1;
    uint64_t FAR_EL1;
    uint64_t ISR_EL1;
    uint64_t MAIR_EL1;
    uint64_t MIDR_EL1;
    uint64_t MPIDR_EL1;
    uint64_t SCTLR_EL1;
    uint64_t SP_EL0;
    uint64_t SP_EL1;
    uint64_t SPSR_EL1;
    uint64_t TCR_EL1;
    uint64_t TPIDR_EL0;
    uint64_t TPIDR_EL1;
    uint64_t TPIDRRO_EL0;
    uint64_t TTBR0_EL1;
    uint64_t TTBR1_EL1;
} __attribute__((__packed__));

struct efi_arm_aarch64_el2_context_system_registers {
    uint64_t ELR_EL2;
    uint64_t ESR_EL2;
    uint64_t FAR_EL2;
    uint64_t HACR_EL2;
    uint64_t HCR_EL2;
    uint64_t HPFAR_EL2;
    uint64_t MAIR_EL2;
    uint64_t SCTLR_EL2;
    uint64_t SP_EL2;
    uint64_t SPSR_EL2;
    uint64_t TCR_EL2;
    uint64_t TPIDR_EL2;
    uint64_t TTBR0_EL2;
    uint64_t VTCR_EL2;
    uint64_t VTTBR_EL2;
} __attribute__((__packed__));

struct efi_arm_aarch64_el3_context_system_registers {
    uint64_t ELR_EL3;
    uint64_t ESR_EL3;
    uint64_t FAR_EL3;
    uint64_t MAIR_EL3;
    uint64_t SCTLR_EL3;
    uint64_t SP_EL3;
    uint64_t SPSR_EL3;
    uint64_t TCR_EL3;
    uint64_t TPIDR_EL3;
    uint64_t TTBR0_EL3;
} __attribute__((__packed__));

struct efi_arm_misc_context_system_register {
    uint16_t MRS_Op2:3;
    uint16_t MRS_CRm:4;
    uint16_t MRS_CRn:4;
    uint16_t MRS_Op1:3;
    uint16_t MRS_O0:1;
    uint16_t Reserved:1;
    uint64_t RegisterVal;
} __attribute__((__packed__));

struct efi_arm_ttbr128_context_system_registers {
    uint64_t TTBR0_EL1[2];
    uint64_t TTBR0_EL2[2];
    uint64_t TTBR0_EL3[2];
    uint64_t TTBR1_EL1[2];
    uint64_t TTBR1_EL2[2];
    uint64_t VTTBR_EL2[2];
} __attribute__((__packed__));

union efi_context_register_array_info {
    struct efi_arm_aarch32_context_gpr Type0SysRegs;
    struct efi_arm_aarch32_el1_context_system_registers Type1SysRegs;
    struct efi_arm_aarch32_el2_context_system_registers Type2SysRegs;
    struct efi_arm_aarch32_secure_context_system_registers Type3SysRegs;
    struct efi_arm_aarch64_context_gpr Type4SysRegs;
    struct efi_arm_aarch64_el1_context_system_registers Type5SysRegs;
    struct efi_arm_aarch64_el2_context_system_registers Type6SysRegs;
    struct efi_arm_aarch64_el3_context_system_registers Type7SysRegs;
    struct efi_arm_misc_context_system_register SysRegInfo;
    struct efi_arm_ttbr128_context_system_registers Type9SysRegs;
} __attribute__((__packed__));

struct efi_arm_processor_context_information {
    uint16_t Version;
    uint16_t RegisterContextType;
    uint32_t RegisterArraySize;
    union efi_context_register_array_info RegisterArray;
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
    uint64_t ValidFields;
    struct efi_generic_error_status ErrorStatus;
    uint64_t PhysicalAddress;
    uint64_t PhysicalAddressMask;
    uint16_t Node;
    uint16_t Card;
    uint16_t ModuleRank;
    uint16_t Bank;
    uint16_t Device;
    uint16_t Row;
    uint16_t Column;
    uint16_t BitPosition;
    uint64_t RequestorId;
    uint64_t ResponderId;
    uint64_t TargetId;
    uint8_t ErrorType;
    uint8_t Extended;
    uint16_t RankNum;
    uint16_t CardHandle;
    uint16_t ModuleHandle;
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
    uint64_t ValidFields;
    struct efi_generic_error_status ErrorStatus;
    uint64_t PhysicalAddress;
    uint64_t PhysicalAddressMask;
    uint16_t Node;
    uint16_t Card;
    uint16_t Module;
    uint16_t Bank;
    uint32_t Device;
    uint32_t Row;
    uint32_t Column;
    uint32_t Rank;
    uint32_t BitPosition;
    uint8_t ChipId;
    uint8_t MemErrorType;
    uint8_t Status;
    uint8_t Reserved;
    uint64_t RequestorId;
    uint64_t ResponderId;
    uint64_t TargetId;
    uint32_t CardHandle;
    uint32_t ModuleHandle;
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
#define EFI_PCIE_ERROR_PORT_ROOT_EVENT_COLLECTOR 0x0000000A

struct efi_generic_error_pci_slot {
    uint16_t Resv1:3;
    uint16_t Number:13;
} __attribute__((__packed__));

struct efi_generic_error_pcie_dev_bridge_id {
    uint16_t VendorId;
    uint16_t DeviceId;
    uint8_t ClassCode[3];
    uint8_t Function;
    uint8_t Device;
    uint16_t Segment;
    uint8_t PrimaryOrDeviceBus;
    uint8_t SecondaryBus;
    struct efi_generic_error_pci_slot Slot;
    uint8_t Resv1;
} __attribute__((__packed__));

struct efi_pcie_error_data_capability {
    uint8_t PcieCap[60];
} __attribute__((__packed__));

struct efi_pcie_error_data_aer {
    uint8_t PcieAer[96];
} __attribute__((__packed__));

struct efi_pcie_error_data {
    uint64_t ValidFields;
    uint32_t PortType;
    uint32_t Version;
    uint32_t CommandStatus;
    uint32_t RcrbHighAddress;
    struct efi_generic_error_pcie_dev_bridge_id DevBridge;
    uint64_t SerialNo;
    uint32_t BridgeControlStatus;
    struct efi_pcie_error_data_capability Capability;
    struct efi_pcie_error_data_aer AerInfo;
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
    uint64_t ValidFields;
    struct efi_generic_error_status ErrorStatus;
    uint16_t Type;
    uint16_t BusId;
    uint32_t Resv2;
    uint64_t BusAddress;
    uint64_t BusData;
    uint64_t BusCommand;
    uint64_t RequestorId;
    uint64_t ResponderId;
    uint64_t TargetId;
} __attribute__((__packed__));

#define EFI_PCI_PCIX_DEVICE_ERROR_STATUS_VALID 0x0000000000000001
#define EFI_PCI_PCIX_DEVICE_ERROR_ID_INFO_VALID 0x0000000000000002
#define EFI_PCI_PCIX_DEVICE_ERROR_MEM_NUM_VALID 0x0000000000000004
#define EFI_PCI_PCIX_DEVICE_ERROR_IO_NUM_VALID 0x0000000000000008
#define EFI_PCI_PCIX_DEVICE_ERROR_REG_DATA_PAIR_VALID 0x0000000000000010

struct efi_generic_error_pci_device_id {
    uint16_t VendorId;
    uint16_t DeviceId;
    uint8_t ClassCode[3];
    uint8_t Function;
    uint8_t Device;
    uint8_t Bus;
    uint8_t Segment;
    uint8_t Resv1;
    uint32_t Resv2;
} __attribute__((__packed__));

/* MemoryNumber + IoNumber register address/data pairs, two uint64_t each, follow. */
struct efi_pci_pcix_device_error_data {
    uint64_t ValidFields;
    struct efi_generic_error_status ErrorStatus;
    struct efi_generic_error_pci_device_id IdInfo;
    uint32_t MemoryNumber;
    uint32_t IoNumber;
} __attribute__((__packed__));

#define EFI_FIRMWARE_ERROR_TYPE_IPF_SAL 0x00
#define EFI_FIRMWARE_ERROR_TYPE_SOC_TYPE1 0x01
#define EFI_FIRMWARE_ERROR_TYPE_SOC_TYPE2 0x02

/* The reserved bytes are misprinted at offset 1, over Revision: they are offsets 2 to 7. */
struct efi_firmware_error_data {
    uint8_t ErrorType;
    uint8_t Revision;
    uint8_t Resv1[6];
    uint64_t RecordId;
    struct efi_guid RecordIdGuid;
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
#define EFI_DMA_FAULT_REASON_INVALID_COMMAND 0x0A
#define EFI_DMA_FAULT_REASON_ACCESS_COMMAND_BUFFER_ERROR 0x0B

#define EFI_DMA_ACCESS_TYPE_WRITE 0x00
#define EFI_DMA_ACCESS_TYPE_READ 0x01

#define EFI_DMA_ADDRESS_UNTRANSLATED 0x00
#define EFI_DMA_ADDRESS_TRANSLATION 0x01

#define EFI_DMA_ARCH_TYPE_VT 0x01
#define EFI_DMA_ARCH_TYPE_IOMMU 0x02

struct efi_dmar_generic_error_data {
    uint16_t RequesterId;
    uint16_t SegmentNumber;
    uint8_t FaultReason;
    uint8_t AccessType;
    uint8_t AddressType;
    uint8_t ArchType;
    uint64_t DeviceAddr;
    uint8_t Resv1[16];
} __attribute__((__packed__));

struct efi_directed_io_dmar_error_data {
    uint8_t Version;
    uint8_t Revision;
    uint8_t OemId[6];
    uint64_t Capability;
    uint64_t CapabilityEx;
    uint32_t GlobalCommand;
    uint32_t GlobalStatus;
    uint32_t FaultStatus;
    uint8_t Resv1[12];
    uint64_t FaultRecord[2];
    uint64_t RootEntry[2];
    uint64_t ContextEntry[2];
    uint64_t PteL6;
    uint64_t PteL5;
    uint64_t PteL4;
    uint64_t PteL3;
    uint64_t PteL2;
    uint64_t PteL1;
} __attribute__((__packed__));

struct efi_iommu_dmar_error_data {
    uint8_t Revision;
    uint8_t Resv1[7];
    uint64_t Control;
    uint64_t Status;
    uint8_t Resv2[8];
    uint64_t EventLogEntry[2];
    uint8_t Resv3[16];
    uint64_t DeviceTableEntry[4];
    uint64_t PteL6;
    uint64_t PteL5;
    uint64_t PteL4;
    uint64_t PteL3;
    uint64_t PteL2;
    uint64_t PteL1;
} __attribute__((__packed__));

#define EFI_CCIX_PER_LOG_SOURCE_ID_VALID 0x0000000000000001
#define EFI_CCIX_PER_LOG_PORT_ID_VALID 0x0000000000000002
#define EFI_CCIX_PER_LOG_VALID 0x0000000000000004

/* The CCIX PER log follows, up to Length bytes in all. */
struct efi_ccix_per_log_error_data {
    uint32_t Length;
    uint64_t ValidFields;
    uint8_t CcixSourceId;
    uint8_t CcixPortId;
    uint16_t Resv1;
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
    struct __attribute__((__packed__)) {
        uint64_t Function:8;
        uint64_t Device:8;
        uint64_t Bus:8;
        uint64_t Segment:16;
        uint64_t Rsvd:24;
    } Bits;
    struct __attribute__((__packed__)) {
        uint32_t Low;
        uint32_t High;
    } RcrbBase;
} __attribute__((__packed__));

struct efi_cxl_agent_device_id {
    uint16_t VendorId;
    uint16_t DeviceId;
    uint16_t Svid;
    uint16_t Sid;
    uint16_t ClassCode;
    struct __attribute__((__packed__)) {
        uint16_t Rsvd:3;
        uint16_t Num:13;
    } Slot;
    uint32_t Rsvd;
} __attribute__((__packed__));

struct efi_cxl_device_serial_num {
    uint32_t Lower;
    uint32_t Upper;
} __attribute__((__packed__));

/* The CXL DVSEC (CxlDvsecLength bytes) follows, then the CXL error log (CxlErrorLogLength). */
struct efi_cxl_protocol_error_data {
    uint64_t ValidFields;
    uint8_t CxlAgentType;
    uint8_t Resv1[7];
    union efi_cxl_agent_address CxlAgentAddress;
    struct efi_cxl_agent_device_id DeviceId;
    struct efi_cxl_device_serial_num DeviceSerialNumber;
    uint8_t CapabilityStructure[60];
    uint16_t CxlDvsecLength;
    uint16_t CxlErrorLogLength;
    uint32_t Resv2;
} __attribute__((__packed__));

#define EFI_CXL_MEM_DEVICE_ID 0x0000000000000001
#define EFI_CXL_MEM_DEVICE_SER_NUM 0x0000000000000002
#define EFI_CXL_MEM_COMP_ERROR_LOG 0x0000000000000004

struct efi_cxl_error_pcie_dev_id {
    uint16_t VendorId;
    uint16_t DeviceId;
    uint8_t Function;
    uint8_t Device;
    uint8_t Bus;
    uint16_t Segment;
    struct efi_generic_error_pci_slot Slot;
    uint8_t Resvd;
} __attribute__((__packed__));

/* The CXL component event log follows, up to Length bytes in all. */
struct efi_cxl_component_event_log {
    uint32_t Length;
    uint64_t ValidFields;
    struct efi_cxl_error_pcie_dev_id CxlDeviceId;
    uint64_t DeviceSerialNo;
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

/* PoisonListEntries struct efi_fru_memory_poison_descriptor follow. */
struct efi_fru_memory_poison_data {
    uint32_t Checksum;
    uint64_t ValidFields;
    uint32_t FruArchType;
    uint64_t FruArchValue;
    uint32_t FruIdType;
    uint64_t FruIdValue;
    uint32_t PoisonListEntries;
} __attribute__((__packed__));

struct efi_fru_memory_poison_descriptor {
    uint64_t PoisonTimestamp;
    uint32_t HwIdType;
    uint64_t HwIdValue;
    uint32_t AddressType;
    uint64_t AddressValue;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
