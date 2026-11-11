#ifndef EFI_EFIPART_H
#define EFI_EFIPART_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MBR_SIGNATURE 0xaa55
#define EFI_MAX_MBR_PARTITIONS 4
#define EFI_PARTITION 0xef
#define EFI_PMBR_GPT_PARTITION 0xee
#define EFI_MBR_SIZE 512

struct efi_mbr_partition_record {
    uint8_t boot_indicator;
    uint8_t start_head;
    uint8_t start_sector;
    uint8_t start_track;
    uint8_t os_indicator;
    uint8_t end_head;
    uint8_t end_sector;
    uint8_t end_track;
    uint8_t starting_lba[4];
    uint8_t size_in_lba[4];
} __attribute__((__packed__));

// boot_strap_code is 440 bytes, as the C definition and the field offsets
// require.
struct efi_master_boot_record {
    uint8_t boot_strap_code[440];
    uint8_t unique_mbr_signature[4];
    uint8_t unknown[2];
    struct efi_mbr_partition_record partition[EFI_MAX_MBR_PARTITIONS];
    uint16_t signature;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
