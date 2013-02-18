CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-g3 -Wall -ansi -pedantic
LDFLAGS     =

all: listTest rStringTest hashTableTest

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

hashTableTest :  List.o rString.o HashTable.o KeyValuePair.o hashTableTest.o HashFunctions.o
	gcc hashTableTest.o HashTable.o List.o rString.o KeyValuePair.o HashFunctions.o -o hashTableTest

hashTableTest.o : HashTable/hashTableTest.c
	gcc $(CFLAGS) -IHashTable -IrString -IList -c HashTable/hashTableTest.c

HashTable.o : HashTable/HashTable.c HashTable/HashTable.h
	gcc $(CFLAGS) -IrString -IList -IHashTable -c HashTable/HashTable.c

KeyValuePair.o : HashTable/KeyValuePair.c HashTable/KeyValuePair.h
	gcc $(CFLAGS) -IrString -IList -IHashTable -c HashTable/KeyValuePair.c

HashFunctions.o : HashTable/HashFunctions.c HashTable/HashFunctions.h
	gcc $(CFLAGS) -IrString -IList -IHashTable -c HashTable/HashFunctions.c



clean:
	@ rm *.o
