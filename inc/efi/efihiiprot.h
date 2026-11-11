#ifndef EFI_EFIHIIPROT_H_
#define EFI_EFIHIIPROT_H_

#include "efihii.h"
#include "efiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HII_FONT_PROTOCOL_GUID \
    {0xe9ca4775, 0x8657, 0x47fc, {0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x8, 0x43, 0x24}}

struct efi_hii_font_protocol;

typedef uint32_t EFI_HII_OUT_FLAGS;

#define EFI_HII_OUT_FLAG_CLIP 0x00000001
#define EFI_HII_OUT_FLAG_WRAP 0x00000002
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 0x00000004
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_X 0x00000008
#define EFI_HII_OUT_FLAG_TRANSPARENT 0x00000010
#define EFI_HII_IGNORE_IF_NO_GLYPH 0x00000020
#define EFI_HII_IGNORE_LINE_BREAK 0x00000040
#define EFI_HII_DIRECT_TO_SCREEN 0x00000080

struct efi_hii_row_info {
    size_t StartIndex;
    size_t EndIndex;
    size_t LineHeight;
    size_t LineWidth;
    size_t BaselineOffset;
};

/* FontName has one element, as firmware lays it out: struct efi_font_display_info embeds this. */
struct efi_font_info {
    EFI_HII_FONT_STYLE FontStyle;
    uint16_t FontSize;
    uint16_t FontName[1];
};

typedef uint32_t EFI_FONT_INFO_MASK;

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
    struct efi_graphics_output_blt_pixel ForegroundColor;
    struct efi_graphics_output_blt_pixel BackgroundColor;
    EFI_FONT_INFO_MASK FontInfoMask;
    struct efi_font_info FontInfo;
};

struct efi_image_output {
    uint16_t Width;
    uint16_t Height;
    union {
        struct efi_graphics_output_blt_pixel *Bitmap;
        struct efi_graphics_output_protocol *Screen;
    } Image;
};

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_TO_IMAGE)(
    const struct efi_hii_font_protocol *This,
    EFI_HII_OUT_FLAGS Flags,
    const EFI_STRING String,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY,
    struct efi_hii_row_info **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_ID_TO_IMAGE)(
    const struct efi_hii_font_protocol *This,
    EFI_HII_OUT_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY,
    struct efi_hii_row_info **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH)(
    const struct efi_hii_font_protocol *This,
    uint16_t Char,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t *Baseline
);

typedef void *EFI_FONT_HANDLE;

typedef EFI_STATUS (EFI_API *EFI_HII_GET_FONT_INFO)(
    const struct efi_hii_font_protocol *This,
    EFI_FONT_HANDLE *FontHandle,
    const struct efi_font_display_info *StringInfoIn,
    struct efi_font_display_info **StringInfoOut,
    const EFI_STRING String
);

struct efi_hii_font_protocol {
    EFI_HII_STRING_TO_IMAGE StringToImage;
    EFI_HII_STRING_ID_TO_IMAGE StringIdToImage;
    EFI_HII_GET_GLYPH GetGlyph;
    EFI_HII_GET_FONT_INFO GetFontInfo;
};

#define EFI_HII_FONT_EX_PROTOCOL_GUID \
    {0x849e6875, 0xdb35, 0x4df8, {0xb4, 0x1e, 0xc8, 0xf3, 0x37, 0x18, 0x7, 0x3f}}

