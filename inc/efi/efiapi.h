#ifndef EFI_EFIAPI_H_
#define EFI_EFIAPI_H_

#include "efidef.h"
#include "efierr.h"
#include "efidevp.h"
#include "eficon.h"
#include "eficonex.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Each defined only if not yet defined: a PE/COFF header of the program's may come first. */
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION
#define EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION 10
#endif
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER
#define EFI_IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER 11
#endif
#ifndef EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER
#define EFI_IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER 12
#endif

#ifndef EFI_IMAGE_MACHINE_IA32
#define EFI_IMAGE_MACHINE_IA32 0x014c
#endif
#ifndef EFI_IMAGE_MACHINE_IA64
#define EFI_IMAGE_MACHINE_IA64 0x0200
#endif
#ifndef EFI_IMAGE_MACHINE_EBC
#define EFI_IMAGE_MACHINE_EBC 0x0EBC
#endif
#ifndef EFI_IMAGE_MACHINE_X64
#define EFI_IMAGE_MACHINE_X64 0x8664
#endif
#ifndef EFI_IMAGE_MACHINE_ARMTHUMB_MIXED
#define EFI_IMAGE_MACHINE_ARMTHUMB_MIXED 0x01C2
#endif
#ifndef EFI_IMAGE_MACHINE_AARCH64
#define EFI_IMAGE_MACHINE_AARCH64 0xAA64
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV32
#define EFI_IMAGE_MACHINE_RISCV32 0x5032
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV64
#define EFI_IMAGE_MACHINE_RISCV64 0x5064
#endif
#ifndef EFI_IMAGE_MACHINE_RISCV128
#define EFI_IMAGE_MACHINE_RISCV128 0x5128
#endif
#ifndef EFI_IMAGE_MACHINE_LOONGARCH32
#define EFI_IMAGE_MACHINE_LOONGARCH32 0x6232
#endif
#ifndef EFI_IMAGE_MACHINE_LOONGARCH64
#define EFI_IMAGE_MACHINE_LOONGARCH64 0x6264
#endif

#ifndef EFI_IMAGE_FILE_MACHINE_EBC
#define EFI_IMAGE_FILE_MACHINE_EBC 0x0EBC
#endif


#ifndef EFI_IMAGE_REL_EBC_ABSOLUTE
#define EFI_IMAGE_REL_EBC_ABSOLUTE 0x0000
#endif
#ifndef EFI_IMAGE_REL_EBC_ADDR32NB
#define EFI_IMAGE_REL_EBC_ADDR32NB 0x0001
#endif
#ifndef EFI_IMAGE_REL_EBC_REL32
#define EFI_IMAGE_REL_EBC_REL32 0x0002
#endif
#ifndef EFI_IMAGE_REL_EBC_SECTION
#define EFI_IMAGE_REL_EBC_SECTION 0x0003
#endif
#ifndef EFI_IMAGE_REL_EBC_SECREL
#define EFI_IMAGE_REL_EBC_SECREL 0x0004
#endif

struct efi_system_table;

typedef EFI_STATUS (EFI_API *EFI_IMAGE_ENTRY_POINT)(
    EFI_HANDLE ImageHandle,
    struct efi_system_table *SystemTable
);

struct efi_table_header {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
};

#define EFI_EVT_TIMER 0x80000000
#define EFI_EVT_RUNTIME 0x40000000
/* Named without a value by the specification; EFI_EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE implies it. */
#define EFI_EVT_RUNTIME_CONTEXT 0x20000000

#define EFI_EVT_NOTIFY_WAIT 0x00000100
#define EFI_EVT_NOTIFY_SIGNAL 0x00000200

#define EFI_EVT_SIGNAL_EXIT_BOOT_SERVICES 0x00000201
#define EFI_EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE 0x60000202

typedef void (EFI_API *EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);

typedef EFI_STATUS (EFI_API *EFI_CREATE_EVENT)(
    uint32_t Type,
    EFI_TPL NotifyTpl,
    EFI_EVENT_NOTIFY NotifyFunction,
    void *NotifyContext,
    EFI_EVENT *Event
);

typedef EFI_STATUS (EFI_API *EFI_CREATE_EVENT_EX)(
    uint32_t Type,
    EFI_TPL NotifyTpl,
    EFI_EVENT_NOTIFY NotifyFunction,
    const void *NotifyContext,
    const struct efi_guid *EventGroup,
    EFI_EVENT *Event
);

