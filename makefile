CC=gcc
CFLAGS=-Wall
DEPS=list.h garbage.h

indexe: indexe.c libcx17.so
	$(CC)  indexe.c  ./libcx17.so -o $@ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC)  -c $<  $(CFLAGS)

libcx17.so: list.c garbage.c
	$(CC)  -fpic -shared list.c garbage.c -o $@ $(CFLAGS)

clean:
	rm *~ *.o libcx17.so indexe
