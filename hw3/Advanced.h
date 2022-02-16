/*********************************************************************/ 
/* Advanced.h: program file for advanced DIP operations	             */ 
/*                                                                   */
/* 2022/01/27 Jiancong Zhu: initial solution version                 */
/*                       for EECS22 assignment3  winter 22           */
/*********************************************************************/

#ifndef ADVANCED_H
#define ADVANCED_H

#include "Constants.h"

/* add noise to an image */
void Noise( int percentage, 
                unsigned char R[WIDTH][HEIGHT], 
                unsigned char G[WIDTH][HEIGHT], 
                unsigned char B[WIDTH][HEIGHT]);


/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], 
             unsigned char G[WIDTH][HEIGHT], 
             unsigned char B[WIDTH][HEIGHT]);


/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], 
               unsigned char G[WIDTH][HEIGHT], 
               unsigned char B[WIDTH][HEIGHT], 
               unsigned int rbits, unsigned int gbits, unsigned int bbits);

/* motion blur */
void MotionBlur(int BlurAmount, 
                unsigned char R[WIDTH][HEIGHT], 
                unsigned char G[WIDTH][HEIGHT], 
                unsigned char B[WIDTH][HEIGHT]);


#endif /* ADVANCED _ H */