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
    EFI_UINT8 DefaultProtocol;
    EFI_BOOLEAN AcceptAnyProtocol;
    EFI_BOOLEAN AcceptIcmpErrors;
    EFI_BOOLEAN AcceptBroadcast;
    EFI_BOOLEAN AcceptPromiscuous;
    EFI_BOOLEAN UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_UINT8 TypeOfService;
    EFI_UINT8 TimeToLive;
    EFI_BOOLEAN DoNotFragment;
    EFI_BOOLEAN RawData;
    EFI_UINT32 ReceiveTimeout;
    EFI_UINT32 TransmitTimeout;
} EFI_IP4_CONFIG_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SubnetAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_IPv4_ADDRESS GatewayAddress;
} EFI_IP4_ROUTE_TABLE;

typedef struct {
    EFI_UINT8 Type;
    EFI_UINT8 Code;
} EFI_IP4_ICMP_TYPE;

/* RouteTable points to RouteCount entries, as described; the structure prints it by value. */
typedef struct {
    EFI_BOOLEAN IsStarted;
    EFI_UINT32 MaxPacketSize;
    EFI_IP4_CONFIG_DATA ConfigData;
    EFI_BOOLEAN IsConfigured;
    EFI_UINT32 GroupCount;
    EFI_IPv4_ADDRESS *GroupTable;
    EFI_UINT32 RouteCount;
    EFI_IP4_ROUTE_TABLE *RouteTable;
    EFI_UINT32 IcmpTypeCount;
    EFI_IP4_ICMP_TYPE *IcmpTypeList;
} EFI_IP4_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_IP4_GET_MODE_DATA)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_OUT EFI_IP4_MODE_DATA *Ip4ModeData EFI_OPTIONAL,
    EFI_OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData EFI_OPTIONAL,
    EFI_OUT EFI_SIMPLE_NETWORK_MODE *SnpModeData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIGURE)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_IP4_CONFIG_DATA *IpConfigData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP4_GROUPS)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN JoinFlag,
    EFI_IN EFI_IPv4_ADDRESS *GroupAddress EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP4_ROUTES)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteRoute,
    EFI_IN EFI_IPv4_ADDRESS *SubnetAddress,
    EFI_IN EFI_IPv4_ADDRESS *SubnetMask,
    EFI_IN EFI_IPv4_ADDRESS *GatewayAddress
);

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 HeaderLength:4;
    EFI_UINT8 Version:4;
    EFI_UINT8 TypeOfService;
    EFI_UINT16 TotalLength;
    EFI_UINT16 Identification;
    EFI_UINT16 Fragmentation;
    EFI_UINT8 TimeToLive;
    EFI_UINT8 Protocol;
    EFI_UINT16 Checksum;
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS DestinationAddress;
} EFI_IP4_HEADER;

typedef struct {
    EFI_UINT32 FragmentLength;
    EFI_VOID *FragmentBuffer;
} EFI_IP4_FRAGMENT_DATA;

typedef struct {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    EFI_UINT32 HeaderLength;
    EFI_IP4_HEADER *Header;
    EFI_UINT32 OptionsLength;
    EFI_VOID *Options;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_IP4_FRAGMENT_DATA FragmentTable[1];
} EFI_IP4_RECEIVE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS SourceAddress;
    EFI_IPv4_ADDRESS GatewayAddress;
    EFI_UINT8 Protocol;
    EFI_UINT8 TypeOfService;
    EFI_UINT8 TimeToLive;
    EFI_BOOLEAN DoNotFragment;
} EFI_IP4_OVERRIDE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS DestinationAddress;
    EFI_IP4_OVERRIDE_DATA *OverrideData;
    EFI_UINT32 OptionsLength;
    EFI_VOID *OptionsBuffer;
    EFI_UINT32 TotalDataLength;
    EFI_UINT32 FragmentCount;
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
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_IP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_RECEIVE)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_IP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CANCEL)(
    EFI_IN EFI_IP4_PROTOCOL *This,
    EFI_IN EFI_IP4_COMPLETION_TOKEN *Token EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP4_POLL)(EFI_IN EFI_IP4_PROTOCOL *This);

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
    EFI_UINT8 DefaultProtocol;
    EFI_BOOLEAN AcceptAnyProtocol;
    EFI_BOOLEAN AcceptIcmpErrors;
    EFI_BOOLEAN AcceptPromiscuous;
    EFI_IPv6_ADDRESS DestinationAddress;
    EFI_IPv6_ADDRESS StationAddress;
    EFI_UINT8 TrafficClass;
    EFI_UINT8 HopLimit;
    EFI_UINT32 FlowLabel;
    EFI_UINT32 ReceiveTimeout;
    EFI_UINT32 TransmitTimeout;
} EFI_IP6_CONFIG_DATA;

