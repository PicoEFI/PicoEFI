#ifndef EFI_EFIDRIVER_H_
#define EFI_EFIDRIVER_H_

#include "efihii.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Printed without the 2, a name that belongs to the EFI 1.10 Driver Diagnostics protocol's GUID. */
#define EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID \
    {0x4d330321, 0x025f, 0x4aac, {0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63}}

typedef struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL EFI_DRIVER_DIAGNOSTICS2_PROTOCOL;

typedef enum {
    EfiDriverDiagnosticTypeStandard = 0,
    EfiDriverDiagnosticTypeExtended = 1,
    EfiDriverDiagnosticTypeManufacturing = 2,
    EfiDriverDiagnosticTypeCancel = 3,
    EfiDriverDiagnosticTypeMaximum
} EFI_DRIVER_DIAGNOSTIC_TYPE;

typedef EFI_STATUS (EFI_API *EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS)(
    EFI_IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_IN EFI_HANDLE ChildHandle EFI_OPTIONAL,
    EFI_IN EFI_DRIVER_DIAGNOSTIC_TYPE DiagnosticType,
    EFI_IN EFI_CHAR8 *Language,
    EFI_OUT EFI_GUID **ErrorType,
    EFI_OUT EFI_UINTN *BufferSize,
    EFI_OUT EFI_CHAR16 **Buffer
);

struct _EFI_DRIVER_DIAGNOSTICS2_PROTOCOL {
    EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS RunDiagnostics;
    EFI_CHAR8 *SupportedLanguages;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_GUID \
    {0x642cd590, 0x8059, 0x4c0a, {0xa9, 0x58, 0xc5, 0xec, 0x07, 0xd2, 0x3c, 0x4b}}

typedef struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY)(
    EFI_IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_IN EFI_HANDLE ChildHandle EFI_OPTIONAL,
    EFI_IN EFI_UINTN *Instance,
    EFI_OUT EFI_GUID **ParameterTypeGuid,
    EFI_OUT EFI_VOID **ParameterBlock,
    EFI_OUT EFI_UINTN *ParameterBlockSize
);

typedef enum {
    EfiPlatformConfigurationActionNone = 0,
    EfiPlatformConfigurationActionStopController = 1,
    EfiPlatformConfigurationActionRestartController = 2,
    EfiPlatformConfigurationActionRestartPlatform = 3,
    EfiPlatformConfigurationActionNvramFailed = 4,
    EfiPlatformConfigurationActionUnsupportedGuid = 5,
    EfiPlatformConfigurationActionMaximum
} EFI_PLATFORM_CONFIGURATION_ACTION;

typedef EFI_STATUS (EFI_API *EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE)(
    EFI_IN EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_IN EFI_HANDLE ChildHandle EFI_OPTIONAL,
    EFI_IN EFI_UINTN *Instance,
    EFI_IN EFI_GUID *ParameterTypeGuid,
    EFI_IN EFI_VOID *ParameterBlock,
    EFI_IN EFI_UINTN ParameterBlockSize,
    EFI_IN EFI_PLATFORM_CONFIGURATION_ACTION ConfigurationAction
);

struct _EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL {
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_QUERY Query;
    EFI_PLATFORM_TO_DRIVER_CONFIGURATION_RESPONSE Response;
};

#define EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID \
    {0x345ecc0e, 0xcb6, 0x4b75, {0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e}}

typedef struct {
    EFI_CHAR8 *CLPCommand;
    EFI_UINT32 CLPCommandLength;
    EFI_CHAR8 *CLPReturnString;
    EFI_UINT32 CLPReturnStringLength;
    EFI_UINT8 CLPCmdStatus;
    EFI_UINT8 CLPErrorValue;
    EFI_UINT16 CLPMsgCode;
} EFI_CONFIGURE_CLP_PARAMETER_BLK;

#define EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_GUID \
    {0x5c198761, 0x16a8, 0x4e69, {0x97, 0x2c, 0x89, 0xd6, 0x79, 0x54, 0xf8, 0x1d}}

typedef struct _EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL {
    EFI_UINT32 Length;
    EFI_UINT32 FirmwareVersion;
} EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL;

#define EFI_DRIVER_HEALTH_PROTOCOL_GUID \
    {0x2a534210, 0x9280, 0x41d8, {0xae, 0x79, 0xca, 0xda, 0x01, 0xa2, 0xb1, 0x27}}

typedef struct _EFI_DRIVER_HEALTH_PROTOCOL EFI_DRIVER_HEALTH_PROTOCOL;

typedef enum {
    EfiDriverHealthStatusHealthy,
    EfiDriverHealthStatusRepairRequired,
    EfiDriverHealthStatusConfigurationRequired,
    EfiDriverHealthStatusFailed,
    EfiDriverHealthStatusReconnectRequired,
    EfiDriverHealthStatusRebootRequired
} EFI_DRIVER_HEALTH_STATUS;

