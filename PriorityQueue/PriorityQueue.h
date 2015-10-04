#ifndef PriorityQueue_ADT
#define PriorityQueue_ADT

#include "Boolean.h"
#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

struct priqueueStruct;
typedef struct priqueueStruct PriorityQueue;

PriorityQueue * PriorityQueue_create(int (*compareData)(void *, void *));

Boolean PriorityQueue_destroy(PriorityQueue *);

Boolean PriorityQueue_destroyQueueAndData(PriorityQueue * PriorityQueue, void (*destroyData)(void * data));

/* Operations */

Boolean PriorityQueue_enqueue(PriorityQueue *, void * data);

void * PriorityQueue_dequeue(PriorityQueue *);

void * PriorityQueue_peek(PriorityQueue *);

/* Properties */

int PriorityQueue_getLength(PriorityQueue *);

#endif
