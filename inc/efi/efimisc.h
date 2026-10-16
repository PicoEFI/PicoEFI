#ifndef EFI_EFIMISC_H_
#define EFI_EFIMISC_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TIMESTAMP_PROTOCOL_GUID \
    {0xafbfde41, 0x2e6e, 0x4262, {0xba, 0x65, 0x62, 0xb9, 0x23, 0x6e, 0x54, 0x95}}

typedef EFI_UINT64 (EFI_API *EFI_TIMESTAMP_GET)(void);

typedef struct {
    EFI_UINT64 Frequency;
    EFI_UINT64 EndValue;
} EFI_TIMESTAMP_PROPERTIES;

typedef EFI_STATUS (EFI_API *EFI_TIMESTAMP_GET_PROPERTIES)(
    EFI_OUT EFI_TIMESTAMP_PROPERTIES *Properties
);

typedef struct _EFI_TIMESTAMP_PROTOCOL {
    EFI_TIMESTAMP_GET GetTimestamp;
    EFI_TIMESTAMP_GET_PROPERTIES GetProperties;
} EFI_TIMESTAMP_PROTOCOL;

#define EFI_RESET_NOTIFICATION_PROTOCOL_GUID \
    {0x9da34ae0, 0xeaf9, 0x4bbf, {0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe}}

typedef struct _EFI_RESET_NOTIFICATION_PROTOCOL EFI_RESET_NOTIFICATION_PROTOCOL;

/* EFI_RESET_SYSTEM is itself a pointer: ResetFunction points to the function, as described. */
typedef EFI_STATUS (EFI_API *EFI_REGISTER_RESET_NOTIFY)(
    EFI_IN EFI_RESET_NOTIFICATION_PROTOCOL *This,
    EFI_IN EFI_RESET_SYSTEM ResetFunction
);

typedef EFI_STATUS (EFI_API *EFI_UNREGISTER_RESET_NOTIFY)(
    EFI_IN EFI_RESET_NOTIFICATION_PROTOCOL *This,
    EFI_IN EFI_RESET_SYSTEM ResetFunction
);

/* The structure prints UnRegisterResetNotify; the heading and text spell it as here. */
struct _EFI_RESET_NOTIFICATION_PROTOCOL {
    EFI_REGISTER_RESET_NOTIFY RegisterResetNotify;
    EFI_UNREGISTER_RESET_NOTIFY UnregisterResetNotify;
};

#ifdef __cplusplus
}
#endif

#endif
