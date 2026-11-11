#ifndef EFI_EFIMEDIA_H
#define EFI_EFIMEDIA_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>
#include <efi/efigpt.h>
#include <efi/efipart.h>
#include <efi/efiprot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TAPE_IO_PROTOCOL_GUID \
    { 0x1e93e633, 0xd65a, 0x459e, { 0xab, 0x84, 0x93, 0xd9, 0xec, 0x26, 0x6d, 0x18 } }

struct efi_tape_io_protocol;

typedef efi_status (EFI_API *efi_tape_read)(
    struct efi_tape_io_protocol *self,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_tape_write)(
    struct efi_tape_io_protocol *self,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_tape_rewind)(struct efi_tape_io_protocol *self);

typedef efi_status (EFI_API *efi_tape_space)(
    struct efi_tape_io_protocol *self,
    intptr_t direction,
    size_t type
);

typedef efi_status (EFI_API *efi_tape_writefm)(
    struct efi_tape_io_protocol *self,
    size_t count
);

typedef efi_status (EFI_API *efi_tape_reset)(
    struct efi_tape_io_protocol *self,
    bool extended_verification
);

struct efi_tape_io_protocol {
    efi_tape_read tape_read;
    efi_tape_write tape_write;
    efi_tape_rewind tape_rewind;
    efi_tape_space tape_space;
    efi_tape_writefm tape_write_fm;
    efi_tape_reset tape_reset;
};

struct efi_tape_header {
    uint64_t signature;
    uint32_t revision;
    uint32_t boot_desc_size;
    uint32_t boot_desc_crc;
    struct efi_guid tape_guid;
    struct efi_guid tape_type;
    struct efi_guid tape_unique;
    uint32_t bl_location;
    uint32_t bl_blocksize;
    uint32_t bl_filesize;
    char os_version[40];
    char app_version[40];
    char creation_date[10];
    char creation_time[10];
    char system_name[256];
    char tape_title[120];
    char pad[468];
};

#define EFI_BLOCK_IO_CRYPTO_PROTOCOL_GUID \
    { 0xa00490ba, 0x3f1a, 0x4b4c, { 0xab, 0x90, 0x4f, 0xa9, 0x97, 0x26, 0xa1, 0xe8 } }

struct efi_block_io_crypto_protocol;

struct efi_block_io_crypto_capability {
    struct efi_guid algorithm;
    uint64_t key_size;
    uint64_t crypto_block_size_bit_mask;
};

struct efi_block_io_crypto_iv_input {
    uint64_t input_size;
};

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS \
    { 0x2f87ba6a, 0x5c04, 0x4385, { 0xa7, 0x80, 0xf3, 0xbf, 0x78, 0xa9, 0x7b, 0xec } }

struct efi_block_io_crypto_iv_input_aes_xts {
    struct efi_block_io_crypto_iv_input header;
    uint64_t crypto_block_number;
    uint64_t crypto_block_byte_size;
};

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER \
    { 0x689e4c62, 0x70bf, 0x4cf3, { 0x88, 0xbb, 0x33, 0xb3, 0x18, 0x26, 0x86, 0x70 } }

struct efi_block_io_crypto_iv_input_aes_cbc_microsoft_bitlocker {
    struct efi_block_io_crypto_iv_input header;
    uint64_t crypto_block_byte_offset;
    uint64_t crypto_block_byte_size;
};

#define EFI_BLOCK_IO_CRYPTO_INDEX_ANY 0xffffffffffffffff

struct efi_block_io_crypto_capabilities {
    uint8_t supported;
    uint64_t key_count;
    uint64_t capability_count;
    struct efi_block_io_crypto_capability capabilities[1];
};

struct efi_block_io_crypto_configuration_table_entry {
    uint64_t index;
    struct efi_guid key_owner_guid;
    struct efi_block_io_crypto_capability capability;
    void *crypto_key;
};

