#ifndef Stream_ADT
#define Stream_ADT

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "rString.h"
#include "Boolean.h"

struct streamStruct;
typedef struct streamStruct Stream;

typedef enum { Open, Create, CreateNew, Append } StreamMode;
typedef enum { ReadOnly, WriteOnly, ReadWrite} AccessMode;

/* Constructors */

Stream * Stream_openFile(String * filename, StreamMode streamMode, AccessMode accessMode);

Stream * Stream_openStdin();

Stream * Stream_openStdout();

Boolean Stream_close(Stream * stream);

/* Reading */

char Stream_nextChar(Stream * stream);

String * Stream_nextWord(Stream * stream);

String * Stream_nextLine(Stream * stream);

int Stream_nextInt(Stream * stream, Boolean * error); 

double Stream_nextDouble(Stream * stream, Boolean * error);

/* Writing */

Boolean Stream_writeChar(Stream * stream, char character);

Boolean Stream_writeLineC(Stream * stream, char * line);

Boolean Stream_writeC(Stream * stream, char * string);

Boolean Stream_writeLine(Stream * stream, String * line);

Boolean Stream_write(Stream * stream, String * string);

Boolean Stream_writeInt(Stream * stream, int integer);

Boolean Stream_writeDouble(Stream * stream, double aDouble);

Boolean Stream_printf(Stream * stream, char * format, ... );

/* Properties */

Boolean Stream_fileExists(String * filename);

#endif
