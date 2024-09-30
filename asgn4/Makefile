CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm


all: calc test


calc: calc.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

test: tests.o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf test calc *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
