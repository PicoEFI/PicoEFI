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
    EFI_IN EFI_ACPI_TABLE_PROTOCOL *This,
    EFI_IN EFI_VOID *AcpiTableBuffer,
    EFI_IN EFI_UINTN AcpiTableBufferSize,
    EFI_OUT EFI_UINTN *TableKey
);

typedef EFI_STATUS (EFI_API *EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE)(
    EFI_IN EFI_ACPI_TABLE_PROTOCOL *This,
    EFI_IN EFI_UINTN TableKey
);

struct _EFI_ACPI_TABLE_PROTOCOL {
    EFI_ACPI_TABLE_INSTALL_ACPI_TABLE InstallAcpiTable;
    EFI_ACPI_TABLE_UNINSTALL_ACPI_TABLE UninstallAcpiTable;
};

/* The specification gives these only as a table, without names. Byte-packed: 36 and 54 bytes. */
typedef struct __attribute__((__packed__)) {
    EFI_UINT32 Signature;
    EFI_UINT32 Length;
    EFI_UINT8 Revision;
    EFI_UINT8 Checksum;
    EFI_UINT8 OemId[6];
    EFI_UINT64 OemTableId;
    EFI_UINT32 OemRevision;
    EFI_UINT32 CreatorId;
    EFI_UINT32 CreatorRevision;
} EFI_ACPI_DESCRIPTION_HEADER;

/* The table's contents follow at DataOffset. */
typedef struct __attribute__((__packed__)) {
    EFI_ACPI_DESCRIPTION_HEADER Header;
    EFI_GUID Identifier;
    EFI_UINT16 DataOffset;
} EFI_ACPI_DATA_TABLE;

/* MessageLength bytes of Data follow the header; the printed ANYSIZE_ARRAY bound becomes 1. */
typedef struct {
    EFI_GUID HeaderGuid;
    EFI_UINTN MessageLength;
    EFI_UINT8 Data[1];
} EFI_SMM_COMMUNICATE_HEADER;

#ifdef __cplusplus
}
#endif

#endif
