#ifndef EFI_EFIARPDHCP_H
#define EFI_EFIARPDHCP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ARP_SERVICE_BINDING_PROTOCOL_GUID \
    {0xf44c00ee, 0x1f2c, 0x4a00, {0xaa, 0x09, 0x1c, 0x9f, 0x3e, 0x08, 0x00, 0xa3}}

#define EFI_ARP_PROTOCOL_GUID \
    {0xf4b427bb, 0xba21, 0x4f16, {0xbc, 0x4e, 0x43, 0xe4, 0x16, 0xab, 0x61, 0x9c}}

struct efi_arp_protocol;

struct efi_arp_config_data {
    uint16_t sw_address_type;
    uint8_t sw_address_length;
    void *station_address;
    uint32_t entry_time_out;
    uint32_t retry_count;
    uint32_t retry_time_out;
};

typedef efi_status (EFI_API *efi_arp_configure)(
    struct efi_arp_protocol *self,
    struct efi_arp_config_data *config_data
);

typedef efi_status (EFI_API *efi_arp_add)(
    struct efi_arp_protocol *self,
    bool deny_flag,
    void *target_sw_address,
    void *target_hw_address,
    uint32_t timeout_value,
    bool overwrite
);

struct efi_arp_find_data {
    uint32_t size;
    uint8_t deny_flag;
    uint8_t static_flag;
    uint16_t hw_address_type;
    uint16_t sw_address_type;
    uint8_t hw_address_length;
    uint8_t sw_address_length;
};

typedef efi_status (EFI_API *efi_arp_find)(
    struct efi_arp_protocol *self,
    bool by_sw_address,
    void *address_buffer,
    uint32_t *entry_length,
    uint32_t *entry_count,
    struct efi_arp_find_data **entries,
    bool refresh
);

typedef efi_status (EFI_API *efi_arp_delete)(
    struct efi_arp_protocol *self,
    bool by_sw_address,
    void *address_buffer
);

typedef efi_status (EFI_API *efi_arp_flush)(struct efi_arp_protocol *self);

typedef efi_status (EFI_API *efi_arp_request)(
    struct efi_arp_protocol *self,
    void *target_sw_address,
    efi_event resolved_event,
    void *target_hw_address
);

typedef efi_status (EFI_API *efi_arp_cancel)(
    struct efi_arp_protocol *self,
    void *target_sw_address,
    efi_event resolved_event
);

struct efi_arp_protocol {
    efi_arp_configure configure;
    efi_arp_add add;
    efi_arp_find find;
#ifdef __cplusplus
    efi_arp_delete delete_;
#else
    efi_arp_delete delete;
#endif
    efi_arp_flush flush;
    efi_arp_request request;
    efi_arp_cancel cancel;
};

#define EFI_DHCP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x9d9a39d8, 0xbd42, 0x4a73, {0xa4, 0xd5, 0x8e, 0xe9, 0x4b, 0xe1, 0x13, 0x80}}

#define EFI_DHCP4_PROTOCOL_GUID \
    {0x8a219718, 0x4ef5, 0x4761, {0x91, 0xc8, 0xc0, 0xf0, 0x4b, 0xda, 0x9e, 0x56}}

struct efi_dhcp4_protocol;

#define EFI_DHCP4_STOPPED ((uint32_t)0x0)
#define EFI_DHCP4_INIT ((uint32_t)0x1)
#define EFI_DHCP4_SELECTING ((uint32_t)0x2)
#define EFI_DHCP4_REQUESTING ((uint32_t)0x3)
#define EFI_DHCP4_BOUND ((uint32_t)0x4)
#define EFI_DHCP4_RENEWING ((uint32_t)0x5)
#define EFI_DHCP4_REBINDING ((uint32_t)0x6)
#define EFI_DHCP4_INIT_REBOOT ((uint32_t)0x7)
#define EFI_DHCP4_REBOOTING ((uint32_t)0x8)

#define EFI_DHCP4_SEND_DISCOVER ((uint32_t)0x01)
#define EFI_DHCP4_RCVD_OFFER ((uint32_t)0x02)
#define EFI_DHCP4_SELECT_OFFER ((uint32_t)0x03)
#define EFI_DHCP4_SEND_REQUEST ((uint32_t)0x04)
#define EFI_DHCP4_RCVD_ACK ((uint32_t)0x05)
#define EFI_DHCP4_RCVD_NAK ((uint32_t)0x06)
#define EFI_DHCP4_SEND_DECLINE ((uint32_t)0x07)
#define EFI_DHCP4_BOUND_COMPLETED ((uint32_t)0x08)
#define EFI_DHCP4_ENTER_RENEWING ((uint32_t)0x09)
#define EFI_DHCP4_ENTER_REBINDING ((uint32_t)0x0a)
#define EFI_DHCP4_ADDRESS_LOST ((uint32_t)0x0b)
#define EFI_DHCP4_FAIL ((uint32_t)0x0c)

struct efi_dhcp4_header {
    uint8_t op_code;
    uint8_t hw_type;
    uint8_t hw_addr_len;
    uint8_t hops;
    uint32_t xid;
    uint16_t seconds;
    uint16_t reserved;
    struct efi_ipv4_address client_addr;
    struct efi_ipv4_address your_addr;
    struct efi_ipv4_address server_addr;
    struct efi_ipv4_address gateway_addr;
    uint8_t client_hw_addr[16];
    char server_name[64];
    char boot_file_name[128];
} __attribute__((__packed__));

