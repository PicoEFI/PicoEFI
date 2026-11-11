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
    uint8_t type;
    uint8_t sub_type;
    uint8_t length[2];
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
    struct efi_device_path_protocol header;
    uint8_t function;
    uint8_t device;
} __attribute__((__packed__));

#define EFI_HW_PCCARD_DP 0x02

struct efi_pccard_device_path {
    struct efi_device_path_protocol header;
    uint8_t function_number;
} __attribute__((__packed__));

#define EFI_HW_MEMMAP_DP 0x03

struct efi_memmap_device_path {
    struct efi_device_path_protocol header;
    uint32_t memory_type;
    efi_physical_address starting_address;
    efi_physical_address ending_address;
} __attribute__((__packed__));

#define EFI_HW_VENDOR_DP 0x04

struct efi_vendor_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid guid;
} __attribute__((__packed__));

#define EFI_HW_CONTROLLER_DP 0x05

struct efi_controller_device_path {
    struct efi_device_path_protocol header;
    uint32_t controller_number;
} __attribute__((__packed__));

#define EFI_HW_BMC_DP 0x06

struct efi_bmc_device_path {
    struct efi_device_path_protocol header;
    uint8_t interface_type;
    uint8_t base_address[8];
} __attribute__((__packed__));

/* The shift is done in uint32_t so that product numbers from 0x8000 up do not overflow. */
#define EFI_PNP_ID(id) ((uint32_t)(((uint32_t)(id) << 16) | 0x41D0))
#define EFI_EISA_PNP_ID(id) EFI_PNP_ID(id)

#define EFI_PNP_EISA_ID_CONST 0x41d0
#define EFI_EISA_ID(name, num) ((uint32_t)(name) | ((uint32_t)(num) << 16))
#define EFI_PNP_EISA_ID_MASK 0xffff
#define EFI_EISA_ID_TO_NUM(id) ((uint32_t)(id) >> 16)

#define EFI_ACPI_DP 0x01

struct efi_acpi_hid_device_path {
    struct efi_device_path_protocol header;
    uint32_t hid;
    uint32_t uid;
} __attribute__((__packed__));

#define EFI_ACPI_EXTENDED_DP 0x02

/* hid_str starts _HIDSTR; _UIDSTR and _CIDSTR follow it. */
struct efi_acpi_extended_hid_device_path {
    struct efi_device_path_protocol header;
    uint32_t hid;
    uint32_t uid;
    uint32_t cid;
    char hid_str[1];
} __attribute__((__packed__));

#define EFI_ACPI_ADR_DP 0x03

struct efi_acpi_adr_device_path {
    struct efi_device_path_protocol header;
    uint32_t adr;
} __attribute__((__packed__));

#define EFI_ACPI_NVDIMM_DP 0x04

struct efi_acpi_nvdimm_device_path {
    struct efi_device_path_protocol header;
    uint32_t nfit_device_handle;
} __attribute__((__packed__));

#define EFI_MSG_ATAPI_DP 0x01

struct efi_atapi_device_path {
    struct efi_device_path_protocol header;
    uint8_t primary_secondary;
    uint8_t slave_master;
    uint16_t lun;
} __attribute__((__packed__));

#define EFI_MSG_SCSI_DP 0x02

struct efi_scsi_device_path {
    struct efi_device_path_protocol header;
    uint16_t pun;
    uint16_t lun;
} __attribute__((__packed__));

#define EFI_MSG_FIBRECHANNEL_DP 0x03

struct efi_fibrechannel_device_path {
    struct efi_device_path_protocol header;
    uint32_t reserved;
    uint64_t wwn;
    uint64_t lun;
} __attribute__((__packed__));

#define EFI_MSG_FIBRECHANNELEX_DP 0x15

struct efi_fibrechannelex_device_path {
    struct efi_device_path_protocol header;
    uint32_t reserved;
    uint8_t wwn[8];
    uint8_t lun[8];
} __attribute__((__packed__));

#define EFI_MSG_1394_DP 0x04

struct efi_f1394_device_path {
    struct efi_device_path_protocol header;
    uint32_t reserved;
    uint64_t guid;
} __attribute__((__packed__));

