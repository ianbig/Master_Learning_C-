test: test.o
	gcc -Wall -Werror -pedantic -std=gnu99 $< -o $@
%.o: %.c
	gcc -Wall -Werror -pedantic -std=gnu99 -c $<

.PHONY: clean
clean:
	rm *.o test
