#ifndef EFI_EFIHII_H_
#define EFI_EFIHII_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef EFI_VOID *EFI_HII_HANDLE;

typedef EFI_CHAR16 *EFI_STRING;

typedef EFI_UINT16 EFI_QUESTION_ID;
typedef EFI_UINT16 EFI_IMAGE_ID;
typedef EFI_UINT16 EFI_STRING_ID;
typedef EFI_UINT16 EFI_FORM_ID;
typedef EFI_UINT16 EFI_VARSTORE_ID;
typedef EFI_UINT16 EFI_ANIMATION_ID;
typedef EFI_UINT16 EFI_DEFAULT_ID;

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
typedef struct __attribute__((__packed__)) {
    EFI_UINT32 Length:24;
    EFI_UINT32 Type:8;
} EFI_HII_PACKAGE_HEADER;

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

typedef struct __attribute__((__packed__)) {
    EFI_GUID PackageListGuid;
    EFI_UINT32 PackageLength;
} EFI_HII_PACKAGE_LIST_HEADER;

typedef EFI_HII_PACKAGE_LIST_HEADER *EFI_HII_PACKAGE_LIST_PROTOCOL;

#define EFI_GLYPH_NON_SPACING 0x01
#define EFI_GLYPH_WIDE 0x02
#define EFI_GLYPH_HEIGHT 19
#define EFI_GLYPH_WIDTH 8

typedef struct __attribute__((__packed__)) {
    EFI_CHAR16 UnicodeWeight;
    EFI_UINT8 Attributes;
    EFI_UINT8 GlyphCol1[EFI_GLYPH_HEIGHT];
} EFI_NARROW_GLYPH;

typedef struct __attribute__((__packed__)) {
    EFI_CHAR16 UnicodeWeight;
    EFI_UINT8 Attributes;
    EFI_UINT8 GlyphCol1[EFI_GLYPH_HEIGHT];
    EFI_UINT8 GlyphCol2[EFI_GLYPH_HEIGHT];
    EFI_UINT8 Pad[3];
} EFI_WIDE_GLYPH;

/*
 * __extension__ on structures ending in a flexible array member: standard C, an extension in C++.
 * The EFI_WIDE_GLYPH WideGlyphs[] follow the narrow glyphs.
 */
__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIMPLE_FONT_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT16 NumberOfNarrowGlyphs;
    EFI_UINT16 NumberOfWideGlyphs;
    EFI_NARROW_GLYPH NarrowGlyphs[];
} EFI_HII_SIMPLE_FONT_PACKAGE_HDR;

typedef EFI_UINT32 EFI_HII_FONT_STYLE;

#define EFI_HII_FONT_STYLE_NORMAL 0x00000000
#define EFI_HII_FONT_STYLE_BOLD 0x00000001
#define EFI_HII_FONT_STYLE_ITALIC 0x00000002
#define EFI_HII_FONT_STYLE_EMBOSS 0x00010000
#define EFI_HII_FONT_STYLE_OUTLINE 0x00020000
#define EFI_HII_FONT_STYLE_SHADOW 0x00040000
#define EFI_HII_FONT_STYLE_UNDERLINE 0x00080000
#define EFI_HII_FONT_STYLE_DBL_UNDER 0x00100000

typedef struct __attribute__((__packed__)) _EFI_HII_GLYPH_INFO {
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_INT16 OffsetX;
    EFI_INT16 OffsetY;
    EFI_INT16 AdvanceX;
} EFI_HII_GLYPH_INFO;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_FONT_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT32 HdrSize;
    EFI_UINT32 GlyphBlockOffset;
    EFI_HII_GLYPH_INFO Cell;
    EFI_HII_FONT_STYLE FontStyle;
    EFI_CHAR16 FontFamily[];
} EFI_HII_FONT_PACKAGE_HDR;

/* The block body (BlockBody[]) follows: each glyph block starts with this header. */
typedef struct __attribute__((__packed__)) _EFI_HII_GLYPH_BLOCK {
    EFI_UINT8 BlockType;
} EFI_HII_GLYPH_BLOCK;

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

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_DEFAULTS_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_HII_GLYPH_INFO Cell;
} EFI_HII_GIBT_DEFAULTS_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_DUPLICATE_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_CHAR16 CharValue;
} EFI_HII_GIBT_DUPLICATE_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_GLYPH_GIBT_END_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
} EFI_GLYPH_GIBT_END_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_EXT1_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT8 Length;
} EFI_HII_GIBT_EXT1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_EXT2_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT16 Length;
} EFI_HII_GIBT_EXT2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_EXT4_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT32 Length;
} EFI_HII_GIBT_EXT4_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_GLYPH_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_HII_GLYPH_INFO Cell;
    EFI_UINT8 BitmapData[1];
} EFI_HII_GIBT_GLYPH_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_GLYPHS_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_HII_GLYPH_INFO Cell;
    EFI_UINT16 Count;
    EFI_UINT8 BitmapData[1];
} EFI_HII_GIBT_GLYPHS_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_GLYPH_DEFAULT_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT8 BitmapData[];
} EFI_HII_GIBT_GLYPH_DEFAULT_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT16 Count;
    EFI_UINT8 BitmapData[];
} EFI_HII_GIBT_GLYPHS_DEFAULT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_SKIP2_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT16 SkipCount;
} EFI_HII_GIBT_SKIP2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_SKIP1_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_UINT8 SkipCount;
} EFI_HII_GIBT_SKIP1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_GIBT_VARIABILITY_BLOCK {
    EFI_HII_GLYPH_BLOCK Header;
    EFI_HII_GLYPH_INFO Cell;
    EFI_UINT8 GlyphPackInBits;
    EFI_UINT8 BitmapData[1];
} EFI_HII_GIBT_VARIABILITY_BLOCK;

