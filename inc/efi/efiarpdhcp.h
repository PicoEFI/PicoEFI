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

struct efi_arp_protocol;

struct efi_arp_config_data {
    uint16_t SwAddressType;
    uint8_t SwAddressLength;
    void *StationAddress;
    uint32_t EntryTimeOut;
    uint32_t RetryCount;
    uint32_t RetryTimeOut;
};

typedef EFI_STATUS (EFI_API *EFI_ARP_CONFIGURE)(
    struct efi_arp_protocol *This,
    struct efi_arp_config_data *ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_ARP_ADD)(
    struct efi_arp_protocol *This,
    bool DenyFlag,
    void *TargetSwAddress,
    void *TargetHwAddress,
    uint32_t TimeoutValue,
    bool Overwrite
);

struct efi_arp_find_data {
    uint32_t Size;
    uint8_t DenyFlag;
    uint8_t StaticFlag;
    uint16_t HwAddressType;
    uint16_t SwAddressType;
    uint8_t HwAddressLength;
    uint8_t SwAddressLength;
};

typedef EFI_STATUS (EFI_API *EFI_ARP_FIND)(
    struct efi_arp_protocol *This,
    bool BySwAddress,
    void *AddressBuffer,
    uint32_t *EntryLength,
    uint32_t *EntryCount,
    struct efi_arp_find_data **Entries,
    bool Refresh
);

typedef EFI_STATUS (EFI_API *EFI_ARP_DELETE)(
    struct efi_arp_protocol *This,
    bool BySwAddress,
    void *AddressBuffer
);

typedef EFI_STATUS (EFI_API *EFI_ARP_FLUSH)(struct efi_arp_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_ARP_REQUEST)(
    struct efi_arp_protocol *This,
    void *TargetSwAddress,
    EFI_EVENT ResolvedEvent,
    void *TargetHwAddress
);

typedef EFI_STATUS (EFI_API *EFI_ARP_CANCEL)(
    struct efi_arp_protocol *This,
    void *TargetSwAddress,
    EFI_EVENT ResolvedEvent
);

struct efi_arp_protocol {
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

struct efi_dhcp4_protocol;

#define EFI_DHCP4_STOPPED ((uint32_t)0x0)
#define EFI_DHCP4_INIT ((uint32_t)0x1)
#define EFI_DHCP4_SELECTING ((uint32_t)0x2)
#define EFI_DHCP4_REQUESTING ((uint32_t)0x3)
#define EFI_DHCP4_BOUND ((uint32_t)0x4)
#define EFI_DHCP4_RENEWING ((uint32_t)0x5)
#define EFI_DHCP4_REBINDING ((uint32_t)0x6)
#define EFI_DHCP4_INIT_REBOOT ((uint32_t)0x7)
#define EFI_DHCP4_REBOOTING ((uint32_t)0x8)

#define EFI_DHCP4_SEND_DISCOVER ((uint32_t)0x01)
#define EFI_DHCP4_RCVD_OFFER ((uint32_t)0x02)
#define EFI_DHCP4_SELECT_OFFER ((uint32_t)0x03)
#define EFI_DHCP4_SEND_REQUEST ((uint32_t)0x04)
#define EFI_DHCP4_RCVD_ACK ((uint32_t)0x05)
#define EFI_DHCP4_RCVD_NAK ((uint32_t)0x06)
#define EFI_DHCP4_SEND_DECLINE ((uint32_t)0x07)
#define EFI_DHCP4_BOUND_COMPLETED ((uint32_t)0x08)
#define EFI_DHCP4_ENTER_RENEWING ((uint32_t)0x09)
#define EFI_DHCP4_ENTER_REBINDING ((uint32_t)0x0a)
#define EFI_DHCP4_ADDRESS_LOST ((uint32_t)0x0b)
#define EFI_DHCP4_FAIL ((uint32_t)0x0c)

struct efi_dhcp4_header {
    uint8_t OpCode;
    uint8_t HwType;
    uint8_t HwAddrLen;
    uint8_t Hops;
    uint32_t Xid;
    uint16_t Seconds;
    uint16_t Reserved;
    struct efi_ipv4_address ClientAddr;
    struct efi_ipv4_address YourAddr;
    struct efi_ipv4_address ServerAddr;
    struct efi_ipv4_address GatewayAddr;
    uint8_t ClientHwAddr[16];
    char ServerName[64];
    char BootFileName[128];
} __attribute__((__packed__));

struct efi_dhcp4_packet {
    uint32_t Size;
    uint32_t Length;
    struct __attribute__((__packed__)) {
        struct efi_dhcp4_header Header;
        uint32_t Magik;
        uint8_t Option[1];
    } Dhcp4;
} __attribute__((__packed__));

struct efi_dhcp4_packet_option {
    uint8_t OpCode;
    uint8_t Length;
    uint8_t Data[1];
} __attribute__((__packed__));

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CALLBACK)(
    struct efi_dhcp4_protocol *This,
    void *Context,
    uint32_t CurrentState,
    uint32_t Dhcp4Event,
    struct efi_dhcp4_packet *Packet,
    struct efi_dhcp4_packet **NewPacket
);

