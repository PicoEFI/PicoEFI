#ifndef EFI_EFI_NII_H
#define EFI_EFI_NII_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID_31 \
    { 0x1aced566, 0x76ed, 0x4218, { 0xbc, 0x81, 0x76, 0x7f, 0x1f, 0x97, 0x7a, 0x89 } }

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_REVISION 0x00020000

struct efi_network_interface_identifier_protocol {
    uint64_t revision;
    uint64_t id;
    uint64_t image_addr;
    uint32_t image_size;
    char string_id[4];
    uint8_t type;
    uint8_t major_ver;
    uint8_t minor_ver;
    uint8_t ipv6_supported;
    uint16_t if_num;
};

#define EFI_NETWORK_INTERFACE_UNDI ((uint32_t)1)

#ifdef __cplusplus
}
#endif

#endif
