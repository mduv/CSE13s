CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode


encode: encode.o node.o code.o pq.o stack.o io.o huffman.o
	$(CC) $(CFLAGS) encode.o node.o code.o pq.o stack.o io.o huffman.o -lm -o encode


encode.o: encode.c 
	$(CC) $(CFLAGS) -c encode.c 
clean:
	rm -f *.o encode 
format:
	clang-format -i -style=file *.[ch]

