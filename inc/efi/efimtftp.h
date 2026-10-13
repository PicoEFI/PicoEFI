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
    EFI_BOOLEAN UseDefaultSetting;
    EFI_IPv4_ADDRESS StationIp;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_UINT16 LocalPort;
    EFI_IPv4_ADDRESS GatewayIp;
    EFI_IPv4_ADDRESS ServerIp;
    EFI_UINT16 InitialServerPort;
    EFI_UINT16 TryCount;
    EFI_UINT16 TimeoutValue;
} EFI_MTFTP4_CONFIG_DATA;

typedef struct {
    EFI_MTFTP4_CONFIG_DATA ConfigData;
    EFI_UINT8 SupportedOptionCount;
    EFI_UINT8 **SupportedOptions;
    EFI_UINT8 UnsupportedOptionCount;
    EFI_UINT8 **UnsupportedOptions;
} EFI_MTFTP4_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_GET_MODE_DATA)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_OUT EFI_MTFTP4_MODE_DATA *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CONFIGURE)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_CONFIG_DATA *MtftpConfigData EFI_OPTIONAL
);

typedef struct {
    EFI_IPv4_ADDRESS GatewayIp;
    EFI_IPv4_ADDRESS ServerIp;
    EFI_UINT16 ServerPort;
    EFI_UINT16 TryCount;
    EFI_UINT16 TimeoutValue;
} EFI_MTFTP4_OVERRIDE_DATA;

typedef struct {
    EFI_UINT8 *OptionStr;
    EFI_UINT8 *ValueStr;
} EFI_MTFTP4_OPTION;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT8 Filename[1];
} EFI_MTFTP4_REQ_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT8 Data[1];
} EFI_MTFTP4_OACK_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 Block;
    EFI_UINT8 Data[1];
} EFI_MTFTP4_DATA_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 Block[1];
} EFI_MTFTP4_ACK_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT64 Block;
    EFI_UINT8 Data[1];
} EFI_MTFTP4_DATA8_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT64 Block[1];
} EFI_MTFTP4_ACK8_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 ErrorCode;
    EFI_UINT8 ErrorMessage[1];
} EFI_MTFTP4_ERROR_HEADER;

typedef union __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
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
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_OVERRIDE_DATA *OverrideData EFI_OPTIONAL,
    EFI_IN EFI_UINT8 *Filename,
    EFI_IN EFI_UINT8 *ModeStr EFI_OPTIONAL,
    EFI_IN EFI_UINT8 OptionCount,
    EFI_IN EFI_MTFTP4_OPTION *OptionList EFI_OPTIONAL,
    EFI_OUT EFI_UINT32 *PacketLength,
    EFI_OUT EFI_MTFTP4_PACKET **Packet EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PARSE_OPTIONS)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_UINT32 PacketLen,
    EFI_IN EFI_MTFTP4_PACKET *Packet,
    EFI_OUT EFI_UINT32 *OptionCount,
    EFI_OUT EFI_MTFTP4_OPTION **OptionList EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_CHECK_PACKET)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token,
    EFI_IN EFI_UINT16 PacketLen,
    EFI_IN EFI_MTFTP4_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_TIMEOUT_CALLBACK)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_PACKET_NEEDED)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token,
    EFI_IN EFI_OUT EFI_UINT16 *Length,
    EFI_OUT EFI_VOID **Buffer
);

struct _EFI_MTFTP4_TOKEN {
    EFI_STATUS Status;
    EFI_EVENT Event;
    EFI_MTFTP4_OVERRIDE_DATA *OverrideData;
    EFI_UINT8 *Filename;
    EFI_UINT8 *ModeStr;
    EFI_UINT32 OptionCount;
    EFI_MTFTP4_OPTION *OptionList;
    EFI_UINT64 BufferSize;
    EFI_VOID *Buffer;
    EFI_VOID *Context;
    EFI_MTFTP4_CHECK_PACKET CheckPacket;
    EFI_MTFTP4_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP4_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_FILE)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_WRITE_FILE)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_READ_DIRECTORY)(
    EFI_IN EFI_MTFTP4_PROTOCOL *This,
    EFI_IN EFI_MTFTP4_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP4_POLL)(EFI_IN EFI_MTFTP4_PROTOCOL *This);

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
    EFI_UINT16 LocalPort;
    EFI_IPv6_ADDRESS ServerIp;
    EFI_UINT16 InitialServerPort;
    EFI_UINT16 TryCount;
    EFI_UINT16 TimeoutValue;
} EFI_MTFTP6_CONFIG_DATA;

