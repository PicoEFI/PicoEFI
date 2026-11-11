#ifndef EFI_EFIHIICONFIG_H
#define EFI_EFIHIICONFIG_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>
#include <efi/efihii.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_GUID \
    { 0x0a8badd5, 0x03b8, 0x4d19, { 0xb1, 0x28, 0x7b, 0x8f, 0x0e, 0xda, 0xa5, 0x96 } }

struct efi_config_keyword_handler_protocol;

// Named as the protocol structure names them; the prototypes print
// EFI_KEYWORD_HANDLER_*.
typedef efi_status (EFI_API *efi_config_keyword_handler_set_data)(
    struct efi_config_keyword_handler_protocol *self,
    const efi_string keyword_string,
    efi_string *progress,
    uint32_t *progress_err
);

#define EFI_KEYWORD_HANDLER_NO_ERROR 0x00000000
#define EFI_KEYWORD_HANDLER_NAMESPACE_ID_NOT_FOUND 0x00000001
#define EFI_KEYWORD_HANDLER_MALFORMED_STRING 0x00000002
#define EFI_KEYWORD_HANDLER_KEYWORD_NOT_FOUND 0x00000004
#define EFI_KEYWORD_HANDLER_INCOMPATIBLE_VALUE_DETECTED 0x00000008
#define EFI_KEYWORD_HANDLER_ACCESS_NOT_PERMITTED 0x00000010
#define EFI_KEYWORD_HANDLER_UNDEFINED_PROCESSING_ERROR 0x80000000

typedef efi_status (EFI_API *efi_config_keyword_handler_get_data)(
    struct efi_config_keyword_handler_protocol *self,
    const efi_string name_space_id,
    const efi_string keyword_string,
    efi_string *progress,
    uint32_t *progress_err,
    efi_string *results
);

struct efi_config_keyword_handler_protocol {
    efi_config_keyword_handler_set_data set_data;
    efi_config_keyword_handler_get_data get_data;
};

#define EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID \
    { 0x587e72d7, 0xcc50, 0x4f79, { 0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f } }

struct efi_hii_config_routing_protocol;

typedef efi_status (EFI_API *efi_hii_extract_config)(
    const struct efi_hii_config_routing_protocol *self,
    const efi_string request,
    efi_string *progress,
    efi_string *results
);

typedef efi_status (EFI_API *efi_hii_export_config)(
    const struct efi_hii_config_routing_protocol *self,
    efi_string *results
);

typedef efi_status (EFI_API *efi_hii_route_config)(
    const struct efi_hii_config_routing_protocol *self,
    const efi_string configuration,
    efi_string *progress
);

typedef efi_status (EFI_API *efi_hii_block_to_config)(
    const struct efi_hii_config_routing_protocol *self,
    const efi_string config_request,
    const uint8_t *block,
    const size_t block_size,
    efi_string *config,
    efi_string *progress
);

// Printed with config_resp as a pointer to an efi_string and block as const:
// config_resp is described as the string itself, and the function writes the
// block.
typedef efi_status (EFI_API *efi_hii_config_to_block)(
    const struct efi_hii_config_routing_protocol *self,
    const efi_string config_resp,
    uint8_t *block,
    size_t *block_size,
    efi_string *progress
);

typedef efi_status (EFI_API *efi_hii_get_alt_cfg)(
    const struct efi_hii_config_routing_protocol *self,
    const efi_string config_resp,
    const struct efi_guid *guid,
    const efi_string name,
    const struct efi_device_path_protocol *device_path,
    const efi_string alt_cfg_id,
    efi_string *alt_cfg_resp
);

struct efi_hii_config_routing_protocol {
    efi_hii_extract_config extract_config;
    efi_hii_export_config export_config;
    efi_hii_route_config route_config;
    efi_hii_block_to_config block_to_config;
    efi_hii_config_to_block config_to_block;
    efi_hii_get_alt_cfg get_alt_config;
};

#define EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID \
    { 0x330d4706, 0xf2a0, 0x4e4f, { 0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85 } }

struct efi_hii_config_access_protocol;

typedef efi_status (EFI_API *efi_hii_access_extract_config)(
    const struct efi_hii_config_access_protocol *self,
    const efi_string request,
    efi_string *progress,
    efi_string *results
);

typedef efi_status (EFI_API *efi_hii_access_route_config)(
    const struct efi_hii_config_access_protocol *self,
    const efi_string configuration,
    efi_string *progress
);

typedef size_t efi_browser_action;

#define EFI_BROWSER_ACTION_CHANGING 0
#define EFI_BROWSER_ACTION_CHANGED 1
#define EFI_BROWSER_ACTION_RETRIEVE 2
#define EFI_BROWSER_ACTION_FORM_OPEN 3
#define EFI_BROWSER_ACTION_FORM_CLOSE 4
#define EFI_BROWSER_ACTION_SUBMITTED 5
#define EFI_BROWSER_ACTION_DEFAULT_STANDARD 0x1000
#define EFI_BROWSER_ACTION_DEFAULT_MANUFACTURING 0x1001
#define EFI_BROWSER_ACTION_DEFAULT_SAFE 0x1002
#define EFI_BROWSER_ACTION_DEFAULT_PLATFORM 0x2000
#define EFI_BROWSER_ACTION_DEFAULT_HARDWARE 0x3000
#define EFI_BROWSER_ACTION_DEFAULT_FIRMWARE 0x4000

