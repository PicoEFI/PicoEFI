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

typedef struct _EFI_TCP4_PROTOCOL EFI_TCP4_PROTOCOL;

typedef struct {
    EFI_BOOLEAN UseDefaultAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_UINT16 StationPort;
    EFI_IPv4_ADDRESS RemoteAddress;
    EFI_UINT16 RemotePort;
    EFI_BOOLEAN ActiveFlag;
} EFI_TCP4_ACCESS_POINT;

typedef struct {
    EFI_UINT32 ReceiveBufferSize;
    EFI_UINT32 SendBufferSize;
    EFI_UINT32 MaxSynBackLog;
    EFI_UINT32 ConnectionTimeout;
    EFI_UINT32 DataRetries;
    EFI_UINT32 FinTimeout;
    EFI_UINT32 TimeWaitTimeout;
    EFI_UINT32 KeepAliveProbes;
    EFI_UINT32 KeepAliveTime;
    EFI_UINT32 KeepAliveInterval;
    EFI_BOOLEAN EnableNagle;
    EFI_BOOLEAN EnableTimeStamp;
    EFI_BOOLEAN EnableWindowScaling;
    EFI_BOOLEAN EnableSelectiveAck;
    EFI_BOOLEAN EnablePathMtuDiscovery;
} EFI_TCP4_OPTION;

/* ControlOption may be NULL, as described (and a pointer in TCPv6); printed by value. */
typedef struct {
    EFI_UINT8 TypeOfService;
    EFI_UINT8 TimeToLive;
    EFI_TCP4_ACCESS_POINT AccessPoint;
    EFI_TCP4_OPTION *ControlOption;
} EFI_TCP4_CONFIG_DATA;

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
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_OUT EFI_TCP4_CONNECTION_STATE *Tcp4State EFI_OPTIONAL,
    EFI_OUT EFI_TCP4_CONFIG_DATA *Tcp4ConfigData EFI_OPTIONAL,
    EFI_OUT EFI_IP4_MODE_DATA *Ip4ModeData EFI_OPTIONAL,
    EFI_OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData EFI_OPTIONAL,
    EFI_OUT EFI_SIMPLE_NETWORK_MODE *SnpModeData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_CONFIGURE)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_CONFIG_DATA *TcpConfigData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_ROUTES)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteRoute,
    EFI_IN EFI_IPv4_ADDRESS *SubnetAddress,
    EFI_IN EFI_IPv4_ADDRESS *SubnetMask,
    EFI_IN EFI_IPv4_ADDRESS *GatewayAddress
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_TCP4_COMPLETION_TOKEN;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
} EFI_TCP4_CONNECTION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP4_CONNECT)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_CONNECTION_TOKEN *ConnectionToken
);

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    EFI_HANDLE NewChildHandle;
} EFI_TCP4_LISTEN_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP4_ACCEPT)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_LISTEN_TOKEN *ListenToken
);

typedef struct {
    EFI_UINT32 FragmentLength;
    EFI_VOID *FragmentBuffer;
} EFI_TCP4_FRAGMENT_DATA;

typedef struct {
    EFI_BOOLEAN UrgentFlag;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_RECEIVE_DATA;

typedef struct {
    EFI_BOOLEAN Push;
    EFI_BOOLEAN Urgent;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_TCP4_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP4_TRANSMIT_DATA;

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    union {
        EFI_TCP4_RECEIVE_DATA *RxData;
        EFI_TCP4_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_TCP4_IO_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP4_TRANSMIT)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_RECEIVE)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_IO_TOKEN *Token
);

typedef struct {
    EFI_TCP4_COMPLETION_TOKEN CompletionToken;
    EFI_BOOLEAN AbortOnClose;
} EFI_TCP4_CLOSE_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP4_CLOSE)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_CLOSE_TOKEN *CloseToken
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_CANCEL)(
    EFI_IN EFI_TCP4_PROTOCOL *This,
    EFI_IN EFI_TCP4_COMPLETION_TOKEN *Token EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_TCP4_POLL)(EFI_IN EFI_TCP4_PROTOCOL *This);

