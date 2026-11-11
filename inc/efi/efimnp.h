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

typedef efi_status (EFI_API *efi_managed_network_get_mode_data)(
    struct efi_managed_network_protocol *self,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_managed_network_configure)(
    struct efi_managed_network_protocol *self,
    struct efi_managed_network_config_data *mnp_config_data
);

typedef efi_status (EFI_API *efi_managed_network_mcast_ip_to_mac)(
    struct efi_managed_network_protocol *self,
    bool ipv6_flag,
    union efi_ip_address *ip_address,
    struct efi_mac_address *mac_address
);

typedef efi_status (EFI_API *efi_managed_network_groups)(
    struct efi_managed_network_protocol *self,
    bool join_flag,
    struct efi_mac_address *mac_address
);

struct efi_managed_network_receive_data {
    struct efi_time timestamp;
    efi_event recycle_event;
    uint32_t packet_length;
    uint32_t header_length;
    uint32_t address_length;
    uint32_t data_length;
    uint8_t broadcast_flag;
    uint8_t multicast_flag;
    uint8_t promiscuous_flag;
    uint16_t protocol_type;
    void *destination_address;
    void *source_address;
    void *media_header;
    void *packet_data;
};

struct efi_managed_network_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_managed_network_transmit_data {
    struct efi_mac_address *destination_address;
    struct efi_mac_address *source_address;
    uint16_t protocol_type;
    uint32_t data_length;
    uint16_t header_length;
    uint16_t fragment_count;
    struct efi_managed_network_fragment_data fragment_table[1];
};

struct efi_managed_network_completion_token {
    efi_event event;
    efi_status status;
    union {
        struct efi_managed_network_receive_data *rx_data;
        struct efi_managed_network_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_managed_network_transmit)(
    struct efi_managed_network_protocol *self,
    struct efi_managed_network_completion_token *token
);

typedef efi_status (EFI_API *efi_managed_network_receive)(
    struct efi_managed_network_protocol *self,
    struct efi_managed_network_completion_token *token
);

typedef efi_status (EFI_API *efi_managed_network_cancel)(
    struct efi_managed_network_protocol *self,
    struct efi_managed_network_completion_token *token
);

typedef efi_status (EFI_API *efi_managed_network_poll)(struct efi_managed_network_protocol *self);

struct efi_managed_network_protocol {
    efi_managed_network_get_mode_data get_mode_data;
    efi_managed_network_configure configure;
    efi_managed_network_mcast_ip_to_mac mcast_ip_to_mac;
    efi_managed_network_groups groups;
    efi_managed_network_transmit transmit;
    efi_managed_network_receive receive;
    efi_managed_network_cancel cancel;
    efi_managed_network_poll poll;
};

#ifdef __cplusplus
}
#endif

#endif
