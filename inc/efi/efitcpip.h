#ifndef EFI_EFITCPIP_H_
#define EFI_EFITCPIP_H_

#include "efiapi.h"
#include "efiip.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_IP4_CONFIG2_PROTOCOL_GUID \
    {0x5b446ed1, 0xe30b, 0x4faa, {0x87, 0x1a, 0x36, 0x54, 0xec, 0xa3, 0x60, 0x80}}

typedef struct _EFI_IP4_CONFIG2_PROTOCOL EFI_IP4_CONFIG2_PROTOCOL;

typedef enum {
    EfiIp4Config2DataTypeInterfaceInfo,
    EfiIp4Config2DataTypePolicy,
    EfiIp4Config2DataTypeManualAddress,
    EfiIp4Config2DataTypeGateway,
    EfiIp4Config2DataTypeDnsServer,
    EfiIp4Config2DataTypeMaximum
} EFI_IP4_CONFIG2_DATA_TYPE;

#define EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE 32

typedef struct {
    uint16_t Name[EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE];
    uint8_t IfType;
    uint32_t HwAddressSize;
    EFI_MAC_ADDRESS HwAddress;
    EFI_IPv4_ADDRESS StationAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    uint32_t RouteTableSize;
    EFI_IP4_ROUTE_TABLE *RouteTable;
} EFI_IP4_CONFIG2_INTERFACE_INFO;

typedef enum {
    EfiIp4Config2PolicyStatic,
    EfiIp4Config2PolicyDhcp,
    EfiIp4Config2PolicyMax
} EFI_IP4_CONFIG2_POLICY;

