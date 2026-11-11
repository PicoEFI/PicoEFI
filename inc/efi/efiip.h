#ifndef EFI_EFIIP_H
#define EFI_EFIIP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efinet.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_IP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xc51711e7, 0xb4bf, 0x404a, {0xbf, 0xb8, 0x0a, 0x04, 0x8e, 0xf1, 0xff, 0xe4}}

#define EFI_IP4_PROTOCOL_GUID \
    {0x41d94cd2, 0x35b6, 0x455a, {0x82, 0x58, 0xd4, 0xe5, 0x13, 0x34, 0xaa, 0xdd}}

struct efi_ip4_protocol;

struct efi_ip4_config_data {
    uint8_t default_protocol;
    uint8_t accept_any_protocol;
    uint8_t accept_icmp_errors;
    uint8_t accept_broadcast;
    uint8_t accept_promiscuous;
    uint8_t use_default_address;
    struct efi_ipv4_address station_address;
    struct efi_ipv4_address subnet_mask;
    uint8_t type_of_service;
    uint8_t time_to_live;
    uint8_t do_not_fragment;
    uint8_t raw_data;
    uint32_t receive_timeout;
    uint32_t transmit_timeout;
};

struct efi_ip4_route_table {
    struct efi_ipv4_address subnet_address;
    struct efi_ipv4_address subnet_mask;
    struct efi_ipv4_address gateway_address;
};

struct efi_ip4_icmp_type {
    uint8_t type;
    uint8_t code;
};

// route_table points to route_count entries, as described; the structure
// prints it by value.
struct efi_ip4_mode_data {
    uint8_t is_started;
    uint32_t max_packet_size;
    struct efi_ip4_config_data config_data;
    uint8_t is_configured;
    uint32_t group_count;
    struct efi_ipv4_address *group_table;
    uint32_t route_count;
    struct efi_ip4_route_table *route_table;
    uint32_t icmp_type_count;
    struct efi_ip4_icmp_type *icmp_type_list;
};

typedef efi_status (EFI_API *efi_ip4_get_mode_data)(
    struct efi_ip4_protocol *self,
    struct efi_ip4_mode_data *ip4_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_ip4_configure)(
    struct efi_ip4_protocol *self,
    struct efi_ip4_config_data *ip_config_data
);

typedef efi_status (EFI_API *efi_ip4_groups)(
    struct efi_ip4_protocol *self,
    bool join_flag,
    struct efi_ipv4_address *group_address
);

typedef efi_status (EFI_API *efi_ip4_routes)(
    struct efi_ip4_protocol *self,
    bool delete_route,
    struct efi_ipv4_address *subnet_address,
    struct efi_ipv4_address *subnet_mask,
    struct efi_ipv4_address *gateway_address
);

struct efi_ip4_header {
    uint8_t version_ihl;
    uint8_t type_of_service;
    uint16_t total_length;
    uint16_t identification;
    uint16_t fragmentation;
    uint8_t time_to_live;
    uint8_t protocol;
    uint16_t checksum;
    struct efi_ipv4_address source_address;
    struct efi_ipv4_address destination_address;
} __attribute__((__packed__));

#define EFI_IP4_HEADER_HEADER_LENGTH_SHIFT 0
#define EFI_IP4_HEADER_HEADER_LENGTH_MASK 0x0f
#define EFI_IP4_HEADER_VERSION_SHIFT 4
#define EFI_IP4_HEADER_VERSION_MASK 0xf0

struct efi_ip4_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_ip4_receive_data {
    struct efi_time time_stamp;
    efi_event recycle_signal;
    uint32_t header_length;
    struct efi_ip4_header *header;
    uint32_t options_length;
    void *options;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_ip4_fragment_data fragment_table[1];
};

struct efi_ip4_override_data {
    struct efi_ipv4_address source_address;
    struct efi_ipv4_address gateway_address;
    uint8_t protocol;
    uint8_t type_of_service;
    uint8_t time_to_live;
    uint8_t do_not_fragment;
};

