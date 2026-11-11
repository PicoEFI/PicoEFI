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
    {0xB3F79D9A, 0x436C, 0xDC11, {0xB0, 0x52, 0xCD, 0x85, 0xDF, 0x52, 0x4C, 0xE6}}

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
    {0x5F05B20F, 0x4A56, 0xC231, {0xFA, 0x0B, 0xA7, 0xB1, 0xF1, 0x10, 0x04, 0x1D}}

#define EFI_REGEX_SYNTAX_TYPE_PERL_GUID \
    {0x63E60A51, 0x497D, 0xD427, {0xC4, 0xA5, 0xB8, 0xAB, 0xDC, 0x3A, 0xAE, 0xB6}}

/* Printed with the first data4 byte (0x41) outside the inner braces. */
#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_GUID \
    {0x9A473A4A, 0x4CEB, 0xB95A, {0x41, 0x5E, 0x5B, 0xA0, 0xBC, 0x63, 0x9B, 0x2E}}

#define EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_ASCII_GUID \
    {0x3FD32128, 0x4BB1, 0xF632, {0xBE, 0x4F, 0xBA, 0xBF, 0x85, 0xC9, 0x36, 0x76}}

#define EFI_REGEX_SYNTAX_TYPE_PERL_ASCII_GUID \
    {0x87DFB76D, 0x4B58, 0xEF3A, {0xF7, 0xC6, 0x16, 0xA4, 0x2A, 0x68, 0x28, 0x10}}

#define EFI_REGEX_SYNTAX_TYPE_ECMA_262_ASCII_GUID \
    {0xB2284A2F, 0x4491, 0x6D9D, {0xEA, 0xB7, 0x11, 0xB0, 0x67, 0xD4, 0x9B, 0x9A}}

#ifdef __cplusplus
}
#endif

#endif