typedef size_t efi_browser_action_request;

#define EFI_BROWSER_ACTION_REQUEST_NONE 0
#define EFI_BROWSER_ACTION_REQUEST_RESET 1
#define EFI_BROWSER_ACTION_REQUEST_SUBMIT 2
#define EFI_BROWSER_ACTION_REQUEST_EXIT 3
#define EFI_BROWSER_ACTION_REQUEST_FORM_SUBMIT_EXIT 4
#define EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD_EXIT 5
#define EFI_BROWSER_ACTION_REQUEST_FORM_APPLY 6
#define EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD 7
#define EFI_BROWSER_ACTION_REQUEST_RECONNECT 8
#define EFI_BROWSER_ACTION_REQUEST_QUESTION_APPLY 9

typedef efi_status (EFI_API *efi_hii_access_form_callback)(
    const struct efi_hii_config_access_protocol *self,
    efi_browser_action action,
    efi_question_id question_id,
    uint8_t type,
    union efi_ifr_type_value *value,
    efi_browser_action_request *action_request
);

struct efi_hii_config_access_protocol {
    efi_hii_access_extract_config extract_config;
    efi_hii_access_route_config route_config;
    efi_hii_access_form_callback callback;
};

#define EFI_FORM_BROWSER2_PROTOCOL_GUID \
    { 0xb9d4c360, 0xbcfb, 0x4f9b, { 0x92, 0x98, 0x53, 0xc1, 0x36, 0x98, 0x22, 0x58 } }

struct efi_form_browser2_protocol;

struct efi_screen_descriptor {
    size_t left_column;
    size_t right_column;
    size_t top_row;
    size_t bottom_row;
};

typedef efi_status (EFI_API *efi_send_form2)(
    const struct efi_form_browser2_protocol *self,
    efi_hii_handle *handles,
    size_t handle_count,
    const struct efi_guid *formset_guid,
    efi_form_id form_id,
    const struct efi_screen_descriptor *screen_dimensions,
    efi_browser_action_request *action_request
);

#define EFI_HII_PLATFORM_SETUP_FORMSET_GUID \
    { 0x93039971, 0x8545, 0x4b04, { 0xb4, 0x5e, 0x32, 0xeb, 0x83, 0x26, 0x04, 0x0e } }

#define EFI_HII_DRIVER_HEALTH_FORMSET_GUID \
    { 0xf22fc20c, 0x8cf4, 0x45eb, { 0x8e, 0x06, 0xad, 0x4e, 0x50, 0xb9, 0x5d, 0xd3 } }

#define EFI_HII_USER_CREDENTIAL_FORMSET_GUID \
    { 0x337f4407, 0x5aee, 0x4b83, { 0xb2, 0xa7, 0x4e, 0xad, 0xca, 0x30, 0x88, 0xcd } }

#define EFI_HII_REST_STYLE_FORMSET_GUID \
    { 0x790217bd, 0xbecf, 0x485b, { 0x91, 0x70, 0x5f, 0xf7, 0x11, 0x31, 0x8b, 0x27 } }

typedef efi_status (EFI_API *efi_browser_callback2)(
    const struct efi_form_browser2_protocol *self,
    size_t *results_data_size,
    efi_string results_data,
    bool retrieve_data,
    const struct efi_guid *variable_guid,
    const uint16_t *variable_name
);

struct efi_form_browser2_protocol {
    efi_send_form2 send_form;
    efi_browser_callback2 browser_callback;
};

#define EFI_HII_POPUP_PROTOCOL_GUID \
    { 0x4311edc0, 0x6054, 0x46d4, { 0x9e, 0x40, 0x89, 0x3e, 0xa9, 0x52, 0xfc, 0xcc } }

#define EFI_HII_POPUP_PROTOCOL_REVISION 1

struct efi_hii_popup_protocol;

#define EFI_HII_POPUP_STYLE_INFO ((uint32_t)0)
#define EFI_HII_POPUP_STYLE_WARNING ((uint32_t)1)
#define EFI_HII_POPUP_STYLE_ERROR ((uint32_t)2)

#define EFI_HII_POPUP_TYPE_OK ((uint32_t)0)
#define EFI_HII_POPUP_TYPE_OK_CANCEL ((uint32_t)1)
#define EFI_HII_POPUP_TYPE_YES_NO ((uint32_t)2)
#define EFI_HII_POPUP_TYPE_YES_NO_CANCEL ((uint32_t)3)

#define EFI_HII_POPUP_SELECTION_OK ((uint32_t)0)
#define EFI_HII_POPUP_SELECTION_CANCEL ((uint32_t)1)
#define EFI_HII_POPUP_SELECTION_YES ((uint32_t)2)
#define EFI_HII_POPUP_SELECTION_NO ((uint32_t)3)

typedef efi_status (EFI_API *efi_hii_create_popup)(
    struct efi_hii_popup_protocol *self,
    uint32_t popup_style,
    uint32_t popup_type,
    efi_hii_handle hii_handle,
    efi_string_id message,
    uint32_t *user_selection
);

struct efi_hii_popup_protocol {
    uint64_t revision;
    efi_hii_create_popup create_popup;
};

#ifdef __cplusplus
}
#endif

#endif