struct efi_block_io_crypto_response_configuration_entry {
    uint64_t index;
    struct efi_guid key_owner_guid;
    struct efi_block_io_crypto_capability capability;
};

struct efi_block_io_crypto_token {
    efi_event event;
    efi_status transaction_status;
};

typedef efi_status (EFI_API *efi_block_io_crypto_reset)(
    struct efi_block_io_crypto_protocol *self,
    bool extended_verification
);

typedef efi_status (EFI_API *efi_block_io_crypto_get_capabilities)(
    struct efi_block_io_crypto_protocol *self,
    struct efi_block_io_crypto_capabilities *capabilities
);

typedef efi_status (EFI_API *efi_block_io_crypto_set_configuration)(
    struct efi_block_io_crypto_protocol *self,
    uint64_t configuration_count,
    struct efi_block_io_crypto_configuration_table_entry *configuration_table,
    struct efi_block_io_crypto_response_configuration_entry *resulting_table
);

typedef efi_status (EFI_API *efi_block_io_crypto_get_configuration)(
    struct efi_block_io_crypto_protocol *self,
    uint64_t start_index,
    uint64_t configuration_count,
    struct efi_guid *key_owner_guid,
    struct efi_block_io_crypto_response_configuration_entry *configuration_table
);

// Named as the prototypes name them; the protocol structure prints
// ..._DEVICE_EXTENDED.
typedef efi_status (EFI_API *efi_block_io_crypto_read_extended)(
    struct efi_block_io_crypto_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    struct efi_block_io_crypto_token *token,
    uint64_t buffer_size,
    void *buffer,
    uint64_t *index,
    void *crypto_iv_input
);

typedef efi_status (EFI_API *efi_block_io_crypto_write_extended)(
    struct efi_block_io_crypto_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    struct efi_block_io_crypto_token *token,
    uint64_t buffer_size,
    void *buffer,
    uint64_t *index,
    void *crypto_iv_input
);

typedef efi_status (EFI_API *efi_block_io_crypto_flush)(
    struct efi_block_io_crypto_protocol *self,
    struct efi_block_io_crypto_token *token
);

struct efi_block_io_crypto_protocol {
    struct efi_block_io_media *media;
    efi_block_io_crypto_reset reset;
    efi_block_io_crypto_get_capabilities get_capabilities;
    efi_block_io_crypto_set_configuration set_configuration;
    efi_block_io_crypto_get_configuration get_configuration;
    efi_block_io_crypto_read_extended read_extended;
    efi_block_io_crypto_write_extended write_extended;
    efi_block_io_crypto_flush flush_blocks;
};

#define EFI_ERASE_BLOCK_PROTOCOL_GUID \
    { 0x95a9a93e, 0xa86e, 0x4926, { 0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87 } }

#define EFI_ERASE_BLOCK_PROTOCOL_REVISION ((2 << 16) | (60))

struct efi_erase_block_protocol;

struct efi_erase_block_token {
    efi_event event;
    efi_status transaction_status;
};

// self is the erase protocol, as described; the prototype prints struct
// efi_block_io_protocol.
typedef efi_status (EFI_API *efi_block_erase)(
    struct efi_erase_block_protocol *self,
    uint32_t media_id,
    efi_lba lba,
    struct efi_erase_block_token *token,
    size_t size
);

struct efi_erase_block_protocol {
    uint64_t revision;
    uint32_t erase_length_granularity;
    efi_block_erase erase_blocks;
};

#define EFI_ATA_PASS_THRU_PROTOCOL_GUID \
    { 0x1d3de7f0, 0x807, 0x424f, { 0xaa, 0x69, 0x11, 0xa5, 0x4e, 0x19, 0xa4, 0x6f } }

struct efi_ata_pass_thru_protocol;

struct efi_ata_pass_thru_mode {
    uint32_t attributes;
    uint32_t io_align;
};

#define EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

