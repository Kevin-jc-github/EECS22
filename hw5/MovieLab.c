/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2022                   */
/*                                                                   */
/* Initial author: Tim Schmidt                                       */
/*                                                                   */
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height);

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();


int main(int argc, char *argv[])
{
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;
        MOVIE *loadedMovie = NULL;
	
	unsigned int frameNum = 0;
	unsigned int width = 512;
	unsigned int height = 288;

	/* the while loop to check options in the command line */
	while (x < argc) {

		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
				printf("The movie file %s has been read successfully!\n", fin);
			} /*fi*/
			else {
				printf("Missing argument for the input file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
				printf("output file is %s\n", fout);
			} /*fi*/
			else {
				printf("Missing argument for the output file name!\n");
				free(fin);
				free(fout);
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/
		
		/* the number of frames */
		if (strcmp(argv[x], "-f") == 0) {
			if (x < argc - 1) {
				if (sscanf(argv[x+1], "%u", &frameNum) == 0) {
				}
			} /*fi*/
			else {
				printf("Missing argument for the number of frames to load!\n");
				return 5;
			} /*esle*/
			x += 2;
			continue;
		} /*fi*/
		
		/* the image dimensions option */
		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc - 1) {
				if (sscanf(argv[x+1], "%ux%u", &width, &height) == 2) {
				} 
			} /*fi*/
			else {
				printf("Missing argument for image dimensions!\n");
				return 5;
			} /*esle*/
			x += 2;	
			continue;		
		} /*fi*/

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			free(fin);
			free(fout);
			return 0;
		} /*fi*/

		/**************************************************/
				
		/* activate the aging */
		if (0 == strcmp(argv[x], "-aging"))
		{
			if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				RGB2YUVMovie(loadedMovie);		
			}
			IENTRY *imgEntry, *nextEntry;
			ILIST *frames = loadedMovie->Frames;
			imgEntry = frames->First; 
			while(imgEntry) {
				nextEntry = imgEntry->Next;
				Aging(imgEntry->RGBImage);				
				imgEntry = nextEntry;
			}
			printf("Operation Aging is done!\n");
			break;
		}
		
		/* activate the horizontal flip */
		if (0 == strcmp(argv[x], "-hflip"))
		{
			if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				YUV2RGBMovie(loadedMovie);		
			}
			IENTRY *imgEntry, *nextEntry;
			ILIST *frames = loadedMovie->Frames;
			imgEntry = frames->First; 
			while(imgEntry) {
				nextEntry = imgEntry->Next;
				HFlip(imgEntry->RGBImage);				
				imgEntry = nextEntry;
			}
			printf("Operation HFlip is done!\n");
			break;
		}

		/* activate edge filter */	
		if (0 == strcmp(argv[x], "-edge"))
		{
			if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				YUV2RGBMovie(loadedMovie);		
			}
			IENTRY *imgEntry, *nextEntry;
			ILIST *frames = loadedMovie->Frames;
			imgEntry = frames->First; 
			while(imgEntry) {
				nextEntry = imgEntry->Next;
				Edge(imgEntry->RGBImage);				
				imgEntry = nextEntry;
			}
			printf("Operation Edge is done!\n");
			break;

		}

		/* to fast forward the video with the provided factor */
		/*if(0 == strcmp(argv[x], "-fast"))
                {
                      	if (x < argc-1)
                        {
                                if (sscanf(argv[x+1], "%d", &fast_factor) != 1)
                                {
                                        printf("Missing argument for fast!");
                                }
				if(fast_factor < 1)
				{
					printf("Invalid fast factor! Must be [1+]");
					return 5;
				}
                        }
                        else
                        {
                                printf("Missing argument for fast!");
                                return 5;
                        }

               		frameNum =  FastImageList(loadedMovie->Frames, fast_factor);	

			printf("Operation Fast is done!");
                        printf(" Number of Frames = %d\n", frameNum );
			x += 2;
                        continue;
	  
               	} */


		/* to reverse the frame order of the input stream */
		/*if (0 == strcmp(argv[x], "-reverse"))
               	 {
                        if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				YUV2RGBMovie(loadedMovie);		
			}
			IENTRY *imgEntry, *nextEntry;
			ILIST *frames = loadedMovie->Frames;
			imgEntry = frames->First; 
			ReverseImageList(frames);
			printf("Operation Reverse is done!\n");
			break;
               	 } */
		

		/* to zoom the frame order of the input stream */
		if (0 == strcmp(argv[x], "-zoom"))
               	 {
                        unsigned int perc = 0;
			unsigned int tmp = 0;	
			
			if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				YUV2RGBMovie(loadedMovie);		
			}
			
			IENTRY *imgEntry, *nextEntry;
			ILIST *frames = loadedMovie->Frames;
			imgEntry = frames->First; 
			
			while(imgEntry) {
				nextEntry = imgEntry->Next;
				Zoom(imgEntry->RGBImage, perc);
				if (tmp == 100 && perc != 0) {
					perc-=2;				
				} else {
					perc+=2;
					tmp+=2;
				}				
				imgEntry = nextEntry;
			}
			printf("Operation Zoom is done!\n");			
			x++;
			continue;
               	 }
		

		/* to make watermark for the frame order of the input stream */
		/*if (0 == strcmp(argv[x], "-watermark<file>"))
               	 {
                        srand(time(NULL));
			unsigned int topLeftX, topLeftY; 
			char ppm;
			IMAGE *ppmF;
			
			if (!loadedMovie) {
				loadedMovie = LoadMovie(fin, frameNum, width, height);
				YUV2RGBMovie(loadedMovie);		
			}
			if (x < argc - 1) {
				ppm = argv[x + 1];
				IENTRY *imgEntry, *nextEntry;
				ILIST *frames = loadedMovie->Frames;
				imgEntry = frames->First;
				ppmF = CreateImage(imgEntry->RGBImage->W, imgEntry->RGBImage->H); 
				while(imgEntry) {
					nextEntry = imgEntry->Next;
					Watermark(imgEntry->RGBImage, ppmF, rand()%width, rand()%height);
					imgEntry = nextEntry;
				}
				printf("Operation Watermark is done!\n");
			} 
			else {
				printf("Missing argument for start and end!\n");
				return 5;
			}	
			x++;
			continue;

               	 }*/
		  x++;

	}
	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}
	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		free(fin);
		free(fout);
		return 5;
	}

	//convert movie from RGB back to YUV
	RGB2YUVMovie(loadedMovie);
	//save and delete movie
	SaveMovie(fout, loadedMovie);
	DeleteMovie(loadedMovie);	

	fin = NULL;
	fout = NULL;

	return 0;
}


void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> -s <WIDTHxHEIGHT> [options]\n"
	       "Options:\n"
	       "-i <file> to provide the input <file> name\n"
               "-o <file> to provide the output <file> name\n"
                "-f <framenum> to determine how many frames are read from the input stream\n"
               "-s <WIDTHxHEIGHT> to set the resolution of the input stream (WIDTHxHEIGHT)\n"
	       "-aging                Activate the aging filter on every movie frame\n"
	       "-hflip                Activate horizontal flip on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-zoom                 Zoom in and out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVIMAGE* LoadOneFrame(const char* fname, int n,
                       unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVIMAGE* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
MOVIE *LoadMovie(const char *fname, int frameNum,
                 unsigned int width, unsigned height)
{
	assert(fname);
	assert(frameNum);
	assert(width);
	assert(height);	 
	MOVIE *movie = CreateMovie();
	for (int i = 0; i < frameNum; i++) {
		AppendYUVImage(movie->Frames, LoadOneFrame(fname, i, width, height));			
	}
	return movie;	
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, MOVIE *movie)
{
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}
	
	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {
		SaveOneFrame(curr->YUVImage, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVIMAGE *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}
