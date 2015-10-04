#include <List.h>

struct nodeStruct{
    struct nodeStruct * previousNode;
    struct nodeStruct * nextNode;
    void * data;
};

typedef struct nodeStruct ListNode;

struct listStruct {
    int length;
    
    void * firstNode;
    void * lastNode;
};

struct iteratorStruct {
    List * list;
    ListNode * currentNode;
};

/* Internal functions, not to be part of the interface */
 
static ListNode * createNode(void * data);
static Boolean destroyNode(ListNode * node);

static Boolean addFirstNode(List * list, ListNode * node);
static ListNode * detachLastNode(List * list);

static ListNode * detachAtIndex(List * list, int index);
static ListNode * detachFront(List * list);
static ListNode * detachBack(List * list);

static ListNode * nodeAtIndex(List * list, int index);

static Boolean locationContainsSubList(List * list, List * sublist, int (isEqual)(void *, void *), int location);

/* Function implementations */

List * List_create()
{
    List * list;

    list = malloc(sizeof(struct listStruct));
    if(list == NULL)
        return NULL;

    list->firstNode = NULL;
    list->lastNode = NULL;
    list->length = 0;

    return list;
}

Boolean List_destroy(List * list)
{
    ListNode * currentNode;
    
    if(list == NULL)
        return false;

    while ((currentNode = detachFront(list)) != NULL) {
        if(!destroyNode(currentNode))
            return false;
    }
    
    free(list);

    return true;
}

Boolean List_destroyListAndData(List * list, void (*destroyData)(void * data))
{
    ListNode * currentNode;
    
    if(list == NULL)
        return false;
    destroyData(NULL);

    while ((currentNode = detachFront(list)) != NULL) {
        destroyData(currentNode->data);
        if(!destroyNode(currentNode))
            return false;
    }
    
    free(list);

    return true;
}

/* Adding */

Boolean List_addFront(List * list, void * data)
{
    ListNode * oldFirstNode, *newNode;
    
    if(list == NULL || data == NULL)
        return false;

    newNode = createNode(data);
    if(newNode == NULL)
        return false;
    
    /* The list is empty */
    if(list->firstNode == NULL && list->lastNode == NULL) 
    {
        return addFirstNode(list, newNode);
    }
    
    oldFirstNode = list->firstNode;
    
    list->firstNode = newNode;
    newNode->nextNode = oldFirstNode;
    
    oldFirstNode->previousNode = newNode;
    newNode->previousNode = NULL;
    
    list->length++;

    return true;
}

Boolean List_addBack(List * list, void * data)
{
    ListNode * oldLastNode, *newNode;
    
    if(list == NULL || data == NULL)
        return false;

    newNode = createNode(data);
    if(newNode == NULL)
        return false;
    
    if(list->firstNode == NULL && list->lastNode == NULL) /* The list is empty */
    {
        return addFirstNode(list, newNode);
    }
    
    oldLastNode = list->lastNode;

    oldLastNode->nextNode = newNode;
    newNode->nextNode = NULL;
    
    list->lastNode = newNode;
    newNode->previousNode = oldLastNode;
    
    list->length++;

    return true;
}

Boolean List_insertAtPosition(List * list, void * data, int index)
{
    ListNode * nextNode, *previousNode, *newNode;
    
    if(list == NULL || data == NULL)
        return false;
    
    if(index < 0 || index > List_getLength(list))
        return false;

    newNode = createNode(data);
    if(newNode == NULL)
        return false;
    
    if(index == 0)
    {
        return List_addFront(list, newNode);
    }
    
    if(index == List_getLength(list))
    {
        return List_addBack(list, newNode);
    }
    
    nextNode = nodeAtIndex(list, index);
    previousNode = nextNode->previousNode;
    
    previousNode->nextNode = newNode;
    newNode->nextNode = nextNode;
    
    nextNode->previousNode = newNode;
    newNode->previousNode = previousNode;
    
    list->length++;

    return true;
}

/* Removing */

