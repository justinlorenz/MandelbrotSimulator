/*********************
**  Color Map generator
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function frees the memory allocated for colorMap.
**Length represents the number of elements in colorMap 
***************/
void freeMap(int length, uint8_t** colorMap)
{
    for (int x = 0; x < length; x++) {
        free(colorMap[x]);
    }
    free(colorMap);
}

/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
    FILE* ptr = fopen(colorfile,"r"); 
    if (ptr==NULL) 
    { 
        return NULL;  
    } 
    if (fscanf(ptr,"%d",colorcount) != 1) {
        return NULL;
        fclose(ptr);
    }
    if (*colorcount < 0) {
        return NULL;
        fclose(ptr);
    }
    
    uint8_t** output = (uint8_t**)malloc(*colorcount * sizeof(uint8_t*));

    for (int i = 0; i < *colorcount; i++) {
        output[i] = (uint8_t*)malloc(3 * sizeof(uint8_t));
        int red = 0;
        int blue = 0;
        int green = 0;
        if (fscanf(ptr, "%d %d %d", &red, &green, &blue) != 3 || red < 0 || blue < 0 || green < 0 ||
            red > 255 || blue > 255 || green > 255) {
            freeMap(i + 1, output);
            fclose(ptr);
            return NULL;
        }
        output[i][0] = red;
        output[i][1] = green;
        output[i][2] = blue;
    }
    fclose(ptr);
    return output;
}


