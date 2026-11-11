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

typedef struct _EFI_MANAGED_NETWORK_PROTOCOL EFI_MANAGED_NETWORK_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_GET_MODE_DATA)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData,
    EFI_SIMPLE_NETWORK_MODE *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_CONFIGURE)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_MCAST_IP_TO_MAC)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    bool Ipv6Flag,
    EFI_IP_ADDRESS *IpAddress,
    EFI_MAC_ADDRESS *MacAddress
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_GROUPS)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    bool JoinFlag,
    EFI_MAC_ADDRESS *MacAddress
);

typedef struct {
    EFI_TIME Timestamp;
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
} EFI_MANAGED_NETWORK_RECEIVE_DATA;

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_MANAGED_NETWORK_FRAGMENT_DATA;

typedef struct {
    EFI_MAC_ADDRESS *DestinationAddress;
    EFI_MAC_ADDRESS *SourceAddress;
    uint16_t ProtocolType;
    uint32_t DataLength;
    uint16_t HeaderLength;
    uint16_t FragmentCount;
    EFI_MANAGED_NETWORK_FRAGMENT_DATA FragmentTable[1];
} EFI_MANAGED_NETWORK_TRANSMIT_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    union {
        EFI_MANAGED_NETWORK_RECEIVE_DATA *RxData;
        EFI_MANAGED_NETWORK_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_MANAGED_NETWORK_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_TRANSMIT)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    EFI_MANAGED_NETWORK_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_RECEIVE)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    EFI_MANAGED_NETWORK_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_CANCEL)(
    EFI_MANAGED_NETWORK_PROTOCOL *This,
    EFI_MANAGED_NETWORK_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MANAGED_NETWORK_POLL)(EFI_MANAGED_NETWORK_PROTOCOL *This);

struct _EFI_MANAGED_NETWORK_PROTOCOL {
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