void * List_removeFront(List * list)
{
    ListNode * nodeToRemove;
    void * data;
    
    if(list == NULL)
        return NULL;
    
    nodeToRemove = detachFront(list);
    if(nodeToRemove == NULL)
        return NULL;

    data = nodeToRemove->data;
    destroyNode(nodeToRemove);
    return data;
}

void * List_removeBack(List * list)
{
    ListNode * nodeToRemove;
    void * data;
    
    if(list == NULL)
        return NULL;
    
    nodeToRemove = detachBack(list);
    if(nodeToRemove == NULL)
        return NULL;

    data = nodeToRemove->data;
    destroyNode(nodeToRemove);
    return data;
}

void * List_removePosition(List * list, int index)
{
    ListNode * nodeToRemove;
    void * data;
    
    if(list == NULL)
        return NULL;
    
    if(index < 0 || index >= List_getLength(list))
        return NULL;
    
    nodeToRemove = detachAtIndex(list, index);
    if(nodeToRemove == NULL)
        return NULL;

    data = nodeToRemove->data;
    destroyNode(nodeToRemove);
    return data;
}

void * List_getFirstValue(List * list)
{
    ListNode * node;

    if(list == NULL)
        return NULL;

    node = list->firstNode;

    if(node == NULL)
        return NULL;

    return node->data;
}

void * List_getLastValue(List * list)
{
    ListNode * node;

    if(list == NULL)
        return NULL;

    node = list->lastNode;

    if(node == NULL)
        return NULL;

    return node->data;
}

void * List_getValueAtPosition(List * list, int index)
{
    ListNode * node;

    if(list == NULL)
        return NULL;

    node = nodeAtIndex(list, index);

    if(node == NULL)
        return NULL;

    return node->data;
}

/* List Properties */

int List_getLength(List * list)
{
    if(list == NULL)
        return -1;
    return list->length;
}

Boolean List_isEmpty(List * list)
{
    return List_getLength(list) == 0;
}

/* List Searching */

Boolean List_containsMatchedData(List * list, void * data, int (*isEqual) (void *, void *))
{
    if(list == NULL || data == NULL)
    {
        return false;
    }
    
    return List_matchedDataPosition(list, data, isEqual) != -1;
}

int List_matchedDataPosition(List * list, void * data, int (*isEqual) (void *, void *))
{
    int count = 0;
    ListNode * currentNode;
    
    if(list == NULL || data == NULL)
        return -1;
    
    currentNode = list->firstNode;
    while(currentNode != NULL)
    {
        if(isEqual(currentNode->data, data))
            return count;
        
        count++;
        currentNode = currentNode->nextNode;
    }
    
    return -1;
}

void * List_removeMatchedData(List * list, void * data, int (*isEqual) (void *, void *))
{   
    if(data == NULL || list == NULL)
        return NULL;

    return List_removePosition(list, List_matchedDataPosition(list, data, isEqual));
}

void * List_getMatchedData(List * list, void * data, int (*isEqual) (void *, void *))
{   
    if(data == NULL || list == NULL)
        return NULL;

    return List_getValueAtPosition(list, List_matchedDataPosition(list, data, isEqual));
}

Boolean List_containsInvalidData(List * list, int (*isValid) (void *))
{
    ListNode * currentNode;
    
    if(list == NULL)
        return true;
    
    currentNode = list->firstNode;
    while(currentNode != NULL)
    {
        if(!isValid(currentNode->data))
            return true;
        
        currentNode = currentNode->nextNode;
    }
    
    return false;
}

Boolean List_containsValidData(List * list, int (*isValid) (void *))
{
    ListNode * currentNode;
    
    if(list == NULL)
        return true;
    
    currentNode = list->firstNode;
    while(currentNode != NULL)
    {
        if(isValid(currentNode->data))
            return true;
        
        currentNode = currentNode->nextNode;
    }
    
    return false;
}

/* Interators */

ListIterator * ListIterator_create(List * list)
{
    ListIterator * iterator;

    if(list == NULL)
        return NULL;

    iterator = malloc(sizeof(ListIterator));

    if(iterator == NULL)
        return NULL;

    iterator->list = list;
    iterator->currentNode = list->firstNode;

    return iterator;
}

