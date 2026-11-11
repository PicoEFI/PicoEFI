#ifndef EFI_EFIACPI_H
#define EFI_EFIACPI_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_ACPI_TABLE_PROTOCOL_GUID \
    { 0xffe06bdd, 0x6107, 0x46a6, { 0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c } }

struct efi_acpi_table_protocol;

typedef efi_status (EFI_API *efi_acpi_table_install_acpi_table)(
    struct efi_acpi_table_protocol *self,
    void *acpi_table_buffer,
    size_t acpi_table_buffer_size,
    size_t *table_key
);

typedef efi_status (EFI_API *efi_acpi_table_uninstall_acpi_table)(
    struct efi_acpi_table_protocol *self,
    size_t table_key
);

struct efi_acpi_table_protocol {
    efi_acpi_table_install_acpi_table install_acpi_table;
    efi_acpi_table_uninstall_acpi_table uninstall_acpi_table;
};

// The specification gives these only as a table, without names. Byte-packed:
// 36 and 54 bytes.
struct efi_acpi_description_header {
    uint32_t signature;
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oem_id[6];
    uint64_t oem_table_id;
    uint32_t oem_revision;
    uint32_t creator_id;
    uint32_t creator_revision;
} __attribute__((__packed__));

// The table's contents follow at data_offset.
struct efi_acpi_data_table {
    struct efi_acpi_description_header header;
    struct efi_guid identifier;
    uint16_t data_offset;
} __attribute__((__packed__));

// message_length bytes of data follow the header; the printed ANYSIZE_ARRAY
// bound becomes 1.
struct efi_smm_communicate_header {
    struct efi_guid header_guid;
    size_t message_length;
    uint8_t data[1];
};

#ifdef __cplusplus
}
#endif

#endif
