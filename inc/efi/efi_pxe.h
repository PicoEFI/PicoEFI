#ifndef EFI_EFI_PXE_H_
#define EFI_EFI_PXE_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Every supported target is little-endian and has a 64-bit integer type. */
#define EFI_PXE_INTEL_ORDER 1
#define EFI_PXE_UINT64_SUPPORT 1

#define EFI_PXE_BUSTYPE(a, b, c, d) \
    ((((uint32_t)(d) & 0xFF) << 24) | \
    (((uint32_t)(c) & 0xFF) << 16) | \
    (((uint32_t)(b) & 0xFF) << 8) | \
    ((uint32_t)(a) & 0xFF))

#define EFI_PXE_BUSTYPE_PXE EFI_PXE_BUSTYPE('!', 'P', 'X', 'E')

#define EFI_PXE_BUSTYPE_PCI EFI_PXE_BUSTYPE('P', 'C', 'I', 'R')
#define EFI_PXE_BUSTYPE_PC_CARD EFI_PXE_BUSTYPE('P', 'C', 'C', 'R')
#define EFI_PXE_BUSTYPE_USB EFI_PXE_BUSTYPE('U', 'S', 'B', 'R')
#define EFI_PXE_BUSTYPE_1394 EFI_PXE_BUSTYPE('1', '3', '9', '4')

#define EFI_PXE_SWAP_UINT16(n) \
    ((((uint16_t)(n) & 0x00FF) << 8) | \
    (((uint16_t)(n) & 0xFF00) >> 8))

#define EFI_PXE_SWAP_UINT32(n) \
    ((((uint32_t)(n) & 0x000000FF) << 24) | \
    (((uint32_t)(n) & 0x0000FF00) << 8) | \
    (((uint32_t)(n) & 0x00FF0000) >> 8) | \
    (((uint32_t)(n) & 0xFF000000) >> 24))

#define EFI_PXE_SWAP_UINT64(n) \
    ((((uint64_t)(n) & 0x00000000000000FF) << 56) | \
    (((uint64_t)(n) & 0x000000000000FF00) << 40) | \
    (((uint64_t)(n) & 0x0000000000FF0000) << 24) | \
    (((uint64_t)(n) & 0x00000000FF000000) << 8) | \
    (((uint64_t)(n) & 0x000000FF00000000) >> 8) | \
    (((uint64_t)(n) & 0x0000FF0000000000) >> 24) | \
    (((uint64_t)(n) & 0x00FF000000000000) >> 40) | \
    (((uint64_t)(n) & 0xFF00000000000000) >> 56))

#define EFI_PXE_CPBSIZE_NOT_USED 0
#define EFI_PXE_DBSIZE_NOT_USED 0
#define EFI_PXE_CPBADDR_NOT_USED ((uint64_t)0)
#define EFI_PXE_DBADDR_NOT_USED ((uint64_t)0)

typedef uint16_t EFI_PXE_OPCODE;

#define EFI_PXE_OPCODE_GET_STATE 0x0000
#define EFI_PXE_OPCODE_START 0x0001
#define EFI_PXE_OPCODE_STOP 0x0002
#define EFI_PXE_OPCODE_GET_INIT_INFO 0x0003
#define EFI_PXE_OPCODE_GET_CONFIG_INFO 0x0004
#define EFI_PXE_OPCODE_INITIALIZE 0x0005
#define EFI_PXE_OPCODE_RESET 0x0006
#define EFI_PXE_OPCODE_SHUTDOWN 0x0007
#define EFI_PXE_OPCODE_INTERRUPT_ENABLES 0x0008
#define EFI_PXE_OPCODE_RECEIVE_FILTERS 0x0009
#define EFI_PXE_OPCODE_STATION_ADDRESS 0x000A
#define EFI_PXE_OPCODE_STATISTICS 0x000B
#define EFI_PXE_OPCODE_MCAST_IP_TO_MAC 0x000C
#define EFI_PXE_OPCODE_NVDATA 0x000D
#define EFI_PXE_OPCODE_GET_STATUS 0x000E
#define EFI_PXE_OPCODE_FILL_HEADER 0x000F
#define EFI_PXE_OPCODE_TRANSMIT 0x0010
#define EFI_PXE_OPCODE_RECEIVE 0x0011
#define EFI_PXE_OPCODE_LAST_VALID 0x0011

