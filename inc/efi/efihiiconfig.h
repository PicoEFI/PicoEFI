#ifndef EFI_EFIHIICONFIG_H_
#define EFI_EFIHIICONFIG_H_

#include "efihiiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_GUID \
    {0x0a8badd5, 0x03b8, 0x4d19, {0xb1, 0x28, 0x7b, 0x8f, 0x0e, 0xda, 0xa5, 0x96}}

struct efi_config_keyword_handler_protocol;

/* Named as the protocol structure names them; the prototypes print EFI_KEYWORD_HANDLER_*. */
typedef EFI_STATUS (EFI_API *EFI_CONFIG_KEYWORD_HANDLER_SET_DATA)(
    struct efi_config_keyword_handler_protocol *This,
    const EFI_STRING KeywordString,
    EFI_STRING *Progress,
    uint32_t *ProgressErr
);

#define EFI_KEYWORD_HANDLER_NO_ERROR 0x00000000
#define EFI_KEYWORD_HANDLER_NAMESPACE_ID_NOT_FOUND 0x00000001
#define EFI_KEYWORD_HANDLER_MALFORMED_STRING 0x00000002
#define EFI_KEYWORD_HANDLER_KEYWORD_NOT_FOUND 0x00000004
#define EFI_KEYWORD_HANDLER_INCOMPATIBLE_VALUE_DETECTED 0x00000008
#define EFI_KEYWORD_HANDLER_ACCESS_NOT_PERMITTED 0x00000010
#define EFI_KEYWORD_HANDLER_UNDEFINED_PROCESSING_ERROR 0x80000000

typedef EFI_STATUS (EFI_API *EFI_CONFIG_KEYWORD_HANDLER_GET_DATA)(
    struct efi_config_keyword_handler_protocol *This,
    const EFI_STRING NameSpaceId,
    const EFI_STRING KeywordString,
    EFI_STRING *Progress,
    uint32_t *ProgressErr,
    EFI_STRING *Results
);

struct efi_config_keyword_handler_protocol {
    EFI_CONFIG_KEYWORD_HANDLER_SET_DATA SetData;
    EFI_CONFIG_KEYWORD_HANDLER_GET_DATA GetData;
};

#define EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID \
    {0x587e72d7, 0xcc50, 0x4f79, {0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f}}

struct efi_hii_config_routing_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_EXTRACT_CONFIG)(
    const struct efi_hii_config_routing_protocol *This,
    const EFI_STRING Request,
    EFI_STRING *Progress,
    EFI_STRING *Results
);

typedef EFI_STATUS (EFI_API *EFI_HII_EXPORT_CONFIG)(
    const struct efi_hii_config_routing_protocol *This,
    EFI_STRING *Results
);

typedef EFI_STATUS (EFI_API *EFI_HII_ROUTE_CONFIG)(
    const struct efi_hii_config_routing_protocol *This,
    const EFI_STRING Configuration,
    EFI_STRING *Progress
);

typedef EFI_STATUS (EFI_API *EFI_HII_BLOCK_TO_CONFIG)(
    const struct efi_hii_config_routing_protocol *This,
    const EFI_STRING ConfigRequest,
    const uint8_t *Block,
    const size_t BlockSize,
    EFI_STRING *Config,
    EFI_STRING *Progress
);

/*
 * Printed with ConfigResp as a pointer to an EFI_STRING and Block as const: ConfigResp is
 * described as the string itself, and the function writes the block.
 */
typedef EFI_STATUS (EFI_API *EFI_HII_CONFIG_TO_BLOCK)(
    const struct efi_hii_config_routing_protocol *This,
    const EFI_STRING ConfigResp,
    uint8_t *Block,
    size_t *BlockSize,
    EFI_STRING *Progress
);

typedef EFI_STATUS (EFI_API *EFI_HII_GET_ALT_CFG)(
    const struct efi_hii_config_routing_protocol *This,
    const EFI_STRING ConfigResp,
    const struct efi_guid *Guid,
    const EFI_STRING Name,
    const struct efi_device_path_protocol *DevicePath,
    const EFI_STRING AltCfgId,
    EFI_STRING *AltCfgResp
);

struct efi_hii_config_routing_protocol {
    EFI_HII_EXTRACT_CONFIG ExtractConfig;
    EFI_HII_EXPORT_CONFIG ExportConfig;
    EFI_HII_ROUTE_CONFIG RouteConfig;
    EFI_HII_BLOCK_TO_CONFIG BlockToConfig;
    EFI_HII_CONFIG_TO_BLOCK ConfigToBlock;
    EFI_HII_GET_ALT_CFG GetAltConfig;
};

