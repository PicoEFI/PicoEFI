#ifndef EFI_EFISHELL_H_
#define EFI_EFISHELL_H_

#include "efiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SHELL_MAJOR_VERSION 2
#define EFI_SHELL_MINOR_VERSION 2

#define EFI_SHELL_PROTOCOL_GUID \
    {0x6302d008, 0x7f9b, 0x4f30, {0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e}}

typedef void *EFI_SHELL_FILE_HANDLE;

struct efi_list_entry {
    struct efi_list_entry *Flink;
    struct efi_list_entry *Blink;
};

struct efi_shell_file_info {
    struct efi_list_entry Link;
    EFI_STATUS Status;
    const uint16_t *FullName;
    const uint16_t *FileName;
    EFI_SHELL_FILE_HANDLE Handle;
    struct efi_file_info *Info;
};

typedef uint32_t EFI_DEVICE_NAME_FLAGS;

/* The prototype of GetDeviceName() spells the flags type this way. */
typedef EFI_DEVICE_NAME_FLAGS EFI_SHELL_DEVICE_NAME_FLAGS;

#define EFI_DEVICE_NAME_USE_COMPONENT_NAME 0x00000001
#define EFI_DEVICE_NAME_USE_DEVICE_PATH 0x00000002

typedef bool (EFI_API *EFI_SHELL_BATCH_IS_ACTIVE)(void);

typedef EFI_STATUS (EFI_API *EFI_SHELL_CLOSE_FILE)(EFI_SHELL_FILE_HANDLE FileHandle);

typedef EFI_STATUS (EFI_API *EFI_SHELL_CREATE_FILE)(
    const uint16_t *FileName,
    uint64_t FileAttribs,
    EFI_SHELL_FILE_HANDLE *FileHandle
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_DELETE_FILE)(EFI_SHELL_FILE_HANDLE FileHandle);

typedef EFI_STATUS (EFI_API *EFI_SHELL_DELETE_FILE_BY_NAME)(const uint16_t *FileName);

typedef void (EFI_API *EFI_SHELL_DISABLE_PAGE_BREAK)(void);

typedef void (EFI_API *EFI_SHELL_ENABLE_PAGE_BREAK)(void);

typedef EFI_STATUS (EFI_API *EFI_SHELL_EXECUTE)(
    EFI_HANDLE *ParentImageHandle,
    uint16_t *CommandLine,
    uint16_t **Environment,
    EFI_STATUS *StatusCode
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_FIND_FILES)(
    const uint16_t *FilePattern,
    struct efi_shell_file_info **FileList
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_FIND_FILES_IN_DIR)(
    EFI_SHELL_FILE_HANDLE FileDirHandle,
    struct efi_shell_file_info **FileList
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_FLUSH_FILE)(EFI_SHELL_FILE_HANDLE FileHandle);

typedef EFI_STATUS (EFI_API *EFI_SHELL_FREE_FILE_LIST)(struct efi_shell_file_info **FileList);

typedef const uint16_t *(EFI_API *EFI_SHELL_GET_ALIAS)(
    const uint16_t *Alias,
    bool *Volatile
);

typedef const uint16_t *(EFI_API *EFI_SHELL_GET_CUR_DIR)(
    const uint16_t *FileSystemMapping
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_DEVICE_NAME)(
    EFI_HANDLE DeviceHandle,
    EFI_SHELL_DEVICE_NAME_FLAGS Flags,
    char *Language,
    uint16_t **BestDeviceName
);

typedef const struct efi_device_path_protocol *(EFI_API *EFI_SHELL_GET_DEVICE_PATH_FROM_MAP)(
    const uint16_t *Mapping
);

typedef struct efi_device_path_protocol *(EFI_API *EFI_SHELL_GET_DEVICE_PATH_FROM_FILE_PATH)(
    const uint16_t *Path
);

typedef const uint16_t *(EFI_API *EFI_SHELL_GET_ENV)(const uint16_t *Name);

typedef const uint16_t *(EFI_API *EFI_SHELL_GET_ENV_EX)(
    const uint16_t *Name,
    uint32_t *Attributes
);

typedef struct efi_file_info *(EFI_API *EFI_SHELL_GET_FILE_INFO)(EFI_SHELL_FILE_HANDLE FileHandle);

