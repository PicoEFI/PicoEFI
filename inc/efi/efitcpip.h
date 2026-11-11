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

typedef enum {
    EfiIp4Config2DataTypeInterfaceInfo,
    EfiIp4Config2DataTypePolicy,
    EfiIp4Config2DataTypeManualAddress,
    EfiIp4Config2DataTypeGateway,
    EfiIp4Config2DataTypeDnsServer,
    EfiIp4Config2DataTypeMaximum
} EFI_IP4_CONFIG2_DATA_TYPE;

#define EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE 32

struct efi_ip4_config2_interface_info {
    uint16_t Name[EFI_IP4_CONFIG2_INTERFACE_INFO_NAME_SIZE];
    uint8_t IfType;
    uint32_t HwAddressSize;
    struct efi_mac_address HwAddress;
    struct efi_ipv4_address StationAddress;
    struct efi_ipv4_address SubnetMask;
    uint32_t RouteTableSize;
    struct efi_ip4_route_table *RouteTable;
};

typedef enum {
    EfiIp4Config2PolicyStatic,
    EfiIp4Config2PolicyDhcp,
    EfiIp4Config2PolicyMax
} EFI_IP4_CONFIG2_POLICY;

struct efi_ip4_config2_manual_address {
    struct efi_ipv4_address Address;
    struct efi_ipv4_address SubnetMask;
};

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_SET_DATA)(
    struct efi_ip4_config2_protocol *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_GET_DATA)(
    struct efi_ip4_config2_protocol *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_REGISTER_NOTIFY)(
    struct efi_ip4_config2_protocol *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IP4_CONFIG2_UNREGISTER_NOTIFY)(
    struct efi_ip4_config2_protocol *This,
    EFI_IP4_CONFIG2_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct efi_ip4_config2_protocol {
    EFI_IP4_CONFIG2_SET_DATA SetData;
    EFI_IP4_CONFIG2_GET_DATA GetData;
    EFI_IP4_CONFIG2_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IP4_CONFIG2_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IP6_CONFIG_PROTOCOL_GUID \
    {0x937fe521, 0x95ae, 0x4d1a, {0x89, 0x29, 0x48, 0xbc, 0xd9, 0x0a, 0xd3, 0x1a}}

struct efi_ip6_config_protocol;

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

struct efi_ip6_config_interface_info {
    uint16_t Name[32];
    uint8_t IfType;
    uint32_t HwAddressSize;
    struct efi_mac_address HwAddress;
    uint32_t AddressInfoCount;
    struct efi_ip6_address_info *AddressInfo;
    uint32_t RouteCount;
    struct efi_ip6_route_table *RouteTable;
};

struct efi_ip6_config_interface_id {
    uint8_t Id[8];
};

typedef enum {
    EfiIp6ConfigPolicyManual,
    EfiIp6ConfigPolicyAutomatic
} EFI_IP6_CONFIG_POLICY;

struct efi_ip6_config_dup_addr_detect_transmits {
    uint32_t DupAddrDetectTransmits;
};

struct efi_ip6_config_manual_address {
    struct efi_ipv6_address Address;
    uint8_t IsAnycast;
    uint8_t PrefixLength;
};

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_SET_DATA)(
    struct efi_ip6_config_protocol *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_GET_DATA)(
    struct efi_ip6_config_protocol *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_REGISTER_NOTIFY)(
    struct efi_ip6_config_protocol *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IP6_CONFIG_UNREGISTER_NOTIFY)(
    struct efi_ip6_config_protocol *This,
    EFI_IP6_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct efi_ip6_config_protocol {
    EFI_IP6_CONFIG_SET_DATA SetData;
    EFI_IP6_CONFIG_GET_DATA GetData;
    EFI_IP6_CONFIG_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IP6_CONFIG_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IPSEC_CONFIG_PROTOCOL_GUID \
    {0xce5e5929, 0xc7a3, 0x4602, {0xad, 0x9e, 0xc9, 0xda, 0xf9, 0x4e, 0xbf, 0xcf}}

struct efi_ipsec_config_protocol;

typedef enum {
    EfiIPsecConfigDataTypeSpd,
    EfiIPsecConfigDataTypeSad,
    EfiIPsecConfigDataTypePad,
    EfiIPsecConfigDataTypeMaximum
} EFI_IPSEC_CONFIG_DATA_TYPE;

struct efi_ip_address_info {
    union efi_ip_address Address;
    uint8_t PrefixLength;
};

struct efi_ipsec_spd_selector {
    uint32_t LocalAddressCount;
    struct efi_ip_address_info *LocalAddress;
    uint32_t RemoteAddressCount;
    struct efi_ip_address_info *RemoteAddress;
    uint16_t NextLayerProtocol;
    uint16_t LocalPort;
    uint16_t LocalPortRange;
    uint16_t RemotePort;
    uint16_t RemotePortRange;
};

typedef enum {
    EfiIPsecAH,
    EfiIPsecESP
} EFI_IPSEC_PROTOCOL_TYPE;

struct efi_ipsec_sa_id {
    uint32_t Spi;
    EFI_IPSEC_PROTOCOL_TYPE Proto;
    union efi_ip_address DestAddress;
};

#define EFI_MAX_PEERID_LEN 128

struct efi_ipsec_pad_id {
    uint8_t PeerIdValid;
    union {
        struct efi_ip_address_info IpAddress;
        uint8_t PeerId[EFI_MAX_PEERID_LEN];
    } Id;
};

union efi_ipsec_config_selector {
    struct efi_ipsec_spd_selector SpdSelector;
    struct efi_ipsec_sa_id SaId;
    struct efi_ipsec_pad_id PadId;
};

typedef enum {
    EfiIPsecInBound,
    EfiIPsecOutBound
} EFI_IPSEC_TRAFFIC_DIR;

typedef enum {
    EfiIPsecActionDiscard,
    EfiIPsecActionBypass,
    EfiIPsecActionProtect
} EFI_IPSEC_ACTION;

struct efi_ipsec_sa_lifetime {
    uint64_t ByteCount;
    uint64_t SoftLifetime;
    uint64_t HardLifetime;
};

typedef enum {
    EfiIPsecTransport,
    EfiIPsecTunnel
} EFI_IPSEC_MODE;

typedef enum {
    EfiIPsecTunnelClearDf,
    EfiIPsecTunnelSetDf,
    EfiIPsecTunnelCopyDf
} EFI_IPSEC_TUNNEL_DF_OPTION;

struct efi_ipsec_tunnel_option {
    union efi_ip_address LocalTunnelAddress;
    union efi_ip_address RemoteTunnelAddress;
    EFI_IPSEC_TUNNEL_DF_OPTION DF;
};

struct efi_ipsec_process_policy {
    uint8_t ExtSeqNum;
    uint8_t SeqOverflow;
    uint8_t FragCheck;
    struct efi_ipsec_sa_lifetime SaLifetime;
    EFI_IPSEC_MODE Mode;
    struct efi_ipsec_tunnel_option *TunnelOption;
    EFI_IPSEC_PROTOCOL_TYPE Proto;
    uint8_t AuthAlgoId;
    uint8_t EncAlgoId;
};

/* Name holds a null-terminated ASCII string, as described; printed as an array of pointers. */
struct efi_ipsec_spd_data {
    uint8_t Name[EFI_MAX_PEERID_LEN];
    uint32_t PackageFlag;
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection;
    EFI_IPSEC_ACTION Action;
    struct efi_ipsec_process_policy *ProcessingPolicy;
    size_t SaIdCount;
    struct efi_ipsec_sa_id *SaId[1];
};

struct efi_ipsec_ah_algo_info {
    uint8_t AuthAlgoId;
    size_t KeyLength;
    void *Key;
};

struct efi_ipsec_esp_algo_info {
    uint8_t EncAlgoId;
    size_t EncKeyLength;
    void *EncKey;
    uint8_t AuthAlgoId;
    size_t AuthKeyLength;
    void *AuthKey;
};

union efi_ipsec_algo_info {
    struct efi_ipsec_ah_algo_info AhAlgoInfo;
    struct efi_ipsec_esp_algo_info EspAlgoInfo;
};

struct efi_ipsec_sa_data {
    EFI_IPSEC_MODE Mode;
    uint64_t SNCount;
    uint8_t AntiReplayWindows;
    union efi_ipsec_algo_info AlgoInfo;
    struct efi_ipsec_sa_lifetime SaLifetime;
    uint32_t PathMTU;
    struct efi_ipsec_spd_selector *SpdSelector;
    uint8_t ManualSet;
};

struct efi_ipsec_sa_data2 {
    EFI_IPSEC_MODE Mode;
    uint64_t SNCount;
    uint8_t AntiReplayWindows;
    union efi_ipsec_algo_info AlgoInfo;
    struct efi_ipsec_sa_lifetime SaLifetime;
    uint32_t PathMTU;
    struct efi_ipsec_spd_selector *SpdSelector;
    uint8_t ManualSet;
    union efi_ip_address TunnelSourceAddress;
    union efi_ip_address TunnelDestinationAddress;
};

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

struct efi_ipsec_pad_data {
    EFI_IPSEC_AUTH_PROTOCOL_TYPE AuthProtocol;
    EFI_IPSEC_AUTH_METHOD AuthMethod;
    uint8_t IkeIdFlag;
    size_t AuthDataSize;
    void *AuthData;
    size_t RevocationDataSize;
    void *RevocationData;
};

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_SET_DATA)(
    struct efi_ipsec_config_protocol *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    union efi_ipsec_config_selector *Selector,
    void *Data,
    union efi_ipsec_config_selector *InsertBefore
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_GET_DATA)(
    struct efi_ipsec_config_protocol *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    union efi_ipsec_config_selector *Selector,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR)(
    struct efi_ipsec_config_protocol *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    size_t *SelectorSize,
    union efi_ipsec_config_selector *Selector
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_REGISTER_NOTIFY)(
    struct efi_ipsec_config_protocol *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY)(
    struct efi_ipsec_config_protocol *This,
    EFI_IPSEC_CONFIG_DATA_TYPE DataType,
    EFI_EVENT Event
);

struct efi_ipsec_config_protocol {
    EFI_IPSEC_CONFIG_SET_DATA SetData;
    EFI_IPSEC_CONFIG_GET_DATA GetData;
    EFI_IPSEC_CONFIG_GET_NEXT_SELECTOR GetNextSelector;
    EFI_IPSEC_CONFIG_REGISTER_NOTIFY RegisterDataNotify;
    EFI_IPSEC_CONFIG_UNREGISTER_NOTIFY UnregisterDataNotify;
};

#define EFI_IPSEC_PROTOCOL_GUID \
    {0xdfb386f7, 0xe100, 0x43ad, {0x9c, 0x9a, 0xed, 0x90, 0xd0, 0x8a, 0x5e, 0x12}}

struct efi_ipsec_protocol;

struct efi_ipsec_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

typedef EFI_STATUS (EFI_API *EFI_IPSEC_PROCESS)(
    struct efi_ipsec_protocol *This,
    EFI_HANDLE NicHandle,
    uint8_t IpVer,
    void *IpHead,
    uint8_t *LastHead,
    void *OptionsBuffer,
    uint32_t OptionsLength,
    struct efi_ipsec_fragment_data **FragmentTable,
    uint32_t *FragmentCount,
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection,
    EFI_EVENT *RecycleSignal
);

struct efi_ipsec_protocol {
    EFI_IPSEC_PROCESS Process;
    EFI_EVENT DisabledEvent;
    uint8_t DisabledFlag;
};

#define EFI_IPSEC2_PROTOCOL_GUID \
    {0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77}}

struct efi_ipsec2_protocol;

typedef EFI_STATUS (EFI_API *EFI_IPSEC_PROCESSEXT)(
    struct efi_ipsec2_protocol *This,
    EFI_HANDLE NicHandle,
    uint8_t IpVer,
    void *IpHead,
    uint8_t *LastHead,
    void **OptionsBuffer,
    uint32_t *OptionsLength,
    struct efi_ipsec_fragment_data **FragmentTable,
    uint32_t *FragmentCount,
    EFI_IPSEC_TRAFFIC_DIR TrafficDirection,
    EFI_EVENT *RecycleSignal
);

struct efi_ipsec2_protocol {
    EFI_IPSEC_PROCESSEXT ProcessExt;
    EFI_EVENT DisabledEvent;
    uint8_t DisabledFlag;
};

#define EFI_FTP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xfaaecb1, 0x226e, 0x4782, {0xaa, 0xce, 0x7d, 0xb9, 0xbc, 0xbf, 0x4d, 0xaf}}

#define EFI_FTP4_PROTOCOL_GUID \
    {0xeb338826, 0x681b, 0x4295, {0xb3, 0x56, 0x2b, 0x36, 0x4c, 0x75, 0x7b, 0x09}}

struct efi_ftp4_protocol;

struct efi_ftp4_config_data {
    uint8_t *Username;
    uint8_t *Password;
    uint8_t Active;
    uint8_t UseDefaultSetting;
    struct efi_ipv4_address StationIp;
    struct efi_ipv4_address SubnetMask;
    struct efi_ipv4_address GatewayIp;
    struct efi_ipv4_address ServerIp;
    uint16_t ServerPort;
    uint16_t AltDataPort;
    uint8_t RepType;
    uint8_t FileStruct;
    uint8_t TransMode;
};

typedef EFI_STATUS (EFI_API *EFI_FTP4_GET_MODE_DATA)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_config_data *ModeData
);

