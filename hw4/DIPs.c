#include "DIPs.h"
#include "Image.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* make the picture color black & white */
IMAGE *BlackNWhite(IMAGE *image)
{
    assert(image);
    int i, j, tmp;

    for (j = 0; j < ImageHeight(image); j++)
    {   
        for (i = 0; i < ImageWidth(image); i++) 
        {
            tmp = (GetPixelR(image, i, j) + GetPixelG(image, i, j) + GetPixelB(image, i, j)) / 3;
            SetPixelR(image, i, j, tmp);
            SetPixelG(image, i, j, tmp);
            SetPixelB(image, i, j, tmp);
        }
    }
    return image;
}

/* reverse image color */
IMAGE *Negative(IMAGE *image)
{
    assert(image);
    int i, j;
    for (j = 0; j < ImageHeight(image); j++) {
        for (i = 0; i < ImageWidth(image); i++) 
        {
            SetPixelR(image, i, j, MAX_PIXEL - GetPixelR(image, i, j));
            SetPixelG(image, i, j, MAX_PIXEL - GetPixelG(image, i, j));
            SetPixelB(image, i, j, MAX_PIXEL - GetPixelB(image, i, j));
        }
    }
    return image;
}

/*colorfiler */
IMAGE *ColorFilter (IMAGE *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b)
{
    assert(image);
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
    int i, j;
    for (j = 0; j < ImageHeight(image); j++)
    {
        for (i = 0; i < ImageWidth(image); i++)
        {
            if (abs(GetPixelR(image, i, j) - target_r) <= threshold && abs(GetPixelG(image, i, j) - target_g) <= threshold && abs(GetPixelB(image, i, j) - target_b) <= threshold)
            {
                SetPixelR(image, i, j, replace_r);
                SetPixelG(image, i, j, replace_g);
                SetPixelB(image, i, j, replace_b);
            }
        }
    }
    return image;
}


