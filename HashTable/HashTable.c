#include "HashTable.h"

struct hashTableStruct
{
	int size;
	List * keys;
	List ** table;
};

static int compareKeys(void * v1, void * v2);
static unsigned int hash(String *, int);

HashTable * HashTable_create(int size)
{
	HashTable * table;
	int i;

	if(size < 1)
		return NULL;

	table = malloc(sizeof(HashTable));
	if(table == NULL)
		return NULL;

	table->size = size;
	table->keys = List_create();
	table->table = malloc(sizeof(List *) * size);

	for(i = 0; i < size; i++)
		table->table[i] = List_create();

	return table;
}

Boolean HashTable_destroy(HashTable * table)
{
	int i;

	if(table == NULL)
		return false;

	for(i = 0; i < table->size; i++)
	{
		List_destroyListAndData(table->table[i], KeyValuePair_destroyVoid);
	}

	free(table->table);
	List_destroyListAndData(table->keys, String_destroyVoidString);

	free(table);

	return true;
}

Boolean HashTable_setValue(HashTable * table, String * key, void * data)
{
	List * currentList;
	KeyValuePair * pair;
	KeyValuePair * removed;
	if(table == NULL || key == NULL || data == NULL)
		return false;

	if(String_getLength(key) == 0)
		return false;

	pair = KeyValuePair_create(key);
	KeyValuePair_setValue(pair, data);

	currentList = table->table[hash(key, table->size)];

	removed = List_removeMatchedData(currentList, pair, KeyValuePair_isEqual);

	if(removed != NULL)
		KeyValuePair_destroy(removed);
	else
		List_addBack(table->keys, String_copy(key));

	List_addFront(currentList, pair);

	return true;
}

void * HashTable_getValue(HashTable * table, String * key)
{
	List * currentList;
	KeyValuePair * tmpPair;
	void * data;

	if(table == NULL || key == NULL)
		return NULL;

	tmpPair = KeyValuePair_create(key);
	currentList = table->table[hash(key, table->size)];

	data = List_getMatchedData(currentList, tmpPair, KeyValuePair_isEqual);
	KeyValuePair_destroy(tmpPair);

	return KeyValuePair_getValue(data);
}

Boolean HashTable_hasValue(HashTable * table, String * key)
{
	List * currentList;
	KeyValuePair * tmpPair;
	Boolean hasValue;

	if(table == NULL || key == NULL)
		return false;

	tmpPair = KeyValuePair_create(key);
	currentList = table->table[hash(key, table->size)];

	hasValue = List_containsMatchedData(currentList, tmpPair, KeyValuePair_isEqual);
	KeyValuePair_destroy(tmpPair);

	return hasValue;
}


void * HashTable_removeValue(HashTable * table, String * key)
{
	List * currentList;
	KeyValuePair * tmpPair;
	KeyValuePair * pair;
	String * removedKey;
	void * data;

	if(table == NULL || key == NULL)
		return false;

	tmpPair = KeyValuePair_create(key);
	currentList = table->table[hash(key, table->size)];

	pair = List_removeMatchedData(currentList, tmpPair, KeyValuePair_isEqual);
	KeyValuePair_destroy(tmpPair);

	if(pair == NULL)
		return NULL;

	data = KeyValuePair_getValue(pair);
	KeyValuePair_destroy(pair);

	removedKey = List_removeMatchedData(table->keys, key, compareKeys);
	String_destroy(removedKey);

	return data;
}

List * HashTable_getKeys(HashTable * table)
{
	return table->keys;
}

static unsigned int hash(String * string, int tableSize)
{
	int hash = shaLikeHash(string) % tableSize;
	return hash;
}

static int compareKeys(void * v1, void * v2)
{
	return String_equalsIgnoreCase((String*)v1, (String*)v2);
}
