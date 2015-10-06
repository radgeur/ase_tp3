CC = gcc
CFLAGS = -W -Wall -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g -m32

all:

ctx.o : ./hw/hw.h ctx.c 
	$(CC) $(CFLAGS) -c ctx.c

main : ./hw/hw.o irq.o ctx.o main.o
	$(CC) $(CFLAGS) -o main ./hw/hw.o irq.o ctx.o main.o

main.o: main.c ctx.h hw/hw.h
	$(CC) $(CFLAGS) -c main.c

irq.o : ./hw/hw.h irq.c
	$(CC) $(CFLAGS) -c irq.c

clean:
	-rm *.o main  .#* *~