typedef struct {
    EFI_IPv4_ADDRESS Address;
    EFI_IPv4_ADDRESS SubnetMask;
} EFI_IP4_CONFIG2_MANUAL_ADDRESS;

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_SET_DATA)(
    EFI_IP4_CONFIG2_PROTOCOL *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_GET_DATA)(
    EFI_IP4_CONFIG2_PROTOCOL *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_REGISTER_NOTIFY)(
    EFI_IP4_CONFIG2_PROTOCOL *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_UNREGISTER_NOTIFY)(
    EFI_IP4_CONFIG2_PROTOCOL *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct _EFI_IP4_CONFIG2_PROTOCOL {
    EFI_IP4_CONFIG2_SET_DATA SetData;
    EFI_IP4_CONFIG2_GET_DATA GetData;
    EFI_IP4_CONFIG2_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IP4_CONFIG2_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IP6_CONFIG_PROTOCOL_GUID \
    {0x937fe521, 0x95ae, 0x4d1a, {0x89, 0x29, 0x48, 0xbc, 0xd9, 0x0a, 0xd3, 0x1a}}

typedef struct _EFI_IP6_CONFIG_PROTOCOL EFI_IP6_CONFIG_PROTOCOL;

typedef enum {
    EfiIp6ConfigDataTypeInterfaceInfo,
    EfiIp6ConfigDataTypeAltInterfaceId,
    EfiIp6ConfigDataTypePolicy,
    EfiIp6ConfigDataTypeDupAddrDetectTransmits,
    EfiIp6ConfigDataTypeManualAddress,
    EfiIp6ConfigDataTypeGateway,
    EfiIp6ConfigDataTypeDnsServer,
    EfiIp6ConfigDataTypeMaximum
} EFI_IP6_CONFIG_DATA_TYPE;

typedef struct {
    uint16_t Name[32];
    uint8_t IfType;
    uint32_t HwAddressSize;
    EFI_MAC_ADDRESS HwAddress;
    uint32_t AddressInfoCount;
    EFI_IP6_ADDRESS_INFO *AddressInfo;
    uint32_t RouteCount;
    EFI_IP6_ROUTE_TABLE *RouteTable;
} EFI_IP6_CONFIG_INTERFACE_INFO;

typedef struct {
    uint8_t Id[8];
} EFI_IP6_CONFIG_INTERFACE_ID;

typedef enum {
    EfiIp6ConfigPolicyManual,
    EfiIp6ConfigPolicyAutomatic
} EFI_IP6_CONFIG_POLICY;

typedef struct {
    uint32_t DupAddrDetectTransmits;
} EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS;

typedef struct {
    EFI_IPv6_ADDRESS Address;
    uint8_t IsAnycast;
    uint8_t PrefixLength;
} EFI_IP6_CONFIG_MANUAL_ADDRESS;

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_SET_DATA)(
    EFI_IP6_CONFIG_PROTOCOL *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_GET_DATA)(
    EFI_IP6_CONFIG_PROTOCOL *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_REGISTER_NOTIFY)(
    EFI_IP6_CONFIG_PROTOCOL *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_UNREGISTER_NOTIFY)(
    EFI_IP6_CONFIG_PROTOCOL *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct _EFI_IP6_CONFIG_PROTOCOL {
    EFI_IP6_CONFIG_SET_DATA SetData;
    EFI_IP6_CONFIG_GET_DATA GetData;
    EFI_IP6_CONFIG_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IP6_CONFIG_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IPSEC_CONFIG_PROTOCOL_GUID \
    {0xce5e5929, 0xc7a3, 0x4602, {0xad, 0x9e, 0xc9, 0xda, 0xf9, 0x4e, 0xbf, 0xcf}}

typedef struct _EFI_IPSEC_CONFIG_PROTOCOL EFI_IPSEC_CONFIG_PROTOCOL;

typedef enum {
    EfiIPsecConfigDataTypeSpd,
    EfiIPsecConfigDataTypeSad,
    EfiIPsecConfigDataTypePad,
    EfiIPsecConfigDataTypeMaximum
} EFI_IPSEC_CONFIG_DATA_TYPE;

typedef struct _EFI_IP_ADDRESS_INFO {
    EFI_IP_ADDRESS Address;
    uint8_t PrefixLength;
} EFI_IP_ADDRESS_INFO;

typedef struct _EFI_IPSEC_SPD_SELECTOR {
    uint32_t LocalAddressCount;
    EFI_IP_ADDRESS_INFO *LocalAddress;
    uint32_t RemoteAddressCount;
    EFI_IP_ADDRESS_INFO *RemoteAddress;
    uint16_t NextLayerProtocol;
    uint16_t LocalPort;
    uint16_t LocalPortRange;
    uint16_t RemotePort;
    uint16_t RemotePortRange;
} EFI_IPSEC_SPD_SELECTOR;

typedef enum {
    EfiIPsecAH,
    EfiIPsecESP
} EFI_IPSEC_PROTOCOL_TYPE;

typedef struct _EFI_IPSEC_SA_ID {
    uint32_t Spi;
    EFI_IPSEC_PROTOCOL_TYPE Proto;
    EFI_IP_ADDRESS DestAddress;
} EFI_IPSEC_SA_ID;

#define EFI_MAX_PEERID_LEN 128

typedef struct _EFI_IPSEC_PAD_ID {
    uint8_t PeerIdValid;
    union {
        EFI_IP_ADDRESS_INFO IpAddress;
        uint8_t PeerId[EFI_MAX_PEERID_LEN];
    } Id;
} EFI_IPSEC_PAD_ID;

typedef union {
    EFI_IPSEC_SPD_SELECTOR SpdSelector;
    EFI_IPSEC_SA_ID SaId;
    EFI_IPSEC_PAD_ID PadId;
} EFI_IPSEC_CONFIG_SELECTOR;

typedef enum {
    EfiIPsecInBound,
    EfiIPsecOutBound
} EFI_IPSEC_TRAFFIC_DIR;

typedef enum {
    EfiIPsecActionDiscard,
    EfiIPsecActionBypass,
    EfiIPsecActionProtect
} EFI_IPSEC_ACTION;

typedef struct _EFI_IPSEC_SA_LIFETIME {
    uint64_t ByteCount;
    uint64_t SoftLifetime;
    uint64_t HardLifetime;
} EFI_IPSEC_SA_LIFETIME;

typedef enum {
    EfiIPsecTransport,
    EfiIPsecTunnel
} EFI_IPSEC_MODE;

typedef enum {
    EfiIPsecTunnelClearDf,
    EfiIPsecTunnelSetDf,
    EfiIPsecTunnelCopyDf
} EFI_IPSEC_TUNNEL_DF_OPTION;

typedef struct _EFI_IPSEC_TUNNEL_OPTION {
    EFI_IP_ADDRESS LocalTunnelAddress;
    EFI_IP_ADDRESS RemoteTunnelAddress;
    EFI_IPSEC_TUNNEL_DF_OPTION DF;
} EFI_IPSEC_TUNNEL_OPTION;

typedef struct _EFI_IPSEC_PROCESS_POLICY {
    uint8_t ExtSeqNum;
    uint8_t SeqOverflow;
    uint8_t FragCheck;
    EFI_IPSEC_SA_LIFETIME SaLifetime;
    EFI_IPSEC_MODE Mode;
    EFI_IPSEC_TUNNEL_OPTION *TunnelOption;
    EFI_IPSEC_PROTOCOL_TYPE Proto;
    uint8_t AuthAlgoId;
    uint8_t EncAlgoId;
} EFI_IPSEC_PROCESS_POLICY;

/* Name holds a null-terminated ASCII string, as described; printed as an array of pointers. */
typedef struct _EFI_IPSEC_SPD_DATA {
    uint8_t Name[EFI_MAX_PEERID_LEN];
    uint32_t PackageFlag;
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection;
    EFI_IPSEC_ACTION Action;
    EFI_IPSEC_PROCESS_POLICY *ProcessingPolicy;
    size_t SaIdCount;
    EFI_IPSEC_SA_ID *SaId[1];
} EFI_IPSEC_SPD_DATA;

typedef struct _EFI_IPSEC_AH_ALGO_INFO {
    uint8_t AuthAlgoId;
    size_t KeyLength;
    void *Key;
} EFI_IPSEC_AH_ALGO_INFO;

typedef struct _EFI_IPSEC_ESP_ALGO_INFO {
    uint8_t EncAlgoId;
    size_t EncKeyLength;
    void *EncKey;
    uint8_t AuthAlgoId;
    size_t AuthKeyLength;
    void *AuthKey;
} EFI_IPSEC_ESP_ALGO_INFO;

typedef union {
    EFI_IPSEC_AH_ALGO_INFO AhAlgoInfo;
    EFI_IPSEC_ESP_ALGO_INFO EspAlgoInfo;
} EFI_IPSEC_ALGO_INFO;

typedef struct _EFI_IPSEC_SA_DATA {
    EFI_IPSEC_MODE Mode;
    uint64_t SNCount;
    uint8_t AntiReplayWindows;
    EFI_IPSEC_ALGO_INFO AlgoInfo;
    EFI_IPSEC_SA_LIFETIME SaLifetime;
    uint32_t PathMTU;
    EFI_IPSEC_SPD_SELECTOR *SpdSelector;
    uint8_t ManualSet;
} EFI_IPSEC_SA_DATA;

typedef struct _EFI_IPSEC_SA_DATA2 {
    EFI_IPSEC_MODE Mode;
    uint64_t SNCount;
    uint8_t AntiReplayWindows;
    EFI_IPSEC_ALGO_INFO AlgoInfo;
    EFI_IPSEC_SA_LIFETIME SaLifetime;
    uint32_t PathMTU;
    EFI_IPSEC_SPD_SELECTOR *SpdSelector;
    uint8_t ManualSet;
    EFI_IP_ADDRESS TunnelSourceAddress;
    EFI_IP_ADDRESS TunnelDestinationAddress;
} EFI_IPSEC_SA_DATA2;

typedef enum {
    EfiIPsecAuthProtocolIKEv1,
    EfiIPsecAuthProtocolIKEv2,
    EfiIPsecAuthProtocolMaximum
} EFI_IPSEC_AUTH_PROTOCOL_TYPE;

typedef enum {
    EfiIPsecAuthMethodPreSharedSecret,
    EfiIPsecAuthMethodCertificates,
    EfiIPsecAuthMethodMaximum
} EFI_IPSEC_AUTH_METHOD;

typedef struct _EFI_IPSEC_PAD_DATA {
    EFI_IPSEC_AUTH_PROTOCOL_TYPE AuthProtocol;
    EFI_IPSEC_AUTH_METHOD AuthMethod;
    uint8_t IkeIdFlag;
    size_t AuthDataSize;
    void *AuthData;
    size_t RevocationDataSize;
    void *RevocationData;
} EFI_IPSEC_PAD_DATA;

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_SET_DATA)(
    EFI_IPSEC_CONFIG_PROTOCOL *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_IPSEC_CONFIG_SELECTOR *Selector,
    void *Data,
    EFI_IPSEC_CONFIG_SELECTOR *InsertBefore
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_GET_DATA)(
    EFI_IPSEC_CONFIG_PROTOCOL *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_IPSEC_CONFIG_SELECTOR *Selector,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR)(
    EFI_IPSEC_CONFIG_PROTOCOL *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    size_t *SelectorSize,
    EFI_IPSEC_CONFIG_SELECTOR *Selector
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_REGISTER_NOTIFY)(
    EFI_IPSEC_CONFIG_PROTOCOL *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY)(
    EFI_IPSEC_CONFIG_PROTOCOL *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct _EFI_IPSEC_CONFIG_PROTOCOL {
    EFI_IPSEC_CONFIG_SET_DATA SetData;
    EFI_IPSEC_CONFIG_GET_DATA GetData;
    EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR GetNextSelector;
    EFI_IPSEC_CONFIG_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IPSEC_PROTOCOL_GUID \
    {0xdfb386f7, 0xe100, 0x43ad, {0x9c, 0x9a, 0xed, 0x90, 0xd0, 0x8a, 0x5e, 0x12}}

typedef struct _EFI_IPSEC_PROTOCOL EFI_IPSEC_PROTOCOL;

typedef struct _EFI_IPSEC_FRAGMENT_DATA {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_IPSEC_FRAGMENT_DATA;

typedef EFI_STATUS (EFI_API *EFI_IPSEC_PROCESS)(
    EFI_IPSEC_PROTOCOL *This,
    EFI_HANDLE NicHandle,
    uint8_t IpVer,
    void *IpHead,
    uint8_t *LastHead,
    void *OptionsBuffer,
    uint32_t OptionsLength,
    EFI_IPSEC_FRAGMENT_DATA **FragmentTable,
    uint32_t *FragmentCount,
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection,
    EFI_EVENT *RecycleSignal
);

struct _EFI_IPSEC_PROTOCOL {
    EFI_IPSEC_PROCESS Process;
    EFI_EVENT DisabledEvent;
    uint8_t DisabledFlag;
};

#define EFI_IPSEC2_PROTOCOL_GUID \
    {0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77}}

typedef struct _EFI_IPSEC2_PROTOCOL EFI_IPSEC2_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_IPSEC_PROCESSEXT)(
    EFI_IPSEC2_PROTOCOL *This,
    EFI_HANDLE NicHandle,
    uint8_t IpVer,
    void *IpHead,
    uint8_t *LastHead,
    void **OptionsBuffer,
    uint32_t *OptionsLength,
    EFI_IPSEC_FRAGMENT_DATA **FragmentTable,
    uint32_t *FragmentCount,
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection,
    EFI_EVENT *RecycleSignal
);

struct _EFI_IPSEC2_PROTOCOL {
    EFI_IPSEC_PROCESSEXT ProcessExt;
    EFI_EVENT DisabledEvent;
    uint8_t DisabledFlag;
};

#define EFI_FTP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xfaaecb1, 0x226e, 0x4782, {0xaa, 0xce, 0x7d, 0xb9, 0xbc, 0xbf, 0x4d, 0xaf}}

#define EFI_FTP4_PROTOCOL_GUID \
    {0xeb338826, 0x681b, 0x4295, {0xb3, 0x56, 0x2b, 0x36, 0x4c, 0x75, 0x7b, 0x09}}

typedef struct _EFI_FTP4_PROTOCOL EFI_FTP4_PROTOCOL;

typedef struct {
    uint8_t *Username;
    uint8_t *Password;
    uint8_t Active;
    uint8_t UseDefaultSetting;
    EFI_IPv4_ADDRESS StationIp;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_IPv4_ADDRESS GatewayIp;
    EFI_IPv4_ADDRESS ServerIp;
    uint16_t ServerPort;
    uint16_t AltDataPort;
    uint8_t RepType;
    uint8_t FileStruct;
    uint8_t TransMode;
} EFI_FTP4_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_FTP4_GET_MODE_DATA)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_CONFIG_DATA *ModeData
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
} EFI_FTP4_CONNECTION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_FTP4_CONNECT)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_CONNECTION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_CLOSE)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_CONNECTION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_CONFIGURE)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_CONFIG_DATA *FtpConfigData
);

