CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=gnu99 -g
test: test.o
	$(CC) $(CFLAGS) $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $<
