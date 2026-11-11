#ifndef EFI_EFIIP_H_
#define EFI_EFIIP_H_

#include "efiapi.h"
#include "efinet.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_IP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xc51711e7, 0xb4bf, 0x404a, {0xbf, 0xb8, 0x0a, 0x04, 0x8e, 0xf1, 0xff, 0xe4}}

#define EFI_IP4_PROTOCOL_GUID \
    {0x41d94cd2, 0x35b6, 0x455a, {0x82, 0x58, 0xd4, 0xe5, 0x13, 0x34, 0xaa, 0xdd}}

typedef struct _EFI_IP4_PROTOCOL EFI_IP4_PROTOCOL;

typedef struct {
    uint8_t DefaultProtocol;
    uint8_t AcceptAnyProtocol;
    uint8_t AcceptIcmpErrors;
    uint8_t AcceptBroadcast;
    uint8_t AcceptPromiscuous;
    uint8_t UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    uint8_t DoNotFragment;
    uint8_t RawData;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SubnetAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_IPv4_ADDRESS GatewayAddress;
} EFI_IP4_ROUTE_TABLE;

typedef struct {
    uint8_t Type;
    uint8_t Code;
} EFI_IP4_ICMP_TYPE;

/* RouteTable points to RouteCount entries, as described; the structure prints it by value. */
typedef struct {
    uint8_t IsStarted;
    uint32_t MaxPacketSize;
    EFI_IP4_CONFIG_DATA ConfigData;
    uint8_t IsConfigured;
    uint32_t GroupCount;
    EFI_IPv4_ADDRESS *GroupTable;
    uint32_t RouteCount;
    EFI_IP4_ROUTE_TABLE *RouteTable;
    uint32_t IcmpTypeCount;
    EFI_IP4_ICMP_TYPE *IcmpTypeList;
} EFI_IP4_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_IP4_GET_MODE_DATA)(
    EFI_IP4_PROTOCOL *This,
    EFI_IP4_MODE_DATA *Ip4ModeData,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData,
    EFI_SIMPLE_NETWORK_MODE *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIGURE)(
    EFI_IP4_PROTOCOL *This,
    EFI_IP4_CONFIG_DATA *IpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_IP4_GROUPS)(
    EFI_IP4_PROTOCOL *This,
    bool JoinFlag,
    EFI_IPv4_ADDRESS *GroupAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP4_ROUTES)(
    EFI_IP4_PROTOCOL *This,
    bool DeleteRoute,
    EFI_IPv4_ADDRESS *SubnetAddress,
    EFI_IPv4_ADDRESS *SubnetMask,
    EFI_IPv4_ADDRESS *GatewayAddress
);

typedef struct __attribute__((__packed__)) {
    uint8_t HeaderLength:4;
    uint8_t Version:4;
    uint8_t TypeOfService;
    uint16_t TotalLength;
    uint16_t Identification;
    uint16_t Fragmentation;
    uint8_t TimeToLive;
    uint8_t Protocol;
    uint16_t Checksum;
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS DestinationAddress;
} EFI_IP4_HEADER;

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_IP4_FRAGMENT_DATA;

typedef struct {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    uint32_t HeaderLength;
    EFI_IP4_HEADER *Header;
    uint32_t OptionsLength;
    void *Options;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_IP4_FRAGMENT_DATA FragmentTable[1];
} EFI_IP4_RECEIVE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS GatewayAddress;
    uint8_t Protocol;
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    uint8_t DoNotFragment;
} EFI_IP4_OVERRIDE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS DestinationAddress;
    EFI_IP4_OVERRIDE_DATA *OverrideData;
    uint32_t OptionsLength;
    void *OptionsBuffer;
    uint32_t TotalDataLength;
    uint32_t FragmentCount;
    EFI_IP4_FRAGMENT_DATA FragmentTable[1];
} EFI_IP4_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        EFI_IP4_RECEIVE_DATA *RxData;
        EFI_IP4_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_IP4_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_IP4_TRANSMIT)(
    EFI_IP4_PROTOCOL *This,
    EFI_IP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_RECEIVE)(
    EFI_IP4_PROTOCOL *This,
    EFI_IP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CANCEL)(
    EFI_IP4_PROTOCOL *This,
    EFI_IP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_POLL)(EFI_IP4_PROTOCOL *This);

