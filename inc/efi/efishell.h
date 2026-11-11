#ifndef EFI_EFISHELL_H
#define EFI_EFISHELL_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efiapi.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>
#include <efi/efiprot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_SHELL_MAJOR_VERSION 2
#define EFI_SHELL_MINOR_VERSION 2

#define EFI_SHELL_PROTOCOL_GUID \
    {0x6302d008, 0x7f9b, 0x4f30, {0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e}}

typedef void *efi_shell_file_handle;

struct efi_list_entry {
    struct efi_list_entry *flink;
    struct efi_list_entry *blink;
};

struct efi_shell_file_info {
    struct efi_list_entry link;
    efi_status status;
    const uint16_t *full_name;
    const uint16_t *file_name;
    efi_shell_file_handle handle;
    struct efi_file_info *info;
};

typedef uint32_t efi_device_name_flags;

/* The prototype of get_device_name() spells the flags type this way. */
typedef efi_device_name_flags efi_shell_device_name_flags;

#define EFI_DEVICE_NAME_USE_COMPONENT_NAME 0x00000001
#define EFI_DEVICE_NAME_USE_DEVICE_PATH 0x00000002

typedef bool (EFI_API *efi_shell_batch_is_active)(void);

typedef efi_status (EFI_API *efi_shell_close_file)(efi_shell_file_handle file_handle);

typedef efi_status (EFI_API *efi_shell_create_file)(
    const uint16_t *file_name,
    uint64_t file_attribs,
    efi_shell_file_handle *file_handle
);

typedef efi_status (EFI_API *efi_shell_delete_file)(efi_shell_file_handle file_handle);

typedef efi_status (EFI_API *efi_shell_delete_file_by_name)(const uint16_t *file_name);

typedef void (EFI_API *efi_shell_disable_page_break)(void);

typedef void (EFI_API *efi_shell_enable_page_break)(void);

typedef efi_status (EFI_API *efi_shell_execute)(
    efi_handle *parent_image_handle,
    uint16_t *command_line,
    uint16_t **environment,
    efi_status *status_code
);

typedef efi_status (EFI_API *efi_shell_find_files)(
    const uint16_t *file_pattern,
    struct efi_shell_file_info **file_list
);

typedef efi_status (EFI_API *efi_shell_find_files_in_dir)(
    efi_shell_file_handle file_dir_handle,
    struct efi_shell_file_info **file_list
);

typedef efi_status (EFI_API *efi_shell_flush_file)(efi_shell_file_handle file_handle);

typedef efi_status (EFI_API *efi_shell_free_file_list)(struct efi_shell_file_info **file_list);

typedef const uint16_t *(EFI_API *efi_shell_get_alias)(
    const uint16_t *alias,
    bool *volatile_
);

typedef const uint16_t *(EFI_API *efi_shell_get_cur_dir)(
    const uint16_t *file_system_mapping
);

typedef efi_status (EFI_API *efi_shell_get_device_name)(
    efi_handle device_handle,
    efi_shell_device_name_flags flags,
    char *language,
    uint16_t **best_device_name
);

typedef const struct efi_device_path_protocol *(EFI_API *efi_shell_get_device_path_from_map)(
    const uint16_t *mapping
);

typedef struct efi_device_path_protocol *(EFI_API *efi_shell_get_device_path_from_file_path)(
    const uint16_t *path
);

typedef const uint16_t *(EFI_API *efi_shell_get_env)(const uint16_t *name);

typedef const uint16_t *(EFI_API *efi_shell_get_env_ex)(
    const uint16_t *name,
    uint32_t *attributes
);

typedef struct efi_file_info *(EFI_API *efi_shell_get_file_info)(efi_shell_file_handle file_handle);

typedef uint16_t *(EFI_API *efi_shell_get_file_path_from_device_path)(
    const struct efi_device_path_protocol *path
);

typedef efi_status (EFI_API *efi_shell_get_file_position)(
    efi_shell_file_handle file_handle,
    uint64_t *position
);

typedef efi_status (EFI_API *efi_shell_get_file_size)(
    efi_shell_file_handle file_handle,
    uint64_t *size
);

