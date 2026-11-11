#ifndef EFI_EFIISCSI_H_
#define EFI_EFIISCSI_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ISCSI_INITIATOR_NAME_PROTOCOL_GUID \
    {0x59324945, 0xec44, 0x4c0d, {0xb1, 0xcd, 0x9d, 0xb1, 0x39, 0xdf, 0x07, 0x0c}}

struct efi_iscsi_initiator_name_protocol;

typedef EFI_STATUS (EFI_API *EFI_ISCSI_INITIATOR_NAME_GET)(
    struct efi_iscsi_initiator_name_protocol *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_ISCSI_INITIATOR_NAME_SET)(
    struct efi_iscsi_initiator_name_protocol *This,
    size_t *BufferSize,
    void *Buffer
);

struct efi_iscsi_initiator_name_protocol {
    EFI_ISCSI_INITIATOR_NAME_GET Get;
    EFI_ISCSI_INITIATOR_NAME_SET Set;
};

#ifdef __cplusplus
}
#endif

#endif