typedef struct {
    EFI_MTFTP6_CONFIG_DATA ConfigData;
    EFI_UINT8 SupportedOptionCount;
    EFI_UINT8 **SupportedOptions;
} EFI_MTFTP6_MODE_DATA;

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_GET_MODE_DATA)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_OUT EFI_MTFTP6_MODE_DATA *ModeData
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CONFIGURE)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_CONFIG_DATA *MtftpConfigData EFI_OPTIONAL
);

typedef struct {
    EFI_IPv6_ADDRESS ServerIp;
    EFI_UINT16 ServerPort;
    EFI_UINT16 TryCount;
    EFI_UINT16 TimeoutValue;
} EFI_MTFTP6_OVERRIDE_DATA;

typedef struct {
    EFI_UINT8 *OptionStr;
    EFI_UINT8 *ValueStr;
} EFI_MTFTP6_OPTION;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT8 Filename[1];
} EFI_MTFTP6_REQ_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT8 Data[1];
} EFI_MTFTP6_OACK_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 Block;
    EFI_UINT8 Data[1];
} EFI_MTFTP6_DATA_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 Block[1];
} EFI_MTFTP6_ACK_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT64 Block;
    EFI_UINT8 Data[1];
} EFI_MTFTP6_DATA8_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT64 Block[1];
} EFI_MTFTP6_ACK8_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 ErrorCode;
    EFI_UINT8 ErrorMessage[1];
} EFI_MTFTP6_ERROR_HEADER;

typedef union __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
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
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_OVERRIDE_DATA *OverrideData EFI_OPTIONAL,
    EFI_IN EFI_UINT8 *Filename,
    EFI_IN EFI_UINT8 *ModeStr EFI_OPTIONAL,
    EFI_IN EFI_UINT8 OptionCount,
    EFI_IN EFI_MTFTP6_OPTION *OptionList EFI_OPTIONAL,
    EFI_OUT EFI_UINT32 *PacketLength,
    EFI_OUT EFI_MTFTP6_PACKET **Packet EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PARSE_OPTIONS)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_UINT32 PacketLen,
    EFI_IN EFI_MTFTP6_PACKET *Packet,
    EFI_OUT EFI_UINT32 *OptionCount,
    EFI_OUT EFI_MTFTP6_OPTION **OptionList EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_CHECK_PACKET)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token,
    EFI_IN EFI_UINT16 PacketLen,
    EFI_IN EFI_MTFTP6_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_TIMEOUT_CALLBACK)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token
);

/* Token is the caller's token, passed by pointer as in every sibling callback; printed by value. */
typedef EFI_STATUS (EFI_API *EFI_MTFTP6_PACKET_NEEDED)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token,
    EFI_IN EFI_OUT EFI_UINT16 *Length,
    EFI_OUT EFI_VOID **Buffer
);

/* OverrideData and OptionList are pointers, as described and as in MTFTPv4; printed by value. */
struct _EFI_MTFTP6_TOKEN {
    EFI_STATUS Status;
    EFI_EVENT Event;
    EFI_MTFTP6_OVERRIDE_DATA *OverrideData;
    EFI_UINT8 *Filename;
    EFI_UINT8 *ModeStr;
    EFI_UINT32 OptionCount;
    EFI_MTFTP6_OPTION *OptionList;
    EFI_UINT64 BufferSize;
    EFI_VOID *Buffer;
    EFI_VOID *Context;
    EFI_MTFTP6_CHECK_PACKET CheckPacket;
    EFI_MTFTP6_TIMEOUT_CALLBACK TimeoutCallback;
    EFI_MTFTP6_PACKET_NEEDED PacketNeeded;
};

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_FILE)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_WRITE_FILE)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_READ_DIRECTORY)(
    EFI_IN EFI_MTFTP6_PROTOCOL *This,
    EFI_IN EFI_MTFTP6_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_MTFTP6_POLL)(EFI_IN EFI_MTFTP6_PROTOCOL *This);

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