struct efi_ata_command_block {
    uint8_t reserved1[2];
    uint8_t ata_command;
    uint8_t ata_features;
    uint8_t ata_sector_number;
    uint8_t ata_cylinder_low;
    uint8_t ata_cylinder_high;
    uint8_t ata_device_head;
    uint8_t ata_sector_number_exp;
    uint8_t ata_cylinder_low_exp;
    uint8_t ata_cylinder_high_exp;
    uint8_t ata_features_exp;
    uint8_t ata_sector_count;
    uint8_t ata_sector_count_exp;
    uint8_t reserved2[6];
};

struct efi_ata_status_block {
    uint8_t reserved1[2];
    uint8_t ata_status;
    uint8_t ata_error;
    uint8_t ata_sector_number;
    uint8_t ata_cylinder_low;
    uint8_t ata_cylinder_high;
    uint8_t ata_device_head;
    uint8_t ata_sector_number_exp;
    uint8_t ata_cylinder_low_exp;
    uint8_t ata_cylinder_high_exp;
    uint8_t reserved2;
    uint8_t ata_sector_count;
    uint8_t ata_sector_count_exp;
    uint8_t reserved3[6];
};

typedef uint8_t efi_ata_pass_thru_cmd_protocol;

#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET 0x00
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_SOFTWARE_RESET 0x01
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA 0x02
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN 0x04
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT 0x05
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA 0x06
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA_QUEUED 0x07
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_DIAGNOSTIC 0x08
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_RESET 0x09
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN 0x0a
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT 0x0b
#define EFI_ATA_PASS_THRU_PROTOCOL_FPDMA 0x0c
#define EFI_ATA_PASS_THRU_PROTOCOL_RETURN_RESPONSE 0xff

typedef uint8_t efi_ata_pass_thru_length;

#define EFI_ATA_PASS_THRU_LENGTH_BYTES 0x80

#define EFI_ATA_PASS_THRU_LENGTH_MASK 0x70
#define EFI_ATA_PASS_THRU_LENGTH_NO_DATA_TRANSFER 0x00
#define EFI_ATA_PASS_THRU_LENGTH_FEATURES 0x10
#define EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT 0x20
#define EFI_ATA_PASS_THRU_LENGTH_TPSIU 0x30

#define EFI_ATA_PASS_THRU_LENGTH_COUNT 0x0f

struct efi_ata_pass_thru_command_packet {
    struct efi_ata_status_block *asb;
    struct efi_ata_command_block *acb;
    uint64_t timeout;
    void *in_data_buffer;
    void *out_data_buffer;
    uint32_t in_transfer_length;
    uint32_t out_transfer_length;
    efi_ata_pass_thru_cmd_protocol protocol;
    efi_ata_pass_thru_length length;
};

typedef efi_status (EFI_API *efi_ata_pass_thru_passthru)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t port,
    uint16_t port_multiplier_port,
    struct efi_ata_pass_thru_command_packet *packet,
    efi_event event
);

typedef efi_status (EFI_API *efi_ata_pass_thru_get_next_port)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t *port
);

typedef efi_status (EFI_API *efi_ata_pass_thru_get_next_device)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t port,
    uint16_t *port_multiplier_port
);

typedef efi_status (EFI_API *efi_ata_pass_thru_build_device_path)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t port,
    uint16_t port_multiplier_port,
    struct efi_device_path_protocol **device_path
);

typedef efi_status (EFI_API *efi_ata_pass_thru_get_device)(
    struct efi_ata_pass_thru_protocol *self,
    struct efi_device_path_protocol *device_path,
    uint16_t *port,
    uint16_t *port_multiplier_port
);

// port is the port number, as described and as reset_device takes it; printed
// as a pointer.
typedef efi_status (EFI_API *efi_ata_pass_thru_reset_port)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t port
);

typedef efi_status (EFI_API *efi_ata_pass_thru_reset_device)(
    struct efi_ata_pass_thru_protocol *self,
    uint16_t port,
    uint16_t port_multiplier_port
);

