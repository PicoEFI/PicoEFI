#ifndef EFI_EFIACPI_H_
#define EFI_EFIACPI_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ACPI_TABLE_PROTOCOL_GUID \
    {0xffe06bdd, 0x6107, 0x46a6, {0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c}}

struct efi_acpi_table_protocol;

typedef EFI_STATUS (EFI_API *EFI_ACPI_TABLE_INSTALL_ACPI_TABLE)(
    struct efi_acpi_table_protocol *This,
    void *AcpiTableBuffer,
    size_t AcpiTableBufferSize,
    uintptr_t *TableKey
);

typedef EFI_STATUS (EFI_API *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE)(
    struct efi_acpi_table_protocol *This,
    uintptr_t TableKey
);

struct efi_acpi_table_protocol {
    EFI_ACPI_TABLE_INSTALL_ACPI_TABLE InstallAcpiTable;
    EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE UninstallAcpiTable;
};

/* The specification gives these only as a table, without names. Byte-packed: 36 and 54 bytes. */
struct efi_acpi_description_header {
    uint32_t Signature;
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    uint8_t OemId[6];
    uint64_t OemTableId;
    uint32_t OemRevision;
    uint32_t CreatorId;
    uint32_t CreatorRevision;
} __attribute__((__packed__));

/* The table's contents follow at DataOffset. */
struct efi_acpi_data_table {
    struct efi_acpi_description_header Header;
    struct efi_guid Identifier;
    uint16_t DataOffset;
} __attribute__((__packed__));

/* MessageLength bytes of Data follow the header; the printed ANYSIZE_ARRAY bound becomes 1. */
struct efi_smm_communicate_header {
    struct efi_guid HeaderGuid;
    size_t MessageLength;
    uint8_t Data[1];
};

#ifdef __cplusplus
}
#endif

#endif
