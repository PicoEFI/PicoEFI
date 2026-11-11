#ifndef EFI_EFIARPDHCP_H_
#define EFI_EFIARPDHCP_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ARP_SERVICE_BINDING_PROTOCOL_GUID \
    {0xf44c00ee, 0x1f2c, 0x4a00, {0xaa, 0x09, 0x1c, 0x9f, 0x3e, 0x08, 0x00, 0xa3}}

#define EFI_ARP_PROTOCOL_GUID \
    {0xf4b427bb, 0xba21, 0x4f16, {0xbc, 0x4e, 0x43, 0xe4, 0x16, 0xab, 0x61, 0x9c}}

typedef struct _EFI_ARP_PROTOCOL EFI_ARP_PROTOCOL;

typedef struct {
    uint16_t SwAddressType;
    uint8_t SwAddressLength;
    void *StationAddress;
    uint32_t EntryTimeOut;
    uint32_t RetryCount;
    uint32_t RetryTimeOut;
} EFI_ARP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_ARP_CONFIGURE)(
    EFI_ARP_PROTOCOL *This,
    EFI_ARP_CONFIG_DATA *ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_ARP_ADD)(
    EFI_ARP_PROTOCOL *This,
    bool DenyFlag,
    void *TargetSwAddress,
    void *TargetHwAddress,
    uint32_t TimeoutValue,
    bool Overwrite
);

typedef struct {
    uint32_t Size;
    uint8_t DenyFlag;
    uint8_t StaticFlag;
    uint16_t HwAddressType;
    uint16_t SwAddressType;
    uint8_t HwAddressLength;
    uint8_t SwAddressLength;
} EFI_ARP_FIND_DATA;

typedef EFI_STATUS (EFI_API *EFI_ARP_FIND)(
    EFI_ARP_PROTOCOL *This,
    bool BySwAddress,
    void *AddressBuffer,
    uint32_t *EntryLength,
    uint32_t *EntryCount,
    EFI_ARP_FIND_DATA **Entries,
    bool Refresh
);

typedef EFI_STATUS (EFI_API *EFI_ARP_DELETE)(
    EFI_ARP_PROTOCOL *This,
    bool BySwAddress,
    void *AddressBuffer
);

typedef EFI_STATUS (EFI_API *EFI_ARP_FLUSH)(EFI_ARP_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_ARP_REQUEST)(
    EFI_ARP_PROTOCOL *This,
    void *TargetSwAddress,
    EFI_EVENT ResolvedEvent,
    void *TargetHwAddress
);

typedef EFI_STATUS (EFI_API *EFI_ARP_CANCEL)(
    EFI_ARP_PROTOCOL *This,
    void *TargetSwAddress,
    EFI_EVENT ResolvedEvent
);

struct _EFI_ARP_PROTOCOL {
    EFI_ARP_CONFIGURE Configure;
    EFI_ARP_ADD Add;
    EFI_ARP_FIND Find;
    EFI_ARP_DELETE Delete;
    EFI_ARP_FLUSH Flush;
    EFI_ARP_REQUEST Request;
    EFI_ARP_CANCEL Cancel;
};

#define EFI_DHCP4_SERVICE_BINDING_PROTOCOL_GUID \
    {0x9d9a39d8, 0xbd42, 0x4a73, {0xa4, 0xd5, 0x8e, 0xe9, 0x4b, 0xe1, 0x13, 0x80}}

#define EFI_DHCP4_PROTOCOL_GUID \
    {0x8a219718, 0x4ef5, 0x4761, {0x91, 0xc8, 0xc0, 0xf0, 0x4b, 0xda, 0x9e, 0x56}}

typedef struct _EFI_DHCP4_PROTOCOL EFI_DHCP4_PROTOCOL;

typedef enum {
    EfiDhcp4Stopped = 0x0,
    EfiDhcp4Init = 0x1,
    EfiDhcp4Selecting = 0x2,
    EfiDhcp4Requesting = 0x3,
    EfiDhcp4Bound = 0x4,
    EfiDhcp4Renewing = 0x5,
    EfiDhcp4Rebinding = 0x6,
    EfiDhcp4InitReboot = 0x7,
    EfiDhcp4Rebooting = 0x8
} EFI_DHCP4_STATE;

typedef enum {
    EfiDhcp4SendDiscover = 0x01,
    EfiDhcp4RcvdOffer = 0x02,
    EfiDhcp4SelectOffer = 0x03,
    EfiDhcp4SendRequest = 0x04,
    EfiDhcp4RcvdAck = 0x05,
    EfiDhcp4RcvdNak = 0x06,
    EfiDhcp4SendDecline = 0x07,
    EfiDhcp4BoundCompleted = 0x08,
    EfiDhcp4EnterRenewing = 0x09,
    EfiDhcp4EnterRebinding = 0x0a,
    EfiDhcp4AddressLost = 0x0b,
    EfiDhcp4Fail = 0x0c
} EFI_DHCP4_EVENT;

