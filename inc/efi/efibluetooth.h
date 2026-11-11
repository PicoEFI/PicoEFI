#ifndef EFI_EFIBLUETOOTH_H_
#define EFI_EFIBLUETOOTH_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_BLUETOOTH_HC_PROTOCOL_GUID \
    {0xb3930571, 0xbeba, 0x4fc5, {0x92, 0x3, 0x94, 0x27, 0x24, 0x2e, 0x6a, 0x43}}

struct efi_bluetooth_hc_protocol;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_SEND_COMMAND)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_RECEIVE_EVENT)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK)(
    void *Data,
    size_t DataLength,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_EVENT)(
    struct efi_bluetooth_hc_protocol *This,
    bool IsNewTransfer,
    uintptr_t PollingInterval,
    size_t DataLength,
    EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_SEND_ACL_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_RECEIVE_ACL_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_ACL_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    bool IsNewTransfer,
    uintptr_t PollingInterval,
    size_t DataLength,
    EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_SEND_SCO_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_RECEIVE_SCO_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_HC_ASYNC_RECEIVE_SCO_DATA)(
    struct efi_bluetooth_hc_protocol *This,
    bool IsNewTransfer,
    uintptr_t PollingInterval,
    size_t DataLength,
    EFI_BLUETOOTH_HC_ASYNC_FUNC_CALLBACK Callback,
    void *Context
);

struct efi_bluetooth_hc_protocol {
    EFI_BLUETOOTH_HC_SEND_COMMAND SendCommand;
    EFI_BLUETOOTH_HC_RECEIVE_EVENT ReceiveEvent;
    EFI_BLUETOOTH_HC_ASYNC_RECEIVE_EVENT AsyncReceiveEvent;
    EFI_BLUETOOTH_HC_SEND_ACL_DATA SendACLData;
    EFI_BLUETOOTH_HC_RECEIVE_ACL_DATA ReceiveACLData;
    EFI_BLUETOOTH_HC_ASYNC_RECEIVE_ACL_DATA AsyncReceiveACLData;
    EFI_BLUETOOTH_HC_SEND_SCO_DATA SendSCOData;
    EFI_BLUETOOTH_HC_RECEIVE_SCO_DATA ReceiveSCOData;
    EFI_BLUETOOTH_HC_ASYNC_RECEIVE_SCO_DATA AsyncReceiveSCOData;
};

#define EFI_BLUETOOTH_IO_SERVICE_BINDING_PROTOCOL_GUID \
    {0x388278d3, 0x7b85, 0x42f0, {0xab, 0xa9, 0xfb, 0x4b, 0xfd, 0x69, 0xf5, 0xab}}

#define EFI_BLUETOOTH_IO_PROTOCOL_GUID \
    {0x467313de, 0x4e30, 0x43f1, {0x94, 0x3e, 0x32, 0x3f, 0x89, 0x84, 0x5d, 0xb5}}

struct efi_bluetooth_io_protocol;

/* Byte-packed as firmware lays it out: the 3-byte Bluetooth Class of Device. */
struct efi_bluetooth_class_of_device {
    uint8_t FormatType:2;
    uint8_t MinorDeviceClass:6;
    uint16_t MajorDeviceClass:5;
    uint16_t MajorServiceClass:11;
} __attribute__((__packed__));

