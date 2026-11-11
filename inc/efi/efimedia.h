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

typedef struct _EFI_TAPE_IO_PROTOCOL EFI_TAPE_IO_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_TAPE_READ)(
    EFI_TAPE_IO_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_WRITE)(
    EFI_TAPE_IO_PROTOCOL *This,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_REWIND)(EFI_TAPE_IO_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_TAPE_SPACE)(
    EFI_TAPE_IO_PROTOCOL *This,
    intptr_t Direction,
    uintptr_t Type
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_WRITEFM)(
    EFI_TAPE_IO_PROTOCOL *This,
    size_t Count
);

typedef EFI_STATUS (EFI_API *EFI_TAPE_RESET)(
    EFI_TAPE_IO_PROTOCOL *This,
    bool ExtendedVerification
);

struct _EFI_TAPE_IO_PROTOCOL {
    EFI_TAPE_READ TapeRead;
    EFI_TAPE_WRITE TapeWrite;
    EFI_TAPE_REWIND TapeRewind;
    EFI_TAPE_SPACE TapeSpace;
    EFI_TAPE_WRITEFM TapeWriteFM;
    EFI_TAPE_RESET TapeReset;
};

typedef struct EFI_TAPE_HEADER {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t BootDescSize;
    uint32_t BootDescCRC;
    EFI_GUID TapeGUID;
    EFI_GUID TapeType;
    EFI_GUID TapeUnique;
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
} EFI_TAPE_HEADER;

#define EFI_BLOCK_IO_CRYPTO_PROTOCOL_GUID \
    {0xa00490ba, 0x3f1a, 0x4b4c, {0xab, 0x90, 0x4f, 0xa9, 0x97, 0x26, 0xa1, 0xe8}}

typedef struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL EFI_BLOCK_IO_CRYPTO_PROTOCOL;

typedef struct {
    EFI_GUID Algorithm;
    uint64_t KeySize;
    uint64_t CryptoBlockSizeBitMask;
} EFI_BLOCK_IO_CRYPTO_CAPABILITY;

typedef struct {
    uint64_t InputSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT;

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS \
    {0x2f87ba6a, 0x5c04, 0x4385, {0xa7, 0x80, 0xf3, 0xbf, 0x78, 0xa9, 0x7b, 0xec}}

typedef struct {
    EFI_BLOCK_IO_CRYPTO_IV_INPUT Header;
    uint64_t CryptoBlockNumber;
    uint64_t CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_XTS;

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER \
    {0x689e4c62, 0x70bf, 0x4cf3, {0x88, 0xbb, 0x33, 0xb3, 0x18, 0x26, 0x86, 0x70}}

typedef struct {
    EFI_BLOCK_IO_CRYPTO_IV_INPUT Header;
    uint64_t CryptoBlockByteOffset;
    uint64_t CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_CBC_MICROSOFT_BITLOCKER;

#define EFI_BLOCK_IO_CRYPTO_INDEX_ANY 0xFFFFFFFFFFFFFFFF

typedef struct {
    uint8_t Supported;
    uint64_t KeyCount;
    uint64_t CapabilityCount;
    EFI_BLOCK_IO_CRYPTO_CAPABILITY Capabilities[1];
} EFI_BLOCK_IO_CRYPTO_CAPABILITIES;

typedef struct {
    uint64_t Index;
    EFI_GUID KeyOwnerGuid;
    EFI_BLOCK_IO_CRYPTO_CAPABILITY Capability;
    void *CryptoKey;
} EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY;

typedef struct {
    uint64_t Index;
    EFI_GUID KeyOwnerGuid;
    EFI_BLOCK_IO_CRYPTO_CAPABILITY Capability;
} EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
} EFI_BLOCK_IO_CRYPTO_TOKEN;

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_RESET)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    EFI_BLOCK_IO_CRYPTO_CAPABILITIES *Capabilities
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    uint64_t ConfigurationCount,
    EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY *ConfigurationTable,
    EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ResultingTable
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    uint64_t StartIndex,
    uint64_t ConfigurationCount,
    EFI_GUID *KeyOwnerGuid,
    EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable
);

