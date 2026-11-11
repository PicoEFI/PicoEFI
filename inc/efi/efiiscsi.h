#ifndef EFI_EFIISCSI_H_
#define EFI_EFIISCSI_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ISCSI_INITIATOR_NAME_PROTOCOL_GUID \
    {0x59324945, 0xec44, 0x4c0d, {0xb1, 0xcd, 0x9d, 0xb1, 0x39, 0xdf, 0x07, 0x0c}}

struct efi_iscsi_initiator_name_protocol;

typedef efi_status (EFI_API *efi_iscsi_initiator_name_get)(
    struct efi_iscsi_initiator_name_protocol *self,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_iscsi_initiator_name_set)(
    struct efi_iscsi_initiator_name_protocol *self,
    size_t *buffer_size,
    void *buffer
);

struct efi_iscsi_initiator_name_protocol {
    efi_iscsi_initiator_name_get get;
    efi_iscsi_initiator_name_set set;
};

#ifdef __cplusplus
}
#endif

#endif