struct efi_bluetooth_device_info {
    uint32_t Version;
    struct efi_bluetooth_address BD_ADDR;
    uint8_t PageScanRepetitionMode;
    struct efi_bluetooth_class_of_device ClassOfDevice;
    uint16_t ClockOffset;
    uint8_t RSSI;
    uint8_t ExtendedInquiryResponse[240];
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_GET_DEVICE_INFO)(
    struct efi_bluetooth_io_protocol *This,
    size_t *DeviceInfoSize,
    void **DeviceInfo
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_GET_SDP_INFO)(
    struct efi_bluetooth_io_protocol *This,
    size_t *SdpInfoSize,
    void **SdpInfo
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_RAW_SEND)(
    struct efi_bluetooth_io_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_RAW_RECEIVE)(
    struct efi_bluetooth_io_protocol *This,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_ASYNC_FUNC_CALLBACK)(
    uint16_t ChannelID,
    void *Data,
    size_t DataLength,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_RAW_ASYNC_RECEIVE)(
    struct efi_bluetooth_io_protocol *This,
    bool IsNewTransfer,
    uintptr_t PollingInterval,
    size_t DataLength,
    EFI_BLUETOOTH_IO_ASYNC_FUNC_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_SEND)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE Handle,
    size_t *BufferSize,
    void *Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_RECEIVE)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE Handle,
    size_t *BufferSize,
    void **Buffer,
    uintptr_t Timeout
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK)(
    void *Data,
    size_t DataLength,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_ASYNC_RECEIVE)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE Handle,
    EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_CONNECT)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE *Handle,
    uint16_t Psm,
    uint16_t Mtu,
    EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_DISCONNECT)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE Handle
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_IO_L2CAP_REGISTER_SERVICE)(
    struct efi_bluetooth_io_protocol *This,
    EFI_HANDLE *Handle,
    uint16_t Psm,
    uint16_t Mtu,
    EFI_BLUETOOTH_IO_CHANNEL_SERVICE_CALLBACK Callback,
    void *Context
);

struct efi_bluetooth_io_protocol {
    EFI_BLUETOOTH_IO_GET_DEVICE_INFO GetDeviceInfo;
    EFI_BLUETOOTH_IO_GET_SDP_INFO GetSdpInfo;
    EFI_BLUETOOTH_IO_L2CAP_RAW_SEND L2CapRawSend;
    EFI_BLUETOOTH_IO_L2CAP_RAW_RECEIVE L2CapRawReceive;
    EFI_BLUETOOTH_IO_L2CAP_RAW_ASYNC_RECEIVE L2CapRawAsyncReceive;
    EFI_BLUETOOTH_IO_L2CAP_SEND L2CapSend;
    EFI_BLUETOOTH_IO_L2CAP_RECEIVE L2CapReceive;
    EFI_BLUETOOTH_IO_L2CAP_ASYNC_RECEIVE L2CapAsyncReceive;
    EFI_BLUETOOTH_IO_L2CAP_CONNECT L2CapConnect;
    EFI_BLUETOOTH_IO_L2CAP_DISCONNECT L2CapDisconnect;
    EFI_BLUETOOTH_IO_L2CAP_REGISTER_SERVICE L2CapRegisterService;
};

#define EFI_BLUETOOTH_CONFIG_PROTOCOL_GUID \
    {0x62960cf3, 0x40ff, 0x4263, {0xa7, 0x7c, 0xdf, 0xde, 0xbd, 0x19, 0x1b, 0x4b}}

struct efi_bluetooth_config_protocol;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_INIT)(struct efi_bluetooth_config_protocol *This);

#define EFI_BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE 248

struct efi_bluetooth_scan_callback_information {
    struct efi_bluetooth_address BDAddr;
    uint8_t RemoteDeviceState;
    struct efi_bluetooth_class_of_device ClassOfDevice;
    uint8_t RemoteDeviceName[EFI_BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_SCAN_CALLBACK_FUNCTION)(
    struct efi_bluetooth_config_protocol *This,
    void *Context,
    struct efi_bluetooth_scan_callback_information *CallbackInfo
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_SCAN)(
    struct efi_bluetooth_config_protocol *This,
    bool ReScan,
    uint8_t ScanType,
    EFI_BLUETOOTH_CONFIG_SCAN_CALLBACK_FUNCTION Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_CONNECT)(
    struct efi_bluetooth_config_protocol *This,
    struct efi_bluetooth_address *BD_ADDR
);

/* Reason is a value, as described and as in the LE protocol; it is printed uint8_t *Reason. */
typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_DISCONNECT)(
    struct efi_bluetooth_config_protocol *This,
    struct efi_bluetooth_address *BD_ADDR,
    uint8_t Reason
);

