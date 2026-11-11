#ifndef EFI_EFIDEVP_H_
#define EFI_EFIDEVP_H_

#include <stddef.h>

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
    {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct efi_device_path_protocol {
    uint8_t Type;
    uint8_t SubType;
    uint8_t Length[2];
};

#define EFI_HARDWARE_DEVICE_PATH 0x01
#define EFI_ACPI_DEVICE_PATH 0x02
#define EFI_MESSAGING_DEVICE_PATH 0x03
#define EFI_MEDIA_DEVICE_PATH 0x04
#define EFI_BBS_DEVICE_PATH 0x05
#define EFI_END_DEVICE_PATH_TYPE 0x7F

#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE 0xFF
#define EFI_END_INSTANCE_DEVICE_PATH_SUBTYPE 0x01
#define EFI_END_DEVICE_PATH_LENGTH (sizeof(struct efi_device_path_protocol))

#define EFI_HW_PCI_DP 0x01

struct efi_pci_device_path {
    struct efi_device_path_protocol Header;
    uint8_t Function;
    uint8_t Device;
} __attribute__((__packed__));

#define EFI_HW_PCCARD_DP 0x02

struct efi_pccard_device_path {
    struct efi_device_path_protocol Header;
    uint8_t FunctionNumber;
} __attribute__((__packed__));

#define EFI_HW_MEMMAP_DP 0x03

struct efi_memmap_device_path {
    struct efi_device_path_protocol Header;
    uint32_t MemoryType;
    EFI_PHYSICAL_ADDRESS StartingAddress;
    EFI_PHYSICAL_ADDRESS EndingAddress;
} __attribute__((__packed__));

#define EFI_HW_VENDOR_DP 0x04

struct efi_vendor_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid Guid;
} __attribute__((__packed__));

#define EFI_HW_CONTROLLER_DP 0x05

struct efi_controller_device_path {
    struct efi_device_path_protocol Header;
    uint32_t ControllerNumber;
} __attribute__((__packed__));

#define EFI_HW_BMC_DP 0x06

struct efi_bmc_device_path {
    struct efi_device_path_protocol Header;
    uint8_t InterfaceType;
    uint8_t BaseAddress[8];
} __attribute__((__packed__));

/* The shift is done in uint32_t so that product numbers from 0x8000 up do not overflow. */
#define EFI_PNP_ID(ID) ((uint32_t)(((uint32_t)(ID) << 16) | 0x41D0))
#define EFI_EISA_PNP_ID(ID) EFI_PNP_ID(ID)

#define EFI_PNP_EISA_ID_CONST 0x41d0
#define EFI_EISA_ID(_Name, _Num) ((uint32_t)(_Name) | ((uint32_t)(_Num) << 16))
#define EFI_PNP_EISA_ID_MASK 0xffff
#define EFI_EISA_ID_TO_NUM(_Id) ((uint32_t)(_Id) >> 16)

#define EFI_ACPI_DP 0x01

struct efi_acpi_hid_device_path {
    struct efi_device_path_protocol Header;
    uint32_t HID;
    uint32_t UID;
} __attribute__((__packed__));

#define EFI_ACPI_EXTENDED_DP 0x02

/* HidStr starts _HIDSTR; _UIDSTR and _CIDSTR follow it. */
struct efi_acpi_extended_hid_device_path {
    struct efi_device_path_protocol Header;
    uint32_t HID;
    uint32_t UID;
    uint32_t CID;
    char HidStr[1];
} __attribute__((__packed__));

#define EFI_ACPI_ADR_DP 0x03

struct efi_acpi_adr_device_path {
    struct efi_device_path_protocol Header;
    uint32_t ADR;
} __attribute__((__packed__));

#define EFI_ACPI_NVDIMM_DP 0x04

struct efi_acpi_nvdimm_device_path {
    struct efi_device_path_protocol Header;
    uint32_t NFITDeviceHandle;
} __attribute__((__packed__));

#define EFI_MSG_ATAPI_DP 0x01

