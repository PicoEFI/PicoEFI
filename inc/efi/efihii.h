#ifndef EFI_EFIHII_H_
#define EFI_EFIHII_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *EFI_HII_HANDLE;

typedef uint16_t *EFI_STRING;

typedef uint16_t EFI_QUESTION_ID;
typedef uint16_t EFI_IMAGE_ID;
typedef uint16_t EFI_STRING_ID;
typedef uint16_t EFI_FORM_ID;
typedef uint16_t EFI_VARSTORE_ID;
typedef uint16_t EFI_ANIMATION_ID;
typedef uint16_t EFI_DEFAULT_ID;

#define EFI_HII_DEFAULT_CLASS_STANDARD 0x0000
#define EFI_HII_DEFAULT_CLASS_MANUFACTURING 0x0001
#define EFI_HII_DEFAULT_CLASS_SAFE 0x0002
#define EFI_HII_DEFAULT_CLASS_PLATFORM_BEGIN 0x4000
#define EFI_HII_DEFAULT_CLASS_PLATFORM_END 0x7fff
#define EFI_HII_DEFAULT_CLASS_HARDWARE_BEGIN 0x8000
#define EFI_HII_DEFAULT_CLASS_HARDWARE_END 0xbfff
#define EFI_HII_DEFAULT_CLASS_FIRMWARE_BEGIN 0xc000
#define EFI_HII_DEFAULT_CLASS_FIRMWARE_END 0xffff

/* The package data (Data[]) follows: each package's own header starts with this one. */
struct efi_hii_package_header {
    uint32_t Length:24;
    uint32_t Type:8;
} __attribute__((__packed__));

#define EFI_HII_PACKAGE_TYPE_ALL 0x00
#define EFI_HII_PACKAGE_TYPE_GUID 0x01
#define EFI_HII_PACKAGE_FORMS 0x02
#define EFI_HII_PACKAGE_STRINGS 0x04
#define EFI_HII_PACKAGE_FONTS 0x05
#define EFI_HII_PACKAGE_IMAGES 0x06
#define EFI_HII_PACKAGE_SIMPLE_FONTS 0x07
#define EFI_HII_PACKAGE_DEVICE_PATH 0x08
#define EFI_HII_PACKAGE_KEYBOARD_LAYOUT 0x09
#define EFI_HII_PACKAGE_ANIMATIONS 0x0A
#define EFI_HII_PACKAGE_END 0xDF
#define EFI_HII_PACKAGE_TYPE_SYSTEM_BEGIN 0xE0
#define EFI_HII_PACKAGE_TYPE_SYSTEM_END 0xFF

struct efi_hii_package_list_header {
    struct efi_guid PackageListGuid;
    uint32_t PackageLength;
} __attribute__((__packed__));

typedef struct efi_hii_package_list_header *EFI_HII_PACKAGE_LIST_PROTOCOL;

#define EFI_GLYPH_NON_SPACING 0x01
#define EFI_GLYPH_WIDE 0x02
#define EFI_GLYPH_HEIGHT 19
#define EFI_GLYPH_WIDTH 8

struct efi_narrow_glyph {
    uint16_t UnicodeWeight;
    uint8_t Attributes;
    uint8_t GlyphCol1[EFI_GLYPH_HEIGHT];
} __attribute__((__packed__));

struct efi_wide_glyph {
    uint16_t UnicodeWeight;
    uint8_t Attributes;
    uint8_t GlyphCol1[EFI_GLYPH_HEIGHT];
    uint8_t GlyphCol2[EFI_GLYPH_HEIGHT];
    uint8_t Pad[3];
} __attribute__((__packed__));

/*
 * __extension__ on structures ending in a flexible array member: standard C, an extension in C++.
 * The struct efi_wide_glyph WideGlyphs[] follow the narrow glyphs.
 */
__extension__ struct efi_hii_simple_font_package_hdr {
    struct efi_hii_package_header Header;
    uint16_t NumberOfNarrowGlyphs;
    uint16_t NumberOfWideGlyphs;
    struct efi_narrow_glyph NarrowGlyphs[];
} __attribute__((__packed__));

typedef uint32_t EFI_HII_FONT_STYLE;

#define EFI_HII_FONT_STYLE_NORMAL 0x00000000
#define EFI_HII_FONT_STYLE_BOLD 0x00000001
#define EFI_HII_FONT_STYLE_ITALIC 0x00000002
#define EFI_HII_FONT_STYLE_EMBOSS 0x00010000
#define EFI_HII_FONT_STYLE_OUTLINE 0x00020000
#define EFI_HII_FONT_STYLE_SHADOW 0x00040000
#define EFI_HII_FONT_STYLE_UNDERLINE 0x00080000
#define EFI_HII_FONT_STYLE_DBL_UNDER 0x00100000

struct efi_hii_glyph_info {
    uint16_t Width;
    uint16_t Height;
    int16_t OffsetX;
    int16_t OffsetY;
    int16_t AdvanceX;
} __attribute__((__packed__));

__extension__ struct efi_hii_font_package_hdr {
    struct efi_hii_package_header Header;
    uint32_t HdrSize;
    uint32_t GlyphBlockOffset;
    struct efi_hii_glyph_info Cell;
    EFI_HII_FONT_STYLE FontStyle;
    uint16_t FontFamily[];
} __attribute__((__packed__));

