#ifndef EFI_EFIMP_H_
#define EFI_EFIMP_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MP_SERVICES_PROTOCOL_GUID \
    {0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}}

struct efi_mp_services_protocol;

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS)(
    struct efi_mp_services_protocol *This,
    size_t *NumberOfProcessors,
    size_t *NumberOfEnabledProcessors
);

#define EFI_PROCESSOR_AS_BSP_BIT 0x00000001
#define EFI_PROCESSOR_ENABLED_BIT 0x00000002
#define EFI_PROCESSOR_HEALTH_STATUS_BIT 0x00000004

struct efi_cpu_physical_location {
    uint32_t Package;
    uint32_t Core;
    uint32_t Thread;
};

/* Bit 24, printed as BIT24, a macro the specification does not define. */
#define EFI_CPU_V2_EXTENDED_TOPOLOGY 0x01000000

struct efi_cpu_physical_location2 {
    uint32_t Package;
    uint32_t Module;
    uint32_t Tile;
    uint32_t Die;
    uint32_t Core;
    uint32_t Thread;
};

union efi_extended_processor_information {
    struct efi_cpu_physical_location2 Location2;
};

struct efi_processor_information {
    uint64_t ProcessorId;
    uint32_t StatusFlag;
    struct efi_cpu_physical_location Location;
    union efi_extended_processor_information ExtendedInformation;
};

/*
 * ProcessorNumber is printed as a pointer; it is a number, which EFI_CPU_V2_EXTENDED_TOPOLOGY
 * flags.
 */
typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_GET_PROCESSOR_INFO)(
    struct efi_mp_services_protocol *This,
    size_t ProcessorNumber,
    struct efi_processor_information *ProcessorInfoBuffer
);

#define EFI_END_OF_CPU_LIST 0xffffffff

typedef void (EFI_API *EFI_AP_PROCEDURE)(void *ProcedureArgument);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_ALL_APS)(
    struct efi_mp_services_protocol *This,
    EFI_AP_PROCEDURE Procedure,
    bool SingleThread,
    EFI_EVENT WaitEvent,
    uintptr_t TimeoutInMicroseconds,
    void *ProcedureArgument,
    size_t **FailedCpuList
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_THIS_AP)(
    struct efi_mp_services_protocol *This,
    EFI_AP_PROCEDURE Procedure,
    size_t ProcessorNumber,
    EFI_EVENT WaitEvent,
    uintptr_t TimeoutInMicroseconds,
    void *ProcedureArgument,
    bool *Finished
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_SWITCH_BSP)(
    struct efi_mp_services_protocol *This,
    size_t ProcessorNumber,
    bool EnableOldBSP
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_ENABLEDISABLEAP)(
    struct efi_mp_services_protocol *This,
    size_t ProcessorNumber,
    bool EnableAP,
    uint32_t *HealthFlag
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_WHOAMI)(
    struct efi_mp_services_protocol *This,
    size_t *ProcessorNumber
);

struct efi_mp_services_protocol {
    EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS GetNumberOfProcessors;
    EFI_MP_SERVICES_GET_PROCESSOR_INFO GetProcessorInfo;
    EFI_MP_SERVICES_STARTUP_ALL_APS StartupAllAPs;
    EFI_MP_SERVICES_STARTUP_THIS_AP StartupThisAP;
    EFI_MP_SERVICES_SWITCH_BSP SwitchBSP;
    EFI_MP_SERVICES_ENABLEDISABLEAP EnableDisableAP;
    EFI_MP_SERVICES_WHOAMI WhoAmI;
};

#ifdef __cplusplus
}
#endif

#endif
