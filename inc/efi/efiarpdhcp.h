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
    EFI_UINT16 SwAddressType;
    EFI_UINT8 SwAddressLength;
    EFI_VOID *StationAddress;
    EFI_UINT32 EntryTimeOut;
    EFI_UINT32 RetryCount;
    EFI_UINT32 RetryTimeOut;
} EFI_ARP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_ARP_CONFIGURE)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_ARP_CONFIG_DATA *ConfigData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_ARP_ADD)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DenyFlag,
    EFI_IN EFI_VOID *TargetSwAddress EFI_OPTIONAL,
    EFI_IN EFI_VOID *TargetHwAddress EFI_OPTIONAL,
    EFI_IN EFI_UINT32 TimeoutValue,
    EFI_IN EFI_BOOLEAN Overwrite
);

typedef struct {
    EFI_UINT32 Size;
    EFI_BOOLEAN DenyFlag;
    EFI_BOOLEAN StaticFlag;
    EFI_UINT16 HwAddressType;
    EFI_UINT16 SwAddressType;
    EFI_UINT8 HwAddressLength;
    EFI_UINT8 SwAddressLength;
} EFI_ARP_FIND_DATA;

typedef EFI_STATUS (EFI_API *EFI_ARP_FIND)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN BySwAddress,
    EFI_IN EFI_VOID *AddressBuffer EFI_OPTIONAL,
    EFI_OUT EFI_UINT32 *EntryLength EFI_OPTIONAL,
    EFI_OUT EFI_UINT32 *EntryCount EFI_OPTIONAL,
    EFI_OUT EFI_ARP_FIND_DATA **Entries EFI_OPTIONAL,
    EFI_IN EFI_BOOLEAN Refresh
);

typedef EFI_STATUS (EFI_API *EFI_ARP_DELETE)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN BySwAddress,
    EFI_IN EFI_VOID *AddressBuffer EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_ARP_FLUSH)(EFI_IN EFI_ARP_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_ARP_REQUEST)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_VOID *TargetSwAddress EFI_OPTIONAL,
    EFI_IN EFI_EVENT ResolvedEvent EFI_OPTIONAL,
    EFI_OUT EFI_VOID *TargetHwAddress
);

typedef EFI_STATUS (EFI_API *EFI_ARP_CANCEL)(
    EFI_IN EFI_ARP_PROTOCOL *This,
    EFI_IN EFI_VOID *TargetSwAddress EFI_OPTIONAL,
    EFI_IN EFI_EVENT ResolvedEvent EFI_OPTIONAL
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
    EFI_UINT8 OpCode;
    EFI_UINT8 HwType;
    EFI_UINT8 HwAddrLen;
    EFI_UINT8 Hops;
    EFI_UINT32 Xid;
    EFI_UINT16 Seconds;
    EFI_UINT16 Reserved;
    EFI_IPv4_ADDRESS ClientAddr;
    EFI_IPv4_ADDRESS YourAddr;
    EFI_IPv4_ADDRESS ServerAddr;
    EFI_IPv4_ADDRESS GatewayAddr;
    EFI_UINT8 ClientHwAddr[16];
    EFI_CHAR8 ServerName[64];
    EFI_CHAR8 BootFileName[128];
} EFI_DHCP4_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT32 Size;
    EFI_UINT32 Length;
    struct __attribute__((__packed__)) {
        EFI_DHCP4_HEADER Header;
        EFI_UINT32 Magik;
        EFI_UINT8 Option[1];
    } Dhcp4;
} EFI_DHCP4_PACKET;

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 OpCode;
    EFI_UINT8 Length;
    EFI_UINT8 Data[1];
} EFI_DHCP4_PACKET_OPTION;

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CALLBACK)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_VOID *Context,
    EFI_IN EFI_DHCP4_STATE CurrentState,
    EFI_IN EFI_DHCP4_EVENT Dhcp4Event,
    EFI_IN EFI_DHCP4_PACKET *Packet EFI_OPTIONAL,
    EFI_OUT EFI_DHCP4_PACKET **NewPacket EFI_OPTIONAL
);

