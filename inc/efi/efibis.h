#ifndef EFI_EFIBIS_H
#define EFI_EFIBIS_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_BIS_PROTOCOL_GUID \
    { 0x0b64aab0, 0x5429, 0x11d4, { 0x98, 0x16, 0x00, 0xa0, 0xc9, 0x1f, 0xad, 0xcf } }

struct efi_bis_protocol;

typedef void *efi_bis_application_handle;

struct efi_bis_version {
    uint32_t major;
    uint32_t minor;
};

#define EFI_BIS_CURRENT_VERSION_MAJOR EFI_BIS_VERSION_1
#define EFI_BIS_VERSION_1 1

struct efi_bis_data {
    uint32_t length;
    uint8_t *data;
};

typedef efi_status (EFI_API *efi_bis_initialize)(
    struct efi_bis_protocol *self,
    efi_bis_application_handle *app_handle,
    struct efi_bis_version *interface_version,
    struct efi_bis_data *target_address
);

typedef efi_status (EFI_API *efi_bis_shutdown)(efi_bis_application_handle app_handle);

typedef efi_status (EFI_API *efi_bis_free)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data *to_free
);

typedef efi_status (EFI_API *efi_bis_get_boot_object_authorization_certificate)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data **certificate
);

typedef efi_status (EFI_API *efi_bis_get_boot_object_authorization_checkflag)(
    efi_bis_application_handle app_handle,
    bool *check_is_required
);

typedef efi_status (EFI_API *efi_bis_get_boot_object_authorization_update_token)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data **update_token
);

typedef uint32_t efi_bis_cert_id;

typedef uint16_t efi_bis_alg_id;

struct efi_bis_signature_info {
    efi_bis_cert_id certificate_id;
    efi_bis_alg_id algorithm_id;
    uint16_t key_length;
};

#define EFI_BIS_GET_SIGINFO_COUNT(bis_data_ptr) \
    ((bis_data_ptr)->length / sizeof(struct efi_bis_signature_info))

#define EFI_BIS_GET_SIGINFO_ARRAY(bis_data_ptr) \
    ((struct efi_bis_signature_info *)(bis_data_ptr)->data)

#define EFI_BIS_CERT_ID_DSA EFI_BIS_ALG_DSA
#define EFI_BIS_CERT_ID_RSA_MD5 EFI_BIS_ALG_RSA_MD5

#define EFI_BIS_CERT_ID_MASK (0xff7f7fff)

#define EFI_BIS_ALG_DSA (41)
#define EFI_BIS_ALG_RSA_MD5 (42)

typedef efi_status (EFI_API *efi_bis_get_signature_info)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data **signature_info
);

typedef efi_status (EFI_API *efi_bis_update_boot_object_authorization)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data *request_credential,
    struct efi_bis_data **new_update_token
);

#define EFI_BOOT_OBJECT_AUTHORIZATION_PARMSET_GUID \
    { 0xedd35e31, 0x7b9, 0x11d2, { 0x83, 0xa3, 0x0, 0xa0, 0xc9, 0x1f, 0xad, 0xcf } }

typedef efi_status (EFI_API *efi_bis_verify_boot_object)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data *credentials,
    struct efi_bis_data *data_object,
    bool *is_verified
);

typedef efi_status (EFI_API *efi_bis_verify_object_with_credential)(
    efi_bis_application_handle app_handle,
    struct efi_bis_data *credentials,
    struct efi_bis_data *data_object,
    struct efi_bis_data *section_name,
    struct efi_bis_data *authority_certificate,
    bool *is_verified
);

struct efi_bis_protocol {
    efi_bis_initialize initialize;
    efi_bis_shutdown shutdown;
    efi_bis_free free;
    efi_bis_get_boot_object_authorization_certificate get_boot_object_authorization_certificate;
    efi_bis_get_boot_object_authorization_checkflag get_boot_object_authorization_check_flag;
    efi_bis_get_boot_object_authorization_update_token get_boot_object_authorization_update_token;
    efi_bis_get_signature_info get_signature_info;
    efi_bis_update_boot_object_authorization update_boot_object_authorization;
    efi_bis_verify_boot_object verify_boot_object;
    efi_bis_verify_object_with_credential verify_object_with_credential;
};

#define EFI_HTTP_BOOT_CALLBACK_PROTOCOL_GUID \
    { 0xba23b311, 0x343d, 0x11e6, { 0x91, 0x85, 0x58, 0x20, 0xb1, 0xd6, 0x52, 0x99 } }

struct efi_http_boot_callback_protocol;

#define EFI_HTTP_BOOT_DHCP4 ((uint32_t)0)
#define EFI_HTTP_BOOT_DHCP6 ((uint32_t)1)
#define EFI_HTTP_BOOT_HTTP_REQUEST ((uint32_t)2)
#define EFI_HTTP_BOOT_HTTP_RESPONSE ((uint32_t)3)
#define EFI_HTTP_BOOT_HTTP_ENTITY_BODY ((uint32_t)4)
#define EFI_HTTP_BOOT_HTTP_AUTH_INFO ((uint32_t)5)
#define EFI_HTTP_BOOT_TYPE_MAX ((uint32_t)6)

typedef efi_status (EFI_API *efi_http_boot_callback)(
    struct efi_http_boot_callback_protocol *self,
    uint32_t data_type,
    bool received,
    uint32_t data_length,
    void *data
);

struct efi_http_boot_callback_protocol {
    efi_http_boot_callback callback;
};

#ifdef __cplusplus
}
#endif

#endif
