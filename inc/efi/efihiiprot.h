#ifndef EFI_EFIHIIPROT_H
#define EFI_EFIHIIPROT_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efihii.h>
#include <efi/efiprot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HII_FONT_PROTOCOL_GUID \
    {0xe9ca4775, 0x8657, 0x47fc, {0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x8, 0x43, 0x24}}

struct efi_hii_font_protocol;

typedef uint32_t efi_hii_out_flags;

#define EFI_HII_OUT_FLAG_CLIP 0x00000001
#define EFI_HII_OUT_FLAG_WRAP 0x00000002
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 0x00000004
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_X 0x00000008
#define EFI_HII_OUT_FLAG_TRANSPARENT 0x00000010
#define EFI_HII_IGNORE_IF_NO_GLYPH 0x00000020
#define EFI_HII_IGNORE_LINE_BREAK 0x00000040
#define EFI_HII_DIRECT_TO_SCREEN 0x00000080

struct efi_hii_row_info {
    size_t start_index;
    size_t end_index;
    size_t line_height;
    size_t line_width;
    size_t baseline_offset;
};

// font_name has one element, as firmware lays it out: struct
// efi_font_display_info embeds this.
struct efi_font_info {
    efi_hii_font_style font_style;
    uint16_t font_size;
    uint16_t font_name[1];
};

typedef uint32_t efi_font_info_mask;

#define EFI_FONT_INFO_SYS_FONT 0x00000001
#define EFI_FONT_INFO_SYS_SIZE 0x00000002
#define EFI_FONT_INFO_SYS_STYLE 0x00000004
#define EFI_FONT_INFO_SYS_FORE_COLOR 0x00000010
#define EFI_FONT_INFO_SYS_BACK_COLOR 0x00000020
#define EFI_FONT_INFO_RESIZE 0x00001000
#define EFI_FONT_INFO_RESTYLE 0x00002000
#define EFI_FONT_INFO_ANY_FONT 0x00010000
#define EFI_FONT_INFO_ANY_SIZE 0x00020000
#define EFI_FONT_INFO_ANY_STYLE 0x00040000

struct efi_font_display_info {
    struct efi_graphics_output_blt_pixel foreground_color;
    struct efi_graphics_output_blt_pixel background_color;
    efi_font_info_mask font_info_mask;
    struct efi_font_info font_info;
};

struct efi_image_output {
    uint16_t width;
    uint16_t height;
    union {
        struct efi_graphics_output_blt_pixel *bitmap;
        struct efi_graphics_output_protocol *screen;
    } image;
};

typedef efi_status (EFI_API *efi_hii_string_to_image)(
    const struct efi_hii_font_protocol *self,
    efi_hii_out_flags flags,
    const efi_string string,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y,
    struct efi_hii_row_info **row_info_array,
    size_t *row_info_array_size,
    size_t *column_info_array
);

typedef efi_status (EFI_API *efi_hii_string_id_to_image)(
    const struct efi_hii_font_protocol *self,
    efi_hii_out_flags flags,
    efi_hii_handle package_list,
    efi_string_id string_id,
    const char *language,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y,
    struct efi_hii_row_info **row_info_array,
    size_t *row_info_array_size,
    size_t *column_info_array
);

typedef efi_status (EFI_API *efi_hii_get_glyph)(
    const struct efi_hii_font_protocol *self,
    uint16_t char_,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t *baseline
);

typedef void *efi_font_handle;

typedef efi_status (EFI_API *efi_hii_get_font_info)(
    const struct efi_hii_font_protocol *self,
    efi_font_handle *font_handle,
    const struct efi_font_display_info *string_info_in,
    struct efi_font_display_info **string_info_out,
    const efi_string string
);

struct efi_hii_font_protocol {
    efi_hii_string_to_image string_to_image;
    efi_hii_string_id_to_image string_id_to_image;
    efi_hii_get_glyph get_glyph;
    efi_hii_get_font_info get_font_info;
};

