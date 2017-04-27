CFLAGS=-c -g -std=gnu99
LDFLAGS=-lm
BINDIR=./bin

all: tp2 tp2_pourscript PNSR

tp2: tp2.o pgm.o divers.o
	mkdir -p bin
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

tp2_pourscript : tp2_pourscript.o pgm.o divers.o
	mkdir -p bin
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

PNSR: PNSR.o pgm.o divers.o
	mkdir -p bin
	gcc $^ -o $(BINDIR)/$@ $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $<

clean:
	rm -f *.o
	rm -rf bin