struct efi_atapi_device_path {
    struct efi_device_path_protocol Header;
    uint8_t PrimarySecondary;
    uint8_t SlaveMaster;
    uint16_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_SCSI_DP 0x02

struct efi_scsi_device_path {
    struct efi_device_path_protocol Header;
    uint16_t Pun;
    uint16_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_FIBRECHANNEL_DP 0x03

struct efi_fibrechannel_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Reserved;
    uint64_t WWN;
    uint64_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_FIBRECHANNELEX_DP 0x15

struct efi_fibrechannelex_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Reserved;
    uint8_t WWN[8];
    uint8_t Lun[8];
} __attribute__((__packed__));

#define EFI_MSG_1394_DP 0x04

struct efi_f1394_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Reserved;
    uint64_t Guid;
} __attribute__((__packed__));

#define EFI_MSG_USB_DP 0x05

struct efi_usb_device_path {
    struct efi_device_path_protocol Header;
    uint8_t ParentPortNumber;
    uint8_t InterfaceNumber;
} __attribute__((__packed__));

#define EFI_MSG_SATA_DP 0x12

struct efi_sata_device_path {
    struct efi_device_path_protocol Header;
    uint16_t HBAPortNumber;
    uint16_t PortMultiplierPortNumber;
    uint16_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_USB_WWID_DP 0x10

struct efi_usb_wwid_device_path {
    struct efi_device_path_protocol Header;
    uint16_t InterfaceNumber;
    uint16_t VendorId;
    uint16_t ProductId;
    uint16_t SerialNumber[1];
} __attribute__((__packed__));

#define EFI_MSG_DEVICE_LOGICAL_UNIT_DP 0x11

struct efi_device_logical_unit_device_path {
    struct efi_device_path_protocol Header;
    uint8_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_USB_CLASS_DP 0x0F

struct efi_usb_class_device_path {
    struct efi_device_path_protocol Header;
    uint16_t VendorId;
    uint16_t ProductId;
    uint8_t DeviceClass;
    uint8_t DeviceSubClass;
    uint8_t DeviceProtocol;
} __attribute__((__packed__));

#define EFI_MSG_I2O_DP 0x06

struct efi_i2o_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Tid;
} __attribute__((__packed__));

#define EFI_MSG_MAC_ADDR_DP 0x0B

struct efi_mac_addr_device_path {
    struct efi_device_path_protocol Header;
    struct efi_mac_address MacAddress;
    uint8_t IfType;
} __attribute__((__packed__));

#define EFI_MSG_IPv4_DP 0x0C

struct efi_ipv4_device_path {
    struct efi_device_path_protocol Header;
    struct efi_ipv4_address LocalIpAddress;
    struct efi_ipv4_address RemoteIpAddress;
    uint16_t LocalPort;
    uint16_t RemotePort;
    uint16_t Protocol;
    uint8_t StaticIpAddress;
    struct efi_ipv4_address GatewayIpAddress;
    struct efi_ipv4_address SubnetMask;
} __attribute__((__packed__));

#define EFI_MSG_IPv6_DP 0x0D

struct efi_ipv6_device_path {
    struct efi_device_path_protocol Header;
    struct efi_ipv6_address LocalIpAddress;
    struct efi_ipv6_address RemoteIpAddress;
    uint16_t LocalPort;
    uint16_t RemotePort;
    uint16_t Protocol;
    uint8_t IpAddressOrigin;
    uint8_t PrefixLength;
    struct efi_ipv6_address GatewayIpAddress;
} __attribute__((__packed__));

#define EFI_MSG_VLAN_DP 0x14

struct efi_vlan_device_path {
    struct efi_device_path_protocol Header;
    uint16_t VlanId;
} __attribute__((__packed__));

#define EFI_MSG_INFINIBAND_DP 0x09

struct efi_infiniband_device_path {
    struct efi_device_path_protocol Header;
    uint32_t ResourceFlags;
    uint8_t PortGid[16];
    uint64_t ServiceId;
    uint64_t TargetPortId;
    uint64_t DeviceId;
} __attribute__((__packed__));

#define EFI_INFINIBAND_RESOURCE_FLAG_IOC_SERVICE 0x01
#define EFI_INFINIBAND_RESOURCE_FLAG_EXTENDED_BOOT_ENVIRONMENT 0x02
#define EFI_INFINIBAND_RESOURCE_FLAG_CONSOLE_PROTOCOL 0x04
#define EFI_INFINIBAND_RESOURCE_FLAG_STORAGE_PROTOCOL 0x08
#define EFI_INFINIBAND_RESOURCE_FLAG_NETWORK_PROTOCOL 0x10

#define EFI_MSG_UART_DP 0x0E

struct efi_uart_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Reserved;
    uint64_t BaudRate;
    uint8_t DataBits;
    uint8_t Parity;
    uint8_t StopBits;
} __attribute__((__packed__));

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

