#ifndef EFI_EFIHIIPROT_H_
#define EFI_EFIHIIPROT_H_

#include "efihii.h"
#include "efiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HII_FONT_PROTOCOL_GUID \
    {0xe9ca4775, 0x8657, 0x47fc, {0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x8, 0x43, 0x24}}

typedef struct _EFI_HII_FONT_PROTOCOL EFI_HII_FONT_PROTOCOL;

typedef uint32_t EFI_HII_OUT_FLAGS;

#define EFI_HII_OUT_FLAG_CLIP 0x00000001
#define EFI_HII_OUT_FLAG_WRAP 0x00000002
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_Y 0x00000004
#define EFI_HII_OUT_FLAG_CLIP_CLEAN_X 0x00000008
#define EFI_HII_OUT_FLAG_TRANSPARENT 0x00000010
#define EFI_HII_IGNORE_IF_NO_GLYPH 0x00000020
#define EFI_HII_IGNORE_LINE_BREAK 0x00000040
#define EFI_HII_DIRECT_TO_SCREEN 0x00000080

typedef struct _EFI_HII_ROW_INFO {
    size_t StartIndex;
    size_t EndIndex;
    size_t LineHeight;
    size_t LineWidth;
    size_t BaselineOffset;
} EFI_HII_ROW_INFO;

/* FontName has one element, as firmware lays it out: EFI_FONT_DISPLAY_INFO embeds this. */
typedef struct {
    EFI_HII_FONT_STYLE FontStyle;
    uint16_t FontSize;
    uint16_t FontName[1];
} EFI_FONT_INFO;

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

typedef struct _EFI_FONT_DISPLAY_INFO {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL ForegroundColor;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackgroundColor;
    EFI_FONT_INFO_MASK FontInfoMask;
    EFI_FONT_INFO FontInfo;
} EFI_FONT_DISPLAY_INFO;

typedef struct _EFI_IMAGE_OUTPUT {
    uint16_t Width;
    uint16_t Height;
    union {
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Bitmap;
        EFI_GRAPHICS_OUTPUT_PROTOCOL *Screen;
    } Image;
} EFI_IMAGE_OUTPUT;

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_TO_IMAGE)(
    const EFI_HII_FONT_PROTOCOL *This,
    EFI_HII_OUT_FLAGS Flags,
    const EFI_STRING String,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY,
    EFI_HII_ROW_INFO **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_ID_TO_IMAGE)(
    const EFI_HII_FONT_PROTOCOL *This,
    EFI_HII_OUT_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY,
    EFI_HII_ROW_INFO **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH)(
    const EFI_HII_FONT_PROTOCOL *This,
    uint16_t Char,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t *Baseline
);

typedef void *EFI_FONT_HANDLE;

typedef EFI_STATUS (EFI_API *EFI_HII_GET_FONT_INFO)(
    const EFI_HII_FONT_PROTOCOL *This,
    EFI_FONT_HANDLE *FontHandle,
    const EFI_FONT_DISPLAY_INFO *StringInfoIn,
    EFI_FONT_DISPLAY_INFO **StringInfoOut,
    const EFI_STRING String
);

struct _EFI_HII_FONT_PROTOCOL {
    EFI_HII_STRING_TO_IMAGE StringToImage;
    EFI_HII_STRING_ID_TO_IMAGE StringIdToImage;
    EFI_HII_GET_GLYPH GetGlyph;
    EFI_HII_GET_FONT_INFO GetFontInfo;
};

#define EFI_HII_FONT_EX_PROTOCOL_GUID \
    {0x849e6875, 0xdb35, 0x4df8, {0xb4, 0x1e, 0xc8, 0xf3, 0x37, 0x18, 0x7, 0x3f}}

