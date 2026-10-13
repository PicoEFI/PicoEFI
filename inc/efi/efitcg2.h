#ifndef EFI_EFITCG2_H_
#define EFI_EFITCG2_H_

#include "efiapi.h"
#include "eficc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TCG2_PROTOCOL_GUID \
    {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}}

typedef struct _EFI_TCG2_PROTOCOL EFI_TCG2_PROTOCOL;

#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x00000001
#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef EFI_UINT32 EFI_TCG2_EVENT_LOG_BITMAP;
typedef EFI_UINT32 EFI_TCG2_EVENT_LOG_FORMAT;
typedef EFI_UINT32 EFI_TCG2_EVENT_ALGORITHM_BITMAP;

typedef struct _EFI_TCG2_VERSION {
    EFI_UINT8 Major;
    EFI_UINT8 Minor;
} EFI_TCG2_VERSION;

/* Explicitly not packed, unlike the document's other structures: 36 bytes. */
typedef struct _EFI_TCG2_BOOT_SERVICE_CAPABILITY {
    EFI_UINT8 Size;
    EFI_TCG2_VERSION StructureVersion;
    EFI_TCG2_VERSION ProtocolVersion;
    EFI_TCG2_EVENT_ALGORITHM_BITMAP HashAlgorithmBitmap;
    EFI_TCG2_EVENT_LOG_BITMAP SupportedEventLogs;
    EFI_BOOLEAN TPMPresentFlag;
    EFI_UINT16 MaxCommandSize;
    EFI_UINT16 MaxResponseSize;
    EFI_UINT32 ManufacturerID;
    EFI_UINT32 NumberOfPcrBanks;
    EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
} EFI_TCG2_BOOT_SERVICE_CAPABILITY;

#define EFI_TCG2_BOOT_HASH_ALG_SHA1 0x00000001
#define EFI_TCG2_BOOT_HASH_ALG_SHA256 0x00000002
#define EFI_TCG2_BOOT_HASH_ALG_SHA384 0x00000004
#define EFI_TCG2_BOOT_HASH_ALG_SHA512 0x00000008
#define EFI_TCG2_BOOT_HASH_ALG_SM3_256 0x00000010

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_CAPABILITY)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_IN EFI_OUT EFI_TCG2_BOOT_SERVICE_CAPABILITY *ProtocolCapability
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_EVENT_LOG)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_IN EFI_TCG2_EVENT_LOG_FORMAT EventLogFormat,
    EFI_OUT EFI_PHYSICAL_ADDRESS *EventLogLocation,
    EFI_OUT EFI_PHYSICAL_ADDRESS *EventLogLastEntry,
    EFI_OUT EFI_BOOLEAN *EventLogTruncated
);

typedef EFI_UINT32 EFI_TCG_EVENTTYPE;

typedef struct __attribute__((__packed__)) _EFI_TCG2_EVENT_HEADER {
    EFI_UINT32 HeaderSize;
    EFI_UINT16 HeaderVersion;
    EFI_TCG_PCRINDEX PCRIndex;
    EFI_TCG_EVENTTYPE EventType;
} EFI_TCG2_EVENT_HEADER;

/* Event is printed as []; it is variable-length, and Size covers the whole record. */
typedef struct __attribute__((__packed__)) _EFI_TCG2_EVENT {
    EFI_UINT32 Size;
    EFI_TCG2_EVENT_HEADER Header;
    EFI_UINT8 Event[1];
} EFI_TCG2_EVENT;

#define EFI_TCG2_EXTEND_ONLY 0x0000000000000001
#define EFI_PE_COFF_IMAGE 0x0000000000000010

typedef EFI_STATUS (EFI_API *EFI_TCG2_HASH_LOG_EXTEND_EVENT)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_IN EFI_UINT64 Flags,
    EFI_IN EFI_PHYSICAL_ADDRESS DataToHash,
    EFI_IN EFI_UINT64 DataToHashLen,
    EFI_IN EFI_TCG2_EVENT *EfiTcgEvent
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_SUBMIT_COMMAND)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_IN EFI_UINT32 InputParameterBlockSize,
    EFI_IN EFI_UINT8 *InputParameterBlock,
    EFI_IN EFI_UINT32 OutputParameterBlockSize,
    EFI_IN EFI_UINT8 *OutputParameterBlock
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_ACTIVE_PCR_BANKS)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_OUT EFI_UINT32 *ActivePcrBanks
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_SET_ACTIVE_PCR_BANKS)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_IN EFI_UINT32 ActivePcrBanks
);

typedef EFI_STATUS (EFI_API *EFI_TCG2_GET_RESULT_OF_SET_ACTIVE_PCR_BANKS)(
    EFI_IN EFI_TCG2_PROTOCOL *This,
    EFI_OUT EFI_UINT32 *OperationPresent,
    EFI_OUT EFI_UINT32 *Response
);

struct _EFI_TCG2_PROTOCOL {
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
typedef struct _EFI_TCG2_FINAL_EVENTS_TABLE {
    EFI_UINT64 Version;
    EFI_UINT64 NumberOfEvents;
    EFI_UINT8 Event[1];
} EFI_TCG2_FINAL_EVENTS_TABLE;

#define EFI_TCG2_FINAL_EVENTS_TABLE_VERSION 1

#ifdef __cplusplus
}
#endif

#endif