Boolean ListIterator_destroy(ListIterator * iterator)
{
    if(iterator == NULL)
        return false;

    iterator->list = NULL;
    iterator->currentNode = NULL;
    free(iterator);

    return true;
}

Boolean ListIterator_hasNextItem(ListIterator * iterator)
{
    if(iterator == NULL)
        return false;

    if(iterator->currentNode == NULL)
        return false;

    return iterator->currentNode->nextNode != NULL;
}

void * ListIterator_nextItem(ListIterator * iterator)
{
    if(!ListIterator_hasNextItem(iterator))
    {
        return NULL;
    }
        

    iterator->currentNode = iterator->currentNode->nextNode;

    return iterator->currentNode->data;
}

Boolean ListIterator_hasPreviousItem(ListIterator * iterator)
{
    if(iterator == NULL)
        return false;

    if(iterator->currentNode == NULL)
        return false;

    return iterator->currentNode->previousNode != NULL;
}

void * ListIterator_previousItem(ListIterator * iterator)
{
    if(!ListIterator_hasPreviousItem(iterator))
        return NULL;

    iterator->currentNode = iterator->currentNode->previousNode;

    return iterator->currentNode->data;
}

void * ListIterator_seekToFirst(ListIterator * iterator)
{
    if(iterator == NULL)
        return NULL;

    if(iterator->list->firstNode == NULL)
        return NULL;

    iterator->currentNode = iterator->list->firstNode;

    return iterator->currentNode->data;
}

void * ListIterator_seekToLast(ListIterator * iterator)
{
    if(iterator == NULL)
        return NULL;

    if(iterator->list->lastNode == NULL)
        return NULL;

    iterator->currentNode = iterator->list->lastNode;

    return iterator->currentNode->data;
}

void * ListIterator_seekToPosition(ListIterator * iterator, int position)
{
    ListNode * node;

    if(iterator == NULL)
        return NULL;

    node = nodeAtIndex(iterator->list, position);
    if(node == NULL)
        return NULL;

    iterator->currentNode = node;

    return iterator->currentNode->data;
}

void * ListIterator_currentValue(ListIterator * iterator)
{
    if(!ListIterator_hasCurrentValue(iterator))
        return NULL;

    return iterator->currentNode->data;
}

Boolean ListIterator_hasCurrentValue(ListIterator * iterator)
{
    if(iterator == NULL)
        return false;

    if(iterator->currentNode == NULL)
        return false;

    return true;
}

Boolean ListIterator_insertValue(ListIterator * iterator, void * data)
{
    ListNode * nextNode;
    ListNode * previousNode;
    ListNode * newNode;

    if(iterator == NULL || data == NULL)
        return false;


    if(!ListIterator_hasCurrentValue(iterator))
    {
        if(iterator->list->firstNode != NULL || iterator->list->lastNode != NULL)
        {
            return false;
        }

        newNode = createNode(data);
        if(newNode == NULL)
        {
            return false;
        }
            
        if(!addFirstNode(iterator->list, newNode))
        {
            return false;
        }

        iterator->currentNode = iterator->list->firstNode;

        return true;

    }

    if(iterator->currentNode->previousNode == NULL)
    {
        if(!List_addFront(iterator->list, data))
        {
            return false;
        }

        iterator->currentNode = iterator->list->firstNode;
        return true;
    }

    newNode = createNode(data);

    previousNode = iterator->currentNode->previousNode;
    nextNode = iterator->currentNode;

    previousNode->nextNode = newNode;
    newNode->nextNode = nextNode;

    nextNode->previousNode = newNode;
    newNode->previousNode = previousNode;

    iterator->currentNode = newNode;
    iterator->list->length++;

    return true;

}

