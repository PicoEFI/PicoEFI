#define EFI_IMAGE_MACHINE_IA32 0x014c
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
    .short EFI_IMAGE_MACHINE_IA32 /* Machine */
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
    .long __text_size - .Lheader /* SizeOfCode */
    /* SizeOfInitializedData: the file data of .reloc, .rdata and .data. */
    .long __initialized_data_size - .Lheader
    .long __bss_size - .Lheader /* SizeOfUninitializedData */
    .long _start - .Lheader /* AddressOfEntryPoint */
    .long __text_start - .Lheader /* BaseOfCode */
    .long __rodata_start - .Lheader /* BaseOfData */
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
    .long __image_size - .Lheader /* SizeOfImage */
    .long __text_start - .Lheader /* SizeOfHeaders */
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
     * Base Relocation Table. Referring to the block, not to __reloc_start, is what keeps
     * .dummy_reloc from --gc-sections.
     */
    .long .Lbase_relocations - .Lheader
    .long .Lbase_relocations_end - .Lbase_relocations

.Lsections:
    .ascii ".text\0\0\0"
    .long __text_size - .Lheader /* VirtualSize */
    .long __text_start - .Lheader /* VirtualAddress */
    .long __text_size - .Lheader /* SizeOfRawData */
    .long __text_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ

    .ascii ".reloc\0\0"
    /* VirtualSize: exactly the base relocation data; SizeOfRawData is its whole page. */
    .long .Lbase_relocations_end - .Lbase_relocations
    .long __reloc_start - .Lheader /* VirtualAddress */
    .long __reloc_size - .Lheader /* SizeOfRawData */
    .long __reloc_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_DISCARDABLE | IMAGE_SCN_MEM_READ

    .ascii ".rdata\0\0"
    .long __rodata_size - .Lheader /* VirtualSize */
    .long __rodata_start - .Lheader /* VirtualAddress */
    .long __rodata_size - .Lheader /* SizeOfRawData */
    .long __rodata_start - .Lheader /* PointerToRawData */
    .long 0 /* PointerToRelocations */
    .long 0 /* PointerToLinenumbers */
    .short 0 /* NumberOfRelocations */
    .short 0 /* NumberOfLinenumbers */
    .long IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_READ

    .ascii ".data\0\0\0"
    .long __data_size - .Lheader /* VirtualSize */
    .long __data_start - .Lheader /* VirtualAddress */
    .long __data_rawsize - .Lheader /* SizeOfRawData */
    .long __data_start - .Lheader /* PointerToRawData */
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
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    andl $-16, %esp
    cld
    subl $16, %esp
    call .Lget_pc
.Lpc:

    /* Zero .bss: firmware need not zero a section beyond its file data. */
    leal __bss_start - .Lpc(%ebx), %eax
    leal __bss_end - .Lpc(%ebx), %ecx
.Lzero:
    cmpl %ecx, %eax
    jae .Lzeroed
    testl $3, %eax
    jnz .Lzero_byte
    movl %ecx, %edx
    subl %eax, %edx
    cmpl $4, %edx
    jb .Lzero_byte
    movl $0, (%eax)
    addl $4, %eax
    jmp .Lzero
.Lzero_byte:
    movb $0, (%eax)
    addl $1, %eax
    jmp .Lzero
.Lzeroed:

    /* Nothing is relocated yet: the image base and _DYNAMIC are reached PC-relatively. */
    leal __image_base - .Lpc(%ebx), %eax
    movl %eax, (%esp)
    leal _DYNAMIC - .Lpc(%ebx), %eax
    movl %eax, 4(%esp)
    call __picoefi_relocate
    /* An image that cannot be relocated must not run: return the status. */
    testl %eax, %eax
    jnz .Lreturn

    movl 8(%ebp), %eax
    movl %eax, (%esp)
    movl 12(%ebp), %edx
    movl %edx, 4(%esp)
    call efi_main

.Lreturn:
    leal -4(%ebp), %esp
    popl %ebx
    popl %ebp
    ret

.Lget_pc:
    movl (%esp), %ebx
    ret
    .size _start, . - _start
