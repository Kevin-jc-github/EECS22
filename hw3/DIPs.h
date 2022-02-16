/*********************************************************************/ 
/* DIPs.h: program file for DIP operations	                         */ 
/*                                                                   */
/* 2022/01/27 Jiancong Zhu: initial solution version                 */
/*                       for EECS22 assignment3 Winter 2022          */
/*********************************************************************/
#include "Constants.h"
#ifndef DIPS_H
#define DIPS_H

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width);

/* Testing all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT] ,unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]);
#endif /* DIPS_H */