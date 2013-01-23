#include "rString.h"

struct stringStruct
{
	List * characters;
	char * cString;
};

static int cStringLength(char *);
static void * copyCharacter(void * ch);

static int compareCaseSensitive(void * v1, void * v2);
static int compareCaseInsensitive(void * v1, void * v2);

static String * stringFromList(List * list);

static int pointerIsSpace(void * data);
static int pointerIsAlpha(void * data);
static int pointerIsDigit(void * data);
static int pointerIsNumeric(void * data);
static int pointerIsAlphaNumeric(void * data);

static int isNumeric(int ch);

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

void String_destroyVoidString(void * data)
{
	String_destroy((String *) data);
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

String * String_join(List * stringList, String * del)
{
	String * currentString;
	String * newString;
	ListIterator * iterator;
	Boolean first;

	if(stringList == NULL)
		return NULL;

	iterator = ListIterator_create(stringList);
	if(iterator == NULL)
		return NULL;

	newString = String_createEmpty();
	if(newString == NULL)
		return NULL;

	first = true;

	currentString = ListIterator_seekToFirst(iterator);
	while(currentString != NULL)
	{
		if(!first && del != NULL)
		{
			String_append(newString, del);
		}

		String_append(newString, currentString);

		first = false;
		currentString = ListIterator_nextItem(iterator);
	}

	ListIterator_destroy(iterator);

	return newString;
}

String * String_toLowerCase(String * string)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		*character = tolower(*character);
		character = ListIterator_nextItem(iterator);
	}

	ListIterator_destroy(iterator);
	return newString;
}

String * String_toUpperCase(String * string)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		*character = toupper(*character);
		character = ListIterator_nextItem(iterator);
	}

	ListIterator_destroy(iterator);
	return newString;
}

String * String_toUpperWords(String * string)
{
	String * newString;
	ListIterator * iterator;
	char * character;
	Boolean upperNext;

	if(string == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);
	upperNext = true;

	upperNext = true;
	while(character != NULL)
	{
		if(upperNext && isalpha(*character))
		{
			*character = toupper(*character);
			upperNext = false;
		}
		
		if(isspace(*character))
			upperNext = true;

		character = ListIterator_nextItem(iterator);
	}

	ListIterator_destroy(iterator);
	return newString;
}

String * String_trim(String * string)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL && isspace(*character))
	{
		ListIterator_removeCurrent(iterator);
		free(character);
		character = ListIterator_currentValue(iterator);
	}

	character = ListIterator_seekToLast(iterator);
	while(character != NULL && isspace(*character))
	{
		ListIterator_removeCurrent(iterator);
		free(character);
		character = ListIterator_currentValue(iterator);
	}

	ListIterator_destroy(iterator);

	return newString;
}

String * String_stripSpace(String * string)
{
	return String_stripMatching(string, isspace);
}

