#include "uart.h"
#include "smp.h"

void slaveCore_Init(void);
void slaveCore_Poll(void);

u32 gLock = LOCK_BUSY;

void masterCore_Init(void)
{
	uart_init();
	timer_init();
	spin_lock_init(&gLock);
}

void masterCore_Poll(void)
{
	while (TRUE)
	{
		spin_lock_acquire(&gLock);
		coreInfoShow();
		spin_lock_release(&gLock);
	};
}

void slaveCore_Init(void)
{
	slaveCore_Poll();
}

void slaveCore_Poll(void)
{
	while (TRUE)
	{
		spin_lock_acquire(&gLock);
		coreInfoShow();
		spin_lock_release(&gLock);
	}
}

void kernel_main(void)
{
	masterCore_Init();

	masterCore_Poll();
}