/* Named as the prototypes name them; the protocol structure prints ..._DEVICE_EXTENDED. */
typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_READ_EXTENDED)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    EFI_BLOCK_IO_CRYPTO_TOKEN *Token,
    uint64_t BufferSize,
    void *Buffer,
    uint64_t *Index,
    void *CryptoIvInput
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    EFI_BLOCK_IO_CRYPTO_TOKEN *Token,
    uint64_t BufferSize,
    void *Buffer,
    uint64_t *Index,
    void *CryptoIvInput
);

typedef EFI_STATUS (EFI_API *EFI_BLOCK_IO_CRYPTO_FLUSH)(
    EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
    EFI_BLOCK_IO_CRYPTO_TOKEN *Token
);

struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL {
    EFI_BLOCK_IO_MEDIA *Media;
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

typedef struct _EFI_ERASE_BLOCK_PROTOCOL EFI_ERASE_BLOCK_PROTOCOL;

typedef struct {
    EFI_EVENT Event;
    EFI_STATUS TransactionStatus;
} EFI_ERASE_BLOCK_TOKEN;

/* This is the erase protocol, as described; the prototype prints EFI_BLOCK_IO_PROTOCOL. */
typedef EFI_STATUS (EFI_API *EFI_BLOCK_ERASE)(
    EFI_ERASE_BLOCK_PROTOCOL *This,
    uint32_t MediaId,
    EFI_LBA LBA,
    EFI_ERASE_BLOCK_TOKEN *Token,
    size_t Size
);

struct _EFI_ERASE_BLOCK_PROTOCOL {
    uint64_t Revision;
    uint32_t EraseLengthGranularity;
    EFI_BLOCK_ERASE EraseBlocks;
};

#define EFI_ATA_PASS_THRU_PROTOCOL_GUID \
    {0x1d3de7f0, 0x807, 0x424f, {0xaa, 0x69, 0x11, 0xa5, 0x4e, 0x19, 0xa4, 0x6f}}

typedef struct _EFI_ATA_PASS_THRU_PROTOCOL EFI_ATA_PASS_THRU_PROTOCOL;

typedef struct {
    uint32_t Attributes;
    uint32_t IoAlign;
} EFI_ATA_PASS_THRU_MODE;

#define EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

typedef struct _EFI_ATA_COMMAND_BLOCK {
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
} EFI_ATA_COMMAND_BLOCK;

typedef struct _EFI_ATA_STATUS_BLOCK {
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
} EFI_ATA_STATUS_BLOCK;

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

typedef struct {
    EFI_ATA_STATUS_BLOCK *Asb;
    EFI_ATA_COMMAND_BLOCK *Acb;
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    EFI_ATA_PASS_THRU_CMD_PROTOCOL Protocol;
    EFI_ATA_PASS_THRU_LENGTH Length;
} EFI_ATA_PASS_THRU_COMMAND_PACKET;

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_PASSTHRU)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t Port,
    uint16_t PortMultiplierPort,
    EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_NEXT_PORT)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t *Port
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_NEXT_DEVICE)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t Port,
    uint16_t *PortMultiplierPort
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t Port,
    uint16_t PortMultiplierPort,
    EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_GET_DEVICE)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    uint16_t *Port,
    uint16_t *PortMultiplierPort
);

/* Port is the port number, as described and as ResetDevice takes it; printed as a pointer. */
typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_RESET_PORT)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t Port
);

typedef EFI_STATUS (EFI_API *EFI_ATA_PASS_THRU_RESET_DEVICE)(
    EFI_ATA_PASS_THRU_PROTOCOL *This,
    uint16_t Port,
    uint16_t PortMultiplierPort
);

