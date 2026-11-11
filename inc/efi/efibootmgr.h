#ifndef EFI_EFIBOOTMGR_H_
#define EFI_EFIBOOTMGR_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Byte-packed variable data: Description, FilePathList and OptionalData follow. */
struct efi_load_option {
    uint32_t Attributes;
    uint16_t FilePathListLength;
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
        uint32_t Revision : 8;
        uint32_t ShiftPressed : 1;
        uint32_t ControlPressed : 1;
        uint32_t AltPressed : 1;
        uint32_t LogoPressed : 1;
        uint32_t MenuPressed : 1;
        uint32_t SysReqPressed : 1;
        uint32_t Reserved : 16;
        uint32_t InputKeyCount : 2;
    } Options;
    uint32_t PackedValue;
} __attribute__((__packed__));

/* Variable data: KeyData.Options.InputKeyCount EFI_INPUT_KEYs (Keys) follow at byte offset 10. */
struct efi_key_option {
    union efi_boot_key_data KeyData;
    uint32_t BootOptionCrc;
    uint16_t BootOption;
} __attribute__((__packed__));

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_GUID \
    {0xFEDF8E0C, 0xE147, 0x11E3, {0x99, 0x03, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_REVISION 0x00010000

struct efi_boot_manager_policy_protocol;

typedef EFI_STATUS (EFI_API *EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_PATH)(
    struct efi_boot_manager_policy_protocol *This,
    struct efi_device_path_protocol *DevicePath,
    bool Recursive
);

typedef EFI_STATUS (EFI_API *EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_CLASS)(
    struct efi_boot_manager_policy_protocol *This,
    struct efi_guid *Class
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
    uint64_t Revision;
    EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_PATH ConnectDevicePath;
    EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_CLASS ConnectDeviceClass;
};

#define EFI_GLOBAL_VARIABLE \
    {0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C}}

#ifdef __cplusplus
}
#endif

#endif
