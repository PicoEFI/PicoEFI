#ifndef EFI_EFIFWUPDATE_H
#define EFI_EFIFWUPDATE_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efisecureboot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_FIRMWARE_MANAGEMENT_PROTOCOL_GUID \
    { 0x86c77a67, 0xb97, 0x4633, { 0xa1, 0x87, 0x49, 0x10, 0x4d, 0x06, 0x85, 0xc7 } }

struct efi_firmware_management_protocol;

// Printed as a flexible array, which cannot be the only member: the op-codes
// run on in memory.
struct efi_firmware_image_dep {
    uint8_t dependencies[1];
};

// dependencies is printed as an EFI_FMP_DEP pointer, a type defined nowhere:
// it points to the op-codes that struct efi_firmware_image_dep holds.
struct efi_firmware_image_descriptor {
    uint8_t image_index;
    struct efi_guid image_type_id;
    uint64_t image_id;
    uint16_t *image_id_name;
    uint32_t version;
    uint16_t *version_name;
    size_t size;
    uint64_t attributes_supported;
    uint64_t attributes_setting;
    uint64_t compatibilities;
    uint32_t lowest_supported_image_version;
    uint32_t last_attempt_version;
    uint32_t last_attempt_status;
    uint64_t hardware_instance;
    struct efi_firmware_image_dep *dependencies;
};

#define EFI_IMAGE_ATTRIBUTE_IMAGE_UPDATABLE 0x0000000000000001
#define EFI_IMAGE_ATTRIBUTE_RESET_REQUIRED 0x0000000000000002
#define EFI_IMAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004
#define EFI_IMAGE_ATTRIBUTE_IN_USE 0x0000000000000008
#define EFI_IMAGE_ATTRIBUTE_UEFI_IMAGE 0x0000000000000010
#define EFI_IMAGE_ATTRIBUTE_DEPENDENCY 0x0000000000000020

#define EFI_IMAGE_COMPATIBILITY_CHECK_SUPPORTED 0x0000000000000001

// Printed as 3, but the descriptor above, ending with dependencies, is the
// version 4 one.
#define EFI_FIRMWARE_IMAGE_DESCRIPTOR_VERSION 4

struct efi_firmware_image_authentication {
    uint64_t monotonic_count;
    struct efi_win_certificate_uefi_guid auth_info;
};

typedef efi_status (EFI_API *efi_firmware_management_protocol_get_image_info)(
    struct efi_firmware_management_protocol *self,
    size_t *image_info_size,
    struct efi_firmware_image_descriptor *image_info,
    uint32_t *descriptor_version,
    uint8_t *descriptor_count,
    size_t *descriptor_size,
    uint32_t *package_version,
    uint16_t **package_version_name
);

typedef efi_status (EFI_API *efi_firmware_management_protocol_get_image)(
    struct efi_firmware_management_protocol *self,
    uint8_t image_index,
    void *image,
    size_t *image_size
);

typedef efi_status (EFI_API *efi_firmware_management_update_image_progress)(
    uintptr_t completion
);

typedef efi_status (EFI_API *efi_firmware_management_protocol_set_image)(
    struct efi_firmware_management_protocol *self,
    uint8_t image_index,
    const void *image,
    size_t image_size,
    const void *vendor_code,
    efi_firmware_management_update_image_progress progress,
    uint16_t **abort_reason
);

typedef efi_status (EFI_API *efi_firmware_management_protocol_check_image)(
    struct efi_firmware_management_protocol *self,
    uint8_t image_index,
    const void *image,
    size_t image_size,
    uint32_t *image_updatable
);

#define EFI_IMAGE_UPDATABLE_VALID 0x0000000000000001
#define EFI_IMAGE_UPDATABLE_INVALID 0x0000000000000002
#define EFI_IMAGE_UPDATABLE_INVALID_TYPE 0x0000000000000004
#define EFI_IMAGE_UPDATABLE_INVALID_OLD 0x0000000000000008
#define EFI_IMAGE_UPDATABLE_VALID_WITH_VENDOR_CODE 0x0000000000000010

// self is misprinted as a pointer to a pointer here and in set_package_info().
typedef efi_status (EFI_API *efi_firmware_management_protocol_get_package_info)(
    struct efi_firmware_management_protocol *self,
    uint32_t *package_version,
    uint16_t **package_version_name,
    uint32_t *package_version_name_max_len,
    uint64_t *attributes_supported,
    uint64_t *attributes_setting
);

#define EFI_PACKAGE_ATTRIBUTE_VERSION_UPDATABLE 0x0000000000000001
#define EFI_PACKAGE_ATTRIBUTE_RESET_REQUIRED 0x0000000000000002
#define EFI_PACKAGE_ATTRIBUTE_AUTHENTICATION_REQUIRED 0x0000000000000004

typedef efi_status (EFI_API *efi_firmware_management_protocol_set_package_info)(
    struct efi_firmware_management_protocol *self,
    const void *image,
    size_t image_size,
    const void *vendor_code,
    uint32_t package_version,
    const uint16_t *package_version_name
);

