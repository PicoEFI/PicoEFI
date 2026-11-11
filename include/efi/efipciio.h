#ifndef EFI_EFIPCIIO_H
#define EFI_EFIPCIIO_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_GUID \
    { 0x2f707ebb, 0x4a1a, 0x11d4, { 0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

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

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_poll_io_mem)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint32_t width,
    uint64_t address,
    uint64_t mask,
    uint64_t value,
    uint64_t delay,
    uint64_t *result
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_io_mem)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint32_t width,
    uint64_t address,
    size_t count,
    void *buffer
);

struct efi_pci_root_bridge_io_protocol_access {
    efi_pci_root_bridge_io_protocol_io_mem read;
    efi_pci_root_bridge_io_protocol_io_mem write;
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

// Layout of the uint64_t address that pci.read() and pci.write() take.
struct efi_pci_root_bridge_io_protocol_pci_address {
    uint8_t register_;
    uint8_t function;
    uint8_t device;
    uint8_t bus;
    uint32_t extended_register;
};

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_copy_mem)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint32_t width,
    uint64_t dest_address,
    uint64_t src_address,
    size_t count
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_map)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint32_t operation,
    void *host_address,
    size_t *number_of_bytes,
    efi_physical_address *device_address,
    void **mapping
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_unmap)(
    struct efi_pci_root_bridge_io_protocol *self,
    void *mapping
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_allocate_buffer)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint32_t type,
    uint32_t memory_type,
    size_t pages,
    void **host_address,
    uint64_t attributes
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_free_buffer)(
    struct efi_pci_root_bridge_io_protocol *self,
    size_t pages,
    void *host_address
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_flush)(
    struct efi_pci_root_bridge_io_protocol *self
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_get_attributes)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint64_t *supports,
    uint64_t *attributes
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_set_attributes)(
    struct efi_pci_root_bridge_io_protocol *self,
    uint64_t attributes,
    uint64_t *resource_base,
    uint64_t *resource_length
);

typedef efi_status (EFI_API *efi_pci_root_bridge_io_protocol_configuration)(
    struct efi_pci_root_bridge_io_protocol *self,
    void **resources
);

#define EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR_TAG 0x8a
#define EFI_ACPI_END_TAG_DESCRIPTOR_TAG 0x79

#define EFI_ACPI_ADDRESS_SPACE_TYPE_MEM 0x00
#define EFI_ACPI_ADDRESS_SPACE_TYPE_IO 0x01
#define EFI_ACPI_ADDRESS_SPACE_TYPE_BUS 0x02

#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_NON_CACHEABLE 0x00
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE 0x02
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_WRITE_COMBINING 0x04
#define EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE 0x06

struct efi_acpi_address_space_descriptor {
    uint8_t desc;
    uint16_t len;
    uint8_t res_type;
    uint8_t gen_flag;
    uint8_t specific_flag;
    uint64_t addr_space_granularity;
    uint64_t addr_range_min;
    uint64_t addr_range_max;
    uint64_t addr_translation_offset;
    uint64_t addr_len;
} __attribute__((__packed__));

struct efi_acpi_end_tag_descriptor {
    uint8_t desc;
    uint8_t checksum;
} __attribute__((__packed__));

struct efi_pci_root_bridge_io_protocol {
    efi_handle parent_handle;
    efi_pci_root_bridge_io_protocol_poll_io_mem poll_mem;
    efi_pci_root_bridge_io_protocol_poll_io_mem poll_io;
    struct efi_pci_root_bridge_io_protocol_access mem;
    struct efi_pci_root_bridge_io_protocol_access io;
    struct efi_pci_root_bridge_io_protocol_access pci;
    efi_pci_root_bridge_io_protocol_copy_mem copy_mem;
    efi_pci_root_bridge_io_protocol_map map;
    efi_pci_root_bridge_io_protocol_unmap unmap;
    efi_pci_root_bridge_io_protocol_allocate_buffer allocate_buffer;
    efi_pci_root_bridge_io_protocol_free_buffer free_buffer;
    efi_pci_root_bridge_io_protocol_flush flush;
    efi_pci_root_bridge_io_protocol_get_attributes get_attributes;
    efi_pci_root_bridge_io_protocol_set_attributes set_attributes;
    efi_pci_root_bridge_io_protocol_configuration configuration;
    uint32_t segment_number;
};

#define EFI_PCI_IO_PROTOCOL_GUID \
    { 0x4cf5b200, 0x68b8, 0x4ca5, { 0x9e, 0xec, 0xb2, 0x3e, 0x3f, 0x50, 0x02, 0x9a } }

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

typedef efi_status (EFI_API *efi_pci_io_protocol_poll_io_mem)(
    struct efi_pci_io_protocol *self,
    uint32_t width,
    uint8_t bar_index,
    uint64_t offset,
    uint64_t mask,
    uint64_t value,
    uint64_t delay,
    uint64_t *result
);

typedef efi_status (EFI_API *efi_pci_io_protocol_io_mem)(
    struct efi_pci_io_protocol *self,
    uint32_t width,
    uint8_t bar_index,
    uint64_t offset,
    size_t count,
    void *buffer
);

struct efi_pci_io_protocol_access {
    efi_pci_io_protocol_io_mem read;
    efi_pci_io_protocol_io_mem write;
};

