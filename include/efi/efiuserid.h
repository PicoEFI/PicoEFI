#ifndef EFI_EFIUSERID_H
#define EFI_EFIUSERID_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>
#include <efi/efihii.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_USER_MANAGER_PROTOCOL_GUID \
    { 0x6fd5b00c, 0xd426, 0x4283, { 0x98, 0x87, 0x6c, 0xf5, 0xcf, 0x1c, 0xb1, 0xfe } }

struct efi_user_manager_protocol;

typedef void *efi_user_profile_handle;

typedef void *efi_user_info_handle;

typedef uint16_t efi_user_info_attribs;

#define EFI_USER_INFO_STORAGE 0x000f
#define EFI_USER_INFO_STORAGE_VOLATILE 0x0000
#define EFI_USER_INFO_STORAGE_CREDENTIAL_NV 0x0001
#define EFI_USER_INFO_STORAGE_PLATFORM_NV 0x0002

#define EFI_USER_INFO_ACCESS 0x0070
#define EFI_USER_INFO_PUBLIC 0x0010
#define EFI_USER_INFO_PRIVATE 0x0020
#define EFI_USER_INFO_PROTECTED 0x0030
#define EFI_USER_INFO_EXCLUSIVE 0x0080

struct efi_user_info {
    struct efi_guid credential;
    uint8_t info_type;
    uint8_t reserved1;
    efi_user_info_attribs info_attribs;
    uint32_t info_size;
};

typedef uint8_t efi_user_info_identifier[16];

typedef efi_status (EFI_API *efi_user_profile_create)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle *user
);

typedef efi_status (EFI_API *efi_user_profile_delete)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle user
);

typedef efi_status (EFI_API *efi_user_profile_get_next)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle *user
);

typedef efi_status (EFI_API *efi_user_profile_current)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle *current_user
);

// Its prototype prints EFI_USER_IDENTIFY; the protocol structure uses this
// name.
typedef efi_status (EFI_API *efi_user_profile_identify)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle *user
);

#define EFI_EVENT_GROUP_USER_PROFILE_CHANGED \
    { 0xbaf1e6de, 0x209e, 0x4adb, { 0x8d, 0x96, 0xfd, 0x8b, 0x71, 0xf3, 0xf6, 0x83 } }

typedef efi_status (EFI_API *efi_user_profile_find)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle *user,
    efi_user_info_handle *user_info,
    const struct efi_user_info *info,
    size_t info_size
);

typedef efi_status (EFI_API *efi_user_profile_notify)(
    const struct efi_user_manager_protocol *self,
    efi_handle changed
);

typedef efi_status (EFI_API *efi_user_profile_get_info)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle user,
    efi_user_info_handle user_info,
    struct efi_user_info *info,
    size_t *info_size
);

typedef efi_status (EFI_API *efi_user_profile_set_info)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle user,
    efi_user_info_handle *user_info,
    const struct efi_user_info *info,
    size_t info_size
);

typedef efi_status (EFI_API *efi_user_profile_delete_info)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle user,
    efi_user_info_handle user_info
);

typedef efi_status (EFI_API *efi_user_profile_get_next_info)(
    const struct efi_user_manager_protocol *self,
    efi_user_profile_handle user,
    efi_user_info_handle *user_info
);

struct efi_user_manager_protocol {
    efi_user_profile_create create;
#ifdef __cplusplus
    efi_user_profile_delete delete_;
#else
    efi_user_profile_delete delete;
#endif
    efi_user_profile_get_next get_next;
    efi_user_profile_current current;
    efi_user_profile_identify identify;
    efi_user_profile_find find;
    efi_user_profile_notify notify;
    efi_user_profile_get_info get_info;
    efi_user_profile_set_info set_info;
    efi_user_profile_delete_info delete_info;
    efi_user_profile_get_next_info get_next_info;
};

#define EFI_USER_CREDENTIAL2_PROTOCOL_GUID \
    { 0xe98adb03, 0xb8b9, 0x4af8, { 0xba, 0x20, 0x26, 0xe9, 0x11, 0x4c, 0xbc, 0xe5 } }

struct efi_user_credential2_protocol;

#define EFI_USER_CREDENTIAL_CLASS_UNKNOWN \
    { 0x5cf32e68, 0x7660, 0x449b, { 0x80, 0xe6, 0x7e, 0xa3, 0x6e, 0x3, 0xf6, 0xa8 } }

#define EFI_USER_CREDENTIAL_CLASS_PASSWORD \
    { 0xf8e5058c, 0xccb6, 0x4714, { 0xb2, 0x20, 0x3f, 0x7e, 0x3a, 0x64, 0xb, 0xd1 } }

#define EFI_USER_CREDENTIAL_CLASS_SMART_CARD \
    { 0x5f03ba33, 0x8c6b, 0x4c24, { 0xaa, 0x2e, 0x14, 0xa2, 0x65, 0x7b, 0xd4, 0x54 } }

