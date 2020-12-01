#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorOut.h"

/**************
**Translate pixel value given in MandelOut array into a color that can be found in the colorMap array
**Length of the MandelOut array = size * size
**Output should be written to outputfile with P3 format
***************/

int P3colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
    FILE *ptr = fopen(outputfile, "w");
    if (ptr == NULL) {
        fclose(ptr);
        return 1;
    }
    if (fprintf(ptr,"P3 %llu %llu 255",size, size) < 0) {
        fclose(ptr);
        return 1;
    }
    for (int i = 0; i < size*size; i++) {
        if (MandelOut[i] == 0) {
            int zero  = 0;
            if (fprintf(ptr,"\n%d %d %d", zero, zero, zero) < 0) {
                fclose(ptr);
                return 1;
            }
        }
        else if (MandelOut[i] > colorcount) {
            int index = MandelOut[i] % colorcount;
            index--;
            if (index == -1) {
                index = colorcount - 1;
            }
            if (fprintf(ptr,"\n%d %d %d", colorMap[index][0],colorMap[index][1], colorMap[index][2])<0) {
                fclose(ptr);
                return 1;
            }
        }
        else {
            if (fprintf(ptr,"\n%d %d %d", colorMap[MandelOut[i] - 1][0],colorMap[MandelOut[i] - 1][1], colorMap[MandelOut[i] - 1][2]) < 0 ) {
                fclose(ptr);
                return 1;
            }
        }
    }
    fclose(ptr);
    return 0;
}

/**************
**Same as above, but with P6 format
***************/
int P6colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile)
{
    FILE *ptr = fopen(outputfile, "w");
    if (ptr == NULL) {
        fclose(ptr);
        return 1;
    }
    if (fprintf(ptr,"P6 %llu %llu 255\n",size, size) < 0) {
        fclose(ptr);
        return 1;
    }
    for (int i = 0; i < size*size; i++) {
        uint8_t arr[3];
        if (MandelOut[i] == 0) {
            arr[0] = 0;
            arr[1] = 0;
            arr[2] = 0;
        }
        else if (MandelOut[i] > colorcount) {
            int index = MandelOut[i] % colorcount;
            index--;
            if (index == -1) {
                index = colorcount - 1;
            }
            arr[0] = colorMap[index][0];
            arr[1] = colorMap[index][1];
            arr[2] = colorMap[index][2];
        }
        else {
            arr[0] = colorMap[MandelOut[i] - 1][0];
            arr[1] = colorMap[MandelOut[i] - 1][1];
            arr[2] = colorMap[MandelOut[i] - 1][2];
        }
        if (fwrite(arr, 1, 3, ptr) != 3) {
                fclose(ptr);
                return 1;
        }
    }
    fclose(ptr);
    return 0;
} 