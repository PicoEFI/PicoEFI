#ifndef EFI_EFIPCIIO_H_
#define EFI_EFIPCIIO_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
    {0x2F707EBB, 0x4A1A, 0x11d4, {0x9A, 0x38, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D}}

typedef struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL;

typedef enum {
    EfiPciWidthUint8,
    EfiPciWidthUint16,
    EfiPciWidthUint32,
    EfiPciWidthUint64,
    EfiPciWidthFifoUint8,
    EfiPciWidthFifoUint16,
    EfiPciWidthFifoUint32,
    EfiPciWidthFifoUint64,
    EfiPciWidthFillUint8,
    EfiPciWidthFillUint16,
    EfiPciWidthFillUint32,
    EfiPciWidthFillUint64,
    EfiPciWidthMaximum
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH;

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH Width,
    uint64_t Address,
    uint64_t Mask,
    uint64_t Value,
    uint64_t Delay,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH Width,
    uint64_t Address,
    size_t Count,
    void *Buffer
);

typedef struct {
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM Read;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM Write;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS;

#define EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO 0x0001
#define EFI_PCI_ATTRIBUTE_ISA_IO 0x0002
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO 0x0004
#define EFI_PCI_ATTRIBUTE_VGA_MEMORY 0x0008
#define EFI_PCI_ATTRIBUTE_VGA_IO 0x0010
#define EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO 0x0020
#define EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO 0x0040
#define EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE 0x0080
#define EFI_PCI_ATTRIBUTE_MEMORY_CACHED 0x0800
#define EFI_PCI_ATTRIBUTE_MEMORY_DISABLE 0x1000
#define EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE 0x8000
#define EFI_PCI_ATTRIBUTE_ISA_IO_16 0x10000
#define EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO_16 0x20000
#define EFI_PCI_ATTRIBUTE_VGA_IO_16 0x40000

typedef enum {
    EfiPciOperationBusMasterRead,
    EfiPciOperationBusMasterWrite,
    EfiPciOperationBusMasterCommonBuffer,
    EfiPciOperationBusMasterRead64,
    EfiPciOperationBusMasterWrite64,
    EfiPciOperationBusMasterCommonBuffer64,
    EfiPciOperationMaximum
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION;

/* Layout of the uint64_t Address that Pci.Read() and Pci.Write() take. */
typedef struct {
    uint8_t Register;
    uint8_t Function;
    uint8_t Device;
    uint8_t Bus;
    uint32_t ExtendedRegister;
} EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_PCI_ADDRESS;

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH Width,
    uint64_t DestAddress,
    uint64_t SrcAddress,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_OPERATION Operation,
    void *HostAddress,
    size_t *NumberOfBytes,
    EFI_PHYSICAL_ADDRESS *DeviceAddress,
    void **Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    void *Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    EFI_ALLOCATE_TYPE Type,
    EFI_MEMORY_TYPE MemoryType,
    size_t Pages,
    void **HostAddress,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    size_t Pages,
    void *HostAddress
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    uint64_t *Supports,
    uint64_t *Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    uint64_t Attributes,
    uint64_t *ResourceBase,
    uint64_t *ResourceLength
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION)(
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *This,
    void **Resources
);

#define EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR_TAG 0x8A
#define EFI_ACPI_END_TAG_DESCRIPTOR_TAG 0x79

#define EFI_ACPI_ADDRESS_SPACE_TYPE_MEM 0x00
#define EFI_ACPI_ADDRESS_SPACE_TYPE_IO 0x01
#define EFI_ACPI_ADDRESS_SPACE_TYPE_BUS 0x02

#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_NON_CACHEABLE 0x00
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE 0x02
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_WRITE_COMBINING 0x04
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE 0x06

typedef struct __attribute__((__packed__)) {
    uint8_t Desc;
    uint16_t Len;
    uint8_t ResType;
    uint8_t GenFlag;
    uint8_t SpecificFlag;
    uint64_t AddrSpaceGranularity;
    uint64_t AddrRangeMin;
    uint64_t AddrRangeMax;
    uint64_t AddrTranslationOffset;
    uint64_t AddrLen;
} EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR;

typedef struct __attribute__((__packed__)) {
    uint8_t Desc;
    uint8_t Checksum;
} EFI_ACPI_END_TAG_DESCRIPTOR;

struct _EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL {
    EFI_HANDLE ParentHandle;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM PollMem;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM PollIo;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS Mem;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS Io;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ACCESS Pci;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM CopyMem;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP Map;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP Unmap;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER AllocateBuffer;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER FreeBuffer;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH Flush;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES GetAttributes;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES SetAttributes;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION Configuration;
    uint32_t SegmentNumber;
};

#define EFI_PCI_IO_PROTOCOL_GUID \
    {0x4cf5b200, 0x68b8, 0x4ca5, {0x9e, 0xec, 0xb2, 0x3e, 0x3f, 0x50, 0x02, 0x9a}}

typedef struct _EFI_PCI_IO_PROTOCOL EFI_PCI_IO_PROTOCOL;

typedef enum {
    EfiPciIoWidthUint8,
    EfiPciIoWidthUint16,
    EfiPciIoWidthUint32,
    EfiPciIoWidthUint64,
    EfiPciIoWidthFifoUint8,
    EfiPciIoWidthFifoUint16,
    EfiPciIoWidthFifoUint32,
    EfiPciIoWidthFifoUint64,
    EfiPciIoWidthFillUint8,
    EfiPciIoWidthFillUint16,
    EfiPciIoWidthFillUint32,
    EfiPciIoWidthFillUint64,
    EfiPciIoWidthMaximum
} EFI_PCI_IO_PROTOCOL_WIDTH;

#define EFI_PCI_IO_PASS_THROUGH_BAR 0xff

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_POLL_IO_MEM)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_WIDTH Width,
    uint8_t BarIndex,
    uint64_t Offset,
    uint64_t Mask,
    uint64_t Value,
    uint64_t Delay,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_IO_MEM)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_WIDTH Width,
    uint8_t BarIndex,
    uint64_t Offset,
    size_t Count,
    void *Buffer
);

