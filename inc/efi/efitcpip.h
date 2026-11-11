#ifndef EFI_EFITCPIP_H_
#define EFI_EFITCPIP_H_

#include "efiapi.h"
#include "efiip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_IP4_CONFIG2_PROTOCOL_GUID \
    {0x5b446ed1, 0xe30b, 0x4faa, {0x87, 0x1a, 0x36, 0x54, 0xec, 0xa3, 0x60, 0x80}}

struct efi_ip4_config2_protocol;

#define EFI_IP4_CONFIG2_DATA_TYPE_INTERFACE_INFO ((uint32_t)0)
#define EFI_IP4_CONFIG2_DATA_TYPE_POLICY ((uint32_t)1)
#define EFI_IP4_CONFIG2_DATA_TYPE_MANUAL_ADDRESS ((uint32_t)2)
#define EFI_IP4_CONFIG2_DATA_TYPE_GATEWAY ((uint32_t)3)
#define EFI_IP4_CONFIG2_DATA_TYPE_DNS_SERVER ((uint32_t)4)
#define EFI_IP4_CONFIG2_DATA_TYPE_MAXIMUM ((uint32_t)5)

#define EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE 32

struct efi_ip4_config2_interface_info {
    uint16_t name[EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE];
    uint8_t if_type;
    uint32_t hw_address_size;
    struct efi_mac_address hw_address;
    struct efi_ipv4_address station_address;
    struct efi_ipv4_address subnet_mask;
    uint32_t route_table_size;
    struct efi_ip4_route_table *route_table;
};

#define EFI_IP4_CONFIG2_POLICY_STATIC ((uint32_t)0)
#define EFI_IP4_CONFIG2_POLICY_DHCP ((uint32_t)1)
#define EFI_IP4_CONFIG2_POLICY_MAX ((uint32_t)2)

struct efi_ip4_config2_manual_address {
    struct efi_ipv4_address address;
    struct efi_ipv4_address subnet_mask;
};

typedef efi_status (EFI_API *efi_ip4_config2_set_data)(
    struct efi_ip4_config2_protocol *self,
    uint32_t data_type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_ip4_config2_get_data)(
    struct efi_ip4_config2_protocol *self,
    uint32_t data_type,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_ip4_config2_register_notify)(
    struct efi_ip4_config2_protocol *self,
    uint32_t data_type,
    efi_event event
);

typedef efi_status (EFI_API *efi_ip4_config2_unregister_notify)(
    struct efi_ip4_config2_protocol *self,
    uint32_t data_type,
    efi_event event
);

struct efi_ip4_config2_protocol {
    efi_ip4_config2_set_data set_data;
    efi_ip4_config2_get_data get_data;
    efi_ip4_config2_register_notify register_data_notify;
    efi_ip4_config2_unregister_notify unregister_data_notify;
};

#define EFI_IP6_CONFIG_PROTOCOL_GUID \
    {0x937fe521, 0x95ae, 0x4d1a, {0x89, 0x29, 0x48, 0xbc, 0xd9, 0x0a, 0xd3, 0x1a}}

struct efi_ip6_config_protocol;

#define EFI_IP6_CONFIG_DATA_TYPE_INTERFACE_INFO ((uint32_t)0)
#define EFI_IP6_CONFIG_DATA_TYPE_ALT_INTERFACE_ID ((uint32_t)1)
#define EFI_IP6_CONFIG_DATA_TYPE_POLICY ((uint32_t)2)
#define EFI_IP6_CONFIG_DATA_TYPE_DUP_ADDR_DETECT_TRANSMITS ((uint32_t)3)
#define EFI_IP6_CONFIG_DATA_TYPE_MANUAL_ADDRESS ((uint32_t)4)
#define EFI_IP6_CONFIG_DATA_TYPE_GATEWAY ((uint32_t)5)
#define EFI_IP6_CONFIG_DATA_TYPE_DNS_SERVER ((uint32_t)6)
#define EFI_IP6_CONFIG_DATA_TYPE_MAXIMUM ((uint32_t)7)

