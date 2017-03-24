CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm
BINDIR=./bin

essai1: essai1.o pgm.o
	gcc $(LDFLAGS)  $^  -o $(BINDIR)/$@

essai2: essai2.o pgm.o fft.o
	gcc $(LDFLAGS)  $^  -o $(BINDIR)/$@

tp1: tp1.o pgm.o fft.o divers.o
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

PNSR: PNSR.o pgm.o divers.o
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

tp1_pourtest: tp1_pourtest.o pgm.o fft.o divers.o
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $<

clean:
	rm *.o
