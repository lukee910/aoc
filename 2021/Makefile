CC = gcc
CFLAGS = -O -Wall -Werror=multichar -fwrapv

all: day1 day2 day3 day4

day1: day1/day1.c
	$(CC) $(CFLAGS) -g -o day1/day1 day1/day1.c

day2: day2/day2.c
	$(CC) $(CFLAGS) -g -o day2/day2 day2/day2.c

day3: day3/day3.c
	$(CC) $(CFLAGS) -g -o day3/day3 day3/day3.c

day4: day4/day4.c
	$(CC) $(CFLAGS) -g -o day4/day4 day4/day4.c

clean:
	rm -f *.o *~
