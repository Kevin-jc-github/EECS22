/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2022                 */
/* author: Kevin Zhu(Jiancong Zhu)                                   */
/* Complete date: 2022/01/13
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
const int WIDTH  = 512;      /* image width */
const int HEIGHT = 288;      /* image height */
const int SLEN   =  80;      /* max. string length */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
int LoadImage(const char fname[SLEN], 
	      unsigned char R[WIDTH][HEIGHT],
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], 
	      unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], 
		 unsigned char G[WIDTH][HEIGHT], 
		 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], 
		 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], 
		 int target_r, int target_g, int target_b, int threshold, 
		 int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], 
	  unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], 
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], 
	     unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], 
	       unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], 
	       char color[SLEN], int border_width);

/* Check the bound */
void Boundcheck(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r_sum, int g_sum, int b_sum, int i, int j);


/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], 
	   unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], 
	      unsigned char G[WIDTH][HEIGHT], 
	      unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
    char fname[SLEN];
    int choice;
    int r_target, g_target, b_target;
    int threshold;
    int r_replace, g_replace, b_replace;
    int inputwidth = 0;
    char color[79];
    
     srand(time(NULL)); 

    /* Please replace the following code with proper menu with function calls for DIP operations */
        while(1)
    {
        PrintMenu();
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                      printf("Please input the file name to load: ");
                      scanf("%s", fname);
                      LoadImage(fname, R, G, B);
                      break;
            case 2:
                      printf("Please input the file name to save: ");
                      scanf("%79s", &fname[0]);
                      SaveImage(fname, R, G, B);
                      break;
            case 3:
                      BlackNWhite(R, G, B);
                      printf("\"Black & White\" operation is done!\n");
                      SaveImage("bw", R, G, B);
                      break;
            case 4:
                      Negative(R, G, B);
                      printf("\"Negative\" operation is done!\n");
                      SaveImage("negative", R, G, B);
                      break;
            case 5:
                      printf("Enter Red   component for the target color: ");
                      scanf("%d", &r_target);
                      printf("Enter Green component for the target color: ");
                      scanf("%d", &g_target);
                      printf("Enter Blue  component for the target color: ");
                      scanf("%d", &b_target);
                      printf("Enter threshold for the color difference: ");
                      scanf("%d", &threshold);
                      printf("Enter value for Red   component in the target color: ");
                      scanf("%d", &r_replace);
                      printf("Enter value for Green component in the target color: ");
                      scanf("%d", &g_replace);
                      printf("Enter value for Blue  component in the target color: ");
                      scanf("%d", &b_replace);
                      ColorFilter(R, G, B, r_target, g_target, b_target, threshold, r_replace, g_replace, b_replace);
                      printf("\"Color Filter\" operation done!\n");
                      break;
            case 6:
                      Edge(R, G, B);
                      printf("\"Edge\" operation done!\n");
                      break;
            case 7:
                      Shuffle(R, G, B);
                      printf("\"Shuffle\" operation done!\n");
                      break;
            case 8:
                      VFlip(R, G, B);
                      printf("\"VFlip\" operation done!\n");
                      break;
            case 9:
                      VMirror(R, G, B);
                      printf("\"VMirror\" operation done!\n");
                      break;
            case 10:
                      printf("Enter border width: ");
                      scanf("%d", &inputwidth);
                      printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                      printf("Select border color from the options: ");
                      scanf("%s", color);
                      AddBorder(R, G, B, color, inputwidth);
                      printf("\"AddBorder\" operation done!\n");
                      SaveImage("border", R, G, B);
                      break;
            case 11:
                      AutoTest(R, G, B);
                      break;        
            case 12:
                      exit(0);
        }
    }
    /* End of replacing */
    return 0;
}

int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
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
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