#define EFI_MSG_USB_DP 0x05

struct efi_usb_device_path {
    struct efi_device_path_protocol header;
    uint8_t parent_port_number;
    uint8_t interface_number;
} __attribute__((__packed__));

#define EFI_MSG_SATA_DP 0x12

struct efi_sata_device_path {
    struct efi_device_path_protocol header;
    uint16_t hba_port_number;
    uint16_t port_multiplier_port_number;
    uint16_t lun;
} __attribute__((__packed__));

#define EFI_MSG_USB_WWID_DP 0x10

struct efi_usb_wwid_device_path {
    struct efi_device_path_protocol header;
    uint16_t interface_number;
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t serial_number[1];
} __attribute__((__packed__));

#define EFI_MSG_DEVICE_LOGICAL_UNIT_DP 0x11

struct efi_device_logical_unit_device_path {
    struct efi_device_path_protocol header;
    uint8_t lun;
} __attribute__((__packed__));

#define EFI_MSG_USB_CLASS_DP 0x0F

struct efi_usb_class_device_path {
    struct efi_device_path_protocol header;
    uint16_t vendor_id;
    uint16_t product_id;
    uint8_t device_class;
    uint8_t device_sub_class;
    uint8_t device_protocol;
} __attribute__((__packed__));

#define EFI_MSG_I2O_DP 0x06

struct efi_i2o_device_path {
    struct efi_device_path_protocol header;
    uint32_t tid;
} __attribute__((__packed__));

#define EFI_MSG_MAC_ADDR_DP 0x0B

struct efi_mac_addr_device_path {
    struct efi_device_path_protocol header;
    struct efi_mac_address mac_address;
    uint8_t if_type;
} __attribute__((__packed__));

#define EFI_MSG_IPV4_DP 0x0C

struct efi_ipv4_device_path {
    struct efi_device_path_protocol header;
    struct efi_ipv4_address local_ip_address;
    struct efi_ipv4_address remote_ip_address;
    uint16_t local_port;
    uint16_t remote_port;
    uint16_t protocol;
    uint8_t static_ip_address;
    struct efi_ipv4_address gateway_ip_address;
    struct efi_ipv4_address subnet_mask;
} __attribute__((__packed__));

#define EFI_MSG_IPV6_DP 0x0D

struct efi_ipv6_device_path {
    struct efi_device_path_protocol header;
    struct efi_ipv6_address local_ip_address;
    struct efi_ipv6_address remote_ip_address;
    uint16_t local_port;
    uint16_t remote_port;
    uint16_t protocol;
    uint8_t ip_address_origin;
    uint8_t prefix_length;
    struct efi_ipv6_address gateway_ip_address;
} __attribute__((__packed__));

#define EFI_MSG_VLAN_DP 0x14

struct efi_vlan_device_path {
    struct efi_device_path_protocol header;
    uint16_t vlan_id;
} __attribute__((__packed__));

#define EFI_MSG_INFINIBAND_DP 0x09

struct efi_infiniband_device_path {
    struct efi_device_path_protocol header;
    uint32_t resource_flags;
    uint8_t port_gid[16];
    uint64_t service_id;
    uint64_t target_port_id;
    uint64_t device_id;
} __attribute__((__packed__));

#define EFI_INFINIBAND_RESOURCE_FLAG_IOC_SERVICE 0x01
#define EFI_INFINIBAND_RESOURCE_FLAG_EXTENDED_BOOT_ENVIRONMENT 0x02
#define EFI_INFINIBAND_RESOURCE_FLAG_CONSOLE_PROTOCOL 0x04
#define EFI_INFINIBAND_RESOURCE_FLAG_STORAGE_PROTOCOL 0x08
#define EFI_INFINIBAND_RESOURCE_FLAG_NETWORK_PROTOCOL 0x10

#define EFI_MSG_UART_DP 0x0E

struct efi_uart_device_path {
    struct efi_device_path_protocol header;
    uint32_t reserved;
    uint64_t baud_rate;
    uint8_t data_bits;
    uint8_t parity;
    uint8_t stop_bits;
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
    struct efi_device_path_protocol header;
    struct efi_guid guid;
    uint32_t flow_control_map;
} __attribute__((__packed__));

