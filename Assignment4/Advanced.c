#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "Constants.h"
#include "Advanced.h"

double FishEyeLens(double coordinate, double radius, double distortion){
    double distorted_radius;
    distorted_radius = 1.0 - distortion * (radius*radius);
    if (distorted_radius > -1e8 && distorted_radius < 1e-8){    //close to zero?
        return coordinate;
    }
        return coordinate / distorted_radius;
}

Image *FishEye(Image *image, double distortion_factor, double scaling_factor){
        int  x, y, x_src, y_src;
        double normalized_x, normalized_y, radius, source_x, source_y;
        unsigned char *R = malloc(image->W * image->H * sizeof(unsigned char));
        unsigned char *G = malloc(image->W * image->H * sizeof(unsigned char));
        unsigned char *B = malloc(image->W * image->H * sizeof(unsigned char));

        for(y=0; y<image->H; y++)
        {   for(x=0; x<image->W; x++)
                {
                    // normalize x and y to be in interval of [-1, 1]
                    normalized_x = (double)(2*x - image->W)/(double)image->W;
                    normalized_y = (double)(2*y - image->H)/(double)image->H;

                    // compute radius (distance from normalized center)
                    radius = sqrt(normalized_x*normalized_x + normalized_y*normalized_y);

                    // compute normalized pixel coordinates through fish eye lens
                    source_x = FishEyeLens(normalized_x, radius, distortion_factor);
                    source_y = FishEyeLens(normalized_y, radius, distortion_factor);

                    // resize the image
                    source_x /= scaling_factor;
                    source_y /= scaling_factor;

                    // convert the normalized distorted coordinates back to image pixels
                    x_src = ((source_x + 1)*image->W)/2.0;
                    y_src = ((source_y + 1)*image->H)/2.0;

                    // if source pixel is in bounds, copy from source pixel location to destination
                    if ((0 <= x_src && x_src < image->W) && (0 <= y_src && y_src < image->H))
                        {
                            SetPixelR(image, x, y, GetPixelR(image, x_src, y_src));
                            SetPixelG(image, x, y, GetPixelG(image, x_src, y_src));
                            SetPixelB(image, x, y, GetPixelB(image, x_src, y_src));
                        }
                    else
                        {
                           SetPixelR(image, x, y, 0);
                            SetPixelG(image, x, y, 0);
                            SetPixelB(image, x, y, 0);
                        }
                }
        }
        for (y = 0; y < image->H; y++)
        {
            for (x = 0; x < image->W; x++)
            {
                SetPixelR(image, x, y, GetPixelR(image, x, y));
                SetPixelG(image, x, y, GetPixelG(image, x, y));
                SetPixelB(image, x, y, GetPixelB(image, x, y));
            }
        }

        free(R);
        free(G);
        free(B);

        return image;
}

Image *Rotate(Image *image, double Angle, double ScaleFactor, int CenterX, int CenterY){
    unsigned char *RotatedR = malloc(image->W * image->H * sizeof(unsigned char));
    unsigned char *RotatedG = malloc(image->W * image->H * sizeof(unsigned char));
    unsigned char *RotatedB = malloc(image->W * image->H * sizeof(unsigned char));
    int x, y;
    int x2, y2;
    const double pi = 3.141592653589793238462024;
    double Radian;
    double ScaleX, ScaleY;
    double M[2][2];

    Radian = -Angle/360.0 * 2*pi;
    ScaleX = ScaleFactor;
    ScaleY = ScaleFactor;
    M[0][0] = cos(Radian)/ScaleX;
    M[0][1] = -sin(Radian)/ScaleX;
    M[1][0] = sin(Radian)/ScaleY;
    M[1][1] = cos(Radian)/ScaleY;
    for(y=0; y<HEIGHT; y++)
    {   for(x=0; x<WIDTH; x++)
        {
            x2 = (x-CenterX)*M[0][0] + (y-CenterY)*M[0][1] + CenterX;
            y2 = (x-CenterX)*M[1][0] + (y-CenterY)*M[1][1] + CenterY;
            if (  (x2<0) || (x2>image->W-1)
                ||(y2<0) || (y2>image->H-1))
            {
                RotatedR[y*image->W+x] = 0;
                RotatedG[y*image->W+x] = 0;
                RotatedB[y*image->W+x] = 0;
            }
            else
            {
                RotatedR[y*image->W+x] = GetPixelR(image, x2, y2);
                RotatedG[y*image->W+x] = GetPixelG(image, x2, y2);
                RotatedB[y*image->W+x] = GetPixelB(image, x2, y2);
            }
        }
    }
    for(y=0; y<image->H; y++)
    {   for(x=0; x<image->W; x++)
        {
            SetPixelR(image, x, y, RotatedR[y*image->W+x]);
            SetPixelG(image, x, y, RotatedG[y*image->W+x]);
            SetPixelB(image, x, y, RotatedB[y*image->W+x]);
        }
    }
    free(RotatedR);
    free(RotatedG);
    free(RotatedB);

    return image;
}

Image *Posterize(Image *image, int rbits, int gbits, int bbits){
    int x, y;
        for(x=0; x<image->W; x++) {
            for(y=0; y<image->H; y++) {
                    unsigned char one = 1;
                    int i;
                    for(i=0; i<rbits-1; i++) {
                            SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
                            one <<= 1;
                    }
                    one = ~one;
                    SetPixelR(image, x, y, GetPixelR(image, x, y) & one);
                    one = 1;
                    for(i=0; i<gbits-1; i++) {
                            SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
                            one <<= 1;
                    }
                    one = ~one;
                    SetPixelG(image, x, y, GetPixelG(image, x, y) & one);

                    one = 1;
                    for(i=0; i<bbits-1; i++) {
                            SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
                            one <<= 1;
                    }
                    one = ~one;
                    SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
            }
        }
        return image;
}