struct efi_ip6_config_interface_info {
    uint16_t name[32];
    uint8_t if_type;
    uint32_t hw_address_size;
    struct efi_mac_address hw_address;
    uint32_t address_info_count;
    struct efi_ip6_address_info *address_info;
    uint32_t route_count;
    struct efi_ip6_route_table *route_table;
};

struct efi_ip6_config_interface_id {
    uint8_t id[8];
};

#define EFI_IP6_CONFIG_POLICY_MANUAL ((uint32_t)0)
#define EFI_IP6_CONFIG_POLICY_AUTOMATIC ((uint32_t)1)

struct efi_ip6_config_dup_addr_detect_transmits {
    uint32_t dup_addr_detect_transmits;
};

struct efi_ip6_config_manual_address {
    struct efi_ipv6_address address;
    uint8_t is_anycast;
    uint8_t prefix_length;
};

typedef efi_status (EFI_API *efi_ip6_config_set_data)(
    struct efi_ip6_config_protocol *self,
    uint32_t data_type,
    size_t data_size,
    void *data
);

typedef efi_status (EFI_API *efi_ip6_config_get_data)(
    struct efi_ip6_config_protocol *self,
    uint32_t data_type,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_ip6_config_register_notify)(
    struct efi_ip6_config_protocol *self,
    uint32_t data_type,
    efi_event event
);

typedef efi_status (EFI_API *efi_ip6_config_unregister_notify)(
    struct efi_ip6_config_protocol *self,
    uint32_t data_type,
    efi_event event
);

struct efi_ip6_config_protocol {
    efi_ip6_config_set_data set_data;
    efi_ip6_config_get_data get_data;
    efi_ip6_config_register_notify register_data_notify;
    efi_ip6_config_unregister_notify unregister_data_notify;
};

#define EFI_IPSEC_CONFIG_PROTOCOL_GUID \
    {0xce5e5929, 0xc7a3, 0x4602, {0xad, 0x9e, 0xc9, 0xda, 0xf9, 0x4e, 0xbf, 0xcf}}

struct efi_ipsec_config_protocol;

#define EFI_IPSEC_CONFIG_DATA_TYPE_SPD ((uint32_t)0)
#define EFI_IPSEC_CONFIG_DATA_TYPE_SAD ((uint32_t)1)
#define EFI_IPSEC_CONFIG_DATA_TYPE_PAD ((uint32_t)2)
#define EFI_IPSEC_CONFIG_DATA_TYPE_MAXIMUM ((uint32_t)3)

struct efi_ip_address_info {
    union efi_ip_address address;
    uint8_t prefix_length;
};

struct efi_ipsec_spd_selector {
    uint32_t local_address_count;
    struct efi_ip_address_info *local_address;
    uint32_t remote_address_count;
    struct efi_ip_address_info *remote_address;
    uint16_t next_layer_protocol;
    uint16_t local_port;
    uint16_t local_port_range;
    uint16_t remote_port;
    uint16_t remote_port_range;
};

#define EFI_IPSEC_AH ((uint32_t)0)
#define EFI_IPSEC_ESP ((uint32_t)1)

struct efi_ipsec_sa_id {
    uint32_t spi;
    uint32_t proto;
    union efi_ip_address dest_address;
};

#define EFI_MAX_PEERID_LEN 128

struct efi_ipsec_pad_id {
    uint8_t peer_id_valid;
    union {
        struct efi_ip_address_info ip_address;
        uint8_t peer_id[EFI_MAX_PEERID_LEN];
    } id;
};

union efi_ipsec_config_selector {
    struct efi_ipsec_spd_selector spd_selector;
    struct efi_ipsec_sa_id sa_id;
    struct efi_ipsec_pad_id pad_id;
};

#define EFI_IPSEC_IN_BOUND ((uint32_t)0)
#define EFI_IPSEC_OUT_BOUND ((uint32_t)1)

#define EFI_IPSEC_ACTION_DISCARD ((uint32_t)0)
#define EFI_IPSEC_ACTION_BYPASS ((uint32_t)1)
#define EFI_IPSEC_ACTION_PROTECT ((uint32_t)2)

struct efi_ipsec_sa_lifetime {
    uint64_t byte_count;
    uint64_t soft_lifetime;
    uint64_t hard_lifetime;
};

