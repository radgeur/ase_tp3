#include "irq.h"

void handler (void) {
  yield();
}

void start_sched(){
  start_hw();
  setup_irq(TIMER_IRQ, handler);
}