struct efi_ata_pass_thru_protocol {
    struct efi_ata_pass_thru_mode *mode;
    efi_ata_pass_thru_passthru pass_thru;
    efi_ata_pass_thru_get_next_port get_next_port;
    efi_ata_pass_thru_get_next_device get_next_device;
    efi_ata_pass_thru_build_device_path build_device_path;
    efi_ata_pass_thru_get_device get_device;
    efi_ata_pass_thru_reset_port reset_port;
    efi_ata_pass_thru_reset_device reset_device;
};

#define EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID \
    { 0xc88b0b6d, 0x0dfc, 0x49a7, { 0x9c, 0xb4, 0x49, 0x7, 0x4b, 0x4c, 0x3a, 0x78 } }

struct efi_storage_security_command_protocol;

typedef efi_status (EFI_API *efi_storage_security_receive_data)(
    struct efi_storage_security_command_protocol *self,
    uint32_t media_id,
    uint64_t timeout,
    uint8_t security_protocol_id,
    uint16_t security_protocol_specific_data,
    size_t payload_buffer_size,
    void *payload_buffer,
    size_t *payload_transfer_size
);

typedef efi_status (EFI_API *efi_storage_security_send_data)(
    struct efi_storage_security_command_protocol *self,
    uint32_t media_id,
    uint64_t timeout,
    uint8_t security_protocol_id,
    uint16_t security_protocol_specific_data,
    size_t payload_buffer_size,
    void *payload_buffer
);

struct efi_storage_security_command_protocol {
    efi_storage_security_receive_data receive_data;
    efi_storage_security_send_data send_data;
};

#define EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID \
    { 0x52c78312, 0x8edc, 0x4233, { 0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5 } }

struct efi_nvm_express_pass_thru_protocol;

struct efi_nvm_express_pass_thru_mode {
    uint32_t attributes;
    uint32_t io_align;
    uint32_t nvme_version;
};

#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM 0x0008

struct efi_nvme_cdw0 {
    uint32_t cdw0;
};

#define EFI_NVME_CDW0_OP_CODE_SHIFT 0
#define EFI_NVME_CDW0_OP_CODE_MASK 0x000000ff
#define EFI_NVME_CDW0_FUSED_OPERATION_SHIFT 8
#define EFI_NVME_CDW0_FUSED_OPERATION_MASK 0x00000300

#define EFI_NORMAL_CMD 0x00
#define EFI_FUSED_FIRST_CMD 0x01
#define EFI_FUSED_SECOND_CMD 0x02

struct efi_nvm_express_command {
    struct efi_nvme_cdw0 cdw0;
    uint8_t flags;
    uint32_t nsid;
    uint32_t cdw2;
    uint32_t cdw3;
    uint32_t cdw10;
    uint32_t cdw11;
    uint32_t cdw12;
    uint32_t cdw13;
    uint32_t cdw14;
    uint32_t cdw15;
};

#define EFI_CDW2_VALID 0x01
#define EFI_CDW3_VALID 0x02
#define EFI_CDW10_VALID 0x04
#define EFI_CDW11_VALID 0x08
#define EFI_CDW12_VALID 0x10
#define EFI_CDW13_VALID 0x20
#define EFI_CDW14_VALID 0x40
#define EFI_CDW15_VALID 0x80

struct efi_nvm_express_completion {
    uint32_t dw0;
    uint32_t dw1;
    uint32_t dw2;
    uint32_t dw3;
};

// metadata_buffer as the text and metadata_length spell it (the structure
// prints meta_data_buffer).
struct efi_nvm_express_pass_thru_command_packet {
    uint64_t command_timeout;
    void *transfer_buffer;
    uint32_t transfer_length;
    void *metadata_buffer;
    uint32_t metadata_length;
    uint8_t queue_type;
    struct efi_nvm_express_command *nvme_cmd;
    struct efi_nvm_express_completion *nvme_completion;
};