#define EFI_IPSEC_TRANSPORT ((uint32_t)0)
#define EFI_IPSEC_TUNNEL ((uint32_t)1)

#define EFI_IPSEC_TUNNEL_CLEAR_DF ((uint32_t)0)
#define EFI_IPSEC_TUNNEL_SET_DF ((uint32_t)1)
#define EFI_IPSEC_TUNNEL_COPY_DF ((uint32_t)2)

struct efi_ipsec_tunnel_option {
    union efi_ip_address local_tunnel_address;
    union efi_ip_address remote_tunnel_address;
    uint32_t df;
};

struct efi_ipsec_process_policy {
    uint8_t ext_seq_num;
    uint8_t seq_overflow;
    uint8_t frag_check;
    struct efi_ipsec_sa_lifetime sa_lifetime;
    uint32_t mode;
    struct efi_ipsec_tunnel_option *tunnel_option;
    uint32_t proto;
    uint8_t auth_algo_id;
    uint8_t enc_algo_id;
};

/* name holds a null-terminated ASCII string, as described; printed as an array of pointers. */
struct efi_ipsec_spd_data {
    uint8_t name[EFI_MAX_PEERID_LEN];
    uint32_t package_flag;
    uint32_t traffic_direction;
    uint32_t action;
    struct efi_ipsec_process_policy *processing_policy;
    size_t sa_id_count;
    struct efi_ipsec_sa_id *sa_id[1];
};

struct efi_ipsec_ah_algo_info {
    uint8_t auth_algo_id;
    size_t key_length;
    void *key;
};

struct efi_ipsec_esp_algo_info {
    uint8_t enc_algo_id;
    size_t enc_key_length;
    void *enc_key;
    uint8_t auth_algo_id;
    size_t auth_key_length;
    void *auth_key;
};

union efi_ipsec_algo_info {
    struct efi_ipsec_ah_algo_info ah_algo_info;
    struct efi_ipsec_esp_algo_info esp_algo_info;
};

struct efi_ipsec_sa_data {
    uint32_t mode;
    uint64_t sn_count;
    uint8_t anti_replay_windows;
    union efi_ipsec_algo_info algo_info;
    struct efi_ipsec_sa_lifetime sa_lifetime;
    uint32_t path_mtu;
    struct efi_ipsec_spd_selector *spd_selector;
    uint8_t manual_set;
};

struct efi_ipsec_sa_data2 {
    uint32_t mode;
    uint64_t sn_count;
    uint8_t anti_replay_windows;
    union efi_ipsec_algo_info algo_info;
    struct efi_ipsec_sa_lifetime sa_lifetime;
    uint32_t path_mtu;
    struct efi_ipsec_spd_selector *spd_selector;
    uint8_t manual_set;
    union efi_ip_address tunnel_source_address;
    union efi_ip_address tunnel_destination_address;
};

#define EFI_IPSEC_AUTH_PROTOCOL_IKEV1 ((uint32_t)0)
#define EFI_IPSEC_AUTH_PROTOCOL_IKEV2 ((uint32_t)1)
#define EFI_IPSEC_AUTH_PROTOCOL_MAXIMUM ((uint32_t)2)

#define EFI_IPSEC_AUTH_METHOD_PRE_SHARED_SECRET ((uint32_t)0)
#define EFI_IPSEC_AUTH_METHOD_CERTIFICATES ((uint32_t)1)
#define EFI_IPSEC_AUTH_METHOD_MAXIMUM ((uint32_t)2)

struct efi_ipsec_pad_data {
    uint32_t auth_protocol;
    uint32_t auth_method;
    uint8_t ike_id_flag;
    size_t auth_data_size;
    void *auth_data;
    size_t revocation_data_size;
    void *revocation_data;
};

typedef efi_status (EFI_API *efi_ipsec_config_set_data)(
    struct efi_ipsec_config_protocol *self,
    uint32_t data_type,
    union efi_ipsec_config_selector *selector,
    void *data,
    union efi_ipsec_config_selector *insert_before
);

