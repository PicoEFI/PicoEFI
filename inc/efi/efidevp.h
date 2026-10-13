#ifndef EFI_EFIDEVP_H_
#define EFI_EFIDEVP_H_

#include <stddef.h>

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
    {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
    EFI_UINT8 Type;
    EFI_UINT8 SubType;
    EFI_UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

#define EFI_HARDWARE_DEVICE_PATH 0x01
#define EFI_ACPI_DEVICE_PATH 0x02
#define EFI_MESSAGING_DEVICE_PATH 0x03
#define EFI_MEDIA_DEVICE_PATH 0x04
#define EFI_BBS_DEVICE_PATH 0x05
#define EFI_END_DEVICE_PATH_TYPE 0x7F

#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE 0xFF
#define EFI_END_INSTANCE_DEVICE_PATH_SUBTYPE 0x01
#define EFI_END_DEVICE_PATH_LENGTH (sizeof(EFI_DEVICE_PATH_PROTOCOL))

#define EFI_HW_PCI_DP 0x01

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 Function;
    EFI_UINT8 Device;
} EFI_PCI_DEVICE_PATH;

#define EFI_HW_PCCARD_DP 0x02

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 FunctionNumber;
} EFI_PCCARD_DEVICE_PATH;

#define EFI_HW_MEMMAP_DP 0x03

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 MemoryType;
    EFI_PHYSICAL_ADDRESS StartingAddress;
    EFI_PHYSICAL_ADDRESS EndingAddress;
} EFI_MEMMAP_DEVICE_PATH;

#define EFI_HW_VENDOR_DP 0x04

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID Guid;
} EFI_VENDOR_DEVICE_PATH;

#define EFI_HW_CONTROLLER_DP 0x05

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 ControllerNumber;
} EFI_CONTROLLER_DEVICE_PATH;

#define EFI_HW_BMC_DP 0x06

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 InterfaceType;
    EFI_UINT8 BaseAddress[8];
} EFI_BMC_DEVICE_PATH;

/* The shift is done in EFI_UINT32 so that product numbers from 0x8000 up do not overflow. */
#define EFI_PNP_ID(ID) ((EFI_UINT32)(((EFI_UINT32)(ID) << 16) | 0x41D0))
#define EFI_EISA_PNP_ID(ID) EFI_PNP_ID(ID)

#define EFI_PNP_EISA_ID_CONST 0x41d0
#define EFI_EISA_ID(_Name, _Num) ((EFI_UINT32)(_Name) | ((EFI_UINT32)(_Num) << 16))
#define EFI_PNP_EISA_ID_MASK 0xffff
#define EFI_EISA_ID_TO_NUM(_Id) ((EFI_UINT32)(_Id) >> 16)

#define EFI_ACPI_DP 0x01

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 HID;
    EFI_UINT32 UID;
} EFI_ACPI_HID_DEVICE_PATH;

#define EFI_ACPI_EXTENDED_DP 0x02

/* HidStr starts _HIDSTR; _UIDSTR and _CIDSTR follow it. */
typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 HID;
    EFI_UINT32 UID;
    EFI_UINT32 CID;
    EFI_CHAR8 HidStr[1];
} EFI_ACPI_EXTENDED_HID_DEVICE_PATH;

#define EFI_ACPI_ADR_DP 0x03

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 ADR;
} EFI_ACPI_ADR_DEVICE_PATH;

#define EFI_ACPI_NVDIMM_DP 0x04

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 NFITDeviceHandle;
} EFI_ACPI_NVDIMM_DEVICE_PATH;

#define EFI_MSG_ATAPI_DP 0x01

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 PrimarySecondary;
    EFI_UINT8 SlaveMaster;
    EFI_UINT16 Lun;
} EFI_ATAPI_DEVICE_PATH;

#define EFI_MSG_SCSI_DP 0x02

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 Pun;
    EFI_UINT16 Lun;
} EFI_SCSI_DEVICE_PATH;

#define EFI_MSG_FIBRECHANNEL_DP 0x03

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Reserved;
    EFI_UINT64 WWN;
    EFI_UINT64 Lun;
} EFI_FIBRECHANNEL_DEVICE_PATH;

#define EFI_MSG_FIBRECHANNELEX_DP 0x15

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Reserved;
    EFI_UINT8 WWN[8];
    EFI_UINT8 Lun[8];
} EFI_FIBRECHANNELEX_DEVICE_PATH;

