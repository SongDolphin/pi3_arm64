#ifndef	_SYSTEM_H
#define	_SYSTEM_H
#include "types.h"

#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")

#define smp_mb()	dmb()
#define smp_rmb()	dmb()
#define smp_wmb()	dmb()

static inline u8 getProcId(void)
{
    u8 procId = 0;

    asm volatile(
        "mrs %0, mpidr_el1\n"
        "and %0, %0, #0xFF"
        : "+r" (procId)
    );
    return procId;
}
#endif