typedef enum {
    EfiBluetoothConfigDataTypeDeviceName,
    EfiBluetoothConfigDataTypeClassOfDevice,
    EfiBluetoothConfigDataTypeRemoteDeviceState,
    EfiBluetoothConfigDataTypeSdpInfo,
    EfiBluetoothConfigDataTypeBDADDR,
    EfiBluetoothConfigDataTypeDiscoverable,
    EfiBluetoothConfigDataTypeControllerStoredPairedDeviceList,
    EfiBluetoothConfigDataTypeAvailableDeviceList,
    EfiBluetoothConfigDataTypeRandomAddress,
    EfiBluetoothConfigDataTypeRSSI,
    EfiBluetoothConfigDataTypeAdvertisementData,
    EfiBluetoothConfigDataTypeIoCapability,
    EfiBluetoothConfigDataTypeOOBDataFlag,
    EfiBluetoothConfigDataTypeKeyType,
    EfiBluetoothConfigDataTypeEncKeySize,
    EfiBluetoothConfigDataTypeMax
} EFI_BLUETOOTH_CONFIG_DATA_TYPE;

typedef uint32_t EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_TYPE;

#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED 0x1
#define EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED 0x2

#define EFI_BLUETOOTH_HCI_LINK_KEY_SIZE 16

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_GET_DATA)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_SET_DATA)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_GET_REMOTE_DATA)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    struct efi_bluetooth_address *BDAddr,
    size_t *DataSize,
    void *Data
);

typedef enum {
    EfiBluetoothCallbackTypeUserPasskeyNotification,
    EfiBluetoothCallbackTypeUserConfirmationRequest,
    EfiBluetoothCallbackTypeOOBDataRequest,
    EfiBluetoothCallbackTypePinCodeRequest,
    EfiBluetoothCallbackTypeMax
} EFI_BLUETOOTH_PIN_CALLBACK_TYPE;

/* Each parameter is printed with a leaked emphasis asterisk; these are the described types. */
typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK_FUNCTION)(
    struct efi_bluetooth_config_protocol *This,
    void *Context,
    EFI_BLUETOOTH_PIN_CALLBACK_TYPE CallbackType,
    void *InputBuffer,
    size_t InputBufferSize,
    void **OutputBuffer,
    size_t *OutputBufferSize
);

/* Callback by value like its siblings; printed as a pointer to the function pointer type. */
typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK_FUNCTION Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK_FUNCTION)(
    struct efi_bluetooth_config_protocol *This,
    void *Context,
    struct efi_bluetooth_address *BDAddr,
    uint8_t LinkKey[EFI_BLUETOOTH_HCI_LINK_KEY_SIZE]
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK_FUNCTION Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK_FUNCTION)(
    struct efi_bluetooth_config_protocol *This,
    void *Context,
    struct efi_bluetooth_address *BDAddr,
    uint8_t LinkKey[EFI_BLUETOOTH_HCI_LINK_KEY_SIZE]
);

/* Callback by value like its siblings; printed as a pointer to the function pointer type. */
typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK_FUNCTION Callback,
    void *Context
);

typedef enum {
    EfiBluetoothConnCallbackTypeDisconnected,
    EfiBluetoothConnCallbackTypeConnected,
    EfiBluetoothConnCallbackTypeAuthenticated,
    EfiBluetoothConnCallbackTypeEncrypted
} EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK_FUNCTION)(
    struct efi_bluetooth_config_protocol *This,
    void *Context,
    EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE CallbackType,
    struct efi_bluetooth_address *BDAddr,
    void *InputBuffer,
    size_t InputBufferSize
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK)(
    struct efi_bluetooth_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK_FUNCTION Callback,
    void *Context
);

