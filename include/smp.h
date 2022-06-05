#ifndef	_SMP_H
#define	_SMP_H
#include "atomic.h"
#include "lock.h"
#include "system.h"
#include "uart.h"

#define MAX_CORE_NUM        4
#define MASTER_CORE_ID      0

static inline void coreInfoShow(void)
{
	u8 procId = 0;
	
	procId = getProcId();

	switch (procId)
	{
		case 0:
	//		uart_send_string("Welcome Pi3 Core #0 :) \n");
			break;
		case 1:
	//		uart_send_string("Welcome Pi3 Core #1 :) \n");
			break;
		case 2:
	//		uart_send_string("Welcome Pi3 Core #2 :) \n");
			break;
		case 3:
	//		uart_send_string("Welcome Pi3 Core #3 :) \n");
			break;
		default:
	//		uart_send_string("ERROR: Unknow Core !!!\n");
			break;
	}
}
#endif