typedef struct {
    EFI_HII_HANDLE HiiHandle;
    EFI_STRING_ID StringId;
    EFI_UINT64 MessageCode;
} EFI_DRIVER_HEALTH_HII_MESSAGE;

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_GET_HEALTH_STATUS)(
    EFI_IN EFI_DRIVER_HEALTH_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle EFI_OPTIONAL,
    EFI_IN EFI_HANDLE ChildHandle EFI_OPTIONAL,
    EFI_OUT EFI_DRIVER_HEALTH_STATUS *HealthStatus,
    EFI_OUT EFI_DRIVER_HEALTH_HII_MESSAGE **MessageList EFI_OPTIONAL,
    EFI_OUT EFI_HII_HANDLE *FormHiiHandle EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_REPAIR_NOTIFY)(
    EFI_IN EFI_UINTN Value,
    EFI_IN EFI_UINTN Limit
);

typedef EFI_STATUS (EFI_API *EFI_DRIVER_HEALTH_REPAIR)(
    EFI_IN EFI_DRIVER_HEALTH_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_IN EFI_HANDLE ChildHandle EFI_OPTIONAL,
    EFI_IN EFI_DRIVER_HEALTH_REPAIR_NOTIFY RepairNotify EFI_OPTIONAL
);

struct _EFI_DRIVER_HEALTH_PROTOCOL {
    EFI_DRIVER_HEALTH_GET_HEALTH_STATUS GetHealthStatus;
    EFI_DRIVER_HEALTH_REPAIR Repair;
};

#define EFI_ADAPTER_INFORMATION_PROTOCOL_GUID \
    {0xE5DD1403, 0xD622, 0xC24E, {0x84, 0x88, 0xC7, 0x1B, 0x17, 0xF5, 0xE8, 0x02}}

typedef struct _EFI_ADAPTER_INFORMATION_PROTOCOL EFI_ADAPTER_INFORMATION_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_GET_INFO)(
    EFI_IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    EFI_IN EFI_GUID *InformationType,
    EFI_OUT EFI_VOID **InformationBlock,
    EFI_OUT EFI_UINTN *InformationBlockSize
);

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_SET_INFO)(
    EFI_IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    EFI_IN EFI_GUID *InformationType,
    EFI_IN EFI_VOID *InformationBlock,
    EFI_IN EFI_UINTN InformationBlockSize
);

typedef EFI_STATUS (EFI_API *EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES)(
    EFI_IN EFI_ADAPTER_INFORMATION_PROTOCOL *This,
    EFI_OUT EFI_GUID **InfoTypesBuffer,
    EFI_OUT EFI_UINTN *InfoTypesBufferCount
);

struct _EFI_ADAPTER_INFORMATION_PROTOCOL {
    EFI_ADAPTER_INFO_GET_INFO GetInformation;
    EFI_ADAPTER_INFO_SET_INFO SetInformation;
    EFI_ADAPTER_INFO_GET_SUPPORTED_TYPES GetSupportedTypes;
};

#define EFI_ADAPTER_INFO_MEDIA_STATE_GUID \
    {0xD7C74207, 0xA831, 0x4A26, {0xB1, 0xF5, 0xD1, 0x93, 0x06, 0x5C, 0xE8, 0xB6}}

typedef struct {
    EFI_STATUS MediaState;
} EFI_ADAPTER_INFO_MEDIA_STATE;

#define EFI_ADAPTER_INFO_NETWORK_BOOT_GUID \
    {0x1FBD2960, 0x4130, 0x41E5, {0x94, 0xAC, 0xD2, 0xCF, 0x03, 0x7F, 0xB3, 0x7C}}

/* The first member is misprinted iSsciIpv4BootCapablity in the structure only. */
typedef struct {
    EFI_BOOLEAN iScsiIpv4BootCapablity;
    EFI_BOOLEAN iScsiIpv6BootCapablity;
    EFI_BOOLEAN FCoeBootCapablity;
    EFI_BOOLEAN OffloadCapability;
    EFI_BOOLEAN iScsiMpioCapability;
    EFI_BOOLEAN iScsiIpv4Boot;
    EFI_BOOLEAN iScsiIpv6Boot;
    EFI_BOOLEAN FCoeBoot;
} EFI_ADAPTER_INFO_NETWORK_BOOT;

#define EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID \
    {0x114da5ef, 0x2cf1, 0x4e12, {0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x05, 0xd9}}

typedef struct {
    EFI_MAC_ADDRESS SanMacAddress;
} EFI_ADAPTER_INFO_SAN_MAC_ADDRESS;

#define EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID \
    {0x4bd56be3, 0x4975, 0x4d8a, {0xa0, 0xad, 0xc4, 0x91, 0x20, 0x4b, 0x5d, 0x4d}}

typedef struct {
    EFI_BOOLEAN Ipv6Support;
} EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT;

#define EFI_ADAPTER_INFO_MEDIA_TYPE_GUID \
    {0x8484472f, 0x71ec, 0x411a, {0xb3, 0x9c, 0x62, 0xcd, 0x94, 0xd9, 0x91, 0x6e}}

typedef struct {
    EFI_UINT8 MediaType;
} EFI_ADAPTER_INFO_MEDIA_TYPE;

#define EFI_ADAPTER_INFO_CDAT_TYPE_GUID \
    {0x77af24d1, 0xb6f0, 0x42b9, {0x83, 0xf5, 0x8f, 0xe6, 0xe8, 0x3e, 0xb6, 0xf0}}

__extension__ typedef struct {
    EFI_UINTN CdatSize;
    EFI_UINT8 Cdat[];
} EFI_ADAPTER_INFO_CDAT_TYPE_TYPE;

#ifdef __cplusplus
}
#endif

#endif
