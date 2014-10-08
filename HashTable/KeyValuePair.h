#ifndef KeyValuePair_ADT
#define KeyValuePair_ADT

#include <stdlib.h>
#include "Boolean.h"
#include "rString.h"

struct keyValuePairStruct;
typedef struct keyValuePairStruct KeyValuePair;

/*******************************************************************************************
 CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************************************/

KeyValuePair * KeyValuePair_create(String *);

Boolean KeyValuePair_destroy(KeyValuePair *);

void KeyValuePair_destroyVoid(void * pair);

/*******************************************************************************************
 PROPERTIES
 ******************************************************************************************/

Boolean KeyValuePair_setValue(KeyValuePair *, void *);

void * KeyValuePair_getValue(KeyValuePair *);

/*******************************************************************************************
 COMPARISION
 ******************************************************************************************/

int KeyValuePair_isEqual(void * , void *);

#endif
