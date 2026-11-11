#ifndef EFI_EFIDEBUG_H
#define EFI_EFIDEBUG_H 1

#if !defined(__cplusplus) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L)
#   error "PicoEFI needs C99 or later."
#endif

#include <stddef.h>
#include <stdint.h>
#include <efi/efidef.h>
#include <efi/efiprot.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DEBUG_SUPPORT_PROTOCOL_GUID \
    { 0x2755590c, 0x6f3c, 0x42fa, { 0x9e, 0xa4, 0xa3, 0xba, 0x54, 0x3c, 0xda, 0x25 } }

struct efi_debug_support_protocol;

// Printed as IMAGE_FILE_MACHINE_* names that nothing defines; these are their
// values.
#define EFI_ISA_IA32 ((uint32_t)0x014c)
#define EFI_ISA_X64 ((uint32_t)0x8664)
#define EFI_ISA_IPF ((uint32_t)0x0200)
#define EFI_ISA_EBC ((uint32_t)0x0ebc)
#define EFI_ISA_ARM ((uint32_t)0x1c2)
#define EFI_ISA_AARCH64 ((uint32_t)0xaa64)
#define EFI_ISA_RISCV32 ((uint32_t)0x5032)
#define EFI_ISA_RISCV64 ((uint32_t)0x5064)
#define EFI_ISA_RISCV128 ((uint32_t)0x5128)
#define EFI_ISA_LOONGARCH32 ((uint32_t)0x6232)
#define EFI_ISA_LOONGARCH64 ((uint32_t)0x6264)

typedef efi_status (EFI_API *efi_get_maximum_processor_index)(
    struct efi_debug_support_protocol *self,
    size_t *max_processor_index
);

struct efi_system_context_ebc {
    uint64_t r0, r1, r2, r3, r4, r5, r6, r7;
    uint64_t flags;
    uint64_t control_flags;
    uint64_t ip;
};

struct efi_system_context_riscv32 {
    uint32_t zero, ra, sp, gp, tp, t0, t1, t2;
    uint32_t s0fp, s1, a0, a1, a2, a3, a4, a5, a6, a7;
    uint32_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    uint32_t t3, t4, t5, t6;

    efi_uint128 ft0, ft1, ft2, ft3, ft4, ft5, ft6, ft7;
    efi_uint128 fs0, fs1, fa0, fa1, fa2, fa3, fa4, fa5, fa6, fa7;
    efi_uint128 fs2, fs3, fs4, fs5, fs6, fs7, fs8, fs9, fs10, fs11;
    efi_uint128 ft8, ft9, ft10, ft11;
};

struct efi_system_context_riscv64 {
    uint64_t zero, ra, sp, gp, tp, t0, t1, t2;
    uint64_t s0fp, s1, a0, a1, a2, a3, a4, a5, a6, a7;
    uint64_t s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    uint64_t t3, t4, t5, t6;

    efi_uint128 ft0, ft1, ft2, ft3, ft4, ft5, ft6, ft7;
    efi_uint128 fs0, fs1, fa0, fa1, fa2, fa3, fa4, fa5, fa6, fa7;
    efi_uint128 fs2, fs3, fs4, fs5, fs6, fs7, fs8, fs9, fs10, fs11;
    efi_uint128 ft8, ft9, ft10, ft11;
};

struct efi_system_context_riscv128 {
    efi_uint128 zero, ra, sp, gp, tp, t0, t1, t2;
    efi_uint128 s0fp, s1, a0, a1, a2, a3, a4, a5, a6, a7;
    efi_uint128 s2, s3, s4, s5, s6, s7, s8, s9, s10, s11;
    efi_uint128 t3, t4, t5, t6;

    efi_uint128 ft0, ft1, ft2, ft3, ft4, ft5, ft6, ft7;
    efi_uint128 fs0, fs1, fa0, fa1, fa2, fa3, fa4, fa5, fa6, fa7;
    efi_uint128 fs2, fs3, fs4, fs5, fs6, fs7, fs8, fs9, fs10, fs11;
    efi_uint128 ft8, ft9, ft10, ft11;
};