typedef efi_status (EFI_API *efi_shell_get_guid_from_name)(
    const uint16_t *guid_name,
    struct efi_guid *guid
);

typedef efi_status (EFI_API *efi_shell_get_guid_name)(
    const struct efi_guid *guid,
    const uint16_t **guid_name
);

typedef efi_status (EFI_API *efi_shell_get_help_text)(
    const uint16_t *command,
    const uint16_t *sections,
    uint16_t **help_text
);

typedef const uint16_t *(EFI_API *efi_shell_get_map_from_device_path)(
    struct efi_device_path_protocol **device_path
);

typedef bool (EFI_API *efi_shell_get_page_break)(void);

typedef bool (EFI_API *efi_shell_is_root_shell)(void);

typedef efi_status (EFI_API *efi_shell_open_file_by_name)(
    const uint16_t *file_name,
    efi_shell_file_handle *file_handle,
    uint64_t open_mode
);

typedef efi_status (EFI_API *efi_shell_open_file_list)(
    uint16_t *path,
    uint64_t open_mode,
    struct efi_shell_file_info **file_list
);

typedef efi_status (EFI_API *efi_shell_open_root)(
    struct efi_device_path_protocol *device_path,
    efi_shell_file_handle *file_handle
);

typedef efi_status (EFI_API *efi_shell_open_root_by_handle)(
    efi_handle device_handle,
    efi_shell_file_handle *file_handle
);

typedef efi_status (EFI_API *efi_shell_read_file)(
    efi_shell_file_handle file_handle,
    size_t *read_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_shell_register_guid_name)(
    const struct efi_guid *guid,
    const uint16_t *guid_name
);

typedef efi_status (EFI_API *efi_shell_remove_dup_in_file_list)(
    struct efi_shell_file_info **file_list
);

typedef efi_status (EFI_API *efi_shell_set_alias)(
    const uint16_t *command,
    const uint16_t *alias,
    bool replace,
    bool volatile_
);

typedef efi_status (EFI_API *efi_shell_set_cur_dir)(
    const uint16_t *file_system,
    const uint16_t *dir
);

typedef efi_status (EFI_API *efi_shell_set_env)(
    const uint16_t *name,
    const uint16_t *value,
    bool volatile_
);

typedef efi_status (EFI_API *efi_shell_set_file_info)(
    efi_shell_file_handle file_handle,
    const struct efi_file_info *file_info
);

typedef efi_status (EFI_API *efi_shell_set_file_position)(
    efi_shell_file_handle file_handle,
    uint64_t position
);

typedef efi_status (EFI_API *efi_shell_set_map)(
    const struct efi_device_path_protocol *device_path,
    const uint16_t *mapping
);

typedef efi_status (EFI_API *efi_shell_write_file)(
    efi_shell_file_handle file_handle,
    size_t *buffer_size,
    void *buffer
);

struct efi_shell_protocol {
    efi_shell_execute execute;
    efi_shell_get_env get_env;
    efi_shell_set_env set_env;
    efi_shell_get_alias get_alias;
    efi_shell_set_alias set_alias;
    efi_shell_get_help_text get_help_text;
    efi_shell_get_device_path_from_map get_device_path_from_map;
    efi_shell_get_map_from_device_path get_map_from_device_path;
    efi_shell_get_device_path_from_file_path get_device_path_from_file_path;
    efi_shell_get_file_path_from_device_path get_file_path_from_device_path;
    efi_shell_set_map set_map;

    efi_shell_get_cur_dir get_cur_dir;
    efi_shell_set_cur_dir set_cur_dir;
    efi_shell_open_file_list open_file_list;
    efi_shell_free_file_list free_file_list;
    efi_shell_remove_dup_in_file_list remove_dup_in_file_list;

    efi_shell_batch_is_active batch_is_active;
    efi_shell_is_root_shell is_root_shell;
    efi_shell_enable_page_break enable_page_break;
    efi_shell_disable_page_break disable_page_break;
    efi_shell_get_page_break get_page_break;
    efi_shell_get_device_name get_device_name;