struct _EFI_IP4_PROTOCOL {
    EFI_IP4_GET_MODE_DATA GetModeData;
    EFI_IP4_CONFIGURE Configure;
    EFI_IP4_GROUPS Groups;
    EFI_IP4_ROUTES Routes;
    EFI_IP4_TRANSMIT Transmit;
    EFI_IP4_RECEIVE Receive;
    EFI_IP4_CANCEL Cancel;
    EFI_IP4_POLL Poll;
};

#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0xec835dd3, 0xfe0f, 0x617b, {0xa6, 0x21, 0xb3, 0x50, 0xc3, 0xe1, 0x33, 0x88}}

#define EFI_IP6_PROTOCOL_GUID \
    {0x2c8759d5, 0x5c2d, 0x66ef, {0x92, 0x5f, 0xb6, 0x6c, 0x10, 0x19, 0x57, 0xe2}}

typedef struct _EFI_IP6_PROTOCOL EFI_IP6_PROTOCOL;

typedef struct {
    uint8_t DefaultProtocol;
    uint8_t AcceptAnyProtocol;
    uint8_t AcceptIcmpErrors;
    uint8_t AcceptPromiscuous;
    EFI_IPv6_ADDRESS DestinationAddress;
    EFI_IPv6_ADDRESS StationAddress;
    uint8_t TrafficClass;
    uint8_t HopLimit;
    uint32_t FlowLabel;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
} EFI_IP6_CONFIG_DATA;

typedef struct {
    EFI_IPv6_ADDRESS Address;
    uint8_t PrefixLength;
} EFI_IP6_ADDRESS_INFO;

typedef struct {
    EFI_IPv6_ADDRESS Gateway;
    EFI_IPv6_ADDRESS Destination;
    uint8_t PrefixLength;
} EFI_IP6_ROUTE_TABLE;

typedef enum {
    EfiNeighborInComplete,
    EfiNeighborReachable,
    EfiNeighborStale,
    EfiNeighborDelay,
    EfiNeighborProbe
} EFI_IP6_NEIGHBOR_STATE;

typedef struct {
    EFI_IPv6_ADDRESS Neighbor;
    EFI_MAC_ADDRESS LinkAddress;
    EFI_IP6_NEIGHBOR_STATE State;
} EFI_IP6_NEIGHBOR_CACHE;

typedef struct {
    uint8_t Type;
    uint8_t Code;
} EFI_IP6_ICMP_TYPE;

#define EFI_ICMP_V6_DEST_UNREACHABLE 0x1
#define EFI_ICMP_V6_PACKET_TOO_BIG 0x2
#define EFI_ICMP_V6_TIME_EXCEEDED 0x3
#define EFI_ICMP_V6_PARAMETER_PROBLEM 0x4

#define EFI_ICMP_V6_ECHO_REQUEST 0x80
#define EFI_ICMP_V6_ECHO_REPLY 0x81
#define EFI_ICMP_V6_LISTENER_QUERY 0x82
#define EFI_ICMP_V6_LISTENER_REPORT 0x83
#define EFI_ICMP_V6_LISTENER_DONE 0x84
#define EFI_ICMP_V6_ROUTER_SOLICIT 0x85
#define EFI_ICMP_V6_ROUTER_ADVERTISE 0x86
#define EFI_ICMP_V6_NEIGHBOR_SOLICIT 0x87
#define EFI_ICMP_V6_NEIGHBOR_ADVERTISE 0x88
#define EFI_ICMP_V6_REDIRECT 0x89
#define EFI_ICMP_V6_LISTENER_REPORT_2 0x8F

#define EFI_ICMP_V6_NO_ROUTE_TO_DEST 0x0
#define EFI_ICMP_V6_COMM_PROHIBITED 0x1
#define EFI_ICMP_V6_BEYOND_SCOPE 0x2
#define EFI_ICMP_V6_ADDR_UNREACHABLE 0x3
#define EFI_ICMP_V6_PORT_UNREACHABLE 0x4
#define EFI_ICMP_V6_SOURCE_ADDR_FAILED 0x5
#define EFI_ICMP_V6_ROUTE_REJECTED 0x6

#define EFI_ICMP_V6_TIMEOUT_HOP_LIMIT 0x0
#define EFI_ICMP_V6_TIMEOUT_REASSEMBLE 0x1

#define EFI_ICMP_V6_ERRONEOUS_HEADER 0x0
#define EFI_ICMP_V6_UNRECOGNIZE_NEXT_HDR 0x1
#define EFI_ICMP_V6_UNRECOGNIZE_OPTION 0x2

