/* PhotoLab.c: assignment 2 for EECS 22 in Winter 2024 */
/* */
/* modifications: (most recent first) */
/* 01/18/24 RD adjusted for lecture usage */
/*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
#define WIDTH  512              /* image width */
#define HEIGHT 288              /* image height */
#define SLEN    80              /* maximum length of file names */
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

/*** function declarations ***/
int choice = 2;

/* print a menu */
int PrintMenu(){
    printf("--------------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save an image in PPM and JPEG format\n");
    printf("3: Change a color image to Black & White\n");
    printf("4: Make a negative of an image\n");
    printf("5: Color filter an image\n");
    printf("6: Sketch the edge of an image\n");
    printf("7: Flip an image horizontally\n");
    printf("8: Mirror an image vertically\n");
    printf("9: Shuffle an image\n");
    printf("10: Add Border to an image\n");
    printf("11: Test all functions\n");
    printf("12: Exit\n");
    printf("please make your choice: ");
    return 0;
}


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

/* Reverse image color*/
void Negative(unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* Color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
                 int target_r, /* target red value */
                 int target_g, /* target green value */
                 int target_b, /* target blue value */
                 int threshold, /* threshold value */
                 int replace_r, /* factor red value */
                 int replace_g, /* factor green value */
                 int replace_b); /* factor blue value */

/* Edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT],
          unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/*Mirror image horizontally*/
void HMirror(unsigned char R[WIDTH][HEIGHT],
             unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* Shuffle the image */
void Shuffle (unsigned char R[WIDTH][HEIGHT], 
             unsigned char G[WIDTH][HEIGHT], 
             unsigned char B[WIDTH][HEIGHT], 
             unsigned char R2[WIDTH][HEIGHT], 
             unsigned char G2[WIDTH][HEIGHT], 
             unsigned char B2[WIDTH][HEIGHT], 
             int blockHeight, int blockWidth,
              int blockx, int blocky, int blockSwitchx, 
              int blockSwitchy, int x, int y);

/* Add border*/
void AddBorder(unsigned char R[WIDTH][HEIGHT],
               unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT],
               char color[SLEN],
               int border_width);

/* flip image vertically*/
void VFlip(unsigned char R[WIDTH][HEIGHT],
           unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], 
              unsigned char G[WIDTH][HEIGHT], 
              unsigned char B[WIDTH][HEIGHT], 
              unsigned char R2[WIDTH][HEIGHT], 
              unsigned char G2[WIDTH][HEIGHT], 
              unsigned char B2[WIDTH][HEIGHT], 
              int blockHeight, int blockWidth, 
              int blockx, int blocky, int blockSwitchx, 
              int blockSwitchy, int x, int y);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
    unsigned char   R2[WIDTH][HEIGHT];
    unsigned char   G2[WIDTH][HEIGHT];
    unsigned char   B2[WIDTH][HEIGHT];
   
    int x;
    int y;

    char fname[100];


    /* Please replace the following code with proper menu with function calls for DIP operations */

        while(1){
        PrintMenu();
        scanf("%d", &choice);
        switch(choice){
        case 1:
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            LoadImage(fname, R, G, B);
            break;
        case 2: 
            printf("Please input the file name to save: ");
            scanf("%s", fname);
            SaveImage(fname, R, G, B);
            break;
        case 3:
            BlackNWhite(R, G, B);
            printf("\"Black & White\" operation is done!\n");   //backslash signifies double quote 
            break;
        case 4:
            Negative(R, G, B);
            printf("\"Negative\" operation is done!\n");
            break;
        case 5:
            int target_r;
            int target_g;
            int target_b;
            int threshold;
            int replace_r;
            int replace_g;
            int replace_b;

            printf("Enter Red component for the target color: ");
            scanf("%d", &target_r);
            printf("Enter Green component for the target color: ");
            scanf("%d", &target_g);
            printf("Enter Blue component for the target color: ");
            scanf("%d", &target_b);
            printf("Enter threshold for the color difference: ");
            scanf("%d", &threshold);
            printf("Enter value for Red component in the target color: ");
            scanf("%d", &replace_r);
            printf("Enter value for Green component in the target color: ");
            scanf("%d", &replace_g);
            printf("Enter value for Blue component in the target color: ");
            scanf("%d", &replace_b);
            ColorFilter(R, G, B, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
            printf("\"Color Filter\" operation is done!\n");
            break;  
        case 6:
            Edge(R, G, B);
            printf("\"Edge\" operation is done!\n");
            break;
        case 7:
        int blockHeight = 0, blockWidth = 0, blockx = 0, blocky = 0, blockSwitchx = 0, blockSwitchy = 0, x = 0, y = 0;
            Shuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);
            printf("\"Shuffle\" operation is done!\n");
            break;
        case 8:
            VFlip(R, G, B);
            printf("\"VFlip\" operation is done!\n");
            break;
        case 9:
            HMirror(R, G, B);
            printf("\"HMirror\" operation is done!\n");
            break;
        case 10:
            int border_width;
            char color[SLEN];
            printf("Enter border width: ");
            scanf("%d", &border_width);
            printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
            printf("Select border color from the options: ");
            AddBorder(R, G, B, color, border_width);
            printf("\"Border\" operation is done!\n");
            break;
        case 11:
            AutoTest(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);
            break;
        case 12:
            printf("Currently exiting");
            return 0;
            break;
        default:
                printf("Invalid choice. Please try again.\n");

        }
      }