#define EFI_EVENT_GROUP_EXIT_BOOT_SERVICES \
    {0x27abf055, 0xb1b8, 0x4c26, {0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf}}

#define EFI_EVENT_GROUP_BEFORE_EXIT_BOOT_SERVICES \
    {0x8be0e274, 0x3970, 0x4b44, {0x80, 0xc5, 0x1a, 0xb9, 0x50, 0x2f, 0x3b, 0xfc}}

#define EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE \
    {0x13fa7698, 0xc831, 0x49c7, {0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96}}

#define EFI_EVENT_GROUP_MEMORY_MAP_CHANGE \
    {0x78bee926, 0x692f, 0x48fd, {0x9e, 0xdb, 0x1, 0x42, 0x2e, 0xf0, 0xd7, 0xab}}

#define EFI_EVENT_GROUP_READY_TO_BOOT \
    {0x7ce88fb3, 0x4bd7, 0x4679, {0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0xd, 0x2b}}

#define EFI_EVENT_GROUP_AFTER_READY_TO_BOOT \
    {0x3a2a00ad, 0x98b9, 0x4cdf, {0xa4, 0x78, 0x70, 0x27, 0x77, 0xf1, 0xc1, 0xb}}

#define EFI_EVENT_GROUP_RESET_SYSTEM \
    {0x62da6a56, 0x13fb, 0x485a, {0xa8, 0xda, 0xa3, 0xdd, 0x79, 0x12, 0xcb, 0x6b}}

typedef EFI_STATUS (EFI_API *EFI_CLOSE_EVENT)(EFI_EVENT Event);

typedef EFI_STATUS (EFI_API *EFI_SIGNAL_EVENT)(EFI_EVENT Event);

typedef EFI_STATUS (EFI_API *EFI_WAIT_FOR_EVENT)(
    size_t NumberOfEvents,
    EFI_EVENT *Event,
    size_t *Index
);

typedef EFI_STATUS (EFI_API *EFI_CHECK_EVENT)(EFI_EVENT Event);

#define EFI_TIMER_CANCEL ((uint32_t)0)
#define EFI_TIMER_PERIODIC ((uint32_t)1)
#define EFI_TIMER_RELATIVE ((uint32_t)2)

typedef EFI_STATUS (EFI_API *EFI_SET_TIMER)(
    EFI_EVENT Event,
    uint32_t Type,
    uint64_t TriggerTime
);

#define EFI_TPL_APPLICATION 4
#define EFI_TPL_CALLBACK 8
#define EFI_TPL_NOTIFY 16
#define EFI_TPL_HIGH_LEVEL 31

typedef EFI_TPL (EFI_API *EFI_RAISE_TPL)(EFI_TPL NewTpl);

typedef void (EFI_API *EFI_RESTORE_TPL)(EFI_TPL OldTpl);

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_PAGES)(
    uint32_t Type,
    uint32_t MemoryType,
    size_t Pages,
    EFI_PHYSICAL_ADDRESS *Memory
);

typedef EFI_STATUS (EFI_API *EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS Memory,
    size_t Pages
);

typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_MAP)(
    size_t *MemoryMapSize,
    struct efi_memory_descriptor *MemoryMap,
    uintptr_t *MapKey,
    size_t *DescriptorSize,
    uint32_t *DescriptorVersion
);

/* Not in the specification: the descriptor after Ptr in a GetMemoryMap() buffer. */
#define EfiNextMemoryDescriptor(Ptr, Size) ((struct efi_memory_descriptor *)((uint8_t *)(Ptr) + (Size)))

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_POOL)(
    uint32_t PoolType,
    size_t Size,
    void **Buffer
);

typedef EFI_STATUS (EFI_API *EFI_FREE_POOL)(void *Buffer);

#define EFI_NATIVE_INTERFACE ((uint32_t)0)

typedef EFI_STATUS (EFI_API *EFI_INSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE *Handle,
    struct efi_guid *Protocol,
    uint32_t InterfaceType,
    void *Interface
);

typedef EFI_STATUS (EFI_API *EFI_UNINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    void *Interface
);

typedef EFI_STATUS (EFI_API *EFI_REINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    void *OldInterface,
    void *NewInterface
);

typedef EFI_STATUS (EFI_API *EFI_REGISTER_PROTOCOL_NOTIFY)(
    struct efi_guid *Protocol,
    EFI_EVENT Event,
    void **Registration
);