typedef efi_status (EFI_API *efi_nvm_express_pass_thru_passthru)(
    struct efi_nvm_express_pass_thru_protocol *self,
    uint32_t namespace_id,
    struct efi_nvm_express_pass_thru_command_packet *packet,
    efi_event event
);

typedef efi_status (EFI_API *efi_nvm_express_pass_thru_get_next_namespace)(
    struct efi_nvm_express_pass_thru_protocol *self,
    uint32_t *namespace_id
);

typedef efi_status (EFI_API *efi_nvm_express_pass_thru_build_device_path)(
    struct efi_nvm_express_pass_thru_protocol *self,
    uint32_t namespace_id,
    struct efi_device_path_protocol **device_path
);

typedef efi_status (EFI_API *efi_nvm_express_pass_thru_get_namespace)(
    struct efi_nvm_express_pass_thru_protocol *self,
    struct efi_device_path_protocol *device_path,
    uint32_t *namespace_id
);

struct efi_nvm_express_pass_thru_protocol {
    struct efi_nvm_express_pass_thru_mode *mode;
    efi_nvm_express_pass_thru_passthru pass_thru;
    efi_nvm_express_pass_thru_get_next_namespace get_next_namespace;
    efi_nvm_express_pass_thru_build_device_path build_device_path;
    efi_nvm_express_pass_thru_get_namespace get_namespace;
};

#define EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID \
    { 0x716ef0d9, 0xff83, 0x4f69, { 0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70 } }

struct efi_sd_mmc_pass_thru_protocol;

struct efi_sd_mmc_command_block {
    uint16_t command_index;
    uint32_t command_argument;
    uint32_t command_type;
    uint32_t response_type;
};

struct efi_sd_mmc_status_block {
    uint32_t resp0;
    uint32_t resp1;
    uint32_t resp2;
    uint32_t resp3;
};

#define EFI_SD_MMC_COMMAND_TYPE_BC ((uint32_t)0)
#define EFI_SD_MMC_COMMAND_TYPE_BCR ((uint32_t)1)
#define EFI_SD_MMC_COMMAND_TYPE_AC ((uint32_t)2)
#define EFI_SD_MMC_COMMAND_TYPE_ADTC ((uint32_t)3)

#define EFI_SD_MMC_RESPONCE_TYPE_R1 ((uint32_t)0)
#define EFI_SD_MMC_RESPONCE_TYPE_R1B ((uint32_t)1)
#define EFI_SD_MMC_RESPONCE_TYPE_R2 ((uint32_t)2)
#define EFI_SD_MMC_RESPONCE_TYPE_R3 ((uint32_t)3)
#define EFI_SD_MMC_RESPONCE_TYPE_R4 ((uint32_t)4)
#define EFI_SD_MMC_RESPONCE_TYPE_R5 ((uint32_t)5)
#define EFI_SD_MMC_RESPONCE_TYPE_R5B ((uint32_t)6)
#define EFI_SD_MMC_RESPONCE_TYPE_R6 ((uint32_t)7)
#define EFI_SD_MMC_RESPONCE_TYPE_R7 ((uint32_t)8)

struct efi_sd_mmc_pass_thru_command_packet {
    struct efi_sd_mmc_command_block *sd_mmc_cmd_blk;
    struct efi_sd_mmc_status_block *sd_mmc_status_blk;
    uint64_t timeout;
    void *in_data_buffer;
    void *out_data_buffer;
    uint32_t in_transfer_length;
    uint32_t out_transfer_length;
    efi_status transaction_status;
};

typedef efi_status (EFI_API *efi_sd_mmc_pass_thru_passthru)(
    struct efi_sd_mmc_pass_thru_protocol *self,
    uint8_t slot,
    struct efi_sd_mmc_pass_thru_command_packet *packet,
    efi_event event
);

