CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = 
EXEC = uniqcounter
HEADERS = item.h ll.h hash.h dictwords.h

all: toy bench1 bench2 uniqq

$(EXEC): main.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

uniqq: uniqq.o ll.o item.o hash.o badhash.o
	$(CC) $^ $(LFLAGS) -o $@

toy: toy.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench1: dictwords_list.o abstractwords.o bench1.o ll.o item.o
	$(CC) $^ $(LFLAGS) -o $@

bench2: dictwords_hash.o abstractwords.o bench2.o hash.o ll.o item.o badhash.o
	$(CC) $^ $(LFLAGS) -o $@
	


clean:
	rm -rf $(EXEC) bench1 bench2 toy uniqq *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
