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

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 RequestType;
    EFI_UINT8 Request;
    EFI_UINT16 Value;
    EFI_UINT16 Index;
    EFI_UINT16 Length;
} EFI_USB_DEVICE_REQUEST;

typedef EFI_STATUS (EFI_API *EFI_ASYNC_USB_TRANSFER_CALLBACK)(
    EFI_IN EFI_VOID *Data,
    EFI_IN EFI_UINTN DataLength,
    EFI_IN EFI_VOID *Context,
    EFI_IN EFI_UINT32 Status
);

#define EFI_USB2_HC_PROTOCOL_GUID \
    {0x3e745226, 0x9818, 0x45b6, {0xa2, 0xac, 0xd7, 0xcd, 0x0e, 0x8b, 0xa2, 0xbc}}

typedef struct _EFI_USB2_HC_PROTOCOL EFI_USB2_HC_PROTOCOL;

#define EFI_USB_SPEED_FULL 0x0000
#define EFI_USB_SPEED_LOW 0x0001
#define EFI_USB_SPEED_HIGH 0x0002
#define EFI_USB_SPEED_SUPER 0x0003

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_GET_CAPABILITY)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_OUT EFI_UINT8 *MaxSpeed,
    EFI_OUT EFI_UINT8 *PortNumber,
    EFI_OUT EFI_UINT8 *Is64BitCapable
);

#define EFI_USB_HC_RESET_GLOBAL 0x0001
#define EFI_USB_HC_RESET_HOST_CONTROLLER 0x0002
#define EFI_USB_HC_RESET_GLOBAL_WITH_DEBUG 0x0004
#define EFI_USB_HC_RESET_HOST_WITH_DEBUG 0x0008

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_RESET)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT16 Attributes
);

typedef enum {
    EfiUsbHcStateHalt,
    EfiUsbHcStateOperational,
    EfiUsbHcStateSuspend,
    EfiUsbHcStateMaximum
} EFI_USB_HC_STATE;

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_GET_STATE)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_OUT EFI_USB_HC_STATE *State
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_SET_STATE)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_USB_HC_STATE State
);

typedef struct {
    EFI_UINT8 TranslatorHubAddress;
    EFI_UINT8 TranslatorPortNumber;
} EFI_USB2_HC_TRANSACTION_TRANSLATOR;

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_CONTROL_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_USB_DEVICE_REQUEST *Request,
    EFI_IN EFI_USB_DATA_DIRECTION TransferDirection,
    EFI_IN EFI_OUT EFI_VOID *Data EFI_OPTIONAL,
    EFI_IN EFI_OUT EFI_UINTN *DataLength EFI_OPTIONAL,
    EFI_IN EFI_UINTN TimeOut,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    EFI_OUT EFI_UINT32 *TransferResult
);

/* The specification refers to this value but never prints it; it is the one firmware uses. */
#define EFI_USB_MAX_BULK_BUFFER_NUM 10

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_BULK_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 EndPointAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_UINT8 DataBuffersNumber,
    EFI_IN EFI_OUT EFI_VOID *Data[EFI_USB_MAX_BULK_BUFFER_NUM],
    EFI_IN EFI_OUT EFI_UINTN *DataLength,
    EFI_IN EFI_OUT EFI_UINT8 *DataToggle,
    EFI_IN EFI_UINTN TimeOut,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    EFI_OUT EFI_UINT32 *TransferResult
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ASYNC_INTERRUPT_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 EndPointAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_BOOLEAN IsNewTransfer,
    EFI_IN EFI_OUT EFI_UINT8 *DataToggle,
    EFI_IN EFI_UINTN PollingInterval EFI_OPTIONAL,
    EFI_IN EFI_UINTN DataLength EFI_OPTIONAL,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator EFI_OPTIONAL,
    EFI_IN EFI_ASYNC_USB_TRANSFER_CALLBACK CallBackFunction EFI_OPTIONAL,
    EFI_IN EFI_VOID *Context EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_SYNC_INTERRUPT_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 EndPointAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_OUT EFI_UINTN *DataLength,
    EFI_IN EFI_OUT EFI_UINT8 *DataToggle,
    EFI_IN EFI_UINTN TimeOut,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    EFI_OUT EFI_UINT32 *TransferResult
);