typedef struct __attribute__((__packed__)) {
    uint8_t OpCode;
    uint8_t HwType;
    uint8_t HwAddrLen;
    uint8_t Hops;
    uint32_t Xid;
    uint16_t Seconds;
    uint16_t Reserved;
    EFI_IPv4_ADDRESS ClientAddr;
    EFI_IPv4_ADDRESS YourAddr;
    EFI_IPv4_ADDRESS ServerAddr;
    EFI_IPv4_ADDRESS GatewayAddr;
    uint8_t ClientHwAddr[16];
    char ServerName[64];
    char BootFileName[128];
} EFI_DHCP4_HEADER;

typedef struct __attribute__((__packed__)) {
    uint32_t Size;
    uint32_t Length;
    struct __attribute__((__packed__)) {
        EFI_DHCP4_HEADER Header;
        uint32_t Magik;
        uint8_t Option[1];
    } Dhcp4;
} EFI_DHCP4_PACKET;

typedef struct __attribute__((__packed__)) {
    uint8_t OpCode;
    uint8_t Length;
    uint8_t Data[1];
} EFI_DHCP4_PACKET_OPTION;

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CALLBACK)(
    EFI_DHCP4_PROTOCOL *This,
    void *Context,
    EFI_DHCP4_STATE CurrentState,
    EFI_DHCP4_EVENT Dhcp4Event,
    EFI_DHCP4_PACKET *Packet,
    EFI_DHCP4_PACKET **NewPacket
);

typedef struct {
    uint32_t DiscoverTryCount;
    uint32_t *DiscoverTimeout;
    uint32_t RequestTryCount;
    uint32_t *RequestTimeout;
    EFI_IPv4_ADDRESS ClientAddress;
    EFI_DHCP4_CALLBACK Dhcp4Callback;
    void *CallbackContext;
    uint32_t OptionCount;
    EFI_DHCP4_PACKET_OPTION **OptionList;
} EFI_DHCP4_CONFIG_DATA;

typedef struct {
    EFI_DHCP4_STATE State;
    EFI_DHCP4_CONFIG_DATA ConfigData;
    EFI_IPv4_ADDRESS ClientAddress;
    EFI_MAC_ADDRESS ClientMacAddress;
    EFI_IPv4_ADDRESS ServerAddress;
    EFI_IPv4_ADDRESS RouterAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    uint32_t LeaseTime;
    EFI_DHCP4_PACKET *ReplyPacket;
} EFI_DHCP4_MODE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS ListenAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    uint16_t ListenPort;
} EFI_DHCP4_LISTEN_POINT;

typedef struct {
    EFI_STATUS Status;
    EFI_EVENT CompletionEvent;
    EFI_IPv4_ADDRESS RemoteAddress;
    uint16_t RemotePort;
    EFI_IPv4_ADDRESS GatewayAddress;
    uint32_t ListenPointCount;
    EFI_DHCP4_LISTEN_POINT *ListenPoints;
    uint32_t TimeoutValue;
    EFI_DHCP4_PACKET *Packet;
    uint32_t ResponseCount;
    EFI_DHCP4_PACKET *ResponseList;
} EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DHCP4_GET_MODE_DATA)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_DHCP4_MODE_DATA *Dhcp4ModeData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CONFIGURE)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_DHCP4_CONFIG_DATA *Dhcp4CfgData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_START)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_EVENT CompletionEvent
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RENEW_REBIND)(
    EFI_DHCP4_PROTOCOL *This,
    bool RebindRequest,
    EFI_EVENT CompletionEvent
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RELEASE)(EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_STOP)(EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_BUILD)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_DHCP4_PACKET *SeedPacket,
    uint32_t DeleteCount,
    uint8_t *DeleteList,
    uint32_t AppendCount,
    EFI_DHCP4_PACKET_OPTION *AppendList[],
    EFI_DHCP4_PACKET **NewPacket
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_TRANSMIT_RECEIVE)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_PARSE)(
    EFI_DHCP4_PROTOCOL *This,
    EFI_DHCP4_PACKET *Packet,
    uint32_t *OptionCount,
    EFI_DHCP4_PACKET_OPTION *PacketOptionList[]
);

struct _EFI_DHCP4_PROTOCOL {
    EFI_DHCP4_GET_MODE_DATA GetModeData;
    EFI_DHCP4_CONFIGURE Configure;
    EFI_DHCP4_START Start;
    EFI_DHCP4_RENEW_REBIND RenewRebind;
    EFI_DHCP4_RELEASE Release;
    EFI_DHCP4_STOP Stop;
    EFI_DHCP4_BUILD Build;
    EFI_DHCP4_TRANSMIT_RECEIVE TransmitReceive;
    EFI_DHCP4_PARSE Parse;
};

#define EFI_DHCP6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x9fb9a8a1, 0x2f4a, 0x43a6, {0x88, 0x9c, 0xd0, 0xf7, 0xb6, 0xc4, 0x7a, 0xd5}}

#define EFI_DHCP6_PROTOCOL_GUID \
    {0x87c8bad7, 0x595, 0x4053, {0x82, 0x97, 0xde, 0xde, 0x39, 0x5f, 0x5d, 0x5b}}

typedef struct _EFI_DHCP6_PROTOCOL EFI_DHCP6_PROTOCOL;

typedef struct {
    uint16_t Length;
    uint8_t Duid[1];
} EFI_DHCP6_DUID;