/* Add edge to the image*/
IMAGE *Edge(IMAGE *image) {
    int             i, j, m, n, a, b;
    IMAGE *tmpImage = NULL;	/* Temporary image */
    tmpImage = CreateImage(image->W, image->H);	

    for (j = 0; j < image->H; j++){
        for (i = 0; i < image->W; i++) {
            SetPixelR(tmpImage, i, j, GetPixelR(image, i, j));
            SetPixelG(tmpImage, i, j, GetPixelG(image, i, j));
            SetPixelB(tmpImage, i, j, GetPixelB(image, i, j));
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (j = 1; j < image->H - 1; j++){
        for (i = 1; i < image->W - 1; i++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (i + m >= image->W) ? image->W - 1 : (i + m < 0) ? 0 : i + m;
                    b = (j + n >= image->H) ? image->H - 1 : (j + n < 0) ? 0 : j + n;
                    sumR += (GetPixelR(tmpImage, i, j) - GetPixelR(tmpImage, a, b));
                    sumG += (GetPixelG(tmpImage, i, j) - GetPixelG(tmpImage, a, b));
                    sumB += (GetPixelB(tmpImage, i, j) - GetPixelB(tmpImage, a, b));
                }
            }
            SetPixelR(image, i, j, ((sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR));
            SetPixelG(image, i, j, ((sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG));
            SetPixelB(image, i, j, ((sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB));
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (j = 0; j < image->H; j++) {
        SetPixelR(image, 0, j, 0);
        SetPixelG(image, 0, j, 0);
        SetPixelB(image, 0, j, 0);
        SetPixelR(image, image->W - 1, j, 0);
        SetPixelG(image, image->W - 1, j, 0);
        SetPixelB(image, image->W - 1, j, 0);
    }
    for (i = 0; i < image->W; i++) {
        SetPixelR(image, i, 0, 0);
        SetPixelG(image, i, 0, 0);
        SetPixelB(image, i, 0, 0);
        SetPixelR(image, i, image->H - 1, 0);
        SetPixelG(image, i, image->H - 1, 0);
        SetPixelB(image, i, image->H - 1, 0);
    }

    DeleteImage(tmpImage);

    return image;
}

/* flip image vertically */
IMAGE *VFlip(IMAGE *image)
{
    assert(image);   
    int             i, j;
    unsigned char   r, g, b;
    
    for (j = 0; j < (ImageHeight(image))/2; j++) 
    {
        for (i = 0; i < ImageWidth(image); i++) 
        {
            r = GetPixelR(image, i, ImageHeight(image) - 1 - j);
            g = GetPixelG(image, i, ImageHeight(image) - 1 - j);
            b = GetPixelG(image, i, ImageHeight(image) - 1 - j);
            
            SetPixelR(image, i, ImageHeight(image) - 1 - j, GetPixelR(image, i, j));
            SetPixelG(image, i, ImageHeight(image) - 1 - j, GetPixelG(image, i, j));
            SetPixelB(image, i, ImageHeight(image) - 1 - j, GetPixelB(image, i, j));
            
            SetPixelR(image, i, j, r);
            SetPixelG(image, i, j, g);
            SetPixelB(image, i, j, b);
        }
    }
    return image;
}


/* mirror image vertically */
IMAGE *VMirror(IMAGE *image) 
{
    assert(image);
    int i, j;
    for (j = 0; j < ImageHeight(image) / 2; j++) 
    {
        for (i = 0; i < ImageWidth(image); i++) 
        {
            SetPixelR(image, i, ImageHeight(image) - 1 - j, GetPixelR(image, i, j));
            SetPixelG(image, i, ImageHeight(image) - 1 - j, GetPixelG(image, i, j));
            SetPixelB(image, i, ImageHeight(image) - 1 - j, GetPixelB(image, i, j));
        }
    }
    return image;
}

int GenerateRandomNumber(int min, int max)
{
    return (rand()%(max - min) + min);
}

/* Shuffle the image */
IMAGE *Shuffle(IMAGE *image)
{
    assert(image);
    int x = 0;
    int y = 0;
    int i = 0;
    for(i = 0; i < 16; i++)
    {
        int random_i = GenerateRandomNumber(0, 15);
        for(y = 0; y < ImageHeight(image)/4; y++)
        {
            for(x = 0; x < ImageWidth(image)/4; x++)
            {
                int piece_width = ImageWidth(image)/4;
                int piece_height = ImageHeight(image)/4;
                int i_xpos = (i%4)*piece_width + x;
                int i_ypos = (i/4)*piece_height + y;
                int random_i_xpos = (random_i%4)*piece_width + x;
                int random_i_ypos = (random_i/4)*piece_height + y;
                int r_temp = GetPixelR(image, i_xpos, i_ypos);
                int g_temp = GetPixelG(image, i_xpos, i_ypos);
                int b_temp = GetPixelB(image, i_xpos, i_ypos);

                SetPixelR(image, i_xpos, i_ypos, GetPixelR(image, random_i_xpos, random_i_ypos));
                SetPixelG(image, i_xpos, i_ypos, GetPixelG(image, random_i_xpos, random_i_ypos));
                SetPixelB(image, i_xpos, i_ypos, GetPixelB(image, random_i_xpos, random_i_ypos));

                SetPixelR(image, random_i_xpos, random_i_ypos, r_temp);
                SetPixelG(image, random_i_xpos, random_i_ypos, g_temp);
                SetPixelB(image, random_i_xpos, random_i_ypos, b_temp);
            }
        }
    }
    return image;
}

/* add border to the image */
IMAGE *AddBorder(IMAGE *image, char color[SLEN], int border_width)
{
    assert(image); 
    int i, j;
    int border_r = 255;
    int border_g = 255;
    int border_b = 255;
    if (!strcmp(color, "black")) {
        border_r = 0;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "white")) {
        border_r = 255;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "red")) {
        border_r = 255;
        border_g = 0;
        border_b = 0;
    } else if (!strcmp(color, "green")) {
        border_r = 0;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "blue")) {
        border_r = 0;
        border_g = 0;
        border_b = 255;
    } else if (!strcmp(color, "yellow")) {
        border_r = 255;
        border_g = 255;
        border_b = 0;
    } else if (!strcmp(color, "cyan")) {
        border_r = 0;
        border_g = 255;
        border_b = 255;
    } else if (!strcmp(color, "pink")) {
        border_r = 255;
        border_g = 192;
        border_b = 203;
    } else if (!strcmp(color, "orange")) {
        border_r = 255;
        border_g = 165;
        border_b = 0;
    } else {
        printf("Unsurported color.\n");
        return image;
    }
    const int X_BORDER_WIDTH = border_width * 9 / 16;
    for (j = 0; j < ImageHeight(image); j++) {
        for (i = 0; i < ImageWidth(image); i++) {
            if ((j < border_width) || (j > ImageHeight(image) - 1 - border_width) ||
                    (i < X_BORDER_WIDTH) || (i > ImageWidth(image) - 1 - X_BORDER_WIDTH)) 
            {
                SetPixelR(image, i, j, border_r);
                SetPixelG(image, i, j, border_g);
                SetPixelB(image, i, j, border_b);
            }
        }
    }
    return image;
}
