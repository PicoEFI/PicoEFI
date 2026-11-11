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

struct efi_ip4_protocol;

struct efi_ip4_config_data {
    uint8_t DefaultProtocol;
    uint8_t AcceptAnyProtocol;
    uint8_t AcceptIcmpErrors;
    uint8_t AcceptBroadcast;
    uint8_t AcceptPromiscuous;
    uint8_t UseDefaultAddress;
    struct efi_ipv4_address StationAddress;
    struct efi_ipv4_address SubnetMask;
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    uint8_t DoNotFragment;
    uint8_t RawData;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
};

struct efi_ip4_route_table {
    struct efi_ipv4_address SubnetAddress;
    struct efi_ipv4_address SubnetMask;
    struct efi_ipv4_address GatewayAddress;
};

struct efi_ip4_icmp_type {
    uint8_t Type;
    uint8_t Code;
};

/* RouteTable points to RouteCount entries, as described; the structure prints it by value. */
struct efi_ip4_mode_data {
    uint8_t IsStarted;
    uint32_t MaxPacketSize;
    struct efi_ip4_config_data ConfigData;
    uint8_t IsConfigured;
    uint32_t GroupCount;
    struct efi_ipv4_address *GroupTable;
    uint32_t RouteCount;
    struct efi_ip4_route_table *RouteTable;
    uint32_t IcmpTypeCount;
    struct efi_ip4_icmp_type *IcmpTypeList;
};

typedef EFI_STATUS (EFI_API *EFI_IP4_GET_MODE_DATA)(
    struct efi_ip4_protocol *This,
    struct efi_ip4_mode_data *Ip4ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIGURE)(
    struct efi_ip4_protocol *This,
    struct efi_ip4_config_data *IpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_IP4_GROUPS)(
    struct efi_ip4_protocol *This,
    bool JoinFlag,
    struct efi_ipv4_address *GroupAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP4_ROUTES)(
    struct efi_ip4_protocol *This,
    bool DeleteRoute,
    struct efi_ipv4_address *SubnetAddress,
    struct efi_ipv4_address *SubnetMask,
    struct efi_ipv4_address *GatewayAddress
);

struct efi_ip4_header {
    uint8_t HeaderLength:4;
    uint8_t Version:4;
    uint8_t TypeOfService;
    uint16_t TotalLength;
    uint16_t Identification;
    uint16_t Fragmentation;
    uint8_t TimeToLive;
    uint8_t Protocol;
    uint16_t Checksum;
    struct efi_ipv4_address SourceAddress;
    struct efi_ipv4_address DestinationAddress;
} __attribute__((__packed__));

struct efi_ip4_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_ip4_receive_data {
    struct efi_time TimeStamp;
    EFI_EVENT RecycleSignal;
    uint32_t HeaderLength;
    struct efi_ip4_header *Header;
    uint32_t OptionsLength;
    void *Options;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_ip4_fragment_data FragmentTable[1];
};

struct efi_ip4_override_data {
    struct efi_ipv4_address SourceAddress;
    struct efi_ipv4_address GatewayAddress;
    uint8_t Protocol;
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    uint8_t DoNotFragment;
};

struct efi_ip4_transmit_data {
    struct efi_ipv4_address DestinationAddress;
    struct efi_ip4_override_data *OverrideData;
    uint32_t OptionsLength;
    void *OptionsBuffer;
    uint32_t TotalDataLength;
    uint32_t FragmentCount;
    struct efi_ip4_fragment_data FragmentTable[1];
};

struct efi_ip4_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        struct efi_ip4_receive_data *RxData;
        struct efi_ip4_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_IP4_TRANSMIT)(
    struct efi_ip4_protocol *This,
    struct efi_ip4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_RECEIVE)(
    struct efi_ip4_protocol *This,
    struct efi_ip4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CANCEL)(
    struct efi_ip4_protocol *This,
    struct efi_ip4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP4_POLL)(struct efi_ip4_protocol *This);

