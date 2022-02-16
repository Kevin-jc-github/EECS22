/*********************************************************************/
/* PhotoLab_v2.c: Template for assignment #3, EECS 22, Winter 2022   */
/*                                                                   */
/*                                                                   */
/* Comments: Enjoy Learning new things!:)                            */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SLEN 80 		/* maximum length of file names and string*/
static const int SUCCESS=0;		/* return code for success */
static const int EXIT=12;			/* menu item number for EXIT */
static const int MAX_PIXEL=255;	/* max pixel value */
static const int MIN_PIXEL=0;		/* min pixel value */
static const int SHUFF_HEIGHT_DIV=4;      /* Height division for shuffleing */
static const int SHUFF_WIDTH_DIV=4;       /* Width division for shuffleing */

const int WIDTH = 512;		/* image width */
const int HEIGHT = 288;		/* image height */

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

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

/* add noise to an image */
void Noise( int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


int main() {
	unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];

	int ChoiceByUser;			/* user input option */
	char fname[SLEN];		/* input file name */
	char colorOption[SLEN];

	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &ChoiceByUser);

	int rc = -1;			/* return code of ReadImage() */
	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;
	/* AddBorder() parameter */
	int border_width;


	while (ChoiceByUser != EXIT) {
		if (ChoiceByUser == 1) {
			printf("Please input the file name to load: ");
			scanf("%75s", fname);
			rc = LoadImage(fname, R, G, B);
		}
		/* menu item 2 - 10 requires image is loaded first */
		else if (ChoiceByUser >= 2 && ChoiceByUser <= 10) {
			if (rc != SUCCESS)	 {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {
				switch(ChoiceByUser) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%75s", fname);
						SaveImage(fname, R, G, B);
						break;
					case 3:
						BlackNWhite(R, G, B);
						printf("\"Black & White\" operation is done!\n");
						break;
					case 4:
						Negative(R,G,B);
						printf("\"Negative\" operation is done!\n");
						break;
					case 5:
						printf("Enter Red   component for the target color: ");
						scanf("%d", &target_r);
						printf("Enter Green component for the target color: ");
						scanf("%d", &target_g);
						printf("Enter Blue  component for the target color: ");
						scanf("%d", &target_b);
						printf("Enter threshold for the color difference: ");
						scanf("%d", &threshold);
						printf("Enter value for Red component in the target color: ");
						scanf("%lf", &factor_r);
						printf("Enter value for Green component in the target color: ");
						scanf("%lf", &factor_g);
						printf("Enter value for Blue  component in the target color: ");
						scanf("%lf", &factor_b);

						ColorFilter(R, G, B, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
						printf("\"Color Filter\" operation is done!\n");
						break;
					case 6:
						Edge(R, G, B);
						printf("\"Edge\" operation is done!\n");
						break;
					case 7:
						Shuffle(R, G, B);
						printf("\"Shuffle\" operation is done!\n");
						break;
					case 8:
						VFlip(R, G, B);
						printf("\"VFlip\" operation is done!\n");
						break;
					case 9:
						VMirror(R, G, B);
						printf("\"Vertically Mirror\" operation is done!\n");
						break;
					case 10:
						printf("Enter border width:");
						scanf("%d", &border_width);
						printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
						printf("Select border color from the options: ");
						scanf("%s",colorOption);
						AddBorder(R, G, B, colorOption, border_width);
						printf("\"Border\" operation is done!\n");
						break;

					default:
						break;
				}
			}
		}
		else if (ChoiceByUser == 11) {
			AutoTest(R,G,B);
			rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
		}
		else {
			printf("Invalid selection!\n");
		}

		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &ChoiceByUser);
	}
	printf("You exit the program.\n");
	return 0;
}


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	FILE           *File;
	char            Type[SLEN];
	int             Width, Height, MaxValue;
	int             x, y;
	char            ftype[] = ".ppm";
	char            fname_tmp[SLEN];      
	strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);

	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("Cannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read.\n", fname_tmp);
	fclose(File);
	return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	FILE	*File;
	int	x, y;
	char	SysCmd[SLEN * 5];

	char	ftype[] = ".ppm";
	char	fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
	char	fname_tmp2[SLEN];

	strcpy(fname_tmp, fname);
	strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("Cannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved. \n", fname_tmp2);

	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw3.tcsh %s", fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored.\n", fname_tmp);
	return 0;
}