typedef struct _EFI_HII_FONT_EX_PROTOCOL EFI_HII_FONT_EX_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_TO_IMAGE_EX)(
    const EFI_HII_FONT_EX_PROTOCOL *This,
    EFI_HII_OUT_FLAGS Flags,
    const EFI_STRING String,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY,
    EFI_HII_ROW_INFO **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

typedef EFI_STATUS (EFI_API *EFI_HII_STRING_ID_TO_IMAGE_EX)(
    const EFI_HII_FONT_EX_PROTOCOL *This,
    EFI_HII_OUT_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY,
    EFI_HII_ROW_INFO **RowInfoArray,
    size_t *RowInfoArraySize,
    size_t *ColumnInfoArray
);

/* Baseline is printed by value, but the parameters are GetGlyph()'s, which returns it. */
typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH_EX)(
    const EFI_HII_FONT_EX_PROTOCOL *This,
    uint16_t Char,
    const EFI_FONT_DISPLAY_INFO *StringInfo,
    EFI_IMAGE_OUTPUT **Blt,
    size_t *Baseline
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_FONT_INFO_EX)(
    const EFI_HII_FONT_EX_PROTOCOL *This,
    EFI_FONT_HANDLE *FontHandle,
    const EFI_FONT_DISPLAY_INFO *StringInfoIn,
    EFI_FONT_DISPLAY_INFO **StringInfoOut,
    const EFI_STRING String
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_GLYPH_INFO)(
    const EFI_HII_FONT_EX_PROTOCOL *This,
    uint16_t Char,
    const EFI_FONT_DISPLAY_INFO *FontDisplayInfo,
    EFI_HII_GLYPH_INFO *GlyphInfo
);

struct _EFI_HII_FONT_EX_PROTOCOL {
    EFI_HII_STRING_TO_IMAGE_EX StringToImageEx;
    EFI_HII_STRING_ID_TO_IMAGE_EX StringIdToImageEx;
    EFI_HII_GET_GLYPH_EX GetGlyphEx;
    EFI_HII_GET_FONT_INFO_EX GetFontInfoEx;
    EFI_HII_GET_GLYPH_INFO GetGlyphInfo;
};

#define EFI_HII_STRING_PROTOCOL_GUID \
    {0xfd96974, 0x23aa, 0x4cdc, {0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}}

typedef struct _EFI_HII_STRING_PROTOCOL EFI_HII_STRING_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_STRING)(
    const EFI_HII_STRING_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID *StringId,
    const char *Language,
    const uint16_t *LanguageName,
    const EFI_STRING String,
    const EFI_FONT_INFO *StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_STRING)(
    const EFI_HII_STRING_PROTOCOL *This,
    const char *Language,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    EFI_STRING String,
    size_t *StringSize,
    EFI_FONT_INFO **StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_STRING)(
    const EFI_HII_STRING_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_STRING_ID StringId,
    const char *Language,
    const EFI_STRING String,
    const EFI_FONT_INFO *StringFontInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_LANGUAGES)(
    const EFI_HII_STRING_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    char *Languages,
    size_t *LanguagesSize
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_2ND_LANGUAGES)(
    const EFI_HII_STRING_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    const char *PrimaryLanguage,
    char *SecondaryLanguages,
    size_t *SecondaryLanguagesSize
);

struct _EFI_HII_STRING_PROTOCOL {
    EFI_HII_NEW_STRING NewString;
    EFI_HII_GET_STRING GetString;
    EFI_HII_SET_STRING SetString;
    EFI_HII_GET_LANGUAGES GetLanguages;
    EFI_HII_GET_2ND_LANGUAGES GetSecondaryLanguages;
};

#define EFI_HII_IMAGE_PROTOCOL_GUID \
    {0x31a6406a, 0x6bdf, 0x4e46, {0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x9, 0x20}}

typedef struct _EFI_HII_IMAGE_PROTOCOL EFI_HII_IMAGE_PROTOCOL;

typedef struct {
    uint32_t Flags;
    uint16_t Width;
    uint16_t Height;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *Bitmap;
} EFI_IMAGE_INPUT;

#define EFI_IMAGE_TRANSPARENT 0x00000001

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_IMAGE)(
    const EFI_HII_IMAGE_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID *ImageId,
    const EFI_IMAGE_INPUT *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE)(
    const EFI_HII_IMAGE_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    EFI_IMAGE_INPUT *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_IMAGE)(
    const EFI_HII_IMAGE_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    const EFI_IMAGE_INPUT *Image
);

