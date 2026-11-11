#ifndef EFI_EFIAPI_H
#define EFI_EFIAPI_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/eficon.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>

#ifdef __cplusplus
extern "C" {
#endif

// Each defined only if not yet defined: a PE/COFF header of the program's may
// come first.
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION
#   define EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION 10
#endif
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER
#   define EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11
#endif
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER
#   define EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 12
#endif

#ifndef EFI_IMAGE_MACHINE_IA32
#   define EFI_IMAGE_MACHINE_IA32 0x014c
#endif
#ifndef EFI_IMAGE_MACHINE_IA64
#   define EFI_IMAGE_MACHINE_IA64 0x0200
#endif
#ifndef EFI_IMAGE_MACHINE_EBC
#   define EFI_IMAGE_MACHINE_EBC 0x0ebc
#endif
#ifndef EFI_IMAGE_MACHINE_X64
#   define EFI_IMAGE_MACHINE_X64 0x8664
#endif
#ifndef EFI_IMAGE_MACHINE_ARMTHUMB_MIXED
#   define EFI_IMAGE_MACHINE_ARMTHUMB_MIXED 0x01c2
#endif
#ifndef EFI_IMAGE_MACHINE_AARCH64
#   define EFI_IMAGE_MACHINE_AARCH64 0xaa64
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV32
#   define EFI_IMAGE_MACHINE_RISCV32 0x5032
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV64
#   define EFI_IMAGE_MACHINE_RISCV64 0x5064
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV128
#   define EFI_IMAGE_MACHINE_RISCV128 0x5128
#endif
#ifndef EFI_IMAGE_MACHINE_LOONGARCH32
#   define EFI_IMAGE_MACHINE_LOONGARCH32 0x6232
#endif
#ifndef EFI_IMAGE_MACHINE_LOONGARCH64
#   define EFI_IMAGE_MACHINE_LOONGARCH64 0x6264
#endif

#ifndef EFI_IMAGE_FILE_MACHINE_EBC
#   define EFI_IMAGE_FILE_MACHINE_EBC 0x0ebc
#endif

#ifndef EFI_IMAGE_REL_EBC_ABSOLUTE
#   define EFI_IMAGE_REL_EBC_ABSOLUTE 0x0000
#endif
#ifndef EFI_IMAGE_REL_EBC_ADDR32NB
#   define EFI_IMAGE_REL_EBC_ADDR32NB 0x0001
#endif
#ifndef EFI_IMAGE_REL_EBC_REL32
#   define EFI_IMAGE_REL_EBC_REL32 0x0002
#endif
#ifndef EFI_IMAGE_REL_EBC_SECTION
#   define EFI_IMAGE_REL_EBC_SECTION 0x0003
#endif
#ifndef EFI_IMAGE_REL_EBC_SECREL
#   define EFI_IMAGE_REL_EBC_SECREL 0x0004
#endif

struct efi_system_table;

typedef efi_status (EFI_API *efi_image_entry_point)(
    efi_handle image_handle,
    struct efi_system_table *system_table
);

struct efi_table_header {
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t crc32;
    uint32_t reserved;
};

#define EFI_EVT_TIMER 0x80000000
#define EFI_EVT_RUNTIME 0x40000000
// Named without a value by the specification;
// EFI_EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE implies it.
#define EFI_EVT_RUNTIME_CONTEXT 0x20000000

#define EFI_EVT_NOTIFY_WAIT 0x00000100
#define EFI_EVT_NOTIFY_SIGNAL 0x00000200

#define EFI_EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EFI_EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

typedef void (EFI_API *efi_event_notify)(efi_event event, void *context);

typedef efi_status (EFI_API *efi_create_event)(
    uint32_t type,
    efi_tpl notify_tpl,
    efi_event_notify notify_function,
    void *notify_context,
    efi_event *event
);

typedef efi_status (EFI_API *efi_create_event_ex)(
    uint32_t type,
    efi_tpl notify_tpl,
    efi_event_notify notify_function,
    const void *notify_context,
    const struct efi_guid *event_group,
    efi_event *event
);

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
    { 0x27abf055, 0xb1b8, 0x4c26, { 0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf } }

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
    { 0x8be0e274, 0x3970, 0x4b44, { 0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc } }

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
    { 0x13fa7698, 0xc831, 0x49c7, { 0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96 } }

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
    { 0x78bee926, 0x692f, 0x48fd, { 0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab } }

#define EFI_EVENT_GROUP_READY_TO_BOOT \
    { 0x7ce88fb3, 0x4bd7, 0x4679, { 0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0xd, 0x2b } }

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
    { 0x3a2a00ad, 0x98b9, 0x4cdf, { 0xa4, 0x78, 0x70, 0x27, 0x77, 0xf1, 0xc1, 0xb } }

#define EFI_EVENT_GROUP_RESET_SYSTEM \
    { 0x62da6a56, 0x13fb, 0x485a, { 0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b } }

typedef efi_status (EFI_API *efi_close_event)(efi_event event);

typedef efi_status (EFI_API *efi_signal_event)(efi_event event);

typedef efi_status (EFI_API *efi_wait_for_event)(
    size_t number_of_events,
    efi_event *event,
    size_t *index
);

typedef efi_status (EFI_API *efi_check_event)(efi_event event);

#define EFI_TIMER_CANCEL ((uint32_t)0)
#define EFI_TIMER_PERIODIC ((uint32_t)1)
#define EFI_TIMER_RELATIVE ((uint32_t)2)

typedef efi_status (EFI_API *efi_set_timer)(
    efi_event event,
    uint32_t type,
    uint64_t trigger_time
);

#define EFI_TPL_APPLICATION 4
#define EFI_TPL_CALLBACK 8
#define EFI_TPL_NOTIFY 16
#define EFI_TPL_HIGH_LEVEL 31

typedef efi_tpl (EFI_API *efi_raise_tpl)(efi_tpl new_tpl);

typedef void (EFI_API *efi_restore_tpl)(efi_tpl old_tpl);

typedef efi_status (EFI_API *efi_allocate_pages)(
    uint32_t type,
    uint32_t memory_type,
    size_t pages,
    efi_physical_address *memory
);

typedef efi_status (EFI_API *efi_free_pages)(
    efi_physical_address memory,
    size_t pages
);

typedef efi_status (EFI_API *efi_get_memory_map)(
    size_t *memory_map_size,
    struct efi_memory_descriptor *memory_map,
    uintptr_t *map_key,
    size_t *descriptor_size,
    uint32_t *descriptor_version
);

// Not in the specification: the descriptor that follows the one at descriptor
// in a get_memory_map() buffer, whose descriptors are descriptor_size bytes
// apart.
static inline struct efi_memory_descriptor *efi_next_memory_descriptor(
    const void *descriptor,
    size_t descriptor_size
) {
    return (struct efi_memory_descriptor *)((const uint8_t *)descriptor + descriptor_size);
}

typedef efi_status (EFI_API *efi_allocate_pool)(
    uint32_t pool_type,
    size_t size,
    void **buffer
);

typedef efi_status (EFI_API *efi_free_pool)(void *buffer);

#define EFI_NATIVE_INTERFACE ((uint32_t)0)

typedef efi_status (EFI_API *efi_install_protocol_interface)(
    efi_handle *handle,
    struct efi_guid *protocol,
    uint32_t interface_type,
    void *interface
);

typedef efi_status (EFI_API *efi_uninstall_protocol_interface)(
    efi_handle handle,
    struct efi_guid *protocol,
    void *interface
);

typedef efi_status (EFI_API *efi_reinstall_protocol_interface)(
    efi_handle handle,
    struct efi_guid *protocol,
    void *old_interface,
    void *new_interface
);

typedef efi_status (EFI_API *efi_register_protocol_notify)(
    struct efi_guid *protocol,
    efi_event event,
    void **registration
);

#define EFI_ALL_HANDLES ((uint32_t)0)
#define EFI_BY_REGISTER_NOTIFY ((uint32_t)1)
#define EFI_BY_PROTOCOL ((uint32_t)2)

typedef efi_status (EFI_API *efi_locate_handle)(
    uint32_t search_type,
    struct efi_guid *protocol,
    void *search_key,
    size_t *buffer_size,
    efi_handle *buffer
);

typedef efi_status (EFI_API *efi_handle_protocol)(
    efi_handle handle,
    struct efi_guid *protocol,
    void **interface
);

typedef efi_status (EFI_API *efi_locate_device_path)(
    struct efi_guid *protocol,
    struct efi_device_path_protocol **device_path,
    efi_handle *device
);

typedef efi_status (EFI_API *efi_open_protocol)(
    efi_handle handle,
    struct efi_guid *protocol,
    void **interface,
    efi_handle agent_handle,
    efi_handle controller_handle,
    uint32_t attributes
);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef efi_status (EFI_API *efi_close_protocol)(
    efi_handle handle,
    struct efi_guid *protocol,
    efi_handle agent_handle,
    efi_handle controller_handle
);

struct efi_open_protocol_information_entry {
    efi_handle agent_handle;
    efi_handle controller_handle;
    uint32_t attributes;
    uint32_t open_count;
};

typedef efi_status (EFI_API *efi_open_protocol_information)(
    efi_handle handle,
    struct efi_guid *protocol,
    struct efi_open_protocol_information_entry **entry_buffer,
    size_t *entry_count
);

typedef efi_status (EFI_API *efi_connect_controller)(
    efi_handle controller_handle,
    efi_handle *driver_image_handle,
    struct efi_device_path_protocol *remaining_device_path,
    bool recursive
);

typedef efi_status (EFI_API *efi_disconnect_controller)(
    efi_handle controller_handle,
    efi_handle driver_image_handle,
    efi_handle child_handle
);

typedef efi_status (EFI_API *efi_protocols_per_handle)(
    efi_handle handle,
    struct efi_guid ***protocol_buffer,
    size_t *protocol_buffer_count
);

typedef efi_status (EFI_API *efi_locate_handle_buffer)(
    uint32_t search_type,
    struct efi_guid *protocol,
    void *search_key,
    size_t *no_handles,
    efi_handle **buffer
);

typedef efi_status (EFI_API *efi_locate_protocol)(
    struct efi_guid *protocol,
    void *registration,
    void **interface
);

typedef efi_status (EFI_API *efi_install_multiple_protocol_interfaces)(
    efi_handle *handle,
    ...
);

typedef efi_status (EFI_API *efi_uninstall_multiple_protocol_interfaces)(
    efi_handle handle,
    ...
);

typedef efi_status (EFI_API *efi_image_load)(
    bool boot_policy,
    efi_handle parent_image_handle,
    struct efi_device_path_protocol *device_path,
    void *source_buffer,
    size_t source_size,
    efi_handle *image_handle
);

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
    { 0x6a1ee763, 0xd47a, 0x43b4, { 0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc } }

typedef efi_status (EFI_API *efi_image_start)(
    efi_handle image_handle,
    size_t *exit_data_size,
    uint16_t **exit_data
);

typedef efi_status (EFI_API *efi_image_unload)(efi_handle image_handle);

typedef efi_status (EFI_API *efi_exit)(
    efi_handle image_handle,
    efi_status exit_status,
    size_t exit_data_size,
    uint16_t *exit_data
);

typedef efi_status (EFI_API *efi_exit_boot_services)(
    efi_handle image_handle,
    uintptr_t map_key
);

typedef efi_status (EFI_API *efi_set_watchdog_timer)(
    uintptr_t timeout,
    uint64_t watchdog_code,
    size_t data_size,
    uint16_t *watchdog_data
);

typedef efi_status (EFI_API *efi_stall)(uintptr_t microseconds);

typedef void (EFI_API *efi_copy_mem)(
    void *destination,
    void *source,
    size_t length
);

typedef void (EFI_API *efi_set_mem)(
    void *buffer,
    size_t size,
    uint8_t value
);

typedef efi_status (EFI_API *efi_get_next_monotonic_count)(uint64_t *count);

typedef efi_status (EFI_API *efi_install_configuration_table)(
    struct efi_guid *guid,
    void *table
);

typedef efi_status (EFI_API *efi_calculate_crc32)(
    void *data,
    size_t data_size,
    uint32_t *crc32
);

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS 0x00000080

// The runtime services are printed as plain function types; the names here are
// the member types of struct efi_runtime_services.
typedef efi_status (EFI_API *efi_get_variable)(
    uint16_t *variable_name,
    struct efi_guid *vendor_guid,
    uint32_t *attributes,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_get_next_variable_name)(
    size_t *variable_name_size,
    uint16_t *variable_name,
    struct efi_guid *vendor_guid
);

typedef efi_status (EFI_API *efi_set_variable)(
    uint16_t *variable_name,
    struct efi_guid *vendor_guid,
    uint32_t attributes,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_query_variable_info)(
    uint32_t attributes,
    uint64_t *maximum_variable_storage_size,
    uint64_t *remaining_variable_storage_size,
    uint64_t *maximum_variable_size
);

#define EFI_HARDWARE_ERROR_VARIABLE \
    { 0x414e6bdd, 0xe47b, 0x47cc, { 0xb2, 0x44, 0xbb, 0x61, 0x02, 0x0c, 0xf5, 0x16 } }

struct efi_time_capabilities {
    uint32_t resolution;
    uint32_t accuracy;
    uint8_t sets_to_zero;
};

typedef efi_status (EFI_API *efi_get_time)(
    struct efi_time *time,
    struct efi_time_capabilities *capabilities
);

typedef efi_status (EFI_API *efi_set_time)(struct efi_time *time);

typedef efi_status (EFI_API *efi_get_wakeup_time)(
    bool *enabled,
    bool *pending,
    struct efi_time *time
);

typedef efi_status (EFI_API *efi_set_wakeup_time)(
    bool enable,
    struct efi_time *time
);

typedef efi_status (EFI_API *efi_set_virtual_address_map)(
    size_t memory_map_size,
    size_t descriptor_size,
    uint32_t descriptor_version,
    struct efi_memory_descriptor *virtual_map
);

typedef efi_status (EFI_API *efi_convert_pointer)(
    uintptr_t debug_disposition,
    void **address
);

#define EFI_OPTIONAL_PTR 0x00000001

#define EFI_RESET_COLD ((uint32_t)0)
#define EFI_RESET_WARM ((uint32_t)1)
#define EFI_RESET_SHUTDOWN ((uint32_t)2)
#define EFI_RESET_PLATFORM_SPECIFIC ((uint32_t)3)

typedef void (EFI_API *efi_reset_system)(
    uint32_t reset_type,
    efi_status reset_status,
    size_t data_size,
    void *reset_data
);

typedef efi_status (EFI_API *efi_get_next_high_mono_count)(uint32_t *high_count);

struct efi_capsule_block_descriptor {
    uint64_t length;
    union {
        efi_physical_address data_block;
        efi_physical_address continuation_pointer;
    } union_;
};

struct efi_capsule_header {
    struct efi_guid capsule_guid;
    uint32_t header_size;
    uint32_t flags;
    uint32_t capsule_image_size;
};

#define EFI_CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define EFI_CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define EFI_CAPSULE_FLAGS_INITIATE_RESET 0x00040000

struct efi_capsule_table {
    uint32_t capsule_array_number;
    void *capsule_ptr[1];
};

typedef efi_status (EFI_API *efi_update_capsule)(
    struct efi_capsule_header **capsule_header_array,
    size_t capsule_count,
    efi_physical_address scatter_gather_list
);

#define EFI_MEMORY_RANGE_CAPSULE_GUID \
    { 0xde9f0ec, 0x88b6, 0x428f, { 0x97, 0x7a, 0x25, 0x8f, 0x1d, 0xe, 0x5e, 0x72 } }

struct efi_memory_range {
    efi_physical_address address;
    uint64_t length;
};

__extension__ struct efi_memory_range_capsule {
    struct efi_capsule_header header;
    uint32_t os_requested_memory_type;
    uint64_t number_of_memory_ranges;
    struct efi_memory_range memory_ranges[];
};

struct efi_memory_range_capsule_result {
    uint64_t firmware_memory_requirement;
    uint64_t number_of_memory_ranges;
};

typedef efi_status (EFI_API *efi_query_capsule_capabilities)(
    struct efi_capsule_header **capsule_header_array,
    size_t capsule_count,
    uint64_t *maximum_capsule_size,
    uint32_t *reset_type
);

#define EFI_CAPSULE_REPORT_GUID \
    { 0x39b68c46, 0xf7fb, 0x441b, { 0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3 } }

struct efi_capsule_result_variable_header {
    uint32_t variable_total_size;
    uint32_t reserved;
    struct efi_guid capsule_guid;
    struct efi_time capsule_processed;
    efi_status capsule_status;
};

// The uint16_t strings capsule_file_name and capsule_target follow, each
// null-terminated.
struct efi_capsule_result_variable_fmp {
    uint16_t version;
    uint8_t payload_index;
    uint8_t update_image_index;
    struct efi_guid update_image_type_id;
};

__extension__ struct efi_capsule_result_variable_json {
    uint32_t version;
    uint32_t capsule_id;
    uint32_t resp_length;
    uint8_t resp[];
};

// The specification prints "0xF000000", outside the range that it reserves for
// itself and that this belongs to, 0xf0000000 to 0xffffffff.
#define EFI_REDFISH_DEFINED_JSON_SCHEMA 0xf0000000

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2 << 16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION ((2 << 16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION ((2 << 16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2 << 16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2 << 16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2 << 16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2 << 16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2 << 16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2 << 16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2 << 16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2 << 16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2 << 16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1 << 16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1 << 16) | (02))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION EFI_2_100_SYSTEM_TABLE_REVISION

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

// The types of load_image and install_multiple_protocol_interfaces are
// misprinted as efi_image_unload and
// efi_uninstall_multiple_protocol_interfaces.
struct efi_boot_services {
    struct efi_table_header hdr;

    efi_raise_tpl raise_tpl;
    efi_restore_tpl restore_tpl;

    efi_allocate_pages allocate_pages;
    efi_free_pages free_pages;
    efi_get_memory_map get_memory_map;
    efi_allocate_pool allocate_pool;
    efi_free_pool free_pool;

    efi_create_event create_event;
    efi_set_timer set_timer;
    efi_wait_for_event wait_for_event;
    efi_signal_event signal_event;
    efi_close_event close_event;
    efi_check_event check_event;

    efi_install_protocol_interface install_protocol_interface;
    efi_reinstall_protocol_interface reinstall_protocol_interface;
    efi_uninstall_protocol_interface uninstall_protocol_interface;
    efi_handle_protocol handle_protocol;
    void *reserved;
    efi_register_protocol_notify register_protocol_notify;
    efi_locate_handle locate_handle;
    efi_locate_device_path locate_device_path;
    efi_install_configuration_table install_configuration_table;

    efi_image_load load_image;
    efi_image_start start_image;
    efi_exit exit;
    efi_image_unload unload_image;
    efi_exit_boot_services exit_boot_services;

    efi_get_next_monotonic_count get_next_monotonic_count;
    efi_stall stall;
    efi_set_watchdog_timer set_watchdog_timer;

    efi_connect_controller connect_controller;
    efi_disconnect_controller disconnect_controller;

    efi_open_protocol open_protocol;
    efi_close_protocol close_protocol;
    efi_open_protocol_information open_protocol_information;

    efi_protocols_per_handle protocols_per_handle;
    efi_locate_handle_buffer locate_handle_buffer;
    efi_locate_protocol locate_protocol;
    efi_install_multiple_protocol_interfaces install_multiple_protocol_interfaces;
    efi_uninstall_multiple_protocol_interfaces uninstall_multiple_protocol_interfaces;

    efi_calculate_crc32 calculate_crc32;

    efi_copy_mem copy_mem;
    efi_set_mem set_mem;
    efi_create_event_ex create_event_ex;
};

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

struct efi_runtime_services {
    struct efi_table_header hdr;

    efi_get_time get_time;
    efi_set_time set_time;
    efi_get_wakeup_time get_wakeup_time;
    efi_set_wakeup_time set_wakeup_time;

    efi_set_virtual_address_map set_virtual_address_map;
    efi_convert_pointer convert_pointer;

    efi_get_variable get_variable;
    efi_get_next_variable_name get_next_variable_name;
    efi_set_variable set_variable;

    efi_get_next_high_mono_count get_next_high_monotonic_count;
    efi_reset_system reset_system;

    efi_update_capsule update_capsule;
    efi_query_capsule_capabilities query_capsule_capabilities;

    efi_query_variable_info query_variable_info;
};

struct efi_configuration_table {
    struct efi_guid vendor_guid;
    void *vendor_table;
};

struct efi_system_table {
    struct efi_table_header hdr;
    uint16_t *firmware_vendor;
    uint32_t firmware_revision;
    efi_handle console_in_handle;
    struct efi_simple_text_input_protocol *con_in;
    efi_handle console_out_handle;
    struct efi_simple_text_output_protocol *con_out;
    efi_handle standard_error_handle;
    struct efi_simple_text_output_protocol *std_err;
    struct efi_runtime_services *runtime_services;
    struct efi_boot_services *boot_services;
    size_t number_of_table_entries;
    struct efi_configuration_table *configuration_table;
};

#define EFI_ACPI_TABLE_GUID \
    { 0x8868e871, 0xe4f1, 0x11d3, { 0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81 } }

#define EFI_ACPI_20_TABLE_GUID EFI_ACPI_TABLE_GUID

#define EFI_ACPI_10_TABLE_GUID \
    { 0xeb9d2d30, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_SAL_SYSTEM_TABLE_GUID \
    { 0xeb9d2d32, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_SMBIOS_TABLE_GUID \
    { 0xeb9d2d31, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_SMBIOS3_TABLE_GUID \
    { 0xf2fd1544, 0x9794, 0x4a2c, { 0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94 } }

#define EFI_MPS_TABLE_GUID \
    { 0xeb9d2d2f, 0x2d88, 0x11d3, { 0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_JSON_CONFIG_DATA_TABLE_GUID \
    { 0x87367f87, 0x1119, 0x41ce, { 0xaa, 0xec, 0x8b, 0xe0, 0x11, 0x1f, 0x55, 0x8a } }

#define EFI_JSON_CAPSULE_DATA_TABLE_GUID \
    { 0x35e7a725, 0x8dd2, 0x4cac, { 0x80, 0x11, 0x33, 0xcd, 0xa8, 0x10, 0x90, 0x56 } }

#define EFI_JSON_CAPSULE_RESULT_TABLE_GUID \
    { 0xdbc461c3, 0xb3de, 0x422a, { 0xb9, 0xb4, 0x98, 0x86, 0xfd, 0x49, 0xa1, 0xe5 } }

#define EFI_DTB_TABLE_GUID \
    { 0xb1b621d5, 0xf19c, 0x41a5, { 0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0 } }

#define EFI_RT_PROPERTIES_TABLE_GUID \
    { 0xeb66918a, 0x7eef, 0x402a, { 0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9 } }

struct efi_rt_properties_table {
    uint16_t version;
    uint16_t length;
    uint32_t runtime_services_supported;
};

#define EFI_RT_PROPERTIES_TABLE_VERSION 0x1

#define EFI_RT_SUPPORTED_GET_TIME 0x0001
#define EFI_RT_SUPPORTED_SET_TIME 0x0002
#define EFI_RT_SUPPORTED_GET_WAKEUP_TIME 0x0004
#define EFI_RT_SUPPORTED_SET_WAKEUP_TIME 0x0008
#define EFI_RT_SUPPORTED_GET_VARIABLE 0x0010
#define EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME 0x0020
#define EFI_RT_SUPPORTED_SET_VARIABLE 0x0040
#define EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP 0x0080
#define EFI_RT_SUPPORTED_CONVERT_POINTER 0x0100
#define EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT 0x0200
#define EFI_RT_SUPPORTED_RESET_SYSTEM 0x0400
#define EFI_RT_SUPPORTED_UPDATE_CAPSULE 0x0800
#define EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES 0x1000
#define EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO 0x2000

#define EFI_MEMORY_ATTRIBUTES_TABLE_GUID \
    { 0xdcfa911d, 0x26eb, 0x469f, { 0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20 } }

// Version 2 is current. number_of_entries descriptors follow, descriptor_size
// bytes apart.
struct efi_memory_attributes_table {
    uint32_t version;
    uint32_t number_of_entries;
    uint32_t descriptor_size;
    uint32_t flags;
};

#define EFI_MEMORY_ATTRIBUTES_FLAGS_RT_FORWARD_CONTROL_FLOW_GUARD 0x1

#define EFI_CONFORMANCE_PROFILES_TABLE_GUID \
    { 0x36122546, 0xf7e7, 0x4c8f, { 0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b } }

// number_of_profiles struct efi_guid (conformance_profiles) follow.
struct efi_conformance_profiles_table {
    uint16_t version;
    uint16_t number_of_profiles;
};

#define EFI_CONFORMANCE_PROFILES_TABLE_VERSION 0x1

#define EFI_CONFORMANCE_PROFILES_UEFI_SPEC_GUID \
    { 0x523c91af, 0xa195, 0x4382, { 0x81, 0x8d, 0x29, 0x5f, 0xe4, 0x00, 0x64, 0x65 } }

#define EFI_PI_SPECIFICATION_VERSION ((1 << 16) | 100)

#define EFI_DXE_SERVICES_TABLE_GUID \
    { 0x5ad34ba, 0x6f02, 0x4214, { 0x95, 0x2e, 0x4d, 0xa0, 0x39, 0x8e, 0x2b, 0xb9 } }

#define EFI_DXE_SERVICES_SIGNATURE 0x565245535f455844
#define EFI_DXE_SERVICES_REVISION EFI_PI_SPECIFICATION_VERSION

#define EFI_GCD_MEMORY_TYPE_NON_EXISTENT ((uint32_t)0)
#define EFI_GCD_MEMORY_TYPE_RESERVED ((uint32_t)1)
#define EFI_GCD_MEMORY_TYPE_SYSTEM_MEMORY ((uint32_t)2)
#define EFI_GCD_MEMORY_TYPE_MEMORY_MAPPED_IO ((uint32_t)3)
#define EFI_GCD_MEMORY_TYPE_PERSISTENT ((uint32_t)4)
#define EFI_GCD_MEMORY_TYPE_MORE_RELIABLE ((uint32_t)5)
#define EFI_GCD_MEMORY_TYPE_UNACCEPTED ((uint32_t)6)
#define EFI_GCD_MEMORY_TYPE_MAXIMUM ((uint32_t)7)

#define EFI_GCD_IO_TYPE_NON_EXISTENT ((uint32_t)0)
#define EFI_GCD_IO_TYPE_RESERVED ((uint32_t)1)
#define EFI_GCD_IO_TYPE_IO ((uint32_t)2)
#define EFI_GCD_IO_TYPE_MAXIMUM ((uint32_t)3)

#define EFI_GCD_ALLOCATE_ANY_SEARCH_BOTTOM_UP ((uint32_t)0)
#define EFI_GCD_ALLOCATE_MAX_ADDRESS_SEARCH_BOTTOM_UP ((uint32_t)1)
#define EFI_GCD_ALLOCATE_ADDRESS ((uint32_t)2)
#define EFI_GCD_ALLOCATE_ANY_SEARCH_TOP_DOWN ((uint32_t)3)
#define EFI_GCD_ALLOCATE_MAX_ADDRESS_SEARCH_TOP_DOWN ((uint32_t)4)
#define EFI_GCD_MAX_ALLOCATE_TYPE ((uint32_t)5)

struct efi_gcd_memory_space_descriptor {
    efi_physical_address base_address;
    uint64_t length;
    uint64_t capabilities;
    uint64_t attributes;
    uint32_t gcd_memory_type;
    efi_handle image_handle;
    efi_handle device_handle;
};

struct efi_gcd_io_space_descriptor {
    efi_physical_address base_address;
    uint64_t length;
    uint32_t gcd_io_type;
    efi_handle image_handle;
    efi_handle device_handle;
};

typedef efi_status (EFI_API *efi_add_memory_space)(
    uint32_t gcd_memory_type,
    efi_physical_address base_address,
    uint64_t length,
    uint64_t capabilities
);

typedef efi_status (EFI_API *efi_allocate_memory_space)(
    uint32_t gcd_allocate_type,
    uint32_t gcd_memory_type,
    size_t alignment,
    uint64_t length,
    efi_physical_address *base_address,
    efi_handle image_handle,
    efi_handle device_handle
);

typedef efi_status (EFI_API *efi_free_memory_space)(
    efi_physical_address base_address,
    uint64_t length
);

typedef efi_status (EFI_API *efi_remove_memory_space)(
    efi_physical_address base_address,
    uint64_t length
);

typedef efi_status (EFI_API *efi_get_memory_space_descriptor)(
    efi_physical_address base_address,
    struct efi_gcd_memory_space_descriptor *descriptor
);

typedef efi_status (EFI_API *efi_set_memory_space_attributes)(
    efi_physical_address base_address,
    uint64_t length,
    uint64_t attributes
);

typedef efi_status (EFI_API *efi_set_memory_space_capabilities)(
    efi_physical_address base_address,
    uint64_t length,
    uint64_t capabilities
);

typedef efi_status (EFI_API *efi_get_memory_space_map)(
    size_t *number_of_descriptors,
    struct efi_gcd_memory_space_descriptor **memory_space_map
);

typedef efi_status (EFI_API *efi_add_io_space)(
    uint32_t gcd_io_type,
    efi_physical_address base_address,
    uint64_t length
);

typedef efi_status (EFI_API *efi_allocate_io_space)(
    uint32_t gcd_allocate_type,
    uint32_t gcd_io_type,
    size_t alignment,
    uint64_t length,
    efi_physical_address *base_address,
    efi_handle image_handle,
    efi_handle device_handle
);

typedef efi_status (EFI_API *efi_free_io_space)(
    efi_physical_address base_address,
    uint64_t length
);

typedef efi_status (EFI_API *efi_remove_io_space)(
    efi_physical_address base_address,
    uint64_t length
);

typedef efi_status (EFI_API *efi_get_io_space_descriptor)(
    efi_physical_address base_address,
    struct efi_gcd_io_space_descriptor *descriptor
);

typedef efi_status (EFI_API *efi_get_io_space_map)(
    size_t *number_of_descriptors,
    struct efi_gcd_io_space_descriptor **io_space_map
);

typedef efi_status (EFI_API *efi_dispatch)(void);

typedef efi_status (EFI_API *efi_schedule)(
    efi_handle firmware_volume_handle,
    const struct efi_guid *file_name
);

typedef efi_status (EFI_API *efi_trust)(
    efi_handle firmware_volume_handle,
    const struct efi_guid *file_name
);

typedef efi_status (EFI_API *efi_process_firmware_volume)(
    const void *firmware_volume_header,
    size_t size,
    efi_handle *firmware_volume_handle
);

struct efi_dxe_services {
    struct efi_table_header hdr;

    efi_add_memory_space add_memory_space;
    efi_allocate_memory_space allocate_memory_space;
    efi_free_memory_space free_memory_space;
    efi_remove_memory_space remove_memory_space;
    efi_get_memory_space_descriptor get_memory_space_descriptor;
    efi_set_memory_space_attributes set_memory_space_attributes;
    efi_get_memory_space_map get_memory_space_map;
    efi_add_io_space add_io_space;
    efi_allocate_io_space allocate_io_space;
    efi_free_io_space free_io_space;
    efi_remove_io_space remove_io_space;
    efi_get_io_space_descriptor get_io_space_descriptor;
    efi_get_io_space_map get_io_space_map;

    efi_dispatch dispatch;
    efi_schedule schedule;
    efi_trust trust;

    efi_process_firmware_volume process_firmware_volume;

    efi_set_memory_space_capabilities set_memory_space_capabilities;
};

#ifdef __cplusplus
}
#endif

#endif
