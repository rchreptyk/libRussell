#include "Stack.h"
#include "List.h"

struct stackStruct {
	List * list;
}

Stack * Stack_create()
{
	Stack * queue = malloc(sizeof(Stack));
	if(stack == NULL)
		return NULL;

	stack->list = List_create();
	if(stack->list == NULL)
	{
		free(stack);
		return NULL;
	}

	return stack;
}

Boolean Stack_destroy(Stack * stack)
{
	List * list = stack->list;
	free(stack);
	return List_destroy(list);
}