struct efi_hii_font_ex_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_TO_IMAGE_EX)(
    const struct efi_hii_font_ex_protocol *This,
    EFI_HII_OUT_FLAGS Flags,
    const EFI_STRING String,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY,
    struct efi_hii_row_info **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_ID_TO_IMAGE_EX)(
    const struct efi_hii_font_ex_protocol *This,
    EFI_HII_OUT_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY,
    struct efi_hii_row_info **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

/* Baseline is printed by value, but the parameters are GetGlyph()'s, which returns it. */
typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH_EX)(
    const struct efi_hii_font_ex_protocol *This,
    uint16_t Char,
    const struct efi_font_display_info *StringInfo,
    struct efi_image_output **Blt,
    size_t *Baseline
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_FONT_INFO_EX)(
    const struct efi_hii_font_ex_protocol *This,
    EFI_FONT_HANDLE *FontHandle,
    const struct efi_font_display_info *StringInfoIn,
    struct efi_font_display_info **StringInfoOut,
    const EFI_STRING String
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH_INFO)(
    const struct efi_hii_font_ex_protocol *This,
    uint16_t Char,
    const struct efi_font_display_info *FontDisplayInfo,
    struct efi_hii_glyph_info *GlyphInfo
);

struct efi_hii_font_ex_protocol {
    EFI_HII_STRING_TO_IMAGE_EX StringToImageEx;
    EFI_HII_STRING_ID_TO_IMAGE_EX StringIdToImageEx;
    EFI_HII_GET_GLYPH_EX GetGlyphEx;
    EFI_HII_GET_FONT_INFO_EX GetFontInfoEx;
    EFI_HII_GET_GLYPH_INFO GetGlyphInfo;
};

#define EFI_HII_STRING_PROTOCOL_GUID \
    {0xfd96974, 0x23aa, 0x4cdc, {0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}}

struct efi_hii_string_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_STRING)(
    const struct efi_hii_string_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID *StringId,
    const char *Language,
    const uint16_t *LanguageName,
    const EFI_STRING String,
    const struct efi_font_info *StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_STRING)(
    const struct efi_hii_string_protocol *This,
    const char *Language,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    EFI_STRING String,
    size_t *StringSize,
    struct efi_font_info **StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_STRING)(
    const struct efi_hii_string_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const EFI_STRING String,
    const struct efi_font_info *StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_LANGUAGES)(
    const struct efi_hii_string_protocol *This,
    EFI_HII_HANDLE PackageList,
    char *Languages,
    size_t *LanguagesSize
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_2ND_LANGUAGES)(
    const struct efi_hii_string_protocol *This,
    EFI_HII_HANDLE PackageList,
    const char *PrimaryLanguage,
    char *SecondaryLanguages,
    size_t *SecondaryLanguagesSize
);

struct efi_hii_string_protocol {
    EFI_HII_NEW_STRING NewString;
    EFI_HII_GET_STRING GetString;
    EFI_HII_SET_STRING SetString;
    EFI_HII_GET_LANGUAGES GetLanguages;
    EFI_HII_GET_2ND_LANGUAGES GetSecondaryLanguages;
};

#define EFI_HII_IMAGE_PROTOCOL_GUID \
    {0x31a6406a, 0x6bdf, 0x4e46, {0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x9, 0x20}}

struct efi_hii_image_protocol;

struct efi_image_input {
    uint32_t Flags;
    uint16_t Width;
    uint16_t Height;
    struct efi_graphics_output_blt_pixel *Bitmap;
};

#define EFI_IMAGE_TRANSPARENT 0x00000001

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_IMAGE)(
    const struct efi_hii_image_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID *ImageId,
    const struct efi_image_input *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE)(
    const struct efi_hii_image_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    struct efi_image_input *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_IMAGE)(
    const struct efi_hii_image_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    const struct efi_image_input *Image
);

typedef uint32_t EFI_HII_DRAW_FLAGS;

#define EFI_HII_DRAW_FLAG_CLIP 0x00000001
#define EFI_HII_DRAW_FLAG_TRANSPARENT 0x00000030
#define EFI_HII_DRAW_FLAG_DEFAULT 0x00000000
#define EFI_HII_DRAW_FLAG_FORCE_TRANS 0x00000010
#define EFI_HII_DRAW_FLAG_FORCE_OPAQUE 0x00000020

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE)(
    const struct efi_hii_image_protocol *This,
    EFI_HII_DRAW_FLAGS Flags,
    const struct efi_image_input *Image,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_ID)(
    const struct efi_hii_image_protocol *This,
    EFI_HII_DRAW_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY
);

