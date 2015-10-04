
#ifndef ArrayList_ADT
#define ArrayList_ADT

#include "Boolean.h"
#include <stdlib.h>
#include <string.h>

struct arrayListStruct;
typedef struct arrayListStruct ArrayList;

ArrayList * ArrayList_create(int initialSize, size_t objectSize);

Boolean ArrayList_destroy(ArrayList * destroy);

Boolean ArrayList_set(ArrayList * list, int index, void * value);

Boolean ArrayList_get(ArrayList * list, int index, void * result);

#endif