#define EFI_ALL_HANDLES ((uint32_t)0)
#define EFI_BY_REGISTER_NOTIFY ((uint32_t)1)
#define EFI_BY_PROTOCOL ((uint32_t)2)

typedef EFI_STATUS (EFI_API *EFI_LOCATE_HANDLE)(
    uint32_t SearchType,
    struct efi_guid *Protocol,
    void *SearchKey,
    size_t *BufferSize,
    EFI_HANDLE *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    void **Interface
);

typedef EFI_STATUS (EFI_API *EFI_LOCATE_DEVICE_PATH)(
    struct efi_guid *Protocol,
    struct efi_device_path_protocol **DevicePath,
    EFI_HANDLE *Device
);

typedef EFI_STATUS (EFI_API *EFI_OPEN_PROTOCOL)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    void **Interface,
    EFI_HANDLE AgentHandle,
    EFI_HANDLE ControllerHandle,
    uint32_t Attributes
);

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef EFI_STATUS (EFI_API *EFI_CLOSE_PROTOCOL)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    EFI_HANDLE AgentHandle,
    EFI_HANDLE ControllerHandle
);

struct efi_open_protocol_information_entry {
    EFI_HANDLE AgentHandle;
    EFI_HANDLE ControllerHandle;
    uint32_t Attributes;
    uint32_t OpenCount;
};

typedef EFI_STATUS (EFI_API *EFI_OPEN_PROTOCOL_INFORMATION)(
    EFI_HANDLE Handle,
    struct efi_guid *Protocol,
    struct efi_open_protocol_information_entry **EntryBuffer,
    size_t *EntryCount
);

typedef EFI_STATUS (EFI_API *EFI_CONNECT_CONTROLLER)(
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE *DriverImageHandle,
    struct efi_device_path_protocol *RemainingDevicePath,
    bool Recursive
);

typedef EFI_STATUS (EFI_API *EFI_DISCONNECT_CONTROLLER)(
    EFI_HANDLE ControllerHandle,
    EFI_HANDLE DriverImageHandle,
    EFI_HANDLE ChildHandle
);

typedef EFI_STATUS (EFI_API *EFI_PROTOCOLS_PER_HANDLE)(
    EFI_HANDLE Handle,
    struct efi_guid ***ProtocolBuffer,
    size_t *ProtocolBufferCount
);

typedef EFI_STATUS (EFI_API *EFI_LOCATE_HANDLE_BUFFER)(
    uint32_t SearchType,
    struct efi_guid *Protocol,
    void *SearchKey,
    size_t *NoHandles,
    EFI_HANDLE **Buffer
);

typedef EFI_STATUS (EFI_API *EFI_LOCATE_PROTOCOL)(
    struct efi_guid *Protocol,
    void *Registration,
    void **Interface
);

typedef EFI_STATUS (EFI_API *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE *Handle,
    ...
);

typedef EFI_STATUS (EFI_API *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE Handle,
    ...
);

typedef EFI_STATUS (EFI_API *EFI_IMAGE_LOAD)(
    bool BootPolicy,
    EFI_HANDLE ParentImageHandle,
    struct efi_device_path_protocol *DevicePath,
    void *SourceBuffer,
    size_t SourceSize,
    EFI_HANDLE *ImageHandle
);

#define EFI_HII_PACKAGE_LIST_PROTOCOL_GUID \
    {0x6a1ee763, 0xd47a, 0x43b4, {0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc}}

typedef EFI_STATUS (EFI_API *EFI_IMAGE_START)(
    EFI_HANDLE ImageHandle,
    size_t *ExitDataSize,
    uint16_t **ExitData
);

typedef EFI_STATUS (EFI_API *EFI_IMAGE_UNLOAD)(EFI_HANDLE ImageHandle);

typedef EFI_STATUS (EFI_API *EFI_EXIT)(
    EFI_HANDLE ImageHandle,
    EFI_STATUS ExitStatus,
    size_t ExitDataSize,
    uint16_t *ExitData
);

typedef EFI_STATUS (EFI_API *EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE ImageHandle,
    uintptr_t MapKey
);

typedef EFI_STATUS (EFI_API *EFI_SET_WATCHDOG_TIMER)(
    uintptr_t Timeout,
    uint64_t WatchdogCode,
    size_t DataSize,
    uint16_t *WatchdogData
);

typedef EFI_STATUS (EFI_API *EFI_STALL)(uintptr_t Microseconds);

typedef void (EFI_API *EFI_COPY_MEM)(
    void *Destination,
    void *Source,
    size_t Length
);

