CC=i586-mingw32msvc-gcc
CCOPTS=-Wall -W

.PHONY: all clean

all: mcfifo.c
	$(CC) $(CCOPTS) -o mcfifo.exe mcfifo.c

argdumper: argdumper.c
	$(CC) $(CCOPTS) -o argdumper.exe argdumper.c

clean:
	rm mcfifo.exe 2> /dev/null
	rm argdumper.exe 2> /dev/null
