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
    EFI_UINT64 Revision;
    EFI_UINT64 Id;
    EFI_UINT64 ImageAddr;
    EFI_UINT32 ImageSize;
    EFI_CHAR8 StringId[4];
    EFI_UINT8 Type;
    EFI_UINT8 MajorVer;
    EFI_UINT8 MinorVer;
    EFI_BOOLEAN Ipv6Supported;
    EFI_UINT16 IfNum;
} EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL;

typedef enum {
    EfiNetworkInterfaceUndi = 1
} EFI_NETWORK_INTERFACE_TYPE;

#ifdef __cplusplus
}
#endif

#endif
