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

void * String_copyVoid(void *);

/* Adding */

Boolean String_append(String *, String *);

Boolean String_SappendC(String * string, char * string2);

Boolean String_appendChar(String *, char);

/* Multi String */

String * String_concat(String *, String *);

String * String_SconcatC(String * first, char * string);

String * String_CconcatS(char * first, String * second);

List * String_split(String *, String *);

List * String_SsplitC(String * string, char * delimiter);

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

String * String_CreplaceC(String * string, char * search, char * replace);

String * String_SreplaceC(String * string, String * search, char * replace);

String * String_CreplaceS(String * string, char * search, String * replace);

/*******************************************************************
* COMPARISIONS
******************************************************************/

Boolean String_equals(String *, String *);

Boolean String_SequalsC(String * string, char * string2);

Boolean String_equalsIgnoreCase(String *, String *);

Boolean String_SequalsIgnoreCaseC(String * string, char * string2);

/*******************************************************************
* PROPERTIES
******************************************************************/

int String_getLength(String *);

int String_indexOf(String *, String *);

int String_numOccurances(String *, String *);

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

String * String_fromInt(int integer);

String * String_fromDouble(double aDouble);

String * String_listToString(List *, String * (*toString)(void *));

String * String_voidToString(void * v);

/*******************************************************************
* CHARACTER LISTS
******************************************************************/

List * String_toCharList(String *);

void * String_copyCharacter(void * ch);

#endif