typedef uint32_t EFI_HII_DRAW_FLAGS;

#define EFI_HII_DRAW_FLAG_CLIP 0x00000001
#define EFI_HII_DRAW_FLAG_TRANSPARENT 0x00000030
#define EFI_HII_DRAW_FLAG_DEFAULT 0x00000000
#define EFI_HII_DRAW_FLAG_FORCE_TRANS 0x00000010
#define EFI_HII_DRAW_FLAG_FORCE_OPAQUE 0x00000020

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE)(
    const EFI_HII_IMAGE_PROTOCOL *This,
    EFI_HII_DRAW_FLAGS Flags,
    const EFI_IMAGE_INPUT *Image,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_ID)(
    const EFI_HII_IMAGE_PROTOCOL *This,
    EFI_HII_DRAW_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY
);

struct _EFI_HII_IMAGE_PROTOCOL {
    EFI_HII_NEW_IMAGE NewImage;
    EFI_HII_GET_IMAGE GetImage;
    EFI_HII_SET_IMAGE SetImage;
    EFI_HII_DRAW_IMAGE DrawImage;
    EFI_HII_DRAW_IMAGE_ID DrawImageId;
};

#define EFI_HII_IMAGE_EX_PROTOCOL_GUID \
    {0x1a1241e6, 0x8f19, 0x41a9, {0xbc, 0xe, 0xe8, 0xef, 0x39, 0xe0, 0x65, 0x46}}

typedef struct _EFI_HII_IMAGE_EX_PROTOCOL EFI_HII_IMAGE_EX_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_NEW_IMAGE_EX)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID *ImageId,
    EFI_IMAGE_INPUT *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE_EX)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    EFI_IMAGE_INPUT *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_IMAGE_EX)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    const EFI_IMAGE_INPUT *Image
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_EX)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_DRAW_FLAGS Flags,
    const EFI_IMAGE_INPUT *Image,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_DRAW_IMAGE_ID_EX)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_DRAW_FLAGS Flags,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    EFI_IMAGE_OUTPUT **Blt,
    size_t BltX,
    size_t BltY
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_IMAGE_INFO)(
    const EFI_HII_IMAGE_EX_PROTOCOL *This,
    EFI_HII_HANDLE PackageList,
    EFI_IMAGE_ID ImageId,
    EFI_IMAGE_OUTPUT *Image
);

struct _EFI_HII_IMAGE_EX_PROTOCOL {
    EFI_HII_NEW_IMAGE_EX NewImageEx;
    EFI_HII_GET_IMAGE_EX GetImageEx;
    EFI_HII_SET_IMAGE_EX SetImageEx;
    EFI_HII_DRAW_IMAGE_EX DrawImageEx;
    EFI_HII_DRAW_IMAGE_ID_EX DrawImageIdEx;
    EFI_HII_GET_IMAGE_INFO GetImageInfo;
};

#define EFI_HII_IMAGE_DECODER_PROTOCOL_GUID \
    {0x9E66F251, 0x727C, 0x418C, {0xBF, 0xD6, 0xC2, 0xB4, 0x25, 0x28, 0x18, 0xEA}}

typedef struct _EFI_HII_IMAGE_DECODER_PROTOCOL EFI_HII_IMAGE_DECODER_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_GET_NAME)(
    const EFI_HII_IMAGE_DECODER_PROTOCOL *This,
    EFI_GUID **DecoderName,
    uint16_t *NumberOfDecoderName
);

#define EFI_HII_IMAGE_DECODER_NAME_JPEG_GUID \
    {0xefefd093, 0xd9b, 0x46eb, {0xa8, 0x56, 0x48, 0x35, 0x7, 0x0, 0xc9, 0x8}}

#define EFI_HII_IMAGE_DECODER_NAME_PNG_GUID \
    {0xaf060190, 0x5e3a, 0x4025, {0xaf, 0xbd, 0xe1, 0xf9, 0x5, 0xbf, 0xaa, 0x4c}}

