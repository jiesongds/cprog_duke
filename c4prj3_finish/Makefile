CC=gcc
CFLAGS=-Wall -Werror -ggdb3 -std=gnu99 -pedantic $(OTHERFLAGS)
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))

poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
		gcc -o $@ $(CFLAGS) $^

%.o: %.c
	$(CC) -c $(CFLAGS) $<
clean:
		rm -rf *.o poker *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
input.o: input.h 
future.o: future.h
main.o: cards.h
main.o: deck.h
main.o: eval.h
main.o: future.h
main.o: input.h