struct efi_dhcp4_packet {
    uint32_t size;
    uint32_t length;
    struct __attribute__((__packed__)) {
        struct efi_dhcp4_header header;
        uint32_t magik;
        uint8_t option[1];
    } dhcp4;
} __attribute__((__packed__));

struct efi_dhcp4_packet_option {
    uint8_t op_code;
    uint8_t length;
    uint8_t data[1];
} __attribute__((__packed__));

typedef efi_status (EFI_API *efi_dhcp4_callback)(
    struct efi_dhcp4_protocol *self,
    void *context,
    uint32_t current_state,
    uint32_t dhcp4_event,
    struct efi_dhcp4_packet *packet,
    struct efi_dhcp4_packet **new_packet
);

struct efi_dhcp4_config_data {
    uint32_t discover_try_count;
    uint32_t *discover_timeout;
    uint32_t request_try_count;
    uint32_t *request_timeout;
    struct efi_ipv4_address client_address;
    efi_dhcp4_callback dhcp4_callback;
    void *callback_context;
    uint32_t option_count;
    struct efi_dhcp4_packet_option **option_list;
};

struct efi_dhcp4_mode_data {
    uint32_t state;
    struct efi_dhcp4_config_data config_data;
    struct efi_ipv4_address client_address;
    struct efi_mac_address client_mac_address;
    struct efi_ipv4_address server_address;
    struct efi_ipv4_address router_address;
    struct efi_ipv4_address subnet_mask;
    uint32_t lease_time;
    struct efi_dhcp4_packet *reply_packet;
};

struct efi_dhcp4_listen_point {
    struct efi_ipv4_address listen_address;
    struct efi_ipv4_address subnet_mask;
    uint16_t listen_port;
};

struct efi_dhcp4_transmit_receive_token {
    efi_status status;
    efi_event completion_event;
    struct efi_ipv4_address remote_address;
    uint16_t remote_port;
    struct efi_ipv4_address gateway_address;
    uint32_t listen_point_count;
    struct efi_dhcp4_listen_point *listen_points;
    uint32_t timeout_value;
    struct efi_dhcp4_packet *packet;
    uint32_t response_count;
    struct efi_dhcp4_packet *response_list;
};

typedef efi_status (EFI_API *efi_dhcp4_get_mode_data)(
    struct efi_dhcp4_protocol *self,
    struct efi_dhcp4_mode_data *dhcp4_mode_data
);

typedef efi_status (EFI_API *efi_dhcp4_configure)(
    struct efi_dhcp4_protocol *self,
    struct efi_dhcp4_config_data *dhcp4_cfg_data
);

typedef efi_status (EFI_API *efi_dhcp4_start)(
    struct efi_dhcp4_protocol *self,
    efi_event completion_event
);

typedef efi_status (EFI_API *efi_dhcp4_renew_rebind)(
    struct efi_dhcp4_protocol *self,
    bool rebind_request,
    efi_event completion_event
);

typedef efi_status (EFI_API *efi_dhcp4_release)(struct efi_dhcp4_protocol *self);

typedef efi_status (EFI_API *efi_dhcp4_stop)(struct efi_dhcp4_protocol *self);

typedef efi_status (EFI_API *efi_dhcp4_build)(
    struct efi_dhcp4_protocol *self,
    struct efi_dhcp4_packet *seed_packet,
    uint32_t delete_count,
    uint8_t *delete_list,
    uint32_t append_count,
    struct efi_dhcp4_packet_option *append_list[],
    struct efi_dhcp4_packet **new_packet
);

typedef efi_status (EFI_API *efi_dhcp4_transmit_receive)(
    struct efi_dhcp4_protocol *self,
    struct efi_dhcp4_transmit_receive_token *token
);

typedef efi_status (EFI_API *efi_dhcp4_parse)(
    struct efi_dhcp4_protocol *self,
    struct efi_dhcp4_packet *packet,
    uint32_t *option_count,
    struct efi_dhcp4_packet_option *packet_option_list[]
);

struct efi_dhcp4_protocol {
    efi_dhcp4_get_mode_data get_mode_data;
    efi_dhcp4_configure configure;
    efi_dhcp4_start start;
    efi_dhcp4_renew_rebind renew_rebind;
    efi_dhcp4_release release;
    efi_dhcp4_stop stop;
    efi_dhcp4_build build;
    efi_dhcp4_transmit_receive transmit_receive;
    efi_dhcp4_parse parse;
};

#define EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x9fb9a8a1, 0x2f4a, 0x43a6, {0x88, 0x9c, 0xd0, 0xf7, 0xb6, 0xc4, 0x7a, 0xd5}}

#define EFI_DHCP6_PROTOCOL_GUID \
    {0x87c8bad7, 0x595, 0x4053, {0x82, 0x97, 0xde, 0xde, 0x39, 0x5f, 0x5d, 0x5b}}

struct efi_dhcp6_protocol;

struct efi_dhcp6_duid {
    uint16_t length;
    uint8_t duid[1];
};