/**************************************************************/
/* PrintMenu definition */
void PrintMenu(void){
    int choice;
    char Loadname[25];
    char Savename[25];
    printf("------------------------------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save an image in PPM and JPEG format\n");
    printf("3: Change a color image to Black & White\n");
    printf("4: Make a negative of an image\n");
    printf("5: Color filter an image\n");
    printf("6: Sketch the edge of an image\n");
    printf("7: Shuffle an image\n");
    printf("8: Flip an image vertically\n");
    printf("9: Mirror an image vertically\n");
    printf("10: Add Border to an image\n");
    printf("11: Test all functions\n");
    printf("12: Exit\n");
    printf("Please make your choice:");
}

/* change color image to black and white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], 
		         unsigned char G[WIDTH][HEIGHT], 
		         unsigned char B[WIDTH][HEIGHT]){
		             
	int i, j, temp = 0;
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
           R[i][j] = B[i][j] = G[i][j] = (R[i][j] + B[i][j] + G[i][j])/3; 
        }
    }
}
 
 
/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]){
    int i, j = 0;
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            R[i][j] = 255 - R[i][j];
            G[i][j] = 255 - G[i][j];
            B[i][j] = 255 - B[i][j];
        }
    }
        
}


/* color filter function */
void ColorFilter(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
                 int target_r, int target_g, int target_b, int threshold,
                 int replace_r, int replace_g, int replace_b){
                     
    int i, j = 0;
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            if(((target_r - threshold) < R[i][j] && R[i][j] < (target_r + threshold)) && ((target_g - threshold) < G[i][j] && G[i][j] < (target_g + threshold)) && ((target_b - threshold) < B[i][j] && B[i][j] < (target_b + threshold)))
            {
                R[i][j] = R[i][j] * replace_r;
                G[i][j] = G[i][j] * replace_g;
                B[i][j] = B[i][j] * replace_b;
  
                if(R[i][j] > 255){ 
                    R[i][j] = 255; 
                }
                
                if(R[i][j] < 0){ 
                    R[i][j] = 0; 
                }
                
                if(G[i][j] > 255){ 
                    G[i][j] = 255; 
                }
                
                if(G[i][j] < 0){ 
                    G[i][j] = 0;
                }
                
                if(B[i][j] > 255){ 
                    B[i][j] = 255; 
                }
                
                if(B[i][j] < 0){ 
                    B[i][j] = 0; 
                }
            }
            else{ 
                continue; 
                
            }
        }       
    } 
}


