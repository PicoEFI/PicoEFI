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

typedef struct _EFI_REDFISH_DISCOVER_PROTOCOL EFI_REDFISH_DISCOVER_PROTOCOL;

typedef struct {
    EFI_MAC_ADDRESS MacAddress;
    uint8_t IsIpv6;
    EFI_IP_ADDRESS SubnetId;
    uint8_t SubnetPrefixLength;
    uint16_t VlanId;
} EFI_REDFISH_DISCOVER_NETWORK_INTERFACE;

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_NETWORK_LIST)(
    EFI_REDFISH_DISCOVER_PROTOCOL *This,
    EFI_HANDLE ImageHandle,
    size_t *NumberOfNetworkInterfaces,
    EFI_REDFISH_DISCOVER_NETWORK_INTERFACE **NetworkInterfaces
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

typedef struct {
    EFI_HANDLE RedfishRestExHandle;
    uint8_t IsIPv6;
    EFI_IP_ADDRESS RedfishHostIpAddress;
    uint16_t RedfishVersion;
    uint16_t *Location;
    uint16_t *Uuid;
    uint16_t *Os;
    uint16_t *OsVersion;
    uint16_t *Product;
    uint16_t *ProductVersion;
    uint8_t UseHttps;
} EFI_REDFISH_DISCOVERED_INFORMATION;

typedef struct {
    EFI_STATUS Status;
    EFI_REDFISH_DISCOVERED_INFORMATION Information;
} EFI_REDFISH_DISCOVERED_INSTANCE;

typedef struct {
    size_t NumberOfServiceFound;
    EFI_REDFISH_DISCOVERED_INSTANCE *RedfishInstances;
} EFI_REDFISH_DISCOVERED_LIST;

/* The specification writes SIGNATURE_32, defined nowhere; EFI_SIGNATURE_32 packs the same way. */
#define EFI_REDFISH_DISCOVER_TOKEN_SIGNATURE EFI_SIGNATURE_32('R', 'F', 'T', 'S')

typedef struct {
    uint32_t Signature;
    EFI_REDFISH_DISCOVERED_LIST DiscoveredList;
    EFI_EVENT Event;
    uintptr_t Timeout;
} EFI_REDFISH_DISCOVERED_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE)(
    EFI_REDFISH_DISCOVER_PROTOCOL *This,
    EFI_HANDLE ImageHandle,
    EFI_REDFISH_DISCOVER_NETWORK_INTERFACE *TargetNetworkInterface,
    EFI_REDFISH_DISCOVER_FLAG Flags,
    EFI_REDFISH_DISCOVERED_TOKEN *Token
);

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_ABORT_ACQUIRE)(
    EFI_REDFISH_DISCOVER_PROTOCOL *This,
    EFI_REDFISH_DISCOVER_NETWORK_INTERFACE *TargetNetworkInterface
);

typedef EFI_STATUS (EFI_API *EFI_REDFISH_DISCOVER_RELEASE_SERVICE)(
    EFI_REDFISH_DISCOVER_PROTOCOL *This,
    EFI_REDFISH_DISCOVERED_LIST *List
);

struct _EFI_REDFISH_DISCOVER_PROTOCOL {
    EFI_REDFISH_DISCOVER_NETWORK_LIST GetNetworkInterfaceList;
    EFI_REDFISH_DISCOVER_ACQUIRE_SERVICE AcquireRedfishService;
    EFI_REDFISH_DISCOVER_ABORT_ACQUIRE AbortAcquireRedfishService;
    EFI_REDFISH_DISCOVER_RELEASE_SERVICE ReleaseRedfishService;
};

#ifdef __cplusplus
}
#endif

#endif
