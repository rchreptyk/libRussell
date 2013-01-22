#include <stdio.h>
#include "List.h"

char * mallocChar(char c)
{
	char * ch = malloc(sizeof(char));
	*ch = c;
	return ch;
}

int isEqual(void * ch, void * ch2)
{
	return *(char*)ch == *(char*)ch2;
}

int main()
{
	List * list = List_create();
	List * list2 = List_create();

	List_addBack(list, mallocChar('a'));
	List_addBack(list, mallocChar('b'));
	List_addBack(list, mallocChar('c'));
	List_addBack(list, mallocChar('e'));

	List_addBack(list2, mallocChar('b'));
	List_addBack(list2, mallocChar('c'));
	List_addBack(list2, mallocChar('e'));

	printf("%d\n", List_positionOfSubList(list, list2, isEqual));

	List_destroyListAndData(list, free);
	List_destroyListAndData(list2, free);
}
