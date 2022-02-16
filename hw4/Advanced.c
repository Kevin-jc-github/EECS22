#include "Advanced.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n)
{
        assert(image);
	int i, j, x;
	int num; /* number of noise added */
	num = ( n * ImageHeight(image) * ImageWidth(image))/100;
	srand(time(NULL));

	for ( x = 0; x < num; x++ ) 
        {
		i = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		j = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
                
                SetPixelR(image, i, j, 255);
                SetPixelG(image, i, j, 255);
                SetPixelB(image, i, j, 255);		
	}
        return image;
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
{
    assert(image);
	int		i, j, x, y, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;
        IMAGE *temp = CreateImage(ImageWidth(image), ImageHeight(image));  
	
	for (j = 0; j < ImageHeight(image); j++){
		for (i = 0; i < ImageWidth(image); i++) {
			SetPixelR(temp, i, j, GetPixelR(image, i, j));
                        SetPixelG(temp, i, j, GetPixelG(image, i, j));
                        SetPixelB(temp, i, j, GetPixelB(image, i, j));
		}
	}

	for (j = 0; j < ImageHeight(image); j++){
		for (i = 0; i < ImageWidth(image); i++){
			for (y = -1; y <= 1; y++){
				for (x = -1; x <= 1; x++) {
					a = i + x;
					b = j + y;
					if (a > ImageWidth(image) - 1)
						a = ImageWidth(image) - 1;
					if (a < 0)
						a = 0;
					if (b > ImageHeight(image) - 1)
						b = ImageHeight(image) - 1;
					if (b < 0)
						b = 0;
					
					if ((y==0)&&(x==0))
					{
						tmpR += 9*GetPixelR(temp, a, b); 
						tmpG += 9*GetPixelG(temp, a, b);
                				tmpB += 9*GetPixelB(temp, a, b); 
					}
					else
					{
						tmpR -= GetPixelR(temp, a, b); 
						tmpG -= GetPixelG(temp, a, b);
						tmpB -= GetPixelB(temp, a, b); 
					}
				}
			}
			SetPixelR(image, i, j, (tmpR>255)? 255: (tmpR<0)? 0: tmpR);
			SetPixelG(image, i, j, (tmpG>255)? 255: (tmpG<0)? 0: tmpG);
			SetPixelB(image, i, j, (tmpB>255)? 255: (tmpB<0)? 0: tmpB);
		  	tmpR = tmpG = tmpB = 0; 	
		}
	}
        DeleteImage(temp);
        return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbit, unsigned int gbit, unsigned int bbit)
{
    assert(image);
    int i, j = 0;
    int r, g, b;
    unsigned char rbitTemp, gbitTemp, bbitTemp;
    unsigned char rbitTemp2, gbitTemp2, bbitTemp2;

    for(j = 0; j < ImageHeight(image); j++)
    {
        for(i = 0; i < ImageWidth(image); i++)
        {
            /* We are going to set the bit posterization to zero */
            rbitTemp = GetPixelR(image, i, j);
            rbitTemp &= ~(1 << (rbit - 1));
            SetPixelR(image, i, j, rbitTemp);
            
            gbitTemp = GetPixelG(image, i, j);
            gbitTemp &= ~(1 << (gbit - 1));
            SetPixelG(image, i, j, gbitTemp);

            bbitTemp = GetPixelB(image, i, j);
            bbitTemp &= ~(1 << (bbit - 1));
            SetPixelB(image, i, j, bbitTemp);

            /* Loops through the R and loops through the bits that are less than rbit and sets them to 1 */
            for(r = 0; r < rbit - 1; r++)
            {
                rbitTemp2 = GetPixelR(image, i, j);
                rbitTemp2 |= 1 << r;
                SetPixelR(image, i, j, rbitTemp2); 
            }
            /* Loops through the G and loops through the bits that are less than gbit and sets them to 1 */
            for(g = 0; g < gbit - 1; g++)
            {
                gbitTemp2 = GetPixelG(image, i, j); 
                gbitTemp2 |= 1 << g;
                SetPixelG(image, i, j, gbitTemp2);
            }
            /* Loops through the B and loops through the bits that are less than bbit and sets them to 1 */
            for(b = 0; b < bbit - 1; b++)
            {
                bbitTemp2 = GetPixelB(image, i, j);
                bbitTemp2 |= 1 << g;
                SetPixelB(image, i, j, bbitTemp2);
            }
        }
    }
    return image;
}


/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
	assert(image);
        int i,j,x;
	unsigned int temp_r , temp_g , temp_b;

	for (i = 0; i < ImageWidth(image); i++)
        	for (j = 0; j < ImageHeight(image) ; j++) 
		{
			temp_r = GetPixelR(image, i, j)/2;
			temp_g = GetPixelG(image, i, j)/2;
			temp_b = GetPixelB(image, i, j)/2;
			
			for (x = 1; x<=BlurAmount ; x++)
			{
				if ((i+x) < ImageWidth(image))
				{
					temp_r = temp_r + GetPixelR(image, i+x, j) * 0.5/BlurAmount;
					temp_g = temp_g + GetPixelG(image, i+x, j) * 0.5/BlurAmount;
					temp_b = temp_b + GetPixelB(image, i+x, j) * 0.5/BlurAmount;
				}
			}	
			SetPixelR(image, i, j, temp_r);
                        SetPixelG(image, i, j, temp_g);
                        SetPixelB(image, i, j, temp_b); 
		}	
        return image;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H)
{
    assert(image);
    int croppedi, croppedj;

    if(x + W > ImageWidth(image))
    {
        W = ImageWidth(image) - x;
    } 
    if(y + H > ImageHeight(image))
    {
        H = ImageHeight(image) - y;
    }
    IMAGE *cropped = CreateImage(W, H);

    for(croppedj = 0; croppedj < ImageHeight(cropped); croppedj++)
    {
        for(croppedi = 0; croppedi < ImageWidth(cropped); croppedi++)
        {
            SetPixelR(cropped, croppedi, croppedj, GetPixelR(image, x + croppedi, y + croppedj));
            SetPixelG(cropped, croppedi, croppedj, GetPixelG(image, x + croppedi, y + croppedj));
            SetPixelB(cropped, croppedi, croppedj, GetPixelB(image, x + croppedi, y + croppedj));
        }
    }
    DeleteImage(image);
    return cropped;     
}

IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast)
{
    assert(image);
    int i, j;
    int pixelContrastR, pixelContrastG, pixelContrastB;
    int newPixelR, newPixelG, newPixelB;
    double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

    for(j = 0; j < ImageHeight(image); j++)
    {
        for(i = 0; i < ImageWidth(image); i++)
        {
            pixelContrastR = (int)(factor * (GetPixelR(image, i, j) - 128) + 128);
            pixelContrastG = (int)(factor * (GetPixelG(image, i, j) - 128) + 128);
            pixelContrastB = (int)(factor * (GetPixelB(image, i, j) - 128) + 128);

            newPixelR = pixelContrastR + brightness;
            newPixelG = pixelContrastG + brightness;
            newPixelB = pixelContrastB + brightness;

            if (newPixelR > 255)
            {
                newPixelR = 255;   
            }
            else if (newPixelR < 0)
            {
                newPixelR = 0;
            }

            if (newPixelG > 255)
            {
                newPixelG = 255;
            }
            else if (newPixelG < 0)
            {
                newPixelG = 0;
            }

            if (newPixelB > 255)
            {
                newPixelB = 255;
            }
            else if (newPixelB < 0)
            {
                newPixelB = 0;
            }

            SetPixelR(image, i, j, newPixelR);
            SetPixelG(image, i, j, newPixelG);
            SetPixelB(image, i, j, newPixelB);
        } 
    }
    return image;
}

IMAGE *Resize(IMAGE *image, int percentage)
{
    assert(image);
    int i, j;
    int originalX, originalY;
    if (percentage == 100)
    {
        return image;
    }

    int scaledWidth = ImageWidth(image) * (percentage / 100.00);
    int scaledHeight = ImageHeight(image) * (percentage / 100.00);
    
    IMAGE *scaled = CreateImage(scaledWidth, scaledHeight);
    if (percentage > 100)
    {
        for (j = 0; j < ImageHeight(scaled); j++)
        {
            for (i = 0; i < ImageWidth(scaled); i++)
            {
                originalX = (int)i*ImageWidth(image)/scaledWidth; 
                originalY = (int)j*ImageHeight(image)/scaledHeight;
                SetPixelR(scaled, i, j, GetPixelR(image, originalX, originalY));
                SetPixelG(scaled, i, j, GetPixelG(image, originalX, originalY));
                SetPixelB(scaled, i, j, GetPixelB(image, originalX, originalY));
            }
        }         
    }
    else
    {
        for (j = 0; j < ImageHeight(scaled); j++)
        {
            for (i = 0; i < ImageWidth(scaled); i++)
            {
                originalX = (int)i*ImageWidth(image)/scaledWidth;
                originalY = (int)j*ImageHeight(image)/scaledHeight;
                SetPixelR(scaled, i, j, GetPixelR(image, originalX, originalY));
                SetPixelG(scaled, i, j, GetPixelG(image, originalX, originalY));
                SetPixelB(scaled, i, j, GetPixelB(image, originalX, originalY));
            }
        }

    }
    DeleteImage(image);
    return scaled;   
}

IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image)
{
    assert(image);
    int i, j;
    int watermarkR, watermarkG, watermarkB;
    int tempR, tempG, tempB;

    for (j = 0; j < ImageHeight(image); j++)
    {
        for (i = 0; i < ImageWidth(image); i++)
        {
            watermarkR = GetPixelR(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image));
            watermarkG = GetPixelG(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image));
            watermarkB = GetPixelB(watermark_image, i % ImageWidth(watermark_image), j % ImageHeight(watermark_image));
            if ((watermarkR + watermarkG + watermarkB) == 0)
            {
                tempR = GetPixelR(image, i, j) * 1.45;
                if(tempR > 255)
                {
                    tempR = 255;   
                }    
                SetPixelR(image, i, j, tempR);
                
                tempG = GetPixelG(image, i, j) * 1.45;
                if(tempG > 255)
                {
                    tempG = 255;
                }
                SetPixelG(image, i, j, tempG);

                tempB = GetPixelB(image, i, j) * 1.45; 
                if(tempB > 255)
                {
                    tempB = 255;
                }
                SetPixelB(image, i, j, tempB);
            }
        }
    }
    return image;    
}