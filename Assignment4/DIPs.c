#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#include "DIPs.h"
#include "Constants.h"

/* Example of DIP */
/* reverse image color */
Image *Negative(Image *image) {
        assert(image != NULL);
        int x, y;
        for (y = 0; y < image->H; y++) {
                for (x = 0; x < image->W; x++) {
                        SetPixelR(image, x, y, MAX_PIXEL - GetPixelR(image, x, y));
                        SetPixelG(image, x, y, MAX_PIXEL - GetPixelG(image, x, y));
                        SetPixelB(image, x, y, MAX_PIXEL - GetPixelB(image, x, y));
                }
        }
        return image;
}

/* color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b) {
        int x, y;

        replace_r = (replace_r > MAX_PIXEL) ? MAX_PIXEL : (replace_r < 0) ? 0 : replace_r;
        replace_g = (replace_g > MAX_PIXEL) ? MAX_PIXEL : (replace_g < 0) ? 0 : replace_g;
        replace_b = (replace_b > MAX_PIXEL) ? MAX_PIXEL : (replace_b < 0) ? 0 : replace_b;

        for (y = 0; y < image->H; y++){
                for (x = 0; x < image->W; x++){
                        if (abs(GetPixelR(image,x,y) - target_r) <= threshold && abs(GetPixelG(image,x,y) - target_g) <= threshold && abs(GetPixelB(image,x,y) - target_b) <= threshold) {
                                SetPixelR(image, x, y, replace_r);
                                SetPixelG(image, x, y, replace_g);
                                SetPixelB(image, x, y, replace_b);
                        }
                }
        }
        return image;
}

/* edge detection */
Image *Edge(Image *image) {
        int x, y, m, n, a, b;
        unsigned char *tmpR = malloc(image->W * image->H * sizeof(unsigned char));
        unsigned char *tmpG = malloc(image->W * image->H * sizeof(unsigned char));
        unsigned char *tmpB = malloc(image->W * image->H * sizeof(unsigned char));

        for (y = 0; y < image->H; y++){
                for (x = 0; x < image->W; x++){
                    tmpR[y * image->W + x] = GetPixelR(image, x, y);
                    tmpG[y * image->W + x] = GetPixelG(image, x, y);
                    tmpB[y * image->W + x] = GetPixelB(image, x, y);
                }
        }
        int sumR =0;
        int sumG =0;
        int sumB =0;
        int sume2R =0;
        int sume2G =0;
        int sume2B =0;
        for(y=1; y < image->H-1; y++){
                for(x=1; x < image->W-1; x++){
                        for(n=-1; n<=1; n++){
                                for(m=-1; m<=1; m++){
                                        a = (x+m >= image->W) ? image->W-1 : (x+m < 0) ? 0 : x+m;
                                        b = (y+n >= image->H) ? image->H-1 : (y+n < 0) ? 0 : y+n;
                                        sumR += (tmpR[y*image->W+x] - tmpR[b*image->W+a]);
                                        sumG += (tmpG[y*image->W+x] - tmpG[b*image->W+a]);
                                        sumB += (tmpB[y*image->W+x] - tmpB[b*image->W+a]);
                                }
                        }
                        sume2R = (sumR > MAX_PIXEL) ? MAX_PIXEL : (sumR < 0) ? 0 : sumR;
                        sume2G = (sumG > MAX_PIXEL) ? MAX_PIXEL : (sumG < 0) ? 0 : sumG;
                        sume2B = (sumB > MAX_PIXEL) ? MAX_PIXEL : (sumB < 0) ? 0 : sumB;
                        SetPixelR(image, x, y, sume2R);
                        SetPixelG(image, x, y, sume2G);
                        SetPixelB(image, x, y, sume2B);
                        sumR = sumG = sumB = 0;
                }
        }
        /* set all 24 borders to 0 */
        for (y = 0; y < image->H; y++) {
                SetPixelR(image, 0, y, 0);
                SetPixelG(image, 0, y, 0);
                SetPixelB(image, 0, y, 0);
                SetPixelR(image, image -> W - 1, y, 0);
                SetPixelG(image, image -> W - 1, y, 0);
                SetPixelB(image, image -> W - 1, y, 0);
        }
        for (x = 0; x < image->W; x++) {
                SetPixelR(image, x, 0, 0);
                SetPixelG(image, x, 0, 0);
                SetPixelB(image, x, 0, 0);
                SetPixelR(image, x, image -> H - 1, 0);
                SetPixelG(image, x, image -> H - 1, 0);
                SetPixelB(image, x, image -> H - 1, 0);
        }
    free(tmpR);
    free(tmpG);
    free(tmpB);

    return image;
}

