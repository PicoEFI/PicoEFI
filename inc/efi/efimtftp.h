#ifndef EFI_EFIMTFTP_H
#define EFI_EFIMTFTP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MTFTP4_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x2e800be, 0x8f01, 0x4aa6, { 0x94, 0x6b, 0xd7, 0x13, 0x88, 0xe1, 0x83, 0x3f } }

#define EFI_MTFTP4_PROTOCOL_GUID \
    { 0x78247c57, 0x63db, 0x4708, { 0x99, 0xc2, 0xa8, 0xb4, 0xa9, 0xa6, 0x1f, 0x6b } }

struct efi_mtftp4_protocol;
struct efi_mtftp4_token;

struct efi_mtftp4_config_data {
    uint8_t use_default_setting;
    struct efi_ipv4_address station_ip;
    struct efi_ipv4_address subnet_mask;
    uint16_t local_port;
    struct efi_ipv4_address gateway_ip;
    struct efi_ipv4_address server_ip;
    uint16_t initial_server_port;
    uint16_t try_count;
    uint16_t timeout_value;
};

struct efi_mtftp4_mode_data {
    struct efi_mtftp4_config_data config_data;
    uint8_t supported_option_count;
    uint8_t **supported_options;
    uint8_t unsupported_option_count;
    uint8_t **unsupported_options;
};

typedef efi_status (EFI_API *efi_mtftp4_get_mode_data)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_mode_data *mode_data
);

typedef efi_status (EFI_API *efi_mtftp4_configure)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_config_data *mtftp_config_data
);

struct efi_mtftp4_override_data {
    struct efi_ipv4_address gateway_ip;
    struct efi_ipv4_address server_ip;
    uint16_t server_port;
    uint16_t try_count;
    uint16_t timeout_value;
};

struct efi_mtftp4_option {
    uint8_t *option_str;
    uint8_t *value_str;
};

struct efi_mtftp4_req_header {
    uint16_t op_code;
    uint8_t filename[1];
} __attribute__((__packed__));

struct efi_mtftp4_oack_header {
    uint16_t op_code;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp4_data_header {
    uint16_t op_code;
    uint16_t block;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp4_ack_header {
    uint16_t op_code;
    uint16_t block[1];
} __attribute__((__packed__));

struct efi_mtftp4_data8_header {
    uint16_t op_code;
    uint64_t block;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp4_ack8_header {
    uint16_t op_code;
    uint64_t block[1];
} __attribute__((__packed__));

struct efi_mtftp4_error_header {
    uint16_t op_code;
    uint16_t error_code;
    uint8_t error_message[1];
} __attribute__((__packed__));

union efi_mtftp4_packet {
    uint16_t op_code;
    struct efi_mtftp4_req_header rrq, wrq;
    struct efi_mtftp4_oack_header oack;
    struct efi_mtftp4_data_header data;
    struct efi_mtftp4_ack_header ack;
    struct efi_mtftp4_data8_header data8;
    struct efi_mtftp4_ack8_header ack8;
    struct efi_mtftp4_error_header error;
} __attribute__((__packed__));

#define EFI_MTFTP4_OPCODE_RRQ 1
#define EFI_MTFTP4_OPCODE_WRQ 2
#define EFI_MTFTP4_OPCODE_DATA 3
#define EFI_MTFTP4_OPCODE_ACK 4
#define EFI_MTFTP4_OPCODE_ERROR 5
#define EFI_MTFTP4_OPCODE_OACK 6
#define EFI_MTFTP4_OPCODE_DIR 7
#define EFI_MTFTP4_OPCODE_DATA8 8
#define EFI_MTFTP4_OPCODE_ACK8 9

#define EFI_MTFTP4_ERRORCODE_NOT_DEFINED 0
#define EFI_MTFTP4_ERRORCODE_FILE_NOT_FOUND 1
#define EFI_MTFTP4_ERRORCODE_ACCESS_VIOLATION 2
#define EFI_MTFTP4_ERRORCODE_DISK_FULL 3
#define EFI_MTFTP4_ERRORCODE_ILLEGAL_OPERATION 4
#define EFI_MTFTP4_ERRORCODE_UNKNOWN_TRANSFER_ID 5
#define EFI_MTFTP4_ERRORCODE_FILE_ALREADY_EXISTS 6
#define EFI_MTFTP4_ERRORCODE_NO_SUCH_USER 7
#define EFI_MTFTP4_ERRORCODE_REQUEST_DENIED 8

typedef efi_status (EFI_API *efi_mtftp4_get_info)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_override_data *override_data,
    uint8_t *filename,
    uint8_t *mode_str,
    uint8_t option_count,
    struct efi_mtftp4_option *option_list,
    uint32_t *packet_length,
    union efi_mtftp4_packet **packet
);

typedef efi_status (EFI_API *efi_mtftp4_parse_options)(
    struct efi_mtftp4_protocol *self,
    uint32_t packet_len,
    union efi_mtftp4_packet *packet,
    uint32_t *option_count,
    struct efi_mtftp4_option **option_list
);

typedef efi_status (EFI_API *efi_mtftp4_check_packet)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token,
    uint16_t packet_len,
    union efi_mtftp4_packet *packet
);

typedef efi_status (EFI_API *efi_mtftp4_timeout_callback)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token
);

