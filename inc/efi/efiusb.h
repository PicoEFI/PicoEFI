#ifndef EFI_EFIUSB_H_
#define EFI_EFIUSB_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EfiUsbDataIn,
    EfiUsbDataOut,
    EfiUsbNoData
} EFI_USB_DATA_DIRECTION;

#define EFI_USB_NOERROR 0x0000
#define EFI_USB_ERR_NOTEXECUTE 0x0001
#define EFI_USB_ERR_STALL 0x0002
#define EFI_USB_ERR_BUFFER 0x0004
#define EFI_USB_ERR_BABBLE 0x0008
#define EFI_USB_ERR_NAK 0x0010
#define EFI_USB_ERR_CRC 0x0020
#define EFI_USB_ERR_TIMEOUT 0x0040
#define EFI_USB_ERR_BITSTUFF 0x0080
#define EFI_USB_ERR_SYSTEM 0x0100

struct efi_usb_device_request {
    uint8_t RequestType;
    uint8_t Request;
    uint16_t Value;
    uint16_t Index;
    uint16_t Length;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_ASYNC_USB_TRANSFER_CALLBACK)(
    void *Data,
    size_t DataLength,
    void *Context,
    uint32_t Status
);

#define EFI_USB2_HC_PROTOCOL_GUID \
    {0x3e745226, 0x9818, 0x45b6, {0xa2, 0xac, 0xd7, 0xcd, 0x0e, 0x8b, 0xa2, 0xbc}}

struct efi_usb2_hc_protocol;

#define EFI_USB_SPEED_FULL 0x0000
#define EFI_USB_SPEED_LOW 0x0001
#define EFI_USB_SPEED_HIGH 0x0002
#define EFI_USB_SPEED_SUPER 0x0003

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_GET_CAPABILITY)(
    struct efi_usb2_hc_protocol *This,
    uint8_t *MaxSpeed,
    uint8_t *PortNumber,
    uint8_t *Is64BitCapable
);

#define EFI_USB_HC_RESET_GLOBAL 0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER 0x0002
#define EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG 0x0004
#define EFI_USB_HC_RESET_HOST_WITH_DEBUG 0x0008

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_RESET)(
    struct efi_usb2_hc_protocol *This,
    uint16_t Attributes
);

typedef enum {
    EfiUsbHcStateHalt,
    EfiUsbHcStateOperational,
    EfiUsbHcStateSuspend,
    EfiUsbHcStateMaximum
} EFI_USB_HC_STATE;

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_GET_STATE)(
    struct efi_usb2_hc_protocol *This,
    EFI_USB_HC_STATE *State
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_SET_STATE)(
    struct efi_usb2_hc_protocol *This,
    EFI_USB_HC_STATE State
);

struct efi_usb2_hc_transaction_translator {
    uint8_t TranslatorHubAddress;
    uint8_t TranslatorPortNumber;
};

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_CONTROL_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    struct efi_usb_device_request *Request,
    EFI_USB_DATA_DIRECTION TransferDirection,
    void *Data,
    size_t *DataLength,
    uintptr_t TimeOut,
    struct efi_usb2_hc_transaction_translator *Translator,
    uint32_t *TransferResult
);

/* The specification refers to this value but never prints it; it is the one firmware uses. */
#define EFI_USB_MAX_BULK_BUFFER_NUM 10

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_BULK_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t EndPointAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    uint8_t DataBuffersNumber,
    void *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
    size_t *DataLength,
    uint8_t *DataToggle,
    uintptr_t TimeOut,
    struct efi_usb2_hc_transaction_translator *Translator,
    uint32_t *TransferResult
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t EndPointAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    bool IsNewTransfer,
    uint8_t *DataToggle,
    uintptr_t PollingInterval,
    size_t DataLength,
    struct efi_usb2_hc_transaction_translator *Translator,
    EFI_ASYNC_USB_TRANSFER_CALLBACK CallBackFunction,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t EndPointAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    void *Data,
    size_t *DataLength,
    uint8_t *DataToggle,
    uintptr_t TimeOut,
    struct efi_usb2_hc_transaction_translator *Translator,
    uint32_t *TransferResult
);