#define EFI_UART_FLOW_CONTROL_HARDWARE 0x00000001
#define EFI_UART_FLOW_CONTROL_XON_XOFF 0x00000002

#define EFI_SAS_DEVICE_PATH_GUID \
    {0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}}

struct efi_sas_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid guid;
    uint32_t reserved;
    uint64_t sas_address;
    uint64_t lun;
    uint16_t device_topology;
    uint16_t relative_target_port;
} __attribute__((__packed__));

#define EFI_MSG_SASEX_DP 0x16

/* length 24: the offsets and length the specification prints for this node disagree. */
struct efi_sasex_device_path {
    struct efi_device_path_protocol header;
    uint8_t sas_address[8];
    uint8_t lun[8];
    uint16_t device_topology;
    uint16_t relative_target_port;
} __attribute__((__packed__));

#define EFI_MSG_ISCSI_DP 0x13

struct efi_iscsi_device_path {
    struct efi_device_path_protocol header;
    uint16_t network_protocol;
    uint16_t login_option;
    uint64_t lun;
    uint16_t target_portal_group_tag;
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
    struct efi_device_path_protocol header;
    uint32_t namespace_id;
    uint64_t namespace_uuid;
} __attribute__((__packed__));

#define EFI_MSG_URI_DP 0x18

struct efi_uri_device_path {
    struct efi_device_path_protocol header;
    char uri[1];
} __attribute__((__packed__));

#define EFI_MSG_UFS_DP 0x19

struct efi_ufs_device_path {
    struct efi_device_path_protocol header;
    uint8_t pun;
    uint8_t lun;
} __attribute__((__packed__));

#define EFI_MSG_SD_DP 0x1A

struct efi_sd_device_path {
    struct efi_device_path_protocol header;
    uint8_t slot_number;
} __attribute__((__packed__));

struct efi_bluetooth_address {
    uint8_t address[6];
} __attribute__((__packed__));

struct efi_bluetooth_le_address {
    uint8_t address[6];
    uint8_t type;
} __attribute__((__packed__));

#define EFI_MSG_BLUETOOTH_DP 0x1B

struct efi_bluetooth_device_path {
    struct efi_device_path_protocol header;
    struct efi_bluetooth_address bd_addr;
} __attribute__((__packed__));

#define EFI_MSG_WIFI_DP 0x1C

struct efi_wifi_device_path {
    struct efi_device_path_protocol header;
    uint8_t ss_id[32];
} __attribute__((__packed__));

#define EFI_MSG_EMMC_DP 0x1D

struct efi_emmc_device_path {
    struct efi_device_path_protocol header;
    uint8_t slot_number;
} __attribute__((__packed__));

#define EFI_MSG_BLUETOOTH_LE_DP 0x1E

struct efi_bluetooth_le_device_path {
    struct efi_device_path_protocol header;
    struct efi_bluetooth_le_address address;
} __attribute__((__packed__));

#define EFI_MSG_DNS_DP 0x1F

__extension__ struct efi_dns_device_path {
    struct efi_device_path_protocol header;
    uint8_t is_ipv6;
    union efi_ip_address dns_server_ip[];
} __attribute__((__packed__));

#define EFI_NVDIMM_NAMESPACE_DP 0x20

struct efi_nvdimm_namespace_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid uuid;
} __attribute__((__packed__));

#define EFI_MSG_REST_SERVICE_DP 0x21

struct efi_rest_service_device_path {
    struct efi_device_path_protocol header;
    uint8_t rest_service;
    uint8_t access_mode;
} __attribute__((__packed__));

/* length 22 + n: the specification prints 21 + n but puts the vendor data at offset 22. */
__extension__ struct efi_rest_vendor_service_device_path {
    struct efi_rest_service_device_path rest_service_device_path;
    struct efi_guid rest_service_guid;
    uint8_t vendor_defined_data[];
} __attribute__((__packed__));

#define EFI_MSG_NVME_OF_NAMESPACE_DP 0x22

/* length 21 + n: the specification prints 20 + n but puts subsystem_nqn at offset 21. */
__extension__ struct efi_nvme_of_namespace_device_path {
    struct efi_device_path_protocol header;
    uint8_t namespace_id_type;
    uint8_t namespace_id[16];
    char subsystem_nqn[];
} __attribute__((__packed__));