/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Example of DIP: YOU WONT CALL THIS FUNCTION */
/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	int x, y;
	for(y = 0; y < HEIGHT; y++ ) {
		for(x = 0; x < WIDTH; x++ ) {
			B[x][y] = (R[x][y] + G[x][y] + B[x][y]) / 5;
			R[x][y] = (unsigned char) (B[x][y] * 1.6);
			G[x][y] = (unsigned char) (B[x][y] * 1.6);
		}
	}
}

void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image vertically\n");
	printf("10: Add border to an image\n");
	printf("11: Test all functions\n");
	printf("12: Exit\n");
}

/* make the picture color black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x, y, tmp;

	for (y = 0; y < HEIGHT; y++)
	{   
		for (x = 0; x < WIDTH; x++) 
		{
			tmp = (R[x][y] + G[x][y] + B[x][y]) / 3;
			R[x][y] = G[x][y] = B[x][y] = tmp;
		}
	}
}

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	int x, y;
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = MAX_PIXEL - R[x][y];
			G[x][y] = MAX_PIXEL - G[x][y];
			B[x][y] = MAX_PIXEL - B[x][y];
		}
	}
}

void ColorFilter (unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
		int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {

	int x, y;

	replace_r = (replace_r > MAX_PIXEL)? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
	replace_g = (replace_g > MAX_PIXEL)? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
	replace_r = (replace_b > MAX_PIXEL)? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++){
			if (abs(R[x][y] - target_r) <= threshold
					&& abs(G[x][y] - target_g) <= threshold
					&& abs(B[x][y] - target_b) <= threshold) {
				R[x][y] = replace_r;
				G[x][y] = replace_g;
				B[x][y] = replace_b;
			}
		}
	}
}

void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	int             x, y, m, n, a, b;
	unsigned char   tmpR[WIDTH][HEIGHT];
	unsigned char   tmpG[WIDTH][HEIGHT];
	unsigned char   tmpB[WIDTH][HEIGHT];
	for (y = 0; y < HEIGHT; y++){
		for (x = 0; x < WIDTH; x++) {
			tmpR[x][y] = R[x][y];
			tmpG[x][y] = G[x][y];
			tmpB[x][y] = B[x][y];
		}
	}
	int sumR = 0;   /* sum of the intensity differences with neighbors */
	int sumG = 0;
	int sumB = 0;
	for (y = 1; y < HEIGHT - 1; y++){
		for (x = 1; x < WIDTH - 1; x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
					b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
					sumR += (tmpR[x][y] - tmpR[a][b]);
					sumG += (tmpG[x][y] - tmpG[a][b]);
					sumB += (tmpB[x][y] - tmpB[a][b]);
				}
			}
			R[x][y] = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
			G[x][y] = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
			B[x][y] = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
			sumR = sumG = sumB = 0;
		}
	}
	/* set all four borders to 0 */
	for (y = 0; y < HEIGHT; y++) {
		R[0][y] = 0;
		G[0][y] = 0;
		B[0][y] = 0;
		R[WIDTH - 1][y] = 0;
		G[WIDTH - 1][y] = 0;
		B[WIDTH - 1][y] = 0;
	}
	for (x = 0; x < WIDTH; x++) {
		R[x][0] = 0;
		G[x][0] = 0;
		B[x][0] = 0;
		R[x][HEIGHT - 1] = 0;
		G[x][HEIGHT - 1] = 0;
		B[x][HEIGHT - 1] = 0;
	}
}

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int             x, y;
	unsigned char   r, g, b;

	for (y = 0; y < HEIGHT/2; y ++) 
	{
		for (x = 0; x < WIDTH; x ++) 
		{
			r = R[x][HEIGHT - 1 - y];
			g = G[x][HEIGHT - 1 - y];
			b = B[x][HEIGHT - 1 - y];

			R[x][HEIGHT - 1 - y] = R[x][y];
			G[x][HEIGHT - 1 - y] = G[x][y];
			B[x][HEIGHT - 1 - y] = B[x][y];

			R[x][y] = r;
			G[x][y] = g;
			B[x][y] = b;
		}
	}
}

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	int x, y;
	for (y = 0; y < HEIGHT / 2; y ++) {
		for (x = 0; x < WIDTH; x ++) {
			R[x][HEIGHT - 1 - y] = R[x][y];
			G[x][HEIGHT - 1 - y] = G[x][y];
			B[x][HEIGHT - 1 - y] = B[x][y];
		}
	}
}


/* Shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int block_cnt = SHUFF_HEIGHT_DIV * SHUFF_WIDTH_DIV;
	int block_width = WIDTH/SHUFF_WIDTH_DIV;
	int block_height = HEIGHT/SHUFF_HEIGHT_DIV;
	int block[SHUFF_WIDTH_DIV][SHUFF_HEIGHT_DIV];
	int i, j;


	srand(time(NULL));
	/* Initialize block markers to not done (-1) */
	for (i = 0; i < SHUFF_WIDTH_DIV; i++) {
		for (j = 0; j< SHUFF_HEIGHT_DIV; j++) {
			block[i][j] = -1;
		}
	}

	while (block_cnt > 0) {
		/* Generate a random pair of blocks */
		int dest_height = rand() % SHUFF_HEIGHT_DIV;
		int dest_width = rand() % SHUFF_WIDTH_DIV;
		int src_height = rand() % SHUFF_HEIGHT_DIV;
		int src_width = rand() % SHUFF_WIDTH_DIV;

		/* Check if these blocks are already swaped, if not swap blocks */
		if ((block[dest_width][dest_height] == -1) && (block[src_width][src_height] == -1)) {
			/* Swap blocks */
			for (i = 0; i < block_height; i++) {
				/* Init src and dest height offset */
				int h_dest = ((dest_height * block_height) + i) % HEIGHT;
				int h_src  = ((src_height * block_height) + i) % HEIGHT; 
				for (j = 0; j < block_width; j++) {
					int temp;
					/* Init src and dest width offset */
					int w_src  = ((src_width * block_width) + j) % WIDTH; 
					int w_dest = ((dest_width * block_width) + j) % WIDTH;

					temp = R[w_dest][h_dest];
					R[w_dest][h_dest] = R[w_src][h_src];
					R[w_src][h_src] = temp;

					temp = G[w_dest][h_dest];
					G[w_dest][h_dest] = G[w_src][h_src];
					G[w_src][h_src] = temp;

					temp = B[w_dest][h_dest];
					B[w_dest][h_dest] = B[w_src][h_src];
					B[w_src][h_src] = temp;
				}
			}
			/* Set marker as done */
			block[dest_width][dest_height] = 1;
			block[src_width][src_height] = 1;
			/* Decrease block count */
			block_cnt -= 2; /* Two blocks are swapped */
		}

	}


}

/* add border to the image */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT],
		char color[SLEN], int border_width) {
	int x, y;
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
		return;
	}
	const int X_BORDER_WIDTH = border_width * 9 / 16;
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			if ((y < border_width) || (y > HEIGHT - 1 - border_width) ||
					(x < X_BORDER_WIDTH) || (x > WIDTH - 1 - X_BORDER_WIDTH)) {
				R[x][y] = border_r;
				G[x][y] = border_g;
				B[x][y] = border_b;
			}
		}
	}
}

void AutoTest(unsigned char R[WIDTH][HEIGHT] ,unsigned char G[WIDTH][HEIGHT],unsigned char B[WIDTH][HEIGHT]){

	char fname[SLEN] = "EngPlaza";

	LoadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	SaveImage("bw", R, G, B);
	printf("Black & White tested!\n\n");

	LoadImage(fname, R, G, B);
	Negative(R, G, B);
	SaveImage("negative", R, G, B);
	printf("Negative tested!\n\n");

	LoadImage(fname, R, G, B);
	ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
	SaveImage("colorfilter", R, G, B);
	printf("Color Filter tested!\n\n");

	LoadImage(fname, R, G, B);
	Edge(R, G, B);
	SaveImage("edge", R, G, B);
	printf("Edge Detection tested!\n\n");

	LoadImage(fname, R, G, B);
	VMirror(R, G, B);
	SaveImage("vmirror", R, G, B);
	printf("VMirror tested!\n\n");

	LoadImage(fname, R, G, B);
	VFlip(R, G, B);
	SaveImage("vflip", R, G, B);
	printf("VFlip tested!\n\n");

	LoadImage(fname, R, G, B);
	Shuffle(R, G, B);
	SaveImage("shuffle", R, G, B);
	printf("Shuffle tested!\n\n");	

	LoadImage(fname, R, G, B);
	AddBorder (R, G, B, "pink", 64);
	SaveImage("border", R, G, B);
	printf("Border tested!\n\n");
}
