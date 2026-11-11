#ifndef EFI_EFISECTECH_H
#define EFI_EFISECTECH_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efisecureboot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_HASH2_SERVICE_BINDING_PROTOCOL_GUID \
    { 0xda836f8d, 0x217f, 0x4ca0, { 0x99, 0xc2, 0x1c, 0xa4, 0xe1, 0x60, 0x77, 0xea } }

#define EFI_HASH2_PROTOCOL_GUID \
    { 0x55b1d734, 0xc5e1, 0x49db, { 0x96, 0x47, 0xb1, 0x6a, 0xfb, 0xe, 0x30, 0x5b } }

struct efi_hash2_protocol;

typedef uint8_t efi_md5_hash2[16];
typedef uint8_t efi_sha1_hash2[20];
typedef uint8_t efi_sha224_hash2[28];
typedef uint8_t efi_sha256_hash2[32];
typedef uint8_t efi_sha384_hash2[48];
typedef uint8_t efi_sha512_hash2[64];

union efi_hash2_output {
    efi_md5_hash2 md5_hash;
    efi_sha1_hash2 sha1_hash;
    efi_sha224_hash2 sha224_hash;
    efi_sha256_hash2 sha256_hash;
    efi_sha384_hash2 sha384_hash;
    efi_sha512_hash2 sha512_hash;
};

// The five services are printed as plain prototypes; the names here are the
// member types of the protocol structure.
typedef efi_status (EFI_API *efi_hash2_get_hash_size)(
    const struct efi_hash2_protocol *self,
    const struct efi_guid *hash_algorithm,
    size_t *hash_size
);

typedef efi_status (EFI_API *efi_hash2_hash)(
    const struct efi_hash2_protocol *self,
    const struct efi_guid *hash_algorithm,
    const uint8_t *message,
    size_t message_size,
    union efi_hash2_output *hash
);

typedef efi_status (EFI_API *efi_hash2_hash_init)(
    const struct efi_hash2_protocol *self,
    const struct efi_guid *hash_algorithm
);

typedef efi_status (EFI_API *efi_hash2_hash_update)(
    const struct efi_hash2_protocol *self,
    const uint8_t *message,
    size_t message_size
);

typedef efi_status (EFI_API *efi_hash2_hash_final)(
    const struct efi_hash2_protocol *self,
    union efi_hash2_output *hash
);

struct efi_hash2_protocol {
    efi_hash2_get_hash_size get_hash_size;
    efi_hash2_hash hash;
    efi_hash2_hash_init hash_init;
    efi_hash2_hash_update hash_update;
    efi_hash2_hash_final hash_final;
};

#define EFI_KMS_PROTOCOL_GUID \
    { 0xec3a978d, 0x7c4e, 0x48fa, { 0x9a, 0xbe, 0x6a, 0xd9, 0x1c, 0xc8, 0xf8, 0x11 } }

#define EFI_KMS_DATA_TYPE_NONE 0
#define EFI_KMS_DATA_TYPE_BINARY 1
#define EFI_KMS_DATA_TYPE_ASCII 2
#define EFI_KMS_DATA_TYPE_UNICODE 4
#define EFI_KMS_DATA_TYPE_UTF8 8

struct efi_kms_protocol;

struct efi_kms_client_info {
    uint16_t client_id_size;
    void *client_id;
    uint8_t client_name_type;
    uint8_t client_name_count;
    void *client_name;
};

#define EFI_KMS_FORMAT_GENERIC_128_GUID \
    { 0xec8a3d69, 0x6ddf, 0x4108, { 0x94, 0x76, 0x73, 0x37, 0xfc, 0x52, 0x21, 0x36 } }

#define EFI_KMS_FORMAT_GENERIC_160_GUID \
    { 0xa3b3e6f8, 0xefca, 0x4bc1, { 0x88, 0xfb, 0xcb, 0x87, 0x33, 0x9b, 0x25, 0x79 } }

