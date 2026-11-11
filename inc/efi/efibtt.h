#ifndef EFI_EFIBTT_H_
#define EFI_EFIBTT_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_BTT_ALIGNMENT 4096
#define EFI_BTT_INFO_UNUSED_LEN 3968

#define EFI_BTT_INFO_BLOCK_SIG_LEN 16

#define EFI_BTT_INFO_BLOCK_FLAGS_ERROR 0x00000001

#define EFI_BTT_INFO_BLOCK_MAJOR_VERSION 2
#define EFI_BTT_INFO_BLOCK_MINOR_VERSION 0

typedef struct _EFI_BTT_INFO_BLOCK {
    char Sig[EFI_BTT_INFO_BLOCK_SIG_LEN];
    EFI_GUID Uuid;
    EFI_GUID ParentUuid;
    uint32_t Flags;
    uint16_t Major;
    uint16_t Minor;
    uint32_t ExternalLbaSize;
    uint32_t ExternalNLba;
    uint32_t InternalLbaSize;
    uint32_t InternalNLba;
    uint32_t NFree;
    uint32_t InfoSize;
    uint64_t NextOff;
    uint64_t DataOff;
    uint64_t MapOff;
    uint64_t FlogOff;
    uint64_t InfoOff;
    char Unused[EFI_BTT_INFO_UNUSED_LEN];
    uint64_t Checksum;
} EFI_BTT_INFO_BLOCK;

typedef struct _EFI_BTT_MAP_ENTRY {
    uint32_t PostMapLba : 30;
    uint32_t Error : 1;
    uint32_t Zero : 1;
} EFI_BTT_MAP_ENTRY;

#define EFI_BTT_FLOG_ENTRY_ALIGNMENT 64

typedef struct _EFI_BTT_FLOG {
    uint32_t Lba0;
    uint32_t OldMap0;
    uint32_t NewMap0;
    uint32_t Seq0;
    uint32_t Lba1;
    uint32_t OldMap1;
    uint32_t NewMap1;
    uint32_t Seq1;
} EFI_BTT_FLOG;

#define EFI_BTT_ABSTRACTION_GUID \
    {0x18633bfc, 0x1735, 0x4217, {0x8a, 0xc9, 0x17, 0x23, 0x92, 0x82, 0xd3, 0xf8}}

#ifdef __cplusplus
}
#endif

#endif
