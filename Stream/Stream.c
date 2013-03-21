
#include "Stream.h"

struct streamStruct {
	FILE * stream;

	Boolean canRead;
	Boolean canWrite;
	Boolean canSeek;
};

Stream * Stream_openFile(String * filename, StreamMode streamMode, AccessMode accessMode)
{
	if(filename == NULL)
		return NULL;


	if(streamMode == CreateNew && Stream_fileExists(filename))
	{
		return NULL;
	}


	char * mode = NULL;

	if(streamMode == Open)
	{
		if(accessMode == ReadOnly)
		{
			mode = "r";
		}
		else if(accessMode == ReadWrite)
		{
			mode = "r+";
		}
		else
		{
			return NULL;
		}

	}

	if(streamMode == Create)
	{
		if(accessMode == WriteOnly)
		{
			mode = "w";
		}
		else if(accessMode == ReadWrite)
		{
			mode = "w+";
		}
		else
		{
			return NULL;
		}
	}

	if(streamMode == CreateNew)
	{
		if(accessMode == WriteOnly)
		{
			mode = "w";
		}
		else if(accessMode == ReadWrite)
		{
			mode = "w+";
		}
		else
		{
			return NULL;
		}
	}

	if(streamMode == Append)
	{
		if(accessMode == WriteOnly)
		{
			mode = "a";
		}
		else if(accessMode == ReadWrite)
		{
			mode = "a+";
		}
		else
		{
			return NULL;
		}
	}

	if(mode == NULL)
		return NULL;

	FILE * fstream = fopen(String_c(filename), mode);

	if(fstream == NULL)
		return NULL;

	Stream * stream = malloc(sizeof(Stream));

	if(stream == NULL)
		return NULL;

	stream->stream = fstream;
	stream->canSeek = true;
	stream->canWrite = accessMode == WriteOnly || accessMode == ReadWrite;
	stream->canRead = accessMode == ReadOnly || accessMode == ReadWrite;

	return stream;
}

Stream * Stream_openStdin()
{
	Stream * stream = malloc(sizeof(Stream));

	stream->stream = stdin;
	stream->canSeek = false;
	stream->canWrite = false;
	stream->canRead = true;
	
	return stream;
}

Boolean Stream_close(Stream * stream)
{
	fclose(stream->stream);
	free(stream);

	return true;
}

char Stream_nextChar(Stream * stream)
{
	if(stream == NULL)
		return EOF;

	if(!stream->canRead)
		return EOF;

	return fgetc(stream->stream);
}

String * Stream_nextLine(Stream * stream)
{
	if(stream == NULL || !stream->canRead)
		return NULL;

	String * line = String_createEmpty();

	char currentChar;
	while((currentChar = fgetc(stream->stream)) != '\n' && currentChar != EOF)
	{
		String_appendChar(line, currentChar);
	}

	return line;
}

int Stream_nextInt(Stream * stream, Boolean * error)
{
	if(stream == NULL || !stream->canRead)
	{
		if(error != NULL)
			*error = true;
		return 0;
	}

	String * integer = String_createEmpty();

	char currentChar;
	while((currentChar = fgetc(stream->stream)) != EOF && !isdigit(currentChar));

	if(currentChar == EOF)
	{
		if(error != NULL)
			*error = true;
		return 0;
	}

	String_appendChar(integer, currentChar);

	while((currentChar = fgetc(stream->stream)) != EOF && isdigit(currentChar))
	{
		String_appendChar(integer, currentChar);
	}

	if(error != NULL)
		*error = false;

	int realInt = String_convertInt(integer);

	String_destroy(integer);

	return realInt;
}

// Boolean Stream_writeLine(String * stream, String * line)
// {
// 	if(stream == NULL || line == NULL)
// 		return false;


// }

// Boolean Stream_write(Stream * stream, String * string)
// {
// 	if(stream == NULL || string == NULL)
// 		return false;
// }

Boolean Stream_fileExists(String * filename)
{
	if(filename == NULL)
		return false;

	FILE * test = fopen(String_c(filename), "r");

	if(test != NULL)
	{
		fclose(test);

		return true;
	}

	return false;
}
