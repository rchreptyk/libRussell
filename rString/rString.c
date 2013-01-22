#include "rString.h"

struct stringStruct
{
	List * characters;
	char * cString;
};

static int cStringLength(char *);
static void * copyCharacter(void * ch);

static int compareCaseSensitive(void * v1, void * v2);
static String * stringFromList(List * list);


/*static String * characterListToString(void * ch);
static String * voidToString(void * v);*/

/* Constructors and Destructors */

String * String_create(char * cStr)
{
	String * string;
	List * characters;
	int i = 0;
	int length;

	if(cStr == NULL)
		return NULL;

	characters = List_create();
	if(characters == NULL)
		return NULL;

	string = malloc(sizeof(String));
	if(string == NULL)
		return NULL;

	string->characters = characters;
	string->cString = NULL;
	length = cStringLength(cStr);

	for(i = 0; i < length; i++)
	{
		if(!List_addBack(string->characters, copyCharacter(&cStr[i])))
		{
			String_destroy(string);
			return NULL;
		}
	}

	return string;
}

String * String_createEmpty()
{
	return String_create("");
}

Boolean String_destroy(String * string)
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

String * String_copy(String * string)
{
	String *newString;
	List * characters;

	if(string == NULL)
		return NULL;

	if(string->characters == NULL)
		return NULL;

	characters = List_copy(string->characters, copyCharacter);

	if(characters == NULL)
		return NULL;

	newString = malloc(sizeof(String));
	if(newString == NULL)
		return NULL;

	newString->cString = NULL;
	newString->characters = characters;

	return newString;
}

Boolean String_append(String * string, String * stringToAppend)
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

Boolean String_appendChar(String * string, char ch)
{
	if(string == NULL)
		return false;

	if(string->characters == NULL)
		return false;

	return List_addBack(string->characters, copyCharacter(&ch));
}

String * String_concat(String * first, String * second)
{
	String * newString;

	if(first == NULL || second == NULL)
		return NULL;

	if(first->characters == NULL || second->characters == NULL)
		return NULL;

	newString = String_copy(first);

	if(!String_append(newString, second))
	{
		String_destroy(newString);
		return NULL;
	}

	if(newString == NULL)
		return NULL;

	return newString;
}

List * String_split(String * string, String * delimiter)
{
	List * splitList;
	List * currentSubList;
	List * subString;
	List * tmpList;
	int delimiterLocation;
	int delimiterLength;
	int length;

	if(string == NULL || delimiter == NULL)
		return NULL;

	if(string->characters == NULL || string->characters == NULL)
		return NULL;

	/*Stores the current section of the string we are searching*/
	currentSubList = List_clone(string->characters);

	delimiterLength = String_getLength(delimiter);

	splitList = List_create();

	if(splitList == NULL)
		return NULL;

	delimiterLocation = List_positionOfSubList(currentSubList, delimiter->characters, compareCaseSensitive);

	while(delimiterLocation != -1)
	{
		int indexAfterDelimiter;
		int indexBeforeDelimiter = delimiterLocation - 1;

		length = List_getLength(currentSubList);

		/* Have valid string before delimiter */
		if(indexBeforeDelimiter >= 0)
		{
			/* Fetch the string before the delimiter */
			subString = List_getRange(currentSubList, 0, indexBeforeDelimiter);
			/*Store the found string in our list of split strings*/
			List_addBack(splitList, stringFromList(subString));
			List_destroy(subString);

		}

		indexAfterDelimiter = delimiterLocation + delimiterLength;

		if(indexAfterDelimiter < (length - 1))
		{
			tmpList = List_getRange(currentSubList, indexAfterDelimiter, length - 1);
			List_destroy(currentSubList);
			currentSubList = tmpList;
		}
		else /* Special Case: String ends with the delimiter */
		{
			List_destroy(currentSubList);
			/* The next sublist is empty because there is no more substring */
			currentSubList = List_create();
			break;
		}

		delimiterLocation = List_positionOfSubList(currentSubList, delimiter->characters, compareCaseSensitive);
	}

	/* There are no more delimiters, so the rest of the string must be added to the list */
	if(List_getLength(currentSubList) != 0)
		List_addBack(splitList, stringFromList(currentSubList));

	List_destroy(currentSubList);

	return splitList;
}

/* Properties */

int String_getLength(String * string)
{
	if(string == NULL)
		return -1;

	if(string->characters == NULL)
		return -1;

	return List_getLength(string->characters);
}

int String_indexOf(String * string, String * substring)
{
	if(string == NULL || substring == NULL)
		return -1;

	return List_positionOfSubList(string->characters, substring->characters, compareCaseSensitive);
}

/* Convertions */

char * String_c(String * string)
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

	length = String_getLength(string);
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

String * String_listToString(List * list, String * (*toString)(void *))
{
	String * string;
	String * comma;
	String * toStringReturn;
	String * endBracket;
	ListIterator * iterator;
	void * data;
	Boolean first;

	string = String_create("{");
	comma = String_create(", ");

	iterator = ListIterator_create(list);
	data = ListIterator_seekToFirst(iterator);
	first = true;

	while(data != NULL)
	{
		if(!first)
			String_append(string, comma);
		else
			first = false;

		toStringReturn = toString(data);
		if(toStringReturn != NULL)
		{
			String_append(string, toStringReturn);
			String_destroy(toStringReturn);
		}

		data = ListIterator_nextItem(iterator);
	}

	String_destroy(comma);
	endBracket = String_create("}");
	String_append(string, endBracket);
	String_destroy(endBracket);
	ListIterator_destroy(iterator);

	return string;

}

/* Internal Functions */
/* DO NOT USE */

/*static String * characterListToString(void * ch)
{
	String * string = String_createEmpty();
	String_appendChar(string, *(char*)ch);
	return string;
}

static String * voidToString(void * v)
{
	return (String *)v;
}*/

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

static String * stringFromList(List * list)
{
	String * string = malloc(sizeof(String));
	if(string == NULL)
		return NULL;

	string->characters = List_copy(list, copyCharacter);
	string->cString = NULL;
	return string;
}