#ifndef	_LOCK_H
#define	_LOCK_H
#include "system.h"

#define LOCK_FREE 0
#define LOCK_BUSY 1

static inline u64 arch_spin_lock(u32 *addr, u32 old, u32 new)
{
    u32 oldVal, res;

    asm volatile(
        "1: ldxr %w0, %2\n"
        "   cmp %w0, %w3\n"
        "   b.ne 2f\n"
        "   stxr %w1, %w4, %2\n"
        "   cbnz %w1, 1b\n"
        "2:"
        :"=&r" (oldVal), "=&r" (res), "+Q" (*addr)
        :"r" (old), "r" (new)
        :"memory");

    return oldVal;
}

static inline void spin_lock_init(u32 *lock)
{
    *lock = LOCK_FREE;
}

static inline void spin_lock_acquire(u32 *lock)
{
    while (arch_spin_lock(lock, LOCK_FREE, LOCK_BUSY) != LOCK_FREE);
}

static inline void spin_lock_release(u32 *lock)
{
    *lock = LOCK_FREE;
}
#endif