#define EFI_MSG_1394_DP 0x04

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Reserved;
    EFI_UINT64 Guid;
} EFI_F1394_DEVICE_PATH;

#define EFI_MSG_USB_DP 0x05

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 ParentPortNumber;
    EFI_UINT8 InterfaceNumber;
} EFI_USB_DEVICE_PATH;

#define EFI_MSG_SATA_DP 0x12

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 HBAPortNumber;
    EFI_UINT16 PortMultiplierPortNumber;
    EFI_UINT16 Lun;
} EFI_SATA_DEVICE_PATH;

#define EFI_MSG_USB_WWID_DP 0x10

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 InterfaceNumber;
    EFI_UINT16 VendorId;
    EFI_UINT16 ProductId;
    EFI_CHAR16 SerialNumber[1];
} EFI_USB_WWID_DEVICE_PATH;

#define EFI_MSG_DEVICE_LOGICAL_UNIT_DP 0x11

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 Lun;
} EFI_DEVICE_LOGICAL_UNIT_DEVICE_PATH;

#define EFI_MSG_USB_CLASS_DP 0x0F

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 VendorId;
    EFI_UINT16 ProductId;
    EFI_UINT8 DeviceClass;
    EFI_UINT8 DeviceSubClass;
    EFI_UINT8 DeviceProtocol;
} EFI_USB_CLASS_DEVICE_PATH;

#define EFI_MSG_I2O_DP 0x06

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Tid;
} EFI_I2O_DEVICE_PATH;

#define EFI_MSG_MAC_ADDR_DP 0x0B

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_MAC_ADDRESS MacAddress;
    EFI_UINT8 IfType;
} EFI_MAC_ADDR_DEVICE_PATH;

#define EFI_MSG_IPv4_DP 0x0C

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_IPv4_ADDRESS LocalIpAddress;
    EFI_IPv4_ADDRESS RemoteIpAddress;
    EFI_UINT16 LocalPort;
    EFI_UINT16 RemotePort;
    EFI_UINT16 Protocol;
    EFI_BOOLEAN StaticIpAddress;
    EFI_IPv4_ADDRESS GatewayIpAddress;
    EFI_IPv4_ADDRESS SubnetMask;
} EFI_IPv4_DEVICE_PATH;

#define EFI_MSG_IPv6_DP 0x0D

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_IPv6_ADDRESS LocalIpAddress;
    EFI_IPv6_ADDRESS RemoteIpAddress;
    EFI_UINT16 LocalPort;
    EFI_UINT16 RemotePort;
    EFI_UINT16 Protocol;
    EFI_UINT8 IpAddressOrigin;
    EFI_UINT8 PrefixLength;
    EFI_IPv6_ADDRESS GatewayIpAddress;
} EFI_IPv6_DEVICE_PATH;

#define EFI_MSG_VLAN_DP 0x14

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 VlanId;
} EFI_VLAN_DEVICE_PATH;

#define EFI_MSG_INFINIBAND_DP 0x09

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 ResourceFlags;
    EFI_UINT8 PortGid[16];
    EFI_UINT64 ServiceId;
    EFI_UINT64 TargetPortId;
    EFI_UINT64 DeviceId;
} EFI_INFINIBAND_DEVICE_PATH;

#define EFI_INFINIBAND_RESOURCE_FLAG_IOC_SERVICE 0x01
#define EFI_INFINIBAND_RESOURCE_FLAG_EXTENDED_BOOT_ENVIRONMENT 0x02
#define EFI_INFINIBAND_RESOURCE_FLAG_CONSOLE_PROTOCOL 0x04
#define EFI_INFINIBAND_RESOURCE_FLAG_STORAGE_PROTOCOL 0x08
#define EFI_INFINIBAND_RESOURCE_FLAG_NETWORK_PROTOCOL 0x10

#define EFI_MSG_UART_DP 0x0E

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Reserved;
    EFI_UINT64 BaudRate;
    EFI_UINT8 DataBits;
    EFI_UINT8 Parity;
    EFI_UINT8 StopBits;
} EFI_UART_DEVICE_PATH;

#define EFI_MSG_VENDOR_DP 0x0A

