/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* Movie.h: header file for basic movie manipulations                */
/*********************************************************************/

#ifndef MOVIE_H
#define MOVIE_H

#include "ImageList.h"

/* the movie structure */
typedef struct {
        unsigned int NumFrames; /* number of frames in the movie */
        unsigned int Height; /* height of each frame */
        unsigned int Width; /* width of each frame */
        ILIST *Frames; /* Pointer to the frame list */
} Movie;

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(unsigned int nFrames, unsigned int W, unsigned int H);

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie);

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie, unsigned char Y, unsigned char U, unsigned char V, unsigned char *R, unsigned char *G, unsigned char *B);

void Movie_DIP_Operation(Movie *movie, Mopf *MovieOP);

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie, unsigned char R, unsigned char G, unsigned char B, unsigned char *Y, unsigned char *U, unsigned char *V);

void clip(int *x);

#endif
