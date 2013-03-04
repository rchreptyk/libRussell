#include "PriorityQueue.h"

int compareInt(void * data, void * data2)
{
	return *(int*)data - *(int*)data2;
}

int main()
{
	int ints[] = { 6, 47, 13, 19, 18, 22, 55, 92, 44, 33 };

	PriorityQueue * queue = PriorityQueue_create(compareInt);

	int i;
	for(i = 0; i < 10; i++)
	{
		PriorityQueue_enqueue(queue, &ints[i]);
	}

	while(PriorityQueue_getLength(queue) > 0)
	{
		printf("Dequeue %d\n", *(int*) PriorityQueue_dequeue(queue));
	}

	PriorityQueue_destroy(queue);

	return 0;
}