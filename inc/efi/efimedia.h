#ifndef EFI_EFIMEDIA_H_
#define EFI_EFIMEDIA_H_

#include "efiprot.h"
#include "efipart.h"
#include "efigpt.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_TAPE_IO_PROTOCOL_GUID \
    {0x1e93e633, 0xd65a, 0x459e, {0xab, 0x84, 0x93, 0xd9, 0xec, 0x26, 0x6d, 0x18}}

struct efi_tape_io_protocol;

typedef EFI_STATUS (EFI_API *EFI_TAPE_READ)(
    struct efi_tape_io_protocol *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_WRITE)(
    struct efi_tape_io_protocol *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_REWIND)(struct efi_tape_io_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_TAPE_SPACE)(
    struct efi_tape_io_protocol *This,
    intptr_t Direction,
    uintptr_t Type
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_WRITEFM)(
    struct efi_tape_io_protocol *This,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_RESET)(
    struct efi_tape_io_protocol *This,
    bool ExtendedVerification
);

struct efi_tape_io_protocol {
    EFI_TAPE_READ TapeRead;
    EFI_TAPE_WRITE TapeWrite;
    EFI_TAPE_REWIND TapeRewind;
    EFI_TAPE_SPACE TapeSpace;
    EFI_TAPE_WRITEFM TapeWriteFM;
    EFI_TAPE_RESET TapeReset;
};

struct efi_tape_header {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t BootDescSize;
    uint32_t BootDescCRC;
    struct efi_guid TapeGUID;
    struct efi_guid TapeType;
    struct efi_guid TapeUnique;
    uint32_t BLLocation;
    uint32_t BLBlocksize;
    uint32_t BLFilesize;
    char OSVersion[40];
    char AppVersion[40];
    char CreationDate[10];
    char CreationTime[10];
    char SystemName[256];
    char TapeTitle[120];
    char pad[468];
};

#define EFI_BLOCK_IO_CRYPTO_PROTOCOL_GUID \
    {0xa00490ba, 0x3f1a, 0x4b4c, {0xab, 0x90, 0x4f, 0xa9, 0x97, 0x26, 0xa1, 0xe8}}

struct efi_block_io_crypto_protocol;

struct efi_block_io_crypto_capability {
    struct efi_guid Algorithm;
    uint64_t KeySize;
    uint64_t CryptoBlockSizeBitMask;
};

struct efi_block_io_crypto_iv_input {
    uint64_t InputSize;
};

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS \
    {0x2f87ba6a, 0x5c04, 0x4385, {0xa7, 0x80, 0xf3, 0xbf, 0x78, 0xa9, 0x7b, 0xec}}

struct efi_block_io_crypto_iv_input_aes_xts {
    struct efi_block_io_crypto_iv_input Header;
    uint64_t CryptoBlockNumber;
    uint64_t CryptoBlockByteSize;
};

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER \
    {0x689e4c62, 0x70bf, 0x4cf3, {0x88, 0xbb, 0x33, 0xb3, 0x18, 0x26, 0x86, 0x70}}

struct efi_block_io_crypto_iv_input_aes_cbc_microsoft_bitlocker {
    struct efi_block_io_crypto_iv_input Header;
    uint64_t CryptoBlockByteOffset;
    uint64_t CryptoBlockByteSize;
};

#define EFI_BLOCK_IO_CRYPTO_INDEX_ANY 0xFFFFFFFFFFFFFFFF

struct efi_block_io_crypto_capabilities {
    uint8_t Supported;
    uint64_t KeyCount;
    uint64_t CapabilityCount;
    struct efi_block_io_crypto_capability Capabilities[1];
};

struct efi_block_io_crypto_configuration_table_entry {
    uint64_t Index;
    struct efi_guid KeyOwnerGuid;
    struct efi_block_io_crypto_capability Capability;
    void *CryptoKey;
};

