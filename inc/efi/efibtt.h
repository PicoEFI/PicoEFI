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
    EFI_CHAR8 Sig[EFI_BTT_INFO_BLOCK_SIG_LEN];
    EFI_GUID Uuid;
    EFI_GUID ParentUuid;
    EFI_UINT32 Flags;
    EFI_UINT16 Major;
    EFI_UINT16 Minor;
    EFI_UINT32 ExternalLbaSize;
    EFI_UINT32 ExternalNLba;
    EFI_UINT32 InternalLbaSize;
    EFI_UINT32 InternalNLba;
    EFI_UINT32 NFree;
    EFI_UINT32 InfoSize;
    EFI_UINT64 NextOff;
    EFI_UINT64 DataOff;
    EFI_UINT64 MapOff;
    EFI_UINT64 FlogOff;
    EFI_UINT64 InfoOff;
    EFI_CHAR8 Unused[EFI_BTT_INFO_UNUSED_LEN];
    EFI_UINT64 Checksum;
} EFI_BTT_INFO_BLOCK;

typedef struct _EFI_BTT_MAP_ENTRY {
    EFI_UINT32 PostMapLba : 30;
    EFI_UINT32 Error : 1;
    EFI_UINT32 Zero : 1;
} EFI_BTT_MAP_ENTRY;

#define EFI_BTT_FLOG_ENTRY_ALIGNMENT 64

typedef struct _EFI_BTT_FLOG {
    EFI_UINT32 Lba0;
    EFI_UINT32 OldMap0;
    EFI_UINT32 NewMap0;
    EFI_UINT32 Seq0;
    EFI_UINT32 Lba1;
    EFI_UINT32 OldMap1;
    EFI_UINT32 NewMap1;
    EFI_UINT32 Seq1;
} EFI_BTT_FLOG;

#define EFI_BTT_ABSTRACTION_GUID \
    {0x18633bfc, 0x1735, 0x4217, {0x8a, 0xc9, 0x17, 0x23, 0x92, 0x82, 0xd3, 0xf8}}

#ifdef __cplusplus
}
#endif

#endif