#define EFI_PC_ANSI_GUID \
    {0xe0c14753, 0xf9be, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_VT_100_GUID \
    {0xdfa66065, 0xb419, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_VT_100_PLUS_GUID \
    {0x7baec70b, 0x57e0, 0x4c76, {0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43}}

#define EFI_VT_UTF8_GUID \
    {0xad15a0d6, 0x8bec, 0x4acf, {0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88}}

#define EFI_DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL \
    {0x37499a9d, 0x542f, 0x4c89, {0xa0, 0x26, 0x35, 0xda, 0x14, 0x20, 0x94, 0xe4}}

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID Guid;
    EFI_UINT32 FlowControlMap;
} EFI_UART_FLOW_CONTROL_DEVICE_PATH;

#define EFI_UART_FLOW_CONTROL_HARDWARE 0x00000001
#define EFI_UART_FLOW_CONTROL_XON_XOFF 0x00000002

#define EFI_SAS_DEVICE_PATH_GUID \
    {0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}}

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID Guid;
    EFI_UINT32 Reserved;
    EFI_UINT64 SasAddress;
    EFI_UINT64 Lun;
    EFI_UINT16 DeviceTopology;
    EFI_UINT16 RelativeTargetPort;
} EFI_SAS_DEVICE_PATH;

#define EFI_MSG_SASEX_DP 0x16

/* Length 24: the offsets and length the specification prints for this node disagree. */
typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 SasAddress[8];
    EFI_UINT8 Lun[8];
    EFI_UINT16 DeviceTopology;
    EFI_UINT16 RelativeTargetPort;
} EFI_SASEX_DEVICE_PATH;

#define EFI_MSG_ISCSI_DP 0x13

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 NetworkProtocol;
    EFI_UINT16 LoginOption;
    EFI_UINT64 Lun;
    EFI_UINT16 TargetPortalGroupTag;
} EFI_ISCSI_DEVICE_PATH;

#define EFI_ISCSI_LOGIN_OPTION_NO_HEADER_DIGEST 0x0000
#define EFI_ISCSI_LOGIN_OPTION_HEADER_DIGEST_USING_CRC32C 0x0002
#define EFI_ISCSI_LOGIN_OPTION_NO_DATA_DIGEST 0x0000
#define EFI_ISCSI_LOGIN_OPTION_DATA_DIGEST_USING_CRC32C 0x0008
#define EFI_ISCSI_LOGIN_OPTION_AUTHMETHOD_CHAP 0x0000
#define EFI_ISCSI_LOGIN_OPTION_AUTHMETHOD_NON 0x0800
#define EFI_ISCSI_LOGIN_OPTION_CHAP_BI 0x0000
#define EFI_ISCSI_LOGIN_OPTION_CHAP_UNI 0x1000

#define EFI_MSG_NVME_NAMESPACE_DP 0x17

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 NamespaceId;
    EFI_UINT64 NamespaceUuid;
} EFI_NVME_NAMESPACE_DEVICE_PATH;

#define EFI_MSG_URI_DP 0x18

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_CHAR8 Uri[1];
} EFI_URI_DEVICE_PATH;

#define EFI_MSG_UFS_DP 0x19

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 Pun;
    EFI_UINT8 Lun;
} EFI_UFS_DEVICE_PATH;

#define EFI_MSG_SD_DP 0x1A

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 SlotNumber;
} EFI_SD_DEVICE_PATH;

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Address[6];
} EFI_BLUETOOTH_ADDRESS;

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 Address[6];
    EFI_UINT8 Type;
} EFI_BLUETOOTH_LE_ADDRESS;

#define EFI_MSG_BLUETOOTH_DP 0x1B

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_BLUETOOTH_ADDRESS BD_ADDR;
} EFI_BLUETOOTH_DEVICE_PATH;

#define EFI_MSG_WIFI_DP 0x1C

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 SSId[32];
} EFI_WIFI_DEVICE_PATH;

#define EFI_MSG_EMMC_DP 0x1D

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 SlotNumber;
} EFI_EMMC_DEVICE_PATH;

#define EFI_MSG_BLUETOOTH_LE_DP 0x1E

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_BLUETOOTH_LE_ADDRESS Address;
} EFI_BLUETOOTH_LE_DEVICE_PATH;

#define EFI_MSG_DNS_DP 0x1F

__extension__ typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 IsIPv6;
    EFI_IP_ADDRESS DnsServerIp[];
} EFI_DNS_DEVICE_PATH;

