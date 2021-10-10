CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: mathlib-test
#Testing
e_test: e.o
	$(CC) $(CFLAGS) e.o -o e_test


# mathlib-test: mathlib-test.o e.o euler.o madhava.o newton.o viete.o bbp.o
#	$(CC) $(CFLAGS) mathlib-test.o e.o euler.o madhava.o newton.o viete.o bbp.o

mathlib-test: mathlib-test.o e.o viete.o newton.o madhava.o
	$(CC) $(CFLAGS) mathlib-test.o e.o viete.o newton.o madhava.o -o mathlib-test



#Object Files
e.o: e.c mathlib.h
	$(CC) $(CFLAGS) -c e.c

mathlib-test.o: mathlib-test.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib-test.c 
clean:
	rm -f e_test *.o *.exe

format:
	clang-format -i -style=file *.[ch]
