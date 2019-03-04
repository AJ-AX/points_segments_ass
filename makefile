CC = gcc
CFLAGS = -Wall -std=gnu99

test: test.o points_segments_naive.o points_segments_divide.o
	$(CC) $(CGLAGS) test.o points_segments_naive.o points_segments_divide.o -o test