struct efi_block_io_crypto_response_configuration_entry {
    uint64_t Index;
    struct efi_guid KeyOwnerGuid;
    struct efi_block_io_crypto_capability Capability;
};

struct efi_block_io_crypto_token {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
};

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_RESET)(
    struct efi_block_io_crypto_protocol *This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES)(
    struct efi_block_io_crypto_protocol *This,
    struct efi_block_io_crypto_capabilities *Capabilities
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION)(
    struct efi_block_io_crypto_protocol *This,
    uint64_t ConfigurationCount,
    struct efi_block_io_crypto_configuration_table_entry *ConfigurationTable,
    struct efi_block_io_crypto_response_configuration_entry *ResultingTable
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION)(
    struct efi_block_io_crypto_protocol *This,
    uint64_t StartIndex,
    uint64_t ConfigurationCount,
    struct efi_guid *KeyOwnerGuid,
    struct efi_block_io_crypto_response_configuration_entry *ConfigurationTable
);

/* Named as the prototypes name them; the protocol structure prints ..._DEVICE_EXTENDED. */
typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_READ_EXTENDED)(
    struct efi_block_io_crypto_protocol *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    struct efi_block_io_crypto_token *Token,
    uint64_t BufferSize,
    void *Buffer,
    uint64_t *Index,
    void *CryptoIvInput
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED)(
    struct efi_block_io_crypto_protocol *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    struct efi_block_io_crypto_token *Token,
    uint64_t BufferSize,
    void *Buffer,
    uint64_t *Index,
    void *CryptoIvInput
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_FLUSH)(
    struct efi_block_io_crypto_protocol *This,
    struct efi_block_io_crypto_token *Token
);

struct efi_block_io_crypto_protocol {
    struct efi_block_io_media *Media;
    EFI_BLOCK_IO_CRYPTO_RESET Reset;
    EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES GetCapabilities;
    EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION SetConfiguration;
    EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION GetConfiguration;
    EFI_BLOCK_IO_CRYPTO_READ_EXTENDED ReadExtended;
    EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED WriteExtended;
    EFI_BLOCK_IO_CRYPTO_FLUSH FlushBlocks;
};

#define EFI_ERASE_BLOCK_PROTOCOL_GUID \
    {0x95A9A93E, 0xA86E, 0x4926, {0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87}}

#define EFI_ERASE_BLOCK_PROTOCOL_REVISION ((2<<16) | (60))

struct efi_erase_block_protocol;

struct efi_erase_block_token {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
};

/* This is the erase protocol, as described; the prototype prints EFI_BLOCK_IO_PROTOCOL. */
typedef EFI_STATUS (EFI_API *EFI_BLOCK_ERASE)(
    struct efi_erase_block_protocol *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    struct efi_erase_block_token *Token,
    size_t Size
);

struct efi_erase_block_protocol {
    uint64_t Revision;
    uint32_t EraseLengthGranularity;
    EFI_BLOCK_ERASE EraseBlocks;
};

#define EFI_ATA_PASS_THRU_PROTOCOL_GUID \
    {0x1d3de7f0, 0x807, 0x424f, {0xaa, 0x69, 0x11, 0xa5, 0x4e, 0x19, 0xa4, 0x6f}}

struct efi_ata_pass_thru_protocol;

struct efi_ata_pass_thru_mode {
    uint32_t Attributes;
    uint32_t IoAlign;
};

#define EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

struct efi_ata_command_block {
    uint8_t Reserved1[2];
    uint8_t AtaCommand;
    uint8_t AtaFeatures;
    uint8_t AtaSectorNumber;
    uint8_t AtaCylinderLow;
    uint8_t AtaCylinderHigh;
    uint8_t AtaDeviceHead;
    uint8_t AtaSectorNumberExp;
    uint8_t AtaCylinderLowExp;
    uint8_t AtaCylinderHighExp;
    uint8_t AtaFeaturesExp;
    uint8_t AtaSectorCount;
    uint8_t AtaSectorCountExp;
    uint8_t Reserved2[6];
};

