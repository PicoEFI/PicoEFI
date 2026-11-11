#ifndef EFI_EFIDEBUG_H_
#define EFI_EFIDEBUG_H_

#include "efiprot.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EFI_DEBUG_SUPPORT_PROTOCOL_GUID \
    {0x2755590C, 0x6F3C, 0x42FA, {0x9E, 0xA4, 0xA3, 0xBA, 0x54, 0x3C, 0xDA, 0x25}}

struct efi_debug_support_protocol;

/* Printed as IMAGE_FILE_MACHINE_* names that nothing defines; these are their values. */
#define EFI_ISA_IA32 ((uint32_t)0x014C)
#define EFI_ISA_X64 ((uint32_t)0x8664)
#define EFI_ISA_IPF ((uint32_t)0x0200)
#define EFI_ISA_EBC ((uint32_t)0x0EBC)
#define EFI_ISA_ARM ((uint32_t)0x1C2)
#define EFI_ISA_AARCH64 ((uint32_t)0xAA64)
#define EFI_ISA_RISCV32 ((uint32_t)0x5032)
#define EFI_ISA_RISCV64 ((uint32_t)0x5064)
#define EFI_ISA_RISCV128 ((uint32_t)0x5128)
#define EFI_ISA_LOONGARCH32 ((uint32_t)0x6232)
#define EFI_ISA_LOONGARCH64 ((uint32_t)0x6264)

typedef EFI_STATUS (EFI_API *EFI_GET_MAXIMUM_PROCESSOR_INDEX)(
    struct efi_debug_support_protocol *This,
    size_t *MaxProcessorIndex
);

struct efi_system_context_ebc {
    uint64_t R0, R1, R2, R3, R4, R5, R6, R7;
    uint64_t Flags;
    uint64_t ControlFlags;
    uint64_t Ip;
};

struct efi_system_context_riscv32 {
    uint32_t Zero, Ra, Sp, Gp, Tp, T0, T1, T2;
    uint32_t S0FP, S1, A0, A1, A2, A3, A4, A5, A6, A7;
    uint32_t S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
    uint32_t T3, T4, T5, T6;

    EFI_UINT128 Ft0, Ft1, Ft2, Ft3, Ft4, Ft5, Ft6, Ft7;
    EFI_UINT128 Fs0, Fs1, Fa0, Fa1, Fa2, Fa3, Fa4, Fa5, Fa6, Fa7;
    EFI_UINT128 Fs2, Fs3, Fs4, Fs5, Fs6, Fs7, Fs8, Fs9, Fs10, Fs11;
    EFI_UINT128 Ft8, Ft9, Ft10, Ft11;
};

struct efi_system_context_riscv64 {
    uint64_t Zero, Ra, Sp, Gp, Tp, T0, T1, T2;
    uint64_t S0FP, S1, A0, A1, A2, A3, A4, A5, A6, A7;
    uint64_t S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
    uint64_t T3, T4, T5, T6;

    EFI_UINT128 Ft0, Ft1, Ft2, Ft3, Ft4, Ft5, Ft6, Ft7;
    EFI_UINT128 Fs0, Fs1, Fa0, Fa1, Fa2, Fa3, Fa4, Fa5, Fa6, Fa7;
    EFI_UINT128 Fs2, Fs3, Fs4, Fs5, Fs6, Fs7, Fs8, Fs9, Fs10, Fs11;
    EFI_UINT128 Ft8, Ft9, Ft10, Ft11;
};

struct efi_system_context_riscv128 {
    EFI_UINT128 Zero, Ra, Sp, Gp, Tp, T0, T1, T2;
    EFI_UINT128 S0FP, S1, A0, A1, A2, A3, A4, A5, A6, A7;
    EFI_UINT128 S2, S3, S4, S5, S6, S7, S8, S9, S10, S11;
    EFI_UINT128 T3, T4, T5, T6;

    EFI_UINT128 Ft0, Ft1, Ft2, Ft3, Ft4, Ft5, Ft6, Ft7;
    EFI_UINT128 Fs0, Fs1, Fa0, Fa1, Fa2, Fa3, Fa4, Fa5, Fa6, Fa7;
    EFI_UINT128 Fs2, Fs3, Fs4, Fs5, Fs6, Fs7, Fs8, Fs9, Fs10, Fs11;
    EFI_UINT128 Ft8, Ft9, Ft10, Ft11;
};

