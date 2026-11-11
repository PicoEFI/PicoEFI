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

struct efi_udp4_protocol;

struct efi_udp4_config_data {
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
    struct efi_ipv4_address StationAddress;
    struct efi_ipv4_address SubnetMask;
    uint16_t StationPort;
    struct efi_ipv4_address RemoteAddress;
    uint16_t RemotePort;
};

typedef EFI_STATUS (EFI_API *EFI_UDP4_GET_MODE_DATA)(
    struct efi_udp4_protocol *This,
    struct efi_udp4_config_data *Udp4ConfigData,
    struct efi_ip4_mode_data *Ip4ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_CONFIGURE)(
    struct efi_udp4_protocol *This,
    struct efi_udp4_config_data *UdpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_GROUPS)(
    struct efi_udp4_protocol *This,
    bool JoinFlag,
    struct efi_ipv4_address *MulticastAddress
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_ROUTES)(
    struct efi_udp4_protocol *This,
    bool DeleteRoute,
    struct efi_ipv4_address *SubnetAddress,
    struct efi_ipv4_address *SubnetMask,
    struct efi_ipv4_address *GatewayAddress
);

struct efi_udp4_session_data {
    struct efi_ipv4_address SourceAddress;
    uint16_t SourcePort;
    struct efi_ipv4_address DestinationAddress;
    uint16_t DestinationPort;
};

struct efi_udp4_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_udp4_receive_data {
    struct efi_time TimeStamp;
    EFI_EVENT RecycleSignal;
    struct efi_udp4_session_data UdpSession;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_udp4_fragment_data FragmentTable[1];
};

struct efi_udp4_transmit_data {
    struct efi_udp4_session_data *UdpSessionData;
    struct efi_ipv4_address *GatewayAddress;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_udp4_fragment_data FragmentTable[1];
};

struct efi_udp4_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        struct efi_udp4_receive_data *RxData;
        struct efi_udp4_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_UDP4_TRANSMIT)(
    struct efi_udp4_protocol *This,
    struct efi_udp4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_RECEIVE)(
    struct efi_udp4_protocol *This,
    struct efi_udp4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_CANCEL)(
    struct efi_udp4_protocol *This,
    struct efi_udp4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP4_POLL)(struct efi_udp4_protocol *This);

struct efi_udp4_protocol {
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

struct efi_udp6_protocol;

struct efi_udp6_config_data {
    uint8_t AcceptPromiscuous;
    uint8_t AcceptAnyPort;
    uint8_t AllowDuplicatePort;
    uint8_t TrafficClass;
    uint8_t HopLimit;
    uint32_t ReceiveTimeout;
    uint32_t TransmitTimeout;
    struct efi_ipv6_address StationAddress;
    uint16_t StationPort;
    struct efi_ipv6_address RemoteAddress;
    uint16_t RemotePort;
};

typedef EFI_STATUS (EFI_API *EFI_UDP6_GET_MODE_DATA)(
    struct efi_udp6_protocol *This,
    struct efi_udp6_config_data *Udp6ConfigData,
    struct efi_ip6_mode_data *Ip6ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_CONFIGURE)(
    struct efi_udp6_protocol *This,
    struct efi_udp6_config_data *UdpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_GROUPS)(
    struct efi_udp6_protocol *This,
    bool JoinFlag,
    struct efi_ipv6_address *MulticastAddress
);

struct efi_udp6_session_data {
    struct efi_ipv6_address SourceAddress;
    uint16_t SourcePort;
    struct efi_ipv6_address DestinationAddress;
    uint16_t DestinationPort;
};

struct efi_udp6_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_udp6_receive_data {
    struct efi_time TimeStamp;
    EFI_EVENT RecycleSignal;
    struct efi_udp6_session_data UdpSession;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_udp6_fragment_data FragmentTable[1];
};

struct efi_udp6_transmit_data {
    struct efi_udp6_session_data *UdpSessionData;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_udp6_fragment_data FragmentTable[1];
};

struct efi_udp6_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        struct efi_udp6_receive_data *RxData;
        struct efi_udp6_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_UDP6_TRANSMIT)(
    struct efi_udp6_protocol *This,
    struct efi_udp6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_RECEIVE)(
    struct efi_udp6_protocol *This,
    struct efi_udp6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_CANCEL)(
    struct efi_udp6_protocol *This,
    struct efi_udp6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_UDP6_POLL)(struct efi_udp6_protocol *This);

struct efi_udp6_protocol {
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
