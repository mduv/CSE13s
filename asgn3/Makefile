CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting


sorting: sorting.o bbp.o
	$(CC) $(CFLAGS) sorting.o bbp.o -lm -o sorting


sorting.o: sorting.c 
	$(CC) $(CFLAGS) -c sorting.c 
clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.[ch]