/* Find edge of an image */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int i, j = 0;
    unsigned char R2[WIDTH][HEIGHT];
    unsigned char G2[WIDTH][HEIGHT];
    unsigned char B2[WIDTH][HEIGHT];
    int r_sum = 0;
    int g_sum = 0;
    int b_sum = 0;

    /* fills in the new array with the original array's values */
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            R2[i][j] = R[i][j];
            G2[i][j] = G[i][j];
            B2[i][j] = B[i][j];
        }
    }

    for(j = 1; j < HEIGHT - 1; j++)
    {
        for(i = 1; i < WIDTH - 1; i++)
        {
            r_sum = 8 * R2[i][j] - R2[i - 1][j - 1] - R2[i - 1][j] - R2[i - 1][j + 1] - R2[i][j + 1] - R2[i + 1][j + 1] - R2[i + 1][j] - R2[i + 1][j - 1] - R2[i][j - 1];
            g_sum = 8 * G2[i][j] - G2[i - 1][j - 1] - G2[i - 1][j] - G2[i - 1][j + 1] - G2[i][j + 1] - G2[i + 1][j + 1] - G2[i + 1][j] - G2[i + 1][j - 1] - G2[i][j - 1];
            b_sum = 8 * B2[i][j] - B2[i - 1][j - 1] - B2[i - 1][j] - B2[i - 1][j + 1] - B2[i][j + 1] - B2[i + 1][j + 1] - B2[i + 1][j] - B2[i + 1][j - 1] - B2[i][j - 1];
            Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
        }
    }
    for(j = 0; j < HEIGHT; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            if(i == 0 && j == 0)
            {
                r_sum = 3*R2[i][j] - R2[i + 1][j] - R2[i][j - 1] - R2[i + 1][j - 1];
                g_sum = 3*G2[i][j] - G2[i + 1][j] - G2[i][j - 1] - G2[i + 1][j - 1];
                b_sum = 3*B2[i][j] - B2[i + 1][j] - B2[i][j - 1] - B2[i + 1][j - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }

            if(i == WIDTH - 1 && j == 0)
            {
                r_sum = 3*R2[i][j] - R2[i - 1][j] - R2[i - 1][j - 1] - R2[i][j - 1];
                g_sum = 3*G2[i][j] - G2[i - 1][j] - G2[i - 1][j - 1] - G2[i][j - 1];
                b_sum = 3*B2[i][j] - B2[i - 1][j] - B2[i - 1][j - 1] - B2[i][j - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }

            if(i == 0 && j == HEIGHT - 1)
            {
                r_sum = 3*R2[i][j] - R2[i + 1][j] - R2[i][j + 1] - R2[i + 1][j + 1];
                g_sum = 3*G2[i][j] - G2[i + 1][j] - G2[i][j + 1] - G2[i + 1][j + 1];
                b_sum = 3*B2[i][j] - B2[i + 1][j] - B2[i][j + 1] - B2[i + 1][j + 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }
 
            if(i == WIDTH - 1 && j == HEIGHT - 1)
            {
                r_sum = 3*R2[i][j] - R2[i - 1][j] - R2[i][j + 1] - R2[i - 1][j + 1];
                g_sum = 3*G2[i][j] - G2[i - 1][j] - G2[i][j + 1] - G2[i - 1][j + 1];
                b_sum = 3*B2[j][j] - B2[i - 1][j] - B2[i][j + 1] - B2[i - 1][j + 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }

            if(i == WIDTH - 1 && j != 0 && j !=  HEIGHT - 1)
            {
                r_sum = 5*R2[i][j] - R2[i - 1][j - 1] - R2[i][j - 1] - R2[i - 1][j] - R2[i - 1][j - 1] - R2[i][j - 1];
                g_sum = 5*G2[i][j] - G2[i - 1][j - 1] - G2[i][j - 1] - G2[i - 1][j] - G2[i - 1][j - 1] - G2[i][j - 1];
                b_sum = 5*B2[i][j] - B2[i - 1][j - 1] - B2[i][j - 1] - B2[i - 1][j] - B2[i - 1][j - 1] - B2[i][j - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            } 

            if(i == 0 && j != 0 && j !=  HEIGHT - 1)
            {
                r_sum = 5*R2[i][j] - R2[i + 1][j - 1] - R2[i][j - 1] - R2[i + 1][j] - R2[i + 1][j - 1] - R2[i][j - 1];
                g_sum = 5*G2[i][j] - G2[i + 1][j - 1] - G2[i][j - 1] - G2[i + 1][j] - G2[i + 1][j - 1] - G2[i][j - 1];
                b_sum = 5*B2[i][j] - B2[i + 1][j - 1] - B2[i][j - 1] - B2[i + 1][j] - B2[i + 1][j - 1] - B2[i][j - 1];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }

            if(i != 0 && i != WIDTH - 1 && j == HEIGHT - 1)
            {
                r_sum = 5*R2[i][j] - R2[i - 1][j - 1] - R2[i][j - 1] - R2[i + 1][j - 1] - R2[i - 1][j] - R2[i + 1][j];
                g_sum = 5*G2[i][j] - G2[i - 1][j - 1] - G2[i][j - 1] - G2[i + 1][j - 1] - G2[i - 1][j] - G2[i + 1][j];
                b_sum = 5*B2[i][j] - B2[i - 1][j - 1] - B2[i][j - 1] - B2[i + 1][j - 1] - B2[i - 1][j] - B2[i + 1][j];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j);
            }

            if(i != 0 && i != WIDTH - 1 && j == 0)
            {
                r_sum = 5*R2[i][j] - R2[i - 1][j + 1] - R2[i][j + 1] - R2[i - 1][j] - R2[i - 1][j + 1] - R2[i + 1][j];
                g_sum = 5*G2[i][j] - G2[i - 1][j + 1] - G2[i][j + 1] - G2[i - 1][j] - G2[i - 1][j + 1] - G2[i + 1][j];
                b_sum = 5*B2[i][j] - B2[i - 1][j + 1] - B2[i][j + 1] - B2[i - 1][j] - B2[i - 1][j + 1] - B2[i + 1][j];
                Boundcheck(R, G, B, r_sum, g_sum, b_sum, i, j); 
            }
        }
    }
}


/* This function is to generate a random number for us */
int GenerateRandomNumber(int min, int max)
{
    return (rand()%(max - min) + min);    
}


/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int i = 0;
    int j = 0;
    int r_temp = 0;
    int g_temp = 0;
    int b_temp = 0;

    for(j = 0; j < HEIGHT/2; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            r_temp = R[i][j];
            g_temp = G[i][j];
            b_temp = B[i][j];
            R[i][j] = R[i][HEIGHT - 1 - j];
            G[i][j] = G[i][HEIGHT - 1 - j];
            B[i][j] = B[i][HEIGHT - 1 - j];
            R[i][HEIGHT - 1 - j] = r_temp;
            G[i][HEIGHT - 1 - j] = g_temp;
            B[i][HEIGHT - 1 - j] = b_temp;
        }
    }
} 


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int i, j = 0;
    for(j = 0; j < HEIGHT/2; j++)
    {
        for(i = 0; i < WIDTH; i++)
        {
            R[i][HEIGHT - j] = R[i][j];
            G[i][HEIGHT - j] = G[i][j];
            B[i][HEIGHT - j] = B[i][j];     
        }
    }
}


