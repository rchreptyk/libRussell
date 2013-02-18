#include "KeyValuePair.h"

struct keyValuePairStruct
{
	String * key;
	void * value;
};

KeyValuePair * KeyValuePair_create(String * key)
{
	KeyValuePair * pair;

	if(key == NULL)
		return NULL;

	pair = malloc(sizeof(KeyValuePair));

	if(pair == NULL)
		return NULL;

	pair->key = String_copy(key);
	pair->value = NULL;

	return pair;
}

Boolean KeyValuePair_destroy(KeyValuePair * pair)
{
	if(pair == NULL)
		return false;

	String_destroy(pair->key);
	pair->key = NULL;

	pair->value = NULL;

	free(pair);

	return true;
}

void KeyValuePair_destroyVoid(void * pair)
{
	KeyValuePair_destroy((KeyValuePair *) pair);
}

Boolean KeyValuePair_setValue(KeyValuePair * pair, void * value)
{
	if(pair == NULL)
		return false;

	pair->value = value;

	return true;
}

void * KeyValuePair_getValue(KeyValuePair * pair)
{
	if(pair == NULL)
		return NULL;

	return pair->value;
}

int KeyValuePair_isEqual(void * v1, void * v2)
{
	KeyValuePair * pair1, *pair2;

	if(v1 == NULL || v2 == NULL)
		return 0;

	pair1 = (KeyValuePair *) v1;
	pair2 = (KeyValuePair *) v2;

	return String_equalsIgnoreCase(pair1->key, pair2->key);
}