struct efi_hii_image_protocol {
    EFI_HII_NEW_IMAGE NewImage;
    EFI_HII_GET_IMAGE GetImage;
    EFI_HII_SET_IMAGE SetImage;
    EFI_HII_DRAW_IMAGE DrawImage;
    EFI_HII_DRAW_IMAGE_ID DrawImageId;
};

#define EFI_HII_IMAGE_EX_PROTOCOL_GUID \
    {0x1a1241e6, 0x8f19, 0x41a9, {0xbc, 0xe, 0xe8, 0xef, 0x39, 0xe0, 0x65, 0x46}}

struct efi_hii_image_ex_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_IMAGE_EX)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID *ImageId,
    struct efi_image_input *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE_EX)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    struct efi_image_input *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_IMAGE_EX)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    const struct efi_image_input *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_EX)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_DRAW_FLAGS Flags,
    const struct efi_image_input *Image,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_ID_EX)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_DRAW_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    struct efi_image_output **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE_INFO)(
    const struct efi_hii_image_ex_protocol *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    struct efi_image_output *Image
);

struct efi_hii_image_ex_protocol {
    EFI_HII_NEW_IMAGE_EX NewImageEx;
    EFI_HII_GET_IMAGE_EX GetImageEx;
    EFI_HII_SET_IMAGE_EX SetImageEx;
    EFI_HII_DRAW_IMAGE_EX DrawImageEx;
    EFI_HII_DRAW_IMAGE_ID_EX DrawImageIdEx;
    EFI_HII_GET_IMAGE_INFO GetImageInfo;
};

#define EFI_HII_IMAGE_DECODER_PROTOCOL_GUID \
    {0x9E66F251, 0x727C, 0x418C, {0xBF, 0xD6, 0xC2, 0xB4, 0x25, 0x28, 0x18, 0xEA}}

struct efi_hii_image_decoder_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_GET_NAME)(
    const struct efi_hii_image_decoder_protocol *This,
    struct efi_guid **DecoderName,
    uint16_t *NumberOfDecoderName
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
    struct efi_guid DecoderName;
    uint16_t ImageInfoSize;
    uint16_t ImageWidth;
    uint16_t ImageHeight;
    uint32_t ColorType;
    uint8_t ColorDepthInBits;
};

struct efi_hii_image_decoder_jpeg_info {
    struct efi_hii_image_decoder_image_info_header Header;
    uint16_t ScanType;
    uint64_t Reserved;
};

#define EFI_IMAGE_JPEG_SCANTYPE_PROGREESSIVE 0x01
#define EFI_IMAGE_JPEG_SCANTYPE_INTERLACED 0x02

struct efi_hii_image_decoder_png_info {
    struct efi_hii_image_decoder_image_info_header Header;
    uint16_t Channels;
    uint64_t Reserved;
};

struct efi_hii_image_decoder_other_info {
    struct efi_hii_image_decoder_image_info_header Header;
    uint16_t ImageExtenion[1];
};

/*
 * ImageInfo is printed as EFI_HII_IMAGE_DECODER_IMAGE_INFO, which is defined nowhere; every image
 * information structure starts with struct efi_hii_image_decoder_image_info_header.
 */
typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_GET_IMAGE_INFO)(
    const struct efi_hii_image_decoder_protocol *This,
    void *Image,
    size_t SizeOfImage,
    struct efi_hii_image_decoder_image_info_header **ImageInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_DECODE)(
    const struct efi_hii_image_decoder_protocol *This,
    void *Image,
    size_t ImageRawDataSize,
    struct efi_image_output **Bitmap,
    bool Transparent
);

