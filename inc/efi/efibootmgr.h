#ifndef EFI_EFIBOOTMGR_H_
#define EFI_EFIBOOTMGR_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Byte-packed variable data: description, file_path_list, and optional_data follow. */
struct efi_load_option {
    uint32_t attributes;
    uint16_t file_path_list_length;
} __attribute__((__packed__));

#define EFI_LOAD_OPTION_ACTIVE 0x00000001
#define EFI_LOAD_OPTION_FORCE_RECONNECT 0x00000002
#define EFI_LOAD_OPTION_HIDDEN 0x00000008
#define EFI_LOAD_OPTION_CATEGORY 0x00001F00

#define EFI_LOAD_OPTION_CATEGORY_BOOT 0x00000000
#define EFI_LOAD_OPTION_CATEGORY_APP 0x00000100

#define EFI_BOOT_OPTION_SUPPORT_KEY 0x00000001
#define EFI_BOOT_OPTION_SUPPORT_APP 0x00000002
#define EFI_BOOT_OPTION_SUPPORT_SYSPREP 0x00000010
#define EFI_BOOT_OPTION_SUPPORT_COUNT 0x00000300

union efi_boot_key_data {
    struct __attribute__((__packed__)) {
        uint32_t revision : 8;
        uint32_t shift_pressed : 1;
        uint32_t control_pressed : 1;
        uint32_t alt_pressed : 1;
        uint32_t logo_pressed : 1;
        uint32_t menu_pressed : 1;
        uint32_t sys_req_pressed : 1;
        uint32_t reserved : 16;
        uint32_t input_key_count : 2;
    } options;
    uint32_t packed_value;
} __attribute__((__packed__));

/* Variable data: key_data.options.input_key_count struct efi_input_key (keys) follow at byte offset 10. */
struct efi_key_option {
    union efi_boot_key_data key_data;
    uint32_t boot_option_crc;
    uint16_t boot_option;
} __attribute__((__packed__));

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_GUID \
    {0xFEDF8E0C, 0xE147, 0x11E3, {0x99, 0x03, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_REVISION 0x00010000

struct efi_boot_manager_policy_protocol;

typedef efi_status (EFI_API *efi_boot_manager_policy_connect_device_path)(
    struct efi_boot_manager_policy_protocol *self,
    struct efi_device_path_protocol *device_path,
    bool recursive
);

typedef efi_status (EFI_API *efi_boot_manager_policy_connect_device_class)(
    struct efi_boot_manager_policy_protocol *self,
#ifdef __cplusplus
    struct efi_guid *class_
#else
    struct efi_guid *class
#endif
);

#define EFI_BOOT_MANAGER_POLICY_CONSOLE_GUID \
    {0xCAB0E94C, 0xE15F, 0x11E3, {0x91, 0x8D, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_NETWORK_GUID \
    {0xD04159DC, 0xE15F, 0x11E3, {0xB2, 0x61, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_STORAGE_GUID \
    {0xCD68FE79, 0xD3CB, 0x436E, {0xA8, 0x50, 0xF4, 0x43, 0xC8, 0x8C, 0xFB, 0x49}}

#define EFI_BOOT_MANAGER_POLICY_CONNECT_ALL_GUID \
    {0x113B2126, 0xFC8A, 0x11E3, {0xBD, 0x6C, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

struct efi_boot_manager_policy_protocol {
    uint64_t revision;
    efi_boot_manager_policy_connect_device_path connect_device_path;
    efi_boot_manager_policy_connect_device_class connect_device_class;
};

#define EFI_GLOBAL_VARIABLE \
    {0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C}}

#ifdef __cplusplus
}
#endif

#endif
