#ifndef EFI_EFIDRIVER_H
#define EFI_EFIDRIVER_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efihii.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Printed without the 2, a name that belongs to the EFI 1.10 Driver Diagnostics protocol's GUID. */
#define EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID \
    {0x4d330321, 0x025f, 0x4aac, {0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63}}

struct efi_driver_diagnostics2_protocol;

#define EFI_DRIVER_DIAGNOSTIC_TYPE_STANDARD ((uint32_t)0)
#define EFI_DRIVER_DIAGNOSTIC_TYPE_EXTENDED ((uint32_t)1)
#define EFI_DRIVER_DIAGNOSTIC_TYPE_MANUFACTURING ((uint32_t)2)
#define EFI_DRIVER_DIAGNOSTIC_TYPE_CANCEL ((uint32_t)3)
#define EFI_DRIVER_DIAGNOSTIC_TYPE_MAXIMUM ((uint32_t)4)

typedef efi_status (EFI_API *efi_driver_diagnostics2_run_diagnostics)(
    struct efi_driver_diagnostics2_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    uint32_t diagnostic_type,
    char *language,
    struct efi_guid **error_type,
    size_t *buffer_size,
    uint16_t **buffer
);

struct efi_driver_diagnostics2_protocol {
    efi_driver_diagnostics2_run_diagnostics run_diagnostics;
    char *supported_languages;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID \
    {0x642cd590, 0x8059, 0x4c0a, {0xa9, 0x58, 0xc5, 0xec, 0x07, 0xd2, 0x3c, 0x4b}}

struct efi_platform_to_driver_configuration_protocol
;

typedef efi_status (EFI_API *efi_platform_to_driver_configuration_query)(
    struct efi_platform_to_driver_configuration_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    size_t *instance,
    struct efi_guid **parameter_type_guid,
    void **parameter_block,
    size_t *parameter_block_size
);

#define EFI_PLATFORM_CONFIGURATION_ACTION_NONE ((uint32_t)0)
#define EFI_PLATFORM_CONFIGURATION_ACTION_STOP_CONTROLLER ((uint32_t)1)
#define EFI_PLATFORM_CONFIGURATION_ACTION_RESTART_CONTROLLER ((uint32_t)2)
#define EFI_PLATFORM_CONFIGURATION_ACTION_RESTART_PLATFORM ((uint32_t)3)
#define EFI_PLATFORM_CONFIGURATION_ACTION_NVRAM_FAILED ((uint32_t)4)
#define EFI_PLATFORM_CONFIGURATION_ACTION_UNSUPPORTED_GUID ((uint32_t)5)
#define EFI_PLATFORM_CONFIGURATION_ACTION_MAXIMUM ((uint32_t)6)

typedef efi_status (EFI_API *efi_platform_to_driver_configuration_response)(
    struct efi_platform_to_driver_configuration_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    size_t *instance,
    struct efi_guid *parameter_type_guid,
    void *parameter_block,
    size_t parameter_block_size,
    uint32_t configuration_action
);

struct efi_platform_to_driver_configuration_protocol {
    efi_platform_to_driver_configuration_query query;
    efi_platform_to_driver_configuration_response response;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID \
    {0x345ecc0e, 0xcb6, 0x4b75, {0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e}}

struct efi_configure_clp_parameter_blk {
    char *clp_command;
    uint32_t clp_command_length;
    char *clp_return_string;
    uint32_t clp_return_string_length;
    uint8_t clp_cmd_status;
    uint8_t clp_error_value;
    uint16_t clp_msg_code;
};

#define EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID \
    {0x5c198761, 0x16a8, 0x4e69, {0x97, 0x2c, 0x89, 0xd6, 0x79, 0x54, 0xf8, 0x1d}}

struct efi_driver_supported_efi_version_protocol {
    uint32_t length;
    uint32_t firmware_version;
};

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID \
    {0x2a534210, 0x9280, 0x41d8, {0xae, 0x79, 0xca, 0xda, 0x01, 0xa2, 0xb1, 0x27}}

struct efi_driver_health_protocol;

#define EFI_DRIVER_HEALTH_STATUS_HEALTHY ((uint32_t)0)
#define EFI_DRIVER_HEALTH_STATUS_REPAIR_REQUIRED ((uint32_t)1)
#define EFI_DRIVER_HEALTH_STATUS_CONFIGURATION_REQUIRED ((uint32_t)2)
#define EFI_DRIVER_HEALTH_STATUS_FAILED ((uint32_t)3)
#define EFI_DRIVER_HEALTH_STATUS_RECONNECT_REQUIRED ((uint32_t)4)
#define EFI_DRIVER_HEALTH_STATUS_REBOOT_REQUIRED ((uint32_t)5)

struct efi_driver_health_hii_message {
    efi_hii_handle hii_handle;
    efi_string_id string_id;
    uint64_t message_code;
};

typedef efi_status (EFI_API *efi_driver_health_get_health_status)(
    struct efi_driver_health_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    uint32_t *health_status,
    struct efi_driver_health_hii_message **message_list,
    efi_hii_handle *form_hii_handle
);

typedef efi_status (EFI_API *efi_driver_health_repair_notify)(
    uintptr_t value,
    uintptr_t limit
);

typedef efi_status (EFI_API *efi_driver_health_repair)(
    struct efi_driver_health_protocol *self,
    efi_handle controller_handle,
    efi_handle child_handle,
    efi_driver_health_repair_notify repair_notify
);

struct efi_driver_health_protocol {
    efi_driver_health_get_health_status get_health_status;
    efi_driver_health_repair repair;
};

#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID \
    {0xE5DD1403, 0xD622, 0xC24E, {0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02}}

struct efi_adapter_information_protocol;

typedef efi_status (EFI_API *efi_adapter_info_get_info)(
    struct efi_adapter_information_protocol *self,
    struct efi_guid *information_type,
    void **information_block,
    size_t *information_block_size
);

typedef efi_status (EFI_API *efi_adapter_info_set_info)(
    struct efi_adapter_information_protocol *self,
    struct efi_guid *information_type,
    void *information_block,
    size_t information_block_size
);

typedef efi_status (EFI_API *efi_adapter_info_get_supported_types)(
    struct efi_adapter_information_protocol *self,
    struct efi_guid **info_types_buffer,
    size_t *info_types_buffer_count
);

struct efi_adapter_information_protocol {
    efi_adapter_info_get_info get_information;
    efi_adapter_info_set_info set_information;
    efi_adapter_info_get_supported_types get_supported_types;
};

#define EFI_ADAPTER_INFO_MEDIA_STATE_GUID \
    {0xD7C74207, 0xA831, 0x4A26, {0xB1, 0xF5, 0xD1, 0x93, 0x06, 0x5C, 0xE8, 0xB6}}

struct efi_adapter_info_media_state {
    efi_status media_state;
};

#define EFI_ADAPTER_INFO_NETWORK_BOOT_GUID \
    {0x1FBD2960, 0x4130, 0x41E5, {0x94, 0xAC, 0xD2, 0xCF, 0x03, 0x7F, 0xB3, 0x7C}}

/* The first member is misprinted issci_ipv4_boot_capablity in the structure only. */
struct efi_adapter_info_network_boot {
    uint8_t iscsi_ipv4_boot_capablity;
    uint8_t iscsi_ipv6_boot_capablity;
    uint8_t fcoe_boot_capablity;
    uint8_t offload_capability;
    uint8_t iscsi_mpio_capability;
    uint8_t iscsi_ipv4_boot;
    uint8_t iscsi_ipv6_boot;
    uint8_t fcoe_boot;
};

#define EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID \
    {0x114da5ef, 0x2cf1, 0x4e12, {0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x05, 0xd9}}

struct efi_adapter_info_san_mac_address {
    struct efi_mac_address san_mac_address;
};

#define EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID \
    {0x4bd56be3, 0x4975, 0x4d8a, {0xa0, 0xad, 0xc4, 0x91, 0x20, 0x4b, 0x5d, 0x4d}}

struct efi_adapter_info_undi_ipv6_support {
    uint8_t ipv6_support;
};

#define EFI_ADAPTER_INFO_MEDIA_TYPE_GUID \
    {0x8484472f, 0x71ec, 0x411a, {0xb3, 0x9c, 0x62, 0xcd, 0x94, 0xd9, 0x91, 0x6e}}

struct efi_adapter_info_media_type {
    uint8_t media_type;
};

#define EFI_ADAPTER_INFO_CDAT_TYPE_GUID \
    {0x77af24d1, 0xb6f0, 0x42b9, {0x83, 0xf5, 0x8f, 0xe6, 0xe8, 0x3e, 0xb6, 0xf0}}

__extension__ struct efi_adapter_info_cdat_type_type {
    size_t cdat_size;
    uint8_t cdat[];
};

#ifdef __cplusplus
}
#endif

#endif
