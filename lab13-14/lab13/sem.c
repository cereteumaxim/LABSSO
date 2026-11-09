// sem.c: counting semaphores inside the xv6 kernel (Lab 13).
// NSEM semaphores in one global table, shared by all processes.
// A semaphore is just a number plus a spinlock that guards the number;
// waiting is done with the kernel's sleep_prepare()/sleep() and wakeup().

#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"

#define NSEM 8

struct sem {
  struct spinlock lock;   // all zero = unlocked, so the table needs no init
  int value;              // how many sem_down calls may still pass
};

static struct sem sems[NSEM];

// look up semaphore number id; 0 if it does not exist
static struct sem *
semget(int id)
{
  if (id < 0 || id >= NSEM)
    return 0;
  return &sems[id];
}

// sem_init(id, value): set the start value of semaphore id.
uint64
sys_sem_init(void)
{
  int id, value;
  struct sem *s;

  argint(0, &id);
  argint(1, &value);
  if ((s = semget(id)) == 0 || value < 0)
    return -1;
  acquire(&s->lock);
  s->value = value;
  release(&s->lock);
  return 0;
}

// sem_down(id): take one unit; while there is none, sleep.
uint64
sys_sem_down(void)
{
  int id;
  struct sem *s;

  argint(0, &id);
  if ((s = semget(id)) == 0)
    return -1;
  acquire(&s->lock);
  while (s->value == 0) {
    sleep_prepare(s);       // register: I wait for wakeups on address s
    release(&s->lock);      // never sleep with a spinlock held
    sleep();                // returns at once if a wakeup came in between
    acquire(&s->lock);      // then test the value again
    if (killed(myproc())) { // a waiting process must still be killable
      release(&s->lock);
      return -1;
    }
  }
  s->value--;
  release(&s->lock);
  return 0;
}

// sem_up(id): give one unit back and wake everyone sleeping on s.
uint64
sys_sem_up(void)
{
  int id;
  struct sem *s;

  argint(0, &id);
  if ((s = semget(id)) == 0)
    return -1;
  acquire(&s->lock);
  s->value++;
  wakeup(s);
  release(&s->lock);
  return 0;
}

// sem_trydown(id): like sem_down, but never sleeps:
// returns -1 at once if the value is 0 (optional part).
uint64
sys_sem_trydown(void)
{
  int id, ok = 0;
  struct sem *s;

  argint(0, &id);
  if ((s = semget(id)) == 0)
    return -1;
  acquire(&s->lock);
  if (s->value > 0) {
    s->value--;
    ok = 1;
  }
  release(&s->lock);
  return ok ? 0 : -1;
}