struct efi_firmware_management_protocol {
    efi_firmware_management_protocol_get_image_info get_image_info;
    efi_firmware_management_protocol_get_image get_image;
    efi_firmware_management_protocol_set_image set_image;
    efi_firmware_management_protocol_check_image check_image;
    efi_firmware_management_protocol_get_package_info get_package_info;
    efi_firmware_management_protocol_set_package_info set_package_info;
};

// The specification gives the dependency expression op-codes values but no
// names.
#define EFI_FMP_DEP_PUSH_GUID 0x00
#define EFI_FMP_DEP_PUSH_VERSION 0x01
#define EFI_FMP_DEP_VERSION_STR 0x02
#define EFI_FMP_DEP_AND 0x03
#define EFI_FMP_DEP_OR 0x04
#define EFI_FMP_DEP_NOT 0x05
#define EFI_FMP_DEP_TRUE 0x06
#define EFI_FMP_DEP_FALSE 0x07
#define EFI_FMP_DEP_EQ 0x08
#define EFI_FMP_DEP_GT 0x09
#define EFI_FMP_DEP_GTE 0x0a
#define EFI_FMP_DEP_LT 0x0b
#define EFI_FMP_DEP_LTE 0x0c
#define EFI_FMP_DEP_END 0x0d
#define EFI_FMP_DEP_DECLARE_LENGTH 0x0e

#define EFI_FIRMWARE_MANAGEMENT_CAPSULE_ID_GUID \
    { 0x6dcbd5ed, 0xe82d, 0x4c44, { 0xbd, 0xa1, 0x71, 0x94, 0x19, 0x9a, 0xd9, 0x2a } }

// item_offset_list follows: embedded_driver_count + payload_item_count
// uint64_t offsets.
struct efi_firmware_management_capsule_header {
    uint32_t version;
    uint16_t embedded_driver_count;
    uint16_t payload_item_count;
} __attribute__((__packed__));

struct efi_firmware_management_capsule_image_header {
    uint32_t version;
    struct efi_guid update_image_type_id;
    uint8_t update_image_index;
    uint8_t reserved_bytes[3];
    uint32_t update_image_size;
    uint32_t update_vendor_code_size;
    uint64_t update_hardware_instance;
    uint64_t image_capsule_support;
} __attribute__((__packed__));

#define EFI_CAPSULE_SUPPORT_AUTHENTICATION 0x0000000000000001
#define EFI_CAPSULE_SUPPORT_DEPENDENCY 0x0000000000000002

#define EFI_SYSTEM_RESOURCE_TABLE_GUID \
    { 0xb122a263, 0x3661, 0x4f68, { 0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80 } }

// fw_resource_count struct efi_system_resource_entry (entries) follow.
struct efi_system_resource_table {
    uint32_t fw_resource_count;
    uint32_t fw_resource_count_max;
    uint64_t fw_resource_version;
};

#define EFI_SYSTEM_RESOURCE_TABLE_FIRMWARE_RESOURCE_VERSION 1

struct efi_system_resource_entry {
    struct efi_guid fw_class;
    uint32_t fw_type;
    uint32_t fw_version;
    uint32_t lowest_supported_fw_version;
    uint32_t capsule_flags;
    uint32_t last_attempt_version;
    uint32_t last_attempt_status;
};

#define EFI_ESRT_FW_TYPE_UNKNOWN 0x00000000
#define EFI_ESRT_FW_TYPE_SYSTEMFIRMWARE 0x00000001
#define EFI_ESRT_FW_TYPE_DEVICEFIRMWARE 0x00000002
#define EFI_ESRT_FW_TYPE_UEFIDRIVER 0x00000003

#define EFI_LAST_ATTEMPT_STATUS_SUCCESS 0x00000000
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL 0x00000001
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INSUFFICIENT_RESOURCES 0x00000002
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INCORRECT_VERSION 0x00000003
#define EFI_LAST_ATTEMPT_STATUS_ERROR_INVALID_FORMAT 0x00000004
#define EFI_LAST_ATTEMPT_STATUS_ERROR_AUTH_ERROR 0x00000005
#define EFI_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_AC 0x00000006
#define EFI_LAST_ATTEMPT_STATUS_ERROR_PWR_EVT_BATT 0x00000007
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSATISFIED_DEPENDENCIES 0x00000008

#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL_VENDOR_RANGE_MIN 0x00001000
#define EFI_LAST_ATTEMPT_STATUS_ERROR_UNSUCCESSFUL_VENDOR_RANGE_MAX 0x00004000

#define EFI_JSON_CAPSULE_ID_GUID \
    { 0x67d6f4cd, 0xd6b8, 0x4573, { 0xbf, 0x4a, 0xde, 0x5e, 0x25, 0x2d, 0x61, 0xae } }

// __extension__: flexible array members are standard C but an extension in
// C++, and an array of structures ending in one (config_data_list) is an
// extension in C as well.
__extension__ struct efi_json_capsule_header {
    uint32_t version;
    uint32_t capsule_id;
    uint32_t payload_length;
    uint8_t payload[];
} __attribute__((__packed__));

__extension__ struct efi_json_config_data_item {
    uint32_t config_data_length;
    uint8_t config_data[];
};

__extension__ struct efi_json_capsule_config_data {
    uint32_t version;
    uint32_t total_length;
    struct efi_json_config_data_item config_data_list[];
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
