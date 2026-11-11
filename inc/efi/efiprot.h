#ifndef EFI_EFIPROT_H_
#define EFI_EFIPROT_H_

#include <stddef.h>

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
    {0x5B1B31A1, 0x9562, 0x11d2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

typedef struct {
    uint32_t Revision;
    EFI_HANDLE ParentHandle;
    EFI_SYSTEM_TABLE *SystemTable;

    EFI_HANDLE DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL *FilePath;
    void *Reserved;

    uint32_t LoadOptionsSize;
    void *LoadOptions;

    void *ImageBase;
    uint64_t ImageSize;
    EFI_MEMORY_TYPE ImageCodeType;
    EFI_MEMORY_TYPE ImageDataType;
    EFI_IMAGE_UNLOAD Unload;
} EFI_LOADED_IMAGE_PROTOCOL;

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
    {0xbc62157e, 0x3e33, 0x4fec, {0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf}}

#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
    {0x18A031AB, 0xB443, 0x4D1A, {0xA5, 0xC0, 0x0C, 0x09, 0x26, 0x1E, 0x9F, 0x71}}

typedef struct _EFI_DRIVER_BINDING_PROTOCOL EFI_DRIVER_BINDING_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED)(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_BINDING_PROTOCOL_START)(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_BINDING_PROTOCOL_STOP)(
    EFI_DRIVER_BINDING_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    size_t NumberOfChildren,
    EFI_HANDLE *ChildHandleBuffer
);

struct _EFI_DRIVER_BINDING_PROTOCOL {
    EFI_DRIVER_BINDING_PROTOCOL_SUPPORTED Supported;
    EFI_DRIVER_BINDING_PROTOCOL_START Start;
    EFI_DRIVER_BINDING_PROTOCOL_STOP Stop;
    uint32_t Version;
    EFI_HANDLE ImageHandle;
    EFI_HANDLE DriverBindingHandle;
};

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID \
    {0x6b30c738, 0xa391, 0x11d4, {0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

typedef struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER)(
    EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE *DriverImageHandle
);

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH)(
    EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_DEVICE_PATH_PROTOCOL **DriverImagePath
);

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED)(
    EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_DEVICE_PATH_PROTOCOL *DriverImagePath,
    EFI_HANDLE DriverImageHandle
);

struct _EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL {
    EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
    EFI_PLATFORM_DRIVER_OVERRIDE_GET_DRIVER_PATH GetDriverPath;
    EFI_PLATFORM_DRIVER_OVERRIDE_DRIVER_LOADED DriverLoaded;
};

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID \
    {0x3bc1b285, 0x8a15, 0x4a82, {0xaa, 0xbf, 0x4d, 0x7d, 0x13, 0xfb, 0x32, 0x65}}

typedef struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL
    EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER)(
    EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL *This,
    EFI_HANDLE *DriverImageHandle
);

struct _EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL {
    EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_GET_DRIVER GetDriver;
};

#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    {0x6a7a5cff, 0xe8d9, 0x4f70, {0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14}}

typedef struct _EFI_COMPONENT_NAME2_PROTOCOL EFI_COMPONENT_NAME2_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_COMPONENT_NAME_GET_DRIVER_NAME)(
    EFI_COMPONENT_NAME2_PROTOCOL *This,
    char *Language,
    uint16_t **DriverName
);

typedef EFI_STATUS (EFI_API *EFI_COMPONENT_NAME_GET_CONTROLLER_NAME)(
    EFI_COMPONENT_NAME2_PROTOCOL *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    char *Language,
    uint16_t **ControllerName
);

struct _EFI_COMPONENT_NAME2_PROTOCOL {
    EFI_COMPONENT_NAME_GET_DRIVER_NAME GetDriverName;
    EFI_COMPONENT_NAME_GET_CONTROLLER_NAME GetControllerName;
    char *SupportedLanguages;
};