typedef struct {
    EFI_UINT32 DiscoverTryCount;
    EFI_UINT32 *DiscoverTimeout;
    EFI_UINT32 RequestTryCount;
    EFI_UINT32 *RequestTimeout;
    EFI_IPv4_ADDRESS ClientAddress;
    EFI_DHCP4_CALLBACK Dhcp4Callback;
    EFI_VOID *CallbackContext;
    EFI_UINT32 OptionCount;
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
    EFI_UINT32 LeaseTime;
    EFI_DHCP4_PACKET *ReplyPacket;
} EFI_DHCP4_MODE_DATA;

typedef struct {
    EFI_IPv4_ADDRESS ListenAddress;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_UINT16 ListenPort;
} EFI_DHCP4_LISTEN_POINT;

typedef struct {
    EFI_STATUS Status;
    EFI_EVENT CompletionEvent;
    EFI_IPv4_ADDRESS RemoteAddress;
    EFI_UINT16 RemotePort;
    EFI_IPv4_ADDRESS GatewayAddress;
    EFI_UINT32 ListenPointCount;
    EFI_DHCP4_LISTEN_POINT *ListenPoints;
    EFI_UINT32 TimeoutValue;
    EFI_DHCP4_PACKET *Packet;
    EFI_UINT32 ResponseCount;
    EFI_DHCP4_PACKET *ResponseList;
} EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DHCP4_GET_MODE_DATA)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_OUT EFI_DHCP4_MODE_DATA *Dhcp4ModeData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CONFIGURE)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_DHCP4_CONFIG_DATA *Dhcp4CfgData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_START)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_EVENT CompletionEvent EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RENEW_REBIND)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN RebindRequest,
    EFI_IN EFI_EVENT CompletionEvent EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RELEASE)(EFI_IN EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_STOP)(EFI_IN EFI_DHCP4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_BUILD)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_DHCP4_PACKET *SeedPacket,
    EFI_IN EFI_UINT32 DeleteCount,
    EFI_IN EFI_UINT8 *DeleteList EFI_OPTIONAL,
    EFI_IN EFI_UINT32 AppendCount,
    EFI_IN EFI_DHCP4_PACKET_OPTION *AppendList[] EFI_OPTIONAL,
    EFI_OUT EFI_DHCP4_PACKET **NewPacket
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_TRANSMIT_RECEIVE)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_PARSE)(
    EFI_IN EFI_DHCP4_PROTOCOL *This,
    EFI_IN EFI_DHCP4_PACKET *Packet,
    EFI_IN EFI_OUT EFI_UINT32 *OptionCount,
    EFI_IN EFI_OUT EFI_DHCP4_PACKET_OPTION *PacketOptionList[] EFI_OPTIONAL
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
    EFI_UINT16 Length;
    EFI_UINT8 Duid[1];
} EFI_DHCP6_DUID;

typedef struct {
    EFI_UINT16 Type;
    EFI_UINT32 IaId;
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
    EFI_UINT32 PreferredLifetime;
    EFI_UINT32 ValidLifetime;
} EFI_DHCP6_IA_ADDRESS;

typedef struct __attribute__((__packed__)) {
    EFI_UINT32 TransactionId:24;
    EFI_UINT32 MessageType:8;
} EFI_DHCP6_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_UINT32 Size;
    EFI_UINT32 Length;
    struct __attribute__((__packed__)) {
        EFI_DHCP6_HEADER Header;
        EFI_UINT8 Option[1];
    } Dhcp6;
} EFI_DHCP6_PACKET;

typedef struct {
    EFI_DHCP6_IA_DESCRIPTOR Descriptor;
    EFI_DHCP6_STATE State;
    EFI_DHCP6_PACKET *ReplyPacket;
    EFI_UINT32 IaAddressCount;
    EFI_DHCP6_IA_ADDRESS IaAddress[1];
} EFI_DHCP6_IA;

typedef struct {
    EFI_DHCP6_DUID *ClientId;
    EFI_DHCP6_IA *Ia;
} EFI_DHCP6_MODE_DATA;

typedef struct __attribute__((__packed__)) {
    EFI_UINT16 OpCode;
    EFI_UINT16 OpLen;
    EFI_UINT8 Data[1];
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
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_VOID *Context,
    EFI_IN EFI_DHCP6_STATE CurrentState,
    EFI_IN EFI_DHCP6_EVENT Dhcp6Event,
    EFI_IN EFI_DHCP6_PACKET *Packet,
    EFI_OUT EFI_DHCP6_PACKET **NewPacket EFI_OPTIONAL
);