#define EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID \
    {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85}}

struct efi_hii_config_access_protocol;

typedef EFI_STATUS (EFI_API *EFI_HII_ACCESS_EXTRACT_CONFIG)(
    const struct efi_hii_config_access_protocol *This,
    const EFI_STRING Request,
    EFI_STRING *Progress,
    EFI_STRING *Results
);

typedef EFI_STATUS (EFI_API *EFI_HII_ACCESS_ROUTE_CONFIG)(
    const struct efi_hii_config_access_protocol *This,
    const EFI_STRING Configuration,
    EFI_STRING *Progress
);

typedef uintptr_t EFI_BROWSER_ACTION;

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

typedef uintptr_t EFI_BROWSER_ACTION_REQUEST;

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

typedef EFI_STATUS (EFI_API *EFI_HII_ACCESS_FORM_CALLBACK)(
    const struct efi_hii_config_access_protocol *This,
    EFI_BROWSER_ACTION Action,
    EFI_QUESTION_ID QuestionId,
    uint8_t Type,
    union efi_ifr_type_value *Value,
    EFI_BROWSER_ACTION_REQUEST *ActionRequest
);

struct efi_hii_config_access_protocol {
    EFI_HII_ACCESS_EXTRACT_CONFIG ExtractConfig;
    EFI_HII_ACCESS_ROUTE_CONFIG RouteConfig;
    EFI_HII_ACCESS_FORM_CALLBACK Callback;
};

#define EFI_FORM_BROWSER2_PROTOCOL_GUID \
    {0xb9d4c360, 0xbcfb, 0x4f9b, {0x92, 0x98, 0x53, 0xc1, 0x36, 0x98, 0x22, 0x58}}

struct efi_form_browser2_protocol;

struct efi_screen_descriptor {
    size_t LeftColumn;
    size_t RightColumn;
    size_t TopRow;
    size_t BottomRow;
};

typedef EFI_STATUS (EFI_API *EFI_SEND_FORM2)(
    const struct efi_form_browser2_protocol *This,
    EFI_HII_HANDLE *Handles,
    size_t HandleCount,
    const struct efi_guid *FormsetGuid,
    EFI_FORM_ID FormId,
    const struct efi_screen_descriptor *ScreenDimensions,
    EFI_BROWSER_ACTION_REQUEST *ActionRequest
);

#define EFI_HII_PLATFORM_SETUP_FORMSET_GUID \
    {0x93039971, 0x8545, 0x4b04, {0xb4, 0x5e, 0x32, 0xeb, 0x83, 0x26, 0x04, 0x0e}}

#define EFI_HII_DRIVER_HEALTH_FORMSET_GUID \
    {0xf22fc20c, 0x8cf4, 0x45eb, {0x8e, 0x06, 0xad, 0x4e, 0x50, 0xb9, 0x5d, 0xd3}}

#define EFI_HII_USER_CREDENTIAL_FORMSET_GUID \
    {0x337f4407, 0x5aee, 0x4b83, {0xb2, 0xa7, 0x4e, 0xad, 0xca, 0x30, 0x88, 0xcd}}

#define EFI_HII_REST_STYLE_FORMSET_GUID \
    {0x790217bd, 0xbecf, 0x485b, {0x91, 0x70, 0x5f, 0xf7, 0x11, 0x31, 0x8b, 0x27}}

typedef EFI_STATUS (EFI_API *EFI_BROWSER_CALLBACK2)(
    const struct efi_form_browser2_protocol *This,
    size_t *ResultsDataSize,
    EFI_STRING ResultsData,
    bool RetrieveData,
    const struct efi_guid *VariableGuid,
    const uint16_t *VariableName
);

struct efi_form_browser2_protocol {
    EFI_SEND_FORM2 SendForm;
    EFI_BROWSER_CALLBACK2 BrowserCallback;
};

#define EFI_HII_POPUP_PROTOCOL_GUID \
    {0x4311edc0, 0x6054, 0x46d4, {0x9e, 0x40, 0x89, 0x3e, 0xa9, 0x52, 0xfc, 0xcc}}

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

typedef EFI_STATUS (EFI_API *EFI_HII_CREATE_POPUP)(
    struct efi_hii_popup_protocol *This,
    uint32_t PopupStyle,
    uint32_t PopupType,
    EFI_HII_HANDLE HiiHandle,
    EFI_STRING_ID Message,
    uint32_t *UserSelection
);

struct efi_hii_popup_protocol {
    uint64_t Revision;
    EFI_HII_CREATE_POPUP CreatePopup;
};

#ifdef __cplusplus
}
#endif

#endif
