#ifndef EFI_EFIDRIVER_H_
#define EFI_EFIDRIVER_H_

#include "efihii.h"

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

typedef EFI_STATUS (EFI_API *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS)(
    struct efi_driver_diagnostics2_protocol *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    uint32_t DiagnosticType,
    char *Language,
    struct efi_guid **ErrorType,
    size_t *BufferSize,
    uint16_t **Buffer
);

struct efi_driver_diagnostics2_protocol {
    EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS RunDiagnostics;
    char *SupportedLanguages;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID \
    {0x642cd590, 0x8059, 0x4c0a, {0xa9, 0x58, 0xc5, 0xec, 0x07, 0xd2, 0x3c, 0x4b}}

struct efi_platform_to_driver_configuration_protocol
;

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY)(
    struct efi_platform_to_driver_configuration_protocol *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    size_t *Instance,
    struct efi_guid **ParameterTypeGuid,
    void **ParameterBlock,
    size_t *ParameterBlockSize
);

#define EFI_PLATFORM_CONFIGURATION_ACTION_NONE ((uint32_t)0)
#define EFI_PLATFORM_CONFIGURATION_ACTION_STOP_CONTROLLER ((uint32_t)1)
#define EFI_PLATFORM_CONFIGURATION_ACTION_RESTART_CONTROLLER ((uint32_t)2)
#define EFI_PLATFORM_CONFIGURATION_ACTION_RESTART_PLATFORM ((uint32_t)3)
#define EFI_PLATFORM_CONFIGURATION_ACTION_NVRAM_FAILED ((uint32_t)4)
#define EFI_PLATFORM_CONFIGURATION_ACTION_UNSUPPORTED_GUID ((uint32_t)5)
#define EFI_PLATFORM_CONFIGURATION_ACTION_MAXIMUM ((uint32_t)6)

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE)(
    struct efi_platform_to_driver_configuration_protocol *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    size_t *Instance,
    struct efi_guid *ParameterTypeGuid,
    void *ParameterBlock,
    size_t ParameterBlockSize,
    uint32_t ConfigurationAction
);

struct efi_platform_to_driver_configuration_protocol {
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY Query;
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE Response;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID \
    {0x345ecc0e, 0xcb6, 0x4b75, {0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e}}

struct efi_configure_clp_parameter_blk {
    char *CLPCommand;
    uint32_t CLPCommandLength;
    char *CLPReturnString;
    uint32_t CLPReturnStringLength;
    uint8_t CLPCmdStatus;
    uint8_t CLPErrorValue;
    uint16_t CLPMsgCode;
};

#define EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID \
    {0x5c198761, 0x16a8, 0x4e69, {0x97, 0x2c, 0x89, 0xd6, 0x79, 0x54, 0xf8, 0x1d}}

struct efi_driver_supported_efi_version_protocol {
    uint32_t Length;
    uint32_t FirmwareVersion;
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
    EFI_HII_HANDLE HiiHandle;
    EFI_STRING_ID StringId;
    uint64_t MessageCode;
};

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_GET_HEALTH_STATUS)(
    struct efi_driver_health_protocol *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    uint32_t *HealthStatus,
    struct efi_driver_health_hii_message **MessageList,
    EFI_HII_HANDLE *FormHiiHandle
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_REPAIR_NOTIFY)(
    uintptr_t Value,
    uintptr_t Limit
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_REPAIR)(
    struct efi_driver_health_protocol *This,
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE ChildHandle,
    EFI_DRIVER_HEALTH_REPAIR_NOTIFY RepairNotify
);

struct efi_driver_health_protocol {
    EFI_DRIVER_HEALTH_GET_HEALTH_STATUS GetHealthStatus;
    EFI_DRIVER_HEALTH_REPAIR Repair;
};

#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID \
    {0xE5DD1403, 0xD622, 0xC24E, {0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02}}

struct efi_adapter_information_protocol;

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_GET_INFO)(
    struct efi_adapter_information_protocol *This,
    struct efi_guid *InformationType,
    void **InformationBlock,
    size_t *InformationBlockSize
);

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_SET_INFO)(
    struct efi_adapter_information_protocol *This,
    struct efi_guid *InformationType,
    void *InformationBlock,
    size_t InformationBlockSize
);

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES)(
    struct efi_adapter_information_protocol *This,
    struct efi_guid **InfoTypesBuffer,
    size_t *InfoTypesBufferCount
);

struct efi_adapter_information_protocol {
    EFI_ADAPTER_INFO_GET_INFO GetInformation;
    EFI_ADAPTER_INFO_SET_INFO SetInformation;
    EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES GetSupportedTypes;
};

#define EFI_ADAPTER_INFO_MEDIA_STATE_GUID \
    {0xD7C74207, 0xA831, 0x4A26, {0xB1, 0xF5, 0xD1, 0x93, 0x06, 0x5C, 0xE8, 0xB6}}

struct efi_adapter_info_media_state {
    EFI_STATUS MediaState;
};

#define EFI_ADAPTER_INFO_NETWORK_BOOT_GUID \
    {0x1FBD2960, 0x4130, 0x41E5, {0x94, 0xAC, 0xD2, 0xCF, 0x03, 0x7F, 0xB3, 0x7C}}

/* The first member is misprinted iSsciIpv4BootCapablity in the structure only. */
struct efi_adapter_info_network_boot {
    uint8_t iScsiIpv4BootCapablity;
    uint8_t iScsiIpv6BootCapablity;
    uint8_t FCoeBootCapablity;
    uint8_t OffloadCapability;
    uint8_t iScsiMpioCapability;
    uint8_t iScsiIpv4Boot;
    uint8_t iScsiIpv6Boot;
    uint8_t FCoeBoot;
};

#define EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID \
    {0x114da5ef, 0x2cf1, 0x4e12, {0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x05, 0xd9}}

struct efi_adapter_info_san_mac_address {
    struct efi_mac_address SanMacAddress;
};

#define EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID \
    {0x4bd56be3, 0x4975, 0x4d8a, {0xa0, 0xad, 0xc4, 0x91, 0x20, 0x4b, 0x5d, 0x4d}}

struct efi_adapter_info_undi_ipv6_support {
    uint8_t Ipv6Support;
};

#define EFI_ADAPTER_INFO_MEDIA_TYPE_GUID \
    {0x8484472f, 0x71ec, 0x411a, {0xb3, 0x9c, 0x62, 0xcd, 0x94, 0xd9, 0x91, 0x6e}}

struct efi_adapter_info_media_type {
    uint8_t MediaType;
};

#define EFI_ADAPTER_INFO_CDAT_TYPE_GUID \
    {0x77af24d1, 0xb6f0, 0x42b9, {0x83, 0xf5, 0x8f, 0xe6, 0xe8, 0x3e, 0xb6, 0xf0}}

__extension__ struct efi_adapter_info_cdat_type_type {
    size_t CdatSize;
    uint8_t Cdat[];
};

#ifdef __cplusplus
}
#endif

#endif
