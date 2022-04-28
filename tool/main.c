#include "AsciiArtTool.h"
#include <string.h>

//**************************** DEFINES *************************//

#define SPACE ' '
#define AT '@'
#define PARAM_TO_MAIN 4


//**************************** FUNCTIONS ***********************//

char inverted(char currentChar)
{
    if(currentChar == AT)
    {
        return SPACE;
    }
    else if(currentChar == SPACE)
    {
        return AT;
    }
    return currentChar;
}


int main(int argc, char **argv)
{
    if(argc != PARAM_TO_MAIN)
    {
        fprintf(stdout, "Wrong number of parameters to main!");
        return 0;
    }

     //check if the flag is valid
    if(strcmp(argv[1], "-i") && strcmp(argv[1], "-e"))
    {
        fprintf(stdout, "Flag given is invalid!");
        return 0;
    }

    //check if it is possible to open the given input and output files
    FILE* source = fopen(argv[2], "r");
    if(!source)
    {
        fprintf(stdout, "Failed opening source file!");
        return 0;
    }
    FILE* dest = fopen(argv[3], "w");
    if(!dest)
    {
        fprintf(stdout, "Failed opening dest file!");
        return fclose(source);
     
    }


    RLEList picture = asciiArtRead(source);
    RLEListResult result;

    if(!strcmp(argv[1], "-e"))
    {
        result = asciiArtPrintEncoded(picture, dest);
    }
    else
    {
        result = RLEListMap(picture, inverted);
        if(result == RLE_LIST_SUCCESS)
        {
            result = asciiArtPrint(picture, dest);
        }
        else
        {
            fprintf(stdout, "Faild in mapping proccess");
            
        }
    }
    if (result != RLE_LIST_SUCCESS)
    {
        fprintf(stdout, "Failed in ArtPrint function");
    }

    //destroy picture RLE list
    RLEListDestroy(picture);

    //remember to close the files in the end of the use
    fclose(source);
    fclose(dest);
    return 0;
}