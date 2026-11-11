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

typedef struct _EFI_MTFTP4_PROTOCOL EFI_MTFTP4_PROTOCOL;
typedef struct _EFI_MTFTP4_TOKEN EFI_MTFTP4_TOKEN;

typedef struct {
    uint8_t UseDefaultSetting;
    EFI_IPv4_ADDRESS StationIp;
    EFI_IPv4_ADDRESS SubnetMask;
    uint16_t LocalPort;
    EFI_IPv4_ADDRESS GatewayIp;
    EFI_IPv4_ADDRESS ServerIp;
    uint16_t InitialServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
} EFI_MTFTP4_CONFIG_DATA;

typedef struct {
    EFI_MTFTP4_CONFIG_DATA ConfigData;
    uint8_t SupportedOptionCount;
    uint8_t **SupportedOptions;
    uint8_t UnsupportedOptionCount;
    uint8_t **UnsupportedOptions;
} EFI_MTFTP4_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_GET_MODE_DATA)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_MODE_DATA *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CONFIGURE)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_CONFIG_DATA *MtftpConfigData
);

typedef struct {
    EFI_IPv4_ADDRESS GatewayIp;
    EFI_IPv4_ADDRESS ServerIp;
    uint16_t ServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
} EFI_MTFTP4_OVERRIDE_DATA;

typedef struct {
    uint8_t *OptionStr;
    uint8_t *ValueStr;
} EFI_MTFTP4_OPTION;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint8_t Filename[1];
} EFI_MTFTP4_REQ_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint8_t Data[1];
} EFI_MTFTP4_OACK_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t Block;
    uint8_t Data[1];
} EFI_MTFTP4_DATA_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t Block[1];
} EFI_MTFTP4_ACK_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint64_t Block;
    uint8_t Data[1];
} EFI_MTFTP4_DATA8_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint64_t Block[1];
} EFI_MTFTP4_ACK8_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t ErrorCode;
    uint8_t ErrorMessage[1];
} EFI_MTFTP4_ERROR_HEADER;

typedef union __attribute__((__packed__)) {
    uint16_t OpCode;
    EFI_MTFTP4_REQ_HEADER Rrq, Wrq;
    EFI_MTFTP4_OACK_HEADER Oack;
    EFI_MTFTP4_DATA_HEADER Data;
    EFI_MTFTP4_ACK_HEADER Ack;
    EFI_MTFTP4_DATA8_HEADER Data8;
    EFI_MTFTP4_ACK8_HEADER Ack8;
    EFI_MTFTP4_ERROR_HEADER Error;
} EFI_MTFTP4_PACKET;

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
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_OVERRIDE_DATA *OverrideData,
    uint8_t *Filename,
    uint8_t *ModeStr,
    uint8_t OptionCount,
    EFI_MTFTP4_OPTION *OptionList,
    uint32_t *PacketLength,
    EFI_MTFTP4_PACKET **Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PARSE_OPTIONS)(
    EFI_MTFTP4_PROTOCOL *This,
    uint32_t PacketLen,
    EFI_MTFTP4_PACKET *Packet,
    uint32_t *OptionCount,
    EFI_MTFTP4_OPTION **OptionList
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CHECK_PACKET)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token,
    uint16_t PacketLen,
    EFI_MTFTP4_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_TIMEOUT_CALLBACK)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PACKET_NEEDED)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token,
    uint16_t *Length,
    void **Buffer
);

struct _EFI_MTFTP4_TOKEN {
    EFI_STATUS Status;
    EFI_EVENT Event;
    EFI_MTFTP4_OVERRIDE_DATA *OverrideData;
    uint8_t *Filename;
    uint8_t *ModeStr;
    uint32_t OptionCount;
    EFI_MTFTP4_OPTION *OptionList;
    uint64_t BufferSize;
    void *Buffer;
    void *Context;
    EFI_MTFTP4_CHECK_PACKET CheckPacket;
    EFI_MTFTP4_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP4_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_FILE)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_WRITE_FILE)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_DIRECTORY)(
    EFI_MTFTP4_PROTOCOL *This,
    EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_POLL)(EFI_MTFTP4_PROTOCOL *This);