typedef void (EFI_API *EFI_SET_MEM)(
    void *Buffer,
    size_t Size,
    uint8_t Value
);

typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_MONOTONIC_COUNT)(uint64_t *Count);

typedef EFI_STATUS (EFI_API *EFI_INSTALL_CONFIGURATION_TABLE)(
    struct efi_guid *Guid,
    void *Table
);

typedef EFI_STATUS (EFI_API *EFI_CALCULATE_CRC32)(
    void *Data,
    size_t DataSize,
    uint32_t *Crc32
);

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040
#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS 0x00000080

/* The runtime services are printed as plain function types; named as in struct efi_runtime_services. */
typedef EFI_STATUS (EFI_API *EFI_GET_VARIABLE)(
    uint16_t *VariableName,
    struct efi_guid *VendorGuid,
    uint32_t *Attributes,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_VARIABLE_NAME)(
    size_t *VariableNameSize,
    uint16_t *VariableName,
    struct efi_guid *VendorGuid
);

typedef EFI_STATUS (EFI_API *EFI_SET_VARIABLE)(
    uint16_t *VariableName,
    struct efi_guid *VendorGuid,
    uint32_t Attributes,
    size_t DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_QUERY_VARIABLE_INFO)(
    uint32_t Attributes,
    uint64_t *MaximumVariableStorageSize,
    uint64_t *RemainingVariableStorageSize,
    uint64_t *MaximumVariableSize
);

#define EFI_HARDWARE_ERROR_VARIABLE \
    {0x414E6BDD, 0xE47B, 0x47cc, {0xB2, 0x44, 0xBB, 0x61, 0x02, 0x0C, 0xF5, 0x16}}

struct efi_time_capabilities {
    uint32_t Resolution;
    uint32_t Accuracy;
    uint8_t SetsToZero;
};

typedef EFI_STATUS (EFI_API *EFI_GET_TIME)(
    struct efi_time *Time,
    struct efi_time_capabilities *Capabilities
);

typedef EFI_STATUS (EFI_API *EFI_SET_TIME)(struct efi_time *Time);

typedef EFI_STATUS (EFI_API *EFI_GET_WAKEUP_TIME)(
    bool *Enabled,
    bool *Pending,
    struct efi_time *Time
);

typedef EFI_STATUS (EFI_API *EFI_SET_WAKEUP_TIME)(
    bool Enable,
    struct efi_time *Time
);

typedef EFI_STATUS (EFI_API *EFI_SET_VIRTUAL_ADDRESS_MAP)(
    size_t MemoryMapSize,
    size_t DescriptorSize,
    uint32_t DescriptorVersion,
    struct efi_memory_descriptor *VirtualMap
);

typedef EFI_STATUS (EFI_API *EFI_CONVERT_POINTER)(
    uintptr_t DebugDisposition,
    void **Address
);

#define EFI_OPTIONAL_PTR 0x00000001

#define EFI_RESET_COLD ((uint32_t)0)
#define EFI_RESET_WARM ((uint32_t)1)
#define EFI_RESET_SHUTDOWN ((uint32_t)2)
#define EFI_RESET_PLATFORM_SPECIFIC ((uint32_t)3)

typedef void (EFI_API *EFI_RESET_SYSTEM)(
    uint32_t ResetType,
    EFI_STATUS ResetStatus,
    size_t DataSize,
    void *ResetData
);

typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_HIGH_MONO_COUNT)(uint32_t *HighCount);

struct efi_capsule_block_descriptor {
    uint64_t Length;
    union {
        EFI_PHYSICAL_ADDRESS DataBlock;
        EFI_PHYSICAL_ADDRESS ContinuationPointer;
    } Union;
};

struct efi_capsule_header {
    struct efi_guid CapsuleGuid;
    uint32_t HeaderSize;
    uint32_t Flags;
    uint32_t CapsuleImageSize;
};

#define EFI_CAPSULE_FLAGS_PERSIST_ACROSS_RESET 0x00010000
#define EFI_CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE 0x00020000
#define EFI_CAPSULE_FLAGS_INITIATE_RESET 0x00040000

struct efi_capsule_table {
    uint32_t CapsuleArrayNumber;
    void *CapsulePtr[1];
};

typedef EFI_STATUS (EFI_API *EFI_UPDATE_CAPSULE)(
    struct efi_capsule_header **CapsuleHeaderArray,
    size_t CapsuleCount,
    EFI_PHYSICAL_ADDRESS ScatterGatherList
);

