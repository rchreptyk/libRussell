#ifndef Stack_ADT
#define Stack_ADT

struct stackStruct;
typedef struct stackStruct Stack;

/*******************************************************************************************
 CONSTRUCTORS AND DESTRUCTORS
 ******************************************************************************************/

Stack * Stack_create();

Boolean Stack_destroy(Stack *);

Boolean Stack_destroyStackAndData(Stack *, void (*destroyData)(void * data));

/*******************************************************************************************
 OPERATIONS
 ******************************************************************************************/

Boolean Stack_push(Stack *, void *);

void * Stack_pop(Stack *);

void * Stack_peek(Stack *);

#endif