typedef efi_status (EFI_API *efi_sd_mmc_pass_thru_get_next_slot)(
    struct efi_sd_mmc_pass_thru_protocol *self,
    uint8_t *slot
);

typedef efi_status (EFI_API *efi_sd_mmc_pass_thru_build_device_path)(
    struct efi_sd_mmc_pass_thru_protocol *self,
    uint8_t slot,
    struct efi_device_path_protocol **device_path
);

typedef efi_status (EFI_API *efi_sd_mmc_pass_thru_get_slot_number)(
    struct efi_sd_mmc_pass_thru_protocol *self,
    struct efi_device_path_protocol *device_path,
    uint8_t *slot
);

typedef efi_status (EFI_API *efi_sd_mmc_pass_thru_reset_device)(
    struct efi_sd_mmc_pass_thru_protocol *self,
    uint8_t slot
);

struct efi_sd_mmc_pass_thru_protocol {
    size_t io_align;
    efi_sd_mmc_pass_thru_passthru pass_thru;
    efi_sd_mmc_pass_thru_get_next_slot get_next_slot;
    efi_sd_mmc_pass_thru_build_device_path build_device_path;
    efi_sd_mmc_pass_thru_get_slot_number get_slot_number;
    efi_sd_mmc_pass_thru_reset_device reset_device;
};

#define EFI_RAM_DISK_PROTOCOL_GUID \
    { 0xab38a0df, 0x6873, 0x44a9, { 0x87, 0xe6, 0xd4, 0xeb, 0x56, 0x14, 0x84, 0x49 } }

typedef efi_status (EFI_API *efi_ram_disk_register_ramdisk)(
    uint64_t ram_disk_base,
    uint64_t ram_disk_size,
    struct efi_guid *ram_disk_type,
    struct efi_device_path_protocol *parent_device_path,
    struct efi_device_path_protocol **device_path
);

typedef efi_status (EFI_API *efi_ram_disk_unregister_ramdisk)(
    struct efi_device_path_protocol *device_path
);

struct efi_ram_disk_protocol {
    efi_ram_disk_register_ramdisk register_;
    efi_ram_disk_unregister_ramdisk unregister;
};

#define EFI_PARTITION_INFO_PROTOCOL_GUID \
    { 0x8cf2f62c, 0xbc9b, 0x4821, { 0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0 } }

// The value printed (not 0x00010000), which is what firmware puts in revision.
#define EFI_PARTITION_INFO_PROTOCOL_REVISION 0x0001000
#define EFI_PARTITION_TYPE_OTHER 0x00
#define EFI_PARTITION_TYPE_MBR 0x01
#define EFI_PARTITION_TYPE_GPT 0x02

struct efi_partition_info_protocol {
    uint32_t revision;
    uint32_t type;
    uint8_t system;
    uint8_t reserved[7];
    union {
        struct efi_mbr_partition_record mbr;
        struct efi_partition_entry gpt;
    } info;
} __attribute__((__packed__));

#define EFI_NVDIMM_LABEL_PROTOCOL_GUID \
    { 0xd40b6b80, 0x97d5, 0x4282, { 0xbb, 0x1d, 0x22, 0x3a, 0x16, 0x91, 0x80, 0x58 } }

struct efi_nvdimm_label_protocol;

typedef efi_status (EFI_API *efi_nvdimm_label_storage_information)(
    struct efi_nvdimm_label_protocol *self,
    uint32_t *size_of_label_storage_area,
    uint32_t *max_transfer_length
);

typedef efi_status (EFI_API *efi_nvdimm_label_storage_read)(
    const struct efi_nvdimm_label_protocol *self,
    uint32_t offset,
    uint32_t transfer_length,
    uint8_t *label_data
);

typedef efi_status (EFI_API *efi_nvdimm_label_storage_write)(
    const struct efi_nvdimm_label_protocol *self,
    uint32_t offset,
    uint32_t transfer_length,
    uint8_t *label_data
);

