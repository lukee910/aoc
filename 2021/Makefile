CC = gcc
CFLAGS = -O -Wall -Werror=multichar -fwrapv

d%: day%/main.c
	$(CC) $(CFLAGS) -g -o $@.o $<

clean:
	rm -f *.o *~
