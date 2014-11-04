
#include "ArrayList.h"
#include <assert.h>

int main()
{
	int numbers[10] = { 1,2,3,4,5,6,7,8,9,10 };

	ArrayList * list = ArrayList_create(5, sizeof(int));
	assert(ArrayList_set(list, 2, &numbers[2]));

	int result;
	ArrayList_get(list, 2, &result);
	assert(numbers[2] == result);

	assert(ArrayList_get(list, 5, &result) == false);
	
	assert(ArrayList_set(list, 7, &numbers[6]));

	ArrayList_get(list, 2, &result);
	assert(numbers[2] == result);

	ArrayList_get(list, 7, &result);
	assert(numbers[6] == result);

	int i;
	for(i = 0; i < 10; i++)
	{
		ArrayList_set(list, i + 30, &numbers[i]);
	}

	for(i = 0; i < 10; i++)
	{
		ArrayList_get(list, i + 30, &result);
		assert(numbers[i] == result);
	}

	ArrayList_get(list, 2, &result);
	assert(numbers[2] == result);

	ArrayList_get(list, 7, &result);
	assert(numbers[6] == result);

	ArrayList_destroy(list);
	return 0;
}