typedef struct _EFI_FTP4_COMMAND_TOKEN EFI_FTP4_COMMAND_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_FTP4_DATA_CALLBACK)(
    EFI_FTP4_COMMAND_TOKEN *Token,
    EFI_FTP4_PROTOCOL *This
);

struct _EFI_FTP4_COMMAND_TOKEN {
    EFI_EVENT Event;
    uint8_t *Pathname;
    uint64_t DataBufferSize;
    void *DataBuffer;
    EFI_FTP4_DATA_CALLBACK DataCallback;
    void *Context;
    EFI_STATUS Status;
};

typedef EFI_STATUS (EFI_API *EFI_FTP4_READ_FILE)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_COMMAND_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_WRITE_FILE)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_COMMAND_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_READ_DIRECTORY)(
    EFI_FTP4_PROTOCOL *This,
    EFI_FTP4_COMMAND_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_POLL)(EFI_FTP4_PROTOCOL *This);

struct _EFI_FTP4_PROTOCOL {
    EFI_FTP4_GET_MODE_DATA GetModeData;
    EFI_FTP4_CONNECT Connect;
    EFI_FTP4_CLOSE Close;
    EFI_FTP4_CONFIGURE Configure;
    EFI_FTP4_READ_FILE ReadFile;
    EFI_FTP4_WRITE_FILE WriteFile;
    EFI_FTP4_READ_DIRECTORY ReadDirectory;
    EFI_FTP4_POLL Poll;
};