typedef struct {
    uint16_t Type;
    uint32_t IaId;
} EFI_DHCP6_IA_DESCRIPTOR;

#define EFI_DHCP6_IA_TYPE_NA 3
#define EFI_DHCP6_IA_TYPE_TA 4

typedef enum {
    EfiDhcp6Init = 0x0,
    EfiDhcp6Selecting = 0x1,
    EfiDhcp6Requesting = 0x2,
    EfiDhcp6Declining = 0x3,
    EfiDhcp6Confirming = 0x4,
    EfiDhcp6Releasing = 0x5,
    EfiDhcp6Bound = 0x6,
    EfiDhcp6Renewing = 0x7,
    EfiDhcp6Rebinding = 0x8
} EFI_DHCP6_STATE;

typedef struct {
    EFI_IPv6_ADDRESS IpAddress;
    uint32_t PreferredLifetime;
    uint32_t ValidLifetime;
} EFI_DHCP6_IA_ADDRESS;

typedef struct __attribute__((__packed__)) {
    uint32_t TransactionId:24;
    uint32_t MessageType:8;
} EFI_DHCP6_HEADER;

typedef struct __attribute__((__packed__)) {
    uint32_t Size;
    uint32_t Length;
    struct __attribute__((__packed__)) {
        EFI_DHCP6_HEADER Header;
        uint8_t Option[1];
    } Dhcp6;
} EFI_DHCP6_PACKET;

typedef struct {
    EFI_DHCP6_IA_DESCRIPTOR Descriptor;
    EFI_DHCP6_STATE State;
    EFI_DHCP6_PACKET *ReplyPacket;
    uint32_t IaAddressCount;
    EFI_DHCP6_IA_ADDRESS IaAddress[1];
} EFI_DHCP6_IA;

typedef struct {
    EFI_DHCP6_DUID *ClientId;
    EFI_DHCP6_IA *Ia;
} EFI_DHCP6_MODE_DATA;

typedef struct __attribute__((__packed__)) {
    uint16_t OpCode;
    uint16_t OpLen;
    uint8_t Data[1];
} EFI_DHCP6_PACKET_OPTION;

typedef enum {
    EfiDhcp6SendSolicit = 0x0,
    EfiDhcp6RcvdAdvertise = 0x1,
    EfiDhcp6SelectAdvertise = 0x2,
    EfiDhcp6SendRequest = 0x3,
    EfiDhcp6RcvdReply = 0x4,
    EfiDhcp6RcvdReconfigure = 0x5,
    EfiDhcp6SendDecline = 0x6,
    EfiDhcp6SendConfirm = 0x7,
    EfiDhcp6SendRelease = 0x8,
    EfiDhcp6SendRenew = 0x9,
    EfiDhcp6SendRebind = 0xa
} EFI_DHCP6_EVENT;

typedef EFI_STATUS (EFI_API *EFI_DHCP6_CALLBACK)(
    EFI_DHCP6_PROTOCOL *This,
    void *Context,
    EFI_DHCP6_STATE CurrentState,
    EFI_DHCP6_EVENT Dhcp6Event,
    EFI_DHCP6_PACKET *Packet,
    EFI_DHCP6_PACKET **NewPacket
);

typedef struct {
    uint32_t Irt;
    uint32_t Mrc;
    uint32_t Mrt;
    uint32_t Mrd;
} EFI_DHCP6_RETRANSMISSION;

typedef struct {
    EFI_DHCP6_CALLBACK Dhcp6Callback;
    void *CallbackContext;
    uint32_t OptionCount;
    EFI_DHCP6_PACKET_OPTION **OptionList;
    EFI_DHCP6_IA_DESCRIPTOR IaDescriptor;
    EFI_EVENT IaInfoEvent;
    uint8_t ReconfigureAccept;
    uint8_t RapidCommit;
    EFI_DHCP6_RETRANSMISSION *SolicitRetransmission;
} EFI_DHCP6_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_DHCP6_GET_MODE_DATA)(
    EFI_DHCP6_PROTOCOL *This,
    EFI_DHCP6_MODE_DATA *Dhcp6ModeData,
    EFI_DHCP6_CONFIG_DATA *Dhcp6ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_CONFIGURE)(
    EFI_DHCP6_PROTOCOL *This,
    EFI_DHCP6_CONFIG_DATA *Dhcp6CfgData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_START)(EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_CALLBACK)(
    EFI_DHCP6_PROTOCOL *This,
    void *Context,
    EFI_DHCP6_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_REQUEST)(
    EFI_DHCP6_PROTOCOL *This,
    bool SendClientId,
    EFI_DHCP6_PACKET_OPTION *OptionRequest,
    uint32_t OptionCount,
    EFI_DHCP6_PACKET_OPTION *OptionList[],
    EFI_DHCP6_RETRANSMISSION *Retransmission,
    EFI_EVENT TimeoutEvent,
    EFI_DHCP6_INFO_CALLBACK ReplyCallback,
    void *CallbackContext
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RENEW_REBIND)(
    EFI_DHCP6_PROTOCOL *This,
    bool RebindRequest
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_DECLINE)(
    EFI_DHCP6_PROTOCOL *This,
    uint32_t AddressCount,
    EFI_IPv6_ADDRESS *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RELEASE)(
    EFI_DHCP6_PROTOCOL *This,
    uint32_t AddressCount,
    EFI_IPv6_ADDRESS *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_STOP)(EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_PARSE)(
    EFI_DHCP6_PROTOCOL *This,
    EFI_DHCP6_PACKET *Packet,
    uint32_t *OptionCount,
    EFI_DHCP6_PACKET_OPTION *PacketOptionList[]
);

