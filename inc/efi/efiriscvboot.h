#ifndef EFI_EFIRISCVBOOT_H
#define EFI_EFIRISCVBOOT_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_RISCV_EFI_BOOT_PROTOCOL_GUID \
    {0xccd15fec, 0x6f73, 0x4eec, {0x83, 0x95, 0x3e, 0x69, 0xe4, 0xb9, 0x40, 0xbf}}

#define EFI_RISCV_EFI_BOOT_PROTOCOL_REVISION 0x00010000
#define EFI_RISCV_EFI_BOOT_PROTOCOL_LATEST_VERSION EFI_RISCV_EFI_BOOT_PROTOCOL_REVISION

struct efi_riscv_efi_boot_protocol;

typedef efi_status (EFI_API *efi_get_boot_hartid)(
    struct efi_riscv_efi_boot_protocol *self,
    uintptr_t *boot_hart_id
);

struct efi_riscv_efi_boot_protocol {
    uint64_t revision;
    efi_get_boot_hartid get_boot_hart_id;
};

#ifdef __cplusplus
}
#endif

#endif