typedef struct {
    EFI_PCI_IO_PROTOCOL_IO_MEM Read;
    EFI_PCI_IO_PROTOCOL_IO_MEM Write;
} EFI_PCI_IO_PROTOCOL_ACCESS;

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_CONFIG)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_WIDTH Width,
    uint32_t Offset,
    size_t Count,
    void *Buffer
);

typedef struct {
    EFI_PCI_IO_PROTOCOL_CONFIG Read;
    EFI_PCI_IO_PROTOCOL_CONFIG Write;
} EFI_PCI_IO_PROTOCOL_CONFIG_ACCESS;

#define EFI_PCI_IO_ATTRIBUTE_ISA_MOTHERBOARD_IO 0x0001
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO 0x0002
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO 0x0004
#define EFI_PCI_IO_ATTRIBUTE_VGA_MEMORY 0x0008
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO 0x0010
#define EFI_PCI_IO_ATTRIBUTE_IDE_PRIMARY_IO 0x0020
#define EFI_PCI_IO_ATTRIBUTE_IDE_SECONDARY_IO 0x0040
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_WRITE_COMBINE 0x0080
#define EFI_PCI_IO_ATTRIBUTE_IO 0x0100
#define EFI_PCI_IO_ATTRIBUTE_MEMORY 0x0200
#define EFI_PCI_IO_ATTRIBUTE_BUS_MASTER 0x0400
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_CACHED 0x0800
#define EFI_PCI_IO_ATTRIBUTE_MEMORY_DISABLE 0x1000
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_DEVICE 0x2000
#define EFI_PCI_IO_ATTRIBUTE_EMBEDDED_ROM 0x4000
#define EFI_PCI_IO_ATTRIBUTE_DUAL_ADDRESS_CYCLE 0x8000
#define EFI_PCI_IO_ATTRIBUTE_ISA_IO_16 0x10000
#define EFI_PCI_IO_ATTRIBUTE_VGA_PALETTE_IO_16 0x20000
#define EFI_PCI_IO_ATTRIBUTE_VGA_IO_16 0x40000

typedef enum {
    EfiPciIoOperationBusMasterRead,
    EfiPciIoOperationBusMasterWrite,
    EfiPciIoOperationBusMasterCommonBuffer,
    EfiPciIoOperationMaximum
} EFI_PCI_IO_PROTOCOL_OPERATION;

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_COPY_MEM)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_WIDTH Width,
    uint8_t DestBarIndex,
    uint64_t DestOffset,
    uint8_t SrcBarIndex,
    uint64_t SrcOffset,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_MAP)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_OPERATION Operation,
    void *HostAddress,
    size_t *NumberOfBytes,
    EFI_PHYSICAL_ADDRESS *DeviceAddress,
    void **Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_UNMAP)(
    EFI_PCI_IO_PROTOCOL *This,
    void *Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_ALLOCATE_BUFFER)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_ALLOCATE_TYPE Type,
    EFI_MEMORY_TYPE MemoryType,
    size_t Pages,
    void **HostAddress,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_FREE_BUFFER)(
    EFI_PCI_IO_PROTOCOL *This,
    size_t Pages,
    void *HostAddress
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_FLUSH)(EFI_PCI_IO_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_GET_LOCATION)(
    EFI_PCI_IO_PROTOCOL *This,
    uintptr_t *SegmentNumber,
    uintptr_t *BusNumber,
    uintptr_t *DeviceNumber,
    uintptr_t *FunctionNumber
);