struct efi_dhcp6_ia_descriptor {
    uint16_t type;
    uint32_t ia_id;
};

#define EFI_DHCP6_IA_TYPE_NA 3
#define EFI_DHCP6_IA_TYPE_TA 4

#define EFI_DHCP6_INIT ((uint32_t)0x0)
#define EFI_DHCP6_SELECTING ((uint32_t)0x1)
#define EFI_DHCP6_REQUESTING ((uint32_t)0x2)
#define EFI_DHCP6_DECLINING ((uint32_t)0x3)
#define EFI_DHCP6_CONFIRMING ((uint32_t)0x4)
#define EFI_DHCP6_RELEASING ((uint32_t)0x5)
#define EFI_DHCP6_BOUND ((uint32_t)0x6)
#define EFI_DHCP6_RENEWING ((uint32_t)0x7)
#define EFI_DHCP6_REBINDING ((uint32_t)0x8)

struct efi_dhcp6_ia_address {
    struct efi_ipv6_address ip_address;
    uint32_t preferred_lifetime;
    uint32_t valid_lifetime;
};

struct efi_dhcp6_header {
    uint32_t header;
} __attribute__((__packed__));

#define EFI_DHCP6_HEADER_TRANSACTION_ID_SHIFT 0
#define EFI_DHCP6_HEADER_TRANSACTION_ID_MASK 0x00ffffff
#define EFI_DHCP6_HEADER_MESSAGE_TYPE_SHIFT 24
#define EFI_DHCP6_HEADER_MESSAGE_TYPE_MASK 0xff000000

struct efi_dhcp6_packet {
    uint32_t size;
    uint32_t length;
    struct __attribute__((__packed__)) {
        struct efi_dhcp6_header header;
        uint8_t option[1];
    } dhcp6;
} __attribute__((__packed__));

struct efi_dhcp6_ia {
    struct efi_dhcp6_ia_descriptor descriptor;
    uint32_t state;
    struct efi_dhcp6_packet *reply_packet;
    uint32_t ia_address_count;
    struct efi_dhcp6_ia_address ia_address[1];
};

struct efi_dhcp6_mode_data {
    struct efi_dhcp6_duid *client_id;
    struct efi_dhcp6_ia *ia;
};

struct efi_dhcp6_packet_option {
    uint16_t op_code;
    uint16_t op_len;
    uint8_t data[1];
} __attribute__((__packed__));

#define EFI_DHCP6_SEND_SOLICIT ((uint32_t)0x0)
#define EFI_DHCP6_RCVD_ADVERTISE ((uint32_t)0x1)
#define EFI_DHCP6_SELECT_ADVERTISE ((uint32_t)0x2)
#define EFI_DHCP6_SEND_REQUEST ((uint32_t)0x3)
#define EFI_DHCP6_RCVD_REPLY ((uint32_t)0x4)
#define EFI_DHCP6_RCVD_RECONFIGURE ((uint32_t)0x5)
#define EFI_DHCP6_SEND_DECLINE ((uint32_t)0x6)
#define EFI_DHCP6_SEND_CONFIRM ((uint32_t)0x7)
#define EFI_DHCP6_SEND_RELEASE ((uint32_t)0x8)
#define EFI_DHCP6_SEND_RENEW ((uint32_t)0x9)
#define EFI_DHCP6_SEND_REBIND ((uint32_t)0xa)

typedef efi_status (EFI_API *efi_dhcp6_callback)(
    struct efi_dhcp6_protocol *self,
    void *context,
    uint32_t current_state,
    uint32_t dhcp6_event,
    struct efi_dhcp6_packet *packet,
    struct efi_dhcp6_packet **new_packet
);

struct efi_dhcp6_retransmission {
    uint32_t irt;
    uint32_t mrc;
    uint32_t mrt;
    uint32_t mrd;
};

struct efi_dhcp6_config_data {
    efi_dhcp6_callback dhcp6_callback;
    void *callback_context;
    uint32_t option_count;
    struct efi_dhcp6_packet_option **option_list;
    struct efi_dhcp6_ia_descriptor ia_descriptor;
    efi_event ia_info_event;
    uint8_t reconfigure_accept;
    uint8_t rapid_commit;
    struct efi_dhcp6_retransmission *solicit_retransmission;
};

typedef efi_status (EFI_API *efi_dhcp6_get_mode_data)(
    struct efi_dhcp6_protocol *self,
    struct efi_dhcp6_mode_data *dhcp6_mode_data,
    struct efi_dhcp6_config_data *dhcp6_config_data
);

typedef efi_status (EFI_API *efi_dhcp6_configure)(
    struct efi_dhcp6_protocol *self,
    struct efi_dhcp6_config_data *dhcp6_cfg_data
);

typedef efi_status (EFI_API *efi_dhcp6_start)(struct efi_dhcp6_protocol *self);

typedef efi_status (EFI_API *efi_dhcp6_info_callback)(
    struct efi_dhcp6_protocol *self,
    void *context,
    struct efi_dhcp6_packet *packet
);