#define EFI_HII_FONT_EX_PROTOCOL_GUID \
    {0x849e6875, 0xdb35, 0x4df8, {0xb4, 0x1e, 0xc8, 0xf3, 0x37, 0x18, 0x7, 0x3f}}

struct efi_hii_font_ex_protocol;

typedef efi_status (EFI_API *efi_hii_string_to_image_ex)(
    const struct efi_hii_font_ex_protocol *self,
    efi_hii_out_flags flags,
    const efi_string string,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y,
    struct efi_hii_row_info **row_info_array,
    size_t *row_info_array_size,
    size_t *column_info_array
);

typedef efi_status (EFI_API *efi_hii_string_id_to_image_ex)(
    const struct efi_hii_font_ex_protocol *self,
    efi_hii_out_flags flags,
    efi_hii_handle package_list,
    efi_string_id string_id,
    const char *language,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y,
    struct efi_hii_row_info **row_info_array,
    size_t *row_info_array_size,
    size_t *column_info_array
);

// baseline is printed by value, but the parameters are get_glyph()'s, which
// returns it.
typedef efi_status (EFI_API *efi_hii_get_glyph_ex)(
    const struct efi_hii_font_ex_protocol *self,
    uint16_t char_,
    const struct efi_font_display_info *string_info,
    struct efi_image_output **blt,
    size_t *baseline
);

typedef efi_status (EFI_API *efi_hii_get_font_info_ex)(
    const struct efi_hii_font_ex_protocol *self,
    efi_font_handle *font_handle,
    const struct efi_font_display_info *string_info_in,
    struct efi_font_display_info **string_info_out,
    const efi_string string
);

typedef efi_status (EFI_API *efi_hii_get_glyph_info)(
    const struct efi_hii_font_ex_protocol *self,
    uint16_t char_,
    const struct efi_font_display_info *font_display_info,
    struct efi_hii_glyph_info *glyph_info
);

struct efi_hii_font_ex_protocol {
    efi_hii_string_to_image_ex string_to_image_ex;
    efi_hii_string_id_to_image_ex string_id_to_image_ex;
    efi_hii_get_glyph_ex get_glyph_ex;
    efi_hii_get_font_info_ex get_font_info_ex;
    efi_hii_get_glyph_info get_glyph_info;
};

#define EFI_HII_STRING_PROTOCOL_GUID \
    {0xfd96974, 0x23aa, 0x4cdc, {0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}}

struct efi_hii_string_protocol;

typedef efi_status (EFI_API *efi_hii_new_string)(
    const struct efi_hii_string_protocol *self,
    efi_hii_handle package_list,
    efi_string_id *string_id,
    const char *language,
    const uint16_t *language_name,
    const efi_string string,
    const struct efi_font_info *string_font_info
);

typedef efi_status (EFI_API *efi_hii_get_string)(
    const struct efi_hii_string_protocol *self,
    const char *language,
    efi_hii_handle package_list,
    efi_string_id string_id,
    efi_string string,
    size_t *string_size,
    struct efi_font_info **string_font_info
);

typedef efi_status (EFI_API *efi_hii_set_string)(
    const struct efi_hii_string_protocol *self,
    efi_hii_handle package_list,
    efi_string_id string_id,
    const char *language,
    const efi_string string,
    const struct efi_font_info *string_font_info
);

typedef efi_status (EFI_API *efi_hii_get_languages)(
    const struct efi_hii_string_protocol *self,
    efi_hii_handle package_list,
    char *languages,
    size_t *languages_size
);

typedef efi_status (EFI_API *efi_hii_get_2nd_languages)(
    const struct efi_hii_string_protocol *self,
    efi_hii_handle package_list,
    const char *primary_language,
    char *secondary_languages,
    size_t *secondary_languages_size
);

struct efi_hii_string_protocol {
    efi_hii_new_string new_string;
    efi_hii_get_string get_string;
    efi_hii_set_string set_string;
    efi_hii_get_languages get_languages;
    efi_hii_get_2nd_languages get_secondary_languages;
};

#define EFI_HII_IMAGE_PROTOCOL_GUID \
    {0x31a6406a, 0x6bdf, 0x4e46, {0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x9, 0x20}}