struct efi_bluetooth_config_protocol {
    EFI_BLUETOOTH_CONFIG_INIT Init;
    EFI_BLUETOOTH_CONFIG_SCAN Scan;
    EFI_BLUETOOTH_CONFIG_CONNECT Connect;
    EFI_BLUETOOTH_CONFIG_DISCONNECT Disconnect;
    EFI_BLUETOOTH_CONFIG_GET_DATA GetData;
    EFI_BLUETOOTH_CONFIG_SET_DATA SetData;
    EFI_BLUETOOTH_CONFIG_GET_REMOTE_DATA GetRemoteData;
    EFI_BLUETOOTH_CONFIG_REGISTER_PIN_CALLBACK RegisterPinCallback;
    EFI_BLUETOOTH_CONFIG_REGISTER_GET_LINK_KEY_CALLBACK RegisterGetLinkKeyCallback;
    EFI_BLUETOOTH_CONFIG_REGISTER_SET_LINK_KEY_CALLBACK RegisterSetLinkKeyCallback;
    EFI_BLUETOOTH_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK RegisterLinkConnectCompleteCallback;
};

#define EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL_GUID \
    {0x898890e9, 0x84b2, 0x4f3a, {0x8c, 0x58, 0xd8, 0x57, 0x78, 0x13, 0xe0, 0xac}}

struct efi_bluetooth_attribute_protocol;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION)(
    struct efi_bluetooth_attribute_protocol *This,
    void *Data,
    size_t DataLength,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_ATTRIBUTE_SEND_REQUEST)(
    struct efi_bluetooth_attribute_protocol *This,
    void *Data,
    size_t DataLength,
    EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback,
    void *Context
);

struct efi_bluetooth_attribute_callback_parameter_notification {
    uint16_t AttributeHandle;
};

struct efi_bluetooth_attribute_callback_parameter_indication {
    uint16_t AttributeHandle;
};

struct efi_bluetooth_attribute_callback_parameter {
    uint32_t Version;
    uint8_t AttributeOpCode;
    union {
        struct efi_bluetooth_attribute_callback_parameter_notification Notification;
        struct efi_bluetooth_attribute_callback_parameter_indication Indication;
    } Parameter;
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_ATTRIBUTE_REGISTER_FOR_SERVER_NOTIFICATION)(
    struct efi_bluetooth_attribute_protocol *This,
    struct efi_bluetooth_attribute_callback_parameter *CallbackParameter,
    EFI_BLUETOOTH_ATTRIBUTE_CALLBACK_FUNCTION Callback,
    void *Context
);

/* Byte-packed, as firmware lays out these attribute types; the print shows no packing. */
struct efi_bluetooth_uuid {
    uint8_t Length;
    union __attribute__((__packed__)) {
        uint16_t Uuid16;
        uint32_t Uuid32;
        uint8_t Uuid128[16];
    } Data;
} __attribute__((__packed__));

union efi_bluetooth_attribute_permission {
    struct __attribute__((__packed__)) {
        uint16_t Readable:1;
        uint16_t ReadEncryption:1;
        uint16_t ReadAuthentication:1;
        uint16_t ReadAuthorization:1;
        uint16_t ReadKeySize:5;
        uint16_t Reserved1:7;
        uint16_t Writeable:1;
        uint16_t WriteEncryption:1;
        uint16_t WriteAuthentication:1;
        uint16_t WriteAuthorization:1;
        uint16_t WriteKeySize:5;
        uint16_t Reserved2:7;
    } Permission;
    uint32_t Data32;
} __attribute__((__packed__));