typedef enum {
    EFI_HII_IMAGE_DECODER_COLOR_TYPE_RGB = 0,
    EFI_HII_IMAGE_DECODER_COLOR_TYPE_RGBA = 1,
    EFI_HII_IMAGE_DECODER_COLOR_TYPE_CMYK = 2,
    EFI_HII_IMAGE_DECODER_COLOR_TYPE_UNKNOWN = 0xff
} EFI_HII_IMAGE_DECODER_COLOR_TYPE;

typedef struct _EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER {
    EFI_GUID DecoderName;
    uint16_t ImageInfoSize;
    uint16_t ImageWidth;
    uint16_t ImageHeight;
    EFI_HII_IMAGE_DECODER_COLOR_TYPE ColorType;
    uint8_t ColorDepthInBits;
} EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER;

typedef struct _EFI_HII_IMAGE_DECODER_JPEG_INFO {
    EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER Header;
    uint16_t ScanType;
    uint64_t Reserved;
} EFI_HII_IMAGE_DECODER_JPEG_INFO;

#define EFI_IMAGE_JPEG_SCANTYPE_PROGREESSIVE 0x01
#define EFI_IMAGE_JPEG_SCANTYPE_INTERLACED 0x02

typedef struct _EFI_HII_IMAGE_DECODER_PNG_INFO {
    EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER Header;
    uint16_t Channels;
    uint64_t Reserved;
} EFI_HII_IMAGE_DECODER_PNG_INFO;

typedef struct _EFI_HII_IMAGE_DECODER_OTHER_INFO {
    EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER Header;
    uint16_t ImageExtenion[1];
} EFI_HII_IMAGE_DECODER_OTHER_INFO;

/*
 * ImageInfo is printed as EFI_HII_IMAGE_DECODER_IMAGE_INFO, which is defined nowhere; every image
 * information structure starts with EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER.
 */
typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_GET_IMAGE_INFO)(
    const EFI_HII_IMAGE_DECODER_PROTOCOL *This,
    void *Image,
    size_t SizeOfImage,
    EFI_HII_IMAGE_DECODER_IMAGE_INFO_HEADER **ImageInfo
);

typedef EFI_STATUS (EFI_API *EFI_HII_IMAGE_DECODER_DECODE)(
    const EFI_HII_IMAGE_DECODER_PROTOCOL *This,
    void *Image,
    size_t ImageRawDataSize,
    EFI_IMAGE_OUTPUT **Bitmap,
    bool Transparent
);

struct _EFI_HII_IMAGE_DECODER_PROTOCOL {
    EFI_HII_IMAGE_DECODER_GET_NAME GetImageDecoderName;
    EFI_HII_IMAGE_DECODER_GET_IMAGE_INFO GetImageInfo;
    EFI_HII_IMAGE_DECODER_DECODE DecodeImage;
};

#define EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL_GUID \
    {0xf7102853, 0x7787, 0x4dc2, {0xa8, 0xa8, 0x21, 0xb5, 0xdd, 0x5, 0xc8, 0x9b}}

typedef struct _EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_GENERATE_GLYPH)(
    const EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL *This,
    uint16_t Char,
    const EFI_FONT_DISPLAY_INFO *FontInfo,
    EFI_HII_GIBT_VARIABILITY_BLOCK *GlyphBlock
);

typedef EFI_STATUS (EFI_API *EFI_HII_GENERATE_GLYPH_IMAGE)(
    const EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL *This,
    const EFI_HII_GLYPH_INFO *Cell,
    uint8_t *GlyphBuffer,
    const EFI_FONT_DISPLAY_INFO *FontInfo,
    EFI_IMAGE_OUTPUT *Image,
    int32_t *BltX,
    int32_t *BltY,
    bool Transparent
);

/* The member types are printed EFI_GENERATE_GLYPH and EFI_GENERATE_IMAGE, defined nowhere. */
struct _EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL {
    EFI_HII_GENERATE_GLYPH GenerateGlyph;
    EFI_HII_GENERATE_GLYPH_IMAGE GenerateGlyphImage;
};

