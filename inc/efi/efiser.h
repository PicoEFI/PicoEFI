#ifndef EFI_EFISER_H_
#define EFI_EFISER_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SERIAL_IO_PROTOCOL_GUID \
    {0xBB25CF6F, 0xF1D4, 0x11D2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0xfd}}

#define EFI_SERIAL_IO_PROTOCOL_REVISION 0x00010000
#define EFI_SERIAL_IO_PROTOCOL_REVISION1p1 0x00010001

typedef struct _EFI_SERIAL_IO_PROTOCOL EFI_SERIAL_IO_PROTOCOL;

typedef struct {
    uint32_t ControlMask;
    uint32_t Timeout;
    uint64_t BaudRate;
    uint32_t ReceiveFifoDepth;
    uint32_t DataBits;
    uint32_t Parity;
    uint32_t StopBits;
} EFI_SERIAL_IO_MODE;

typedef enum {
    EfiDefaultParity,
    EfiNoParity,
    EfiEvenParity,
    EfiOddParity,
    EfiMarkParity,
    EfiSpaceParity
} EFI_PARITY_TYPE;

typedef enum {
    EfiDefaultStopBits,
    EfiOneStopBit,
    EfiOneFiveStopBits,
    EfiTwoStopBits
} EFI_STOP_BITS_TYPE;

typedef EFI_STATUS (EFI_API *EFI_SERIAL_RESET)(EFI_SERIAL_IO_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_SERIAL_SET_ATTRIBUTES)(
    EFI_SERIAL_IO_PROTOCOL *This,
    uint64_t BaudRate,
    uint32_t ReceiveFifoDepth,
    uint32_t Timeout,
    EFI_PARITY_TYPE Parity,
    uint8_t DataBits,
    EFI_STOP_BITS_TYPE StopBits
);

#define EFI_SERIAL_CLEAR_TO_SEND 0x0010
#define EFI_SERIAL_DATA_SET_READY 0x0020
#define EFI_SERIAL_RING_INDICATE 0x0040
#define EFI_SERIAL_CARRIER_DETECT 0x0080
#define EFI_SERIAL_REQUEST_TO_SEND 0x0002
#define EFI_SERIAL_DATA_TERMINAL_READY 0x0001
#define EFI_SERIAL_INPUT_BUFFER_EMPTY 0x0100
#define EFI_SERIAL_OUTPUT_BUFFER_EMPTY 0x0200
#define EFI_SERIAL_HARDWARE_LOOPBACK_ENABLE 0x1000
#define EFI_SERIAL_SOFTWARE_LOOPBACK_ENABLE 0x2000
#define EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE 0x4000

typedef EFI_STATUS (EFI_API *EFI_SERIAL_SET_CONTROL_BITS)(
    EFI_SERIAL_IO_PROTOCOL *This,
    uint32_t Control
);

typedef EFI_STATUS (EFI_API *EFI_SERIAL_GET_CONTROL_BITS)(
    EFI_SERIAL_IO_PROTOCOL *This,
    uint32_t *Control
);

typedef EFI_STATUS (EFI_API *EFI_SERIAL_WRITE)(
    EFI_SERIAL_IO_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_SERIAL_READ)(
    EFI_SERIAL_IO_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

struct _EFI_SERIAL_IO_PROTOCOL {
    uint32_t Revision;
    EFI_SERIAL_RESET Reset;
    EFI_SERIAL_SET_ATTRIBUTES SetAttributes;
    EFI_SERIAL_SET_CONTROL_BITS SetControl;
    EFI_SERIAL_GET_CONTROL_BITS GetControl;
    EFI_SERIAL_WRITE Write;
    EFI_SERIAL_READ Read;
    EFI_SERIAL_IO_MODE *Mode;
    /* Present from EFI_SERIAL_IO_PROTOCOL_REVISION1p1 on. */
    const EFI_GUID *DeviceTypeGuid;
};

#define EFI_SERIAL_TERMINAL_DEVICE_TYPE_GUID \
    {0x6ad9a60f, 0x5815, 0x4c7c, {0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b}}

#ifdef __cplusplus
}
#endif

#endif
