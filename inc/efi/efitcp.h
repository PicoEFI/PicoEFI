#ifndef EFI_EFITCP_H_
#define EFI_EFITCP_H_

#include "efiapi.h"
#include "efinet.h"
#include "efiip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x00720665, 0x67EB, 0x4a99, {0xBA, 0xF7, 0xD3, 0xC3, 0x3A, 0x1C, 0x7C, 0xC9}}

#define EFI_TCP4_PROTOCOL_GUID \
    {0x65530BC7, 0xA359, 0x410f, {0xB0, 0x10, 0x5A, 0xAD, 0xC7, 0xEC, 0x2B, 0x62}}

struct efi_tcp4_protocol;

struct efi_tcp4_access_point {
    uint8_t use_default_address;
    struct efi_ipv4_address station_address;
    struct efi_ipv4_address subnet_mask;
    uint16_t station_port;
    struct efi_ipv4_address remote_address;
    uint16_t remote_port;
    uint8_t active_flag;
};

struct efi_tcp4_option {
    uint32_t receive_buffer_size;
    uint32_t send_buffer_size;
    uint32_t max_syn_back_log;
    uint32_t connection_timeout;
    uint32_t data_retries;
    uint32_t fin_timeout;
    uint32_t time_wait_timeout;
    uint32_t keep_alive_probes;
    uint32_t keep_alive_time;
    uint32_t keep_alive_interval;
    uint8_t enable_nagle;
    uint8_t enable_time_stamp;
    uint8_t enable_window_scaling;
    uint8_t enable_selective_ack;
    uint8_t enable_path_mtu_discovery;
};

/* control_option may be NULL, as described (and a pointer in TCPv6); printed by value. */
struct efi_tcp4_config_data {
    uint8_t type_of_service;
    uint8_t time_to_live;
    struct efi_tcp4_access_point access_point;
    struct efi_tcp4_option *control_option;
};

#define EFI_TCP4_STATE_CLOSED ((uint32_t)0)
#define EFI_TCP4_STATE_LISTEN ((uint32_t)1)
#define EFI_TCP4_STATE_SYN_SENT ((uint32_t)2)
#define EFI_TCP4_STATE_SYN_RECEIVED ((uint32_t)3)
#define EFI_TCP4_STATE_ESTABLISHED ((uint32_t)4)
#define EFI_TCP4_STATE_FIN_WAIT1 ((uint32_t)5)
#define EFI_TCP4_STATE_FIN_WAIT2 ((uint32_t)6)
#define EFI_TCP4_STATE_CLOSING ((uint32_t)7)
#define EFI_TCP4_STATE_TIME_WAIT ((uint32_t)8)
#define EFI_TCP4_STATE_CLOSE_WAIT ((uint32_t)9)
#define EFI_TCP4_STATE_LAST_ACK ((uint32_t)10)

typedef efi_status (EFI_API *efi_tcp4_get_mode_data)(
    struct efi_tcp4_protocol *self,
    uint32_t *tcp4_state,
    struct efi_tcp4_config_data *tcp4_config_data,
    struct efi_ip4_mode_data *ip4_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_tcp4_configure)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_config_data *tcp_config_data
);

typedef efi_status (EFI_API *efi_tcp4_routes)(
    struct efi_tcp4_protocol *self,
    bool delete_route,
    struct efi_ipv4_address *subnet_address,
    struct efi_ipv4_address *subnet_mask,
    struct efi_ipv4_address *gateway_address
);

struct efi_tcp4_completion_token {
    efi_event event;
    efi_status status;
};

struct efi_tcp4_connection_token {
    struct efi_tcp4_completion_token completion_token;
};

typedef efi_status (EFI_API *efi_tcp4_connect)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_connection_token *connection_token
);

struct efi_tcp4_listen_token {
    struct efi_tcp4_completion_token completion_token;
    efi_handle new_child_handle;
};

typedef efi_status (EFI_API *efi_tcp4_accept)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_listen_token *listen_token
);

struct efi_tcp4_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_tcp4_receive_data {
    uint8_t urgent_flag;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_tcp4_fragment_data fragment_table[1];
};

struct efi_tcp4_transmit_data {
    uint8_t push;
    uint8_t urgent;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_tcp4_fragment_data fragment_table[1];
};

struct efi_tcp4_io_token {
    struct efi_tcp4_completion_token completion_token;
    union {
        struct efi_tcp4_receive_data *rx_data;
        struct efi_tcp4_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_tcp4_transmit)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_io_token *token
);

typedef efi_status (EFI_API *efi_tcp4_receive)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_io_token *token
);

struct efi_tcp4_close_token {
    struct efi_tcp4_completion_token completion_token;
    uint8_t abort_on_close;
};

typedef efi_status (EFI_API *efi_tcp4_close)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_close_token *close_token
);

typedef efi_status (EFI_API *efi_tcp4_cancel)(
    struct efi_tcp4_protocol *self,
    struct efi_tcp4_completion_token *token
);

typedef efi_status (EFI_API *efi_tcp4_poll)(struct efi_tcp4_protocol *self);