void * ListIterator_removeCurrent(ListIterator * iterator)
{
    ListNode * previousNode, *nextNode;
    void * data;

    if(!ListIterator_hasCurrentValue(iterator))
        return NULL;

    /*last node in list case*/
    if(iterator->list->firstNode == iterator->list->lastNode && iterator->list->lastNode == iterator->currentNode)
    {
        void * data;
        ListNode * node = detachLastNode(iterator->list);
        data = node->data;
        iterator->currentNode = NULL;
        destroyNode(node);
        return data;
    }

    /*first node case*/
    if(iterator->currentNode->previousNode == NULL)
    {
        iterator->currentNode = iterator->currentNode->nextNode;
        return List_removeFront(iterator->list);
    }
    
    /*last node case*/
    if(iterator->currentNode->nextNode == NULL)
    {
        iterator->currentNode = iterator->currentNode->previousNode;
        return List_removeBack(iterator->list);
    }

    /*middle node case*/
    previousNode = iterator->currentNode->previousNode;
    nextNode = iterator->currentNode->nextNode;

    data = iterator->currentNode->data;
    if(!destroyNode(iterator->currentNode))
        return NULL;

    iterator->currentNode = nextNode;

    previousNode->nextNode = nextNode;
    nextNode->previousNode = previousNode;

    iterator->list->length--;

    return data;
}

int ListIterator_currentPosition(ListIterator * iterator)
{
    int pos = 0;
    ListNode * current;

    if(iterator == NULL)
        return -1;

    if(iterator->currentNode == NULL)
        return -1;

    current = iterator->currentNode;

    while((current = current->previousNode) != NULL) pos++;

    return pos;
}

/* List Wide Operations */

List * List_clone(List * list)
{
    List * newList;
    void * data;
    ListIterator * iterator;

    if(list == NULL)
        return NULL;

    newList = List_create();
    iterator = ListIterator_create(list);

    data = ListIterator_seekToFirst(iterator);

    while(data != NULL)
    {
        List_addBack(newList, data);
        data = ListIterator_nextItem(iterator);
    }

    ListIterator_destroy(iterator);

    return newList;
}

List * List_copy(List * list, void * (*copy)(void *))
{
    List * newList;
    void * data, * copyData;
    ListIterator * iterator;

    if(list == NULL)
        return NULL;

    newList = List_create();
    iterator = ListIterator_create(list);

    data = ListIterator_seekToFirst(iterator);

    while(data != NULL)
    {
        copyData = copy(data);
        if(copyData != NULL)
        {
            List_addBack(newList, copyData);
        }
        
        data = ListIterator_nextItem(iterator);
    }

    ListIterator_destroy(iterator);

    return newList;
}

List * List_prependList(List * list, List * prePendList)
{
    ListIterator * prependIterator;
    void * data;
    List * newList;

    if(list == NULL || prePendList == NULL)
        return NULL;

    newList = List_clone(list);

    prependIterator = ListIterator_create(prePendList);
   
    data = ListIterator_seekToLast(prependIterator);

    while(data != NULL)
    {
        List_addFront(newList, data);
        data = ListIterator_previousItem(prependIterator);
    }

    ListIterator_destroy(prependIterator);

    return newList;
}

List * List_appendList(List * list, List * appendList)
{
    ListIterator * appendIterator;
    void * data;
    List * newList;

    if(list == NULL || appendList == NULL)
        return NULL;

    newList = List_clone(list);

    appendIterator = ListIterator_create(appendList);
    data = ListIterator_seekToFirst(appendIterator);

    while(data != NULL)
    {
        List_addBack(newList, data);
        data = ListIterator_nextItem(appendIterator);
    }

    ListIterator_destroy(appendIterator);

    return newList;
}