#define EFI_MEMORY_RANGE_CAPSULE_GUID \
    {0xde9f0ec, 0x88b6, 0x428f, {0x97, 0x7a, 0x25, 0x8f, 0x1d, 0xe, 0x5e, 0x72}}

struct efi_memory_range {
    EFI_PHYSICAL_ADDRESS Address;
    uint64_t Length;
};

__extension__ struct efi_memory_range_capsule {
    struct efi_capsule_header Header;
    uint32_t OsRequestedMemoryType;
    uint64_t NumberOfMemoryRanges;
    struct efi_memory_range MemoryRanges[];
};

struct efi_memory_range_capsule_result {
    uint64_t FirmwareMemoryRequirement;
    uint64_t NumberOfMemoryRanges;
};

typedef EFI_STATUS (EFI_API *EFI_QUERY_CAPSULE_CAPABILITIES)(
    struct efi_capsule_header **CapsuleHeaderArray,
    size_t CapsuleCount,
    uint64_t *MaximumCapsuleSize,
    uint32_t *ResetType
);

#define EFI_CAPSULE_REPORT_GUID \
    {0x39b68c46, 0xf7fb, 0x441b, {0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3}}

struct efi_capsule_result_variable_header {
    uint32_t VariableTotalSize;
    uint32_t Reserved;
    struct efi_guid CapsuleGuid;
    struct efi_time CapsuleProcessed;
    EFI_STATUS CapsuleStatus;
};

/* The uint16_t strings CapsuleFileName and CapsuleTarget follow, each null-terminated. */
struct efi_capsule_result_variable_fmp {
    uint16_t Version;
    uint8_t PayloadIndex;
    uint8_t UpdateImageIndex;
    struct efi_guid UpdateImageTypeId;
};

__extension__ struct efi_capsule_result_variable_json {
    uint32_t Version;
    uint32_t CapsuleId;
    uint32_t RespLength;
    uint8_t Resp[];
};

/* Printed as 0xF000000, which is outside the specification-reserved range it belongs to. */
#define EFI_REDFISH_DEFINED_JSON_SCHEMA 0xF0000000

#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION ((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION ((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION ((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION ((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION ((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION ((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION ((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION ((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION ((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION ((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION ((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION ((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION ((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION EFI_2_100_SYSTEM_TABLE_REVISION

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

/*
 * LoadImage and InstallMultipleProtocolInterfaces are misprinted as EFI_IMAGE_UNLOAD and
 * EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES.
 */
struct efi_boot_services {
    struct efi_table_header Hdr;

    EFI_RAISE_TPL RaiseTPL;
    EFI_RESTORE_TPL RestoreTPL;

    EFI_ALLOCATE_PAGES AllocatePages;
    EFI_FREE_PAGES FreePages;
    EFI_GET_MEMORY_MAP GetMemoryMap;
    EFI_ALLOCATE_POOL AllocatePool;
    EFI_FREE_POOL FreePool;

    EFI_CREATE_EVENT CreateEvent;
    EFI_SET_TIMER SetTimer;
    EFI_WAIT_FOR_EVENT WaitForEvent;
    EFI_SIGNAL_EVENT SignalEvent;
    EFI_CLOSE_EVENT CloseEvent;
    EFI_CHECK_EVENT CheckEvent;

    EFI_INSTALL_PROTOCOL_INTERFACE InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL HandleProtocol;
    void *Reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY RegisterProtocolNotify;
    EFI_LOCATE_HANDLE LocateHandle;
    EFI_LOCATE_DEVICE_PATH LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE InstallConfigurationTable;

    EFI_IMAGE_LOAD LoadImage;
    EFI_IMAGE_START StartImage;
    EFI_EXIT Exit;
    EFI_IMAGE_UNLOAD UnloadImage;
    EFI_EXIT_BOOT_SERVICES ExitBootServices;

    EFI_GET_NEXT_MONOTONIC_COUNT GetNextMonotonicCount;
    EFI_STALL Stall;
    EFI_SET_WATCHDOG_TIMER SetWatchdogTimer;

    EFI_CONNECT_CONTROLLER ConnectController;
    EFI_DISCONNECT_CONTROLLER DisconnectController;

    EFI_OPEN_PROTOCOL OpenProtocol;
    EFI_CLOSE_PROTOCOL CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION OpenProtocolInformation;