Image *MotionBlur(Image *image, unsigned char BlurAmount){

        int x,y,m;
        double temp_r , temp_g , temp_b;
        double sum_r, sum_g, sum_b;
        int n;

        for (x = 0; x < image->W - 1; x++)
        {
                for (y = 0; y < image->H - 1; y++)
                {
                        temp_r = GetPixelR(image, x, y);
                        temp_g = GetPixelG(image, x, y);
                        temp_b = GetPixelB(image, x, y);
                        sum_r = 0.0;
                        sum_g = 0.0;
                        sum_b = 0.0;
                        n = 0;
                        for (m = 1; m<=BlurAmount ; m++)
                        {
                                if ((x+m) < image->W)
                                {
                                        sum_r = sum_r + GetPixelR(image, x+m, y);
                                        sum_g = sum_g + GetPixelG(image, x+m, y);
                                        sum_b = sum_b + GetPixelB(image, x+m, y);
                                        n = m;
                                }else{
                                        break;
                                }
                        }
                        temp_r = temp_r*0.5 + sum_r * 0.5/n;
                        temp_g = temp_g*0.5 + sum_g * 0.5/n;
                        temp_b = temp_b*0.5 + sum_b * 0.5/n;
                        SetPixelR(image, x, y, temp_r);
                        SetPixelG(image, x, y, temp_g);
                        SetPixelB(image, x, y, temp_b);
        }
        
        }
        return image;
}


Image *Crop(Image *image, int x, int y, int W, int H){
    assert(image != NULL);
    assert(x >= 0 && y >= 0 && W > 0 && H > 0);
    assert(x + W <= image->W && y + H <= image->H);

    //Ensure the crop dimension does not exceed the image dimensions
    if (x + W > image->W){
        W = image->W - x;
    }
    
    if (y + H > image->H){
        H = image->H - y;
    }

    Image *newImage = CreateImage(W, H);

    for (int j = 0; j < H; j++){
        for (int i = 0; i < W; i++){
            SetPixelR(newImage, i, j, GetPixelR(image, x + i, y + j));
            SetPixelG(newImage, i, j, GetPixelG(image, x + i, y + j));
            SetPixelB(newImage, i, j, GetPixelB(image, x + i, y + j));
        }
    }
    return newImage;

}

Image *Resize(Image *image, int newWidth, int newHeight){
    assert(image != NULL);
    assert(newWidth > 0 && newHeight > 0);

    Image *newImage = CreateImage(newWidth, newHeight);

    //Calculate the scale factors
    double scaleX = (double)image->W / newWidth;
    double scaleY = (double)image->H / newHeight;

    // Copy the pixel data from the original image to the new image
    for (unsigned int j = 0; j < newHeight; j++){
        for (unsigned int i = 0; i < newWidth; i++){
            int x = (int)(i * scaleX);
            int y = (int)(j * scaleY);
            SetPixelR(newImage, i, j, GetPixelR(image, x, y));
            SetPixelG(newImage, i, j, GetPixelG(image, x, y));
            SetPixelB(newImage, i, j, GetPixelB(image, x, y));
        }
    }
    return newImage;
}

Image *Watermark(Image *image, const Image *watermark_image){
    assert(image != NULL);
    assert(watermark_image != NULL);
    const Image *watermark = watermark_image;
    //Create a new image
    Image *newImage = CreateImage(image->W, image->H);

    //Copy the pixel data from the original image to the new image
    for (unsigned int j = 0; j < image->H; j++){
        for (unsigned int i = 0; i < image->W; i++){
            unsigned int x = i % watermark_image->W;
            unsigned int y = j % watermark_image->H;

            unsigned char r = GetPixelR(image, i, j);
            unsigned char g = GetPixelG(image, i, j);
            unsigned char b = GetPixelB(image, i, j);

            //Apply the watermark if the pixel in the watermark image is black
            if (GetPixelR(watermark, x, y) == 0 && GetPixelG(watermark, x, y) == 0 && GetPixelB(watermark, x, y) == 0){
                r = (unsigned char) fmin(r * 1.45, 255);
                g = (unsigned char) fmin(g * 1.45, 255);
                b = (unsigned char) fmin(b * 1.45, 255);
            }

            SetPixelR(newImage, i, j, r);
            SetPixelG(newImage, i, j, g);
            SetPixelB(newImage, i, j, b);

        }
    }

    return newImage;
}

Image *RotateBy90(Image *image, int rotateDirection){
    int oldWidth = image->W;
    int oldHeight = image->H;
    int newWidth = oldHeight;
    int newHeight = oldWidth;

    Image *newImage = CreateImage(newWidth, newHeight);

    for(int i = 0; i < oldWidth; i++){
        for(int j = 0; j < oldHeight; j++){
            int newI = rotateDirection == 0 ? j : newWidth - 1 - j;
            int newJ = rotateDirection == 0 ? newHeight - 1 - i : i;

            SetPixelR(newImage, newI, newJ, GetPixelR(image, i, j));
            SetPixelG(newImage, newI, newJ, GetPixelG(image, i, j));
            SetPixelB(newImage, newI, newJ, GetPixelB(image, i, j));
        }
    }
    return newImage;
}