typedef uint16_t *(EFI_API *EFI_SHELL_GET_FILE_PATH_FROM_DEVICE_PATH)(
    const struct efi_device_path_protocol *Path
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_FILE_POSITION)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    uint64_t *Position
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_FILE_SIZE)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    uint64_t *Size
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_GUID_FROM_NAME)(
    const uint16_t *GuidName,
    struct efi_guid *Guid
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_GUID_NAME)(
    const struct efi_guid *Guid,
    const uint16_t **GuidName
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_GET_HELP_TEXT)(
    const uint16_t *Command,
    const uint16_t *Sections,
    uint16_t **HelpText
);

typedef const uint16_t *(EFI_API *EFI_SHELL_GET_MAP_FROM_DEVICE_PATH)(
    struct efi_device_path_protocol **DevicePath
);

typedef bool (EFI_API *EFI_SHELL_GET_PAGE_BREAK)(void);

typedef bool (EFI_API *EFI_SHELL_IS_ROOT_SHELL)(void);

typedef EFI_STATUS (EFI_API *EFI_SHELL_OPEN_FILE_BY_NAME)(
    const uint16_t *FileName,
    EFI_SHELL_FILE_HANDLE *FileHandle,
    uint64_t OpenMode
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_OPEN_FILE_LIST)(
    uint16_t *Path,
    uint64_t OpenMode,
    struct efi_shell_file_info **FileList
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_OPEN_ROOT)(
    struct efi_device_path_protocol *DevicePath,
    EFI_SHELL_FILE_HANDLE *FileHandle
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_OPEN_ROOT_BY_HANDLE)(
    EFI_HANDLE DeviceHandle,
    EFI_SHELL_FILE_HANDLE *FileHandle
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_READ_FILE)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    size_t *ReadSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_REGISTER_GUID_NAME)(
    const struct efi_guid *Guid,
    const uint16_t *GuidName
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_REMOVE_DUP_IN_FILE_LIST)(
    struct efi_shell_file_info **FileList
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_ALIAS)(
    const uint16_t *Command,
    const uint16_t *Alias,
    bool Replace,
    bool Volatile
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_CUR_DIR)(
    const uint16_t *FileSystem,
    const uint16_t *Dir
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_ENV)(
    const uint16_t *Name,
    const uint16_t *Value,
    bool Volatile
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_FILE_INFO)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    const struct efi_file_info *FileInfo
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_FILE_POSITION)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    uint64_t Position
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_SET_MAP)(
    const struct efi_device_path_protocol *DevicePath,
    const uint16_t *Mapping
);

typedef EFI_STATUS (EFI_API *EFI_SHELL_WRITE_FILE)(
    EFI_SHELL_FILE_HANDLE FileHandle,
    size_t *BufferSize,
    void *Buffer
);

struct efi_shell_protocol {
    EFI_SHELL_EXECUTE Execute;
    EFI_SHELL_GET_ENV GetEnv;
    EFI_SHELL_SET_ENV SetEnv;
    EFI_SHELL_GET_ALIAS GetAlias;
    EFI_SHELL_SET_ALIAS SetAlias;
    EFI_SHELL_GET_HELP_TEXT GetHelpText;
    EFI_SHELL_GET_DEVICE_PATH_FROM_MAP GetDevicePathFromMap;
    EFI_SHELL_GET_MAP_FROM_DEVICE_PATH GetMapFromDevicePath;
    EFI_SHELL_GET_DEVICE_PATH_FROM_FILE_PATH GetDevicePathFromFilePath;
    EFI_SHELL_GET_FILE_PATH_FROM_DEVICE_PATH GetFilePathFromDevicePath;
    EFI_SHELL_SET_MAP SetMap;

    EFI_SHELL_GET_CUR_DIR GetCurDir;
    EFI_SHELL_SET_CUR_DIR SetCurDir;
    EFI_SHELL_OPEN_FILE_LIST OpenFileList;
    EFI_SHELL_FREE_FILE_LIST FreeFileList;
    EFI_SHELL_REMOVE_DUP_IN_FILE_LIST RemoveDupInFileList;

    EFI_SHELL_BATCH_IS_ACTIVE BatchIsActive;
    EFI_SHELL_IS_ROOT_SHELL IsRootShell;
    EFI_SHELL_ENABLE_PAGE_BREAK EnablePageBreak;
    EFI_SHELL_DISABLE_PAGE_BREAK DisablePageBreak;
    EFI_SHELL_GET_PAGE_BREAK GetPageBreak;
    EFI_SHELL_GET_DEVICE_NAME GetDeviceName;