/* Named without values: GlyphPackInBits is the number of bits per pixel. */
#define EFI_GIBT_VARIABILITY_BLOCK_1_BIT 1
#define EFI_GIBT_VARIABILITY_BLOCK_2_BIT 2
#define EFI_GIBT_VARIABILITY_BLOCK_4_BIT 4
#define EFI_GIBT_VARIABILITY_BLOCK_8_BIT 8
#define EFI_GIBT_VARIABILITY_BLOCK_16_BIT 16
#define EFI_GIBT_VARIABILITY_BLOCK_24_BIT 24
#define EFI_GIBT_VARIABILITY_BLOCK_32_BIT 32

/* EFI_DEVICE_PATH_PROTOCOL DevicePath[] follows (printed commented out). */
typedef struct __attribute__((__packed__)) _EFI_HII_DEVICE_PATH_PACKAGE {
    EFI_HII_PACKAGE_HEADER Header;
} EFI_HII_DEVICE_PATH_PACKAGE;

typedef struct __attribute__((__packed__)) _EFI_HII_GUID_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_GUID Guid;
} EFI_HII_GUID_PACKAGE_HDR;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_STRING_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT32 HdrSize;
    EFI_UINT32 StringInfoOffset;
    EFI_CHAR16 LanguageWindow[16];
    EFI_STRING_ID LanguageName;
    EFI_CHAR8 Language[];
} EFI_HII_STRING_PACKAGE_HDR;

#define EFI_UEFI_CONFIG_LANG "x-UEFI"
#define EFI_UEFI_CONFIG_LANG_2 "x-i-UEFI"

/* The block body (BlockBody[]) follows: each string block starts with this header. */
typedef struct __attribute__((__packed__)) {
    EFI_UINT8 BlockType;
} EFI_HII_STRING_BLOCK;

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

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_DUPLICATE_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_STRING_ID StringId;
} EFI_HII_SIBT_DUPLICATE_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_END_BLOCK {
    EFI_HII_STRING_BLOCK Header;
} EFI_HII_SIBT_END_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_EXT1_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT8 Length;
} EFI_HII_SIBT_EXT1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_EXT2_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT16 Length;
} EFI_HII_SIBT_EXT2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_EXT4_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT32 Length;
} EFI_HII_SIBT_EXT4_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_FONT_BLOCK {
    EFI_HII_SIBT_EXT2_BLOCK Header;
    EFI_UINT8 FontId;
    EFI_UINT16 FontSize;
    EFI_HII_FONT_STYLE FontStyle;
    EFI_CHAR16 FontName[];
} EFI_HII_SIBT_FONT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_SKIP1_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 SkipCount;
} EFI_HII_SIBT_SKIP1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_SKIP2_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT16 SkipCount;
} EFI_HII_SIBT_SKIP2_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRING_SCSU_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 StringText[];
} EFI_HII_SIBT_STRING_SCSU_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 FontIdentifier;
    EFI_UINT8 StringText[];
} EFI_HII_SIBT_STRING_SCSU_FONT_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRINGS_SCSU_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT16 StringCount;
    EFI_UINT8 StringText[];
} EFI_HII_SIBT_STRINGS_SCSU_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 FontIdentifier;
    EFI_UINT16 StringCount;
    EFI_UINT8 StringText[];
} EFI_HII_SIBT_STRINGS_SCSU_FONT_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRING_UCS2_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_CHAR16 StringText[];
} EFI_HII_SIBT_STRING_UCS2_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 FontIdentifier;
    EFI_CHAR16 StringText[];
} EFI_HII_SIBT_STRING_UCS2_FONT_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRINGS_UCS2_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT16 StringCount;
    EFI_CHAR16 StringText[];
} EFI_HII_SIBT_STRINGS_UCS2_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK {
    EFI_HII_STRING_BLOCK Header;
    EFI_UINT8 FontIdentifier;
    EFI_UINT16 StringCount;
    EFI_CHAR16 StringText[];
} EFI_HII_SIBT_STRINGS_UCS2_FONT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IMAGE_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT32 ImageInfoOffset;
    EFI_UINT32 PaletteInfoOffset;
} EFI_HII_IMAGE_PACKAGE_HDR;

/* The block body (BlockBody[]) follows: each image block starts with this header. */
typedef struct __attribute__((__packed__)) _EFI_HII_IMAGE_BLOCK {
    EFI_UINT8 BlockType;
} EFI_HII_IMAGE_BLOCK;

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

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_END_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
} EFI_HII_IIBT_END_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_EXT1_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT8 Length;
} EFI_HII_IIBT_EXT1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_EXT2_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT16 Length;
} EFI_HII_IIBT_EXT2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_EXT4_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT32 Length;
} EFI_HII_IIBT_EXT4_BLOCK;

/* The image bases end in a one-element array, as firmware lays them out: the blocks embed them. */
typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_1BIT_BASE {
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT8 Data[1];
} EFI_HII_IIBT_IMAGE_1BIT_BASE;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_1BIT_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_1BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_1BIT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_1BIT_TRANS_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_1BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_1BIT_TRANS_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_RGB_PIXEL {
    EFI_UINT8 b;
    EFI_UINT8 g;
    EFI_UINT8 r;
} EFI_HII_RGB_PIXEL;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_24BIT_BASE {
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_HII_RGB_PIXEL Bitmap[1];
} EFI_HII_IIBT_IMAGE_24BIT_BASE;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_24BIT_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_HII_IIBT_IMAGE_24BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_24BIT_BLOCK;