#define EFI_MEDIA_HARDDRIVE_DP 0x01

struct efi_harddrive_device_path {
    struct efi_device_path_protocol header;
    uint32_t partition_number;
    uint64_t partition_start;
    uint64_t partition_size;
    uint8_t signature[16];
    uint8_t mbr_type;
    uint8_t signature_type;
} __attribute__((__packed__));

#define EFI_MBR_TYPE_PCAT 0x01
#define EFI_MBR_TYPE_EFI_PARTITION_TABLE_HEADER 0x02

#define EFI_NO_DISK_SIGNATURE 0x00
#define EFI_SIGNATURE_TYPE_MBR 0x01
#define EFI_SIGNATURE_TYPE_GUID 0x02

#define EFI_MEDIA_CDROM_DP 0x02

struct efi_cdrom_device_path {
    struct efi_device_path_protocol header;
    uint32_t boot_entry;
    uint64_t partition_start;
    uint64_t partition_size;
} __attribute__((__packed__));

#define EFI_MEDIA_VENDOR_DP 0x03

#define EFI_MEDIA_FILEPATH_DP 0x04

struct efi_filepath_device_path {
    struct efi_device_path_protocol header;
    uint16_t path_name[1];
} __attribute__((__packed__));

#define EFI_SIZE_OF_FILEPATH_DEVICE_PATH offsetof(struct efi_filepath_device_path, path_name)

#define EFI_MEDIA_PROTOCOL_DP 0x05

struct efi_media_protocol_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid protocol;
} __attribute__((__packed__));

#define EFI_MEDIA_PIWG_FW_FILE_DP 0x06

struct efi_media_fw_vol_filepath_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid fv_file_name;
} __attribute__((__packed__));

#define EFI_MEDIA_PIWG_FW_VOL_DP 0x07

struct efi_media_fw_vol_device_path {
    struct efi_device_path_protocol header;
    struct efi_guid fv_name;
} __attribute__((__packed__));

#define EFI_MEDIA_RELATIVE_OFFSET_RANGE_DP 0x08

struct efi_media_relative_offset_range_device_path {
    struct efi_device_path_protocol header;
    uint32_t reserved;
    uint64_t starting_offset;
    uint64_t ending_offset;
} __attribute__((__packed__));

#define EFI_MEDIA_RAM_DISK_DP 0x09

struct efi_media_ram_disk_device_path {
    struct efi_device_path_protocol header;
    uint32_t starting_addr[2];
    uint32_t ending_addr[2];
    struct efi_guid type_guid;
    uint16_t instance;
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
    struct efi_device_path_protocol header;
    uint16_t device_type;
    uint16_t status_flag;
    char string[1];
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
    struct efi_device_path_protocol dev_path;
    struct efi_pci_device_path pci;
    struct efi_pccard_device_path pc_card;
    struct efi_memmap_device_path mem_map;
    struct efi_vendor_device_path vendor;
    struct efi_controller_device_path controller;
    struct efi_bmc_device_path bmc;
    struct efi_acpi_hid_device_path acpi;
    struct efi_acpi_extended_hid_device_path extended_acpi;
    struct efi_acpi_adr_device_path acpi_adr;
    struct efi_atapi_device_path atapi;
    struct efi_scsi_device_path scsi;
    struct efi_iscsi_device_path iscsi;
    struct efi_fibrechannel_device_path fibre_channel;
    struct efi_fibrechannelex_device_path fibre_channel_ex;
    struct efi_f1394_device_path f1394;
    struct efi_usb_device_path usb;
    struct efi_sata_device_path sata;
    struct efi_usb_class_device_path usb_class;
    struct efi_usb_wwid_device_path usb_wwid;
    struct efi_device_logical_unit_device_path logic_unit;
    struct efi_i2o_device_path i2o;
    struct efi_mac_addr_device_path mac_addr;
    struct efi_ipv4_device_path ipv4;
    struct efi_ipv6_device_path ipv6;
    struct efi_vlan_device_path vlan;
    struct efi_infiniband_device_path infini_band;
    struct efi_uart_device_path uart;
    struct efi_uart_flow_control_device_path uart_flow_control;
    struct efi_sas_device_path sas;
    struct efi_sasex_device_path sas_ex;
    struct efi_nvme_namespace_device_path nvme_namespace;
    struct efi_nvme_of_namespace_device_path nvme_of_namespace;
    struct efi_dns_device_path dns;
    struct efi_uri_device_path uri;
    struct efi_bluetooth_device_path bluetooth;
    struct efi_wifi_device_path wifi;
    struct efi_ufs_device_path ufs;
    struct efi_sd_device_path sd;
    struct efi_emmc_device_path emmc;
    struct efi_harddrive_device_path hard_drive;
    struct efi_cdrom_device_path cd;
    struct efi_filepath_device_path file_path;
    struct efi_media_protocol_device_path media_protocol;
    struct efi_media_fw_vol_device_path firmware_volume;
    struct efi_media_fw_vol_filepath_device_path firmware_file;
    struct efi_media_relative_offset_range_device_path offset;
    struct efi_media_ram_disk_device_path ram_disk;
    struct efi_bbs_bbs_device_path bbs;
};