struct efi_ata_status_block {
    uint8_t Reserved1[2];
    uint8_t AtaStatus;
    uint8_t AtaError;
    uint8_t AtaSectorNumber;
    uint8_t AtaCylinderLow;
    uint8_t AtaCylinderHigh;
    uint8_t AtaDeviceHead;
    uint8_t AtaSectorNumberExp;
    uint8_t AtaCylinderLowExp;
    uint8_t AtaCylinderHighExp;
    uint8_t Reserved2;
    uint8_t AtaSectorCount;
    uint8_t AtaSectorCountExp;
    uint8_t Reserved3[6];
};

typedef uint8_t EFI_ATA_PASS_THRU_CMD_PROTOCOL;

#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET 0x00
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_SOFTWARE_RESET 0x01
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA 0x02
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN 0x04
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT 0x05
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA 0x06
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA_QUEUED 0x07
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_DIAGNOSTIC 0x08
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_RESET 0x09
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN 0x0A
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT 0x0B
#define EFI_ATA_PASS_THRU_PROTOCOL_FPDMA 0x0C
#define EFI_ATA_PASS_THRU_PROTOCOL_RETURN_RESPONSE 0xFF

typedef uint8_t EFI_ATA_PASS_THRU_LENGTH;

#define EFI_ATA_PASS_THRU_LENGTH_BYTES 0x80

#define EFI_ATA_PASS_THRU_LENGTH_MASK 0x70
#define EFI_ATA_PASS_THRU_LENGTH_NO_DATA_TRANSFER 0x00
#define EFI_ATA_PASS_THRU_LENGTH_FEATURES 0x10
#define EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT 0x20
#define EFI_ATA_PASS_THRU_LENGTH_TPSIU 0x30

#define EFI_ATA_PASS_THRU_LENGTH_COUNT 0x0F

struct efi_ata_pass_thru_command_packet {
    struct efi_ata_status_block *Asb;
    struct efi_ata_command_block *Acb;
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL Protocol;
    EFI_ATA_PASS_THRU_LENGTH Length;
};

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_PASSTHRU)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t Port,
    uint16_t PortMultiplierPort,
    struct efi_ata_pass_thru_command_packet *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_NEXT_PORT)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t *Port
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_NEXT_DEVICE)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t Port,
    uint16_t *PortMultiplierPort
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t Port,
    uint16_t PortMultiplierPort,
    struct efi_device_path_protocol **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_DEVICE)(
    struct efi_ata_pass_thru_protocol *This,
    struct efi_device_path_protocol *DevicePath,
    uint16_t *Port,
    uint16_t *PortMultiplierPort
);

/* Port is the port number, as described and as ResetDevice takes it; printed as a pointer. */
typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_RESET_PORT)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t Port
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_RESET_DEVICE)(
    struct efi_ata_pass_thru_protocol *This,
    uint16_t Port,
    uint16_t PortMultiplierPort
);

struct efi_ata_pass_thru_protocol {
    struct efi_ata_pass_thru_mode *Mode;
    EFI_ATA_PASS_THRU_PASSTHRU PassThru;
    EFI_ATA_PASS_THRU_GET_NEXT_PORT GetNextPort;
    EFI_ATA_PASS_THRU_GET_NEXT_DEVICE GetNextDevice;
    EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_ATA_PASS_THRU_GET_DEVICE GetDevice;
    EFI_ATA_PASS_THRU_RESET_PORT ResetPort;
    EFI_ATA_PASS_THRU_RESET_DEVICE ResetDevice;
};

#define EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID \
    {0xc88b0b6d, 0x0dfc, 0x49a7, {0x9c, 0xb4, 0x49, 0x7, 0x4b, 0x4c, 0x3a, 0x78}}

struct efi_storage_security_command_protocol;

