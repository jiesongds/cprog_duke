test-subseq: maxSeq.o test-subseq.o
	gcc -o test-subseq maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc -c -std=gnu99 -pedantic -Wall maxSeq.c
test-subseq.o: test-subseq.c
	gcc -c -std=gnu99 -pedantic -Wall test-subseq.c
.PHONY: clean
clean:
	rm -f test-subseq *.o *.c~ 
