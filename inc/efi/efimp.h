#ifndef EFI_EFIMP_H_
#define EFI_EFIMP_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_MP_SERVICES_PROTOCOL_GUID \
    {0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}}

typedef struct _EFI_MP_SERVICES_PROTOCOL EFI_MP_SERVICES_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_GET_NUMBER_OF_PROCESSORS)(
    EFI_MP_SERVICES_PROTOCOL *This,
    size_t *NumberOfProcessors,
    size_t *NumberOfEnabledProcessors
);

#define EFI_PROCESSOR_AS_BSP_BIT 0x00000001
#define EFI_PROCESSOR_ENABLED_BIT 0x00000002
#define EFI_PROCESSOR_HEALTH_STATUS_BIT 0x00000004

typedef struct {
    uint32_t Package;
    uint32_t Core;
    uint32_t Thread;
} EFI_CPU_PHYSICAL_LOCATION;

/* Bit 24, printed as BIT24, a macro the specification does not define. */
#define EFI_CPU_V2_EXTENDED_TOPOLOGY 0x01000000

typedef struct {
    uint32_t Package;
    uint32_t Module;
    uint32_t Tile;
    uint32_t Die;
    uint32_t Core;
    uint32_t Thread;
} EFI_CPU_PHYSICAL_LOCATION2;

typedef union {
    EFI_CPU_PHYSICAL_LOCATION2 Location2;
} EFI_EXTENDED_PROCESSOR_INFORMATION;

typedef struct {
    uint64_t ProcessorId;
    uint32_t StatusFlag;
    EFI_CPU_PHYSICAL_LOCATION Location;
    EFI_EXTENDED_PROCESSOR_INFORMATION ExtendedInformation;
} EFI_PROCESSOR_INFORMATION;

/*
 * ProcessorNumber is printed as a pointer; it is a number, which EFI_CPU_V2_EXTENDED_TOPOLOGY
 * flags.
 */
typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_GET_PROCESSOR_INFO)(
    EFI_MP_SERVICES_PROTOCOL *This,
    size_t ProcessorNumber,
    EFI_PROCESSOR_INFORMATION *ProcessorInfoBuffer
);

#define EFI_END_OF_CPU_LIST 0xffffffff

typedef void (EFI_API *EFI_AP_PROCEDURE)(void *ProcedureArgument);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_ALL_APS)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_AP_PROCEDURE Procedure,
    bool SingleThread,
    EFI_EVENT WaitEvent,
    uintptr_t TimeoutInMicroseconds,
    void *ProcedureArgument,
    size_t **FailedCpuList
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_THIS_AP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_AP_PROCEDURE Procedure,
    size_t ProcessorNumber,
    EFI_EVENT WaitEvent,
    uintptr_t TimeoutInMicroseconds,
    void *ProcedureArgument,
    bool *Finished
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_SWITCH_BSP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    size_t ProcessorNumber,
    bool EnableOldBSP
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_ENABLEDISABLEAP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    size_t ProcessorNumber,
    bool EnableAP,
    uint32_t *HealthFlag
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_WHOAMI)(
    EFI_MP_SERVICES_PROTOCOL *This,
    size_t *ProcessorNumber
);

struct _EFI_MP_SERVICES_PROTOCOL {
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