/* mirror image horizontally */
Image *HMirror(Image *image){
    int x, y;
    for (y = 0; y < image->H; y++) {
        for (x = 0; x < image -> W / 2; x++) {
            SetPixelR(image, image->W - 1 - x, y, GetPixelR(image, x, y));
            SetPixelG(image, image->W - 1 - x, y, GetPixelG(image, x, y));
            SetPixelB(image, image->W - 1 - x, y, GetPixelB(image, x, y));
        }
    }
}

/* add border to the image */
Iamge *AddBorder(Image *image, char color[SLEN], int border_width){
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
        for (y = 0; y < image->H; y++) {
            for (x = 0; x < image->W; x++) {
                if ((y < border_width) || (y > HEIGHT - 1 - border_width) || (x < border_width) || (x > WIDTH - 1 - border_width)) {
                        SetPixelR(image, x, y, border_r);
                        SetPixelG(image, x, y, border_g);
                        SetPixelB(image, x, y, border_b);
                }
            }
        }
}

/* change color image to black & white */
Image *BlackNWhite(Image *image)
{
    int x, y, tmp;
    for (y = 0; y < image->H; y++)
    {
        for (x = 0; x < image->W; x++)
        {
            tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, tmp);
            SetPixelG(image, x, y, tmp);
            SetPixelB(image, x, y, tmp);
        }
    }
}

/* flip image vertically */
Image *VFlip(Image *image)
{
    int x, y;
    unsigned char r, g, b;

    for (y = 0; y < image->H/2; y++) {
        for (x = 0; x < image->W; x++) {
            r = GetPixelR(image, x, image->H - 1 - y);
            g = GetPixelG(image, x, image->H - 1 - y);
            b = GetPixelB(image, x, image->H - 1 - y);
            
            SetPixelR(image, x, image->H - 1 - y, GetPixelR(image, x, y));
            SetPixelG(image, x, image->H - 1 - y, GetPixelG(image, x, y));
            SetPixelB(image, x, image->H - 1 - y, GetPixelB(image, x, y));

            SetPixelR(image, x, y, r);
            SetPixelG(image, x, y, g);
            SetPixelB(image, x, y, b);
        }
    }
    return image;
}

/* Shuffle the image W24 */
Image *Shuffle(Image *image)
{
    int block_width = image->W/SHUFF_WIDTH_DIV;
    int block_height = image->H/SHUFF_HEIGHT_DIV;
    int i, j, x, y;
    unsigned char *tempR = malloc(block_width * block_height * sizeof(unsigned char));
    unsigned char *tempG = malloc(block_width * block_height * sizeof(unsigned char));
    unsigned char *tempB = malloc(block_width * block_height * sizeof(unsigned char));

    for (i = 0; i < SHUFF_HEIGHT_DIV/2; i++){ // only need to iterate throught half of the blocks
        for (j = 0; j < SHUFF_WIDTH_DIV; j++){
            for (x = 0; x < block_width; x++){
                for (y = 0; y < block_height; y++){
                    tempR[y * block_width + x] = GetPixelR(image, x + (j * block_width), y + (i * block_height));
                    tempG[y * block_width + x] = GetPixelG(image, x + (j * block_width), y + (i * block_height));
                    tempB[y * block_width + x] = GetPixelB(image, x + (j * block_width), y + (i * block_height));
                    SetPixelR(image, x + j * block_width, y + i * block_height, GetPixelR(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height));
                    SetPixelG(image, x + j * block_width, y + i * block_height, GetPixelG(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height));
                    SetPixelB(image, x + j * block_width, y + i * block_height, GetPixelB(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height));
                    SetPixelR(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height, tempR[y * block_width + x]);
                    SetPixelG(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height, tempR[y * block_width + x]);
                    SetPixelB(image, x + (SHUFF_WIDTH_DIV - 1 -j) * block_width, y + (SHUFF_HEIGHT_DIV - 1 -i) * block_height, tempR[y * block_width + x]);
                }
            }
        }
    }
        free(tempR);
        free(tempG);
        free(tempB);

        return image;
}
                            