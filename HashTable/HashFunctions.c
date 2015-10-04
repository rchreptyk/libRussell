#include "HashFunctions.h"

static void padString(String * string);
static List * breakIntoChunks(String * string);
static int * extendChunk(List * list);

unsigned int shaLikeHash(String * string)
{
	String * hashString;
	List * chunks;
	List * currentChunk;
	ListIterator * chunkIterator;
	int i;

	unsigned int a, b, c, d, e, f, k, temp;
	
	unsigned int h0 = 0x67452301;
	unsigned int h1 = 0xEFCDAB89;
	unsigned int h2 = 0x98BADCFE;
	unsigned int h3 = 0x10325476;
	unsigned int h4 = 0xC3D2E1F0;

	if(string == NULL)
		return 0;

	hashString = String_copy(string);
	
	padString(hashString);
	chunks = breakIntoChunks(hashString);
	
	chunkIterator = ListIterator_create(chunks);
	currentChunk = ListIterator_removeCurrent(chunkIterator);


	while(currentChunk != NULL)
	{
		int * words = extendChunk(currentChunk);
		a = h0;
    	b = h1;
    	c = h2;
    	d = h3;
    	e = h4;

		List_destroyListAndData(currentChunk, free);

		for(i = 0; i < 80; i++)
		{
			if(i < 20)
			{
				f = (b & c) | (~b & d);
				k = 0x5A827999;
			}
			else if(i < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if(i < 60)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			temp = (((a << 5) | ((a >> (32 + (~5 + 1))) & 0x0f))) + f + e + k + words[i];
			e = d;
			d = c;
			c = (((b << 30) | ((b >> (32 + (~30 + 1))) & 0x0f)));
			b = a;
			a = temp;
		}

		h0 = h0 + a;
    	h1 = h1 + b;
    	h2 = h2 + c;
    	h3 = h3 + d;
    	h4 = h4 + e;

		free(words);
		currentChunk = ListIterator_removeCurrent(chunkIterator);
	}

	ListIterator_destroy(chunkIterator);
	String_destroy(hashString);
	List_destroy(chunks);

	return (h0 + h1 + h2 + h3 + h4);
}

static void padString(String * string)
{
	while((String_getLength(string) % 16) != 0)
	{
		String_appendChar(string, '\0');
	}
}

static List * breakIntoChunks(String * string)
{
	List * chunks;
	List * tmpChunk;
	int chunk;
	List * characterList; 

	chunks = List_create();
	characterList = String_toCharList(string);

	for(chunk = 0; chunk < (String_getLength(string) / 16); chunk++)
	{
		tmpChunk = List_getRange(characterList, chunk * 16, chunk * 16 + 15);
		List_addBack(chunks, tmpChunk);
	}

	List_destroy(characterList);

	return chunks;
}

static int * extendChunk(List * list)
{
	int a, b, c, d, result;
	int word;
	ListIterator * iterator;
	char * currentData;

	int * eightyWords = malloc(sizeof(int) * 80);

	iterator = ListIterator_create(list);
	currentData = ListIterator_seekToFirst(iterator);

	for(word = 0; word < 16; word++)
	{
		eightyWords[word] = (int)(*(char *)currentData);
		currentData = ListIterator_nextItem(iterator);
	}

	for(word = 16; word < 80; word++)
	{
		a = (int)eightyWords[word - 3];
		b = (int)eightyWords[word - 8];
		c = (int)eightyWords[word - 14];
		d = (int)eightyWords[word - 16];

		result = a ^ b ^ c ^ d;
		result = ((result << 1) | ((result >> (32 + (~1 + 1))) & 0x0f));

		eightyWords[word] = result;
	}

	ListIterator_destroy(iterator);

	return eightyWords;
}
