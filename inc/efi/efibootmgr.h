#ifndef EFI_EFIBOOTMGR_H_
#define EFI_EFIBOOTMGR_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Byte-packed variable data: Description, FilePathList and OptionalData follow. */
typedef struct __attribute__((__packed__)) _EFI_LOAD_OPTION {
    EFI_UINT32 Attributes;
    EFI_UINT16 FilePathListLength;
} EFI_LOAD_OPTION;

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

typedef union __attribute__((__packed__)) {
    struct __attribute__((__packed__)) {
        EFI_UINT32 Revision : 8;
        EFI_UINT32 ShiftPressed : 1;
        EFI_UINT32 ControlPressed : 1;
        EFI_UINT32 AltPressed : 1;
        EFI_UINT32 LogoPressed : 1;
        EFI_UINT32 MenuPressed : 1;
        EFI_UINT32 SysReqPressed : 1;
        EFI_UINT32 Reserved : 16;
        EFI_UINT32 InputKeyCount : 2;
    } Options;
    EFI_UINT32 PackedValue;
} EFI_BOOT_KEY_DATA;

/* Variable data: KeyData.Options.InputKeyCount EFI_INPUT_KEYs (Keys) follow at byte offset 10. */
typedef struct __attribute__((__packed__)) _EFI_KEY_OPTION {
    EFI_BOOT_KEY_DATA KeyData;
    EFI_UINT32 BootOptionCrc;
    EFI_UINT16 BootOption;
} EFI_KEY_OPTION;

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_GUID \
    {0xFEDF8E0C, 0xE147, 0x11E3, {0x99, 0x03, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_BOOT_MANAGER_POLICY_PROTOCOL EFI_BOOT_MANAGER_POLICY_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_PATH)(
    EFI_IN EFI_BOOT_MANAGER_POLICY_PROTOCOL *This,
    EFI_IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    EFI_IN EFI_BOOLEAN Recursive
);

typedef EFI_STATUS (EFI_API *EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_CLASS)(
    EFI_IN EFI_BOOT_MANAGER_POLICY_PROTOCOL *This,
    EFI_IN EFI_GUID *Class
);

#define EFI_BOOT_MANAGER_POLICY_CONSOLE_GUID \
    {0xCAB0E94C, 0xE15F, 0x11E3, {0x91, 0x8D, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_NETWORK_GUID \
    {0xD04159DC, 0xE15F, 0x11E3, {0xB2, 0x61, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

#define EFI_BOOT_MANAGER_POLICY_STORAGE_GUID \
    {0xCD68FE79, 0xD3CB, 0x436E, {0xA8, 0x50, 0xF4, 0x43, 0xC8, 0x8C, 0xFB, 0x49}}

#define EFI_BOOT_MANAGER_POLICY_CONNECT_ALL_GUID \
    {0x113B2126, 0xFC8A, 0x11E3, {0xBD, 0x6C, 0xB8, 0xE8, 0x56, 0x2C, 0xBA, 0xFA}}

struct _EFI_BOOT_MANAGER_POLICY_PROTOCOL {
    EFI_UINT64 Revision;
    EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_PATH ConnectDevicePath;
    EFI_BOOT_MANAGER_POLICY_CONNECT_DEVICE_CLASS ConnectDeviceClass;
};

#define EFI_GLOBAL_VARIABLE \
    {0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C}}

#ifdef __cplusplus
}
#endif

#endif
