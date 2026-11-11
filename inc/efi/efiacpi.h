#ifndef EFI_EFIACPI_H_
#define EFI_EFIACPI_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ACPI_TABLE_PROTOCOL_GUID \
    {0xffe06bdd, 0x6107, 0x46a6, {0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c}}

typedef struct _EFI_ACPI_TABLE_PROTOCOL EFI_ACPI_TABLE_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_ACPI_TABLE_INSTALL_ACPI_TABLE)(
    EFI_ACPI_TABLE_PROTOCOL *This,
    void *AcpiTableBuffer,
    size_t AcpiTableBufferSize,
    uintptr_t *TableKey
);

typedef EFI_STATUS (EFI_API *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE)(
    EFI_ACPI_TABLE_PROTOCOL *This,
    uintptr_t TableKey
);

struct _EFI_ACPI_TABLE_PROTOCOL {
    EFI_ACPI_TABLE_INSTALL_ACPI_TABLE InstallAcpiTable;
    EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE UninstallAcpiTable;
};

/* The specification gives these only as a table, without names. Byte-packed: 36 and 54 bytes. */
typedef struct __attribute__((__packed__)) {
    uint32_t Signature;
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    uint8_t OemId[6];
    uint64_t OemTableId;
    uint32_t OemRevision;
    uint32_t CreatorId;
    uint32_t CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;

/* The table's contents follow at DataOffset. */
typedef struct __attribute__((__packed__)) {
    EFI_ACPI_DESCRIPTION_HEADER Header;
    EFI_GUID Identifier;
    uint16_t DataOffset;
} EFI_ACPI_DATA_TABLE;

/* MessageLength bytes of Data follow the header; the printed ANYSIZE_ARRAY bound becomes 1. */
typedef struct {
    EFI_GUID HeaderGuid;
    size_t MessageLength;
    uint8_t Data[1];
} EFI_SMM_COMMUNICATE_HEADER;

#ifdef __cplusplus
}
#endif

#endif
