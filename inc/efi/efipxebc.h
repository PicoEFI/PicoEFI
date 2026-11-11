#ifndef EFI_EFIPXEBC_H_
#define EFI_EFIPXEBC_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PXE_BASE_CODE_PROTOCOL_GUID \
    {0x03C4E603, 0xAC28, 0x11d3, {0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D}}

#define EFI_PXE_BASE_CODE_PROTOCOL_REVISION 0x00010000

struct efi_pxe_base_code_protocol;

#define EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES 8
#define EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES 8

typedef uint16_t EFI_PXE_BASE_CODE_UDP_PORT;

/* Not packed: firmware lays these out naturally, though the specification says byte-packed. */
struct efi_pxe_base_code_dhcpv4_packet {
    uint8_t BootpOpcode;
    uint8_t BootpHwType;
    uint8_t BootpHwAddrLen;
    uint8_t BootpGateHops;
    uint32_t BootpIdent;
    uint16_t BootpSeconds;
    uint16_t BootpFlags;
    uint8_t BootpCiAddr[4];
    uint8_t BootpYiAddr[4];
    uint8_t BootpSiAddr[4];
    uint8_t BootpGiAddr[4];
    uint8_t BootpHwAddr[16];
    uint8_t BootpSrvName[64];
    uint8_t BootpBootFile[128];
    uint32_t DhcpMagik;
    uint8_t DhcpOptions[56];
};

struct efi_pxe_base_code_dhcpv6_packet {
    uint32_t MessageType : 8;
    uint32_t TransactionId : 24;
    uint8_t DhcpOptions[1024];
};

union efi_pxe_base_code_packet {
    uint8_t Raw[1472];
    struct efi_pxe_base_code_dhcpv4_packet Dhcpv4;
    struct efi_pxe_base_code_dhcpv6_packet Dhcpv6;
};

/* Data ends at offset 502; natural alignment makes the size 504. */
struct efi_pxe_base_code_icmp_error {
    uint8_t Type;
    uint8_t Code;
    uint16_t Checksum;
    union {
        uint32_t reserved;
        uint32_t Mtu;
        uint32_t Pointer;
        struct {
            uint16_t Identifier;
            uint16_t Sequence;
        } Echo;
    } u;
    uint8_t Data[494];
};

struct efi_pxe_base_code_tftp_error {
    uint8_t ErrorCode;
    char ErrorString[127];
};

#define EFI_PXE_BASE_CODE_MAX_IPCNT 8

struct efi_pxe_base_code_ip_filter {
    uint8_t Filters;
    uint8_t IpCnt;
    uint16_t reserved;
    union efi_ip_address IpList[EFI_PXE_BASE_CODE_MAX_IPCNT];
};

#define EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP 0x0001
#define EFI_PXE_BASE_CODE_IP_FILTER_BROADCAST 0x0002
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS 0x0004
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS_MULTICAST 0x0008

struct efi_pxe_base_code_arp_entry {
    union efi_ip_address IpAddr;
    struct efi_mac_address MacAddr;
};

struct efi_pxe_base_code_route_entry {
    union efi_ip_address IpAddr;
    union efi_ip_address SubnetMask;
    union efi_ip_address GwAddr;
};

struct efi_pxe_base_code_mode {
    uint8_t Started;
    uint8_t Ipv6Available;
    uint8_t Ipv6Supported;
    uint8_t UsingIpv6;
    uint8_t BisSupported;
    uint8_t BisDetected;
    uint8_t AutoArp;
    uint8_t SendGUID;
    uint8_t DhcpDiscoverValid;
    uint8_t DhcpAckReceived;
    uint8_t ProxyOfferReceived;
    uint8_t PxeDiscoverValid;
    uint8_t PxeReplyReceived;
    uint8_t PxeBisReplyReceived;
    uint8_t IcmpErrorReceived;
    uint8_t TftpErrorReceived;
    uint8_t MakeCallbacks;
    uint8_t TTL;
    uint8_t ToS;
    union efi_ip_address StationIp;
    union efi_ip_address SubnetMask;
    union efi_pxe_base_code_packet DhcpDiscover;
    union efi_pxe_base_code_packet DhcpAck;
    union efi_pxe_base_code_packet ProxyOffer;
    union efi_pxe_base_code_packet PxeDiscover;
    union efi_pxe_base_code_packet PxeReply;
    union efi_pxe_base_code_packet PxeBisReply;
    struct efi_pxe_base_code_ip_filter IpFilter;
    uint32_t ArpCacheEntries;
    struct efi_pxe_base_code_arp_entry ArpCache[EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES];
    uint32_t RouteTableEntries;
    struct efi_pxe_base_code_route_entry RouteTable[EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES];
    struct efi_pxe_base_code_icmp_error IcmpError;
    struct efi_pxe_base_code_tftp_error TftpError;
};

