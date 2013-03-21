/*******************************************************

LIST ADT

Russell Chreptyk
0760162

This ADT represents a simple list data type which allows
for multible data elements to be stored and retrieved.

A "List" object contains all elements. The operations listed
below allow you to alter and access the List.

A "ListIterator" contains an object allowing you to step
through a list given it's operations

 ******************************************************/


#ifndef List_ADT
#define List_ADT

#include "Boolean.h"
#include <stdlib.h>

struct listStruct;
/* The List object defintion */
typedef struct listStruct List;

struct iteratorStruct;
/* The ListIterator definition */
typedef struct iteratorStruct ListIterator;

/*******************************************************************************************
 CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************************************/

List * List_create(); /*
Initilizes a List object and returns a pointer to the object. An initilized List object
allows you to use the rest of the operations in this List library

Return Value:
List * - returns an initilized list object. NULL is returned if a memory error occurs.

Preconditions: None
Postconditions: An initalized List is returned.

*/

Boolean List_destroy(List *); /*
Destroys a list, freeing resources used by the list structure. All data stored in the list
is left intact and must be released by the user.

Parameters:
List * - A list object you wish to destroy freeing resources used by the list structure

Return Value: 
Boolean - true is returned when the list is destroyed correctly. false is returned if an
error occured

Preconditions: An initalized List
Postconditions: All resources used by the list strcture are freed.

*/

Boolean List_destroyListAndData(List * list, void (*destroyData)(void * data)); /*
Destroys a list, freeing resources used by the list structure as well as destroys
all data stored in the list using the function passed in. All data stored in the
node is passed to the destroyData function pointer to allow for the user to
free resources stored in the list.

Parameters:
List * - The list you wish to destroy, freeing all resources used by the list structure
or data in the list

void (*destroyData)(void *) - A function pointer to a function which recieves a void pointer
to the current data being destroyed. This function is responsible for releasing all data stored
by the list

Return Value:
Boolean - true is returned when the list and data is destroyed correctly, false is returned
when an error occurs.

Preconditions: An initalized list and a function which releases resources used by the data
in the list.
Postconditions: All data stored in the list and the list structure is freed from memory.

*/

/*******************************************************************************************
 ADDING
 ******************************************************************************************/

Boolean List_addFront(List *, void *); /*
Adds the given void pointer reference to the beginning of the list.

Parameters:
List * - A list of which the void pointer reference will be added to the beginning of.
void * - The reference to be stored in the beginning of the list

Return Value:
Boolean - true is returned when the reference is added correctly to the beginning of 
the list, false is returned if an error occured

Preconditions: An initalized List and a valid non-null pointer reference
Postconditions: The reference is added to the beginning of the list.

*/

Boolean List_addBack(List *, void *); /*
Adds a given void pointer reference to the end of the list.

Parameters:
List * - A list of which the void pointer reference will be added to the end of.
void * - The reference to be stored in the beginning of the list

Return Value:
Boolean - true is returned when the reference is added correctly to the end of the 
list, false is returned if an error occured

Preconditions: An initilized List and a valid non-null pointer reference
Postconditions: The reference is added to the end of the list

*/

Boolean List_insertAtPosition(List *, void *, int); /*
Adds a given void pointer reference to a location specified by a position in the list.
The value is inserted into the list with all other proceding values being shifted down.

Paramaters:
List * - A list to add a void pointer to, at the location specified
void * - The reference to insert into the list
int - The position in the list to place the reference. It must be between 0 and the length
of the list. Placing at position 0 will place the reference at the beginning of the list.
Placing at the length of the list will place it it at the end of the list.

Return Value:
Boolean - true is returned when the reference is stored correctly, false is returned if an
error occured or the position is not a valid position

Preconditions: An initialized list, a non-null pointer reference and a position between 0
and the length of the list.
Postconditions: The void pointer reference is inserted into the list.

*/

/*******************************************************************************************
 REMOVING
 ******************************************************************************************/

void * List_removeFront(List *); /*
Removes the front most item from the list and returns the reference to the item.

Parameters:
List * - The list to remove the front item from.

Return Value:
void * - A reference to the front most item is returned. If there is no items in the list, NULL is
returned.

Preconditions: An initialized list with at least one item
Postconditions: The front most node is removed from the list, and the reference stored
is returned.

*/