typedef uint16_t EFI_PXE_OPFLAGS;

#define EFI_PXE_OPFLAGS_NOT_USED 0x0000

#define EFI_PXE_OPFLAGS_INITIALIZE_CABLE_DETECT_MASK 0x0001
#define EFI_PXE_OPFLAGS_INITIALIZE_DETECT_CABLE 0x0000
#define EFI_PXE_OPFLAGS_INITIALIZE_DO_NOT_DETECT_CABLE 0x0001

#define EFI_PXE_OPFLAGS_RESET_DISABLE_INTERRUPTS 0x0001
#define EFI_PXE_OPFLAGS_RESET_DISABLE_FILTERS 0x0002

#define EFI_PXE_OPFLAGS_INTERRUPT_OPMASK 0xC000
#define EFI_PXE_OPFLAGS_INTERRUPT_ENABLE 0x8000
#define EFI_PXE_OPFLAGS_INTERRUPT_DISABLE 0x4000
#define EFI_PXE_OPFLAGS_INTERRUPT_READ 0x0000
#define EFI_PXE_OPFLAGS_INTERRUPT_RECEIVE 0x0001
#define EFI_PXE_OPFLAGS_INTERRUPT_TRANSMIT 0x0002
#define EFI_PXE_OPFLAGS_INTERRUPT_COMMAND 0x0004
#define EFI_PXE_OPFLAGS_INTERRUPT_SOFTWARE 0x0008

#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_OPMASK 0xC000
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_ENABLE 0x8000
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_DISABLE 0x4000
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_READ 0x0000
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_RESET_MCAST_LIST 0x2000
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_UNICAST 0x0001
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_BROADCAST 0x0002
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_FILTERED_MULTICAST 0x0004
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_PROMISCUOUS 0x0008
#define EFI_PXE_OPFLAGS_RECEIVE_FILTER_ALL_MULTICAST 0x0010

#define EFI_PXE_OPFLAGS_STATION_ADDRESS_READ 0x0000
#define EFI_PXE_OPFLAGS_STATION_ADDRESS_WRITE 0x0000
#define EFI_PXE_OPFLAGS_STATION_ADDRESS_RESET 0x0001

#define EFI_PXE_OPFLAGS_STATISTICS_READ 0x0000
#define EFI_PXE_OPFLAGS_STATISTICS_RESET 0x0001

#define EFI_PXE_OPFLAGS_MCAST_IP_TO_MAC_OPMASK 0x0003
#define EFI_PXE_OPFLAGS_MCAST_IPV4_TO_MAC 0x0000
#define EFI_PXE_OPFLAGS_MCAST_IPV6_TO_MAC 0x0001

#define EFI_PXE_OPFLAGS_NVDATA_OPMASK 0x0001
#define EFI_PXE_OPFLAGS_NVDATA_READ 0x0000
#define EFI_PXE_OPFLAGS_NVDATA_WRITE 0x0001

#define EFI_PXE_OPFLAGS_GET_INTERRUPT_STATUS 0x0001
#define EFI_PXE_OPFLAGS_GET_TRANSMITTED_BUFFERS 0x0002
#define EFI_PXE_OPFLAGS_GET_MEDIA_STATUS 0x0004

#define EFI_PXE_OPFLAGS_FILL_HEADER_OPMASK 0x0001
#define EFI_PXE_OPFLAGS_FILL_HEADER_FRAGMENTED 0x0001
#define EFI_PXE_OPFLAGS_FILL_HEADER_WHOLE 0x0000

#define EFI_PXE_OPFLAGS_SWUNDI_TRANSMIT_OPMASK 0x0001
#define EFI_PXE_OPFLAGS_TRANSMIT_BLOCK 0x0001
#define EFI_PXE_OPFLAGS_TRANSMIT_DONT_BLOCK 0x0000

#define EFI_PXE_OPFLAGS_TRANSMIT_OPMASK 0x0002
#define EFI_PXE_OPFLAGS_TRANSMIT_FRAGMENTED 0x0002
#define EFI_PXE_OPFLAGS_TRANSMIT_WHOLE 0x0000

typedef uint16_t EFI_PXE_STATFLAGS;

#define EFI_PXE_STATFLAGS_INITIALIZE 0x0000