    EFI_PROTOCOLS_PER_HANDLE ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL LocateProtocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;

    EFI_CALCULATE_CRC32 CalculateCrc32;

    EFI_COPY_MEM CopyMem;
    EFI_SET_MEM SetMem;
    EFI_CREATE_EVENT_EX CreateEventEx;
};

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

struct efi_runtime_services {
    struct efi_table_header Hdr;

    EFI_GET_TIME GetTime;
    EFI_SET_TIME SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;

    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER ConvertPointer;

    EFI_GET_VARIABLE GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME GetNextVariableName;
    EFI_SET_VARIABLE SetVariable;

    EFI_GET_NEXT_HIGH_MONO_COUNT GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM ResetSystem;

    EFI_UPDATE_CAPSULE UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES QueryCapsuleCapabilities;

    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
};

struct efi_configuration_table {
    struct efi_guid VendorGuid;
    void *VendorTable;
};

struct efi_system_table {
    struct efi_table_header Hdr;
    uint16_t *FirmwareVendor;
    uint32_t FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    struct efi_simple_text_input_protocol *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    struct efi_simple_text_output_protocol *ConOut;
    EFI_HANDLE StandardErrorHandle;
    struct efi_simple_text_output_protocol *StdErr;
    struct efi_runtime_services *RuntimeServices;
    struct efi_boot_services *BootServices;
    size_t NumberOfTableEntries;
    struct efi_configuration_table *ConfigurationTable;
};

#define EFI_ACPI_TABLE_GUID \
    {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}

#define EFI_ACPI_20_TABLE_GUID EFI_ACPI_TABLE_GUID

