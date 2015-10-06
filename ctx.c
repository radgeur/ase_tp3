#include "ctx.h"

static struct ctx_s *current_ctx = NULL;
static struct ctx_s *ctx_ring = NULL;

static void start_current_ctx (void) {
  current_ctx->ctx_state = CTX_EXEQ;
  current_ctx->ctx_F(current_ctx->ctx_args);
  current_ctx->ctx_state = CTX_END;
  printf ("une des fonctions est terminée\n");
  yield();
}


void init_ctx(struct ctx_s *ctx, int stack_size, func_t *f, void *args) {
  ctx->ctx_F = f;
  ctx->ctx_args = args;
  ctx->ctx_magic = CTX_MAGIC;
  ctx->ctx_state = CTX_INIT;
  ctx->ctx_base = malloc(stack_size);
  ctx->ctx_esp = ctx->ctx_ebp = ctx->ctx_base + stack_size - 4;
}


void switch_to_ctx (struct ctx_s *next) {
  assert (next->ctx_magic == CTX_MAGIC);

  assert (next->ctx_state == CTX_INIT || next->ctx_state == CTX_EXEQ);
  
  if (current_ctx)
    asm ("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
       : "=r"(current_ctx->ctx_esp) , "=r"(current_ctx->ctx_ebp)
       : );

  current_ctx = next;
  
  asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
      :
      :"r"(current_ctx->ctx_esp), "r"(current_ctx->ctx_ebp));

  if (current_ctx->ctx_state == CTX_INIT)
    start_current_ctx();

  while (next->ctx_state == CTX_END){
    if (current_ctx == next)
      return;
    free(next->ctx_base);
    current_ctx->next_ctx = next->next_ctx;
    free(next);
    next=current_ctx->next_ctx;
  }
}

void create_ctx(int stack_size, func_t *f, void *args) {
  struct ctx_s *new = malloc(sizeof(struct ctx_s));
  init_ctx(new, stack_size, f, args);
  if (!ctx_ring)
    ctx_ring = new->next_ctx=new;
  else {
    new->next_ctx = ctx_ring->next_ctx;
    ctx_ring->next_ctx = new;
  }
}

void yield(){
  if(current_ctx)
    switch_to_ctx(current_ctx->next_ctx);
  else if (ctx_ring)
    switch_to_ctx(ctx_ring);
  else
    return;
}