/* The block body (BlockBody[]) follows: each glyph block starts with this header. */
struct efi_hii_glyph_block {
    uint8_t BlockType;
} __attribute__((__packed__));

#define EFI_HII_GIBT_END 0x00
#define EFI_HII_GIBT_GLYPH 0x10
#define EFI_HII_GIBT_GLYPHS 0x11
#define EFI_HII_GIBT_GLYPH_DEFAULT 0x12
#define EFI_HII_GIBT_GLYPHS_DEFAULT 0x13
#define EFI_HII_GIBT_GLYPH_VARIABILITY 0x14
#define EFI_HII_GIBT_DUPLICATE 0x20
#define EFI_HII_GIBT_SKIP2 0x21
#define EFI_HII_GIBT_SKIP1 0x22
#define EFI_HII_GIBT_DEFAULTS 0x23
#define EFI_HII_GIBT_EXT1 0x30
#define EFI_HII_GIBT_EXT2 0x31
#define EFI_HII_GIBT_EXT4 0x32

struct efi_hii_gibt_defaults_block {
    struct efi_hii_glyph_block Header;
    struct efi_hii_glyph_info Cell;
} __attribute__((__packed__));

struct efi_hii_gibt_duplicate_block {
    struct efi_hii_glyph_block Header;
    uint16_t CharValue;
} __attribute__((__packed__));

struct efi_glyph_gibt_end_block {
    struct efi_hii_glyph_block Header;
} __attribute__((__packed__));

struct efi_hii_gibt_ext1_block {
    struct efi_hii_glyph_block Header;
    uint8_t BlockType2;
    uint8_t Length;
} __attribute__((__packed__));

struct efi_hii_gibt_ext2_block {
    struct efi_hii_glyph_block Header;
    uint8_t BlockType2;
    uint16_t Length;
} __attribute__((__packed__));

struct efi_hii_gibt_ext4_block {
    struct efi_hii_glyph_block Header;
    uint8_t BlockType2;
    uint32_t Length;
} __attribute__((__packed__));

struct efi_hii_gibt_glyph_block {
    struct efi_hii_glyph_block Header;
    struct efi_hii_glyph_info Cell;
    uint8_t BitmapData[1];
} __attribute__((__packed__));

struct efi_hii_gibt_glyphs_block {
    struct efi_hii_glyph_block Header;
    struct efi_hii_glyph_info Cell;
    uint16_t Count;
    uint8_t BitmapData[1];
} __attribute__((__packed__));

__extension__ struct efi_hii_gibt_glyph_default_block {
    struct efi_hii_glyph_block Header;
    uint8_t BitmapData[];
} __attribute__((__packed__));

__extension__ struct efi_hii_gibt_glyphs_default_block {
    struct efi_hii_glyph_block Header;
    uint16_t Count;
    uint8_t BitmapData[];
} __attribute__((__packed__));

