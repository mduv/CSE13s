CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: tsp


tsp: tsp.o graph.o stack.o path.o
	$(CC) $(CFLAGS) tsp.o graph.o stack.o path.o -lm -o tsp


tsp.o: tsp.c 
	$(CC) $(CFLAGS) -c tsp.c 
clean:
	rm -f *.o tsp 
format:
	clang-format -i -style=file *.[ch]

