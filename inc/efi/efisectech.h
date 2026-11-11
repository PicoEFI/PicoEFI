#ifndef EFI_EFISECTECH_H_
#define EFI_EFISECTECH_H_

#include "efiapi.h"
#include "efiprot.h"
#include "efisecureboot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HASH2_SERVICE_BINDING_PROTOCOL_GUID \
    {0xda836f8d, 0x217f, 0x4ca0, {0x99, 0xc2, 0x1c, 0xa4, 0xe1, 0x60, 0x77, 0xea}}

#define EFI_HASH2_PROTOCOL_GUID \
    {0x55b1d734, 0xc5e1, 0x49db, {0x96, 0x47, 0xb1, 0x6a, 0xfb, 0xe, 0x30, 0x5b}}

typedef struct _EFI_HASH2_PROTOCOL EFI_HASH2_PROTOCOL;

typedef uint8_t EFI_MD5_HASH2[16];
typedef uint8_t EFI_SHA1_HASH2[20];
typedef uint8_t EFI_SHA224_HASH2[28];
typedef uint8_t EFI_SHA256_HASH2[32];
typedef uint8_t EFI_SHA384_HASH2[48];
typedef uint8_t EFI_SHA512_HASH2[64];

typedef union _EFI_HASH2_OUTPUT {
    EFI_MD5_HASH2 Md5Hash;
    EFI_SHA1_HASH2 Sha1Hash;
    EFI_SHA224_HASH2 Sha224Hash;
    EFI_SHA256_HASH2 Sha256Hash;
    EFI_SHA384_HASH2 Sha384Hash;
    EFI_SHA512_HASH2 Sha512Hash;
} EFI_HASH2_OUTPUT;

/* The five services are printed as plain prototypes; named as the protocol structure types them. */
typedef EFI_STATUS (EFI_API *EFI_HASH2_GET_HASH_SIZE)(
    const EFI_HASH2_PROTOCOL *This,
    const EFI_GUID *HashAlgorithm,
    size_t *HashSize
);

typedef EFI_STATUS (EFI_API *EFI_HASH2_HASH)(
    const EFI_HASH2_PROTOCOL *This,
    const EFI_GUID *HashAlgorithm,
    const uint8_t *Message,
    size_t MessageSize,
    EFI_HASH2_OUTPUT *Hash
);

typedef EFI_STATUS (EFI_API *EFI_HASH2_HASH_INIT)(
    const EFI_HASH2_PROTOCOL *This,
    const EFI_GUID *HashAlgorithm
);

typedef EFI_STATUS (EFI_API *EFI_HASH2_HASH_UPDATE)(
    const EFI_HASH2_PROTOCOL *This,
    const uint8_t *Message,
    size_t MessageSize
);

typedef EFI_STATUS (EFI_API *EFI_HASH2_HASH_FINAL)(
    const EFI_HASH2_PROTOCOL *This,
    EFI_HASH2_OUTPUT *Hash
);

struct _EFI_HASH2_PROTOCOL {
    EFI_HASH2_GET_HASH_SIZE GetHashSize;
    EFI_HASH2_HASH Hash;
    EFI_HASH2_HASH_INIT HashInit;
    EFI_HASH2_HASH_UPDATE HashUpdate;
    EFI_HASH2_HASH_FINAL HashFinal;
};

#define EFI_KMS_PROTOCOL_GUID \
    {0xEC3A978D, 0x7C4E, 0x48FA, {0x9A, 0xBE, 0x6A, 0xD9, 0x1C, 0xC8, 0xF8, 0x11}}

#define EFI_KMS_DATA_TYPE_NONE 0
#define EFI_KMS_DATA_TYPE_BINARY 1
#define EFI_KMS_DATA_TYPE_ASCII 2
#define EFI_KMS_DATA_TYPE_UNICODE 4
#define EFI_KMS_DATA_TYPE_UTF8 8

typedef struct _EFI_KMS_SERVICE_PROTOCOL EFI_KMS_PROTOCOL;

typedef struct {
    uint16_t ClientIdSize;
    void *ClientId;
    uint8_t ClientNameType;
    uint8_t ClientNameCount;
    void *ClientName;
} EFI_KMS_CLIENT_INFO;