struct _EFI_TCP4_PROTOCOL {
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

typedef struct _EFI_TCP6_PROTOCOL EFI_TCP6_PROTOCOL;

typedef struct {
    EFI_IPv6_ADDRESS StationAddress;
    EFI_UINT16 StationPort;
    EFI_IPv6_ADDRESS RemoteAddress;
    EFI_UINT16 RemotePort;
    EFI_BOOLEAN ActiveFlag;
} EFI_TCP6_ACCESS_POINT;

typedef struct {
    EFI_UINT32 ReceiveBufferSize;
    EFI_UINT32 SendBufferSize;
    EFI_UINT32 MaxSynBackLog;
    EFI_UINT32 ConnectionTimeout;
    EFI_UINT32 DataRetries;
    EFI_UINT32 FinTimeout;
    EFI_UINT32 TimeWaitTimeout;
    EFI_UINT32 KeepAliveProbes;
    EFI_UINT32 KeepAliveTime;
    EFI_UINT32 KeepAliveInterval;
    EFI_BOOLEAN EnableNagle;
    EFI_BOOLEAN EnableTimeStamp;
    EFI_BOOLEAN EnableWindowScaling;
    EFI_BOOLEAN EnableSelectiveAck;
    EFI_BOOLEAN EnablePathMtuDiscovery;
} EFI_TCP6_OPTION;

typedef struct {
    EFI_UINT8 TrafficClass;
    EFI_UINT8 HopLimit;
    EFI_TCP6_ACCESS_POINT AccessPoint;
    EFI_TCP6_OPTION *ControlOption;
} EFI_TCP6_CONFIG_DATA;

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
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_OUT EFI_TCP6_CONNECTION_STATE *Tcp6State EFI_OPTIONAL,
    EFI_OUT EFI_TCP6_CONFIG_DATA *Tcp6ConfigData EFI_OPTIONAL,
    EFI_OUT EFI_IP6_MODE_DATA *Ip6ModeData EFI_OPTIONAL,
    EFI_OUT EFI_MANAGED_NETWORK_CONFIG_DATA *MnpConfigData EFI_OPTIONAL,
    EFI_OUT EFI_SIMPLE_NETWORK_MODE *SnpModeData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_CONFIGURE)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_CONFIG_DATA *Tcp6ConfigData EFI_OPTIONAL
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_TCP6_COMPLETION_TOKEN;

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
} EFI_TCP6_CONNECTION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP6_CONNECT)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_CONNECTION_TOKEN *ConnectionToken
);

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
    EFI_HANDLE NewChildHandle;
} EFI_TCP6_LISTEN_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP6_ACCEPT)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_LISTEN_TOKEN *ListenToken
);

typedef struct {
    EFI_UINT32 FragmentLength;
    EFI_VOID *FragmentBuffer;
} EFI_TCP6_FRAGMENT_DATA;

typedef struct {
    EFI_BOOLEAN UrgentFlag;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_TCP6_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP6_RECEIVE_DATA;

typedef struct {
    EFI_BOOLEAN Push;
    EFI_BOOLEAN Urgent;
    EFI_UINT32 DataLength;
    EFI_UINT32 FragmentCount;
    EFI_TCP6_FRAGMENT_DATA FragmentTable[1];
} EFI_TCP6_TRANSMIT_DATA;

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
    union {
        EFI_TCP6_RECEIVE_DATA *RxData;
        EFI_TCP6_TRANSMIT_DATA *TxData;
    } Packet;
} EFI_TCP6_IO_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP6_TRANSMIT)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_IO_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_RECEIVE)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_IO_TOKEN *Token
);

typedef struct {
    EFI_TCP6_COMPLETION_TOKEN CompletionToken;
    EFI_BOOLEAN AbortOnClose;
} EFI_TCP6_CLOSE_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_TCP6_CLOSE)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_CLOSE_TOKEN *CloseToken
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_CANCEL)(
    EFI_IN EFI_TCP6_PROTOCOL *This,
    EFI_IN EFI_TCP6_COMPLETION_TOKEN *Token EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_TCP6_POLL)(EFI_IN EFI_TCP6_PROTOCOL *This);

struct _EFI_TCP6_PROTOCOL {
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