#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP 0x0001
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT 0x0002
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_IP 0x0004
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT 0x0008
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_USE_FILTER 0x0010
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT 0x0020
#define EFI_DEFAULT_TTL 64
#define EFI_DEFAULT_ToS 0

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_START)(
    struct efi_pxe_base_code_protocol *This,
    bool UseIpv6
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_STOP)(struct efi_pxe_base_code_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_DHCP)(
    struct efi_pxe_base_code_protocol *This,
    bool SortOffers
);

#define EFI_PXE_BASE_CODE_BOOT_TYPE_BOOTSTRAP 0
#define EFI_PXE_BASE_CODE_BOOT_TYPE_MS_WINNT_RIS 1
#define EFI_PXE_BASE_CODE_BOOT_TYPE_INTEL_LCM 2
#define EFI_PXE_BASE_CODE_BOOT_TYPE_DOSUNDI 3
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NEC_ESMPRO 4
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_WSoD 5
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_LCCM 6
#define EFI_PXE_BASE_CODE_BOOT_TYPE_CA_UNICENTER_TNG 7
#define EFI_PXE_BASE_CODE_BOOT_TYPE_HP_OPENVIEW 8
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_9 9
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_10 10
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_11 11
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NOT_USED_12 12
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_INSTALL 13
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_BOOT 14
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REMBO 15
#define EFI_PXE_BASE_CODE_BOOT_TYPE_BEOBOOT 16
#define EFI_PXE_BASE_CODE_BOOT_TYPE_PXETEST 65535

#define EFI_PXE_BASE_CODE_BOOT_LAYER_MASK 0x7FFF
#define EFI_PXE_BASE_CODE_BOOT_LAYER_INITIAL 0x0000

struct efi_pxe_base_code_srvlist {
    uint16_t Type;
    uint8_t AcceptAnyResponse;
    uint8_t reserved;
    union efi_ip_address IpAddr;
};

/* SrvList holds IpCnt entries (printed SrvList[IpCnt]). */
struct efi_pxe_base_code_discover_info {
    uint8_t UseMCast;
    uint8_t UseBCast;
    uint8_t UseUCast;
    uint8_t MustUseList;
    union efi_ip_address ServerMCastIp;
    uint16_t IpCnt;
    struct efi_pxe_base_code_srvlist SrvList[1];
};

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_DISCOVER)(
    struct efi_pxe_base_code_protocol *This,
    uint16_t Type,
    uint16_t *Layer,
    bool UseBis,
    struct efi_pxe_base_code_discover_info *Info
);

typedef enum {
    EFI_PXE_BASE_CODE_TFTP_FIRST,
    EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_TFTP_READ_FILE,
    EFI_PXE_BASE_CODE_TFTP_WRITE_FILE,
    EFI_PXE_BASE_CODE_TFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE,
    EFI_PXE_BASE_CODE_MTFTP_READ_FILE,
    EFI_PXE_BASE_CODE_MTFTP_READ_DIRECTORY,
    EFI_PXE_BASE_CODE_MTFTP_LAST
} EFI_PXE_BASE_CODE_TFTP_OPCODE;