struct efi_hii_image_decoder_protocol {
    EFI_HII_IMAGE_DECODER_GET_NAME GetImageDecoderName;
    EFI_HII_IMAGE_DECODER_GET_IMAGE_INFO GetImageInfo;
    EFI_HII_IMAGE_DECODER_DECODE DecodeImage;
};

#define EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL_GUID \
    {0xf7102853, 0x7787, 0x4dc2, {0xa8, 0xa8, 0x21, 0xb5, 0xdd, 0x5, 0xc8, 0x9b}}

struct efi_hii_font_glyph_generator_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_GENERATE_GLYPH)(
    const struct efi_hii_font_glyph_generator_protocol *This,
    uint16_t Char,
    const struct efi_font_display_info *FontInfo,
    struct efi_hii_gibt_variability_block *GlyphBlock
);

typedef EFI_STATUS (EFI_API *EFI_HII_GENERATE_GLYPH_IMAGE)(
    const struct efi_hii_font_glyph_generator_protocol *This,
    const struct efi_hii_glyph_info *Cell,
    uint8_t *GlyphBuffer,
    const struct efi_font_display_info *FontInfo,
    struct efi_image_output *Image,
    int32_t *BltX,
    int32_t *BltY,
    bool Transparent
);

/* The member types are printed EFI_GENERATE_GLYPH and EFI_GENERATE_IMAGE, defined nowhere. */
struct efi_hii_font_glyph_generator_protocol {
    EFI_HII_GENERATE_GLYPH GenerateGlyph;
    EFI_HII_GENERATE_GLYPH_IMAGE GenerateGlyphImage;
};

#define EFI_HII_DATABASE_PROTOCOL_GUID \
    {0xef9fc172, 0xa1b2, 0x4693, {0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}}

struct efi_hii_database_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_NEW_PACK)(
    const struct efi_hii_database_protocol *This,
    const struct efi_hii_package_list_header *PackageList,
    const EFI_HANDLE DriverHandle,
    EFI_HII_HANDLE *Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_REMOVE_PACK)(
    const struct efi_hii_database_protocol *This,
    EFI_HII_HANDLE Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_UPDATE_PACK)(
    const struct efi_hii_database_protocol *This,
    EFI_HII_HANDLE Handle,
    const struct efi_hii_package_list_header *PackageList
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_LIST_PACKS)(
    const struct efi_hii_database_protocol *This,
    uint8_t PackageType,
    const struct efi_guid *PackageGuid,
    size_t *HandleBufferLength,
    EFI_HII_HANDLE *Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_EXPORT_PACKS)(
    const struct efi_hii_database_protocol *This,
    EFI_HII_HANDLE Handle,
    size_t *BufferSize,
    struct efi_hii_package_list_header *Buffer
);

typedef uintptr_t EFI_HII_DATABASE_NOTIFY_TYPE;

#define EFI_HII_DATABASE_NOTIFY_NEW_PACK 0x00000001
#define EFI_HII_DATABASE_NOTIFY_REMOVE_PACK 0x00000002
#define EFI_HII_DATABASE_NOTIFY_EXPORT_PACK 0x00000004
#define EFI_HII_DATABASE_NOTIFY_ADD_PACK 0x00000008

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_NOTIFY)(
    uint8_t PackageType,
    const struct efi_guid *PackageGuid,
    const struct efi_hii_package_header *Package,
    EFI_HII_HANDLE Handle,
    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_REGISTER_NOTIFY)(
    const struct efi_hii_database_protocol *This,
    uint8_t PackageType,
    const struct efi_guid *PackageGuid,
    const EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
    EFI_HANDLE *NotifyHandle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_UNREGISTER_NOTIFY)(
    const struct efi_hii_database_protocol *This,
    EFI_HANDLE NotificationHandle
);

typedef EFI_STATUS (EFI_API *EFI_HII_FIND_KEYBOARD_LAYOUTS)(
    const struct efi_hii_database_protocol *This,
    uint16_t *KeyGuidBufferLength,
    struct efi_guid *KeyGuidBuffer
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
    uint32_t Key;
    uint16_t Unicode;
    uint16_t ShiftedUnicode;
    uint16_t AltGrUnicode;
    uint16_t ShiftedAltGrUnicode;
    uint16_t Modifier;
    uint16_t AffectedAttribute;
} __attribute__((__packed__));