typedef struct {
    EFI_UINT32 Irt;
    EFI_UINT32 Mrc;
    EFI_UINT32 Mrt;
    EFI_UINT32 Mrd;
} EFI_DHCP6_RETRANSMISSION;

typedef struct {
    EFI_DHCP6_CALLBACK Dhcp6Callback;
    EFI_VOID *CallbackContext;
    EFI_UINT32 OptionCount;
    EFI_DHCP6_PACKET_OPTION **OptionList;
    EFI_DHCP6_IA_DESCRIPTOR IaDescriptor;
    EFI_EVENT IaInfoEvent;
    EFI_BOOLEAN ReconfigureAccept;
    EFI_BOOLEAN RapidCommit;
    EFI_DHCP6_RETRANSMISSION *SolicitRetransmission;
} EFI_DHCP6_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_DHCP6_GET_MODE_DATA)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_OUT EFI_DHCP6_MODE_DATA *Dhcp6ModeData EFI_OPTIONAL,
    EFI_OUT EFI_DHCP6_CONFIG_DATA *Dhcp6ConfigData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_CONFIGURE)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_DHCP6_CONFIG_DATA *Dhcp6CfgData EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_START)(EFI_IN EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_CALLBACK)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_VOID *Context,
    EFI_IN EFI_DHCP6_PACKET *Packet
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_REQUEST)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN SendClientId,
    EFI_IN EFI_DHCP6_PACKET_OPTION *OptionRequest,
    EFI_IN EFI_UINT32 OptionCount,
    EFI_IN EFI_DHCP6_PACKET_OPTION *OptionList[] EFI_OPTIONAL,
    EFI_IN EFI_DHCP6_RETRANSMISSION *Retransmission,
    EFI_IN EFI_EVENT TimeoutEvent EFI_OPTIONAL,
    EFI_IN EFI_DHCP6_INFO_CALLBACK ReplyCallback,
    EFI_IN EFI_VOID *CallbackContext EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RENEW_REBIND)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN RebindRequest
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_DECLINE)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_UINT32 AddressCount,
    EFI_IN EFI_IPv6_ADDRESS *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RELEASE)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_UINT32 AddressCount,
    EFI_IN EFI_IPv6_ADDRESS *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_STOP)(EFI_IN EFI_DHCP6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_PARSE)(
    EFI_IN EFI_DHCP6_PROTOCOL *This,
    EFI_IN EFI_DHCP6_PACKET *Packet,
    EFI_IN EFI_OUT EFI_UINT32 *OptionCount,
    EFI_IN EFI_DHCP6_PACKET_OPTION *PacketOptionList[] EFI_OPTIONAL
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
    EFI_UINTN DnsServerListCount;
    EFI_IPv4_ADDRESS *DnsServerList;
    EFI_BOOLEAN UseDefaultSetting;
    EFI_BOOLEAN EnableDnsCache;
    EFI_UINT8 Protocol;
    EFI_IPv4_ADDRESS StationIp;
    EFI_IPv4_ADDRESS SubnetMask;
    EFI_UINT16 LocalPort;
    EFI_UINT32 RetryCount;
    EFI_UINT32 RetryInterval;
} EFI_DNS4_CONFIG_DATA;

typedef struct {
    EFI_CHAR16 *HostName;
    EFI_IPv4_ADDRESS *IpAddress;
    EFI_UINT32 Timeout;
} EFI_DNS4_CACHE_ENTRY;

typedef struct {
    EFI_DNS4_CONFIG_DATA DnsConfigData;
    EFI_UINT32 DnsServerCount;
    EFI_IPv4_ADDRESS *DnsServerList;
    EFI_UINT32 DnsCacheCount;
    EFI_DNS4_CACHE_ENTRY *DnsCacheList;
} EFI_DNS4_MODE_DATA;

typedef struct {
    EFI_UINT32 IpCount;
    EFI_IPv4_ADDRESS *IpList;
} EFI_DNS_HOST_TO_ADDR_DATA;

typedef struct {
    EFI_CHAR16 *HostName;
} EFI_DNS_ADDR_TO_HOST_DATA;

typedef struct {
    EFI_CHAR8 *QName;
    EFI_UINT16 QType;
    EFI_UINT16 QClass;
    EFI_UINT32 TTL;
    EFI_UINT16 DataLength;
    EFI_CHAR8 *RData;
} EFI_DNS_RESOURCE_RECORD;

