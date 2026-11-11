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
    struct efi_mac_address MacAddress;
    uint8_t IsIpv6;
    union efi_ip_address SubnetId;
    uint8_t SubnetPrefixLength;
    uint16_t VlanId;
};

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_NETWORK_LIST)(
    struct efi_redfish_discover_protocol *This,
    EFI_HANDLE ImageHandle,
    size_t *NumberOfNetworkInterfaces,
    struct efi_redfish_discover_network_interface **NetworkInterfaces
);

/* The specification uses this type and lists its 32-bit flags but prints no definition for it. */
typedef uint32_t EFI_REDFISH_DISCOVER_FLAG;

#define EFI_REDFISH_DISCOVER_HOST_INTERFACE 0x00000001
#define EFI_REDFISH_DISCOVER_SSDP 0x00000002
#define EFI_REDFISH_DISCOVER_SSDP_UDP6 0x00000004
#define EFI_REDFISH_DISCOVER_KEEP_ALIVE 0x00000008
#define EFI_REDFISH_DISCOVER_RENEW 0x00000010
#define EFI_REDFISH_DISCOVER_VALIDATION 0x80000000
#define EFI_REDFISH_DISCOVER_DURATION_MASK 0x0f000000

struct efi_redfish_discovered_information {
    EFI_HANDLE RedfishRestExHandle;
    uint8_t IsIPv6;
    union efi_ip_address RedfishHostIpAddress;
    uint16_t RedfishVersion;
    uint16_t *Location;
    uint16_t *Uuid;
    uint16_t *Os;
    uint16_t *OsVersion;
    uint16_t *Product;
    uint16_t *ProductVersion;
    uint8_t UseHttps;
};

struct efi_redfish_discovered_instance {
    EFI_STATUS Status;
    struct efi_redfish_discovered_information Information;
};

struct efi_redfish_discovered_list {
    size_t NumberOfServiceFound;
    struct efi_redfish_discovered_instance *RedfishInstances;
};

/* The specification writes SIGNATURE_32, defined nowhere; EFI_SIGNATURE_32 packs the same way. */
#define EFI_REDFISH_DISCOVER_TOKEN_SIGNATURE EFI_SIGNATURE_32('R', 'F', 'T', 'S')

struct efi_redfish_discovered_token {
    uint32_t Signature;
    struct efi_redfish_discovered_list DiscoveredList;
    EFI_EVENT Event;
    uintptr_t Timeout;
};

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE)(
    struct efi_redfish_discover_protocol *This,
    EFI_HANDLE ImageHandle,
    struct efi_redfish_discover_network_interface *TargetNetworkInterface,
    EFI_REDFISH_DISCOVER_FLAG Flags,
    struct efi_redfish_discovered_token *Token
);

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_ABORT_ACQUIRE)(
    struct efi_redfish_discover_protocol *This,
    struct efi_redfish_discover_network_interface *TargetNetworkInterface
);

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_RELEASE_SERVICE)(
    struct efi_redfish_discover_protocol *This,
    struct efi_redfish_discovered_list *List
);

struct efi_redfish_discover_protocol {
    EFI_REDFISH_DISCOVER_NETWORK_LIST GetNetworkInterfaceList;
    EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE AcquireRedfishService;
    EFI_REDFISH_DISCOVER_ABORT_ACQUIRE AbortAcquireRedfishService;
    EFI_REDFISH_DISCOVER_RELEASE_SERVICE ReleaseRedfishService;
};

#ifdef __cplusplus
}
#endif

#endif
