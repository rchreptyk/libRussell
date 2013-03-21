
#ifndef AVLTree_ADT
#define AVLTree_ADT

#include "Boolean.h"
#include <stdlib.h>
#include <stdio.h>

struct avltreeStruct;
typedef struct avltreeStruct AVLTree;

/* CONSTRUCTOR DESTRUCTOR */

AVLTree * AVLTree_create(int (*compareData)(void *, void *));

Boolean AVLTree_destroy(AVLTree *);

Boolean AVLTree_destroyTreeAndData(AVLTree *, void (*destroyData)(void * data));

/* OPERATIONS */

Boolean AVLTree_insert(AVLTree *, void * data);

void * AVLTree_remove(AVLTree *, void * data);

void * AVLTree_search(AVLTree *, void * data);

Boolean AVLTree_exists(AVLTree *, void * data);

/* PROPERTIES */

void * AVLTree_getGreatestNode(AVLTree *);

void * AVLTree_getLeastNode(AVLTree *);

int AVLTree_getNumNodes(AVLTree *);

/* DEBUG */

/* void saveIntTree(AVLTree * tree, int num); */

#endif