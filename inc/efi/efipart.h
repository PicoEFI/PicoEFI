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

typedef struct __attribute__((__packed__)) {
    EFI_UINT8 BootIndicator;
    EFI_UINT8 StartHead;
    EFI_UINT8 StartSector;
    EFI_UINT8 StartTrack;
    EFI_UINT8 OSIndicator;
    EFI_UINT8 EndHead;
    EFI_UINT8 EndSector;
    EFI_UINT8 EndTrack;
    EFI_UINT8 StartingLBA[4];
    EFI_UINT8 SizeInLBA[4];
} EFI_MBR_PARTITION_RECORD;

/* BootStrapCode is 440 bytes, as the C definition and the field offsets require. */
typedef struct __attribute__((__packed__)) {
    EFI_UINT8 BootStrapCode[440];
    EFI_UINT8 UniqueMbrSignature[4];
    EFI_UINT8 Unknown[2];
    EFI_MBR_PARTITION_RECORD Partition[EFI_MAX_MBR_PARTITIONS];
    EFI_UINT16 Signature;
} EFI_MASTER_BOOT_RECORD;

#ifdef __cplusplus
}
#endif

#endif
