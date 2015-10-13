CC = gcc
CFLAGS = -W -Wall -pedantic
CFLAGS += -D_XOPEN_SOURCE=500
CFLAGS += -g -m32

all:

ctx.o : ./hw/hw.h ctx.c 
	$(CC) $(CFLAGS) -c ctx.c

main : ./hw/hw.o ctx.o main.o sem.o
	$(CC) $(CFLAGS) -o main ./hw/hw.o ctx.o main.o sem.o

main.o: main.c ctx.h hw/hw.h sem.h
	$(CC) $(CFLAGS) -c main.c

sem.o : ctx.h sem.c 
	$(CC) $(CFLAGS) -c sem.c

clean:
	-rm *.o main .#* *~