    EFI_SHELL_GET_FILE_INFO GetFileInfo;
    EFI_SHELL_SET_FILE_INFO SetFileInfo;
    EFI_SHELL_OPEN_FILE_BY_NAME OpenFileByName;
    EFI_SHELL_CLOSE_FILE CloseFile;
    EFI_SHELL_CREATE_FILE CreateFile;
    EFI_SHELL_READ_FILE ReadFile;
    EFI_SHELL_WRITE_FILE WriteFile;
    EFI_SHELL_DELETE_FILE DeleteFile;
    EFI_SHELL_DELETE_FILE_BY_NAME DeleteFileByName;
    EFI_SHELL_GET_FILE_POSITION GetFilePosition;
    EFI_SHELL_SET_FILE_POSITION SetFilePosition;
    EFI_SHELL_FLUSH_FILE FlushFile;
    EFI_SHELL_FIND_FILES FindFiles;
    EFI_SHELL_FIND_FILES_IN_DIR FindFilesInDir;
    EFI_SHELL_GET_FILE_SIZE GetFileSize;

    EFI_SHELL_OPEN_ROOT OpenRoot;
    EFI_SHELL_OPEN_ROOT_BY_HANDLE OpenRootByHandle;

    EFI_EVENT ExecutionBreak;

    uint32_t MajorVersion;
    uint32_t MinorVersion;
    /* The last four members exist from version 2.1 on. */
    EFI_SHELL_REGISTER_GUID_NAME RegisterGuidName;
    EFI_SHELL_GET_GUID_NAME GetGuidName;
    EFI_SHELL_GET_GUID_FROM_NAME GetGuidFromName;
    EFI_SHELL_GET_ENV_EX GetEnvEx;
};

#define EFI_SHELL_PARAMETERS_PROTOCOL_GUID \
    {0x752f3136, 0x4e16, 0x4fdc, {0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca}}

struct efi_shell_parameters_protocol {
    uint16_t **Argv;
    size_t Argc;
    EFI_SHELL_FILE_HANDLE StdIn;
    EFI_SHELL_FILE_HANDLE StdOut;
    EFI_SHELL_FILE_HANDLE StdErr;
};

#define EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL_GUID \
    {0x3c7200e9, 0x5f, 0x4ea4, {0x87, 0xde, 0xa3, 0xdf, 0xac, 0x8a, 0x27, 0xc3}}

struct efi_shell_dynamic_command_protocol;

typedef EFI_STATUS (EFI_API *EFI_SHELL_COMMAND_HANDLER)(
    struct efi_shell_dynamic_command_protocol *This,
    struct efi_system_table *SystemTable,
    struct efi_shell_parameters_protocol *ShellParameters,
    struct efi_shell_protocol *Shell
);

typedef uint16_t *(EFI_API *EFI_SHELL_COMMAND_GETHELP)(
    struct efi_shell_dynamic_command_protocol *This,
    const char *Language
);

struct efi_shell_dynamic_command_protocol {
    const uint16_t *CommandName;
    EFI_SHELL_COMMAND_HANDLER Handler;
    EFI_SHELL_COMMAND_GETHELP GetHelp;
};

typedef enum {
    EFI_SHELL_SUCCESS = 0,
    EFI_SHELL_LOAD_ERROR = 1,
    EFI_SHELL_INVALID_PARAMETER = 2,
    EFI_SHELL_UNSUPPORTED = 3,
    EFI_SHELL_BAD_BUFFER_SIZE = 4,
    EFI_SHELL_BUFFER_TOO_SMALL = 5,
    EFI_SHELL_NOT_READY = 6,
    EFI_SHELL_DEVICE_ERROR = 7,
    EFI_SHELL_WRITE_PROTECTED = 8,
    EFI_SHELL_OUT_OF_RESOURCES = 9,
    EFI_SHELL_VOLUME_CORRUPTED = 10,
    EFI_SHELL_VOLUME_FULL = 11,
    EFI_SHELL_NO_MEDIA = 12,
    EFI_SHELL_MEDIA_CHANGED = 13,
    EFI_SHELL_NOT_FOUND = 14,
    EFI_SHELL_ACCESS_DENIED = 15,
    EFI_SHELL_TIMEOUT = 18,
    EFI_SHELL_NOT_STARTED = 19,
    EFI_SHELL_ALREADY_STARTED = 20,
    EFI_SHELL_ABORTED = 21,
    EFI_SHELL_INCOMPATIBLE_VERSION = 25,
    EFI_SHELL_SECURITY_VIOLATION = 26,
    EFI_SHELL_NOT_EQUAL = 27
} EFI_SHELL_STATUS;

#ifdef __cplusplus
}
#endif

#endif
