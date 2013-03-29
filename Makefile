CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-g3 -Wall -ansi
LDFLAGS     =

REQBOOL = -IBoolean

REQLIST = -IList
LISTOBJ = obj/lib/List.o

REQSTR = -IrString
STROBJ = $(LISTOBJ) obj/lib/rString.o

REQHASH = -IHashTable
HASHOBJ = $(STROBJ) obj/lib/HashTable.o obj/lib/KeyValuePair.o obj/lib/HashFunctions.o

REQQUE = -IQueue
QUEOBJ = $(LISTOBJ) obj/lib/Queue.o

REQTREE = -IAVLTree
TREEOBJ = obj/lib/AVLTree.o

REQPQUE = $(REQTREE) -I PriorityQueue
PQUEOBJ = $(TREEOBJ) obj/lib/PriorityQueue.o

STMPOBJ = $(STROBJ) obj/lib/Stream.o
REQSTMP = -IStream

all: libs tests
libs: $(LISTOBJ) $(STROBJ) $(HASHOBJ) $(QUEOBJ) $(TREEOBJ) $(PQUEOBJ) $(STMPOBJ)
tests: bin/listTest bin/rStringTest bin/hashTableTest bin/queueTest bin/avlTreeTest bin/priorityQueueTest bin/streamTest 


deploy: clean libs
	@ echo Deploying Libraries...
	@ echo Copying headers to headers folder
	@ find . -path ./headers -prune -o -name *.h -exec cp {} headers \;
	@ ar r libRussell.a obj/lib/*
	@ echo Created libRussell.a static library
	@ echo
	@ echo include items headers/ to use library elements
	@ echo link your code with libRussell.a
	@ echo

listTest : bin/listTest
rStringTest : bin/rStringTest
hashTableTest : bin/hashTableTest
listTest : bin/listTest


# List

bin/listTest: $(LISTOBJ) obj/test/listTest.o
	@ echo Linking List Test
	@ gcc $^ -o $@

obj/lib/List.o: List/List.c List/List.h
	@ echo Compiling List Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) -c List/List.c -o $@

obj/test/listTest.o: List/listTest.c
	@ echo Compiling List Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) -c List/listTest.c -o $@

# String

bin/rStringTest: $(STROBJ) obj/test/rStringTest.o
	@ echo Linking String Test
	@ gcc $^ -o $@

obj/lib/rString.o: rString/rString.c rString/rString.h
	@ echo Compiling String Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) -c rString/rString.c -o $@

obj/test/rStringTest.o: rString/rStringTest.c
	@ echo Compiling String Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) -c $^ -o $@

# Hash

bin/hashTableTest: $(HASHOBJ) obj/test/hashTableTest.o
	@ echo Linking HashTable Test
	@ gcc $^ -o $@

obj/test/hashTableTest.o: HashTable/hashTableTest.c
	@ echo Compiling HashTable Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/hashTableTest.c -o $@

obj/lib/HashTable.o: HashTable/HashTable.c HashTable/HashTable.h
	@ echo Compiling HashTable Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/HashTable.c -o $@

obj/lib/KeyValuePair.o: HashTable/KeyValuePair.c HashTable/KeyValuePair.h
	@ echo Compiling KeyValuePair Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/KeyValuePair.c -o $@

obj/lib/HashFunctions.o: HashTable/HashFunctions.c HashTable/HashFunctions.h
	@ echo Compiling Hash Functions
	@gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/HashFunctions.c -o $@

# Queue

bin/queueTest: $(QUEOBJ) obj/test/queueTest.o
	@ echo Link Queue Test
	@ gcc $^ -o $@

obj/test/queueTest.o: Queue/queueTest.c
	@ echo Compiling Queue Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQQUE) -c Queue/queueTest.c -o $@

obj/lib/Queue.o: Queue/Queue.c Queue/Queue.h
	@ echo Compiling Queue Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQQUE) -c Queue/Queue.c -o $@

#AVL Tree

bin/avlTreeTest: $(TREEOBJ) obj/test/avlTreeTest.o
	@ echo Linking AVL Tree Test
	@ gcc $^ -o $@

obj/test/avlTreeTest.o: AVLTree/treeTest.c
	@ echo Compiling AVL Tree Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQTREE) -c AVLTree/treeTest.c -o $@

obj/lib/AVLTree.o: AVLTree/AVLTree.c AVLTree/AVLTree.h
	@ echo Compiling AVLTree Library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQTREE) -c AVLTree/AVLTree.c -o $@

#Priority Queue

bin/priorityQueueTest: $(PQUEOBJ) obj/test/priorityQueueTest.o
	@ echo Linking PriorityQueue test
	@ gcc $^ -o $@

obj/test/priorityQueueTest.o: PriorityQueue/priTest.c
	@ echo Compiling Queue Test
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQTREE) $(REQPQUE) -c PriorityQueue/priTest.c -o $@

obj/lib/PriorityQueue.o: PriorityQueue/PriorityQueue.c PriorityQueue/PriorityQueue.h
	@ echo Compiling PriorityQueue library
	@ gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQTREE) $(REQPQUE) -c PriorityQueue/PriorityQueue.c -o $@

#Stream

bin/streamTest: $(STMPOBJ) obj/test/streamTest.o
	@ echo Linking Stream Test
	@ gcc $^ -o $@

obj/test/streamTest.o: Stream/streamTest.c
	@ echo Compiling Stream Test 
	@ gcc $(CFLAGS) $(REQSTR) $(REQSTMP) $(REQBOOL) $(REQLIST) -c Stream/streamTest.c -o $@

obj/lib/Stream.o: Stream/Stream.c Stream/Stream.h
	@ echo Compiling Stream Library
	@ gcc $(CFLAGS) $(REQSTR) $(REQSTMP) $(REQBOOL) $(REQLIST) -c Stream/Stream.c -o $@

clean:
	@ rm -f libRussell.a
	@ rm -f headers/*
	@ rm -rf bin/*
	@ rm -f obj/*/*.o
