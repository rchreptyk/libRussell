CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-g3 -Wall -ansi -pedantic
LDFLAGS     =

all: listTest rStringTest

listTest : List.o listTest.o
	gcc List.o listTest.o -o listTest

List.o : List/List.c List/List.h
	gcc $(CFLAGS) -I List -c List/List.c

listTest.o : List/listTest.c
	gcc $(CFLAGS) -c -I List List/listTest.c

rStringTest : rString.o rStringTest.o List.o
	gcc rString.o rStringTest.o List.o -o rStringTest

rString.o : rString/rString.c rString/rString.h
	gcc $(CFLAGS) -IList -IrString -c rString/rString.c

rStringTest.o : rString/rStringTest.c
	gcc $(CFLAGS) -IrString -IList -c rString/rStringTest.c

clean:
	@ rm *.o