typedef struct {
    EFI_UINTN RRCount;
    EFI_DNS_RESOURCE_RECORD *RRList;
} EFI_DNS_GENERAL_LOOKUP_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_UINT32 RetryCount;
    EFI_UINT32 RetryInterval;
    union {
        EFI_DNS_HOST_TO_ADDR_DATA *H2AData;
        EFI_DNS_ADDR_TO_HOST_DATA *A2HData;
        EFI_DNS_GENERAL_LOOKUP_DATA *GLookupData;
    } RspData;
} EFI_DNS4_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DNS4_GET_MODE_DATA)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_OUT EFI_DNS4_MODE_DATA *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CONFIGURE)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_DNS4_CONFIG_DATA *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_HOST_NAME_TO_IP)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_CHAR16 *HostName,
    EFI_IN EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_IP_TO_HOST_NAME)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_IPv4_ADDRESS IpAddress,
    EFI_IN EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_GENERAL_LOOKUP)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_CHAR8 *QName,
    EFI_IN EFI_UINT16 QType,
    EFI_IN EFI_UINT16 QClass,
    EFI_IN EFI_DNS4_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_UPDATE_DNS_CACHE)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteFlag,
    EFI_IN EFI_BOOLEAN Override,
    EFI_IN EFI_DNS4_CACHE_ENTRY DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_POLL)(EFI_IN EFI_DNS4_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CANCEL)(
    EFI_IN EFI_DNS4_PROTOCOL *This,
    EFI_IN EFI_DNS4_COMPLETION_TOKEN *Token
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
    EFI_BOOLEAN EnableDnsCache;
    EFI_UINT8 Protocol;
    EFI_IPv6_ADDRESS StationIp;
    EFI_UINT16 LocalPort;
    EFI_UINT32 DnsServerCount;
    EFI_IPv6_ADDRESS *DnsServerList;
    EFI_UINT32 RetryCount;
    EFI_UINT32 RetryInterval;
} EFI_DNS6_CONFIG_DATA;

typedef struct {
    EFI_CHAR16 *HostName;
    EFI_IPv6_ADDRESS *IpAddress;
    EFI_UINT32 Timeout;
} EFI_DNS6_CACHE_ENTRY;

typedef struct {
    EFI_DNS6_CONFIG_DATA DnsConfigData;
    EFI_UINT32 DnsServerCount;
    EFI_IPv6_ADDRESS *DnsServerList;
    EFI_UINT32 DnsCacheCount;
    EFI_DNS6_CACHE_ENTRY *DnsCacheList;
} EFI_DNS6_MODE_DATA;

typedef struct {
    EFI_UINT32 IpCount;
    EFI_IPv6_ADDRESS *IpList;
} EFI_DNS6_HOST_TO_ADDR_DATA;

typedef struct {
    EFI_CHAR16 *HostName;
} EFI_DNS6_ADDR_TO_HOST_DATA;

typedef struct {
    EFI_CHAR8 *QName;
    EFI_UINT16 QType;
    EFI_UINT16 QClass;
    EFI_UINT32 TTL;
    EFI_UINT16 DataLength;
    EFI_CHAR8 *RData;
} EFI_DNS6_RESOURCE_RECORD;

typedef struct {
    EFI_UINTN RRCount;
    EFI_DNS6_RESOURCE_RECORD *RRList;
} EFI_DNS6_GENERAL_LOOKUP_DATA;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_UINT32 RetryCount;
    EFI_UINT32 RetryInterval;
    union {
        EFI_DNS6_HOST_TO_ADDR_DATA *H2AData;
        EFI_DNS6_ADDR_TO_HOST_DATA *A2HData;
        EFI_DNS6_GENERAL_LOOKUP_DATA *GLookupData;
    } RspData;
} EFI_DNS6_COMPLETION_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_DNS6_GET_MODE_DATA)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_OUT EFI_DNS6_MODE_DATA *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CONFIGURE)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_DNS6_CONFIG_DATA *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_HOST_NAME_TO_IP)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_CHAR16 *HostName,
    EFI_IN EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_IP_TO_HOST_NAME)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_IPv6_ADDRESS IpAddress,
    EFI_IN EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_GENERAL_LOOKUP)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_CHAR8 *QName,
    EFI_IN EFI_UINT16 QType,
    EFI_IN EFI_UINT16 QClass,
    EFI_IN EFI_DNS6_COMPLETION_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_UPDATE_DNS_CACHE)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_BOOLEAN DeleteFlag,
    EFI_IN EFI_BOOLEAN Override,
    EFI_IN EFI_DNS6_CACHE_ENTRY DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_POLL)(EFI_IN EFI_DNS6_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CANCEL)(
    EFI_IN EFI_DNS6_PROTOCOL *This,
    EFI_IN EFI_DNS6_COMPLETION_TOKEN *Token
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
    EFI_BOOLEAN UseDefaultAddress;
    EFI_IPv4_ADDRESS LocalAddress;
    EFI_IPv4_ADDRESS LocalSubnet;
    EFI_UINT16 LocalPort;
} EFI_HTTPv4_ACCESS_POINT;

