CC = gcc
CFLAGS = -Wall -O3 -lm -lpthread
TARGETS = finite_diff_single finite_diff_parallel

all: $(TARGETS)

finite_diff_single: finite_diff_single.c
	$(CC) $(CFLAGS) -o finite_diff_single finite_diff_single.c

finite_diff_parallel: finite_diff_parallel.c
	$(CC) $(CFLAGS) -o finite_diff_parallel finite_diff_parallel.c

clean:
	rm -f $(TARGETS) solution.csv parallel_solution.csv

run_single: finite_diff_single
	./finite_diff_single

run_parallel: finite_diff_parallel
	./finite_diff_parallel
