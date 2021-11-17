CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt decrypt keygen


encrypt: encrypt.o randstate.o numtheory.o
	$(CC) encrypt.o randstate.o numtheory.o -lm -lgmp -o encrypt $(LFLAGS)

decrypt: decrypt.o randstate.o numtheory.o
	$(CC) decrypt.o randstate.o numtheory.o -lm -lgmp -o decrypt $(LFLAGS)

keygen: keygen.o randstate.o numtheory.o
	$(CC) keygen.o randstate.o numtheory.o -lm -lgmp -o keygen $(LFLAGS)

encrypt.o: encrypt.c decrypt.c keygen.c
	$(CC) $(CFLAGS) -c encrypt.c decrypt.c keygen.c
clean:
	rm -f *.o encrypt decrypt keygen
format:
	clang-format -i -style=file *.[ch]

# decode.o: decode.c 
# 	$(CC) $(CFLAGS) -c decode.c 
# clean:
# 	rm -f *.o decode 
# format:
# 	clang-format -i -style=file *.[ch]