typedef efi_status (EFI_API *efi_dhcp6_info_request)(
    struct efi_dhcp6_protocol *self,
    bool send_client_id,
    struct efi_dhcp6_packet_option *option_request,
    uint32_t option_count,
    struct efi_dhcp6_packet_option *option_list[],
    struct efi_dhcp6_retransmission *retransmission,
    efi_event timeout_event,
    efi_dhcp6_info_callback reply_callback,
    void *callback_context
);

typedef efi_status (EFI_API *efi_dhcp6_renew_rebind)(
    struct efi_dhcp6_protocol *self,
    bool rebind_request
);

typedef efi_status (EFI_API *efi_dhcp6_decline)(
    struct efi_dhcp6_protocol *self,
    uint32_t address_count,
    struct efi_ipv6_address *addresses
);

typedef efi_status (EFI_API *efi_dhcp6_release)(
    struct efi_dhcp6_protocol *self,
    uint32_t address_count,
    struct efi_ipv6_address *addresses
);

typedef efi_status (EFI_API *efi_dhcp6_stop)(struct efi_dhcp6_protocol *self);

typedef efi_status (EFI_API *efi_dhcp6_parse)(
    struct efi_dhcp6_protocol *self,
    struct efi_dhcp6_packet *packet,
    uint32_t *option_count,
    struct efi_dhcp6_packet_option *packet_option_list[]
);

struct efi_dhcp6_protocol {
    efi_dhcp6_get_mode_data get_mode_data;
    efi_dhcp6_configure configure;
    efi_dhcp6_start start;
    efi_dhcp6_info_request info_request;
    efi_dhcp6_renew_rebind renew_rebind;
    efi_dhcp6_decline decline;
    efi_dhcp6_release release;
    efi_dhcp6_stop stop;
    efi_dhcp6_parse parse;
};

#define EFI_DNS4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xb625b186, 0xe063, 0x44f7, {0x89, 0x5, 0x6a, 0x74, 0xdc, 0x6f, 0x52, 0xb4}}

#define EFI_DNS4_PROTOCOL_GUID \
    {0xae3d28cc, 0xe05b, 0x4fa1, {0xa0, 0x11, 0x7e, 0xb5, 0x5a, 0x3f, 0x14, 0x1}}

struct efi_dns4_protocol;

struct efi_dns4_config_data {
    size_t dns_server_list_count;
    struct efi_ipv4_address *dns_server_list;
    uint8_t use_default_setting;
    uint8_t enable_dns_cache;
    uint8_t protocol;
    struct efi_ipv4_address station_ip;
    struct efi_ipv4_address subnet_mask;
    uint16_t local_port;
    uint32_t retry_count;
    uint32_t retry_interval;
};

struct efi_dns4_cache_entry {
    uint16_t *host_name;
    struct efi_ipv4_address *ip_address;
    uint32_t timeout;
};

struct efi_dns4_mode_data {
    struct efi_dns4_config_data dns_config_data;
    uint32_t dns_server_count;
    struct efi_ipv4_address *dns_server_list;
    uint32_t dns_cache_count;
    struct efi_dns4_cache_entry *dns_cache_list;
};

struct efi_dns_host_to_addr_data {
    uint32_t ip_count;
    struct efi_ipv4_address *ip_list;
};

struct efi_dns_addr_to_host_data {
    uint16_t *host_name;
};

struct efi_dns_resource_record {
    char *qname;
    uint16_t qtype;
    uint16_t qclass;
    uint32_t ttl;
    uint16_t data_length;
    char *rdata;
};

struct efi_dns_general_lookup_data {
    size_t rr_count;
    struct efi_dns_resource_record *rr_list;
};

struct efi_dns4_completion_token {
    efi_event event;
    efi_status status;
    uint32_t retry_count;
    uint32_t retry_interval;
    union {
        struct efi_dns_host_to_addr_data *h2a_data;
        struct efi_dns_addr_to_host_data *a2h_data;
        struct efi_dns_general_lookup_data *glookup_data;
    } rsp_data;
};

typedef efi_status (EFI_API *efi_dns4_get_mode_data)(
    struct efi_dns4_protocol *self,
    struct efi_dns4_mode_data *dns_mode_data
);

typedef efi_status (EFI_API *efi_dns4_configure)(
    struct efi_dns4_protocol *self,
    struct efi_dns4_config_data *dns_config_data
);

typedef efi_status (EFI_API *efi_dns4_host_name_to_ip)(
    struct efi_dns4_protocol *self,
    uint16_t *host_name,
    struct efi_dns4_completion_token *token
);

typedef efi_status (EFI_API *efi_dns4_ip_to_host_name)(
    struct efi_dns4_protocol *self,
    struct efi_ipv4_address ip_address,
    struct efi_dns4_completion_token *token
);

typedef efi_status (EFI_API *efi_dns4_general_lookup)(
    struct efi_dns4_protocol *self,
    char *qname,
    uint16_t qtype,
    uint16_t qclass,
    struct efi_dns4_completion_token *token
);

typedef efi_status (EFI_API *efi_dns4_update_dns_cache)(
    struct efi_dns4_protocol *self,
    bool delete_flag,
    bool override,
    struct efi_dns4_cache_entry dns_cache_entry
);

typedef efi_status (EFI_API *efi_dns4_poll)(struct efi_dns4_protocol *self);

