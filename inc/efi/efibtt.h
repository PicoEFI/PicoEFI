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

struct efi_btt_info_block {
    char sig[EFI_BTT_INFO_BLOCK_SIG_LEN];
    struct efi_guid uuid;
    struct efi_guid parent_uuid;
    uint32_t flags;
    uint16_t major;
    uint16_t minor;
    uint32_t external_lba_size;
    uint32_t external_nlba;
    uint32_t internal_lba_size;
    uint32_t internal_nlba;
    uint32_t nfree;
    uint32_t info_size;
    uint64_t next_off;
    uint64_t data_off;
    uint64_t map_off;
    uint64_t flog_off;
    uint64_t info_off;
    char unused[EFI_BTT_INFO_UNUSED_LEN];
    uint64_t checksum;
};

struct efi_btt_map_entry {
    uint32_t post_map_lba : 30;
    uint32_t error : 1;
    uint32_t zero : 1;
};

#define EFI_BTT_FLOG_ENTRY_ALIGNMENT 64

struct efi_btt_flog {
    uint32_t lba0;
    uint32_t old_map0;
    uint32_t new_map0;
    uint32_t seq0;
    uint32_t lba1;
    uint32_t old_map1;
    uint32_t new_map1;
    uint32_t seq1;
};

#define EFI_BTT_ABSTRACTION_GUID \
    {0x18633bfc, 0x1735, 0x4217, {0x8a, 0xc9, 0x17, 0x23, 0x92, 0x82, 0xd3, 0xf8}}

#ifdef __cplusplus
}
#endif

#endif
