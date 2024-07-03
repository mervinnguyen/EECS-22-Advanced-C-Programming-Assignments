#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "Image.h"
#include "Constants.h"

unsigned char GetPixelR(const Image *image, unsigned int x, unsigned int y){
    //get the R intensity of pixel at (x, y)
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    return image->R[y * image->W + x];
}

unsigned char GetPixelG(const Image *image, unsigned int x, unsigned int y){
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    return image->G[y * image->W + x];
}

unsigned char GetPixelB(const Image *image, unsigned int x, unsigned int y){
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    return image->B[y * image->W + x];
}

void SetPixelR(Image *image, unsigned int x, unsigned int y, unsigned char r){
    assert(image != NULL);
    assert(image->R != NULL);
    assert(x < image->W && y < image->H);
    image->R[x + y * image->W] = r;
}

void SetPixelG(Image *image, unsigned int x, unsigned int y, unsigned char g){
    assert(image != NULL);
    assert(image->G != NULL);
    assert(x < image->W && y < image->H);
    image->G[x + y * image->W] = g;
}

void SetPixelB(Image *image, unsigned int x, unsigned int y, unsigned char b){
    assert(image != NULL);
    assert(image->B != NULL);
    assert(x < image->W && y < image->H);
    image->B[x + y * image->W] = b;
}

Image *CreateImage(unsigned int Width, unsigned int Height){
    Image *image = malloc(sizeof(Image));
    image->W = Width;
    image->H = Height;
    image->R = malloc(sizeof(unsigned char)*Width *Height);
    image->G = malloc(sizeof(unsigned char)*Width *Height);
    image->B = malloc(sizeof(unsigned char)*Width *Height);
    
    if(!image){
        perror("Image not created.");
        return NULL;
    }
    assert(image->R != NULL && image->G != NULL && image->B != NULL);
    return image;
}

void DeleteImage(Image *image){
    free(image->R);
    free(image->G);
    free(image->B);
    free(image);
}

unsigned int ImageWidth(const Image *image){
    return image->W;
}

unsigned int ImageHeight(const Image *image){
    return image->H;
}