typedef efi_status (EFI_API *efi_dns4_cancel)(
    struct efi_dns4_protocol *self,
    struct efi_dns4_completion_token *token
);

struct efi_dns4_protocol {
    efi_dns4_get_mode_data get_mode_data;
    efi_dns4_configure configure;
    efi_dns4_host_name_to_ip host_name_to_ip;
    efi_dns4_ip_to_host_name ip_to_host_name;
    efi_dns4_general_lookup general_look_up;
    efi_dns4_update_dns_cache update_dns_cache;
    efi_dns4_poll poll;
    efi_dns4_cancel cancel;
};

#define EFI_DNS6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x7f1647c8, 0xb76e, 0x44b2, {0xa5, 0x65, 0xf7, 0xf, 0xf1, 0x9c, 0xd1, 0x9e}}

#define EFI_DNS6_PROTOCOL_GUID \
    {0xca37bc1f, 0xa327, 0x4ae9, {0x82, 0x8a, 0x8c, 0x40, 0xd8, 0x50, 0x6a, 0x17}}

struct efi_dns6_protocol;

struct efi_dns6_config_data {
    uint8_t enable_dns_cache;
    uint8_t protocol;
    struct efi_ipv6_address station_ip;
    uint16_t local_port;
    uint32_t dns_server_count;
    struct efi_ipv6_address *dns_server_list;
    uint32_t retry_count;
    uint32_t retry_interval;
};

struct efi_dns6_cache_entry {
    uint16_t *host_name;
    struct efi_ipv6_address *ip_address;
    uint32_t timeout;
};

struct efi_dns6_mode_data {
    struct efi_dns6_config_data dns_config_data;
    uint32_t dns_server_count;
    struct efi_ipv6_address *dns_server_list;
    uint32_t dns_cache_count;
    struct efi_dns6_cache_entry *dns_cache_list;
};

struct efi_dns6_host_to_addr_data {
    uint32_t ip_count;
    struct efi_ipv6_address *ip_list;
};

struct efi_dns6_addr_to_host_data {
    uint16_t *host_name;
};

struct efi_dns6_resource_record {
    char *qname;
    uint16_t qtype;
    uint16_t qclass;
    uint32_t ttl;
    uint16_t data_length;
    char *rdata;
};

struct efi_dns6_general_lookup_data {
    size_t rr_count;
    struct efi_dns6_resource_record *rr_list;
};

struct efi_dns6_completion_token {
    efi_event event;
    efi_status status;
    uint32_t retry_count;
    uint32_t retry_interval;
    union {
        struct efi_dns6_host_to_addr_data *h2a_data;
        struct efi_dns6_addr_to_host_data *a2h_data;
        struct efi_dns6_general_lookup_data *glookup_data;
    } rsp_data;
};

typedef efi_status (EFI_API *efi_dns6_get_mode_data)(
    struct efi_dns6_protocol *self,
    struct efi_dns6_mode_data *dns_mode_data
);

typedef efi_status (EFI_API *efi_dns6_configure)(
    struct efi_dns6_protocol *self,
    struct efi_dns6_config_data *dns_config_data
);

typedef efi_status (EFI_API *efi_dns6_host_name_to_ip)(
    struct efi_dns6_protocol *self,
    uint16_t *host_name,
    struct efi_dns6_completion_token *token
);

typedef efi_status (EFI_API *efi_dns6_ip_to_host_name)(
    struct efi_dns6_protocol *self,
    struct efi_ipv6_address ip_address,
    struct efi_dns6_completion_token *token
);

typedef efi_status (EFI_API *efi_dns6_general_lookup)(
    struct efi_dns6_protocol *self,
    char *qname,
    uint16_t qtype,
    uint16_t qclass,
    struct efi_dns6_completion_token *token
);

typedef efi_status (EFI_API *efi_dns6_update_dns_cache)(
    struct efi_dns6_protocol *self,
    bool delete_flag,
    bool override,
    struct efi_dns6_cache_entry dns_cache_entry
);

typedef efi_status (EFI_API *efi_dns6_poll)(struct efi_dns6_protocol *self);

typedef efi_status (EFI_API *efi_dns6_cancel)(
    struct efi_dns6_protocol *self,
    struct efi_dns6_completion_token *token
);

struct efi_dns6_protocol {
    efi_dns6_get_mode_data get_mode_data;
    efi_dns6_configure configure;
    efi_dns6_host_name_to_ip host_name_to_ip;
    efi_dns6_ip_to_host_name ip_to_host_name;
    efi_dns6_general_lookup general_look_up;
    efi_dns6_update_dns_cache update_dns_cache;
    efi_dns6_poll poll;
    efi_dns6_cancel cancel;
};

#define EFI_HTTP_SERVICE_BINDING_PROTOCOL_GUID \
    {0xbdc8e6af, 0xd9bc, 0x4379, {0xa7, 0x2a, 0xe0, 0xc4, 0xe7, 0x5d, 0xae, 0x1c}}

#define EFI_HTTP_PROTOCOL_GUID \
    {0x7a59b29b, 0x910b, 0x4171, {0x82, 0x42, 0xa8, 0x5a, 0x0d, 0xf2, 0x5b, 0x5b}}

struct efi_http_protocol;