#define EFI_KMS_FORMAT_GENERIC_128_GUID \
    {0xec8a3d69, 0x6ddf, 0x4108, {0x94, 0x76, 0x73, 0x37, 0xfc, 0x52, 0x21, 0x36}}

#define EFI_KMS_FORMAT_GENERIC_160_GUID \
    {0xa3b3e6f8, 0xefca, 0x4bc1, {0x88, 0xfb, 0xcb, 0x87, 0x33, 0x9b, 0x25, 0x79}}

#define EFI_KMS_FORMAT_GENERIC_256_GUID \
    {0x70f64793, 0xc323, 0x4261, {0xac, 0x2c, 0xd8, 0x76, 0xf2, 0x7c, 0x53, 0x45}}

#define EFI_KMS_FORMAT_GENERIC_512_GUID \
    {0x978fe043, 0xd7af, 0x422e, {0x8a, 0x92, 0x2b, 0x48, 0xe4, 0x63, 0xbd, 0xe6}}

#define EFI_KMS_FORMAT_GENERIC_1024_GUID \
    {0x43be0b44, 0x874b, 0x4ead, {0xb0, 0x9c, 0x24, 0x1a, 0x4f, 0xbd, 0x7e, 0xb3}}

#define EFI_KMS_FORMAT_GENERIC_2048_GUID \
    {0x40093f23, 0x630c, 0x4626, {0x9c, 0x48, 0x40, 0x37, 0x3b, 0x19, 0xcb, 0xbe}}

#define EFI_KMS_FORMAT_GENERIC_3072_GUID \
    {0xb9237513, 0x6c44, 0x4411, {0xa9, 0x90, 0x21, 0xe5, 0x56, 0xe0, 0x5a, 0xde}}

#define EFI_KMS_FORMAT_GENERIC_DYNAMIC_GUID \
    {0x2156e996, 0x66de, 0x4b27, {0x9c, 0xc9, 0xb0, 0x9f, 0xac, 0x4d, 0x2, 0xbe}}

typedef struct {
    uint32_t KeySize;
    uint8_t KeyData[1];
} EFI_KMS_FORMAT_GENERIC_DYNAMIC;

#define EFI_KMS_FORMAT_MD2_128_GUID \
    {0x78be11c4, 0xee44, 0x4a22, {0x9f, 0x05, 0x03, 0x85, 0x2e, 0xc5, 0xc9, 0x78}}

#define EFI_KMS_FORMAT_MDC2_128_GUID \
    {0xf7ad60f8, 0xefa8, 0x44a3, {0x91, 0x13, 0x23, 0x1f, 0x39, 0x9e, 0xb4, 0xc7}}

/* Printed with the inner brace one byte late. */
#define EFI_KMS_FORMAT_MD4_128_GUID \
    {0xd1c17aa1, 0xcac5, 0x400f, {0xbe, 0x17, 0xe2, 0xa2, 0xae, 0x06, 0x67, 0x7c}}

#define EFI_KMS_FORMAT_MDC4_128_GUID \
    {0x3fa4f847, 0xd8eb, 0x4df4, {0xbd, 0x49, 0x10, 0x3a, 0x0a, 0x84, 0x7b, 0xbc}}

#define EFI_KMS_FORMAT_MD5_128_GUID \
    {0xdcbc3662, 0x9cda, 0x4b52, {0xa0, 0x4c, 0x82, 0xeb, 0x1d, 0x23, 0x48, 0xc7}}

#define EFI_KMS_FORMAT_MD5SHA_128_GUID \
    {0x1c178237, 0x6897, 0x459e, {0x9d, 0x36, 0x67, 0xce, 0x8e, 0xf9, 0x4f, 0x76}}

#define EFI_KMS_FORMAT_SHA1_160_GUID \
    {0x453c5e5a, 0x482d, 0x43f0, {0x87, 0xc9, 0x59, 0x41, 0xf3, 0xa3, 0x8a, 0xc2}}

#define EFI_KMS_FORMAT_SHA256_256_GUID \
    {0x6bb4f5cd, 0x8022, 0x448d, {0xbc, 0x6d, 0x77, 0x1b, 0xae, 0x93, 0x5f, 0xc6}}

