#ifndef EFI_EFISCSI_H
#define EFI_EFISCSI_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SCSI_IO_PROTOCOL_GUID \
    {0x932f47e6, 0x2362, 0x4002, {0x80, 0x3e, 0x3c, 0xd5, 0x4b, 0x13, 0x8f, 0x85}}

struct efi_scsi_io_protocol;

#define EFI_SCSI_IO_TYPE_DISK 0x00
#define EFI_SCSI_IO_TYPE_TAPE 0x01
#define EFI_SCSI_IO_TYPE_PRINTER 0x02
#define EFI_SCSI_IO_TYPE_PROCESSOR 0x03
#define EFI_SCSI_IO_TYPE_WORM 0x04
#define EFI_SCSI_IO_TYPE_CDROM 0x05
#define EFI_SCSI_IO_TYPE_SCANNER 0x06
#define EFI_SCSI_IO_TYPE_OPTICAL 0x07
#define EFI_SCSI_IO_TYPE_MEDIUMCHANGER 0x08
#define EFI_SCSI_IO_TYPE_COMMUNICATION 0x09
/* MFI_ (not EFI_) is the specification's own, consistent spelling for 0x0A to 0x11. */
#define EFI_MFI_SCSI_IO_TYPE_A 0x0A
#define EFI_MFI_SCSI_IO_TYPE_B 0x0B
#define EFI_MFI_SCSI_IO_TYPE_RAID 0x0C
#define EFI_MFI_SCSI_IO_TYPE_SES 0x0D
#define EFI_MFI_SCSI_IO_TYPE_RBC 0x0E
#define EFI_MFI_SCSI_IO_TYPE_OCRW 0x0F
#define EFI_MFI_SCSI_IO_TYPE_BRIDGE 0x10
#define EFI_MFI_SCSI_IO_TYPE_OSD 0x11
#define EFI_SCSI_IO_TYPE_RESERVED_LOW 0x12
#define EFI_SCSI_IO_TYPE_RESERVED_HIGH 0x1E
#define EFI_SCSI_IO_TYPE_UNKNOWN 0x1F

struct efi_scsi_io_scsi_request_packet {
    uint64_t timeout;
    void *in_data_buffer;
    void *out_data_buffer;
    void *sense_data;
    void *cdb;
    uint32_t in_transfer_length;
    uint32_t out_transfer_length;
    uint8_t cdb_length;
    uint8_t data_direction;
    uint8_t host_adapter_status;
    uint8_t target_status;
    uint8_t sense_data_length;
};

#define EFI_SCSI_IO_DATA_DIRECTION_READ 0
#define EFI_SCSI_IO_DATA_DIRECTION_WRITE 1
#define EFI_SCSI_IO_DATA_DIRECTION_BIDIRECTIONAL 2

#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_OK 0x00
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND 0x09
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_TIMEOUT 0x0b
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_MESSAGE_REJECT 0x0d
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_BUS_RESET 0x0e
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_PARITY_ERROR 0x0f
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_REQUEST_SENSE_FAILED 0x10
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_SELECTION_TIMEOUT 0x11
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_DATA_OVERRUN_UNDERRUN 0x12
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_BUS_FREE 0x13
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_PHASE_ERROR 0x14
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_OTHER 0x7f

#define EFI_SCSI_IO_STATUS_TARGET_GOOD 0x00
#define EFI_SCSI_IO_STATUS_TARGET_CHECK_CONDITION 0x02
#define EFI_SCSI_IO_STATUS_TARGET_CONDITION_MET 0x04
#define EFI_SCSI_IO_STATUS_TARGET_BUSY 0x08
#define EFI_SCSI_IO_STATUS_TARGET_INTERMEDIATE 0x10
#define EFI_SCSI_IO_STATUS_TARGET_INTERMEDIATE_CONDITION_MET 0x14
#define EFI_SCSI_IO_STATUS_TARGET_RESERVATION_CONFLICT 0x18
#define EFI_SCSI_IO_STATUS_TARGET_COMMAND_TERMINATED 0x22
#define EFI_SCSI_IO_STATUS_TARGET_QUEUE_FULL 0x28

typedef efi_status (EFI_API *efi_scsi_io_protocol_get_device_type)(
    struct efi_scsi_io_protocol *self,
    uint8_t *device_type
);

typedef efi_status (EFI_API *efi_scsi_io_protocol_get_device_location)(
    struct efi_scsi_io_protocol *self,
    uint8_t **target,
    uint64_t *lun
);

typedef efi_status (EFI_API *efi_scsi_io_protocol_reset_bus)(struct efi_scsi_io_protocol *self);

