#ifndef EFI_EFICOMPRESS_H
#define EFI_EFICOMPRESS_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DECOMPRESS_PROTOCOL_GUID \
    { 0xd8117cfe, 0x94a6, 0x11d4, { 0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d } }

struct efi_decompress_protocol;

typedef efi_status (EFI_API *efi_decompress_get_info)(
    struct efi_decompress_protocol *self,
    void *source,
    uint32_t source_size,
    uint32_t *destination_size,
    uint32_t *scratch_size
);

typedef efi_status (EFI_API *efi_decompress_decompress)(
    struct efi_decompress_protocol *self,
    void *source,
    uint32_t source_size,
    void *destination,
    uint32_t destination_size,
    void *scratch,
    uint32_t scratch_size
);

struct efi_decompress_protocol {
    efi_decompress_get_info get_info;
    efi_decompress_decompress decompress;
};

#ifdef __cplusplus
}
#endif

#endif