#define EFI_USB_MAX_ISO_BUFFER_NUM 7
#define EFI_USB_MAX_ISO_BUFFER_NUM1 2

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ISOCHRONOUS_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 EndPointAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_UINT8 DataBuffersNumber,
    EFI_IN EFI_OUT EFI_VOID *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    EFI_IN EFI_UINTN DataLength,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    EFI_OUT EFI_UINT32 *TransferResult
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_ASYNC_ISOCHRONOUS_TRANSFER)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceAddress,
    EFI_IN EFI_UINT8 EndPointAddress,
    EFI_IN EFI_UINT8 DeviceSpeed,
    EFI_IN EFI_UINTN MaximumPacketLength,
    EFI_IN EFI_UINT8 DataBuffersNumber,
    EFI_IN EFI_OUT EFI_VOID *Data[EFI_USB_MAX_ISO_BUFFER_NUM],
    EFI_IN EFI_UINTN DataLength,
    EFI_IN EFI_USB2_HC_TRANSACTION_TRANSLATOR *Translator,
    EFI_IN EFI_ASYNC_USB_TRANSFER_CALLBACK IsochronousCallBack,
    EFI_IN EFI_VOID *Context EFI_OPTIONAL
);

typedef struct {
    EFI_UINT16 PortStatus;
    EFI_UINT16 PortChangeStatus;
} EFI_USB_PORT_STATUS;

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
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 PortNumber,
    EFI_OUT EFI_USB_PORT_STATUS *PortStatus
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
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 PortNumber,
    EFI_IN EFI_USB_PORT_FEATURE PortFeature
);

typedef EFI_STATUS (EFI_API *EFI_USB2_HC_PROTOCOL_CLEAR_ROOTHUB_PORT_FEATURE)(
    EFI_IN EFI_USB2_HC_PROTOCOL *This,
    EFI_IN EFI_UINT8 PortNumber,
    EFI_IN EFI_USB_PORT_FEATURE PortFeature
);

/* The specification's structure body types SyncInterruptTransfer as the asynchronous call. */
struct _EFI_USB2_HC_PROTOCOL {
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
    EFI_UINT16 MajorRevision;
    EFI_UINT16 MinorRevision;
};

#define EFI_USB_IO_PROTOCOL_GUID \
    {0x2B2F68D6, 0x0CD2, 0x44cf, {0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75}}

