#ifndef _IRQ_
#define _IRQ_

#include <stdio.h>
#include <stdlib.h>
#include "./hw/hw.h"
#include "ctx.h"

extern void handler (void);

extern void start_sched();

#endif
