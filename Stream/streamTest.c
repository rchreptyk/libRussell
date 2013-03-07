#include "Stream.h"
#include <stdio.h>

int main()
{
	String * filename = String_create("test.txt");
	Stream * stream = Stream_openFile(filename, Open, ReadOnly);

	if(stream == NULL)
	{
		printf("Failed to open file\n");
	}

	String_destroy(filename);

	String * line = Stream_nextLine(stream);

	printf("%s\n", String_c(line));

	String_destroy(line);

	int i;
	for(i = 0; i < 3; i++)
	{
		printf("%d, ", Stream_nextInt(stream, NULL));
	}

	Stream_close(stream);

	return 0;
}