#define EFI_USER_CREDENTIAL_CLASS_FINGERPRINT \
    { 0x32cba21f, 0xf308, 0x4cbc, { 0x9a, 0xb5, 0xf5, 0xa3, 0x69, 0x9f, 0x4, 0x4a } }

#define EFI_USER_CREDENTIAL_CLASS_HANDPRINT \
    { 0x5917ef16, 0xf723, 0x4bb9, { 0xa6, 0x4b, 0xd8, 0xc5, 0x32, 0xf4, 0xd8, 0xb5 } }

#define EFI_USER_CREDENTIAL_CLASS_SECURE_CARD \
    { 0x8a6b4a83, 0x42fe, 0x45d2, { 0xa2, 0xef, 0x46, 0xf0, 0x6c, 0x7d, 0x98, 0x52 } }

typedef uint64_t efi_credential_capabilities;

#define EFI_CREDENTIAL_CAPABILITIES_ENROLL 0x0000000000000001

// Its prototype prints EFI_CREDENTIAL2_ENROLL; the protocol structure uses
// this name.
typedef efi_status (EFI_API *efi_credential_enroll)(
    const struct efi_user_credential2_protocol *self,
    efi_user_profile_handle user
);

typedef efi_status (EFI_API *efi_credential_form)(
    const struct efi_user_credential2_protocol *self,
    efi_hii_handle *hii,
    struct efi_guid *form_set_id,
    efi_form_id *form_id
);

typedef efi_status (EFI_API *efi_credential_tile)(
    const struct efi_user_credential2_protocol *self,
    size_t *width,
    size_t *height,
    efi_hii_handle *hii,
    efi_image_id *image
);

typedef efi_status (EFI_API *efi_credential_title)(
    const struct efi_user_credential2_protocol *self,
    efi_hii_handle *hii,
    efi_string_id *string
);

typedef efi_status (EFI_API *efi_credential_user)(
    const struct efi_user_credential2_protocol *self,
    efi_user_profile_handle user,
    efi_user_info_identifier *identifier
);

typedef uint32_t efi_credential_logon_flags;

#define EFI_CREDENTIAL_LOGON_FLAG_AUTO 0x00000001
#define EFI_CREDENTIAL_LOGON_FLAG_DEFAULT 0x00000002

typedef efi_status (EFI_API *efi_credential_select)(
    const struct efi_user_credential2_protocol *self,
    efi_credential_logon_flags *auto_logon
);

typedef efi_status (EFI_API *efi_credential_deselect)(
    const struct efi_user_credential2_protocol *self
);

typedef efi_status (EFI_API *efi_credential_default)(
    const struct efi_user_credential2_protocol *self,
    efi_credential_logon_flags *auto_logon
);

typedef efi_status (EFI_API *efi_credential_get_info)(
    const struct efi_user_credential2_protocol *self,
    efi_user_info_handle user_info,
    struct efi_user_info *info,
    size_t *info_size
);

// Its prototype prints EFI_USER_CREDENTIAL_GET_NEXT_INFO; the protocol
// structure uses this name.
typedef efi_status (EFI_API *efi_credential_get_next_info)(
    const struct efi_user_credential2_protocol *self,
    efi_user_info_handle *user_info
);

typedef efi_status (EFI_API *efi_credential_delete)(
    const struct efi_user_credential2_protocol *self,
    efi_user_profile_handle user
);

struct efi_user_credential2_protocol {
    struct efi_guid identifier;
    struct efi_guid type;
    efi_credential_enroll enroll;
    efi_credential_form form;
    efi_credential_tile tile;
    efi_credential_title title;
    efi_credential_user user;
    efi_credential_select select;
    efi_credential_deselect deselect;
    efi_credential_default default_;
    efi_credential_get_info get_info;
    efi_credential_get_next_info get_next_info;
    efi_credential_capabilities capabilities;
#ifdef __cplusplus
    efi_credential_delete delete_;
#else
    efi_credential_delete delete;
#endif
};

#define EFI_DEFERRED_IMAGE_LOAD_PROTOCOL_GUID \
    { 0x15853d7c, 0x3ddf, 0x43e0, { 0xa1, 0xcb, 0xeb, 0xf8, 0x5b, 0x8f, 0x87, 0x2c } }

struct efi_deferred_image_load_protocol;

typedef efi_status (EFI_API *efi_deferred_image_info)(
    struct efi_deferred_image_load_protocol *self,
    size_t image_index,
    struct efi_device_path_protocol **image_device_path,
    void **image,
    size_t *image_size,
    bool *boot_option
);

struct efi_deferred_image_load_protocol {
    efi_deferred_image_info get_image_info;
};

// Named only in the table of record types.
#define EFI_USER_INFO_EMPTY_RECORD 0x00

#define EFI_USER_INFO_ACCESS_POLICY_RECORD 0x0e

struct efi_user_info_access_control {
    uint32_t type;
    uint32_t size;
};

