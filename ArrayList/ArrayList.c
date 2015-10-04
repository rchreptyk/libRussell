
#include "ArrayList.h"

struct arrayListStruct {
	int length;
	void * array;
	
	size_t defaultSize;
};

static Boolean validateIndex(ArrayList * list, int index);

ArrayList * ArrayList_create(int initialSize, size_t objectSize)
{
	if(initialSize < 1)
		return NULL;

	ArrayList * list = malloc(sizeof(struct arrayListStruct));
	if(list == NULL)
		return NULL;

	list->length = initialSize;
	list->defaultSize = objectSize;
	list->array = calloc(objectSize, initialSize);

	return list;
}

Boolean ArrayList_destroy(ArrayList * list)
{
	if(list == NULL)
		return false;

	free(list->array);
	free(list);

	return true;
}

Boolean ArrayList_set(ArrayList * list, int index, void * value)
{
	if(!validateIndex(list, index))
		return false;

	void * destPoint = list->array + (index * list->defaultSize);
	memcpy(destPoint, value, list->defaultSize);
	return true;
}

Boolean ArrayList_get(ArrayList * list, int index, void * result)
{
	if(index >= list->length)
		return false;

	void * srcPoint = list->array + (index * list->defaultSize);
	memcpy(result, srcPoint, list->defaultSize);
	return true;
}

static Boolean validateIndex(ArrayList * list, int index)
{
	if(index < list->length)
	{
		return true;
	}

	int newLength = list->length * 2;
	while(index >= newLength)
		newLength *= 2;

	void * newArray = calloc(list->defaultSize, newLength);
	if(newArray == NULL)
		return false;

	memcpy(newArray, list->array, list->defaultSize * newLength);

	free(list->array);
	list->length = newLength;
	list->array = newArray;

	return true;
}
