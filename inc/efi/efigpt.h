#ifndef EFI_EFIGPT_H_
#define EFI_EFIGPT_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_PRIMARY_PART_HEADER_LBA 1
#define EFI_PTAB_HEADER_ID 0x5452415020494645
#define EFI_GPT_PART_ENTRY_MIN_SIZE 16384

/* Packed: the header is 92 bytes on disk; natural alignment would pad it to 96. */
typedef struct __attribute__((__packed__)) {
    EFI_TABLE_HEADER Header;
    EFI_LBA MyLBA;
    EFI_LBA AlternateLBA;
    EFI_LBA FirstUsableLBA;
    EFI_LBA LastUsableLBA;
    EFI_GUID DiskGUID;
    EFI_LBA PartitionEntryLBA;
    EFI_UINT32 NumberOfPartitionEntries;
    EFI_UINT32 SizeOfPartitionEntry;
    EFI_UINT32 PartitionEntryArrayCRC32;
} EFI_PARTITION_TABLE_HEADER;

typedef struct __attribute__((__packed__)) {
    EFI_GUID PartitionTypeGUID;
    EFI_GUID UniquePartitionGUID;
    EFI_LBA StartingLBA;
    EFI_LBA EndingLBA;
    EFI_UINT64 Attributes;
    EFI_CHAR16 PartitionName[36];
} EFI_PARTITION_ENTRY;

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
