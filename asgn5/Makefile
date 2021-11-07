CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode


encode: encode.o node.o code.o pq.o stack.o io.o huffman.o
	$(CC) $(CFLAGS) encode.o node.o code.o pq.o stack.o io.o huffman.o -lm -o encode


encode.o: encode.c decode.c
	$(CC) $(CFLAGS) -c encode.c decode.c
clean:
	rm -f *.o encode decode
format:
	clang-format -i -style=file *.[ch]



decode: decode.o node.o code.o pq.o stack.o io.o huffman.o
	$(CC) $(CFLAGS) decode.o node.o code.o pq.o stack.o io.o huffman.o -lm -o decode


# decode.o: decode.c 
# 	$(CC) $(CFLAGS) -c decode.c 
# clean:
# 	rm -f *.o decode 
# format:
# 	clang-format -i -style=file *.[ch]

