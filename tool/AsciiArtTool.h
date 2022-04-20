#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "RLEList.h"

/**
 * ASCII Art Tool
 * 
 * Implements an ASCII Art Tool presents pictures in the
 * shell using RLE to save the pictures comprassed
 * 
 * The following functions are available:
 *  asciiArtRead          - Reads the data from a given file and compress it with RLE
 *  asciiArtPrint         - Writes a picture that represented by RLEList to the file
 *  asciiArtPrintEncoded  - Writes the compressed pecture to the file
 */



/**
* asciiArtRead: Reads the data from a given file and compress it by RLE.
*
* @param in_stream - The list that contains the data that should be compressed.
* @return
* 	A RLEList type list that contains all the characters in the picture
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* asciiArtPrint: Writes a picture from a given RLE list to a given file
*
* @param list - RLE list to be deallocated. If RLE list is NULL nothing will be done
* @param out_stream -  a pointer to the file the picture is written to
* @return
*  RLE_LIST_NULL_ARGUMENT if one of the params is NULL
*  RLE_LIST_SUCCESS in case of success  
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiArtPrintEncoded: Writes the compressed pecture to the file.
*
* @param list - RLE list to be deallocated. If RLE list is NULL nothing will be done
* @param out_stream - The file that the compressed picture is writen to.
* @return
* 	NULL if the list or the file are NULL.
*   RLE_LIST_SUCCESS if the writing is done successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif //HW1_ASCIIARTTOOL_H