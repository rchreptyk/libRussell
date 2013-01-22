#include "rString.h"
#include <stdio.h>

int main()
{
	String * string, *del, *tmpString;
	List * result;
	ListIterator * iterator;

	string = String_create("Russell&Melissa&Sex");
	del = String_create("&");

	result = String_split(string, del);
	iterator = ListIterator_create(result);
	tmpString = ListIterator_removeCurrent(iterator);

	while(tmpString != NULL)
	{
		printf("%s\n", String_c(tmpString));
		String_destroy(tmpString);
		tmpString = ListIterator_removeCurrent(iterator);
	}

	List_destroy(result);
	ListIterator_destroy(iterator);
	String_destroy(string);
	String_destroy(del);

	return 0;
}