#define EFI_PXE_STATFLAGS_STATUS_MASK 0xC000
#define EFI_PXE_STATFLAGS_COMMAND_COMPLETE 0xC000
#define EFI_PXE_STATFLAGS_COMMAND_FAILED 0x8000
#define EFI_PXE_STATFLAGS_COMMAND_QUEUED 0x4000

#define EFI_PXE_STATFLAGS_GET_STATE_MASK 0x0003
#define EFI_PXE_STATFLAGS_GET_STATE_INITIALIZED 0x0002
#define EFI_PXE_STATFLAGS_GET_STATE_STARTED 0x0001
#define EFI_PXE_STATFLAGS_GET_STATE_STOPPED 0x0000

#define EFI_PXE_STATFLAGS_CABLE_DETECT_MASK 0x0001
#define EFI_PXE_STATFLAGS_CABLE_DETECT_NOT_SUPPORTED 0x0000
#define EFI_PXE_STATFLAGS_CABLE_DETECT_SUPPORTED 0x0001
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_MEDIA_MASK 0x0002
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_MEDIA_NOT_SUPPORTED 0x0000
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_MEDIA_SUPPORTED 0x0002

#define EFI_PXE_STATFLAGS_INITIALIZED_NO_MEDIA 0x0001

#define EFI_PXE_STATFLAGS_RESET_NO_MEDIA 0x0001

#define EFI_PXE_STATFLAGS_INTERRUPT_RECEIVE 0x0001
#define EFI_PXE_STATFLAGS_INTERRUPT_TRANSMIT 0x0002
#define EFI_PXE_STATFLAGS_INTERRUPT_COMMAND 0x0004

#define EFI_PXE_STATFLAGS_RECEIVE_FILTER_UNICAST 0x0001
#define EFI_PXE_STATFLAGS_RECEIVE_FILTER_BROADCAST 0x0002
#define EFI_PXE_STATFLAGS_RECEIVE_FILTER_FILTERED_MULTICAST 0x0004
#define EFI_PXE_STATFLAGS_RECEIVE_FILTER_PROMISCUOUS 0x0008
#define EFI_PXE_STATFLAGS_RECEIVE_FILTER_ALL_MULTICAST 0x0010

#define EFI_PXE_STATFLAGS_GET_STATUS_INTERRUPT_MASK 0x000F
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_INTERRUPTS 0x0000
#define EFI_PXE_STATFLAGS_GET_STATUS_RECEIVE 0x0001
#define EFI_PXE_STATFLAGS_GET_STATUS_TRANSMIT 0x0002
#define EFI_PXE_STATFLAGS_GET_STATUS_COMMAND 0x0004
#define EFI_PXE_STATFLAGS_GET_STATUS_SOFTWARE 0x0008
#define EFI_PXE_STATFLAGS_GET_STATUS_TXBUF_QUEUE_EMPTY 0x0010
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_TXBUFS_WRITTEN 0x0020
#define EFI_PXE_STATFLAGS_GET_STATUS_NO_MEDIA 0x0040

typedef uint16_t EFI_PXE_STATCODE;

#define EFI_PXE_STATCODE_INITIALIZE 0x0000

#define EFI_PXE_STATCODE_SUCCESS 0x0000
#define EFI_PXE_STATCODE_INVALID_CDB 0x0001
#define EFI_PXE_STATCODE_INVALID_CPB 0x0002
#define EFI_PXE_STATCODE_BUSY 0x0003
#define EFI_PXE_STATCODE_QUEUE_FULL 0x0004
#define EFI_PXE_STATCODE_ALREADY_STARTED 0x0005
#define EFI_PXE_STATCODE_NOT_STARTED 0x0006
#define EFI_PXE_STATCODE_NOT_SHUTDOWN 0x0007
#define EFI_PXE_STATCODE_ALREADY_INITIALIZED 0x0008
#define EFI_PXE_STATCODE_NOT_INITIALIZED 0x0009
#define EFI_PXE_STATCODE_DEVICE_FAILURE 0x000A
#define EFI_PXE_STATCODE_NVDATA_FAILURE 0x000B
#define EFI_PXE_STATCODE_UNSUPPORTED 0x000C
#define EFI_PXE_STATCODE_BUFFER_FULL 0x000D
#define EFI_PXE_STATCODE_INVALID_PARAMETER 0x000E
#define EFI_PXE_STATCODE_INVALID_UNDI 0x000F
#define EFI_PXE_STATCODE_IPV4_NOT_SUPPORTED 0x0010
#define EFI_PXE_STATCODE_IPV6_NOT_SUPPORTED 0x0011
#define EFI_PXE_STATCODE_NOT_ENOUGH_MEMORY 0x0012
#define EFI_PXE_STATCODE_NO_DATA 0x0013

