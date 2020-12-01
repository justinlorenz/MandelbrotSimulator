#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * c, double threshold)
{   
    ComplexNumber* curr;
    double result = 0;
    ComplexNumber* old = newComplexNumber(0,0);
    for (u_int64_t x = 0; x < maxiters; x++) {
            ComplexNumber* product = ComplexProduct(old,old);
            curr = ComplexSum(product,c);
            freeComplexNumber(product);
            freeComplexNumber(old);
            result = ComplexAbs(curr);
            if (result >= threshold) {
                freeComplexNumber(curr);
                return x + 1;
            }
            old = curr;
    }
    freeComplexNumber(old);
    return 0;
} 

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //scale = 5
    //res = 2
    if (resolution <= 0) {
        output[0] = MandelbrotIterations(max_iterations,center,threshold);
        return;
    }
    double step = scale/resolution;
    int currIndex = 0; 
    for (int x = 0; x < (2 * resolution + 1); x++) {
        for (int y = 0; y < (2 * resolution + 1); y++) {
            double real = (-scale + (step * y));
            double imag = (scale - (step * x));
            ComplexNumber* box = newComplexNumber(real, imag);
            ComplexNumber* C = ComplexSum(center, box);
            freeComplexNumber(box);
            output[currIndex] = MandelbrotIterations(max_iterations,C,threshold);
            freeComplexNumber(C);
            currIndex++;
        }
    }
}


