#ifndef EFI_EFICC_H_
#define EFI_EFICC_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CC_MEASUREMENT_PROTOCOL_GUID \
    {0x96751a3d, 0x72f4, 0x41a6, {0xa7, 0x94, 0xed, 0x5d, 0xe, 0x67, 0xae, 0x6b}}

typedef struct _EFI_CC_MEASUREMENT_PROTOCOL EFI_CC_MEASUREMENT_PROTOCOL;

typedef struct {
    EFI_UINT8 Major;
    EFI_UINT8 Minor;
} EFI_CC_VERSION;

typedef EFI_UINT32 EFI_CC_EVENT_LOG_BITMAP;
typedef EFI_UINT32 EFI_CC_EVENT_ALGORITHM_BITMAP;

#define EFI_CC_BOOT_HASH_ALG_SHA384 0x00000004

typedef struct {
    EFI_UINT8 Type;
    EFI_UINT8 SubType;
} EFI_CC_TYPE;

#define EFI_CC_TYPE_NONE 0
/* Not listed by UEFI 2.11: the value the ACPI CC event log table gives AMD SEV. */
#define EFI_CC_TYPE_AMD_SEV 1
#define EFI_CC_TYPE_INTEL_TDX 2
#define EFI_CC_TYPE_RISCV_APTEE 3

typedef struct {
    EFI_UINT8 Size;
    EFI_CC_VERSION StructureVersion;
    EFI_CC_VERSION ProtocolVersion;
    EFI_CC_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
    EFI_CC_EVENT_LOG_BITMAP SupportedEventLogs;
    EFI_CC_TYPE CcType;
} EFI_CC_BOOT_SERVICE_CAPABILITY;

typedef EFI_STATUS (EFI_API *EFI_CC_GET_CAPABILITY)(
    EFI_IN EFI_CC_MEASUREMENT_PROTOCOL *This,
    EFI_IN EFI_OUT EFI_CC_BOOT_SERVICE_CAPABILITY *ProtocolCapability
);

typedef EFI_UINT32 EFI_CC_EVENT_LOG_FORMAT;

#define EFI_CC_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef EFI_STATUS (EFI_API *EFI_CC_GET_EVENT_LOG)(
    EFI_IN EFI_CC_MEASUREMENT_PROTOCOL *This,
    EFI_IN EFI_CC_EVENT_LOG_FORMAT EventLogFormat,
    EFI_OUT EFI_PHYSICAL_ADDRESS *EventLogLocation,
    EFI_OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry,
    EFI_OUT EFI_BOOLEAN *EventLogTruncated
);

#define EFI_CC_FLAG_EXTEND_ONLY 0x0000000000000001
#define EFI_CC_FLAG_PE_COFF_IMAGE 0x0000000000000010

typedef EFI_UINT32 EFI_CC_MR_INDEX;

/* Not named by the specification: the value HeaderVersion must hold. */
#define EFI_CC_EVENT_HEADER_VERSION 1

typedef struct __attribute__((__packed__)) {
    EFI_UINT32 HeaderSize;
    EFI_UINT16 HeaderVersion;
    EFI_CC_MR_INDEX MrIndex;
    EFI_UINT32 EventType;
} EFI_CC_EVENT_HEADER;

/* Event is variable-length: Size covers the whole record. */
typedef struct __attribute__((__packed__)) {
    EFI_UINT32 Size;
    EFI_CC_EVENT_HEADER Header;
    EFI_UINT8 Event[1];
} EFI_CC_EVENT;

/* Printed as a second EFI_CC_GET_EVENT_LOG; named as the protocol structure types it. */
typedef EFI_STATUS (EFI_API *EFI_CC_HASH_LOG_EXTEND_EVENT)(
    EFI_IN EFI_CC_MEASUREMENT_PROTOCOL *This,
    EFI_IN EFI_UINT64 Flags,
    EFI_IN EFI_PHYSICAL_ADDRESS DataToHash,
    EFI_IN EFI_UINT64 DataToHashLen,
    EFI_IN EFI_CC_EVENT *EfiCcEvent
);

typedef EFI_UINT32 EFI_TCG_PCRINDEX;

typedef EFI_STATUS (EFI_API *EFI_CC_MAP_PCR_TO_MR_INDEX)(
    EFI_IN EFI_CC_MEASUREMENT_PROTOCOL *This,
    EFI_IN EFI_TCG_PCRINDEX PcrIndex,
    EFI_OUT EFI_CC_MR_INDEX *MrIndex
);

struct _EFI_CC_MEASUREMENT_PROTOCOL {
    EFI_CC_GET_CAPABILITY GetCapability;
    EFI_CC_GET_EVENT_LOG GetEventLog;
    EFI_CC_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
    EFI_CC_MAP_PCR_TO_MR_INDEX MapPcrToMrIndex;
};

#define EFI_CC_FINAL_EVENTS_TABLE_GUID \
    {0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}

/* NumberOfEvents serialised CC_EVENT records follow; they have no C layout (TCG digest lists). */
typedef struct {
    EFI_UINT64 Version;
    EFI_UINT64 NumberOfEvents;
} EFI_CC_FINAL_EVENTS_TABLE;

#ifdef __cplusplus
}
#endif

#endif