#define EFI_HTTP_VERSION10 ((uint32_t)0)
#define EFI_HTTP_VERSION11 ((uint32_t)1)
#define EFI_HTTP_VERSION_UNSUPPORTED ((uint32_t)2)

struct efi_httpv4_access_point {
    uint8_t use_default_address;
    struct efi_ipv4_address local_address;
    struct efi_ipv4_address local_subnet;
    uint16_t local_port;
};

struct efi_httpv6_access_point {
    struct efi_ipv6_address local_address;
    uint16_t local_port;
};

struct efi_http_config_data {
    uint32_t http_version;
    uint32_t time_out_millisec;
    uint8_t local_address_is_ipv6;
    union {
        struct efi_httpv4_access_point *ipv4_node;
        struct efi_httpv6_access_point *ipv6_node;
    } access_point;
};

typedef efi_status (EFI_API *efi_http_get_mode_data)(
    struct efi_http_protocol *self,
    struct efi_http_config_data *http_config_data
);

typedef efi_status (EFI_API *efi_http_configure)(
    struct efi_http_protocol *self,
    struct efi_http_config_data *http_config_data
);

#define EFI_HTTP_METHOD_GET ((uint32_t)0)
#define EFI_HTTP_METHOD_POST ((uint32_t)1)
#define EFI_HTTP_METHOD_PATCH ((uint32_t)2)
#define EFI_HTTP_METHOD_OPTIONS ((uint32_t)3)
#define EFI_HTTP_METHOD_CONNECT ((uint32_t)4)
#define EFI_HTTP_METHOD_HEAD ((uint32_t)5)
#define EFI_HTTP_METHOD_PUT ((uint32_t)6)
#define EFI_HTTP_METHOD_DELETE ((uint32_t)7)
#define EFI_HTTP_METHOD_TRACE ((uint32_t)8)
#define EFI_HTTP_METHOD_MAX ((uint32_t)9)

struct efi_http_request_data {
    uint32_t method;
    uint16_t *url;
};

struct efi_http_connect_request_data {
    struct efi_http_request_data base;
    uint16_t *proxy_url;
};

#define EFI_HTTP_STATUS_UNSUPPORTED_STATUS ((uint32_t)0)
#define EFI_HTTP_STATUS_100_CONTINUE ((uint32_t)1)
#define EFI_HTTP_STATUS_101_SWITCHING_PROTOCOLS ((uint32_t)2)
#define EFI_HTTP_STATUS_200_OK ((uint32_t)3)
#define EFI_HTTP_STATUS_201_CREATED ((uint32_t)4)
#define EFI_HTTP_STATUS_202_ACCEPTED ((uint32_t)5)
#define EFI_HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION ((uint32_t)6)
#define EFI_HTTP_STATUS_204_NO_CONTENT ((uint32_t)7)
#define EFI_HTTP_STATUS_205_RESET_CONTENT ((uint32_t)8)
#define EFI_HTTP_STATUS_206_PARTIAL_CONTENT ((uint32_t)9)
#define EFI_HTTP_STATUS_300_MULTIPLE_CHOICES ((uint32_t)10)
#define EFI_HTTP_STATUS_301_MOVED_PERMANENTLY ((uint32_t)11)
#define EFI_HTTP_STATUS_302_FOUND ((uint32_t)12)
#define EFI_HTTP_STATUS_303_SEE_OTHER ((uint32_t)13)
#define EFI_HTTP_STATUS_304_NOT_MODIFIED ((uint32_t)14)
#define EFI_HTTP_STATUS_305_USE_PROXY ((uint32_t)15)
#define EFI_HTTP_STATUS_307_TEMPORARY_REDIRECT ((uint32_t)16)
#define EFI_HTTP_STATUS_400_BAD_REQUEST ((uint32_t)17)
#define EFI_HTTP_STATUS_401_UNAUTHORIZED ((uint32_t)18)
#define EFI_HTTP_STATUS_402_PAYMENT_REQUIRED ((uint32_t)19)
#define EFI_HTTP_STATUS_403_FORBIDDEN ((uint32_t)20)
#define EFI_HTTP_STATUS_404_NOT_FOUND ((uint32_t)21)
#define EFI_HTTP_STATUS_405_METHOD_NOT_ALLOWED ((uint32_t)22)
#define EFI_HTTP_STATUS_406_NOT_ACCEPTABLE ((uint32_t)23)
#define EFI_HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED ((uint32_t)24)
#define EFI_HTTP_STATUS_408_REQUEST_TIME_OUT ((uint32_t)25)
#define EFI_HTTP_STATUS_409_CONFLICT ((uint32_t)26)
#define EFI_HTTP_STATUS_410_GONE ((uint32_t)27)
#define EFI_HTTP_STATUS_411_LENGTH_REQUIRED ((uint32_t)28)
#define EFI_HTTP_STATUS_412_PRECONDITION_FAILED ((uint32_t)29)
#define EFI_HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE ((uint32_t)30)
#define EFI_HTTP_STATUS_414_REQUEST_URI_TOO_LARGE ((uint32_t)31)
#define EFI_HTTP_STATUS_415_UNSUPPORTED_MEDIA_TYPE ((uint32_t)32)
#define EFI_HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED ((uint32_t)33)
#define EFI_HTTP_STATUS_417_EXPECTATION_FAILED ((uint32_t)34)
#define EFI_HTTP_STATUS_500_INTERNAL_SERVER_ERROR ((uint32_t)35)
#define EFI_HTTP_STATUS_501_NOT_IMPLEMENTED ((uint32_t)36)
#define EFI_HTTP_STATUS_502_BAD_GATEWAY ((uint32_t)37)
#define EFI_HTTP_STATUS_503_SERVICE_UNAVAILABLE ((uint32_t)38)
#define EFI_HTTP_STATUS_504_GATEWAY_TIME_OUT ((uint32_t)39)
#define EFI_HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED ((uint32_t)40)
#define EFI_HTTP_STATUS_308_PERMANENT_REDIRECT ((uint32_t)41)