void * List_removeBack(List *); /*
Removes the last item from the list and returns the original reference to stored to the
caller.

Parameters:
List * - The list the last item will be removed from.

Return Value:
void * - The last reference stored in the list. NULL is returned if there is no items in the list
or another error occured

Preconditions: An initilized list with at least one item.
Postconditions: The last item on the list is removed and the reference is returned.

*/

void * List_removePosition(List *, int);

/*******************************************************************************************
 FETCHING DATA
 ******************************************************************************************/

void * List_getFirstValue(List *); /*
Returns the item positioned at the front of the list. The item is not altered in the list.

Parameters:
List * - The list which to fetch the item at the front of the list.

Return Value:
void * - The value stored at the beginning of the list. NULL is returned if the list is empty or
another error occured.

Preconditions: An initialized List with at least one item.
Postconditions: The first item on the list is returned while leaving it's position in the list
intact

*/

void * List_getLastValue(List * ); /*
Returns the item positioned at the end of the list. The item is not altered in the list.

Parameters:
List * - The list which to fetch the item at the back of the list.

Return Value:
void * - The value stored at the end of the list. NULL is returned if the list is empty or 
another error occured.

Preconditions: An initilized List with at least one item.
Postconditions: The last item in the list is returend while leaving it's position in the list
inact

*/

void * List_getValueAtPosition(List *, int); /*
Returns the value of an item stored at the location specified by a position in the list.

Parameters:
List * - The list which to fetch the value at the specified position from.
int - The position of the item to return it's value. The position must be between 0 and one
less then the length of the list (e.g. if the list had 3 items, it could be between 0 and 2)
Any other position will result in an error.

Return Value:
void * - The value stored at the specified position. NULL is returned if the position is invalid
or an error occured.

Preconditions: An initalized list and a position which refers to a real value in the list.
Postconditions: The value of the item stored in the specified position is returned.

*/

/*******************************************************************************************
 LIST PROPERTIES
 ******************************************************************************************/

int List_getLength(List *); /*
******************************
Returns the number of items stored in a given list.

Parameters:
List * - The list who's length will be returned.

Return Value:
int - The number of items on the list will be returned. -1 will be returned if an error occured.

Preconditions: An initilized list.
Postconditions: The number of items in the list will be returned.

*/

Boolean List_isEmpty(List *); /*
********************************
Returns whether the list is empty or not.

Parameters:
List * - The list of whether it is empty or not will be returned.

Return Value:
Boolean - true is returned if there is no items in the list, false is returned if there are
elements in the list or if an error occured.

Preconditions: An initilized list.
Postconditions: true is returned if there is no elements in the list, false is returned if
the list contains items.

*/

/*******************************************************************************************
 LIST SEARCHING
 ******************************************************************************************/

Boolean List_containsMatchedData(List *, void *, int (*isEqual) (void *, void *)); /*
*************************************************************************************
Returns whether list contains data which is considered equal to the void reference
given by the isEqual function given. This effectivily allows you to determine if 
any reference in the list as specified by the isEqual function.

Parameters:
List * - The list which you are searching for matched data.
void * - The data or resource you are searching for
int (*isEqual) (void *,void *) - A function which compares two pieces of data within
the list. If the data is determined to be equal, it should return 1. If the value is
determined to not be equal, it should return 0. This function is used to determine
equality.

Return Value:
Boolean - true is returned if the data is found, false is returned if the data is
not found or an error occured

Preconditions: An initilized List, a non NULL void pointer, a valid function pointer
which returns 0 on inequality, and 1 on equality of passed elements.
Postconditions: true is returned if the data is found, false is returned if the data
is not found

*/

int List_matchedDataPosition(List *, void *, int (*isEqual) (void *, void *)); /*
Returns the position of the first data in the list which is considered to equal 
to the void reference given by the isEqual function given. This allows you to 
locate pieces of data within the list.

Parameters:
List * - The list which you are searching for matched data
void * - The data or resource you are searching for
int (*isEqual) (void *, void *) - A function which compares two pieces of data within
the list. If the data is determined to be equal, it should return 1. If the value is
determined to not be equal, it should return 0. This function is used to determine
equality.

Return Value:
int - The position of the data is returned. If the data is not found or another error
occured, -1 is returned.

Preconditions: An initilized List, a non NULL void pointer, a valid function pointer
which returns 0 on inequality, and 1 on equality of passed elements.
Postconditions: The position of the data is returned. -1 is returned if the item
is not found.

*/

