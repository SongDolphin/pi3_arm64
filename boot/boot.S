#include "mm.h"
#include "asm/sysregs.h"

.section ".text.boot"

/*
 * Branch according to exception level
 */
.macro	switch_core_entry, xreg, core0_label, core1_label, core2_label core3_label
	mrs	\xreg, mpidr_el1
	and \xreg, \xreg, #0xFF
	cmp	\xreg, 0x0
	b.eq	\core0_label
	cmp \xreg, 0x1
	b.eq	\core1_label
	cmp \xreg, 0x2
	b.eq	\core2_label
	cmp \xreg, 0x3
	b.eq	\core3_label
.endm

.globl _start
_start:
	switch_core_entry x1, 0f, 1f, 2f, 3f

0:
	mrs x5, CurrentEL
	cmp x5, #CurrentEL_EL3
	b.eq el3_entry
	b el2_entry

el3_entry:
	ldr x0, =((1<<10) | 1)
	msr scr_el3, x0

	ldr x0, =0
	msr sctlr_el3, x0

	ldr x0, =SPSR_EL2
	msr spsr_el3, x0
	
	adr x0, el2_entry
	msr elr_el3, x0
	eret

el2_entry:
	mrs x0, CurrentEL
	/* The Execution state for EL1 is AArch64 */
	ldr x0, =HCR_HOST_NVHE_FLAGS
	msr hcr_el2, x0

	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el1, x0

	ldr x0, =SPSR_EL1
	msr spsr_el2, x0

	adr x0, el1_entry
	msr elr_el2, x0

	eret

el1_entry:
	ldr x5, =vectors
	msr vbar_el1, x5
	isb

	adr	x0, bss_begin
	adr	x1, bss_end
	sub	x1, x1, x0
	bl 	memzero

	mov	sp, #CORE_0_SP
	bl	kernel_main

1:
	mov	sp, #CORE_1_SP
	b slave_core

2:
	mov	sp, #CORE_2_SP
	b slave_core

3:
	mov	sp, #CORE_3_SP
	b slave_core

slave_core:
	bl slaveCore_Init