struct efi_bluetooth_attribute_header {
    struct efi_bluetooth_uuid Type;
    uint16_t Length;
    uint16_t AttributeHandle;
    union efi_bluetooth_attribute_permission AttributePermission;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_primary_service_info {
    struct efi_bluetooth_attribute_header Header;
    uint16_t EndGroupHandle;
    struct efi_bluetooth_uuid ServiceUuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_include_service_info {
    struct efi_bluetooth_attribute_header Header;
    uint16_t StartGroupHandle;
    uint16_t EndGroupHandle;
    struct efi_bluetooth_uuid ServiceUuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_characteristic_info {
    struct efi_bluetooth_attribute_header Header;
    uint8_t CharacteristicProperties;
    uint16_t CharacteristicValueHandle;
    struct efi_bluetooth_uuid CharacteristicUuid;
} __attribute__((__packed__));

struct efi_bluetooth_gatt_characteristic_descriptor_info {
    struct efi_bluetooth_attribute_header Header;
    struct efi_bluetooth_uuid CharacteristicDescriptorUuid;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_ATTRIBUTE_GET_SERVICE_INFO)(
    struct efi_bluetooth_attribute_protocol *This,
    size_t *ServiceInfoSize,
    void **ServiceInfo
);

struct efi_bluetooth_le_device_info {
    uint32_t Version;
    struct efi_bluetooth_le_address BD_ADDR;
    struct efi_bluetooth_le_address DirectAddress;
    uint8_t RSSI;
    size_t AdvertisementDataSize;
    void *AdvertisementData;
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_ATTRIBUTE_GET_DEVICE_INFO)(
    struct efi_bluetooth_attribute_protocol *This,
    size_t *DeviceInfoSize,
    void **DeviceInfo
);

struct efi_bluetooth_attribute_protocol {
    EFI_BLUETOOTH_ATTRIBUTE_SEND_REQUEST SendRequest;
    EFI_BLUETOOTH_ATTRIBUTE_REGISTER_FOR_SERVER_NOTIFICATION RegisterForServerNotification;
    EFI_BLUETOOTH_ATTRIBUTE_GET_SERVICE_INFO GetServiceInfo;
    EFI_BLUETOOTH_ATTRIBUTE_GET_DEVICE_INFO GetDeviceInfo;
};

#define EFI_BLUETOOTH_ATTRIBUTE_SERVICE_BINDING_PROTOCOL_GUID \
    {0x5639867a, 0x8c8e, 0x408d, {0xac, 0x2f, 0x4b, 0x61, 0xbd, 0xc0, 0xbb, 0xbb}}

#define EFI_BLUETOOTH_LE_CONFIG_PROTOCOL_GUID \
    {0x8f76da58, 0x1f99, 0x4275, {0xa4, 0xec, 0x47, 0x56, 0x51, 0x5b, 0x1c, 0xe8}}

struct efi_bluetooth_le_config_protocol;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_INIT)(
    struct efi_bluetooth_le_config_protocol *This
);

struct efi_bluetooth_le_config_scan_parameter {
    uint32_t Version;
    uint8_t ScanType;
    uint16_t ScanInterval;
    uint16_t ScanWindow;
    uint8_t ScanningFilterPolicy;
    uint8_t AdvertisementFlagFilter;
};

struct efi_bluetooth_le_scan_callback_information {
    struct efi_bluetooth_le_address BDAddr;
    struct efi_bluetooth_le_address DirectAddress;
    uint8_t RemoteDeviceState;
    int8_t RSSI;
    size_t AdvertisementDataSize;
    void *AdvertisementData;
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION)(
    struct efi_bluetooth_le_config_protocol *This,
    void *Context,
    struct efi_bluetooth_le_scan_callback_information *CallbackInfo
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SCAN)(
    struct efi_bluetooth_le_config_protocol *This,
    bool ReScan,
    uint32_t Timeout,
    struct efi_bluetooth_le_config_scan_parameter *ScanParameter,
    EFI_BLUETOOTH_LE_CONFIG_SCAN_CALLBACK_FUNCTION Callback,
    void *Context
);

struct efi_bluetooth_le_config_connect_parameter {
    uint32_t Version;
    uint16_t ScanInterval;
    uint16_t ScanWindow;
    uint16_t ConnIntervalMin;
    uint16_t ConnIntervalMax;
    uint16_t ConnLatency;
    uint16_t SupervisionTimeout;
};

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_CONNECT)(
    struct efi_bluetooth_le_config_protocol *This,
    bool AutoReconnect,
    bool DoBonding,
    struct efi_bluetooth_le_config_connect_parameter *ConnectParameter,
    struct efi_bluetooth_le_address *BD_ADDR
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_DISCONNECT)(
    struct efi_bluetooth_le_config_protocol *This,
    struct efi_bluetooth_le_address *BD_ADDR,
    uint8_t Reason
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_GET_DATA)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SET_DATA)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_GET_REMOTE_DATA)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_CONFIG_DATA_TYPE DataType,
    struct efi_bluetooth_le_address *BDAddr,
    size_t *DataSize,
    void *Data
);

