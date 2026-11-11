#ifndef EFI_EFITCG2_H_
#define EFI_EFITCG2_H_

#include "efiapi.h"
#include "eficc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TCG2_PROTOCOL_GUID \
    {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}}

struct efi_tcg2_protocol;

#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x00000001
#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef uint32_t EFI_TCG2_EVENT_LOG_BITMAP;
typedef uint32_t EFI_TCG2_EVENT_LOG_FORMAT;
typedef uint32_t EFI_TCG2_EVENT_ALGORITHM_BITMAP;

struct efi_tcg2_version {
    uint8_t Major;
    uint8_t Minor;
};

/* Explicitly not packed, unlike the document's other structures: 36 bytes. */
struct efi_tcg2_boot_service_capability {
    uint8_t Size;
    struct efi_tcg2_version StructureVersion;
    struct efi_tcg2_version ProtocolVersion;
    EFI_TCG2_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
    EFI_TCG2_EVENT_LOG_BITMAP SupportedEventLogs;
    uint8_t TPMPresentFlag;
    uint16_t MaxCommandSize;
    uint16_t MaxResponseSize;
    uint32_t ManufacturerID;
    uint32_t NumberOfPcrBanks;
    EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
};

#define EFI_TCG2_BOOT_HASH_ALG_SHA1 0x00000001
#define EFI_TCG2_BOOT_HASH_ALG_SHA256 0x00000002
#define EFI_TCG2_BOOT_HASH_ALG_SHA384 0x00000004
#define EFI_TCG2_BOOT_HASH_ALG_SHA512 0x00000008
#define EFI_TCG2_BOOT_HASH_ALG_SM3_256 0x00000010

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_CAPABILITY)(
    struct efi_tcg2_protocol *This,
    struct efi_tcg2_boot_service_capability *ProtocolCapability
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_EVENT_LOG)(
    struct efi_tcg2_protocol *This,
    EFI_TCG2_EVENT_LOG_FORMAT EventLogFormat,
    EFI_PHYSICAL_ADDRESS *EventLogLocation,
    EFI_PHYSICAL_ADDRESS *EventLogLastEntry,
    bool *EventLogTruncated
);

typedef uint32_t EFI_TCG_EVENTTYPE;

struct efi_tcg2_event_header {
    uint32_t HeaderSize;
    uint16_t HeaderVersion;
    EFI_TCG_PCRINDEX PCRIndex;
    EFI_TCG_EVENTTYPE EventType;
} __attribute__((__packed__));

/* Event is printed as []; it is variable-length, and Size covers the whole record. */
struct efi_tcg2_event {
    uint32_t Size;
    struct efi_tcg2_event_header Header;
    uint8_t Event[1];
} __attribute__((__packed__));

#define EFI_TCG2_EXTEND_ONLY 0x0000000000000001
#define EFI_PE_COFF_IMAGE 0x0000000000000010

typedef EFI_STATUS (EFI_API *EFI_TCG2_HASH_LOG_EXTEND_EVENT)(
    struct efi_tcg2_protocol *This,
    uint64_t Flags,
    EFI_PHYSICAL_ADDRESS DataToHash,
    uint64_t DataToHashLen,
    struct efi_tcg2_event *EfiTcgEvent
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_SUBMIT_COMMAND)(
    struct efi_tcg2_protocol *This,
    uint32_t InputParameterBlockSize,
    uint8_t *InputParameterBlock,
    uint32_t OutputParameterBlockSize,
    uint8_t *OutputParameterBlock
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_ACTIVE_PCR_BANKS)(
    struct efi_tcg2_protocol *This,
    uint32_t *ActivePcrBanks
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_SET_ACTIVE_PCR_BANKS)(
    struct efi_tcg2_protocol *This,
    uint32_t ActivePcrBanks
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS)(
    struct efi_tcg2_protocol *This,
    uint32_t *OperationPresent,
    uint32_t *Response
);

struct efi_tcg2_protocol {
    EFI_TCG2_GET_CAPABILITY GetCapability;
    EFI_TCG2_GET_EVENT_LOG GetEventLog;
    EFI_TCG2_HASH_LOG_EXTEND_EVENT HashLogExtendEvent;
    EFI_TCG2_SUBMIT_COMMAND SubmitCommand;
    EFI_TCG2_GET_ACTIVE_PCR_BANKS GetActivePcrBanks;
    EFI_TCG2_SET_ACTIVE_PCR_BANKS SetActivePcrBanks;
    EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS GetResultOfSetActivePcrBanks;
};

#define EFI_TCG2_FINAL_EVENTS_TABLE_GUID \
    {0x1e2ed096, 0x30e2, 0x4254, {0xbd, 0x89, 0x86, 0x3b, 0xbe, 0xf8, 0x23, 0x25}}

/* Natural alignment; Event starts NumberOfEvents serialised TCG_PCR_EVENT2 records. */
struct efi_tcg2_final_events_table {
    uint64_t Version;
    uint64_t NumberOfEvents;
    uint8_t Event[1];
};

#define EFI_TCG2_FINAL_EVENTS_TABLE_VERSION 1

#ifdef __cplusplus
}
#endif

#endif
