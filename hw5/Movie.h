/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/* New author: Kevin Zhu                                             */
/* Movie.h: header file for basic movie manipulations                */
/* Date: 2022/02/30                                                  */
/*********************************************************************/

#ifndef MOVIE_H
#define MOVIE_H

#include "ImageList.h"

/* the movie structure */
typedef struct {
	ILIST *Frames; /* Pointer to the frame list */
} MOVIE;

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void);

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie);

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie);

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie);

#endif
