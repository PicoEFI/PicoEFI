#ifndef EFI_EFIUDP_H_
#define EFI_EFIUDP_H_

#include "efiapi.h"
#include "efinet.h"
#include "efiip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_UDP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x83f01464, 0x99bd, 0x45e5, {0xb3, 0x83, 0xaf, 0x63, 0x05, 0xd8, 0xe9, 0xe6}}

#define EFI_UDP4_PROTOCOL_GUID \
    {0x3ad9df29, 0x4501, 0x478d, {0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0x0e, 0x50, 0xf3}}

typedef struct _EFI_UDP4_PROTOCOL EFI_UDP4_PROTOCOL;

typedef struct {
    uint8_t AcceptBroadcast;
    uint8_t AcceptPromiscuous;
    uint8_t AcceptAnyPort;
    uint8_t AllowDuplicatePort;
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    uint8_t DoNotFragment;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
    uint8_t UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    uint16_t StationPort;
    EFI_IPv4_ADDRESS RemoteAddress;
    uint16_t RemotePort;
} EFI_UDP4_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_UDP4_GET_MODE_DATA)(
    EFI_UDP4_PROTOCOL *This,
    EFI_UDP4_CONFIG_DATA *Udp4ConfigData,
    EFI_IP4_MODE_DATA *Ip4ModeData,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData,
    EFI_SIMPLE_NETWORK_MODE *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_CONFIGURE)(
    EFI_UDP4_PROTOCOL *This,
    EFI_UDP4_CONFIG_DATA *UdpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_GROUPS)(
    EFI_UDP4_PROTOCOL *This,
    bool JoinFlag,
    EFI_IPv4_ADDRESS *MulticastAddress
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_ROUTES)(
    EFI_UDP4_PROTOCOL *This,
    bool DeleteRoute,
    EFI_IPv4_ADDRESS *SubnetAddress,
    EFI_IPv4_ADDRESS *SubnetMask,
    EFI_IPv4_ADDRESS *GatewayAddress
);

typedef struct {
    EFI_IPv4_ADDRESS SourceAddress;
    uint16_t SourcePort;
    EFI_IPv4_ADDRESS DestinationAddress;
    uint16_t DestinationPort;
} EFI_UDP4_SESSION_DATA;

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_UDP4_FRAGMENT_DATA;

typedef struct {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    EFI_UDP4_SESSION_DATA UdpSession;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_UDP4_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP4_RECEIVE_DATA;

typedef struct {
    EFI_UDP4_SESSION_DATA *UdpSessionData;
    EFI_IPv4_ADDRESS *GatewayAddress;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_UDP4_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP4_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        EFI_UDP4_RECEIVE_DATA *RxData;
        EFI_UDP4_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_UDP4_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_UDP4_TRANSMIT)(
    EFI_UDP4_PROTOCOL *This,
    EFI_UDP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_RECEIVE)(
    EFI_UDP4_PROTOCOL *This,
    EFI_UDP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_CANCEL)(
    EFI_UDP4_PROTOCOL *This,
    EFI_UDP4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_POLL)(EFI_UDP4_PROTOCOL *This);

struct _EFI_UDP4_PROTOCOL {
    EFI_UDP4_GET_MODE_DATA GetModeData;
    EFI_UDP4_CONFIGURE Configure;
    EFI_UDP4_GROUPS Groups;
    EFI_UDP4_ROUTES Routes;
    EFI_UDP4_TRANSMIT Transmit;
    EFI_UDP4_RECEIVE Receive;
    EFI_UDP4_CANCEL Cancel;
    EFI_UDP4_POLL Poll;
};

#define EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x66ed4721, 0x3c98, 0x4d3e, {0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54}}

#define EFI_UDP6_PROTOCOL_GUID \
    {0x4f948815, 0xb4b9, 0x43cb, {0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3, 0x49, 0x55}}

typedef struct _EFI_UDP6_PROTOCOL EFI_UDP6_PROTOCOL;

typedef struct {
    uint8_t AcceptPromiscuous;
    uint8_t AcceptAnyPort;
    uint8_t AllowDuplicatePort;
    uint8_t TrafficClass;
    uint8_t HopLimit;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
    EFI_IPv6_ADDRESS StationAddress;
    uint16_t StationPort;
    EFI_IPv6_ADDRESS RemoteAddress;
    uint16_t RemotePort;
} EFI_UDP6_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_UDP6_GET_MODE_DATA)(
    EFI_UDP6_PROTOCOL *This,
    EFI_UDP6_CONFIG_DATA *Udp6ConfigData,
    EFI_IP6_MODE_DATA *Ip6ModeData,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData,
    EFI_SIMPLE_NETWORK_MODE *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_CONFIGURE)(
    EFI_UDP6_PROTOCOL *This,
    EFI_UDP6_CONFIG_DATA *UdpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_GROUPS)(
    EFI_UDP6_PROTOCOL *This,
    bool JoinFlag,
    EFI_IPv6_ADDRESS *MulticastAddress
);

typedef struct {
    EFI_IPv6_ADDRESS SourceAddress;
    uint16_t SourcePort;
    EFI_IPv6_ADDRESS DestinationAddress;
    uint16_t DestinationPort;
} EFI_UDP6_SESSION_DATA;

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_UDP6_FRAGMENT_DATA;

typedef struct {
    EFI_TIME TimeStamp;
    EFI_EVENT RecycleSignal;
    EFI_UDP6_SESSION_DATA UdpSession;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_UDP6_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP6_RECEIVE_DATA;

typedef struct {
    EFI_UDP6_SESSION_DATA *UdpSessionData;
    uint32_t DataLength;
    uint32_t FragmentCount;
    EFI_UDP6_FRAGMENT_DATA FragmentTable[1];
} EFI_UDP6_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        EFI_UDP6_RECEIVE_DATA *RxData;
        EFI_UDP6_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_UDP6_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_UDP6_TRANSMIT)(
    EFI_UDP6_PROTOCOL *This,
    EFI_UDP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_RECEIVE)(
    EFI_UDP6_PROTOCOL *This,
    EFI_UDP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_CANCEL)(
    EFI_UDP6_PROTOCOL *This,
    EFI_UDP6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_POLL)(EFI_UDP6_PROTOCOL *This);

struct _EFI_UDP6_PROTOCOL {
    EFI_UDP6_GET_MODE_DATA GetModeData;
    EFI_UDP6_CONFIGURE Configure;
    EFI_UDP6_GROUPS Groups;
    EFI_UDP6_TRANSMIT Transmit;
    EFI_UDP6_RECEIVE Receive;
    EFI_UDP6_CANCEL Cancel;
    EFI_UDP6_POLL Poll;
};

#ifdef __cplusplus
}
#endif

#endif
