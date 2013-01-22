#ifndef String_ADT
#define String_ADT

#include <List.h>
#include <ctype.h>
#include <stdlib.h>

/******************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************/

struct rStringStruct;
typedef struct rStringStruct rString;

rString * rString_create(char *);

rString * rString_createEmpty();

Boolean rString_destroy(rString *);

/*******************************************************************
 * OPERATIONS
 ******************************************************************/

rString * rString_copy(rString *);

Boolean rString_append(rString *, rString *);

Boolean rString_appendChar(rString *, char);

rString * rString_concat(rString *, rString *);

List * rString_split(rString *, rString *);

rString * rString_join();

List * rString_contains(rString *, rString *);

rString * rString_toLowerCase(rString *);

rString * rString_toUpperCase(rString *);

rString * rString_trim(rString *);

/*******************************************************************
* COMPARISIONS
******************************************************************/

Boolean rString_equals(rString *, rString *);

Boolean rString_equalsIgnoreCase(rString *, rString *);

/*******************************************************************
* PROPERTIES
******************************************************************/

int rString_getLength(rString *);

int rString_indexOf(rString *, rString *);

char rString_charAt(rString *, int);

/*******************************************************************
* COVERTIONS
******************************************************************/

char * rString_c(rString *);

int rString_convertInt(rString *);

double rString_convertDouble(rString *);

#endif