typedef EFI_STATUS (EFI_API *EFI_STORAGE_SECURITY_RECEIVE_DATA)(
    struct efi_storage_security_command_protocol *This,
    uint32_t MediaId,
    uint64_t Timeout,
    uint8_t SecurityProtocolId,
    uint16_t SecurityProtocolSpecificData,
    size_t PayloadBufferSize,
    void *PayloadBuffer,
    size_t *PayloadTransferSize
);

typedef EFI_STATUS (EFI_API *EFI_STORAGE_SECURITY_SEND_DATA)(
    struct efi_storage_security_command_protocol *This,
    uint32_t MediaId,
    uint64_t Timeout,
    uint8_t SecurityProtocolId,
    uint16_t SecurityProtocolSpecificData,
    size_t PayloadBufferSize,
    void *PayloadBuffer
);

struct efi_storage_security_command_protocol {
    EFI_STORAGE_SECURITY_RECEIVE_DATA ReceiveData;
    EFI_STORAGE_SECURITY_SEND_DATA SendData;
};

#define EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID \
    {0x52c78312, 0x8edc, 0x4233, {0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5}}

struct efi_nvm_express_pass_thru_protocol;

struct efi_nvm_express_pass_thru_mode {
    uint32_t Attributes;
    uint32_t IoAlign;
    uint32_t NvmeVersion;
};

#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM 0x0008

struct efi_nvme_cdw0 {
    uint32_t OpCode : 8;
    uint32_t FusedOperation : 2;
    uint32_t Reserved : 22;
};

#define EFI_NORMAL_CMD 0x00
#define EFI_FUSED_FIRST_CMD 0x01
#define EFI_FUSED_SECOND_CMD 0x02

struct efi_nvm_express_command {
    struct efi_nvme_cdw0 Cdw0;
    uint8_t Flags;
    uint32_t Nsid;
    uint32_t Cdw2;
    uint32_t Cdw3;
    uint32_t Cdw10;
    uint32_t Cdw11;
    uint32_t Cdw12;
    uint32_t Cdw13;
    uint32_t Cdw14;
    uint32_t Cdw15;
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
    uint32_t DW0;
    uint32_t DW1;
    uint32_t DW2;
    uint32_t DW3;
};

/* MetadataBuffer as the text and MetadataLength spell it (the structure prints MetaDataBuffer). */
struct efi_nvm_express_pass_thru_command_packet {
    uint64_t CommandTimeout;
    void *TransferBuffer;
    uint32_t TransferLength;
    void *MetadataBuffer;
    uint32_t MetadataLength;
    uint8_t QueueType;
    struct efi_nvm_express_command *NvmeCmd;
    struct efi_nvm_express_completion *NvmeCompletion;
};

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU)(
    struct efi_nvm_express_pass_thru_protocol *This,
    uint32_t NamespaceId,
    struct efi_nvm_express_pass_thru_command_packet *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE)(
    struct efi_nvm_express_pass_thru_protocol *This,
    uint32_t *NamespaceId
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH)(
    struct efi_nvm_express_pass_thru_protocol *This,
    uint32_t NamespaceId,
    struct efi_device_path_protocol **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE)(
    struct efi_nvm_express_pass_thru_protocol *This,
    struct efi_device_path_protocol *DevicePath,
    uint32_t *NamespaceId
);

struct efi_nvm_express_pass_thru_protocol {
    struct efi_nvm_express_pass_thru_mode *Mode;
    EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU PassThru;
    EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE GetNextNamespace;
    EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE GetNamespace;
};

#define EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID \
    {0x716ef0d9, 0xff83, 0x4f69, {0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70}}

struct efi_sd_mmc_pass_thru_protocol;

struct efi_sd_mmc_command_block {
    uint16_t CommandIndex;
    uint32_t CommandArgument;
    uint32_t CommandType;
    uint32_t ResponseType;
};