struct efi_fx_save_state_ia32 {
    uint16_t fcw;
    uint16_t fsw;
    uint16_t ftw;
    uint16_t opcode;
    uint32_t eip;
    uint16_t cs;
    uint16_t reserved1;
    uint32_t data_offset;
    uint16_t ds;
    uint8_t reserved2[10];
    uint8_t st0_mm0[10], reserved3[6];
    uint8_t st1_mm1[10], reserved4[6];
    uint8_t st2_mm2[10], reserved5[6];
    uint8_t st3_mm3[10], reserved6[6];
    uint8_t st4_mm4[10], reserved7[6];
    uint8_t st5_mm5[10], reserved8[6];
    uint8_t st6_mm6[10], reserved9[6];
    uint8_t st7_mm7[10], reserved10[6];
    uint8_t xmm0[16];
    uint8_t xmm1[16];
    uint8_t xmm2[16];
    uint8_t xmm3[16];
    uint8_t xmm4[16];
    uint8_t xmm5[16];
    uint8_t xmm6[16];
    uint8_t xmm7[16];
    uint8_t reserved11[14 * 16];
};

struct efi_system_context_ia32 {
    uint32_t exception_data;
    struct efi_fx_save_state_ia32 fx_save_state;
    uint32_t dr0, dr1, dr2, dr3, dr6, dr7;
    uint32_t cr0, cr1, cr2, cr3, cr4;
    uint32_t eflags;
    uint32_t ldtr, tr;
    uint32_t gdtr[2], idtr[2];
    uint32_t eip;
    uint32_t gs, fs, es, ds, cs, ss;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
};

struct efi_fx_save_state_x64 {
    uint16_t fcw;
    uint16_t fsw;
    uint16_t ftw;
    uint16_t opcode;
    uint64_t rip;
    uint64_t data_offset;
    uint8_t reserved1[8];
    uint8_t st0_mm0[10], reserved2[6];
    uint8_t st1_mm1[10], reserved3[6];
    uint8_t st2_mm2[10], reserved4[6];
    uint8_t st3_mm3[10], reserved5[6];
    uint8_t st4_mm4[10], reserved6[6];
    uint8_t st5_mm5[10], reserved7[6];
    uint8_t st6_mm6[10], reserved8[6];
    uint8_t st7_mm7[10], reserved9[6];
    uint8_t xmm0[16];
    uint8_t xmm1[16];
    uint8_t xmm2[16];
    uint8_t xmm3[16];
    uint8_t xmm4[16];
    uint8_t xmm5[16];
    uint8_t xmm6[16];
    uint8_t xmm7[16];
    uint8_t reserved11[14 * 16];
};

struct efi_system_context_x64 {
    uint64_t exception_data;
    struct efi_fx_save_state_x64 fx_save_state;
    uint64_t dr0, dr1, dr2, dr3, dr6, dr7;
    uint64_t cr0, cr1, cr2, cr3, cr4, cr8;
    uint64_t rflags;
    uint64_t ldtr, tr;
    uint64_t gdtr[2], idtr[2];
    uint64_t rip;
    uint64_t gs, fs, es, ds, cs, ss;
    uint64_t rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;
    uint64_t r8, r9, r10, r11, r12, r13, r14, r15;
};

struct efi_system_context_ipf {
    uint64_t reserved;

    uint64_t r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19,
             r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;

    uint64_t f2[2], f3[2], f4[2], f5[2], f6[2], f7[2], f8[2], f9[2], f10[2], f11[2], f12[2],
             f13[2], f14[2], f15[2], f16[2], f17[2], f18[2], f19[2], f20[2], f21[2], f22[2],
             f23[2], f24[2], f25[2], f26[2], f27[2], f28[2], f29[2], f30[2], f31[2];

    uint64_t pr;

    uint64_t b0, b1, b2, b3, b4, b5, b6, b7;