typedef efi_status (EFI_API *efi_mtftp4_packet_needed)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token,
    uint16_t *length,
    void **buffer
);

struct efi_mtftp4_token {
    efi_status status;
    efi_event event;
    struct efi_mtftp4_override_data *override_data;
    uint8_t *filename;
    uint8_t *mode_str;
    uint32_t option_count;
    struct efi_mtftp4_option *option_list;
    uint64_t buffer_size;
    void *buffer;
    void *context;
    efi_mtftp4_check_packet check_packet;
    efi_mtftp4_timeout_callback timeout_callback;
    efi_mtftp4_packet_needed packet_needed;
};

typedef efi_status (EFI_API *efi_mtftp4_read_file)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token
);

typedef efi_status (EFI_API *efi_mtftp4_write_file)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token
);

typedef efi_status (EFI_API *efi_mtftp4_read_directory)(
    struct efi_mtftp4_protocol *self,
    struct efi_mtftp4_token *token
);

typedef efi_status (EFI_API *efi_mtftp4_poll)(struct efi_mtftp4_protocol *self);

struct efi_mtftp4_protocol {
    efi_mtftp4_get_mode_data get_mode_data;
    efi_mtftp4_configure configure;
    efi_mtftp4_get_info get_info;
    efi_mtftp4_parse_options parse_options;
    efi_mtftp4_read_file read_file;
    efi_mtftp4_write_file write_file;
    efi_mtftp4_read_directory read_directory;
    efi_mtftp4_poll poll;
};

#define EFI_MTFTP6_SERVICE_BINDING_PROTOCOL_GUID \
    { 0xd9760ff3, 0x3cca, 0x4267, { 0x80, 0xf9, 0x75, 0x27, 0xfa, 0xfa, 0x42, 0x23 } }

#define EFI_MTFTP6_PROTOCOL_GUID \
    { 0xbf0a78ba, 0xec29, 0x49cf, { 0xa1, 0xc9, 0x7a, 0xe5, 0x4e, 0xab, 0x6a, 0x51 } }

struct efi_mtftp6_protocol;
struct efi_mtftp6_token;

struct efi_mtftp6_config_data {
    struct efi_ipv6_address station_ip;
    uint16_t local_port;
    struct efi_ipv6_address server_ip;
    uint16_t initial_server_port;
    uint16_t try_count;
    uint16_t timeout_value;
};

struct efi_mtftp6_mode_data {
    struct efi_mtftp6_config_data config_data;
    uint8_t supported_option_count;
    uint8_t **supported_options;
};

typedef efi_status (EFI_API *efi_mtftp6_get_mode_data)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_mode_data *mode_data
);

typedef efi_status (EFI_API *efi_mtftp6_configure)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_config_data *mtftp_config_data
);

struct efi_mtftp6_override_data {
    struct efi_ipv6_address server_ip;
    uint16_t server_port;
    uint16_t try_count;
    uint16_t timeout_value;
};

struct efi_mtftp6_option {
    uint8_t *option_str;
    uint8_t *value_str;
};

struct efi_mtftp6_req_header {
    uint16_t op_code;
    uint8_t filename[1];
} __attribute__((__packed__));

