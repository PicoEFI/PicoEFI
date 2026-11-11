#ifndef EFI_EFICC_H
#define EFI_EFICC_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CC_MEASUREMENT_PROTOCOL_GUID \
    {0x96751a3d, 0x72f4, 0x41a6, {0xa7, 0x94, 0xed, 0x5d, 0xe, 0x67, 0xae, 0x6b}}

struct efi_cc_measurement_protocol;

struct efi_cc_version {
    uint8_t major;
    uint8_t minor;
};

typedef uint32_t efi_cc_event_log_bitmap;
typedef uint32_t efi_cc_event_algorithm_bitmap;

#define EFI_CC_BOOT_HASH_ALG_SHA384 0x00000004

struct efi_cc_type {
    uint8_t type;
    uint8_t sub_type;
};

#define EFI_CC_TYPE_NONE 0
// Not listed by UEFI 2.11: the value the ACPI CC event log table gives AMD
// SEV.
#define EFI_CC_TYPE_AMD_SEV 1
#define EFI_CC_TYPE_INTEL_TDX 2
#define EFI_CC_TYPE_RISCV_APTEE 3

struct efi_cc_boot_service_capability {
    uint8_t size;
    struct efi_cc_version structure_version;
    struct efi_cc_version protocol_version;
    efi_cc_event_algorithm_bitmap hash_algorithm_bitmap;
    efi_cc_event_log_bitmap supported_event_logs;
    struct efi_cc_type cc_type;
};

typedef efi_status (EFI_API *efi_cc_get_capability)(
    struct efi_cc_measurement_protocol *self,
    struct efi_cc_boot_service_capability *protocol_capability
);

typedef uint32_t efi_cc_event_log_format;

#define EFI_CC_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef efi_status (EFI_API *efi_cc_get_event_log)(
    struct efi_cc_measurement_protocol *self,
    efi_cc_event_log_format event_log_format,
    efi_physical_address *event_log_location,
    efi_physical_address *event_log_last_entry,
    bool *event_log_truncated
);

#define EFI_CC_FLAG_EXTEND_ONLY 0x0000000000000001
#define EFI_CC_FLAG_PE_COFF_IMAGE 0x0000000000000010

typedef uint32_t efi_cc_mr_index;

// Not named by the specification: the value header_version must hold.
#define EFI_CC_EVENT_HEADER_VERSION 1

struct efi_cc_event_header {
    uint32_t header_size;
    uint16_t header_version;
    efi_cc_mr_index mr_index;
    uint32_t event_type;
} __attribute__((__packed__));

// event is variable-length: size covers the whole record.
struct efi_cc_event {
    uint32_t size;
    struct efi_cc_event_header header;
    uint8_t event[1];
} __attribute__((__packed__));

// Printed as a second efi_cc_get_event_log; named as the protocol structure
// types it.
typedef efi_status (EFI_API *efi_cc_hash_log_extend_event)(
    struct efi_cc_measurement_protocol *self,
    uint64_t flags,
    efi_physical_address data_to_hash,
    uint64_t data_to_hash_len,
    struct efi_cc_event *efi_cc_event
);

typedef uint32_t efi_tcg_pcrindex;

typedef efi_status (EFI_API *efi_cc_map_pcr_to_mr_index)(
    struct efi_cc_measurement_protocol *self,
    efi_tcg_pcrindex pcr_index,
    efi_cc_mr_index *mr_index
);

struct efi_cc_measurement_protocol {
    efi_cc_get_capability get_capability;
    efi_cc_get_event_log get_event_log;
    efi_cc_hash_log_extend_event hash_log_extend_event;
    efi_cc_map_pcr_to_mr_index map_pcr_to_mr_index;
};

#define EFI_CC_FINAL_EVENTS_TABLE_GUID \
    {0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}

// number_of_events serialised CC_EVENT records follow; they have no C layout
// (TCG digest lists).
struct efi_cc_final_events_table {
    uint64_t version;
    uint64_t number_of_events;
};

#ifdef __cplusplus
}
#endif

#endif