typedef struct {
    EFI_IPv6_ADDRESS LocalAddress;
    EFI_UINT16 LocalPort;
} EFI_HTTPv6_ACCESS_POINT;

typedef struct {
    EFI_HTTP_VERSION HttpVersion;
    EFI_UINT32 TimeOutMillisec;
    EFI_BOOLEAN LocalAddressIsIPv6;
    union {
        EFI_HTTPv4_ACCESS_POINT *IPv4Node;
        EFI_HTTPv6_ACCESS_POINT *IPv6Node;
    } AccessPoint;
} EFI_HTTP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_HTTP_GET_MODE_DATA)(
    EFI_IN EFI_HTTP_PROTOCOL *This,
    EFI_OUT EFI_HTTP_CONFIG_DATA *HttpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CONFIGURE)(
    EFI_IN EFI_HTTP_PROTOCOL *This,
    EFI_IN EFI_HTTP_CONFIG_DATA *HttpConfigData EFI_OPTIONAL
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
    EFI_CHAR16 *Url;
} EFI_HTTP_REQUEST_DATA;

typedef struct {
    EFI_HTTP_REQUEST_DATA Base;
    EFI_CHAR16 *ProxyUrl;
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
    EFI_CHAR8 *FieldName;
    EFI_CHAR8 *FieldValue;
} EFI_HTTP_HEADER;

typedef struct {
    union {
        EFI_HTTP_REQUEST_DATA *Request;
        EFI_HTTP_RESPONSE_DATA *Response;
    } Data;
    EFI_UINTN HeaderCount;
    EFI_HTTP_HEADER *Headers;
    EFI_UINTN BodyLength;
    EFI_VOID *Body;
} EFI_HTTP_MESSAGE;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_HTTP_MESSAGE *Message;
} EFI_HTTP_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_HTTP_REQUEST)(
    EFI_IN EFI_HTTP_PROTOCOL *This,
    EFI_IN EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CANCEL)(
    EFI_IN EFI_HTTP_PROTOCOL *This,
    EFI_IN EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_RESPONSE)(
    EFI_IN EFI_HTTP_PROTOCOL *This,
    EFI_IN EFI_HTTP_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_POLL)(EFI_IN EFI_HTTP_PROTOCOL *This);

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
    EFI_IN EFI_HTTP_UTILITIES_PROTOCOL *This,
    EFI_IN EFI_UINTN SeedMessageSize,
    EFI_IN EFI_VOID *SeedMessage EFI_OPTIONAL,
    EFI_IN EFI_UINTN DeleteCount,
    EFI_IN EFI_CHAR8 *DeleteList[] EFI_OPTIONAL,
    EFI_IN EFI_UINTN AppendCount,
    EFI_IN EFI_HTTP_HEADER *AppendList[] EFI_OPTIONAL,
    EFI_OUT EFI_UINTN *NewMessageSize,
    EFI_OUT EFI_VOID **NewMessage
);

/* This is the utilities protocol, as described; the prototype prints EFI_HTTP_PROTOCOL. */
typedef EFI_STATUS (EFI_API *EFI_HTTP_UTILS_PARSE)(
    EFI_IN EFI_HTTP_UTILITIES_PROTOCOL *This,
    EFI_IN EFI_CHAR8 *HttpMessage,
    EFI_IN EFI_UINTN HttpMessageSize,
    EFI_OUT EFI_HTTP_HEADER **HeaderFields,
    EFI_OUT EFI_UINTN *FieldCount
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
    EFI_IN EFI_REST_PROTOCOL *This,
    EFI_IN EFI_HTTP_MESSAGE *RequestMessage,
    EFI_OUT EFI_HTTP_MESSAGE *ResponseMessage
);

