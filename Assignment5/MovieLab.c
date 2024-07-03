/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* MovieLab.c: source file for the main function                     */
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
#include "ImageList.h"

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
        unsigned int width, unsigned height);

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
        unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

void Movie_DIP_Operation(Movie *movie, Mopf *MovieOP);

int main(int argc, char *argv[])
{
        int x = 0;
        int c = 0;
        int num = 0;
        int factor = 0;
        int percent = 0;
        int start = 0;
        int end = 0;
        int width = 0;
        int height = 0;
        int nframes = 0;
        char *fin = NULL;
        char *fout = NULL;

        unsigned int width = 512;
        unsigned int height = 288;

        Movie *movie;
        movie = NULL;

        /* the while loop to check options in the command line */
        while (x < argc) {
                /* the input file name */
                if (strcmp(argv[x], "-i") == 0) {
                        if (x < argc - 1) {
                                fin = argv[x + 1];
                        } /*fi*/
else {
                                printf("Missing argument for the input file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the output file name */
                if (strcmp(argv[x], "-o") == 0) {
                        if (x < argc - 1) {
                                fout = argv[x + 1];
                        } /*fi*/
                        else {
                                printf("Missing argument for the output file name!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                /* the help option */
                if (strcmp(argv[x], "-h") == 0) {
                        PrintUsage();
                        return 0;
                } /*fi*/

                for (int i = 1; i < argc; i++) {
                        if (strcmp(argv[i], "-s") == 0 && i + 2 < argc) {
                                width = atoi(argv[i + 1]);
                                height = atoi(argv[i + 2]);
                                break;
                        }
                }

                if (width == 0 || height == 0) {
                        char *filename = argv[argc - 1];
                        if (sscanf(filename, "%*s %d %d.yuv", &width, &height) != 2) {
                                fprintf(stderr, "Invalid resolution. \n");
                                return 1;
                        }
                }
                printf("Width: %d, Height: %d\n", width, height);
        

                if(strcmp(argv[x], "-f") == 0) {
                        if (x < argc - 1) {
                                sscanf(argv[x + 1], "%d", &nframes);
                        } /*fi*/
                        else {
                                printf("Missing argument for the frame number!\n");
                                return 5;
                        } /*esle*/
                        x += 2;
                        continue;
                } /*fi*/

                if (c == 0 && nframes && width && height){
                        movie = LoadMovie(fin, nframes, width, height);
                        c++;
                }

                if (fin && movie){
                        ReadMovie(fin, movie);
                }

                if (strcmp(argv[x], "-bw") == 0) {
                        Movie_DIP_Operation(movie, BlackNWhite);
                        printf("Black and White filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-hmirror") == 0) {
                        Movie_DIP_Operation(movie, HMirror);
                        printf("Horizontal Mirror filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-edge") == 0) {
                        Movie_DIP_Operation(movie, Edge);
                        printf("Edge filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-crop") == 0) {
                        if (x < argc - 1) {
                                if (sscanf(argv[x + 1], "%d-%d", &start, &end) != 2) {
                                        printf("Invalid argument for the crop!\n");
                                } /*fi*/
                        }
                                else {
                                        printf("Invalid argument for the crop!");
                                        return 5;
                                } /*esle*/
                        CropImageList(movie->Frames, start, end);
                        printf("Crop filter has been applied!\n");
                        x += 2;
                        continue;
                } /*fi*/

                if (0 == strcmp(argv[x], "-fast")) {
                        if (x < argc - 1) {
                                if (sscanf(argv[x + 1], "%d", &factor) == 1) {
                                        printf("Missing argument for fast!");
                                } /*fi*/
                                if (factor < 1){
                                        printf("Invalid argument for the fast forward factor!\n");
                                        return 5;
                                }
                        }
                                else {
                                        printf("Missing argument for fast!\n");
                                        return 5;
                                } /*esle*/
                                num = FastImageList(movie->Frames, factor);

                                printf("Fast forward filter has been applied!\n");
                                printf("The number of frames in the movie after fast forward is %d.\n", num);
                                x += 2;
                                continue;
                        
                } /*fi*/

                if (strcmp(argv[x], "-reverse") == 0) {
                        ReverseImageList(movie->Frames);
                        printf("Reverse filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-watermark") == 0) {
                       Movie_DIP_Operation(movie, Watermark);
                        printf("Watermark filter has been applied!\n");
                        x += 2;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-spotlight") == 0) {
                        Movie_DIP_Operation(movie, Spotlight);
                        printf("Spotlight filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

                if (strcmp(argv[x], "-rotate") == 0) {
                        Movie_DIP_Operation(movie, Rotate);
                        printf("Rotate filter has been applied!\n");
                        x++;
                        continue;
                } /*fi*/

        } /*elihw*/
        SaveMovie(fout, movie);
        DeleteMovie(movie);        
        
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

                /* to be implemented */
        free(fin);
        free(fout);

        fin = NULL;
        fout = NULL;

        return 0;
}
void PrintUsage()
{
        printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> [options]\n"
               "Options:\n"
               "-s <WidthxHeight>     To set the resolution of the input stream (WidthxHeight)\n"
               "-bw                   Activate the black and white filter on every movie frame\n"
               "-hmirror              Activate horizontal mirror on every movie frame\n"
               "-edge                 Activate the edge filter on every movie frame\n"
               "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
               "-fast <factor>        Fast forward the movie by <factor>\n"
               "-reverse              Reverse the frame order of the input movie\n"
               "-watermark <file>     Add a watermark from <file> to every movie frame\n"
               "-spotlight            Spotlight the fade in and fade out\n"
               "-rotate               Rotate and zoom in/out the input movie\n"
               "-h                    Display this usage information\n"
              );
}

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
        unsigned int width, unsigned height)
{
        FILE *file;
        unsigned int x, y;
        unsigned char c;
        YUVImage* YUVimage;

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

void Crop
/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
        unsigned int width, unsigned height)
{
        int i;
        Movie *movie;
        Image *image;

        assert(fname);
        assert(movie);
        assert(movie->Frames);

        NewImageList();
        for (i = 0; i < frameNum; i++) {
                image = LoadOneFrame(fname, i, width, height);
                AppendYUVImage(movie->Frames, image);
        }
        printf("The movie file %s has been read successfully!\n", fname);
        return 0;
}

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie)
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

                SaveOneFrame(curr->image, fname, file);
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
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file)
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

void Movie_DIP_Operation(MOVIE *movie, MOP_F *MovieOP)
{
        int frames;
        int i;
        assert(movie);
        frames = movie->NumFrames;
        IENTRY *curr;
        curr = movie->Frames->First;
        for (i = 0; i < frames; i++) {
                MovieOP(curr->image);
                if(curr->Next != NULL) {
                        curr = curr->Next;
                }
        }       

}

/* EOF */