    efi_shell_get_file_info get_file_info;
    efi_shell_set_file_info set_file_info;
    efi_shell_open_file_by_name open_file_by_name;
    efi_shell_close_file close_file;
    efi_shell_create_file create_file;
    efi_shell_read_file read_file;
    efi_shell_write_file write_file;
    efi_shell_delete_file delete_file;
    efi_shell_delete_file_by_name delete_file_by_name;
    efi_shell_get_file_position get_file_position;
    efi_shell_set_file_position set_file_position;
    efi_shell_flush_file flush_file;
    efi_shell_find_files find_files;
    efi_shell_find_files_in_dir find_files_in_dir;
    efi_shell_get_file_size get_file_size;

    efi_shell_open_root open_root;
    efi_shell_open_root_by_handle open_root_by_handle;

    efi_event execution_break;

    uint32_t major_version;
    uint32_t minor_version;
    /* The last four members exist from version 2.1 on. */
    efi_shell_register_guid_name register_guid_name;
    efi_shell_get_guid_name get_guid_name;
    efi_shell_get_guid_from_name get_guid_from_name;
    efi_shell_get_env_ex get_env_ex;
};

#define EFI_SHELL_PARAMETERS_PROTOCOL_GUID \
    {0x752f3136, 0x4e16, 0x4fdc, {0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca}}

struct efi_shell_parameters_protocol {
    uint16_t **argv;
    size_t argc;
    efi_shell_file_handle std_in;
    efi_shell_file_handle std_out;
    efi_shell_file_handle std_err;
};

#define EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL_GUID \
    {0x3c7200e9, 0x5f, 0x4ea4, {0x87, 0xde, 0xa3, 0xdf, 0xac, 0x8a, 0x27, 0xc3}}

struct efi_shell_dynamic_command_protocol;

typedef efi_status (EFI_API *efi_shell_command_handler)(
    struct efi_shell_dynamic_command_protocol *self,
    struct efi_system_table *system_table,
    struct efi_shell_parameters_protocol *shell_parameters,
    struct efi_shell_protocol *shell
);

typedef uint16_t *(EFI_API *efi_shell_command_gethelp)(
    struct efi_shell_dynamic_command_protocol *self,
    const char *language
);

struct efi_shell_dynamic_command_protocol {
    const uint16_t *command_name;
    efi_shell_command_handler handler;
    efi_shell_command_gethelp get_help;
};

#define EFI_SHELL_SUCCESS ((uint32_t)0)
#define EFI_SHELL_LOAD_ERROR ((uint32_t)1)
#define EFI_SHELL_INVALID_PARAMETER ((uint32_t)2)
#define EFI_SHELL_UNSUPPORTED ((uint32_t)3)
#define EFI_SHELL_BAD_BUFFER_SIZE ((uint32_t)4)
#define EFI_SHELL_BUFFER_TOO_SMALL ((uint32_t)5)
#define EFI_SHELL_NOT_READY ((uint32_t)6)
#define EFI_SHELL_DEVICE_ERROR ((uint32_t)7)
#define EFI_SHELL_WRITE_PROTECTED ((uint32_t)8)
#define EFI_SHELL_OUT_OF_RESOURCES ((uint32_t)9)
#define EFI_SHELL_VOLUME_CORRUPTED ((uint32_t)10)
#define EFI_SHELL_VOLUME_FULL ((uint32_t)11)
#define EFI_SHELL_NO_MEDIA ((uint32_t)12)
#define EFI_SHELL_MEDIA_CHANGED ((uint32_t)13)
#define EFI_SHELL_NOT_FOUND ((uint32_t)14)
#define EFI_SHELL_ACCESS_DENIED ((uint32_t)15)
#define EFI_SHELL_TIMEOUT ((uint32_t)18)
#define EFI_SHELL_NOT_STARTED ((uint32_t)19)
#define EFI_SHELL_ALREADY_STARTED ((uint32_t)20)
#define EFI_SHELL_ABORTED ((uint32_t)21)
#define EFI_SHELL_INCOMPATIBLE_VERSION ((uint32_t)25)
#define EFI_SHELL_SECURITY_VIOLATION ((uint32_t)26)
#define EFI_SHELL_NOT_EQUAL ((uint32_t)27)

#ifdef __cplusplus
}
#endif

#endif