#define EFI_KMS_FORMAT_GENERIC_256_GUID \
    { 0x70f64793, 0xc323, 0x4261, { 0xac, 0x2c, 0xd8, 0x76, 0xf2, 0x7c, 0x53, 0x45 } }

#define EFI_KMS_FORMAT_GENERIC_512_GUID \
    { 0x978fe043, 0xd7af, 0x422e, { 0x8a, 0x92, 0x2b, 0x48, 0xe4, 0x63, 0xbd, 0xe6 } }

#define EFI_KMS_FORMAT_GENERIC_1024_GUID \
    { 0x43be0b44, 0x874b, 0x4ead, { 0xb0, 0x9c, 0x24, 0x1a, 0x4f, 0xbd, 0x7e, 0xb3 } }

#define EFI_KMS_FORMAT_GENERIC_2048_GUID \
    { 0x40093f23, 0x630c, 0x4626, { 0x9c, 0x48, 0x40, 0x37, 0x3b, 0x19, 0xcb, 0xbe } }

#define EFI_KMS_FORMAT_GENERIC_3072_GUID \
    { 0xb9237513, 0x6c44, 0x4411, { 0xa9, 0x90, 0x21, 0xe5, 0x56, 0xe0, 0x5a, 0xde } }

#define EFI_KMS_FORMAT_GENERIC_DYNAMIC_GUID \
    { 0x2156e996, 0x66de, 0x4b27, { 0x9c, 0xc9, 0xb0, 0x9f, 0xac, 0x4d, 0x2, 0xbe } }

struct efi_kms_format_generic_dynamic {
    uint32_t key_size;
    uint8_t key_data[1];
};

#define EFI_KMS_FORMAT_MD2_128_GUID \
    { 0x78be11c4, 0xee44, 0x4a22, { 0x9f, 0x05, 0x03, 0x85, 0x2e, 0xc5, 0xc9, 0x78 } }

#define EFI_KMS_FORMAT_MDC2_128_GUID \
    { 0xf7ad60f8, 0xefa8, 0x44a3, { 0x91, 0x13, 0x23, 0x1f, 0x39, 0x9e, 0xb4, 0xc7 } }

// Printed with the inner brace one byte late.
#define EFI_KMS_FORMAT_MD4_128_GUID \
    { 0xd1c17aa1, 0xcac5, 0x400f, { 0xbe, 0x17, 0xe2, 0xa2, 0xae, 0x06, 0x67, 0x7c } }

#define EFI_KMS_FORMAT_MDC4_128_GUID \
    { 0x3fa4f847, 0xd8eb, 0x4df4, { 0xbd, 0x49, 0x10, 0x3a, 0x0a, 0x84, 0x7b, 0xbc } }

#define EFI_KMS_FORMAT_MD5_128_GUID \
    { 0xdcbc3662, 0x9cda, 0x4b52, { 0xa0, 0x4c, 0x82, 0xeb, 0x1d, 0x23, 0x48, 0xc7 } }

#define EFI_KMS_FORMAT_MD5SHA_128_GUID \
    { 0x1c178237, 0x6897, 0x459e, { 0x9d, 0x36, 0x67, 0xce, 0x8e, 0xf9, 0x4f, 0x76 } }

#define EFI_KMS_FORMAT_SHA1_160_GUID \
    { 0x453c5e5a, 0x482d, 0x43f0, { 0x87, 0xc9, 0x59, 0x41, 0xf3, 0xa3, 0x8a, 0xc2 } }

#define EFI_KMS_FORMAT_SHA256_256_GUID \
    { 0x6bb4f5cd, 0x8022, 0x448d, { 0xbc, 0x6d, 0x77, 0x1b, 0xae, 0x93, 0x5f, 0xc6 } }

#define EFI_KMS_FORMAT_SHA512_512_GUID \
    { 0x2f240e12, 0xe14d, 0x475c, { 0x83, 0xb0, 0xef, 0xff, 0x22, 0xd7, 0x7b, 0xe7 } }