struct efi_dhcp4_config_data {
    uint32_t DiscoverTryCount;
    uint32_t *DiscoverTimeout;
    uint32_t RequestTryCount;
    uint32_t *RequestTimeout;
    struct efi_ipv4_address ClientAddress;
    EFI_DHCP4_CALLBACK Dhcp4Callback;
    void *CallbackContext;
    uint32_t OptionCount;
    struct efi_dhcp4_packet_option **OptionList;
};

struct efi_dhcp4_mode_data {
    uint32_t State;
    struct efi_dhcp4_config_data ConfigData;
    struct efi_ipv4_address ClientAddress;
    struct efi_mac_address ClientMacAddress;
    struct efi_ipv4_address ServerAddress;
    struct efi_ipv4_address RouterAddress;
    struct efi_ipv4_address SubnetMask;
    uint32_t LeaseTime;
    struct efi_dhcp4_packet *ReplyPacket;
};

struct efi_dhcp4_listen_point {
    struct efi_ipv4_address ListenAddress;
    struct efi_ipv4_address SubnetMask;
    uint16_t ListenPort;
};

struct efi_dhcp4_transmit_receive_token {
    EFI_STATUS Status;
    EFI_EVENT CompletionEvent;
    struct efi_ipv4_address RemoteAddress;
    uint16_t RemotePort;
    struct efi_ipv4_address GatewayAddress;
    uint32_t ListenPointCount;
    struct efi_dhcp4_listen_point *ListenPoints;
    uint32_t TimeoutValue;
    struct efi_dhcp4_packet *Packet;
    uint32_t ResponseCount;
    struct efi_dhcp4_packet *ResponseList;
};

typedef EFI_STATUS (EFI_API *EFI_DHCP4_GET_MODE_DATA)(
    struct efi_dhcp4_protocol *This,
    struct efi_dhcp4_mode_data *Dhcp4ModeData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_CONFIGURE)(
    struct efi_dhcp4_protocol *This,
    struct efi_dhcp4_config_data *Dhcp4CfgData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_START)(
    struct efi_dhcp4_protocol *This,
    EFI_EVENT CompletionEvent
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RENEW_REBIND)(
    struct efi_dhcp4_protocol *This,
    bool RebindRequest,
    EFI_EVENT CompletionEvent
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_RELEASE)(struct efi_dhcp4_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_STOP)(struct efi_dhcp4_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_BUILD)(
    struct efi_dhcp4_protocol *This,
    struct efi_dhcp4_packet *SeedPacket,
    uint32_t DeleteCount,
    uint8_t *DeleteList,
    uint32_t AppendCount,
    struct efi_dhcp4_packet_option *AppendList[],
    struct efi_dhcp4_packet **NewPacket
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_TRANSMIT_RECEIVE)(
    struct efi_dhcp4_protocol *This,
    struct efi_dhcp4_transmit_receive_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DHCP4_PARSE)(
    struct efi_dhcp4_protocol *This,
    struct efi_dhcp4_packet *Packet,
    uint32_t *OptionCount,
    struct efi_dhcp4_packet_option *PacketOptionList[]
);