#define EFI_AFFECTED_BY_STANDARD_SHIFT 0x0001
#define EFI_AFFECTED_BY_CAPS_LOCK 0x0002
#define EFI_AFFECTED_BY_NUM_LOCK 0x0004

/* __extension__: a flexible array member is standard C but an extension in C++. */
__extension__ struct efi_hii_keyboard_layout {
    uint16_t LayoutLength;
    struct efi_guid Guid;
    uint32_t LayoutDescriptorStringOffset;
    uint8_t DescriptorCount;
    struct efi_key_descriptor Descriptors[];
} __attribute__((__packed__));

/* The fixed part: each EFI_DESCRIPTION_STRING that follows starts with a variable-length array. */
struct efi_description_string_bundle {
    uint16_t DescriptionCount;
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
#define EFI_HOME_MODIFIER 0x000A
#define EFI_END_MODIFIER 0x000B
#define EFI_LEFT_SHIFT_MODIFIER 0x000C
#define EFI_RIGHT_SHIFT_MODIFIER 0x000D
#define EFI_CAPS_LOCK_MODIFIER 0x000E
#define EFI_NUM_LOCK_MODIFIER 0x000F
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
#define EFI_FUNCTION_KEY_FIVE_MODIFIER 0x001A
#define EFI_FUNCTION_KEY_SIX_MODIFIER 0x001B
#define EFI_FUNCTION_KEY_SEVEN_MODIFIER 0x001C
#define EFI_FUNCTION_KEY_EIGHT_MODIFIER 0x001D
#define EFI_FUNCTION_KEY_NINE_MODIFIER 0x001E
#define EFI_FUNCTION_KEY_TEN_MODIFIER 0x001F
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

typedef EFI_STATUS (EFI_API *EFI_HII_GET_KEYBOARD_LAYOUT)(
    const struct efi_hii_database_protocol *This,
    struct efi_guid *KeyGuid,
    uint16_t *KeyboardLayoutLength,
    struct efi_hii_keyboard_layout *KeyboardLayout
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_KEYBOARD_LAYOUT)(
    const struct efi_hii_database_protocol *This,
    struct efi_guid *KeyGuid
);

#define EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID \
    {0x14982a4f, 0xb0ed, 0x45b8, {0xa8, 0x11, 0x5a, 0x7a, 0x9b, 0xc2, 0x32, 0xdf}}

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_GET_PACK_HANDLE)(
    const struct efi_hii_database_protocol *This,
    EFI_HII_HANDLE PackageListHandle,
    EFI_HANDLE *DriverHandle
);

struct efi_hii_database_protocol {
    EFI_HII_DATABASE_NEW_PACK NewPackageList;
    EFI_HII_DATABASE_REMOVE_PACK RemovePackageList;
    EFI_HII_DATABASE_UPDATE_PACK UpdatePackageList;
    EFI_HII_DATABASE_LIST_PACKS ListPackageLists;
    EFI_HII_DATABASE_EXPORT_PACKS ExportPackageLists;
    EFI_HII_DATABASE_REGISTER_NOTIFY RegisterPackageNotify;
    EFI_HII_DATABASE_UNREGISTER_NOTIFY UnregisterPackageNotify;
    EFI_HII_FIND_KEYBOARD_LAYOUTS FindKeyboardLayouts;
    EFI_HII_GET_KEYBOARD_LAYOUT GetKeyboardLayout;
    EFI_HII_SET_KEYBOARD_LAYOUT SetKeyboardLayout;
    EFI_HII_DATABASE_GET_PACK_HANDLE GetPackageListHandle;
};

#ifdef __cplusplus
}
#endif

#endif
