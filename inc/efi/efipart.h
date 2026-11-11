#ifndef EFI_EFIPART_H_
#define EFI_EFIPART_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MBR_SIGNATURE 0xAA55
#define EFI_MAX_MBR_PARTITIONS 4
#define EFI_PARTITION 0xEF
#define EFI_PMBR_GPT_PARTITION 0xEE
#define EFI_MBR_SIZE 512

struct efi_mbr_partition_record {
    uint8_t BootIndicator;
    uint8_t StartHead;
    uint8_t StartSector;
    uint8_t StartTrack;
    uint8_t OSIndicator;
    uint8_t EndHead;
    uint8_t EndSector;
    uint8_t EndTrack;
    uint8_t StartingLBA[4];
    uint8_t SizeInLBA[4];
} __attribute__((__packed__));

/* BootStrapCode is 440 bytes, as the C definition and the field offsets require. */
struct efi_master_boot_record {
    uint8_t BootStrapCode[440];
    uint8_t UniqueMbrSignature[4];
    uint8_t Unknown[2];
    struct efi_mbr_partition_record Partition[EFI_MAX_MBR_PARTITIONS];
    uint16_t Signature;
} __attribute__((__packed__));

#ifdef __cplusplus
}
#endif

#endif
