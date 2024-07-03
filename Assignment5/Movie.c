/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* Movie.c: source file for basic movie manipulations                */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H)
{
        Movie *movie;
        ILIST *new;
        movie = (Movie *)malloc(sizeof(Movie));
        if(!movie) {
                return NULL;
        }
        if(!(ILIST *)malloc(sizeof(ILIST))){
                return NULL;
        }
        movie->Width = W;
        movie->Height = H;
        movie->NumFrames = nFrames;
        new = NewImageList();
        movie->Frames = new;

        return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
        DeleteImageList(movie->Frames);
        free(movie);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie, unsigned char Y, unsigned char U, unsigned char V, unsigned char *R, unsigned char *G, unsigned char *B)
{
    int r, g, b;
    int C = Y - 16;
    int D = U - 128;
    int E = V - 128;
    r = (298 * C + 409 * E + 128) >> 8;
    g = (298 * C - 100 * D - 208 * E + 128) >> 8;
    b = (298 * C + 516 * D + 128) >> 8;
    clip(&r);
    clip(&g);
    clip(&b);
    *R = r;
    *G = g;
    *B = b;
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie, unsigned char R, unsigned char G, unsigned char B, unsigned char *Y, unsigned char *U, unsigned char *V)
{
    int y, u, v;
    y = ( ( 66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
    u = ( ( -38 * R - 74 * G + 112 * B + 128) >> 8) + 128;
    v = ( ( 112 * R - 94 * G - 18 * B + 128) >> 8) + 128;
    clip(&y);
    clip(&u);
    clip(&v);
    *Y = y;
    *U = u;
    *V = v;
}

void clip(int *x) {
    if (*x < 0) *x = 0;
    else if (*x > 255) *x = 255;
}