struct efi_hii_image_protocol;

struct efi_image_input {
    uint32_t flags;
    uint16_t width;
    uint16_t height;
    struct efi_graphics_output_blt_pixel *bitmap;
};

#define EFI_IMAGE_TRANSPARENT 0x00000001

typedef efi_status (EFI_API *efi_hii_new_image)(
    const struct efi_hii_image_protocol *self,
    efi_hii_handle package_list,
    efi_image_id *image_id,
    const struct efi_image_input *image
);

typedef efi_status (EFI_API *efi_hii_get_image)(
    const struct efi_hii_image_protocol *self,
    efi_hii_handle package_list,
    efi_image_id image_id,
    struct efi_image_input *image
);

typedef efi_status (EFI_API *efi_hii_set_image)(
    const struct efi_hii_image_protocol *self,
    efi_hii_handle package_list,
    efi_image_id image_id,
    const struct efi_image_input *image
);

typedef uint32_t efi_hii_draw_flags;

#define EFI_HII_DRAW_FLAG_CLIP 0x00000001
#define EFI_HII_DRAW_FLAG_TRANSPARENT 0x00000030
#define EFI_HII_DRAW_FLAG_DEFAULT 0x00000000
#define EFI_HII_DRAW_FLAG_FORCE_TRANS 0x00000010
#define EFI_HII_DRAW_FLAG_FORCE_OPAQUE 0x00000020

typedef efi_status (EFI_API *efi_hii_draw_image)(
    const struct efi_hii_image_protocol *self,
    efi_hii_draw_flags flags,
    const struct efi_image_input *image,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y
);

typedef efi_status (EFI_API *efi_hii_draw_image_id)(
    const struct efi_hii_image_protocol *self,
    efi_hii_draw_flags flags,
    efi_hii_handle package_list,
    efi_image_id image_id,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y
);

struct efi_hii_image_protocol {
    efi_hii_new_image new_image;
    efi_hii_get_image get_image;
    efi_hii_set_image set_image;
    efi_hii_draw_image draw_image;
    efi_hii_draw_image_id draw_image_id;
};

#define EFI_HII_IMAGE_EX_PROTOCOL_GUID \
    {0x1a1241e6, 0x8f19, 0x41a9, {0xbc, 0xe, 0xe8, 0xef, 0x39, 0xe0, 0x65, 0x46}}

struct efi_hii_image_ex_protocol;

typedef efi_status (EFI_API *efi_hii_new_image_ex)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_handle package_list,
    efi_image_id *image_id,
    struct efi_image_input *image
);

typedef efi_status (EFI_API *efi_hii_get_image_ex)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_handle package_list,
    efi_image_id image_id,
    struct efi_image_input *image
);

typedef efi_status (EFI_API *efi_hii_set_image_ex)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_handle package_list,
    efi_image_id image_id,
    const struct efi_image_input *image
);

typedef efi_status (EFI_API *efi_hii_draw_image_ex)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_draw_flags flags,
    const struct efi_image_input *image,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y
);

typedef efi_status (EFI_API *efi_hii_draw_image_id_ex)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_draw_flags flags,
    efi_hii_handle package_list,
    efi_image_id image_id,
    struct efi_image_output **blt,
    size_t blt_x,
    size_t blt_y
);

typedef efi_status (EFI_API *efi_hii_get_image_info)(
    const struct efi_hii_image_ex_protocol *self,
    efi_hii_handle package_list,
    efi_image_id image_id,
    struct efi_image_output *image
);

struct efi_hii_image_ex_protocol {
    efi_hii_new_image_ex new_image_ex;
    efi_hii_get_image_ex get_image_ex;
    efi_hii_set_image_ex set_image_ex;
    efi_hii_draw_image_ex draw_image_ex;
    efi_hii_draw_image_id_ex draw_image_id_ex;
    efi_hii_get_image_info get_image_info;
};