#define EFI_ACPI_10_TABLE_GUID \
    {0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_SAL_SYSTEM_TABLE_GUID \
    {0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_SMBIOS_TABLE_GUID \
    {0xeb9d2d31, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_SMBIOS3_TABLE_GUID \
    {0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94}}

#define EFI_MPS_TABLE_GUID \
    {0xeb9d2d2f, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define EFI_JSON_CONFIG_DATA_TABLE_GUID \
    {0x87367f87, 0x1119, 0x41ce, {0xaa, 0xec, 0x8b, 0xe0, 0x11, 0x1f, 0x55, 0x8a}}

#define EFI_JSON_CAPSULE_DATA_TABLE_GUID \
    {0x35e7a725, 0x8dd2, 0x4cac, {0x80, 0x11, 0x33, 0xcd, 0xa8, 0x10, 0x90, 0x56}}

#define EFI_JSON_CAPSULE_RESULT_TABLE_GUID \
    {0xdbc461c3, 0xb3de, 0x422a, {0xb9, 0xb4, 0x98, 0x86, 0xfd, 0x49, 0xa1, 0xe5}}

#define EFI_DTB_TABLE_GUID \
    {0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0}}

#define EFI_RT_PROPERTIES_TABLE_GUID \
    {0xeb66918a, 0x7eef, 0x402a, {0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9}}

struct efi_rt_properties_table {
    uint16_t Version;
    uint16_t Length;
    uint32_t RuntimeServicesSupported;
};

#define EFI_RT_PROPERTIES_TABLE_VERSION 0x1

#define EFI_RT_SUPPORTED_GET_TIME 0x0001
#define EFI_RT_SUPPORTED_SET_TIME 0x0002
#define EFI_RT_SUPPORTED_GET_WAKEUP_TIME 0x0004
#define EFI_RT_SUPPORTED_SET_WAKEUP_TIME 0x0008
#define EFI_RT_SUPPORTED_GET_VARIABLE 0x0010
#define EFI_RT_SUPPORTED_GET_NEXT_VARIABLE_NAME 0x0020
#define EFI_RT_SUPPORTED_SET_VARIABLE 0x0040
#define EFI_RT_SUPPORTED_SET_VIRTUAL_ADDRESS_MAP 0x0080
#define EFI_RT_SUPPORTED_CONVERT_POINTER 0x0100
#define EFI_RT_SUPPORTED_GET_NEXT_HIGH_MONOTONIC_COUNT 0x0200
#define EFI_RT_SUPPORTED_RESET_SYSTEM 0x0400
#define EFI_RT_SUPPORTED_UPDATE_CAPSULE 0x0800
#define EFI_RT_SUPPORTED_QUERY_CAPSULE_CAPABILITIES 0x1000
#define EFI_RT_SUPPORTED_QUERY_VARIABLE_INFO 0x2000

#define EFI_MEMORY_ATTRIBUTES_TABLE_GUID \
    {0xdcfa911d, 0x26eb, 0x469f, {0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20}}

/* Version 2 is current. NumberOfEntries descriptors follow, DescriptorSize bytes apart. */
struct efi_memory_attributes_table {
    uint32_t Version;
    uint32_t NumberOfEntries;
    uint32_t DescriptorSize;
    uint32_t Flags;
};

#define EFI_MEMORY_ATTRIBUTES_FLAGS_RT_FORWARD_CONTROL_FLOW_GUARD 0x1

#define EFI_CONFORMANCE_PROFILES_TABLE_GUID \
    {0x36122546, 0xf7e7, 0x4c8f, {0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b}}

/* NumberOfProfiles EFI_GUIDs (ConformanceProfiles) follow. */
struct efi_conformance_profiles_table {
    uint16_t Version;
    uint16_t NumberOfProfiles;
};

#define EFI_CONFORMANCE_PROFILES_TABLE_VERSION 0x1

#define EFI_CONFORMANCE_PROFILES_UEFI_SPEC_GUID \
    {0x523c91af, 0xa195, 0x4382, {0x81, 0x8d, 0x29, 0x5f, 0xe4, 0x00, 0x64, 0x65}}

#define EFI_PI_SPECIFICATION_VERSION ((1<<16) | 100)

#define EFI_DXE_SERVICES_TABLE_GUID \
    {0x5ad34ba, 0x6f02, 0x4214, {0x95, 0x2e, 0x4d, 0xa0, 0x39, 0x8e, 0x2b, 0xb9}}

#define EFI_DXE_SERVICES_SIGNATURE 0x565245535f455844
#define EFI_DXE_SERVICES_REVISION EFI_PI_SPECIFICATION_VERSION

#define EFI_GCD_MEMORY_TYPE_NON_EXISTENT ((uint32_t)0)
#define EFI_GCD_MEMORY_TYPE_RESERVED ((uint32_t)1)
#define EFI_GCD_MEMORY_TYPE_SYSTEM_MEMORY ((uint32_t)2)
#define EFI_GCD_MEMORY_TYPE_MEMORY_MAPPED_IO ((uint32_t)3)
#define EFI_GCD_MEMORY_TYPE_PERSISTENT ((uint32_t)4)
#define EFI_GCD_MEMORY_TYPE_MORE_RELIABLE ((uint32_t)5)
#define EFI_GCD_MEMORY_TYPE_UNACCEPTED ((uint32_t)6)
#define EFI_GCD_MEMORY_TYPE_MAXIMUM ((uint32_t)7)

#define EFI_GCD_IO_TYPE_NON_EXISTENT ((uint32_t)0)
#define EFI_GCD_IO_TYPE_RESERVED ((uint32_t)1)
#define EFI_GCD_IO_TYPE_IO ((uint32_t)2)
#define EFI_GCD_IO_TYPE_MAXIMUM ((uint32_t)3)

#define EFI_GCD_ALLOCATE_ANY_SEARCH_BOTTOM_UP ((uint32_t)0)
#define EFI_GCD_ALLOCATE_MAX_ADDRESS_SEARCH_BOTTOM_UP ((uint32_t)1)
#define EFI_GCD_ALLOCATE_ADDRESS ((uint32_t)2)
#define EFI_GCD_ALLOCATE_ANY_SEARCH_TOP_DOWN ((uint32_t)3)
#define EFI_GCD_ALLOCATE_MAX_ADDRESS_SEARCH_TOP_DOWN ((uint32_t)4)
#define EFI_GCD_MAX_ALLOCATE_TYPE ((uint32_t)5)

struct efi_gcd_memory_space_descriptor {
    EFI_PHYSICAL_ADDRESS BaseAddress;
    uint64_t Length;
    uint64_t Capabilities;
    uint64_t Attributes;
    uint32_t GcdMemoryType;
    EFI_HANDLE ImageHandle;
    EFI_HANDLE DeviceHandle;
};

struct efi_gcd_io_space_descriptor {
    EFI_PHYSICAL_ADDRESS BaseAddress;
    uint64_t Length;
    uint32_t GcdIoType;
    EFI_HANDLE ImageHandle;
    EFI_HANDLE DeviceHandle;
};

typedef EFI_STATUS (EFI_API *EFI_ADD_MEMORY_SPACE)(
    uint32_t GcdMemoryType,
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t Capabilities
);

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_MEMORY_SPACE)(
    uint32_t GcdAllocateType,
    uint32_t GcdMemoryType,
    size_t Alignment,
    uint64_t Length,
    EFI_PHYSICAL_ADDRESS *BaseAddress,
    EFI_HANDLE ImageHandle,
    EFI_HANDLE DeviceHandle
);

typedef EFI_STATUS (EFI_API *EFI_FREE_MEMORY_SPACE)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length
);