//       if (LoadImage("EngPlaza", R, G, B) != 0){
//                return 1;
//    }

    /* End of replacing */

    return 0;
}


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char Type[SLEN];
    int x, y;
    int Width, Height, MaxValue;
    FILE *File;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\".ppm for loading!\n", fname);
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
/* Please add your function definitions here...               */
/**************************************************************/

//done
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    int newIntensity;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            newIntensity = (R[x][y] + G[x][y] + B[x][y])/3;
            R[x][y] = newIntensity;
            G[x][y] = newIntensity;
            B[x][y] = newIntensity;
        }
    }
};

//done
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            R[x][y] = 255 - R[x][y];
            G[x][y] = 255 - G[x][y];
            B[x][y] = 255 - B[x][y];
        }
    }
    return 0;
};

//done
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
    int x, y;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            if ((R[x][y] >= target_r - threshold && R[x][y] <= target_r + threshold) && (G[x][y] >= target_g - threshold && G[x][y] <= target_g + threshold) && (B[x][y] >= target_b - threshold && B[x][y] <= target_b + threshold)){
                R[x][y] = replace_r;
                G[x][y] = replace_g;
                B[x][y] = replace_b;
            }
        }
    }
};

//done
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    int R2, G2, B2;

    unsigned char R3[WIDTH][HEIGHT];
    unsigned char G3[WIDTH][HEIGHT];
    unsigned char B3[WIDTH][HEIGHT];

    for (y = 1; y < HEIGHT - 1; y++){
            for (x = 1; x < WIDTH - 1; x++){
                R2 = - R[x-1][y+1] - R[x][y+1] - R[x+1][y+1] - R[x+1][y] + (8 * R[x][y]) - R[x-1][y] - R[x-1][y-1] - R[x][y-1] + R[x+1][y-1];
                G2 = - G[x-1][y+1] - G[x][y+1] - G[x+1][y+1] - G[x+1][y] + (8 * G[x][y]) - G[x-1][y] - G[x-1][y-1] - G[x][y-1] + G[x+1][y-1];
                B2 = - B[x-1][y+1] - B[x][y+1] - B[x+1][y+1] - B[x+1][y] + (8 * B[x][y]) - B[x-1][y] - B[x-1][y-1] - B[x][y-1] + B[x+1][y-1];

                // Saturated arithmetic
                R3[x][y] = (R2 < 0) ? 0 : ((R2 > 255) ? 255 : R2);
                G3[x][y] = (G2 < 0) ? 0 : ((G2 > 255) ? 255 : G2);
                B3[x][y] = (B2 < 0) ? 0 : ((B2 > 255) ? 255 : B2);
            }
        }

        // Copy the processed data back to the original arrays
        for (y = 1; y < HEIGHT - 1; y++){
            for (x = 1; x < WIDTH - 1; x++){
                R[x][y] = R3[x][y];
                G[x][y] = G3[x][y];
                B[x][y] = B3[x][y];
            }
        }
};

void swapShuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned char R2[WIDTH][HEIGHT], unsigned char G2[WIDTH][HEIGHT], unsigned char B2[WIDTH][HEIGHT], int blockHeight, int blockWidth, int blockx, int blocky, int blockSwitchx, int blockSwitchy, int x, int y){
     for(y = 0; y < blockHeight; y++){
        for(x = 0; x < blockWidth; x++){

        R2[x][y] = R[blockx + x][blocky + y];
        G2[x][y] = G[blockx + x][blocky + y];
        B2[x][y] = B[blockx + x][blocky + y];

        R[blockx + x][blocky + y] = R[blockSwitchx + x][blockSwitchy + y];
        G[blockx + x][blocky + y] = G[blockSwitchx + x][blockSwitchy + y];
        B[blockx + x][blocky + y] = B[blockSwitchx + x][blockSwitchy + y];
        
        }
    }
    for(y = 0; y < blockHeight; y++){
        for(x = 0; x < blockWidth; x++){
            R[blockSwitchx + x][blockSwitchy + y] = R2[x][y];
            G[blockSwitchx + x][blockSwitchy + y] = G2[x][y];
            B[blockSwitchx + x][blockSwitchy + y] = B2[x][y];
        }
    }
}

void Shuffle (unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned char R2[WIDTH][HEIGHT], unsigned char G2[WIDTH][HEIGHT], unsigned char B2[WIDTH][HEIGHT], int blockHeight, int blockWidth, int blockx, int blocky, int blockSwitchx, int blockSwitchy, int x, int y) {
    blockWidth = WIDTH / 4;
    blockHeight = HEIGHT / 4;

    //Switch blocks 1 and 16
    blockx = 0;
    blocky = 0;
    blockSwitchx = 3 * blockWidth;
    blockSwitchy = 3 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 2 and 15
    blockx = blockWidth;
    blocky = 0;
    blockSwitchx = 2 * blockWidth;
    blockSwitchy = 3 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 3 and 14
    blockx = 2 * blockWidth;
    blocky = 0;
    blockSwitchx = blockWidth;
    blockSwitchy = 3 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 4 and 13
    blockx = 3 * blockWidth;
    blocky = 0;
    blockSwitchx = 0;
    blockSwitchy = 3 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 5 and 12
    blockx = 0;
    blocky = blockHeight;
    blockSwitchx = 3 * blockWidth;
    blockSwitchy = 2 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 6 and 11
    blockx = blockWidth;
    blocky = blockHeight;
    blockSwitchx = 2 * blockWidth;
    blockSwitchy = 2 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);    

    //Switch blocks 7 and 10
    blockx = 2 * blockWidth;
    blocky = blockHeight;
    blockSwitchx = blockWidth;
    blockSwitchy = 2 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

    //Switch blocks 8 and 9
    blockx = 3 * blockWidth;
    blocky = blockHeight;
    blockSwitchx = 0;
    blockSwitchy = 2 * blockHeight;
    swapShuffle(R, G, B, R2, G2, B2, blockHeight, blockWidth, blockx, blocky, blockSwitchx, blockSwitchy, x, y);

}

//done
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    unsigned char R2, G2, B2;
    for (y = 0; y < HEIGHT / 2; y++){
        for (x = 0; x < WIDTH; x++){
            
            //Swap R
            R2 = R[x][y];
            R[x][y]= R[x][HEIGHT - y - 1];
            R[x][HEIGHT - y - 1] = R2;

            //Swap G
            G2 = G[x][y];
            G[x][y] = G[x][HEIGHT - y - 1];
            G[x][HEIGHT - y - 1] = G2; 

            //Swap B
            B2 = B[x][y];
            B[x][y] = B[x][HEIGHT - y -1];
            B[x][HEIGHT - y - 1] = B2;

        }
    }
    return 0;
};

//done
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH/2; x++){
            R[WIDTH - x - 1][y] = R[x][y];
            G[WIDTH - x - 1][y] = G[x][y];
            B[WIDTH - x - 1][y] = B[x][y];
        }
    }
    return 0;
};

