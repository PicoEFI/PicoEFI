#ifndef EFI_EFICON_H
#define EFI_EFICON_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
    { 0x387477c1, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

struct efi_simple_text_input_protocol;

struct efi_input_key {
    uint16_t scan_code;
    uint16_t unicode_char;
};

// The specification lists these control characters and scan codes without
// names.
#define EFI_CHAR_NULL 0x0000
#define EFI_CHAR_BACKSPACE 0x0008
#define EFI_CHAR_TAB 0x0009
#define EFI_CHAR_LINEFEED 0x000a
#define EFI_CHAR_CARRIAGE_RETURN 0x000d

#define EFI_SCAN_NULL 0x0000
#define EFI_SCAN_UP 0x0001
#define EFI_SCAN_DOWN 0x0002
#define EFI_SCAN_RIGHT 0x0003
#define EFI_SCAN_LEFT 0x0004
#define EFI_SCAN_HOME 0x0005
#define EFI_SCAN_END 0x0006
#define EFI_SCAN_INSERT 0x0007
#define EFI_SCAN_DELETE 0x0008
#define EFI_SCAN_PAGE_UP 0x0009
#define EFI_SCAN_PAGE_DOWN 0x000a
#define EFI_SCAN_F1 0x000b
#define EFI_SCAN_F2 0x000c
#define EFI_SCAN_F3 0x000d
#define EFI_SCAN_F4 0x000e
#define EFI_SCAN_F5 0x000f
#define EFI_SCAN_F6 0x0010
#define EFI_SCAN_F7 0x0011
#define EFI_SCAN_F8 0x0012
#define EFI_SCAN_F9 0x0013
#define EFI_SCAN_F10 0x0014
#define EFI_SCAN_F11 0x0015
#define EFI_SCAN_F12 0x0016
#define EFI_SCAN_ESC 0x0017

typedef efi_status (EFI_API *efi_input_reset)(
    struct efi_simple_text_input_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_input_read_key)(
    struct efi_simple_text_input_protocol *self,
    struct efi_input_key *key
);

struct efi_simple_text_input_protocol {
    efi_input_reset reset;
    efi_input_read_key read_key_stroke;
    efi_event wait_for_key;
};

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
    { 0x387477c2, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

struct efi_simple_text_output_protocol;

struct efi_simple_text_output_mode {
    int32_t max_mode;
    int32_t mode;
    int32_t attribute;
    int32_t cursor_column;
    int32_t cursor_row;
    uint8_t cursor_visible;
};

typedef efi_status (EFI_API *efi_text_reset)(
    struct efi_simple_text_output_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_text_string)(
    struct efi_simple_text_output_protocol *self,
    uint16_t *string
);

#define EFI_BOXDRAW_HORIZONTAL 0x2500
#define EFI_BOXDRAW_VERTICAL 0x2502
#define EFI_BOXDRAW_DOWN_RIGHT 0x250c
#define EFI_BOXDRAW_DOWN_LEFT 0x2510
#define EFI_BOXDRAW_UP_RIGHT 0x2514
#define EFI_BOXDRAW_UP_LEFT 0x2518
#define EFI_BOXDRAW_VERTICAL_RIGHT 0x251c
#define EFI_BOXDRAW_VERTICAL_LEFT 0x2524
#define EFI_BOXDRAW_DOWN_HORIZONTAL 0x252c
#define EFI_BOXDRAW_UP_HORIZONTAL 0x2534
#define EFI_BOXDRAW_VERTICAL_HORIZONTAL 0x253c

#define EFI_BOXDRAW_DOUBLE_HORIZONTAL 0x2550
#define EFI_BOXDRAW_DOUBLE_VERTICAL 0x2551
#define EFI_BOXDRAW_DOWN_RIGHT_DOUBLE 0x2552
#define EFI_BOXDRAW_DOWN_DOUBLE_RIGHT 0x2553
#define EFI_BOXDRAW_DOUBLE_DOWN_RIGHT 0x2554
#define EFI_BOXDRAW_DOWN_LEFT_DOUBLE 0x2555
#define EFI_BOXDRAW_DOWN_DOUBLE_LEFT 0x2556
#define EFI_BOXDRAW_DOUBLE_DOWN_LEFT 0x2557

#define EFI_BOXDRAW_UP_RIGHT_DOUBLE 0x2558
#define EFI_BOXDRAW_UP_DOUBLE_RIGHT 0x2559
#define EFI_BOXDRAW_DOUBLE_UP_RIGHT 0x255a
#define EFI_BOXDRAW_UP_LEFT_DOUBLE 0x255b
#define EFI_BOXDRAW_UP_DOUBLE_LEFT 0x255c
#define EFI_BOXDRAW_DOUBLE_UP_LEFT 0x255d

#define EFI_BOXDRAW_VERTICAL_RIGHT_DOUBLE 0x255e
#define EFI_BOXDRAW_VERTICAL_DOUBLE_RIGHT 0x255f
#define EFI_BOXDRAW_DOUBLE_VERTICAL_RIGHT 0x2560

#define EFI_BOXDRAW_VERTICAL_LEFT_DOUBLE 0x2561
#define EFI_BOXDRAW_VERTICAL_DOUBLE_LEFT 0x2562
#define EFI_BOXDRAW_DOUBLE_VERTICAL_LEFT 0x2563

#define EFI_BOXDRAW_DOWN_HORIZONTAL_DOUBLE 0x2564
#define EFI_BOXDRAW_DOWN_DOUBLE_HORIZONTAL 0x2565
#define EFI_BOXDRAW_DOUBLE_DOWN_HORIZONTAL 0x2566

#define EFI_BOXDRAW_UP_HORIZONTAL_DOUBLE 0x2567
#define EFI_BOXDRAW_UP_DOUBLE_HORIZONTAL 0x2568
#define EFI_BOXDRAW_DOUBLE_UP_HORIZONTAL 0x2569

#define EFI_BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE 0x256a
#define EFI_BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL 0x256b
#define EFI_BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL 0x256c

#define EFI_BLOCKELEMENT_FULL_BLOCK 0x2588
#define EFI_BLOCKELEMENT_LIGHT_SHADE 0x2591

#define EFI_GEOMETRICSHAPE_UP_TRIANGLE 0x25b2
#define EFI_GEOMETRICSHAPE_RIGHT_TRIANGLE 0x25ba
#define EFI_GEOMETRICSHAPE_DOWN_TRIANGLE 0x25bc
#define EFI_GEOMETRICSHAPE_LEFT_TRIANGLE 0x25c4

#define EFI_ARROW_UP 0x2191
#define EFI_ARROW_DOWN 0x2193

typedef efi_status (EFI_API *efi_text_test_string)(
    struct efi_simple_text_output_protocol *self,
    uint16_t *string
);

typedef efi_status (EFI_API *efi_text_query_mode)(
    struct efi_simple_text_output_protocol *self,
    size_t mode_number,
    size_t *columns,
    size_t *rows
);

typedef efi_status (EFI_API *efi_text_set_mode)(
    struct efi_simple_text_output_protocol *self,
    size_t mode_number
);

typedef efi_status (EFI_API *efi_text_set_attribute)(
    struct efi_simple_text_output_protocol *self,
    uintptr_t attribute
);

#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_MAGENTA 0x05
#define EFI_BROWN 0x06
#define EFI_LIGHTGRAY 0x07
#define EFI_BRIGHT 0x08
#define EFI_DARKGRAY 0x08
#define EFI_LIGHTBLUE 0x09
#define EFI_LIGHTGREEN 0x0a
#define EFI_LIGHTCYAN 0x0b
#define EFI_LIGHTRED 0x0c
#define EFI_LIGHTMAGENTA 0x0d
#define EFI_YELLOW 0x0e
#define EFI_WHITE 0x0f

#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

// Printed commented out (a misprint). background is EFI_BLACK ...
// EFI_LIGHTGRAY.
#define EFI_TEXT_ATTR(foreground, background) ((foreground) | ((background) << 4))

typedef efi_status (EFI_API *efi_text_clear_screen)(struct efi_simple_text_output_protocol *self);

typedef efi_status (EFI_API *efi_text_set_cursor_position)(
    struct efi_simple_text_output_protocol *self,
    size_t column,
    size_t row
);

typedef efi_status (EFI_API *efi_text_enable_cursor)(
    struct efi_simple_text_output_protocol *self,
    bool visible
);

struct efi_simple_text_output_protocol {
    efi_text_reset reset;
    efi_text_string output_string;
    efi_text_test_string test_string;
    efi_text_query_mode query_mode;
    efi_text_set_mode set_mode;
    efi_text_set_attribute set_attribute;
    efi_text_clear_screen clear_screen;
    efi_text_set_cursor_position set_cursor_position;
    efi_text_enable_cursor enable_cursor;
    struct efi_simple_text_output_mode *mode;
};

#ifdef __cplusplus
}
#endif

#endif