struct efi_dhcp4_protocol {
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

struct efi_dhcp6_protocol;

struct efi_dhcp6_duid {
    uint16_t Length;
    uint8_t Duid[1];
};

struct efi_dhcp6_ia_descriptor {
    uint16_t Type;
    uint32_t IaId;
};

#define EFI_DHCP6_IA_TYPE_NA 3
#define EFI_DHCP6_IA_TYPE_TA 4

#define EFI_DHCP6_INIT ((uint32_t)0x0)
#define EFI_DHCP6_SELECTING ((uint32_t)0x1)
#define EFI_DHCP6_REQUESTING ((uint32_t)0x2)
#define EFI_DHCP6_DECLINING ((uint32_t)0x3)
#define EFI_DHCP6_CONFIRMING ((uint32_t)0x4)
#define EFI_DHCP6_RELEASING ((uint32_t)0x5)
#define EFI_DHCP6_BOUND ((uint32_t)0x6)
#define EFI_DHCP6_RENEWING ((uint32_t)0x7)
#define EFI_DHCP6_REBINDING ((uint32_t)0x8)

struct efi_dhcp6_ia_address {
    struct efi_ipv6_address IpAddress;
    uint32_t PreferredLifetime;
    uint32_t ValidLifetime;
};

struct efi_dhcp6_header {
    uint32_t TransactionId:24;
    uint32_t MessageType:8;
} __attribute__((__packed__));

struct efi_dhcp6_packet {
    uint32_t Size;
    uint32_t Length;
    struct __attribute__((__packed__)) {
        struct efi_dhcp6_header Header;
        uint8_t Option[1];
    } Dhcp6;
} __attribute__((__packed__));

struct efi_dhcp6_ia {
    struct efi_dhcp6_ia_descriptor Descriptor;
    uint32_t State;
    struct efi_dhcp6_packet *ReplyPacket;
    uint32_t IaAddressCount;
    struct efi_dhcp6_ia_address IaAddress[1];
};

struct efi_dhcp6_mode_data {
    struct efi_dhcp6_duid *ClientId;
    struct efi_dhcp6_ia *Ia;
};

struct efi_dhcp6_packet_option {
    uint16_t OpCode;
    uint16_t OpLen;
    uint8_t Data[1];
} __attribute__((__packed__));

#define EFI_DHCP6_SEND_SOLICIT ((uint32_t)0x0)
#define EFI_DHCP6_RCVD_ADVERTISE ((uint32_t)0x1)
#define EFI_DHCP6_SELECT_ADVERTISE ((uint32_t)0x2)
#define EFI_DHCP6_SEND_REQUEST ((uint32_t)0x3)
#define EFI_DHCP6_RCVD_REPLY ((uint32_t)0x4)
#define EFI_DHCP6_RCVD_RECONFIGURE ((uint32_t)0x5)
#define EFI_DHCP6_SEND_DECLINE ((uint32_t)0x6)
#define EFI_DHCP6_SEND_CONFIRM ((uint32_t)0x7)
#define EFI_DHCP6_SEND_RELEASE ((uint32_t)0x8)
#define EFI_DHCP6_SEND_RENEW ((uint32_t)0x9)
#define EFI_DHCP6_SEND_REBIND ((uint32_t)0xa)

typedef EFI_STATUS (EFI_API *EFI_DHCP6_CALLBACK)(
    struct efi_dhcp6_protocol *This,
    void *Context,
    uint32_t CurrentState,
    uint32_t Dhcp6Event,
    struct efi_dhcp6_packet *Packet,
    struct efi_dhcp6_packet **NewPacket
);

struct efi_dhcp6_retransmission {
    uint32_t Irt;
    uint32_t Mrc;
    uint32_t Mrt;
    uint32_t Mrd;
};

struct efi_dhcp6_config_data {
    EFI_DHCP6_CALLBACK Dhcp6Callback;
    void *CallbackContext;
    uint32_t OptionCount;
    struct efi_dhcp6_packet_option **OptionList;
    struct efi_dhcp6_ia_descriptor IaDescriptor;
    EFI_EVENT IaInfoEvent;
    uint8_t ReconfigureAccept;
    uint8_t RapidCommit;
    struct efi_dhcp6_retransmission *SolicitRetransmission;
};

typedef EFI_STATUS (EFI_API *EFI_DHCP6_GET_MODE_DATA)(
    struct efi_dhcp6_protocol *This,
    struct efi_dhcp6_mode_data *Dhcp6ModeData,
    struct efi_dhcp6_config_data *Dhcp6ConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_CONFIGURE)(
    struct efi_dhcp6_protocol *This,
    struct efi_dhcp6_config_data *Dhcp6CfgData
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_START)(struct efi_dhcp6_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_CALLBACK)(
    struct efi_dhcp6_protocol *This,
    void *Context,
    struct efi_dhcp6_packet *Packet
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_INFO_REQUEST)(
    struct efi_dhcp6_protocol *This,
    bool SendClientId,
    struct efi_dhcp6_packet_option *OptionRequest,
    uint32_t OptionCount,
    struct efi_dhcp6_packet_option *OptionList[],
    struct efi_dhcp6_retransmission *Retransmission,
    EFI_EVENT TimeoutEvent,
    EFI_DHCP6_INFO_CALLBACK ReplyCallback,
    void *CallbackContext
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RENEW_REBIND)(
    struct efi_dhcp6_protocol *This,
    bool RebindRequest
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_DECLINE)(
    struct efi_dhcp6_protocol *This,
    uint32_t AddressCount,
    struct efi_ipv6_address *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_RELEASE)(
    struct efi_dhcp6_protocol *This,
    uint32_t AddressCount,
    struct efi_ipv6_address *Addresses
);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_STOP)(struct efi_dhcp6_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DHCP6_PARSE)(
    struct efi_dhcp6_protocol *This,
    struct efi_dhcp6_packet *Packet,
    uint32_t *OptionCount,
    struct efi_dhcp6_packet_option *PacketOptionList[]
);

