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
MODULES=pnm/pnm.c pnm/utils.c stegano.c
OBJECTS=pnm/pnm.o pnm/utils.o stegano.o main-stegano.o
OUTPUT=steganographie.tar.gz
CONFIG=doxygen.config
PNM_TESTS=pnm_tests
STEGANO_TESTS=stegano_tests
SEATEST=seatest/seatest.c

.PHONY: $(EXEC)

$(EXEC): $(OBJECTS) pnm_create
	$(LD) -o $(EXEC) $(OBJECTS) $(LDFLAGS)

main-stegano.o: main-stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

stegano.o: stegano.c
	$(CC) -c $^ -o $@ $(CFLAGS)

pnm_create: pnm/pnm.c pnm/utils.c
	cd $(PWD)/pnm && make pnm

$(PNM_TESTS): $(PNM_TESTS).c
	$(LD) $(CFLAGS) $(MODULES) $(SEATEST) $(PNM_TESTS).c -o $(PNM_TESTS)

$(STEGANO_TESTS): $(STEGANO_TESTS).c
	$(LD) $(MODULES) $(SEATEST) $(STEGANO_TESTS).c -o $(STEGANO_TESTS) $(CFLAGS)

clean_pnm:
	cd $(PWD)/pnm && make clean

clean: clean_pnm
	rm -f *.o *.ppm *.pgm *.pbm *.txt $(STEGANO_TESTS) $(PNM_TESTS) $(EXEC) $(OUTPUT) *~
	clear

archive: clean
	$(AT) $(ATFLAGS) $(OUTPUT) *

doc:
	$(DT) $(CONFIG)

check_memory:
	valgrind --leak-check=full ./