struct _EFI_DHCP6_PROTOCOL {
    EFI_DHCP6_GET_MODE_DATA GetModeData;
    EFI_DHCP6_CONFIGURE Configure;
    EFI_DHCP6_START Start;
    EFI_DHCP6_INFO_REQUEST InfoRequest;
    EFI_DHCP6_RENEW_REBIND RenewRebind;
    EFI_DHCP6_DECLINE Decline;
    EFI_DHCP6_RELEASE Release;
    EFI_DHCP6_STOP Stop;
    EFI_DHCP6_PARSE Parse;
};

#define EFI_DNS4_SERVICE_BINDING_PROTOCOL_GUID \
    {0xb625b186, 0xe063, 0x44f7, {0x89, 0x5, 0x6a, 0x74, 0xdc, 0x6f, 0x52, 0xb4}}

#define EFI_DNS4_PROTOCOL_GUID \
    {0xae3d28cc, 0xe05b, 0x4fa1, {0xa0, 0x11, 0x7e, 0xb5, 0x5a, 0x3f, 0x14, 0x1}}

typedef struct _EFI_DNS4_PROTOCOL EFI_DNS4_PROTOCOL;

typedef struct {
    size_t DnsServerListCount;
    EFI_IPv4_ADDRESS *DnsServerList;
    uint8_t UseDefaultSetting;
    uint8_t EnableDnsCache;
    uint8_t Protocol;
    EFI_IPv4_ADDRESS StationIp;
    EFI_IPv4_ADDRESS SubnetMask;
    uint16_t LocalPort;
    uint32_t RetryCount;
    uint32_t RetryInterval;
} EFI_DNS4_CONFIG_DATA;

typedef struct {
    uint16_t *HostName;
    EFI_IPv4_ADDRESS *IpAddress;
    uint32_t Timeout;
} EFI_DNS4_CACHE_ENTRY;

typedef struct {
    EFI_DNS4_CONFIG_DATA DnsConfigData;
    uint32_t DnsServerCount;
    EFI_IPv4_ADDRESS *DnsServerList;
    uint32_t DnsCacheCount;
    EFI_DNS4_CACHE_ENTRY *DnsCacheList;
} EFI_DNS4_MODE_DATA;

typedef struct {
    uint32_t IpCount;
    EFI_IPv4_ADDRESS *IpList;
} EFI_DNS_HOST_TO_ADDR_DATA;

typedef struct {
    uint16_t *HostName;
} EFI_DNS_ADDR_TO_HOST_DATA;

typedef struct {
    char *QName;
    uint16_t QType;
    uint16_t QClass;
    uint32_t TTL;
    uint16_t DataLength;
    char *RData;
} EFI_DNS_RESOURCE_RECORD;

typedef struct {
    size_t RRCount;
    EFI_DNS_RESOURCE_RECORD *RRList;
} EFI_DNS_GENERAL_LOOKUP_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    uint32_t RetryCount;
    uint32_t RetryInterval;
    union {
        EFI_DNS_HOST_TO_ADDR_DATA *H2AData;
        EFI_DNS_ADDR_TO_HOST_DATA *A2HData;
        EFI_DNS_GENERAL_LOOKUP_DATA *GLookupData;
    } RspData;
} EFI_DNS4_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DNS4_GET_MODE_DATA)(
    EFI_DNS4_PROTOCOL *This,
    EFI_DNS4_MODE_DATA *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CONFIGURE)(
    EFI_DNS4_PROTOCOL *This,
    EFI_DNS4_CONFIG_DATA *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_HOST_NAME_TO_IP)(
    EFI_DNS4_PROTOCOL *This,
    uint16_t *HostName,
    EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_IP_TO_HOST_NAME)(
    EFI_DNS4_PROTOCOL *This,
    EFI_IPv4_ADDRESS IpAddress,
    EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_GENERAL_LOOKUP)(
    EFI_DNS4_PROTOCOL *This,
    char *QName,
    uint16_t QType,
    uint16_t QClass,
    EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_UPDATE_DNS_CACHE)(
    EFI_DNS4_PROTOCOL *This,
    bool DeleteFlag,
    bool Override,
    EFI_DNS4_CACHE_ENTRY DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_POLL)(EFI_DNS4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CANCEL)(
    EFI_DNS4_PROTOCOL *This,
    EFI_DNS4_COMPLETION_TOKEN *Token
);

struct _EFI_DNS4_PROTOCOL {
    EFI_DNS4_GET_MODE_DATA GetModeData;
    EFI_DNS4_CONFIGURE Configure;
    EFI_DNS4_HOST_NAME_TO_IP HostNameToIp;
    EFI_DNS4_IP_TO_HOST_NAME IpToHostName;
    EFI_DNS4_GENERAL_LOOKUP GeneralLookUp;
    EFI_DNS4_UPDATE_DNS_CACHE UpdateDnsCache;
    EFI_DNS4_POLL Poll;
    EFI_DNS4_CANCEL Cancel;
};

