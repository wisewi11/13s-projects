CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS =

EXEC1 = huff
EXEC2 = pqtest
EXEC3 = nodetest
EXEC4 = bwtest
EXEC5 = brtest
EXEC6 = dehuff

OBJS1 = huff.o bitwriter.o bitreader.o node.o pq.o
OBJS2 = pq.o pqtest.o node.o
OBJS3 = node.o nodetest.o
OBJS4 = bitwriter.o bwtest.o
OBJS5 = bitreader.o brtest.o
OBJS6 = dehuff.o bitwriter.o bitreader.o node.o pq.o

.PHONY: all clean format scan-build

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6)

$(EXEC1): $(OBJS1)
	$(CC) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(CC) $(LFLAGS) -o $@ $^

$(EXEC3): $(OBJS3)
	$(CC) $(LFLAGS) -o $@ $^

$(EXEC4): $(OBJS4)
	$(CC) $(LFLAGS) -o $@ $^

$(EXEC5): $(OBJS5)
	$(CC) $(LFLAGS) -o $@ $^

$(EXEC6): $(OBJS6)
	$(CC) $(LFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)  brtest.in bwtest.out

scan-build: clean
	scan-build --use-cc=clang make

format:
	clang-format -i -style=file *.[ch]

