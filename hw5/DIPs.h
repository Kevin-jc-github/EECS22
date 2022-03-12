/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* DIPs.h: header file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#ifndef DIPS_H
#define DIPS_H

#include "Image.h"

/* Aging */
IMAGE *Aging(IMAGE *image);

/* Horizontal flip */
IMAGE *HFlip(IMAGE *image);

/* Edge detection */
IMAGE *Edge(IMAGE *image);

/* Add a watermark to an image */
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark,
                 unsigned int topLeftX, unsigned int topLeftY);

/* Spotlight */
IMAGE *Spotlight(IMAGE *image, int centerX, int centerY, unsigned int radius);

/* Zoom an image */
IMAGE *Zoom(IMAGE *image, unsigned int percentage);

#endif
