#include "PriorityQueue.h"

struct priqueueStruct
{
	AVLTree * tree;
};

PriorityQueue * PriorityQueue_create(int (*compareData)(void *, void *))
{
	if(compareData == NULL)
		return NULL;

	AVLTree * tree = AVLTree_create(compareData);

	if(tree == NULL)
		return NULL;

	PriorityQueue * queue = malloc(sizeof(PriorityQueue));
	if(queue == NULL)
		return NULL;

	queue->tree = tree;

	return queue;
}

Boolean PriorityQueue_destroy(PriorityQueue * queue)
{
	if(queue == NULL)
		return false;

	AVLTree_destroy(queue->tree);
	free(queue);

	return true;
}

Boolean PriorityQueue_destroyQueueAndData(PriorityQueue * queue, void (*destroyData)(void * data))
{
	if(queue == NULL)
		return false;

	AVLTree_destroyTreeAndData(queue->tree, destroyData);
	free(queue);

	return true;
}

/* Operations */

Boolean PriorityQueue_enqueue(PriorityQueue * queue, void * data)
{
	if(queue == NULL || data == NULL)
		return false;

	return AVLTree_insert(queue->tree, data);
}

void * PriorityQueue_dequeue(PriorityQueue * queue)
{
	if(queue == NULL)
		return NULL;

	void * data = AVLTree_getGreatestNode(queue->tree);

	if(data == NULL)
		return NULL;

	return AVLTree_remove(queue->tree, data);
}

void * PriorityQueue_peek(PriorityQueue * queue)
{
	if(queue == NULL)
		return NULL;

	return AVLTree_getGreatestNode(queue->tree);
}

/* Properties */

int PriorityQueue_getLength(PriorityQueue * queue)
{
	if(queue == NULL)
		return 0;

	return AVLTree_getNumNodes(queue->tree);
}