#define EFI_DNS6_SERVICE_BINDING_PROTOCOL_GUID \
    {0x7f1647c8, 0xb76e, 0x44b2, {0xa5, 0x65, 0xf7, 0xf, 0xf1, 0x9c, 0xd1, 0x9e}}

#define EFI_DNS6_PROTOCOL_GUID \
    {0xca37bc1f, 0xa327, 0x4ae9, {0x82, 0x8a, 0x8c, 0x40, 0xd8, 0x50, 0x6a, 0x17}}

typedef struct _EFI_DNS6_PROTOCOL EFI_DNS6_PROTOCOL;

typedef struct {
    uint8_t EnableDnsCache;
    uint8_t Protocol;
    EFI_IPv6_ADDRESS StationIp;
    uint16_t LocalPort;
    uint32_t DnsServerCount;
    EFI_IPv6_ADDRESS *DnsServerList;
    uint32_t RetryCount;
    uint32_t RetryInterval;
} EFI_DNS6_CONFIG_DATA;

typedef struct {
    uint16_t *HostName;
    EFI_IPv6_ADDRESS *IpAddress;
    uint32_t Timeout;
} EFI_DNS6_CACHE_ENTRY;

typedef struct {
    EFI_DNS6_CONFIG_DATA DnsConfigData;
    uint32_t DnsServerCount;
    EFI_IPv6_ADDRESS *DnsServerList;
    uint32_t DnsCacheCount;
    EFI_DNS6_CACHE_ENTRY *DnsCacheList;
} EFI_DNS6_MODE_DATA;

typedef struct {
    uint32_t IpCount;
    EFI_IPv6_ADDRESS *IpList;
} EFI_DNS6_HOST_TO_ADDR_DATA;

typedef struct {
    uint16_t *HostName;
} EFI_DNS6_ADDR_TO_HOST_DATA;

typedef struct {
    char *QName;
    uint16_t QType;
    uint16_t QClass;
    uint32_t TTL;
    uint16_t DataLength;
    char *RData;
} EFI_DNS6_RESOURCE_RECORD;

typedef struct {
    size_t RRCount;
    EFI_DNS6_RESOURCE_RECORD *RRList;
} EFI_DNS6_GENERAL_LOOKUP_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    uint32_t RetryCount;
    uint32_t RetryInterval;
    union {
        EFI_DNS6_HOST_TO_ADDR_DATA *H2AData;
        EFI_DNS6_ADDR_TO_HOST_DATA *A2HData;
        EFI_DNS6_GENERAL_LOOKUP_DATA *GLookupData;
    } RspData;
} EFI_DNS6_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DNS6_GET_MODE_DATA)(
    EFI_DNS6_PROTOCOL *This,
    EFI_DNS6_MODE_DATA *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CONFIGURE)(
    EFI_DNS6_PROTOCOL *This,
    EFI_DNS6_CONFIG_DATA *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_HOST_NAME_TO_IP)(
    EFI_DNS6_PROTOCOL *This,
    uint16_t *HostName,
    EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_IP_TO_HOST_NAME)(
    EFI_DNS6_PROTOCOL *This,
    EFI_IPv6_ADDRESS IpAddress,
    EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_GENERAL_LOOKUP)(
    EFI_DNS6_PROTOCOL *This,
    char *QName,
    uint16_t QType,
    uint16_t QClass,
    EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_UPDATE_DNS_CACHE)(
    EFI_DNS6_PROTOCOL *This,
    bool DeleteFlag,
    bool Override,
    EFI_DNS6_CACHE_ENTRY DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_POLL)(EFI_DNS6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CANCEL)(
    EFI_DNS6_PROTOCOL *This,
    EFI_DNS6_COMPLETION_TOKEN *Token
);

struct _EFI_DNS6_PROTOCOL {
    EFI_DNS6_GET_MODE_DATA GetModeData;
    EFI_DNS6_CONFIGURE Configure;
    EFI_DNS6_HOST_NAME_TO_IP HostNameToIp;
    EFI_DNS6_IP_TO_HOST_NAME IpToHostName;
    EFI_DNS6_GENERAL_LOOKUP GeneralLookUp;
    EFI_DNS6_UPDATE_DNS_CACHE UpdateDnsCache;
    EFI_DNS6_POLL Poll;
    EFI_DNS6_CANCEL Cancel;
};

#define EFI_HTTP_SERVICE_BINDING_PROTOCOL_GUID \
    {0xbdc8e6af, 0xd9bc, 0x4379, {0xa7, 0x2a, 0xe0, 0xc4, 0xe7, 0x5d, 0xae, 0x1c}}

#define EFI_HTTP_PROTOCOL_GUID \
    {0x7A59B29B, 0x910B, 0x4171, {0x82, 0x42, 0xA8, 0x5A, 0x0D, 0xF2, 0x5B, 0x5B}}

typedef struct _EFI_HTTP_PROTOCOL EFI_HTTP_PROTOCOL;

typedef enum {
    EfiHttpVersion10,
    EfiHttpVersion11,
    EfiHttpVersionUnsupported
} EFI_HTTP_VERSION;