struct efi_hii_gibt_skip2_block {
    struct efi_hii_glyph_block Header;
    uint16_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_gibt_skip1_block {
    struct efi_hii_glyph_block Header;
    uint8_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_gibt_variability_block {
    struct efi_hii_glyph_block Header;
    struct efi_hii_glyph_info Cell;
    uint8_t GlyphPackInBits;
    uint8_t BitmapData[1];
} __attribute__((__packed__));

/* Named without values: GlyphPackInBits is the number of bits per pixel. */
#define EFI_GIBT_VARIABILITY_BLOCK_1_BIT 1
#define EFI_GIBT_VARIABILITY_BLOCK_2_BIT 2
#define EFI_GIBT_VARIABILITY_BLOCK_4_BIT 4
#define EFI_GIBT_VARIABILITY_BLOCK_8_BIT 8
#define EFI_GIBT_VARIABILITY_BLOCK_16_BIT 16
#define EFI_GIBT_VARIABILITY_BLOCK_24_BIT 24
#define EFI_GIBT_VARIABILITY_BLOCK_32_BIT 32

/* struct efi_device_path_protocol DevicePath[] follows (printed commented out). */
struct efi_hii_device_path_package {
    struct efi_hii_package_header Header;
} __attribute__((__packed__));

struct efi_hii_guid_package_hdr {
    struct efi_hii_package_header Header;
    struct efi_guid Guid;
} __attribute__((__packed__));

__extension__ struct efi_hii_string_package_hdr {
    struct efi_hii_package_header Header;
    uint32_t HdrSize;
    uint32_t StringInfoOffset;
    uint16_t LanguageWindow[16];
    EFI_STRING_ID LanguageName;
    char Language[];
} __attribute__((__packed__));

#define EFI_UEFI_CONFIG_LANG "x-UEFI"
#define EFI_UEFI_CONFIG_LANG_2 "x-i-UEFI"

/* The block body (BlockBody[]) follows: each string block starts with this header. */
struct efi_hii_string_block {
    uint8_t BlockType;
} __attribute__((__packed__));

#define EFI_HII_SIBT_END 0x00
#define EFI_HII_SIBT_STRING_SCSU 0x10
#define EFI_HII_SIBT_STRING_SCSU_FONT 0x11
#define EFI_HII_SIBT_STRINGS_SCSU 0x12
#define EFI_HII_SIBT_STRINGS_SCSU_FONT 0x13
#define EFI_HII_SIBT_STRING_UCS2 0x14
#define EFI_HII_SIBT_STRING_UCS2_FONT 0x15
#define EFI_HII_SIBT_STRINGS_UCS2 0x16
#define EFI_HII_SIBT_STRINGS_UCS2_FONT 0x17
#define EFI_HII_SIBT_DUPLICATE 0x20
#define EFI_HII_SIBT_SKIP2 0x21
#define EFI_HII_SIBT_SKIP1 0x22
#define EFI_HII_SIBT_EXT1 0x30
#define EFI_HII_SIBT_EXT2 0x31
#define EFI_HII_SIBT_EXT4 0x32
#define EFI_HII_SIBT_FONT 0x40

struct efi_hii_sibt_duplicate_block {
    struct efi_hii_string_block Header;
    EFI_STRING_ID StringId;
} __attribute__((__packed__));

struct efi_hii_sibt_end_block {
    struct efi_hii_string_block Header;
} __attribute__((__packed__));

struct efi_hii_sibt_ext1_block {
    struct efi_hii_string_block Header;
    uint8_t BlockType2;
    uint8_t Length;
} __attribute__((__packed__));

struct efi_hii_sibt_ext2_block {
    struct efi_hii_string_block Header;
    uint8_t BlockType2;
    uint16_t Length;
} __attribute__((__packed__));

struct efi_hii_sibt_ext4_block {
    struct efi_hii_string_block Header;
    uint8_t BlockType2;
    uint32_t Length;
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_font_block {
    struct efi_hii_sibt_ext2_block Header;
    uint8_t FontId;
    uint16_t FontSize;
    EFI_HII_FONT_STYLE FontStyle;
    uint16_t FontName[];
} __attribute__((__packed__));

struct efi_hii_sibt_skip1_block {
    struct efi_hii_string_block Header;
    uint8_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_sibt_skip2_block {
    struct efi_hii_string_block Header;
    uint16_t SkipCount;
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_string_scsu_block {
    struct efi_hii_string_block Header;
    uint8_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_string_scsu_font_block {
    struct efi_hii_string_block Header;
    uint8_t FontIdentifier;
    uint8_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_strings_scsu_block {
    struct efi_hii_string_block Header;
    uint16_t StringCount;
    uint8_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_strings_scsu_font_block {
    struct efi_hii_string_block Header;
    uint8_t FontIdentifier;
    uint16_t StringCount;
    uint8_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_string_ucs2_block {
    struct efi_hii_string_block Header;
    uint16_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_string_ucs2_font_block {
    struct efi_hii_string_block Header;
    uint8_t FontIdentifier;
    uint16_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_strings_ucs2_block {
    struct efi_hii_string_block Header;
    uint16_t StringCount;
    uint16_t StringText[];
} __attribute__((__packed__));

__extension__ struct efi_hii_sibt_strings_ucs2_font_block {
    struct efi_hii_string_block Header;
    uint8_t FontIdentifier;
    uint16_t StringCount;
    uint16_t StringText[];
} __attribute__((__packed__));

struct efi_hii_image_package_hdr {
    struct efi_hii_package_header Header;
    uint32_t ImageInfoOffset;
    uint32_t PaletteInfoOffset;
} __attribute__((__packed__));

/* The block body (BlockBody[]) follows: each image block starts with this header. */
struct efi_hii_image_block {
    uint8_t BlockType;
} __attribute__((__packed__));

#define EFI_HII_IIBT_END 0x00
#define EFI_HII_IIBT_IMAGE_1BIT 0x10
#define EFI_HII_IIBT_IMAGE_1BIT_TRANS 0x11
#define EFI_HII_IIBT_IMAGE_4BIT 0x12
#define EFI_HII_IIBT_IMAGE_4BIT_TRANS 0x13
#define EFI_HII_IIBT_IMAGE_8BIT 0x14
#define EFI_HII_IIBT_IMAGE_8BIT_TRANS 0x15
#define EFI_HII_IIBT_IMAGE_24BIT 0x16
#define EFI_HII_IIBT_IMAGE_24BIT_TRANS 0x17
#define EFI_HII_IIBT_IMAGE_JPEG 0x18
#define EFI_HII_IIBT_IMAGE_PNG 0x19
#define EFI_HII_IIBT_DUPLICATE 0x20
#define EFI_HII_IIBT_SKIP2 0x21
#define EFI_HII_IIBT_SKIP1 0x22
#define EFI_HII_IIBT_EXT1 0x30
#define EFI_HII_IIBT_EXT2 0x31
#define EFI_HII_IIBT_EXT4 0x32

struct efi_hii_iibt_end_block {
    struct efi_hii_image_block Header;
} __attribute__((__packed__));

struct efi_hii_iibt_ext1_block {
    struct efi_hii_image_block Header;
    uint8_t BlockType2;
    uint8_t Length;
} __attribute__((__packed__));

struct efi_hii_iibt_ext2_block {
    struct efi_hii_image_block Header;
    uint8_t BlockType2;
    uint16_t Length;
} __attribute__((__packed__));

struct efi_hii_iibt_ext4_block {
    struct efi_hii_image_block Header;
    uint8_t BlockType2;
    uint32_t Length;
} __attribute__((__packed__));

/* The image bases end in a one-element array, as firmware lays them out: the blocks embed them. */
struct efi_hii_iibt_image_1bit_base {
    uint16_t Width;
    uint16_t Height;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_hii_iibt_image_1bit_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_1bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_1bit_trans_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_1bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_rgb_pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} __attribute__((__packed__));

struct efi_hii_iibt_image_24bit_base {
    uint16_t Width;
    uint16_t Height;
    struct efi_hii_rgb_pixel Bitmap[1];
} __attribute__((__packed__));

struct efi_hii_iibt_image_24bit_block {
    struct efi_hii_image_block Header;
    struct efi_hii_iibt_image_24bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_24bit_trans_block {
    struct efi_hii_image_block Header;
    struct efi_hii_iibt_image_24bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_4bit_base {
    uint16_t Width;
    uint16_t Height;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_hii_iibt_image_4bit_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_4bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_4bit_trans_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_4bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_8bit_base {
    uint16_t Width;
    uint16_t Height;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_hii_iibt_image_8bit_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_8bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_image_8bit_trans_block {
    struct efi_hii_image_block Header;
    uint8_t PaletteIndex;
    struct efi_hii_iibt_image_8bit_base Bitmap;
} __attribute__((__packed__));

struct efi_hii_iibt_duplicate_block {
    struct efi_hii_image_block Header;
    EFI_IMAGE_ID ImageId;
} __attribute__((__packed__));

__extension__ struct efi_hii_iibt_jpeg_block {
    struct efi_hii_image_block Header;
    uint32_t Size;
    uint8_t Data[];
} __attribute__((__packed__));

struct efi_hii_iibt_skip1_block {
    struct efi_hii_image_block Header;
    uint8_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_iibt_skip2_block {
    struct efi_hii_image_block Header;
    uint16_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_iibt_png_block {
    struct efi_hii_image_block Header;
    uint32_t Size;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_hii_image_palette_info_header {
    uint16_t PaletteCount;
} __attribute__((__packed__));

__extension__ struct efi_hii_image_palette_info {
    uint16_t PaletteSize;
    struct efi_hii_rgb_pixel PaletteValue[];
} __attribute__((__packed__));

/* The op-codes follow the package header (printed commented out as OpCodeHeader). */
struct efi_hii_form_package_hdr {
    struct efi_hii_package_header Header;
} __attribute__((__packed__));

struct efi_ifr_op_header {
    uint8_t OpCode;
    uint8_t Length:7;
    uint8_t Scope:1;
} __attribute__((__packed__));

struct efi_ifr_statement_header {
    EFI_STRING_ID Prompt;
    EFI_STRING_ID Help;
} __attribute__((__packed__));

struct efi_ifr_question_header {
    struct efi_ifr_statement_header Header;
    EFI_QUESTION_ID QuestionId;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        uint16_t VarOffset;
    } VarStoreInfo;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_FLAG_READ_ONLY 0x01
#define EFI_IFR_FLAG_CALLBACK 0x04
#define EFI_IFR_FLAG_RESET_REQUIRED 0x10
#define EFI_IFR_FLAG_REST_STYLE 0x20
#define EFI_IFR_FLAG_RECONNECT_REQUIRED 0x40
#define EFI_IFR_FLAG_OPTIONS_ONLY 0x80

struct efi_hii_time {
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
} __attribute__((__packed__));

struct efi_hii_date {
    uint16_t Year;
    uint8_t Month;
    uint8_t Day;
} __attribute__((__packed__));

struct efi_hii_ref {
    EFI_QUESTION_ID QuestionId;
    EFI_FORM_ID FormId;
    struct efi_guid FormSetGuid;
    EFI_STRING_ID DevicePath;
} __attribute__((__packed__));

/* An EFI_IFR_TYPE_BUFFER value is a byte array (buffer[], printed commented out). */
union efi_ifr_type_value {
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    uint8_t b;
    struct efi_hii_time time;
    struct efi_hii_date date;
    EFI_STRING_ID string;
    struct efi_hii_ref ref;
} __attribute__((__packed__));

/* Printed inline in struct efi_ifr_numeric and struct efi_ifr_one_of; named at file scope for both. */
union efi_minmaxstep_data {
    struct __attribute__((__packed__)) {
        uint8_t MinValue;
        uint8_t MaxValue;
        uint8_t Step;
    } u8;
    struct __attribute__((__packed__)) {
        uint16_t MinValue;
        uint16_t MaxValue;
        uint16_t Step;
    } u16;
    struct __attribute__((__packed__)) {
        uint32_t MinValue;
        uint32_t MaxValue;
        uint32_t Step;
    } u32;
    struct __attribute__((__packed__)) {
        uint64_t MinValue;
        uint64_t MaxValue;
        uint64_t Step;
    } u64;
} __attribute__((__packed__));

#define EFI_IFR_ACTION_OP 0x0C

struct efi_ifr_action {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    EFI_STRING_ID QuestionConfig;
} __attribute__((__packed__));

struct efi_ifr_action_1 {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
} __attribute__((__packed__));

#define EFI_IFR_ANIMATION_OP 0x1F

struct efi_ifr_animation {
    struct efi_ifr_op_header Header;
    EFI_ANIMATION_ID Id;
} __attribute__((__packed__));

#define EFI_IFR_ADD_OP 0x3a

struct efi_ifr_add {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_AND_OP 0x15

struct efi_ifr_and {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_BITWISE_AND_OP 0x35

struct efi_ifr_bitwise_and {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_BITWISE_NOT_OP 0x37

struct efi_ifr_bitwise_not {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_BITWISE_OR_OP 0x36

struct efi_ifr_bitwise_or {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_CATENATE_OP 0x5e

struct efi_ifr_catenate {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_CHECKBOX_OP 0x06

struct efi_ifr_checkbox {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_CHECKBOX_DEFAULT 0x01
#define EFI_IFR_CHECKBOX_DEFAULT_MFG 0x02

#define EFI_IFR_CONDITIONAL_OP 0x50

struct efi_ifr_conditional {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_DATE_OP 0x1A

struct efi_ifr_date {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_QF_DATE_YEAR_SUPPRESS 0x01
#define EFI_QF_DATE_MONTH_SUPPRESS 0x02
#define EFI_QF_DATE_DAY_SUPPRESS 0x04
#define EFI_QF_DATE_STORAGE 0x30

#define EFI_QF_DATE_STORAGE_NORMAL 0x00
#define EFI_QF_DATE_STORAGE_TIME 0x10
#define EFI_QF_DATE_STORAGE_WAKEUP 0x20

#define EFI_IFR_DEFAULT_OP 0x5b

struct efi_ifr_default {
    struct efi_ifr_op_header Header;
    uint16_t DefaultId;
    uint8_t Type;
    union efi_ifr_type_value Value;
} __attribute__((__packed__));

struct efi_ifr_default_2 {
    struct efi_ifr_op_header Header;
    uint16_t DefaultId;
    uint8_t Type;
} __attribute__((__packed__));

#define EFI_IFR_DEFAULTSTORE_OP 0x5c

struct efi_ifr_defaultstore {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID DefaultName;
    uint16_t DefaultId;
} __attribute__((__packed__));

#define EFI_IFR_DISABLE_IF_OP 0x1e

struct efi_ifr_disable_if {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_DIVIDE_OP 0x3d

struct efi_ifr_divide {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_DUP_OP 0x57

struct efi_ifr_dup {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_END_OP 0x29

struct efi_ifr_end {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_EQUAL_OP 0x2f

struct efi_ifr_equal {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_EQ_ID_ID_OP 0x13

struct efi_ifr_eq_id_id {
    struct efi_ifr_op_header Header;
    EFI_QUESTION_ID QuestionId1;
    EFI_QUESTION_ID QuestionId2;
} __attribute__((__packed__));

#define EFI_IFR_EQ_ID_VAL_LIST_OP 0x14

struct efi_ifr_eq_id_val_list {
    struct efi_ifr_op_header Header;
    EFI_QUESTION_ID QuestionId;
    uint16_t ListLength;
    uint16_t ValueList[1];
} __attribute__((__packed__));

#define EFI_IFR_EQ_ID_VAL_OP 0x12

struct efi_ifr_eq_id_val {
    struct efi_ifr_op_header Header;
    EFI_QUESTION_ID QuestionId;
    uint16_t Value;
} __attribute__((__packed__));

#define EFI_IFR_FALSE_OP 0x47

struct efi_ifr_false {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_FIND_OP 0x4c

struct efi_ifr_find {
    struct efi_ifr_op_header Header;
    uint8_t Format;
} __attribute__((__packed__));

#define EFI_IFR_FF_CASE_SENSITIVE 0x00
#define EFI_IFR_FF_CASE_INSENSITIVE 0x01

#define EFI_IFR_FORM_OP 0x01

struct efi_ifr_form {
    struct efi_ifr_op_header Header;
    EFI_FORM_ID FormId;
    EFI_STRING_ID FormTitle;
} __attribute__((__packed__));

#define EFI_IFR_FORM_MAP_OP 0x5D

struct efi_ifr_form_map_method {
    EFI_STRING_ID MethodTitle;
    struct efi_guid MethodIdentifier;
} __attribute__((__packed__));

/* struct efi_ifr_form_map_method Methods[] follows (printed commented out). */
struct efi_ifr_form_map {
    struct efi_ifr_op_header Header;
    EFI_FORM_ID FormId;
} __attribute__((__packed__));

#define EFI_HII_STANDARD_FORM_GUID \
    {0x3bd2f4ec, 0xe524, 0x46e4, {0xa9, 0xd8, 0x51, 0x01, 0x17, 0x42, 0x55, 0x62}}

#define EFI_IFR_FORM_SET_OP 0x0E

/* Flags bits 0:1 count the struct efi_guid ClassGuid[] that follows (printed commented out). */
struct efi_ifr_form_set {
    struct efi_ifr_op_header Header;
    struct efi_guid Guid;
    EFI_STRING_ID FormSetTitle;
    EFI_STRING_ID Help;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_GET_OP 0x2B

struct efi_ifr_get {
    struct efi_ifr_op_header Header;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        uint16_t VarOffset;
    } VarStoreInfo;
    uint8_t VarStoreType;
} __attribute__((__packed__));

#define EFI_IFR_GRAY_OUT_IF_OP 0x19

struct efi_ifr_gray_out_if {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_GREATER_EQUAL_OP 0x32

struct efi_ifr_greater_equal {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_GREATER_THAN_OP 0x31

struct efi_ifr_greater_than {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_GUID_OP 0x5F

struct efi_ifr_guid {
    struct efi_ifr_op_header Header;
    struct efi_guid Guid;
} __attribute__((__packed__));

#define EFI_IFR_IMAGE_OP 0x04

/* The printed structure lost the struct efi_ifr_op_header that every op-code starts with. */
struct efi_ifr_image {
    struct efi_ifr_op_header Header;
    EFI_IMAGE_ID Id;
} __attribute__((__packed__));

#define EFI_IFR_INCONSISTENT_IF_OP 0x011

struct efi_ifr_inconsistent_if {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID Error;
} __attribute__((__packed__));

#define EFI_IFR_LENGTH_OP 0x56

struct efi_ifr_length {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_LESS_EQUAL_OP 0x34

struct efi_ifr_less_equal {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_LESS_THAN_OP 0x33

struct efi_ifr_less_than {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_LOCKED_OP 0x0B

struct efi_ifr_locked {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MAP_OP 0x22

struct efi_ifr_map {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MATCH_OP 0x2a

struct efi_ifr_match {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MID_OP 0x4b

struct efi_ifr_mid {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MODAL_TAG_OP 0x61

struct efi_ifr_modal_tag {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MODULO_OP 0x3e

struct efi_ifr_modulo {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_MULTIPLY_OP 0x3c

struct efi_ifr_multiply {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_NOT_OP 0x17

struct efi_ifr_not {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_NOT_EQUAL_OP 0x30

struct efi_ifr_not_equal {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_NO_SUBMIT_IF_OP 0x10

struct efi_ifr_no_submit_if {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID Error;
} __attribute__((__packed__));

#define EFI_IFR_NUMERIC_OP 0x07

struct efi_ifr_numeric {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t Flags;
    union efi_minmaxstep_data data;
} __attribute__((__packed__));

#define EFI_IFR_NUMERIC_SIZE 0x03
#define EFI_IFR_NUMERIC_SIZE_1 0x00
#define EFI_IFR_NUMERIC_SIZE_2 0x01
#define EFI_IFR_NUMERIC_SIZE_4 0x02
#define EFI_IFR_NUMERIC_SIZE_8 0x03

#define EFI_IFR_DISPLAY 0x30
#define EFI_IFR_DISPLAY_INT_DEC 0x00
#define EFI_IFR_DISPLAY_UINT_DEC 0x10
#define EFI_IFR_DISPLAY_UINT_HEX 0x20

#define EFI_IFR_ONE_OP 0x53

struct efi_ifr_one {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_ONES_OP 0x54

struct efi_ifr_ones {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_ONE_OF_OP 0x05

struct efi_ifr_one_of {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t Flags;
    union efi_minmaxstep_data data;
} __attribute__((__packed__));

#define EFI_IFR_ONE_OF_OPTION_OP 0x09

struct efi_ifr_one_of_option {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID Option;
    uint8_t Flags;
    uint8_t Type;
    union efi_ifr_type_value Value;
} __attribute__((__packed__));

#define EFI_IFR_TYPE_NUM_SIZE_8 0x00
#define EFI_IFR_TYPE_NUM_SIZE_16 0x01
#define EFI_IFR_TYPE_NUM_SIZE_32 0x02
#define EFI_IFR_TYPE_NUM_SIZE_64 0x03
#define EFI_IFR_TYPE_BOOLEAN 0x04
#define EFI_IFR_TYPE_TIME 0x05
#define EFI_IFR_TYPE_DATE 0x06
#define EFI_IFR_TYPE_STRING 0x07
#define EFI_IFR_TYPE_OTHER 0x08
#define EFI_IFR_TYPE_UNDEFINED 0x09
#define EFI_IFR_TYPE_ACTION 0x0A
#define EFI_IFR_TYPE_BUFFER 0x0B
#define EFI_IFR_TYPE_REF 0x0C

#define EFI_IFR_OPTION_DEFAULT 0x10
#define EFI_IFR_OPTION_DEFAULT_MFG 0x20

#define EFI_IFR_OR_OP 0x16

struct efi_ifr_or {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_ORDERED_LIST_OP 0x23

struct efi_ifr_ordered_list {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t MaxContainers;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_UNIQUE_SET 0x01
#define EFI_IFR_NO_EMPTY_SET 0x02

#define EFI_IFR_PASSWORD_OP 0x08

struct efi_ifr_password {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint16_t MinSize;
    uint16_t MaxSize;
} __attribute__((__packed__));

#define EFI_IFR_QUESTION_REF1_OP 0x40

struct efi_ifr_question_ref1 {
    struct efi_ifr_op_header Header;
    EFI_QUESTION_ID QuestionId;
} __attribute__((__packed__));

#define EFI_IFR_QUESTION_REF2_OP 0x41

struct efi_ifr_question_ref2 {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_QUESTION_REF3_OP 0x51

struct efi_ifr_question_ref3 {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

struct efi_ifr_question_ref3_2 {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID DevicePath;
} __attribute__((__packed__));

struct efi_ifr_question_ref3_3 {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID DevicePath;
    struct efi_guid Guid;
} __attribute__((__packed__));

#define EFI_IFR_READ_OP 0x2D

struct efi_ifr_read {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_REF_OP 0x0F

struct efi_ifr_ref {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    EFI_FORM_ID FormId;
} __attribute__((__packed__));

struct efi_ifr_ref2 {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
} __attribute__((__packed__));

struct efi_ifr_ref3 {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
    struct efi_guid FormSetId;
} __attribute__((__packed__));

struct efi_ifr_ref4 {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
    struct efi_guid FormSetId;
    EFI_STRING_ID DevicePath;
} __attribute__((__packed__));

struct efi_ifr_ref5 {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
} __attribute__((__packed__));

#define EFI_IFR_REFRESH_OP 0x1d

struct efi_ifr_refresh {
    struct efi_ifr_op_header Header;
    uint8_t RefreshInterval;
} __attribute__((__packed__));

#define EFI_IFR_REFRESH_ID_OP 0x62

struct efi_ifr_refresh_id {
    struct efi_ifr_op_header Header;
    struct efi_guid RefreshEventGroupId;
} __attribute__((__packed__));

#define EFI_IFR_RESET_BUTTON_OP 0x0d

struct efi_ifr_reset_button {
    struct efi_ifr_op_header Header;
    struct efi_ifr_statement_header Statement;
    EFI_DEFAULT_ID DefaultId;
} __attribute__((__packed__));

#define EFI_IFR_RULE_OP 0x18

struct efi_ifr_rule {
    struct efi_ifr_op_header Header;
    uint8_t RuleId;
} __attribute__((__packed__));

#define EFI_IFR_RULE_REF_OP 0x3f

struct efi_ifr_rule_ref {
    struct efi_ifr_op_header Header;
    uint8_t RuleId;
} __attribute__((__packed__));

#define EFI_IFR_SECURITY_OP 0x60

struct efi_ifr_security {
    struct efi_ifr_op_header Header;
    struct efi_guid Permissions;
} __attribute__((__packed__));

#define EFI_IFR_SET_OP 0x2C

struct efi_ifr_set {
    struct efi_ifr_op_header Header;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        uint16_t VarOffset;
    } VarStoreInfo;
    uint8_t VarStoreType;
} __attribute__((__packed__));

#define EFI_IFR_SHIFT_LEFT_OP 0x38

struct efi_ifr_shift_left {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_SHIFT_RIGHT_OP 0x39

struct efi_ifr_shift_right {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_SPAN_OP 0x59

struct efi_ifr_span {
    struct efi_ifr_op_header Header;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_FLAGS_FIRST_MATCHING 0x00
#define EFI_IFR_FLAGS_FIRST_NON_MATCHING 0x01

#define EFI_IFR_STRING_OP 0x1C

struct efi_ifr_string {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t MinSize;
    uint8_t MaxSize;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_STRING_MULTI_LINE 0x01

#define EFI_IFR_STRING_REF1_OP 0x4e

struct efi_ifr_string_ref1 {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID StringId;
} __attribute__((__packed__));

#define EFI_IFR_STRING_REF2_OP 0x4f

struct efi_ifr_string_ref2 {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_SUBTITLE_OP 0x02

struct efi_ifr_subtitle {
    struct efi_ifr_op_header Header;
    struct efi_ifr_statement_header Statement;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_IFR_FLAGS_HORIZONTAL 0x01

#define EFI_IFR_SUBTRACT_OP 0x3b

struct efi_ifr_subtract {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_SUPPRESS_IF_OP 0x0a

struct efi_ifr_suppress_if {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TEXT_OP 0x03

struct efi_ifr_text {
    struct efi_ifr_op_header Header;
    struct efi_ifr_statement_header Statement;
    EFI_STRING_ID TextTwo;
} __attribute__((__packed__));

#define EFI_IFR_THIS_OP 0x58

struct efi_ifr_this {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TIME_OP 0x1b

struct efi_ifr_time {
    struct efi_ifr_op_header Header;
    struct efi_ifr_question_header Question;
    uint8_t Flags;
} __attribute__((__packed__));

#define EFI_QF_TIME_HOUR_SUPPRESS 0x01
#define EFI_QF_TIME_MINUTE_SUPPRESS 0x02
#define EFI_QF_TIME_SECOND_SUPPRESS 0x04
#define EFI_QF_TIME_STORAGE 0x30

#define EFI_QF_TIME_STORAGE_NORMAL 0x00
#define EFI_QF_TIME_STORAGE_TIME 0x10
#define EFI_QF_TIME_STORAGE_WAKEUP 0x20

#define EFI_IFR_TOKEN_OP 0x4d

struct efi_ifr_token {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TO_BOOLEAN_OP 0x4A

struct efi_ifr_to_boolean {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TO_LOWER_OP 0x20

struct efi_ifr_to_lower {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TO_STRING_OP 0x49

struct efi_ifr_to_string {
    struct efi_ifr_op_header Header;
    uint8_t Format;
} __attribute__((__packed__));

#define EFI_IFR_TO_UINT_OP 0x48

struct efi_ifr_to_uint {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TO_UPPER_OP 0x21

struct efi_ifr_to_upper {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_TRUE_OP 0x46

struct efi_ifr_true {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_UINT8_OP 0x42

struct efi_ifr_uint8 {
    struct efi_ifr_op_header Header;
    uint8_t Value;
} __attribute__((__packed__));

#define EFI_IFR_UINT16_OP 0x43

struct efi_ifr_uint16 {
    struct efi_ifr_op_header Header;
    uint16_t Value;
} __attribute__((__packed__));

#define EFI_IFR_UINT32_OP 0x44

struct efi_ifr_uint32 {
    struct efi_ifr_op_header Header;
    uint32_t Value;
} __attribute__((__packed__));

#define EFI_IFR_UINT64_OP 0x45

struct efi_ifr_uint64 {
    struct efi_ifr_op_header Header;
    uint64_t Value;
} __attribute__((__packed__));

#define EFI_IFR_UNDEFINED_OP 0x55

struct efi_ifr_undefined {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_VALUE_OP 0x5a

struct efi_ifr_value {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_VARSTORE_OP 0x24

/* The null-terminated ASCII Name follows Size (printed commented out). */
struct efi_ifr_varstore {
    struct efi_ifr_op_header Header;
    struct efi_guid Guid;
    EFI_VARSTORE_ID VarStoreId;
    uint16_t Size;
} __attribute__((__packed__));

#define EFI_IFR_VARSTORE_NAME_VALUE_OP 0x25

struct efi_ifr_varstore_name_value {
    struct efi_ifr_op_header Header;
    EFI_VARSTORE_ID VarStoreId;
    struct efi_guid Guid;
} __attribute__((__packed__));

#define EFI_IFR_VARSTORE_EFI_OP 0x26

/* The null-terminated ASCII Name follows Size (printed commented out). */
struct efi_ifr_varstore_efi {
    struct efi_ifr_op_header Header;
    EFI_VARSTORE_ID VarStoreId;
    struct efi_guid Guid;
    uint32_t Attributes;
    uint16_t Size;
} __attribute__((__packed__));

#define EFI_IFR_VARSTORE_DEVICE_OP 0x27

struct efi_ifr_varstore_device {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID DevicePath;
} __attribute__((__packed__));

#define EFI_IFR_VERSION_OP 0x28

struct efi_ifr_version {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_WRITE_OP 0x2E

struct efi_ifr_write {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_ZERO_OP 0x52

struct efi_ifr_zero {
    struct efi_ifr_op_header Header;
} __attribute__((__packed__));

#define EFI_IFR_WARNING_IF_OP 0x063

struct efi_ifr_warning_if {
    struct efi_ifr_op_header Header;
    EFI_STRING_ID Warning;
    uint8_t TimeOut;
} __attribute__((__packed__));

#define EFI_IFR_MATCH2_OP 0x64

struct efi_ifr_match2 {
    struct efi_ifr_op_header Header;
    struct efi_guid SyntaxType;
} __attribute__((__packed__));

/* struct efi_hii_keyboard_layout Layout[] follows (printed commented out). */
struct efi_hii_keyboard_package_hdr {
    struct efi_hii_package_header Header;
    uint16_t LayoutCount;
} __attribute__((__packed__));

struct efi_hii_animation_package_hdr {
    struct efi_hii_package_header Header;
    uint32_t AnimationInfoOffset;
} __attribute__((__packed__));

/* The block body follows BlockType (printed commented out). */
struct efi_hii_animation_block {
    uint8_t BlockType;
} __attribute__((__packed__));

#define EFI_HII_AIBT_END 0x00
#define EFI_HII_AIBT_OVERLAY_IMAGES 0x10
#define EFI_HII_AIBT_CLEAR_IMAGES 0x11
#define EFI_HII_AIBT_RESTORE_SCRN 0x12
#define EFI_HII_AIBT_OVERLAY_IMAGES_LOOP 0x18
#define EFI_HII_AIBT_CLEAR_IMAGES_LOOP 0x19
#define EFI_HII_AIBT_RESTORE_SCRN_LOOP 0x1A
#define EFI_HII_AIBT_DUPLICATE 0x20
#define EFI_HII_AIBT_SKIP2 0x21
#define EFI_HII_AIBT_SKIP1 0x22
#define EFI_HII_AIBT_EXT1 0x30
#define EFI_HII_AIBT_EXT2 0x31
#define EFI_HII_AIBT_EXT4 0x32

struct efi_hii_aibt_ext1_block {
    struct efi_hii_animation_block Header;
    uint8_t BlockType2;
    uint8_t Length;
} __attribute__((__packed__));

struct efi_hii_aibt_ext2_block {
    struct efi_hii_animation_block Header;
    uint8_t BlockType2;
    uint16_t Length;
} __attribute__((__packed__));

struct efi_hii_aibt_ext4_block {
    struct efi_hii_animation_block Header;
    uint8_t BlockType2;
    uint32_t Length;
} __attribute__((__packed__));

struct efi_hii_animation_cell {
    uint16_t OffsetX;
    uint16_t OffsetY;
    EFI_IMAGE_ID ImageId;
    uint16_t Delay;
} __attribute__((__packed__));

/*
 * The animation block bodies carry no header: either a struct efi_hii_animation_block or a
 * struct efi_hii_aibt_ext*_block precedes them.
 */
__extension__ struct efi_hii_aibt_overlay_images_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

__extension__ struct efi_hii_aibt_clear_images_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_rgb_pixel BackgndColor;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

__extension__ struct efi_hii_aibt_restore_scrn_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

__extension__ struct efi_hii_aibt_overlay_images_loop_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

__extension__ struct efi_hii_aibt_clear_images_loop_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_rgb_pixel BackgndColor;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

__extension__ struct efi_hii_aibt_restore_scrn_loop_block {
    EFI_IMAGE_ID DftImageId;
    uint16_t Width;
    uint16_t Height;
    uint16_t CellCount;
    struct efi_hii_animation_cell AnimationCell[];
} __attribute__((__packed__));

struct efi_hii_aibt_duplicate_block {
    EFI_ANIMATION_ID AnimationId;
} __attribute__((__packed__));

struct efi_hii_aibt_skip1_block {
    uint8_t SkipCount;
} __attribute__((__packed__));

struct efi_hii_aibt_skip2_block {
    uint16_t SkipCount;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