void * List_removeMatchedData(List *, void *, int (*isEqual) (void *, void *)); /*
Removes the first data which is determined equal to the given data by the passed
in isEqual function. This allows you to remove a piece of data from the list by 
searching for it. This function will only remove the first piece of data found
to be a match. To remove more then one matching elements, call List_removeMatchData
multible times. To remove all matching elements please see List_List_removeElements

Parameters:
List * - The list which you are searching for matched data
void * - The data or resource you are searching for
int (*isEqual) (void *, void *) - A function which compares two pieces of data within
the list. If the data is determined to be equal, it should return 1. If the value is
determined to not be equal, it should return 0. This function is used to determine
equality.

Return Value:
void * - The data reference stored in the list after it has been removed from the list.
NULL is returned if the data has not been found or an error occured.

Preconditions: An initilized List, a non NULL void pointer, a valid function pointer
which returns 0 on inequality, and 1 on equality of passed elements.
Postconditions: If the data is found, it is removed from the list and it's data
reference is returned. NULL is returned if the data is not found.

*/

void * List_getMatchedData(List *, void *, int (*isEqual) (void *, void *)); /*
Gets the first data which is determined equal to the given data by the passed
in isEqual function. This allows you to get a piece of data from the list by 
searching for it. This function will only get the first piece of data found
to be a match. To remove all matching elements please see List_getMatchedElements

Parameters:
List * - The list which you are searching for matched data
void * - The data or resource you are searching for
int (*isEqual) (void *, void *) - A function which compares two pieces of data within
the list. If the data is determined to be equal, it should return 1. If the value is
determined to not be equal, it should return 0. This function is used to determine
equality.

Return Value:
void * - The data reference stored in the list that was found by the isEqual function.
NULL is returned if the data has not been found or an error occured.

Preconditions: An initilized List, a non NULL void pointer, a valid function pointer
which returns 0 on inequality, and 1 on equality of passed elements.
Postconditions: If the data is found, it's data
reference is returned. NULL is returned if the data is not found.

*/

Boolean List_containsInvalidData(List *, int (*isValid) (void *)); /*
*********************************************************************************
Like List_containsMatchedData this function searching through a list of data. However
this function returns true whenever data is found that the isValid function determines
not to be a match. This allows you to check a List for invalid data.

Parameters:
List * - The list which you are searching for invalid data
int (*isValid) (void *) - This function must recieve a piece of data and declare
whether the data is valid or not.

Return Value:
Boolean - returns true if data is not valid based off of the isValid function

Preconditions: An initilized List, a non NULL void pointer, a valid function pointers
which validates data and returns 1 on valid data and 0 on invalid data
Postconditions: true is returned if invalid data is found, false if it is not

*/

Boolean List_containsValidData(List *, int (*isValid) (void *)); /*
*********************************************************************************
Like List_containsInvalidData this function searching through a list of data. However
this function returns true whenever data is found to be valid in the list.

Parameters:
List * - The list which you are searching for valid data
int (*isValid) (void *) - This function must recieve a piece of data and declare
whether the data is valid or not.

Return Value:
Boolean - returns true if data is not valid based off of the isValid function

Preconditions: An initilized List, a non NULL void pointer, a valid function pointers
which validates data and returns 1 on valid data and 0 on invalid data
Postconditions: true is returned if valid data is found, false if it is not

*/

/*******************************************************************************************
 INTERATORS
 ******************************************************************************************/

ListIterator * ListIterator_create(List * ); /*
Creates an iterator for a given list. The iterator allows you to move throughout the list 
preforming actions. On a valid list, the iterator is placed on the first element in the
list. On an empty list, the iterator is not placed on an element and cannot iterate
until there is an element in the list.

Paramaters:
List * - The list of which to bind the new iterator to.

Return Value:
ListIterator * - An initilized ListIterator binded to the given list. NULL is returned on
an invalid list or if an error occured.

Preconditions: An initlized List
Postconditions: An initilized ListIterator is created and binded to the given list.

*/

Boolean ListIterator_destroy(ListIterator *); /*
This releases the resources used by a ListIterator, destroying it. This leaves the 
binded list intact.

Paramaters:
ListIterator * - The ListIterator to destroy and free all resources used by it

Return Value:
Boolean - returns true on success, false if an error occured.

Preconditions: An initilized ListIterator
Postconditions: The list iterator is destroyed.

*/

