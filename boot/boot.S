#include "mm.h"

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