struct efi_dhcp6_protocol {
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

struct efi_dns4_protocol;

struct efi_dns4_config_data {
    size_t DnsServerListCount;
    struct efi_ipv4_address *DnsServerList;
    uint8_t UseDefaultSetting;
    uint8_t EnableDnsCache;
    uint8_t Protocol;
    struct efi_ipv4_address StationIp;
    struct efi_ipv4_address SubnetMask;
    uint16_t LocalPort;
    uint32_t RetryCount;
    uint32_t RetryInterval;
};

struct efi_dns4_cache_entry {
    uint16_t *HostName;
    struct efi_ipv4_address *IpAddress;
    uint32_t Timeout;
};

struct efi_dns4_mode_data {
    struct efi_dns4_config_data DnsConfigData;
    uint32_t DnsServerCount;
    struct efi_ipv4_address *DnsServerList;
    uint32_t DnsCacheCount;
    struct efi_dns4_cache_entry *DnsCacheList;
};

struct efi_dns_host_to_addr_data {
    uint32_t IpCount;
    struct efi_ipv4_address *IpList;
};

struct efi_dns_addr_to_host_data {
    uint16_t *HostName;
};

struct efi_dns_resource_record {
    char *QName;
    uint16_t QType;
    uint16_t QClass;
    uint32_t TTL;
    uint16_t DataLength;
    char *RData;
};

struct efi_dns_general_lookup_data {
    size_t RRCount;
    struct efi_dns_resource_record *RRList;
};

struct efi_dns4_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    uint32_t RetryCount;
    uint32_t RetryInterval;
    union {
        struct efi_dns_host_to_addr_data *H2AData;
        struct efi_dns_addr_to_host_data *A2HData;
        struct efi_dns_general_lookup_data *GLookupData;
    } RspData;
};

typedef EFI_STATUS (EFI_API *EFI_DNS4_GET_MODE_DATA)(
    struct efi_dns4_protocol *This,
    struct efi_dns4_mode_data *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CONFIGURE)(
    struct efi_dns4_protocol *This,
    struct efi_dns4_config_data *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_HOST_NAME_TO_IP)(
    struct efi_dns4_protocol *This,
    uint16_t *HostName,
    struct efi_dns4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_IP_TO_HOST_NAME)(
    struct efi_dns4_protocol *This,
    struct efi_ipv4_address IpAddress,
    struct efi_dns4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_GENERAL_LOOKUP)(
    struct efi_dns4_protocol *This,
    char *QName,
    uint16_t QType,
    uint16_t QClass,
    struct efi_dns4_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_UPDATE_DNS_CACHE)(
    struct efi_dns4_protocol *This,
    bool DeleteFlag,
    bool Override,
    struct efi_dns4_cache_entry DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS4_POLL)(struct efi_dns4_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DNS4_CANCEL)(
    struct efi_dns4_protocol *This,
    struct efi_dns4_completion_token *Token
);

