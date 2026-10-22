    .option norelax

#define EFI_IMAGE_MACHINE_RISCV32 0x5032
#define EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION 10

#define IMAGE_FILE_EXECUTABLE_IMAGE 0x0002
#define IMAGE_FILE_LINE_NUMS_STRIPPED 0x0004
#define IMAGE_FILE_32BIT_MACHINE 0x0100
#define IMAGE_FILE_DEBUG_STRIPPED 0x0200

#define IMAGE_DLLCHARACTERISTICS_NX_COMPAT 0x0100

#define IMAGE_SCN_CNT_CODE 0x00000020
#define IMAGE_SCN_CNT_INITIALIZED_DATA 0x00000040
#define IMAGE_SCN_MEM_DISCARDABLE 0x02000000
#define IMAGE_SCN_MEM_EXECUTE 0x20000000
#define IMAGE_SCN_MEM_READ 0x40000000
#define IMAGE_SCN_MEM_WRITE 0x80000000

#define IMAGE_REL_BASED_ABSOLUTE 0

/*
 * The image is linked at address 0 with .pe_header first, so "symbol - .Lheader" is the symbol's
 * value. Every header value taken from a symbol is written so: the assemblers emit it as a
 * PC-relative relocation or an ADD32/SUB32 pair, which GNU ld and LLD resolve at link time,
 * whereas the plain symbol, an absolute relocation, is rejected or made dynamic in a PIE.
 */
    .section .pe_header, "ax"
    /*
     * Where the image was loaded, for the program. A label, as gold leaves stored pointers to a
     * link script symbol unrelocated, and older GNU ld gives them symbolic relocations.
     */
    .globl EfiLoadSlide
    .hidden EfiLoadSlide
EfiLoadSlide:
.Lheader:
    .ascii "MZ" /* e_magic */
    .short 0x0090 /* e_cblp */
    .short 0x0003 /* e_cp */
    .short 0 /* e_crlc */
    .short 0x0004 /* e_cparhdr */
    .short 0 /* e_minalloc */
    .short 0xffff /* e_maxalloc */
    .short 0 /* e_ss */
    .short 0x00b8 /* e_sp */
    .short 0 /* e_csum */
    .short 0 /* e_ip */
    .short 0 /* e_cs */
    .short 0x0040 /* e_lfarlc */
    .short 0 /* e_ovno */
    .org .Lheader + 0x3c /* e_res, e_oemid, e_oeminfo, e_res2 */
    .long .Lpe_signature - .Lheader /* e_lfanew */

    /* The DOS program at the header's entry point: print the message, exit with return code 1. */
.Ldos_program:
    .byte 0x0e /* push cs */
    .byte 0x1f /* pop ds */
    .byte 0xba /* mov dx, offset of the message */
    .short .Ldos_message - .Ldos_program
    .byte 0xb4, 0x09 /* mov ah, 0x09 */
    .byte 0xcd, 0x21 /* int 0x21 */
    .byte 0xb8 /* mov ax, 0x4c01 */
    .short 0x4c01
    .byte 0xcd, 0x21 /* int 0x21 */
.Ldos_message:
    .ascii "This program cannot be run in DOS mode.\r\r\n$"
    .org .Lheader + 0x80

.Lpe_signature:
    .ascii "PE\0\0"
    .short EFI_IMAGE_MACHINE_RISCV32 /* Machine */
    .short (.Lsections_end - .Lsections) / 40 /* NumberOfSections */
    .long 0 /* TimeDateStamp */
    .long 0 /* PointerToSymbolTable */
    .long 0 /* NumberOfSymbols */
    .short .Lsections - .Loptional_header /* SizeOfOptionalHeader */
    .short IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_LINE_NUMS_STRIPPED | \
        IMAGE_FILE_32BIT_MACHINE | IMAGE_FILE_DEBUG_STRIPPED /* Characteristics */

.Loptional_header:
    .short 0x10b /* Magic: PE32 */
    .byte 2 /* MajorLinkerVersion */
    .byte 38 /* MinorLinkerVersion */
    .long picoefi_text_size - .Lheader /* SizeOfCode */
    /* SizeOfInitializedData: the file data of .reloc, .rdata and .data. */
    .long picoefi_initialized_data_size - .Lheader
    .long picoefi_bss_size - .Lheader /* SizeOfUninitializedData */
    .long _start - .Lheader /* AddressOfEntryPoint */
    .long picoefi_text_start - .Lheader /* BaseOfCode */
    .long picoefi_rodata_start - .Lheader /* BaseOfData */
    .long 0 /* ImageBase */
    .long 0x1000 /* SectionAlignment */
    .long 0x1000 /* FileAlignment */
    .short 0 /* MajorOperatingSystemVersion */
    .short 0 /* MinorOperatingSystemVersion */
    .short 0 /* MajorImageVersion */
    .short 0 /* MinorImageVersion */
    .short 0 /* MajorSubsystemVersion */
    .short 0 /* MinorSubsystemVersion */
    .long 0 /* Win32VersionValue */
    .long picoefi_image_size - .Lheader /* SizeOfImage */
    .long picoefi_text_start - .Lheader /* SizeOfHeaders */
    .long 0 /* CheckSum */
    .short EFI_IMAGE_SUBSYSTEM_EFI_APPLICATION /* Subsystem */
    .short IMAGE_DLLCHARACTERISTICS_NX_COMPAT /* DllCharacteristics */
    .long 0 /* SizeOfStackReserve */
    .long 0 /* SizeOfStackCommit */
    .long 0 /* SizeOfHeapReserve */
    .long 0 /* SizeOfHeapCommit */
    .long 0 /* LoaderFlags */
    .long (.Lsections - .Ldirectories) / 8 /* NumberOfRvaAndSizes */