struct efi_uart_flow_control_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid Guid;
    uint32_t FlowControlMap;
} __attribute__((__packed__));

#define EFI_UART_FLOW_CONTROL_HARDWARE 0x00000001
#define EFI_UART_FLOW_CONTROL_XON_XOFF 0x00000002

#define EFI_SAS_DEVICE_PATH_GUID \
    {0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}}

struct efi_sas_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid Guid;
    uint32_t Reserved;
    uint64_t SasAddress;
    uint64_t Lun;
    uint16_t DeviceTopology;
    uint16_t RelativeTargetPort;
} __attribute__((__packed__));

#define EFI_MSG_SASEX_DP 0x16

/* Length 24: the offsets and length the specification prints for this node disagree. */
struct efi_sasex_device_path {
    struct efi_device_path_protocol Header;
    uint8_t SasAddress[8];
    uint8_t Lun[8];
    uint16_t DeviceTopology;
    uint16_t RelativeTargetPort;
} __attribute__((__packed__));

#define EFI_MSG_ISCSI_DP 0x13

struct efi_iscsi_device_path {
    struct efi_device_path_protocol Header;
    uint16_t NetworkProtocol;
    uint16_t LoginOption;
    uint64_t Lun;
    uint16_t TargetPortalGroupTag;
} __attribute__((__packed__));

#define EFI_ISCSI_LOGIN_OPTION_NO_HEADER_DIGEST 0x0000
#define EFI_ISCSI_LOGIN_OPTION_HEADER_DIGEST_USING_CRC32C 0x0002
#define EFI_ISCSI_LOGIN_OPTION_NO_DATA_DIGEST 0x0000
#define EFI_ISCSI_LOGIN_OPTION_DATA_DIGEST_USING_CRC32C 0x0008
#define EFI_ISCSI_LOGIN_OPTION_AUTHMETHOD_CHAP 0x0000
#define EFI_ISCSI_LOGIN_OPTION_AUTHMETHOD_NON 0x0800
#define EFI_ISCSI_LOGIN_OPTION_CHAP_BI 0x0000
#define EFI_ISCSI_LOGIN_OPTION_CHAP_UNI 0x1000

#define EFI_MSG_NVME_NAMESPACE_DP 0x17

struct efi_nvme_namespace_device_path {
    struct efi_device_path_protocol Header;
    uint32_t NamespaceId;
    uint64_t NamespaceUuid;
} __attribute__((__packed__));

#define EFI_MSG_URI_DP 0x18

struct efi_uri_device_path {
    struct efi_device_path_protocol Header;
    char Uri[1];
} __attribute__((__packed__));

#define EFI_MSG_UFS_DP 0x19

struct efi_ufs_device_path {
    struct efi_device_path_protocol Header;
    uint8_t Pun;
    uint8_t Lun;
} __attribute__((__packed__));

#define EFI_MSG_SD_DP 0x1A

struct efi_sd_device_path {
    struct efi_device_path_protocol Header;
    uint8_t SlotNumber;
} __attribute__((__packed__));

struct efi_bluetooth_address {
    uint8_t Address[6];
} __attribute__((__packed__));

struct efi_bluetooth_le_address {
    uint8_t Address[6];
    uint8_t Type;
} __attribute__((__packed__));

#define EFI_MSG_BLUETOOTH_DP 0x1B

struct efi_bluetooth_device_path {
    struct efi_device_path_protocol Header;
    struct efi_bluetooth_address BD_ADDR;
} __attribute__((__packed__));