union efi_dev_path_ptr {
    struct efi_device_path_protocol *dev_path;
    struct efi_pci_device_path *pci;
    struct efi_pccard_device_path *pc_card;
    struct efi_memmap_device_path *mem_map;
    struct efi_vendor_device_path *vendor;
    struct efi_controller_device_path *controller;
    struct efi_bmc_device_path *bmc;
    struct efi_acpi_hid_device_path *acpi;
    struct efi_acpi_extended_hid_device_path *extended_acpi;
    struct efi_acpi_adr_device_path *acpi_adr;
    struct efi_atapi_device_path *atapi;
    struct efi_scsi_device_path *scsi;
    struct efi_iscsi_device_path *iscsi;
    struct efi_fibrechannel_device_path *fibre_channel;
    struct efi_fibrechannelex_device_path *fibre_channel_ex;
    struct efi_f1394_device_path *f1394;
    struct efi_usb_device_path *usb;
    struct efi_sata_device_path *sata;
    struct efi_usb_class_device_path *usb_class;
    struct efi_usb_wwid_device_path *usb_wwid;
    struct efi_device_logical_unit_device_path *logic_unit;
    struct efi_i2o_device_path *i2o;
    struct efi_mac_addr_device_path *mac_addr;
    struct efi_ipv4_device_path *ipv4;
    struct efi_ipv6_device_path *ipv6;
    struct efi_vlan_device_path *vlan;
    struct efi_infiniband_device_path *infini_band;
    struct efi_uart_device_path *uart;
    struct efi_uart_flow_control_device_path *uart_flow_control;
    struct efi_sas_device_path *sas;
    struct efi_sasex_device_path *sas_ex;
    struct efi_nvme_namespace_device_path *nvme_namespace;
    struct efi_nvme_of_namespace_device_path *nvme_of_namespace;
    struct efi_dns_device_path *dns;
    struct efi_uri_device_path *uri;
    struct efi_bluetooth_device_path *bluetooth;
    struct efi_wifi_device_path *wifi;
    struct efi_ufs_device_path *ufs;
    struct efi_sd_device_path *sd;
    struct efi_emmc_device_path *emmc;
    struct efi_harddrive_device_path *hard_drive;
    struct efi_cdrom_device_path *cd;
    struct efi_filepath_device_path *file_path;
    struct efi_media_protocol_device_path *media_protocol;
    struct efi_media_fw_vol_device_path *firmware_volume;
    struct efi_media_fw_vol_filepath_device_path *firmware_file;
    struct efi_media_relative_offset_range_device_path *offset;
    struct efi_media_ram_disk_device_path *ram_disk;
    struct efi_bbs_bbs_device_path *bbs;
    uint8_t *raw;
};

#define EfiDevicePathType(a) (((const struct efi_device_path_protocol *)(a))->type)
#define EfiDevicePathSubType(a) (((const struct efi_device_path_protocol *)(a))->sub_type)
#define EfiDevicePathNodeLength(a) \
    ((uint16_t)(((const struct efi_device_path_protocol *)(a))->length[0] | \
        (((const struct efi_device_path_protocol *)(a))->length[1] << 8)))
