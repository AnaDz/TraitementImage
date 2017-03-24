CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm
BINDIR=./bin

tp2: tp2.o pgm.o divers.o
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

PNSR: PNSR.o pgm.o divers.o
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)


%.o:%.c
	gcc $(CFLAGS) $<

clean:
	rm *.o