typedef struct _EFI_USB_IO_PROTOCOL EFI_USB_IO_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_CONTROL_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_USB_DEVICE_REQUEST *Request,
    EFI_IN EFI_USB_DATA_DIRECTION Direction,
    EFI_IN EFI_UINT32 Timeout,
    EFI_IN EFI_OUT EFI_VOID *Data EFI_OPTIONAL,
    EFI_IN EFI_UINTN DataLength EFI_OPTIONAL,
    EFI_OUT EFI_UINT32 *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_BULK_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceEndpoint,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_OUT EFI_UINTN *DataLength,
    EFI_IN EFI_UINTN Timeout,
    EFI_OUT EFI_UINT32 *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ASYNC_INTERRUPT_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceEndpoint,
    EFI_IN EFI_BOOLEAN IsNewTransfer,
    EFI_IN EFI_UINTN PollingInterval EFI_OPTIONAL,
    EFI_IN EFI_UINTN DataLength EFI_OPTIONAL,
    EFI_IN EFI_ASYNC_USB_TRANSFER_CALLBACK InterruptCallBack EFI_OPTIONAL,
    EFI_IN EFI_VOID *Context EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_SYNC_INTERRUPT_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceEndpoint,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_OUT EFI_UINTN *DataLength,
    EFI_IN EFI_UINTN Timeout,
    EFI_OUT EFI_UINT32 *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ISOCHRONOUS_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceEndpoint,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_UINTN DataLength,
    EFI_OUT EFI_UINT32 *Status
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_ASYNC_ISOCHRONOUS_TRANSFER)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 DeviceEndpoint,
    EFI_IN EFI_OUT EFI_VOID *Data,
    EFI_IN EFI_UINTN DataLength,
    EFI_IN EFI_ASYNC_USB_TRANSFER_CALLBACK IsochronousCallBack,
    EFI_IN EFI_VOID *Context EFI_OPTIONAL
);

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Length;
    EFI_UINT8 DescriptorType;
    EFI_UINT16 BcdUSB;
    EFI_UINT8 DeviceClass;
    EFI_UINT8 DeviceSubClass;
    EFI_UINT8 DeviceProtocol;
    EFI_UINT8 MaxPacketSize0;
    EFI_UINT16 IdVendor;
    EFI_UINT16 IdProduct;
    EFI_UINT16 BcdDevice;
    EFI_UINT8 StrManufacturer;
    EFI_UINT8 StrProduct;
    EFI_UINT8 StrSerialNumber;
    EFI_UINT8 NumConfigurations;
} EFI_USB_DEVICE_DESCRIPTOR;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_DEVICE_DESCRIPTOR)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_OUT EFI_USB_DEVICE_DESCRIPTOR *DeviceDescriptor
);

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Length;
    EFI_UINT8 DescriptorType;
    EFI_UINT16 TotalLength;
    EFI_UINT8 NumInterfaces;
    EFI_UINT8 ConfigurationValue;
    EFI_UINT8 Configuration;
    EFI_UINT8 Attributes;
    EFI_UINT8 MaxPower;
} EFI_USB_CONFIG_DESCRIPTOR;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_CONFIG_DESCRIPTOR)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_OUT EFI_USB_CONFIG_DESCRIPTOR *ConfigurationDescriptor
);

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Length;
    EFI_UINT8 DescriptorType;
    EFI_UINT8 InterfaceNumber;
    EFI_UINT8 AlternateSetting;
    EFI_UINT8 NumEndpoints;
    EFI_UINT8 InterfaceClass;
    EFI_UINT8 InterfaceSubClass;
    EFI_UINT8 InterfaceProtocol;
    EFI_UINT8 Interface;
} EFI_USB_INTERFACE_DESCRIPTOR;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_INTERFACE_DESCRIPTOR)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_OUT EFI_USB_INTERFACE_DESCRIPTOR *InterfaceDescriptor
);

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Length;
    EFI_UINT8 DescriptorType;
    EFI_UINT8 EndpointAddress;
    EFI_UINT8 Attributes;
    EFI_UINT16 MaxPacketSize;
    EFI_UINT8 Interval;
} EFI_USB_ENDPOINT_DESCRIPTOR;

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_ENDPOINT_DESCRIPTOR)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_OUT EFI_USB_ENDPOINT_DESCRIPTOR *EndpointDescriptor
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_STRING_DESCRIPTOR)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_IN EFI_UINT16 LangID,
    EFI_IN EFI_UINT8 StringID,
    EFI_OUT EFI_CHAR16 **String
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_GET_SUPPORTED_LANGUAGES)(
    EFI_IN EFI_USB_IO_PROTOCOL *This,
    EFI_OUT EFI_UINT16 **LangIDTable,
    EFI_OUT EFI_UINT16 *TableSize
);

typedef EFI_STATUS (EFI_API *EFI_USB_IO_PORT_RESET)(EFI_IN EFI_USB_IO_PROTOCOL *This);

/* The specification's structure body misspells the type of UsbSyncInterruptTransfer. */
struct _EFI_USB_IO_PROTOCOL {
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

typedef struct _EFI_USBFN_IO_PROTOCOL EFI_USBFN_IO_PROTOCOL;

typedef enum _EFI_USBFN_PORT_TYPE {
    EfiUsbUnknownPort = 0,
    EfiUsbStandardDownstreamPort,
    EfiUsbChargingDownstreamPort,
    EfiUsbDedicatedChargingPort,
    EfiUsbInvalidDedicatedChargingPort
} EFI_USBFN_PORT_TYPE;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_DETECT_PORT)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_OUT EFI_USBFN_PORT_TYPE *PortType
);

typedef struct {
    EFI_USB_INTERFACE_DESCRIPTOR *InterfaceDescriptor;
    EFI_USB_ENDPOINT_DESCRIPTOR **EndpointDescriptorTable;
} EFI_USB_INTERFACE_INFO;

typedef struct {
    EFI_USB_CONFIG_DESCRIPTOR *ConfigDescriptor;
    EFI_USB_INTERFACE_INFO **InterfaceInfoTable;
} EFI_USB_CONFIG_INFO;

typedef struct {
    EFI_USB_DEVICE_DESCRIPTOR *DeviceDescriptor;
    EFI_USB_CONFIG_INFO **ConfigInfoTable;
} EFI_USB_DEVICE_INFO;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_CONFIGURE_ENABLE_ENDPOINTS)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_USB_DEVICE_INFO *DeviceInfo
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
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_USB_ENDPOINT_TYPE EndpointType,
    EFI_IN EFI_USB_BUS_SPEED BusSpeed,
    EFI_OUT EFI_UINT16 *MaxPacketSize
);

