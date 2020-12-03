CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -pedantic -ggdb3
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS)) 
PROGRAM=test-c4deck

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c 
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(PROGRAM) *~

cards.o: cards.h
deck.o: deck.h
eval.o: eval.h
test-c4deck.o: cards.h
test-c4deck.o: deck.h
test-c4deck.o: eval.h


