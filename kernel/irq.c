#include "io.h"
#include "arm_local_reg.h"
#include "base.h"
#include "timer.h"

void irq_handle(void)
{
	unsigned int irq = readl(ARM_LOCAL_IRQ_SOURCE0);

	switch (irq) {
	case (CNT_PNS_IRQ):
		handle_timer_irq();
		break;
	default:
	//	printk("Unknown pending irq: %x\r\n", irq);
	//	break;
	}
}