#define EFI_TLS_SERVICE_BINDING_PROTOCOL_GUID \
    {0x952cb795, 0xff36, 0x48cf, {0xa2, 0x49, 0x4d, 0xf4, 0x86, 0xd6, 0xab, 0x8d}}

#define EFI_TLS_PROTOCOL_GUID \
    {0xca959f, 0x6cfa, 0x4db1, {0x95, 0xbc, 0xe4, 0x6c, 0x47, 0x51, 0x43, 0x90}}

typedef struct _EFI_TLS_PROTOCOL EFI_TLS_PROTOCOL;

typedef enum {
    EfiTlsVersion,
    EfiTlsConnectionEnd,
    EfiTlsCipherList,
    EfiTlsCompressionMethod,
    EfiTlsExtensionData,
    EfiTlsVerifyMethod,
    EfiTlsSessionID,
    EfiTlsSessionState,
    EfiTlsClientRandom,
    EfiTlsServerRandom,
    EfiTlsKeyMaterial,
    EfiTlsVerifyHost,
    EfiTlsSessionDataTypeMaximum
} EFI_TLS_SESSION_DATA_TYPE;

typedef struct {
    uint8_t Major;
    uint8_t Minor;
} EFI_TLS_VERSION;

typedef enum {
    EfiTlsClient,
    EfiTlsServer
} EFI_TLS_CONNECTION_END;

