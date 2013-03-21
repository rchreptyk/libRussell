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

all: bin/listTest bin/rStringTest bin/hashTableTest bin/queueTest bin/avlTreeTest bin/priorityQueueTest
deploy: clean all
	find . -name *.h -exec cp {} headers \;
	ar r libRussell.a obj/lib/*

listTest : bin/listTest
rStringTest : bin/rStringTest
hashTableTest : bin/hashTableTest
listTest : bin/listTest

# List

bin/listTest: $(LISTOBJ) obj/test/listTest.o
	gcc $^ -o $@

obj/lib/List.o: List/List.c List/List.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) -c List/List.c -o $@

obj/test/listTest.o: List/listTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) -c List/listTest.c -o $@

# String

bin/rStringTest: $(STROBJ) obj/test/rStringTest.o
	gcc $^ -o $@

obj/lib/rString.o: rString/rString.c rString/rString.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) -c rString/rString.c -o $@

obj/test/rStringTest.o: rString/rStringTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) -c $^ -o $@

# Hash

bin/hashTableTest: $(HASHOBJ) obj/test/hashTableTest.o
	gcc $^ -o $@

obj/test/hashTableTest.o: HashTable/hashTableTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/hashTableTest.c -o $@

obj/lib/HashTable.o: HashTable/HashTable.c HashTable/HashTable.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/HashTable.c -o $@

obj/lib/KeyValuePair.o: HashTable/KeyValuePair.c HashTable/KeyValuePair.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/KeyValuePair.c -o $@

obj/lib/HashFunctions.o: HashTable/HashFunctions.c HashTable/HashFunctions.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQSTR) $(REQHASH) -c HashTable/HashFunctions.c -o $@

# Queue

bin/queueTest: $(QUEOBJ) obj/test/queueTest.o
	gcc $^ -o $@

obj/test/queueTest.o: Queue/queueTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQQUE) -c Queue/queueTest.c -o $@

obj/lib/Queue.o: Queue/Queue.c Queue/Queue.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQQUE) -c Queue/Queue.c -o $@

#AVL Tree

bin/avlTreeTest: $(TREEOBJ) obj/test/avlTreeTest.o
	gcc $^ -o $@

obj/test/avlTreeTest.o: AVLTree/treeTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQTREE) -c AVLTree/treeTest.c -o $@

obj/lib/AVLTree.o: AVLTree/AVLTree.c AVLTree/AVLTree.h
	gcc $(CFLAGS) $(REQBOOL) $(REQTREE) -c AVLTree/AVLTree.c -o $@

#Priority Queue

bin/priorityQueueTest: $(PQUEOBJ) obj/test/priorityQueueTest.o
	gcc $^ -o $@

obj/test/priorityQueueTest.o: PriorityQueue/priTest.c
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQTREE) $(REQPQUE) -c PriorityQueue/priTest.c -o $@

obj/lib/PriorityQueue.o: PriorityQueue/PriorityQueue.c PriorityQueue/PriorityQueue.h
	gcc $(CFLAGS) $(REQBOOL) $(REQLIST) $(REQTREE) $(REQPQUE) -c PriorityQueue/PriorityQueue.c -o $@

#Stream

bin/streamTest: $(STMPOBJ) obj/test/streamTest.o
	gcc $^ -o $@

obj/test/streamTest.o: Stream/streamTest.c
	gcc $(CFLAGS) $(REQSTR) $(REQSTMP) $(REQBOOL) $(REQLIST) -c Stream/streamTest.c -o $@

obj/lib/Stream.o: Stream/Stream.c Stream/Stream.h
	gcc $(CFLAGS) $(REQSTR) $(REQSTMP) $(REQBOOL) $(REQLIST) -c Stream/Stream.c -o $@

clean:
	@ rm -rf deploy
	@ rm -rf bin/*
	@ rm -f obj/*/*.o