struct efi_nvdimm_label_protocol {
    efi_nvdimm_label_storage_information label_storage_information;
    efi_nvdimm_label_storage_read label_storage_read;
    efi_nvdimm_label_storage_write label_storage_write;
};

#define EFI_NVDIMM_LABEL_INDEX_SIG_LEN 16
#define EFI_NVDIMM_LABEL_INDEX_ALIGN 256

__extension__ struct efi_nvdimm_label_index_block {
    char sig[EFI_NVDIMM_LABEL_INDEX_SIG_LEN];
    uint8_t flags[3];
    uint8_t label_size;
    uint32_t seq;
    uint64_t my_off;
    uint64_t my_size;
    uint64_t other_off;
    uint64_t label_off;
    uint32_t nslot;
    uint16_t major;
    uint16_t minor;
    uint64_t checksum;
    uint8_t free[];
};

#define EFI_NVDIMM_LABEL_NAME_LEN 64

// flags bits 0x4 and 0x8 are reserved; the text's
// EFI_NVDIMM_LABEL_FLAGS_UPDATING has no value.
#define EFI_NVDIMM_LABEL_FLAGS_ROLABEL 0x00000001
#define EFI_NVDIMM_LABEL_FLAGS_LOCAL 0x00000002
#define EFI_NVDIMM_LABEL_FLAGS_SPACOOKIE_BOUND 0x00000010

struct efi_nvdimm_label {
    struct efi_guid uuid;
    char name[EFI_NVDIMM_LABEL_NAME_LEN];
    uint32_t flags;
    uint16_t nlabel;
    uint16_t position;
    uint64_t set_cookie;
    uint64_t lba_size;
    uint64_t dpa;
    uint64_t raw_size;
    uint32_t slot;
    uint8_t alignment;
    uint8_t reserved[3];
    struct efi_guid type_guid;
    struct efi_guid address_abstraction_guid;
    uint64_t spa_location_cookie;
    uint8_t reserved1[80];
    uint64_t checksum;
};

struct efi_nvdimm_label_set_cookie_map {
    uint64_t region_offset;
    uint32_t serial_number;
    uint16_t vendor_id;
    uint16_t manufacturing_date;
    uint8_t manufacturing_location;
    uint8_t reserved[31];
};

// One mapping entry per NVDIMM in the interleave set (the printed bound is not
// a constant).
struct efi_nvdimm_label_set_cookie_info {
    struct efi_nvdimm_label_set_cookie_map mapping[1];
};

#define EFI_UFS_DEVICE_CONFIG_GUID \
    { 0xb81bfab0, 0xeb3, 0x4cf9, { 0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64 } }

struct efi_ufs_device_config_protocol;

// descriptor points to the caller's buffer, as described; the prototype prints
// it by value.
typedef efi_status (EFI_API *efi_ufs_device_config_rw_descriptor)(
    struct efi_ufs_device_config_protocol *self,
    bool read,
    uint8_t desc_id,
    uint8_t index,
    uint8_t selector,
    uint8_t *descriptor,
    uint32_t *desc_size
);

typedef efi_status (EFI_API *efi_ufs_device_config_rw_flag)(
    struct efi_ufs_device_config_protocol *self,
    bool read,
    uint8_t flag_id,
    uint8_t *flag
);

typedef efi_status (EFI_API *efi_ufs_device_config_rw_attribute)(
    struct efi_ufs_device_config_protocol *self,
    bool read,
    uint8_t attr_id,
    uint8_t index,
    uint8_t selector,
    uint8_t *attribute,
    uint32_t *attr_size
);

struct efi_ufs_device_config_protocol {
    efi_ufs_device_config_rw_descriptor rw_ufs_descriptor;
    efi_ufs_device_config_rw_flag rw_ufs_flag;
    efi_ufs_device_config_rw_attribute rw_ufs_attribute;
};

#ifdef __cplusplus
}
#endif

#endif
