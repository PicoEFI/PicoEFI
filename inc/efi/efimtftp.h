#ifndef EFI_EFIMTFTP_H_
#define EFI_EFIMTFTP_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MTFTP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x2e800be, 0x8f01, 0x4aa6, {0x94, 0x6b, 0xd7, 0x13, 0x88, 0xe1, 0x83, 0x3f}}

#define EFI_MTFTP4_PROTOCOL_GUID \
    {0x78247c57, 0x63db, 0x4708, {0x99, 0xc2, 0xa8, 0xb4, 0xa9, 0xa6, 0x1f, 0x6b}}

struct efi_mtftp4_protocol;
struct efi_mtftp4_token;

struct efi_mtftp4_config_data {
    uint8_t UseDefaultSetting;
    struct efi_ipv4_address StationIp;
    struct efi_ipv4_address SubnetMask;
    uint16_t LocalPort;
    struct efi_ipv4_address GatewayIp;
    struct efi_ipv4_address ServerIp;
    uint16_t InitialServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
};

struct efi_mtftp4_mode_data {
    struct efi_mtftp4_config_data ConfigData;
    uint8_t SupportedOptionCount;
    uint8_t **SupportedOptions;
    uint8_t UnsupportedOptionCount;
    uint8_t **UnsupportedOptions;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_GET_MODE_DATA)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_mode_data *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CONFIGURE)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_config_data *MtftpConfigData
);

struct efi_mtftp4_override_data {
    struct efi_ipv4_address GatewayIp;
    struct efi_ipv4_address ServerIp;
    uint16_t ServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
};

struct efi_mtftp4_option {
    uint8_t *OptionStr;
    uint8_t *ValueStr;
};

struct efi_mtftp4_req_header {
    uint16_t OpCode;
    uint8_t Filename[1];
} __attribute__((__packed__));

struct efi_mtftp4_oack_header {
    uint16_t OpCode;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp4_data_header {
    uint16_t OpCode;
    uint16_t Block;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp4_ack_header {
    uint16_t OpCode;
    uint16_t Block[1];
} __attribute__((__packed__));

struct efi_mtftp4_data8_header {
    uint16_t OpCode;
    uint64_t Block;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp4_ack8_header {
    uint16_t OpCode;
    uint64_t Block[1];
} __attribute__((__packed__));

struct efi_mtftp4_error_header {
    uint16_t OpCode;
    uint16_t ErrorCode;
    uint8_t ErrorMessage[1];
} __attribute__((__packed__));

union efi_mtftp4_packet {
    uint16_t OpCode;
    struct efi_mtftp4_req_header Rrq, Wrq;
    struct efi_mtftp4_oack_header Oack;
    struct efi_mtftp4_data_header Data;
    struct efi_mtftp4_ack_header Ack;
    struct efi_mtftp4_data8_header Data8;
    struct efi_mtftp4_ack8_header Ack8;
    struct efi_mtftp4_error_header Error;
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

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_GET_INFO)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_override_data *OverrideData,
    uint8_t *Filename,
    uint8_t *ModeStr,
    uint8_t OptionCount,
    struct efi_mtftp4_option *OptionList,
    uint32_t *PacketLength,
    union efi_mtftp4_packet **Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PARSE_OPTIONS)(
    struct efi_mtftp4_protocol *This,
    uint32_t PacketLen,
    union efi_mtftp4_packet *Packet,
    uint32_t *OptionCount,
    struct efi_mtftp4_option **OptionList
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CHECK_PACKET)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token,
    uint16_t PacketLen,
    union efi_mtftp4_packet *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_TIMEOUT_CALLBACK)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PACKET_NEEDED)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token,
    uint16_t *Length,
    void **Buffer
);

struct efi_mtftp4_token {
    EFI_STATUS Status;
    EFI_EVENT Event;
    struct efi_mtftp4_override_data *OverrideData;
    uint8_t *Filename;
    uint8_t *ModeStr;
    uint32_t OptionCount;
    struct efi_mtftp4_option *OptionList;
    uint64_t BufferSize;
    void *Buffer;
    void *Context;
    EFI_MTFTP4_CHECK_PACKET CheckPacket;
    EFI_MTFTP4_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP4_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_FILE)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_WRITE_FILE)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_DIRECTORY)(
    struct efi_mtftp4_protocol *This,
    struct efi_mtftp4_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_POLL)(struct efi_mtftp4_protocol *This);

struct efi_mtftp4_protocol {
    EFI_MTFTP4_GET_MODE_DATA GetModeData;
    EFI_MTFTP4_CONFIGURE Configure;
    EFI_MTFTP4_GET_INFO GetInfo;
    EFI_MTFTP4_PARSE_OPTIONS ParseOptions;
    EFI_MTFTP4_READ_FILE ReadFile;
    EFI_MTFTP4_WRITE_FILE WriteFile;
    EFI_MTFTP4_READ_DIRECTORY ReadDirectory;
    EFI_MTFTP4_POLL Poll;
};

#define EFI_MTFTP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0xd9760ff3, 0x3cca, 0x4267, {0x80, 0xf9, 0x75, 0x27, 0xfa, 0xfa, 0x42, 0x23}}