struct efi_fx_save_state_ia32 {
    uint16_t Fcw;
    uint16_t Fsw;
    uint16_t Ftw;
    uint16_t Opcode;
    uint32_t Eip;
    uint16_t Cs;
    uint16_t Reserved1;
    uint32_t DataOffset;
    uint16_t Ds;
    uint8_t Reserved2[10];
    uint8_t St0Mm0[10], Reserved3[6];
    uint8_t St1Mm1[10], Reserved4[6];
    uint8_t St2Mm2[10], Reserved5[6];
    uint8_t St3Mm3[10], Reserved6[6];
    uint8_t St4Mm4[10], Reserved7[6];
    uint8_t St5Mm5[10], Reserved8[6];
    uint8_t St6Mm6[10], Reserved9[6];
    uint8_t St7Mm7[10], Reserved10[6];
    uint8_t Xmm0[16];
    uint8_t Xmm1[16];
    uint8_t Xmm2[16];
    uint8_t Xmm3[16];
    uint8_t Xmm4[16];
    uint8_t Xmm5[16];
    uint8_t Xmm6[16];
    uint8_t Xmm7[16];
    uint8_t Reserved11[14 * 16];
};

struct efi_system_context_ia32 {
    uint32_t ExceptionData;
    struct efi_fx_save_state_ia32 FxSaveState;
    uint32_t Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    uint32_t Cr0, Cr1, Cr2, Cr3, Cr4;
    uint32_t Eflags;
    uint32_t Ldtr, Tr;
    uint32_t Gdtr[2], Idtr[2];
    uint32_t Eip;
    uint32_t Gs, Fs, Es, Ds, Cs, Ss;
    uint32_t Edi, Esi, Ebp, Esp, Ebx, Edx, Ecx, Eax;
};

struct efi_fx_save_state_x64 {
    uint16_t Fcw;
    uint16_t Fsw;
    uint16_t Ftw;
    uint16_t Opcode;
    uint64_t Rip;
    uint64_t DataOffset;
    uint8_t Reserved1[8];
    uint8_t St0Mm0[10], Reserved2[6];
    uint8_t St1Mm1[10], Reserved3[6];
    uint8_t St2Mm2[10], Reserved4[6];
    uint8_t St3Mm3[10], Reserved5[6];
    uint8_t St4Mm4[10], Reserved6[6];
    uint8_t St5Mm5[10], Reserved7[6];
    uint8_t St6Mm6[10], Reserved8[6];
    uint8_t St7Mm7[10], Reserved9[6];
    uint8_t Xmm0[16];
    uint8_t Xmm1[16];
    uint8_t Xmm2[16];
    uint8_t Xmm3[16];
    uint8_t Xmm4[16];
    uint8_t Xmm5[16];
    uint8_t Xmm6[16];
    uint8_t Xmm7[16];
    uint8_t Reserved11[14 * 16];
};

struct efi_system_context_x64 {
    uint64_t ExceptionData;
    struct efi_fx_save_state_x64 FxSaveState;
    uint64_t Dr0, Dr1, Dr2, Dr3, Dr6, Dr7;
    uint64_t Cr0, Cr1, Cr2, Cr3, Cr4, Cr8;
    uint64_t Rflags;
    uint64_t Ldtr, Tr;
    uint64_t Gdtr[2], Idtr[2];
    uint64_t Rip;
    uint64_t Gs, Fs, Es, Ds, Cs, Ss;
    uint64_t Rdi, Rsi, Rbp, Rsp, Rbx, Rdx, Rcx, Rax;
    uint64_t R8, R9, R10, R11, R12, R13, R14, R15;
};

struct efi_system_context_ipf {
    uint64_t Reserved;

    uint64_t R1, R2, R3, R4, R5, R6, R7, R8, R9, R10,
        R11, R12, R13, R14, R15, R16, R17, R18, R19, R20,
        R21, R22, R23, R24, R25, R26, R27, R28, R29, R30,
        R31;

    uint64_t F2[2], F3[2], F4[2], F5[2], F6[2],
        F7[2], F8[2], F9[2], F10[2], F11[2],
        F12[2], F13[2], F14[2], F15[2], F16[2],
        F17[2], F18[2], F19[2], F20[2], F21[2],
        F22[2], F23[2], F24[2], F25[2], F26[2],
        F27[2], F28[2], F29[2], F30[2], F31[2];

    uint64_t Pr;

    uint64_t B0, B1, B2, B3, B4, B5, B6, B7;

    uint64_t ArRsc, ArBsp, ArBspstore, ArRnat;
    uint64_t ArFcr;
    uint64_t ArEflag, ArCsd, ArSsd, ArCflg;
    uint64_t ArFsr, ArFir, ArFdr;
    uint64_t ArCcv;
    uint64_t ArUnat;
    uint64_t ArFpsr;
    uint64_t ArPfs, ArLc, ArEc;

    uint64_t CrDcr, CrItm, CrIva, CrPta, CrIpsr, CrIsr;
    uint64_t CrIip, CrIfa, CrItir, CrIipa, CrIfs, CrIim;
    uint64_t CrIha;

