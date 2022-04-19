#include "RLEList.h"

//**************************** DEFINES *************************//

#define NULL_POINTER -1
#define FAILURE 0
#define END_OF_STRING 1
#define NUM_OF_DATA 4 //char,counter and newline

//**************************** STRUCTS *************************//

struct RLEList_t{
    char curChar;
    int counter;
    struct RLEList_t* next;
};

//************************* DECLARATIONS ***********************//
static RLEList CreateNode(char value);


//**************************** FUNCTIONS ***********************//


RLEList RLEListCreate()
{
    RLEList newNode = CreateNode('0');
    if (!newNode)
    {
        return NULL;
    }
    newNode->counter = 0;
    ptr->next = NULL;
    return newNode; 
}

static RLEList CreateNode(char value)
{
    RLEList ptr = malloc (sizeof(*ptr));
    if (!ptr)
    {
        return NULL;
    }
    ptr->curChar = value;
    ptr->counter = 1;
    ptr->next = NULL;
    return ptr; 
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList curNode = list;
        
    while (!curNode->next)
    {
        curNode = curNode->next;
    }
    if (curNode->curChar == value)
    {
        curNode->counter ++;
    }
    else
    {
        RLEList newNode = CreateNode(value);
        if (!newNode)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        curNode->next = newNode;
    }
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list);
{
    if(!list)
    {
        return NULL_POINTER;
    }
    else
    {
        int counter = 0;
        while(list)
        {
            counter += list->counter;
            list = list->next;
        }

    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index >= RLEListSize(list))
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }  
    int curIndex = -1;
    RLEList prev = NULL;

    while ((list->counter)+curIndex < index)
    {
        curIndex += list->counter;
        prev = list;
        list = list->next;
    }
    
    if(list->counter > 1)
    {
        list->counter--;
    }
    else
    {
        prev->next = list->next;
        free(list);
    }

    return RLE_LIST_SUCCESS;

}

// index is starting from 0
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return FAILURE;
    }
    if(index >= RLEListSize(list))
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return FAILURE;
    }
    
    int count = 0;
    
    //skiping the imaginary node
    list = list->next;
    while(list)
    {
        if(index <= (count + list->counter))
        {
            *result = RLE_LIST_SUCCESS;
            return list->cur_char;
        }
        else
        {
            count += list->counter;
            list = list->next;
        }
    }
    *result = RLE_LIST_ERROR;
    return FAILURE;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    char* listToString = (char*)malloc(4*RLEListSize(list)+END_OF_STRING);

    int index = 0;
    while(list)
    {
        listToString[index] = list-> curChar;
        listToString[++index] =(char) list-> counter;
        listToString[++index] = '\n' ;
        index++;
    }
    listToString[index]='\0';
    *result = LIST_SUCCESS;
    return listToString ;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    //skiping imaginary node
    list = list->next;
    while(list)
    {
        char mappedChar = map_function(list->curChar);
        list->curChar = mappedChar;
        list = list->next;
    }
    return RLE_LIST_SUCCESS;
}