#define EFI_KMS_FORMAT_SHA512_512_GUID \
    {0x2f240e12, 0xe14d, 0x475c, {0x83, 0xb0, 0xef, 0xff, 0x22, 0xd7, 0x7b, 0xe7}}

#define EFI_KMS_FORMAT_AESXTS_128_GUID \
    {0x4776e33f, 0xdb47, 0x479a, {0xa2, 0x5f, 0xa1, 0xcd, 0x0a, 0xfa, 0xb3, 0x8b}}

#define EFI_KMS_FORMAT_AESXTS_256_GUID \
    {0xdc7e8613, 0xc4bb, 0x4db0, {0x84, 0x62, 0x13, 0x51, 0x13, 0x57, 0xab, 0xe2}}

#define EFI_KMS_FORMAT_AESCBC_128_GUID \
    {0xa0e8ee6a, 0x0e92, 0x44d4, {0x86, 0x1b, 0x0e, 0xaa, 0x4a, 0xca, 0x44, 0xa2}}

#define EFI_KMS_FORMAT_AESCBC_256_GUID \
    {0xd7e69789, 0x1f68, 0x45e8, {0x96, 0xef, 0x3b, 0x64, 0x07, 0xa5, 0xb2, 0xdc}}

#define EFI_KMS_FORMAT_RSASHA1_1024_GUID \
    {0x56417bed, 0x6bbe, 0x4882, {0x86, 0xa0, 0x3a, 0xe8, 0xbb, 0x17, 0xf8, 0xf9}}

#define EFI_KMS_FORMAT_RSASHA1_2048_GUID \
    {0xf66447d4, 0x75a6, 0x463e, {0xa8, 0x19, 0x07, 0x7f, 0x2d, 0xda, 0x05, 0xe9}}

#define EFI_KMS_FORMAT_RSASHA256_2048_GUID \
    {0xa477af13, 0x877d, 0x4060, {0xba, 0xa1, 0x25, 0xd1, 0xbe, 0xa0, 0x8a, 0xd3}}

#define EFI_KMS_FORMAT_RSASHA256_3072_GUID \
    {0x4e1356c2, 0xeed, 0x463f, {0x81, 0x47, 0x99, 0x33, 0xab, 0xdb, 0xc7, 0xd5}}

typedef struct {
    uint8_t KeyIdentifierType;
    uint8_t KeyIdentifierSize;
    void *KeyIdentifier;
    EFI_GUID KeyFormat;
    void *KeyValue;
    EFI_STATUS KeyStatus;
} EFI_KMS_KEY_DESCRIPTOR;

#define EFI_KMS_ATTRIBUTE_TYPE_NONE 0x00
#define EFI_KMS_ATTRIBUTE_TYPE_INTEGER 0x01
#define EFI_KMS_ATTRIBUTE_TYPE_LONG_INTEGER 0x02
#define EFI_KMS_ATTRIBUTE_TYPE_BIG_INTEGER 0x03
#define EFI_KMS_ATTRIBUTE_TYPE_ENUMERATION 0x04
#define EFI_KMS_ATTRIBUTE_TYPE_BOOLEAN 0x05
#define EFI_KMS_ATTRIBUTE_TYPE_BYTE_STRING 0x06
#define EFI_KMS_ATTRIBUTE_TYPE_TEXT_STRING 0x07
#define EFI_KMS_ATTRIBUTE_TYPE_DATE_TIME 0x08
#define EFI_KMS_ATTRIBUTE_TYPE_INTERVAL 0x09
#define EFI_KMS_ATTRIBUTE_TYPE_STRUCTURE 0x0A
#define EFI_KMS_ATTRIBUTE_TYPE_DYNAMIC 0x0B

typedef struct {
    uint16_t Tag;
    uint16_t Type;
    uint32_t Length;
    uint8_t KeyAttributeData[1];
} EFI_KMS_DYNAMIC_FIELD;

typedef struct {
    uint32_t FieldCount;
    EFI_KMS_DYNAMIC_FIELD Field[1];
} EFI_KMS_DYNAMIC_ATTRIBUTE;

