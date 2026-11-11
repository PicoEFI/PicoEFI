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

typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET_EX)(
    struct efi_simple_text_input_ex_protocol *This,
    bool ExtendedVerification
);

typedef uint8_t EFI_KEY_TOGGLE_STATE;

#define EFI_TOGGLE_STATE_VALID 0x80
#define EFI_KEY_STATE_EXPOSED 0x40
#define EFI_SCROLL_LOCK_ACTIVE 0x01
#define EFI_NUM_LOCK_ACTIVE 0x02
#define EFI_CAPS_LOCK_ACTIVE 0x04

struct efi_key_state {
    uint32_t KeyShiftState;
    EFI_KEY_TOGGLE_STATE KeyToggleState;
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
    struct efi_input_key Key;
    struct efi_key_state KeyState;
};

typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY_EX)(
    struct efi_simple_text_input_ex_protocol *This,
    struct efi_key_data *KeyData
);

typedef EFI_STATUS (EFI_API *EFI_SET_STATE)(
    struct efi_simple_text_input_ex_protocol *This,
    EFI_KEY_TOGGLE_STATE *KeyToggleState
);

typedef EFI_STATUS (EFI_API *EFI_KEY_NOTIFY_FUNCTION)(struct efi_key_data *KeyData);

typedef EFI_STATUS (EFI_API *EFI_REGISTER_KEYSTROKE_NOTIFY)(
    struct efi_simple_text_input_ex_protocol *This,
    struct efi_key_data *KeyData,
    EFI_KEY_NOTIFY_FUNCTION KeyNotificationFunction,
    void **NotifyHandle
);

typedef EFI_STATUS (EFI_API *EFI_UNREGISTER_KEYSTROKE_NOTIFY)(
    struct efi_simple_text_input_ex_protocol *This,
    void *NotificationHandle
);

struct efi_simple_text_input_ex_protocol {
    EFI_INPUT_RESET_EX Reset;
    EFI_INPUT_READ_KEY_EX ReadKeyStrokeEx;
    EFI_EVENT WaitForKeyEx;
    EFI_SET_STATE SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};

#ifdef __cplusplus
}
#endif

#endif
