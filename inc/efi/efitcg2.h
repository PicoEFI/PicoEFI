#ifndef EFI_EFITCG2_H
#define EFI_EFITCG2_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/eficc.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TCG2_PROTOCOL_GUID \
    {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}}

struct efi_tcg2_protocol;

#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 0x00000001
#define EFI_TCG2_EVENT_LOG_FORMAT_TCG_2 0x00000002

typedef uint32_t efi_tcg2_event_log_bitmap;
typedef uint32_t efi_tcg2_event_log_format;
typedef uint32_t efi_tcg2_event_algorithm_bitmap;

struct efi_tcg2_version {
    uint8_t major;
    uint8_t minor;
};

// Explicitly not packed, unlike the document's other structures: 36 bytes.
struct efi_tcg2_boot_service_capability {
    uint8_t size;
    struct efi_tcg2_version structure_version;
    struct efi_tcg2_version protocol_version;
    efi_tcg2_event_algorithm_bitmap hash_algorithm_bitmap;
    efi_tcg2_event_log_bitmap supported_event_logs;
    uint8_t tpm_present_flag;
    uint16_t max_command_size;
    uint16_t max_response_size;
    uint32_t manufacturer_id;
    uint32_t number_of_pcr_banks;
    efi_tcg2_event_algorithm_bitmap active_pcr_banks;
};

#define EFI_TCG2_BOOT_HASH_ALG_SHA1 0x00000001
#define EFI_TCG2_BOOT_HASH_ALG_SHA256 0x00000002
#define EFI_TCG2_BOOT_HASH_ALG_SHA384 0x00000004
#define EFI_TCG2_BOOT_HASH_ALG_SHA512 0x00000008
#define EFI_TCG2_BOOT_HASH_ALG_SM3_256 0x00000010

typedef efi_status (EFI_API *efi_tcg2_get_capability)(
    struct efi_tcg2_protocol *self,
    struct efi_tcg2_boot_service_capability *protocol_capability
);

typedef efi_status (EFI_API *efi_tcg2_get_event_log)(
    struct efi_tcg2_protocol *self,
    efi_tcg2_event_log_format event_log_format,
    efi_physical_address *event_log_location,
    efi_physical_address *event_log_last_entry,
    bool *event_log_truncated
);

typedef uint32_t efi_tcg_eventtype;

struct efi_tcg2_event_header {
    uint32_t header_size;
    uint16_t header_version;
    efi_tcg_pcrindex pcr_index;
    efi_tcg_eventtype event_type;
} __attribute__((__packed__));

// event is printed as []; it is variable-length, and size covers the whole
// record.
struct efi_tcg2_event {
    uint32_t size;
    struct efi_tcg2_event_header header;
    uint8_t event[1];
} __attribute__((__packed__));

#define EFI_TCG2_EXTEND_ONLY 0x0000000000000001
#define EFI_PE_COFF_IMAGE 0x0000000000000010

typedef efi_status (EFI_API *efi_tcg2_hash_log_extend_event)(
    struct efi_tcg2_protocol *self,
    uint64_t flags,
    efi_physical_address data_to_hash,
    uint64_t data_to_hash_len,
    struct efi_tcg2_event *efi_tcg_event
);

typedef efi_status (EFI_API *efi_tcg2_submit_command)(
    struct efi_tcg2_protocol *self,
    uint32_t input_parameter_block_size,
    uint8_t *input_parameter_block,
    uint32_t output_parameter_block_size,
    uint8_t *output_parameter_block
);

typedef efi_status (EFI_API *efi_tcg2_get_active_pcr_banks)(
    struct efi_tcg2_protocol *self,
    uint32_t *active_pcr_banks
);

typedef efi_status (EFI_API *efi_tcg2_set_active_pcr_banks)(
    struct efi_tcg2_protocol *self,
    uint32_t active_pcr_banks
);

typedef efi_status (EFI_API *efi_tcg2_get_result_of_set_active_pcr_banks)(
    struct efi_tcg2_protocol *self,
    uint32_t *operation_present,
    uint32_t *response
);

struct efi_tcg2_protocol {
    efi_tcg2_get_capability get_capability;
    efi_tcg2_get_event_log get_event_log;
    efi_tcg2_hash_log_extend_event hash_log_extend_event;
    efi_tcg2_submit_command submit_command;
    efi_tcg2_get_active_pcr_banks get_active_pcr_banks;
    efi_tcg2_set_active_pcr_banks set_active_pcr_banks;
    efi_tcg2_get_result_of_set_active_pcr_banks get_result_of_set_active_pcr_banks;
};

#define EFI_TCG2_FINAL_EVENTS_TABLE_GUID \
    {0x1e2ed096, 0x30e2, 0x4254, {0xbd, 0x89, 0x86, 0x3b, 0xbe, 0xf8, 0x23, 0x25}}

// Natural alignment; event starts number_of_events serialised TCG_PCR_EVENT2
// records.
struct efi_tcg2_final_events_table {
    uint64_t version;
    uint64_t number_of_events;
    uint8_t event[1];
};

#define EFI_TCG2_FINAL_EVENTS_TABLE_VERSION 1

#ifdef __cplusplus
}
#endif

#endif