String * String_stripChars(String * string, List * chars)
{
	String * newString;
	ListIterator * iterator;
	char * character;

	if(string == NULL || chars == NULL)
		return NULL;

	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		if(List_containsMatchedData(chars, character, compareCaseSensitive))
		{
			ListIterator_removeCurrent(iterator);
			free(character);
			character = ListIterator_currentValue(iterator);
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return newString;
}

String * String_stripNonAlpha(String * string)
{
	return String_stripNotMatching(string, isalpha);
}

String * String_stripNonDigit(String * string)
{
	return String_stripNotMatching(string, isdigit);
}

String * String_stripNonNumeric(String * string)
{
	return String_stripNotMatching(string, isNumeric);
}

String * String_stripNonAlphaNumeric(String * string)
{
	return String_stripNotMatching(string, isalnum);
}

String * String_stripMatching(String * string, int (*isEqual)(int))
{
	String * newString;
	ListIterator * iterator;
	char * character;
	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		if(isEqual(*character))
		{
			ListIterator_removeCurrent(iterator);
			free(character);
			character = ListIterator_currentValue(iterator);
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return newString;
}

String * String_stripNotMatching(String * string, int (*isEqual)(int))
{
	String * newString;
	ListIterator * iterator;
	char * character;
	newString = String_copy(string);
	iterator = ListIterator_create(newString->characters);
	character = ListIterator_seekToFirst(iterator);

	while(character != NULL)
	{
		if(!isEqual(*character))
		{
			ListIterator_removeCurrent(iterator);
			free(character);
			character = ListIterator_currentValue(iterator);
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return newString;
}

String * String_replace(String * string, String * search, String * replace)
{
	int offset;
	int replacePosition;
	String * newString;

	if(string == NULL || replace == NULL || search == NULL)
		return NULL;

	newString = String_copy(string);
	if(newString == NULL)
		return NULL;

	offset = 0;

	while((replacePosition = List_positionOfSubListOffset(newString->characters, search->characters, compareCaseSensitive, offset)) != -1)
	{
		List * removed;
		List * copy;
		List * merged;

		removed = List_removeRange(newString->characters, replacePosition, replacePosition + String_getLength(search) - 1);
		List_destroyListAndData(removed, free);

		copy = List_copy(replace->characters, copyCharacter);
		merged = List_insertList(newString->characters, replacePosition, copy);

		List_destroy(newString->characters);
		newString->characters = merged;
		List_destroy(copy);

		offset = replacePosition + String_getLength(replace);
	}

	return newString;
}

/* Comparisions */

Boolean String_equals(String * string, String * string2)
{
	if(string == NULL && string == NULL)
		return true;

	if(string == NULL || string2 == NULL)
		return false;

	return List_isEqual(string->characters, string2->characters, compareCaseSensitive);
}

Boolean String_equalsIgnoreCase(String * string, String * string2)
{
	if(string == NULL && string == NULL)
		return true;

	if(string == NULL || string2 == NULL)
		return false;

	return List_isEqual(string->characters, string2->characters, compareCaseInsensitive);
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

char String_charAt(String * string, int position)
{
	char * val;

	if(string == NULL)
		return '\0';

	if(position < 0 || position >= String_getLength(string))
		return '\0';

	val = List_getValueAtPosition(string->characters, position);

	return (val == NULL) ? '\0' : *val;
}

Boolean String_containsSpace(String * string)
{
	if(string == NULL)
		return false;

	return List_containsInvalidData(string->characters, pointerIsSpace);
}

Boolean String_containsChars(String * string, List * chars)
{
	ListIterator * iterator;
	char * character;
	Boolean contains;

	if(string == NULL || chars == NULL)
		return false;

	iterator = ListIterator_create(string->characters);
	character = ListIterator_seekToFirst(iterator);

	contains = false;
	while(character != NULL)
	{
		if(List_containsMatchedData(chars, character, compareCaseSensitive))
		{
			contains = true;
			break;
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return contains;
}

Boolean String_containsNonAlpha(String * string)
{
	if(string == NULL)
		return false;

	return List_containsInvalidData(string->characters, pointerIsAlpha);
}

Boolean String_containsNonDigit(String * string)
{
	if(string == NULL)
		return false;

	return List_containsInvalidData(string->characters, pointerIsDigit);
}

Boolean String_containsNonNumeric(String * string)
{
	if(string == NULL)
		return false;

	return List_containsInvalidData(string->characters, pointerIsNumeric);
}

Boolean String_containsNonAlphaNumeric(String * string)
{
	if(string == NULL)
		return false;

	return List_containsInvalidData(string->characters, pointerIsAlphaNumeric);
}

Boolean String_containsMatching(String * string, int (*isEqual)(int))
{
	Boolean contains;
	ListIterator * iterator;
	char * character;
	iterator = ListIterator_create(string->characters);
	character = ListIterator_seekToFirst(iterator);

	contains = false;
	while(character != NULL)
	{
		if(isEqual(*character))
		{
			contains = true;
			break;
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return contains;
}

Boolean String_containsNotMatching(String * string, int (*isEqual)(int))
{
	Boolean contains;
	ListIterator * iterator;
	char * character;
	iterator = ListIterator_create(string->characters);
	character = ListIterator_seekToFirst(iterator);

	contains = false;
	while(character != NULL)
	{
		if(!isEqual(*character))
		{
			contains = true;
		}
		else
		{
			character = ListIterator_nextItem(iterator);
		}
	}

	ListIterator_destroy(iterator);

	return contains;
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

	if(cString != NULL)
		free(cString);

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

int String_convertInt(String * string)
{
	if(string == NULL)
		return 0;

	return atoi(String_c(string));
}

double String_convertDouble(String * string)
{
	if(string == NULL)
		return 0;

	return atof(String_c(string));
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

	if(list == NULL || toString == NULL)
		return NULL;

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

List * String_toCharList(String * string)
{
	List * list;
	
	if(string == NULL)
		return NULL;

	list = List_copy(string->characters, copyCharacter);
	return list;
}

String * String_voidToString(void * v)
{
	return (String *)v;
}

/* Internal Functions */
/* DO NOT USE */

/*static String * characterListToString(void * ch)
{
	char c;
	String * string = String_createEmpty();
	c =  *(char*)ch;

	switch(c)
	{
		case '\n':
			String_appendChar(string,'\\');
			String_appendChar(string,'n');
			break;
		case '\t':
			String_appendChar(string,'\\');
			String_appendChar(string,'t');
			break;
		case '\b':
			String_appendChar(string,'\\');
			String_appendChar(string,'b');
			break;
		default:
			String_appendChar(string, c);
	}
	
	return string;
}
*/
/*

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

static int compareCaseInsensitive(void * v1, void * v2)
{
	return tolower(*(char*)v1) == tolower(*(char*)v2);
}

static int isNumeric(int ch)
{
	return isdigit(ch) || ch == '.';
}

static int pointerIsSpace(void * data)
{
	if(data == NULL)
		return false;

	return isspace(*(char*)data);
}

static int pointerIsAlpha(void * data)
{
	if(data == NULL)
		return false;

	return isalpha(*(char*)data);
}
static int pointerIsDigit(void * data)
{
	if(data == NULL)
		return false;

	return isdigit(*(char*)data);
}

static int pointerIsNumeric(void * data)
{
	if(data == NULL)
		return false;

	return isdigit(*(char*)data) || *(char*)data == '.';
}

static int pointerIsAlphaNumeric(void * data)
{
	if(data == NULL)
		return false;

	return isalnum(*(char*)data);
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