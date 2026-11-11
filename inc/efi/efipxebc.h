#ifndef EFI_EFIPXEBC_H_
#define EFI_EFIPXEBC_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PXE_BASE_CODE_PROTOCOL_GUID \
    {0x03C4E603, 0xAC28, 0x11d3, {0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D}}

#define EFI_PXE_BASE_CODE_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_PXE_BASE_CODE_PROTOCOL EFI_PXE_BASE_CODE_PROTOCOL;

#define EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES 8
#define EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES 8

typedef uint16_t EFI_PXE_BASE_CODE_UDP_PORT;

/* Not packed: firmware lays these out naturally, though the specification says byte-packed. */
typedef struct {
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
} EFI_PXE_BASE_CODE_DHCPV4_PACKET;

typedef struct {
    uint32_t MessageType : 8;
    uint32_t TransactionId : 24;
    uint8_t DhcpOptions[1024];
} EFI_PXE_BASE_CODE_DHCPV6_PACKET;

typedef union {
    uint8_t Raw[1472];
    EFI_PXE_BASE_CODE_DHCPV4_PACKET Dhcpv4;
    EFI_PXE_BASE_CODE_DHCPV6_PACKET Dhcpv6;
} EFI_PXE_BASE_CODE_PACKET;

/* Data ends at offset 502; natural alignment makes the size 504. */
typedef struct {
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
} EFI_PXE_BASE_CODE_ICMP_ERROR;

typedef struct {
    uint8_t ErrorCode;
    char ErrorString[127];
} EFI_PXE_BASE_CODE_TFTP_ERROR;

#define EFI_PXE_BASE_CODE_MAX_IPCNT 8

typedef struct {
    uint8_t Filters;
    uint8_t IpCnt;
    uint16_t reserved;
    EFI_IP_ADDRESS IpList[EFI_PXE_BASE_CODE_MAX_IPCNT];
} EFI_PXE_BASE_CODE_IP_FILTER;

#define EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP 0x0001
#define EFI_PXE_BASE_CODE_IP_FILTER_BROADCAST 0x0002
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS 0x0004
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS_MULTICAST 0x0008

typedef struct {
    EFI_IP_ADDRESS IpAddr;
    EFI_MAC_ADDRESS MacAddr;
} EFI_PXE_BASE_CODE_ARP_ENTRY;

typedef struct {
    EFI_IP_ADDRESS IpAddr;
    EFI_IP_ADDRESS SubnetMask;
    EFI_IP_ADDRESS GwAddr;
} EFI_PXE_BASE_CODE_ROUTE_ENTRY;

typedef struct {
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
    EFI_IP_ADDRESS StationIp;
    EFI_IP_ADDRESS SubnetMask;
    EFI_PXE_BASE_CODE_PACKET DhcpDiscover;
    EFI_PXE_BASE_CODE_PACKET DhcpAck;
    EFI_PXE_BASE_CODE_PACKET ProxyOffer;
    EFI_PXE_BASE_CODE_PACKET PxeDiscover;
    EFI_PXE_BASE_CODE_PACKET PxeReply;
    EFI_PXE_BASE_CODE_PACKET PxeBisReply;
    EFI_PXE_BASE_CODE_IP_FILTER IpFilter;
    uint32_t ArpCacheEntries;
    EFI_PXE_BASE_CODE_ARP_ENTRY ArpCache[EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES];
    uint32_t RouteTableEntries;
    EFI_PXE_BASE_CODE_ROUTE_ENTRY RouteTable[EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES];
    EFI_PXE_BASE_CODE_ICMP_ERROR IcmpError;
    EFI_PXE_BASE_CODE_TFTP_ERROR TftpError;
} EFI_PXE_BASE_CODE_MODE;

#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP 0x0001
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT 0x0002
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_IP 0x0004
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT 0x0008
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_USE_FILTER 0x0010
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT 0x0020
#define EFI_DEFAULT_TTL 64
#define EFI_DEFAULT_ToS 0

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_START)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    bool UseIpv6
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_STOP)(EFI_PXE_BASE_CODE_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_DHCP)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
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

typedef struct {
    uint16_t Type;
    uint8_t AcceptAnyResponse;
    uint8_t reserved;
    EFI_IP_ADDRESS IpAddr;
} EFI_PXE_BASE_CODE_SRVLIST;

