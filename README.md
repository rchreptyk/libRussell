libRussell
==========

libRussell is a collection of C Abstract Datatypes that I commonly use during C Programs. When writing C code for class I must only use code that I have written. libRussell is a library that I use for these programs.

The set of data structures are by no means the best implementation possible. There are much more efficient ways of implementing some of the data structures. My String implementation is very inefficient and memory hard, but it is convenient to use.

AVLTree
-------

This is an implementation of an AVL Binary Tree. This structure provides the essential operations that can be preformed on the tree.

Boolean
-------

A simple definition of a `Boolean` type, and `true` and `false` constants. This definition is used throughout libRussell as the Boolean type implementation.

HashTable
---------

This is a basic implementation of a hash table. It also provides a `KeyValuePair` data type for a double tuple. This structure associates keys and valuables. The hash table provides a way of storing KeyValuePairs. There is also a basic implementation of SHA2 for use within the hash table. *do not* use the hash for a secure hash.

List
----

A vanilla linked list implementation with an iterator.

PriorityQueue
-------------

A queue implementation where added elements are inserted in order specified by a `compareData` function.

Queue
-----

A vanilla queue implementation.

Stack
-----

A stack implementation, not finished.

Steam
-----

The beginning of an abstract stream implementation. A `stream` structure can represent a file, stdout, stdin and a socket in the future. It allows you to easily read and write to a stream. It also has a basic printf implementation for printing an `rString`.

rString
-------

An inefficient but convenient String representation. This allows for easy string manipulation without worrying about managing array memory.

