#include "ctx.h"
#include "./hw/hw.h"
#include "sem.h"

void f_ping(void *arg);
void f_pong(void *arg);
void producteur(void *arg);
void consommateur(void *arg);

struct sem_s * mutex;
struct sem_s * fullSem;
struct sem_s * emptySem;

int main(int argc, char *argv[])
{
  /*create the context for all the fonctions*/
  /*create_ctx(16384, f_ping, NULL);
    create_ctx(16384, f_pong, NULL);*/
  create_ctx(16384, producteur, NULL);
  create_ctx(16384, consommateur, NULL);

  /*initialise the semaphore*/
  mutex = malloc(sizeof(struct sem_s));
  sem_init(mutex, 1);
  fullSem = malloc(sizeof(struct sem_s));
  sem_init(fullSem, 0);
  emptySem = malloc(sizeof(struct sem_s));
  sem_init(emptySem, 1);

  /*start the schedule*/
  start_sched();
  printf("je suis revenu dans le main\n");
  exit(EXIT_SUCCESS);
}


void producteur(void *args) {
  int i = 1;
  while (i<=1000) {
    printf("Le produit numéro %i a été confectionné\n", i);
    sem_down(emptySem);
    sem_down(mutex);
    yield();
    printf("Le produit numéro %i est disponible\n", i);
    sem_up(mutex);
    sem_up(fullSem);
    yield();
    i++;
  }
}

void consommateur(void *args) {
  int i = 1;
  while (i<=1000) {
    sem_down(fullSem);
    sem_down(mutex);
    printf("Le produit numéro %i a été pris\n", i);
    yield();
    sem_up(mutex);
    sem_up(emptySem);
    printf("Le produit numéro %i a été utilisé\n", i);
    yield();
    i++;
  }
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
