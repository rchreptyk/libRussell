#include "rString.h"

struct rStringStruct
{
	List * characters;
	char * cString;
};

static int cStringLength(char *);
static void * copyCharacter(void * ch);

static int compareCaseSensitive(void * v1, void * v2);
static rString * stringFromList(List * list);

/* Constructors and Destructors */

rString * rString_create(char * cStr)
{
	rString * string;
	List * characters;
	int i = 0;
	int length;

	if(cStr == NULL)
		return NULL;

	characters = List_create();
	if(characters == NULL)
		return NULL;

	string = malloc(sizeof(rString));
	if(string == NULL)
		return NULL;

	string->characters = characters;
	string->cString = NULL;
	length = cStringLength(cStr);

	for(i = 0; i < length; i++)
	{
		if(!List_addBack(string->characters, copyCharacter(&cStr[i])))
		{
			rString_destroy(string);
			return NULL;
		}
	}

	return string;
}

rString * rString_createEmpty()
{
	return rString_create("");
}

Boolean rString_destroy(rString * string)
{
	if(string == NULL)
		return false;

	if(string->characters == NULL)
		return false;

	if(!List_destroyListAndData(string->characters, free))
		return false;

	if(string->cString != NULL)
		free(string->cString);

	string->characters = NULL;
	string->cString = NULL;

	free(string);

	return true;
}

/* Operations */

rString * rString_copy(rString * string)
{
	rString *newString;
	List * characters;

	if(string == NULL)
		return NULL;

	if(string->characters == NULL)
		return NULL;

	characters = List_copy(string->characters, copyCharacter);

	if(characters == NULL)
		return NULL;

	newString = malloc(sizeof(rString));
	if(newString == NULL)
		return NULL;

	newString->cString = NULL;
	newString->characters = characters;

	return newString;
}

Boolean rString_append(rString * string, rString * stringToAppend)
{
	List * appendedCharacters, * tmpAppendedCharacters;

	if(string == NULL || stringToAppend == NULL)
		return false;

	tmpAppendedCharacters = List_appendList(string->characters, stringToAppend->characters);
	if(tmpAppendedCharacters == NULL)
		return false;

	appendedCharacters = List_copy(tmpAppendedCharacters, copyCharacter);
	List_destroy(tmpAppendedCharacters);
	if(appendedCharacters == NULL)
		return false;

	List_destroyListAndData(string->characters, free);
	string->characters = appendedCharacters;

	return true;
}

Boolean rString_appendChar(rString * string, char ch)
{
	if(string == NULL)
		return false;

	if(string->characters == NULL)
		return false;

	return List_addBack(string->characters, copyCharacter(&ch));
}

rString * rString_concat(rString * first, rString * second)
{
	rString * newString;

	if(first == NULL || second == NULL)
		return NULL;

	if(first->characters == NULL || second->characters == NULL)
		return NULL;

	newString = rString_copy(first);

	if(!rString_append(newString, second))
	{
		rString_destroy(newString);
		return NULL;
	}

	if(newString == NULL)
		return NULL;

	return newString;
}

List * rString_split(rString * string, rString * delimiter)
{
	List * splitList;
	List * currentSubList;
	List * subString;
	int currentPosition;
	int length;

	if(string == NULL || delimiter == NULL)
		return NULL;

	if(string->characters == NULL || string->characters == NULL)
		return NULL;

	currentPosition = 0;
	length = rString_getLength(string);
	currentSubList = List_clone(string->characters);
	splitList = List_create();

	if(splitList == NULL)
		return NULL;

	currentPosition = List_positionOfSubList(currentSubList, delimiter->characters, compareCaseSensitive);
	while(currentPosition != -1)
	{
		int endLocation = currentPosition - 1;

		if(endLocation >= 0)
		{
			subString = List_getRange(currentSubList, 0, endLocation);
			List_addBack(splitList, stringFromList(subString));
			List_destroy(currentSubList);
			currentSubList = List_getRange(currentSubList, currentPosition, List_getLength(currentSubList) - 1);
		}

		currentPosition = List_positionOfSubList(currentSubList, delimiter->characters, compareCaseSensitive);
	}

	if(List_getLength(currentSubList) != 0)
		List_addBack(splitList, stringFromList(currentSubList));

	List_destroy(currentSubList);

	return splitList;
}

/* Properties */

int rString_getLength(rString * string)
{
	if(string == NULL)
		return -1;

	if(string->characters == NULL)
		return -1;

	return List_getLength(string->characters);
}

/* Convertions */

char * rString_c(rString * string)
{
	char * cString = NULL;
	int length;
	int i;
	ListIterator * iterator;
	void * data;

	if(string == NULL)
		return NULL;

	if(string->characters == NULL)
		return NULL;

	length = rString_getLength(string);
	if(length < 0)
		return NULL;

	cString = malloc(sizeof(char) * (length + 1));
	
	iterator = ListIterator_create(string->characters);

	i = 0;
	data = ListIterator_seekToFirst(iterator);

	while(data != NULL)
	{
		cString[i] = *(char*)data;
		data = ListIterator_nextItem(iterator);
		i++;
	}

	cString[length] = '\0';

	ListIterator_destroy(iterator);

	string->cString = cString;

	return cString;
}

/* Internal Functions */
/* DO NOT USE */

static int cStringLength(char * cStr)
{
	int i;

	for(i = 0; cStr[i] != '\0'; i++);

	return i;
}

static void * copyCharacter(void * ch)
{
	char * newCh = malloc(sizeof(char));
	*newCh = *(char *)ch;
	return newCh;
}

static int compareCaseSensitive(void * v1, void * v2)
{
	return *(char*)v1 == *(char*)v2;
}

static rString * stringFromList(List * list)
{
	rString * string = malloc(sizeof(rString));
	if(string == NULL)
		return NULL;

	string->characters = List_copy(list, copyCharacter);
	string->cString = NULL;
	return string;
}