#ifndef EFI_EFISER_H
#define EFI_EFISER_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SERIAL_IO_PROTOCOL_GUID \
    {0xBB25CF6F, 0xF1D4, 0x11D2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0xfd}}

#define EFI_SERIAL_IO_PROTOCOL_REVISION 0x00010000
#define EFI_SERIAL_IO_PROTOCOL_REVISION1P1 0x00010001

struct efi_serial_io_protocol;

struct efi_serial_io_mode {
    uint32_t control_mask;
    uint32_t timeout;
    uint64_t baud_rate;
    uint32_t receive_fifo_depth;
    uint32_t data_bits;
    uint32_t parity;
    uint32_t stop_bits;
};

#define EFI_DEFAULT_PARITY ((uint32_t)0)
#define EFI_NO_PARITY ((uint32_t)1)
#define EFI_EVEN_PARITY ((uint32_t)2)
#define EFI_ODD_PARITY ((uint32_t)3)
#define EFI_MARK_PARITY ((uint32_t)4)
#define EFI_SPACE_PARITY ((uint32_t)5)

#define EFI_DEFAULT_STOP_BITS ((uint32_t)0)
#define EFI_ONE_STOP_BIT ((uint32_t)1)
#define EFI_ONE_FIVE_STOP_BITS ((uint32_t)2)
#define EFI_TWO_STOP_BITS ((uint32_t)3)

typedef efi_status (EFI_API *efi_serial_reset)(struct efi_serial_io_protocol *self);

typedef efi_status (EFI_API *efi_serial_set_attributes)(
    struct efi_serial_io_protocol *self,
    uint64_t baud_rate,
    uint32_t receive_fifo_depth,
    uint32_t timeout,
    uint32_t parity,
    uint8_t data_bits,
    uint32_t stop_bits
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

typedef efi_status (EFI_API *efi_serial_set_control_bits)(
    struct efi_serial_io_protocol *self,
    uint32_t control
);

typedef efi_status (EFI_API *efi_serial_get_control_bits)(
    struct efi_serial_io_protocol *self,
    uint32_t *control
);

typedef efi_status (EFI_API *efi_serial_write)(
    struct efi_serial_io_protocol *self,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_serial_read)(
    struct efi_serial_io_protocol *self,
    size_t *buffer_size,
    void *buffer
);

struct efi_serial_io_protocol {
    uint32_t revision;
    efi_serial_reset reset;
    efi_serial_set_attributes set_attributes;
    efi_serial_set_control_bits set_control;
    efi_serial_get_control_bits get_control;
    efi_serial_write write;
    efi_serial_read read;
    struct efi_serial_io_mode *mode;
    /* Present from EFI_SERIAL_IO_PROTOCOL_REVISION1P1 on. */
    const struct efi_guid *device_type_guid;
};

#define EFI_SERIAL_TERMINAL_DEVICE_TYPE_GUID \
    {0x6ad9a60f, 0x5815, 0x4c7c, {0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b}}

#ifdef __cplusplus
}
#endif

#endif
