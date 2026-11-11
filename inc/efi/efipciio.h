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

struct efi_pci_root_bridge_io_protocol;

#define EFI_PCI_WIDTH_UINT8 ((uint32_t)0)
#define EFI_PCI_WIDTH_UINT16 ((uint32_t)1)
#define EFI_PCI_WIDTH_UINT32 ((uint32_t)2)
#define EFI_PCI_WIDTH_UINT64 ((uint32_t)3)
#define EFI_PCI_WIDTH_FIFO_UINT8 ((uint32_t)4)
#define EFI_PCI_WIDTH_FIFO_UINT16 ((uint32_t)5)
#define EFI_PCI_WIDTH_FIFO_UINT32 ((uint32_t)6)
#define EFI_PCI_WIDTH_FIFO_UINT64 ((uint32_t)7)
#define EFI_PCI_WIDTH_FILL_UINT8 ((uint32_t)8)
#define EFI_PCI_WIDTH_FILL_UINT16 ((uint32_t)9)
#define EFI_PCI_WIDTH_FILL_UINT32 ((uint32_t)10)
#define EFI_PCI_WIDTH_FILL_UINT64 ((uint32_t)11)
#define EFI_PCI_WIDTH_MAXIMUM ((uint32_t)12)

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint32_t Width,
    uint64_t Address,
    uint64_t Mask,
    uint64_t Value,
    uint64_t Delay,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint32_t Width,
    uint64_t Address,
    size_t Count,
    void *Buffer
);

struct efi_pci_root_bridge_io_protocol_access {
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM Read;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_IO_MEM Write;
};

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

#define EFI_PCI_OPERATION_BUS_MASTER_READ ((uint32_t)0)
#define EFI_PCI_OPERATION_BUS_MASTER_WRITE ((uint32_t)1)
#define EFI_PCI_OPERATION_BUS_MASTER_COMMON_BUFFER ((uint32_t)2)
#define EFI_PCI_OPERATION_BUS_MASTER_READ64 ((uint32_t)3)
#define EFI_PCI_OPERATION_BUS_MASTER_WRITE64 ((uint32_t)4)
#define EFI_PCI_OPERATION_BUS_MASTER_COMMON_BUFFER64 ((uint32_t)5)
#define EFI_PCI_OPERATION_MAXIMUM ((uint32_t)6)

/* Layout of the uint64_t Address that Pci.Read() and Pci.Write() take. */
struct efi_pci_root_bridge_io_protocol_pci_address {
    uint8_t Register;
    uint8_t Function;
    uint8_t Device;
    uint8_t Bus;
    uint32_t ExtendedRegister;
};

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_COPY_MEM)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint32_t Width,
    uint64_t DestAddress,
    uint64_t SrcAddress,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_MAP)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint32_t Operation,
    void *HostAddress,
    size_t *NumberOfBytes,
    EFI_PHYSICAL_ADDRESS *DeviceAddress,
    void **Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_UNMAP)(
    struct efi_pci_root_bridge_io_protocol *This,
    void *Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_ALLOCATE_BUFFER)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint32_t Type,
    uint32_t MemoryType,
    size_t Pages,
    void **HostAddress,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FREE_BUFFER)(
    struct efi_pci_root_bridge_io_protocol *This,
    size_t Pages,
    void *HostAddress
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_FLUSH)(
    struct efi_pci_root_bridge_io_protocol *This
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GET_ATTRIBUTES)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint64_t *Supports,
    uint64_t *Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_SET_ATTRIBUTES)(
    struct efi_pci_root_bridge_io_protocol *This,
    uint64_t Attributes,
    uint64_t *ResourceBase,
    uint64_t *ResourceLength
);

typedef EFI_STATUS (EFI_API *EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_CONFIGURATION)(
    struct efi_pci_root_bridge_io_protocol *This,
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

struct efi_acpi_address_space_descriptor {
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
} __attribute__((__packed__));

struct efi_acpi_end_tag_descriptor {
    uint8_t Desc;
    uint8_t Checksum;
} __attribute__((__packed__));

struct efi_pci_root_bridge_io_protocol {
    EFI_HANDLE ParentHandle;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM PollMem;
    EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_POLL_IO_MEM PollIo;
    struct efi_pci_root_bridge_io_protocol_access Mem;
    struct efi_pci_root_bridge_io_protocol_access Io;
    struct efi_pci_root_bridge_io_protocol_access Pci;
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

struct efi_pci_io_protocol;

#define EFI_PCI_IO_WIDTH_UINT8 ((uint32_t)0)
#define EFI_PCI_IO_WIDTH_UINT16 ((uint32_t)1)
#define EFI_PCI_IO_WIDTH_UINT32 ((uint32_t)2)
#define EFI_PCI_IO_WIDTH_UINT64 ((uint32_t)3)
#define EFI_PCI_IO_WIDTH_FIFO_UINT8 ((uint32_t)4)
#define EFI_PCI_IO_WIDTH_FIFO_UINT16 ((uint32_t)5)
#define EFI_PCI_IO_WIDTH_FIFO_UINT32 ((uint32_t)6)
#define EFI_PCI_IO_WIDTH_FIFO_UINT64 ((uint32_t)7)
#define EFI_PCI_IO_WIDTH_FILL_UINT8 ((uint32_t)8)
#define EFI_PCI_IO_WIDTH_FILL_UINT16 ((uint32_t)9)
#define EFI_PCI_IO_WIDTH_FILL_UINT32 ((uint32_t)10)
#define EFI_PCI_IO_WIDTH_FILL_UINT64 ((uint32_t)11)
#define EFI_PCI_IO_WIDTH_MAXIMUM ((uint32_t)12)

#define EFI_PCI_IO_PASS_THROUGH_BAR 0xff

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_POLL_IO_MEM)(
    struct efi_pci_io_protocol *This,
    uint32_t Width,
    uint8_t BarIndex,
    uint64_t Offset,
    uint64_t Mask,
    uint64_t Value,
    uint64_t Delay,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_IO_MEM)(
    struct efi_pci_io_protocol *This,
    uint32_t Width,
    uint8_t BarIndex,
    uint64_t Offset,
    size_t Count,
    void *Buffer
);

struct efi_pci_io_protocol_access {
    EFI_PCI_IO_PROTOCOL_IO_MEM Read;
    EFI_PCI_IO_PROTOCOL_IO_MEM Write;
};

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_CONFIG)(
    struct efi_pci_io_protocol *This,
    uint32_t Width,
    uint32_t Offset,
    size_t Count,
    void *Buffer
);

