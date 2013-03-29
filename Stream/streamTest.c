#include "Stream.h"
#include "rString.h"
#include <stdio.h>

int main()
{
	Stream * stream = Stream_openStdout();

	String * myString = String_create("Hellooo");

	Stream_printf(stream, "Hello %r %d %f Bla.\n", myString, 2423, 34.34);

	return 0;
}