struct efi_http_response_data {
    uint32_t status_code;
};

struct efi_http_header {
    char *field_name;
    char *field_value;
};

struct efi_http_message {
    union {
        struct efi_http_request_data *request;
        struct efi_http_response_data *response;
    } data;
    size_t header_count;
    struct efi_http_header *headers;
    size_t body_length;
    void *body;
};

struct efi_http_token {
    efi_event event;
    efi_status status;
    struct efi_http_message *message;
};

typedef efi_status (EFI_API *efi_http_request)(
    struct efi_http_protocol *self,
    struct efi_http_token *token
);

typedef efi_status (EFI_API *efi_http_cancel)(
    struct efi_http_protocol *self,
    struct efi_http_token *token
);

typedef efi_status (EFI_API *efi_http_response)(
    struct efi_http_protocol *self,
    struct efi_http_token *token
);

typedef efi_status (EFI_API *efi_http_poll)(struct efi_http_protocol *self);

struct efi_http_protocol {
    efi_http_get_mode_data get_mode_data;
    efi_http_configure configure;
    efi_http_request request;
    efi_http_cancel cancel;
    efi_http_response response;
    efi_http_poll poll;
};

#define EFI_HTTP_UTILITIES_PROTOCOL_GUID \
    {0x3e35c163, 0x4074, 0x45dd, {0x43, 0x1e, 0x23, 0x98, 0x9d, 0xd8, 0x6b, 0x32}}

struct efi_http_utilities_protocol;

typedef efi_status (EFI_API *efi_http_utils_build)(
    struct efi_http_utilities_protocol *self,
    size_t seed_message_size,
    void *seed_message,
    size_t delete_count,
    char *delete_list[],
    size_t append_count,
    struct efi_http_header *append_list[],
    size_t *new_message_size,
    void **new_message
);

// self is the utilities protocol, as described; the prototype prints struct
// efi_http_protocol.
typedef efi_status (EFI_API *efi_http_utils_parse)(
    struct efi_http_utilities_protocol *self,
    char *http_message,
    size_t http_message_size,
    struct efi_http_header **header_fields,
    size_t *field_count
);

struct efi_http_utilities_protocol {
    efi_http_utils_build build;
    efi_http_utils_parse parse;
};

#define EFI_REST_PROTOCOL_GUID \
    {0x0db48a36, 0x4e54, 0xea9c, {0x9b, 0x09, 0x1e, 0xa5, 0xbe, 0x3a, 0x66, 0x0b}}

struct efi_rest_protocol;

// Shared by struct efi_rest_ex_protocol, whose section reprints it with a
// struct efi_rest_ex_protocol *self.
typedef efi_status (EFI_API *efi_rest_send_receive)(
    struct efi_rest_protocol *self,
    struct efi_http_message *request_message,
    struct efi_http_message *response_message
);

typedef efi_status (EFI_API *efi_rest_get_time)(
    struct efi_rest_protocol *self,
    struct efi_time *time
);

struct efi_rest_protocol {
    efi_rest_send_receive send_receive;
    efi_rest_get_time get_service_time;
};

#define EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID \
    {0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59}}

#define EFI_REST_EX_PROTOCOL_GUID \
    {0x55648b91, 0xe7d, 0x40a3, {0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97}}

struct efi_rest_ex_protocol;

struct efi_rest_ex_service_info_ver {
    uint8_t major;
    uint8_t minor;
};

struct efi_rest_ex_service_info_header {
    uint32_t length;
    struct efi_rest_ex_service_info_ver rest_service_info_ver;
};

#define EFI_REST_EX_SERVICE_UNSPECIFIC ((uint32_t)1)
#define EFI_REST_EX_SERVICE_REDFISH ((uint32_t)2)
#define EFI_REST_EX_SERVICE_ODATA ((uint32_t)3)
#define EFI_REST_EX_SERVICE_VENDOR_SPECIFIC ((uint32_t)0xff)
#define EFI_REST_EX_SERVICE_TYPE_MAX ((uint32_t)256)

#define EFI_REST_EX_SERVICE_IN_BAND_ACCESS ((uint32_t)1)
#define EFI_REST_EX_SERVICE_OUT_OF_BAND_ACCESS ((uint32_t)2)
#define EFI_REST_EX_SERVICE_ACCESS_MODE_MAX ((uint32_t)3)