struct efi_pci_io_protocol_config_access {
    EFI_PCI_IO_PROTOCOL_CONFIG Read;
    EFI_PCI_IO_PROTOCOL_CONFIG Write;
};

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

#define EFI_PCI_IO_OPERATION_BUS_MASTER_READ ((uint32_t)0)
#define EFI_PCI_IO_OPERATION_BUS_MASTER_WRITE ((uint32_t)1)
#define EFI_PCI_IO_OPERATION_BUS_MASTER_COMMON_BUFFER ((uint32_t)2)
#define EFI_PCI_IO_OPERATION_MAXIMUM ((uint32_t)3)

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_COPY_MEM)(
    struct efi_pci_io_protocol *This,
    uint32_t Width,
    uint8_t DestBarIndex,
    uint64_t DestOffset,
    uint8_t SrcBarIndex,
    uint64_t SrcOffset,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_MAP)(
    struct efi_pci_io_protocol *This,
    uint32_t Operation,
    void *HostAddress,
    size_t *NumberOfBytes,
    EFI_PHYSICAL_ADDRESS *DeviceAddress,
    void **Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_UNMAP)(
    struct efi_pci_io_protocol *This,
    void *Mapping
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_ALLOCATE_BUFFER)(
    struct efi_pci_io_protocol *This,
    uint32_t Type,
    uint32_t MemoryType,
    size_t Pages,
    void **HostAddress,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_FREE_BUFFER)(
    struct efi_pci_io_protocol *This,
    size_t Pages,
    void *HostAddress
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_FLUSH)(struct efi_pci_io_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_GET_LOCATION)(
    struct efi_pci_io_protocol *This,
    uintptr_t *SegmentNumber,
    uintptr_t *BusNumber,
    uintptr_t *DeviceNumber,
    uintptr_t *FunctionNumber
);

#define EFI_PCI_IO_ATTRIBUTE_OPERATION_GET ((uint32_t)0)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_SET ((uint32_t)1)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_ENABLE ((uint32_t)2)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_DISABLE ((uint32_t)3)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_SUPPORTED ((uint32_t)4)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_MAXIMUM ((uint32_t)5)

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_ATTRIBUTES)(
    struct efi_pci_io_protocol *This,
    uint32_t Operation,
    uint64_t Attributes,
    uint64_t *Result
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_GET_BAR_ATTRIBUTES)(
    struct efi_pci_io_protocol *This,
    uint8_t BarIndex,
    uint64_t *Supports,
    void **Resources
);

typedef EFI_STATUS (EFI_API *EFI_PCI_IO_PROTOCOL_SET_BAR_ATTRIBUTES)(
    struct efi_pci_io_protocol *This,
    uint64_t Attributes,
    uint8_t BarIndex,
    uint64_t *Offset,
    uint64_t *Length
);

struct efi_pci_io_protocol {
    EFI_PCI_IO_PROTOCOL_POLL_IO_MEM PollMem;
    EFI_PCI_IO_PROTOCOL_POLL_IO_MEM PollIo;
    struct efi_pci_io_protocol_access Mem;
    struct efi_pci_io_protocol_access Io;
    struct efi_pci_io_protocol_config_access Pci;
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

struct efi_standard_pci_expansion_rom_header {
    uint16_t Signature;
    uint8_t Reserved[0x16];
    uint16_t PcirOffset;
} __attribute__((__packed__));

struct efi_pci_expansion_rom_header {
    uint16_t Signature;
    uint16_t InitializationSize;
    uint32_t EfiSignature;
    uint16_t EfiSubsystem;
    uint16_t EfiMachineType;
    uint16_t CompressionType;
    uint8_t Reserved[8];
    uint16_t EfiImageHeaderOffset;
    uint16_t PcirOffset;
} __attribute__((__packed__));

struct efi_pci_data_structure {
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
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