typedef efi_status (EFI_API *efi_ipsec_config_get_data)(
    struct efi_ipsec_config_protocol *self,
    uint32_t data_type,
    union efi_ipsec_config_selector *selector,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_ipsec_config_get_next_selector)(
    struct efi_ipsec_config_protocol *self,
    uint32_t data_type,
    size_t *selector_size,
    union efi_ipsec_config_selector *selector
);

typedef efi_status (EFI_API *efi_ipsec_config_register_notify)(
    struct efi_ipsec_config_protocol *self,
    uint32_t data_type,
    efi_event event
);

typedef efi_status (EFI_API *efi_ipsec_config_unregister_notify)(
    struct efi_ipsec_config_protocol *self,
    uint32_t data_type,
    efi_event event
);

struct efi_ipsec_config_protocol {
    efi_ipsec_config_set_data set_data;
    efi_ipsec_config_get_data get_data;
    efi_ipsec_config_get_next_selector get_next_selector;
    efi_ipsec_config_register_notify register_data_notify;
    efi_ipsec_config_unregister_notify unregister_data_notify;
};

#define EFI_IPSEC_PROTOCOL_GUID \
    {0xdfb386f7, 0xe100, 0x43ad, {0x9c, 0x9a, 0xed, 0x90, 0xd0, 0x8a, 0x5e, 0x12}}

struct efi_ipsec_protocol;

struct efi_ipsec_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

typedef efi_status (EFI_API *efi_ipsec_process)(
    struct efi_ipsec_protocol *self,
    efi_handle nic_handle,
    uint8_t ip_ver,
    void *ip_head,
    uint8_t *last_head,
    void *options_buffer,
    uint32_t options_length,
    struct efi_ipsec_fragment_data **fragment_table,
    uint32_t *fragment_count,
    uint32_t traffic_direction,
    efi_event *recycle_signal
);

struct efi_ipsec_protocol {
    efi_ipsec_process process;
    efi_event disabled_event;
    uint8_t disabled_flag;
};

#define EFI_IPSEC2_PROTOCOL_GUID \
    {0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77}}

struct efi_ipsec2_protocol;

typedef efi_status (EFI_API *efi_ipsec_processext)(
    struct efi_ipsec2_protocol *self,
    efi_handle nic_handle,
    uint8_t ip_ver,
    void *ip_head,
    uint8_t *last_head,
    void **options_buffer,
    uint32_t *options_length,
    struct efi_ipsec_fragment_data **fragment_table,
    uint32_t *fragment_count,
    uint32_t traffic_direction,
    efi_event *recycle_signal
);

struct efi_ipsec2_protocol {
    efi_ipsec_processext process_ext;
    efi_event disabled_event;
    uint8_t disabled_flag;
};

#define EFI_FTP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xfaaecb1, 0x226e, 0x4782, {0xaa, 0xce, 0x7d, 0xb9, 0xbc, 0xbf, 0x4d, 0xaf}}

#define EFI_FTP4_PROTOCOL_GUID \
    {0xeb338826, 0x681b, 0x4295, {0xb3, 0x56, 0x2b, 0x36, 0x4c, 0x75, 0x7b, 0x09}}

struct efi_ftp4_protocol;

struct efi_ftp4_config_data {
    uint8_t *username;
    uint8_t *password;
    uint8_t active;
    uint8_t use_default_setting;
    struct efi_ipv4_address station_ip;
    struct efi_ipv4_address subnet_mask;
    struct efi_ipv4_address gateway_ip;
    struct efi_ipv4_address server_ip;
    uint16_t server_port;
    uint16_t alt_data_port;
    uint8_t rep_type;
    uint8_t file_struct;
    uint8_t trans_mode;
};

typedef efi_status (EFI_API *efi_ftp4_get_mode_data)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_config_data *mode_data
);

struct efi_ftp4_connection_token {
    efi_event event;
    efi_status status;
};

typedef efi_status (EFI_API *efi_ftp4_connect)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_connection_token *token
);

typedef efi_status (EFI_API *efi_ftp4_close)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_connection_token *token
);

typedef efi_status (EFI_API *efi_ftp4_configure)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_config_data *ftp_config_data
);