typedef struct {
    uint8_t UseDefaultAddress;
    EFI_IPv4_ADDRESS LocalAddress;
    EFI_IPv4_ADDRESS LocalSubnet;
    uint16_t LocalPort;
} EFI_HTTPv4_ACCESS_POINT;

typedef struct {
    EFI_IPv6_ADDRESS LocalAddress;
    uint16_t LocalPort;
} EFI_HTTPv6_ACCESS_POINT;

typedef struct {
    EFI_HTTP_VERSION HttpVersion;
    uint32_t TimeOutMillisec;
    uint8_t LocalAddressIsIPv6;
    union {
        EFI_HTTPv4_ACCESS_POINT *IPv4Node;
        EFI_HTTPv6_ACCESS_POINT *IPv6Node;
    } AccessPoint;
} EFI_HTTP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_HTTP_GET_MODE_DATA)(
    EFI_HTTP_PROTOCOL *This,
    EFI_HTTP_CONFIG_DATA *HttpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CONFIGURE)(
    EFI_HTTP_PROTOCOL *This,
    EFI_HTTP_CONFIG_DATA *HttpConfigData
);

typedef enum {
    EfiHttpMethodGet,
    EfiHttpMethodPost,
    EfiHttpMethodPatch,
    EfiHttpMethodOptions,
    EfiHttpMethodConnect,
    EfiHttpMethodHead,
    EfiHttpMethodPut,
    EfiHttpMethodDelete,
    EfiHttpMethodTrace,
    EfiHttpMethodMax
} EFI_HTTP_METHOD;

typedef struct {
    EFI_HTTP_METHOD Method;
    uint16_t *Url;
} EFI_HTTP_REQUEST_DATA;

typedef struct {
    EFI_HTTP_REQUEST_DATA Base;
    uint16_t *ProxyUrl;
} EFI_HTTP_CONNECT_REQUEST_DATA;

typedef enum {
    EFI_HTTP_STATUS_UNSUPPORTED_STATUS = 0,
    EFI_HTTP_STATUS_100_CONTINUE,
    EFI_HTTP_STATUS_101_SWITCHING_PROTOCOLS,
    EFI_HTTP_STATUS_200_OK,
    EFI_HTTP_STATUS_201_CREATED,
    EFI_HTTP_STATUS_202_ACCEPTED,
    EFI_HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION,
    EFI_HTTP_STATUS_204_NO_CONTENT,
    EFI_HTTP_STATUS_205_RESET_CONTENT,
    EFI_HTTP_STATUS_206_PARTIAL_CONTENT,
    EFI_HTTP_STATUS_300_MULTIPLE_CHOICES,
    EFI_HTTP_STATUS_301_MOVED_PERMANENTLY,
    EFI_HTTP_STATUS_302_FOUND,
    EFI_HTTP_STATUS_303_SEE_OTHER,
    EFI_HTTP_STATUS_304_NOT_MODIFIED,
    EFI_HTTP_STATUS_305_USE_PROXY,
    EFI_HTTP_STATUS_307_TEMPORARY_REDIRECT,
    EFI_HTTP_STATUS_400_BAD_REQUEST,
    EFI_HTTP_STATUS_401_UNAUTHORIZED,
    EFI_HTTP_STATUS_402_PAYMENT_REQUIRED,
    EFI_HTTP_STATUS_403_FORBIDDEN,
    EFI_HTTP_STATUS_404_NOT_FOUND,
    EFI_HTTP_STATUS_405_METHOD_NOT_ALLOWED,
    EFI_HTTP_STATUS_406_NOT_ACCEPTABLE,
    EFI_HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED,
    EFI_HTTP_STATUS_408_REQUEST_TIME_OUT,
    EFI_HTTP_STATUS_409_CONFLICT,
    EFI_HTTP_STATUS_410_GONE,
    EFI_HTTP_STATUS_411_LENGTH_REQUIRED,
    EFI_HTTP_STATUS_412_PRECONDITION_FAILED,
    EFI_HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE,
    EFI_HTTP_STATUS_414_REQUEST_URI_TOO_LARGE,
    EFI_HTTP_STATUS_415_UNSUPPORTED_MEDIA_TYPE,
    EFI_HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED,
    EFI_HTTP_STATUS_417_EXPECTATION_FAILED,
    EFI_HTTP_STATUS_500_INTERNAL_SERVER_ERROR,
    EFI_HTTP_STATUS_501_NOT_IMPLEMENTED,
    EFI_HTTP_STATUS_502_BAD_GATEWAY,
    EFI_HTTP_STATUS_503_SERVICE_UNAVAILABLE,
    EFI_HTTP_STATUS_504_GATEWAY_TIME_OUT,
    EFI_HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED,
    EFI_HTTP_STATUS_308_PERMANENT_REDIRECT
} EFI_HTTP_STATUS_CODE;

typedef struct {
    EFI_HTTP_STATUS_CODE StatusCode;
} EFI_HTTP_RESPONSE_DATA;

typedef struct {
    char *FieldName;
    char *FieldValue;
} EFI_HTTP_HEADER;

