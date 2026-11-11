#ifndef EFI_H
#define EFI_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stdint.h>
#include <efi/efi_nii.h>
#include <efi/efi_pxe.h>
#include <efi/efiacpi.h>
#include <efi/efiapi.h>
#include <efi/efiarpdhcp.h>
#include <efi/efibis.h>
#include <efi/efibluetooth.h>
#include <efi/efibootmgr.h>
#include <efi/efibtt.h>
#include <efi/eficc.h>
#include <efi/eficompress.h>
#include <efi/eficon.h>
#include <efi/eficonex.h>
#include <efi/eficper.h>
#include <efi/efidebug.h>
#include <efi/efidef.h>
#include <efi/efidevp.h>
#include <efi/efidriver.h>
#include <efi/efierr.h>
#include <efi/efifwupdate.h>
#include <efi/efigpt.h>
#include <efi/efihii.h>
#include <efi/efihiiconfig.h>
#include <efi/efihiiprot.h>
#include <efi/efiip.h>
#include <efi/efiiscsi.h>
#include <efi/efimedia.h>
#include <efi/efimisc.h>
#include <efi/efimnp.h>
#include <efi/efimp.h>
#include <efi/efimtftp.h>
#include <efi/efinet.h>
#include <efi/efipart.h>
#include <efi/efipciio.h>
#include <efi/efipoint.h>
#include <efi/efiprot.h>
#include <efi/efipxebc.h>
#include <efi/efiredfish.h>
#include <efi/efiriscvboot.h>
#include <efi/efiscsi.h>
#include <efi/efisectech.h>
#include <efi/efisecureboot.h>
#include <efi/efiser.h>
#include <efi/efishell.h>
#include <efi/efistring.h>
#include <efi/efitcg2.h>
#include <efi/efitcp.h>
#include <efi/efitcpip.h>
#include <efi/efiudp.h>
#include <efi/efiusb.h>
#include <efi/efiuserid.h>
#include <efi/efivlaneap.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Where the image was loaded. As it is linked at address 0, this is also how far everything in it
 * slid: subtracting it from an address in the image gives the one it was linked at.
 */
extern const uint8_t efi_load_slide[];

/*
 * The size of the image in memory, .bss included: what the firmware allocated at efi_load_slide, a
 * whole number of pages.
 */
extern const uint32_t efi_image_size;

#ifdef __cplusplus
}
#endif

#endif
