#ifndef EFI_EFICOMPRESS_H_
#define EFI_EFICOMPRESS_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DECOMPRESS_PROTOCOL_GUID \
    {0xd8117cfe, 0x94a6, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

struct efi_decompress_protocol;

typedef EFI_STATUS (EFI_API *EFI_DECOMPRESS_GET_INFO)(
    struct efi_decompress_protocol *This,
    void *Source,
    uint32_t SourceSize,
    uint32_t *DestinationSize,
    uint32_t *ScratchSize
);

typedef EFI_STATUS (EFI_API *EFI_DECOMPRESS_DECOMPRESS)(
    struct efi_decompress_protocol *This,
    void *Source,
    uint32_t SourceSize,
    void *Destination,
    uint32_t DestinationSize,
    void *Scratch,
    uint32_t ScratchSize
);

struct efi_decompress_protocol {
    EFI_DECOMPRESS_GET_INFO GetInfo;
    EFI_DECOMPRESS_DECOMPRESS Decompress;
};

#ifdef __cplusplus
}
#endif

#endif
