#ifndef EFI_EFISTRING_H
#define EFI_EFISTRING_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_REGULAR_EXPRESSION_PROTOCOL_GUID \
    { 0xb3f79d9a, 0x436c, 0xdc11, { 0xb0, 0x52, 0xcd, 0x85, 0xdf, 0x52, 0x4c, 0xe6 } }

struct efi_regular_expression_protocol;

typedef struct efi_guid efi_regex_syntax_type;

struct efi_regex_capture {
    const uint16_t *capture_ptr;
    size_t length;
};

typedef efi_status (EFI_API *efi_regular_expression_match)(
    struct efi_regular_expression_protocol *self,
    uint16_t *string,
    uint16_t *pattern,
    efi_regex_syntax_type *syntax_type,
    bool *result,
    struct efi_regex_capture **captures,
    size_t *captures_count
);

typedef efi_status (EFI_API *efi_regular_expression_get_info)(
    struct efi_regular_expression_protocol *self,
    size_t *reg_ex_syntax_type_list_size,
    efi_regex_syntax_type *reg_ex_syntax_type_list
);

struct efi_regular_expression_protocol {
    efi_regular_expression_match match_string;
    efi_regular_expression_get_info get_info;
};

#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_GUID \
    { 0x5f05b20f, 0x4a56, 0xc231, { 0xfa, 0x0b, 0xa7, 0xb1, 0xf1, 0x10, 0x04, 0x1d } }

#define EFI_REGEX_SYNTAX_TYPE_PERL_GUID \
    { 0x63e60a51, 0x497d, 0xd427, { 0xc4, 0xa5, 0xb8, 0xab, 0xdc, 0x3a, 0xae, 0xb6 } }

// Printed with the first data4 byte (0x41) outside the inner braces.
#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_GUID \
    { 0x9a473a4a, 0x4ceb, 0xb95a, { 0x41, 0x5e, 0x5b, 0xa0, 0xbc, 0x63, 0x9b, 0x2e } }

#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_ASCII_GUID \
    { 0x3fd32128, 0x4bb1, 0xf632, { 0xbe, 0x4f, 0xba, 0xbf, 0x85, 0xc9, 0x36, 0x76 } }

#define EFI_REGEX_SYNTAX_TYPE_PERL_ASCII_GUID \
    { 0x87dfb76d, 0x4b58, 0xef3a, { 0xf7, 0xc6, 0x16, 0xa4, 0x2a, 0x68, 0x28, 0x10 } }

#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_ASCII_GUID \
    { 0xb2284a2f, 0x4491, 0x6d9d, { 0xea, 0xb7, 0x11, 0xb0, 0x67, 0xd4, 0x9b, 0x9a } }

#ifdef __cplusplus
}
#endif

#endif