#define EFI_HII_DATABASE_PROTOCOL_GUID \
    {0xef9fc172, 0xa1b2, 0x4693, {0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}}

typedef struct _EFI_HII_DATABASE_PROTOCOL EFI_HII_DATABASE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_NEW_PACK)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    const EFI_HII_PACKAGE_LIST_HEADER *PackageList,
    const EFI_HANDLE DriverHandle,
    EFI_HII_HANDLE *Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_REMOVE_PACK)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_HII_HANDLE Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_UPDATE_PACK)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_HII_HANDLE Handle,
    const EFI_HII_PACKAGE_LIST_HEADER *PackageList
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_LIST_PACKS)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    uint8_t PackageType,
    const EFI_GUID *PackageGuid,
    size_t *HandleBufferLength,
    EFI_HII_HANDLE *Handle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_EXPORT_PACKS)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_HII_HANDLE Handle,
    size_t *BufferSize,
    EFI_HII_PACKAGE_LIST_HEADER *Buffer
);

typedef uintptr_t EFI_HII_DATABASE_NOTIFY_TYPE;

#define EFI_HII_DATABASE_NOTIFY_NEW_PACK 0x00000001
#define EFI_HII_DATABASE_NOTIFY_REMOVE_PACK 0x00000002
#define EFI_HII_DATABASE_NOTIFY_EXPORT_PACK 0x00000004
#define EFI_HII_DATABASE_NOTIFY_ADD_PACK 0x00000008

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_NOTIFY)(
    uint8_t PackageType,
    const EFI_GUID *PackageGuid,
    const EFI_HII_PACKAGE_HEADER *Package,
    EFI_HII_HANDLE Handle,
    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_REGISTER_NOTIFY)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    uint8_t PackageType,
    const EFI_GUID *PackageGuid,
    const EFI_HII_DATABASE_NOTIFY PackageNotifyFn,
    EFI_HII_DATABASE_NOTIFY_TYPE NotifyType,
    EFI_HANDLE *NotifyHandle
);

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_UNREGISTER_NOTIFY)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_HANDLE NotificationHandle
);

typedef EFI_STATUS (EFI_API *EFI_HII_FIND_KEYBOARD_LAYOUTS)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    uint16_t *KeyGuidBufferLength,
    EFI_GUID *KeyGuidBuffer
);