#define EFI_HII_IMAGE_DECODER_PROTOCOL_GUID \
    {0x9e66f251, 0x727c, 0x418c, {0xbf, 0xd6, 0xc2, 0xb4, 0x25, 0x28, 0x18, 0xea}}

struct efi_hii_image_decoder_protocol;

typedef efi_status (EFI_API *efi_hii_image_decoder_get_name)(
    const struct efi_hii_image_decoder_protocol *self,
    struct efi_guid **decoder_name,
    uint16_t *number_of_decoder_name
);

#define EFI_HII_IMAGE_DECODER_NAME_JPEG_GUID \
    {0xefefd093, 0xd9b, 0x46eb, {0xa8, 0x56, 0x48, 0x35, 0x7, 0x0, 0xc9, 0x8}}

#define EFI_HII_IMAGE_DECODER_NAME_PNG_GUID \
    {0xaf060190, 0x5e3a, 0x4025, {0xaf, 0xbd, 0xe1, 0xf9, 0x5, 0xbf, 0xaa, 0x4c}}

#define EFI_HII_IMAGE_DECODER_COLOR_TYPE_RGB ((uint32_t)0)
#define EFI_HII_IMAGE_DECODER_COLOR_TYPE_RGBA ((uint32_t)1)
#define EFI_HII_IMAGE_DECODER_COLOR_TYPE_CMYK ((uint32_t)2)
#define EFI_HII_IMAGE_DECODER_COLOR_TYPE_UNKNOWN ((uint32_t)0xff)

struct efi_hii_image_decoder_image_info_header {
    struct efi_guid decoder_name;
    uint16_t image_info_size;
    uint16_t image_width;
    uint16_t image_height;
    uint32_t color_type;
    uint8_t color_depth_in_bits;
};

struct efi_hii_image_decoder_jpeg_info {
    struct efi_hii_image_decoder_image_info_header header;
    uint16_t scan_type;
    uint64_t reserved;
};

#define EFI_IMAGE_JPEG_SCANTYPE_PROGREESSIVE 0x01
#define EFI_IMAGE_JPEG_SCANTYPE_INTERLACED 0x02

struct efi_hii_image_decoder_png_info {
    struct efi_hii_image_decoder_image_info_header header;
    uint16_t channels;
    uint64_t reserved;
};

struct efi_hii_image_decoder_other_info {
    struct efi_hii_image_decoder_image_info_header header;
    uint16_t image_extenion[1];
};

// image_info is printed as EFI_HII_IMAGE_DECODER_IMAGE_INFO, which is defined
// nowhere; every image information structure starts with struct
// efi_hii_image_decoder_image_info_header.
typedef efi_status (EFI_API *efi_hii_image_decoder_get_image_info)(
    const struct efi_hii_image_decoder_protocol *self,
    void *image,
    size_t size_of_image,
    struct efi_hii_image_decoder_image_info_header **image_info
);

typedef efi_status (EFI_API *efi_hii_image_decoder_decode)(
    const struct efi_hii_image_decoder_protocol *self,
    void *image,
    size_t image_raw_data_size,
    struct efi_image_output **bitmap,
    bool transparent
);

struct efi_hii_image_decoder_protocol {
    efi_hii_image_decoder_get_name get_image_decoder_name;
    efi_hii_image_decoder_get_image_info get_image_info;
    efi_hii_image_decoder_decode decode_image;
};

#define EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL_GUID \
    {0xf7102853, 0x7787, 0x4dc2, {0xa8, 0xa8, 0x21, 0xb5, 0xdd, 0x5, 0xc8, 0x9b}}

struct efi_hii_font_glyph_generator_protocol;

typedef efi_status (EFI_API *efi_hii_generate_glyph)(
    const struct efi_hii_font_glyph_generator_protocol *self,
    uint16_t char_,
    const struct efi_font_display_info *font_info,
    struct efi_hii_gibt_variability_block *glyph_block
);