typedef struct {
    uint8_t KeyAttributeIdentifierType;
    uint8_t KeyAttributeIdentifierCount;
    void *KeyAttributeIdentifier;
    uint16_t KeyAttributeInstance;
    uint16_t KeyAttributeType;
    uint16_t KeyAttributeValueSize;
    void *KeyAttributeValue;
    EFI_STATUS KeyAttributeStatus;
} EFI_KMS_KEY_ATTRIBUTE;

typedef EFI_STATUS (EFI_API *EFI_KMS_GET_SERVICE_STATUS)(EFI_KMS_PROTOCOL *This);

typedef EFI_STATUS (EFI_API *EFI_KMS_REGISTER_CLIENT)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_CREATE_KEY)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint16_t *KeyDescriptorCount,
    EFI_KMS_KEY_DESCRIPTOR *KeyDescriptors,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_GET_KEY)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint16_t *KeyDescriptorCount,
    EFI_KMS_KEY_DESCRIPTOR *KeyDescriptors,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_ADD_KEY)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint16_t *KeyDescriptorCount,
    EFI_KMS_KEY_DESCRIPTOR *KeyDescriptors,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_DELETE_KEY)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint16_t *KeyDescriptorCount,
    EFI_KMS_KEY_DESCRIPTOR *KeyDescriptors,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_GET_KEY_ATTRIBUTES)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint8_t *KeyIdentifierSize,
    const void *KeyIdentifier,
    uint16_t *KeyAttributesCount,
    EFI_KMS_KEY_ATTRIBUTE *KeyAttributes,
    size_t *ClientDataSize,
    void **ClientData
);

/* KeyIdentifierSize is printed as UINT *, a type that does not exist; its siblings use uint8_t *. */
typedef EFI_STATUS (EFI_API *EFI_KMS_ADD_KEY_ATTRIBUTES)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint8_t *KeyIdentifierSize,
    const void *KeyIdentifier,
    uint16_t *KeyAttributesCount,
    EFI_KMS_KEY_ATTRIBUTE *KeyAttributes,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_DELETE_KEY_ATTRIBUTES)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    uint8_t *KeyIdentifierSize,
    const void *KeyIdentifier,
    uint16_t *KeyAttributesCount,
    EFI_KMS_KEY_ATTRIBUTE *KeyAttributes,
    size_t *ClientDataSize,
    void **ClientData
);

typedef EFI_STATUS (EFI_API *EFI_KMS_GET_KEY_BY_ATTRIBUTES)(
    EFI_KMS_PROTOCOL *This,
    EFI_KMS_CLIENT_INFO *Client,
    size_t *KeyAttributeCount,
    EFI_KMS_KEY_ATTRIBUTE *KeyAttributes,
    size_t *KeyDescriptorCount,
    EFI_KMS_KEY_DESCRIPTOR *KeyDescriptors,
    size_t *ClientDataSize,
    void **ClientData
);

struct _EFI_KMS_SERVICE_PROTOCOL {
    EFI_KMS_GET_SERVICE_STATUS GetServiceStatus;
    EFI_KMS_REGISTER_CLIENT RegisterClient;
    EFI_KMS_CREATE_KEY CreateKey;
    EFI_KMS_GET_KEY GetKey;
    EFI_KMS_ADD_KEY AddKey;
    EFI_KMS_DELETE_KEY DeleteKey;
    EFI_KMS_GET_KEY_ATTRIBUTES GetKeyAttributes;
    EFI_KMS_ADD_KEY_ATTRIBUTES AddKeyAttributes;
    EFI_KMS_DELETE_KEY_ATTRIBUTES DeleteKeyAttributes;
    EFI_KMS_GET_KEY_BY_ATTRIBUTES GetKeyByAttributes;
    uint32_t ProtocolVersion;
    EFI_GUID ServiceId;
    uint16_t *ServiceName;
    uint32_t ServiceVersion;
    uint8_t ServiceAvailable;
    uint8_t ClientIdSupported;
    uint8_t ClientIdRequired;
    uint16_t ClientIdMaxSize;
    uint8_t ClientNameStringTypes;
    uint8_t ClientNameRequired;
    uint16_t ClientNameMaxCount;
    uint8_t ClientDataSupported;
    size_t ClientDataMaxSize;
    uint8_t KeyIdVariableLenSupported;
    size_t KeyIdMaxSize;
    size_t KeyFormatsCount;
    EFI_GUID *KeyFormats;
    uint8_t KeyAttributesSupported;
    uint8_t KeyAttributeIdStringTypes;
    uint16_t KeyAttributeIdMaxCount;
    size_t KeyAttributesCount;
    EFI_KMS_KEY_ATTRIBUTE *KeyAttributes;
};