typedef uint16_t EFI_PXE_IFNUM;

#define EFI_PXE_IFNUM_START 0x0000

#define EFI_PXE_IFNUM_INVALID 0x0000

typedef uint16_t EFI_PXE_CONTROL;

#define EFI_PXE_CONTROL_QUEUE_IF_BUSY 0x0002

#define EFI_PXE_CONTROL_LINK 0x0001
#define EFI_PXE_CONTROL_LAST_CDB_IN_LIST 0x0000

typedef uint8_t EFI_PXE_FRAME_TYPE;

#define EFI_PXE_FRAME_TYPE_NONE 0x00
#define EFI_PXE_FRAME_TYPE_UNICAST 0x01
#define EFI_PXE_FRAME_TYPE_BROADCAST 0x02
#define EFI_PXE_FRAME_TYPE_FILTERED_MULTICAST 0x03
#define EFI_PXE_FRAME_TYPE_PROMISCUOUS 0x04
#define EFI_PXE_FRAME_TYPE_PROMISCUOUS_MULTICAST 0x05

typedef uint32_t EFI_PXE_IPV4;

/* Every PXE structure is byte packed, also those printed without the pragma. */
struct efi_pxe_ipv6 {
    uint32_t num[4];
} __attribute__((__packed__));

struct efi_pxe_mac_addr {
    uint8_t num[32];
} __attribute__((__packed__));

typedef uint8_t EFI_PXE_IFTYPE;

#define EFI_PXE_IFTYPE_ETHERNET 0x01
#define EFI_PXE_IFTYPE_TOKENRING 0x04
#define EFI_PXE_IFTYPE_FIBRE_CHANNEL 0x12

typedef uint16_t EFI_PXE_MEDIA_PROTOCOL;

struct efi_pxe_hw_undi {
    uint32_t Signature;
    uint8_t Len;
    uint8_t Fudge;
    uint8_t Rev;
    uint8_t IFcnt;
    uint8_t MajorVer;
    uint8_t MinorVer;
    uint8_t IFcntExt;
    uint8_t reserved;
    uint32_t Implementation;
} __attribute__((__packed__));

#define EFI_PXE_HWSTAT_STATE_MASK 0xC0000000
#define EFI_PXE_HWSTAT_BUSY 0xC0000000
#define EFI_PXE_HWSTAT_INITIALIZED 0x80000000
#define EFI_PXE_HWSTAT_STARTED 0x40000000
#define EFI_PXE_HWSTAT_STOPPED 0x00000000

#define EFI_PXE_HWSTAT_COMMAND_FAILED 0x20000000

#define EFI_PXE_HWSTAT_PROMISCUOUS_MULTICAST_RX_ENABLED 0x00001000
#define EFI_PXE_HWSTAT_PROMISCUOUS_RX_ENABLED 0x00000800
#define EFI_PXE_HWSTAT_BROADCAST_RX_ENABLED 0x00000400
#define EFI_PXE_HWSTAT_MULTICAST_RX_ENABLED 0x00000200
#define EFI_PXE_HWSTAT_UNICAST_RX_ENABLED 0x00000100

#define EFI_PXE_HWSTAT_SOFTWARE_INT_ENABLED 0x00000080
#define EFI_PXE_HWSTAT_TX_COMPLETE_INT_ENABLED 0x00000040
#define EFI_PXE_HWSTAT_PACKET_RX_INT_ENABLED 0x00000020
#define EFI_PXE_HWSTAT_CMD_COMPLETE_INT_ENABLED 0x00000010

#define EFI_PXE_HWSTAT_SOFTWARE_INT_PENDING 0x00000008
#define EFI_PXE_HWSTAT_TX_COMPLETE_INT_PENDING 0x00000004
#define EFI_PXE_HWSTAT_PACKET_RX_INT_PENDING 0x00000002
#define EFI_PXE_HWSTAT_CMD_COMPLETE_INT_PENDING 0x00000001

#define EFI_PXE_HWCMD_ISSUE_COMMAND 0x80000000
#define EFI_PXE_HWCMD_INTS_AND_FILTS 0x00000000