struct efi_dns4_protocol {
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

struct efi_dns6_protocol;

struct efi_dns6_config_data {
    uint8_t EnableDnsCache;
    uint8_t Protocol;
    struct efi_ipv6_address StationIp;
    uint16_t LocalPort;
    uint32_t DnsServerCount;
    struct efi_ipv6_address *DnsServerList;
    uint32_t RetryCount;
    uint32_t RetryInterval;
};

struct efi_dns6_cache_entry {
    uint16_t *HostName;
    struct efi_ipv6_address *IpAddress;
    uint32_t Timeout;
};

struct efi_dns6_mode_data {
    struct efi_dns6_config_data DnsConfigData;
    uint32_t DnsServerCount;
    struct efi_ipv6_address *DnsServerList;
    uint32_t DnsCacheCount;
    struct efi_dns6_cache_entry *DnsCacheList;
};

struct efi_dns6_host_to_addr_data {
    uint32_t IpCount;
    struct efi_ipv6_address *IpList;
};

struct efi_dns6_addr_to_host_data {
    uint16_t *HostName;
};

struct efi_dns6_resource_record {
    char *QName;
    uint16_t QType;
    uint16_t QClass;
    uint32_t TTL;
    uint16_t DataLength;
    char *RData;
};

struct efi_dns6_general_lookup_data {
    size_t RRCount;
    struct efi_dns6_resource_record *RRList;
};

struct efi_dns6_completion_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    uint32_t RetryCount;
    uint32_t RetryInterval;
    union {
        struct efi_dns6_host_to_addr_data *H2AData;
        struct efi_dns6_addr_to_host_data *A2HData;
        struct efi_dns6_general_lookup_data *GLookupData;
    } RspData;
};

typedef EFI_STATUS (EFI_API *EFI_DNS6_GET_MODE_DATA)(
    struct efi_dns6_protocol *This,
    struct efi_dns6_mode_data *DnsModeData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CONFIGURE)(
    struct efi_dns6_protocol *This,
    struct efi_dns6_config_data *DnsConfigData
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_HOST_NAME_TO_IP)(
    struct efi_dns6_protocol *This,
    uint16_t *HostName,
    struct efi_dns6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_IP_TO_HOST_NAME)(
    struct efi_dns6_protocol *This,
    struct efi_ipv6_address IpAddress,
    struct efi_dns6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_GENERAL_LOOKUP)(
    struct efi_dns6_protocol *This,
    char *QName,
    uint16_t QType,
    uint16_t QClass,
    struct efi_dns6_completion_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_UPDATE_DNS_CACHE)(
    struct efi_dns6_protocol *This,
    bool DeleteFlag,
    bool Override,
    struct efi_dns6_cache_entry DnsCacheEntry
);

typedef EFI_STATUS (EFI_API *EFI_DNS6_POLL)(struct efi_dns6_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DNS6_CANCEL)(
    struct efi_dns6_protocol *This,
    struct efi_dns6_completion_token *Token
);