typedef struct _EFI_SERVICE_BINDING_PROTOCOL EFI_SERVICE_BINDING_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_SERVICE_BINDING_CREATE_CHILD)(
    EFI_SERVICE_BINDING_PROTOCOL *This,
    EFI_HANDLE *ChildHandle
);

typedef EFI_STATUS (EFI_API *EFI_SERVICE_BINDING_DESTROY_CHILD)(
    EFI_SERVICE_BINDING_PROTOCOL *This,
    EFI_HANDLE ChildHandle
);

struct _EFI_SERVICE_BINDING_PROTOCOL {
    EFI_SERVICE_BINDING_CREATE_CHILD CreateChild;
    EFI_SERVICE_BINDING_DESTROY_CHILD DestroyChild;
};

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID \
    {0xb1ee129e, 0xda36, 0x4181, {0x91, 0xf8, 0x04, 0xa4, 0x92, 0x37, 0x66, 0xa7}}

typedef struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL;

typedef uint32_t (EFI_API *EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION)(
    EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL *This
);

struct _EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL {
    EFI_DRIVER_FAMILY_OVERRIDE_GET_VERSION GetVersion;
};

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
    {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}}

typedef struct _EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef struct {
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum {
    EfiPixelRedGreenBlueReserved8BitPerColor,
    EfiPixelBlueGreenRedReserved8BitPerColor,
    EfiPixelBitMask,
    EfiPixelBltOnly,
    EfiPixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode;
    uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    size_t SizeOfInfo;
    EFI_PHYSICAL_ADDRESS FrameBufferBase;
    size_t FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef EFI_STATUS (EFI_API *EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(
    EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    uint32_t ModeNumber,
    size_t *SizeOfInfo,
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info
);

typedef EFI_STATUS (EFI_API *EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(
    EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    uint32_t ModeNumber
);

typedef struct {
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
    uint8_t Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

/* Not in the specification: a pixel together with its 32-bit value. */
typedef union {
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel;
    uint32_t Raw;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL_UNION;

typedef enum {
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef EFI_STATUS (EFI_API *EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(
    EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
    EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
    size_t SourceX,
    size_t SourceY,
    size_t DestinationX,
    size_t DestinationY,
    size_t Width,
    size_t Height,
    size_t Delta
);

struct _EFI_GRAPHICS_OUTPUT_PROTOCOL {
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

#define EFI_EDID_DISCOVERED_PROTOCOL_GUID \
    {0x1c0c34f6, 0xd380, 0x41fa, {0xa0, 0x49, 0x8a, 0xd0, 0x6c, 0x1a, 0x66, 0xaa}}

typedef struct {
    uint32_t SizeOfEdid;
    uint8_t *Edid;
} EFI_EDID_DISCOVERED_PROTOCOL;

#define EFI_EDID_ACTIVE_PROTOCOL_GUID \
    {0xbd8c1056, 0x9f36, 0x44ec, {0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86}}

typedef struct {
    uint32_t SizeOfEdid;
    uint8_t *Edid;
} EFI_EDID_ACTIVE_PROTOCOL;

#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    {0x48ecb431, 0xfb72, 0x45c0, {0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x04, 0x0b, 0xd5}}

typedef struct _EFI_EDID_OVERRIDE_PROTOCOL EFI_EDID_OVERRIDE_PROTOCOL;

/* ChildHandle points to the handle: the specification keeps this historical typing on purpose. */
typedef EFI_STATUS (EFI_API *EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID)(
    EFI_EDID_OVERRIDE_PROTOCOL *This,
    EFI_HANDLE *ChildHandle,
    uint32_t *Attributes,
    size_t *EdidSize,
    uint8_t **Edid
);

#define EFI_EDID_OVERRIDE_DONT_OVERRIDE 0x01
#define EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG 0x02

struct _EFI_EDID_OVERRIDE_PROTOCOL {
    EFI_EDID_OVERRIDE_PROTOCOL_GET_EDID GetEdid;
};

#define EFI_LOAD_FILE_PROTOCOL_GUID \
    {0x56EC3091, 0x954C, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

typedef struct _EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_LOAD_FILE)(
    EFI_LOAD_FILE_PROTOCOL *This,
    EFI_DEVICE_PATH_PROTOCOL *FilePath,
    bool BootPolicy,
    size_t *BufferSize,
    void *Buffer
);

struct _EFI_LOAD_FILE_PROTOCOL {
    EFI_LOAD_FILE LoadFile;
};

#define EFI_LOAD_FILE2_PROTOCOL_GUID \
    {0x4006c0c1, 0xfcb3, 0x403e, {0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d}}

typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
    EFI_FILE_PROTOCOL **Root
);

struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    uint64_t Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

typedef EFI_STATUS (EFI_API *EFI_FILE_OPEN)(
    EFI_FILE_PROTOCOL *This,
    EFI_FILE_PROTOCOL **NewHandle,
    uint16_t *FileName,
    uint64_t OpenMode,
    uint64_t Attributes
);

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

typedef EFI_STATUS (EFI_API *EFI_FILE_CLOSE)(EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_FILE_DELETE)(EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_FILE_READ)(
    EFI_FILE_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_FILE_WRITE)(
    EFI_FILE_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    size_t BufferSize;
    void *Buffer;
} EFI_FILE_IO_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_FILE_OPEN_EX)(
    EFI_FILE_PROTOCOL *This,
    EFI_FILE_PROTOCOL **NewHandle,
    uint16_t *FileName,
    uint64_t OpenMode,
    uint64_t Attributes,
    EFI_FILE_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FILE_READ_EX)(
    EFI_FILE_PROTOCOL *This,
    EFI_FILE_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FILE_WRITE_EX)(
    EFI_FILE_PROTOCOL *This,
    EFI_FILE_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FILE_FLUSH_EX)(
    EFI_FILE_PROTOCOL *This,
    EFI_FILE_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FILE_SET_POSITION)(
    EFI_FILE_PROTOCOL *This,
    uint64_t Position
);

typedef EFI_STATUS (EFI_API *EFI_FILE_GET_POSITION)(
    EFI_FILE_PROTOCOL *This,
    uint64_t *Position
);

typedef EFI_STATUS (EFI_API *EFI_FILE_GET_INFO)(
    EFI_FILE_PROTOCOL *This,
    EFI_GUID *InformationType,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_FILE_SET_INFO)(
    EFI_FILE_PROTOCOL *This,
    EFI_GUID *InformationType,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_FILE_FLUSH)(EFI_FILE_PROTOCOL *This);

struct _EFI_FILE_PROTOCOL {
    uint64_t Revision;
    EFI_FILE_OPEN Open;
    EFI_FILE_CLOSE Close;
    EFI_FILE_DELETE Delete;
    EFI_FILE_READ Read;
    EFI_FILE_WRITE Write;
    EFI_FILE_GET_POSITION GetPosition;
    EFI_FILE_SET_POSITION SetPosition;
    EFI_FILE_GET_INFO GetInfo;
    EFI_FILE_SET_INFO SetInfo;
    EFI_FILE_FLUSH Flush;
    /* The Ex services exist from EFI_FILE_PROTOCOL_REVISION2 on. */
    EFI_FILE_OPEN_EX OpenEx;
    EFI_FILE_READ_EX ReadEx;
    EFI_FILE_WRITE_EX WriteEx;
    EFI_FILE_FLUSH_EX FlushEx;
};

#define EFI_FILE_INFO_ID \
    {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

/* Name arrays have one element, as in firmware ([] in print); SIZE_OF_* is the fixed part. */
typedef struct {
    uint64_t Size;
    uint64_t FileSize;
    uint64_t PhysicalSize;
    EFI_TIME CreateTime;
    EFI_TIME LastAccessTime;
    EFI_TIME ModificationTime;
    uint64_t Attribute;
    uint16_t FileName[1];
} EFI_FILE_INFO;

#define EFI_SIZE_OF_EFI_FILE_INFO offsetof(EFI_FILE_INFO, FileName)

#define EFI_FILE_SYSTEM_INFO_ID \
    {0x09576e93, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

typedef struct {
    uint64_t Size;
    uint8_t ReadOnly;
    uint64_t VolumeSize;
    uint64_t FreeSpace;
    uint32_t BlockSize;
    uint16_t VolumeLabel[1];
} EFI_FILE_SYSTEM_INFO;

#define EFI_SIZE_OF_EFI_FILE_SYSTEM_INFO offsetof(EFI_FILE_SYSTEM_INFO, VolumeLabel)

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID \
    {0xdb47d7d3, 0xfe81, 0x11d3, {0x9a, 0x35, 0x00, 0x90, 0x27, 0x3f, 0xC1, 0x4d}}

typedef struct {
    uint16_t VolumeLabel[1];
} EFI_FILE_SYSTEM_VOLUME_LABEL;

#define EFI_SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL offsetof(EFI_FILE_SYSTEM_VOLUME_LABEL, VolumeLabel)

#define EFI_DISK_IO_PROTOCOL_GUID \
    {0xCE345171, 0xBA0B, 0x11d2, {0x8e, 0x4F, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_DISK_READ)(
    EFI_DISK_IO_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Offset,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_DISK_WRITE)(
    EFI_DISK_IO_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Offset,
    size_t BufferSize,
    void *Buffer
);

struct _EFI_DISK_IO_PROTOCOL {
    uint64_t Revision;
    EFI_DISK_READ ReadDisk;
    EFI_DISK_WRITE WriteDisk;
};

#define EFI_DISK_IO2_PROTOCOL_GUID \
    {0x151c8eae, 0x7f2c, 0x472c, {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88}}

#define EFI_DISK_IO2_PROTOCOL_REVISION 0x00020000

typedef struct _EFI_DISK_IO2_PROTOCOL EFI_DISK_IO2_PROTOCOL;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DISK_CANCEL_EX)(EFI_DISK_IO2_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DISK_READ_EX)(
    EFI_DISK_IO2_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Offset,
    EFI_DISK_IO2_TOKEN *Token,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_DISK_WRITE_EX)(
    EFI_DISK_IO2_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Offset,
    EFI_DISK_IO2_TOKEN *Token,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_DISK_FLUSH_EX)(
    EFI_DISK_IO2_PROTOCOL *This,
    EFI_DISK_IO2_TOKEN *Token
);

struct _EFI_DISK_IO2_PROTOCOL {
    uint64_t Revision;
    EFI_DISK_CANCEL_EX Cancel;
    EFI_DISK_READ_EX ReadDiskEx;
    EFI_DISK_WRITE_EX WriteDiskEx;
    EFI_DISK_FLUSH_EX FlushDiskEx;
};

#define EFI_BLOCK_IO_PROTOCOL_GUID \
    {0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

#define EFI_BLOCK_IO_PROTOCOL_REVISION 0x00010000
#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2<<16) | (31))

typedef struct _EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL;

typedef struct {
    uint32_t MediaId;
    uint8_t RemovableMedia;
    uint8_t MediaPresent;
    uint8_t LogicalPartition;
    uint8_t ReadOnly;
    uint8_t WriteCaching;
    uint32_t BlockSize;
    uint32_t IoAlign;
    EFI_LBA LastBlock;
    /* Valid from EFI_BLOCK_IO_PROTOCOL_REVISION2 on. */
    EFI_LBA LowestAlignedLba;
    uint32_t LogicalBlocksPerPhysicalBlock;
    /* Valid from EFI_BLOCK_IO_PROTOCOL_REVISION3 on. */
    uint32_t OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef EFI_STATUS (EFI_API *EFI_BLOCK_RESET)(
    EFI_BLOCK_IO_PROTOCOL *This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_READ)(
    EFI_BLOCK_IO_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_WRITE)(
    EFI_BLOCK_IO_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_FLUSH)(EFI_BLOCK_IO_PROTOCOL *This);

struct _EFI_BLOCK_IO_PROTOCOL {
    uint64_t Revision;
    EFI_BLOCK_IO_MEDIA *Media;
    EFI_BLOCK_RESET Reset;
    EFI_BLOCK_READ ReadBlocks;
    EFI_BLOCK_WRITE WriteBlocks;
    EFI_BLOCK_FLUSH FlushBlocks;
};

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
    {0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1}}

typedef struct _EFI_BLOCK_IO2_PROTOCOL EFI_BLOCK_IO2_PROTOCOL;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_BLOCK_RESET_EX)(
    EFI_BLOCK_IO2_PROTOCOL *This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_READ_EX)(
    EFI_BLOCK_IO2_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    EFI_BLOCK_IO2_TOKEN *Token,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_WRITE_EX)(
    EFI_BLOCK_IO2_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    EFI_BLOCK_IO2_TOKEN *Token,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_FLUSH_EX)(
    EFI_BLOCK_IO2_PROTOCOL *This,
    EFI_BLOCK_IO2_TOKEN *Token
);

struct _EFI_BLOCK_IO2_PROTOCOL {
    EFI_BLOCK_IO_MEDIA *Media;
    EFI_BLOCK_RESET_EX Reset;
    EFI_BLOCK_READ_EX ReadBlocksEx;
    EFI_BLOCK_WRITE_EX WriteBlocksEx;
    EFI_BLOCK_FLUSH_EX FlushBlocksEx;
};

#define EFI_UNICODE_COLLATION_PROTOCOL2_GUID \
    {0xa4c751fc, 0x23ae, 0x4c3e, {0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49}}

typedef struct _EFI_UNICODE_COLLATION_PROTOCOL EFI_UNICODE_COLLATION_PROTOCOL;

typedef intptr_t (EFI_API *EFI_UNICODE_COLLATION_STRICOLL)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    uint16_t *s1,
    uint16_t *s2
);

typedef bool (EFI_API *EFI_UNICODE_COLLATION_METAIMATCH)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    uint16_t *String,
    uint16_t *Pattern
);

typedef void (EFI_API *EFI_UNICODE_COLLATION_STRLWR)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    uint16_t *String
);

typedef void (EFI_API *EFI_UNICODE_COLLATION_STRUPR)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    uint16_t *String
);

typedef void (EFI_API *EFI_UNICODE_COLLATION_FATTOSTR)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    size_t FatSize,
    char *Fat,
    uint16_t *String
);

typedef bool (EFI_API *EFI_UNICODE_COLLATION_STRTOFAT)(
    EFI_UNICODE_COLLATION_PROTOCOL *This,
    uint16_t *String,
    size_t FatSize,
    char *Fat
);

struct _EFI_UNICODE_COLLATION_PROTOCOL {
    EFI_UNICODE_COLLATION_STRICOLL StriColl;
    EFI_UNICODE_COLLATION_METAIMATCH MetaiMatch;
    EFI_UNICODE_COLLATION_STRLWR StrLwr;
    EFI_UNICODE_COLLATION_STRUPR StrUpr;
    EFI_UNICODE_COLLATION_FATTOSTR FatToStr;
    EFI_UNICODE_COLLATION_STRTOFAT StrToFat;
    char *SupportedLanguages;
};

/* Not in the specification: the byte order mark that starts a UCS-2 text file. */
#define EFI_UNICODE_BYTE_ORDER_MARK ((uint16_t)0xFEFF)

#define EFI_EBC_PROTOCOL_GUID \
    {0x13ac6dd1, 0x73d0, 0x11d4, {0xb0, 0x6b, 0x00, 0xaa, 0x00, 0xbd, 0x6d, 0xe7}}

typedef struct _EFI_EBC_PROTOCOL EFI_EBC_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_EBC_CREATE_THUNK)(
    EFI_EBC_PROTOCOL *This,
    EFI_HANDLE ImageHandle,
    void *EbcEntryPoint,
    void **Thunk
);

typedef EFI_STATUS (EFI_API *EFI_EBC_UNLOAD_IMAGE)(
    EFI_EBC_PROTOCOL *This,
    EFI_HANDLE ImageHandle
);

typedef EFI_STATUS (EFI_API *EFI_EBC_ICACHE_FLUSH)(
    EFI_PHYSICAL_ADDRESS Start,
    uint64_t Length
);

/* The prototype prints **This and *Flush; the descriptions want one level less. */
typedef EFI_STATUS (EFI_API *EFI_EBC_REGISTER_ICACHE_FLUSH)(
    EFI_EBC_PROTOCOL *This,
    EFI_EBC_ICACHE_FLUSH Flush
);

typedef EFI_STATUS (EFI_API *EFI_EBC_GET_VERSION)(
    EFI_EBC_PROTOCOL *This,
    uint64_t *Version
);

struct _EFI_EBC_PROTOCOL {
    EFI_EBC_CREATE_THUNK CreateThunk;
    EFI_EBC_UNLOAD_IMAGE UnloadImage;
    EFI_EBC_REGISTER_ICACHE_FLUSH RegisterICacheFlush;
    EFI_EBC_GET_VERSION GetVersion;
};

#define EFI_HASH_SERVICE_BINDING_PROTOCOL_GUID \
    {0x42881c98, 0xa4f3, 0x44b0, {0xa3, 0x9d, 0xdf, 0xa1, 0x86, 0x67, 0xd8, 0xcd}}

#define EFI_HASH_PROTOCOL_GUID \
    {0xc5184932, 0xdba5, 0x46db, {0xa5, 0xba, 0xcc, 0x0b, 0xda, 0x9c, 0x14, 0x35}}

typedef struct _EFI_HASH_PROTOCOL EFI_HASH_PROTOCOL;

typedef uint8_t EFI_MD5_HASH[16];
typedef uint8_t EFI_SHA1_HASH[20];
typedef uint8_t EFI_SHA224_HASH[28];
typedef uint8_t EFI_SHA256_HASH[32];
typedef uint8_t EFI_SHA384_HASH[48];
typedef uint8_t EFI_SHA512_HASH[64];

typedef union _EFI_HASH_OUTPUT {
    EFI_MD5_HASH *Md5Hash;
    EFI_SHA1_HASH *Sha1Hash;
    EFI_SHA224_HASH *Sha224Hash;
    EFI_SHA256_HASH *Sha256Hash;
    EFI_SHA384_HASH *Sha384Hash;
    EFI_SHA512_HASH *Sha512Hash;
} EFI_HASH_OUTPUT;

/* GetHashSize() and Hash() are printed as plain prototypes; named as the protocol types them. */
typedef EFI_STATUS (EFI_API *EFI_HASH_GET_HASH_SIZE)(
    const EFI_HASH_PROTOCOL *This,
    const EFI_GUID *HashAlgorithm,
    size_t *HashSize
);

typedef EFI_STATUS (EFI_API *EFI_HASH_HASH)(
    const EFI_HASH_PROTOCOL *This,
    const EFI_GUID *HashAlgorithm,
    bool Extend,
    const uint8_t *Message,
    uint64_t MessageSize,
    EFI_HASH_OUTPUT *Hash
);

struct _EFI_HASH_PROTOCOL {
    EFI_HASH_GET_HASH_SIZE GetHashSize;
    EFI_HASH_HASH Hash;
};

#define EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID \
    {0x24c5dc2f, 0x53e2, 0x40ca, {0x9e, 0xd6, 0xa5, 0xd9, 0xa4, 0x9f, 0x46, 0x3b}}

#define EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID \
    {0x8628752a, 0x6cb7, 0x4814, {0x96, 0xfc, 0x24, 0xa8, 0x15, 0xac, 0x22, 0x26}}

/* The Hash2 algorithms: efisectech.h takes them from here rather than defining them again. */
#define EFI_HASH_ALGORITHM_SHA1_GUID \
    {0x2ae9d80f, 0x3fb2, 0x4095, {0xb7, 0xb1, 0xe9, 0x31, 0x57, 0xb9, 0x46, 0xb6}}

#define EFI_HASH_ALGORITHM_SHA224_GUID \
    {0x8df01a06, 0x9bd5, 0x4bf7, {0xb0, 0x21, 0xdb, 0x4f, 0xd9, 0xcc, 0xf4, 0x5b}}

#define EFI_HASH_ALGORITHM_SHA256_GUID \
    {0x51aa59de, 0xfdf2, 0x4ea3, {0xbc, 0x63, 0x87, 0x5f, 0xb7, 0x84, 0x2e, 0xe9}}

#define EFI_HASH_ALGORITHM_SHA384_GUID \
    {0xefa96432, 0xde33, 0x4dd2, {0xae, 0xe6, 0x32, 0x8c, 0x33, 0xdf, 0x77, 0x7a}}

#define EFI_HASH_ALGORITHM_SHA512_GUID \
    {0xcaa4381e, 0x750c, 0x4770, {0xb8, 0x70, 0x7a, 0x23, 0xb4, 0xe4, 0x21, 0x30}}

#define EFI_HASH_ALGORITHM_MD5_GUID \
    {0xaf7c79c, 0x65b5, 0x4319, {0xb0, 0xae, 0x44, 0xec, 0x48, 0x4e, 0x4a, 0xd7}}

#define EFI_RNG_PROTOCOL_GUID \
    {0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44}}

typedef struct _EFI_RNG_PROTOCOL EFI_RNG_PROTOCOL;

typedef EFI_GUID EFI_RNG_ALGORITHM;

typedef EFI_STATUS (EFI_API *EFI_RNG_GET_INFO)(
    EFI_RNG_PROTOCOL *This,
    size_t *RNGAlgorithmListSize,
    EFI_RNG_ALGORITHM *RNGAlgorithmList
);

typedef EFI_STATUS (EFI_API *EFI_RNG_GET_RNG)(
    EFI_RNG_PROTOCOL *This,
    EFI_RNG_ALGORITHM *RNGAlgorithm,
    size_t RNGValueLength,
    uint8_t *RNGValue
);

struct _EFI_RNG_PROTOCOL {
    EFI_RNG_GET_INFO GetInfo;
    EFI_RNG_GET_RNG GetRNG;
};

#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID \
    {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96}}

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID \
    {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7}}

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID \
    {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e}}

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID \
    {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46}}

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID \
    {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9}}

