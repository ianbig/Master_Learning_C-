CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -std=gnu99
OBJS = power.o test-power.o
power: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm  *.o power