typedef efi_status (EFI_API *efi_hii_generate_glyph_image)(
    const struct efi_hii_font_glyph_generator_protocol *self,
    const struct efi_hii_glyph_info *cell,
    uint8_t *glyph_buffer,
    const struct efi_font_display_info *font_info,
    struct efi_image_output *image,
    int32_t *blt_x,
    int32_t *blt_y,
    bool transparent
);

// The member types are printed EFI_GENERATE_GLYPH and EFI_GENERATE_IMAGE,
// defined nowhere.
struct efi_hii_font_glyph_generator_protocol {
    efi_hii_generate_glyph generate_glyph;
    efi_hii_generate_glyph_image generate_glyph_image;
};

#define EFI_HII_DATABASE_PROTOCOL_GUID \
    {0xef9fc172, 0xa1b2, 0x4693, {0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}}

struct efi_hii_database_protocol;

typedef efi_status (EFI_API *efi_hii_database_new_pack)(
    const struct efi_hii_database_protocol *self,
    const struct efi_hii_package_list_header *package_list,
    const efi_handle driver_handle,
    efi_hii_handle *handle
);

typedef efi_status (EFI_API *efi_hii_database_remove_pack)(
    const struct efi_hii_database_protocol *self,
    efi_hii_handle handle
);

typedef efi_status (EFI_API *efi_hii_database_update_pack)(
    const struct efi_hii_database_protocol *self,
    efi_hii_handle handle,
    const struct efi_hii_package_list_header *package_list
);

typedef efi_status (EFI_API *efi_hii_database_list_packs)(
    const struct efi_hii_database_protocol *self,
    uint8_t package_type,
    const struct efi_guid *package_guid,
    size_t *handle_buffer_length,
    efi_hii_handle *handle
);

typedef efi_status (EFI_API *efi_hii_database_export_packs)(
    const struct efi_hii_database_protocol *self,
    efi_hii_handle handle,
    size_t *buffer_size,
    struct efi_hii_package_list_header *buffer
);

typedef uintptr_t efi_hii_database_notify_type;

#define EFI_HII_DATABASE_NOTIFY_NEW_PACK 0x00000001
#define EFI_HII_DATABASE_NOTIFY_REMOVE_PACK 0x00000002
#define EFI_HII_DATABASE_NOTIFY_EXPORT_PACK 0x00000004
#define EFI_HII_DATABASE_NOTIFY_ADD_PACK 0x00000008

typedef efi_status (EFI_API *efi_hii_database_notify)(
    uint8_t package_type,
    const struct efi_guid *package_guid,
    const struct efi_hii_package_header *package,
    efi_hii_handle handle,
    efi_hii_database_notify_type notify_type
);

typedef efi_status (EFI_API *efi_hii_database_register_notify)(
    const struct efi_hii_database_protocol *self,
    uint8_t package_type,
    const struct efi_guid *package_guid,
    const efi_hii_database_notify package_notify_fn,
    efi_hii_database_notify_type notify_type,
    efi_handle *notify_handle
);

typedef efi_status (EFI_API *efi_hii_database_unregister_notify)(
    const struct efi_hii_database_protocol *self,
    efi_handle notification_handle
);

typedef efi_status (EFI_API *efi_hii_find_keyboard_layouts)(
    const struct efi_hii_database_protocol *self,
    uint16_t *key_guid_buffer_length,
    struct efi_guid *key_guid_buffer
);