#define EFI_PKCS7_VERIFY_PROTOCOL_GUID \
    {0x47889fb2, 0xd671, 0x4fab, {0xa0, 0xca, 0xdf, 0xe, 0x44, 0xdf, 0x70, 0xd6}}

typedef struct _EFI_PKCS7_VERIFY_PROTOCOL EFI_PKCS7_VERIFY_PROTOCOL;

/* Printed under the member names; named as the protocol structure types the members. */
typedef EFI_STATUS (EFI_API *EFI_PKCS7_VERIFY_BUFFER)(
    EFI_PKCS7_VERIFY_PROTOCOL *This,
    void *SignedData,
    size_t SignedDataSize,
    void *InData,
    size_t InDataSize,
    EFI_SIGNATURE_LIST **AllowedDb,
    EFI_SIGNATURE_LIST **RevokedDb,
    EFI_SIGNATURE_LIST **TimeStampDb,
    void *Content,
    size_t *ContentSize
);

typedef EFI_STATUS (EFI_API *EFI_PKCS7_VERIFY_SIGNATURE)(
    EFI_PKCS7_VERIFY_PROTOCOL *This,
    void *Signature,
    size_t SignatureSize,
    void *InHash,
    size_t InHashSize,
    EFI_SIGNATURE_LIST **AllowedDb,
    EFI_SIGNATURE_LIST **RevokedDb,
    EFI_SIGNATURE_LIST **TimeStampDb
);

/* The members are printed as pointers to these types, which are already function pointers. */
struct _EFI_PKCS7_VERIFY_PROTOCOL {
    EFI_PKCS7_VERIFY_BUFFER VerifyBuffer;
    EFI_PKCS7_VERIFY_SIGNATURE VerifySignature;
};

#define EFI_SMART_CARD_READER_PROTOCOL_GUID \
    {0x2a4d1adf, 0x21dc, 0x4b81, {0xa4, 0x2f, 0x8b, 0x8e, 0xe2, 0x38, 0x00, 0x60}}

typedef struct _EFI_SMART_CARD_READER_PROTOCOL EFI_SMART_CARD_READER_PROTOCOL;

/*
 * The prototypes print these names with _PROTOCOL_ inserted (..._READER_PROTOCOL_CONNECT); the
 * names here are the ones the protocol structure uses, in the pattern of the Edge protocol.
 */
typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_CONNECT)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint32_t AccessMode,
    uint32_t CardAction,
    uint32_t PreferredProtocols,
    uint32_t *ActiveProtocol
);

#define EFI_SCARD_AM_READER 0x0001
#define EFI_SCARD_AM_CARD 0x0002

#define EFI_SCARD_CA_NORESET 0x0000
#define EFI_SCARD_CA_COLDRESET 0x0001
#define EFI_SCARD_CA_WARMRESET 0x0002
#define EFI_SCARD_CA_UNPOWER 0x0003
#define EFI_SCARD_CA_EJECT 0x0004

#define EFI_SCARD_PROTOCOL_UNDEFINED 0x0000
#define EFI_SCARD_PROTOCOL_T0 0x0001
#define EFI_SCARD_PROTOCOL_T1 0x0002
#define EFI_SCARD_PROTOCOL_RAW 0x0004

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_DISCONNECT)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint32_t CardAction
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_STATUS)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint16_t *ReaderName,
    size_t *ReaderNameLength,
    uint32_t *State,
    uint32_t *CardProtocol,
    uint8_t *Atr,
    size_t *AtrLength
);

