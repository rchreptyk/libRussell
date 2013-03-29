
#include "Stream.h"

#include <string.h>

struct streamStruct {
	FILE * stream;

	Boolean canRead;
	Boolean canWrite;
	Boolean canSeek;
};

Stream * Stream_openFile(String * filename, StreamMode streamMode, AccessMode accessMode)
{
	FILE * fstream;
	Stream * stream;

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

	fstream = fopen(String_c(filename), mode);

	if(fstream == NULL)
		return NULL;

	stream = malloc(sizeof(Stream));

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
	Stream * stream;

	stream = malloc(sizeof(Stream));

	if(stream == NULL)
		return NULL;

	stream->stream = stdin;
	stream->canSeek = false;
	stream->canWrite = false;
	stream->canRead = true;
	
	return stream;
}

Stream * Stream_openStdout()
{
	Stream * stream;

	stream = malloc(sizeof(Stream));

	if(stream == NULL)
		return NULL;

	stream->stream = stdout;
	stream->canSeek = false;
	stream->canWrite = true;
	stream->canRead = false;

	return stream;
}

Boolean Stream_close(Stream * stream)
{
	if(stream == NULL)
		return false;

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
	String * line;
	char currentChar;

	if(stream == NULL || !stream->canRead)
		return NULL;

	line = String_createEmpty();
	
	while((currentChar = fgetc(stream->stream)) != '\n' && currentChar != EOF)
	{
		String_appendChar(line, currentChar);
	}

	return line;
}

int Stream_nextInt(Stream * stream, Boolean * error)
{
	String * integer;
	char currentChar;
	int realInt;

	if(stream == NULL || !stream->canRead)
	{
		if(error != NULL)
			*error = true;
		return 0;
	}

	integer = String_createEmpty();

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

	realInt = String_convertInt(integer);

	String_destroy(integer);

	return realInt;
}

double Stream_nextDouble(Stream * stream, Boolean * error)
{
	String * aDouble;
	double realDouble;
	char currentChar;

	if(stream == NULL || !stream->canRead)
	{
		if(error != NULL)
			*error = true;
		return 0.0;
	}

	aDouble = String_createEmpty();

	while((currentChar = fgetc(stream->stream)) != EOF && !isdigit(currentChar));

	if(currentChar == EOF)
	{
		if(error != NULL)
			*error = true;
		return 0.0;
	}

	String_appendChar(aDouble, currentChar);

	while(isdigit(currentChar = fgetc(stream->stream)))
	{
		String_appendChar(aDouble, currentChar);
	}

	if(currentChar == '.')
	{
		String_appendChar(aDouble, currentChar);

		while(isdigit(currentChar = fgetc(stream->stream)))
		{
			String_appendChar(aDouble, currentChar);
		}
	}

	realDouble = String_convertDouble(aDouble);

	String_destroy(aDouble);

	return realDouble;
}

Boolean Stream_writeChar(Stream * stream, char character)
{
	if(stream == NULL || character != EOF || !stream->canWrite)
		return false;

	fputc(character, stream->stream);

	return true;
}

Boolean Stream_writeLineC(Stream * stream, char * line)
{
	if(stream == NULL || line == NULL || !stream->canWrite)
		return false;

	Stream_writeC(stream, line);

	fputc('\n', stream->stream);

	return true;
}

Boolean Stream_writeC(Stream * stream, char * string)
{
	int currentChar;

	if(stream == NULL || string == NULL || !stream->canWrite)
		return false;

	for(currentChar = 0; string[currentChar] != '\0'; currentChar++)
		fputc(string[currentChar], stream->stream);

	return true;
}

Boolean Stream_writeLine(Stream * stream, String * line)
{
	if(stream == NULL || line == NULL)
		return false;

	return Stream_writeLineC(stream, String_c(line));
}

Boolean Stream_write(Stream * stream, String * string)
{
	if(stream == NULL || string == NULL)
		return false;

	return Stream_writeC(stream, String_c(string));
}

Boolean Stream_writeInt(Stream * stream, int integer)
{
	String * string;

	if(stream == NULL || !stream->canWrite)
		return false;
	
	string = String_fromInt(integer);

	if(string == NULL)
		return false;

	return Stream_write(stream, string);
}

Boolean Stream_writeDouble(Stream * stream, double aDouble)
{
	String * string;

	if(stream == NULL || !stream->canWrite)
		return false;

	string = String_fromDouble(aDouble);

	if(string == NULL)
		return false;

	return Stream_write(stream, string);
}

Boolean Stream_printf(Stream * stream, char * format, ... )
{
	int i, length;
	int myInt;
	va_list arguments;

	if(stream == NULL || format == NULL)
		return false;

	va_start(arguments, format);

	length = strlen(format);

	for(i = 0; i < length; i++)
	{
		if(format[i] == '%' && i + 1 < length)
		{
			i++;
			switch(format[i])
			{
				case 'd':
				case 'i':
					myInt =  va_arg(arguments, int);
					printf("%d\n", myInt);
					Stream_writeInt(stream, myInt);
					break;
				case 'f':
					Stream_writeDouble(stream, va_arg(arguments, double));
					break;
				case 's':
					Stream_writeC(stream, va_arg(arguments, char *));
					break;
				case 'c':
					Stream_writeChar(stream, va_arg(arguments, char));
					break;
				case 'r':
					Stream_write(stream, va_arg(arguments, String *));
					break;
				default:
					Stream_writeChar(stream, format[i]);
			}
		}
		else
		{
			fputc(format[i], stream->stream);
		}
	}

	va_end(arguments);

	return true;
}

Boolean Stream_fileExists(String * filename)
{
	FILE * test;

	if(filename == NULL)
		return false;

	test = fopen(String_c(filename), "r");

	if(test != NULL)
	{
		fclose(test);

		return true;
	}

	return false;
}