struct _EFI_MTFTP4_PROTOCOL {
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

typedef struct _EFI_MTFTP6_PROTOCOL EFI_MTFTP6_PROTOCOL;
typedef struct _EFI_MTFTP6_TOKEN EFI_MTFTP6_TOKEN;

typedef struct {
    EFI_IPv6_ADDRESS StationIp;
    uint16_t LocalPort;
    EFI_IPv6_ADDRESS ServerIp;
    uint16_t InitialServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
} EFI_MTFTP6_CONFIG_DATA;

typedef struct {
    EFI_MTFTP6_CONFIG_DATA ConfigData;
    uint8_t SupportedOptionCount;
    uint8_t **SupportedOptions;
} EFI_MTFTP6_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_GET_MODE_DATA)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_MODE_DATA *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CONFIGURE)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_CONFIG_DATA *MtftpConfigData
);

typedef struct {
    EFI_IPv6_ADDRESS ServerIp;
    uint16_t ServerPort;
    uint16_t TryCount;
    uint16_t TimeoutValue;
} EFI_MTFTP6_OVERRIDE_DATA;

typedef struct {
    uint8_t *OptionStr;
    uint8_t *ValueStr;
} EFI_MTFTP6_OPTION;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint8_t Filename[1];
} EFI_MTFTP6_REQ_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint8_t Data[1];
} EFI_MTFTP6_OACK_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t Block;
    uint8_t Data[1];
} EFI_MTFTP6_DATA_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t Block[1];
} EFI_MTFTP6_ACK_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint64_t Block;
    uint8_t Data[1];
} EFI_MTFTP6_DATA8_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint64_t Block[1];
} EFI_MTFTP6_ACK8_HEADER;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t ErrorCode;
    uint8_t ErrorMessage[1];
} EFI_MTFTP6_ERROR_HEADER;

typedef union __attribute__((__packed__)) {
    uint16_t OpCode;
    EFI_MTFTP6_REQ_HEADER Rrq;
    EFI_MTFTP6_REQ_HEADER Wrq;
    EFI_MTFTP6_OACK_HEADER Oack;
    EFI_MTFTP6_DATA_HEADER Data;
    EFI_MTFTP6_ACK_HEADER Ack;
    EFI_MTFTP6_DATA8_HEADER Data8;
    EFI_MTFTP6_ACK8_HEADER Ack8;
    EFI_MTFTP6_ERROR_HEADER Error;
} EFI_MTFTP6_PACKET;

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
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_OVERRIDE_DATA *OverrideData,
    uint8_t *Filename,
    uint8_t *ModeStr,
    uint8_t OptionCount,
    EFI_MTFTP6_OPTION *OptionList,
    uint32_t *PacketLength,
    EFI_MTFTP6_PACKET **Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PARSE_OPTIONS)(
    EFI_MTFTP6_PROTOCOL *This,
    uint32_t PacketLen,
    EFI_MTFTP6_PACKET *Packet,
    uint32_t *OptionCount,
    EFI_MTFTP6_OPTION **OptionList
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CHECK_PACKET)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token,
    uint16_t PacketLen,
    EFI_MTFTP6_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_TIMEOUT_CALLBACK)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token
);

/* Token is the caller's token, passed by pointer as in every sibling callback; printed by value. */
typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PACKET_NEEDED)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token,
    uint16_t *Length,
    void **Buffer
);

/* OverrideData and OptionList are pointers, as described and as in MTFTPv4; printed by value. */
struct _EFI_MTFTP6_TOKEN {
    EFI_STATUS Status;
    EFI_EVENT Event;
    EFI_MTFTP6_OVERRIDE_DATA *OverrideData;
    uint8_t *Filename;
    uint8_t *ModeStr;
    uint32_t OptionCount;
    EFI_MTFTP6_OPTION *OptionList;
    uint64_t BufferSize;
    void *Buffer;
    void *Context;
    EFI_MTFTP6_CHECK_PACKET CheckPacket;
    EFI_MTFTP6_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP6_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_FILE)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_WRITE_FILE)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_DIRECTORY)(
    EFI_MTFTP6_PROTOCOL *This,
    EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_POLL)(EFI_MTFTP6_PROTOCOL *This);

struct _EFI_MTFTP6_PROTOCOL {
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