    uint64_t Dbr0, Dbr1, Dbr2, Dbr3, Dbr4, Dbr5, Dbr6, Dbr7;
    uint64_t Ibr0, Ibr1, Ibr2, Ibr3, Ibr4, Ibr5, Ibr6, Ibr7;

    uint64_t IntNat;
};

/* IFAR, the instruction fault address paired with IFSR, is missing from the print. */
struct efi_system_context_arm {
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;
    uint32_t R12;
    uint32_t SP;
    uint32_t LR;
    uint32_t PC;
    uint32_t CPSR;
    uint32_t DFSR;
    uint32_t DFAR;
    uint32_t IFSR;
    uint32_t IFAR;
};

struct efi_system_context_aarch64 {
    uint64_t X0;
    uint64_t X1;
    uint64_t X2;
    uint64_t X3;
    uint64_t X4;
    uint64_t X5;
    uint64_t X6;
    uint64_t X7;
    uint64_t X8;
    uint64_t X9;
    uint64_t X10;
    uint64_t X11;
    uint64_t X12;
    uint64_t X13;
    uint64_t X14;
    uint64_t X15;
    uint64_t X16;
    uint64_t X17;
    uint64_t X18;
    uint64_t X19;
    uint64_t X20;
    uint64_t X21;
    uint64_t X22;
    uint64_t X23;
    uint64_t X24;
    uint64_t X25;
    uint64_t X26;
    uint64_t X27;
    uint64_t X28;
    uint64_t FP;
    uint64_t LR;
    uint64_t SP;

    uint64_t V0[2];
    uint64_t V1[2];
    uint64_t V2[2];
    uint64_t V3[2];
    uint64_t V4[2];
    uint64_t V5[2];
    uint64_t V6[2];
    uint64_t V7[2];
    uint64_t V8[2];
    uint64_t V9[2];
    uint64_t V10[2];
    uint64_t V11[2];
    uint64_t V12[2];
    uint64_t V13[2];
    uint64_t V14[2];
    uint64_t V15[2];
    uint64_t V16[2];
    uint64_t V17[2];
    uint64_t V18[2];
    uint64_t V19[2];
    uint64_t V20[2];
    uint64_t V21[2];
    uint64_t V22[2];
    uint64_t V23[2];
    uint64_t V24[2];
    uint64_t V25[2];
    uint64_t V26[2];
    uint64_t V27[2];
    uint64_t V28[2];
    uint64_t V29[2];
    uint64_t V30[2];
    uint64_t V31[2];

    uint64_t ELR;
    uint64_t SPSR;
    uint64_t FPSR;
    uint64_t ESR;
    uint64_t FAR;
};

struct efi_system_context_loongarch64 {
    uint64_t R0;
    uint64_t R1;
    uint64_t R2;
    uint64_t R3;
    uint64_t R4;
    uint64_t R5;
    uint64_t R6;
    uint64_t R7;
    uint64_t R8;
    uint64_t R9;
    uint64_t R10;
    uint64_t R11;
    uint64_t R12;
    uint64_t R13;
    uint64_t R14;
    uint64_t R15;
    uint64_t R16;
    uint64_t R17;
    uint64_t R18;
    uint64_t R19;
    uint64_t R20;
    uint64_t R21;
    uint64_t R22;
    uint64_t R23;
    uint64_t R24;
    uint64_t R25;
    uint64_t R26;
    uint64_t R27;
    uint64_t R28;
    uint64_t R29;
    uint64_t R30;
    uint64_t R31;

    uint64_t CRMD;
    uint64_t PRMD;
    uint64_t EUEN;
    uint64_t MISC;
    uint64_t ECFG;
    uint64_t ESTAT;
    uint64_t ERA;
    uint64_t BADV;
    uint64_t BADI;
};

/* SystemContextRiscV128 and SystemContextLoongArch64 are misprinted Riscv128 and LongArch64. */
union efi_system_context {
    struct efi_system_context_ebc *SystemContextEbc;
    struct efi_system_context_ia32 *SystemContextIa32;
    struct efi_system_context_x64 *SystemContextX64;
    struct efi_system_context_ipf *SystemContextIpf;
    struct efi_system_context_arm *SystemContextArm;
    struct efi_system_context_aarch64 *SystemContextAArch64;
    struct efi_system_context_riscv32 *SystemContextRiscV32;
    struct efi_system_context_riscv64 *SystemContextRiscV64;
    struct efi_system_context_riscv128 *SystemContextRiscV128;
    struct efi_system_context_loongarch64 *SystemContextLoongArch64;
};

typedef void (EFI_API *EFI_PERIODIC_CALLBACK)(union efi_system_context SystemContext);