struct efi_dns6_protocol {
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

struct efi_http_protocol;

#define EFI_HTTP_VERSION10 ((uint32_t)0)
#define EFI_HTTP_VERSION11 ((uint32_t)1)
#define EFI_HTTP_VERSION_UNSUPPORTED ((uint32_t)2)

struct efi_httpv4_access_point {
    uint8_t UseDefaultAddress;
    struct efi_ipv4_address LocalAddress;
    struct efi_ipv4_address LocalSubnet;
    uint16_t LocalPort;
};

struct efi_httpv6_access_point {
    struct efi_ipv6_address LocalAddress;
    uint16_t LocalPort;
};

struct efi_http_config_data {
    uint32_t HttpVersion;
    uint32_t TimeOutMillisec;
    uint8_t LocalAddressIsIPv6;
    union {
        struct efi_httpv4_access_point *IPv4Node;
        struct efi_httpv6_access_point *IPv6Node;
    } AccessPoint;
};

typedef EFI_STATUS (EFI_API *EFI_HTTP_GET_MODE_DATA)(
    struct efi_http_protocol *This,
    struct efi_http_config_data *HttpConfigData
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CONFIGURE)(
    struct efi_http_protocol *This,
    struct efi_http_config_data *HttpConfigData
);

#define EFI_HTTP_METHOD_GET ((uint32_t)0)
#define EFI_HTTP_METHOD_POST ((uint32_t)1)
#define EFI_HTTP_METHOD_PATCH ((uint32_t)2)
#define EFI_HTTP_METHOD_OPTIONS ((uint32_t)3)
#define EFI_HTTP_METHOD_CONNECT ((uint32_t)4)
#define EFI_HTTP_METHOD_HEAD ((uint32_t)5)
#define EFI_HTTP_METHOD_PUT ((uint32_t)6)
#define EFI_HTTP_METHOD_DELETE ((uint32_t)7)
#define EFI_HTTP_METHOD_TRACE ((uint32_t)8)
#define EFI_HTTP_METHOD_MAX ((uint32_t)9)

struct efi_http_request_data {
    uint32_t Method;
    uint16_t *Url;
};

struct efi_http_connect_request_data {
    struct efi_http_request_data Base;
    uint16_t *ProxyUrl;
};

#define EFI_HTTP_STATUS_UNSUPPORTED_STATUS ((uint32_t)0)
#define EFI_HTTP_STATUS_100_CONTINUE ((uint32_t)1)
#define EFI_HTTP_STATUS_101_SWITCHING_PROTOCOLS ((uint32_t)2)
#define EFI_HTTP_STATUS_200_OK ((uint32_t)3)
#define EFI_HTTP_STATUS_201_CREATED ((uint32_t)4)
#define EFI_HTTP_STATUS_202_ACCEPTED ((uint32_t)5)
#define EFI_HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION ((uint32_t)6)
#define EFI_HTTP_STATUS_204_NO_CONTENT ((uint32_t)7)
#define EFI_HTTP_STATUS_205_RESET_CONTENT ((uint32_t)8)
#define EFI_HTTP_STATUS_206_PARTIAL_CONTENT ((uint32_t)9)
#define EFI_HTTP_STATUS_300_MULTIPLE_CHOICES ((uint32_t)10)
#define EFI_HTTP_STATUS_301_MOVED_PERMANENTLY ((uint32_t)11)
#define EFI_HTTP_STATUS_302_FOUND ((uint32_t)12)
#define EFI_HTTP_STATUS_303_SEE_OTHER ((uint32_t)13)
#define EFI_HTTP_STATUS_304_NOT_MODIFIED ((uint32_t)14)
#define EFI_HTTP_STATUS_305_USE_PROXY ((uint32_t)15)
#define EFI_HTTP_STATUS_307_TEMPORARY_REDIRECT ((uint32_t)16)
#define EFI_HTTP_STATUS_400_BAD_REQUEST ((uint32_t)17)
#define EFI_HTTP_STATUS_401_UNAUTHORIZED ((uint32_t)18)
#define EFI_HTTP_STATUS_402_PAYMENT_REQUIRED ((uint32_t)19)
#define EFI_HTTP_STATUS_403_FORBIDDEN ((uint32_t)20)
#define EFI_HTTP_STATUS_404_NOT_FOUND ((uint32_t)21)
#define EFI_HTTP_STATUS_405_METHOD_NOT_ALLOWED ((uint32_t)22)
#define EFI_HTTP_STATUS_406_NOT_ACCEPTABLE ((uint32_t)23)
#define EFI_HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED ((uint32_t)24)
#define EFI_HTTP_STATUS_408_REQUEST_TIME_OUT ((uint32_t)25)
#define EFI_HTTP_STATUS_409_CONFLICT ((uint32_t)26)
#define EFI_HTTP_STATUS_410_GONE ((uint32_t)27)
#define EFI_HTTP_STATUS_411_LENGTH_REQUIRED ((uint32_t)28)
#define EFI_HTTP_STATUS_412_PRECONDITION_FAILED ((uint32_t)29)
#define EFI_HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE ((uint32_t)30)
#define EFI_HTTP_STATUS_414_REQUEST_URI_TOO_LARGE ((uint32_t)31)
#define EFI_HTTP_STATUS_415_UNSUPPORTED_MEDIA_TYPE ((uint32_t)32)
#define EFI_HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED ((uint32_t)33)
#define EFI_HTTP_STATUS_417_EXPECTATION_FAILED ((uint32_t)34)
#define EFI_HTTP_STATUS_500_INTERNAL_SERVER_ERROR ((uint32_t)35)
#define EFI_HTTP_STATUS_501_NOT_IMPLEMENTED ((uint32_t)36)
#define EFI_HTTP_STATUS_502_BAD_GATEWAY ((uint32_t)37)
#define EFI_HTTP_STATUS_503_SERVICE_UNAVAILABLE ((uint32_t)38)
#define EFI_HTTP_STATUS_504_GATEWAY_TIME_OUT ((uint32_t)39)
#define EFI_HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED ((uint32_t)40)
#define EFI_HTTP_STATUS_308_PERMANENT_REDIRECT ((uint32_t)41)

struct efi_http_response_data {
    uint32_t StatusCode;
};

struct efi_http_header {
    char *FieldName;
    char *FieldValue;
};

struct efi_http_message {
    union {
        struct efi_http_request_data *Request;
        struct efi_http_response_data *Response;
    } Data;
    size_t HeaderCount;
    struct efi_http_header *Headers;
    size_t BodyLength;
    void *Body;
};

struct efi_http_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_http_message *Message;
};

