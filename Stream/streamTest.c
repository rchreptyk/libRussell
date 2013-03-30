#include "Stream.h"
#include "rString.h"
#include <stdio.h>

int main()
{
	Stream * stream = Stream_openStdin();
	Stream * out = Stream_openStdout();
	String * line;

	while((line = Stream_nextWord(stream)))
	{
		Stream_printf(out, "%r\n", line);
	}

	return 0;
}