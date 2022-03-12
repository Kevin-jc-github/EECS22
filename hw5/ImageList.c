/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ImageList.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "ImageList.h"
#include "Image.h"
#include "Movie.h"

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *imgList;
	imgList = malloc(sizeof(ILIST));
	if (!imgList) {
		perror("Out of memory yo! Aborting....");
		exit(10);	
	}
	imgList->Length = 0;
	imgList->First = NULL;
	imgList->Last = NULL;
	return imgList;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	IENTRY *f, *n;
	assert(list);
	f = list->First;
	while(f) { 
		n = f->Next;
		DeleteImage(f->RGBImage);
		DeleteYUVImage(f->YUVImage);
		f = n;
	}
	free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *l;
	IENTRY *newE = malloc(sizeof(IENTRY));
	assert(list);
	assert(RGBimage);
	l = list->Last;
	newE->RGBImage = RGBimage;
	newE->YUVImage = NULL;
	newE->List = list; 	
	if (!l) {
		newE->Prev = NULL;
		newE->Next = NULL;
		list->First = newE;
		list->Last = newE;	
	} else {
		newE->Prev = l;
		newE->Next = NULL;
		l->Next = newE;
		list->Last = newE;
	}
	list->Length++;	
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	IENTRY *l;
	IENTRY *newE = malloc(sizeof(IENTRY));
	assert(list);
	assert(YUVimage);
	l = list->Last;
	newE->RGBImage = NULL;
	newE->YUVImage = YUVimage;
	newE->List = list; 	
	if (!l) {
		newE->Prev = NULL;
		newE->Next = NULL;
		list->First = newE;
		list->Last = newE;	
	} else {
		newE->Prev = l;
		newE->Next = NULL;		
		l->Next = newE;
		list->Last = newE;
	}
	list->Length++;	
}


/* Crop an image list */
/*void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);
	assert(start);
	assert(end);
	IENTRY *imgEntry, *nextEntry;
	unsigned int counter = 0;
	imgEntry = list->First;
	while(list->Length != ((end-start) + 1)) {
		nextEntry = imgEntry->Next;
		if (counter < start) {
			DeleteImage(imgEntry->RGBImage);
			DeleteYUVImage(imgEntry->YUVImage);
			imgEntry->List = NULL;			
			imgEntry->Prev = NULL;
			imgEntry->Next = NULL;
			imgEntry->RGBImage = NULL;
			imgEntry->YUVImage = NULL;
			free(imgEntry);
			list->Length--;
		} else if (counter > end) {
			DeleteImage(imgEntry->RGBImage);
			DeleteYUVImage(imgEntry->YUVImage);
			DeleteImageList(imgEntry->List);
			imgEntry->List = NULL;			
			imgEntry->Prev = NULL;
			imgEntry->Next = NULL;
			imgEntry->RGBImage = NULL;
			imgEntry->YUVImage = NULL;
			free(imgEntry);
			list->Length--;	
		}
		imgEntry = nextEntry;		
		counter++;	
	}
}*/


/* Fast forward an image list */
/*void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	assert(factor);
	unsigned int count = 0;
	IENTRY *entry, *nextEntry;
	entry = list->First;
	while(entry) {
				
		count++;
		entry+=factor;			
	}
	list->Length = count;
	printf("Operation Fast Forward is done! New number of frames is %u.\n", count);
}*/

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
       assert(list);
    IENTRY *curr = NULL;
    IENTRY *next = NULL;
    IENTRY *prev = NULL;
    IENTRY *first = NULL;
    
    curr = list->First;
    first = list->First;
    while(curr != NULL)
    {
        next = curr->Next;
        prev = curr->Prev;
        if(curr == list->First)
        {
            curr->Prev = next;
            curr->Next = NULL;
        }
        else if(curr == list->Last)
        {
            curr->Next = prev;
            curr->Prev = NULL;
        }
        else
        {
            curr->Next = prev;
            curr->Prev = next;
        }

        curr = next;
    }
    list->First = list->Last;
    list->Last = first;
}

/* EOF */