#define EFI_NVDIMM_NAMESPACE_DP 0x20

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID Uuid;
} EFI_NVDIMM_NAMESPACE_DEVICE_PATH;

#define EFI_MSG_REST_SERVICE_DP 0x21

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 RESTService;
    EFI_UINT8 AccessMode;
} EFI_REST_SERVICE_DEVICE_PATH;

/* Length 22 + n: the specification prints 21 + n but puts the vendor data at offset 22. */
__extension__ typedef struct __attribute__((__packed__)) {
    EFI_REST_SERVICE_DEVICE_PATH RestServiceDevicePath;
    EFI_GUID RestServiceGuid;
    EFI_UINT8 VendorDefinedData[];
} EFI_REST_VENDOR_SERVICE_DEVICE_PATH;

#define EFI_MSG_NVME_OF_NAMESPACE_DP 0x22

/* Length 21 + n: the specification prints 20 + n but puts SubsystemNqn at offset 21. */
__extension__ typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT8 NamespaceIdType;
    EFI_UINT8 NamespaceId[16];
    EFI_CHAR8 SubsystemNqn[];
} EFI_NVME_OF_NAMESPACE_DEVICE_PATH;

#define EFI_MEDIA_HARDDRIVE_DP 0x01

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 PartitionNumber;
    EFI_UINT64 PartitionStart;
    EFI_UINT64 PartitionSize;
    EFI_UINT8 Signature[16];
    EFI_UINT8 MBRType;
    EFI_UINT8 SignatureType;
} EFI_HARDDRIVE_DEVICE_PATH;

#define EFI_MBR_TYPE_PCAT 0x01
#define EFI_MBR_TYPE_EFI_PARTITION_TABLE_HEADER 0x02

#define EFI_NO_DISK_SIGNATURE 0x00
#define EFI_SIGNATURE_TYPE_MBR 0x01
#define EFI_SIGNATURE_TYPE_GUID 0x02

#define EFI_MEDIA_CDROM_DP 0x02

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 BootEntry;
    EFI_UINT64 PartitionStart;
    EFI_UINT64 PartitionSize;
} EFI_CDROM_DEVICE_PATH;

#define EFI_MEDIA_VENDOR_DP 0x03

#define EFI_MEDIA_FILEPATH_DP 0x04

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_CHAR16 PathName[1];
} EFI_FILEPATH_DEVICE_PATH;

#define EFI_SIZE_OF_FILEPATH_DEVICE_PATH offsetof(EFI_FILEPATH_DEVICE_PATH, PathName)

#define EFI_MEDIA_PROTOCOL_DP 0x05

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID Protocol;
} EFI_MEDIA_PROTOCOL_DEVICE_PATH;

#define EFI_MEDIA_PIWG_FW_FILE_DP 0x06

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID FvFileName;
} EFI_MEDIA_FW_VOL_FILEPATH_DEVICE_PATH;

#define EFI_MEDIA_PIWG_FW_VOL_DP 0x07

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_GUID FvName;
} EFI_MEDIA_FW_VOL_DEVICE_PATH;

#define EFI_MEDIA_RELATIVE_OFFSET_RANGE_DP 0x08

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 Reserved;
    EFI_UINT64 StartingOffset;
    EFI_UINT64 EndingOffset;
} EFI_MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH;

#define EFI_MEDIA_RAM_DISK_DP 0x09

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT32 StartingAddr[2];
    EFI_UINT32 EndingAddr[2];
    EFI_GUID TypeGuid;
    EFI_UINT16 Instance;
} EFI_MEDIA_RAM_DISK_DEVICE_PATH;

#define EFI_VIRTUAL_DISK_GUID \
    {0x77AB535A, 0x45FC, 0x624B, {0x55, 0x60, 0xF7, 0xB2, 0x81, 0xD1, 0xF9, 0x6E}}

#define EFI_VIRTUAL_CD_GUID \
    {0x3D5ABD30, 0x4175, 0x87CE, {0x6D, 0x64, 0xD2, 0xAD, 0xE5, 0x23, 0xC4, 0xBB}}

#define EFI_PERSISTENT_VIRTUAL_DISK_GUID \
    {0x5CEA02C9, 0x4D07, 0x69D3, {0x26, 0x9F, 0x44, 0x96, 0xFB, 0xE0, 0x96, 0xF9}}

