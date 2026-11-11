#ifndef EFI_EFIBOOTMGR_H
#define EFI_EFIBOOTMGR_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>

#ifdef __cplusplus
extern "C" {
#endif

// Byte-packed variable data: description, file_path_list, and optional_data
// follow.
struct efi_load_option {
    uint32_t attributes;
    uint16_t file_path_list_length;
} __attribute__((__packed__));

#define EFI_LOAD_OPTION_ACTIVE 0x00000001
#define EFI_LOAD_OPTION_FORCE_RECONNECT 0x00000002
#define EFI_LOAD_OPTION_HIDDEN 0x00000008
#define EFI_LOAD_OPTION_CATEGORY 0x00001f00

#define EFI_LOAD_OPTION_CATEGORY_BOOT 0x00000000
#define EFI_LOAD_OPTION_CATEGORY_APP 0x00000100

#define EFI_BOOT_OPTION_SUPPORT_KEY 0x00000001
#define EFI_BOOT_OPTION_SUPPORT_APP 0x00000002
#define EFI_BOOT_OPTION_SUPPORT_SYSPREP 0x00000010
#define EFI_BOOT_OPTION_SUPPORT_COUNT 0x00000300

union efi_boot_key_data {
    uint32_t options;
    uint32_t packed_value;
} __attribute__((__packed__));

#define EFI_BOOT_KEY_DATA_REVISION_SHIFT 0
#define EFI_BOOT_KEY_DATA_REVISION_MASK 0x000000ff
#define EFI_BOOT_KEY_DATA_SHIFT_PRESSED 0x00000100
#define EFI_BOOT_KEY_DATA_CONTROL_PRESSED 0x00000200
#define EFI_BOOT_KEY_DATA_ALT_PRESSED 0x00000400
#define EFI_BOOT_KEY_DATA_LOGO_PRESSED 0x00000800
#define EFI_BOOT_KEY_DATA_MENU_PRESSED 0x00001000
#define EFI_BOOT_KEY_DATA_SYS_REQ_PRESSED 0x00002000
#define EFI_BOOT_KEY_DATA_INPUT_KEY_COUNT_SHIFT 30
#define EFI_BOOT_KEY_DATA_INPUT_KEY_COUNT_MASK 0xc0000000

// Variable data: the struct efi_input_key keys, as many as key_data.options
// counts under EFI_BOOT_KEY_DATA_INPUT_KEY_COUNT_MASK, follow at byte offset
// 10.
struct efi_key_option {
    union efi_boot_key_data key_data;
    uint32_t boot_option_crc;
    uint16_t boot_option;
} __attribute__((__packed__));

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_GUID \
    { 0xfedf8e0c, 0xe147, 0x11e3, { 0x99, 0x03, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa } }

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
    { 0xcab0e94c, 0xe15f, 0x11e3, { 0x91, 0x8d, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa } }

#define EFI_BOOT_MANAGER_POLICY_NETWORK_GUID \
    { 0xd04159dc, 0xe15f, 0x11e3, { 0xb2, 0x61, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa } }

#define EFI_BOOT_MANAGER_POLICY_STORAGE_GUID \
    { 0xcd68fe79, 0xd3cb, 0x436e, { 0xa8, 0x50, 0xf4, 0x43, 0xc8, 0x8c, 0xfb, 0x49 } }

#define EFI_BOOT_MANAGER_POLICY_CONNECT_ALL_GUID \
    { 0x113b2126, 0xfc8a, 0x11e3, { 0xbd, 0x6c, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa } }

struct efi_boot_manager_policy_protocol {
    uint64_t revision;
    efi_boot_manager_policy_connect_device_path connect_device_path;
    efi_boot_manager_policy_connect_device_class connect_device_class;
};

#define EFI_GLOBAL_VARIABLE \
    { 0x8be4df61, 0x93ca, 0x11d2, { 0xaa, 0x0d, 0x00, 0xe0, 0x98, 0x03, 0x2b, 0x8c } }

#ifdef __cplusplus
}
#endif

#endif
