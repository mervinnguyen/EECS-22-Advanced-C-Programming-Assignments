
/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.h: header file for image list manipulations             */
/*********************************************************************/
#ifndef IMAGELIST_H
#define IMAGELIST_H

#include "Image.h"

typedef struct ImageEntry IENTRY;
typedef struct ImageList ILIST;
typedef struct Image IMAGE; // Add this line to define the struct

struct ImageEntry {
        ILIST *List;         /* Pointer to the list which this entry belongs to */
        IENTRY *Next;        /* Pointer to the next entry, or NULL */
        IENTRY *Prev;        /* Pointer to the previous entry, or NULL */
        IMAGE *image         /* Pointer to the RGB image, or YUV image, or NULL */
};

struct ImageList {
        unsigned int Length;  /* Length of the list */
        IENTRY *First;        /* Pointer to the first entry, or NULL */
        IENTRY *Last;         /* Pointer to the last entry, or NULL */
};

static IENTRY *NewImageEntry(IMAGE *image);

#include "Image.h"

static IMAGE *DeleteImageEntry(IENTRY *e);

/* Create a new image list */
ILIST *CreateImageList(void);

ILIST *NewImageList(void);

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list);

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage);

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage);

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end);

/* Fast forward an image list */
unsigned int FastImageList(ILIST *list, unsigned int factor);

/* Reverse an image list */
void ReverseImageList(ILIST *list);

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage);

#endif
