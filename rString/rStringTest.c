#include "rString.h"
#include <stdio.h>

int main()
{
	String * string;

	string = String_create("3242443");
	printf("%d\n", String_convertInt(string));;

	String_destroy(string);

	return 0;
}