#define EFI_KEY_LCTRL ((uint32_t)0)
#define EFI_KEY_A0 ((uint32_t)1)
#define EFI_KEY_LALT ((uint32_t)2)
#define EFI_KEY_SPACE_BAR ((uint32_t)3)
#define EFI_KEY_A2 ((uint32_t)4)
#define EFI_KEY_A3 ((uint32_t)5)
#define EFI_KEY_A4 ((uint32_t)6)
#define EFI_KEY_RCTRL ((uint32_t)7)
#define EFI_KEY_LEFT_ARROW ((uint32_t)8)
#define EFI_KEY_DOWN_ARROW ((uint32_t)9)
#define EFI_KEY_RIGHT_ARROW ((uint32_t)10)
#define EFI_KEY_ZERO ((uint32_t)11)
#define EFI_KEY_PERIOD ((uint32_t)12)
#define EFI_KEY_ENTER ((uint32_t)13)
#define EFI_KEY_LSHIFT ((uint32_t)14)
#define EFI_KEY_B0 ((uint32_t)15)
#define EFI_KEY_B1 ((uint32_t)16)
#define EFI_KEY_B2 ((uint32_t)17)
#define EFI_KEY_B3 ((uint32_t)18)
#define EFI_KEY_B4 ((uint32_t)19)
#define EFI_KEY_B5 ((uint32_t)20)
#define EFI_KEY_B6 ((uint32_t)21)
#define EFI_KEY_B7 ((uint32_t)22)
#define EFI_KEY_B8 ((uint32_t)23)
#define EFI_KEY_B9 ((uint32_t)24)
#define EFI_KEY_B10 ((uint32_t)25)
#define EFI_KEY_RSHIFT ((uint32_t)26)
#define EFI_KEY_UP_ARROW ((uint32_t)27)
#define EFI_KEY_ONE ((uint32_t)28)
#define EFI_KEY_TWO ((uint32_t)29)
#define EFI_KEY_THREE ((uint32_t)30)
#define EFI_KEY_CAPS_LOCK ((uint32_t)31)
#define EFI_KEY_C1 ((uint32_t)32)
#define EFI_KEY_C2 ((uint32_t)33)
#define EFI_KEY_C3 ((uint32_t)34)
#define EFI_KEY_C4 ((uint32_t)35)
#define EFI_KEY_C5 ((uint32_t)36)
#define EFI_KEY_C6 ((uint32_t)37)
#define EFI_KEY_C7 ((uint32_t)38)
#define EFI_KEY_C8 ((uint32_t)39)
#define EFI_KEY_C9 ((uint32_t)40)
#define EFI_KEY_C10 ((uint32_t)41)
#define EFI_KEY_C11 ((uint32_t)42)
#define EFI_KEY_C12 ((uint32_t)43)
#define EFI_KEY_FOUR ((uint32_t)44)
#define EFI_KEY_FIVE ((uint32_t)45)
#define EFI_KEY_SIX ((uint32_t)46)
#define EFI_KEY_PLUS ((uint32_t)47)
#define EFI_KEY_TAB ((uint32_t)48)
#define EFI_KEY_D1 ((uint32_t)49)
#define EFI_KEY_D2 ((uint32_t)50)
#define EFI_KEY_D3 ((uint32_t)51)
#define EFI_KEY_D4 ((uint32_t)52)
#define EFI_KEY_D5 ((uint32_t)53)
#define EFI_KEY_D6 ((uint32_t)54)
#define EFI_KEY_D7 ((uint32_t)55)
#define EFI_KEY_D8 ((uint32_t)56)
#define EFI_KEY_D9 ((uint32_t)57)
#define EFI_KEY_D10 ((uint32_t)58)
#define EFI_KEY_D11 ((uint32_t)59)
#define EFI_KEY_D12 ((uint32_t)60)
#define EFI_KEY_D13 ((uint32_t)61)
#define EFI_KEY_DEL ((uint32_t)62)
#define EFI_KEY_END ((uint32_t)63)
#define EFI_KEY_PG_DN ((uint32_t)64)
#define EFI_KEY_SEVEN ((uint32_t)65)
#define EFI_KEY_EIGHT ((uint32_t)66)
#define EFI_KEY_NINE ((uint32_t)67)
#define EFI_KEY_E0 ((uint32_t)68)
#define EFI_KEY_E1 ((uint32_t)69)
#define EFI_KEY_E2 ((uint32_t)70)
#define EFI_KEY_E3 ((uint32_t)71)
#define EFI_KEY_E4 ((uint32_t)72)
#define EFI_KEY_E5 ((uint32_t)73)
#define EFI_KEY_E6 ((uint32_t)74)
#define EFI_KEY_E7 ((uint32_t)75)
#define EFI_KEY_E8 ((uint32_t)76)
#define EFI_KEY_E9 ((uint32_t)77)
#define EFI_KEY_E10 ((uint32_t)78)
#define EFI_KEY_E11 ((uint32_t)79)
#define EFI_KEY_E12 ((uint32_t)80)
#define EFI_KEY_BACK_SPACE ((uint32_t)81)
#define EFI_KEY_INS ((uint32_t)82)
#define EFI_KEY_HOME ((uint32_t)83)
#define EFI_KEY_PG_UP ((uint32_t)84)
#define EFI_KEY_NLCK ((uint32_t)85)
#define EFI_KEY_SLASH ((uint32_t)86)
#define EFI_KEY_ASTERISK ((uint32_t)87)
#define EFI_KEY_MINUS ((uint32_t)88)
#define EFI_KEY_ESC ((uint32_t)89)
#define EFI_KEY_F1 ((uint32_t)90)
#define EFI_KEY_F2 ((uint32_t)91)
#define EFI_KEY_F3 ((uint32_t)92)
#define EFI_KEY_F4 ((uint32_t)93)
#define EFI_KEY_F5 ((uint32_t)94)
#define EFI_KEY_F6 ((uint32_t)95)
#define EFI_KEY_F7 ((uint32_t)96)
#define EFI_KEY_F8 ((uint32_t)97)
#define EFI_KEY_F9 ((uint32_t)98)
#define EFI_KEY_F10 ((uint32_t)99)
#define EFI_KEY_F11 ((uint32_t)100)
#define EFI_KEY_F12 ((uint32_t)101)
#define EFI_KEY_PRINT ((uint32_t)102)
#define EFI_KEY_SLCK ((uint32_t)103)
#define EFI_KEY_PAUSE ((uint32_t)104)
#define EFI_KEY_INTL0 ((uint32_t)105)
#define EFI_KEY_INTL1 ((uint32_t)106)
#define EFI_KEY_INTL2 ((uint32_t)107)
#define EFI_KEY_INTL3 ((uint32_t)108)
#define EFI_KEY_INTL4 ((uint32_t)109)
#define EFI_KEY_INTL5 ((uint32_t)110)
#define EFI_KEY_INTL6 ((uint32_t)111)
#define EFI_KEY_INTL7 ((uint32_t)112)
#define EFI_KEY_INTL8 ((uint32_t)113)
#define EFI_KEY_INTL9 ((uint32_t)114)