#define EFI_SCARD_UNKNOWN 0x0000
#define EFI_SCARD_ABSENT 0x0001
#define EFI_SCARD_INACTIVE 0x0002
#define EFI_SCARD_ACTIVE 0x0003

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_TRANSMIT)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint8_t *CAPDU,
    size_t CAPDULength,
    uint8_t *RAPDU,
    size_t *RAPDULength
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_CONTROL)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint32_t ControlCode,
    uint8_t *InBuffer,
    size_t InBufferLength,
    uint8_t *OutBuffer,
    size_t *OutBufferLength
);

#define EFI_SCARD_CTL_CODE(code) (0x42000000 + (code))
#define EFI_CM_IOCTL_GET_FEATURE_REQUEST EFI_SCARD_CTL_CODE(3400)

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_READER_GET_ATTRIB)(
    EFI_SMART_CARD_READER_PROTOCOL *This,
    uint32_t Attrib,
    uint8_t *OutBuffer,
    size_t *OutBufferLength
);

struct _EFI_SMART_CARD_READER_PROTOCOL {
    EFI_SMART_CARD_READER_CONNECT SCardConnect;
    EFI_SMART_CARD_READER_DISCONNECT SCardDisconnect;
    EFI_SMART_CARD_READER_STATUS SCardStatus;
    EFI_SMART_CARD_READER_TRANSMIT SCardTransmit;
    EFI_SMART_CARD_READER_CONTROL SCardControl;
    EFI_SMART_CARD_READER_GET_ATTRIB SCardGetAttrib;
};

#define EFI_SMART_CARD_EDGE_PROTOCOL_GUID \
    {0xd317f29b, 0xa325, 0x4712, {0x9b, 0xf1, 0xc6, 0x19, 0x54, 0xdc, 0x19, 0x8c}}

typedef struct _EFI_SMART_CARD_EDGE_PROTOCOL EFI_SMART_CARD_EDGE_PROTOCOL;

#define EFI_SCARD_AID_MAXSIZE 0x0010
#define EFI_SCARD_CSN_SIZE 0x0010
#define EFI_SMART_CARD_EDGE_PROTOCOL_VERSION_1 0x00000100

typedef uint8_t EFI_SMART_CARD_AID[EFI_SCARD_AID_MAXSIZE];
typedef uint8_t EFI_SMART_CARD_CSN[EFI_SCARD_CSN_SIZE];

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_CONTEXT)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    size_t *NumberAidSupported,
    size_t *AidTableSize,
    EFI_SMART_CARD_AID *AidTable,
    size_t *NumberSCPresent,
    size_t *CsnTableSize,
    EFI_SMART_CARD_CSN *CsnTable,
    uint32_t *VersionScEdgeProtocol
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_CONNECT)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE *SCardHandle,
    uint8_t *ScardCsn,
    uint8_t *ScardAid
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_DISCONNECT)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_CSN)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    uint8_t Csn[EFI_SCARD_CSN_SIZE]
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_READER_NAME)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    size_t *ReaderNameLength,
    uint16_t *ReaderName
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_VERIFY_PIN)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    int32_t PinSize,
    uint8_t *PinCode,
    bool *PinResult,
    uint32_t *RemainingAttempts
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_PIN_REMAINING)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    uint32_t *RemainingAttempts
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_DATA)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    EFI_GUID *DataId,
    size_t *DataSize,
    void *Data
);

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_GET_CREDENTIAL)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    size_t *CredentialSize,
    uint8_t *CredentialList
);

#define EFI_SC_EDGE_TAG_HEADER 0x0000
#define EFI_SC_EDGE_TAG_CERT 0x0001
#define EFI_SC_EDGE_TAG_KEY_ID 0x0002
#define EFI_SC_EDGE_TAG_KEY_TYPE 0x0003
#define EFI_SC_EDGE_TAG_KEY_SIZE 0x0004

#define EFI_SC_EDGE_L_SIZE_HEADER 1
#define EFI_SC_EDGE_L_SIZE_CERT 2
#define EFI_SC_EDGE_L_SIZE_KEY_ID 1
#define EFI_SC_EDGE_L_SIZE_KEY_TYPE 1
#define EFI_SC_EDGE_L_SIZE_KEY_SIZE 2