Boolean ListIterator_hasNextItem(ListIterator *); /*
Returns whether the iterator has a next item it can
move to.

Parameters:
ListIterator * - The ListIterator you are querying
to determine if it can move to the next item.

Return Value:
Boolean - true is returned if there is another
item to move to, false is returned if there is not
or an error occured.

Preconditions: An initilized ListIterator
Postconditions: true is returned if there is another
item to move to, false is returned if there is not.

*/

void * ListIterator_nextItem(ListIterator *); /*
Moves the iterator to the next item and returns
it's value. The iterator does not move if there
is no next item.

Parameters:
ListIterator * - The ListIterator you wish to
move to the next item.

Return Value:
void * - The value stored in the next item after
the iterator moves to it. NULL is returned if
there is no next item/

Preconditions: An initilized ListIterator.
Postconditions: If there is a next item, the
iterator moves to it. The value of the next item
is returned, NULL is retured if there was no
next item.

*/

Boolean ListIterator_hasPreviousItem(ListIterator *); /*
Returns whether the iterator is able to move to the
previous item in the list. It will not be able to move
if it is at the beginning of the list.

Parameters:
ListIterator * - The ListIterator you are querying
to determine if it can move to the next item.

Return Value:
Boolean - true is returned if there is another
item to move to, false is returned if there is not
or an error occured.

Preconditions: An initilized ListIterator
Postconditions: true is returned if there is another
item to move to, false is returned if there is not.

*/

void * ListIterator_previousItem(ListIterator *); /*
Moves the iterator to the previous item in the list
and returns it's value. If there is no previous item
the iterator does not move.

Parameters:
ListIterator * - The ListIterator you wish to move to
the previous item.

Return Value:
void * - The value stored in the previous item after
the iterator moves to it. NULL is returned if
there is no previous item/

Preconditions: An initilized ListIterator.
Postconditions: If there is a previous item, the
iterator moves to it. The value of the previous item
is returned, NULL is retured if there was no
previous item.

*/

void * ListIterator_seekToFirst(ListIterator *); /*
Moves the iterator to the first item in the list.
Returns the value of the first item of the list.

Parameters:
ListIterator * - The list iterator you wish to
move to the beginning of the list.

Return Value:
void * - The value of the first item in the list,
NULL is returned if the list is empty or an
error occured.

Preconditions: An initilized ListIterator contiaining
a non-empty list
Postconditions: The iterator moves to the first item
in the list and the value of the first item is returned

*/

void * ListIterator_seekToLast(ListIterator *); /*
Moves the iterator to the last item in the list.
Returns the value of the last item of the list.

Parameters:
ListIterator * - The list iterator you wish to
move to the end of the list.

Return Value:
void * - The value of the last item in the list,
NULL is returned if the list is empty or an
error occured.

Preconditions: An initilized ListIterator contiaining
a non-empty list
Postconditions: The iterator moves to the last item
in the list and the value of the last item is returned

*/

void * ListIterator_seekToPosition(ListIterator *, int position); /*
Moves the iterator to a specific position in the list. The position
must be between 0 and one less then the length of the list. The value
at that position is returned

Paramaters:
ListIterator * - The iterator you wish to move a specific position 
int - The position in the list you wish to move the iterator to.
Position 0 refers the beginning of the list, a position one less
then the length of the list refers to the last item.

Return Value:
void * - Returns the value of the item at the specified position.
NULL is returned if the given position is invalid or an error
occured.

Preconditions: An initilized ListIterator contiaining
a non-empty list and a valid position within that list.
Postconditions: The iterator moves to the given position
and returns the value stored at that position

*/

void * ListIterator_currentValue(ListIterator *); /*
Returns the value of the iterators current location
in it's list.

Parameters:
ListIterator * - the current iterator of which it's
current location's value is being returned.

Return Value:
void * - the value stored at the iterators current
position within the list. NULL is returned if the
list is empty or an error occured.

Preconditions: An initilized ListIterator containing
a non-empty list.
Postconditions: The current value of the iterators
position in the list is returned.

*/

Boolean ListIterator_hasCurrentValue(ListIterator *); /*
Returns whether the given iterator has a value. 
It will not have a value if the list is empty.

Parameters: 
ListIterator * - The iterator being checked for a current
value

Return Value: true is returned if the iterator has a
current value. false is returned when the list is 
empty or an error occured.

*/

