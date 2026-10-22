#ifndef EFI_H_
#define EFI_H_

#include "efi/efidef.h"
#include "efi/efierr.h"
#include "efi/efidevp.h"
#include "efi/eficon.h"
#include "efi/eficonex.h"
#include "efi/efiapi.h"
#include "efi/efinet.h"
#include "efi/efibootmgr.h"

#include "efi/efiprot.h"
#include "efi/efipoint.h"
#include "efi/efiser.h"
#include "efi/efistring.h"
#include "efi/eficompress.h"
#include "efi/efiacpi.h"
#include "efi/efimisc.h"

#include "efi/efipart.h"
#include "efi/efigpt.h"
#include "efi/efimedia.h"
#include "efi/efibtt.h"
#include "efi/efiscsi.h"
#include "efi/efiiscsi.h"

#include "efi/efipciio.h"
#include "efi/efiusb.h"

#include "efi/efipxebc.h"
#include "efi/efi_nii.h"
#include "efi/efi_pxe.h"
#include "efi/efibis.h"
#include "efi/efimnp.h"
#include "efi/efiip.h"
#include "efi/efitcp.h"
#include "efi/efiudp.h"
#include "efi/efitcpip.h"
#include "efi/efimtftp.h"
#include "efi/efibluetooth.h"
#include "efi/efivlaneap.h"
#include "efi/efiarpdhcp.h"
#include "efi/efiredfish.h"

#include "efi/efisecureboot.h"
#include "efi/efisectech.h"
#include "efi/eficc.h"
#include "efi/efitcg2.h"

#include "efi/efidebug.h"
#include "efi/efifwupdate.h"
#include "efi/eficper.h"

#include "efi/efihii.h"
#include "efi/efihiiprot.h"
#include "efi/efihiiconfig.h"

#include "efi/efidriver.h"
#include "efi/efiuserid.h"
#include "efi/efimp.h"
#include "efi/efishell.h"
#include "efi/efiriscvboot.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Where the image was loaded. As it is linked at address 0, this is also how far everything in it
 * slid: subtracting it from an address in the image gives the one it was linked at.
 */
extern EFI_CONST EFI_UINT8 EfiLoadSlide[];

#ifdef __cplusplus
}
#endif

#endif
