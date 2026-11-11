#ifndef EFI_EFI_NII_H_
#define EFI_EFI_NII_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID_31 \
    {0x1ACED566, 0x76ED, 0x4218, {0xBC, 0x81, 0x76, 0x7F, 0x1F, 0x97, 0x7A, 0x89}}

#define EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_REVISION 0x00020000

typedef struct {
    uint64_t Revision;
    uint64_t Id;
    uint64_t ImageAddr;
    uint32_t ImageSize;
    char StringId[4];
    uint8_t Type;
    uint8_t MajorVer;
    uint8_t MinorVer;
    uint8_t Ipv6Supported;
    uint16_t IfNum;
} EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL;

typedef enum {
    EfiNetworkInterfaceUndi = 1
} EFI_NETWORK_INTERFACE_TYPE;

#ifdef __cplusplus
}
#endif

#endif