#define EFI_RNG_ALGORITHM_RAW \
    {0xe43176d7, 0xb6e8, 0x4827, {0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61}}

#define EFI_RNG_ALGORITHM_ARM_RNDR \
    {0x43d2fde3, 0x9d4e, 0x4d79, {0x02, 0x96, 0xa8, 0x9b, 0xca, 0x78, 0x08, 0x41}}

#define EFI_MEMORY_ATTRIBUTE_PROTOCOL_GUID \
    {0xf4560cf6, 0x40ec, 0x4b4a, {0xa1, 0x92, 0xbf, 0x1d, 0x57, 0xd0, 0xb1, 0x89}}

typedef struct _EFI_MEMORY_ATTRIBUTE_PROTOCOL EFI_MEMORY_ATTRIBUTE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_ATTRIBUTES)(
    EFI_MEMORY_ATTRIBUTE_PROTOCOL *This,
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t *Attributes
);

typedef EFI_STATUS (EFI_API *EFI_SET_MEMORY_ATTRIBUTES)(
    EFI_MEMORY_ATTRIBUTE_PROTOCOL *This,
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_CLEAR_MEMORY_ATTRIBUTES)(
    EFI_MEMORY_ATTRIBUTE_PROTOCOL *This,
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t Attributes
);

struct _EFI_MEMORY_ATTRIBUTE_PROTOCOL {
    EFI_GET_MEMORY_ATTRIBUTES GetMemoryAttributes;
    EFI_SET_MEMORY_ATTRIBUTES SetMemoryAttributes;
    EFI_CLEAR_MEMORY_ATTRIBUTES ClearMemoryAttributes;
};

#ifdef __cplusplus
}
#endif

#endif