struct efi_ip4_protocol {
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

struct efi_ip6_protocol;

struct efi_ip6_config_data {
    uint8_t DefaultProtocol;
    uint8_t AcceptAnyProtocol;
    uint8_t AcceptIcmpErrors;
    uint8_t AcceptPromiscuous;
    struct efi_ipv6_address DestinationAddress;
    struct efi_ipv6_address StationAddress;
    uint8_t TrafficClass;
    uint8_t HopLimit;
    uint32_t FlowLabel;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
};

struct efi_ip6_address_info {
    struct efi_ipv6_address Address;
    uint8_t PrefixLength;
};

struct efi_ip6_route_table {
    struct efi_ipv6_address Gateway;
    struct efi_ipv6_address Destination;
    uint8_t PrefixLength;
};

typedef enum {
    EfiNeighborInComplete,
    EfiNeighborReachable,
    EfiNeighborStale,
    EfiNeighborDelay,
    EfiNeighborProbe
} EFI_IP6_NEIGHBOR_STATE;

struct efi_ip6_neighbor_cache {
    struct efi_ipv6_address Neighbor;
    struct efi_mac_address LinkAddress;
    EFI_IP6_NEIGHBOR_STATE State;
};

struct efi_ip6_icmp_type {
    uint8_t Type;
    uint8_t Code;
};

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

struct efi_ip6_mode_data {
    uint8_t IsStarted;
    uint32_t MaxPacketSize;
    struct efi_ip6_config_data ConfigData;
    uint8_t IsConfigured;
    uint32_t AddressCount;
    struct efi_ip6_address_info *AddressList;
    uint32_t GroupCount;
    struct efi_ipv6_address *GroupTable;
    uint32_t RouteCount;
    struct efi_ip6_route_table *RouteTable;
    uint32_t NeighborCount;
    struct efi_ip6_neighbor_cache *NeighborCache;
    uint32_t PrefixCount;
    struct efi_ip6_address_info *PrefixTable;
    uint32_t IcmpTypeCount;
    struct efi_ip6_icmp_type *IcmpTypeList;
};

typedef EFI_STATUS (EFI_API *EFI_IP6_GET_MODE_DATA)(
    struct efi_ip6_protocol *This,
    struct efi_ip6_mode_data *Ip6ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIGURE)(
    struct efi_ip6_protocol *This,
    struct efi_ip6_config_data *Ip6ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_IP6_GROUPS)(
    struct efi_ip6_protocol *This,
    bool JoinFlag,
    struct efi_ipv6_address *GroupAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP6_ROUTES)(
    struct efi_ip6_protocol *This,
    bool DeleteRoute,
    struct efi_ipv6_address *Destination,
    uint8_t PrefixLength,
    struct efi_ipv6_address *GatewayAddress
);

typedef EFI_STATUS (EFI_API *EFI_IP6_NEIGHBORS)(
    struct efi_ip6_protocol *This,
    bool DeleteFlag,
    struct efi_ipv6_address *TargetIp6Address,
    struct efi_mac_address *TargetLinkAddress,
    uint32_t Timeout,
    bool Override
);

struct efi_ip6_header {
    uint8_t TrafficClassH:4;
    uint8_t Version:4;
    uint8_t FlowLabelH:4;
    uint8_t TrafficClassL:4;
    uint16_t FlowLabelL;
    uint16_t PayloadLength;
    uint8_t NextHeader;
    uint8_t HopLimit;
    struct efi_ipv6_address SourceAddress;
    struct efi_ipv6_address DestinationAddress;
} __attribute__((__packed__));

struct efi_ip6_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_ip6_receive_data {
    struct efi_time TimeStamp;
    EFI_EVENT RecycleSignal;
    uint32_t HeaderLength;
    struct efi_ip6_header *Header;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_ip6_fragment_data FragmentTable[1];
};

struct efi_ip6_override_data {
    uint8_t Protocol;
    uint8_t HopLimit;
    uint32_t FlowLabel;
};

struct efi_ip6_transmit_data {
    struct efi_ipv6_address DestinationAddress;
    struct efi_ip6_override_data *OverrideData;
    uint32_t ExtHdrsLength;
    void *ExtHdrs;
    uint8_t NextHeader;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_ip6_fragment_data FragmentTable[1];
};

struct efi_ip6_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        struct efi_ip6_receive_data *RxData;
        struct efi_ip6_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_IP6_TRANSMIT)(
    struct efi_ip6_protocol *This,
    struct efi_ip6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_RECEIVE)(
    struct efi_ip6_protocol *This,
    struct efi_ip6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CANCEL)(
    struct efi_ip6_protocol *This,
    struct efi_ip6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_IP6_POLL)(struct efi_ip6_protocol *This);

struct efi_ip6_protocol {
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