#define EFI_USB_MAX_ISO_BUFFER_NUM 7
#define EFI_USB_MAX_ISO_BUFFER_NUM1 2

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ISOCHRONOUS_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t EndPointAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    uint8_t DataBuffersNumber,
    void *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    size_t DataLength,
    struct efi_usb2_hc_transaction_translator *Translator,
    uint32_t *TransferResult
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER)(
    struct efi_usb2_hc_protocol *This,
    uint8_t DeviceAddress,
    uint8_t EndPointAddress,
    uint8_t DeviceSpeed,
    size_t MaximumPacketLength,
    uint8_t DataBuffersNumber,
    void *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    size_t DataLength,
    struct efi_usb2_hc_transaction_translator *Translator,
    EFI_ASYNC_USB_TRANSFER_CALLBACK IsochronousCallBack,
    void *Context
);

struct efi_usb_port_status {
    uint16_t PortStatus;
    uint16_t PortChangeStatus;
};

#define EFI_USB_PORT_STAT_CONNECTION 0x0001
#define EFI_USB_PORT_STAT_ENABLE 0x0002
#define EFI_USB_PORT_STAT_SUSPEND 0x0004
#define EFI_USB_PORT_STAT_OVERCURRENT 0x0008
#define EFI_USB_PORT_STAT_RESET 0x0010
#define EFI_USB_PORT_STAT_POWER 0x0100
#define EFI_USB_PORT_STAT_LOW_SPEED 0x0200
#define EFI_USB_PORT_STAT_HIGH_SPEED 0x0400
#define EFI_USB_PORT_STAT_SUPER_SPEED 0x0800
#define EFI_USB_PORT_STAT_OWNER 0x2000

#define EFI_USB_PORT_STAT_C_CONNECTION 0x0001
#define EFI_USB_PORT_STAT_C_ENABLE 0x0002
#define EFI_USB_PORT_STAT_C_SUSPEND 0x0004
#define EFI_USB_PORT_STAT_C_OVERCURRENT 0x0008
#define EFI_USB_PORT_STAT_C_RESET 0x0010

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS)(
    struct efi_usb2_hc_protocol *This,
    uint8_t PortNumber,
    struct efi_usb_port_status *PortStatus
);

typedef enum {
    EfiUsbPortEnable = 1,
    EfiUsbPortSuspend = 2,
    EfiUsbPortReset = 4,
    EfiUsbPortPower = 8,
    EfiUsbPortOwner = 13,
    EfiUsbPortConnectChange = 16,
    EfiUsbPortEnableChange = 17,
    EfiUsbPortSuspendChange = 18,
    EfiUsbPortOverCurrentChange = 19,
    EfiUsbPortResetChange = 20
} EFI_USB_PORT_FEATURE;

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE)(
    struct efi_usb2_hc_protocol *This,
    uint8_t PortNumber,
    EFI_USB_PORT_FEATURE PortFeature
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE)(
    struct efi_usb2_hc_protocol *This,
    uint8_t PortNumber,
    EFI_USB_PORT_FEATURE PortFeature
);

/* The specification's structure body types SyncInterruptTransfer as the asynchronous call. */
struct efi_usb2_hc_protocol {
    EFI_USB2_HC_PROTOCOL_GET_CAPABILITY GetCapability;
    EFI_USB2_HC_PROTOCOL_RESET Reset;
    EFI_USB2_HC_PROTOCOL_GET_STATE GetState;
    EFI_USB2_HC_PROTOCOL_SET_STATE SetState;
    EFI_USB2_HC_PROTOCOL_CONTROL_TRANSFER ControlTransfer;
    EFI_USB2_HC_PROTOCOL_BULK_TRANSFER BulkTransfer;
    EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER AsyncInterruptTransfer;
    EFI_USB2_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER SyncInterruptTransfer;
    EFI_USB2_HC_PROTOCOL_ISOCHRONOUS_TRANSFER IsochronousTransfer;
    EFI_USB2_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER AsyncIsochronousTransfer;
    EFI_USB2_HC_PROTOCOL_GET_ROOTHUB_PORT_STATUS GetRootHubPortStatus;
    EFI_USB2_HC_PROTOCOL_SET_ROOTHUB_PORT_FEATURE SetRootHubPortFeature;
    EFI_USB2_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE ClearRootHubPortFeature;
    uint16_t MajorRevision;
    uint16_t MinorRevision;
};

#define EFI_USB_IO_PROTOCOL_GUID \
    {0x2B2F68D6, 0x0CD2, 0x44cf, {0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75}}

