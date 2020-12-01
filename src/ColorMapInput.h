/*********************
**  Color Map generator
**********************/

#include <stdint.h>

/**************
**This function frees the memory allocated for colorMap.
**Length represents the number of elements in colorMap 
***************/
void freeMap(int length, uint8_t** colorMap);


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount);


 