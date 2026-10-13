#ifndef EFI_EFISECUREBOOT_H_
#define EFI_EFISECUREBOOT_H_

#include "efiapi.h"
#include "efiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_AUTHENTICATION_INFO_PROTOCOL_GUID \
    {0x7671d9d0, 0x53db, 0x4173, {0xaa, 0x69, 0x23, 0x27, 0xf2, 0x1f, 0x0b, 0xc7}}

typedef struct _EFI_AUTHENTICATION_INFO_PROTOCOL EFI_AUTHENTICATION_INFO_PROTOCOL;

typedef EFI_STATUS (EFI_API *EFI_AUTHENTICATION_INFO_PROTOCOL_GET)(
    EFI_IN EFI_AUTHENTICATION_INFO_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_OUT EFI_VOID **Buffer
);

/* Printed with one more level of indirection on each parameter than its description gives. */
typedef EFI_STATUS (EFI_API *EFI_AUTHENTICATION_INFO_PROTOCOL_SET)(
    EFI_IN EFI_AUTHENTICATION_INFO_PROTOCOL *This,
    EFI_IN EFI_HANDLE ControllerHandle,
    EFI_IN EFI_VOID *Buffer
);

struct _EFI_AUTHENTICATION_INFO_PROTOCOL {
    EFI_AUTHENTICATION_INFO_PROTOCOL_GET Get;
    EFI_AUTHENTICATION_INFO_PROTOCOL_SET Set;
};

/* Only unnamed tables in the specification; packed: nodes may start at any byte. */
typedef struct __attribute__((__packed__)) {
    EFI_GUID Guid;
    EFI_UINT16 Length;
} EFI_AUTH_NODE_HEADER;

#define EFI_AUTHENTICATION_CHAP_RADIUS_GUID \
    {0xd6062b50, 0x15ca, 0x11da, {0x92, 0x19, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}}

/* CHAP secret/name and reverse CHAP name/secret follow, each after an EFI_UINT16 length. */
__extension__ typedef struct __attribute__((__packed__)) {
    EFI_AUTH_NODE_HEADER Header;
    EFI_UINT8 RadiusIpAddr[16];
    EFI_UINT16 Reserved;
    EFI_UINT8 NasIpAddr[16];
    EFI_UINT16 NasSecretLength;
    EFI_UINT8 NasSecret[];
} EFI_CHAP_RADIUS_AUTH_NODE;

#define EFI_AUTHENTICATION_CHAP_LOCAL_GUID \
    {0xc280c73e, 0x15ca, 0x11da, {0xb0, 0xca, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}}

/*
 * User name, CHAP secret/name, and reverse CHAP name/secret follow, each after an EFI_UINT16
 * length.
 */
__extension__ typedef struct __attribute__((__packed__)) {
    EFI_AUTH_NODE_HEADER Header;
    EFI_UINT16 Reserved;
    EFI_UINT16 UserSecretLength;
    EFI_UINT8 UserSecret[];
} EFI_CHAP_LOCAL_AUTH_NODE;

/* The certificate (bCertificate) follows; dwLength includes this header. */
typedef struct _EFI_WIN_CERTIFICATE {
    EFI_UINT32 dwLength;
    EFI_UINT16 wRevision;
    EFI_UINT16 wCertificateType;
} EFI_WIN_CERTIFICATE;

#define EFI_WIN_CERT_TYPE_PKCS_SIGNED_DATA 0x0002
#define EFI_WIN_CERT_TYPE_EFI_PKCS115 0x0EF0
#define EFI_WIN_CERT_TYPE_EFI_GUID 0x0EF1

/* The signature follows, as long as the key. */
typedef struct _EFI_WIN_CERTIFICATE_EFI_PKCS1_15 {
    EFI_WIN_CERTIFICATE Hdr;
    EFI_GUID HashAlgorithm;
} EFI_WIN_CERTIFICATE_EFI_PKCS1_15;

/* CertData[ANYSIZE_ARRAY] in print: one element, since other structures embed this one. */
typedef struct _EFI_WIN_CERTIFICATE_UEFI_GUID {
    EFI_WIN_CERTIFICATE Hdr;
    EFI_GUID CertType;
    EFI_UINT8 CertData[1];
} EFI_WIN_CERTIFICATE_UEFI_GUID;

#define EFI_CERT_TYPE_RSA2048_SHA256_GUID \
    {0xa7717414, 0xc616, 0x4977, {0x94, 0x20, 0x84, 0x47, 0x12, 0xa7, 0x35, 0xbf}}

#define EFI_CERT_TYPE_PKCS7_GUID \
    {0x4aafd29d, 0x68df, 0x49ee, {0x8a, 0xa9, 0x34, 0x7d, 0x37, 0x56, 0x65, 0xa7}}

