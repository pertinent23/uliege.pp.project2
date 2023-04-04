### 
## Makefile skeleton
## INFO0030: Projet 1
## 
### 

## Variables

# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=
AT=tar
ATFLAGS=-zcvf
DT=doxygen

# Files
EXEC=stegano
MODULES=pnm.c stegano.c main-stegano.c
OBJECTS=pnm/pnm.o pnm/utils.o stegano.o main-stegano.o
OUTPUT=steganographie.tar.gz
CONFIG=doxygen.config

.PHONY: $(EXEC)

$(EXEC): $(OBJECTS) pnm
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main-stegano.o: main-stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

stegano.o: stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

pnm:
	cd $(PWD)/pnm && make pnm

clean_pnm:
	cd $(PWD)/pnm && make clean

clean: clean_pnm
	rm -f *.o *.ppm *.pgm *.pbm *.txt $(EXEC) $(OUTPUT) *~

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc:
	$(DT) $(CONFIG)

check_memory:
	valgrind --leak-check=full ./