#define EFI_MSG_WIFI_DP 0x1C

struct efi_wifi_device_path {
    struct efi_device_path_protocol Header;
    uint8_t SSId[32];
} __attribute__((__packed__));

#define EFI_MSG_EMMC_DP 0x1D

struct efi_emmc_device_path {
    struct efi_device_path_protocol Header;
    uint8_t SlotNumber;
} __attribute__((__packed__));

#define EFI_MSG_BLUETOOTH_LE_DP 0x1E

struct efi_bluetooth_le_device_path {
    struct efi_device_path_protocol Header;
    struct efi_bluetooth_le_address Address;
} __attribute__((__packed__));

#define EFI_MSG_DNS_DP 0x1F

__extension__ struct efi_dns_device_path {
    struct efi_device_path_protocol Header;
    uint8_t IsIPv6;
    union efi_ip_address DnsServerIp[];
} __attribute__((__packed__));

#define EFI_NVDIMM_NAMESPACE_DP 0x20

struct efi_nvdimm_namespace_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid Uuid;
} __attribute__((__packed__));

#define EFI_MSG_REST_SERVICE_DP 0x21

struct efi_rest_service_device_path {
    struct efi_device_path_protocol Header;
    uint8_t RESTService;
    uint8_t AccessMode;
} __attribute__((__packed__));

/* Length 22 + n: the specification prints 21 + n but puts the vendor data at offset 22. */
__extension__ struct efi_rest_vendor_service_device_path {
    struct efi_rest_service_device_path RestServiceDevicePath;
    struct efi_guid RestServiceGuid;
    uint8_t VendorDefinedData[];
} __attribute__((__packed__));

#define EFI_MSG_NVME_OF_NAMESPACE_DP 0x22

/* Length 21 + n: the specification prints 20 + n but puts SubsystemNqn at offset 21. */
__extension__ struct efi_nvme_of_namespace_device_path {
    struct efi_device_path_protocol Header;
    uint8_t NamespaceIdType;
    uint8_t NamespaceId[16];
    char SubsystemNqn[];
} __attribute__((__packed__));

#define EFI_MEDIA_HARDDRIVE_DP 0x01

struct efi_harddrive_device_path {
    struct efi_device_path_protocol Header;
    uint32_t PartitionNumber;
    uint64_t PartitionStart;
    uint64_t PartitionSize;
    uint8_t Signature[16];
    uint8_t MBRType;
    uint8_t SignatureType;
} __attribute__((__packed__));

#define EFI_MBR_TYPE_PCAT 0x01
#define EFI_MBR_TYPE_EFI_PARTITION_TABLE_HEADER 0x02

#define EFI_NO_DISK_SIGNATURE 0x00
#define EFI_SIGNATURE_TYPE_MBR 0x01
#define EFI_SIGNATURE_TYPE_GUID 0x02

#define EFI_MEDIA_CDROM_DP 0x02

struct efi_cdrom_device_path {
    struct efi_device_path_protocol Header;
    uint32_t BootEntry;
    uint64_t PartitionStart;
    uint64_t PartitionSize;
} __attribute__((__packed__));

#define EFI_MEDIA_VENDOR_DP 0x03

#define EFI_MEDIA_FILEPATH_DP 0x04

struct efi_filepath_device_path {
    struct efi_device_path_protocol Header;
    uint16_t PathName[1];
} __attribute__((__packed__));

#define EFI_SIZE_OF_FILEPATH_DEVICE_PATH offsetof(struct efi_filepath_device_path, PathName)

#define EFI_MEDIA_PROTOCOL_DP 0x05

struct efi_media_protocol_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid Protocol;
} __attribute__((__packed__));

#define EFI_MEDIA_PIWG_FW_FILE_DP 0x06

struct efi_media_fw_vol_filepath_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid FvFileName;
} __attribute__((__packed__));

#define EFI_MEDIA_PIWG_FW_VOL_DP 0x07

struct efi_media_fw_vol_device_path {
    struct efi_device_path_protocol Header;
    struct efi_guid FvName;
} __attribute__((__packed__));

#define EFI_MEDIA_RELATIVE_OFFSET_RANGE_DP 0x08