typedef struct _EFI_CERT_BLOCK_RSA_2048_SHA256 {
    EFI_GUID HashType;
    EFI_UINT8 PublicKey[256];
    EFI_UINT8 Signature[256];
} EFI_CERT_BLOCK_RSA_2048_SHA256;

__extension__ typedef struct __attribute__((__packed__)) _EFI_SIGNATURE_DATA {
    EFI_GUID SignatureOwner;
    EFI_UINT8 SignatureData[];
} EFI_SIGNATURE_DATA;

/* SignatureHeaderSize header bytes follow, then signatures of SignatureSize bytes each. */
typedef struct __attribute__((__packed__)) _EFI_SIGNATURE_LIST {
    EFI_GUID SignatureType;
    EFI_UINT32 SignatureListSize;
    EFI_UINT32 SignatureHeaderSize;
    EFI_UINT32 SignatureSize;
} EFI_SIGNATURE_LIST;

#define EFI_CERT_SHA256_GUID \
    {0xc1c41626, 0x504c, 0x4092, {0xac, 0xa9, 0x41, 0xf9, 0x36, 0x93, 0x43, 0x28}}

#define EFI_CERT_RSA2048_GUID \
    {0x3c5766e8, 0x269c, 0x4e34, {0xaa, 0x14, 0xed, 0x77, 0x6e, 0x85, 0xb3, 0xb6}}

#define EFI_CERT_RSA2048_SHA256_GUID \
    {0xe2b36190, 0x879b, 0x4a3d, {0xad, 0x8d, 0xf2, 0xe7, 0xbb, 0xa3, 0x27, 0x84}}

#define EFI_CERT_SHA1_GUID \
    {0x826ca512, 0xcf10, 0x4ac9, {0xb1, 0x87, 0xbe, 0x01, 0x49, 0x66, 0x31, 0xbd}}

#define EFI_CERT_RSA2048_SHA1_GUID \
    {0x67f8444f, 0x8743, 0x48f1, {0xa3, 0x28, 0x1e, 0xaa, 0xb8, 0x73, 0x60, 0x80}}

#define EFI_CERT_X509_GUID \
    {0xa5c059a1, 0x94e4, 0x4aa7, {0x87, 0xb5, 0xab, 0x15, 0x5c, 0x2b, 0xf0, 0x72}}

#define EFI_CERT_SHA224_GUID \
    {0xb6e5233, 0xa65c, 0x44c9, {0x94, 0x07, 0xd9, 0xab, 0x83, 0xbf, 0xc8, 0xbd}}

#define EFI_CERT_SHA384_GUID \
    {0xff3e5307, 0x9fd0, 0x48c9, {0x85, 0xf1, 0x8a, 0xd5, 0x6c, 0x70, 0x1e, 0x01}}

#define EFI_CERT_SHA512_GUID \
    {0x93e0fae, 0xa6c4, 0x4f50, {0x9f, 0x1b, 0xd4, 0x1e, 0x2b, 0x89, 0xc1, 0x9a}}

#define EFI_CERT_X509_SHA256_GUID \
    {0x3bd2a492, 0x96c0, 0x4079, {0xb4, 0x20, 0xfc, 0xf9, 0x8e, 0xf1, 0x03, 0xed}}

typedef struct __attribute__((__packed__)) _EFI_CERT_X509_SHA256 {
    EFI_SHA256_HASH ToBeSignedHash;
    EFI_TIME TimeOfRevocation;
} EFI_CERT_X509_SHA256;

#define EFI_CERT_X509_SHA384_GUID \
    {0x7076876e, 0x80c2, 0x4ee6, {0xaa, 0xd2, 0x28, 0xb3, 0x49, 0xa6, 0x86, 0x5b}}

typedef struct __attribute__((__packed__)) _EFI_CERT_X509_SHA384 {
    EFI_SHA384_HASH ToBeSignedHash;
    EFI_TIME TimeOfRevocation;
} EFI_CERT_X509_SHA384;

#define EFI_CERT_X509_SHA512_GUID \
    {0x446dbf63, 0x2502, 0x4cda, {0xbc, 0xfa, 0x24, 0x65, 0xd2, 0xb0, 0xfe, 0x9d}}

typedef struct __attribute__((__packed__)) _EFI_CERT_X509_SHA512 {
    EFI_SHA512_HASH ToBeSignedHash;
    EFI_TIME TimeOfRevocation;
} EFI_CERT_X509_SHA512;

#define EFI_CERT_SM3_GUID \
    {0x57347f87, 0x7a9b, 0x403a, {0xb9, 0x3c, 0xdc, 0x4a, 0xfb, 0x7a, 0xe, 0xbc}}

