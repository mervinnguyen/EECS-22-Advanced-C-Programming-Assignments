#include "Constants.h"
#include "Advanced.h"
#include <math.h>
#define SLEN 80
#define WIDTH 512
#define HEIGHT 288
#define PI 3.14159265

// Add missing declaration for variable "R"
unsigned char R[WIDTH][HEIGHT];
unsigned char G[WIDTH][HEIGHT];
unsigned char B[WIDTH][HEIGHT];

double FishEyeLens(double coordinate, double radius, double distortion){
    double distorted_radius = 1.0 - distortion * pow(radius, 2.0);
        if (distorted_radius < pow(10, -2)){
            return coordinate;
        } else {
        return coordinate / distorted_radius;
        }
}

void FishEye(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double distortion_factor, double scaling_factor){
    int x, y;
    int x_src, y_src;
    double normalized_x, normalized_y;
    double radius;
    double source_x, source_y;
    unsigned char Rtemp[WIDTH][HEIGHT];
    unsigned char Gtemp[WIDTH][HEIGHT];
    unsigned char Btemp[WIDTH][HEIGHT];

    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            Rtemp[x][y] = R[x][y];
            Gtemp[x][y] = G[x][y];
            Btemp[x][y] = B[x][y];
        }
    }

    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            normalized_x = (2.0 * x - WIDTH) / WIDTH;
            normalized_y = (2.0 * y - HEIGHT) / HEIGHT;
            radius = sqrt(pow(normalized_x, 2.0) + pow(normalized_y, 2.0));
            source_x = FishEyeLens(normalized_x, radius, distortion_factor);
            source_y = FishEyeLens(normalized_y, radius, distortion_factor);
            source_x = source_x / scaling_factor;
            source_y = source_y / scaling_factor;
            x_src = (source_x + 1.0) * WIDTH / 2.0;
            y_src = (source_y + 1.0) * HEIGHT / 2.0;
            if (x_src >= 0 && x_src < WIDTH && y_src >= 0 && y_src < HEIGHT){
                R[x][y] = R[x_src][y_src];
                G[x][y] = G[x_src][y_src];
                B[x][y] = B[x_src][y_src];
            } else {
            //set target pixel to black
                R[x][y] = 0;
                G[x][y] = 0;
                B[x][y] = 0;
            
            }
        }
    }
}

void Rotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], double Angle, double ScaleFactor, int CenterX, int CenterY){
    int x, y;
    int xNew, yNew;
    unsigned char R_temp[WIDTH][HEIGHT], G_temp[WIDTH][HEIGHT], B_temp[WIDTH][HEIGHT];

    //Convert angle to radians
    double AngleRad = Angle * ( 2 * PI / 360.0);

    // Copy original image to temp arrays
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            R_temp[x][y] = R[x][y];
            G_temp[x][y] = G[x][y];
            B_temp[x][y] = B[x][y];
        }
    }

    // Apply rotation and scaling
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            xNew = (int)(((cos(AngleRad) * (x - CenterX)) + (-sin(AngleRad) * (y - CenterY))) / ScaleFactor + CenterX);
            yNew = (int)(((sin(AngleRad) * (x - CenterX)) + (cos(AngleRad) * (y - CenterY))) / ScaleFactor + CenterY);
            if (xNew >= 0 && xNew < WIDTH - 1 && yNew >= 0 && yNew < HEIGHT - 1){
                R[x][y] = R_temp[xNew][yNew];
                G[x][y] = G_temp[xNew][yNew];
                B[x][y] = B_temp[xNew][yNew];
            } else {
                R[x][y] = 0;
                G[x][y] = 0;
                B[x][y] = 0;
            }
        }
    }
}

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){
    int x, y;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            R[x][y] = R[x][y] & (~((1 << rbits) - 1)) | ((1 << (rbits -1)) -1);
            G[x][y] = G[x][y] & (~((1 << gbits) - 1)) | ((1 << (gbits -1)) -1);
            B[x][y] = B[x][y] & (~((1 << bbits) - 1)) | ((1 << (bbits -1)) -1);
        }
    }
}

void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int x, y;
    int sumR, sumG, sumB;
    int count;
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++){
            sumR = R[x][y] / 2;
            sumG = G[x][y] / 2;
            sumB = B[x][y] / 2;
            count = 1;
            for (int i = 1; i <= BlurAmount; i++){
                if (x + i < WIDTH){
                    sumR += R[x + i][y];
                    sumG += G[x + i][y];
                    sumB += B[x + i][y];
                    count++;
                }
            }
            R[x][y] = (R[x][y] / 2) + (sumR / (2 * count));
            G[x][y] = (G[x][y] / 2) + (sumG / (2 * count));
            B[x][y] = (B[x][y] / 2) + (sumB / (2 * count));
        }
    }
}