struct efi_sd_mmc_status_block {
    uint32_t Resp0;
    uint32_t Resp1;
    uint32_t Resp2;
    uint32_t Resp3;
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
    struct efi_sd_mmc_command_block *SdMmcCmdBlk;
    struct efi_sd_mmc_status_block *SdMmcStatusBlk;
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    EFI_STATUS TransactionStatus;
};

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_PASSTHRU)(
    struct efi_sd_mmc_pass_thru_protocol *This,
    uint8_t Slot,
    struct efi_sd_mmc_pass_thru_command_packet *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT)(
    struct efi_sd_mmc_pass_thru_protocol *This,
    uint8_t *Slot
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH)(
    struct efi_sd_mmc_pass_thru_protocol *This,
    uint8_t Slot,
    struct efi_device_path_protocol **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER)(
    struct efi_sd_mmc_pass_thru_protocol *This,
    struct efi_device_path_protocol *DevicePath,
    uint8_t *Slot
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_RESET_DEVICE)(
    struct efi_sd_mmc_pass_thru_protocol *This,
    uint8_t Slot
);

struct efi_sd_mmc_pass_thru_protocol {
    size_t IoAlign;
    EFI_SD_MMC_PASS_THRU_PASSTHRU PassThru;
    EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT GetNextSlot;
    EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER GetSlotNumber;
    EFI_SD_MMC_PASS_THRU_RESET_DEVICE ResetDevice;
};

#define EFI_RAM_DISK_PROTOCOL_GUID \
    {0xab38a0df, 0x6873, 0x44a9, {0x87, 0xe6, 0xd4, 0xeb, 0x56, 0x14, 0x84, 0x49}}

typedef EFI_STATUS (EFI_API *EFI_RAM_DISK_REGISTER_RAMDISK)(
    uint64_t RamDiskBase,
    uint64_t RamDiskSize,
    struct efi_guid *RamDiskType,
    struct efi_device_path_protocol *ParentDevicePath,
    struct efi_device_path_protocol **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_RAM_DISK_UNREGISTER_RAMDISK)(
    struct efi_device_path_protocol *DevicePath
);

struct efi_ram_disk_protocol {
    EFI_RAM_DISK_REGISTER_RAMDISK Register;
    EFI_RAM_DISK_UNREGISTER_RAMDISK Unregister;
};

#define EFI_PARTITION_INFO_PROTOCOL_GUID \
    {0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0}}

/* The value printed (not 0x00010000), which is what firmware puts in Revision. */
#define EFI_PARTITION_INFO_PROTOCOL_REVISION 0x0001000
#define EFI_PARTITION_TYPE_OTHER 0x00
#define EFI_PARTITION_TYPE_MBR 0x01
#define EFI_PARTITION_TYPE_GPT 0x02

struct efi_partition_info_protocol {
    uint32_t Revision;
    uint32_t Type;
    uint8_t System;
    uint8_t Reserved[7];
    union {
        struct efi_mbr_partition_record Mbr;
        struct efi_partition_entry Gpt;
    } Info;
} __attribute__((__packed__));

#define EFI_NVDIMM_LABEL_PROTOCOL_GUID \
    {0xd40b6b80, 0x97d5, 0x4282, {0xbb, 0x1d, 0x22, 0x3a, 0x16, 0x91, 0x80, 0x58}}

struct efi_nvdimm_label_protocol;

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_INFORMATION)(
    struct efi_nvdimm_label_protocol *This,
    uint32_t *SizeOfLabelStorageArea,
    uint32_t *MaxTransferLength
);

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_READ)(
    const struct efi_nvdimm_label_protocol *This,
    uint32_t Offset,
    uint32_t TransferLength,
    uint8_t *LabelData
);

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_WRITE)(
    const struct efi_nvdimm_label_protocol *This,
    uint32_t Offset,
    uint32_t TransferLength,
    uint8_t *LabelData
);

