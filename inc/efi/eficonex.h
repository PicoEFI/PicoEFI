#ifndef EFI_EFICONEX_H_
#define EFI_EFICONEX_H_

#include "eficon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The specification lists these scan codes without names. */
#define EFI_SCAN_PAUSE 0x0048
#define EFI_SCAN_F13 0x0068
#define EFI_SCAN_F14 0x0069
#define EFI_SCAN_F15 0x006A
#define EFI_SCAN_F16 0x006B
#define EFI_SCAN_F17 0x006C
#define EFI_SCAN_F18 0x006D
#define EFI_SCAN_F19 0x006E
#define EFI_SCAN_F20 0x006F
#define EFI_SCAN_F21 0x0070
#define EFI_SCAN_F22 0x0071
#define EFI_SCAN_F23 0x0072
#define EFI_SCAN_F24 0x0073
#define EFI_SCAN_MUTE 0x007F
#define EFI_SCAN_VOLUME_UP 0x0080
#define EFI_SCAN_VOLUME_DOWN 0x0081
#define EFI_SCAN_BRIGHTNESS_UP 0x0100
#define EFI_SCAN_BRIGHTNESS_DOWN 0x0101
#define EFI_SCAN_SUSPEND 0x0102
#define EFI_SCAN_HIBERNATE 0x0103
#define EFI_SCAN_TOGGLE_DISPLAY 0x0104
#define EFI_SCAN_RECOVERY 0x0105
#define EFI_SCAN_EJECT 0x0106

#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
    {0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}}

struct efi_simple_text_input_ex_protocol;

typedef efi_status (EFI_API *efi_input_reset_ex)(
    struct efi_simple_text_input_ex_protocol *self,
    bool extended_verification
);

typedef uint8_t efi_key_toggle_state;

#define EFI_TOGGLE_STATE_VALID 0x80
#define EFI_KEY_STATE_EXPOSED 0x40
#define EFI_SCROLL_LOCK_ACTIVE 0x01
#define EFI_NUM_LOCK_ACTIVE 0x02
#define EFI_CAPS_LOCK_ACTIVE 0x04

struct efi_key_state {
    uint32_t key_shift_state;
    efi_key_toggle_state key_toggle_state;
};

#define EFI_SHIFT_STATE_VALID 0x80000000
#define EFI_RIGHT_SHIFT_PRESSED 0x00000001
#define EFI_LEFT_SHIFT_PRESSED 0x00000002
#define EFI_RIGHT_CONTROL_PRESSED 0x00000004
#define EFI_LEFT_CONTROL_PRESSED 0x00000008
#define EFI_RIGHT_ALT_PRESSED 0x00000010
#define EFI_LEFT_ALT_PRESSED 0x00000020
#define EFI_RIGHT_LOGO_PRESSED 0x00000040
#define EFI_LEFT_LOGO_PRESSED 0x00000080
#define EFI_MENU_KEY_PRESSED 0x00000100
#define EFI_SYS_REQ_PRESSED 0x00000200

struct efi_key_data {
    struct efi_input_key key;
    struct efi_key_state key_state;
};

typedef efi_status (EFI_API *efi_input_read_key_ex)(
    struct efi_simple_text_input_ex_protocol *self,
    struct efi_key_data *key_data
);

typedef efi_status (EFI_API *efi_set_state)(
    struct efi_simple_text_input_ex_protocol *self,
    efi_key_toggle_state *key_toggle_state
);

typedef efi_status (EFI_API *efi_key_notify_function)(struct efi_key_data *key_data);

typedef efi_status (EFI_API *efi_register_keystroke_notify)(
    struct efi_simple_text_input_ex_protocol *self,
    struct efi_key_data *key_data,
    efi_key_notify_function key_notification_function,
    void **notify_handle
);

typedef efi_status (EFI_API *efi_unregister_keystroke_notify)(
    struct efi_simple_text_input_ex_protocol *self,
    void *notification_handle
);

struct efi_simple_text_input_ex_protocol {
    efi_input_reset_ex reset;
    efi_input_read_key_ex read_key_stroke_ex;
    efi_event wait_for_key_ex;
    efi_set_state set_state;
    efi_register_keystroke_notify register_key_notify;
    efi_unregister_keystroke_notify unregister_key_notify;
};

#ifdef __cplusplus
}
#endif

#endif
