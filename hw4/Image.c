#include "Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y)
{
    assert(image);
    assert(x <= image->W && y <= image->H); 
    return image->R[x + y * image->W];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y)
{
    assert(image);
    assert(x <= image->W && y <= image->H);   
    return image->G[x + y * image->W];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y)
{
    assert(image);
    assert(x <= image->W && y <= image->H);
    return image->B[x + y * image->W];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r)
{
    assert(image);
    assert(x <= image->W && y <= image->H);
    image->R[x + y * image->W] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
    assert(image);
    assert(x <= image->W && y <= image->H);
    image->G[x + y * image->W] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
    assert(image);
    assert(x <= image->W && y <= image->H);
    image->B[x + y * image->W] = b;
}

IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
    IMAGE *image;
    image = malloc(sizeof(IMAGE));
    if (! image)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }

    image->W = Width;
    image->H = Height;

    image->R = malloc(sizeof(unsigned char) * Width * Height);
    if (! image->R)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }

    image->G = malloc(sizeof(unsigned char) * Width * Height);
    if (! image->G)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }

    image->B = malloc(sizeof(unsigned char) * Width * Height); 
    if (! image->B)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }

    return image;
}

void DeleteImage(IMAGE *image)
{
    assert(image);
    free(image->R);
    free(image->G);
    free(image->B);
    image->R = NULL;
    image->G = NULL;
    image->B = NULL;
    free(image);
    image = NULL; 
}

unsigned int ImageWidth(const IMAGE *image)
{
    assert(image);
    return image->W;
}

unsigned int ImageHeight(const IMAGE *image)
{
    assert(image);   
    return image->H;
}