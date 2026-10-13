#ifndef EFI_EFICOMPRESS_H_
#define EFI_EFICOMPRESS_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DECOMPRESS_PROTOCOL_GUID \
    {0xd8117cfe, 0x94a6, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

typedef struct _EFI_DECOMPRESS_PROTOCOL EFI_DECOMPRESS_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_DECOMPRESS_GET_INFO)(
    EFI_IN EFI_DECOMPRESS_PROTOCOL *This,
    EFI_IN EFI_VOID *Source,
    EFI_IN EFI_UINT32 SourceSize,
    EFI_OUT EFI_UINT32 *DestinationSize,
    EFI_OUT EFI_UINT32 *ScratchSize
);

typedef EFI_STATUS (EFI_API *EFI_DECOMPRESS_DECOMPRESS)(
    EFI_IN EFI_DECOMPRESS_PROTOCOL *This,
    EFI_IN EFI_VOID *Source,
    EFI_IN EFI_UINT32 SourceSize,
    EFI_IN EFI_OUT EFI_VOID *Destination,
    EFI_IN EFI_UINT32 DestinationSize,
    EFI_IN EFI_OUT EFI_VOID *Scratch,
    EFI_IN EFI_UINT32 ScratchSize
);

struct _EFI_DECOMPRESS_PROTOCOL {
    EFI_DECOMPRESS_GET_INFO GetInfo;
    EFI_DECOMPRESS_DECOMPRESS Decompress;
};

#ifdef __cplusplus
}
#endif

#endif