Boolean ListIterator_insertValue(ListIterator *, void *); /*
Inserts a value at the current location of the iterator.
The new value is inserted before the old value. This
effectivly shifts the entire list down from where the 
iterator is, and places the new value there. The current
positon of the list becomes the new values.

Parameters:
ListIterator * - The iterator who's location the value
will be inserted.
void * - The data that is going to be inserted into the
list.

Return Value:
Boolean - true is returned if the value is inserted
correctly. false is returned if the insertion failed

Preconditions: An initilized ListIterator and a non NULL
void pointer.
Postconditions: The value passed is inserted into the
listiterator's current position

*/

void * ListIterator_removeCurrent(ListIterator *); /*
Removes the value stored at the current position from
the list. After the value is removed from the list,
the iterator automatically moves to the next item
after the removed item. If there is no next item,
it will move to the previous item. If there is no
previous item, the list is empty and the iterator
has no current location. The data removed is returned.

Parameters:
ListIterator * - The iterator to get the position
to remove in the list

Return Value:
void * - The value removed is returned. NULL is
returned if the list is empty.

Preconditions: An initlized ListIterator containing
a non-empty list
Postconditions: The current position of the iterator
is removed from the list and returned.


*/

int ListIterator_currentPosition(ListIterator *); /*
Returns the iterator's current position in the list.

Parameters:
ListIterator * - The iterator to get the current position from.

Return Value:
int - The iterators current position is returned. -1
is returned on error or if the list is empty.

Preconditions: An initiliized ListIterator which
contains a non-empty list
Postcondition: The current position in the list is returned.

*/

/*******************************************************************************************
 LIST WIDE OPERATIONS
 ******************************************************************************************/

List * List_clone(List *);
/*
Creates a skeleton copy of another list. This means
a new list is created containing the same values as the
previous list. Both lists refer to the exact same values.

Parameters: 
List * - The list you wish to clone

Return Value:
List * - A another list is returned as an exact copy as
the one handed before. NULL is returned on error.

Preconditions: An initlized list
Postconditions: An exact clone of the list is returned.

*/

List * List_copy(List * list, void * (*copy)(void *)); /*
Creates a copy of a list and creates a copy of all
data within the list with the given copy function.
This allows for both lists to be memory managed seperatly.

Parameters:
List * - The list you wish to deep copy
void * (*copy)(void *) - A function to duplicate all data
stored at the reference point given. The reference returned
from this function will be used in the new list. NULL should
be returned if an error occured copying. The value will be
skipped if it is not copied correctly.

Return Value:
List * - The new copied list is returned. NULL is returned 
on error.

Preconditions: An initialized list to copy, and a function
which will copy data in the list.
Postconditions: A new copy of the given list is retuned.

*/

List * List_prependList(List *, List *); /*
Inserts the elements in the second given list
before the elements in the first given list.
The result is stored in a new list which
is returned.

Parameters:
List * - A list which elements will be
inserted before this list
List * - A list of elements which will
be inserted in front of the first list

Return Value:
List * - A new listed containing
the elements of the second list
prepending the elements of the
first list

Preconditions: Two initilized lists
Postconditions: A new list containing
the second list prepended to the first
is returned.

*/

List * List_appendList(List *, List *); /*
Adds the second list to the end of the first
list and stores them in a new list which
is returned containing elements from both.

Parameters:
List * - The list which elements will be
appened to.
List * - A list containing elements to 
append to the first one.

Return Value:
List * - A new list containg the result
of appending the second given list to the 
first. NULL is returned on error.

Preconditions: Two initilized lists
Postconditions: A new list containing
the second list appended to the first
is returned.

*/

List * List_insertList(List *, int, List *); /*
Inserts the elements of a list into a position
of another list and returns the result in a 
new list.

Parameters:
List * - The list which will have elements inserted
into
int - The position in the first list to insert the
elements. It the must between 0 (front of list) and the
length of the list (back of list).
List * - A list containing the elements to insert

Return Value:
List * - A new list containg the result of the insertion

Preconditions: Two initalized lists and a position in the
first list
Postconditions: The elements of the second list is inserted
at the given position in the first list and returned in a 
new list.

*/