struct efi_ftp4_connection_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
};

typedef EFI_STATUS (EFI_API *EFI_FTP4_CONNECT)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_connection_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_CLOSE)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_connection_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_CONFIGURE)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_config_data *FtpConfigData
);

struct efi_ftp4_command_token;

typedef EFI_STATUS (EFI_API *EFI_FTP4_DATA_CALLBACK)(
    struct efi_ftp4_command_token *Token,
    struct efi_ftp4_protocol *This
);

struct efi_ftp4_command_token {
    EFI_EVENT Event;
    uint8_t *Pathname;
    uint64_t DataBufferSize;
    void *DataBuffer;
    EFI_FTP4_DATA_CALLBACK DataCallback;
    void *Context;
    EFI_STATUS Status;
};

typedef EFI_STATUS (EFI_API *EFI_FTP4_READ_FILE)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_command_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_WRITE_FILE)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_command_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_READ_DIRECTORY)(
    struct efi_ftp4_protocol *This,
    struct efi_ftp4_command_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_FTP4_POLL)(struct efi_ftp4_protocol *This);

struct efi_ftp4_protocol {
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

struct efi_tls_protocol;

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

struct efi_tls_version {
    uint8_t Major;
    uint8_t Minor;
};

typedef enum {
    EfiTlsClient,
    EfiTlsServer
} EFI_TLS_CONNECTION_END;

struct efi_tls_cipher {
    uint8_t Data1;
    uint8_t Data2;
};

typedef uint8_t EFI_TLS_COMPRESSION;

__extension__ struct efi_tls_extension {
    uint16_t ExtensionType;
    uint16_t Length;
    uint8_t Data[];
};

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
struct efi_tls_verify_host {
    EFI_TLS_VERIFY_HOST_FLAG Flags;
    char *HostName;
} __attribute__((__packed__));

struct efi_tls_random {
    uint32_t GmtUnixTime;
    uint8_t RandomBytes[28];
};

/* The 48-byte master secret of RFC 5246; printed as an array of 48 pointers. */
struct efi_tls_master_secret {
    uint8_t Data[48];
};

#define EFI_MAX_TLS_SESSION_ID_LENGTH 32

struct efi_tls_session_id {
    uint16_t Length;
    uint8_t Data[EFI_MAX_TLS_SESSION_ID_LENGTH];
};

typedef enum {
    EfiTlsSessionNotStarted,
    EfiTlsSessionHandShaking,
    EfiTlsSessionDataTransferring,
    EfiTlsSessionClosing,
    EfiTlsSessionError,
    EfiTlsSessionStateMaximum
} EFI_TLS_SESSION_STATE;

typedef EFI_STATUS (EFI_API *EFI_TLS_SET_SESSION_DATA)(
    struct efi_tls_protocol *This,
    EFI_TLS_SESSION_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_GET_SESSION_DATA)(
    struct efi_tls_protocol *This,
    EFI_TLS_SESSION_DATA_TYPE DataType,
    void *Data,
    size_t *DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_BUILD_RESPONSE_PACKET)(
    struct efi_tls_protocol *This,
    uint8_t *RequestBuffer,
    size_t RequestSize,
    uint8_t *Buffer,
    size_t *BufferSize
);

struct efi_tls_fragment_data {
    uint32_t FragmentLength;
    void *FragmentBuffer;
};

typedef enum {
    EfiTlsEncrypt,
    EfiTlsDecrypt
} EFI_TLS_CRYPT_MODE;

typedef EFI_STATUS (EFI_API *EFI_TLS_PROCESS_PACKET)(
    struct efi_tls_protocol *This,
    struct efi_tls_fragment_data **FragmentTable,
    uint32_t *FragmentCount,
    EFI_TLS_CRYPT_MODE CryptMode
);

struct efi_tls_protocol {
    EFI_TLS_SET_SESSION_DATA SetSessionData;
    EFI_TLS_GET_SESSION_DATA GetSessionData;
    EFI_TLS_BUILD_RESPONSE_PACKET BuildResponsePacket;
    EFI_TLS_PROCESS_PACKET ProcessPacket;
};

#define EFI_TLS_CONFIGURATION_PROTOCOL_GUID \
    {0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d}}

struct efi_tls_configuration_protocol;

typedef enum {
    EfiTlsConfigDataTypeHostPublicCert,
    EfiTlsConfigDataTypeHostPrivateKey,
    EfiTlsConfigDataTypeCACertificate,
    EfiTlsConfigDataTypeCertRevocationList,
    EfiTlsConfigDataTypeMaximum
} EFI_TLS_CONFIG_DATA_TYPE;

typedef EFI_STATUS (EFI_API *EFI_TLS_CONFIGURATION_SET_DATA)(
    struct efi_tls_configuration_protocol *This,
    EFI_TLS_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t DataSize
);

typedef EFI_STATUS (EFI_API *EFI_TLS_CONFIGURATION_GET_DATA)(
    struct efi_tls_configuration_protocol *This,
    EFI_TLS_CONFIG_DATA_TYPE DataType,
    void *Data,
    size_t *DataSize
);

struct efi_tls_configuration_protocol {
    EFI_TLS_CONFIGURATION_SET_DATA SetData;
    EFI_TLS_CONFIGURATION_GET_DATA GetData;
};

#ifdef __cplusplus
}
#endif

#endif