#define EFI_SC_EDGE_L_VALUE_HEADER 1
#define EFI_SC_EDGE_L_VALUE_KEY_ID 1
#define EFI_SC_EDGE_L_VALUE_KEY_TYPE 1
#define EFI_SC_EDGE_L_VALUE_KEY_SIZE 2

#define EFI_SC_EDGE_RSA_EXCHANGE 0x01
#define EFI_SC_EDGE_RSA_SIGNATURE 0x02
#define EFI_SC_EDGE_ECDSA_256 0x03
#define EFI_SC_EDGE_ECDSA_384 0x04
#define EFI_SC_EDGE_ECDSA_521 0x05
#define EFI_SC_EDGE_ECDH_256 0x06
#define EFI_SC_EDGE_ECDH_384 0x07
#define EFI_SC_EDGE_ECDH_521 0x08

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_SIGN_DATA)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    uintptr_t KeyId,
    uintptr_t KeyType,
    EFI_GUID *HashAlgorithm,
    EFI_GUID *PaddingMethod,
    uint8_t *HashedData,
    uint8_t *SignatureData
);

#define EFI_PADDING_RSASSA_PKCS1V1P5_GUID \
    {0x9317ec24, 0x7cb0, 0x4d0e, {0x8b, 0x32, 0x2e, 0xd9, 0x20, 0x9c, 0xd8, 0xaf}}

#define EFI_PADDING_RSASSA_PSS_GUID \
    {0x7b2349e0, 0x522d, 0x4f8e, {0xb9, 0x27, 0x69, 0xd9, 0x7c, 0x9e, 0x79, 0x5f}}

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_DECRYPT_DATA)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    uintptr_t KeyId,
    EFI_GUID *HashAlgorithm,
    EFI_GUID *PaddingMethod,
    size_t EncryptedSize,
    uint8_t *EncryptedData,
    size_t *PlaintextSize,
    uint8_t *PlaintextData
);

#define EFI_PADDING_NONE_GUID \
    {0x3629ddb1, 0x228c, 0x452e, {0xb6, 0x16, 0x09, 0xed, 0x31, 0x6a, 0x97, 0x00}}

#define EFI_PADDING_RSAES_PKCS1V1P5_GUID \
    {0xe1c1d0a9, 0x40b1, 0x4632, {0xbd, 0xcc, 0xd9, 0xd6, 0xe5, 0x29, 0x56, 0x31}}

#define EFI_PADDING_RSAES_OAEP_GUID \
    {0xc1e63ac4, 0xd0cf, 0x4ce6, {0x83, 0x5b, 0xee, 0xd0, 0xe6, 0xa8, 0xa4, 0x5b}}

typedef EFI_STATUS (EFI_API *EFI_SMART_CARD_EDGE_BUILD_DH_AGREEMENT)(
    EFI_SMART_CARD_EDGE_PROTOCOL *This,
    EFI_HANDLE SCardHandle,
    uintptr_t KeyId,
    uint8_t *dataQx,
    uint8_t *dataQy,
    uint8_t *DHAgreement
);

struct _EFI_SMART_CARD_EDGE_PROTOCOL {
    EFI_SMART_CARD_EDGE_GET_CONTEXT GetContext;
    EFI_SMART_CARD_EDGE_CONNECT Connect;
    EFI_SMART_CARD_EDGE_DISCONNECT Disconnect;
    EFI_SMART_CARD_EDGE_GET_CSN GetCsn;
    EFI_SMART_CARD_EDGE_GET_READER_NAME GetReaderName;
    EFI_SMART_CARD_EDGE_VERIFY_PIN VerifyPin;
    EFI_SMART_CARD_EDGE_GET_PIN_REMAINING GetPinRemaining;
    EFI_SMART_CARD_EDGE_GET_DATA GetData;
    EFI_SMART_CARD_EDGE_GET_CREDENTIAL GetCredential;
    EFI_SMART_CARD_EDGE_SIGN_DATA SignData;
    EFI_SMART_CARD_EDGE_DECRYPT_DATA DecryptData;
    EFI_SMART_CARD_EDGE_BUILD_DH_AGREEMENT BuildDHAgreement;
};

#ifdef __cplusplus
}
#endif

#endif