#define EFI_KMS_FORMAT_AESXTS_128_GUID \
    { 0x4776e33f, 0xdb47, 0x479a, { 0xa2, 0x5f, 0xa1, 0xcd, 0x0a, 0xfa, 0xb3, 0x8b } }

#define EFI_KMS_FORMAT_AESXTS_256_GUID \
    { 0xdc7e8613, 0xc4bb, 0x4db0, { 0x84, 0x62, 0x13, 0x51, 0x13, 0x57, 0xab, 0xe2 } }

#define EFI_KMS_FORMAT_AESCBC_128_GUID \
    { 0xa0e8ee6a, 0x0e92, 0x44d4, { 0x86, 0x1b, 0x0e, 0xaa, 0x4a, 0xca, 0x44, 0xa2 } }

#define EFI_KMS_FORMAT_AESCBC_256_GUID \
    { 0xd7e69789, 0x1f68, 0x45e8, { 0x96, 0xef, 0x3b, 0x64, 0x07, 0xa5, 0xb2, 0xdc } }

#define EFI_KMS_FORMAT_RSASHA1_1024_GUID \
    { 0x56417bed, 0x6bbe, 0x4882, { 0x86, 0xa0, 0x3a, 0xe8, 0xbb, 0x17, 0xf8, 0xf9 } }

#define EFI_KMS_FORMAT_RSASHA1_2048_GUID \
    { 0xf66447d4, 0x75a6, 0x463e, { 0xa8, 0x19, 0x07, 0x7f, 0x2d, 0xda, 0x05, 0xe9 } }

#define EFI_KMS_FORMAT_RSASHA256_2048_GUID \
    { 0xa477af13, 0x877d, 0x4060, { 0xba, 0xa1, 0x25, 0xd1, 0xbe, 0xa0, 0x8a, 0xd3 } }

#define EFI_KMS_FORMAT_RSASHA256_3072_GUID \
    { 0x4e1356c2, 0xeed, 0x463f, { 0x81, 0x47, 0x99, 0x33, 0xab, 0xdb, 0xc7, 0xd5 } }

struct efi_kms_key_descriptor {
    uint8_t key_identifier_type;
    uint8_t key_identifier_size;
    void *key_identifier;
    struct efi_guid key_format;
    void *key_value;
    efi_status key_status;
};

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
#define EFI_KMS_ATTRIBUTE_TYPE_STRUCTURE 0x0a
#define EFI_KMS_ATTRIBUTE_TYPE_DYNAMIC 0x0b

struct efi_kms_dynamic_field {
    uint16_t tag;
    uint16_t type;
    uint32_t length;
    uint8_t key_attribute_data[1];
};

struct efi_kms_dynamic_attribute {
    uint32_t field_count;
    struct efi_kms_dynamic_field field[1];
};

struct efi_kms_key_attribute {
    uint8_t key_attribute_identifier_type;
    uint8_t key_attribute_identifier_count;
    void *key_attribute_identifier;
    uint16_t key_attribute_instance;
    uint16_t key_attribute_type;
    uint16_t key_attribute_value_size;
    void *key_attribute_value;
    efi_status key_attribute_status;
};

typedef efi_status (EFI_API *efi_kms_get_service_status)(struct efi_kms_protocol *self);

typedef efi_status (EFI_API *efi_kms_register_client)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_create_key)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint16_t *key_descriptor_count,
    struct efi_kms_key_descriptor *key_descriptors,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_get_key)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint16_t *key_descriptor_count,
    struct efi_kms_key_descriptor *key_descriptors,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_add_key)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint16_t *key_descriptor_count,
    struct efi_kms_key_descriptor *key_descriptors,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_delete_key)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint16_t *key_descriptor_count,
    struct efi_kms_key_descriptor *key_descriptors,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_get_key_attributes)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint8_t *key_identifier_size,
    const void *key_identifier,
    uint16_t *key_attributes_count,
    struct efi_kms_key_attribute *key_attributes,
    size_t *client_data_size,
    void **client_data
);