typedef struct {
    uint8_t Data1;
    uint8_t Data2;
} EFI_TLS_CIPHER;

typedef uint8_t EFI_TLS_COMPRESSION;

__extension__ typedef struct {
    uint16_t ExtensionType;
    uint16_t Length;
    uint8_t Data[];
} EFI_TLS_EXTENSION;

typedef uint32_t EFI_TLS_VERIFY;

#define EFI_TLS_VERIFY_NONE 0x0
#define EFI_TLS_VERIFY_PEER 0x1
#define EFI_TLS_VERIFY_FAIL_IF_NO_PEER_CERT 0x2
#define EFI_TLS_VERIFY_CLIENT_ONCE 0x4

typedef uint32_t EFI_TLS_VERIFY_HOST_FLAG;

#define EFI_TLS_VERIFY_FLAG_NONE 0x00
#define EFI_TLS_VERIFY_FLAG_ALWAYS_CHECK_SUBJECT 0x01
#define EFI_TLS_VERIFY_FLAG_NO_WILDCARDS 0x02
#define EFI_TLS_VERIFY_FLAG_NO_PARTIAL_WILDCARDS 0x04
#define EFI_TLS_VERIFY_FLAG_MULTI_LABEL_WILDCARDS 0x08
#define EFI_TLS_VERIFY_FLAG_SINGLE_LABEL_SUBDOMAINS 0x10
#define EFI_TLS_VERIFY_FLAG_NEVER_CHECK_SUBJECT 0x20