typedef efi_status (EFI_API *efi_scsi_io_protocol_reset_device)(struct efi_scsi_io_protocol *self);

typedef efi_status (EFI_API *efi_scsi_io_protocol_execute_scsi_command)(
    struct efi_scsi_io_protocol *self,
    struct efi_scsi_io_scsi_request_packet *packet,
    efi_event event
);

struct efi_scsi_io_protocol {
    efi_scsi_io_protocol_get_device_type get_device_type;
    efi_scsi_io_protocol_get_device_location get_device_location;
    efi_scsi_io_protocol_reset_bus reset_bus;
    efi_scsi_io_protocol_reset_device reset_device;
    efi_scsi_io_protocol_execute_scsi_command execute_scsi_command;
    uint32_t io_align;
};

#define EFI_EXT_SCSI_PASS_THRU_PROTOCOL_GUID \
    {0x143b7632, 0xb81b, 0x4cb7, {0xab, 0xd3, 0xb6, 0x25, 0xa5, 0xb9, 0xbf, 0xfe}}

struct efi_ext_scsi_pass_thru_protocol;

struct efi_ext_scsi_pass_thru_mode {
    uint32_t adapter_id;
    uint32_t attributes;
    uint32_t io_align;
};

#define EFI_TARGET_MAX_BYTES 0x10
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

struct efi_ext_scsi_pass_thru_scsi_request_packet {
    uint64_t timeout;
    void *in_data_buffer;
    void *out_data_buffer;
    void *sense_data;
    void *cdb;
    uint32_t in_transfer_length;
    uint32_t out_transfer_length;
    uint8_t cdb_length;
    uint8_t data_direction;
    uint8_t host_adapter_status;
    uint8_t target_status;
    uint8_t sense_data_length;
};

#define EFI_EXT_SCSI_DATA_DIRECTION_READ 0
#define EFI_EXT_SCSI_DATA_DIRECTION_WRITE 1
#define EFI_EXT_SCSI_DATA_DIRECTION_BIDIRECTIONAL 2

#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OK 0x00
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND 0x09
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT 0x0b
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_MESSAGE_REJECT 0x0d
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_RESET 0x0e
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PARITY_ERROR 0x0f
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_REQUEST_SENSE_FAILED 0x10
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_SELECTION_TIMEOUT 0x11
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_DATA_OVERRUN_UNDERRUN 0x12
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_FREE 0x13
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PHASE_ERROR 0x14
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OTHER 0x7f

#define EFI_EXT_SCSI_STATUS_TARGET_GOOD 0x00
#define EFI_EXT_SCSI_STATUS_TARGET_CHECK_CONDITION 0x02
#define EFI_EXT_SCSI_STATUS_TARGET_CONDITION_MET 0x04
#define EFI_EXT_SCSI_STATUS_TARGET_BUSY 0x08
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE 0x10
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE_CONDITION_MET 0x14
#define EFI_EXT_SCSI_STATUS_TARGET_RESERVATION_CONFLICT 0x18
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_SET_FULL 0x28
#define EFI_EXT_SCSI_STATUS_TARGET_ACA_ACTIVE 0x30
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_ABORTED 0x40

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_passthru)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    uint8_t *target,
    uint64_t lun,
    struct efi_ext_scsi_pass_thru_scsi_request_packet *packet,
    efi_event event
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_get_next_target_lun)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    uint8_t **target,
    uint64_t *lun
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_build_device_path)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    uint8_t *target,
    uint64_t lun,
    struct efi_device_path_protocol **device_path
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_get_target_lun)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    struct efi_device_path_protocol *device_path,
    uint8_t **target,
    uint64_t *lun
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_reset_channel)(
    struct efi_ext_scsi_pass_thru_protocol *self
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_reset_target_lun)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    uint8_t *target,
    uint64_t lun
);

typedef efi_status (EFI_API *efi_ext_scsi_pass_thru_get_next_target)(
    struct efi_ext_scsi_pass_thru_protocol *self,
    uint8_t **target
);

struct efi_ext_scsi_pass_thru_protocol {
    struct efi_ext_scsi_pass_thru_mode *mode;
    efi_ext_scsi_pass_thru_passthru pass_thru;
    efi_ext_scsi_pass_thru_get_next_target_lun get_next_target_lun;
    efi_ext_scsi_pass_thru_build_device_path build_device_path;
    efi_ext_scsi_pass_thru_get_target_lun get_target_lun;
    efi_ext_scsi_pass_thru_reset_channel reset_channel;
    efi_ext_scsi_pass_thru_reset_target_lun reset_target_lun;
    efi_ext_scsi_pass_thru_get_next_target get_next_target;
};

#ifdef __cplusplus
}
#endif

#endif
