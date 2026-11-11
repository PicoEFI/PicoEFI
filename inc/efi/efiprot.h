#ifndef EFI_EFIPROT_H
#define EFI_EFIPROT_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efiapi.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
    { 0x5b1b31a1, 0x9562, 0x11d2, { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

struct efi_loaded_image_protocol {
    uint32_t revision;
    efi_handle parent_handle;
    struct efi_system_table *system_table;

    efi_handle device_handle;
    struct efi_device_path_protocol *file_path;
    void *reserved;

    uint32_t load_options_size;
    void *load_options;

    void *image_base;
    uint64_t image_size;
    uint32_t image_code_type;
    uint32_t image_data_type;
    efi_image_unload unload;
};

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
    { 0xbc62157e, 0x3e33, 0x4fec, { 0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf } }

#define EFI_DRIVER_BINDING_PROTOCOL_GUID \
    { 0x18a031ab, 0xb443, 0x4d1a, { 0xa5, 0xc0, 0x0c, 0x09, 0x26, 0x1e, 0x9f, 0x71 } }

struct efi_driver_binding_protocol;

typedef efi_status (EFI_API *efi_driver_binding_protocol_supported)(
    struct efi_driver_binding_protocol *self,
    efi_handle controller_handle,
    struct efi_device_path_protocol *remaining_device_path
);

typedef efi_status (EFI_API *efi_driver_binding_protocol_start)(
    struct efi_driver_binding_protocol *self,
    efi_handle controller_handle,
    struct efi_device_path_protocol *remaining_device_path
);

typedef efi_status (EFI_API *efi_driver_binding_protocol_stop)(
    struct efi_driver_binding_protocol *self,
    efi_handle controller_handle,
    size_t number_of_children,
    efi_handle *child_handle_buffer
);

struct efi_driver_binding_protocol {
    efi_driver_binding_protocol_supported supported;
    efi_driver_binding_protocol_start start;
    efi_driver_binding_protocol_stop stop;
    uint32_t version;
    efi_handle image_handle;
    efi_handle driver_binding_handle;
};

#define EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_GUID \
    { 0x6b30c738, 0xa391, 0x11d4, { 0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

struct efi_platform_driver_override_protocol;

typedef efi_status (EFI_API *efi_platform_driver_override_get_driver)(
    struct efi_platform_driver_override_protocol *self,
    efi_handle controller_handle,
    efi_handle *driver_image_handle
);

typedef efi_status (EFI_API *efi_platform_driver_override_get_driver_path)(
    struct efi_platform_driver_override_protocol *self,
    efi_handle controller_handle,
    struct efi_device_path_protocol **driver_image_path
);

typedef efi_status (EFI_API *efi_platform_driver_override_driver_loaded)(
    struct efi_platform_driver_override_protocol *self,
    efi_handle controller_handle,
    struct efi_device_path_protocol *driver_image_path,
    efi_handle driver_image_handle
);

struct efi_platform_driver_override_protocol {
    efi_platform_driver_override_get_driver get_driver;
    efi_platform_driver_override_get_driver_path get_driver_path;
    efi_platform_driver_override_driver_loaded driver_loaded;
};

#define EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_GUID \
    { 0x3bc1b285, 0x8a15, 0x4a82, { 0xaa, 0xbf, 0x4d, 0x7d, 0x13, 0xfb, 0x32, 0x65 } }

struct efi_bus_specific_driver_override_protocol;

typedef efi_status (EFI_API *efi_bus_specific_driver_override_get_driver)(
    struct efi_bus_specific_driver_override_protocol *self,
    efi_handle *driver_image_handle
);

struct efi_bus_specific_driver_override_protocol {
    efi_bus_specific_driver_override_get_driver get_driver;
};

#define EFI_COMPONENT_NAME2_PROTOCOL_GUID \
    { 0x6a7a5cff, 0xe8d9, 0x4f70, { 0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14 } }

struct efi_component_name2_protocol;

typedef efi_status (EFI_API *efi_component_name_get_driver_name)(
    struct efi_component_name2_protocol *self,
    char *language,
    uint16_t **driver_name
);

typedef efi_status (EFI_API *efi_component_name_get_controller_name)(
    struct efi_component_name2_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    char *language,
    uint16_t **controller_name
);

struct efi_component_name2_protocol {
    efi_component_name_get_driver_name get_driver_name;
    efi_component_name_get_controller_name get_controller_name;
    char *supported_languages;
};

struct efi_service_binding_protocol;

typedef efi_status (EFI_API *efi_service_binding_create_child)(
    struct efi_service_binding_protocol *self,
    efi_handle *child_handle
);

typedef efi_status (EFI_API *efi_service_binding_destroy_child)(
    struct efi_service_binding_protocol *self,
    efi_handle child_handle
);

struct efi_service_binding_protocol {
    efi_service_binding_create_child create_child;
    efi_service_binding_destroy_child destroy_child;
};

#define EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_GUID \
    { 0xb1ee129e, 0xda36, 0x4181, { 0x91, 0xf8, 0x04, 0xa4, 0x92, 0x37, 0x66, 0xa7 } }

struct efi_driver_family_override_protocol;

typedef uint32_t (EFI_API *efi_driver_family_override_get_version)(
    struct efi_driver_family_override_protocol *self
);

struct efi_driver_family_override_protocol {
    efi_driver_family_override_get_version get_version;
};

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
    { 0x9042a9de, 0x23dc, 0x4a38, { 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } }

struct efi_graphics_output_protocol;

struct efi_pixel_bitmask {
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
    uint32_t reserved_mask;
};

#define EFI_PIXEL_RED_GREEN_BLUE_RESERVED_8_BIT_PER_COLOR ((uint32_t)0)
#define EFI_PIXEL_BLUE_GREEN_RED_RESERVED_8_BIT_PER_COLOR ((uint32_t)1)
#define EFI_PIXEL_BIT_MASK ((uint32_t)2)
#define EFI_PIXEL_BLT_ONLY ((uint32_t)3)
#define EFI_PIXEL_FORMAT_MAX ((uint32_t)4)

struct efi_graphics_output_mode_information {
    uint32_t version;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t pixel_format;
    struct efi_pixel_bitmask pixel_information;
    uint32_t pixels_per_scan_line;
};

struct efi_graphics_output_protocol_mode {
    uint32_t max_mode;
    uint32_t mode;
    struct efi_graphics_output_mode_information *info;
    size_t size_of_info;
    efi_physical_address frame_buffer_base;
    size_t frame_buffer_size;
};

typedef efi_status (EFI_API *efi_graphics_output_protocol_query_mode)(
    struct efi_graphics_output_protocol *self,
    uint32_t mode_number,
    size_t *size_of_info,
    struct efi_graphics_output_mode_information **info
);

typedef efi_status (EFI_API *efi_graphics_output_protocol_set_mode)(
    struct efi_graphics_output_protocol *self,
    uint32_t mode_number
);

struct efi_graphics_output_blt_pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

// Not in the specification: a pixel together with its 32-bit value.
union efi_graphics_output_blt_pixel_union {
    struct efi_graphics_output_blt_pixel pixel;
    uint32_t raw;
};

#define EFI_BLT_VIDEO_FILL ((uint32_t)0)
#define EFI_BLT_VIDEO_TO_BLT_BUFFER ((uint32_t)1)
#define EFI_BLT_BUFFER_TO_VIDEO ((uint32_t)2)
#define EFI_BLT_VIDEO_TO_VIDEO ((uint32_t)3)
#define EFI_GRAPHICS_OUTPUT_BLT_OPERATION_MAX ((uint32_t)4)

typedef efi_status (EFI_API *efi_graphics_output_protocol_blt)(
    struct efi_graphics_output_protocol *self,
    struct efi_graphics_output_blt_pixel *blt_buffer,
    uint32_t blt_operation,
    size_t source_x,
    size_t source_y,
    size_t destination_x,
    size_t destination_y,
    size_t width,
    size_t height,
    size_t delta
);

struct efi_graphics_output_protocol {
    efi_graphics_output_protocol_query_mode query_mode;
    efi_graphics_output_protocol_set_mode set_mode;
    efi_graphics_output_protocol_blt blt;
    struct efi_graphics_output_protocol_mode *mode;
};

#define EFI_EDID_DISCOVERED_PROTOCOL_GUID \
    { 0x1c0c34f6, 0xd380, 0x41fa, { 0xa0, 0x49, 0x8a, 0xd0, 0x6c, 0x1a, 0x66, 0xaa } }

struct efi_edid_discovered_protocol {
    uint32_t size_of_edid;
    uint8_t *edid;
};

#define EFI_EDID_ACTIVE_PROTOCOL_GUID \
    { 0xbd8c1056, 0x9f36, 0x44ec, { 0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86 } }

struct efi_edid_active_protocol {
    uint32_t size_of_edid;
    uint8_t *edid;
};

#define EFI_EDID_OVERRIDE_PROTOCOL_GUID \
    { 0x48ecb431, 0xfb72, 0x45c0, { 0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x04, 0x0b, 0xd5 } }

struct efi_edid_override_protocol;

// child_handle points to the handle: the specification keeps this historical
// typing on purpose.
typedef efi_status (EFI_API *efi_edid_override_protocol_get_edid)(
    struct efi_edid_override_protocol *self,
    efi_handle *child_handle,
    uint32_t *attributes,
    size_t *edid_size,
    uint8_t **edid
);

#define EFI_EDID_OVERRIDE_DONT_OVERRIDE 0x01
#define EFI_EDID_OVERRIDE_ENABLE_HOT_PLUG 0x02

struct efi_edid_override_protocol {
    efi_edid_override_protocol_get_edid get_edid;
};

#define EFI_LOAD_FILE_PROTOCOL_GUID \
    { 0x56ec3091, 0x954c, 0x11d2, { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

struct efi_load_file_protocol;

typedef efi_status (EFI_API *efi_load_file)(
    struct efi_load_file_protocol *self,
    struct efi_device_path_protocol *file_path,
    bool boot_policy,
    size_t *buffer_size,
    void *buffer
);

struct efi_load_file_protocol {
    efi_load_file load_file;
};

#define EFI_LOAD_FILE2_PROTOCOL_GUID \
    { 0x4006c0c1, 0xfcb3, 0x403e, { 0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d } }

typedef struct efi_load_file_protocol efi_load_file2_protocol;

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x0964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

struct efi_simple_file_system_protocol;

struct efi_file_protocol;

typedef efi_status (EFI_API *efi_simple_file_system_protocol_open_volume)(
    struct efi_simple_file_system_protocol *self,
    struct efi_file_protocol **root
);

struct efi_simple_file_system_protocol {
    uint64_t revision;
    efi_simple_file_system_protocol_open_volume open_volume;
};

#define EFI_FILE_PROTOCOL_REVISION 0x00010000
#define EFI_FILE_PROTOCOL_REVISION2 0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION EFI_FILE_PROTOCOL_REVISION2

typedef efi_status (EFI_API *efi_file_open)(
    struct efi_file_protocol *self,
    struct efi_file_protocol **new_handle,
    uint16_t *file_name,
    uint64_t open_mode,
    uint64_t attributes
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

typedef efi_status (EFI_API *efi_file_close)(struct efi_file_protocol *self);

typedef efi_status (EFI_API *efi_file_delete)(struct efi_file_protocol *self);

typedef efi_status (EFI_API *efi_file_read)(
    struct efi_file_protocol *self,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_file_write)(
    struct efi_file_protocol *self,
    size_t *buffer_size,
    void *buffer
);

struct efi_file_io_token {
    efi_event event;
    efi_status status;
    size_t buffer_size;
    void *buffer;
};

typedef efi_status (EFI_API *efi_file_open_ex)(
    struct efi_file_protocol *self,
    struct efi_file_protocol **new_handle,
    uint16_t *file_name,
    uint64_t open_mode,
    uint64_t attributes,
    struct efi_file_io_token *token
);

typedef efi_status (EFI_API *efi_file_read_ex)(
    struct efi_file_protocol *self,
    struct efi_file_io_token *token
);

typedef efi_status (EFI_API *efi_file_write_ex)(
    struct efi_file_protocol *self,
    struct efi_file_io_token *token
);

typedef efi_status (EFI_API *efi_file_flush_ex)(
    struct efi_file_protocol *self,
    struct efi_file_io_token *token
);

typedef efi_status (EFI_API *efi_file_set_position)(
    struct efi_file_protocol *self,
    uint64_t position
);

typedef efi_status (EFI_API *efi_file_get_position)(
    struct efi_file_protocol *self,
    uint64_t *position
);

typedef efi_status (EFI_API *efi_file_get_info)(
    struct efi_file_protocol *self,
    struct efi_guid *information_type,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_file_set_info)(
    struct efi_file_protocol *self,
    struct efi_guid *information_type,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_file_flush)(struct efi_file_protocol *self);

struct efi_file_protocol {
    uint64_t revision;
    efi_file_open open;
    efi_file_close close;
#ifdef __cplusplus
    efi_file_delete delete_;
#else
    efi_file_delete delete;
#endif
    efi_file_read read;
    efi_file_write write;
    efi_file_get_position get_position;
    efi_file_set_position set_position;
    efi_file_get_info get_info;
    efi_file_set_info set_info;
    efi_file_flush flush;
    // The Ex services exist from EFI_FILE_PROTOCOL_REVISION2 on.
    efi_file_open_ex open_ex;
    efi_file_read_ex read_ex;
    efi_file_write_ex write_ex;
    efi_file_flush_ex flush_ex;
};

#define EFI_FILE_INFO_ID \
    { 0x09576e92, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

// Name arrays have one element, as in firmware ([] in print); EFI_SIZE_OF_* is
// the fixed part.
struct efi_file_info {
    uint64_t size;
    uint64_t file_size;
    uint64_t physical_size;
    struct efi_time create_time;
    struct efi_time last_access_time;
    struct efi_time modification_time;
    uint64_t attribute;
    uint16_t file_name[1];
};

#define EFI_SIZE_OF_EFI_FILE_INFO offsetof(struct efi_file_info, file_name)

#define EFI_FILE_SYSTEM_INFO_ID \
    { 0x09576e93, 0x6d3f, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

struct efi_file_system_info {
    uint64_t size;
    uint8_t read_only;
    uint64_t volume_size;
    uint64_t free_space;
    uint32_t block_size;
    uint16_t volume_label[1];
};

#define EFI_SIZE_OF_EFI_FILE_SYSTEM_INFO offsetof(struct efi_file_system_info, volume_label)

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID \
    { 0xdb47d7d3, 0xfe81, 0x11d3, { 0x9a, 0x35, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

struct efi_file_system_volume_label {
    uint16_t volume_label[1];
};

#define EFI_SIZE_OF_EFI_FILE_SYSTEM_VOLUME_LABEL \
    offsetof(struct efi_file_system_volume_label, volume_label)

#define EFI_DISK_IO_PROTOCOL_GUID \
    { 0xce345171, 0xba0b, 0x11d2, { 0x8e, 0x4f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

struct efi_disk_io_protocol;

typedef efi_status (EFI_API *efi_disk_read)(
    struct efi_disk_io_protocol *self,
    uint32_t media_id,
    uint64_t offset,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_disk_write)(
    struct efi_disk_io_protocol *self,
    uint32_t media_id,
    uint64_t offset,
    size_t buffer_size,
    void *buffer
);

struct efi_disk_io_protocol {
    uint64_t revision;
    efi_disk_read read_disk;
    efi_disk_write write_disk;
};

#define EFI_DISK_IO2_PROTOCOL_GUID \
    { 0x151c8eae, 0x7f2c, 0x472c, { 0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88 } }

#define EFI_DISK_IO2_PROTOCOL_REVISION 0x00020000

struct efi_disk_io2_protocol;

struct efi_disk_io2_token {
    efi_event event;
    efi_status transaction_status;
};

typedef efi_status (EFI_API *efi_disk_cancel_ex)(struct efi_disk_io2_protocol *self);

typedef efi_status (EFI_API *efi_disk_read_ex)(
    struct efi_disk_io2_protocol *self,
    uint32_t media_id,
    uint64_t offset,
    struct efi_disk_io2_token *token,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_disk_write_ex)(
    struct efi_disk_io2_protocol *self,
    uint32_t media_id,
    uint64_t offset,
    struct efi_disk_io2_token *token,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_disk_flush_ex)(
    struct efi_disk_io2_protocol *self,
    struct efi_disk_io2_token *token
);

struct efi_disk_io2_protocol {
    uint64_t revision;
    efi_disk_cancel_ex cancel;
    efi_disk_read_ex read_disk_ex;
    efi_disk_write_ex write_disk_ex;
    efi_disk_flush_ex flush_disk_ex;
};

#define EFI_BLOCK_IO_PROTOCOL_GUID \
    { 0x964e5b21, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

#define EFI_BLOCK_IO_PROTOCOL_REVISION 0x00010000
#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2 << 16) | (31))

struct efi_block_io_protocol;

struct efi_block_io_media {
    uint32_t media_id;
    uint8_t removable_media;
    uint8_t media_present;
    uint8_t logical_partition;
    uint8_t read_only;
    uint8_t write_caching;
    uint32_t block_size;
    uint32_t io_align;
    efi_lba last_block;
    // Valid from EFI_BLOCK_IO_PROTOCOL_REVISION2 on.
    efi_lba lowest_aligned_lba;
    uint32_t logical_blocks_per_physical_block;
    // Valid from EFI_BLOCK_IO_PROTOCOL_REVISION3 on.
    uint32_t optimal_transfer_length_granularity;
};

typedef efi_status (EFI_API *efi_block_reset)(
    struct efi_block_io_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_block_read)(
    struct efi_block_io_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_block_write)(
    struct efi_block_io_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_block_flush)(struct efi_block_io_protocol *self);

struct efi_block_io_protocol {
    uint64_t revision;
    struct efi_block_io_media *media;
    efi_block_reset reset;
    efi_block_read read_blocks;
    efi_block_write write_blocks;
    efi_block_flush flush_blocks;
};

#define EFI_BLOCK_IO2_PROTOCOL_GUID \
    { 0xa77b2472, 0xe282, 0x4e9f, { 0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1 } }

struct efi_block_io2_protocol;

struct efi_block_io2_token {
    efi_event event;
    efi_status transaction_status;
};

typedef efi_status (EFI_API *efi_block_reset_ex)(
    struct efi_block_io2_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_block_read_ex)(
    struct efi_block_io2_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    struct efi_block_io2_token *token,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_block_write_ex)(
    struct efi_block_io2_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    struct efi_block_io2_token *token,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_block_flush_ex)(
    struct efi_block_io2_protocol *self,
    struct efi_block_io2_token *token
);

struct efi_block_io2_protocol {
    struct efi_block_io_media *media;
    efi_block_reset_ex reset;
    efi_block_read_ex read_blocks_ex;
    efi_block_write_ex write_blocks_ex;
    efi_block_flush_ex flush_blocks_ex;
};

#define EFI_UNICODE_COLLATION_PROTOCOL2_GUID \
    { 0xa4c751fc, 0x23ae, 0x4c3e, { 0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49 } }

struct efi_unicode_collation_protocol;

typedef intptr_t (EFI_API *efi_unicode_collation_stricoll)(
    struct efi_unicode_collation_protocol *self,
    uint16_t *s1,
    uint16_t *s2
);

typedef bool (EFI_API *efi_unicode_collation_metaimatch)(
    struct efi_unicode_collation_protocol *self,
    uint16_t *string,
    uint16_t *pattern
);

typedef void (EFI_API *efi_unicode_collation_strlwr)(
    struct efi_unicode_collation_protocol *self,
    uint16_t *string
);

typedef void (EFI_API *efi_unicode_collation_strupr)(
    struct efi_unicode_collation_protocol *self,
    uint16_t *string
);

typedef void (EFI_API *efi_unicode_collation_fattostr)(
    struct efi_unicode_collation_protocol *self,
    size_t fat_size,
    char *fat,
    uint16_t *string
);

typedef bool (EFI_API *efi_unicode_collation_strtofat)(
    struct efi_unicode_collation_protocol *self,
    uint16_t *string,
    size_t fat_size,
    char *fat
);

struct efi_unicode_collation_protocol {
    efi_unicode_collation_stricoll stri_coll;
    efi_unicode_collation_metaimatch metai_match;
    efi_unicode_collation_strlwr str_lwr;
    efi_unicode_collation_strupr str_upr;
    efi_unicode_collation_fattostr fat_to_str;
    efi_unicode_collation_strtofat str_to_fat;
    char *supported_languages;
};

// Not in the specification: the byte order mark that starts a UCS-2 text file.
#define EFI_UNICODE_BYTE_ORDER_MARK ((uint16_t)0xfeff)

#define EFI_EBC_PROTOCOL_GUID \
    { 0x13ac6dd1, 0x73d0, 0x11d4, { 0xb0, 0x6b, 0x00, 0xaa, 0x00, 0xbd, 0x6d, 0xe7 } }

struct efi_ebc_protocol;

typedef efi_status (EFI_API *efi_ebc_create_thunk)(
    struct efi_ebc_protocol *self,
    efi_handle image_handle,
    void *ebc_entry_point,
    void **thunk
);

typedef efi_status (EFI_API *efi_ebc_unload_image)(
    struct efi_ebc_protocol *self,
    efi_handle image_handle
);

typedef efi_status (EFI_API *efi_ebc_icache_flush)(
    efi_physical_address start,
    uint64_t length
);

// The prototype prints **self and *flush; the descriptions want one level
// less.
typedef efi_status (EFI_API *efi_ebc_register_icache_flush)(
    struct efi_ebc_protocol *self,
    efi_ebc_icache_flush flush
);

typedef efi_status (EFI_API *efi_ebc_get_version)(
    struct efi_ebc_protocol *self,
    uint64_t *version
);

struct efi_ebc_protocol {
    efi_ebc_create_thunk create_thunk;
    efi_ebc_unload_image unload_image;
    efi_ebc_register_icache_flush register_icache_flush;
    efi_ebc_get_version get_version;
};

#define EFI_HASH_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x42881c98, 0xa4f3, 0x44b0, { 0xa3, 0x9d, 0xdf, 0xa1, 0x86, 0x67, 0xd8, 0xcd } }

#define EFI_HASH_PROTOCOL_GUID \
    { 0xc5184932, 0xdba5, 0x46db, { 0xa5, 0xba, 0xcc, 0x0b, 0xda, 0x9c, 0x14, 0x35 } }

struct efi_hash_protocol;

typedef uint8_t efi_md5_hash[16];
typedef uint8_t efi_sha1_hash[20];
typedef uint8_t efi_sha224_hash[28];
typedef uint8_t efi_sha256_hash[32];
typedef uint8_t efi_sha384_hash[48];
typedef uint8_t efi_sha512_hash[64];

union efi_hash_output {
    efi_md5_hash *md5_hash;
    efi_sha1_hash *sha1_hash;
    efi_sha224_hash *sha224_hash;
    efi_sha256_hash *sha256_hash;
    efi_sha384_hash *sha384_hash;
    efi_sha512_hash *sha512_hash;
};

// get_hash_size() and hash() are printed as plain prototypes; the names here
// are the member types of the protocol structure.
typedef efi_status (EFI_API *efi_hash_get_hash_size)(
    const struct efi_hash_protocol *self,
    const struct efi_guid *hash_algorithm,
    size_t *hash_size
);

typedef efi_status (EFI_API *efi_hash_hash)(
    const struct efi_hash_protocol *self,
    const struct efi_guid *hash_algorithm,
    bool extend,
    const uint8_t *message,
    uint64_t message_size,
    union efi_hash_output *hash
);

struct efi_hash_protocol {
    efi_hash_get_hash_size get_hash_size;
    efi_hash_hash hash;
};

#define EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID \
    { 0x24c5dc2f, 0x53e2, 0x40ca, { 0x9e, 0xd6, 0xa5, 0xd9, 0xa4, 0x9f, 0x46, 0x3b } }

#define EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID \
    { 0x8628752a, 0x6cb7, 0x4814, { 0x96, 0xfc, 0x24, 0xa8, 0x15, 0xac, 0x22, 0x26 } }

// The Hash2 algorithms: efisectech.h takes them from here rather than defining
// them again.
#define EFI_HASH_ALGORITHM_SHA1_GUID \
    { 0x2ae9d80f, 0x3fb2, 0x4095, { 0xb7, 0xb1, 0xe9, 0x31, 0x57, 0xb9, 0x46, 0xb6 } }

#define EFI_HASH_ALGORITHM_SHA224_GUID \
    { 0x8df01a06, 0x9bd5, 0x4bf7, { 0xb0, 0x21, 0xdb, 0x4f, 0xd9, 0xcc, 0xf4, 0x5b } }

#define EFI_HASH_ALGORITHM_SHA256_GUID \
    { 0x51aa59de, 0xfdf2, 0x4ea3, { 0xbc, 0x63, 0x87, 0x5f, 0xb7, 0x84, 0x2e, 0xe9 } }

#define EFI_HASH_ALGORITHM_SHA384_GUID \
    { 0xefa96432, 0xde33, 0x4dd2, { 0xae, 0xe6, 0x32, 0x8c, 0x33, 0xdf, 0x77, 0x7a } }

#define EFI_HASH_ALGORITHM_SHA512_GUID \
    { 0xcaa4381e, 0x750c, 0x4770, { 0xb8, 0x70, 0x7a, 0x23, 0xb4, 0xe4, 0x21, 0x30 } }

#define EFI_HASH_ALGORITHM_MD5_GUID \
    { 0xaf7c79c, 0x65b5, 0x4319, { 0xb0, 0xae, 0x44, 0xec, 0x48, 0x4e, 0x4a, 0xd7 } }

#define EFI_RNG_PROTOCOL_GUID \
    { 0x3152bca5, 0xeade, 0x433d, { 0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44 } }

struct efi_rng_protocol;

typedef struct efi_guid efi_rng_algorithm;

typedef efi_status (EFI_API *efi_rng_get_info)(
    struct efi_rng_protocol *self,
    size_t *rng_algorithm_list_size,
    efi_rng_algorithm *rng_algorithm_list
);

typedef efi_status (EFI_API *efi_rng_get_rng)(
    struct efi_rng_protocol *self,
    efi_rng_algorithm *rng_algorithm,
    size_t rng_value_length,
    uint8_t *rng_value
);

struct efi_rng_protocol {
    efi_rng_get_info get_info;
    efi_rng_get_rng get_rng;
};

#define EFI_RNG_ALGORITHM_SP800_90_HASH_256_GUID \
    { 0xa7af67cb, 0x603b, 0x4d42, { 0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96 } }

#define EFI_RNG_ALGORITHM_SP800_90_HMAC_256_GUID \
    { 0xc5149b43, 0xae85, 0x4f53, { 0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7 } }

#define EFI_RNG_ALGORITHM_SP800_90_CTR_256_GUID \
    { 0x44f0de6e, 0x4d8c, 0x4045, { 0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e } }

#define EFI_RNG_ALGORITHM_X9_31_3DES_GUID \
    { 0x63c4785a, 0xca34, 0x4012, { 0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46 } }

#define EFI_RNG_ALGORITHM_X9_31_AES_GUID \
    { 0xacd03321, 0x777e, 0x4d3d, { 0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9 } }

#define EFI_RNG_ALGORITHM_RAW \
    { 0xe43176d7, 0xb6e8, 0x4827, { 0xb7, 0x84, 0x7f, 0xfd, 0xc4, 0xb6, 0x85, 0x61 } }

#define EFI_RNG_ALGORITHM_ARM_RNDR \
    { 0x43d2fde3, 0x9d4e, 0x4d79, { 0x02, 0x96, 0xa8, 0x9b, 0xca, 0x78, 0x08, 0x41 } }

#define EFI_MEMORY_ATTRIBUTE_PROTOCOL_GUID \
    { 0xf4560cf6, 0x40ec, 0x4b4a, { 0xa1, 0x92, 0xbf, 0x1d, 0x57, 0xd0, 0xb1, 0x89 } }

struct efi_memory_attribute_protocol;

typedef efi_status (EFI_API *efi_get_memory_attributes)(
    struct efi_memory_attribute_protocol *self,
    efi_physical_address base_address,
    uint64_t length,
    uint64_t *attributes
);

typedef efi_status (EFI_API *efi_set_memory_attributes)(
    struct efi_memory_attribute_protocol *self,
    efi_physical_address base_address,
    uint64_t length,
    uint64_t attributes
);

typedef efi_status (EFI_API *efi_clear_memory_attributes)(
    struct efi_memory_attribute_protocol *self,
    efi_physical_address base_address,
    uint64_t length,
    uint64_t attributes
);

struct efi_memory_attribute_protocol {
    efi_get_memory_attributes get_memory_attributes;
    efi_set_memory_attributes set_memory_attributes;
    efi_clear_memory_attributes clear_memory_attributes;
};

#ifdef __cplusplus
}
#endif

#endif