// key_identifier_size is printed as UINT *, a type that does not exist; its
// siblings use uint8_t *.
typedef efi_status (EFI_API *efi_kms_add_key_attributes)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint8_t *key_identifier_size,
    const void *key_identifier,
    uint16_t *key_attributes_count,
    struct efi_kms_key_attribute *key_attributes,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_delete_key_attributes)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    uint8_t *key_identifier_size,
    const void *key_identifier,
    uint16_t *key_attributes_count,
    struct efi_kms_key_attribute *key_attributes,
    size_t *client_data_size,
    void **client_data
);

typedef efi_status (EFI_API *efi_kms_get_key_by_attributes)(
    struct efi_kms_protocol *self,
    struct efi_kms_client_info *client,
    size_t *key_attribute_count,
    struct efi_kms_key_attribute *key_attributes,
    size_t *key_descriptor_count,
    struct efi_kms_key_descriptor *key_descriptors,
    size_t *client_data_size,
    void **client_data
);

struct efi_kms_protocol {
    efi_kms_get_service_status get_service_status;
    efi_kms_register_client register_client;
    efi_kms_create_key create_key;
    efi_kms_get_key get_key;
    efi_kms_add_key add_key;
    efi_kms_delete_key delete_key;
    efi_kms_get_key_attributes get_key_attributes;
    efi_kms_add_key_attributes add_key_attributes;
    efi_kms_delete_key_attributes delete_key_attributes;
    efi_kms_get_key_by_attributes get_key_by_attributes;
    uint32_t protocol_version;
    struct efi_guid service_id;
    uint16_t *service_name;
    uint32_t service_version;
    uint8_t service_available;
    uint8_t client_id_supported;
    uint8_t client_id_required;
    uint16_t client_id_max_size;
    uint8_t client_name_string_types;
    uint8_t client_name_required;
    uint16_t client_name_max_count;
    uint8_t client_data_supported;
    size_t client_data_max_size;
    uint8_t key_id_variable_len_supported;
    size_t key_id_max_size;
    size_t key_formats_count;
    struct efi_guid *key_formats;
    uint8_t key_attributes_supported;
    uint8_t key_attribute_id_string_types;
    uint16_t key_attribute_id_max_count;
    size_t key_attributes_count;
    struct efi_kms_key_attribute *key_attributes;
};

#define EFI_PKCS7_VERIFY_PROTOCOL_GUID \
    { 0x47889fb2, 0xd671, 0x4fab, { 0xa0, 0xca, 0xdf, 0xe, 0x44, 0xdf, 0x70, 0xd6 } }

struct efi_pkcs7_verify_protocol;

// Printed under the member names; the names here are the member types of the
// protocol structure.
typedef efi_status (EFI_API *efi_pkcs7_verify_buffer)(
    struct efi_pkcs7_verify_protocol *self,
    void *signed_data,
    size_t signed_data_size,
    void *in_data,
    size_t in_data_size,
    struct efi_signature_list **allowed_db,
    struct efi_signature_list **revoked_db,
    struct efi_signature_list **time_stamp_db,
    void *content,
    size_t *content_size
);

typedef efi_status (EFI_API *efi_pkcs7_verify_signature)(
    struct efi_pkcs7_verify_protocol *self,
    void *signature,
    size_t signature_size,
    void *in_hash,
    size_t in_hash_size,
    struct efi_signature_list **allowed_db,
    struct efi_signature_list **revoked_db,
    struct efi_signature_list **time_stamp_db
);

// The members are printed as pointers to these types, which are already
// function pointers.
struct efi_pkcs7_verify_protocol {
    efi_pkcs7_verify_buffer verify_buffer;
    efi_pkcs7_verify_signature verify_signature;
};

#define EFI_SMART_CARD_READER_PROTOCOL_GUID \
    { 0x2a4d1adf, 0x21dc, 0x4b81, { 0xa4, 0x2f, 0x8b, 0x8e, 0xe2, 0x38, 0x00, 0x60 } }