typedef struct {
    union {
        EFI_HTTP_REQUEST_DATA *Request;
        EFI_HTTP_RESPONSE_DATA *Response;
    } Data;
    size_t HeaderCount;
    EFI_HTTP_HEADER *Headers;
    size_t BodyLength;
    void *Body;
} EFI_HTTP_MESSAGE;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_HTTP_MESSAGE *Message;
} EFI_HTTP_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_HTTP_REQUEST)(
    EFI_HTTP_PROTOCOL *This,
    EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CANCEL)(
    EFI_HTTP_PROTOCOL *This,
    EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_RESPONSE)(
    EFI_HTTP_PROTOCOL *This,
    EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_POLL)(EFI_HTTP_PROTOCOL *This);

struct _EFI_HTTP_PROTOCOL {
    EFI_HTTP_GET_MODE_DATA GetModeData;
    EFI_HTTP_CONFIGURE Configure;
    EFI_HTTP_REQUEST Request;
    EFI_HTTP_CANCEL Cancel;
    EFI_HTTP_RESPONSE Response;
    EFI_HTTP_POLL Poll;
};

#define EFI_HTTP_UTILITIES_PROTOCOL_GUID \
    {0x3E35C163, 0x4074, 0x45DD, {0x43, 0x1E, 0x23, 0x98, 0x9D, 0xD8, 0x6B, 0x32}}

typedef struct _EFI_HTTP_UTILITIES_PROTOCOL EFI_HTTP_UTILITIES_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_HTTP_UTILS_BUILD)(
    EFI_HTTP_UTILITIES_PROTOCOL *This,
    size_t SeedMessageSize,
    void *SeedMessage,
    size_t DeleteCount,
    char *DeleteList[],
    size_t AppendCount,
    EFI_HTTP_HEADER *AppendList[],
    size_t *NewMessageSize,
    void **NewMessage
);

/* This is the utilities protocol, as described; the prototype prints EFI_HTTP_PROTOCOL. */
typedef EFI_STATUS (EFI_API *EFI_HTTP_UTILS_PARSE)(
    EFI_HTTP_UTILITIES_PROTOCOL *This,
    char *HttpMessage,
    size_t HttpMessageSize,
    EFI_HTTP_HEADER **HeaderFields,
    size_t *FieldCount
);

struct _EFI_HTTP_UTILITIES_PROTOCOL {
    EFI_HTTP_UTILS_BUILD Build;
    EFI_HTTP_UTILS_PARSE Parse;
};

#define EFI_REST_PROTOCOL_GUID \
    {0x0DB48A36, 0x4E54, 0xEA9C, {0x9B, 0x09, 0x1E, 0xA5, 0xBE, 0x3A, 0x66, 0x0B}}

typedef struct _EFI_REST_PROTOCOL EFI_REST_PROTOCOL;

/* Shared by EFI_REST_EX_PROTOCOL, whose section reprints it with an EFI_REST_EX_PROTOCOL This. */
typedef EFI_STATUS (EFI_API *EFI_REST_SEND_RECEIVE)(
    EFI_REST_PROTOCOL *This,
    EFI_HTTP_MESSAGE *RequestMessage,
    EFI_HTTP_MESSAGE *ResponseMessage
);

typedef EFI_STATUS (EFI_API *EFI_REST_GET_TIME)(
    EFI_REST_PROTOCOL *This,
    EFI_TIME *Time
);

struct _EFI_REST_PROTOCOL {
    EFI_REST_SEND_RECEIVE SendReceive;
    EFI_REST_GET_TIME GetServiceTime;
};

#define EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID \
    {0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59}}

#define EFI_REST_EX_PROTOCOL_GUID \
    {0x55648b91, 0xe7d, 0x40a3, {0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97}}

typedef struct _EFI_REST_EX_PROTOCOL EFI_REST_EX_PROTOCOL;

typedef struct {
    uint8_t Major;
    uint8_t Minor;
} EFI_REST_EX_SERVICE_INFO_VER;

typedef struct {
    uint32_t Length;
    EFI_REST_EX_SERVICE_INFO_VER RestServiceInfoVer;
} EFI_REST_EX_SERVICE_INFO_HEADER;

typedef enum {
    EFI_REST_EX_SERVICE_UNSPECIFIC = 1,
    EFI_REST_EX_SERVICE_REDFISH,
    EFI_REST_EX_SERVICE_ODATA,
    EFI_REST_EX_SERVICE_VENDOR_SPECIFIC = 0xff,
    EFI_REST_EX_SERVICE_TYPE_MAX
} EFI_REST_EX_SERVICE_TYPE;

typedef enum {
    EFI_REST_EX_SERVICE_IN_BAND_ACCESS = 1,
    EFI_REST_EX_SERVICE_OUT_OF_BAND_ACCESS = 2,
    EFI_REST_EX_SERVICE_ACCESS_MODE_MAX
} EFI_REST_EX_SERVICE_ACCESS_MODE;

typedef enum {
    EFI_REST_EX_CONFIG_TYPE_HTTP,
    EFI_REST_EX_CONFIG_TYPE_UNSPECIFIC,
    EFI_REST_EX_CONFIG_TYPE_MAX
} EFI_REST_EX_CONFIG_TYPE;