List * List_insertList(List * list, int position, List * insertList)
{
    ListIterator * newIterator;
    ListIterator * insertIterator;
    void * data;
    List * newList;

    if(list == NULL || insertList == NULL)
        return NULL;

    if(position < 0 || position > List_getLength(list))
        return NULL;

    if(position == 0)
        return List_prependList(list, insertList);

    if(position == List_getLength(list))
        return List_appendList(list, insertList);

    newList = List_clone(list);

    newIterator = ListIterator_create(newList);
    insertIterator = ListIterator_create(insertList);

    if(ListIterator_seekToPosition(newIterator, position) == NULL)
    {
        ListIterator_destroy(newIterator);
        ListIterator_destroy(insertIterator);
        List_destroy(newList);
        return NULL;
    }

    data = ListIterator_seekToFirst(insertIterator);

    while(data != NULL)
    {
        if(!ListIterator_insertValue(newIterator, data))
        {
            ListIterator_destroy(newIterator);
            ListIterator_destroy(insertIterator);
            List_destroy(newList);
            return NULL;
        }

        ListIterator_nextItem(newIterator);
        data = ListIterator_nextItem(insertIterator);
    }

    ListIterator_destroy(newIterator);
    ListIterator_destroy(insertIterator);

    return newList;
}

List * List_removeRange(List * list, int start, int end)
{
    List * newList;
    int length, i;
    void * data;
    ListIterator * iterator;

    if(list == NULL)
        return NULL;

    if(start < 0 || start >= List_getLength(list))
        return NULL;

    if(end < 0 || end >= List_getLength(list))
        return NULL;

    if(end < start)
        return NULL;

    length = end - start;
    newList = List_create();
    iterator = ListIterator_create(list);

    if(ListIterator_seekToPosition(iterator, start) == NULL)
    {
        ListIterator_destroy(iterator);
        List_destroy(newList);
        return NULL;
    }

    for(i = 0; i <= length; i++)
    {
        data = ListIterator_removeCurrent(iterator);
        if(data == NULL)
        {
            ListIterator_destroy(iterator);
            List_destroy(newList);
        }
        List_addBack(newList, data);
    }

    ListIterator_destroy(iterator);

    return newList;
}

List * List_getMatchedElements(List * list, List * elements, int (*isEqual)(void *, void *))
{
    ListIterator * iterator;
    ListIterator * elementsIterator;

    void * data;
    void * searchData;
    List * newList;

    if(list == NULL || elements == NULL || isEqual == NULL)
    {
        return NULL;
    }

    iterator = ListIterator_create(list);
    elementsIterator = ListIterator_create(elements);
    newList = List_create();

    data = ListIterator_seekToFirst(iterator);

    while(data != NULL)
    {
        searchData = ListIterator_seekToFirst(elementsIterator);

        while(searchData != NULL)
        {
            if(isEqual(data, searchData))
            {
                List_addBack(newList, data);
                break;
            }
            else
            {
                searchData = ListIterator_nextItem(elementsIterator);
            }
        }

        data = ListIterator_nextItem(iterator);
    }

    ListIterator_destroy(iterator);
    ListIterator_destroy(elementsIterator);

    return newList;
}

List * List_removeElements(List * list, List * elements, int (*isEqual)(void *, void *))
{
    ListIterator * iterator;
    ListIterator * elementsIterator;

    void * data;
    void * searchData;
    List * newList;
    Boolean removed;

    if(list == NULL || elements == NULL || isEqual == NULL)
    {
        return NULL;
    }

    iterator = ListIterator_create(list);
    elementsIterator = ListIterator_create(elements);
    newList = List_create();

    data = ListIterator_seekToFirst(iterator);

    while(data != NULL)
    {
        removed = false;
        searchData = ListIterator_seekToFirst(elementsIterator);

        while(searchData != NULL)
        {
            if(isEqual(data, searchData))
            {
                ListIterator_removeCurrent(iterator);
                List_addBack(newList, data);
                removed = true;
                break;
            }
            else
            {
                searchData = ListIterator_nextItem(elementsIterator);
            }
        }

        if(!removed)
        {
            data = ListIterator_nextItem(iterator);
        }
        else
        {
            data = ListIterator_currentValue(iterator);
        }
    }

    ListIterator_destroy(iterator);
    ListIterator_destroy(elementsIterator);

    return newList;
}