typedef EFI_STATUS (EFI_API *EFI_REGISTER_PERIODIC_CALLBACK)(
    struct efi_debug_support_protocol *This,
    size_t ProcessorIndex,
    EFI_PERIODIC_CALLBACK PeriodicCallback
);

typedef intptr_t EFI_EXCEPTION_TYPE;

typedef void (EFI_API *EFI_EXCEPTION_CALLBACK)(
    EFI_EXCEPTION_TYPE ExceptionType,
    union efi_system_context SystemContext
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

/* Not in the specification: the highest EBC exception type, like EFI_MAX_ARM_EXCEPTION. */
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

/* Printed as REGISTER_EXCEPTION_CALLBACK; the protocol structure uses this name. */
typedef EFI_STATUS (EFI_API *EFI_REGISTER_EXCEPTION_CALLBACK)(
    struct efi_debug_support_protocol *This,
    size_t ProcessorIndex,
    EFI_EXCEPTION_CALLBACK ExceptionCallback,
    EFI_EXCEPTION_TYPE ExceptionType
);

typedef EFI_STATUS (EFI_API *EFI_INVALIDATE_INSTRUCTION_CACHE)(
    struct efi_debug_support_protocol *This,
    size_t ProcessorIndex,
    void *Start,
    uint64_t Length
);

struct efi_debug_support_protocol {
    uint32_t Isa;
    EFI_GET_MAXIMUM_PROCESSOR_INDEX GetMaximumProcessorIndex;
    EFI_REGISTER_PERIODIC_CALLBACK RegisterPeriodicCallback;
    EFI_REGISTER_EXCEPTION_CALLBACK RegisterExceptionCallback;
    EFI_INVALIDATE_INSTRUCTION_CACHE InvalidateInstructionCache;
};

#define EFI_DEBUGPORT_PROTOCOL_GUID \
    {0xEBA4E8D2, 0x3858, 0x41EC, {0xA2, 0x81, 0x26, 0x47, 0xBA, 0x96, 0x60, 0xD0}}

struct efi_debugport_protocol;

typedef EFI_STATUS (EFI_API *EFI_DEBUGPORT_RESET)(struct efi_debugport_protocol *This);

typedef EFI_STATUS (EFI_API *EFI_DEBUGPORT_WRITE)(
    struct efi_debugport_protocol *This,
    uint32_t Timeout,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_DEBUGPORT_READ)(
    struct efi_debugport_protocol *This,
    uint32_t Timeout,
    size_t *BufferSize,
    void *Buffer
);

typedef EFI_STATUS (EFI_API *EFI_DEBUGPORT_POLL)(struct efi_debugport_protocol *This);

struct efi_debugport_protocol {
    EFI_DEBUGPORT_RESET Reset;
    EFI_DEBUGPORT_WRITE Write;
    EFI_DEBUGPORT_READ Read;
    EFI_DEBUGPORT_POLL Poll;
};

#define EFI_DEVICE_PATH_MESSAGING_DEBUGPORT EFI_DEBUGPORT_PROTOCOL_GUID

#define EFI_DEBUGPORT_VARIABLE_NAME L"DEBUGPORT"
#define EFI_DEBUGPORT_VARIABLE_GUID EFI_DEBUGPORT_PROTOCOL_GUID

struct efi_system_table_pointer {
    uint64_t Signature;
    EFI_PHYSICAL_ADDRESS EfiSystemTableBase;
    uint32_t Crc32;
};

#define EFI_DEBUG_IMAGE_INFO_TABLE_GUID \
    {0x49152E77, 0x1ADA, 0x4764, {0xB7, 0xA2, 0x7A, 0xFE, 0xFE, 0xD9, 0x5E, 0x8B}}

#define EFI_DEBUG_IMAGE_INFO_UPDATE_IN_PROGRESS 0x01
#define EFI_DEBUG_IMAGE_INFO_TABLE_MODIFIED 0x02

#define EFI_DEBUG_IMAGE_INFO_TYPE_NORMAL 0x01

struct efi_debug_image_info_normal {
    uint32_t ImageInfoType;
    struct efi_loaded_image_protocol *LoadedImageProtocolInstance;
    EFI_HANDLE ImageHandle;
};

union efi_debug_image_info {
    uint32_t *ImageInfoType;
    struct efi_debug_image_info_normal *NormalImage;
};

/* Not in the specification: how many union efi_debug_image_info, pointer-sized, fill a page. */
#define EFI_DEBUG_IMAGE_INFO_INITIAL_SIZE (EFI_PAGE_SIZE / sizeof(uintptr_t))

struct efi_debug_image_info_table_header {
    volatile uint32_t UpdateStatus;
    uint32_t TableSize;
    union efi_debug_image_info *EfiDebugImageInfoTable;
};

#ifdef __cplusplus
}
#endif

#endif
