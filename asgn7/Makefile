CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: banhammer


banhammer: banhammer.o bf.o bv.o speck.o
	$(CC) $(CFLAGS) banhammer.o bf.o bv.o speck.o -lm -o banhammer


banhammer.o: banhammer.c 
	$(CC) $(CFLAGS) -c banhammer.c 
clean:
	rm -f *.o banhammer
format:
	clang-format -i -style=file *.[ch]