List * List_getRange(List * list, int start, int end)
{
    List * newList;
    int length, i;
    void * data;
    ListIterator * iterator;

    if(list == NULL)
        return NULL;

    if(start < 0 || start >= List_getLength(list))
        return NULL;

    if(end < 0 || end >= List_getLength(list))
        return NULL;

    if(end < start)
        return NULL;

    length = end - start;
    newList = List_create();
    iterator = ListIterator_create(list);

    ListIterator_seekToPosition(iterator, start);

    for(i = 0; i <= length; i++)
    {
        data = ListIterator_currentValue(iterator);
        List_addBack(newList, data);
        ListIterator_nextItem(iterator);
    }

    ListIterator_destroy(iterator);

    return newList;
}

Boolean List_containsSubList(List * list, List * sublist, int (*isEqual)(void *, void*))
{
    int i;

    if(list == NULL || sublist == NULL || isEqual == NULL)
        return false;

    if(List_isEmpty(sublist))
        return true;

    if(List_getLength(sublist) > List_getLength(list))
        return false;

    if(List_getLength(list) == List_getLength(sublist))
        return List_isEqual(list, sublist, isEqual);

    for(i = 0; i < List_getLength(list) - List_getLength(sublist) + 1; i++)
    {
        if(locationContainsSubList(list, sublist, isEqual, i))
            return true;
    }

    return false;

}

int List_positionOfSubList(List * list, List * sublist, int (*isEqual)(void *, void*))
{
    return List_positionOfSubListOffset(list, sublist, isEqual, 0);
}

int List_positionOfSubListOffset(List * list, List * sublist, int (*isEqual)(void *, void*), int offset)
{
    int i;

    if(list == NULL || sublist == NULL || isEqual == NULL)
        return false;

    if(List_isEmpty(sublist))
        return -1;

    if(List_getLength(sublist) > List_getLength(list))
        return -1;

    if(offset < 0 || offset >= List_getLength(sublist))
        return -1;

    if(List_getLength(list) == List_getLength(sublist) && offset == 0)
    {
        if(List_isEqual(list, sublist, isEqual))
            return 0;
        else
            return -1;
    }

    for(i = offset; i < List_getLength(list) - List_getLength(sublist) + 1; i++)
    {
        if(locationContainsSubList(list, sublist, isEqual, i))
            return i;
    }

    return -1;

}

Boolean List_isEqual(List * list, List * secondList, int (*isEqual)(void *, void *))
{
    ListIterator * first;
    ListIterator * second;
    void * firstData;
    void * secondData;

    if(list == NULL || secondList == NULL || isEqual == NULL)
        return false;

    if(List_getLength(list) != List_getLength(secondList))
        return false;

    first = ListIterator_create(list);
    second = ListIterator_create(secondList);

    firstData = ListIterator_seekToFirst(first);
    secondData = ListIterator_seekToFirst(second);

    while(firstData != NULL && secondData != NULL)
    {
        if(!isEqual(firstData, secondData))
        {
            ListIterator_destroy(first);
            ListIterator_destroy(second);
            return false;
        }

        firstData = ListIterator_nextItem(first);
        secondData = ListIterator_nextItem(second);
    }

    ListIterator_destroy(first);
    ListIterator_destroy(second);

    return firstData == secondData;
}

/* Internal Functions */
/* DO NOT USE */

static Boolean locationContainsSubList(List * list, List * sublist, int (isEqual)(void *, void *), int location)
{
    ListIterator * iterator;
    ListIterator * subIterator;
    void * data;
    void * searchData;

    iterator = ListIterator_create(list);
    subIterator = ListIterator_create(sublist);

    data = ListIterator_seekToPosition(iterator, location);
    searchData = ListIterator_seekToFirst(subIterator);

    while(data != NULL && searchData != NULL && isEqual(data, searchData))
    {

        data = ListIterator_nextItem(iterator);
        searchData = ListIterator_nextItem(subIterator);
    }

    ListIterator_destroy(iterator);
    ListIterator_destroy(subIterator);

    return searchData == NULL;
}

static Boolean addFirstNode(List * list, ListNode * node)
{
    if(list->firstNode != NULL || list->lastNode != NULL)
        return false;
    
    list->firstNode = node;
    list->lastNode = node;
    list->length = 1;
    node->nextNode = NULL;
    node->previousNode = NULL;

    return true;
}