typedef struct {
    EFI_IPv6_ADDRESS Address;
    EFI_UINT8 PrefixLength;
} EFI_IP6_ADDRESS_INFO;

typedef struct {
    EFI_IPv6_ADDRESS Gateway;
    EFI_IPv6_ADDRESS Destination;
    EFI_UINT8 PrefixLength;
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
    EFI_UINT8 Type;
    EFI_UINT8 Code;
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
    EFI_BOOLEAN IsStarted;
    EFI_UINT32 MaxPacketSize;
    EFI_IP6_CONFIG_DATA ConfigData;
    EFI_BOOLEAN IsConfigured;
    EFI_UINT32 AddressCount;
    EFI_IP6_ADDRESS_INFO *AddressList;
    EFI_UINT32 GroupCount;
    EFI_IPv6_ADDRESS *GroupTable;
    EFI_UINT32 RouteCount;
    EFI_IP6_ROUTE_TABLE *RouteTable;
    EFI_UINT32 NeighborCount;
    EFI_IP6_NEIGHBOR_CACHE *NeighborCache;
    EFI_UINT32 PrefixCount;
    EFI_IP6_ADDRESS_INFO *PrefixTable;
    EFI_UINT32 IcmpTypeCount;
    EFI_IP6_ICMP_TYPE *IcmpTypeList;
} EFI_IP6_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_IP6_GET_MODE_DATA)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_OUT EFI_IP6_MODE_DATA *Ip6ModeData EFI_OPTIONAL,
    EFI_OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData EFI_OPTIONAL,
    EFI_OUT EFI_SIMPLE_NETWORK_MODE *SnpModeData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIGURE)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_IP6_CONFIG_DATA *Ip6ConfigData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP6_GROUPS)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN JoinFlag,
    EFI_IN EFI_IPv6_ADDRESS *GroupAddress EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP6_ROUTES)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteRoute,
    EFI_IN EFI_IPv6_ADDRESS *Destination EFI_OPTIONAL,
    EFI_IN EFI_UINT8 PrefixLength,
    EFI_IN EFI_IPv6_ADDRESS *GatewayAddress EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP6_NEIGHBORS)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteFlag,
    EFI_IN EFI_IPv6_ADDRESS *TargetIp6Address,
    EFI_IN EFI_MAC_ADDRESS *TargetLinkAddress EFI_OPTIONAL,
    EFI_IN EFI_UINT32 Timeout,
    EFI_IN EFI_BOOLEAN Override
);

typedef struct __attribute__((__packed__)) _EFI_IP6_HEADER {
    EFI_UINT8 TrafficClassH:4;
    EFI_UINT8 Version:4;
    EFI_UINT8 FlowLabelH:4;
    EFI_UINT8 TrafficClassL:4;
    EFI_UINT16 FlowLabelL;
    EFI_UINT16 PayloadLength;
    EFI_UINT8 NextHeader;
    EFI_UINT8 HopLimit;
    EFI_IPv6_ADDRESS SourceAddress;
    EFI_IPv6_ADDRESS DestinationAddress;
} EFI_IP6_HEADER;

typedef struct _EFI_IP6_FRAGMENT_DATA {
    EFI_UINT32 FragmentLength;
    EFI_VOID *FragmentBuffer;
} EFI_IP6_FRAGMENT_DATA;

typedef struct _EFI_IP6_RECEIVE_DATA {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    EFI_UINT32 HeaderLength;
    EFI_IP6_HEADER *Header;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_IP6_FRAGMENT_DATA FragmentTable[1];
} EFI_IP6_RECEIVE_DATA;

typedef struct _EFI_IP6_OVERRIDE_DATA {
    EFI_UINT8 Protocol;
    EFI_UINT8 HopLimit;
    EFI_UINT32 FlowLabel;
} EFI_IP6_OVERRIDE_DATA;

typedef struct _EFI_IP6_TRANSMIT_DATA {
    EFI_IPv6_ADDRESS DestinationAddress;
    EFI_IP6_OVERRIDE_DATA *OverrideData;
    EFI_UINT32 ExtHdrsLength;
    EFI_VOID *ExtHdrs;
    EFI_UINT8 NextHeader;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
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
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_IP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_RECEIVE)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_IP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CANCEL)(
    EFI_IN EFI_IP6_PROTOCOL *This,
    EFI_IN EFI_IP6_COMPLETION_TOKEN *Token EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_IP6_POLL)(EFI_IN EFI_IP6_PROTOCOL *This);

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