struct efi_media_relative_offset_range_device_path {
    struct efi_device_path_protocol Header;
    uint32_t Reserved;
    uint64_t StartingOffset;
    uint64_t EndingOffset;
} __attribute__((__packed__));

#define EFI_MEDIA_RAM_DISK_DP 0x09

struct efi_media_ram_disk_device_path {
    struct efi_device_path_protocol Header;
    uint32_t StartingAddr[2];
    uint32_t EndingAddr[2];
    struct efi_guid TypeGuid;
    uint16_t Instance;
} __attribute__((__packed__));

#define EFI_VIRTUAL_DISK_GUID \
    {0x77AB535A, 0x45FC, 0x624B, {0x55, 0x60, 0xF7, 0xB2, 0x81, 0xD1, 0xF9, 0x6E}}

#define EFI_VIRTUAL_CD_GUID \
    {0x3D5ABD30, 0x4175, 0x87CE, {0x6D, 0x64, 0xD2, 0xAD, 0xE5, 0x23, 0xC4, 0xBB}}

#define EFI_PERSISTENT_VIRTUAL_DISK_GUID \
    {0x5CEA02C9, 0x4D07, 0x69D3, {0x26, 0x9F, 0x44, 0x96, 0xFB, 0xE0, 0x96, 0xF9}}

#define EFI_PERSISTENT_VIRTUAL_CD_GUID \
    {0x08018188, 0x42CD, 0xBB48, {0x10, 0x0F, 0x53, 0x87, 0xD5, 0x3D, 0xED, 0x3D}}

#define EFI_BBS_BBS_DP 0x01

struct efi_bbs_bbs_device_path {
    struct efi_device_path_protocol Header;
    uint16_t DeviceType;
    uint16_t StatusFlag;
    char String[1];
} __attribute__((__packed__));

#define EFI_BBS_TYPE_FLOPPY 0x01
#define EFI_BBS_TYPE_HARDDRIVE 0x02
#define EFI_BBS_TYPE_CDROM 0x03
#define EFI_BBS_TYPE_PCMCIA 0x04
#define EFI_BBS_TYPE_USB 0x05
#define EFI_BBS_TYPE_EMBEDDED_NETWORK 0x06
#define EFI_BBS_TYPE_BEV 0x80
#define EFI_BBS_TYPE_UNKNOWN 0xFF

union efi_dev_path {
    struct efi_device_path_protocol DevPath;
    struct efi_pci_device_path Pci;
    struct efi_pccard_device_path PcCard;
    struct efi_memmap_device_path MemMap;
    struct efi_vendor_device_path Vendor;
    struct efi_controller_device_path Controller;
    struct efi_bmc_device_path Bmc;
    struct efi_acpi_hid_device_path Acpi;
    struct efi_acpi_extended_hid_device_path ExtendedAcpi;
    struct efi_acpi_adr_device_path AcpiAdr;
    struct efi_atapi_device_path Atapi;
    struct efi_scsi_device_path Scsi;
    struct efi_iscsi_device_path Iscsi;
    struct efi_fibrechannel_device_path FibreChannel;
    struct efi_fibrechannelex_device_path FibreChannelEx;
    struct efi_f1394_device_path F1394;
    struct efi_usb_device_path Usb;
    struct efi_sata_device_path Sata;
    struct efi_usb_class_device_path UsbClass;
    struct efi_usb_wwid_device_path UsbWwid;
    struct efi_device_logical_unit_device_path LogicUnit;
    struct efi_i2o_device_path I2O;
    struct efi_mac_addr_device_path MacAddr;
    struct efi_ipv4_device_path Ipv4;
    struct efi_ipv6_device_path Ipv6;
    struct efi_vlan_device_path Vlan;
    struct efi_infiniband_device_path InfiniBand;
    struct efi_uart_device_path Uart;
    struct efi_uart_flow_control_device_path UartFlowControl;
    struct efi_sas_device_path Sas;
    struct efi_sasex_device_path SasEx;
    struct efi_nvme_namespace_device_path NvmeNamespace;
    struct efi_nvme_of_namespace_device_path NvmeOfNamespace;
    struct efi_dns_device_path Dns;
    struct efi_uri_device_path Uri;
    struct efi_bluetooth_device_path Bluetooth;
    struct efi_wifi_device_path WiFi;
    struct efi_ufs_device_path Ufs;
    struct efi_sd_device_path Sd;
    struct efi_emmc_device_path Emmc;
    struct efi_harddrive_device_path HardDrive;
    struct efi_cdrom_device_path CD;
    struct efi_filepath_device_path FilePath;
    struct efi_media_protocol_device_path MediaProtocol;
    struct efi_media_fw_vol_device_path FirmwareVolume;
    struct efi_media_fw_vol_filepath_device_path FirmwareFile;
    struct efi_media_relative_offset_range_device_path Offset;
    struct efi_media_ram_disk_device_path RamDisk;
    struct efi_bbs_bbs_device_path Bbs;
};

