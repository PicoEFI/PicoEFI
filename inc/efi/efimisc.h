#ifndef EFI_EFIMISC_H
#define EFI_EFIMISC_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efiapi.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TIMESTAMP_PROTOCOL_GUID \
    {0xafbfde41, 0x2e6e, 0x4262, {0xba, 0x65, 0x62, 0xb9, 0x23, 0x6e, 0x54, 0x95}}

typedef uint64_t (EFI_API *efi_timestamp_get)(void);

struct efi_timestamp_properties {
    uint64_t frequency;
    uint64_t end_value;
};

typedef efi_status (EFI_API *efi_timestamp_get_properties)(
    struct efi_timestamp_properties *properties
);

struct efi_timestamp_protocol {
    efi_timestamp_get get_timestamp;
    efi_timestamp_get_properties get_properties;
};

#define EFI_RESET_NOTIFICATION_PROTOCOL_GUID \
    {0x9da34ae0, 0xeaf9, 0x4bbf, {0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe}}

struct efi_reset_notification_protocol;

// efi_reset_system is itself a pointer: reset_function points to the function,
// as described.
typedef efi_status (EFI_API *efi_register_reset_notify)(
    struct efi_reset_notification_protocol *self,
    efi_reset_system reset_function
);

typedef efi_status (EFI_API *efi_unregister_reset_notify)(
    struct efi_reset_notification_protocol *self,
    efi_reset_system reset_function
);

// The structure prints un_register_reset_notify; the heading and text spell it
// as here.
struct efi_reset_notification_protocol {
    efi_register_reset_notify register_reset_notify;
    efi_unregister_reset_notify unregister_reset_notify;
};

#ifdef __cplusplus
}
#endif

#endif