#define EfiNextDevicePathNode(a) \
    ((struct efi_device_path_protocol *)((uint8_t *)(a) + EfiDevicePathNodeLength(a)))

#define EfiIsDevicePathEndType(a) (EfiDevicePathType(a) == EFI_END_DEVICE_PATH_TYPE)
#define EfiIsDevicePathEndSubType(a) (EfiDevicePathSubType(a) == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#define EfiIsDevicePathEnd(a) (EfiIsDevicePathEndType(a) && EfiIsDevicePathEndSubType(a))

#define EFI_DP_IS_END_TYPE(a) EfiIsDevicePathEndType(a)
#define EFI_DP_IS_END_SUBTYPE(a) EfiIsDevicePathEndSubType(a)

#define EfiSetDevicePathNodeLength(a, l) \
    do { \
        ((struct efi_device_path_protocol *)(a))->length[0] = (uint8_t)(l); \
        ((struct efi_device_path_protocol *)(a))->length[1] = (uint8_t)((l) >> 8); \
    } while (0)

#define EfiSetDevicePathEndNode(a) \
    do { \
        ((struct efi_device_path_protocol *)(a))->type = EFI_END_DEVICE_PATH_TYPE; \
        ((struct efi_device_path_protocol *)(a))->sub_type = EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE; \
        EfiSetDevicePathNodeLength(a, EFI_END_DEVICE_PATH_LENGTH); \
    } while (0)

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
    {0x379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}}

typedef size_t (EFI_API *efi_device_path_utils_get_device_path_size)(
    const struct efi_device_path_protocol *device_path
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_dup_device_path)(
    const struct efi_device_path_protocol *device_path
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_append_path)(
    const struct efi_device_path_protocol *src1,
    const struct efi_device_path_protocol *src2
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_append_node)(
    const struct efi_device_path_protocol *device_path,
    const struct efi_device_path_protocol *device_node
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_append_instance)(
    const struct efi_device_path_protocol *device_path,
    const struct efi_device_path_protocol *device_path_instance
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_get_next_instance)(
    struct efi_device_path_protocol **device_path_instance,
    size_t *device_path_instance_size
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_utils_create_node)(
    uint8_t node_type,
    uint8_t node_sub_type,
    uint16_t node_length
);

typedef bool (EFI_API *efi_device_path_utils_is_multi_instance)(
    const struct efi_device_path_protocol *device_path
);

struct efi_device_path_utilities_protocol {
    efi_device_path_utils_get_device_path_size get_device_path_size;
    efi_device_path_utils_dup_device_path duplicate_device_path;
    efi_device_path_utils_append_path append_device_path;
    efi_device_path_utils_append_node append_device_node;
    efi_device_path_utils_append_instance append_device_path_instance;
    efi_device_path_utils_get_next_instance get_next_device_path_instance;
    efi_device_path_utils_is_multi_instance is_device_path_multi_instance;
    efi_device_path_utils_create_node create_device_node;
};

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID \
    {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}}

typedef uint16_t *(EFI_API *efi_device_path_to_text_node)(
    const struct efi_device_path_protocol *device_node,
    bool display_only,
    bool allow_shortcuts
);

typedef uint16_t *(EFI_API *efi_device_path_to_text_path)(
    const struct efi_device_path_protocol *device_path,
    bool display_only,
    bool allow_shortcuts
);

struct efi_device_path_to_text_protocol {
    efi_device_path_to_text_node convert_device_node_to_text;
    efi_device_path_to_text_path convert_device_path_to_text;
};

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID \
    {0x5c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}}

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_from_text_node)(
    const uint16_t *text_device_node
);

typedef struct efi_device_path_protocol *(EFI_API *efi_device_path_from_text_path)(
    const uint16_t *text_device_path
);

/* The specification's structure body misspells both member names ("Devic"). */
struct efi_device_path_from_text_protocol {
    efi_device_path_from_text_node convert_text_to_device_node;
    efi_device_path_from_text_path convert_text_to_device_path;
};

#ifdef __cplusplus
}
#endif

#endif