List * List_removeRange(List *, int, int); /*
Removes a set of values from a given list
between the two given positions. The elements
removed are returned in a new list.

Parameters:
List * - The list to remove the range of values
from
int - The starting position between 0 and one
less then the length of the list.
int - The ending poisiton between the starting
position and one less then the length of the 
list.

Return Value:
List * - A list of all the elements removed
from the list.

Preconditions: An initalized list and two valid
positions within the list
Postconditions: Elements between the given
range are removed from the list and returned

*/

List * List_getMatchedElements(List *, List *, int (*isEqual)(void *, void*)); /*
Removes all elements from the first list which are in the second list as
determined by the isEqual function passed. The removed elements are returned
in a new list.

Parameters:
List * - The list to remove matched elements from
List * - A list of elements to search the first list for
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.

Return Value:
List * - A new list of all matched elements is returned. NULL is returned if an
error occured

Preconditions: Two initlized lists and a equal function which returns 1 or 0.
Postconditions: A new list is returned containing matched elements

*/

List * List_removeElements(List *, List *, int (*isEqual)(void *, void*)); /*
Remove elements from a List which are contained within the second given
list as determined by the given isEqual function. The removed elements
are returned in a new list.

Parameters:
List * - The list to remove match elements from
List * - The list of elements to search for within the list
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.

Return Value:
List * - A list of all removed elements from the first list. NULL is returned if
an error occured.

*/

List * List_getRange(List *, int, int); /*
Returns a list containing elements between the given range in the 
given list.

Parameters:
List * - The list to get the range of values
from
int - The starting position between 0 and one
less then the length of the list.
int - The ending poisiton between the starting
position and one less then the length of the 
list.

Return Value:
List * - A new list of all the elements in the
specified range

Preconditions: An initalized list and two valid
positions within the list
Postconditions: Elements between the given
range are returned in a new list

*/

Boolean List_containsSubList(List *, List *, int (*isEqual)(void *, void*)); /*
Returns whether the second list exists within the first list. Each item is
compared using the isEqual function passed in.

List * - The list to be checked for a sublist
List * - The sublist that is being looked for in the first list
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.

Return Value:
Boolean - true is returned if the sublist is found, false if not or an error
occurs

Preconditions: Two initilized lists, and a equal function which returns 1
if the both references are equal or 0 if not.
Postconditions: true is returned if the first list contains the second,
false if not

*/

int List_positionOfSubList(List *, List *, int (*isEqual)(void *, void*)); /*
Returns the position of the second list in the first list. If the list is
not found, -1 is returned.

List * - The list to be checked for a sublist
List * - The sublist that is being looked for in the first list
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.

Return Value:
int - Returns the position of the second list in the first list. -1 is
returned if the list is not found or an error occured.

Preconditions: Two initilized lists, and a equal function which returns 1
if the both references are equal or 0 if not.
Postconditions: The position of the second list within the first list
is returned. -1 is returned if the list is not found

*/

int List_positionOfSubListOffset(List *, List *, int (*isEqual)(void *, void*), int offset); /*
Returns the position of the second list in the first list. If the list is
not found, -1 is returned. This preforms the same as List_positionOfSubList however it
will only start searching for the sublist after the offset

List * - The list to be checked for a sublist
List * - The sublist that is being looked for in the first list
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.
int - The location to start looking at the list from. This must be between 0
and one less then the list

Return Value:
int - Returns the position of the second list in the first list after the offset. -1 is
returned if the list is not found or an error occured.

Preconditions: Two initilized lists, and a equal function which returns 1
if the both references are equal or 0 if not and a valid valid offset.
Postconditions: The position of the second list within the first list
is returned. -1 is returned if the list is not found

*/

Boolean List_isEqual(List *, List *, int (*isEqual)(void *, void *)); /*
Returns whether the first list is equal to the second list as
determined by the isEqual function passed in.

List * - A list to be checked for equality with the second list
List * - A list to be checked for equality with the first list
int (*isEqual)(void*, void*) - A function to determine if a value is the same
as a value we are searching for. Given to pieces of data, this function should
return 1 if they are determined to be the equal. 0 Should be returned if they
are determined to not be equal.

Return Value:
Boolean - true is returned if the two lists are equal. false is returned if
they are not equal or an error occured

Preconditions: Two initilized lists, and a equal function which returns 1
if the both references are equal or 0 if not.
Postconditions: true is returned if the lists are equal, false if they
arn't

*/

#endif