typedef EFI_STATUS (EFI_API *EFI_HTTP_REQUEST)(
    struct efi_http_protocol *This,
    struct efi_http_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_CANCEL)(
    struct efi_http_protocol *This,
    struct efi_http_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_RESPONSE)(
    struct efi_http_protocol *This,
    struct efi_http_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_HTTP_POLL)(struct efi_http_protocol *This);

struct efi_http_protocol {
    EFI_HTTP_GET_MODE_DATA GetModeData;
    EFI_HTTP_CONFIGURE Configure;
    EFI_HTTP_REQUEST Request;
    EFI_HTTP_CANCEL Cancel;
    EFI_HTTP_RESPONSE Response;
    EFI_HTTP_POLL Poll;
};

#define EFI_HTTP_UTILITIES_PROTOCOL_GUID \
    {0x3E35C163, 0x4074, 0x45DD, {0x43, 0x1E, 0x23, 0x98, 0x9D, 0xD8, 0x6B, 0x32}}

struct efi_http_utilities_protocol;

typedef EFI_STATUS (EFI_API *EFI_HTTP_UTILS_BUILD)(
    struct efi_http_utilities_protocol *This,
    size_t SeedMessageSize,
    void *SeedMessage,
    size_t DeleteCount,
    char *DeleteList[],
    size_t AppendCount,
    struct efi_http_header *AppendList[],
    size_t *NewMessageSize,
    void **NewMessage
);

/* This is the utilities protocol, as described; the prototype prints EFI_HTTP_PROTOCOL. */
typedef EFI_STATUS (EFI_API *EFI_HTTP_UTILS_PARSE)(
    struct efi_http_utilities_protocol *This,
    char *HttpMessage,
    size_t HttpMessageSize,
    struct efi_http_header **HeaderFields,
    size_t *FieldCount
);

struct efi_http_utilities_protocol {
    EFI_HTTP_UTILS_BUILD Build;
    EFI_HTTP_UTILS_PARSE Parse;
};

#define EFI_REST_PROTOCOL_GUID \
    {0x0DB48A36, 0x4E54, 0xEA9C, {0x9B, 0x09, 0x1E, 0xA5, 0xBE, 0x3A, 0x66, 0x0B}}

struct efi_rest_protocol;

/* Shared by struct efi_rest_ex_protocol, whose section reprints it with an EFI_REST_EX_PROTOCOL This. */
typedef EFI_STATUS (EFI_API *EFI_REST_SEND_RECEIVE)(
    struct efi_rest_protocol *This,
    struct efi_http_message *RequestMessage,
    struct efi_http_message *ResponseMessage
);

typedef EFI_STATUS (EFI_API *EFI_REST_GET_TIME)(
    struct efi_rest_protocol *This,
    struct efi_time *Time
);

struct efi_rest_protocol {
    EFI_REST_SEND_RECEIVE SendReceive;
    EFI_REST_GET_TIME GetServiceTime;
};

#define EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID \
    {0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59}}

#define EFI_REST_EX_PROTOCOL_GUID \
    {0x55648b91, 0xe7d, 0x40a3, {0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97}}

struct efi_rest_ex_protocol;

struct efi_rest_ex_service_info_ver {
    uint8_t Major;
    uint8_t Minor;
};

struct efi_rest_ex_service_info_header {
    uint32_t Length;
    struct efi_rest_ex_service_info_ver RestServiceInfoVer;
};

#define EFI_REST_EX_SERVICE_UNSPECIFIC ((uint32_t)1)
#define EFI_REST_EX_SERVICE_REDFISH ((uint32_t)2)
#define EFI_REST_EX_SERVICE_ODATA ((uint32_t)3)
#define EFI_REST_EX_SERVICE_VENDOR_SPECIFIC ((uint32_t)0xff)
#define EFI_REST_EX_SERVICE_TYPE_MAX ((uint32_t)256)

#define EFI_REST_EX_SERVICE_IN_BAND_ACCESS ((uint32_t)1)
#define EFI_REST_EX_SERVICE_OUT_OF_BAND_ACCESS ((uint32_t)2)
#define EFI_REST_EX_SERVICE_ACCESS_MODE_MAX ((uint32_t)3)

#define EFI_REST_EX_CONFIG_TYPE_HTTP ((uint32_t)0)
#define EFI_REST_EX_CONFIG_TYPE_UNSPECIFIC ((uint32_t)1)
#define EFI_REST_EX_CONFIG_TYPE_MAX ((uint32_t)2)

