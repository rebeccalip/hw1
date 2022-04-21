#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdlib.h>


//**************************** DEFINES *************************//



//************************* DECLARATIONS ***********************//


//**************************** FUNCTIONS ***********************//

RLEList asciiArtRead(FILE* in_stream)
{
    if (!in_stream)
    {
        return NULL;
    }
    RLEListResult result;
    RLEList rlelist = RLEListCreate();
    char currentChar;
    
    while (fscanf(in_stream, "%s", &currentChar) != EOF)
    {
        result = RLEListAppend(rlelist, currentChar);
        if (result != RLE_LIST_SUCCESS)
        {
            return NULL;
        }
    }
    
    return rlelist;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream) 
{
    RLEListResult result = RLE_LIST_SUCCESS;
    if(!list || !out_stream)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }

    int len = RLEListSize(list);
    char currentChar;
    for (int i=0; i<len; i++)
    {
        currentChar = RLEListGet(list, i, &result);
        if (result != RLE_LIST_SUCCESS)
        {
            return result;
        }
        fprintf(out_stream, "%c" ,currentChar);
    }

    return result;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(!list || !out_stream)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult resultStatus = RLE_LIST_SUCCESS;
    //remember to free the memory taken with malloc at the function
    char* encodedList = RLEListExportToString(list, &resultStatus);
    fprintf(out_stream, encodedList);
    free(encodedList);
    return resultStatus;
}