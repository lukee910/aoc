CC = gcc
CFLAGS = -O -Wall -Werror=multichar -fwrapv

all: day1 day2 day3

day1: day1/day1.c
	$(CC) $(CFLAGS) -g -o day1/day1 day1/day1.c

day2: day2/day2.c
	$(CC) $(CFLAGS) -g -o day2/day2 day2/day2.c

day3: day3/day3.c
	$(CC) $(CFLAGS) -g -o day3/day3 day3/day3.c

clean:
	rm -f *.o d1 *~