struct efi_key_descriptor {
    uint32_t key;
    uint16_t unicode;
    uint16_t shifted_unicode;
    uint16_t alt_gr_unicode;
    uint16_t shifted_alt_gr_unicode;
    uint16_t modifier;
    uint16_t affected_attribute;
} __attribute__((__packed__));

#define EFI_AFFECTED_BY_STANDARD_SHIFT 0x0001
#define EFI_AFFECTED_BY_CAPS_LOCK 0x0002
#define EFI_AFFECTED_BY_NUM_LOCK 0x0004

// __extension__: a flexible array member is standard C but an extension in
// C++.
__extension__ struct efi_hii_keyboard_layout {
    uint16_t layout_length;
    struct efi_guid guid;
    uint32_t layout_descriptor_string_offset;
    uint8_t descriptor_count;
    struct efi_key_descriptor descriptors[];
} __attribute__((__packed__));

// The fixed part: each EFI_DESCRIPTION_STRING that follows starts with a
// variable-length array.
struct efi_description_string_bundle {
    uint16_t description_count;
} __attribute__((__packed__));

#define EFI_NULL_MODIFIER 0x0000
#define EFI_LEFT_CONTROL_MODIFIER 0x0001
#define EFI_RIGHT_CONTROL_MODIFIER 0x0002
#define EFI_LEFT_ALT_MODIFIER 0x0003
#define EFI_RIGHT_ALT_MODIFIER 0x0004
#define EFI_ALT_GR_MODIFIER 0x0005
#define EFI_INSERT_MODIFIER 0x0006
#define EFI_DELETE_MODIFIER 0x0007
#define EFI_PAGE_DOWN_MODIFIER 0x0008
#define EFI_PAGE_UP_MODIFIER 0x0009
#define EFI_HOME_MODIFIER 0x000a
#define EFI_END_MODIFIER 0x000b
#define EFI_LEFT_SHIFT_MODIFIER 0x000c
#define EFI_RIGHT_SHIFT_MODIFIER 0x000d
#define EFI_CAPS_LOCK_MODIFIER 0x000e
#define EFI_NUM_LOCK_MODIFIER 0x000f
#define EFI_LEFT_ARROW_MODIFIER 0x0010
#define EFI_RIGHT_ARROW_MODIFIER 0x0011
#define EFI_DOWN_ARROW_MODIFIER 0x0012
#define EFI_UP_ARROW_MODIFIER 0x0013
#define EFI_NS_KEY_MODIFIER 0x0014
#define EFI_NS_KEY_DEPENDENCY_MODIFIER 0x0015
#define EFI_FUNCTION_KEY_ONE_MODIFIER 0x0016
#define EFI_FUNCTION_KEY_TWO_MODIFIER 0x0017
#define EFI_FUNCTION_KEY_THREE_MODIFIER 0x0018
#define EFI_FUNCTION_KEY_FOUR_MODIFIER 0x0019
#define EFI_FUNCTION_KEY_FIVE_MODIFIER 0x001a
#define EFI_FUNCTION_KEY_SIX_MODIFIER 0x001b
#define EFI_FUNCTION_KEY_SEVEN_MODIFIER 0x001c
#define EFI_FUNCTION_KEY_EIGHT_MODIFIER 0x001d
#define EFI_FUNCTION_KEY_NINE_MODIFIER 0x001e
#define EFI_FUNCTION_KEY_TEN_MODIFIER 0x001f
#define EFI_FUNCTION_KEY_ELEVEN_MODIFIER 0x0020
#define EFI_FUNCTION_KEY_TWELVE_MODIFIER 0x0021
#define EFI_PRINT_MODIFIER 0x0022
#define EFI_SYS_REQUEST_MODIFIER 0x0023
#define EFI_SCROLL_LOCK_MODIFIER 0x0024
#define EFI_PAUSE_MODIFIER 0x0025
#define EFI_BREAK_MODIFIER 0x0026
#define EFI_LEFT_LOGO_MODIFIER 0x0027
#define EFI_RIGHT_LOGO_MODIFIER 0x0028
#define EFI_MENU_MODIFIER 0x0029