    uint64_t ar_rsc, ar_bsp, ar_bspstore, ar_rnat;
    uint64_t ar_fcr;
    uint64_t ar_eflag, ar_csd, ar_ssd, ar_cflg;
    uint64_t ar_fsr, ar_fir, ar_fdr;
    uint64_t ar_ccv;
    uint64_t ar_unat;
    uint64_t ar_fpsr;
    uint64_t ar_pfs, ar_lc, ar_ec;

    uint64_t cr_dcr, cr_itm, cr_iva, cr_pta, cr_ipsr, cr_isr;
    uint64_t cr_iip, cr_ifa, cr_itir, cr_iipa, cr_ifs, cr_iim;
    uint64_t cr_iha;

    uint64_t dbr0, dbr1, dbr2, dbr3, dbr4, dbr5, dbr6, dbr7;
    uint64_t ibr0, ibr1, ibr2, ibr3, ibr4, ibr5, ibr6, ibr7;

    uint64_t int_nat;
};

// ifar, the instruction fault address paired with ifsr, is missing from the
// print.
struct efi_system_context_arm {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t cpsr;
    uint32_t dfsr;
    uint32_t dfar;
    uint32_t ifsr;
    uint32_t ifar;
};

struct efi_system_context_aarch64 {
    uint64_t x0;
    uint64_t x1;
    uint64_t x2;
    uint64_t x3;
    uint64_t x4;
    uint64_t x5;
    uint64_t x6;
    uint64_t x7;
    uint64_t x8;
    uint64_t x9;
    uint64_t x10;
    uint64_t x11;
    uint64_t x12;
    uint64_t x13;
    uint64_t x14;
    uint64_t x15;
    uint64_t x16;
    uint64_t x17;
    uint64_t x18;
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp;
    uint64_t lr;
    uint64_t sp;

    uint64_t v0[2];
    uint64_t v1[2];
    uint64_t v2[2];
    uint64_t v3[2];
    uint64_t v4[2];
    uint64_t v5[2];
    uint64_t v6[2];
    uint64_t v7[2];
    uint64_t v8[2];
    uint64_t v9[2];
    uint64_t v10[2];
    uint64_t v11[2];
    uint64_t v12[2];
    uint64_t v13[2];
    uint64_t v14[2];
    uint64_t v15[2];
    uint64_t v16[2];
    uint64_t v17[2];
    uint64_t v18[2];
    uint64_t v19[2];
    uint64_t v20[2];
    uint64_t v21[2];
    uint64_t v22[2];
    uint64_t v23[2];
    uint64_t v24[2];
    uint64_t v25[2];
    uint64_t v26[2];
    uint64_t v27[2];
    uint64_t v28[2];
    uint64_t v29[2];
    uint64_t v30[2];
    uint64_t v31[2];

    uint64_t elr;
    uint64_t spsr;
    uint64_t fpsr;
    uint64_t esr;
    uint64_t far;
};

struct efi_system_context_loongarch64 {
    uint64_t r0;
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t r6;
    uint64_t r7;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t r16;
    uint64_t r17;
    uint64_t r18;
    uint64_t r19;
    uint64_t r20;
    uint64_t r21;
    uint64_t r22;
    uint64_t r23;
    uint64_t r24;
    uint64_t r25;
    uint64_t r26;
    uint64_t r27;
    uint64_t r28;
    uint64_t r29;
    uint64_t r30;
    uint64_t r31;

    uint64_t crmd;
    uint64_t prmd;
    uint64_t euen;
    uint64_t misc;
    uint64_t ecfg;
    uint64_t estat;
    uint64_t era;
    uint64_t badv;
    uint64_t badi;
};

// system_context_loongarch64 is misprinted as system_context_long_arch64.
union efi_system_context {
    struct efi_system_context_ebc *system_context_ebc;
    struct efi_system_context_ia32 *system_context_ia32;
    struct efi_system_context_x64 *system_context_x64;
    struct efi_system_context_ipf *system_context_ipf;
    struct efi_system_context_arm *system_context_arm;
    struct efi_system_context_aarch64 *system_context_aarch64;
    struct efi_system_context_riscv32 *system_context_riscv32;
    struct efi_system_context_riscv64 *system_context_riscv64;
    struct efi_system_context_riscv128 *system_context_riscv128;
    struct efi_system_context_loongarch64 *system_context_loongarch64;
};