#define EFI_PERSISTENT_VIRTUAL_CD_GUID \
    {0x08018188, 0x42CD, 0xBB48, {0x10, 0x0F, 0x53, 0x87, 0xD5, 0x3D, 0xED, 0x3D}}

#define EFI_BBS_BBS_DP 0x01

typedef struct __attribute__((__packed__)) {
    EFI_DEVICE_PATH_PROTOCOL Header;
    EFI_UINT16 DeviceType;
    EFI_UINT16 StatusFlag;
    EFI_CHAR8 String[1];
} EFI_BBS_BBS_DEVICE_PATH;

#define EFI_BBS_TYPE_FLOPPY 0x01
#define EFI_BBS_TYPE_HARDDRIVE 0x02
#define EFI_BBS_TYPE_CDROM 0x03
#define EFI_BBS_TYPE_PCMCIA 0x04
#define EFI_BBS_TYPE_USB 0x05
#define EFI_BBS_TYPE_EMBEDDED_NETWORK 0x06
#define EFI_BBS_TYPE_BEV 0x80
#define EFI_BBS_TYPE_UNKNOWN 0xFF

typedef union {
    EFI_DEVICE_PATH_PROTOCOL DevPath;
    EFI_PCI_DEVICE_PATH Pci;
    EFI_PCCARD_DEVICE_PATH PcCard;
    EFI_MEMMAP_DEVICE_PATH MemMap;
    EFI_VENDOR_DEVICE_PATH Vendor;
    EFI_CONTROLLER_DEVICE_PATH Controller;
    EFI_BMC_DEVICE_PATH Bmc;
    EFI_ACPI_HID_DEVICE_PATH Acpi;
    EFI_ACPI_EXTENDED_HID_DEVICE_PATH ExtendedAcpi;
    EFI_ACPI_ADR_DEVICE_PATH AcpiAdr;
    EFI_ATAPI_DEVICE_PATH Atapi;
    EFI_SCSI_DEVICE_PATH Scsi;
    EFI_ISCSI_DEVICE_PATH Iscsi;
    EFI_FIBRECHANNEL_DEVICE_PATH FibreChannel;
    EFI_FIBRECHANNELEX_DEVICE_PATH FibreChannelEx;
    EFI_F1394_DEVICE_PATH F1394;
    EFI_USB_DEVICE_PATH Usb;
    EFI_SATA_DEVICE_PATH Sata;
    EFI_USB_CLASS_DEVICE_PATH UsbClass;
    EFI_USB_WWID_DEVICE_PATH UsbWwid;
    EFI_DEVICE_LOGICAL_UNIT_DEVICE_PATH LogicUnit;
    EFI_I2O_DEVICE_PATH I2O;
    EFI_MAC_ADDR_DEVICE_PATH MacAddr;
    EFI_IPv4_DEVICE_PATH Ipv4;
    EFI_IPv6_DEVICE_PATH Ipv6;
    EFI_VLAN_DEVICE_PATH Vlan;
    EFI_INFINIBAND_DEVICE_PATH InfiniBand;
    EFI_UART_DEVICE_PATH Uart;
    EFI_UART_FLOW_CONTROL_DEVICE_PATH UartFlowControl;
    EFI_SAS_DEVICE_PATH Sas;
    EFI_SASEX_DEVICE_PATH SasEx;
    EFI_NVME_NAMESPACE_DEVICE_PATH NvmeNamespace;
    EFI_NVME_OF_NAMESPACE_DEVICE_PATH NvmeOfNamespace;
    EFI_DNS_DEVICE_PATH Dns;
    EFI_URI_DEVICE_PATH Uri;
    EFI_BLUETOOTH_DEVICE_PATH Bluetooth;
    EFI_WIFI_DEVICE_PATH WiFi;
    EFI_UFS_DEVICE_PATH Ufs;
    EFI_SD_DEVICE_PATH Sd;
    EFI_EMMC_DEVICE_PATH Emmc;
    EFI_HARDDRIVE_DEVICE_PATH HardDrive;
    EFI_CDROM_DEVICE_PATH CD;
    EFI_FILEPATH_DEVICE_PATH FilePath;
    EFI_MEDIA_PROTOCOL_DEVICE_PATH MediaProtocol;
    EFI_MEDIA_FW_VOL_DEVICE_PATH FirmwareVolume;
    EFI_MEDIA_FW_VOL_FILEPATH_DEVICE_PATH FirmwareFile;
    EFI_MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH Offset;
    EFI_MEDIA_RAM_DISK_DEVICE_PATH RamDisk;
    EFI_BBS_BBS_DEVICE_PATH Bbs;
} EFI_DEV_PATH;