struct _EFI_ATA_PASS_THRU_PROTOCOL {
    EFI_ATA_PASS_THRU_MODE *Mode;
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

typedef struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL EFI_STORAGE_SECURITY_COMMAND_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_STORAGE_SECURITY_RECEIVE_DATA)(
    EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Timeout,
    uint8_t SecurityProtocolId,
    uint16_t SecurityProtocolSpecificData,
    size_t PayloadBufferSize,
    void *PayloadBuffer,
    size_t *PayloadTransferSize
);

typedef EFI_STATUS (EFI_API *EFI_STORAGE_SECURITY_SEND_DATA)(
    EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
    uint32_t MediaId,
    uint64_t Timeout,
    uint8_t SecurityProtocolId,
    uint16_t SecurityProtocolSpecificData,
    size_t PayloadBufferSize,
    void *PayloadBuffer
);

struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL {
    EFI_STORAGE_SECURITY_RECEIVE_DATA ReceiveData;
    EFI_STORAGE_SECURITY_SEND_DATA SendData;
};

#define EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID \
    {0x52c78312, 0x8edc, 0x4233, {0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5}}

typedef struct _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL;

typedef struct {
    uint32_t Attributes;
    uint32_t IoAlign;
    uint32_t NvmeVersion;
} EFI_NVM_EXPRESS_PASS_THRU_MODE;

#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM 0x0008

typedef struct {
    uint32_t OpCode : 8;
    uint32_t FusedOperation : 2;
    uint32_t Reserved : 22;
} EFI_NVME_CDW0;

#define EFI_NORMAL_CMD 0x00
#define EFI_FUSED_FIRST_CMD 0x01
#define EFI_FUSED_SECOND_CMD 0x02

typedef struct {
    EFI_NVME_CDW0 Cdw0;
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
} EFI_NVM_EXPRESS_COMMAND;

#define EFI_CDW2_VALID 0x01
#define EFI_CDW3_VALID 0x02
#define EFI_CDW10_VALID 0x04
#define EFI_CDW11_VALID 0x08
#define EFI_CDW12_VALID 0x10
#define EFI_CDW13_VALID 0x20
#define EFI_CDW14_VALID 0x40
#define EFI_CDW15_VALID 0x80

typedef struct {
    uint32_t DW0;
    uint32_t DW1;
    uint32_t DW2;
    uint32_t DW3;
} EFI_NVM_EXPRESS_COMPLETION;

/* MetadataBuffer as the text and MetadataLength spell it (the structure prints MetaDataBuffer). */
typedef struct {
    uint64_t CommandTimeout;
    void *TransferBuffer;
    uint32_t TransferLength;
    void *MetadataBuffer;
    uint32_t MetadataLength;
    uint8_t QueueType;
    EFI_NVM_EXPRESS_COMMAND *NvmeCmd;
    EFI_NVM_EXPRESS_COMPLETION *NvmeCompletion;
} EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET;

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU)(
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
    uint32_t NamespaceId,
    EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE)(
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
    uint32_t *NamespaceId
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH)(
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
    uint32_t NamespaceId,
    EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE)(
    EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    uint32_t *NamespaceId
);

struct _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL {
    EFI_NVM_EXPRESS_PASS_THRU_MODE *Mode;
    EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU PassThru;
    EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE GetNextNamespace;
    EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
    EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE GetNamespace;
};

#define EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID \
    {0x716ef0d9, 0xff83, 0x4f69, {0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70}}

typedef struct _EFI_SD_MMC_PASS_THRU_PROTOCOL EFI_SD_MMC_PASS_THRU_PROTOCOL;

typedef struct {
    uint16_t CommandIndex;
    uint32_t CommandArgument;
    uint32_t CommandType;
    uint32_t ResponseType;
} EFI_SD_MMC_COMMAND_BLOCK;

typedef struct {
    uint32_t Resp0;
    uint32_t Resp1;
    uint32_t Resp2;
    uint32_t Resp3;
} EFI_SD_MMC_STATUS_BLOCK;