struct efi_ftp4_command_token;

typedef efi_status (EFI_API *efi_ftp4_data_callback)(
    struct efi_ftp4_command_token *token,
    struct efi_ftp4_protocol *self
);

struct efi_ftp4_command_token {
    efi_event event;
    uint8_t *pathname;
    uint64_t data_buffer_size;
    void *data_buffer;
    efi_ftp4_data_callback data_callback;
    void *context;
    efi_status status;
};

typedef efi_status (EFI_API *efi_ftp4_read_file)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_command_token *token
);

typedef efi_status (EFI_API *efi_ftp4_write_file)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_command_token *token
);

typedef efi_status (EFI_API *efi_ftp4_read_directory)(
    struct efi_ftp4_protocol *self,
    struct efi_ftp4_command_token *token
);

typedef efi_status (EFI_API *efi_ftp4_poll)(struct efi_ftp4_protocol *self);

struct efi_ftp4_protocol {
    efi_ftp4_get_mode_data get_mode_data;
    efi_ftp4_connect connect;
    efi_ftp4_close close;
    efi_ftp4_configure configure;
    efi_ftp4_read_file read_file;
    efi_ftp4_write_file write_file;
    efi_ftp4_read_directory read_directory;
    efi_ftp4_poll poll;
};

#define EFI_TLS_SERVICE_BINDING_PROTOCOL_GUID \
    {0x952cb795, 0xff36, 0x48cf, {0xa2, 0x49, 0x4d, 0xf4, 0x86, 0xd6, 0xab, 0x8d}}

#define EFI_TLS_PROTOCOL_GUID \
    {0xca959f, 0x6cfa, 0x4db1, {0x95, 0xbc, 0xe4, 0x6c, 0x47, 0x51, 0x43, 0x90}}

struct efi_tls_protocol;

#define EFI_TLS_VERSION ((uint32_t)0)
#define EFI_TLS_CONNECTION_END ((uint32_t)1)
#define EFI_TLS_CIPHER_LIST ((uint32_t)2)
#define EFI_TLS_COMPRESSION_METHOD ((uint32_t)3)
#define EFI_TLS_EXTENSION_DATA ((uint32_t)4)
#define EFI_TLS_VERIFY_METHOD ((uint32_t)5)
#define EFI_TLS_SESSION_ID ((uint32_t)6)
#define EFI_TLS_SESSION_STATE ((uint32_t)7)
#define EFI_TLS_CLIENT_RANDOM ((uint32_t)8)
#define EFI_TLS_SERVER_RANDOM ((uint32_t)9)
#define EFI_TLS_KEY_MATERIAL ((uint32_t)10)
#define EFI_TLS_VERIFY_HOST ((uint32_t)11)
#define EFI_TLS_SESSION_DATA_TYPE_MAXIMUM ((uint32_t)12)

struct efi_tls_version {
    uint8_t major;
    uint8_t minor;
};

#define EFI_TLS_CLIENT ((uint32_t)0)
#define EFI_TLS_SERVER ((uint32_t)1)

struct efi_tls_cipher {
    uint8_t data1;
    uint8_t data2;
};

typedef uint8_t efi_tls_compression;

__extension__ struct efi_tls_extension {
    uint16_t extension_type;
    uint16_t length;
    uint8_t data[];
};

typedef uint32_t efi_tls_verify;

#define EFI_TLS_VERIFY_NONE 0x0
#define EFI_TLS_VERIFY_PEER 0x1
#define EFI_TLS_VERIFY_FAIL_IF_NO_PEER_CERT 0x2
#define EFI_TLS_VERIFY_CLIENT_ONCE 0x4

typedef uint32_t efi_tls_verify_host_flag;

#define EFI_TLS_VERIFY_FLAG_NONE 0x00
#define EFI_TLS_VERIFY_FLAG_ALWAYS_CHECK_SUBJECT 0x01
#define EFI_TLS_VERIFY_FLAG_NO_WILDCARDS 0x02
#define EFI_TLS_VERIFY_FLAG_NO_PARTIAL_WILDCARDS 0x04
#define EFI_TLS_VERIFY_FLAG_MULTI_LABEL_WILDCARDS 0x08
#define EFI_TLS_VERIFY_FLAG_SINGLE_LABEL_SUBDOMAINS 0x10
#define EFI_TLS_VERIFY_FLAG_NEVER_CHECK_SUBJECT 0x20

