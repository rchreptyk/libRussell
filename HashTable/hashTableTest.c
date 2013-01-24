#include "HashTable.h"
#include <stdio.h>

int main()
{
	String * myKey, *myKey2, *myValue, *tmpString;
	List * keys; 
	ListIterator * iterator;
	HashTable * table = HashTable_create(500);

	myKey = String_create("Mia");
	myKey2 = String_create("Russell");
	myValue = String_create("shrug");

	HashTable_setValue(table, myKey, String_copy(myValue));
	HashTable_setValue(table, myKey2, String_copy(myValue));

	String_destroy(myValue);

	keys = HashTable_getKeys(table);

	iterator = ListIterator_create(keys);
	tmpString = ListIterator_seekToFirst(iterator);

	while(tmpString != NULL)
	{
		myValue = HashTable_removeValue(table, tmpString);
		printf("Removed -> %s\n", String_c(myValue));
		String_destroy(myValue);
		tmpString = ListIterator_seekToFirst(iterator);
	}

	ListIterator_destroy(iterator);

	String_destroy(myKey);
	String_destroy(myKey2);

	HashTable_destroy(table);
	return 0;
}