typedef union {
    EFI_DEVICE_PATH_PROTOCOL *DevPath;
    EFI_PCI_DEVICE_PATH *Pci;
    EFI_PCCARD_DEVICE_PATH *PcCard;
    EFI_MEMMAP_DEVICE_PATH *MemMap;
    EFI_VENDOR_DEVICE_PATH *Vendor;
    EFI_CONTROLLER_DEVICE_PATH *Controller;
    EFI_BMC_DEVICE_PATH *Bmc;
    EFI_ACPI_HID_DEVICE_PATH *Acpi;
    EFI_ACPI_EXTENDED_HID_DEVICE_PATH *ExtendedAcpi;
    EFI_ACPI_ADR_DEVICE_PATH *AcpiAdr;
    EFI_ATAPI_DEVICE_PATH *Atapi;
    EFI_SCSI_DEVICE_PATH *Scsi;
    EFI_ISCSI_DEVICE_PATH *Iscsi;
    EFI_FIBRECHANNEL_DEVICE_PATH *FibreChannel;
    EFI_FIBRECHANNELEX_DEVICE_PATH *FibreChannelEx;
    EFI_F1394_DEVICE_PATH *F1394;
    EFI_USB_DEVICE_PATH *Usb;
    EFI_SATA_DEVICE_PATH *Sata;
    EFI_USB_CLASS_DEVICE_PATH *UsbClass;
    EFI_USB_WWID_DEVICE_PATH *UsbWwid;
    EFI_DEVICE_LOGICAL_UNIT_DEVICE_PATH *LogicUnit;
    EFI_I2O_DEVICE_PATH *I2O;
    EFI_MAC_ADDR_DEVICE_PATH *MacAddr;
    EFI_IPv4_DEVICE_PATH *Ipv4;
    EFI_IPv6_DEVICE_PATH *Ipv6;
    EFI_VLAN_DEVICE_PATH *Vlan;
    EFI_INFINIBAND_DEVICE_PATH *InfiniBand;
    EFI_UART_DEVICE_PATH *Uart;
    EFI_UART_FLOW_CONTROL_DEVICE_PATH *UartFlowControl;
    EFI_SAS_DEVICE_PATH *Sas;
    EFI_SASEX_DEVICE_PATH *SasEx;
    EFI_NVME_NAMESPACE_DEVICE_PATH *NvmeNamespace;
    EFI_NVME_OF_NAMESPACE_DEVICE_PATH *NvmeOfNamespace;
    EFI_DNS_DEVICE_PATH *Dns;
    EFI_URI_DEVICE_PATH *Uri;
    EFI_BLUETOOTH_DEVICE_PATH *Bluetooth;
    EFI_WIFI_DEVICE_PATH *WiFi;
    EFI_UFS_DEVICE_PATH *Ufs;
    EFI_SD_DEVICE_PATH *Sd;
    EFI_EMMC_DEVICE_PATH *Emmc;
    EFI_HARDDRIVE_DEVICE_PATH *HardDrive;
    EFI_CDROM_DEVICE_PATH *CD;
    EFI_FILEPATH_DEVICE_PATH *FilePath;
    EFI_MEDIA_PROTOCOL_DEVICE_PATH *MediaProtocol;
    EFI_MEDIA_FW_VOL_DEVICE_PATH *FirmwareVolume;
    EFI_MEDIA_FW_VOL_FILEPATH_DEVICE_PATH *FirmwareFile;
    EFI_MEDIA_RELATIVE_OFFSET_RANGE_DEVICE_PATH *Offset;
    EFI_MEDIA_RAM_DISK_DEVICE_PATH *RamDisk;
    EFI_BBS_BBS_DEVICE_PATH *Bbs;
    EFI_UINT8 *Raw;
} EFI_DEV_PATH_PTR;