typedef enum {
    EfiKeyLCtrl,
    EfiKeyA0,
    EfiKeyLAlt,
    EfiKeySpaceBar,
    EfiKeyA2,
    EfiKeyA3,
    EfiKeyA4,
    EfiKeyRCtrl,
    EfiKeyLeftArrow,
    EfiKeyDownArrow,
    EfiKeyRightArrow,
    EfiKeyZero,
    EfiKeyPeriod,
    EfiKeyEnter,
    EfiKeyLShift,
    EfiKeyB0,
    EfiKeyB1,
    EfiKeyB2,
    EfiKeyB3,
    EfiKeyB4,
    EfiKeyB5,
    EfiKeyB6,
    EfiKeyB7,
    EfiKeyB8,
    EfiKeyB9,
    EfiKeyB10,
    EfiKeyRShift,
    EfiKeyUpArrow,
    EfiKeyOne,
    EfiKeyTwo,
    EfiKeyThree,
    EfiKeyCapsLock,
    EfiKeyC1,
    EfiKeyC2,
    EfiKeyC3,
    EfiKeyC4,
    EfiKeyC5,
    EfiKeyC6,
    EfiKeyC7,
    EfiKeyC8,
    EfiKeyC9,
    EfiKeyC10,
    EfiKeyC11,
    EfiKeyC12,
    EfiKeyFour,
    EfiKeyFive,
    EfiKeySix,
    EfiKeyPlus,
    EfiKeyTab,
    EfiKeyD1,
    EfiKeyD2,
    EfiKeyD3,
    EfiKeyD4,
    EfiKeyD5,
    EfiKeyD6,
    EfiKeyD7,
    EfiKeyD8,
    EfiKeyD9,
    EfiKeyD10,
    EfiKeyD11,
    EfiKeyD12,
    EfiKeyD13,
    EfiKeyDel,
    EfiKeyEnd,
    EfiKeyPgDn,
    EfiKeySeven,
    EfiKeyEight,
    EfiKeyNine,
    EfiKeyE0,
    EfiKeyE1,
    EfiKeyE2,
    EfiKeyE3,
    EfiKeyE4,
    EfiKeyE5,
    EfiKeyE6,
    EfiKeyE7,
    EfiKeyE8,
    EfiKeyE9,
    EfiKeyE10,
    EfiKeyE11,
    EfiKeyE12,
    EfiKeyBackSpace,
    EfiKeyIns,
    EfiKeyHome,
    EfiKeyPgUp,
    EfiKeyNLck,
    EfiKeySlash,
    EfiKeyAsterisk,
    EfiKeyMinus,
    EfiKeyEsc,
    EfiKeyF1,
    EfiKeyF2,
    EfiKeyF3,
    EfiKeyF4,
    EfiKeyF5,
    EfiKeyF6,
    EfiKeyF7,
    EfiKeyF8,
    EfiKeyF9,
    EfiKeyF10,
    EfiKeyF11,
    EfiKeyF12,
    EfiKeyPrint,
    EfiKeySLck,
    EfiKeyPause,
    EfiKeyIntl0,
    EfiKeyIntl1,
    EfiKeyIntl2,
    EfiKeyIntl3,
    EfiKeyIntl4,
    EfiKeyIntl5,
    EfiKeyIntl6,
    EfiKeyIntl7,
    EfiKeyIntl8,
    EfiKeyIntl9
} EFI_KEY;

typedef struct __attribute__((__packed__)) {
    EFI_KEY Key;
    uint16_t Unicode;
    uint16_t ShiftedUnicode;
    uint16_t AltGrUnicode;
    uint16_t ShiftedAltGrUnicode;
    uint16_t Modifier;
    uint16_t AffectedAttribute;
} EFI_KEY_DESCRIPTOR;

#define EFI_AFFECTED_BY_STANDARD_SHIFT 0x0001
#define EFI_AFFECTED_BY_CAPS_LOCK 0x0002
#define EFI_AFFECTED_BY_NUM_LOCK 0x0004

/* __extension__: a flexible array member is standard C but an extension in C++. */
__extension__ typedef struct __attribute__((__packed__)) {
    uint16_t LayoutLength;
    EFI_GUID Guid;
    uint32_t LayoutDescriptorStringOffset;
    uint8_t DescriptorCount;
    EFI_KEY_DESCRIPTOR Descriptors[];
} EFI_HII_KEYBOARD_LAYOUT;

/* The fixed part: each EFI_DESCRIPTION_STRING that follows starts with a variable-length array. */
typedef struct __attribute__((__packed__)) {
    uint16_t DescriptionCount;
} EFI_DESCRIPTION_STRING_BUNDLE;

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
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_GUID *KeyGuid,
    uint16_t *KeyboardLayoutLength,
    EFI_HII_KEYBOARD_LAYOUT *KeyboardLayout
);

typedef EFI_STATUS (EFI_API *EFI_HII_SET_KEYBOARD_LAYOUT)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_GUID *KeyGuid
);

#define EFI_HII_SET_KEYBOARD_LAYOUT_EVENT_GUID \
    {0x14982a4f, 0xb0ed, 0x45b8, {0xa8, 0x11, 0x5a, 0x7a, 0x9b, 0xc2, 0x32, 0xdf}}

typedef EFI_STATUS (EFI_API *EFI_HII_DATABASE_GET_PACK_HANDLE)(
    const EFI_HII_DATABASE_PROTOCOL *This,
    EFI_HII_HANDLE PackageListHandle,
    EFI_HANDLE *DriverHandle
);

struct _EFI_HII_DATABASE_PROTOCOL {
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
