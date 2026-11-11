#ifndef EFI_EFIMP_H
#define EFI_EFIMP_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MP_SERVICES_PROTOCOL_GUID \
    {0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}}

struct efi_mp_services_protocol;

typedef efi_status (EFI_API *efi_mp_services_get_number_of_processors)(
    struct efi_mp_services_protocol *self,
    size_t *number_of_processors,
    size_t *number_of_enabled_processors
);

#define EFI_PROCESSOR_AS_BSP_BIT 0x00000001
#define EFI_PROCESSOR_ENABLED_BIT 0x00000002
#define EFI_PROCESSOR_HEALTH_STATUS_BIT 0x00000004

struct efi_cpu_physical_location {
    uint32_t package;
    uint32_t core;
    uint32_t thread;
};

// Bit 24, printed as BIT24, a macro the specification does not define.
#define EFI_CPU_V2_EXTENDED_TOPOLOGY 0x01000000

struct efi_cpu_physical_location2 {
    uint32_t package;
    uint32_t module;
    uint32_t tile;
    uint32_t die;
    uint32_t core;
    uint32_t thread;
};

union efi_extended_processor_information {
    struct efi_cpu_physical_location2 location2;
};

struct efi_processor_information {
    uint64_t processor_id;
    uint32_t status_flag;
    struct efi_cpu_physical_location location;
    union efi_extended_processor_information extended_information;
};

// processor_number is printed as a pointer; it is a number, which
// EFI_CPU_V2_EXTENDED_TOPOLOGY flags.
typedef efi_status (EFI_API *efi_mp_services_get_processor_info)(
    struct efi_mp_services_protocol *self,
    size_t processor_number,
    struct efi_processor_information *processor_info_buffer
);

#define EFI_END_OF_CPU_LIST 0xffffffff

typedef void (EFI_API *efi_ap_procedure)(void *procedure_argument);

typedef efi_status (EFI_API *efi_mp_services_startup_all_aps)(
    struct efi_mp_services_protocol *self,
    efi_ap_procedure procedure,
    bool single_thread,
    efi_event wait_event,
    uintptr_t timeout_in_microseconds,
    void *procedure_argument,
    size_t **failed_cpu_list
);

typedef efi_status (EFI_API *efi_mp_services_startup_this_ap)(
    struct efi_mp_services_protocol *self,
    efi_ap_procedure procedure,
    size_t processor_number,
    efi_event wait_event,
    uintptr_t timeout_in_microseconds,
    void *procedure_argument,
    bool *finished
);

typedef efi_status (EFI_API *efi_mp_services_switch_bsp)(
    struct efi_mp_services_protocol *self,
    size_t processor_number,
    bool enable_old_bsp
);

typedef efi_status (EFI_API *efi_mp_services_enabledisableap)(
    struct efi_mp_services_protocol *self,
    size_t processor_number,
    bool enable_ap,
    uint32_t *health_flag
);

typedef efi_status (EFI_API *efi_mp_services_whoami)(
    struct efi_mp_services_protocol *self,
    size_t *processor_number
);

struct efi_mp_services_protocol {
    efi_mp_services_get_number_of_processors get_number_of_processors;
    efi_mp_services_get_processor_info get_processor_info;
    efi_mp_services_startup_all_aps startup_all_aps;
    efi_mp_services_startup_this_ap startup_this_ap;
    efi_mp_services_switch_bsp switch_bsp;
    efi_mp_services_enabledisableap enable_disable_ap;
    efi_mp_services_whoami who_am_i;
};

#ifdef __cplusplus
}
#endif

#endif
