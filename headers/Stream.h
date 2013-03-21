#ifndef Stream_ADT
#define Stream_ADT

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "rString.h"
#include "Boolean.h"

struct streamStruct;
typedef struct streamStruct Stream;

typedef enum { Open, Create, CreateNew, Append } StreamMode;
typedef enum { ReadOnly, WriteOnly, ReadWrite} AccessMode;

/* Constructors */

Stream * Stream_openFile(String * filename, StreamMode streamMode, AccessMode accessMode);

Stream * Stream_openStdin();

Boolean Stream_close(Stream * stream);

/* Reading */

char Stream_nextChar(Stream * stream);

String * Stream_nextLine(Stream * stream);

int Stream_nextInt(Stream * stream, Boolean * error); 

/* Writing */

// Boolean Stream_writeLine(Stream * stream, String * line);

// Boolean Stream_write(Stream * stream, String * string);

/* Properties */

Boolean Stream_fileExists(String * filename);

#endif