typedef enum {
    EfiPciIoAttributeOperationGet,
    EfiPciIoAttributeOperationSet,
    EfiPciIoAttributeOperationEnable,
    EfiPciIoAttributeOperationDisable,
    EfiPciIoAttributeOperationSupported,
    EfiPciIoAttributeOperationMaximum
} EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION;

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_ATTRIBUTES)(
    EFI_PCI_IO_PROTOCOL *This,
    EFI_PCI_IO_PROTOCOL_ATTRIBUTE_OPERATION Operation,
    uint64_t Attributes,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_GET_BAR_ATTRIBUTES)(
    EFI_PCI_IO_PROTOCOL *This,
    uint8_t BarIndex,
    uint64_t *Supports,
    void **Resources
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_SET_BAR_ATTRIBUTES)(
    EFI_PCI_IO_PROTOCOL *This,
    uint64_t Attributes,
    uint8_t BarIndex,
    uint64_t *Offset,
    uint64_t *Length
);

struct _EFI_PCI_IO_PROTOCOL {
    EFI_PCI_IO_PROTOCOL_POLL_IO_MEM PollMem;
    EFI_PCI_IO_PROTOCOL_POLL_IO_MEM PollIo;
    EFI_PCI_IO_PROTOCOL_ACCESS Mem;
    EFI_PCI_IO_PROTOCOL_ACCESS Io;
    EFI_PCI_IO_PROTOCOL_CONFIG_ACCESS Pci;
    EFI_PCI_IO_PROTOCOL_COPY_MEM CopyMem;
    EFI_PCI_IO_PROTOCOL_MAP Map;
    EFI_PCI_IO_PROTOCOL_UNMAP Unmap;
    EFI_PCI_IO_PROTOCOL_ALLOCATE_BUFFER AllocateBuffer;
    EFI_PCI_IO_PROTOCOL_FREE_BUFFER FreeBuffer;
    EFI_PCI_IO_PROTOCOL_FLUSH Flush;
    EFI_PCI_IO_PROTOCOL_GET_LOCATION GetLocation;
    EFI_PCI_IO_PROTOCOL_ATTRIBUTES Attributes;
    EFI_PCI_IO_PROTOCOL_GET_BAR_ATTRIBUTES GetBarAttributes;
    EFI_PCI_IO_PROTOCOL_SET_BAR_ATTRIBUTES SetBarAttributes;
    uint64_t RomSize;
    void *RomImage;
};

#define EFI_PCI_EXPANSION_ROM_HEADER_SIGNATURE 0xAA55
#define EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE 0x0EF1
#define EFI_PCI_DATA_STRUCTURE_SIGNATURE EFI_SIGNATURE_32('P', 'C', 'I', 'R')

#define EFI_PCI_CODE_TYPE_PCAT_IMAGE 0x00
#define EFI_PCI_CODE_TYPE_EFI_IMAGE 0x03

#define EFI_PCI_EXPANSION_ROM_HEADER_COMPRESSED 0x0001

typedef struct __attribute__((__packed__)) {
    uint16_t Signature;
    uint8_t Reserved[0x16];
    uint16_t PcirOffset;
} EFI_STANDARD_PCI_EXPANSION_ROM_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t Signature;
    uint16_t InitializationSize;
    uint32_t EfiSignature;
    uint16_t EfiSubsystem;
    uint16_t EfiMachineType;
    uint16_t CompressionType;
    uint8_t Reserved[8];
    uint16_t EfiImageHeaderOffset;
    uint16_t PcirOffset;
} EFI_PCI_EXPANSION_ROM_HEADER;

typedef struct __attribute__((__packed__)) {
    uint32_t Signature;
    uint16_t VendorId;
    uint16_t DeviceId;
    uint16_t Reserved0;
    uint16_t Length;
    uint8_t Revision;
    uint8_t ClassCode[3];
    uint16_t ImageLength;
    uint16_t CodeRevision;
    uint8_t CodeType;
    uint8_t Indicator;
    uint16_t Reserved1;
} EFI_PCI_DATA_STRUCTURE;

#ifdef __cplusplus
}
#endif

#endif