struct efi_tcp4_protocol {
    efi_tcp4_get_mode_data get_mode_data;
    efi_tcp4_configure configure;
    efi_tcp4_routes routes;
    efi_tcp4_connect connect;
    efi_tcp4_accept accept;
    efi_tcp4_transmit transmit;
    efi_tcp4_receive receive;
    efi_tcp4_close close;
    efi_tcp4_cancel cancel;
    efi_tcp4_poll poll;
};

#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0xec20eb79, 0x6c1a, 0x4664, {0x9a, 0x0d, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64}}

#define EFI_TCP6_PROTOCOL_GUID \
    {0x46e44855, 0xbd60, 0x4ab7, {0xab, 0x0d, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77}}

struct efi_tcp6_protocol;

struct efi_tcp6_access_point {
    struct efi_ipv6_address station_address;
    uint16_t station_port;
    struct efi_ipv6_address remote_address;
    uint16_t remote_port;
    uint8_t active_flag;
};

struct efi_tcp6_option {
    uint32_t receive_buffer_size;
    uint32_t send_buffer_size;
    uint32_t max_syn_back_log;
    uint32_t connection_timeout;
    uint32_t data_retries;
    uint32_t fin_timeout;
    uint32_t time_wait_timeout;
    uint32_t keep_alive_probes;
    uint32_t keep_alive_time;
    uint32_t keep_alive_interval;
    uint8_t enable_nagle;
    uint8_t enable_time_stamp;
    uint8_t enable_window_scaling;
    uint8_t enable_selective_ack;
    uint8_t enable_path_mtu_discovery;
};

struct efi_tcp6_config_data {
    uint8_t traffic_class;
    uint8_t hop_limit;
    struct efi_tcp6_access_point access_point;
    struct efi_tcp6_option *control_option;
};

#define EFI_TCP6_STATE_CLOSED ((uint32_t)0)
#define EFI_TCP6_STATE_LISTEN ((uint32_t)1)
#define EFI_TCP6_STATE_SYN_SENT ((uint32_t)2)
#define EFI_TCP6_STATE_SYN_RECEIVED ((uint32_t)3)
#define EFI_TCP6_STATE_ESTABLISHED ((uint32_t)4)
#define EFI_TCP6_STATE_FIN_WAIT1 ((uint32_t)5)
#define EFI_TCP6_STATE_FIN_WAIT2 ((uint32_t)6)
#define EFI_TCP6_STATE_CLOSING ((uint32_t)7)
#define EFI_TCP6_STATE_TIME_WAIT ((uint32_t)8)
#define EFI_TCP6_STATE_CLOSE_WAIT ((uint32_t)9)
#define EFI_TCP6_STATE_LAST_ACK ((uint32_t)10)

typedef efi_status (EFI_API *efi_tcp6_get_mode_data)(
    struct efi_tcp6_protocol *self,
    uint32_t *tcp6_state,
    struct efi_tcp6_config_data *tcp6_config_data,
    struct efi_ip6_mode_data *ip6_mode_data,
    struct efi_managed_network_config_data *mnp_config_data,
    struct efi_simple_network_mode *snp_mode_data
);

typedef efi_status (EFI_API *efi_tcp6_configure)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_config_data *tcp6_config_data
);

struct efi_tcp6_completion_token {
    efi_event event;
    efi_status status;
};

struct efi_tcp6_connection_token {
    struct efi_tcp6_completion_token completion_token;
};

typedef efi_status (EFI_API *efi_tcp6_connect)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_connection_token *connection_token
);

struct efi_tcp6_listen_token {
    struct efi_tcp6_completion_token completion_token;
    efi_handle new_child_handle;
};

typedef efi_status (EFI_API *efi_tcp6_accept)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_listen_token *listen_token
);

struct efi_tcp6_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

struct efi_tcp6_receive_data {
    uint8_t urgent_flag;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_tcp6_fragment_data fragment_table[1];
};

struct efi_tcp6_transmit_data {
    uint8_t push;
    uint8_t urgent;
    uint32_t data_length;
    uint32_t fragment_count;
    struct efi_tcp6_fragment_data fragment_table[1];
};

struct efi_tcp6_io_token {
    struct efi_tcp6_completion_token completion_token;
    union {
        struct efi_tcp6_receive_data *rx_data;
        struct efi_tcp6_transmit_data *tx_data;
    } packet;
};

typedef efi_status (EFI_API *efi_tcp6_transmit)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_io_token *token
);

typedef efi_status (EFI_API *efi_tcp6_receive)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_io_token *token
);

struct efi_tcp6_close_token {
    struct efi_tcp6_completion_token completion_token;
    uint8_t abort_on_close;
};

typedef efi_status (EFI_API *efi_tcp6_close)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_close_token *close_token
);

typedef efi_status (EFI_API *efi_tcp6_cancel)(
    struct efi_tcp6_protocol *self,
    struct efi_tcp6_completion_token *token
);

typedef efi_status (EFI_API *efi_tcp6_poll)(struct efi_tcp6_protocol *self);

struct efi_tcp6_protocol {
    efi_tcp6_get_mode_data get_mode_data;
    efi_tcp6_configure configure;
    efi_tcp6_connect connect;
    efi_tcp6_accept accept;
    efi_tcp6_transmit transmit;
    efi_tcp6_receive receive;
    efi_tcp6_close close;
    efi_tcp6_cancel cancel;
    efi_tcp6_poll poll;
};

#ifdef __cplusplus
}
#endif

#endif
