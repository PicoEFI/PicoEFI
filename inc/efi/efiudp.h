#ifndef EFI_EFIUDP_H
#define EFI_EFIUDP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efiip.h>
#include <efi/efinet.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_UDP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x83f01464, 0x99bd, 0x45e5, {0xb3, 0x83, 0xaf, 0x63, 0x05, 0xd8, 0xe9, 0xe6}}

#define EFI_UDP4_PROTOCOL_GUID \
    {0x3ad9df29, 0x4501, 0x478d, {0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0x0e, 0x50, 0xf3}}

struct efi_udp4_protocol;

struct efi_udp4_config_data {
    uint8_t accept_broadcast;
    uint8_t accept_promiscuous;
    uint8_t accept_any_port;
    uint8_t allow_duplicate_port;
    uint8_t type_of_service;
    uint8_t time_to_live;
    uint8_t do_not_fragment;
    uint32_t receive_timeout;
    uint32_t transmit_timeout;
    uint8_t use_default_address;
    struct efi_ipv4_address station_address;
    struct efi_ipv4_address subnet_mask;
    uint16_t station_port;
    struct efi_ipv4_address remote_address;
    uint16_t remote_port;
};

typedef efi_status (EFI_API *efi_udp4_get_mode_data)(
    struct efi_udp4_protocol *self,
    struct efi_udp4_config_data *udp4_config_data,
    struct efi_ip4_mode_data *ip4_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_udp4_configure)(
    struct efi_udp4_protocol *self,
    struct efi_udp4_config_data *udp_config_data
);

typedef efi_status (EFI_API *efi_udp4_groups)(
    struct efi_udp4_protocol *self,
    bool join_flag,
    struct efi_ipv4_address *multicast_address
);

typedef efi_status (EFI_API *efi_udp4_routes)(
    struct efi_udp4_protocol *self,
    bool delete_route,
    struct efi_ipv4_address *subnet_address,
    struct efi_ipv4_address *subnet_mask,
    struct efi_ipv4_address *gateway_address
);

struct efi_udp4_session_data {
    struct efi_ipv4_address source_address;
    uint16_t source_port;
    struct efi_ipv4_address destination_address;
    uint16_t destination_port;
};

struct efi_udp4_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_udp4_receive_data {
    struct efi_time time_stamp;
    efi_event recycle_signal;
    struct efi_udp4_session_data udp_session;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_udp4_fragment_data fragment_table[1];
};

struct efi_udp4_transmit_data {
    struct efi_udp4_session_data *udp_session_data;
    struct efi_ipv4_address *gateway_address;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_udp4_fragment_data fragment_table[1];
};

struct efi_udp4_completion_token {
    efi_event event;
    efi_status status;
    union {
        struct efi_udp4_receive_data *rx_data;
        struct efi_udp4_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_udp4_transmit)(
    struct efi_udp4_protocol *self,
    struct efi_udp4_completion_token *token
);

typedef efi_status (EFI_API *efi_udp4_receive)(
    struct efi_udp4_protocol *self,
    struct efi_udp4_completion_token *token
);

typedef efi_status (EFI_API *efi_udp4_cancel)(
    struct efi_udp4_protocol *self,
    struct efi_udp4_completion_token *token
);

typedef efi_status (EFI_API *efi_udp4_poll)(struct efi_udp4_protocol *self);

struct efi_udp4_protocol {
    efi_udp4_get_mode_data get_mode_data;
    efi_udp4_configure configure;
    efi_udp4_groups groups;
    efi_udp4_routes routes;
    efi_udp4_transmit transmit;
    efi_udp4_receive receive;
    efi_udp4_cancel cancel;
    efi_udp4_poll poll;
};

#define EFI_UDP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x66ed4721, 0x3c98, 0x4d3e, {0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54}}

#define EFI_UDP6_PROTOCOL_GUID \
    {0x4f948815, 0xb4b9, 0x43cb, {0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3, 0x49, 0x55}}

struct efi_udp6_protocol;

struct efi_udp6_config_data {
    uint8_t accept_promiscuous;
    uint8_t accept_any_port;
    uint8_t allow_duplicate_port;
    uint8_t traffic_class;
    uint8_t hop_limit;
    uint32_t receive_timeout;
    uint32_t transmit_timeout;
    struct efi_ipv6_address station_address;
    uint16_t station_port;
    struct efi_ipv6_address remote_address;
    uint16_t remote_port;
};

typedef efi_status (EFI_API *efi_udp6_get_mode_data)(
    struct efi_udp6_protocol *self,
    struct efi_udp6_config_data *udp6_config_data,
    struct efi_ip6_mode_data *ip6_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_udp6_configure)(
    struct efi_udp6_protocol *self,
    struct efi_udp6_config_data *udp_config_data
);

typedef efi_status (EFI_API *efi_udp6_groups)(
    struct efi_udp6_protocol *self,
    bool join_flag,
    struct efi_ipv6_address *multicast_address
);

struct efi_udp6_session_data {
    struct efi_ipv6_address source_address;
    uint16_t source_port;
    struct efi_ipv6_address destination_address;
    uint16_t destination_port;
};

struct efi_udp6_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_udp6_receive_data {
    struct efi_time time_stamp;
    efi_event recycle_signal;
    struct efi_udp6_session_data udp_session;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_udp6_fragment_data fragment_table[1];
};

struct efi_udp6_transmit_data {
    struct efi_udp6_session_data *udp_session_data;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_udp6_fragment_data fragment_table[1];
};

struct efi_udp6_completion_token {
    efi_event event;
    efi_status status;
    union {
        struct efi_udp6_receive_data *rx_data;
        struct efi_udp6_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_udp6_transmit)(
    struct efi_udp6_protocol *self,
    struct efi_udp6_completion_token *token
);

typedef efi_status (EFI_API *efi_udp6_receive)(
    struct efi_udp6_protocol *self,
    struct efi_udp6_completion_token *token
);

typedef efi_status (EFI_API *efi_udp6_cancel)(
    struct efi_udp6_protocol *self,
    struct efi_udp6_completion_token *token
);

typedef efi_status (EFI_API *efi_udp6_poll)(struct efi_udp6_protocol *self);

struct efi_udp6_protocol {
    efi_udp6_get_mode_data get_mode_data;
    efi_udp6_configure configure;
    efi_udp6_groups groups;
    efi_udp6_transmit transmit;
    efi_udp6_receive receive;
    efi_udp6_cancel cancel;
    efi_udp6_poll poll;
};

#ifdef __cplusplus
}
#endif

#endif
