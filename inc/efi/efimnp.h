#ifndef EFI_EFIMNP_H_
#define EFI_EFIMNP_H_

#include "efinet.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL_GUID \
    {0xf36ff770, 0xa7e1, 0x42cf, {0x9e, 0xd2, 0x56, 0xf0, 0xf2, 0x71, 0xf4, 0x4c}}

#define EFI_MANAGED_NETWORK_PROTOCOL_GUID \
    {0x7ab33a91, 0xace5, 0x4326, {0xb5, 0x72, 0xe7, 0xee, 0x33, 0xd3, 0x9f, 0x16}}

struct efi_managed_network_protocol;

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_GET_MODE_DATA)(
    struct efi_managed_network_protocol *This,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_CONFIGURE)(
    struct efi_managed_network_protocol *This,
    struct efi_managed_network_config_data *MnpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_MCAST_IP_TO_MAC)(
    struct efi_managed_network_protocol *This,
    bool Ipv6Flag,
    union efi_ip_address *IpAddress,
    struct efi_mac_address *MacAddress
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_GROUPS)(
    struct efi_managed_network_protocol *This,
    bool JoinFlag,
    struct efi_mac_address *MacAddress
);

struct efi_managed_network_receive_data {
    struct efi_time Timestamp;
    EFI_EVENT RecycleEvent;
    uint32_t PacketLength;
    uint32_t HeaderLength;
    uint32_t AddressLength;
    uint32_t DataLength;
    uint8_t BroadcastFlag;
    uint8_t MulticastFlag;
    uint8_t PromiscuousFlag;
    uint16_t ProtocolType;
    void *DestinationAddress;
    void *SourceAddress;
    void *MediaHeader;
    void *PacketData;
};

struct efi_managed_network_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_managed_network_transmit_data {
    struct efi_mac_address *DestinationAddress;
    struct efi_mac_address *SourceAddress;
    uint16_t ProtocolType;
    uint32_t DataLength;
    uint16_t HeaderLength;
    uint16_t FragmentCount;
    struct efi_managed_network_fragment_data FragmentTable[1];
};

struct efi_managed_network_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        struct efi_managed_network_receive_data *RxData;
        struct efi_managed_network_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_TRANSMIT)(
    struct efi_managed_network_protocol *This,
    struct efi_managed_network_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_RECEIVE)(
    struct efi_managed_network_protocol *This,
    struct efi_managed_network_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_CANCEL)(
    struct efi_managed_network_protocol *This,
    struct efi_managed_network_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_POLL)(struct efi_managed_network_protocol *This);

struct efi_managed_network_protocol {
    EFI_MANAGED_NETWORK_GET_MODE_DATA GetModeData;
    EFI_MANAGED_NETWORK_CONFIGURE Configure;
    EFI_MANAGED_NETWORK_MCAST_IP_TO_MAC McastIpToMac;
    EFI_MANAGED_NETWORK_GROUPS Groups;
    EFI_MANAGED_NETWORK_TRANSMIT Transmit;
    EFI_MANAGED_NETWORK_RECEIVE Receive;
    EFI_MANAGED_NETWORK_CANCEL Cancel;
    EFI_MANAGED_NETWORK_POLL Poll;
};

#ifdef __cplusplus
}
#endif

#endif