/* Packed as firmware lays it out, although the specification prints no packing. */
struct efi_tls_verify_host {
    efi_tls_verify_host_flag flags;
    char *host_name;
} __attribute__((__packed__));

struct efi_tls_random {
    uint32_t gmt_unix_time;
    uint8_t random_bytes[28];
};

/* The 48-byte master secret of RFC 5246; printed as an array of 48 pointers. */
struct efi_tls_master_secret {
    uint8_t data[48];
};

#define EFI_MAX_TLS_SESSION_ID_LENGTH 32

struct efi_tls_session_id {
    uint16_t length;
    uint8_t data[EFI_MAX_TLS_SESSION_ID_LENGTH];
};

#define EFI_TLS_SESSION_NOT_STARTED ((uint32_t)0)
#define EFI_TLS_SESSION_HAND_SHAKING ((uint32_t)1)
#define EFI_TLS_SESSION_DATA_TRANSFERRING ((uint32_t)2)
#define EFI_TLS_SESSION_CLOSING ((uint32_t)3)
#define EFI_TLS_SESSION_ERROR ((uint32_t)4)
#define EFI_TLS_SESSION_STATE_MAXIMUM ((uint32_t)5)

typedef efi_status (EFI_API *efi_tls_set_session_data)(
    struct efi_tls_protocol *self,
    uint32_t data_type,
    void *data,
    size_t data_size
);

typedef efi_status (EFI_API *efi_tls_get_session_data)(
    struct efi_tls_protocol *self,
    uint32_t data_type,
    void *data,
    size_t *data_size
);

typedef efi_status (EFI_API *efi_tls_build_response_packet)(
    struct efi_tls_protocol *self,
    uint8_t *request_buffer,
    size_t request_size,
    uint8_t *buffer,
    size_t *buffer_size
);

struct efi_tls_fragment_data {
    uint32_t fragment_length;
    void *fragment_buffer;
};

#define EFI_TLS_ENCRYPT ((uint32_t)0)
#define EFI_TLS_DECRYPT ((uint32_t)1)

typedef efi_status (EFI_API *efi_tls_process_packet)(
    struct efi_tls_protocol *self,
    struct efi_tls_fragment_data **fragment_table,
    uint32_t *fragment_count,
    uint32_t crypt_mode
);

struct efi_tls_protocol {
    efi_tls_set_session_data set_session_data;
    efi_tls_get_session_data get_session_data;
    efi_tls_build_response_packet build_response_packet;
    efi_tls_process_packet process_packet;
};

#define EFI_TLS_CONFIGURATION_PROTOCOL_GUID \
    {0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d}}

struct efi_tls_configuration_protocol;

#define EFI_TLS_CONFIG_DATA_TYPE_HOST_PUBLIC_CERT ((uint32_t)0)
#define EFI_TLS_CONFIG_DATA_TYPE_HOST_PRIVATE_KEY ((uint32_t)1)
#define EFI_TLS_CONFIG_DATA_TYPE_CA_CERTIFICATE ((uint32_t)2)
#define EFI_TLS_CONFIG_DATA_TYPE_CERT_REVOCATION_LIST ((uint32_t)3)
#define EFI_TLS_CONFIG_DATA_TYPE_MAXIMUM ((uint32_t)4)

typedef efi_status (EFI_API *efi_tls_configuration_set_data)(
    struct efi_tls_configuration_protocol *self,
    uint32_t data_type,
    void *data,
    size_t data_size
);

typedef efi_status (EFI_API *efi_tls_configuration_get_data)(
    struct efi_tls_configuration_protocol *self,
    uint32_t data_type,
    void *data,
    size_t *data_size
);

struct efi_tls_configuration_protocol {
    efi_tls_configuration_set_data set_data;
    efi_tls_configuration_get_data get_data;
};

#ifdef __cplusplus
}
#endif

#endif