typedef struct efi_user_info_access_control efi_user_info_access_policy;

#define EFI_USER_INFO_ACCESS_FORBID_LOAD 0x00000001
#define EFI_USER_INFO_ACCESS_PERMIT_LOAD 0x00000002
#define EFI_USER_INFO_ACCESS_ENROLL_SELF 0x00000003
#define EFI_USER_INFO_ACCESS_ENROLL_OTHERS 0x00000004
#define EFI_USER_INFO_ACCESS_MANAGE 0x00000005
#define EFI_USER_INFO_ACCESS_SETUP 0x00000006

#define EFI_USER_INFO_ACCESS_SETUP_ADMIN_GUID \
    { 0x85b75607, 0xf7ce, 0x471e, { 0xb7, 0xe4, 0x2a, 0xea, 0x5f, 0x72, 0x32, 0xee } }

#define EFI_USER_INFO_ACCESS_SETUP_NORMAL_GUID \
    { 0x1db29ae0, 0x9dcb, 0x43bc, { 0x8d, 0x87, 0x5d, 0xa1, 0x49, 0x64, 0xdd, 0xe2 } }

#define EFI_USER_INFO_ACCESS_SETUP_RESTRICTED_GUID \
    { 0xbdb38125, 0x4d63, 0x49f4, { 0x82, 0x12, 0x61, 0xcf, 0x5a, 0x19, 0x0a, 0xf8 } }

#define EFI_USER_INFO_ACCESS_FORBID_CONNECT 0x00000007
#define EFI_USER_INFO_ACCESS_PERMIT_CONNECT 0x00000008
#define EFI_USER_INFO_ACCESS_BOOT_ORDER 0x00000009

typedef uint32_t efi_user_info_access_boot_order_hdr;

#define EFI_USER_INFO_ACCESS_BOOT_ORDER_MASK 0x000f
#define EFI_USER_INFO_ACCESS_BOOT_ORDER_INSERT 0x0000
#define EFI_USER_INFO_ACCESS_BOOT_ORDER_APPEND 0x0001
#define EFI_USER_INFO_ACCESS_BOOT_ORDER_REPLACE 0x0002

#define EFI_USER_INFO_ACCESS_BOOT_ORDER_NODEFAULT 0x0010

#define EFI_USER_INFO_CBEFF_RECORD 0x0b
typedef void *efi_user_info_cbeff;

#define EFI_USER_INFO_CREATE_DATE_RECORD 0x02
typedef struct efi_time efi_user_info_create_date;

#define EFI_USER_INFO_CREDENTIAL_PROVIDER_RECORD 0x08
typedef struct efi_guid efi_user_info_credential_provider;

#define EFI_USER_INFO_CREDENTIAL_PROVIDER_NAME_RECORD 0x09
typedef uint16_t *efi_user_info_credential_provider_name;

#define EFI_USER_INFO_CREDENTIAL_TYPE_RECORD 0x06
typedef struct efi_guid efi_user_info_credential_type;

#define EFI_USER_INFO_CREDENTIAL_TYPE_NAME_RECORD 0x07
typedef uint16_t *efi_user_info_credential_type_name;

#define EFI_USER_INFO_GUID_RECORD 0xff
typedef struct efi_guid efi_user_info_guid;

#define EFI_USER_INFO_FAR_RECORD 0x0c
typedef uint8_t efi_user_info_far;

#define EFI_USER_INFO_IDENTIFIER_RECORD 0x05

#define EFI_USER_INFO_IDENTITY_POLICY_RECORD 0x0f

struct efi_user_info_identity_policy {
    uint32_t type;
    uint32_t length;
};

#define EFI_USER_INFO_IDENTITY_FALSE 0x00
#define EFI_USER_INFO_IDENTITY_TRUE 0x01
#define EFI_USER_INFO_IDENTITY_CREDENTIAL_TYPE 0x02
#define EFI_USER_INFO_IDENTITY_CREDENTIAL_PROVIDER 0x03
#define EFI_USER_INFO_IDENTITY_NOT 0x10
#define EFI_USER_INFO_IDENTITY_AND 0x11
#define EFI_USER_INFO_IDENTITY_OR 0x12

#define EFI_USER_INFO_NAME_RECORD 0x01
typedef uint16_t *efi_user_info_name;

#define EFI_USER_INFO_PKCS11_RECORD 0x0a

#define EFI_USER_INFO_RETRY_RECORD 0x0d
typedef uint8_t efi_user_info_retry;

#define EFI_USER_INFO_USAGE_DATE_RECORD 0x03
typedef struct efi_time efi_user_info_usage_date;

// Printed without _RECORD, as the usage count type's name; the table of record
// types has it.
#define EFI_USER_INFO_USAGE_COUNT_RECORD 0x04
typedef uint64_t efi_user_info_usage_count;

struct efi_user_info_table {
    uint64_t size;
};

#ifdef __cplusplus
}
#endif

#endif