struct efi_pxe_base_code_mtftp_info {
    union efi_ip_address MCastIp;
    EFI_PXE_BASE_CODE_UDP_PORT CPort;
    EFI_PXE_BASE_CODE_UDP_PORT SPort;
    uint16_t ListenTimeout;
    uint16_t TransmitTimeout;
};

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_MTFTP)(
    struct efi_pxe_base_code_protocol *This,
    EFI_PXE_BASE_CODE_TFTP_OPCODE Operation,
    void *BufferPtr,
    bool Overwrite,
    uint64_t *BufferSize,
    size_t *BlockSize,
    union efi_ip_address *ServerIp,
    char *Filename,
    struct efi_pxe_base_code_mtftp_info *Info,
    bool DontUseBuffer
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_UDP_WRITE)(
    struct efi_pxe_base_code_protocol *This,
    uint16_t OpFlags,
    union efi_ip_address *DestIp,
    EFI_PXE_BASE_CODE_UDP_PORT *DestPort,
    union efi_ip_address *GatewayIp,
    union efi_ip_address *SrcIp,
    EFI_PXE_BASE_CODE_UDP_PORT *SrcPort,
    size_t *HeaderSize,
    void *HeaderPtr,
    size_t *BufferSize,
    void *BufferPtr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_UDP_READ)(
    struct efi_pxe_base_code_protocol *This,
    uint16_t OpFlags,
    union efi_ip_address *DestIp,
    EFI_PXE_BASE_CODE_UDP_PORT *DestPort,
    union efi_ip_address *SrcIp,
    EFI_PXE_BASE_CODE_UDP_PORT *SrcPort,
    size_t *HeaderSize,
    void *HeaderPtr,
    size_t *BufferSize,
    void *BufferPtr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_IP_FILTER)(
    struct efi_pxe_base_code_protocol *This,
    struct efi_pxe_base_code_ip_filter *NewFilter
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_ARP)(
    struct efi_pxe_base_code_protocol *This,
    union efi_ip_address *IpAddr,
    struct efi_mac_address *MacAddr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_PARAMETERS)(
    struct efi_pxe_base_code_protocol *This,
    bool *NewAutoArp,
    bool *NewSendGUID,
    uint8_t *NewTTL,
    uint8_t *NewToS,
    bool *NewMakeCallback
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_STATION_IP)(
    struct efi_pxe_base_code_protocol *This,
    union efi_ip_address *NewStationIp,
    union efi_ip_address *NewSubnetMask
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_PACKETS)(
    struct efi_pxe_base_code_protocol *This,
    bool *NewDhcpDiscoverValid,
    bool *NewDhcpAckReceived,
    bool *NewProxyOfferReceived,
    bool *NewPxeDiscoverValid,
    bool *NewPxeReplyReceived,
    bool *NewPxeBisReplyReceived,
    union efi_pxe_base_code_packet *NewDhcpDiscover,
    union efi_pxe_base_code_packet *NewDhcpAck,
    union efi_pxe_base_code_packet *NewProxyOffer,
    union efi_pxe_base_code_packet *NewPxeDiscover,
    union efi_pxe_base_code_packet *NewPxeReply,
    union efi_pxe_base_code_packet *NewPxeBisReply
);

struct efi_pxe_base_code_protocol {
    uint64_t Revision;
    EFI_PXE_BASE_CODE_START Start;
    EFI_PXE_BASE_CODE_STOP Stop;
    EFI_PXE_BASE_CODE_DHCP Dhcp;
    EFI_PXE_BASE_CODE_DISCOVER Discover;
    EFI_PXE_BASE_CODE_MTFTP Mtftp;
    EFI_PXE_BASE_CODE_UDP_WRITE UdpWrite;
    EFI_PXE_BASE_CODE_UDP_READ UdpRead;
    EFI_PXE_BASE_CODE_SET_IP_FILTER SetIpFilter;
    EFI_PXE_BASE_CODE_ARP Arp;
    EFI_PXE_BASE_CODE_SET_PARAMETERS SetParameters;
    EFI_PXE_BASE_CODE_SET_STATION_IP SetStationIp;
    EFI_PXE_BASE_CODE_SET_PACKETS SetPackets;
    struct efi_pxe_base_code_mode *Mode;
};

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID \
    {0x245DCA21, 0xFB7B, 0x11d3, {0x8F, 0x01, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION 0x00010000

struct efi_pxe_base_code_callback_protocol;

typedef enum {
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_FIRST,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_CONTINUE,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_ABORT,
    EFI_PXE_BASE_CODE_CALLBACK_STATUS_LAST
} EFI_PXE_BASE_CODE_CALLBACK_STATUS;

typedef enum {
    EFI_PXE_BASE_CODE_FUNCTION_FIRST,
    EFI_PXE_BASE_CODE_FUNCTION_DHCP,
    EFI_PXE_BASE_CODE_FUNCTION_DISCOVER,
    EFI_PXE_BASE_CODE_FUNCTION_MTFTP,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_WRITE,
    EFI_PXE_BASE_CODE_FUNCTION_UDP_READ,
    EFI_PXE_BASE_CODE_FUNCTION_ARP,
    EFI_PXE_BASE_CODE_FUNCTION_IGMP,
    EFI_PXE_BASE_CODE_PXE_FUNCTION_LAST
} EFI_PXE_BASE_CODE_FUNCTION;

typedef EFI_PXE_BASE_CODE_CALLBACK_STATUS (EFI_API *EFI_PXE_CALLBACK)(
    struct efi_pxe_base_code_callback_protocol *This,
    EFI_PXE_BASE_CODE_FUNCTION Function,
    bool Received,
    uint32_t PacketLen,
    union efi_pxe_base_code_packet *Packet
);

struct efi_pxe_base_code_callback_protocol {
    uint64_t Revision;
    EFI_PXE_CALLBACK Callback;
};

#ifdef __cplusplus
}
#endif

#endif