typedef efi_status (EFI_API *efi_hii_get_keyboard_layout)(
    const struct efi_hii_database_protocol *self,
    struct efi_guid *key_guid,
    uint16_t *keyboard_layout_length,
    struct efi_hii_keyboard_layout *keyboard_layout
);

typedef efi_status (EFI_API *efi_hii_set_keyboard_layout)(
    const struct efi_hii_database_protocol *self,
    struct efi_guid *key_guid
);

#define EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID \
    {0x14982a4f, 0xb0ed, 0x45b8, {0xa8, 0x11, 0x5a, 0x7a, 0x9b, 0xc2, 0x32, 0xdf}}

typedef efi_status (EFI_API *efi_hii_database_get_pack_handle)(
    const struct efi_hii_database_protocol *self,
    efi_hii_handle package_list_handle,
    efi_handle *driver_handle
);

struct efi_hii_database_protocol {
    efi_hii_database_new_pack new_package_list;
    efi_hii_database_remove_pack remove_package_list;
    efi_hii_database_update_pack update_package_list;
    efi_hii_database_list_packs list_package_lists;
    efi_hii_database_export_packs export_package_lists;
    efi_hii_database_register_notify register_package_notify;
    efi_hii_database_unregister_notify unregister_package_notify;
    efi_hii_find_keyboard_layouts find_keyboard_layouts;
    efi_hii_get_keyboard_layout get_keyboard_layout;
    efi_hii_set_keyboard_layout set_keyboard_layout;
    efi_hii_database_get_pack_handle get_package_list_handle;
};

#ifdef __cplusplus
}
#endif

#endif