union efi_dev_path_ptr {
    struct efi_device_path_protocol *DevPath;
    struct efi_pci_device_path *Pci;
    struct efi_pccard_device_path *PcCard;
    struct efi_memmap_device_path *MemMap;
    struct efi_vendor_device_path *Vendor;
    struct efi_controller_device_path *Controller;
    struct efi_bmc_device_path *Bmc;
    struct efi_acpi_hid_device_path *Acpi;
    struct efi_acpi_extended_hid_device_path *ExtendedAcpi;
    struct efi_acpi_adr_device_path *AcpiAdr;
    struct efi_atapi_device_path *Atapi;
    struct efi_scsi_device_path *Scsi;
    struct efi_iscsi_device_path *Iscsi;
    struct efi_fibrechannel_device_path *FibreChannel;
    struct efi_fibrechannelex_device_path *FibreChannelEx;
    struct efi_f1394_device_path *F1394;
    struct efi_usb_device_path *Usb;
    struct efi_sata_device_path *Sata;
    struct efi_usb_class_device_path *UsbClass;
    struct efi_usb_wwid_device_path *UsbWwid;
    struct efi_device_logical_unit_device_path *LogicUnit;
    struct efi_i2o_device_path *I2O;
    struct efi_mac_addr_device_path *MacAddr;
    struct efi_ipv4_device_path *Ipv4;
    struct efi_ipv6_device_path *Ipv6;
    struct efi_vlan_device_path *Vlan;
    struct efi_infiniband_device_path *InfiniBand;
    struct efi_uart_device_path *Uart;
    struct efi_uart_flow_control_device_path *UartFlowControl;
    struct efi_sas_device_path *Sas;
    struct efi_sasex_device_path *SasEx;
    struct efi_nvme_namespace_device_path *NvmeNamespace;
    struct efi_nvme_of_namespace_device_path *NvmeOfNamespace;
    struct efi_dns_device_path *Dns;
    struct efi_uri_device_path *Uri;
    struct efi_bluetooth_device_path *Bluetooth;
    struct efi_wifi_device_path *WiFi;
    struct efi_ufs_device_path *Ufs;
    struct efi_sd_device_path *Sd;
    struct efi_emmc_device_path *Emmc;
    struct efi_harddrive_device_path *HardDrive;
    struct efi_cdrom_device_path *CD;
    struct efi_filepath_device_path *FilePath;
    struct efi_media_protocol_device_path *MediaProtocol;
    struct efi_media_fw_vol_device_path *FirmwareVolume;
    struct efi_media_fw_vol_filepath_device_path *FirmwareFile;
    struct efi_media_relative_offset_range_device_path *Offset;
    struct efi_media_ram_disk_device_path *RamDisk;
    struct efi_bbs_bbs_device_path *Bbs;
    uint8_t *Raw;
};

#define EfiDevicePathType(a) (((const struct efi_device_path_protocol *)(a))->Type)
#define EfiDevicePathSubType(a) (((const struct efi_device_path_protocol *)(a))->SubType)
#define EfiDevicePathNodeLength(a) \
    ((uint16_t)(((const struct efi_device_path_protocol *)(a))->Length[0] | \
        (((const struct efi_device_path_protocol *)(a))->Length[1] << 8)))