/* Packed as firmware lays it out, although the specification prints no packing. */
typedef struct __attribute__((__packed__)) {
    EFI_TLS_VERIFY_HOST_FLAG Flags;
    char *HostName;
} EFI_TLS_VERIFY_HOST;

typedef struct {
    uint32_t GmtUnixTime;
    uint8_t RandomBytes[28];
} EFI_TLS_RANDOM;

/* The 48-byte master secret of RFC 5246; printed as an array of 48 pointers. */
typedef struct {
    uint8_t Data[48];
} EFI_TLS_MASTER_SECRET;

#define EFI_MAX_TLS_SESSION_ID_LENGTH 32

typedef struct {
    uint16_t Length;
    uint8_t Data[EFI_MAX_TLS_SESSION_ID_LENGTH];
} EFI_TLS_SESSION_ID;

typedef enum {
    EfiTlsSessionNotStarted,
    EfiTlsSessionHandShaking,
    EfiTlsSessionDataTransferring,
    EfiTlsSessionClosing,
    EfiTlsSessionError,
    EfiTlsSessionStateMaximum
} EFI_TLS_SESSION_STATE;

typedef EFI_STATUS (EFI_API *EFI_TLS_SET_SESSION_DATA)(
    EFI_TLS_PROTOCOL *This,
    EFI_TLS_SESSION_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_GET_SESSION_DATA)(
    EFI_TLS_PROTOCOL *This,
    EFI_TLS_SESSION_DATA_TYPE DataType,
    void *Data,
    size_t *DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_BUILD_RESPONSE_PACKET)(
    EFI_TLS_PROTOCOL *This,
    uint8_t *RequestBuffer,
    size_t RequestSize,
    uint8_t *Buffer,
    size_t *BufferSize
);

typedef struct {
    uint32_t FragmentLength;
    void *FragmentBuffer;
} EFI_TLS_FRAGMENT_DATA;

typedef enum {
    EfiTlsEncrypt,
    EfiTlsDecrypt
} EFI_TLS_CRYPT_MODE;

typedef EFI_STATUS (EFI_API *EFI_TLS_PROCESS_PACKET)(
    EFI_TLS_PROTOCOL *This,
    EFI_TLS_FRAGMENT_DATA **FragmentTable,
    uint32_t *FragmentCount,
    EFI_TLS_CRYPT_MODE CryptMode
);

struct _EFI_TLS_PROTOCOL {
    EFI_TLS_SET_SESSION_DATA SetSessionData;
    EFI_TLS_GET_SESSION_DATA GetSessionData;
    EFI_TLS_BUILD_RESPONSE_PACKET BuildResponsePacket;
    EFI_TLS_PROCESS_PACKET ProcessPacket;
};

#define EFI_TLS_CONFIGURATION_PROTOCOL_GUID \
    {0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d}}

typedef struct _EFI_TLS_CONFIGURATION_PROTOCOL EFI_TLS_CONFIGURATION_PROTOCOL;

typedef enum {
    EfiTlsConfigDataTypeHostPublicCert,
    EfiTlsConfigDataTypeHostPrivateKey,
    EfiTlsConfigDataTypeCACertificate,
    EfiTlsConfigDataTypeCertRevocationList,
    EfiTlsConfigDataTypeMaximum
} EFI_TLS_CONFIG_DATA_TYPE;

typedef EFI_STATUS (EFI_API *EFI_TLS_CONFIGURATION_SET_DATA)(
    EFI_TLS_CONFIGURATION_PROTOCOL *This,
    EFI_TLS_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_CONFIGURATION_GET_DATA)(
    EFI_TLS_CONFIGURATION_PROTOCOL *This,
    EFI_TLS_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t *DataSize
);

struct _EFI_TLS_CONFIGURATION_PROTOCOL {
    EFI_TLS_CONFIGURATION_SET_DATA SetData;
    EFI_TLS_CONFIGURATION_GET_DATA GetData;
};

#ifdef __cplusplus
}
#endif

#endif