static ListNode * detachLastNode(List * list)
{
    ListNode * node;
    
    if(list->firstNode != list->lastNode)
        return NULL;
    
    if(list->firstNode == NULL)
        return NULL;
    
    node = list->firstNode;
    node->nextNode = NULL;
    node->previousNode = NULL;
    list->firstNode = NULL;
    list->lastNode = 0;
    list->length = 0;
    return node;
}

/* Detach */

static ListNode * detachFront(List * list)
{
    ListNode * nodeToRemove, *nextNode;
    
    if(list == NULL)
        return NULL;
    
    if(list->firstNode == list->lastNode) /* Only one node left in the list */
        return detachLastNode(list);
    
    nodeToRemove = list->firstNode;
    nextNode = nodeToRemove->nextNode;
    
    list->firstNode = nextNode;
    nextNode->previousNode = NULL;
    
    nodeToRemove->nextNode = NULL;
    nodeToRemove->previousNode = NULL;
    
    list->length--;
    
    return nodeToRemove;
}

static ListNode * detachBack(List * list)
{
    ListNode * nodeToRemove, *previousNode;
    
    if(list == NULL)
        return NULL;
    
    if(list->firstNode == list->lastNode) /* Only one node left in the list */
        return detachLastNode(list);
    
    nodeToRemove = list->lastNode;
    
    previousNode = nodeToRemove->previousNode;
    previousNode->nextNode = NULL;
    
    list->lastNode = previousNode;
    
    list->length--;
    
    nodeToRemove->nextNode = NULL;
    nodeToRemove->previousNode = NULL;
    
    return nodeToRemove;
}

static ListNode * detachAtIndex(List * list, int index)
{
    ListNode * nodeToRemove, *previousNode, *nextNode;
    
    if(list == NULL)
        return NULL;
    
    if(index < 0 || index >= List_getLength(list))
        return NULL;
    
    if(index == 0)
        return detachFront(list);
    
    if(index == (List_getLength(list) - 1))
        return detachBack(list);
    
    nodeToRemove = nodeAtIndex(list, index);
    previousNode = nodeToRemove->previousNode;
    nextNode = nodeToRemove->nextNode;
    
    previousNode->nextNode = nextNode;
    nextNode->previousNode = previousNode;
    
    nodeToRemove->nextNode = NULL;
    nodeToRemove->previousNode = NULL;
    
    list->length--;
    
    return nodeToRemove;
}

static ListNode * nodeAtIndex(List * list, int index)
{
    int direction, count;
    ListNode * currentNode;
    
    if(list == NULL)
        return NULL;
    
    if(index > list->length / 2)
    {
        direction = -1;
        count = list->length - 1;
    }
    else
    {
        direction = 1;
        count = 0;
    }
    
    currentNode = (direction == 1) ? list->firstNode : list->lastNode;
    
    while (currentNode != NULL)
    {
        if(count == index)
        {
            return currentNode;
        }
        
        count += direction;
        currentNode = (direction == 1) ? currentNode->nextNode : currentNode->previousNode;
    }
    
    return NULL;
}

static Boolean destroyNode(ListNode * node)
{
    node->nextNode = NULL;
    node->previousNode = NULL;
    free(node);
    return true;
}

static ListNode * createNode(void * data)
{
    ListNode * node;

    if(data == NULL)
        return NULL;

    node = malloc(sizeof(ListNode));

    if(node == NULL)
        return NULL;

    node->nextNode = NULL;
    node->previousNode = NULL;
    node->data = data;

    return node;
}

/*int debugCalculateLengthForward(List * list)
{
    int length = 0;
    ListNode * currentNode;
    
    currentNode = firstNode(list);
    
    while (currentNode != NULL) {
        length++;
        currentNode = currentNode->rightNode;
    }
    
    return length;
}

int debugCalculateLengthBackward(List * list)
{
    int length = 0;
    ListNode * currentNode;
    
    currentNode = firstNode(list);
    
    while (currentNode != NULL) {
        length++;
        currentNode = currentNode->leftNode;
    }
    
    return length;
}*/
