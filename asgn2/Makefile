CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib-test


mathlib-test: mathlib-test.o e.o viete.o newton.o madhava.o euler.o bbp.o
	$(CC) $(CFLAGS) mathlib-test.o e.o viete.o newton.o madhava.o euler.o bbp.o -o mathlib-test


mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c 
clean:
	rm -f *.o

format:
	clang-format -i -style=file *.[ch]