typedef void (EFI_API *efi_periodic_callback)(union efi_system_context system_context);

typedef efi_status (EFI_API *efi_register_periodic_callback)(
    struct efi_debug_support_protocol *self,
    size_t processor_index,
    efi_periodic_callback periodic_callback
);

typedef intptr_t efi_exception_type;

typedef void (EFI_API *efi_exception_callback)(
    efi_exception_type exception_type,
    union efi_system_context system_context
);

#define EFI_EXCEPT_EBC_UNDEFINED 0
#define EFI_EXCEPT_EBC_DIVIDE_ERROR 1
#define EFI_EXCEPT_EBC_DEBUG 2
#define EFI_EXCEPT_EBC_BREAKPOINT 3
#define EFI_EXCEPT_EBC_OVERFLOW 4
#define EFI_EXCEPT_EBC_INVALID_OPCODE 5
#define EFI_EXCEPT_EBC_STACK_FAULT 6
#define EFI_EXCEPT_EBC_ALIGNMENT_CHECK 7
#define EFI_EXCEPT_EBC_INSTRUCTION_ENCODING 8
#define EFI_EXCEPT_EBC_BAD_BREAK 9
#define EFI_EXCEPT_EBC_SINGLE_STEP 10

// Not in the specification: the highest EBC exception type, like
// EFI_MAX_ARM_EXCEPTION.
#define EFI_MAX_EBC_EXCEPTION EFI_EXCEPT_EBC_SINGLE_STEP

#define EFI_EXCEPT_IA32_DIVIDE_ERROR 0
#define EFI_EXCEPT_IA32_DEBUG 1
#define EFI_EXCEPT_IA32_NMI 2
#define EFI_EXCEPT_IA32_BREAKPOINT 3
#define EFI_EXCEPT_IA32_OVERFLOW 4
#define EFI_EXCEPT_IA32_BOUND 5
#define EFI_EXCEPT_IA32_INVALID_OPCODE 6
#define EFI_EXCEPT_IA32_DOUBLE_FAULT 8
#define EFI_EXCEPT_IA32_INVALID_TSS 10
#define EFI_EXCEPT_IA32_SEG_NOT_PRESENT 11
#define EFI_EXCEPT_IA32_STACK_FAULT 12
#define EFI_EXCEPT_IA32_GP_FAULT 13
#define EFI_EXCEPT_IA32_PAGE_FAULT 14
#define EFI_EXCEPT_IA32_FP_ERROR 16
#define EFI_EXCEPT_IA32_ALIGNMENT_CHECK 17
#define EFI_EXCEPT_IA32_MACHINE_CHECK 18
#define EFI_EXCEPT_IA32_SIMD 19

#define EFI_EXCEPT_X64_DIVIDE_ERROR 0
#define EFI_EXCEPT_X64_DEBUG 1
#define EFI_EXCEPT_X64_NMI 2
#define EFI_EXCEPT_X64_BREAKPOINT 3
#define EFI_EXCEPT_X64_OVERFLOW 4
#define EFI_EXCEPT_X64_BOUND 5
#define EFI_EXCEPT_X64_INVALID_OPCODE 6
#define EFI_EXCEPT_X64_DOUBLE_FAULT 8
#define EFI_EXCEPT_X64_INVALID_TSS 10
#define EFI_EXCEPT_X64_SEG_NOT_PRESENT 11
#define EFI_EXCEPT_X64_STACK_FAULT 12
#define EFI_EXCEPT_X64_GP_FAULT 13
#define EFI_EXCEPT_X64_PAGE_FAULT 14
#define EFI_EXCEPT_X64_FP_ERROR 16
#define EFI_EXCEPT_X64_ALIGNMENT_CHECK 17
#define EFI_EXCEPT_X64_MACHINE_CHECK 18
#define EFI_EXCEPT_X64_SIMD 19

