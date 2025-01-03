CC = gcc
CFLAGS = -Wall -O3 -lm
TARGET = finite_diff_single

all: $(TARGET)

$(TARGET): finite_diff_single.c
	$(CC) $(CFLAGS) -o $(TARGET) finite_diff_single.c

clean:
	rm -f $(TARGET) solution.csv

run: $(TARGET)
	./$(TARGET)