#define EFI_REST_EX_CONFIG_TYPE_HTTP ((uint32_t)0)
#define EFI_REST_EX_CONFIG_TYPE_UNSPECIFIC ((uint32_t)1)
#define EFI_REST_EX_CONFIG_TYPE_MAX ((uint32_t)2)

struct efi_rest_ex_service_info_v_1_0 {
    struct efi_rest_ex_service_info_header efi_rest_ex_service_info_header;
    uint32_t rest_ex_service_type;
    uint32_t rest_service_access_mode;
    struct efi_guid vendor_rest_service_name;
    uint32_t vendor_specific_data_length;
    uint8_t *vendor_specifc_data;
    uint32_t rest_ex_config_type;
    uint8_t rest_ex_config_data_length;
};

union efi_rest_ex_service_info {
    struct efi_rest_ex_service_info_header efi_rest_ex_service_info_header;
    struct efi_rest_ex_service_info_v_1_0 efi_rest_ex_service_info_v10;
};

struct efi_rest_ex_http_config_data {
    struct efi_http_config_data http_config_data;
    uint32_t send_receive_timeout;
};

typedef efi_status (EFI_API *efi_rest_ex_get_service)(
    struct efi_rest_ex_protocol *self,
    union efi_rest_ex_service_info **rest_ex_service_info
);

typedef uint8_t *efi_rest_ex_config_data;

typedef efi_status (EFI_API *efi_rest_ex_get_mode_data)(
    struct efi_rest_ex_protocol *self,
    efi_rest_ex_config_data *rest_ex_config_data
);

typedef efi_status (EFI_API *efi_rest_ex_configure)(
    struct efi_rest_ex_protocol *self,
    efi_rest_ex_config_data rest_ex_config_data
);

struct efi_rest_ex_token {
    efi_event event;
    efi_status status;
    struct efi_http_message *response_message;
};

typedef efi_status (EFI_API *efi_rest_ex_async_send_receive)(
    struct efi_rest_ex_protocol *self,
    struct efi_http_message *request_message,
    struct efi_rest_ex_token *rest_ex_token,
    uintptr_t *time_out_in_milli_seconds
);

typedef efi_status (EFI_API *efi_rest_ex_event_service)(
    struct efi_rest_ex_protocol *self,
    struct efi_http_message *request_message,
    struct efi_rest_ex_token *rest_ex_token
);

struct efi_rest_ex_protocol {
    efi_rest_send_receive send_receive;
    efi_rest_get_time get_service_time;
    efi_rest_ex_get_service get_service;
    efi_rest_ex_get_mode_data get_mode_data;
    efi_rest_ex_configure configure;
    efi_rest_ex_async_send_receive async_send_receive;
    efi_rest_ex_event_service event_service;
};

#define EFI_REST_JSON_STRUCTURE_PROTOCOL_GUID \
    {0xa9a048f6, 0x48a0, 0x4714, {0xb7, 0xda, 0xa9, 0xad, 0x87, 0xd4, 0xda, 0xc9}}

struct efi_rest_json_structure_protocol;

typedef char *efi_rest_json_resource_type_datatype;

struct efi_rest_json_resource_type_namespace {
    char *resource_type_name;
    char *major_version;
    char *minor_version;
    char *errata_version;
};

struct efi_rest_json_resource_type_identifier {
#ifdef __cplusplus
    struct efi_rest_json_resource_type_namespace namespace_;
#else
    struct efi_rest_json_resource_type_namespace namespace;
#endif
    efi_rest_json_resource_type_datatype datatype;
};

struct efi_rest_json_structure_supported;

struct efi_rest_json_structure_supported {
    struct efi_rest_json_structure_supported *next;
    struct efi_rest_json_resource_type_identifier json_resource_type;
};

struct efi_rest_json_structure_header {
    struct efi_rest_json_resource_type_identifier json_rsrc_identifier;
    void *json_structure_pointer;
};

typedef efi_status (EFI_API *efi_rest_json_structure_to_structure)(
    struct efi_rest_json_structure_protocol *self,
    struct efi_rest_json_resource_type_identifier *json_rsrc_identifier,
    char *resource_json_text,
    struct efi_rest_json_structure_header **json_structure
);

typedef efi_status (EFI_API *efi_rest_json_structure_to_json)(
    struct efi_rest_json_structure_protocol *self,
    struct efi_rest_json_structure_header *json_structure_header,
    char **resource_json_text
);

typedef efi_status (EFI_API *efi_rest_json_structure_destory_structure)(
    struct efi_rest_json_structure_protocol *self,
    struct efi_rest_json_structure_header *json_structure_header
);

typedef efi_status (EFI_API *efi_rest_json_structure_register)(
    struct efi_rest_json_structure_protocol *self,
    struct efi_rest_json_structure_supported *json_structure_supported,
    efi_rest_json_structure_to_structure to_structure,
    efi_rest_json_structure_to_json to_json,
    efi_rest_json_structure_destory_structure destroy_structure
);

struct efi_rest_json_structure_protocol {
    efi_rest_json_structure_register register_;
    efi_rest_json_structure_to_structure to_structure;
    efi_rest_json_structure_to_json to_json;
    efi_rest_json_structure_destory_structure destory_structure;
};

#ifdef __cplusplus
}
#endif

#endif