#define EFI_EXCEPT_IPF_VHTP_TRANSLATION 0
#define EFI_EXCEPT_IPF_INSTRUCTION_TLB 1
#define EFI_EXCEPT_IPF_DATA_TLB 2
#define EFI_EXCEPT_IPF_ALT_INSTRUCTION_TLB 3
#define EFI_EXCEPT_IPF_ALT_DATA_TLB 4
#define EFI_EXCEPT_IPF_DATA_NESTED_TLB 5
#define EFI_EXCEPT_IPF_INSTRUCTION_KEY_MISSED 6
#define EFI_EXCEPT_IPF_DATA_KEY_MISSED 7
#define EFI_EXCEPT_IPF_DIRTY_BIT 8
#define EFI_EXCEPT_IPF_INSTRUCTION_ACCESS_BIT 9
#define EFI_EXCEPT_IPF_DATA_ACCESS_BIT 10
#define EFI_EXCEPT_IPF_BREAKPOINT 11
#define EFI_EXCEPT_IPF_EXTERNAL_INTERRUPT 12
#define EFI_EXCEPT_IPF_PAGE_NOT_PRESENT 20
#define EFI_EXCEPT_IPF_KEY_PERMISSION 21
#define EFI_EXCEPT_IPF_INSTRUCTION_ACCESS_RIGHTS 22
#define EFI_EXCEPT_IPF_DATA_ACCESS_RIGHTS 23
#define EFI_EXCEPT_IPF_GENERAL_EXCEPTION 24
#define EFI_EXCEPT_IPF_DISABLED_FP_REGISTER 25
#define EFI_EXCEPT_IPF_NAT_CONSUMPTION 26
#define EFI_EXCEPT_IPF_SPECULATION 27
#define EFI_EXCEPT_IPF_DEBUG 29
#define EFI_EXCEPT_IPF_UNALIGNED_REFERENCE 30
#define EFI_EXCEPT_IPF_UNSUPPORTED_DATA_REFERENCE 31
#define EFI_EXCEPT_IPF_FP_FAULT 32
#define EFI_EXCEPT_IPF_FP_TRAP 33
#define EFI_EXCEPT_IPF_LOWER_PRIVILEGE_TRANSFER_TRAP 34
#define EFI_EXCEPT_IPF_TAKEN_BRANCH 35
#define EFI_EXCEPT_IPF_SINGLE_STEP 36
#define EFI_EXCEPT_IPF_IA32_EXCEPTION 45
#define EFI_EXCEPT_IPF_IA32_INTERCEPT 46
#define EFI_EXCEPT_IPF_IA32_INTERRUPT 47

#define EFI_EXCEPT_ARM_RESET 0
#define EFI_EXCEPT_ARM_UNDEFINED_INSTRUCTION 1
#define EFI_EXCEPT_ARM_SOFTWARE_INTERRUPT 2
#define EFI_EXCEPT_ARM_PREFETCH_ABORT 3
#define EFI_EXCEPT_ARM_DATA_ABORT 4
#define EFI_EXCEPT_ARM_RESERVED 5
#define EFI_EXCEPT_ARM_IRQ 6
#define EFI_EXCEPT_ARM_FIQ 7

#define EFI_MAX_ARM_EXCEPTION EFI_EXCEPT_ARM_FIQ

#define EFI_EXCEPT_AARCH64_SYNCHRONOUS_EXCEPTIONS 0
#define EFI_EXCEPT_AARCH64_IRQ 1
#define EFI_EXCEPT_AARCH64_FIQ 2
#define EFI_EXCEPT_AARCH64_SERROR 3

#define EFI_MAX_AARCH64_EXCEPTION EFI_EXCEPT_AARCH64_SERROR