struct efi_ip4_transmit_data {
    struct efi_ipv4_address destination_address;
    struct efi_ip4_override_data *override_data;
    uint32_t options_length;
    void *options_buffer;
    uint32_t total_data_length;
    uint32_t fragment_count;
    struct efi_ip4_fragment_data fragment_table[1];
};

struct efi_ip4_completion_token {
    efi_event event;
    efi_status status;
    union {
        struct efi_ip4_receive_data *rx_data;
        struct efi_ip4_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_ip4_transmit)(
    struct efi_ip4_protocol *self,
    struct efi_ip4_completion_token *token
);

typedef efi_status (EFI_API *efi_ip4_receive)(
    struct efi_ip4_protocol *self,
    struct efi_ip4_completion_token *token
);

typedef efi_status (EFI_API *efi_ip4_cancel)(
    struct efi_ip4_protocol *self,
    struct efi_ip4_completion_token *token
);

typedef efi_status (EFI_API *efi_ip4_poll)(struct efi_ip4_protocol *self);

struct efi_ip4_protocol {
    efi_ip4_get_mode_data get_mode_data;
    efi_ip4_configure configure;
    efi_ip4_groups groups;
    efi_ip4_routes routes;
    efi_ip4_transmit transmit;
    efi_ip4_receive receive;
    efi_ip4_cancel cancel;
    efi_ip4_poll poll;
};

#define EFI_IP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0xec835dd3, 0xfe0f, 0x617b, {0xa6, 0x21, 0xb3, 0x50, 0xc3, 0xe1, 0x33, 0x88}}

#define EFI_IP6_PROTOCOL_GUID \
    {0x2c8759d5, 0x5c2d, 0x66ef, {0x92, 0x5f, 0xb6, 0x6c, 0x10, 0x19, 0x57, 0xe2}}

struct efi_ip6_protocol;

struct efi_ip6_config_data {
    uint8_t default_protocol;
    uint8_t accept_any_protocol;
    uint8_t accept_icmp_errors;
    uint8_t accept_promiscuous;
    struct efi_ipv6_address destination_address;
    struct efi_ipv6_address station_address;
    uint8_t traffic_class;
    uint8_t hop_limit;
    uint32_t flow_label;
    uint32_t receive_timeout;
    uint32_t transmit_timeout;
};

struct efi_ip6_address_info {
    struct efi_ipv6_address address;
    uint8_t prefix_length;
};

struct efi_ip6_route_table {
    struct efi_ipv6_address gateway;
    struct efi_ipv6_address destination;
    uint8_t prefix_length;
};

#define EFI_NEIGHBOR_IN_COMPLETE ((uint32_t)0)
#define EFI_NEIGHBOR_REACHABLE ((uint32_t)1)
#define EFI_NEIGHBOR_STALE ((uint32_t)2)
#define EFI_NEIGHBOR_DELAY ((uint32_t)3)
#define EFI_NEIGHBOR_PROBE ((uint32_t)4)

struct efi_ip6_neighbor_cache {
    struct efi_ipv6_address neighbor;
    struct efi_mac_address link_address;
    uint32_t state;
};

struct efi_ip6_icmp_type {
    uint8_t type;
    uint8_t code;
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
#define EFI_ICMP_V6_LISTENER_REPORT_2 0x8f

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
    uint8_t is_started;
    uint32_t max_packet_size;
    struct efi_ip6_config_data config_data;
    uint8_t is_configured;
    uint32_t address_count;
    struct efi_ip6_address_info *address_list;
    uint32_t group_count;
    struct efi_ipv6_address *group_table;
    uint32_t route_count;
    struct efi_ip6_route_table *route_table;
    uint32_t neighbor_count;
    struct efi_ip6_neighbor_cache *neighbor_cache;
    uint32_t prefix_count;
    struct efi_ip6_address_info *prefix_table;
    uint32_t icmp_type_count;
    struct efi_ip6_icmp_type *icmp_type_list;
};

typedef efi_status (EFI_API *efi_ip6_get_mode_data)(
    struct efi_ip6_protocol *self,
    struct efi_ip6_mode_data *ip6_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_ip6_configure)(
    struct efi_ip6_protocol *self,
    struct efi_ip6_config_data *ip6_config_data
);

typedef efi_status (EFI_API *efi_ip6_groups)(
    struct efi_ip6_protocol *self,
    bool join_flag,
    struct efi_ipv6_address *group_address
);

typedef efi_status (EFI_API *efi_ip6_routes)(
    struct efi_ip6_protocol *self,
    bool delete_route,
    struct efi_ipv6_address *destination,
    uint8_t prefix_length,
    struct efi_ipv6_address *gateway_address
);

typedef efi_status (EFI_API *efi_ip6_neighbors)(
    struct efi_ip6_protocol *self,
    bool delete_flag,
    struct efi_ipv6_address *target_ip6_address,
    struct efi_mac_address *target_link_address,
    uint32_t timeout,
    bool override
);

struct efi_ip6_header {
    uint8_t version_class;
    uint8_t class_flow;
    uint16_t flow_label_l;
    uint16_t payload_length;
    uint8_t next_header;
    uint8_t hop_limit;
    struct efi_ipv6_address source_address;
    struct efi_ipv6_address destination_address;
} __attribute__((__packed__));

#define EFI_IP6_HEADER_TRAFFIC_CLASS_H_SHIFT 0
#define EFI_IP6_HEADER_TRAFFIC_CLASS_H_MASK 0x0f
#define EFI_IP6_HEADER_VERSION_SHIFT 4
#define EFI_IP6_HEADER_VERSION_MASK 0xf0
#define EFI_IP6_HEADER_FLOW_LABEL_H_SHIFT 0
#define EFI_IP6_HEADER_FLOW_LABEL_H_MASK 0x0f
#define EFI_IP6_HEADER_TRAFFIC_CLASS_L_SHIFT 4
#define EFI_IP6_HEADER_TRAFFIC_CLASS_L_MASK 0xf0

struct efi_ip6_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_ip6_receive_data {
    struct efi_time time_stamp;
    efi_event recycle_signal;
    uint32_t header_length;
    struct efi_ip6_header *header;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_ip6_fragment_data fragment_table[1];
};

struct efi_ip6_override_data {
    uint8_t protocol;
    uint8_t hop_limit;
    uint32_t flow_label;
};

struct efi_ip6_transmit_data {
    struct efi_ipv6_address destination_address;
    struct efi_ip6_override_data *override_data;
    uint32_t ext_hdrs_length;
    void *ext_hdrs;
    uint8_t next_header;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_ip6_fragment_data fragment_table[1];
};

struct efi_ip6_completion_token {
    efi_event event;
    efi_status status;
    union {
        struct efi_ip6_receive_data *rx_data;
        struct efi_ip6_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_ip6_transmit)(
    struct efi_ip6_protocol *self,
    struct efi_ip6_completion_token *token
);

typedef efi_status (EFI_API *efi_ip6_receive)(
    struct efi_ip6_protocol *self,
    struct efi_ip6_completion_token *token
);

typedef efi_status (EFI_API *efi_ip6_cancel)(
    struct efi_ip6_protocol *self,
    struct efi_ip6_completion_token *token
);

typedef efi_status (EFI_API *efi_ip6_poll)(struct efi_ip6_protocol *self);

struct efi_ip6_protocol {
    efi_ip6_get_mode_data get_mode_data;
    efi_ip6_configure configure;
    efi_ip6_groups groups;
    efi_ip6_routes routes;
    efi_ip6_neighbors neighbors;
    efi_ip6_transmit transmit;
    efi_ip6_receive receive;
    efi_ip6_cancel cancel;
    efi_ip6_poll poll;
};

#ifdef __cplusplus
}
#endif

#endif
