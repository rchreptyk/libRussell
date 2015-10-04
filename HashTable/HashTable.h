#ifndef HashTable_ADT
#define HashTable_ADT

#include <stdlib.h>
#include "Boolean.h"
#include "List.h"
#include "rString.h"
#include "KeyValuePair.h"
#include "HashFunctions.h"

struct hashTableStruct;
typedef struct hashTableStruct HashTable;

/*******************************************************************************************
 CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************************************/

HashTable * HashTable_create(int);

Boolean HashTable_destroy(HashTable *);

/*******************************************************************************************
 OPERATIONS
 ******************************************************************************************/

Boolean HashTable_setValue(HashTable *, String *, void *);

void * HashTable_getValue(HashTable *, String *);

Boolean HashTable_hasValue(HashTable *, String *);

void * HashTable_removeValue(HashTable *, String *);

List * HashTable_getKeys(HashTable *);

#endif
