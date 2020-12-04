CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS_T=cards.c deck.c eval.c future.c input.c test-input.c
OBJS_T=$(patsubst %.c, %.o, $(SRCS_T))
SRCS_F=cards.c deck.c eval.c future.c test-future.c
OBJS_F=$(patsubst %.c, %.o, $(SRCS_F))
ALL_OBJS=$(wildcard *.o)
PROGRAMS=test-future test-input

test-future: $(OBJS_F)
	$(CC) $(CFLAGS) -o $@ $(OBJS_F)

test-input: $(OBJS_T)
	$(CC) $(CFLAGS) -o $@ $(OBJS_T)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(ALL_OBJS) $(PROGRAMS) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
input.o: input.h 
future.o: future.h
test-future.o: cards.h
test-future.o: deck.h
test-future.o: future.h
test-input.o: input.h
