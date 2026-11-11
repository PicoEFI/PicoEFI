#ifndef EFI_EFICC_H_
#define EFI_EFICC_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CC_MEASUREMENT_PROTOCOL_GUID \
    {0x96751a3d, 0x72f4, 0x41a6, {0xa7, 0x94, 0xed, 0x5d, 0xe, 0x67, 0xae, 0x6b}}

struct efi_cc_measurement_protocol;

struct efi_cc_version {
    uint8_t Major;
    uint8_t Minor;
};

typedef uint32_t EFI_CC_EVENT_LOG_BITMAP;
typedef uint32_t EFI_CC_EVENT_ALGORITHM_BITMAP;

#define EFI_CC_BOOT_HASH_ALG_SHA384 0x00000004

struct efi_cc_type {
    uint8_t Type;
    uint8_t SubType;
};

#define EFI_CC_TYPE_NONE 0
/* Not listed by UEFI 2.11: the value the ACPI CC event log table gives AMD SEV. */
#define EFI_CC_TYPE_AMD_SEV 1
#define EFI_CC_TYPE_INTEL_TDX 2
#define EFI_CC_TYPE_RISCV_APTEE 3

struct efi_cc_boot_service_capability {
    uint8_t Size;
    struct efi_cc_version StructureVersion;
    struct efi_cc_version ProtocolVersion;
    EFI_CC_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
    EFI_CC_EVENT_LOG_BITMAP SupportedEventLogs;
    struct efi_cc_type CcType;
};

typedef EFI_STATUS (EFI_API *EFI_CC_GET_CAPABILITY)(
    struct efi_cc_measurement_protocol *This,
    struct efi_cc_boot_service_capability *ProtocolCapability
);

typedef uint32_t EFI_CC_EVENT_LOG_FORMAT;

#define EFI_CC_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef EFI_STATUS (EFI_API *EFI_CC_GET_EVENT_LOG)(
    struct efi_cc_measurement_protocol *This,
    EFI_CC_EVENT_LOG_FORMAT EventLogFormat,
    EFI_PHYSICAL_ADDRESS *EventLogLocation,
    EFI_PHYSICAL_ADDRESS *EventLogLastEntry,
    bool *EventLogTruncated
);

#define EFI_CC_FLAG_EXTEND_ONLY 0x0000000000000001
#define EFI_CC_FLAG_PE_COFF_IMAGE 0x0000000000000010

typedef uint32_t EFI_CC_MR_INDEX;

/* Not named by the specification: the value HeaderVersion must hold. */
#define EFI_CC_EVENT_HEADER_VERSION 1

struct efi_cc_event_header {
    uint32_t HeaderSize;
    uint16_t HeaderVersion;
    EFI_CC_MR_INDEX MrIndex;
    uint32_t EventType;
} __attribute__((__packed__));

/* Event is variable-length: Size covers the whole record. */
struct efi_cc_event {
    uint32_t Size;
    struct efi_cc_event_header Header;
    uint8_t Event[1];
} __attribute__((__packed__));

/* Printed as a second EFI_CC_GET_EVENT_LOG; named as the protocol structure types it. */
typedef EFI_STATUS (EFI_API *EFI_CC_HASH_LOG_EXTEND_EVENT)(
    struct efi_cc_measurement_protocol *This,
    uint64_t Flags,
    EFI_PHYSICAL_ADDRESS DataToHash,
    uint64_t DataToHashLen,
    struct efi_cc_event *EfiCcEvent
);

typedef uint32_t EFI_TCG_PCRINDEX;

typedef EFI_STATUS (EFI_API *EFI_CC_MAP_PCR_TO_MR_INDEX)(
    struct efi_cc_measurement_protocol *This,
    EFI_TCG_PCRINDEX PcrIndex,
    EFI_CC_MR_INDEX *MrIndex
);

struct efi_cc_measurement_protocol {
    EFI_CC_GET_CAPABILITY GetCapability;
    EFI_CC_GET_EVENT_LOG GetEventLog;
    EFI_CC_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
    EFI_CC_MAP_PCR_TO_MR_INDEX MapPcrToMrIndex;
};

#define EFI_CC_FINAL_EVENTS_TABLE_GUID \
    {0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}

/* NumberOfEvents serialised CC_EVENT records follow; they have no C layout (TCG digest lists). */
struct efi_cc_final_events_table {
    uint64_t Version;
    uint64_t NumberOfEvents;
};

#ifdef __cplusplus
}
#endif

#endif