typedef EFI_STATUS (EFI_API *EFI_REST_GET_TIME)(
    EFI_IN EFI_REST_PROTOCOL *This,
    EFI_OUT EFI_TIME *Time
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
    EFI_UINT8 Major;
    EFI_UINT8 Minor;
} EFI_REST_EX_SERVICE_INFO_VER;

typedef struct {
    EFI_UINT32 Length;
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
    EFI_UINT32 VendorSpecificDataLength;
    EFI_UINT8 *VendorSpecifcData;
    EFI_REST_EX_CONFIG_TYPE RestExConfigType;
    EFI_UINT8 RestExConfigDataLength;
} EFI_REST_EX_SERVICE_INFO_V_1_0;

typedef union {
    EFI_REST_EX_SERVICE_INFO_HEADER EfiRestExServiceInfoHeader;
    EFI_REST_EX_SERVICE_INFO_V_1_0 EfiRestExServiceInfoV10;
} EFI_REST_EX_SERVICE_INFO;

typedef struct {
    EFI_HTTP_CONFIG_DATA HttpConfigData;
    EFI_UINT32 SendReceiveTimeout;
} EFI_REST_EX_HTTP_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_SERVICE)(
    EFI_IN EFI_REST_EX_PROTOCOL *This,
    EFI_OUT EFI_REST_EX_SERVICE_INFO **RestExServiceInfo
);

typedef EFI_UINT8 *EFI_REST_EX_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_MODE_DATA)(
    EFI_IN EFI_REST_EX_PROTOCOL *This,
    EFI_OUT EFI_REST_EX_CONFIG_DATA *RestExConfigData
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_CONFIGURE)(
    EFI_IN EFI_REST_EX_PROTOCOL *This,
    EFI_IN EFI_REST_EX_CONFIG_DATA RestExConfigData
);

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS Status;
    EFI_HTTP_MESSAGE *ResponseMessage;
} EFI_REST_EX_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_ASYNC_SEND_RECEIVE)(
    EFI_IN EFI_REST_EX_PROTOCOL *This,
    EFI_IN EFI_HTTP_MESSAGE *RequestMessage EFI_OPTIONAL,
    EFI_IN EFI_REST_EX_TOKEN *RestExToken,
    EFI_IN EFI_UINTN *TimeOutInMilliSeconds EFI_OPTIONAL
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_EVENT_SERVICE)(
    EFI_IN EFI_REST_EX_PROTOCOL *This,
    EFI_IN EFI_HTTP_MESSAGE *RequestMessage EFI_OPTIONAL,
    EFI_IN EFI_REST_EX_TOKEN *RestExToken
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

typedef EFI_CHAR8 *EFI_REST_JSON_RESOURCE_TYPE_DATATYPE;

typedef struct _EFI_REST_JSON_RESOURCE_TYPE_NAMESPACE {
    EFI_CHAR8 *ResourceTypeName;
    EFI_CHAR8 *MajorVersion;
    EFI_CHAR8 *MinorVersion;
    EFI_CHAR8 *ErrataVersion;
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
    EFI_VOID *JsonStructurePointer;
} EFI_REST_JSON_STRUCTURE_HEADER;

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_STRUCTURE)(
    EFI_IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_IN EFI_REST_JSON_RESOURCE_TYPE_IDENTIFIER *JsonRsrcIdentifier EFI_OPTIONAL,
    EFI_IN EFI_CHAR8 *ResourceJsonText,
    EFI_OUT EFI_REST_JSON_STRUCTURE_HEADER **JsonStructure
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_JSON)(
    EFI_IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_IN EFI_REST_JSON_STRUCTURE_HEADER *JsonStructureHeader,
    EFI_OUT EFI_CHAR8 **ResourceJsonText
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE)(
    EFI_IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_IN EFI_REST_JSON_STRUCTURE_HEADER *JsonStructureHeader
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_REGISTER)(
    EFI_IN EFI_REST_JSON_STRUCTURE_PROTOCOL *This,
    EFI_IN EFI_REST_JSON_STRUCTURE_SUPPORTED *JsonStructureSupported,
    EFI_IN EFI_REST_JSON_STRUCTURE_TO_STRUCTURE ToStructure,
    EFI_IN EFI_REST_JSON_STRUCTURE_TO_JSON ToJson,
    EFI_IN EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE DestroyStructure
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