//fix this
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width){
    int x, y, i, j, k;
    
    scanf("%s", color);
    if (strcmp(color, "black") == 0){
        i = 0;
        j = 0;
        k = 0;
    }
    else if (strcmp(color, "white") == 0){
        i = 255;
        j = 255;
        k = 255;
    }
    else if (strcmp(color, "red") == 0){
        i = 255;
        j = 0;
        k = 0;
    }
    else if (strcmp(color, "green") == 0){
        i = 0;
        j = 255;
        k = 0;
    }
    else if (strcmp(color, "blue") == 0){
        i = 0;
        j = 0;
        k = 255;
    }
    else if (strcmp(color, "yellow") == 0){
        i = 255;
        j = 255;
        k = 0;
    }
    else if (strcmp(color, "cyan") == 0){
        i = 0;
        j = 255;
        k = 255;
    }
    else if (strcmp(color, "pink") == 0){
        i = 255;
        j = 192;
        k = 203;
    }
    else if (strcmp(color, "orange") == 0){
        i = 255;
        j = 165;
        k = 0;
    }
    else{
        printf("Invalid color. Please try again.\n");
        return;
    }

    //Add Border to top and bottom
    for (y = 0; y < border_width; y++){
        for (x = 0; x < WIDTH; x++){
            R[x][y] = i;
            G[x][y] = j;
            B[x][y] = k;

            R[x][HEIGHT - y - 1] = i;
            G[x][HEIGHT - y - 1] = j;
            B[x][HEIGHT - y - 1] = k;
        }
    }

    //Add Border to left and right
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < border_width; x++){
            R[x][y] = i;
            G[x][y] = j;
            B[x][y] = k;

            R[WIDTH - x - 1][y] = i;
            G[WIDTH - x - 1][y] = j;
            B[WIDTH - x - 1][y] = k;
        }
    }
}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned char R2[WIDTH][HEIGHT], unsigned char G2[WIDTH][HEIGHT], unsigned char B2[WIDTH][HEIGHT], int blockHeight, int blockWidth, int blockx, int blocky, int blockSwitchx, int blockSwitchy, int x, int y) {
        char fname[SLEN] = "EngPlaza";
        char sname[SLEN];

        LoadImage(fname, R, G, B);
        Negative(R, G, B);
        strcpy(sname, "negative");
        SaveImage(sname, R, G, B);
        printf("Negative tested!\n\n");

        LoadImage(fname, R, G, B);
        ColorFilter(R, G, B, 130, 130, 150, 30, 0, 255, 255);
        strcpy(sname, "colorfilter");
        SaveImage(sname, R, G, B);
        printf("Color Filter tested!\n\n");

        LoadImage(fname, R, G, B);
        Edge(R, G, B);
        strcpy(sname, "edge");
        SaveImage(sname, R, G, B);
        printf("Edge Detection tested!\n\n");

        LoadImage(fname, R, G, B);
        HMirror(R, G, B);
        strcpy(sname, "hmirror");
        SaveImage(sname, R, G, B);
        printf("HMirror tested!\n\n");

        LoadImage(fname, R, G, B);
        AddBorder (R, G, B, "pink", 32);
        strcpy(sname, "border");
        SaveImage(sname, R, G, B);
        printf("Border tested!\n\n");

        LoadImage(fname, R, G, B);
        BlackNWhite(R, G, B);
        strcpy(sname, "bw");
        SaveImage(sname, R, G, B);
        printf("Black & White tested!\n\n");

        LoadImage(fname, R, G, B);
        VFlip(R, G, B);
        strcpy(sname, "vflip");
        SaveImage(sname, R, G, B);
        printf("VFlip tested!\n\n");

        LoadImage(fname, R, G, B);
        Shuffle(R, G, B);
        strcpy(sname, "shuffle");
        SaveImage(sname, R, G, B);
        printf("Shuffle tested!\n\n");

        LoadImage(fname, R, G, B);
        AddBorder(R, G, B, "pink", 32);
        strcpy(sname, "border");
        SaveImage(sname, R, G, B);
        printf("Border tested!\n\n");
        
    
}

/* EOF */