.Ldirectories:
    .quad 0 /* Export Table */
    .quad 0 /* Import Table */
    .quad 0 /* Resource Table */
    .quad 0 /* Exception Table */
    .quad 0 /* Certificate Table */
    /*
     * Base Relocation Table. Referring to the block, not to picoefi_reloc_start, is what keeps
     * .dummy_reloc from --gc-sections.
     */
    .long .Lbase_relocations - .Lheader
    .long .Lbase_relocations_end - .Lbase_relocations

.Lsections:
    .ascii ".text\0\0\0"
    .long picoefi_text_size - .Lheader /* VirtualSize */
    .long picoefi_text_start - .Lheader /* VirtualAddress */
    .long picoefi_text_size - .Lheader /* SizeOfRawData */
    .long picoefi_text_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ

    .ascii ".reloc\0\0"
    /* VirtualSize: exactly the base relocation data; SizeOfRawData is its whole page. */
    .long .Lbase_relocations_end - .Lbase_relocations
    .long picoefi_reloc_start - .Lheader /* VirtualAddress */
    .long picoefi_reloc_size - .Lheader /* SizeOfRawData */
    .long picoefi_reloc_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_DISCARDABLE | IMAGE_SCN_MEM_READ

    .ascii ".rdata\0\0"
    .long picoefi_rodata_size - .Lheader /* VirtualSize */
    .long picoefi_rodata_start - .Lheader /* VirtualAddress */
    .long picoefi_rodata_size - .Lheader /* SizeOfRawData */
    .long picoefi_rodata_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ

    .ascii ".data\0\0\0"
    .long picoefi_data_size - .Lheader /* VirtualSize */
    .long picoefi_data_start - .Lheader /* VirtualAddress */
    .long picoefi_data_rawsize - .Lheader /* SizeOfRawData */
    .long picoefi_data_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE
.Lsections_end:

    .section .dummy_reloc, "a"
    /*
     * Without base relocations, firmware may load the image at ImageBase only. One block of
     * IMAGE_REL_BASED_ABSOLUTE entries, which change nothing; two keep it a multiple of 4. Its
     * page is given as the dummy word's address less the block's own, a link-time constant.
     */
.Lbase_relocations:
    .long .Ldummy - .Lbase_relocations /* Page RVA */
    .long .Lbase_relocations_end - .Lbase_relocations /* Block Size */
    .short IMAGE_REL_BASED_ABSOLUTE << 12
    .short IMAGE_REL_BASED_ABSOLUTE << 12
.Lbase_relocations_end:

    /* The word the base relocation block names; nothing reads it. */
    .data
    .balign 0x1000
.Ldummy:
    .long 0

    .text
    .globl _start
    .type _start, %function
_start:
    /*
     * Save what the UEFI convention preserves beyond the C one and the registers used here, and
     * give the calls the stack alignment, and on x86 the clear direction flag, that not all
     * firmware provides. ImageHandle and SystemTable wait where the relocator leaves them.
     */
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 20(sp)
    sw s2, 16(sp)
    sw gp, 12(sp)
    sw tp, 8(sp)
    mv s0, sp
    andi sp, sp, -16
    mv s1, a0
    mv s2, a1

    /* Zero .bss: firmware need not zero a section beyond its file data. */
    lla t0, picoefi_bss_start
    lla t1, picoefi_bss_end
.Lzero:
    bgeu t0, t1, .Lzeroed
    andi t2, t0, 3
    bnez t2, .Lzero_byte
    sub t2, t1, t0
    li t3, 4
    bltu t2, t3, .Lzero_byte
    sw zero, 0(t0)
    addi t0, t0, 4
    j .Lzero
.Lzero_byte:
    sb zero, 0(t0)
    addi t0, t0, 1
    j .Lzero
.Lzeroed:

    /* Nothing is relocated yet, so the arguments are reached PC-relatively. */
    lla a0, picoefi_image_base
    lla a1, _DYNAMIC
    lla a2, picoefi_data_start
    lla a3, picoefi_data_end
    call picoefi_relocate
    /* An image that cannot be relocated must not run: return the status. */
    bnez a0, .Lreturn

    mv a0, s1
    mv a1, s2
    call efi_main

.Lreturn:
    mv sp, s0
    lw tp, 8(sp)
    lw gp, 12(sp)
    lw s2, 16(sp)
    lw s1, 20(sp)
    lw s0, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32
    ret
    .size _start, . - _start
