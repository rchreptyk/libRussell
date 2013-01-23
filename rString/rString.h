#ifndef String_ADT
#define String_ADT

#include "List.h"
#include "Boolean.h"
#include <ctype.h>

/******************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************/

struct stringStruct;
typedef struct stringStruct String;

String * String_create(char *);

String * String_createEmpty();

Boolean String_destroy(String *);

void String_destroyVoidString(void *);

/*******************************************************************
 * OPERATIONS
 ******************************************************************/

String * String_copy(String *);

/* Adding */

Boolean String_append(String *, String *);

Boolean String_appendChar(String *, char);

/* Multi String */

String * String_concat(String *, String *);

List * String_split(String *, String *);

String * String_join(List *, String *);

/* String Mutations */

String * String_toLowerCase(String *);

String * String_toUpperCase(String *);

String * String_toUpperWords(String *);

String * String_toUpperFirst(String *);

String * String_trim(String *);

String * String_stripSpace(String *);

String * String_stripChars(String *, List *);

String * String_stripNonAlpha(String *);

String * String_stripNonDigit(String *);

String * String_stripNonNumeric(String *);

String * String_stripNonAlphaNumeric(String *);

String * String_stripMatching(String *, int isEqual(int));

String * String_stripNotMatching(String * string, int (*isEqual)(int));

String * String_replace(String *, String *, String *);

/*******************************************************************
* COMPARISIONS
******************************************************************/

Boolean String_equals(String *, String *);

Boolean String_equalsIgnoreCase(String *, String *);

/*******************************************************************
* PROPERTIES
******************************************************************/

int String_getLength(String *);

int String_indexOf(String *, String *);

char String_charAt(String *, int);

Boolean String_containsSpace(String *);

Boolean String_containsChars(String *, List *);

Boolean String_containsNonAlpha(String *);

Boolean String_containsNonDigit(String *);

Boolean String_containsNonNumeric(String *);

Boolean String_containsNonAlphaNumeric(String *);

Boolean String_containsMatching(String *, int (*isEqual)(int));

Boolean String_containsNotMatching(String * string, int (*isEqual)(int));

/*******************************************************************
* COVERTIONS
******************************************************************/

char * String_c(String *);

int String_convertInt(String *);

double String_convertDouble(String *);

String * String_listToString(List *, String * (*toString)(void *));

List * String_toCharList(String *);

String * String_voidToString(void * v);

#endif

