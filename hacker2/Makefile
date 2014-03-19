#
# Makefile
#
# Computer Science 50
# Hacker 2
#

crack: crack.c Makefile
	clang -ggdb3 -O0 -std=c99 -Wall -Werror -Wno-unused-variable -o crack crack.c -lm -lcrypt
	
clean:
	rm -f *.o core breakout