struct efi_smart_card_reader_protocol;

// The prototypes print these names with _PROTOCOL_ inserted
// (..._READER_PROTOCOL_CONNECT); the names here are the ones the protocol
// structure uses, in the pattern of the Edge protocol.
typedef efi_status (EFI_API *efi_smart_card_reader_connect)(
    struct efi_smart_card_reader_protocol *self,
    uint32_t access_mode,
    uint32_t card_action,
    uint32_t preferred_protocols,
    uint32_t *active_protocol
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

typedef efi_status (EFI_API *efi_smart_card_reader_disconnect)(
    struct efi_smart_card_reader_protocol *self,
    uint32_t card_action
);

typedef efi_status (EFI_API *efi_smart_card_reader_status)(
    struct efi_smart_card_reader_protocol *self,
    uint16_t *reader_name,
    size_t *reader_name_length,
    uint32_t *state,
    uint32_t *card_protocol,
    uint8_t *atr,
    size_t *atr_length
);

#define EFI_SCARD_UNKNOWN 0x0000
#define EFI_SCARD_ABSENT 0x0001
#define EFI_SCARD_INACTIVE 0x0002
#define EFI_SCARD_ACTIVE 0x0003

typedef efi_status (EFI_API *efi_smart_card_reader_transmit)(
    struct efi_smart_card_reader_protocol *self,
    uint8_t *capdu,
    size_t capdu_length,
    uint8_t *rapdu,
    size_t *rapdu_length
);

typedef efi_status (EFI_API *efi_smart_card_reader_control)(
    struct efi_smart_card_reader_protocol *self,
    uint32_t control_code,
    uint8_t *in_buffer,
    size_t in_buffer_length,
    uint8_t *out_buffer,
    size_t *out_buffer_length
);

#define EFI_SCARD_CTL_CODE(code) (0x42000000 + (code))
#define EFI_CM_IOCTL_GET_FEATURE_REQUEST EFI_SCARD_CTL_CODE(3400)

typedef efi_status (EFI_API *efi_smart_card_reader_get_attrib)(
    struct efi_smart_card_reader_protocol *self,
    uint32_t attrib,
    uint8_t *out_buffer,
    size_t *out_buffer_length
);

struct efi_smart_card_reader_protocol {
    efi_smart_card_reader_connect scard_connect;
    efi_smart_card_reader_disconnect scard_disconnect;
    efi_smart_card_reader_status scard_status;
    efi_smart_card_reader_transmit scard_transmit;
    efi_smart_card_reader_control scard_control;
    efi_smart_card_reader_get_attrib scard_get_attrib;
};

#define EFI_SMART_CARD_EDGE_PROTOCOL_GUID \
    { 0xd317f29b, 0xa325, 0x4712, { 0x9b, 0xf1, 0xc6, 0x19, 0x54, 0xdc, 0x19, 0x8c } }

struct efi_smart_card_edge_protocol;

#define EFI_SCARD_AID_MAXSIZE 0x0010
#define EFI_SCARD_CSN_SIZE 0x0010
#define EFI_SMART_CARD_EDGE_PROTOCOL_VERSION_1 0x00000100

typedef uint8_t efi_smart_card_aid[EFI_SCARD_AID_MAXSIZE];
typedef uint8_t efi_smart_card_csn[EFI_SCARD_CSN_SIZE];

typedef efi_status (EFI_API *efi_smart_card_edge_get_context)(
    struct efi_smart_card_edge_protocol *self,
    size_t *number_aid_supported,
    size_t *aid_table_size,
    efi_smart_card_aid *aid_table,
    size_t *number_sc_present,
    size_t *csn_table_size,
    efi_smart_card_csn *csn_table,
    uint32_t *version_sc_edge_protocol
);

typedef efi_status (EFI_API *efi_smart_card_edge_connect)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle *scard_handle,
    uint8_t *scard_csn,
    uint8_t *scard_aid
);

typedef efi_status (EFI_API *efi_smart_card_edge_disconnect)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle
);

