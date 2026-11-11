#ifndef EFI_EFIPOINT_H_
#define EFI_EFIPOINT_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
    {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

typedef struct _EFI_SIMPLE_POINTER_PROTOCOL EFI_SIMPLE_POINTER_PROTOCOL;

typedef struct {
    uint64_t ResolutionX;
    uint64_t ResolutionY;
    uint64_t ResolutionZ;
    uint8_t LeftButton;
    uint8_t RightButton;
} EFI_SIMPLE_POINTER_MODE;

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_POINTER_RESET)(
    EFI_SIMPLE_POINTER_PROTOCOL *This,
    bool ExtendedVerification
);

typedef struct {
    int32_t RelativeMovementX;
    int32_t RelativeMovementY;
    int32_t RelativeMovementZ;
    uint8_t LeftButton;
    uint8_t RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_POINTER_GET_STATE)(
    EFI_SIMPLE_POINTER_PROTOCOL *This,
    EFI_SIMPLE_POINTER_STATE *State
);

/* Mode is printed with a nonexistent type; its description names EFI_SIMPLE_POINTER_MODE. */
struct _EFI_SIMPLE_POINTER_PROTOCOL {
    EFI_SIMPLE_POINTER_RESET Reset;
    EFI_SIMPLE_POINTER_GET_STATE GetState;
    EFI_EVENT WaitForInput;
    EFI_SIMPLE_POINTER_MODE *Mode;
};

#define EFI_ABSOLUTE_POINTER_PROTOCOL_GUID \
    {0x8D59D32B, 0xC655, 0x4AE9, {0x9B, 0x15, 0xF2, 0x59, 0x04, 0x99, 0x2A, 0x43}}

typedef struct _EFI_ABSOLUTE_POINTER_PROTOCOL EFI_ABSOLUTE_POINTER_PROTOCOL;

typedef struct {
    uint64_t AbsoluteMinX;
    uint64_t AbsoluteMinY;
    uint64_t AbsoluteMinZ;
    uint64_t AbsoluteMaxX;
    uint64_t AbsoluteMaxY;
    uint64_t AbsoluteMaxZ;
    uint32_t Attributes;
} EFI_ABSOLUTE_POINTER_MODE;

#define EFI_ABSP_SupportsAltActive 0x00000001
#define EFI_ABSP_SupportsPressureAsZ 0x00000002

typedef EFI_STATUS (EFI_API *EFI_ABSOLUTE_POINTER_RESET)(
    EFI_ABSOLUTE_POINTER_PROTOCOL *This,
    bool ExtendedVerification
);

typedef struct {
    uint64_t CurrentX;
    uint64_t CurrentY;
    uint64_t CurrentZ;
    uint32_t ActiveButtons;
} EFI_ABSOLUTE_POINTER_STATE;

/* EFI_ABS_AltActive (not EFI_ABSP_) is the specification's own, consistent spelling. */
#define EFI_ABSP_TouchActive 0x00000001
#define EFI_ABS_AltActive 0x00000002

typedef EFI_STATUS (EFI_API *EFI_ABSOLUTE_POINTER_GET_STATE)(
    EFI_ABSOLUTE_POINTER_PROTOCOL *This,
    EFI_ABSOLUTE_POINTER_STATE *State
);

struct _EFI_ABSOLUTE_POINTER_PROTOCOL {
    EFI_ABSOLUTE_POINTER_RESET Reset;
    EFI_ABSOLUTE_POINTER_GET_STATE GetState;
    EFI_EVENT WaitForInput;
    EFI_ABSOLUTE_POINTER_MODE *Mode;
};

#ifdef __cplusplus
}
#endif

#endif
