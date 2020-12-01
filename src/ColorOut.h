#include <stdint.h>

/**************
**Translate pixel value given in MandelOut array into a color that can be found in the colorMap array
**Length of the MandelOut array = size * size
**Output should be written to outputfile with P3 format
***************/
int P3colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile);

/**************
**Same as above, but with P6 format
***************/
int P6colorpalette(u_int64_t size, uint8_t** colorMap, int colorcount, u_int64_t * MandelOut, char* outputfile); 