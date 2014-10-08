/*
Queue
 */

#include "Boolean.h"

#ifndef Queue_ADT
#define Queue_ADT

struct queueStruct;
typedef struct queueStruct Queue;

/*******************************************************************************************
 CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************************************/

Queue * Queue_create();

Boolean Queue_destroy(Queue *);

Boolean Queue_destroyQueueAndData(Queue *, void (*destroyData)(void * data));

/*******************************************************************************************
 OPERATIONS
 ******************************************************************************************/

Boolean Queue_enqueue(Queue *, void *);

void * Queue_dequeue(Queue *);

void * Queue_peek(Queue *);

/*******************************************************************************************
 PROPERTIES
 ******************************************************************************************/

int Queue_getLength(Queue * queue);

#endif