#define EFI_EXCEPT_RISCV_INST_MISALIGNED 0
#define EFI_EXCEPT_RISCV_INST_ACCESS_FAULT 1
#define EFI_EXCEPT_RISCV_ILLEGAL_INST 2
#define EFI_EXCEPT_RISCV_BREAKPOINT 3
#define EFI_EXCEPT_RISCV_LOAD_ADDRESS_MISALIGNED 4
#define EFI_EXCEPT_RISCV_LOAD_ACCESS_FAULT 5
#define EFI_EXCEPT_RISCV_STORE_AMO_ADDRESS_MISALIGNED 6
#define EFI_EXCEPT_RISCV_STORE_AMO_ACCESS_FAULT 7
#define EFI_EXCEPT_RISCV_ENV_CALL_FROM_UMODE 8
#define EFI_EXCEPT_RISCV_ENV_CALL_FROM_SMODE 9
#define EFI_EXCEPT_RISCV_ENV_CALL_FROM_MMODE 11
#define EFI_EXCEPT_RISCV_INST_PAGE_FAULT 12
#define EFI_EXCEPT_RISCV_LOAD_PAGE_FAULT 13
#define EFI_EXCEPT_RISCV_STORE_AMO_PAGE_FAULT 15

#define EFI_EXCEPT_RISCV_SUPERVISOR_SOFTWARE_INT 1
#define EFI_EXCEPT_RISCV_MACHINE_SOFTWARE_INT 3
#define EFI_EXCEPT_RISCV_SUPERVISOR_TIMER_INT 5
#define EFI_EXCEPT_RISCV_MACHINE_TIMER_INT 7
#define EFI_EXCEPT_RISCV_SUPERVISOR_EXTERNAL_INT 9
#define EFI_EXCEPT_RISCV_MACHINE_EXTERNAL_INT 11

#define EFI_EXCEPT_LOONGARCH_INT 0
#define EFI_EXCEPT_LOONGARCH_PIL 1
#define EFI_EXCEPT_LOONGARCH_PIS 2
#define EFI_EXCEPT_LOONGARCH_PIF 3
#define EFI_EXCEPT_LOONGARCH_PME 4
#define EFI_EXCEPT_LOONGARCH_PNR 5
#define EFI_EXCEPT_LOONGARCH_PNX 6
#define EFI_EXCEPT_LOONGARCH_PPI 7
#define EFI_EXCEPT_LOONGARCH_ADE 8
#define EFI_EXCEPT_LOONGARCH_ALE 9
#define EFI_EXCEPT_LOONGARCH_BCE 10
#define EFI_EXCEPT_LOONGARCH_SYS 11
#define EFI_EXCEPT_LOONGARCH_BRK 12
#define EFI_EXCEPT_LOONGARCH_INE 13
#define EFI_EXCEPT_LOONGARCH_IPE 14
#define EFI_EXCEPT_LOONGARCH_FPD 15
#define EFI_EXCEPT_LOONGARCH_SXD 16
#define EFI_EXCEPT_LOONGARCH_ASXD 17
#define EFI_EXCEPT_LOONGARCH_FPE 18
#define EFI_EXCEPT_LOONGARCH_WPE 19
#define EFI_EXCEPT_LOONGARCH_BTD 20
#define EFI_EXCEPT_LOONGARCH_BTE 21
#define EFI_EXCEPT_LOONGARCH_GSPR 22
#define EFI_EXCEPT_LOONGARCH_HVC 23
#define EFI_EXCEPT_LOONGARCH_GCXC 24

#define EFI_MAX_LOONGARCH_EXCEPTION 64

#define EFI_EXCEPT_LOONGARCH_INT_SIP0 0
#define EFI_EXCEPT_LOONGARCH_INT_SIP1 1
#define EFI_EXCEPT_LOONGARCH_INT_IP0 2
#define EFI_EXCEPT_LOONGARCH_INT_IP1 3
#define EFI_EXCEPT_LOONGARCH_INT_IP2 4
#define EFI_EXCEPT_LOONGARCH_INT_IP3 5
#define EFI_EXCEPT_LOONGARCH_INT_IP4 6
#define EFI_EXCEPT_LOONGARCH_INT_IP5 7
#define EFI_EXCEPT_LOONGARCH_INT_IP6 8
#define EFI_EXCEPT_LOONGARCH_INT_IP7 9
#define EFI_EXCEPT_LOONGARCH_INT_PMC 10
#define EFI_EXCEPT_LOONGARCH_INT_TIMER 11
#define EFI_EXCEPT_LOONGARCH_INT_IPI 12