#define EfiNextDevicePathNode(a) \
    ((struct efi_device_path_protocol *)((uint8_t *)(a) + EfiDevicePathNodeLength(a)))

#define EfiIsDevicePathEndType(a) (EfiDevicePathType(a) == EFI_END_DEVICE_PATH_TYPE)
#define EfiIsDevicePathEndSubType(a) (EfiDevicePathSubType(a) == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define EfiIsDevicePathEnd(a) (EfiIsDevicePathEndType(a) && EfiIsDevicePathEndSubType(a))

#define EFI_DP_IS_END_TYPE(a) EfiIsDevicePathEndType(a)
#define EFI_DP_IS_END_SUBTYPE(a) EfiIsDevicePathEndSubType(a)

#define EfiSetDevicePathNodeLength(a, l) \
    do { \
        ((struct efi_device_path_protocol *)(a))->Length[0] = (uint8_t)(l); \
        ((struct efi_device_path_protocol *)(a))->Length[1] = (uint8_t)((l) >> 8); \
    } while (0)

#define EfiSetDevicePathEndNode(a) \
    do { \
        ((struct efi_device_path_protocol *)(a))->Type = EFI_END_DEVICE_PATH_TYPE; \
        ((struct efi_device_path_protocol *)(a))->SubType = EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE; \
        EfiSetDevicePathNodeLength(a, EFI_END_DEVICE_PATH_LENGTH); \
    } while (0)

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
    {0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}}

typedef size_t (EFI_API *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE)(
    const struct efi_device_path_protocol *DevicePath
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH)(
    const struct efi_device_path_protocol *DevicePath
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_PATH)(
    const struct efi_device_path_protocol *Src1,
    const struct efi_device_path_protocol *Src2
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_NODE)(
    const struct efi_device_path_protocol *DevicePath,
    const struct efi_device_path_protocol *DeviceNode
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)(
    const struct efi_device_path_protocol *DevicePath,
    const struct efi_device_path_protocol *DevicePathInstance
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)(
    struct efi_device_path_protocol **DevicePathInstance,
    size_t *DevicePathInstanceSize
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_UTILS_CREATE_NODE)(
    uint8_t NodeType,
    uint8_t NodeSubType,
    uint16_t NodeLength
);

typedef bool (EFI_API *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE)(
    const struct efi_device_path_protocol *DevicePath
);

struct efi_device_path_utilities_protocol {
    EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE GetDevicePathSize;
    EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH DuplicateDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_PATH AppendDevicePath;
    EFI_DEVICE_PATH_UTILS_APPEND_NODE AppendDeviceNode;
    EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE AppendDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE GetNextDevicePathInstance;
    EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE IsDevicePathMultiInstance;
    EFI_DEVICE_PATH_UTILS_CREATE_NODE CreateDeviceNode;
};

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
    {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}}

typedef uint16_t *(EFI_API *EFI_DEVICE_PATH_TO_TEXT_NODE)(
    const struct efi_device_path_protocol *DeviceNode,
    bool DisplayOnly,
    bool AllowShortcuts
);

typedef uint16_t *(EFI_API *EFI_DEVICE_PATH_TO_TEXT_PATH)(
    const struct efi_device_path_protocol *DevicePath,
    bool DisplayOnly,
    bool AllowShortcuts
);

struct efi_device_path_to_text_protocol {
    EFI_DEVICE_PATH_TO_TEXT_NODE ConvertDeviceNodeToText;
    EFI_DEVICE_PATH_TO_TEXT_PATH ConvertDevicePathToText;
};

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
    {0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}}

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_FROM_TEXT_NODE)(
    const uint16_t *TextDeviceNode
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_DEVICE_PATH_FROM_TEXT_PATH)(
    const uint16_t *TextDevicePath
);

/* The specification's structure body misspells both member names ("Devic"). */
struct efi_device_path_from_text_protocol {
    EFI_DEVICE_PATH_FROM_TEXT_NODE ConvertTextToDeviceNode;
    EFI_DEVICE_PATH_FROM_TEXT_PATH ConvertTextToDevicePath;
};

#ifdef __cplusplus
}
#endif

#endif