typedef enum _EFI_USBFN_DEVICE_INFO_ID {
    EfiUsbDeviceInfoUnknown = 0,
    EfiUsbDeviceInfoSerialNumber,
    EfiUsbDeviceInfoManufacturerName,
    EfiUsbDeviceInfoProductName
} EFI_USBFN_DEVICE_INFO_ID;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_DEVICE_INFO)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_USBFN_DEVICE_INFO_ID Id,
    EFI_IN EFI_OUT EFI_UINTN *BufferSize,
    EFI_OUT EFI_VOID *Buffer EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_VENDOR_ID_PRODUCT_ID)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_OUT EFI_UINT16 *Vid,
    EFI_OUT EFI_UINT16 *Pid
);

typedef enum _EFI_USBFN_ENDPOINT_DIRECTION {
    EfiUsbEndpointDirectionHostOut = 0,
    EfiUsbEndpointDirectionHostIn,
    EfiUsbEndpointDirectionDeviceTx = EfiUsbEndpointDirectionHostIn,
    EfiUsbEndpointDirectionDeviceRx = EfiUsbEndpointDirectionHostOut
} EFI_USBFN_ENDPOINT_DIRECTION;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_ABORT_TRANSFER)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_ENDPOINT_STALL_STATE)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_IN EFI_OUT EFI_BOOLEAN *State
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_SET_ENDPOINT_STALL_STATE)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_IN EFI_BOOLEAN State
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

typedef struct _EFI_USBFN_TRANSFER_RESULT {
    EFI_UINTN BytesTransferred;
    EFI_USBFN_TRANSFER_STATUS TransferStatus;
    EFI_UINT8 EndpointIndex;
    EFI_USBFN_ENDPOINT_DIRECTION Direction;
    EFI_VOID *Buffer;
} EFI_USBFN_TRANSFER_RESULT;

typedef union _EFI_USBFN_MESSAGE_PAYLOAD {
    EFI_USB_DEVICE_REQUEST udr;
    EFI_USBFN_TRANSFER_RESULT utr;
    EFI_USB_BUS_SPEED ubs;
} EFI_USBFN_MESSAGE_PAYLOAD;

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_EVENTHANDLER)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_OUT EFI_USBFN_MESSAGE *Message,
    EFI_IN EFI_OUT EFI_UINTN *PayloadSize,
    EFI_OUT EFI_USBFN_MESSAGE_PAYLOAD *Payload
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_TRANSFER)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_IN EFI_OUT EFI_UINTN *BufferSize,
    EFI_IN EFI_OUT EFI_VOID *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_MAXTRANSFER_SIZE)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_OUT EFI_UINTN *MaxTransferSize
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_ALLOCATE_TRANSFER_BUFFER)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINTN Size,
    EFI_OUT EFI_VOID **Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_FREE_TRANSFER_BUFFER)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_VOID *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_START_CONTROLLER)(EFI_IN EFI_USBFN_IO_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_STOP_CONTROLLER)(EFI_IN EFI_USBFN_IO_PROTOCOL *This);

typedef enum _EFI_USBFN_POLICY_TYPE {
    EfiUsbPolicyUndefined = 0,
    EfiUsbPolicyMaxTransactionSize,
    EfiUsbPolicyZeroLengthTerminationSupport,
    EfiUsbPolicyZeroLengthTermination
} EFI_USBFN_POLICY_TYPE;

/* Named as the protocol structure names them; the prototypes print these two without _IO. */
typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_SET_ENDPOINT_POLICY)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_IN EFI_USBFN_POLICY_TYPE PolicyType,
    EFI_IN EFI_UINTN BufferSize,
    EFI_IN EFI_VOID *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_USBFN_IO_GET_ENDPOINT_POLICY)(
    EFI_IN EFI_USBFN_IO_PROTOCOL *This,
    EFI_IN EFI_UINT8 EndpointIndex,
    EFI_IN EFI_USBFN_ENDPOINT_DIRECTION Direction,
    EFI_IN EFI_USBFN_POLICY_TYPE PolicyType,
    EFI_IN EFI_OUT EFI_UINTN *BufferSize,
    EFI_IN EFI_OUT EFI_VOID *Buffer
);

struct _EFI_USBFN_IO_PROTOCOL {
    EFI_UINT32 Revision;
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