struct efi_mtftp6_oack_header {
    uint16_t op_code;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp6_data_header {
    uint16_t op_code;
    uint16_t block;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp6_ack_header {
    uint16_t op_code;
    uint16_t block[1];
} __attribute__((__packed__));

struct efi_mtftp6_data8_header {
    uint16_t op_code;
    uint64_t block;
    uint8_t data[1];
} __attribute__((__packed__));

struct efi_mtftp6_ack8_header {
    uint16_t op_code;
    uint64_t block[1];
} __attribute__((__packed__));

struct efi_mtftp6_error_header {
    uint16_t op_code;
    uint16_t error_code;
    uint8_t error_message[1];
} __attribute__((__packed__));

union efi_mtftp6_packet {
    uint16_t op_code;
    struct efi_mtftp6_req_header rrq;
    struct efi_mtftp6_req_header wrq;
    struct efi_mtftp6_oack_header oack;
    struct efi_mtftp6_data_header data;
    struct efi_mtftp6_ack_header ack;
    struct efi_mtftp6_data8_header data8;
    struct efi_mtftp6_ack8_header ack8;
    struct efi_mtftp6_error_header error;
} __attribute__((__packed__));

#define EFI_MTFTP6_OPCODE_RRQ 1
#define EFI_MTFTP6_OPCODE_WRQ 2
#define EFI_MTFTP6_OPCODE_DATA 3
// TFTP's ACK, as in MTFTPv4; the specification prints 6, which is
// EFI_MTFTP6_OPCODE_OACK.
#define EFI_MTFTP6_OPCODE_ACK 4
#define EFI_MTFTP6_OPCODE_ERROR 5
#define EFI_MTFTP6_OPCODE_OACK 6
#define EFI_MTFTP6_OPCODE_DIR 7
// Named as the MTFTPv6 tables name them; the opcode list prints the MTFTPv4
// names.
#define EFI_MTFTP6_OPCODE_DATA8 8
#define EFI_MTFTP6_OPCODE_ACK8 9

#define EFI_MTFTP6_ERRORCODE_NOT_DEFINED 0
#define EFI_MTFTP6_ERRORCODE_FILE_NOT_FOUND 1
#define EFI_MTFTP6_ERRORCODE_ACCESS_VIOLATION 2
#define EFI_MTFTP6_ERRORCODE_DISK_FULL 3
#define EFI_MTFTP6_ERRORCODE_ILLEGAL_OPERATION 4
#define EFI_MTFTP6_ERRORCODE_UNKNOWN_TRANSFER_ID 5
#define EFI_MTFTP6_ERRORCODE_FILE_ALREADY_EXISTS 6
#define EFI_MTFTP6_ERRORCODE_NO_SUCH_USER 7
#define EFI_MTFTP6_ERRORCODE_REQUEST_DENIED 8

typedef efi_status (EFI_API *efi_mtftp6_get_info)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_override_data *override_data,
    uint8_t *filename,
    uint8_t *mode_str,
    uint8_t option_count,
    struct efi_mtftp6_option *option_list,
    uint32_t *packet_length,
    union efi_mtftp6_packet **packet
);

typedef efi_status (EFI_API *efi_mtftp6_parse_options)(
    struct efi_mtftp6_protocol *self,
    uint32_t packet_len,
    union efi_mtftp6_packet *packet,
    uint32_t *option_count,
    struct efi_mtftp6_option **option_list
);

typedef efi_status (EFI_API *efi_mtftp6_check_packet)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token,
    uint16_t packet_len,
    union efi_mtftp6_packet *packet
);

typedef efi_status (EFI_API *efi_mtftp6_timeout_callback)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token
);

// token is the caller's token, passed by pointer as in every sibling callback;
// printed by value.
typedef efi_status (EFI_API *efi_mtftp6_packet_needed)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token,
    uint16_t *length,
    void **buffer
);

// override_data and option_list are pointers, as described and as in MTFTPv4;
// printed by value.
struct efi_mtftp6_token {
    efi_status status;
    efi_event event;
    struct efi_mtftp6_override_data *override_data;
    uint8_t *filename;
    uint8_t *mode_str;
    uint32_t option_count;
    struct efi_mtftp6_option *option_list;
    uint64_t buffer_size;
    void *buffer;
    void *context;
    efi_mtftp6_check_packet check_packet;
    efi_mtftp6_timeout_callback timeout_callback;
    efi_mtftp6_packet_needed packet_needed;
};

typedef efi_status (EFI_API *efi_mtftp6_read_file)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token
);

typedef efi_status (EFI_API *efi_mtftp6_write_file)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token
);

typedef efi_status (EFI_API *efi_mtftp6_read_directory)(
    struct efi_mtftp6_protocol *self,
    struct efi_mtftp6_token *token
);

typedef efi_status (EFI_API *efi_mtftp6_poll)(struct efi_mtftp6_protocol *self);

struct efi_mtftp6_protocol {
    efi_mtftp6_get_mode_data get_mode_data;
    efi_mtftp6_configure configure;
    efi_mtftp6_get_info get_info;
    efi_mtftp6_parse_options parse_options;
    efi_mtftp6_read_file read_file;
    efi_mtftp6_write_file write_file;
    efi_mtftp6_read_directory read_directory;
    efi_mtftp6_poll poll;
};

#ifdef __cplusplus
}
#endif

#endif