#define EFI_MAX_LOONGARCH_INTERRUPT 16

// Printed as REGISTER_EXCEPTION_CALLBACK; the protocol structure uses this
// name.
typedef efi_status (EFI_API *efi_register_exception_callback)(
    struct efi_debug_support_protocol *self,
    size_t processor_index,
    efi_exception_callback exception_callback,
    efi_exception_type exception_type
);

typedef efi_status (EFI_API *efi_invalidate_instruction_cache)(
    struct efi_debug_support_protocol *self,
    size_t processor_index,
    void *start,
    uint64_t length
);

struct efi_debug_support_protocol {
    uint32_t isa;
    efi_get_maximum_processor_index get_maximum_processor_index;
    efi_register_periodic_callback register_periodic_callback;
    efi_register_exception_callback register_exception_callback;
    efi_invalidate_instruction_cache invalidate_instruction_cache;
};

#define EFI_DEBUGPORT_PROTOCOL_GUID \
    { 0xeba4e8d2, 0x3858, 0x41ec, { 0xa2, 0x81, 0x26, 0x47, 0xba, 0x96, 0x60, 0xd0 } }

struct efi_debugport_protocol;

typedef efi_status (EFI_API *efi_debugport_reset)(struct efi_debugport_protocol *self);

typedef efi_status (EFI_API *efi_debugport_write)(
    struct efi_debugport_protocol *self,
    uint32_t timeout,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_debugport_read)(
    struct efi_debugport_protocol *self,
    uint32_t timeout,
    size_t *buffer_size,
    void *buffer
);

typedef efi_status (EFI_API *efi_debugport_poll)(struct efi_debugport_protocol *self);

struct efi_debugport_protocol {
    efi_debugport_reset reset;
    efi_debugport_write write;
    efi_debugport_read read;
    efi_debugport_poll poll;
};

#define EFI_DEVICE_PATH_MESSAGING_DEBUGPORT EFI_DEBUGPORT_PROTOCOL_GUID

#define EFI_DEBUGPORT_VARIABLE_NAME L"DEBUGPORT"
#define EFI_DEBUGPORT_VARIABLE_GUID EFI_DEBUGPORT_PROTOCOL_GUID

struct efi_system_table_pointer {
    uint64_t signature;
    efi_physical_address efi_system_table_base;
    uint32_t crc32;
};

#define EFI_DEBUG_IMAGE_INFO_TABLE_GUID \
    { 0x49152e77, 0x1ada, 0x4764, { 0xb7, 0xa2, 0x7a, 0xfe, 0xfe, 0xd9, 0x5e, 0x8b } }

#define EFI_DEBUG_IMAGE_INFO_UPDATE_IN_PROGRESS 0x01
#define EFI_DEBUG_IMAGE_INFO_TABLE_MODIFIED 0x02

#define EFI_DEBUG_IMAGE_INFO_TYPE_NORMAL 0x01

struct efi_debug_image_info_normal {
    uint32_t image_info_type;
    struct efi_loaded_image_protocol *loaded_image_protocol_instance;
    efi_handle image_handle;
};

union efi_debug_image_info {
    uint32_t *image_info_type;
    struct efi_debug_image_info_normal *normal_image;
};

// Not in the specification: how many union efi_debug_image_info,
// pointer-sized, fill a page.
#define EFI_DEBUG_IMAGE_INFO_INITIAL_SIZE (EFI_PAGE_SIZE / sizeof(size_t))

struct efi_debug_image_info_table_header {
    volatile uint32_t update_status;
    uint32_t table_size;
    union efi_debug_image_info *efi_debug_image_info_table;
};

#ifdef __cplusplus
}
#endif

#endif
