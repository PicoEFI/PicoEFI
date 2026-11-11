#ifndef EFI_EFINET_H_
#define EFI_EFINET_H_

#include "efiapi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID \
    {0xA19832B9, 0xAC25, 0x11D3, {0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION 0x00010000

struct efi_simple_network_protocol;

#define EFI_SIMPLE_NETWORK_STOPPED ((uint32_t)0)
#define EFI_SIMPLE_NETWORK_STARTED ((uint32_t)1)
#define EFI_SIMPLE_NETWORK_INITIALIZED ((uint32_t)2)
#define EFI_SIMPLE_NETWORK_MAX_STATE ((uint32_t)3)

#define EFI_MAX_MCAST_FILTER_CNT 16

struct efi_simple_network_mode {
    uint32_t State;
    uint32_t HwAddressSize;
    uint32_t MediaHeaderSize;
    uint32_t MaxPacketSize;
    uint32_t NvRamSize;
    uint32_t NvRamAccessSize;
    uint32_t ReceiveFilterMask;
    uint32_t ReceiveFilterSetting;
    uint32_t MaxMCastFilterCount;
    uint32_t MCastFilterCount;
    struct efi_mac_address MCastFilter[EFI_MAX_MCAST_FILTER_CNT];
    struct efi_mac_address CurrentAddress;
    struct efi_mac_address BroadcastAddress;
    struct efi_mac_address PermanentAddress;
    uint8_t IfType;
    uint8_t MacAddressChangeable;
    uint8_t MultipleTxSupported;
    uint8_t MediaPresentSupported;
    uint8_t MediaPresent;
};

#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST 0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST 0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST 0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS 0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_START)(struct efi_simple_network_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_STOP)(struct efi_simple_network_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_INITIALIZE)(
    struct efi_simple_network_protocol *This,
    size_t ExtraRxBufferSize,
    size_t ExtraTxBufferSize
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_RESET)(
    struct efi_simple_network_protocol *This,
    bool ExtendedVerification
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_SHUTDOWN)(struct efi_simple_network_protocol *This);

/* MCastFilter points to a list, as described; the prototype prints it by value. */
typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_RECEIVE_FILTERS)(
    struct efi_simple_network_protocol *This,
    uint32_t Enable,
    uint32_t Disable,
    bool ResetMCastFilter,
    size_t MCastFilterCnt,
    struct efi_mac_address *MCastFilter
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_STATION_ADDRESS)(
    struct efi_simple_network_protocol *This,
    bool Reset,
    struct efi_mac_address *New
);

struct efi_network_statistics {
    uint64_t RxTotalFrames;
    uint64_t RxGoodFrames;
    uint64_t RxUndersizeFrames;
    uint64_t RxOversizeFrames;
    uint64_t RxDroppedFrames;
    uint64_t RxUnicastFrames;
    uint64_t RxBroadcastFrames;
    uint64_t RxMulticastFrames;
    uint64_t RxCrcErrorFrames;
    uint64_t RxTotalBytes;
    uint64_t TxTotalFrames;
    uint64_t TxGoodFrames;
    uint64_t TxUndersizeFrames;
    uint64_t TxOversizeFrames;
    uint64_t TxDroppedFrames;
    uint64_t TxUnicastFrames;
    uint64_t TxBroadcastFrames;
    uint64_t TxMulticastFrames;
    uint64_t TxCrcErrorFrames;
    uint64_t TxTotalBytes;
    uint64_t Collisions;
    uint64_t UnsupportedProtocol;
    uint64_t RxDuplicatedFrames;
    uint64_t RxDecryptErrorFrames;
    uint64_t TxErrorFrames;
    uint64_t TxRetryFrames;
};

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_STATISTICS)(
    struct efi_simple_network_protocol *This,
    bool Reset,
    size_t *StatisticsSize,
    struct efi_network_statistics *StatisticsTable
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC)(
    struct efi_simple_network_protocol *This,
    bool IPv6,
    union efi_ip_address *IP,
    struct efi_mac_address *MAC
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_NVDATA)(
    struct efi_simple_network_protocol *This,
    bool ReadWrite,
    size_t Offset,
    size_t BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_GET_STATUS)(
    struct efi_simple_network_protocol *This,
    uint32_t *InterruptStatus,
    void **TxBuf
);

#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT 0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT 0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT 0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT 0x08

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_TRANSMIT)(
    struct efi_simple_network_protocol *This,
    size_t HeaderSize,
    size_t BufferSize,
    void *Buffer,
    struct efi_mac_address *SrcAddr,
    struct efi_mac_address *DestAddr,
    uint16_t *Protocol
);

typedef EFI_STATUS (EFI_API *EFI_SIMPLE_NETWORK_RECEIVE)(
    struct efi_simple_network_protocol *This,
    size_t *HeaderSize,
    size_t *BufferSize,
    void *Buffer,
    struct efi_mac_address *SrcAddr,
    struct efi_mac_address *DestAddr,
    uint16_t *Protocol
);

struct efi_simple_network_protocol {
    uint64_t Revision;
    EFI_SIMPLE_NETWORK_START Start;
    EFI_SIMPLE_NETWORK_STOP Stop;
    EFI_SIMPLE_NETWORK_INITIALIZE Initialize;
    EFI_SIMPLE_NETWORK_RESET Reset;
    EFI_SIMPLE_NETWORK_SHUTDOWN Shutdown;
    EFI_SIMPLE_NETWORK_RECEIVE_FILTERS ReceiveFilters;
    EFI_SIMPLE_NETWORK_STATION_ADDRESS StationAddress;
    EFI_SIMPLE_NETWORK_STATISTICS Statistics;
    EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC MCastIpToMac;
    EFI_SIMPLE_NETWORK_NVDATA NvData;
    EFI_SIMPLE_NETWORK_GET_STATUS GetStatus;
    EFI_SIMPLE_NETWORK_TRANSMIT Transmit;
    EFI_SIMPLE_NETWORK_RECEIVE Receive;
    EFI_EVENT WaitForPacket;
    struct efi_simple_network_mode *Mode;
};

#ifdef __cplusplus
}
#endif

#endif
