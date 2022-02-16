/*******************************************************************************/ 
/* Advanced.c: contains the function definitions of new filters in Assignment 3*/ 
/*                                                                             */
/* 2022/01/31 Jiancong Zhu: initial solution version                           */
/*                       for EECS22 assignment3  winter 22                     */
/*******************************************************************************/

#include "Constants.h"
#include "Advanced.h"

/* Add noise to image */
void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    
	srand(time(NULL));
	int i, j;
	int count = n*WIDTH*HEIGHT/100;
	while(count>0) {
		i = rand() % WIDTH;
		j = rand() % HEIGHT;
		R[i][j] = B[i][j] = G[i][j] = 255; 
		count--;
		
	}
}

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    int R_temp[WIDTH][HEIGHT];
    int G_temp[WIDTH][HEIGHT];
    int B_temp[WIDTH][HEIGHT];
    int i,j = 0;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0; j < HEIGHT; j++) {
            R_temp[i][j] = R[i][j];
            B_temp[i][j] = B[i][j];
            G_temp[i][j] = G[i][j]; 
        }
    }
    i = 1;
    j = 1;
    for (i = 1; i < WIDTH-1; i++) {
        for (j = 1; j < HEIGHT-1; j++) {
            int red = 9*R_temp[i][j]-R_temp[i-1][j-1]-R_temp[i][j-1]-R_temp[i+1][j-1]-R_temp[i-1][j]-R_temp[i+1][j]-R_temp[i-1][j+1]-R_temp[i][j+1]-R_temp[i+1][j+1];
            int green = 9*G_temp[i][j]-G_temp[i-1][j-1]-G_temp[i][j-1]-G_temp[i+1][j-1]-G_temp[i-1][j]-G_temp[i+1][j]-G_temp[i-1][j+1]-G_temp[i][j+1]-G_temp[i+1][j+1];
            int blue = 9*B_temp[i][j]-B_temp[i-1][j-1]-B_temp[i][j-1]-B_temp[i+1][j-1]-B_temp[i-1][j]-B_temp[i+1][j]-B_temp[i-1][j+1]-B_temp[i][j+1]-B_temp[i+1][j+1];
            if (red < 0) {
                red = 0;
            } else if (red > 255) {
                red = 255;
            }
            if (green < 0) {
                green = 0;
            } else if (green > 255) {
                green = 255;
            }
            if (blue < 0) {
                blue = 0;
            } else if (blue > 255) {
                blue = 255;
            }
            R[i][j] = red;
            G[i][j] = green; 
            B[i][j] = blue;
        }
    }
}


/* Posterizes the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbit, unsigned int gbit, unsigned int bbit)
{
    int i, j = 0;
    int r, g, b;
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            /* Set the bit posterization to zero */ 
            R[i][j] &= ~(1 << (rbit - 1));
            G[i][j] &= ~(1 << (gbit - 1));
            B[i][j] &= ~(1 << (bbit - 1));


            for(r = 0; r < rbit - 1; r++)
            {
                R[i][j] |= 1 << r;     
            }

            for(g = 0; g < gbit - 1; g++)
            {
                G[i][j] |= 1 << g;
            }

            for(b = 0; b < bbit - 1; b++)
            {
                B[i][j] |= 1 << b;
            }
        }   
    } 	
}


/*motion blur*/
void MotionBlur(int bluramount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int             i, j;
    int             offset;
    int             sumR = 0;
    int             sumG = 0;
    int             sumB = 0;
    int             count = 0;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    for (j = 0; j < HEIGHT; j++){
        for (i = 0; i < WIDTH; i++) {
            tmpR[i][j] = R[i][j];
            tmpG[i][j] = G[i][j];
            tmpB[i][j] = B[i][j];
        }
    }
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            for(offset = 1; offset <= bluramount; offset++)
            {
                if((i + offset) <= WIDTH)
                {
                    sumR += R[i + offset][j];
                    sumG += G[j + offset][j];
                    sumB += B[j + offset][j];
                    count++;
                }                    
            } 
            R[i][j] = (R[i][j] + (sumR/count))/2; 
            G[i][j] = (G[i][j] + (sumG/count))/2;
            B[i][j] = (B[i][j] + (sumB/count))/2;
            sumR = 0;
            sumG = 0;
            sumB = 0;
            count = 0;
        }
    }
} 
 