struct efi_usb_io_protocol;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_CONTROL_TRANSFER)(
    struct efi_usb_io_protocol *This,
    struct efi_usb_device_request *Request,
    EFI_USB_DATA_DIRECTION Direction,
    uint32_t Timeout,
    void *Data,
    size_t DataLength,
    uint32_t *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_BULK_TRANSFER)(
    struct efi_usb_io_protocol *This,
    uint8_t DeviceEndpoint,
    void *Data,
    size_t *DataLength,
    uintptr_t Timeout,
    uint32_t *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER)(
    struct efi_usb_io_protocol *This,
    uint8_t DeviceEndpoint,
    bool IsNewTransfer,
    uintptr_t PollingInterval,
    size_t DataLength,
    EFI_ASYNC_USB_TRANSFER_CALLBACK InterruptCallBack,
    void *Context
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_SYNC_INTERRUPT_TRANSFER)(
    struct efi_usb_io_protocol *This,
    uint8_t DeviceEndpoint,
    void *Data,
    size_t *DataLength,
    uintptr_t Timeout,
    uint32_t *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ISOCHRONOUS_TRANSFER)(
    struct efi_usb_io_protocol *This,
    uint8_t DeviceEndpoint,
    void *Data,
    size_t DataLength,
    uint32_t *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER)(
    struct efi_usb_io_protocol *This,
    uint8_t DeviceEndpoint,
    void *Data,
    size_t DataLength,
    EFI_ASYNC_USB_TRANSFER_CALLBACK IsochronousCallBack,
    void *Context
);

struct efi_usb_device_descriptor {
    uint8_t Length;
    uint8_t DescriptorType;
    uint16_t BcdUSB;
    uint8_t DeviceClass;
    uint8_t DeviceSubClass;
    uint8_t DeviceProtocol;
    uint8_t MaxPacketSize0;
    uint16_t IdVendor;
    uint16_t IdProduct;
    uint16_t BcdDevice;
    uint8_t StrManufacturer;
    uint8_t StrProduct;
    uint8_t StrSerialNumber;
    uint8_t NumConfigurations;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_DEVICE_DESCRIPTOR)(
    struct efi_usb_io_protocol *This,
    struct efi_usb_device_descriptor *DeviceDescriptor
);

struct efi_usb_config_descriptor {
    uint8_t Length;
    uint8_t DescriptorType;
    uint16_t TotalLength;
    uint8_t NumInterfaces;
    uint8_t ConfigurationValue;
    uint8_t Configuration;
    uint8_t Attributes;
    uint8_t MaxPower;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_CONFIG_DESCRIPTOR)(
    struct efi_usb_io_protocol *This,
    struct efi_usb_config_descriptor *ConfigurationDescriptor
);

struct efi_usb_interface_descriptor {
    uint8_t Length;
    uint8_t DescriptorType;
    uint8_t InterfaceNumber;
    uint8_t AlternateSetting;
    uint8_t NumEndpoints;
    uint8_t InterfaceClass;
    uint8_t InterfaceSubClass;
    uint8_t InterfaceProtocol;
    uint8_t Interface;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_INTERFACE_DESCRIPTOR)(
    struct efi_usb_io_protocol *This,
    struct efi_usb_interface_descriptor *InterfaceDescriptor
);

struct efi_usb_endpoint_descriptor {
    uint8_t Length;
    uint8_t DescriptorType;
    uint8_t EndpointAddress;
    uint8_t Attributes;
    uint16_t MaxPacketSize;
    uint8_t Interval;
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR)(
    struct efi_usb_io_protocol *This,
    uint8_t EndpointIndex,
    struct efi_usb_endpoint_descriptor *EndpointDescriptor
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_STRING_DESCRIPTOR)(
    struct efi_usb_io_protocol *This,
    uint16_t LangID,
    uint8_t StringID,
    uint16_t **String
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_SUPPORTED_LANGUAGES)(
    struct efi_usb_io_protocol *This,
    uint16_t **LangIDTable,
    uint16_t *TableSize
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_PORT_RESET)(struct efi_usb_io_protocol *This);

/* The specification's structure body misspells the type of UsbSyncInterruptTransfer. */
struct efi_usb_io_protocol {
    EFI_USB_IO_CONTROL_TRANSFER UsbControlTransfer;
    EFI_USB_IO_BULK_TRANSFER UsbBulkTransfer;
    EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER UsbAsyncInterruptTransfer;
    EFI_USB_IO_SYNC_INTERRUPT_TRANSFER UsbSyncInterruptTransfer;
    EFI_USB_IO_ISOCHRONOUS_TRANSFER UsbIsochronousTransfer;
    EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER UsbAsyncIsochronousTransfer;
    EFI_USB_IO_GET_DEVICE_DESCRIPTOR UsbGetDeviceDescriptor;
    EFI_USB_IO_GET_CONFIG_DESCRIPTOR UsbGetConfigDescriptor;
    EFI_USB_IO_GET_INTERFACE_DESCRIPTOR UsbGetInterfaceDescriptor;
    EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR UsbGetEndpointDescriptor;
    EFI_USB_IO_GET_STRING_DESCRIPTOR UsbGetStringDescriptor;
    EFI_USB_IO_GET_SUPPORTED_LANGUAGES UsbGetSupportedLanguages;
    EFI_USB_IO_PORT_RESET UsbPortReset;
};

