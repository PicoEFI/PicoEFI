#ifndef EFI_EFIBIS_H_
#define EFI_EFIBIS_H_

#include "efidef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_BIS_PROTOCOL_GUID \
    {0x0b64aab0, 0x5429, 0x11d4, {0x98, 0x16, 0x00, 0xa0, 0xc9, 0x1f, 0xad, 0xcf}}

struct efi_bis_protocol;

typedef void *EFI_BIS_APPLICATION_HANDLE;

struct efi_bis_version {
    uint32_t Major;
    uint32_t Minor;
};

#define EFI_BIS_CURRENT_VERSION_MAJOR EFI_BIS_VERSION_1
#define EFI_BIS_VERSION_1 1

struct efi_bis_data {
    uint32_t Length;
    uint8_t *Data;
};

typedef EFI_STATUS (EFI_API *EFI_BIS_INITIALIZE)(
    struct efi_bis_protocol *This,
    EFI_BIS_APPLICATION_HANDLE *AppHandle,
    struct efi_bis_version *InterfaceVersion,
    struct efi_bis_data *TargetAddress
);

typedef EFI_STATUS (EFI_API *EFI_BIS_SHUTDOWN)(EFI_BIS_APPLICATION_HANDLE AppHandle);

typedef EFI_STATUS (EFI_API *EFI_BIS_FREE)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data *ToFree
);

typedef EFI_STATUS (EFI_API *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CERTIFICATE)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data **Certificate
);

typedef EFI_STATUS (EFI_API *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CHECKFLAG)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    bool *CheckIsRequired
);

typedef EFI_STATUS (EFI_API *EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_UPDATE_TOKEN)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data **UpdateToken
);

typedef uint32_t EFI_BIS_CERT_ID;

typedef uint16_t EFI_BIS_ALG_ID;

struct efi_bis_signature_info {
    EFI_BIS_CERT_ID CertificateID;
    EFI_BIS_ALG_ID AlgorithmID;
    uint16_t KeyLength;
};

#define EFI_BIS_GET_SIGINFO_COUNT(BisDataPtr) \
    ((BisDataPtr)->Length / sizeof(struct efi_bis_signature_info))

#define EFI_BIS_GET_SIGINFO_ARRAY(BisDataPtr) ((struct efi_bis_signature_info *)(BisDataPtr)->Data)

#define EFI_BIS_CERT_ID_DSA EFI_BIS_ALG_DSA
#define EFI_BIS_CERT_ID_RSA_MD5 EFI_BIS_ALG_RSA_MD5

#define EFI_BIS_CERT_ID_MASK (0xFF7F7FFF)

#define EFI_BIS_ALG_DSA (41)
#define EFI_BIS_ALG_RSA_MD5 (42)

typedef EFI_STATUS (EFI_API *EFI_BIS_GET_SIGNATURE_INFO)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data **SignatureInfo
);

typedef EFI_STATUS (EFI_API *EFI_BIS_UPDATE_BOOT_OBJECT_AUTHORIZATION)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data *RequestCredential,
    struct efi_bis_data **NewUpdateToken
);

#define EFI_BOOT_OBJECT_AUTHORIZATION_PARMSET_GUID \
    {0xedd35e31, 0x7b9, 0x11d2, {0x83, 0xa3, 0x0, 0xa0, 0xc9, 0x1f, 0xad, 0xcf}}

typedef EFI_STATUS (EFI_API *EFI_BIS_VERIFY_BOOT_OBJECT)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data *Credentials,
    struct efi_bis_data *DataObject,
    bool *IsVerified
);

typedef EFI_STATUS (EFI_API *EFI_BIS_VERIFY_OBJECT_WITH_CREDENTIAL)(
    EFI_BIS_APPLICATION_HANDLE AppHandle,
    struct efi_bis_data *Credentials,
    struct efi_bis_data *DataObject,
    struct efi_bis_data *SectionName,
    struct efi_bis_data *AuthorityCertificate,
    bool *IsVerified
);

struct efi_bis_protocol {
    EFI_BIS_INITIALIZE Initialize;
    EFI_BIS_SHUTDOWN Shutdown;
    EFI_BIS_FREE Free;
    EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CERTIFICATE GetBootObjectAuthorizationCertificate;
    EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_CHECKFLAG GetBootObjectAuthorizationCheckFlag;
    EFI_BIS_GET_BOOT_OBJECT_AUTHORIZATION_UPDATE_TOKEN GetBootObjectAuthorizationUpdateToken;
    EFI_BIS_GET_SIGNATURE_INFO GetSignatureInfo;
    EFI_BIS_UPDATE_BOOT_OBJECT_AUTHORIZATION UpdateBootObjectAuthorization;
    EFI_BIS_VERIFY_BOOT_OBJECT VerifyBootObject;
    EFI_BIS_VERIFY_OBJECT_WITH_CREDENTIAL VerifyObjectWithCredential;
};

#define EFI_HTTP_BOOT_CALLBACK_PROTOCOL_GUID \
    {0xba23b311, 0x343d, 0x11e6, {0x91, 0x85, 0x58, 0x20, 0xb1, 0xd6, 0x52, 0x99}}

struct efi_http_boot_callback_protocol;

#define EFI_HTTP_BOOT_DHCP4 ((uint32_t)0)
#define EFI_HTTP_BOOT_DHCP6 ((uint32_t)1)
#define EFI_HTTP_BOOT_HTTP_REQUEST ((uint32_t)2)
#define EFI_HTTP_BOOT_HTTP_RESPONSE ((uint32_t)3)
#define EFI_HTTP_BOOT_HTTP_ENTITY_BODY ((uint32_t)4)
#define EFI_HTTP_BOOT_HTTP_AUTH_INFO ((uint32_t)5)
#define EFI_HTTP_BOOT_TYPE_MAX ((uint32_t)6)

typedef EFI_STATUS (EFI_API *EFI_HTTP_BOOT_CALLBACK)(
    struct efi_http_boot_callback_protocol *This,
    uint32_t DataType,
    bool Received,
    uint32_t DataLength,
    void *Data
);

struct efi_http_boot_callback_protocol {
    EFI_HTTP_BOOT_CALLBACK Callback;
};

#ifdef __cplusplus
}
#endif

#endif