typedef struct {
    uint8_t IsStarted;
    uint32_t MaxPacketSize;
    EFI_IP6_CONFIG_DATA ConfigData;
    uint8_t IsConfigured;
    uint32_t AddressCount;
    EFI_IP6_ADDRESS_INFO *AddressList;
    uint32_t GroupCount;
    EFI_IPv6_ADDRESS *GroupTable;
    uint32_t RouteCount;
    EFI_IP6_ROUTE_TABLE *RouteTable;
    uint32_t NeighborCount;
    EFI_IP6_NEIGHBOR_CACHE *NeighborCache;
    uint32_t PrefixCount;
    EFI_IP6_ADDRESS_INFO *PrefixTable;
    uint32_t IcmpTypeCount;
    EFI_IP6_ICMP_TYPE *IcmpTypeList;
} EFI_IP6_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_IP6_GET_MODE_DATA)(
    EFI_IP6_PROTOCOL *This,
    EFI_IP6_MODE_DATA *Ip6ModeData,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData,
    EFI_SIMPLE_NETWORK_MODE *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIGURE)(
    EFI_IP6_PROTOCOL *This,
    EFI_IP6_CONFIG_DATA *Ip6ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_IP6_GROUPS)(
    EFI_IP6_PROTOCOL *This,
    bool JoinFlag,
    EFI_IPv6_ADDRESS *GroupAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP6_ROUTES)(
    EFI_IP6_PROTOCOL *This,
    bool DeleteRoute,
    EFI_IPv6_ADDRESS *Destination,
    uint8_t PrefixLength,
    EFI_IPv6_ADDRESS *GatewayAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP6_NEIGHBORS)(
    EFI_IP6_PROTOCOL *This,
    bool DeleteFlag,
    EFI_IPv6_ADDRESS *TargetIp6Address,
    EFI_MAC_ADDRESS *TargetLinkAddress,
    uint32_t Timeout,
    bool Override
);

typedef struct __attribute__((__packed__)) _EFI_IP6_HEADER {
    uint8_t TrafficClassH:4;
    uint8_t Version:4;
    uint8_t FlowLabelH:4;
    uint8_t TrafficClassL:4;
    uint16_t FlowLabelL;
    uint16_t PayloadLength;
    uint8_t NextHeader;
    uint8_t HopLimit;
    EFI_IPv6_ADDRESS SourceAddress;
    EFI_IPv6_ADDRESS DestinationAddress;
} EFI_IP6_HEADER;

typedef struct _EFI_IP6_FRAGMENT_DATA {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_IP6_FRAGMENT_DATA;

typedef struct _EFI_IP6_RECEIVE_DATA {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    uint32_t HeaderLength;
    EFI_IP6_HEADER *Header;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_IP6_FRAGMENT_DATA FragmentTable[1];
} EFI_IP6_RECEIVE_DATA;

typedef struct _EFI_IP6_OVERRIDE_DATA {
    uint8_t Protocol;
    uint8_t HopLimit;
    uint32_t FlowLabel;
} EFI_IP6_OVERRIDE_DATA;

typedef struct _EFI_IP6_TRANSMIT_DATA {
    EFI_IPv6_ADDRESS DestinationAddress;
    EFI_IP6_OVERRIDE_DATA *OverrideData;
    uint32_t ExtHdrsLength;
    void *ExtHdrs;
    uint8_t NextHeader;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_IP6_FRAGMENT_DATA FragmentTable[1];
} EFI_IP6_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        EFI_IP6_RECEIVE_DATA *RxData;
        EFI_IP6_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_IP6_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_IP6_TRANSMIT)(
    EFI_IP6_PROTOCOL *This,
    EFI_IP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_RECEIVE)(
    EFI_IP6_PROTOCOL *This,
    EFI_IP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CANCEL)(
    EFI_IP6_PROTOCOL *This,
    EFI_IP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_POLL)(EFI_IP6_PROTOCOL *This);

struct _EFI_IP6_PROTOCOL {
    EFI_IP6_GET_MODE_DATA GetModeData;
    EFI_IP6_CONFIGURE Configure;
    EFI_IP6_GROUPS Groups;
    EFI_IP6_ROUTES Routes;
    EFI_IP6_NEIGHBORS Neighbors;
    EFI_IP6_TRANSMIT Transmit;
    EFI_IP6_RECEIVE Receive;
    EFI_IP6_CANCEL Cancel;
    EFI_IP6_POLL Poll;
};

#ifdef __cplusplus
}
#endif

#endif