#define EfiDevicePathType(a) (((EFI_CONST EFI_DEVICE_PATH_PROTOCOL *)(a))->Type)
#define EfiDevicePathSubType(a) (((EFI_CONST EFI_DEVICE_PATH_PROTOCOL *)(a))->SubType)
#define EfiDevicePathNodeLength(a) \
    ((EFI_UINT16)(((EFI_CONST EFI_DEVICE_PATH_PROTOCOL *)(a))->Length[0] | \
        (((EFI_CONST EFI_DEVICE_PATH_PROTOCOL *)(a))->Length[1] << 8)))
#define EfiNextDevicePathNode(a) \
    ((EFI_DEVICE_PATH_PROTOCOL *)((EFI_UINT8 *)(a) + EfiDevicePathNodeLength(a)))

#define EfiIsDevicePathEndType(a) (EfiDevicePathType(a) == EFI_END_DEVICE_PATH_TYPE)
#define EfiIsDevicePathEndSubType(a) (EfiDevicePathSubType(a) == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define EfiIsDevicePathEnd(a) (EfiIsDevicePathEndType(a) && EfiIsDevicePathEndSubType(a))

#define EFI_DP_IS_END_TYPE(a) EfiIsDevicePathEndType(a)
#define EFI_DP_IS_END_SUBTYPE(a) EfiIsDevicePathEndSubType(a)

#define EfiSetDevicePathNodeLength(a, l) \
    do { \
        ((EFI_DEVICE_PATH_PROTOCOL *)(a))->Length[0] = (EFI_UINT8)(l); \
        ((EFI_DEVICE_PATH_PROTOCOL *)(a))->Length[1] = (EFI_UINT8)((l) >> 8); \
    } while (0)

#define EfiSetDevicePathEndNode(a) \
    do { \
        ((EFI_DEVICE_PATH_PROTOCOL *)(a))->Type = EFI_END_DEVICE_PATH_TYPE; \
        ((EFI_DEVICE_PATH_PROTOCOL *)(a))->SubType = EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE; \
        EfiSetDevicePathNodeLength(a, EFI_END_DEVICE_PATH_LENGTH); \
    } while (0)

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
    {0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}}

typedef EFI_UINTN (EFI_API *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_PATH)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *Src1,
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *Src2
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_NODE)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DeviceNode
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePathInstance
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)(
    EFI_IN EFI_OUT EFI_DEVICE_PATH_PROTOCOL **DevicePathInstance,
    EFI_OUT EFI_UINTN *DevicePathInstanceSize EFI_OPTIONAL
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_UTILS_CREATE_NODE)(
    EFI_IN EFI_UINT8 NodeType,
    EFI_IN EFI_UINT8 NodeSubType,
    EFI_IN EFI_UINT16 NodeLength
);

typedef EFI_BOOLEAN (EFI_API *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
    EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE GetDevicePathSize;
    EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH DuplicateDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_PATH AppendDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_NODE AppendDeviceNode;
    EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE AppendDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE GetNextDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE IsDevicePathMultiInstance;
    EFI_DEVICE_PATH_UTILS_CREATE_NODE CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
    {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}}

typedef EFI_CHAR16 *(EFI_API *EFI_DEVICE_PATH_TO_TEXT_NODE)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DeviceNode,
    EFI_IN EFI_BOOLEAN DisplayOnly,
    EFI_IN EFI_BOOLEAN AllowShortcuts
);

typedef EFI_CHAR16 *(EFI_API *EFI_DEVICE_PATH_TO_TEXT_PATH)(
    EFI_IN EFI_CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    EFI_IN EFI_BOOLEAN DisplayOnly,
    EFI_IN EFI_BOOLEAN AllowShortcuts
);

typedef struct _EFI_DEVICE_PATH_TO_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
} EFI_DEVICE_PATH_TO_TEXT_PROTOCOL;

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
    {0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}}

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_FROM_TEXT_NODE)(
    EFI_IN EFI_CONST EFI_CHAR16 *TextDeviceNode
);

typedef EFI_DEVICE_PATH_PROTOCOL *(EFI_API *EFI_DEVICE_PATH_FROM_TEXT_PATH)(
    EFI_IN EFI_CONST EFI_CHAR16 *TextDevicePath
);

/* The specification's structure body misspells both member names ("Devic"). */
typedef struct _EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL {
    EFI_DEVICE_PATH_FROM_TEXT_NODE ConvertTextToDeviceNode;
    EFI_DEVICE_PATH_FROM_TEXT_PATH ConvertTextToDevicePath;
} EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL;

#ifdef __cplusplus
}
#endif

#endif
