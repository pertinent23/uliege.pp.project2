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
MODULES=pnm/pnm.c pnm/utils.c
OBJECTS=pnm/pnm.o pnm/utils.o stegano.o main-stegano.o
OUTPUT=steganographie.tar.gz
CONFIG=doxygen.config
PNM_TESTS=pnm_tests
STEGANO_TESTS=stegano_tests
SEATEST=seatest/seatest.c

.PHONY: $(EXEC)

$(EXEC): $(OBJECTS) pnm
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main-stegano.o: main-stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

stegano.o: stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

pnm:
	cd $(PWD)/pnm && make pnm

$(PNM_TESTS):
	$(LD) -o $(PNM_TESTS) $(SEATEST) $(MODULES) $(PNM_TESTS).c $(LDFLAGS)

$(STEGANO_TESTS):
	$(LD) -o $(STEGANO_TESTS) $(SEATEST) $(MODULES) $(STEGANO_TESTS).c $(LDFLAGS)

clean_pnm:
	cd $(PWD)/pnm && make clean

clean: clean_pnm
	rm -f *.o *.ppm *.pgm *.pbm *.txt $(EXEC) $(OUTPUT) *~
	clear

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc:
	$(DT) $(CONFIG)

check_memory:
	valgrind --leak-check=full ./