/* Shuffle an image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int i = 0;
    int j = 0;
    int k = 0;
    for(k = 0; k < 16; k++)
    {
        int random_k = GenerateRandomNumber(0, 15); 
        for(j = 0; j < HEIGHT/4; j++)
        {
            for(i = 0; i < WIDTH/4; i++)
            {
                int piece_width = WIDTH/4;
                int piece_height = HEIGHT/4;
                int k_xpos = (k%4)*piece_width + i;
                int k_ypos = (k/4)*piece_height + j;
                int random_k_xpos = (random_k%4)*piece_width + i;
                int random_k_ypos = (random_k/4)*piece_height + j;
                int r_temp = R[k_xpos][k_ypos];
                int g_temp = G[k_xpos][k_ypos];
                int b_temp = B[k_xpos][k_ypos];
               
                R[k_xpos][k_ypos] = R[random_k_xpos][random_k_ypos];
                G[k_xpos][k_ypos] = G[random_k_xpos][random_k_ypos];
                B[k_xpos][k_ypos] = B[random_k_xpos][random_k_ypos]; 

                R[random_k_xpos][random_k_ypos] = r_temp;
                G[random_k_xpos][random_k_ypos] = g_temp;
                B[random_k_xpos][random_k_ypos] = b_temp; 
            }
        }
    } 
}

/* add a border to the image */
void AddBorder(unsigned char R[WIDTH][HEIGHT], 
               unsigned char G[WIDTH][HEIGHT], 
               unsigned char B[WIDTH][HEIGHT], 
               char color[SLEN], int border_width) {
        int i , j = 0;
        // Black
        if (strcmp(color, "black") == 0) {  
        int i , j = 0;
    	for (i = 0; i < (9*border_width)/16; i++) {
      	    for (j = 0; j < HEIGHT; j++) {
      		    R[i][j] = 0;
      		    G[i][j] = 0; 
      	    	B[i][j] = 0;
      	    }
    	}
    	i = j = 0;
    	for (i = 0; i < WIDTH; i++) {
      	    for (j = 0; j < border_width; j++) {
      		    R[i][j] = 0;
      		    G[i][j] = 0; 
      		    B[i][j] = 0;
      	    }
    	}
    	i = j = 0;
    	for (i = 0; i < WIDTH; i++) {
      	    for (j = 0; j < border_width; j++) {
      		    R[i][HEIGHT-j] = 0;
      		    G[i][HEIGHT-j] = 0;
      		    B[i][HEIGHT-j] = 0;
      	    }
    	}
    	i = j = 0;
    	for (i = 0; i < (9*border_width)/16; i++) {
      	    for (j = 0; j < HEIGHT; j++) {
      		    R[WIDTH-i][j] = 0;
      		    G[WIDTH-i][j] = 0;
      		    B[WIDTH-i][j] = 0;
      	    }
    	}
    	printf("'Border' operation is done!\n");
		} 
		
		// white
		else if (strcmp(color, "white") == 0) {
		    int i, j = 0;
  			for (i = 0; i < (9*border_width)/16; i++) {
        	    for (j = 0; j < HEIGHT; j++) {
        		    R[i][j] = 255;
        		    G[i][j] = 255; 
        		    B[i][j] = 255;
        	    }
      	    }
      	    i = j = 0;
      	    for (i = 0; i < WIDTH; i++) {
        	    for (j = 0; j < border_width; j++) {
        		    R[i][j] = 255;
        		    G[i][j] = 255; 
        		    B[i][j] = 255;
        	    }
      	    }
      	    i = j = 0;
      	    for (i = 0; i < WIDTH; i++) {
        	    for (j = 0; j < border_width; j++) {
        		    R[i][HEIGHT-j] = 255;
        		    G[i][HEIGHT-j] = 255;
        		    B[i][HEIGHT-j] = 255;
        	    }
      	    }
      	    i = j = 0;
      	    for (i = 0; i < 9*(border_width)/16; i++) {
        	    for (j = 0; j < HEIGHT; j++) {
        		    R[WIDTH-i][j] = 255;
        		    G[WIDTH-i][j] = 255;
        		    B[WIDTH-i][j] = 255;
        	    }
      	    }
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "red") == 0) {
		      i = j = 0;
			  for (i= 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 255;
        		G[i][j] = 0; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 255;
        		G[i][j] = 0; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 255;
        		G[i][HEIGHT-j] = 0;
        		B[i][HEIGHT-j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 255;
        		G[WIDTH-i][j] = 0;
        		B[WIDTH-i][j] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "green") == 0) {
		    i = j = 0;
			  for (i = 0; i < 9*(border_width)/16; i++) {
	        for (j = 0; j < HEIGHT; j++) {
	        	R[i][j] = 0;
	        	G[i][j] = 255; 
	        	B[i][j] = 0;
	        }
        }
        i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 0;
        		G[i][j] = 255; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 0;
        		G[i][HEIGHT-j] = 255;
        		B[i][HEIGHT-j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 0;
        		G[WIDTH-i][j] = 255;
        		B[WIDTH-i][j] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "blue") == 0) {
		    i = j = 0;
  			for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 0;
        		G[i][j] = 0; 
        		B[i][j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 0;
        		G[i][j] = 0; 
        		B[i][j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 0;
        		G[i][HEIGHT-j] = 0;
        		B[i][HEIGHT-j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 0;
        		G[WIDTH-i][j] = 0;
        		B[WIDTH-i][j] = 255;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "yellow") == 0) {
		    i = j = 0;
	    for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 255;
        		G[i][j] = 255; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 255;
        		G[i][j] = 255; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 255;
        		G[i][HEIGHT-j] = 255;
        		B[i][HEIGHT-j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 255;
        		G[WIDTH-i][j] = 255;
        		B[WIDTH-i][j] = 0;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "cyan") == 0) {
		    i = j = 0;
		for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 0;
        		G[i][j] = 255; 
        		B[i][j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 0;
        		G[i][j] = 255; 
        		B[i][j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 0;
        		G[i][HEIGHT-j] = 255;
        		B[i][HEIGHT-j] = 255;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 0;
        		G[WIDTH-i][j] = 255;
        		B[WIDTH-i][j] = 255;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "pink") == 0) {
		    i = j = 0;
		for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 255;
        		G[i][j] = 192; 
        		B[i][j] = 203;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 255;
        		G[i][j] = 192; 
        		B[i][j] = 203;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 255;
        		G[i][HEIGHT-j] = 192;
        		B[i][HEIGHT-j] = 203;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 255;
        		G[WIDTH-i][j] = 192;
        		B[WIDTH-i][j] = 203;
        	}
      	}
      	printf("'Border' operation is done!\n");
		} else if (strcmp(color, "orange") == 0) {
		    i = j = 0;
		for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[i][j] = 255;
        		G[i][j] = 165; 
        		B[i][j] = 0;
        	}
        }
        i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][j] = 255;
        		G[i][j] = 165; 
        		B[i][j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < WIDTH; i++) {
        	for (j = 0; j < border_width; j++) {
        		R[i][HEIGHT-j] = 255;
        		G[i][HEIGHT-j] = 165;
        		B[i][HEIGHT-j] = 0;
        	}
      	}
      	i = j = 0;
      	for (i = 0; i < 9*(border_width)/16; i++) {
        	for (j = 0; j < HEIGHT; j++) {
        		R[WIDTH-i][j] = 255;
        		G[WIDTH-i][j] = 165;
        		B[WIDTH-i][j] = 0;
        	}
        }
        printf("'Border' operation is done!\n");
    } else {
  		printf("Invalid entry: Please try again.\n");
    }
}