#define EFI_PXE_HWCMD_PROMISCUOUS_MULTICAST_RX_ENABLE 0x00001000
#define EFI_PXE_HWCMD_PROMISCUOUS_RX_ENABLE 0x00000800
#define EFI_PXE_HWCMD_BROADCAST_RX_ENABLE 0x00000400
#define EFI_PXE_HWCMD_MULTICAST_RX_ENABLE 0x00000200
#define EFI_PXE_HWCMD_UNICAST_RX_ENABLE 0x00000100

#define EFI_PXE_HWCMD_SOFTWARE_INT_ENABLE 0x00000080
#define EFI_PXE_HWCMD_TX_COMPLETE_INT_ENABLE 0x00000040
#define EFI_PXE_HWCMD_PACKET_RX_INT_ENABLE 0x00000020
#define EFI_PXE_HWCMD_CMD_COMPLETE_INT_ENABLE 0x00000010

#define EFI_PXE_HWCMD_CLEAR_SOFTWARE_INT 0x00000008
#define EFI_PXE_HWCMD_CLEAR_TX_COMPLETE_INT 0x00000004
#define EFI_PXE_HWCMD_CLEAR_PACKET_RX_INT 0x00000002
#define EFI_PXE_HWCMD_CLEAR_CMD_COMPLETE_INT 0x00000001

struct efi_pxe_sw_undi {
    uint32_t Signature;
    uint8_t Len;
    uint8_t Fudge;
    uint8_t Rev;
    uint8_t IFcnt;
    uint8_t MajorVer;
    uint8_t MinorVer;
    uint8_t IFcntExt;
    uint8_t reserved1;
    uint32_t Implementation;
    uint64_t EntryPoint;
    uint8_t reserved2[3];
    uint8_t BusCnt;
    uint32_t BusType[1];
} __attribute__((__packed__));

union efi_pxe_undi {
    struct efi_pxe_hw_undi hw;
    struct efi_pxe_sw_undi sw;
} __attribute__((__packed__));

#define EFI_PXE_ROMID_SIGNATURE EFI_PXE_BUSTYPE('!', 'P', 'X', 'E')

#define EFI_PXE_ROMID_REV 0x02

#define EFI_PXE_ROMID_MAJORVER 0x03
#define EFI_PXE_ROMID_MINORVER 0x01

#define EFI_PXE_ROMID_IMP_HW_UNDI 0x80000000
#define EFI_PXE_ROMID_IMP_SW_VIRT_ADDR 0x40000000
#define EFI_PXE_ROMID_IMP_64BIT_DEVICE 0x00010000
#define EFI_PXE_ROMID_IMP_FRAG_SUPPORTED 0x00008000
#define EFI_PXE_ROMID_IMP_CMD_LINK_SUPPORTED 0x00004000
#define EFI_PXE_ROMID_IMP_CMD_QUEUE_SUPPORTED 0x00002000
#define EFI_PXE_ROMID_IMP_MULTI_FRAME_SUPPORTED 0x00001000
#define EFI_PXE_ROMID_IMP_NVDATA_SUPPORT_MASK 0x00000C00
#define EFI_PXE_ROMID_IMP_NVDATA_BULK_WRITABLE 0x00000C00
#define EFI_PXE_ROMID_IMP_NVDATA_SPARSE_WRITABLE 0x00000800
#define EFI_PXE_ROMID_IMP_NVDATA_READ_ONLY 0x00000400
#define EFI_PXE_ROMID_IMP_NVDATA_NOT_AVAILABLE 0x00000000
#define EFI_PXE_ROMID_IMP_STATISTICS_SUPPORTED 0x00000200
#define EFI_PXE_ROMID_IMP_STATION_ADDR_SETTABLE 0x00000100
#define EFI_PXE_ROMID_IMP_PROMISCUOUS_MULTICAST_RX_SUPPORTED 0x00000080
#define EFI_PXE_ROMID_IMP_PROMISCUOUS_RX_SUPPORTED 0x00000040
#define EFI_PXE_ROMID_IMP_BROADCAST_RX_SUPPORTED 0x00000020
#define EFI_PXE_ROMID_IMP_FILTERED_MULTICAST_RX_SUPPORTED 0x00000010
#define EFI_PXE_ROMID_IMP_SOFTWARE_INT_SUPPORTED 0x00000008
#define EFI_PXE_ROMID_IMP_TX_COMPLETE_INT_SUPPORTED 0x00000004
#define EFI_PXE_ROMID_IMP_PACKET_RX_INT_SUPPORTED 0x00000002
#define EFI_PXE_ROMID_IMP_CMD_COMPLETE_INT_SUPPORTED 0x00000001