#define EFI_USBFN_IO_PROTOCOL_GUID \
    {0x32d2963a, 0xfe5d, 0x4f30, {0xb6, 0x33, 0x6e, 0x5d, 0xc5, 0x58, 0x3, 0xcc}}

#define EFI_USBFN_IO_PROTOCOL_REVISION 0x00010001

struct efi_usbfn_io_protocol;

typedef enum _EFI_USBFN_PORT_TYPE {
    EfiUsbUnknownPort = 0,
    EfiUsbStandardDownstreamPort,
    EfiUsbChargingDownstreamPort,
    EfiUsbDedicatedChargingPort,
    EfiUsbInvalidDedicatedChargingPort
} EFI_USBFN_PORT_TYPE;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_DETECT_PORT)(
    struct efi_usbfn_io_protocol *This,
    EFI_USBFN_PORT_TYPE *PortType
);

struct efi_usb_interface_info {
    struct efi_usb_interface_descriptor *InterfaceDescriptor;
    struct efi_usb_endpoint_descriptor **EndpointDescriptorTable;
};

struct efi_usb_config_info {
    struct efi_usb_config_descriptor *ConfigDescriptor;
    struct efi_usb_interface_info **InterfaceInfoTable;
};

struct efi_usb_device_info {
    struct efi_usb_device_descriptor *DeviceDescriptor;
    struct efi_usb_config_info **ConfigInfoTable;
};

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_CONFIGURE_ENABLE_ENDPOINTS)(
    struct efi_usbfn_io_protocol *This,
    struct efi_usb_device_info *DeviceInfo
);

/* No isochronous (0x01) or interrupt (0x03) type: the protocol supports neither. */
typedef enum _EFI_USB_ENDPOINT_TYPE {
    EfiUsbEndpointControl = 0x00,
    EfiUsbEndpointBulk = 0x02
} EFI_USB_ENDPOINT_TYPE;

typedef enum _EFI_USB_BUS_SPEED {
    EfiUsbBusSpeedUnknown = 0,
    EfiUsbBusSpeedLow,
    EfiUsbBusSpeedFull,
    EfiUsbBusSpeedHigh,
    EfiUsbBusSpeedSuper,
    EfiUsbBusSpeedMaximum = EfiUsbBusSpeedSuper
} EFI_USB_BUS_SPEED;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_ENDPOINT_MAXPACKET_SIZE)(
    struct efi_usbfn_io_protocol *This,
    EFI_USB_ENDPOINT_TYPE EndpointType,
    EFI_USB_BUS_SPEED BusSpeed,
    uint16_t *MaxPacketSize
);

typedef enum _EFI_USBFN_DEVICE_INFO_ID {
    EfiUsbDeviceInfoUnknown = 0,
    EfiUsbDeviceInfoSerialNumber,
    EfiUsbDeviceInfoManufacturerName,
    EfiUsbDeviceInfoProductName
} EFI_USBFN_DEVICE_INFO_ID;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_DEVICE_INFO)(
    struct efi_usbfn_io_protocol *This,
    EFI_USBFN_DEVICE_INFO_ID Id,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_VENDOR_ID_PRODUCT_ID)(
    struct efi_usbfn_io_protocol *This,
    uint16_t *Vid,
    uint16_t *Pid
);

typedef enum _EFI_USBFN_ENDPOINT_DIRECTION {
    EfiUsbEndpointDirectionHostOut = 0,
    EfiUsbEndpointDirectionHostIn,
    EfiUsbEndpointDirectionDeviceTx = EfiUsbEndpointDirectionHostIn,
    EfiUsbEndpointDirectionDeviceRx = EfiUsbEndpointDirectionHostOut
} EFI_USBFN_ENDPOINT_DIRECTION;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_ABORT_TRANSFER)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_ENDPOINT_STALL_STATE)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction,
    bool *State
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_SET_ENDPOINT_STALL_STATE)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction,
    bool State
);