#define EFI_CERT_X509_SM3_GUID \
    {0x60d807e5, 0x10b4, 0x49a9, {0x93, 0x31, 0xe4, 0x4, 0x37, 0x88, 0x8d, 0x37}}

typedef EFI_UINT8 EFI_SM3_HASH[32];

typedef struct __attribute__((__packed__)) _EFI_CERT_X509_SM3 {
    EFI_SM3_HASH ToBeSignedHash;
    EFI_TIME TimeOfRevocation;
} EFI_CERT_X509_SM3;

#define EFI_CERT_EXTERNAL_MANAGEMENT_GUID \
    {0x452e8ced, 0xdfff, 0x4b8c, {0xae, 0x01, 0x51, 0x18, 0x86, 0x2e, 0x68, 0x2c}}

typedef EFI_UINT32 EFI_IMAGE_EXECUTION_ACTION;

#define EFI_IMAGE_EXECUTION_AUTHENTICATION 0x00000007
#define EFI_IMAGE_EXECUTION_AUTH_UNTESTED 0x00000000
#define EFI_IMAGE_EXECUTION_AUTH_SIG_FAILED 0x00000001
#define EFI_IMAGE_EXECUTION_AUTH_SIG_PASSED 0x00000002
#define EFI_IMAGE_EXECUTION_AUTH_SIG_NOT_FOUND 0x00000003
#define EFI_IMAGE_EXECUTION_AUTH_SIG_FOUND 0x00000004
#define EFI_IMAGE_EXECUTION_POLICY_FAILED 0x00000005

#define EFI_IMAGE_EXECUTION_INITIALIZED 0x00000008

/* Name, DevicePath and Signature follow; InfoSize counts them too. */
typedef struct {
    EFI_IMAGE_EXECUTION_ACTION Action;
    EFI_UINT32 InfoSize;
} EFI_IMAGE_EXECUTION_INFO;

/* Entries vary in size (InfoSize), so only the first can be reached by indexing. */
__extension__ typedef struct {
    EFI_UINTN NumberOfImages;
    EFI_IMAGE_EXECUTION_INFO InformationInfo[];
} EFI_IMAGE_EXECUTION_INFO_TABLE;

#define EFI_IMAGE_SECURITY_DATABASE_GUID \
    {0xd719b2cb, 0x3d3a, 0x4596, {0xa3, 0xbc, 0xda, 0xd0, 0x0e, 0x67, 0x65, 0x6f}}

#define EFI_IMAGE_SECURITY_DATABASE L"db"
#define EFI_IMAGE_SECURITY_DATABASE1 L"dbx"
#define EFI_IMAGE_SECURITY_DATABASE2 L"dbt"
#define EFI_IMAGE_SECURITY_DATABASE3 L"dbr"

#define EFI_DEVICE_SECURITY_DATABASE_GUID \
    {0xb9c2b4f4, 0xbf5f, 0x462d, {0x8a, 0xdf, 0xc5, 0xc7, 0xa, 0xc3, 0x5d, 0xad}}

#define EFI_DEVICE_SECURITY_DATABASE L"devdb"

/* Cited but no longer printed by 2.11; laid out like EFI_FIRMWARE_IMAGE_AUTHENTICATION. */
typedef struct {
    EFI_UINT64 MonotonicCount;
    EFI_WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_VARIABLE_AUTHENTICATION;

typedef struct {
    EFI_TIME TimeStamp;
    EFI_WIN_CERTIFICATE_UEFI_GUID AuthInfo;
} EFI_VARIABLE_AUTHENTICATION_2;

#define EFI_VARIABLE_AUTHENTICATION_3_TIMESTAMP_TYPE 1
#define EFI_VARIABLE_AUTHENTICATION_3_NONCE_TYPE 2

typedef struct {
    EFI_UINT8 Version;
    EFI_UINT8 Type;
    EFI_UINT32 MetadataSize;
    EFI_UINT32 Flags;
} EFI_VARIABLE_AUTHENTICATION_3;

#define EFI_VARIABLE_ENHANCED_AUTH_FLAG_UPDATE_CERT 0x00000001

#define EFI_VARIABLE_AUTHENTICATION_3_CERT_ID_SHA256 1

/* IdSize bytes of Id follow. */
typedef struct {
    EFI_UINT8 Type;
    EFI_UINT32 IdSize;
} EFI_VARIABLE_AUTHENTICATION_3_CERT_ID;

/* NonceSize bytes of Nonce follow, then an EFI_WIN_CERTIFICATE_UEFI_GUID. */
typedef struct {
    EFI_UINT32 NonceSize;
} EFI_VARIABLE_AUTHENTICATION_3_NONCE;

#ifdef __cplusplus
}
#endif

#endif