typedef efi_status (EFI_API *efi_smart_card_edge_get_csn)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    uint8_t csn[EFI_SCARD_CSN_SIZE]
);

typedef efi_status (EFI_API *efi_smart_card_edge_get_reader_name)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    size_t *reader_name_length,
    uint16_t *reader_name
);

typedef efi_status (EFI_API *efi_smart_card_edge_verify_pin)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    int32_t pin_size,
    uint8_t *pin_code,
    bool *pin_result,
    uint32_t *remaining_attempts
);

typedef efi_status (EFI_API *efi_smart_card_edge_get_pin_remaining)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    uint32_t *remaining_attempts
);

typedef efi_status (EFI_API *efi_smart_card_edge_get_data)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    struct efi_guid *data_id,
    size_t *data_size,
    void *data
);

typedef efi_status (EFI_API *efi_smart_card_edge_get_credential)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    size_t *credential_size,
    uint8_t *credential_list
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

typedef efi_status (EFI_API *efi_smart_card_edge_sign_data)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    uintptr_t key_id,
    uintptr_t key_type,
    struct efi_guid *hash_algorithm,
    struct efi_guid *padding_method,
    uint8_t *hashed_data,
    uint8_t *signature_data
);

#define EFI_PADDING_RSASSA_PKCS1V1P5_GUID \
    { 0x9317ec24, 0x7cb0, 0x4d0e, { 0x8b, 0x32, 0x2e, 0xd9, 0x20, 0x9c, 0xd8, 0xaf } }

#define EFI_PADDING_RSASSA_PSS_GUID \
    { 0x7b2349e0, 0x522d, 0x4f8e, { 0xb9, 0x27, 0x69, 0xd9, 0x7c, 0x9e, 0x79, 0x5f } }

typedef efi_status (EFI_API *efi_smart_card_edge_decrypt_data)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    uintptr_t key_id,
    struct efi_guid *hash_algorithm,
    struct efi_guid *padding_method,
    size_t encrypted_size,
    uint8_t *encrypted_data,
    size_t *plaintext_size,
    uint8_t *plaintext_data
);

#define EFI_PADDING_NONE_GUID \
    { 0x3629ddb1, 0x228c, 0x452e, { 0xb6, 0x16, 0x09, 0xed, 0x31, 0x6a, 0x97, 0x00 } }

#define EFI_PADDING_RSAES_PKCS1V1P5_GUID \
    { 0xe1c1d0a9, 0x40b1, 0x4632, { 0xbd, 0xcc, 0xd9, 0xd6, 0xe5, 0x29, 0x56, 0x31 } }

#define EFI_PADDING_RSAES_OAEP_GUID \
    { 0xc1e63ac4, 0xd0cf, 0x4ce6, { 0x83, 0x5b, 0xee, 0xd0, 0xe6, 0xa8, 0xa4, 0x5b } }

typedef efi_status (EFI_API *efi_smart_card_edge_build_dh_agreement)(
    struct efi_smart_card_edge_protocol *self,
    efi_handle scard_handle,
    uintptr_t key_id,
    uint8_t *data_qx,
    uint8_t *data_qy,
    uint8_t *dh_agreement
);

struct efi_smart_card_edge_protocol {
    efi_smart_card_edge_get_context get_context;
    efi_smart_card_edge_connect connect;
    efi_smart_card_edge_disconnect disconnect;
    efi_smart_card_edge_get_csn get_csn;
    efi_smart_card_edge_get_reader_name get_reader_name;
    efi_smart_card_edge_verify_pin verify_pin;
    efi_smart_card_edge_get_pin_remaining get_pin_remaining;
    efi_smart_card_edge_get_data get_data;
    efi_smart_card_edge_get_credential get_credential;
    efi_smart_card_edge_sign_data sign_data;
    efi_smart_card_edge_decrypt_data decrypt_data;
    efi_smart_card_edge_build_dh_agreement build_dh_agreement;
};

#ifdef __cplusplus
}
#endif

#endif
