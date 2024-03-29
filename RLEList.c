#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

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

static RLEList createNode(char value);
static RLEListResult removeNode(RLEList node);
static int getNumOfDigits(int number);


//**************************** FUNCTIONS ***********************//

static RLEList createNode(char value)
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

static RLEListResult removeNode(RLEList prevNode)
{
    if(!prevNode || !prevNode->next)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList toRemove = prevNode->next;
    prevNode->next = prevNode->next->next;
    toRemove->next = NULL;
    free(toRemove);
    return RLE_LIST_SUCCESS;
    
}

static int getNumOfDigits(int number)
{
    int counter = 1;
    while((number / 10))
    {
        number = number / 10;
        counter++;
    }
    return counter;
}

RLEList RLEListCreate()
{
    RLEList newNode = createNode('\0');
    if (!newNode)
    {
        return NULL;
    }
    newNode->counter = 0;
    newNode->next = NULL;
    return newNode; 
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
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList curNode = list;
        
    while (curNode->next)
    {
        curNode = curNode->next;
    }
    if (curNode->curChar == value)
    {
        curNode->counter ++;
    }
    else
    {
        RLEList newNode = createNode(value);
        if (!newNode)
        {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        curNode->next = newNode;
    }
    return RLE_LIST_SUCCESS;
}


int RLEListSize(RLEList list)
{
    if(!list)
    {
        return NULL_POINTER;
    }

    int counter = 0;
    while(list)
    {
        counter += list->counter;
        list = list->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    else if (index >= RLEListSize(list) || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }  
    int curIndex = -1;
    RLEList prev = NULL;


    while (((list->counter)+curIndex) < index)
    {
        curIndex += list->counter;
        prev = list;
        list = list->next;
    }
    
    if(list->counter > 1)
    {
        list->counter--;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        RLEListResult result = removeNode(prev);

        //If unification is needed
        if(prev->next && (prev->curChar == (prev->next)->curChar))
        {
            prev->counter += (prev->next)->counter;
            return removeNode(prev);
        }

        return result;
    }
}

// index is starting from 0
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return FAILURE;
    }
    if(index >= RLEListSize(list) || index < 0)
    {
        if(result)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return FAILURE;
    }
    
    int count = -1;
    
    //skiping the imaginary node
    list = list->next;
    while(list)
    {
        if(index <= (count + list->counter))
        {
            if(result)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return list->curChar;
        }
        else
        {
            count += list->counter;
            list = list->next;
        }
    }
    if(result)
    {
        *result = RLE_LIST_ERROR;
    } 
    return FAILURE;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list)
    {
        if(result)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        } 
        return NULL;
    }
    char* listToString = (char*)malloc(NUM_OF_DATA*RLEListSize(list)+END_OF_STRING);
    if (!listToString)
    {
        if(result)
        {
            *result = RLE_LIST_ERROR;
        }
        return NULL;
    }
    *listToString = '\0';
    //int index = 0;

    //skipinig imaginary node
    list = list->next;
    while(list)
    {
        int numOfDigitis = getNumOfDigits(list->counter);
        char* counterAsChar = (char*)malloc(numOfDigitis + 3);
        if(!counterAsChar)
        {
            if(result)
            {
                *result = RLE_LIST_ERROR;
            }
            return NULL;
        }
        sprintf(counterAsChar, "%c%d\n",list->curChar, list->counter);
        strcat(listToString, counterAsChar);
        free(counterAsChar);
        list = list->next;
    }
    if(result)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return listToString ;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    if(!list || !map_function)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    
    //setting prev as the imaginary node and skiping it
    RLEList prev = list;
    list = list->next;
    while(list)
    {
        char mappedChar = map_function(list->curChar);
        if(mappedChar != prev->curChar)
        {   
            prev = list;
            list->curChar = mappedChar;
            list = list->next;
        }
        else
        {
            prev->counter += list->counter;
            RLEListResult nodeRemoveStatus = removeNode(prev);
            if(nodeRemoveStatus != RLE_LIST_SUCCESS)
            {
                return RLE_LIST_ERROR;
            }
            list = prev->next;
        }
    }
    return RLE_LIST_SUCCESS;
}