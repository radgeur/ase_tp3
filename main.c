#include "ctx.h"
#include "./hw/hw.h"
#include "sem.h"

void f_ping(void *arg);
void f_pong(void *arg);

struct sem_s * sem;

int main(int argc, char *argv[])
{
  /*create the context for all the fonctions*/
  create_ctx(16384, f_ping, NULL);
  create_ctx(16384, f_pong, NULL);

  /*initialise the semaphore*/
  /*sem = malloc(sizeof(struct sem_s));
    sem_init(sem, 1);*/

  /*start the schedule*/
  start_sched();
  printf("je suis revenu dans le main\n");
  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
  int i = 10000;
  while(i--) {
    printf("A") ;
    /*sem_down(sem);*/
    yield();
    printf("B") ;
    /*sem_down(sem);*/
    yield();
    printf("C") ;
    /*sem_down(sem);*/
    yield();
  }
}

void f_pong(void *args)
{
  int i =10000;
  while(i--) {
    printf("1") ;
    /*sem_up(sem);*/
    yield();
    printf("2") ;
    /*sem_up(sem);*/
    yield();
  }
} 
