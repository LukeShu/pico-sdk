// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/**
 * Copyright (c) 2024 Raspberry Pi Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _HARDWARE_STRUCTS_SCB_H
#define _HARDWARE_STRUCTS_SCB_H

/**
 * \file rp2350/scb.h
 */

#include "hardware/address_mapped.h"
#include "hardware/regs/m33.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf#tab-registerlist_m33
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/m33.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE] FIELDNAME (RESETVALUE) DESCRIPTION

#if defined(__riscv) && PICO_FORBID_ARM_HEADERS_ON_RISCV
#error "Arm header included in a RISC-V build with PICO_FORBID_ARM_HEADERS_ON_RISCV=1"
#endif

typedef struct {
    _REG_(M33_CPUID_OFFSET) // M33_CPUID
    // Provides identification information for the PE, including an implementer code for the device and...
    // 0xff000000 [31:24] IMPLEMENTER  (0x41) This field must hold an implementer code that has been...
    // 0x00f00000 [23:20] VARIANT      (0x1) IMPLEMENTATION DEFINED variant number
    // 0x000f0000 [19:16] ARCHITECTURE (0xf) Defines the Architecture implemented by the PE
    // 0x0000fff0 [15:4]  PARTNO       (0xd21) IMPLEMENTATION DEFINED primary part number for the device
    // 0x0000000f [3:0]   REVISION     (0x0) IMPLEMENTATION DEFINED revision number for the device
    io_ro_32 cpuid;

    _REG_(M33_ICSR_OFFSET) // M33_ICSR
    // Controls and provides status information for NMI, PendSV, SysTick and interrupts
    // 0x80000000 [31]    PENDNMISET   (0) Indicates whether the NMI exception is pending
    // 0x40000000 [30]    PENDNMICLR   (0) Allows the NMI exception pend state to be cleared
    // 0x10000000 [28]    PENDSVSET    (0) Indicates whether the PendSV `FTSSS exception is pending
    // 0x08000000 [27]    PENDSVCLR    (0) Allows the PendSV exception pend state to be cleared `FTSSS
    // 0x04000000 [26]    PENDSTSET    (0) Indicates whether the SysTick `FTSSS exception is pending
    // 0x02000000 [25]    PENDSTCLR    (0) Allows the SysTick exception pend state to be cleared `FTSSS
    // 0x01000000 [24]    STTNS        (0) Controls whether in a single SysTick implementation, the...
    // 0x00800000 [23]    ISRPREEMPT   (0) Indicates whether a pending exception will be serviced...
    // 0x00400000 [22]    ISRPENDING   (0) Indicates whether an external interrupt, generated by...
    // 0x001ff000 [20:12] VECTPENDING  (0x000) The exception number of the highest priority pending and...
    // 0x00000800 [11]    RETTOBASE    (0) In Handler mode, indicates whether there is more than...
    // 0x000001ff [8:0]   VECTACTIVE   (0x000) The exception number of the current executing exception
    io_rw_32 icsr;

    _REG_(M33_VTOR_OFFSET) // M33_VTOR
    // Vector Table Offset Register
    // 0xffffff80 [31:7]  TBLOFF       (0x0000000) Vector table base offset field
    io_rw_32 vtor;

    _REG_(M33_AIRCR_OFFSET) // M33_AIRCR
    // Application Interrupt and Reset Control Register
    // 0xffff0000 [31:16] VECTKEY      (0x0000) Register key: +
    // 0x00008000 [15]    ENDIANESS    (0) Data endianness implemented: +
    // 0x00004000 [14]    PRIS         (0) Prioritize Secure exceptions
    // 0x00002000 [13]    BFHFNMINS    (0) BusFault, HardFault, and NMI Non-secure enable
    // 0x00000700 [10:8]  PRIGROUP     (0x0) Interrupt priority grouping field
    // 0x00000008 [3]     SYSRESETREQS (0) System reset request, Secure state only
    // 0x00000004 [2]     SYSRESETREQ  (0) Writing 1 to this bit causes the SYSRESETREQ signal to...
    // 0x00000002 [1]     VECTCLRACTIVE (0) Clears all active state information for fixed and...
    io_rw_32 aircr;

    _REG_(M33_SCR_OFFSET) // M33_SCR
    // System Control Register
    // 0x00000010 [4]     SEVONPEND    (0) Send Event on Pending bit: +
    // 0x00000008 [3]     SLEEPDEEPS   (0) 0 SLEEPDEEP is available to both security states +
    // 0x00000004 [2]     SLEEPDEEP    (0) Controls whether the processor uses sleep or deep sleep...
    // 0x00000002 [1]     SLEEPONEXIT  (0) Indicates sleep-on-exit when returning from Handler mode...
    io_rw_32 scr;

    _REG_(M33_CCR_OFFSET) // M33_CCR
    // Sets or returns configuration and control data
    // 0x00040000 [18]    BP           (0) Enables program flow prediction `FTSSS
    // 0x00020000 [17]    IC           (0) This is a global enable bit for instruction caches in...
    // 0x00010000 [16]    DC           (0) Enables data caching of all data accesses to Normal memory `FTSSS
    // 0x00000400 [10]    STKOFHFNMIGN (0) Controls the effect of a stack limit violation while...
    // 0x00000200 [9]     RES1         (1) Reserved, RES1
    // 0x00000100 [8]     BFHFNMIGN    (0) Determines the effect of precise BusFaults on handlers...
    // 0x00000010 [4]     DIV_0_TRP    (0) Controls the generation of a DIVBYZERO UsageFault when...
    // 0x00000008 [3]     UNALIGN_TRP  (0) Controls the trapping of unaligned word or halfword accesses
    // 0x00000002 [1]     USERSETMPEND (0) Determines whether unprivileged accesses are permitted...
    // 0x00000001 [0]     RES1_1       (1) Reserved, RES1
    io_rw_32 ccr;

    // (Description copied from array index 0 register M33_SHPR1 applies similarly to other array indexes)
    _REG_(M33_SHPR1_OFFSET) // M33_SHPR1
    // Sets or returns priority for system handlers 4 - 7
    // 0xe0000000 [31:29] PRI_7_3      (0x0) Priority of system handler 7, SecureFault
    // 0x00e00000 [23:21] PRI_6_3      (0x0) Priority of system handler 6, SecureFault
    // 0x0000e000 [15:13] PRI_5_3      (0x0) Priority of system handler 5, SecureFault
    // 0x000000e0 [7:5]   PRI_4_3      (0x0) Priority of system handler 4, SecureFault
    io_rw_32 shpr[3];

    _REG_(M33_SHCSR_OFFSET) // M33_SHCSR
    // Provides access to the active and pending status of system exceptions
    // 0x00200000 [21]    HARDFAULTPENDED (0) `IAAMO the pending state of the HardFault exception `CTTSSS
    // 0x00100000 [20]    SECUREFAULTPENDED (0) `IAAMO the pending state of the SecureFault exception
    // 0x00080000 [19]    SECUREFAULTENA (0) `DW the SecureFault exception is enabled
    // 0x00040000 [18]    USGFAULTENA  (0) `DW the UsageFault exception is enabled `FTSSS
    // 0x00020000 [17]    BUSFAULTENA  (0) `DW the BusFault exception is enabled
    // 0x00010000 [16]    MEMFAULTENA  (0) `DW the MemManage exception is enabled `FTSSS
    // 0x00008000 [15]    SVCALLPENDED (0) `IAAMO the pending state of the SVCall exception `FTSSS
    // 0x00004000 [14]    BUSFAULTPENDED (0) `IAAMO the pending state of the BusFault exception
    // 0x00002000 [13]    MEMFAULTPENDED (0) `IAAMO the pending state of the MemManage exception `FTSSS
    // 0x00001000 [12]    USGFAULTPENDED (0) The UsageFault exception is banked between Security...
    // 0x00000800 [11]    SYSTICKACT   (0) `IAAMO the active state of the SysTick exception `FTSSS
    // 0x00000400 [10]    PENDSVACT    (0) `IAAMO the active state of the PendSV exception `FTSSS
    // 0x00000100 [8]     MONITORACT   (0) `IAAMO the active state of the DebugMonitor exception
    // 0x00000080 [7]     SVCALLACT    (0) `IAAMO the active state of the SVCall exception `FTSSS
    // 0x00000020 [5]     NMIACT       (0) `IAAMO the active state of the NMI exception
    // 0x00000010 [4]     SECUREFAULTACT (0) `IAAMO the active state of the SecureFault exception
    // 0x00000008 [3]     USGFAULTACT  (0) `IAAMO the active state of the UsageFault exception `FTSSS
    // 0x00000004 [2]     HARDFAULTACT (0) Indicates and allows limited modification of the active...
    // 0x00000002 [1]     BUSFAULTACT  (0) `IAAMO the active state of the BusFault exception
    // 0x00000001 [0]     MEMFAULTACT  (0) `IAAMO the active state of the MemManage exception `FTSSS
    io_rw_32 shcsr;

    _REG_(M33_CFSR_OFFSET) // M33_CFSR
    // Contains the three Configurable Fault Status Registers
    // 0x02000000 [25]    UFSR_DIVBYZERO (0) Sticky flag indicating whether an integer division by...
    // 0x01000000 [24]    UFSR_UNALIGNED (0) Sticky flag indicating whether an unaligned access error...
    // 0x00100000 [20]    UFSR_STKOF   (0) Sticky flag indicating whether a stack overflow error...
    // 0x00080000 [19]    UFSR_NOCP    (0) Sticky flag indicating whether a coprocessor disabled or...
    // 0x00040000 [18]    UFSR_INVPC   (0) Sticky flag indicating whether an integrity check error...
    // 0x00020000 [17]    UFSR_INVSTATE (0) Sticky flag indicating whether an EPSR
    // 0x00010000 [16]    UFSR_UNDEFINSTR (0) Sticky flag indicating whether an undefined instruction...
    // 0x00008000 [15]    BFSR_BFARVALID (0) Indicates validity of the contents of the BFAR register
    // 0x00002000 [13]    BFSR_LSPERR  (0) Records whether a BusFault occurred during FP lazy state...
    // 0x00001000 [12]    BFSR_STKERR  (0) Records whether a derived BusFault occurred during...
    // 0x00000800 [11]    BFSR_UNSTKERR (0) Records whether a derived BusFault occurred during...
    // 0x00000400 [10]    BFSR_IMPRECISERR (0) Records whether an imprecise data access error has occurred
    // 0x00000200 [9]     BFSR_PRECISERR (0) Records whether a precise data access error has occurred
    // 0x00000100 [8]     BFSR_IBUSERR (0) Records whether a BusFault on an instruction prefetch...
    // 0x000000ff [7:0]   MMFSR        (0x00) Provides information on MemManage exceptions
    io_rw_32 cfsr;

    _REG_(M33_HFSR_OFFSET) // M33_HFSR
    // Shows the cause of any HardFaults
    // 0x80000000 [31]    DEBUGEVT     (0) Indicates when a Debug event has occurred
    // 0x40000000 [30]    FORCED       (0) Indicates that a fault with configurable priority has...
    // 0x00000002 [1]     VECTTBL      (0) Indicates when a fault has occurred because of a vector...
    io_rw_32 hfsr;

    _REG_(M33_DFSR_OFFSET) // M33_DFSR
    // Shows which debug event occurred
    // 0x00000010 [4]     EXTERNAL     (0) Sticky flag indicating whether an External debug request...
    // 0x00000008 [3]     VCATCH       (0) Sticky flag indicating whether a Vector catch debug...
    // 0x00000004 [2]     DWTTRAP      (0) Sticky flag indicating whether a Watchpoint debug event...
    // 0x00000002 [1]     BKPT         (0) Sticky flag indicating whether a Breakpoint debug event...
    // 0x00000001 [0]     HALTED       (0) Sticky flag indicating that a Halt request debug event...
    io_rw_32 dfsr;

    _REG_(M33_MMFAR_OFFSET) // M33_MMFAR
    // Shows the address of the memory location that caused an MPU fault
    // 0xffffffff [31:0]  ADDRESS      (0x00000000) This register is updated with the address of a location...
    io_rw_32 mmfar;

    _REG_(M33_BFAR_OFFSET) // M33_BFAR
    // Shows the address associated with a precise data access BusFault
    // 0xffffffff [31:0]  ADDRESS      (0x00000000) This register is updated with the address of a location...
    io_rw_32 bfar;

    uint32_t _pad0;

    // (Description copied from array index 0 register M33_ID_PFR0 applies similarly to other array indexes)
    _REG_(M33_ID_PFR0_OFFSET) // M33_ID_PFR0
    // Gives top-level information about the instruction set supported by the PE
    // 0x000000f0 [7:4]   STATE1       (0x3) T32 instruction set support
    // 0x0000000f [3:0]   STATE0       (0x0) A32 instruction set support
    io_ro_32 id_pfr[2];

    _REG_(M33_ID_DFR0_OFFSET) // M33_ID_DFR0
    // Provides top level information about the debug system
    // 0x00f00000 [23:20] MPROFDBG     (0x2) Indicates the supported M-profile debug architecture
    io_ro_32 id_dfr0;

    _REG_(M33_ID_AFR0_OFFSET) // M33_ID_AFR0
    // Provides information about the IMPLEMENTATION DEFINED features of the PE
    // 0x0000f000 [15:12] IMPDEF3      (0x0) IMPLEMENTATION DEFINED meaning
    // 0x00000f00 [11:8]  IMPDEF2      (0x0) IMPLEMENTATION DEFINED meaning
    // 0x000000f0 [7:4]   IMPDEF1      (0x0) IMPLEMENTATION DEFINED meaning
    // 0x0000000f [3:0]   IMPDEF0      (0x0) IMPLEMENTATION DEFINED meaning
    io_ro_32 id_afr0;

    // (Description copied from array index 0 register M33_ID_MMFR0 applies similarly to other array indexes)
    _REG_(M33_ID_MMFR0_OFFSET) // M33_ID_MMFR0
    // Provides information about the implemented memory model and memory management support
    // 0x00f00000 [23:20] AUXREG       (0x1) Indicates support for Auxiliary Control Registers
    // 0x000f0000 [19:16] TCM          (0x0) Indicates support for tightly coupled memories (TCMs)
    // 0x0000f000 [15:12] SHARELVL     (0x1) Indicates the number of shareability levels implemented
    // 0x00000f00 [11:8]  OUTERSHR     (0xf) Indicates the outermost shareability domain implemented
    // 0x000000f0 [7:4]   PMSA         (0x4) Indicates support for the protected memory system...
    io_ro_32 id_mmfr[4];

    // (Description copied from array index 0 register M33_ID_ISAR0 applies similarly to other array indexes)
    _REG_(M33_ID_ISAR0_OFFSET) // M33_ID_ISAR0
    // Provides information about the instruction set implemented by the PE
    // 0x0f000000 [27:24] DIVIDE       (0x8) Indicates the supported Divide instructions
    // 0x00f00000 [23:20] DEBUG        (0x0) Indicates the implemented Debug instructions
    // 0x000f0000 [19:16] COPROC       (0x9) Indicates the supported Coprocessor instructions
    // 0x0000f000 [15:12] CMPBRANCH    (0x2) Indicates the supported combined Compare and Branch instructions
    // 0x00000f00 [11:8]  BITFIELD     (0x3) Indicates the supported bit field instructions
    // 0x000000f0 [7:4]   BITCOUNT     (0x0) Indicates the supported bit count instructions
    io_ro_32 id_isar[6];

    uint32_t _pad1;

    _REG_(M33_CTR_OFFSET) // M33_CTR
    // Provides information about the architecture of the caches
    // 0x80000000 [31]    RES1         (1) Reserved, RES1
    // 0x0f000000 [27:24] CWG          (0x0) Log2 of the number of words of the maximum size of...
    // 0x00f00000 [23:20] ERG          (0x0) Log2 of the number of words of the maximum size of the...
    // 0x000f0000 [19:16] DMINLINE     (0x0) Log2 of the number of words in the smallest cache line...
    // 0x0000c000 [15:14] RES1_1       (0x3) Reserved, RES1
    // 0x0000000f [3:0]   IMINLINE     (0x0) Log2 of the number of words in the smallest cache line...
    io_ro_32 ctr;

    uint32_t _pad2[2];

    _REG_(M33_CPACR_OFFSET) // M33_CPACR
    // Specifies the access privileges for coprocessors and the FP Extension
    // 0x00c00000 [23:22] CP11         (0x0) The value in this field is ignored
    // 0x00300000 [21:20] CP10         (0x0) Defines the access rights for the floating-point functionality
    // 0x0000c000 [15:14] CP7          (0x0) Controls access privileges for coprocessor 7
    // 0x00003000 [13:12] CP6          (0x0) Controls access privileges for coprocessor 6
    // 0x00000c00 [11:10] CP5          (0x0) Controls access privileges for coprocessor 5
    // 0x00000300 [9:8]   CP4          (0x0) Controls access privileges for coprocessor 4
    // 0x000000c0 [7:6]   CP3          (0x0) Controls access privileges for coprocessor 3
    // 0x00000030 [5:4]   CP2          (0x0) Controls access privileges for coprocessor 2
    // 0x0000000c [3:2]   CP1          (0x0) Controls access privileges for coprocessor 1
    // 0x00000003 [1:0]   CP0          (0x0) Controls access privileges for coprocessor 0
    io_rw_32 cpacr;

    _REG_(M33_NSACR_OFFSET) // M33_NSACR
    // Defines the Non-secure access permissions for both the FP Extension and coprocessors CP0 to CP7
    // 0x00000800 [11]    CP11         (0) Enables Non-secure access to the Floating-point Extension
    // 0x00000400 [10]    CP10         (0) Enables Non-secure access to the Floating-point Extension
    // 0x00000080 [7]     CP7          (0) Enables Non-secure access to coprocessor CP7
    // 0x00000040 [6]     CP6          (0) Enables Non-secure access to coprocessor CP6
    // 0x00000020 [5]     CP5          (0) Enables Non-secure access to coprocessor CP5
    // 0x00000010 [4]     CP4          (0) Enables Non-secure access to coprocessor CP4
    // 0x00000008 [3]     CP3          (0) Enables Non-secure access to coprocessor CP3
    // 0x00000004 [2]     CP2          (0) Enables Non-secure access to coprocessor CP2
    // 0x00000002 [1]     CP1          (0) Enables Non-secure access to coprocessor CP1
    // 0x00000001 [0]     CP0          (0) Enables Non-secure access to coprocessor CP0
    io_rw_32 nsacr;
} armv8m_scb_hw_t;

#define scb_hw ((armv8m_scb_hw_t *)(PPB_BASE + M33_CPUID_OFFSET))
#define scb_ns_hw ((armv8m_scb_hw_t *)(PPB_NONSEC_BASE + M33_CPUID_OFFSET))
static_assert(sizeof (armv8m_scb_hw_t) == 0x0090, "");

#endif // _HARDWARE_STRUCTS_SCB_H