struct efi_pxe_cdb {
    EFI_PXE_OPCODE OpCode;
    EFI_PXE_OPFLAGS OpFlags;
    uint16_t CPBsize;
    uint16_t DBsize;
    uint64_t CPBaddr;
    uint64_t DBaddr;
    EFI_PXE_STATCODE StatCode;
    EFI_PXE_STATFLAGS StatFlags;
    uint16_t IFnum;
    EFI_PXE_CONTROL Control;
} __attribute__((__packed__));

union efi_pxe_ip_addr {
    struct efi_pxe_ipv6 IPv6;
    EFI_PXE_IPV4 IPv4;
} __attribute__((__packed__));

union efi_pxe_device {
    struct __attribute__((__packed__)) {
        uint32_t BusType;
        uint16_t Bus;
        uint8_t Device;
        uint8_t Function;
    } PCI, PCC;
} __attribute__((__packed__));

/* Bounds for the arrays printed with [n]; the CDB's CPBsize and DBsize give the length used. */
#define EFI_MAX_PCI_CONFIG_LEN 64
#define EFI_MAX_EEPROM_LEN 128
#define EFI_MAX_XMIT_BUFFERS 32
#define EFI_MAX_MCAST_ADDRESS_CNT 8
#define EFI_MAX_XMIT_FRAGMENTS 16

struct efi_pxe_cpb_start_31 {
    uint64_t Delay;
    uint64_t Block;
    uint64_t Virt2Phys;
    uint64_t Mem_IO;
    uint64_t Map_Mem;
    uint64_t UnMap_Mem;
    uint64_t Sync_Mem;
    uint64_t UniqueId;
} __attribute__((__packed__));

struct efi_pxe_cpb_start_30 {
    uint64_t Delay;
    uint64_t Block;
    uint64_t Virt2Phys;
    uint64_t Mem_IO;
} __attribute__((__packed__));

#define EFI_TO_AND_FROM_DEVICE 0
#define EFI_FROM_DEVICE 1
#define EFI_TO_DEVICE 2

/* Mem_IO() access types, which the specification cites but never defines. */
#define EFI_PXE_IO_READ 0
#define EFI_PXE_IO_WRITE 1
#define EFI_PXE_MEM_READ 2
#define EFI_PXE_MEM_WRITE 4

struct efi_pxe_db_get_init_info {
    uint32_t MemoryRequired;
    uint32_t FrameDataLen;
    uint32_t LinkSpeeds[4];
    uint32_t NvCount;
    uint16_t NvWidth;
    uint16_t MediaHeaderLen;
    uint16_t HWaddrLen;
    uint16_t MCastFilterCnt;
    uint16_t TxBufCnt;
    uint16_t TxBufSize;
    uint16_t RxBufCnt;
    uint16_t RxBufSize;
    uint8_t IFtype;
    uint8_t SupportedDuplexModes;
    uint8_t SupportedLoopBackModes;
} __attribute__((__packed__));

#define EFI_PXE_MAX_TXRX_UNIT_ETHER 1500
#define EFI_PXE_HWADDR_LEN_ETHER 0x0006

#define EFI_PXE_DUPLEX_DEFAULT 0
#define EFI_PXE_DUPLEX_ENABLE_FULL_SUPPORTED 1
#define EFI_PXE_DUPLEX_FORCE_FULL_SUPPORTED 2

#define EFI_PXE_LOOPBACK_INTERNAL_SUPPORTED 1
#define EFI_PXE_LOOPBACK_EXTERNAL_SUPPORTED 2

struct efi_pxe_pci_config_info {
    uint32_t BusType;
    uint16_t Bus;
    uint8_t Device;
    uint8_t Function;
    union __attribute__((__packed__)) {
        uint8_t Byte[256];
        uint16_t Word[128];
        uint32_t Dword[64];
    } Config;
} __attribute__((__packed__));

