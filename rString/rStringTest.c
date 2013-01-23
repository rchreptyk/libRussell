#include "rString.h"
#include <stdio.h>

int main()
{
	String * string;

	string = String_create("3242.34234");

	if(String_containsNonNumeric(string))
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}

	String_destroy(string);

	return 0;
}