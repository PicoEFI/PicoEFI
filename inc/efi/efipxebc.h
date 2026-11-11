#ifndef EFI_EFIPXEBC_H
#define EFI_EFIPXEBC_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PXE_BASE_CODE_PROTOCOL_GUID \
    {0x03c4e603, 0xac28, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_PXE_BASE_CODE_PROTOCOL_REVISION 0x00010000

struct efi_pxe_base_code_protocol;

#define EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES 8
#define EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES 8

typedef uint16_t efi_pxe_base_code_udp_port;

// Not packed: firmware lays these out naturally, though the specification says
// byte-packed.
struct efi_pxe_base_code_dhcpv4_packet {
    uint8_t bootp_opcode;
    uint8_t bootp_hw_type;
    uint8_t bootp_hw_addr_len;
    uint8_t bootp_gate_hops;
    uint32_t bootp_ident;
    uint16_t bootp_seconds;
    uint16_t bootp_flags;
    uint8_t bootp_ci_addr[4];
    uint8_t bootp_yi_addr[4];
    uint8_t bootp_si_addr[4];
    uint8_t bootp_gi_addr[4];
    uint8_t bootp_hw_addr[16];
    uint8_t bootp_srv_name[64];
    uint8_t bootp_boot_file[128];
    uint32_t dhcp_magik;
    uint8_t dhcp_options[56];
};

struct efi_pxe_base_code_dhcpv6_packet {
    uint32_t header;
    uint8_t dhcp_options[1024];
};

#define EFI_PXE_BASE_CODE_DHCPV6_PACKET_MESSAGE_TYPE_SHIFT 0
#define EFI_PXE_BASE_CODE_DHCPV6_PACKET_MESSAGE_TYPE_MASK 0x000000ff
#define EFI_PXE_BASE_CODE_DHCPV6_PACKET_TRANSACTION_ID_SHIFT 8
#define EFI_PXE_BASE_CODE_DHCPV6_PACKET_TRANSACTION_ID_MASK 0xffffff00

union efi_pxe_base_code_packet {
    uint8_t raw[1472];
    struct efi_pxe_base_code_dhcpv4_packet dhcpv4;
    struct efi_pxe_base_code_dhcpv6_packet dhcpv6;
};

// data ends at offset 502; natural alignment makes the size 504.
struct efi_pxe_base_code_icmp_error {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
    union {
        uint32_t reserved;
        uint32_t mtu;
        uint32_t pointer;
        struct {
            uint16_t identifier;
            uint16_t sequence;
        } echo;
    } u;
    uint8_t data[494];
};

struct efi_pxe_base_code_tftp_error {
    uint8_t error_code;
    char error_string[127];
};

#define EFI_PXE_BASE_CODE_MAX_IPCNT 8

struct efi_pxe_base_code_ip_filter {
    uint8_t filters;
    uint8_t ip_cnt;
    uint16_t reserved;
    union efi_ip_address ip_list[EFI_PXE_BASE_CODE_MAX_IPCNT];
};

#define EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP 0x0001
#define EFI_PXE_BASE_CODE_IP_FILTER_BROADCAST 0x0002
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS 0x0004
#define EFI_PXE_BASE_CODE_IP_FILTER_PROMISCUOUS_MULTICAST 0x0008

struct efi_pxe_base_code_arp_entry {
    union efi_ip_address ip_addr;
    struct efi_mac_address mac_addr;
};

struct efi_pxe_base_code_route_entry {
    union efi_ip_address ip_addr;
    union efi_ip_address subnet_mask;
    union efi_ip_address gw_addr;
};

struct efi_pxe_base_code_mode {
    uint8_t started;
    uint8_t ipv6_available;
    uint8_t ipv6_supported;
    uint8_t using_ipv6;
    uint8_t bis_supported;
    uint8_t bis_detected;
    uint8_t auto_arp;
    uint8_t send_guid;
    uint8_t dhcp_discover_valid;
    uint8_t dhcp_ack_received;
    uint8_t proxy_offer_received;
    uint8_t pxe_discover_valid;
    uint8_t pxe_reply_received;
    uint8_t pxe_bis_reply_received;
    uint8_t icmp_error_received;
    uint8_t tftp_error_received;
    uint8_t make_callbacks;
    uint8_t ttl;
    uint8_t tos;
    union efi_ip_address station_ip;
    union efi_ip_address subnet_mask;
    union efi_pxe_base_code_packet dhcp_discover;
    union efi_pxe_base_code_packet dhcp_ack;
    union efi_pxe_base_code_packet proxy_offer;
    union efi_pxe_base_code_packet pxe_discover;
    union efi_pxe_base_code_packet pxe_reply;
    union efi_pxe_base_code_packet pxe_bis_reply;
    struct efi_pxe_base_code_ip_filter ip_filter;
    uint32_t arp_cache_entries;
    struct efi_pxe_base_code_arp_entry arp_cache[EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES];
    uint32_t route_table_entries;
    struct efi_pxe_base_code_route_entry route_table[EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES];
    struct efi_pxe_base_code_icmp_error icmp_error;
    struct efi_pxe_base_code_tftp_error tftp_error;
};

#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP 0x0001
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT 0x0002
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_IP 0x0004
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT 0x0008
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_USE_FILTER 0x0010
#define EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT 0x0020
#define EFI_DEFAULT_TTL 64
#define EFI_DEFAULT_TOS 0

typedef efi_status (EFI_API *efi_pxe_base_code_start)(
    struct efi_pxe_base_code_protocol *self,
    bool use_ipv6
);

typedef efi_status (EFI_API *efi_pxe_base_code_stop)(struct efi_pxe_base_code_protocol *self);

typedef efi_status (EFI_API *efi_pxe_base_code_dhcp)(
    struct efi_pxe_base_code_protocol *self,
    bool sort_offers
);

#define EFI_PXE_BASE_CODE_BOOT_TYPE_BOOTSTRAP 0
#define EFI_PXE_BASE_CODE_BOOT_TYPE_MS_WINNT_RIS 1
#define EFI_PXE_BASE_CODE_BOOT_TYPE_INTEL_LCM 2
#define EFI_PXE_BASE_CODE_BOOT_TYPE_DOSUNDI 3
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NEC_ESMPRO 4
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_WSOD 5
#define EFI_PXE_BASE_CODE_BOOT_TYPE_IBM_LCCM 6
#define EFI_PXE_BASE_CODE_BOOT_TYPE_CA_UNICENTER_TNG 7
#define EFI_PXE_BASE_CODE_BOOT_TYPE_HP_OPENVIEW 8
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_9 9
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_10 10
#define EFI_PXE_BASE_CODE_BOOT_TYPE_ALTIRIS_11 11
#define EFI_PXE_BASE_CODE_BOOT_TYPE_NOT_USED_12 12
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_INSTALL 13
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REDHAT_BOOT 14
#define EFI_PXE_BASE_CODE_BOOT_TYPE_REMBO 15
#define EFI_PXE_BASE_CODE_BOOT_TYPE_BEOBOOT 16
#define EFI_PXE_BASE_CODE_BOOT_TYPE_PXETEST 65535

#define EFI_PXE_BASE_CODE_BOOT_LAYER_MASK 0x7fff
#define EFI_PXE_BASE_CODE_BOOT_LAYER_INITIAL 0x0000

struct efi_pxe_base_code_srvlist {
    uint16_t type;
    uint8_t accept_any_response;
    uint8_t reserved;
    union efi_ip_address ip_addr;
};

// srv_list holds ip_cnt entries (printed srv_list[ip_cnt]).
struct efi_pxe_base_code_discover_info {
    uint8_t use_mcast;
    uint8_t use_bcast;
    uint8_t use_ucast;
    uint8_t must_use_list;
    union efi_ip_address server_mcast_ip;
    uint16_t ip_cnt;
    struct efi_pxe_base_code_srvlist srv_list[1];
};

typedef efi_status (EFI_API *efi_pxe_base_code_discover)(
    struct efi_pxe_base_code_protocol *self,
    uint16_t type,
    uint16_t *layer,
    bool use_bis,
    struct efi_pxe_base_code_discover_info *info
);

#define EFI_PXE_BASE_CODE_TFTP_FIRST ((uint32_t)0)
#define EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE ((uint32_t)1)
#define EFI_PXE_BASE_CODE_TFTP_READ_FILE ((uint32_t)2)
#define EFI_PXE_BASE_CODE_TFTP_WRITE_FILE ((uint32_t)3)
#define EFI_PXE_BASE_CODE_TFTP_READ_DIRECTORY ((uint32_t)4)
#define EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE ((uint32_t)5)
#define EFI_PXE_BASE_CODE_MTFTP_READ_FILE ((uint32_t)6)
#define EFI_PXE_BASE_CODE_MTFTP_READ_DIRECTORY ((uint32_t)7)
#define EFI_PXE_BASE_CODE_MTFTP_LAST ((uint32_t)8)

struct efi_pxe_base_code_mtftp_info {
    union efi_ip_address mcast_ip;
    efi_pxe_base_code_udp_port cport;
    efi_pxe_base_code_udp_port sport;
    uint16_t listen_timeout;
    uint16_t transmit_timeout;
};

typedef efi_status (EFI_API *efi_pxe_base_code_mtftp)(
    struct efi_pxe_base_code_protocol *self,
    uint32_t operation,
    void *buffer_ptr,
    bool overwrite,
    uint64_t *buffer_size,
    size_t *block_size,
    union efi_ip_address *server_ip,
    char *filename,
    struct efi_pxe_base_code_mtftp_info *info,
    bool dont_use_buffer
);

typedef efi_status (EFI_API *efi_pxe_base_code_udp_write)(
    struct efi_pxe_base_code_protocol *self,
    uint16_t op_flags,
    union efi_ip_address *dest_ip,
    efi_pxe_base_code_udp_port *dest_port,
    union efi_ip_address *gateway_ip,
    union efi_ip_address *src_ip,
    efi_pxe_base_code_udp_port *src_port,
    size_t *header_size,
    void *header_ptr,
    size_t *buffer_size,
    void *buffer_ptr
);

typedef efi_status (EFI_API *efi_pxe_base_code_udp_read)(
    struct efi_pxe_base_code_protocol *self,
    uint16_t op_flags,
    union efi_ip_address *dest_ip,
    efi_pxe_base_code_udp_port *dest_port,
    union efi_ip_address *src_ip,
    efi_pxe_base_code_udp_port *src_port,
    size_t *header_size,
    void *header_ptr,
    size_t *buffer_size,
    void *buffer_ptr
);

typedef efi_status (EFI_API *efi_pxe_base_code_set_ip_filter)(
    struct efi_pxe_base_code_protocol *self,
    struct efi_pxe_base_code_ip_filter *new_filter
);

typedef efi_status (EFI_API *efi_pxe_base_code_arp)(
    struct efi_pxe_base_code_protocol *self,
    union efi_ip_address *ip_addr,
    struct efi_mac_address *mac_addr
);

typedef efi_status (EFI_API *efi_pxe_base_code_set_parameters)(
    struct efi_pxe_base_code_protocol *self,
    bool *new_auto_arp,
    bool *new_send_guid,
    uint8_t *new_ttl,
    uint8_t *new_tos,
    bool *new_make_callback
);

typedef efi_status (EFI_API *efi_pxe_base_code_set_station_ip)(
    struct efi_pxe_base_code_protocol *self,
    union efi_ip_address *new_station_ip,
    union efi_ip_address *new_subnet_mask
);

typedef efi_status (EFI_API *efi_pxe_base_code_set_packets)(
    struct efi_pxe_base_code_protocol *self,
    bool *new_dhcp_discover_valid,
    bool *new_dhcp_ack_received,
    bool *new_proxy_offer_received,
    bool *new_pxe_discover_valid,
    bool *new_pxe_reply_received,
    bool *new_pxe_bis_reply_received,
    union efi_pxe_base_code_packet *new_dhcp_discover,
    union efi_pxe_base_code_packet *new_dhcp_ack,
    union efi_pxe_base_code_packet *new_proxy_offer,
    union efi_pxe_base_code_packet *new_pxe_discover,
    union efi_pxe_base_code_packet *new_pxe_reply,
    union efi_pxe_base_code_packet *new_pxe_bis_reply
);

struct efi_pxe_base_code_protocol {
    uint64_t revision;
    efi_pxe_base_code_start start;
    efi_pxe_base_code_stop stop;
    efi_pxe_base_code_dhcp dhcp;
    efi_pxe_base_code_discover discover;
    efi_pxe_base_code_mtftp mtftp;
    efi_pxe_base_code_udp_write udp_write;
    efi_pxe_base_code_udp_read udp_read;
    efi_pxe_base_code_set_ip_filter set_ip_filter;
    efi_pxe_base_code_arp arp;
    efi_pxe_base_code_set_parameters set_parameters;
    efi_pxe_base_code_set_station_ip set_station_ip;
    efi_pxe_base_code_set_packets set_packets;
    struct efi_pxe_base_code_mode *mode;
};

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_GUID \
    {0x245dca21, 0xfb7b, 0x11d3, {0x8f, 0x01, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

#define EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_REVISION 0x00010000

struct efi_pxe_base_code_callback_protocol;

#define EFI_PXE_BASE_CODE_CALLBACK_STATUS_FIRST ((uint32_t)0)
#define EFI_PXE_BASE_CODE_CALLBACK_STATUS_CONTINUE ((uint32_t)1)
#define EFI_PXE_BASE_CODE_CALLBACK_STATUS_ABORT ((uint32_t)2)
#define EFI_PXE_BASE_CODE_CALLBACK_STATUS_LAST ((uint32_t)3)

#define EFI_PXE_BASE_CODE_FUNCTION_FIRST ((uint32_t)0)
#define EFI_PXE_BASE_CODE_FUNCTION_DHCP ((uint32_t)1)
#define EFI_PXE_BASE_CODE_FUNCTION_DISCOVER ((uint32_t)2)
#define EFI_PXE_BASE_CODE_FUNCTION_MTFTP ((uint32_t)3)
#define EFI_PXE_BASE_CODE_FUNCTION_UDP_WRITE ((uint32_t)4)
#define EFI_PXE_BASE_CODE_FUNCTION_UDP_READ ((uint32_t)5)
#define EFI_PXE_BASE_CODE_FUNCTION_ARP ((uint32_t)6)
#define EFI_PXE_BASE_CODE_FUNCTION_IGMP ((uint32_t)7)
#define EFI_PXE_BASE_CODE_PXE_FUNCTION_LAST ((uint32_t)8)

typedef uint32_t (EFI_API *efi_pxe_callback)(
    struct efi_pxe_base_code_callback_protocol *self,
    uint32_t function,
    bool received,
    uint32_t packet_len,
    union efi_pxe_base_code_packet *packet
);

struct efi_pxe_base_code_callback_protocol {
    uint64_t revision;
    efi_pxe_callback callback;
};

#ifdef __cplusplus
}
#endif

#endif
