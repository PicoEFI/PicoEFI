#ifndef EFI_EFIPOINT_H
#define EFI_EFIPOINT_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
    {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

struct efi_simple_pointer_protocol;

struct efi_simple_pointer_mode {
    uint64_t resolution_x;
    uint64_t resolution_y;
    uint64_t resolution_z;
    uint8_t left_button;
    uint8_t right_button;
};

typedef efi_status (EFI_API *efi_simple_pointer_reset)(
    struct efi_simple_pointer_protocol *self,
    bool extended_verification
);

struct efi_simple_pointer_state {
    int32_t relative_movement_x;
    int32_t relative_movement_y;
    int32_t relative_movement_z;
    uint8_t left_button;
    uint8_t right_button;
};

typedef efi_status (EFI_API *efi_simple_pointer_get_state)(
    struct efi_simple_pointer_protocol *self,
    struct efi_simple_pointer_state *state
);

// mode is printed with a nonexistent type; its description names struct
// efi_simple_pointer_mode.
struct efi_simple_pointer_protocol {
    efi_simple_pointer_reset reset;
    efi_simple_pointer_get_state get_state;
    efi_event wait_for_input;
    struct efi_simple_pointer_mode *mode;
};

#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
    {0x8D59D32B, 0xC655, 0x4AE9, {0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43}}

struct efi_absolute_pointer_protocol;

struct efi_absolute_pointer_mode {
    uint64_t absolute_min_x;
    uint64_t absolute_min_y;
    uint64_t absolute_min_z;
    uint64_t absolute_max_x;
    uint64_t absolute_max_y;
    uint64_t absolute_max_z;
    uint32_t attributes;
};

#define EFI_ABSP_SUPPORTS_ALT_ACTIVE 0x00000001
#define EFI_ABSP_SUPPORTS_PRESSURE_AS_Z 0x00000002

typedef efi_status (EFI_API *efi_absolute_pointer_reset)(
    struct efi_absolute_pointer_protocol *self,
    bool extended_verification
);

struct efi_absolute_pointer_state {
    uint64_t current_x;
    uint64_t current_y;
    uint64_t current_z;
    uint32_t active_buttons;
};

// EFI_ABS_ALT_ACTIVE (not EFI_ABSP_) is the specification's own, consistent
// spelling.
#define EFI_ABSP_TOUCH_ACTIVE 0x00000001
#define EFI_ABS_ALT_ACTIVE 0x00000002

typedef efi_status (EFI_API *efi_absolute_pointer_get_state)(
    struct efi_absolute_pointer_protocol *self,
    struct efi_absolute_pointer_state *state
);

struct efi_absolute_pointer_protocol {
    efi_absolute_pointer_reset reset;
    efi_absolute_pointer_get_state get_state;
    efi_event wait_for_input;
    struct efi_absolute_pointer_mode *mode;
};

#ifdef __cplusplus
}
#endif

#endif