/* This function is to check the bound */
void Boundcheck(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int r_sum, int g_sum, int b_sum, int i, int j)
{
    if(r_sum <= 255 && r_sum >=0){
        R[i][j] = r_sum;
    }
    if(r_sum > 255){
        R[i][j] = 255; 
    }
    if(r_sum < 0){
       R[i][j] = 0; 
    }
    if(g_sum <= 255 && g_sum >=0){
       G[i][j] = g_sum;
    }
    if(g_sum > 255){
        G[i][j] = 255;
    }
    if(g_sum < 0){
       G[i][j] = 0; 
    }
    if(b_sum <= 255 && b_sum >=0){
        B[i][j] = b_sum;
    }
    if(b_sum > 255){
        B[i][j] = 255;
    }
    if(b_sum < 0){
       B[i][j] = 0; 
    }
}

/* This function is for autotest */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    //char fname[79] = "EngPlaza";
    char sname[SLEN];
    
    LoadImage("EngPlaza", R, G, B);
    BlackNWhite(R, G, B);
    strcpy(sname, "bw");/*string copy function to prepare the file name to be saved*/
	SaveImage(sname, R, G, B);
    printf("Black and White tested!\n\n");
    
    LoadImage("EngPlaza", R, G, B);
    Negative(R, G, B);
    strcpy(sname, "negative");/*string copy function to prepare the file name to be saved*/
	SaveImage(sname, R, G, B);
    printf("Negative tested!\n\n");
    
    LoadImage("EngPlaza", R, G, B);
    ColorFilter(R, G, B, 190, 100, 150, 60, 0, 0, 255);
    SaveImage("colorfilter", R, G, B);
    printf("Color Filter tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
    printf("Shuffle tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    printf("VFlip tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    VMirror(R, G, B);
    SaveImage("vmirror", R, G, B);
    printf("VMirror tested!\n\n");

    LoadImage("EngPlaza", R, G, B);
    AddBorder(R, G, B, "orange", 64);
    strcpy(sname, "border");
    SaveImage(sname, R, G, B);
    printf("AddBorder tested!\n\n");
}
/**************************************************************/

/* EOF */