typedef enum {
    EfiBlutoothSmpAuthorizationRequestEvent,
    EfiBlutoothSmpPasskeyReadyEvent,
    EfiBlutoothSmpPasskeyRequestEvent,
    EfiBlutoothSmpOOBDataRequestEvent,
    EfiBlutoothSmpNumericComparisonEvent
} EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_SMP_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    void *Context,
    struct efi_bluetooth_le_address *BDAddr,
    EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE EventDataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_AUTH_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_LE_SMP_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SEND_SMP_AUTH_DATA)(
    struct efi_bluetooth_le_config_protocol *This,
    struct efi_bluetooth_le_address *BDAddr,
    EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE EventDataType,
    size_t DataSize,
    void *Data
);

typedef enum {
    EfiBluetoothSmpLocalIR,
    EfiBluetoothSmpLocalER,
    EfiBluetoothSmpLocalDHK,
    EfiBluetoothSmpKeysDistributed = 0x1000,
    EfiBluetoothSmpKeySize,
    EfiBluetoothSmpKeyType,
    EfiBluetoothSmpPeerLTK,
    EfiBluetoothSmpPeerIRK,
    EfiBluetoothSmpPeerCSRK,
    EfiBluetoothSmpPeerRand,
    EfiBluetoothSmpPeerEDIV,
    EfiBluetoothSmpPeerSignCounter,
    EfiBluetoothSmpLocalLTK,
    EfiBluetoothSmpLocalIRK,
    EfiBluetoothSmpLocalCSRK,
    EfiBluetoothSmpLocalSignCounter,
    EfiBluetoothSmpLocalDIV,
    EfiBluetoothSmpPeerAddressList,
    EfiBluetoothSmpMax
} EFI_BLUETOOTH_LE_SMP_DATA_TYPE;

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    void *Context,
    struct efi_bluetooth_le_address *BDAddr,
    EFI_BLUETOOTH_LE_SMP_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_GET_DATA_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_LE_CONFIG_SMP_GET_DATA_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    void *Context,
    struct efi_bluetooth_le_address *BDAddr,
    EFI_BLUETOOTH_LE_SMP_DATA_TYPE Type,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_SET_DATA_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_LE_CONFIG_SMP_SET_DATA_CALLBACK Callback,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    void *Context,
    EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE CallbackType,
    struct efi_bluetooth_le_address *BDAddr,
    void *InputBuffer,
    size_t InputBufferSize
);

typedef EFI_STATUS (EFI_API *EFI_BLUETOOTH_LE_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK)(
    struct efi_bluetooth_le_config_protocol *This,
    EFI_BLUETOOTH_LE_CONFIG_CONNECT_COMPLETE_CALLBACK Callback,
    void *Context
);

struct efi_bluetooth_le_config_protocol {
    EFI_BLUETOOTH_LE_CONFIG_INIT Init;
    EFI_BLUETOOTH_LE_CONFIG_SCAN Scan;
    EFI_BLUETOOTH_LE_CONFIG_CONNECT Connect;
    EFI_BLUETOOTH_LE_CONFIG_DISCONNECT Disconnect;
    EFI_BLUETOOTH_LE_CONFIG_GET_DATA GetData;
    EFI_BLUETOOTH_LE_CONFIG_SET_DATA SetData;
    EFI_BLUETOOTH_LE_CONFIG_GET_REMOTE_DATA GetRemoteData;
    EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_AUTH_CALLBACK RegisterSmpAuthCallback;
    EFI_BLUETOOTH_LE_CONFIG_SEND_SMP_AUTH_DATA SendSmpAuthData;
    EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_GET_DATA_CALLBACK RegisterSmpGetDataCallback;
    EFI_BLUETOOTH_LE_CONFIG_REGISTER_SMP_SET_DATA_CALLBACK RegisterSmpSetDataCallback;
    EFI_BLUETOOTH_LE_CONFIG_REGISTER_CONNECT_COMPLETE_CALLBACK RegisterLinkConnectCompleteCallback;
};

#ifdef __cplusplus
}
#endif

#endif