typedef efi_status (EFI_API *efi_pci_io_protocol_config)(
    struct efi_pci_io_protocol *self,
    uint32_t width,
    uint32_t offset,
    size_t count,
    void *buffer
);

struct efi_pci_io_protocol_config_access {
    efi_pci_io_protocol_config read;
    efi_pci_io_protocol_config write;
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

typedef efi_status (EFI_API *efi_pci_io_protocol_copy_mem)(
    struct efi_pci_io_protocol *self,
    uint32_t width,
    uint8_t dest_bar_index,
    uint64_t dest_offset,
    uint8_t src_bar_index,
    uint64_t src_offset,
    size_t count
);

typedef efi_status (EFI_API *efi_pci_io_protocol_map)(
    struct efi_pci_io_protocol *self,
    uint32_t operation,
    void *host_address,
    size_t *number_of_bytes,
    efi_physical_address *device_address,
    void **mapping
);

typedef efi_status (EFI_API *efi_pci_io_protocol_unmap)(
    struct efi_pci_io_protocol *self,
    void *mapping
);

typedef efi_status (EFI_API *efi_pci_io_protocol_allocate_buffer)(
    struct efi_pci_io_protocol *self,
    uint32_t type,
    uint32_t memory_type,
    size_t pages,
    void **host_address,
    uint64_t attributes
);

typedef efi_status (EFI_API *efi_pci_io_protocol_free_buffer)(
    struct efi_pci_io_protocol *self,
    size_t pages,
    void *host_address
);

typedef efi_status (EFI_API *efi_pci_io_protocol_flush)(struct efi_pci_io_protocol *self);

typedef efi_status (EFI_API *efi_pci_io_protocol_get_location)(
    struct efi_pci_io_protocol *self,
    size_t *segment_number,
    size_t *bus_number,
    size_t *device_number,
    size_t *function_number
);

#define EFI_PCI_IO_ATTRIBUTE_OPERATION_GET ((uint32_t)0)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_SET ((uint32_t)1)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_ENABLE ((uint32_t)2)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_DISABLE ((uint32_t)3)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_SUPPORTED ((uint32_t)4)
#define EFI_PCI_IO_ATTRIBUTE_OPERATION_MAXIMUM ((uint32_t)5)

typedef efi_status (EFI_API *efi_pci_io_protocol_attributes)(
    struct efi_pci_io_protocol *self,
    uint32_t operation,
    uint64_t attributes,
    uint64_t *result
);

typedef efi_status (EFI_API *efi_pci_io_protocol_get_bar_attributes)(
    struct efi_pci_io_protocol *self,
    uint8_t bar_index,
    uint64_t *supports,
    void **resources
);

typedef efi_status (EFI_API *efi_pci_io_protocol_set_bar_attributes)(
    struct efi_pci_io_protocol *self,
    uint64_t attributes,
    uint8_t bar_index,
    uint64_t *offset,
    uint64_t *length
);

struct efi_pci_io_protocol {
    efi_pci_io_protocol_poll_io_mem poll_mem;
    efi_pci_io_protocol_poll_io_mem poll_io;
    struct efi_pci_io_protocol_access mem;
    struct efi_pci_io_protocol_access io;
    struct efi_pci_io_protocol_config_access pci;
    efi_pci_io_protocol_copy_mem copy_mem;
    efi_pci_io_protocol_map map;
    efi_pci_io_protocol_unmap unmap;
    efi_pci_io_protocol_allocate_buffer allocate_buffer;
    efi_pci_io_protocol_free_buffer free_buffer;
    efi_pci_io_protocol_flush flush;
    efi_pci_io_protocol_get_location get_location;
    efi_pci_io_protocol_attributes attributes;
    efi_pci_io_protocol_get_bar_attributes get_bar_attributes;
    efi_pci_io_protocol_set_bar_attributes set_bar_attributes;
    uint64_t rom_size;
    void *rom_image;
};

#define EFI_PCI_EXPANSION_ROM_HEADER_SIGNATURE 0xaa55
#define EFI_PCI_EXPANSION_ROM_HEADER_EFISIGNATURE 0x0ef1
#define EFI_PCI_DATA_STRUCTURE_SIGNATURE EFI_SIGNATURE_32('P', 'C', 'I', 'R')

#define EFI_PCI_CODE_TYPE_PCAT_IMAGE 0x00
#define EFI_PCI_CODE_TYPE_EFI_IMAGE 0x03

#define EFI_PCI_EXPANSION_ROM_HEADER_COMPRESSED 0x0001

struct efi_standard_pci_expansion_rom_header {
    uint16_t signature;
    uint8_t reserved[0x16];
    uint16_t pcir_offset;
} __attribute__((__packed__));

struct efi_pci_expansion_rom_header {
    uint16_t signature;
    uint16_t initialization_size;
    uint32_t efi_signature;
    uint16_t efi_subsystem;
    uint16_t efi_machine_type;
    uint16_t compression_type;
    uint8_t reserved[8];
    uint16_t efi_image_header_offset;
    uint16_t pcir_offset;
} __attribute__((__packed__));

struct efi_pci_data_structure {
    uint32_t signature;
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t reserved0;
    uint16_t length;
    uint8_t revision;
    uint8_t class_code[3];
    uint16_t image_length;
    uint16_t code_revision;
    uint8_t code_type;
    uint8_t indicator;
    uint16_t reserved1;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
