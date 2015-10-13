#include "ctx.h"
#include "./hw/hw.h"

void f_ping(void *arg);
void f_pong(void *arg);

int main(int argc, char *argv[])
{
  create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong, NULL);
  start_sched();
  printf("je suis revenu dans le main\n");
  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
  int i = 10000;
  while(i--) {
    printf("A") ;
    yield();
    printf("B") ;
    yield();
    printf("C") ;
    yield();
  }
}

void f_pong(void *args)
{
  int i =10000;
  while(i--) {
    printf("1") ;
    yield();
    printf("2") ;
    yield();
  }
} 
