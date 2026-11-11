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
    uint8_t UseDefaultAddress;
    struct efi_ipv4_address StationAddress;
    struct efi_ipv4_address SubnetMask;
    uint16_t StationPort;
    struct efi_ipv4_address RemoteAddress;
    uint16_t RemotePort;
    uint8_t ActiveFlag;
};

struct efi_tcp4_option {
    uint32_t ReceiveBufferSize;
    uint32_t SendBufferSize;
    uint32_t MaxSynBackLog;
    uint32_t ConnectionTimeout;
    uint32_t DataRetries;
    uint32_t FinTimeout;
    uint32_t TimeWaitTimeout;
    uint32_t KeepAliveProbes;
    uint32_t KeepAliveTime;
    uint32_t KeepAliveInterval;
    uint8_t EnableNagle;
    uint8_t EnableTimeStamp;
    uint8_t EnableWindowScaling;
    uint8_t EnableSelectiveAck;
    uint8_t EnablePathMtuDiscovery;
};

/* ControlOption may be NULL, as described (and a pointer in TCPv6); printed by value. */
struct efi_tcp4_config_data {
    uint8_t TypeOfService;
    uint8_t TimeToLive;
    struct efi_tcp4_access_point AccessPoint;
    struct efi_tcp4_option *ControlOption;
};

typedef enum {
    EfiTcp4StateClosed = 0,
    EfiTcp4StateListen = 1,
    EfiTcp4StateSynSent = 2,
    EfiTcp4StateSynReceived = 3,
    EfiTcp4StateEstablished = 4,
    EfiTcp4StateFinWait1 = 5,
    EfiTcp4StateFinWait2 = 6,
    EfiTcp4StateClosing = 7,
    EfiTcp4StateTimeWait = 8,
    EfiTcp4StateCloseWait = 9,
    EfiTcp4StateLastAck = 10
} EFI_TCP4_CONNECTION_STATE;

typedef EFI_STATUS (EFI_API *EFI_TCP4_GET_MODE_DATA)(
    struct efi_tcp4_protocol *This,
    EFI_TCP4_CONNECTION_STATE *Tcp4State,
    struct efi_tcp4_config_data *Tcp4ConfigData,
    struct efi_ip4_mode_data *Ip4ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_CONFIGURE)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_config_data *TcpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_ROUTES)(
    struct efi_tcp4_protocol *This,
    bool DeleteRoute,
    struct efi_ipv4_address *SubnetAddress,
    struct efi_ipv4_address *SubnetMask,
    struct efi_ipv4_address *GatewayAddress
);

struct efi_tcp4_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
};

struct efi_tcp4_connection_token {
    struct efi_tcp4_completion_token CompletionToken;
};

typedef EFI_STATUS (EFI_API *EFI_TCP4_CONNECT)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_connection_token *ConnectionToken
);

struct efi_tcp4_listen_token {
    struct efi_tcp4_completion_token CompletionToken;
    EFI_HANDLE NewChildHandle;
};

typedef EFI_STATUS (EFI_API *EFI_TCP4_ACCEPT)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_listen_token *ListenToken
);

struct efi_tcp4_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_tcp4_receive_data {
    uint8_t UrgentFlag;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_tcp4_fragment_data FragmentTable[1];
};

struct efi_tcp4_transmit_data {
    uint8_t Push;
    uint8_t Urgent;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_tcp4_fragment_data FragmentTable[1];
};

struct efi_tcp4_io_token {
    struct efi_tcp4_completion_token CompletionToken;
    union {
        struct efi_tcp4_receive_data *RxData;
        struct efi_tcp4_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_TCP4_TRANSMIT)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_io_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_RECEIVE)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_io_token *Token
);

struct efi_tcp4_close_token {
    struct efi_tcp4_completion_token CompletionToken;
    uint8_t AbortOnClose;
};

typedef EFI_STATUS (EFI_API *EFI_TCP4_CLOSE)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_close_token *CloseToken
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_CANCEL)(
    struct efi_tcp4_protocol *This,
    struct efi_tcp4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_POLL)(struct efi_tcp4_protocol *This);

struct efi_tcp4_protocol {
    EFI_TCP4_GET_MODE_DATA GetModeData;
    EFI_TCP4_CONFIGURE Configure;
    EFI_TCP4_ROUTES Routes;
    EFI_TCP4_CONNECT Connect;
    EFI_TCP4_ACCEPT Accept;
    EFI_TCP4_TRANSMIT Transmit;
    EFI_TCP4_RECEIVE Receive;
    EFI_TCP4_CLOSE Close;
    EFI_TCP4_CANCEL Cancel;
    EFI_TCP4_POLL Poll;
};

#define EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0xec20eb79, 0x6c1a, 0x4664, {0x9a, 0x0d, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64}}

