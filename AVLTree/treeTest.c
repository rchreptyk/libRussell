#include "AVLTree.h"
#include <stdio.h>

int compareInt(void * data, void * data2)
{
	return *(int*)data - *(int*)data2;
}

int main()
{

	AVLTree * tree = AVLTree_create(compareInt);

	int ints[] = { 6, 47, 13, 19, 18, 22, 55, 92, 44, 33 };

	int i;
	for(i = 0; i < 10; i++)
	{
		printf("%d\n", AVLTree_insert(tree, &ints[i]));
	}

	printf("Num of nodes: %d", AVLTree_getNumNodes(tree));

	AVLTree_destroy(tree);
	return 0;
}