struct efi_nvdimm_label_protocol {
    EFI_NVDIMM_LABEL_STORAGE_INFORMATION LabelStorageInformation;
    EFI_NVDIMM_LABEL_STORAGE_READ LabelStorageRead;
    EFI_NVDIMM_LABEL_STORAGE_WRITE LabelStorageWrite;
};

#define EFI_NVDIMM_LABEL_INDEX_SIG_LEN 16
#define EFI_NVDIMM_LABEL_INDEX_ALIGN 256

__extension__ struct efi_nvdimm_label_index_block {
    char Sig[EFI_NVDIMM_LABEL_INDEX_SIG_LEN];
    uint8_t Flags[3];
    uint8_t LabelSize;
    uint32_t Seq;
    uint64_t MyOff;
    uint64_t MySize;
    uint64_t OtherOff;
    uint64_t LabelOff;
    uint32_t NSlot;
    uint16_t Major;
    uint16_t Minor;
    uint64_t Checksum;
    uint8_t Free[];
};

#define EFI_NVDIMM_LABEL_NAME_LEN 64

/* Flag bits 0x4 and 0x8 are reserved; the text's EFI_NVDIMM_LABEL_FLAGS_UPDATING has no value. */
#define EFI_NVDIMM_LABEL_FLAGS_ROLABEL 0x00000001
#define EFI_NVDIMM_LABEL_FLAGS_LOCAL 0x00000002
#define EFI_NVDIMM_LABEL_FLAGS_SPACOOKIE_BOUND 0x00000010

struct efi_nvdimm_label {
    struct efi_guid Uuid;
    char Name[EFI_NVDIMM_LABEL_NAME_LEN];
    uint32_t Flags;
    uint16_t NLabel;
    uint16_t Position;
    uint64_t SetCookie;
    uint64_t LbaSize;
    uint64_t Dpa;
    uint64_t RawSize;
    uint32_t Slot;
    uint8_t Alignment;
    uint8_t Reserved[3];
    struct efi_guid TypeGuid;
    struct efi_guid AddressAbstractionGuid;
    uint64_t SPALocationCookie;
    uint8_t Reserved1[80];
    uint64_t Checksum;
};

struct efi_nvdimm_label_set_cookie_map {
    uint64_t RegionOffset;
    uint32_t SerialNumber;
    uint16_t VendorId;
    uint16_t ManufacturingDate;
    uint8_t ManufacturingLocation;
    uint8_t Reserved[31];
};

/* One Mapping entry per NVDIMM in the interleave set (the printed bound is not a constant). */
struct efi_nvdimm_label_set_cookie_info {
    struct efi_nvdimm_label_set_cookie_map Mapping[1];
};

#define EFI_UFS_DEVICE_CONFIG_GUID \
    {0xb81bfab0, 0xeb3, 0x4cf9, {0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64}}

struct efi_ufs_device_config_protocol;

/* Descriptor points to the caller's buffer, as described; the prototype prints it by value. */
typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR)(
    struct efi_ufs_device_config_protocol *This,
    bool Read,
    uint8_t DescId,
    uint8_t Index,
    uint8_t Selector,
    uint8_t *Descriptor,
    uint32_t *DescSize
);

typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_FLAG)(
    struct efi_ufs_device_config_protocol *This,
    bool Read,
    uint8_t FlagId,
    uint8_t *Flag
);

typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE)(
    struct efi_ufs_device_config_protocol *This,
    bool Read,
    uint8_t AttrId,
    uint8_t Index,
    uint8_t Selector,
    uint8_t *Attribute,
    uint32_t *AttrSize
);

struct efi_ufs_device_config_protocol {
    EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR RwUfsDescriptor;
    EFI_UFS_DEVICE_CONFIG_RW_FLAG RwUfsFlag;
    EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE RwUfsAttribute;
};

#ifdef __cplusplus
}
#endif

#endif