typedef enum {
    EfiSdMmcCommandTypeBc,
    EfiSdMmcCommandTypeBcr,
    EfiSdMmcCommandTypeAc,
    EfiSdMmcCommandTypeAdtc
} EFI_SD_MMC_COMMAND_TYPE;

typedef enum {
    EfiSdMmcResponceTypeR1,
    EfiSdMmcResponceTypeR1b,
    EfiSdMmcResponceTypeR2,
    EfiSdMmcResponceTypeR3,
    EfiSdMmcResponceTypeR4,
    EfiSdMmcResponceTypeR5,
    EfiSdMmcResponceTypeR5b,
    EfiSdMmcResponceTypeR6,
    EfiSdMmcResponceTypeR7
} EFI_SD_MMC_RESPONSE_TYPE;

typedef struct {
    EFI_SD_MMC_COMMAND_BLOCK *SdMmcCmdBlk;
    EFI_SD_MMC_STATUS_BLOCK *SdMmcStatusBlk;
    uint64_t Timeout;
    void *InDataBuffer;
    void *OutDataBuffer;
    uint32_t InTransferLength;
    uint32_t OutTransferLength;
    EFI_STATUS TransactionStatus;
} EFI_SD_MMC_PASS_THRU_COMMAND_PACKET;

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_PASSTHRU)(
    EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    uint8_t Slot,
    EFI_SD_MMC_PASS_THRU_COMMAND_PACKET *Packet,
    EFI_EVENT Event
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT)(
    EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    uint8_t *Slot
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH)(
    EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    uint8_t Slot,
    EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER)(
    EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    EFI_DEVICE_PATH_PROTOCOL *DevicePath,
    uint8_t *Slot
);

typedef EFI_STATUS (EFI_API *EFI_SD_MMC_PASS_THRU_RESET_DEVICE)(
    EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
    uint8_t Slot
);

struct _EFI_SD_MMC_PASS_THRU_PROTOCOL {
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
    EFI_GUID *RamDiskType,
    EFI_DEVICE_PATH_PROTOCOL *ParentDevicePath,
    EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef EFI_STATUS (EFI_API *EFI_RAM_DISK_UNREGISTER_RAMDISK)(
    EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

typedef struct _EFI_RAM_DISK_PROTOCOL {
    EFI_RAM_DISK_REGISTER_RAMDISK Register;
    EFI_RAM_DISK_UNREGISTER_RAMDISK Unregister;
} EFI_RAM_DISK_PROTOCOL;

#define EFI_PARTITION_INFO_PROTOCOL_GUID \
    {0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0}}

/* The value printed (not 0x00010000), which is what firmware puts in Revision. */
#define EFI_PARTITION_INFO_PROTOCOL_REVISION 0x0001000
#define EFI_PARTITION_TYPE_OTHER 0x00
#define EFI_PARTITION_TYPE_MBR 0x01
#define EFI_PARTITION_TYPE_GPT 0x02

typedef struct __attribute__((__packed__)) {
    uint32_t Revision;
    uint32_t Type;
    uint8_t System;
    uint8_t Reserved[7];
    union {
        EFI_MBR_PARTITION_RECORD Mbr;
        EFI_PARTITION_ENTRY Gpt;
    } Info;
} EFI_PARTITION_INFO_PROTOCOL;

#define EFI_NVDIMM_LABEL_PROTOCOL_GUID \
    {0xd40b6b80, 0x97d5, 0x4282, {0xbb, 0x1d, 0x22, 0x3a, 0x16, 0x91, 0x80, 0x58}}

typedef struct _EFI_NVDIMM_LABEL_PROTOCOL EFI_NVDIMM_LABEL_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_INFORMATION)(
    EFI_NVDIMM_LABEL_PROTOCOL *This,
    uint32_t *SizeOfLabelStorageArea,
    uint32_t *MaxTransferLength
);

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_READ)(
    const EFI_NVDIMM_LABEL_PROTOCOL *This,
    uint32_t Offset,
    uint32_t TransferLength,
    uint8_t *LabelData
);