typedef struct __attribute__((__packed__)) EFI_HII_IIBT_IMAGE_24BIT_TRANS_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_HII_IIBT_IMAGE_24BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_24BIT_TRANS_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_4BIT_BASE {
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT8 Data[1];
} EFI_HII_IIBT_IMAGE_4BIT_BASE;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_4BIT_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_4BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_4BIT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_4BIT_TRANS_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_4BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_4BIT_TRANS_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_8BIT_BASE {
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT8 Data[1];
} EFI_HII_IIBT_IMAGE_8BIT_BASE;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_8BIT_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_8BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_8BIT_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_IMAGE_8BIT_TRANS_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 PaletteIndex;
    EFI_HII_IIBT_IMAGE_8BIT_BASE Bitmap;
} EFI_HII_IIBT_IMAGE_8BIT_TRANS_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_DUPLICATE_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_IMAGE_ID ImageId;
} EFI_HII_IIBT_DUPLICATE_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_JPEG_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT32 Size;
    EFI_UINT8 Data[];
} EFI_HII_IIBT_JPEG_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_SKIP1_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT8 SkipCount;
} EFI_HII_IIBT_SKIP1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_SKIP2_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT16 SkipCount;
} EFI_HII_IIBT_SKIP2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IIBT_PNG_BLOCK {
    EFI_HII_IMAGE_BLOCK Header;
    EFI_UINT32 Size;
    EFI_UINT8 Data[1];
} EFI_HII_IIBT_PNG_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_IMAGE_PALETTE_INFO_HEADER {
    EFI_UINT16 PaletteCount;
} EFI_HII_IMAGE_PALETTE_INFO_HEADER;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_IMAGE_PALETTE_INFO {
    EFI_UINT16 PaletteSize;
    EFI_HII_RGB_PIXEL PaletteValue[];
} EFI_HII_IMAGE_PALETTE_INFO;

/* The op-codes follow the package header (printed commented out as OpCodeHeader). */
typedef struct __attribute__((__packed__)) _EFI_HII_FORM_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
} EFI_HII_FORM_PACKAGE_HDR;

typedef struct __attribute__((__packed__)) _EFI_IFR_OP_HEADER {
    EFI_UINT8 OpCode;
    EFI_UINT8 Length:7;
    EFI_UINT8 Scope:1;
} EFI_IFR_OP_HEADER;

typedef struct __attribute__((__packed__)) _EFI_IFR_STATEMENT_HEADER {
    EFI_STRING_ID Prompt;
    EFI_STRING_ID Help;
} EFI_IFR_STATEMENT_HEADER;

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_HEADER {
    EFI_IFR_STATEMENT_HEADER Header;
    EFI_QUESTION_ID QuestionId;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        EFI_UINT16 VarOffset;
    } VarStoreInfo;
    EFI_UINT8 Flags;
} EFI_IFR_QUESTION_HEADER;

#define EFI_IFR_FLAG_READ_ONLY 0x01
#define EFI_IFR_FLAG_CALLBACK 0x04
#define EFI_IFR_FLAG_RESET_REQUIRED 0x10
#define EFI_IFR_FLAG_REST_STYLE 0x20
#define EFI_IFR_FLAG_RECONNECT_REQUIRED 0x40
#define EFI_IFR_FLAG_OPTIONS_ONLY 0x80

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Hour;
    EFI_UINT8 Minute;
    EFI_UINT8 Second;
} EFI_HII_TIME;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 Year;
    EFI_UINT8 Month;
    EFI_UINT8 Day;
} EFI_HII_DATE;

typedef struct __attribute__((__packed__)) {
    EFI_QUESTION_ID QuestionId;
    EFI_FORM_ID FormId;
    EFI_GUID FormSetGuid;
    EFI_STRING_ID DevicePath;
} EFI_HII_REF;

/* An EFI_IFR_TYPE_BUFFER value is a byte array (buffer[], printed commented out). */
typedef union __attribute__((__packed__)) {
    EFI_UINT8 u8;
    EFI_UINT16 u16;
    EFI_UINT32 u32;
    EFI_UINT64 u64;
    EFI_BOOLEAN b;
    EFI_HII_TIME time;
    EFI_HII_DATE date;
    EFI_STRING_ID string;
    EFI_HII_REF ref;
} EFI_IFR_TYPE_VALUE;

/* Printed inline in EFI_IFR_NUMERIC and EFI_IFR_ONE_OF; named at file scope for both. */
typedef union __attribute__((__packed__)) {
    struct __attribute__((__packed__)) {
        EFI_UINT8 MinValue;
        EFI_UINT8 MaxValue;
        EFI_UINT8 Step;
    } u8;
    struct __attribute__((__packed__)) {
        EFI_UINT16 MinValue;
        EFI_UINT16 MaxValue;
        EFI_UINT16 Step;
    } u16;
    struct __attribute__((__packed__)) {
        EFI_UINT32 MinValue;
        EFI_UINT32 MaxValue;
        EFI_UINT32 Step;
    } u32;
    struct __attribute__((__packed__)) {
        EFI_UINT64 MinValue;
        EFI_UINT64 MaxValue;
        EFI_UINT64 Step;
    } u64;
} EFI_MINMAXSTEP_DATA;

#define EFI_IFR_ACTION_OP 0x0C

typedef struct __attribute__((__packed__)) _EFI_IFR_ACTION {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_STRING_ID QuestionConfig;
} EFI_IFR_ACTION;

typedef struct __attribute__((__packed__)) _EFI_IFR_ACTION_1 {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
} EFI_IFR_ACTION_1;

#define EFI_IFR_ANIMATION_OP 0x1F

