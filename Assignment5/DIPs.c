/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* DIPs.c: source file for DIP operations                            */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include "string.h"
#include "math.h"

/* Black and White */
Image *BlackNWhite(Image *image)
{
        assert(image);
        int x, y, tmp;

        for (y = 0; y < ImageHeight(image); y++) {
                for (x = 0; x < ImageWidth(image); x++) {
                tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
                        SetPixelR(image, x, y, tmp);
                        SetPixelG(image, x, y, tmp);
                SetPixelB(image, x, y, tmp);
                }
        }
        return image;
}

/* Mirror image horizontal  */
Image *HMirror(Image *image) {
        assert(image);
        int x, y;
        for (y = 0; y < ImageHeight(image); y++) {
                for (x = 0; x < ImageWidth(image)/2; x++) {
                        SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
                        SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
                        SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
                }
        }
        return image;
}

/* Edge detection */
Image *Edge(Image *image) {
        assert(image);
        Image *tmpImage = CreateImage(ImageWidth(image), ImageHeight(image));
        assert(tmpImage);

        int x, y, m, n;
        memcpy(tmpImage->R, image->R, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(tmpImage->G, image->G, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        memcpy(tmpImage->B, image->B, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
        for (y = 1; y < ImageHeight(image) - 1; y++) {
 for (x = 1; x < ImageWidth(image) - 1; x++) {
                        int tmpR = 0;
                        int tmpG = 0;
                        int tmpB = 0;
                        for (m = -1; m <= 1; m++) {
                                for (n = -1; n <= 1; n++) {
                                        tmpR += (GetPixelR(tmpImage, x, y) - GetPixelR(tmpImage, x + n, y + m));
                                        tmpG += (GetPixelG(tmpImage, x, y) - GetPixelG(tmpImage, x + n, y + m));
                                        tmpB += (GetPixelB(tmpImage, x, y) - GetPixelB(tmpImage, x + n, y + m));
                                }
                        }
                        SetPixelR(image, x, y, (tmpR > 255) ? 255 : (tmpR < 0) ? 0 : tmpR);
                        SetPixelG(image, x, y, (tmpG > 255) ? 255 : (tmpG < 0) ? 0 : tmpG);
                        SetPixelB(image, x, y, (tmpB > 255) ? 255 : (tmpB < 0) ? 0 : tmpB);
                }
        }
        for (y = 0; y < ImageHeight(image); y++) {
                x = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                x = ImageWidth(image) - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }
        for (x = 0; x < ImageWidth(image); x++) {
                y = 0;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
                y = ImageHeight(image) - 1;
                SetPixelR(image, x, y, 0);
                SetPixelG(image, x, y, 0);
                SetPixelB(image, x, y, 0);
        }
        DeleteImage(tmpImage);
        tmpImage = NULL;
        return image;
}


/* Add a watermark to an image */
Image *Watermark(Image *image, const Image *watermark,
         unsigned int topLeftX, unsigned int topLeftY)
{
        unsigned int x, y;
        unsigned int R, G, B;

        assert(image);
        assert(watermark);
        
        for (x = 0; x < watermark->W; x++) {
                for (y = 0; y < watermark->H; y++) {
                        if (topLeftX + x < image->W && topLeftY + y < image->H) {
                               if (GetPixelR(watermark, x , y) == 0 && GetPixelG(watermark, x , y) == 0 && GetPixelB(watermark, x , y) == 0) {
                                        R = GetPixelR(image, topLeftX + x, topLeftY + y);
                                        G = GetPixelG(image, topLeftX + x, topLeftY + y);
                                        B = GetPixelB(image, topLeftX + x, topLeftY + y);
                                        
                                        if (R * WATERMARK_RATIO > 255) {
                                                SetPixelR(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelR(image, topLeftX + x, topLeftY + y, R * WATERMARK_RATIO);
                                        }
                                        if (G * WATERMARK_RATIO > 255) {
                                                SetPixelG(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelG(image, topLeftX + x, topLeftY + y, G * WATERMARK_RATIO);
                                        }
                                        if (B * WATERMARK_RATIO > 255) {
                                                SetPixelB(image, topLeftX + x, topLeftY + y, 255);
                                        } else {
                                                SetPixelB(image, topLeftX + x, topLeftY + y, B * WATERMARK_RATIO);
                                        }
                        }

                }
        }
        return image;
        }

/* Spotlight */
Image *Spotlight(Image *image, int centerX, int centerY, unsigned int radius)
{
        Image *new_image = CopyImage(image);

    // Iterate over each pixel in the image
    for (int y = 0; y < new_image->height; y++) {
        for (int x = 0; x < new_image->width; x++) {
            // Calculate the distance from the current pixel to the center
            int dx = x - centerX;
            int dy = y - centerY;
            unsigned int distance = sqrt(dx * dx + dy * dy);

            // If the distance is less than the radius, apply the spotlight effect
            if (distance < radius) {
                // Calculate the spotlight intensity
                double intensity = 1.0 - (double)distance / radius;

                // Apply the spotlight effect to the pixel
                new_image->data[y][x].r = (unsigned char)(new_image->data[y][x].r * intensity);
                new_image->data[y][x].g = (unsigned char)(new_image->data[y][x].g * intensity);
                new_image->data[y][x].b = (unsigned char)(new_image->data[y][x].b * intensity);
            }
        }
    }

    return new_image;
}

/* Rotate and zoom an image */
Image *Rotate(Image *image, double Angle, double ScaleFactor)
{
        /* to be implemented */
}