/* SrvList holds IpCnt entries (printed SrvList[IpCnt]). */
typedef struct {
    uint8_t UseMCast;
    uint8_t UseBCast;
    uint8_t UseUCast;
    uint8_t MustUseList;
    EFI_IP_ADDRESS ServerMCastIp;
    uint16_t IpCnt;
    EFI_PXE_BASE_CODE_SRVLIST SrvList[1];
} EFI_PXE_BASE_CODE_DISCOVER_INFO;

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_DISCOVER)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    uint16_t Type,
    uint16_t *Layer,
    bool UseBis,
    EFI_PXE_BASE_CODE_DISCOVER_INFO *Info
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

typedef struct {
    EFI_IP_ADDRESS MCastIp;
    EFI_PXE_BASE_CODE_UDP_PORT CPort;
    EFI_PXE_BASE_CODE_UDP_PORT SPort;
    uint16_t ListenTimeout;
    uint16_t TransmitTimeout;
} EFI_PXE_BASE_CODE_MTFTP_INFO;

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_MTFTP)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    EFI_PXE_BASE_CODE_TFTP_OPCODE Operation,
    void *BufferPtr,
    bool Overwrite,
    uint64_t *BufferSize,
    size_t *BlockSize,
    EFI_IP_ADDRESS *ServerIp,
    char *Filename,
    EFI_PXE_BASE_CODE_MTFTP_INFO *Info,
    bool DontUseBuffer
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_UDP_WRITE)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    uint16_t OpFlags,
    EFI_IP_ADDRESS *DestIp,
    EFI_PXE_BASE_CODE_UDP_PORT *DestPort,
    EFI_IP_ADDRESS *GatewayIp,
    EFI_IP_ADDRESS *SrcIp,
    EFI_PXE_BASE_CODE_UDP_PORT *SrcPort,
    size_t *HeaderSize,
    void *HeaderPtr,
    size_t *BufferSize,
    void *BufferPtr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_UDP_READ)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    uint16_t OpFlags,
    EFI_IP_ADDRESS *DestIp,
    EFI_PXE_BASE_CODE_UDP_PORT *DestPort,
    EFI_IP_ADDRESS *SrcIp,
    EFI_PXE_BASE_CODE_UDP_PORT *SrcPort,
    size_t *HeaderSize,
    void *HeaderPtr,
    size_t *BufferSize,
    void *BufferPtr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_IP_FILTER)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    EFI_PXE_BASE_CODE_IP_FILTER *NewFilter
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_ARP)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    EFI_IP_ADDRESS *IpAddr,
    EFI_MAC_ADDRESS *MacAddr
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_PARAMETERS)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    bool *NewAutoArp,
    bool *NewSendGUID,
    uint8_t *NewTTL,
    uint8_t *NewToS,
    bool *NewMakeCallback
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_STATION_IP)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    EFI_IP_ADDRESS *NewStationIp,
    EFI_IP_ADDRESS *NewSubnetMask
);

typedef EFI_STATUS (EFI_API *EFI_PXE_BASE_CODE_SET_PACKETS)(
    EFI_PXE_BASE_CODE_PROTOCOL *This,
    bool *NewDhcpDiscoverValid,
    bool *NewDhcpAckReceived,
    bool *NewProxyOfferReceived,
    bool *NewPxeDiscoverValid,
    bool *NewPxeReplyReceived,
    bool *NewPxeBisReplyReceived,
    EFI_PXE_BASE_CODE_PACKET *NewDhcpDiscover,
    EFI_PXE_BASE_CODE_PACKET *NewDhcpAck,
    EFI_PXE_BASE_CODE_PACKET *NewProxyOffer,
    EFI_PXE_BASE_CODE_PACKET *NewPxeDiscover,
    EFI_PXE_BASE_CODE_PACKET *NewPxeReply,
    EFI_PXE_BASE_CODE_PACKET *NewPxeBisReply
);

struct _EFI_PXE_BASE_CODE_PROTOCOL {
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
    EFI_PXE_BASE_CODE_MODE *Mode;
};

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID \
    {0x245DCA21, 0xFB7B, 0x11d3, {0x8F, 0x01, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL;

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
    EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL *This,
    EFI_PXE_BASE_CODE_FUNCTION Function,
    bool Received,
    uint32_t PacketLen,
    EFI_PXE_BASE_CODE_PACKET *Packet
);

struct _EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL {
    uint64_t Revision;
    EFI_PXE_CALLBACK Callback;
};

#ifdef __cplusplus
}
#endif

#endif
