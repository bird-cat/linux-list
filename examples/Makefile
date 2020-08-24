CC = gcc
CFLAGS = -g -O0 -I../include -I../private
OPTIONS = -DSIZE=1000 -DRANDOM
OBJECTS = insert-sort.o quick-sort.o merge-sort.o bubble-sort.o

.PHONY: all clean

plot: test
	gnuplot plot.gp

test: all
	./benchmark list_insertsort
	./benchmark list_qsort
	./benchmark list_mergesort
	./benchmark list_bubblesort

all: benchmark

benchmark: benchmark.c $(OBJECTS)
	$(CC) $(CFLAGS) $(OPTIONS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.log *.png benchmark