typedef EFI_STATUS (EFI_API *EFI_REMOVE_MEMORY_SPACE)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length
);

typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_SPACE_DESCRIPTOR)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    struct efi_gcd_memory_space_descriptor *Descriptor
);

typedef EFI_STATUS (EFI_API *EFI_SET_MEMORY_SPACE_ATTRIBUTES)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t Attributes
);

typedef EFI_STATUS (EFI_API *EFI_SET_MEMORY_SPACE_CAPABILITIES)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length,
    uint64_t Capabilities
);

typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_SPACE_MAP)(
    size_t *NumberOfDescriptors,
    struct efi_gcd_memory_space_descriptor **MemorySpaceMap
);

typedef EFI_STATUS (EFI_API *EFI_ADD_IO_SPACE)(
    uint32_t GcdIoType,
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length
);

typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_IO_SPACE)(
    uint32_t GcdAllocateType,
    uint32_t GcdIoType,
    size_t Alignment,
    uint64_t Length,
    EFI_PHYSICAL_ADDRESS *BaseAddress,
    EFI_HANDLE ImageHandle,
    EFI_HANDLE DeviceHandle
);

typedef EFI_STATUS (EFI_API *EFI_FREE_IO_SPACE)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length
);

typedef EFI_STATUS (EFI_API *EFI_REMOVE_IO_SPACE)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    uint64_t Length
);

typedef EFI_STATUS (EFI_API *EFI_GET_IO_SPACE_DESCRIPTOR)(
    EFI_PHYSICAL_ADDRESS BaseAddress,
    struct efi_gcd_io_space_descriptor *Descriptor
);

typedef EFI_STATUS (EFI_API *EFI_GET_IO_SPACE_MAP)(
    size_t *NumberOfDescriptors,
    struct efi_gcd_io_space_descriptor **IoSpaceMap
);

typedef EFI_STATUS (EFI_API *EFI_DISPATCH)(void);

typedef EFI_STATUS (EFI_API *EFI_SCHEDULE)(
    EFI_HANDLE FirmwareVolumeHandle,
    const struct efi_guid *FileName
);

typedef EFI_STATUS (EFI_API *EFI_TRUST)(
    EFI_HANDLE FirmwareVolumeHandle,
    const struct efi_guid *FileName
);

typedef EFI_STATUS (EFI_API *EFI_PROCESS_FIRMWARE_VOLUME)(
    const void *FirmwareVolumeHeader,
    size_t Size,
    EFI_HANDLE *FirmwareVolumeHandle
);

struct efi_dxe_services {
    struct efi_table_header Hdr;

    EFI_ADD_MEMORY_SPACE AddMemorySpace;
    EFI_ALLOCATE_MEMORY_SPACE AllocateMemorySpace;
    EFI_FREE_MEMORY_SPACE FreeMemorySpace;
    EFI_REMOVE_MEMORY_SPACE RemoveMemorySpace;
    EFI_GET_MEMORY_SPACE_DESCRIPTOR GetMemorySpaceDescriptor;
    EFI_SET_MEMORY_SPACE_ATTRIBUTES SetMemorySpaceAttributes;
    EFI_GET_MEMORY_SPACE_MAP GetMemorySpaceMap;
    EFI_ADD_IO_SPACE AddIoSpace;
    EFI_ALLOCATE_IO_SPACE AllocateIoSpace;
    EFI_FREE_IO_SPACE FreeIoSpace;
    EFI_REMOVE_IO_SPACE RemoveIoSpace;
    EFI_GET_IO_SPACE_DESCRIPTOR GetIoSpaceDescriptor;
    EFI_GET_IO_SPACE_MAP GetIoSpaceMap;

    EFI_DISPATCH Dispatch;
    EFI_SCHEDULE Schedule;
    EFI_TRUST Trust;

    EFI_PROCESS_FIRMWARE_VOLUME ProcessFirmwareVolume;

    EFI_SET_MEMORY_SPACE_CAPABILITIES SetMemorySpaceCapabilities;
};

#ifdef __cplusplus
}
#endif

#endif
