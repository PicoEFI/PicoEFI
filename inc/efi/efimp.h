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
    EFI_UINTN *NumberOfProcessors,
    EFI_UINTN *NumberOfEnabledProcessors
);

#define EFI_PROCESSOR_AS_BSP_BIT 0x00000001
#define EFI_PROCESSOR_ENABLED_BIT 0x00000002
#define EFI_PROCESSOR_HEALTH_STATUS_BIT 0x00000004

typedef struct {
    EFI_UINT32 Package;
    EFI_UINT32 Core;
    EFI_UINT32 Thread;
} EFI_CPU_PHYSICAL_LOCATION;

/* Bit 24, printed as BIT24, a macro the specification does not define. */
#define EFI_CPU_V2_EXTENDED_TOPOLOGY 0x01000000

typedef struct {
    EFI_UINT32 Package;
    EFI_UINT32 Module;
    EFI_UINT32 Tile;
    EFI_UINT32 Die;
    EFI_UINT32 Core;
    EFI_UINT32 Thread;
} EFI_CPU_PHYSICAL_LOCATION2;

typedef union {
    EFI_CPU_PHYSICAL_LOCATION2 Location2;
} EFI_EXTENDED_PROCESSOR_INFORMATION;

typedef struct {
    EFI_UINT64 ProcessorId;
    EFI_UINT32 StatusFlag;
    EFI_CPU_PHYSICAL_LOCATION Location;
    EFI_EXTENDED_PROCESSOR_INFORMATION ExtendedInformation;
} EFI_PROCESSOR_INFORMATION;

/*
 * ProcessorNumber is printed as a pointer; it is a number, which EFI_CPU_V2_EXTENDED_TOPOLOGY
 * flags.
 */
typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_GET_PROCESSOR_INFO)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_UINTN ProcessorNumber,
    EFI_PROCESSOR_INFORMATION *ProcessorInfoBuffer
);

#define EFI_END_OF_CPU_LIST 0xffffffff

typedef EFI_VOID (EFI_API *EFI_AP_PROCEDURE)(EFI_VOID *ProcedureArgument);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_ALL_APS)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_AP_PROCEDURE Procedure,
    EFI_BOOLEAN SingleThread,
    EFI_EVENT WaitEvent,
    EFI_UINTN TimeoutInMicroseconds,
    EFI_VOID *ProcedureArgument,
    EFI_UINTN **FailedCpuList
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_STARTUP_THIS_AP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_AP_PROCEDURE Procedure,
    EFI_UINTN ProcessorNumber,
    EFI_EVENT WaitEvent,
    EFI_UINTN TimeoutInMicroseconds,
    EFI_VOID *ProcedureArgument,
    EFI_BOOLEAN *Finished
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_SWITCH_BSP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_UINTN ProcessorNumber,
    EFI_BOOLEAN EnableOldBSP
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_ENABLEDISABLEAP)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_UINTN ProcessorNumber,
    EFI_BOOLEAN EnableAP,
    EFI_UINT32 *HealthFlag
);

typedef EFI_STATUS (EFI_API *EFI_MP_SERVICES_WHOAMI)(
    EFI_MP_SERVICES_PROTOCOL *This,
    EFI_UINTN *ProcessorNumber
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