typedef enum _EFI_USBFN_MESSAGE {
    EfiUsbMsgNone = 0,
    EfiUsbMsgSetupPacket,
    EfiUsbMsgEndpointStatusChangedRx,
    EfiUsbMsgEndpointStatusChangedTx,
    EfiUsbMsgBusEventDetach,
    EfiUsbMsgBusEventAttach,
    EfiUsbMsgBusEventReset,
    EfiUsbMsgBusEventSuspend,
    EfiUsbMsgBusEventResume,
    EfiUsbMsgBusEventSpeed
} EFI_USBFN_MESSAGE;

typedef enum _EFI_USBFN_TRANSFER_STATUS {
    EfiUsbTransferStatusUnknown = 0,
    EfiUsbTransferStatusComplete,
    EfiUsbTransferStatusAborted,
    EfiUsbTransferStatusActive,
    EfiUsbTransferStatusNone
} EFI_USBFN_TRANSFER_STATUS;

struct efi_usbfn_transfer_result {
    size_t BytesTransferred;
    EFI_USBFN_TRANSFER_STATUS TransferStatus;
    uint8_t EndpointIndex;
    EFI_USBFN_ENDPOINT_DIRECTION Direction;
    void *Buffer;
};

union efi_usbfn_message_payload {
    struct efi_usb_device_request udr;
    struct efi_usbfn_transfer_result utr;
    EFI_USB_BUS_SPEED ubs;
};

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_EVENTHANDLER)(
    struct efi_usbfn_io_protocol *This,
    EFI_USBFN_MESSAGE *Message,
    size_t *PayloadSize,
    union efi_usbfn_message_payload *Payload
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_TRANSFER)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_MAXTRANSFER_SIZE)(
    struct efi_usbfn_io_protocol *This,
    size_t *MaxTransferSize
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_ALLOCATE_TRANSFER_BUFFER)(
    struct efi_usbfn_io_protocol *This,
    size_t Size,
    void **Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_FREE_TRANSFER_BUFFER)(
    struct efi_usbfn_io_protocol *This,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_START_CONTROLLER)(struct efi_usbfn_io_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_STOP_CONTROLLER)(struct efi_usbfn_io_protocol *This);

typedef enum _EFI_USBFN_POLICY_TYPE {
    EfiUsbPolicyUndefined = 0,
    EfiUsbPolicyMaxTransactionSize,
    EfiUsbPolicyZeroLengthTerminationSupport,
    EfiUsbPolicyZeroLengthTermination
} EFI_USBFN_POLICY_TYPE;

/* Named as the protocol structure names them; the prototypes print these two without _IO. */
typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_SET_ENDPOINT_POLICY)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_USBFN_POLICY_TYPE PolicyType,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_ENDPOINT_POLICY)(
    struct efi_usbfn_io_protocol *This,
    uint8_t EndpointIndex,
    EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_USBFN_POLICY_TYPE PolicyType,
    size_t *BufferSize,
    void *Buffer
);

struct efi_usbfn_io_protocol {
    uint32_t Revision;
    EFI_USBFN_IO_DETECT_PORT DetectPort;
    EFI_USBFN_IO_CONFIGURE_ENABLE_ENDPOINTS ConfigureEnableEndpoints;
    EFI_USBFN_IO_GET_ENDPOINT_MAXPACKET_SIZE GetEndpointMaxPacketSize;
    EFI_USBFN_IO_GET_DEVICE_INFO GetDeviceInfo;
    EFI_USBFN_IO_GET_VENDOR_ID_PRODUCT_ID GetVendorIdProductId;
    EFI_USBFN_IO_ABORT_TRANSFER AbortTransfer;
    EFI_USBFN_IO_GET_ENDPOINT_STALL_STATE GetEndpointStallState;
    EFI_USBFN_IO_SET_ENDPOINT_STALL_STATE SetEndpointStallState;
    EFI_USBFN_IO_EVENTHANDLER EventHandler;
    EFI_USBFN_IO_TRANSFER Transfer;
    EFI_USBFN_IO_GET_MAXTRANSFER_SIZE GetMaxTransferSize;
    EFI_USBFN_IO_ALLOCATE_TRANSFER_BUFFER AllocateTransferBuffer;
    EFI_USBFN_IO_FREE_TRANSFER_BUFFER FreeTransferBuffer;
    EFI_USBFN_IO_START_CONTROLLER StartController;
    EFI_USBFN_IO_STOP_CONTROLLER StopController;
    EFI_USBFN_IO_SET_ENDPOINT_POLICY SetEndpointPolicy;
    EFI_USBFN_IO_GET_ENDPOINT_POLICY GetEndpointPolicy;
};

#ifdef __cplusplus
}
#endif

#endif
