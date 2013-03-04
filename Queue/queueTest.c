#include <stdio.h>
#include "Queue.h"

int main()
{
	int num[] = { 4, 5, 6, 2, 4, 3, 2, 5 };
	int i;

	Queue * queue = Queue_create(); 

	for(i = 0; i < 8; i++)
	{
		printf("Pushing %d\n", num[i]);
		Queue_enqueue(queue, &num[i]);
	}

	while(Queue_getLength(queue) > 0)
	{
		int num = *(int *)Queue_dequeue(queue);

		printf("Popping %d\n", num);
	}

	Queue_destroy(queue);

	return 0;
}