typedef struct {
    EFI_REST_EX_SERVICE_INFO_HEADER EfiRestExServiceInfoHeader;
    EFI_REST_EX_SERVICE_TYPE RestExServiceType;
    EFI_REST_EX_SERVICE_ACCESS_MODE RestServiceAccessMode;
    EFI_GUID VendorRestServiceName;
    uint32_t VendorSpecificDataLength;
    uint8_t *VendorSpecifcData;
    EFI_REST_EX_CONFIG_TYPE RestExConfigType;
    uint8_t RestExConfigDataLength;
} EFI_REST_EX_SERVICE_INFO_V_1_0;

typedef union {
    EFI_REST_EX_SERVICE_INFO_HEADER EfiRestExServiceInfoHeader;
    EFI_REST_EX_SERVICE_INFO_V_1_0 EfiRestExServiceInfoV10;
} EFI_REST_EX_SERVICE_INFO;

typedef struct {
    EFI_HTTP_CONFIG_DATA HttpConfigData;
    uint32_t SendReceiveTimeout;
} EFI_REST_EX_HTTP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_SERVICE)(
    EFI_REST_EX_PROTOCOL *This,
    EFI_REST_EX_SERVICE_INFO **RestExServiceInfo
);

typedef uint8_t *EFI_REST_EX_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_MODE_DATA)(
    EFI_REST_EX_PROTOCOL *This,
    EFI_REST_EX_CONFIG_DATA *RestExConfigData
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_CONFIGURE)(
    EFI_REST_EX_PROTOCOL *This,
    EFI_REST_EX_CONFIG_DATA RestExConfigData
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_HTTP_MESSAGE *ResponseMessage;
} EFI_REST_EX_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_ASYNC_SEND_RECEIVE)(
    EFI_REST_EX_PROTOCOL *This,
    EFI_HTTP_MESSAGE *RequestMessage,
    EFI_REST_EX_TOKEN *RestExToken,
    uintptr_t *TimeOutInMilliSeconds
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_EVENT_SERVICE)(
    EFI_REST_EX_PROTOCOL *This,
    EFI_HTTP_MESSAGE *RequestMessage,
    EFI_REST_EX_TOKEN *RestExToken
);

struct _EFI_REST_EX_PROTOCOL {
    EFI_REST_SEND_RECEIVE SendReceive;
    EFI_REST_GET_TIME GetServiceTime;
    EFI_REST_EX_GET_SERVICE GetService;
    EFI_REST_EX_GET_MODE_DATA GetModeData;
    EFI_REST_EX_CONFIGURE Configure;
    EFI_REST_EX_ASYNC_SEND_RECEIVE AsyncSendReceive;
    EFI_REST_EX_EVENT_SERVICE EventService;
};

#define EFI_REST_JSON_STRUCTURE_PROTOCOL_GUID \
    {0xa9a048f6, 0x48a0, 0x4714, {0xb7, 0xda, 0xa9, 0xad, 0x87, 0xd4, 0xda, 0xc9}}

typedef struct _EFI_REST_JSON_STRUCTURE_PROTOCOL EFI_REST_JSON_STRUCTURE_PROTOCOL;

typedef char *EFI_REST_JSON_RESOURCE_TYPE_DATATYPE;

typedef struct _EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE {
    char *ResourceTypeName;
    char *MajorVersion;
    char *MinorVersion;
    char *ErrataVersion;
} EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE;

typedef struct _EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER {
    EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE Namespace;
    EFI_REST_JSON_RESOURCE_TYPE_DATATYPE Datatype;
} EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER;

typedef struct _EFI_REST_JSON_STRUCTURE_SUPPORTED EFI_REST_JSON_STRUCTURE_SUPPORTED;

struct _EFI_REST_JSON_STRUCTURE_SUPPORTED {
    EFI_REST_JSON_STRUCTURE_SUPPORTED *Next;
    EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER JsonResourceType;
};

typedef struct _EFI_REST_JSON_STRUCTURE_HEADER {
    EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER JsonRsrcIdentifier;
    void *JsonStructurePointer;
} EFI_REST_JSON_STRUCTURE_HEADER;

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_STRUCTURE)(
    EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER *JsonRsrcIdentifier,
    char *ResourceJsonText,
    EFI_REST_JSON_STRUCTURE_HEADER **JsonStructure
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_JSON)(
    EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_REST_JSON_STRUCTURE_HEADER *JsonStructureHeader,
    char **ResourceJsonText
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE)(
    EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_REST_JSON_STRUCTURE_HEADER *JsonStructureHeader
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_REGISTER)(
    EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_REST_JSON_STRUCTURE_SUPPORTED *JsonStructureSupported,
    EFI_REST_JSON_STRUCTURE_TO_STRUCTURE ToStructure,
    EFI_REST_JSON_STRUCTURE_TO_JSON ToJson,
    EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE DestroyStructure
);

struct _EFI_REST_JSON_STRUCTURE_PROTOCOL {
    EFI_REST_JSON_STRUCTURE_REGISTER Register;
    EFI_REST_JSON_STRUCTURE_TO_STRUCTURE ToStructure;
    EFI_REST_JSON_STRUCTURE_TO_JSON ToJson;
    EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE DestoryStructure;
};

#ifdef __cplusplus
}
#endif

#endif