#define EFI_TCP6_PROTOCOL_GUID \
    {0x46e44855, 0xbd60, 0x4ab7, {0xab, 0x0d, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77}}

struct efi_tcp6_protocol;

struct efi_tcp6_access_point {
    struct efi_ipv6_address StationAddress;
    uint16_t StationPort;
    struct efi_ipv6_address RemoteAddress;
    uint16_t RemotePort;
    uint8_t ActiveFlag;
};

struct efi_tcp6_option {
    uint32_t ReceiveBufferSize;
    uint32_t SendBufferSize;
    uint32_t MaxSynBackLog;
    uint32_t ConnectionTimeout;
    uint32_t DataRetries;
    uint32_t FinTimeout;
    uint32_t TimeWaitTimeout;
    uint32_t KeepAliveProbes;
    uint32_t KeepAliveTime;
    uint32_t KeepAliveInterval;
    uint8_t EnableNagle;
    uint8_t EnableTimeStamp;
    uint8_t EnableWindowScaling;
    uint8_t EnableSelectiveAck;
    uint8_t EnablePathMtuDiscovery;
};

struct efi_tcp6_config_data {
    uint8_t TrafficClass;
    uint8_t HopLimit;
    struct efi_tcp6_access_point AccessPoint;
    struct efi_tcp6_option *ControlOption;
};

typedef enum {
    EfiTcp6StateClosed = 0,
    EfiTcp6StateListen = 1,
    EfiTcp6StateSynSent = 2,
    EfiTcp6StateSynReceived = 3,
    EfiTcp6StateEstablished = 4,
    EfiTcp6StateFinWait1 = 5,
    EfiTcp6StateFinWait2 = 6,
    EfiTcp6StateClosing = 7,
    EfiTcp6StateTimeWait = 8,
    EfiTcp6StateCloseWait = 9,
    EfiTcp6StateLastAck = 10
} EFI_TCP6_CONNECTION_STATE;

typedef EFI_STATUS (EFI_API *EFI_TCP6_GET_MODE_DATA)(
    struct efi_tcp6_protocol *This,
    EFI_TCP6_CONNECTION_STATE *Tcp6State,
    struct efi_tcp6_config_data *Tcp6ConfigData,
    struct efi_ip6_mode_data *Ip6ModeData,
    struct efi_managed_network_config_data *MnpConfigData,
    struct efi_simple_network_mode *SnpModeData
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_CONFIGURE)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_config_data *Tcp6ConfigData
);

struct efi_tcp6_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
};

struct efi_tcp6_connection_token {
    struct efi_tcp6_completion_token CompletionToken;
};

typedef EFI_STATUS (EFI_API *EFI_TCP6_CONNECT)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_connection_token *ConnectionToken
);

struct efi_tcp6_listen_token {
    struct efi_tcp6_completion_token CompletionToken;
    EFI_HANDLE NewChildHandle;
};

typedef EFI_STATUS (EFI_API *EFI_TCP6_ACCEPT)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_listen_token *ListenToken
);

struct efi_tcp6_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

struct efi_tcp6_receive_data {
    uint8_t UrgentFlag;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_tcp6_fragment_data FragmentTable[1];
};

struct efi_tcp6_transmit_data {
    uint8_t Push;
    uint8_t Urgent;
    uint32_t DataLength;
    uint32_t FragmentCount;
    struct efi_tcp6_fragment_data FragmentTable[1];
};

struct efi_tcp6_io_token {
    struct efi_tcp6_completion_token CompletionToken;
    union {
        struct efi_tcp6_receive_data *RxData;
        struct efi_tcp6_transmit_data *TxData;
    } Packet;
};

typedef EFI_STATUS (EFI_API *EFI_TCP6_TRANSMIT)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_io_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_RECEIVE)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_io_token *Token
);

struct efi_tcp6_close_token {
    struct efi_tcp6_completion_token CompletionToken;
    uint8_t AbortOnClose;
};

typedef EFI_STATUS (EFI_API *EFI_TCP6_CLOSE)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_close_token *CloseToken
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_CANCEL)(
    struct efi_tcp6_protocol *This,
    struct efi_tcp6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_POLL)(struct efi_tcp6_protocol *This);

struct efi_tcp6_protocol {
    EFI_TCP6_GET_MODE_DATA GetModeData;
    EFI_TCP6_CONFIGURE Configure;
    EFI_TCP6_CONNECT Connect;
    EFI_TCP6_ACCEPT Accept;
    EFI_TCP6_TRANSMIT Transmit;
    EFI_TCP6_RECEIVE Receive;
    EFI_TCP6_CLOSE Close;
    EFI_TCP6_CANCEL Cancel;
    EFI_TCP6_POLL Poll;
};

#ifdef __cplusplus
}
#endif

#endif