#define EFI_MTFTP6_PROTOCOL_GUID \
    {0xbf0a78ba, 0xec29, 0x49cf, {0xa1, 0xc9, 0x7a, 0xe5, 0x4e, 0xab, 0x6a, 0x51}}

struct efi_mtftp6_protocol;
struct efi_mtftp6_token;

struct efi_mtftp6_config_data {
    struct efi_ipv6_address StationIp;
    uint16_t LocalPort;
    struct efi_ipv6_address ServerIp;
    uint16_t InitialServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
};

struct efi_mtftp6_mode_data {
    struct efi_mtftp6_config_data ConfigData;
    uint8_t SupportedOptionCount;
    uint8_t **SupportedOptions;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_GET_MODE_DATA)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_mode_data *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CONFIGURE)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_config_data *MtftpConfigData
);

struct efi_mtftp6_override_data {
    struct efi_ipv6_address ServerIp;
    uint16_t ServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
};

struct efi_mtftp6_option {
    uint8_t *OptionStr;
    uint8_t *ValueStr;
};

struct efi_mtftp6_req_header {
    uint16_t OpCode;
    uint8_t Filename[1];
} __attribute__((__packed__));

struct efi_mtftp6_oack_header {
    uint16_t OpCode;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp6_data_header {
    uint16_t OpCode;
    uint16_t Block;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp6_ack_header {
    uint16_t OpCode;
    uint16_t Block[1];
} __attribute__((__packed__));

struct efi_mtftp6_data8_header {
    uint16_t OpCode;
    uint64_t Block;
    uint8_t Data[1];
} __attribute__((__packed__));

struct efi_mtftp6_ack8_header {
    uint16_t OpCode;
    uint64_t Block[1];
} __attribute__((__packed__));

struct efi_mtftp6_error_header {
    uint16_t OpCode;
    uint16_t ErrorCode;
    uint8_t ErrorMessage[1];
} __attribute__((__packed__));

union efi_mtftp6_packet {
    uint16_t OpCode;
    struct efi_mtftp6_req_header Rrq;
    struct efi_mtftp6_req_header Wrq;
    struct efi_mtftp6_oack_header Oack;
    struct efi_mtftp6_data_header Data;
    struct efi_mtftp6_ack_header Ack;
    struct efi_mtftp6_data8_header Data8;
    struct efi_mtftp6_ack8_header Ack8;
    struct efi_mtftp6_error_header Error;
} __attribute__((__packed__));

#define EFI_MTFTP6_OPCODE_RRQ 1
#define EFI_MTFTP6_OPCODE_WRQ 2
#define EFI_MTFTP6_OPCODE_DATA 3
/* TFTP's ACK, as in MTFTPv4; the specification prints 6, which is EFI_MTFTP6_OPCODE_OACK. */
#define EFI_MTFTP6_OPCODE_ACK 4
#define EFI_MTFTP6_OPCODE_ERROR 5
#define EFI_MTFTP6_OPCODE_OACK 6
#define EFI_MTFTP6_OPCODE_DIR 7
/* Named as the MTFTPv6 tables name them; the opcode list prints the MTFTPv4 names. */
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

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_GET_INFO)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_override_data *OverrideData,
    uint8_t *Filename,
    uint8_t *ModeStr,
    uint8_t OptionCount,
    struct efi_mtftp6_option *OptionList,
    uint32_t *PacketLength,
    union efi_mtftp6_packet **Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PARSE_OPTIONS)(
    struct efi_mtftp6_protocol *This,
    uint32_t PacketLen,
    union efi_mtftp6_packet *Packet,
    uint32_t *OptionCount,
    struct efi_mtftp6_option **OptionList
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CHECK_PACKET)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token,
    uint16_t PacketLen,
    union efi_mtftp6_packet *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_TIMEOUT_CALLBACK)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token
);

/* Token is the caller's token, passed by pointer as in every sibling callback; printed by value. */
typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PACKET_NEEDED)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token,
    uint16_t *Length,
    void **Buffer
);

/* OverrideData and OptionList are pointers, as described and as in MTFTPv4; printed by value. */
struct efi_mtftp6_token {
    EFI_STATUS Status;
    EFI_EVENT Event;
    struct efi_mtftp6_override_data *OverrideData;
    uint8_t *Filename;
    uint8_t *ModeStr;
    uint32_t OptionCount;
    struct efi_mtftp6_option *OptionList;
    uint64_t BufferSize;
    void *Buffer;
    void *Context;
    EFI_MTFTP6_CHECK_PACKET CheckPacket;
    EFI_MTFTP6_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP6_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_FILE)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_WRITE_FILE)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_DIRECTORY)(
    struct efi_mtftp6_protocol *This,
    struct efi_mtftp6_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_POLL)(struct efi_mtftp6_protocol *This);

struct efi_mtftp6_protocol {
    EFI_MTFTP6_GET_MODE_DATA GetModeData;
    EFI_MTFTP6_CONFIGURE Configure;
    EFI_MTFTP6_GET_INFO GetInfo;
    EFI_MTFTP6_PARSE_OPTIONS ParseOptions;
    EFI_MTFTP6_READ_FILE ReadFile;
    EFI_MTFTP6_WRITE_FILE WriteFile;
    EFI_MTFTP6_READ_DIRECTORY ReadDirectory;
    EFI_MTFTP6_POLL Poll;
};

#ifdef __cplusplus
}
#endif

#endif