struct efi_pxe_pcc_config_info {
    uint32_t BusType;
    uint16_t Bus;
    uint8_t Device;
    uint8_t Function;
    union __attribute__((__packed__)) {
        uint8_t Byte[256];
        uint16_t Word[128];
        uint32_t Dword[64];
    } Config;
} __attribute__((__packed__));

union efi_pxe_db_get_config_info {
    struct efi_pxe_pci_config_info pci;
    struct efi_pxe_pcc_config_info pcc;
} __attribute__((__packed__));

struct efi_pxe_cpb_initialize {
    uint64_t MemoryAddr;
    uint32_t MemoryLength;
    uint32_t LinkSpeed;
    uint16_t TxBufCnt;
    uint16_t TxBufSize;
    uint16_t RxBufCnt;
    uint16_t RxBufSize;
    uint8_t DuplexMode;
    uint8_t LoopBackMode;
} __attribute__((__packed__));

#define EFI_PXE_DUPLEX_AUTO_DETECT 0x00
#define EFI_PXE_FORCE_FULL_DUPLEX 0x01

#define EFI_PXE_FORCE_HALF_DUPLEX 0x02
#define EFI_PXE_LOOPBACK_NORMAL 0
#define EFI_PXE_LOOPBACK_INTERNAL 1
#define EFI_PXE_LOOPBACK_EXTERNAL 2

struct efi_pxe_db_initialize {
    uint32_t MemoryUsed;
    uint16_t TxBufCnt;
    uint16_t TxBufSize;
    uint16_t RxBufCnt;
    uint16_t RxBufSize;
} __attribute__((__packed__));

struct efi_pxe_cpb_receive_filters {
    struct efi_pxe_mac_addr MCastList[EFI_MAX_MCAST_ADDRESS_CNT];
} __attribute__((__packed__));

struct efi_pxe_db_receive_filters {
    struct efi_pxe_mac_addr MCastList[EFI_MAX_MCAST_ADDRESS_CNT];
} __attribute__((__packed__));

struct efi_pxe_cpb_station_address {
    struct efi_pxe_mac_addr StationAddr;
} __attribute__((__packed__));

struct efi_pxe_db_station_address {
    struct efi_pxe_mac_addr StationAddr;
    struct efi_pxe_mac_addr BroadcastAddr;
    struct efi_pxe_mac_addr PermanentAddr;
} __attribute__((__packed__));

struct efi_pxe_db_statistics {
    uint64_t Supported;
    uint64_t Data[64];
} __attribute__((__packed__));

#define EFI_PXE_STATISTICS_RX_TOTAL_FRAMES 0x00
#define EFI_PXE_STATISTICS_RX_GOOD_FRAMES 0x01
#define EFI_PXE_STATISTICS_RX_UNDERSIZE_FRAMES 0x02
#define EFI_PXE_STATISTICS_RX_OVERSIZE_FRAMES 0x03
#define EFI_PXE_STATISTICS_RX_DROPPED_FRAMES 0x04
#define EFI_PXE_STATISTICS_RX_UNICAST_FRAMES 0x05
#define EFI_PXE_STATISTICS_RX_BROADCAST_FRAMES 0x06
#define EFI_PXE_STATISTICS_RX_MULTICAST_FRAMES 0x07
#define EFI_PXE_STATISTICS_RX_CRC_ERROR_FRAMES 0x08
#define EFI_PXE_STATISTICS_RX_TOTAL_BYTES 0x09

#define EFI_PXE_STATISTICS_TX_TOTAL_FRAMES 0x0A
#define EFI_PXE_STATISTICS_TX_GOOD_FRAMES 0x0B
#define EFI_PXE_STATISTICS_TX_UNDERSIZE_FRAMES 0x0C
#define EFI_PXE_STATISTICS_TX_OVERSIZE_FRAMES 0x0D
#define EFI_PXE_STATISTICS_TX_DROPPED_FRAMES 0x0E
#define EFI_PXE_STATISTICS_TX_UNICAST_FRAMES 0x0F
#define EFI_PXE_STATISTICS_TX_BROADCAST_FRAMES 0x10
#define EFI_PXE_STATISTICS_TX_MULTICAST_FRAMES 0x11
#define EFI_PXE_STATISTICS_TX_CRC_ERROR_FRAMES 0x12
#define EFI_PXE_STATISTICS_TX_TOTAL_BYTES 0x13

