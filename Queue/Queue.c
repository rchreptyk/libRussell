#include "Queue.h"
#include "List.h"

struct queueStruct {
	List * list;
};

Queue * Queue_create()
{
	Queue * queue = malloc(sizeof(Queue));
	if(queue == NULL)
		return NULL;

	queue->list = List_create();
	if(queue->list == NULL)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

Boolean Queue_destroy(Queue * queue)
{
	List * list = queue->list;
	free(queue);
	return List_destroy(list);
}

Boolean Queue_destroyQueueAndData(Queue * queue, void (*destroyData)(void * data))
{
	List * list = queue->list;
	free(queue);
	return List_destroyListAndData(list, destroyData);
}

Boolean Queue_enqueue(Queue * queue, void * data)
{
	return List_addBack(queue->list, data);
}

void * Queue_dequeue(Queue * queue)
{
	return List_removeFront(queue->list);
}

void * Queue_peek(Queue * queue)
{
	return List_getFirstValue(queue->list);
}

int Queue_getLength(Queue * queue)
{
	return List_getLength(queue->list);
}