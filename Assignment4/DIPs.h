#ifndef DIPS_H
#define DIPS_H
#include "Constants.h"

/* DIP function declarations*/

/*reverse image color*/
Image *Negative(Image *image);

/*color filter*/
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/*edge detection*/
Image *Edge(Image *image);

/* mirror image horizontally*/
Image *HMirror(Image *image);

/* change color image to black & white*/
Image *BlackNWhite(Image *image);

/* shuffle the image */
Image *Shuffle(Image *image);

/* add border*/
Image *AddBorder(Image *image, char color[SLEN], int border_width);

/* flip image vertically*/
Image *VFlip(Image *image);

#endif