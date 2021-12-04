CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: banhammer


banhammer: banhammer.o bf.o bv.o speck.o node.o
	$(CC) $(CFLAGS) banhammer.o bf.o bv.o speck.o node.o -lm -o banhammer


banhammer.o: banhammer.c 
	$(CC) $(CFLAGS) -c banhammer.c 
clean:
	rm -f *.o banhammer
format:
	clang-format -i -style=file *.[ch]
