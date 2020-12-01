/*********************
**  Color Palette generator
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"

//You don't need to call this function but it helps you understand how the arguments are passed in 
void usage(char* argv[])
{
    printf("Incorrect usage: Expected arguments are %s <inputfile> <outputfileP3> <outputfileP6> <array_size> <array>", argv[0]);
}
 

int main(int argc, char* argv[])
{
    if (argc != 6)
    {	
    	usage(argv);
    	return 1;
    }
    int size = atoi(argv[4]);
    char* bufferP3 = argv[2];
    char* bufferP6 = argv[3];
    int colorCount;
    uint8_t** colorMap = FileToColorMap(argv[1], &colorCount);

    if(colorMap == NULL){
    	printf("ColorMap not initialized\n");
    	return EXIT_FAILURE;
    }

    u_int64_t MandelOut[size*size];	
    char* buff = argv[5];
    int i = 0;
    char *p = strtok (buff, ",");

    for(int i = 0; i < size * size; i++){
    	MandelOut[i] = atoi(p);
    	p = strtok (NULL, ",");
    }

    int P3failed = P3colorpalette(size, colorMap, colorCount, MandelOut, bufferP3);

    if (P3failed)
    {
    	freeMap(colorCount, colorMap);
    	printf("Error in making P3colorpalette");
    	return 1;
    }

    int P6failed = P6colorpalette(size, colorMap, colorCount, MandelOut, bufferP6);
    
    if (P6failed)
    {
    	freeMap(colorCount, colorMap);
    	printf("Error in making P6colorpalette");
    	return 1;
    }
    printf("P3colorpalette and P6colorpalette ran without error, output should be stored in %s, %s", bufferP3, bufferP6);
    freeMap(colorCount, colorMap);
    return 0;
}