struct efi_rest_ex_service_info_v_1_0 {
    struct efi_rest_ex_service_info_header EfiRestExServiceInfoHeader;
    uint32_t RestExServiceType;
    uint32_t RestServiceAccessMode;
    struct efi_guid VendorRestServiceName;
    uint32_t VendorSpecificDataLength;
    uint8_t *VendorSpecifcData;
    uint32_t RestExConfigType;
    uint8_t RestExConfigDataLength;
};

union efi_rest_ex_service_info {
    struct efi_rest_ex_service_info_header EfiRestExServiceInfoHeader;
    struct efi_rest_ex_service_info_v_1_0 EfiRestExServiceInfoV10;
};

struct efi_rest_ex_http_config_data {
    struct efi_http_config_data HttpConfigData;
    uint32_t SendReceiveTimeout;
};

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_SERVICE)(
    struct efi_rest_ex_protocol *This,
    union efi_rest_ex_service_info **RestExServiceInfo
);

typedef uint8_t *EFI_REST_EX_CONFIG_DATA;

typedef EFI_STATUS (EFI_API *EFI_REST_EX_GET_MODE_DATA)(
    struct efi_rest_ex_protocol *This,
    EFI_REST_EX_CONFIG_DATA *RestExConfigData
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_CONFIGURE)(
    struct efi_rest_ex_protocol *This,
    EFI_REST_EX_CONFIG_DATA RestExConfigData
);

struct efi_rest_ex_token {
    EFI_EVENT Event;
    EFI_STATUS Status;
    struct efi_http_message *ResponseMessage;
};

typedef EFI_STATUS (EFI_API *EFI_REST_EX_ASYNC_SEND_RECEIVE)(
    struct efi_rest_ex_protocol *This,
    struct efi_http_message *RequestMessage,
    struct efi_rest_ex_token *RestExToken,
    uintptr_t *TimeOutInMilliSeconds
);

typedef EFI_STATUS (EFI_API *EFI_REST_EX_EVENT_SERVICE)(
    struct efi_rest_ex_protocol *This,
    struct efi_http_message *RequestMessage,
    struct efi_rest_ex_token *RestExToken
);

struct efi_rest_ex_protocol {
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

struct efi_rest_json_structure_protocol;

typedef char *EFI_REST_JSON_RESOURCE_TYPE_DATATYPE;

struct efi_rest_json_resource_type_namespace {
    char *ResourceTypeName;
    char *MajorVersion;
    char *MinorVersion;
    char *ErrataVersion;
};

struct efi_rest_json_resource_type_identifier {
    struct efi_rest_json_resource_type_namespace Namespace;
    EFI_REST_JSON_RESOURCE_TYPE_DATATYPE Datatype;
};

struct efi_rest_json_structure_supported;

struct efi_rest_json_structure_supported {
    struct efi_rest_json_structure_supported *Next;
    struct efi_rest_json_resource_type_identifier JsonResourceType;
};

struct efi_rest_json_structure_header {
    struct efi_rest_json_resource_type_identifier JsonRsrcIdentifier;
    void *JsonStructurePointer;
};

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_STRUCTURE)(
    struct efi_rest_json_structure_protocol *This,
    struct efi_rest_json_resource_type_identifier *JsonRsrcIdentifier,
    char *ResourceJsonText,
    struct efi_rest_json_structure_header **JsonStructure
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_TO_JSON)(
    struct efi_rest_json_structure_protocol *This,
    struct efi_rest_json_structure_header *JsonStructureHeader,
    char **ResourceJsonText
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE)(
    struct efi_rest_json_structure_protocol *This,
    struct efi_rest_json_structure_header *JsonStructureHeader
);

typedef EFI_STATUS (EFI_API *EFI_REST_JSON_STRUCTURE_REGISTER)(
    struct efi_rest_json_structure_protocol *This,
    struct efi_rest_json_structure_supported *JsonStructureSupported,
    EFI_REST_JSON_STRUCTURE_TO_STRUCTURE ToStructure,
    EFI_REST_JSON_STRUCTURE_TO_JSON ToJson,
    EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE DestroyStructure
);

struct efi_rest_json_structure_protocol {
    EFI_REST_JSON_STRUCTURE_REGISTER Register;
    EFI_REST_JSON_STRUCTURE_TO_STRUCTURE ToStructure;
    EFI_REST_JSON_STRUCTURE_TO_JSON ToJson;
    EFI_REST_JSON_STRUCTURE_DESTORY_STRUCTURE DestoryStructure;
};

#ifdef __cplusplus
}
#endif

#endif
