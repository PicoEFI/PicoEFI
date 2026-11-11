#ifndef EFI_EFIGPT_H
#define EFI_EFIGPT_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efiapi.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PRIMARY_PART_HEADER_LBA 1
#define EFI_PTAB_HEADER_ID 0x5452415020494645
#define EFI_GPT_PART_ENTRY_MIN_SIZE 16384

// Packed: the header is 92 bytes on disk; natural alignment would pad it to
// 96.
struct efi_partition_table_header {
    struct efi_table_header header;
    efi_lba my_lba;
    efi_lba alternate_lba;
    efi_lba first_usable_lba;
    efi_lba last_usable_lba;
    struct efi_guid disk_guid;
    efi_lba partition_entry_lba;
    uint32_t number_of_partition_entries;
    uint32_t size_of_partition_entry;
    uint32_t partition_entry_array_crc32;
} __attribute__((__packed__));

struct efi_partition_entry {
    struct efi_guid partition_type_guid;
    struct efi_guid unique_partition_guid;
    efi_lba starting_lba;
    efi_lba ending_lba;
    uint64_t attributes;
    uint16_t partition_name[36];
} __attribute__((__packed__));

#define EFI_PART_TYPE_UNUSED_GUID \
    {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}

#define EFI_PART_TYPE_EFI_SYSTEM_PART_GUID \
    {0xC12A7328, 0xF81F, 0x11D2, {0xBA, 0x4B, 0x00, 0xA0, 0xC9, 0x3E, 0xC9, 0x3B}}

#define EFI_PART_TYPE_LEGACY_MBR_GUID \
    {0x024DEE41, 0x33E7, 0x11D3, {0x9D, 0x69, 0x00, 0x08, 0xC7, 0x81, 0xF3, 0x9F}}

#ifdef __cplusplus
}
#endif

#endif
