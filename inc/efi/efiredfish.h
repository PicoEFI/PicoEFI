#ifndef EFI_EFIREDFISH_H_
#define EFI_EFIREDFISH_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"
#include "efiarpdhcp.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_REDFISH_DISCOVER_PROTOCOL_GUID \
    {0x5db12509, 0x4550, 0x4347, {0x96, 0xb3, 0x73, 0xc0, 0xff, 0x6e, 0x86, 0x9f}}

struct efi_redfish_discover_protocol;

struct efi_redfish_discover_network_interface {
    struct efi_mac_address mac_address;
    uint8_t is_ipv6;
    union efi_ip_address subnet_id;
    uint8_t subnet_prefix_length;
    uint16_t vlan_id;
};

typedef efi_status (EFI_API *efi_redfish_discover_network_list)(
    struct efi_redfish_discover_protocol *self,
    efi_handle image_handle,
    size_t *number_of_network_interfaces,
    struct efi_redfish_discover_network_interface **network_interfaces
);

/* The specification uses this type and lists its 32-bit flags but prints no definition for it. */
typedef uint32_t efi_redfish_discover_flag;

#define EFI_REDFISH_DISCOVER_HOST_INTERFACE 0x00000001
#define EFI_REDFISH_DISCOVER_SSDP 0x00000002
#define EFI_REDFISH_DISCOVER_SSDP_UDP6 0x00000004
#define EFI_REDFISH_DISCOVER_KEEP_ALIVE 0x00000008
#define EFI_REDFISH_DISCOVER_RENEW 0x00000010
#define EFI_REDFISH_DISCOVER_VALIDATION 0x80000000
#define EFI_REDFISH_DISCOVER_DURATION_MASK 0x0f000000

struct efi_redfish_discovered_information {
    efi_handle redfish_rest_ex_handle;
    uint8_t is_ipv6;
    union efi_ip_address redfish_host_ip_address;
    uint16_t redfish_version;
    uint16_t *location;
    uint16_t *uuid;
    uint16_t *os;
    uint16_t *os_version;
    uint16_t *product;
    uint16_t *product_version;
    uint8_t use_https;
};

struct efi_redfish_discovered_instance {
    efi_status status;
    struct efi_redfish_discovered_information information;
};

struct efi_redfish_discovered_list {
    size_t number_of_service_found;
    struct efi_redfish_discovered_instance *redfish_instances;
};

/* The specification writes SIGNATURE_32, defined nowhere; EFI_SIGNATURE_32 packs the same way. */
#define EFI_REDFISH_DISCOVER_TOKEN_SIGNATURE EFI_SIGNATURE_32('R', 'F', 'T', 'S')

struct efi_redfish_discovered_token {
    uint32_t signature;
    struct efi_redfish_discovered_list discovered_list;
    efi_event event;
    uintptr_t timeout;
};

typedef efi_status (EFI_API *efi_redfish_discover_acquire_service)(
    struct efi_redfish_discover_protocol *self,
    efi_handle image_handle,
    struct efi_redfish_discover_network_interface *target_network_interface,
    efi_redfish_discover_flag flags,
    struct efi_redfish_discovered_token *token
);

typedef efi_status (EFI_API *efi_redfish_discover_abort_acquire)(
    struct efi_redfish_discover_protocol *self,
    struct efi_redfish_discover_network_interface *target_network_interface
);

typedef efi_status (EFI_API *efi_redfish_discover_release_service)(
    struct efi_redfish_discover_protocol *self,
    struct efi_redfish_discovered_list *list
);

struct efi_redfish_discover_protocol {
    efi_redfish_discover_network_list get_network_interface_list;
    efi_redfish_discover_acquire_service acquire_redfish_service;
    efi_redfish_discover_abort_acquire abort_acquire_redfish_service;
    efi_redfish_discover_release_service release_redfish_service;
};

#ifdef __cplusplus
}
#endif

#endif