typedef EFI_STATUS (EFI_API *EFI_NVDIMM_LABEL_STORAGE_WRITE)(
    const EFI_NVDIMM_LABEL_PROTOCOL *This,
    uint32_t Offset,
    uint32_t TransferLength,
    uint8_t *LabelData
);

struct _EFI_NVDIMM_LABEL_PROTOCOL {
    EFI_NVDIMM_LABEL_STORAGE_INFORMATION LabelStorageInformation;
    EFI_NVDIMM_LABEL_STORAGE_READ LabelStorageRead;
    EFI_NVDIMM_LABEL_STORAGE_WRITE LabelStorageWrite;
};

#define EFI_NVDIMM_LABEL_INDEX_SIG_LEN 16
#define EFI_NVDIMM_LABEL_INDEX_ALIGN 256

__extension__ typedef struct EFI_NVDIMM_LABEL_INDEX_BLOCK {
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
} EFI_NVDIMM_LABEL_INDEX_BLOCK;

#define EFI_NVDIMM_LABEL_NAME_LEN 64

/* Flag bits 0x4 and 0x8 are reserved; the text's EFI_NVDIMM_LABEL_FLAGS_UPDATING has no value. */
#define EFI_NVDIMM_LABEL_FLAGS_ROLABEL 0x00000001
#define EFI_NVDIMM_LABEL_FLAGS_LOCAL 0x00000002
#define EFI_NVDIMM_LABEL_FLAGS_SPACOOKIE_BOUND 0x00000010

typedef struct EFI_NVDIMM_LABEL {
    EFI_GUID Uuid;
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
    EFI_GUID TypeGuid;
    EFI_GUID AddressAbstractionGuid;
    uint64_t SPALocationCookie;
    uint8_t Reserved1[80];
    uint64_t Checksum;
} EFI_NVDIMM_LABEL;

typedef struct EFI_NVDIMM_LABEL_SET_COOKIE_MAP {
    uint64_t RegionOffset;
    uint32_t SerialNumber;
    uint16_t VendorId;
    uint16_t ManufacturingDate;
    uint8_t ManufacturingLocation;
    uint8_t Reserved[31];
} EFI_NVDIMM_LABEL_SET_COOKIE_MAP;

/* One Mapping entry per NVDIMM in the interleave set (the printed bound is not a constant). */
typedef struct EFI_NVDIMM_LABEL_SET_COOKIE_INFO {
    EFI_NVDIMM_LABEL_SET_COOKIE_MAP Mapping[1];
} EFI_NVDIMM_LABEL_SET_COOKIE_INFO;

#define EFI_UFS_DEVICE_CONFIG_GUID \
    {0xb81bfab0, 0xeb3, 0x4cf9, {0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64}}

typedef struct _EFI_UFS_DEVICE_CONFIG_PROTOCOL EFI_UFS_DEVICE_CONFIG_PROTOCOL;

/* Descriptor points to the caller's buffer, as described; the prototype prints it by value. */
typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR)(
    EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
    bool Read,
    uint8_t DescId,
    uint8_t Index,
    uint8_t Selector,
    uint8_t *Descriptor,
    uint32_t *DescSize
);

typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_FLAG)(
    EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
    bool Read,
    uint8_t FlagId,
    uint8_t *Flag
);

typedef EFI_STATUS (EFI_API *EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE)(
    EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
    bool Read,
    uint8_t AttrId,
    uint8_t Index,
    uint8_t Selector,
    uint8_t *Attribute,
    uint32_t *AttrSize
);

struct _EFI_UFS_DEVICE_CONFIG_PROTOCOL {
    EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR RwUfsDescriptor;
    EFI_UFS_DEVICE_CONFIG_RW_FLAG RwUfsFlag;
    EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE RwUfsAttribute;
};

#ifdef __cplusplus
}
#endif

#endif