#define EFI_PXE_STATISTICS_COLLISIONS 0x14
#define EFI_PXE_STATISTICS_UNSUPPORTED_PROTOCOL 0x15
#define EFI_PXE_STATISTICS_RX_DUPLICATED_FRAMES 0x16
#define EFI_PXE_STATISTICS_RX_DECRYPT_ERROR_FRAMES 0x17
#define EFI_PXE_STATISTICS_TX_ERROR_FRAMES 0x18
#define EFI_PXE_STATISTICS_TX_RETRY_FRAMES 0x19

struct efi_pxe_cpb_mcast_ip_to_mac {
    union efi_pxe_ip_addr IP[1];
} __attribute__((__packed__));

struct efi_pxe_db_mcast_ip_to_mac {
    struct efi_pxe_mac_addr MAC[1];
} __attribute__((__packed__));

struct efi_pxe_cpb_nvdata_sparse {
    struct __attribute__((__packed__)) {
        uint32_t Addr;
        union __attribute__((__packed__)) {
            uint8_t Byte;
            uint16_t Word;
            uint32_t Dword;
        } Data;
    } Item[EFI_MAX_EEPROM_LEN];
} __attribute__((__packed__));

union efi_pxe_cpb_nvdata_bulk {
    uint8_t Byte[EFI_MAX_EEPROM_LEN << 2];
    uint16_t Word[EFI_MAX_EEPROM_LEN << 1];
    uint32_t Dword[EFI_MAX_EEPROM_LEN];
} __attribute__((__packed__));

struct efi_pxe_db_nvdata {
    union __attribute__((__packed__)) {
        uint8_t Byte[EFI_MAX_EEPROM_LEN << 2];
        uint16_t Word[EFI_MAX_EEPROM_LEN << 1];
        uint32_t Dword[EFI_MAX_EEPROM_LEN];
    } Data;
} __attribute__((__packed__));

struct efi_pxe_db_get_status {
    uint32_t RxFrameLen;
    uint32_t reserved;
    uint64_t TxBuffer[EFI_MAX_XMIT_BUFFERS];
} __attribute__((__packed__));

struct efi_pxe_cpb_fill_header {
    struct efi_pxe_mac_addr SrcAddr;
    struct efi_pxe_mac_addr DestAddr;
    uint64_t MediaHeader;
    uint32_t PacketLen;
    uint16_t Protocol;
    uint16_t MediaHeaderLen;
} __attribute__((__packed__));

#define EFI_PXE_PROTOCOL_ETHERNET_IP 0x0800
#define EFI_PXE_PROTOCOL_ETHERNET_ARP 0x0806

struct efi_pxe_cpb_fill_header_fragmented {
    struct efi_pxe_mac_addr SrcAddr;
    struct efi_pxe_mac_addr DestAddr;
    uint32_t PacketLen;
    EFI_PXE_MEDIA_PROTOCOL Protocol;
    uint16_t MediaHeaderLen;
    uint16_t FragCnt;
    uint16_t reserved;
    struct __attribute__((__packed__)) {
        uint64_t FragAddr;
        uint32_t FragLen;
        uint32_t reserved;
    } FragDesc[EFI_MAX_XMIT_FRAGMENTS];
} __attribute__((__packed__));

struct efi_pxe_cpb_transmit {
    uint64_t FrameAddr;
    uint32_t DataLen;
    uint16_t MediaheaderLen;
    uint16_t reserved;
} __attribute__((__packed__));

struct efi_pxe_cpb_transmit_fragments {
    uint32_t FrameLen;
    uint16_t MediaheaderLen;
    uint16_t FragCnt;
    struct __attribute__((__packed__)) {
        uint64_t FragAddr;
        uint32_t FragLen;
        uint32_t reserved;
    } FragDesc[EFI_MAX_XMIT_FRAGMENTS];
} __attribute__((__packed__));

struct efi_pxe_cpb_receive {
    uint64_t BufferAddr;
    uint32_t BufferLen;
    uint32_t reserved;
} __attribute__((__packed__));

struct efi_pxe_db_receive {
    struct efi_pxe_mac_addr SrcAddr;
    struct efi_pxe_mac_addr DestAddr;
    uint32_t FrameLen;
    EFI_PXE_MEDIA_PROTOCOL Protocol;
    uint16_t MediaHeaderLen;
    EFI_PXE_FRAME_TYPE Type;
    uint8_t reserved[7];
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
