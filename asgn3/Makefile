CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting


sorting: sorting.o insert.o stats.o shell.o quick.o heap.o
	$(CC) $(CFLAGS) insert.o stats.o sorting.o shell.o quick.o heap.o  -lm -o sorting


sorting.o: sorting.c 
	$(CC) $(CFLAGS) -c sorting.c 
clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.[ch]
