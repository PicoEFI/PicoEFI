#ifndef EFI_EFISCSI_H_
#define EFI_EFISCSI_H_

#include "efiapi.h"

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
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    void *SenseData;
    void *Cdb;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    uint8_t CdbLength;
    uint8_t DataDirection;
    uint8_t HostAdapterStatus;
    uint8_t TargetStatus;
    uint8_t SenseDataLength;
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

typedef EFI_STATUS (EFI_API *EFI_SCSI_IO_PROTOCOL_GET_DEVICE_TYPE)(
    struct efi_scsi_io_protocol *This,
    uint8_t *DeviceType
);

typedef EFI_STATUS (EFI_API *EFI_SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION)(
    struct efi_scsi_io_protocol *This,
    uint8_t **Target,
    uint64_t *Lun
);

typedef EFI_STATUS (EFI_API *EFI_SCSI_IO_PROTOCOL_RESET_BUS)(struct efi_scsi_io_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_SCSI_IO_PROTOCOL_RESET_DEVICE)(struct efi_scsi_io_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND)(
    struct efi_scsi_io_protocol *This,
    struct efi_scsi_io_scsi_request_packet *Packet,
    EFI_EVENT Event
);

struct efi_scsi_io_protocol {
    EFI_SCSI_IO_PROTOCOL_GET_DEVICE_TYPE GetDeviceType;
    EFI_SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION GetDeviceLocation;
    EFI_SCSI_IO_PROTOCOL_RESET_BUS ResetBus;
    EFI_SCSI_IO_PROTOCOL_RESET_DEVICE ResetDevice;
    EFI_SCSI_IO_PROTOCOL_EXECUTE_SCSI_COMMAND ExecuteScsiCommand;
    uint32_t IoAlign;
};

#define EFI_EXT_SCSI_PASS_THRU_PROTOCOL_GUID \
    {0x143b7632, 0xb81b, 0x4cb7, {0xab, 0xd3, 0xb6, 0x25, 0xa5, 0xb9, 0xbf, 0xfe}}

struct efi_ext_scsi_pass_thru_protocol;

struct efi_ext_scsi_pass_thru_mode {
    uint32_t AdapterId;
    uint32_t Attributes;
    uint32_t IoAlign;
};

#define EFI_TARGET_MAX_BYTES 0x10
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

struct efi_ext_scsi_pass_thru_scsi_request_packet {
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    void *SenseData;
    void *Cdb;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    uint8_t CdbLength;
    uint8_t DataDirection;
    uint8_t HostAdapterStatus;
    uint8_t TargetStatus;
    uint8_t SenseDataLength;
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

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_PASSTHRU)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    uint8_t *Target,
    uint64_t Lun,
    struct efi_ext_scsi_pass_thru_scsi_request_packet *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    uint8_t **Target,
    uint64_t *Lun
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    uint8_t *Target,
    uint64_t Lun,
    struct efi_device_path_protocol **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    struct efi_device_path_protocol *DevicePath,
    uint8_t **Target,
    uint64_t *Lun
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL)(
    struct efi_ext_scsi_pass_thru_protocol *This
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    uint8_t *Target,
    uint64_t Lun
);

typedef EFI_STATUS (EFI_API *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET)(
    struct efi_ext_scsi_pass_thru_protocol *This,
    uint8_t **Target
);

struct efi_ext_scsi_pass_thru_protocol {
    struct efi_ext_scsi_pass_thru_mode *Mode;
    EFI_EXT_SCSI_PASS_THRU_PASSTHRU PassThru;
    EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN GetNextTargetLun;
    EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN GetTargetLun;
    EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL ResetChannel;
    EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN ResetTargetLun;
    EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET GetNextTarget;
};

#ifdef __cplusplus
}
#endif

#endif