typedef struct __attribute__((__packed__)) _EFI_IFR_ANIMATION {
    EFI_IFR_OP_HEADER Header;
    EFI_ANIMATION_ID Id;
} EFI_IFR_ANIMATION;

#define EFI_IFR_ADD_OP 0x3a

typedef struct __attribute__((__packed__)) _EFI_IFR_ADD {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_ADD;

#define EFI_IFR_AND_OP 0x15

typedef struct __attribute__((__packed__)) _EFI_IFR_AND {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_AND;

#define EFI_IFR_BITWISE_AND_OP 0x35

typedef struct __attribute__((__packed__)) _EFI_IFR_BITWISE_AND {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_BITWISE_AND;

#define EFI_IFR_BITWISE_NOT_OP 0x37

typedef struct __attribute__((__packed__)) _EFI_IFR_BITWISE_NOT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_BITWISE_NOT;

#define EFI_IFR_BITWISE_OR_OP 0x36

typedef struct __attribute__((__packed__)) _EFI_IFR_BITWISE_OR {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_BITWISE_OR;

#define EFI_IFR_CATENATE_OP 0x5e

typedef struct __attribute__((__packed__)) _EFI_IFR_CATENATE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_CATENATE;

#define EFI_IFR_CHECKBOX_OP 0x06

typedef struct __attribute__((__packed__)) _EFI_IFR_CHECKBOX {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 Flags;
} EFI_IFR_CHECKBOX;

#define EFI_IFR_CHECKBOX_DEFAULT 0x01
#define EFI_IFR_CHECKBOX_DEFAULT_MFG 0x02

#define EFI_IFR_CONDITIONAL_OP 0x50

typedef struct __attribute__((__packed__)) _EFI_IFR_CONDITIONAL {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_CONDITIONAL;

#define EFI_IFR_DATE_OP 0x1A

typedef struct __attribute__((__packed__)) _EFI_IFR_DATE {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 Flags;
} EFI_IFR_DATE;

#define EFI_QF_DATE_YEAR_SUPPRESS 0x01
#define EFI_QF_DATE_MONTH_SUPPRESS 0x02
#define EFI_QF_DATE_DAY_SUPPRESS 0x04
#define EFI_QF_DATE_STORAGE 0x30

#define EFI_QF_DATE_STORAGE_NORMAL 0x00
#define EFI_QF_DATE_STORAGE_TIME 0x10
#define EFI_QF_DATE_STORAGE_WAKEUP 0x20

#define EFI_IFR_DEFAULT_OP 0x5b

typedef struct __attribute__((__packed__)) _EFI_IFR_DEFAULT {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT16 DefaultId;
    EFI_UINT8 Type;
    EFI_IFR_TYPE_VALUE Value;
} EFI_IFR_DEFAULT;

typedef struct __attribute__((__packed__)) _EFI_IFR_DEFAULT_2 {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT16 DefaultId;
    EFI_UINT8 Type;
} EFI_IFR_DEFAULT_2;

#define EFI_IFR_DEFAULTSTORE_OP 0x5c

typedef struct __attribute__((__packed__)) _EFI_IFR_DEFAULTSTORE {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID DefaultName;
    EFI_UINT16 DefaultId;
} EFI_IFR_DEFAULTSTORE;

#define EFI_IFR_DISABLE_IF_OP 0x1e

typedef struct __attribute__((__packed__)) _EFI_IFR_DISABLE_IF {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_DISABLE_IF;

#define EFI_IFR_DIVIDE_OP 0x3d

typedef struct __attribute__((__packed__)) _EFI_IFR_DIVIDE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_DIVIDE;

#define EFI_IFR_DUP_OP 0x57

typedef struct __attribute__((__packed__)) _EFI_IFR_DUP {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_DUP;

#define EFI_IFR_END_OP 0x29

typedef struct __attribute__((__packed__)) _EFI_IFR_END {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_END;

#define EFI_IFR_EQUAL_OP 0x2f

typedef struct __attribute__((__packed__)) _EFI_IFR_EQUAL {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_EQUAL;

#define EFI_IFR_EQ_ID_ID_OP 0x13

typedef struct __attribute__((__packed__)) _EFI_IFR_EQ_ID_ID {
    EFI_IFR_OP_HEADER Header;
    EFI_QUESTION_ID QuestionId1;
    EFI_QUESTION_ID QuestionId2;
} EFI_IFR_EQ_ID_ID;

#define EFI_IFR_EQ_ID_VAL_LIST_OP 0x14

typedef struct __attribute__((__packed__)) _EFI_IFR_EQ_ID_VAL_LIST {
    EFI_IFR_OP_HEADER Header;
    EFI_QUESTION_ID QuestionId;
    EFI_UINT16 ListLength;
    EFI_UINT16 ValueList[1];
} EFI_IFR_EQ_ID_VAL_LIST;

#define EFI_IFR_EQ_ID_VAL_OP 0x12

typedef struct __attribute__((__packed__)) _EFI_IFR_EQ_ID_VAL {
    EFI_IFR_OP_HEADER Header;
    EFI_QUESTION_ID QuestionId;
    EFI_UINT16 Value;
} EFI_IFR_EQ_ID_VAL;

#define EFI_IFR_FALSE_OP 0x47

typedef struct __attribute__((__packed__)) _EFI_IFR_FALSE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_FALSE;

#define EFI_IFR_FIND_OP 0x4c

typedef struct __attribute__((__packed__)) _EFI_IFR_FIND {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 Format;
} EFI_IFR_FIND;

#define EFI_IFR_FF_CASE_SENSITIVE 0x00
#define EFI_IFR_FF_CASE_INSENSITIVE 0x01

#define EFI_IFR_FORM_OP 0x01

typedef struct __attribute__((__packed__)) _EFI_IFR_FORM {
    EFI_IFR_OP_HEADER Header;
    EFI_FORM_ID FormId;
    EFI_STRING_ID FormTitle;
} EFI_IFR_FORM;

#define EFI_IFR_FORM_MAP_OP 0x5D

typedef struct __attribute__((__packed__)) _EFI_IFR_FORM_MAP_METHOD {
    EFI_STRING_ID MethodTitle;
    EFI_GUID MethodIdentifier;
} EFI_IFR_FORM_MAP_METHOD;

/* EFI_IFR_FORM_MAP_METHOD Methods[] follows (printed commented out). */
typedef struct __attribute__((__packed__)) _EFI_IFR_FORM_MAP {
    EFI_IFR_OP_HEADER Header;
    EFI_FORM_ID FormId;
} EFI_IFR_FORM_MAP;

#define EFI_HII_STANDARD_FORM_GUID \
    {0x3bd2f4ec, 0xe524, 0x46e4, {0xa9, 0xd8, 0x51, 0x01, 0x17, 0x42, 0x55, 0x62}}

#define EFI_IFR_FORM_SET_OP 0x0E

/* Flags bits 0:1 count the EFI_GUID ClassGuid[] that follows (printed commented out). */
typedef struct __attribute__((__packed__)) _EFI_IFR_FORM_SET {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID Guid;
    EFI_STRING_ID FormSetTitle;
    EFI_STRING_ID Help;
    EFI_UINT8 Flags;
} EFI_IFR_FORM_SET;

#define EFI_IFR_GET_OP 0x2B

typedef struct __attribute__((__packed__)) _EFI_IFR_GET {
    EFI_IFR_OP_HEADER Header;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        EFI_UINT16 VarOffset;
    } VarStoreInfo;
    EFI_UINT8 VarStoreType;
} EFI_IFR_GET;

#define EFI_IFR_GRAY_OUT_IF_OP 0x19

typedef struct __attribute__((__packed__)) _EFI_IFR_GRAY_OUT_IF {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_GRAY_OUT_IF;

#define EFI_IFR_GREATER_EQUAL_OP 0x32

typedef struct __attribute__((__packed__)) _EFI_IFR_GREATER_EQUAL {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_GREATER_EQUAL;

#define EFI_IFR_GREATER_THAN_OP 0x31

typedef struct __attribute__((__packed__)) _EFI_IFR_GREATER_THAN {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_GREATER_THAN;

#define EFI_IFR_GUID_OP 0x5F

typedef struct __attribute__((__packed__)) _EFI_IFR_GUID {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID Guid;
} EFI_IFR_GUID;

#define EFI_IFR_IMAGE_OP 0x04

/* The printed structure lost the EFI_IFR_OP_HEADER that every op-code starts with. */
typedef struct __attribute__((__packed__)) _EFI_IFR_IMAGE {
    EFI_IFR_OP_HEADER Header;
    EFI_IMAGE_ID Id;
} EFI_IFR_IMAGE;

#define EFI_IFR_INCONSISTENT_IF_OP 0x011

typedef struct __attribute__((__packed__)) _EFI_IFR_INCONSISTENT_IF {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID Error;
} EFI_IFR_INCONSISTENT_IF;

#define EFI_IFR_LENGTH_OP 0x56

typedef struct __attribute__((__packed__)) _EFI_IFR_LENGTH {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_LENGTH;

#define EFI_IFR_LESS_EQUAL_OP 0x34

typedef struct __attribute__((__packed__)) _EFI_IFR_LESS_EQUAL {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_LESS_EQUAL;

#define EFI_IFR_LESS_THAN_OP 0x33

typedef struct __attribute__((__packed__)) _EFI_IFR_LESS_THAN {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_LESS_THAN;

#define EFI_IFR_LOCKED_OP 0x0B

typedef struct __attribute__((__packed__)) _EFI_IFR_LOCKED {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_LOCKED;

#define EFI_IFR_MAP_OP 0x22

typedef struct __attribute__((__packed__)) _EFI_IFR_MAP {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MAP;

#define EFI_IFR_MATCH_OP 0x2a

typedef struct __attribute__((__packed__)) _EFI_IFR_MATCH {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MATCH;

#define EFI_IFR_MID_OP 0x4b

typedef struct __attribute__((__packed__)) _EFI_IFR_MID {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MID;

#define EFI_IFR_MODAL_TAG_OP 0x61

typedef struct __attribute__((__packed__)) _EFI_IFR_MODAL_TAG {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MODAL_TAG;

#define EFI_IFR_MODULO_OP 0x3e

typedef struct __attribute__((__packed__)) _EFI_IFR_MODULO {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MODULO;

#define EFI_IFR_MULTIPLY_OP 0x3c

typedef struct __attribute__((__packed__)) _EFI_IFR_MULTIPLY {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_MULTIPLY;

#define EFI_IFR_NOT_OP 0x17

typedef struct __attribute__((__packed__)) _EFI_IFR_NOT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_NOT;

#define EFI_IFR_NOT_EQUAL_OP 0x30

typedef struct __attribute__((__packed__)) _EFI_IFR_NOT_EQUAL {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_NOT_EQUAL;

#define EFI_IFR_NO_SUBMIT_IF_OP 0x10

typedef struct __attribute__((__packed__)) _EFI_IFR_NO_SUBMIT_IF {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID Error;
} EFI_IFR_NO_SUBMIT_IF;

#define EFI_IFR_NUMERIC_OP 0x07

typedef struct __attribute__((__packed__)) _EFI_IFR_NUMERIC {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 Flags;
    EFI_MINMAXSTEP_DATA data;
} EFI_IFR_NUMERIC;

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

typedef struct __attribute__((__packed__)) _EFI_IFR_ONE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_ONE;

#define EFI_IFR_ONES_OP 0x54

typedef struct __attribute__((__packed__)) _EFI_IFR_ONES {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_ONES;

#define EFI_IFR_ONE_OF_OP 0x05

typedef struct __attribute__((__packed__)) _EFI_IFR_ONE_OF {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 Flags;
    EFI_MINMAXSTEP_DATA data;
} EFI_IFR_ONE_OF;

#define EFI_IFR_ONE_OF_OPTION_OP 0x09

typedef struct __attribute__((__packed__)) _EFI_IFR_ONE_OF_OPTION {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID Option;
    EFI_UINT8 Flags;
    EFI_UINT8 Type;
    EFI_IFR_TYPE_VALUE Value;
} EFI_IFR_ONE_OF_OPTION;

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

typedef struct __attribute__((__packed__)) _EFI_IFR_OR {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_OR;

#define EFI_IFR_ORDERED_LIST_OP 0x23

typedef struct __attribute__((__packed__)) _EFI_IFR_ORDERED_LIST {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 MaxContainers;
    EFI_UINT8 Flags;
} EFI_IFR_ORDERED_LIST;

#define EFI_IFR_UNIQUE_SET 0x01
#define EFI_IFR_NO_EMPTY_SET 0x02

#define EFI_IFR_PASSWORD_OP 0x08

typedef struct __attribute__((__packed__)) _EFI_IFR_PASSWORD {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT16 MinSize;
    EFI_UINT16 MaxSize;
} EFI_IFR_PASSWORD;

#define EFI_IFR_QUESTION_REF1_OP 0x40

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_REF1 {
    EFI_IFR_OP_HEADER Header;
    EFI_QUESTION_ID QuestionId;
} EFI_IFR_QUESTION_REF1;

#define EFI_IFR_QUESTION_REF2_OP 0x41

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_REF2 {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_QUESTION_REF2;

#define EFI_IFR_QUESTION_REF3_OP 0x51

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_REF3 {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_QUESTION_REF3;

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_REF3_2 {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID DevicePath;
} EFI_IFR_QUESTION_REF3_2;

typedef struct __attribute__((__packed__)) _EFI_IFR_QUESTION_REF3_3 {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID DevicePath;
    EFI_GUID Guid;
} EFI_IFR_QUESTION_REF3_3;

#define EFI_IFR_READ_OP 0x2D

typedef struct __attribute__((__packed__)) _EFI_IFR_READ {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_READ;

#define EFI_IFR_REF_OP 0x0F

typedef struct __attribute__((__packed__)) _EFI_IFR_REF {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_FORM_ID FormId;
} EFI_IFR_REF;

typedef struct __attribute__((__packed__)) _EFI_IFR_REF2 {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
} EFI_IFR_REF2;

typedef struct __attribute__((__packed__)) _EFI_IFR_REF3 {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
    EFI_GUID FormSetId;
} EFI_IFR_REF3;

typedef struct __attribute__((__packed__)) _EFI_IFR_REF4 {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_FORM_ID FormId;
    EFI_QUESTION_ID QuestionId;
    EFI_GUID FormSetId;
    EFI_STRING_ID DevicePath;
} EFI_IFR_REF4;

typedef struct __attribute__((__packed__)) _EFI_IFR_REF5 {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
} EFI_IFR_REF5;

#define EFI_IFR_REFRESH_OP 0x1d

typedef struct __attribute__((__packed__)) _EFI_IFR_REFRESH {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 RefreshInterval;
} EFI_IFR_REFRESH;

#define EFI_IFR_REFRESH_ID_OP 0x62

typedef struct __attribute__((__packed__)) _EFI_IFR_REFRESH_ID {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID RefreshEventGroupId;
} EFI_IFR_REFRESH_ID;

#define EFI_IFR_RESET_BUTTON_OP 0x0d

typedef struct __attribute__((__packed__)) _EFI_IFR_RESET_BUTTON {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_STATEMENT_HEADER Statement;
    EFI_DEFAULT_ID DefaultId;
} EFI_IFR_RESET_BUTTON;

#define EFI_IFR_RULE_OP 0x18

typedef struct __attribute__((__packed__)) _EFI_IFR_RULE {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 RuleId;
} EFI_IFR_RULE;

#define EFI_IFR_RULE_REF_OP 0x3f

typedef struct __attribute__((__packed__)) _EFI_IFR_RULE_REF {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 RuleId;
} EFI_IFR_RULE_REF;

#define EFI_IFR_SECURITY_OP 0x60

typedef struct __attribute__((__packed__)) _EFI_IFR_SECURITY {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID Permissions;
} EFI_IFR_SECURITY;

#define EFI_IFR_SET_OP 0x2C

typedef struct __attribute__((__packed__)) _EFI_IFR_SET {
    EFI_IFR_OP_HEADER Header;
    EFI_VARSTORE_ID VarStoreId;
    union __attribute__((__packed__)) {
        EFI_STRING_ID VarName;
        EFI_UINT16 VarOffset;
    } VarStoreInfo;
    EFI_UINT8 VarStoreType;
} EFI_IFR_SET;

#define EFI_IFR_SHIFT_LEFT_OP 0x38

typedef struct __attribute__((__packed__)) _EFI_IFR_SHIFT_LEFT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_SHIFT_LEFT;

#define EFI_IFR_SHIFT_RIGHT_OP 0x39

typedef struct __attribute__((__packed__)) _EFI_IFR_SHIFT_RIGHT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_SHIFT_RIGHT;

#define EFI_IFR_SPAN_OP 0x59

typedef struct __attribute__((__packed__)) _EFI_IFR_SPAN {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 Flags;
} EFI_IFR_SPAN;

#define EFI_IFR_FLAGS_FIRST_MATCHING 0x00
#define EFI_IFR_FLAGS_FIRST_NON_MATCHING 0x01

#define EFI_IFR_STRING_OP 0x1C

typedef struct __attribute__((__packed__)) _EFI_IFR_STRING {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 MinSize;
    EFI_UINT8 MaxSize;
    EFI_UINT8 Flags;
} EFI_IFR_STRING;

#define EFI_IFR_STRING_MULTI_LINE 0x01

#define EFI_IFR_STRING_REF1_OP 0x4e

typedef struct __attribute__((__packed__)) _EFI_IFR_STRING_REF1 {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID StringId;
} EFI_IFR_STRING_REF1;

#define EFI_IFR_STRING_REF2_OP 0x4f

typedef struct __attribute__((__packed__)) _EFI_IFR_STRING_REF2 {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_STRING_REF2;

#define EFI_IFR_SUBTITLE_OP 0x02

typedef struct __attribute__((__packed__)) _EFI_IFR_SUBTITLE {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_STATEMENT_HEADER Statement;
    EFI_UINT8 Flags;
} EFI_IFR_SUBTITLE;

#define EFI_IFR_FLAGS_HORIZONTAL 0x01

#define EFI_IFR_SUBTRACT_OP 0x3b

typedef struct __attribute__((__packed__)) _EFI_IFR_SUBTRACT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_SUBTRACT;

#define EFI_IFR_SUPPRESS_IF_OP 0x0a

typedef struct __attribute__((__packed__)) _EFI_IFR_SUPPRESS_IF {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_SUPPRESS_IF;

#define EFI_IFR_TEXT_OP 0x03

typedef struct __attribute__((__packed__)) _EFI_IFR_TEXT {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_STATEMENT_HEADER Statement;
    EFI_STRING_ID TextTwo;
} EFI_IFR_TEXT;

#define EFI_IFR_THIS_OP 0x58

typedef struct __attribute__((__packed__)) _EFI_IFR_THIS {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_THIS;

#define EFI_IFR_TIME_OP 0x1b

typedef struct __attribute__((__packed__)) _EFI_IFR_TIME {
    EFI_IFR_OP_HEADER Header;
    EFI_IFR_QUESTION_HEADER Question;
    EFI_UINT8 Flags;
} EFI_IFR_TIME;

#define EFI_QF_TIME_HOUR_SUPPRESS 0x01
#define EFI_QF_TIME_MINUTE_SUPPRESS 0x02
#define EFI_QF_TIME_SECOND_SUPPRESS 0x04
#define EFI_QF_TIME_STORAGE 0x30

#define EFI_QF_TIME_STORAGE_NORMAL 0x00
#define EFI_QF_TIME_STORAGE_TIME 0x10
#define EFI_QF_TIME_STORAGE_WAKEUP 0x20

#define EFI_IFR_TOKEN_OP 0x4d

typedef struct __attribute__((__packed__)) _EFI_IFR_TOKEN {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TOKEN;

#define EFI_IFR_TO_BOOLEAN_OP 0x4A

typedef struct __attribute__((__packed__)) _EFI_IFR_TO_BOOLEAN {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TO_BOOLEAN;

#define EFI_IFR_TO_LOWER_OP 0x20

typedef struct __attribute__((__packed__)) _EFI_IFR_TO_LOWER {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TO_LOWER;

#define EFI_IFR_TO_STRING_OP 0x49

typedef struct __attribute__((__packed__)) _EFI_IFR_TO_STRING {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 Format;
} EFI_IFR_TO_STRING;

#define EFI_IFR_TO_UINT_OP 0x48

typedef struct __attribute__((__packed__)) _EFI_IFR_TO_UINT {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TO_UINT;

#define EFI_IFR_TO_UPPER_OP 0x21

typedef struct __attribute__((__packed__)) _EFI_IFR_TO_UPPER {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TO_UPPER;

#define EFI_IFR_TRUE_OP 0x46

typedef struct __attribute__((__packed__)) _EFI_IFR_TRUE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_TRUE;

#define EFI_IFR_UINT8_OP 0x42

typedef struct __attribute__((__packed__)) _EFI_IFR_UINT8 {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT8 Value;
} EFI_IFR_UINT8;

#define EFI_IFR_UINT16_OP 0x43

typedef struct __attribute__((__packed__)) _EFI_IFR_UINT16 {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT16 Value;
} EFI_IFR_UINT16;

#define EFI_IFR_UINT32_OP 0x44

typedef struct __attribute__((__packed__)) _EFI_IFR_UINT32 {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT32 Value;
} EFI_IFR_UINT32;

#define EFI_IFR_UINT64_OP 0x45

typedef struct __attribute__((__packed__)) _EFI_IFR_UINT64 {
    EFI_IFR_OP_HEADER Header;
    EFI_UINT64 Value;
} EFI_IFR_UINT64;

#define EFI_IFR_UNDEFINED_OP 0x55

typedef struct __attribute__((__packed__)) _EFI_IFR_UNDEFINED {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_UNDEFINED;

#define EFI_IFR_VALUE_OP 0x5a

typedef struct __attribute__((__packed__)) _EFI_IFR_VALUE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_VALUE;

#define EFI_IFR_VARSTORE_OP 0x24

/* The null-terminated ASCII Name follows Size (printed commented out). */
typedef struct __attribute__((__packed__)) {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID Guid;
    EFI_VARSTORE_ID VarStoreId;
    EFI_UINT16 Size;
} EFI_IFR_VARSTORE;

#define EFI_IFR_VARSTORE_NAME_VALUE_OP 0x25

typedef struct __attribute__((__packed__)) _EFI_IFR_VARSTORE_NAME_VALUE {
    EFI_IFR_OP_HEADER Header;
    EFI_VARSTORE_ID VarStoreId;
    EFI_GUID Guid;
} EFI_IFR_VARSTORE_NAME_VALUE;

#define EFI_IFR_VARSTORE_EFI_OP 0x26

/* The null-terminated ASCII Name follows Size (printed commented out). */
typedef struct __attribute__((__packed__)) _EFI_IFR_VARSTORE_EFI {
    EFI_IFR_OP_HEADER Header;
    EFI_VARSTORE_ID VarStoreId;
    EFI_GUID Guid;
    EFI_UINT32 Attributes;
    EFI_UINT16 Size;
} EFI_IFR_VARSTORE_EFI;

#define EFI_IFR_VARSTORE_DEVICE_OP 0x27

typedef struct __attribute__((__packed__)) _EFI_IFR_VARSTORE_DEVICE {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID DevicePath;
} EFI_IFR_VARSTORE_DEVICE;

#define EFI_IFR_VERSION_OP 0x28

typedef struct __attribute__((__packed__)) _EFI_IFR_VERSION {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_VERSION;

#define EFI_IFR_WRITE_OP 0x2E

typedef struct __attribute__((__packed__)) _EFI_IFR_WRITE {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_WRITE;

#define EFI_IFR_ZERO_OP 0x52

typedef struct __attribute__((__packed__)) _EFI_IFR_ZERO {
    EFI_IFR_OP_HEADER Header;
} EFI_IFR_ZERO;

#define EFI_IFR_WARNING_IF_OP 0x063

typedef struct __attribute__((__packed__)) _EFI_IFR_WARNING_IF {
    EFI_IFR_OP_HEADER Header;
    EFI_STRING_ID Warning;
    EFI_UINT8 TimeOut;
} EFI_IFR_WARNING_IF;

#define EFI_IFR_MATCH2_OP 0x64

typedef struct __attribute__((__packed__)) _EFI_IFR_MATCH2 {
    EFI_IFR_OP_HEADER Header;
    EFI_GUID SyntaxType;
} EFI_IFR_MATCH2;

/* EFI_HII_KEYBOARD_LAYOUT Layout[] follows (printed commented out). */
typedef struct __attribute__((__packed__)) {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT16 LayoutCount;
} EFI_HII_KEYBOARD_PACKAGE_HDR;

typedef struct __attribute__((__packed__)) _EFI_HII_ANIMATION_PACKAGE_HDR {
    EFI_HII_PACKAGE_HEADER Header;
    EFI_UINT32 AnimationInfoOffset;
} EFI_HII_ANIMATION_PACKAGE_HDR;

/* The block body follows BlockType (printed commented out). */
typedef struct __attribute__((__packed__)) _EFI_HII_ANIMATION_BLOCK {
    EFI_UINT8 BlockType;
} EFI_HII_ANIMATION_BLOCK;

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

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_EXT1_BLOCK {
    EFI_HII_ANIMATION_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT8 Length;
} EFI_HII_AIBT_EXT1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_EXT2_BLOCK {
    EFI_HII_ANIMATION_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT16 Length;
} EFI_HII_AIBT_EXT2_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_EXT4_BLOCK {
    EFI_HII_ANIMATION_BLOCK Header;
    EFI_UINT8 BlockType2;
    EFI_UINT32 Length;
} EFI_HII_AIBT_EXT4_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_ANIMATION_CELL {
    EFI_UINT16 OffsetX;
    EFI_UINT16 OffsetY;
    EFI_IMAGE_ID ImageId;
    EFI_UINT16 Delay;
} EFI_HII_ANIMATION_CELL;

/*
 * The animation block bodies carry no header: either an EFI_HII_ANIMATION_BLOCK or an
 * EFI_HII_AIBT_EXTx_BLOCK precedes them.
 */
__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_OVERLAY_IMAGES_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_OVERLAY_IMAGES_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_CLEAR_IMAGES_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_RGB_PIXEL BackgndColor;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_CLEAR_IMAGES_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_RESTORE_SCRN_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_RESTORE_SCRN_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_OVERLAY_IMAGES_LOOP_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_OVERLAY_IMAGES_LOOP_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_CLEAR_IMAGES_LOOP_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_RGB_PIXEL BackgndColor;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_CLEAR_IMAGES_LOOP_BLOCK;

__extension__ typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_RESTORE_SCRN_LOOP_BLOCK {
    EFI_IMAGE_ID DftImageId;
    EFI_UINT16 Width;
    EFI_UINT16 Height;
    EFI_UINT16 CellCount;
    EFI_HII_ANIMATION_CELL AnimationCell[];
} EFI_HII_AIBT_RESTORE_SCRN_LOOP_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_DUPLICATE_BLOCK {
    EFI_ANIMATION_ID AnimationId;
} EFI_HII_AIBT_DUPLICATE_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_SKIP1_BLOCK {
    EFI_UINT8 SkipCount;
} EFI_HII_AIBT_SKIP1_BLOCK;

typedef struct __attribute__((__packed__)) _EFI_HII_AIBT_SKIP2_BLOCK {
    EFI_UINT16 SkipCount;
} EFI_HII_AIBT_SKIP2_BLOCK;

#ifdef __cplusplus
}
#endif

#endif
