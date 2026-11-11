#ifndef EFI_EFINET_H
#define EFI_EFINET_H 1

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

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID \
    { 0xa19832b9, 0xac25, 0x11d3, { 0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION 0x00010000

struct efi_simple_network_protocol;

#define EFI_SIMPLE_NETWORK_STOPPED ((uint32_t)0)
#define EFI_SIMPLE_NETWORK_STARTED ((uint32_t)1)
#define EFI_SIMPLE_NETWORK_INITIALIZED ((uint32_t)2)
#define EFI_SIMPLE_NETWORK_MAX_STATE ((uint32_t)3)

#define EFI_MAX_MCAST_FILTER_CNT 16

struct efi_simple_network_mode {
    uint32_t state;
    uint32_t hw_address_size;
    uint32_t media_header_size;
    uint32_t max_packet_size;
    uint32_t nv_ram_size;
    uint32_t nv_ram_access_size;
    uint32_t receive_filter_mask;
    uint32_t receive_filter_setting;
    uint32_t max_mcast_filter_count;
    uint32_t mcast_filter_count;
    struct efi_mac_address mcast_filter[EFI_MAX_MCAST_FILTER_CNT];
    struct efi_mac_address current_address;
    struct efi_mac_address broadcast_address;
    struct efi_mac_address permanent_address;
    uint8_t if_type;
    uint8_t mac_address_changeable;
    uint8_t multiple_tx_supported;
    uint8_t media_present_supported;
    uint8_t media_present;
};

#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST 0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST 0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST 0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS 0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

typedef efi_status (EFI_API *efi_simple_network_start)(struct efi_simple_network_protocol *self);

typedef efi_status (EFI_API *efi_simple_network_stop)(struct efi_simple_network_protocol *self);

typedef efi_status (EFI_API *efi_simple_network_initialize)(
    struct efi_simple_network_protocol *self,
    size_t extra_rx_buffer_size,
    size_t extra_tx_buffer_size
);

typedef efi_status (EFI_API *efi_simple_network_reset)(
    struct efi_simple_network_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_simple_network_shutdown)(
    struct efi_simple_network_protocol *self
);

// mcast_filter points to a list, as described; the prototype prints it by
// value.
typedef efi_status (EFI_API *efi_simple_network_receive_filters)(
    struct efi_simple_network_protocol *self,
    uint32_t enable,
    uint32_t disable,
    bool reset_mcast_filter,
    size_t mcast_filter_cnt,
    struct efi_mac_address *mcast_filter
);

typedef efi_status (EFI_API *efi_simple_network_station_address)(
    struct efi_simple_network_protocol *self,
    bool reset,
#ifdef __cplusplus
    struct efi_mac_address *new_
#else
    struct efi_mac_address *new
#endif
);

struct efi_network_statistics {
    uint64_t rx_total_frames;
    uint64_t rx_good_frames;
    uint64_t rx_undersize_frames;
    uint64_t rx_oversize_frames;
    uint64_t rx_dropped_frames;
    uint64_t rx_unicast_frames;
    uint64_t rx_broadcast_frames;
    uint64_t rx_multicast_frames;
    uint64_t rx_crc_error_frames;
    uint64_t rx_total_bytes;
    uint64_t tx_total_frames;
    uint64_t tx_good_frames;
    uint64_t tx_undersize_frames;
    uint64_t tx_oversize_frames;
    uint64_t tx_dropped_frames;
    uint64_t tx_unicast_frames;
    uint64_t tx_broadcast_frames;
    uint64_t tx_multicast_frames;
    uint64_t tx_crc_error_frames;
    uint64_t tx_total_bytes;
    uint64_t collisions;
    uint64_t unsupported_protocol;
    uint64_t rx_duplicated_frames;
    uint64_t rx_decrypt_error_frames;
    uint64_t tx_error_frames;
    uint64_t tx_retry_frames;
};

typedef efi_status (EFI_API *efi_simple_network_statistics)(
    struct efi_simple_network_protocol *self,
    bool reset,
    size_t *statistics_size,
    struct efi_network_statistics *statistics_table
);

typedef efi_status (EFI_API *efi_simple_network_mcast_ip_to_mac)(
    struct efi_simple_network_protocol *self,
    bool ipv6,
    union efi_ip_address *ip,
    struct efi_mac_address *mac
);

typedef efi_status (EFI_API *efi_simple_network_nvdata)(
    struct efi_simple_network_protocol *self,
    bool read_write,
    size_t offset,
    size_t buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_simple_network_get_status)(
    struct efi_simple_network_protocol *self,
    uint32_t *interrupt_status,
    void **tx_buf
);

#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT 0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT 0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT 0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT 0x08

typedef efi_status (EFI_API *efi_simple_network_transmit)(
    struct efi_simple_network_protocol *self,
    size_t header_size,
    size_t buffer_size,
    void *buffer,
    struct efi_mac_address *src_addr,
    struct efi_mac_address *dest_addr,
    uint16_t *protocol
);

typedef efi_status (EFI_API *efi_simple_network_receive)(
    struct efi_simple_network_protocol *self,
    size_t *header_size,
    size_t *buffer_size,
    void *buffer,
    struct efi_mac_address *src_addr,
    struct efi_mac_address *dest_addr,
    uint16_t *protocol
);

struct efi_simple_network_protocol {
    uint64_t revision;
    efi_simple_network_start start;
    efi_simple_network_stop stop;
    efi_simple_network_initialize initialize;
    efi_simple_network_reset reset;
    efi_simple_network_shutdown shutdown;
    efi_simple_network_receive_filters receive_filters;
    efi_simple_network_station_address station_address;
    efi_simple_network_statistics statistics;
    efi_simple_network_mcast_ip_to_mac mcast_ip_to_mac;
    efi_simple_network_nvdata nv_data;
    efi_simple_network_get_status get_status;
    efi_simple_network_transmit transmit;
    efi_simple_network_receive receive;
    efi_event wait_for_packet;
    struct efi_simple_network_mode *mode;
};

#ifdef __cplusplus
}
#endif

#endif
