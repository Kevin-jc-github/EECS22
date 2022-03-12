
/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/* New author: Kevin Zhu                                             */
/* Movie.c: source file for basic movie manipulations                */
/* Date: 2022/02/30                                                  */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Movie.h"
#include "ImageList.h"
#include "Image.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */

unsigned char clip(unsigned char value) {
	if (value < 0) {
		value = 0;	
	} else if (value > 255) {
		value = 255;
	} 
	return value;
}

MOVIE *CreateMovie(void)
{
	MOVIE *movie;
	movie = malloc(sizeof(MOVIE));
	if (!movie) {
		perror("Out of memory yo! Aborting....");
		exit(10);	
	}
	movie->Frames = CreateImageList();
	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	ILIST *f;
	assert(movie);
	f = movie->Frames;
	DeleteImageList(f);
	free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *imgEntry, *nextEntry;
	IMAGE *img;
	unsigned char c, d, e;
	unsigned char clipR, clipG, clipB;
	ILIST *imgList = movie->Frames; 
	imgEntry = imgList->First; 
	while(imgEntry) {
		assert(imgEntry);
		nextEntry = imgEntry->Next;
		img = CreateImage(imgEntry->YUVImage->W, imgEntry->YUVImage->H);
		for (int x = 0; x < imgEntry->YUVImage->W; x++) {
			for (int y = 0; y < imgEntry->YUVImage->H; y++) {
				c = GetPixelY(imgEntry->YUVImage, x, y) - 16;
				d = GetPixelU(imgEntry->YUVImage, x, y) - 128;
				e = GetPixelV(imgEntry->YUVImage, x, y) - 128;
				clipR = clip((298 * c + 409 * e + 128) >> 8);
				clipG = clip((298 * c - 100 * d - 208 * e + 128) >> 8);
				clipB = clip((298 * c + 516 * d + 128) >> 8);
				SetPixelR(img, x, y, clipR);
				SetPixelG(img, x, y, clipG);
				SetPixelB(img, x, y, clipB);
				imgEntry->RGBImage = img;		
			}	
		}
		imgEntry = nextEntry;
	}
			
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie);
	IENTRY *imgEntry, *nextEntry; 
	YUVIMAGE *yuvImg;
	unsigned char clipY, clipU, clipV;
	ILIST *imgList = movie->Frames;
	imgEntry = imgList->First;
	while(imgEntry) {
		assert(imgEntry);
		nextEntry = imgEntry->Next;
		yuvImg = CreateYUVImage(imgEntry->RGBImage->W, imgEntry->RGBImage->H);
		for (int x = 0; x < imgEntry->RGBImage->W; x++) {
			for (int y = 0; y < imgEntry->RGBImage->H; y++) {
				clipY = clip( ( ( 66 * GetPixelR(imgEntry->RGBImage, x, y) + 129 * GetPixelG(imgEntry->RGBImage, x, y) + 25 * GetPixelB(imgEntry->RGBImage, x, y) + 128) >> 8) + 16 );
				clipU =  clip( ( ( -38 * GetPixelR(imgEntry->RGBImage, x, y) - 74 * GetPixelG(imgEntry->RGBImage, x, y) + 112 * GetPixelB(imgEntry->RGBImage, x, y) + 128) >> 8) + 128 );
				clipV = clip( ( ( 112 * GetPixelR(imgEntry->RGBImage, x, y) - 94 * GetPixelG(imgEntry->RGBImage, x, y) - 18 * GetPixelB(imgEntry->RGBImage, x, y) + 128) >> 8) + 128 );
				SetPixelY(yuvImg, x, y, clipY);
				SetPixelU(yuvImg, x, y, clipU);
				SetPixelV(yuvImg, x, y, clipV);
				imgEntry->YUVImage = yuvImg;		
			}	
		}
		imgEntry = nextEntry;		
	}	 
		
}

/* EOF */
