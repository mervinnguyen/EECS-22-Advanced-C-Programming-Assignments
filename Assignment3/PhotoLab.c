#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"
#define DEBUG
//Update PhotoLab.c, Advanced.c, Advanced.h
void PrintMenu() {
        printf("\n----------------------------\n");
        printf(" 1: Load a PPM image\n");
        printf(" 2: Save an image in PPM and JPEG format\n");
        printf(" 3: Change a color image to Black & White\n");
        printf(" 4: Make a negative of an image\n");
        printf(" 5: Color filter an image\n");
        printf(" 6: Sketch the edge of an image\n");
        printf(" 7: Shuffle an image\n");
        printf(" 8: Flip an image vertically\n");
        printf(" 9: Mirror an image horizontally\n");
        printf("10: Add border to an image\n");
        printf("11: Create a fisheye image\n");
        printf("12: Posterize an image\n");
        printf("13: Rotate and zoom an image\n");
        printf("14: Motion Blur\n");
        printf("15: Test all functions\n");
        printf("16: Exit\n");
}

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        char fname[SLEN] = "EngPlaza";
        char sname[SLEN];
        #ifdef DEBUG

        LoadImage(fname, R, G, B);
        Negative(R, G, B);
        strcpy(sname, "negative");
        SaveImage(sname, R, G, B);
        printf("Negative tested!\n\n");

        LoadImage(fname, R, G, B);
        ColorFilter(R, G, B, 130, 130, 150, 30, 0, 255, 255);
        strcpy(sname, "colorfilter");
        SaveImage(sname, R, G, B);
        printf("Color Filter tested!\n\n");

        LoadImage(fname, R, G, B);
        Edge(R, G, B);
        strcpy(sname, "edge");
        SaveImage(sname, R, G, B);
        printf("Edge Detection tested!\n\n");


        LoadImage(fname, R, G, B);
        HMirror(R, G, B);
        strcpy(sname, "hmirror");
        SaveImage(sname, R, G, B);
        printf("HMirror tested!\n\n");

        LoadImage(fname, R, G, B);
        AddBorder (R, G, B, "pink", 32);
        strcpy(sname, "border");
        SaveImage(sname, R, G, B);
        printf("Border tested!\n\n");

        LoadImage(fname, R, G, B);
        BlackNWhite(R, G, B);
        strcpy(sname, "bw");
        SaveImage(sname, R, G, B);
        printf("Black & White tested!\n\n");

        LoadImage(fname, R, G, B);
        VFlip(R, G, B);
        strcpy(sname, "vflip");
        SaveImage(sname, R, G, B);
        printf("VFlip tested!\n\n");

        LoadImage(fname, R, G, B);
        Shuffle(R, G, B);
        strcpy(sname, "shuffle");
        SaveImage(sname, R, G, B);
        printf("Shuffle tested!\n\n");

        LoadImage(fname, R, G, B);
        FishEye(R, G, B, 0.5, 2.0);
        strcpy(sname, "fisheye");
        SaveImage(sname, R, G, B);
        printf("Fisheye tested!\n\n");

        LoadImage(fname, R, G, B);
        Posterize(R, G, B, 7, 7, 7);
        strcpy(sname, "posterize");
        SaveImage(sname, R, G, B);
        printf("Posterize tested!\n\n");

        LoadImage(fname, R, G, B);
        MotionBlur(R, G, B, 40);
        strcpy(sname, "motionblur");
        SaveImage(sname, R, G, B);
        printf("Motion Blur tested!\n\n");

        LoadImage(fname, R, G, B);
        Rotate(R, G, B, 22, 0.78, 110, 220);
        strcpy(sname, "rotate");
        SaveImage(sname, R, G, B);
        printf("Rotate tested!\n\n");

        #endif
}

int main(void) {
        unsigned char   R[WIDTH][HEIGHT];       /* use three 2-D arrays to store R, G, B components */
        unsigned char   G[WIDTH][HEIGHT];
        unsigned char   B[WIDTH][HEIGHT];


        int option;                     /* user input option */
        char fname[SLEN];               /* input file name */
        char colorOption[SLEN];

while(1){
        PrintMenu();
        scanf("%d", &option);
        switch(option){
        case 1:
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            LoadImage(fname, R, G, B);
            break;
        case 2: 
            printf("Please input the file name to save: ");
            scanf("%s", fname);
            SaveImage(fname, R, G, B);
            break;
        case 3:
            BlackNWhite(R, G, B);
            printf("\"Black & White\" operation is done!\n");   //backslash signifies double quote 
            break;
        case 4:
            Negative(R, G, B);
            printf("\"Negative\" operation is done!\n");
            break;
        case 5:

            printf("Enter Red component for the target color: ");
            int target_r;
            scanf("%d", &target_r);
            printf("Enter Green component for the target color: ");
            int target_g;
            scanf("%d", &target_g);
            printf("Enter Blue component for the target color: ");
            int target_b;
            scanf("%d", &target_b);
            printf("Enter threshold for the color difference: ");
            int threshold;
            scanf("%d", &threshold);
            printf("Enter value for Red component in the target color: ");
            int replace_r;
            scanf("%d", &replace_r);
            printf("Enter value for Green component in the target color: ");
            int replace_g;
            scanf("%d", &replace_g);
            printf("Enter value for Blue component in the target color: ");
            int replace_b;
            scanf("%d", &replace_b);
            ColorFilter(R, G, B, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
            printf("\"Color Filter\" operation is done!\n");
            break;  
        case 6:
            Edge(R, G, B);
            printf("\"Edge\" operation is done!\n");
            break;
        case 7:
        int blockHeight = 0, blockWidth = 0, blockx = 0, blocky = 0, blockSwitchx = 0, blockSwitchy = 0, x = 0, y = 0;
            Shuffle(R, G, B);
            printf("\"Shuffle\" operation is done!\n");
            break;
        case 8:
            VFlip(R, G, B);
            printf("\"VFlip\" operation is done!\n");
            break;
        case 9:
            HMirror(R, G, B);
            printf("\"HMirror\" operation is done!\n");
            break;
        case 10:
            char color[SLEN];
            printf("Enter border width: ");
            int border_width;
            scanf("%d", &border_width);
            printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
            printf("Select border color from the options: ");
            AddBorder(R, G, B, color, border_width);
            printf("\"Border\" operation is done!\n");
            break;
        case 11:
            printf("Enter a value for distortion factor: ");
            double distortion_factor;
            scanf("%lf", &distortion_factor);
            printf("Enter a value for scaling factor: ");
            double scaling_factor;
            scanf("%lf", &scaling_factor);
            FishEye(R, G, B, distortion_factor, scaling_factor);
            printf("\"Fisheye\" operation is done!\n");
            break;
        case 12:
            printf("Enter the number of bits for each color component (1 to 8): ");
            int numBits;
            int rbits, gbits, bbits;
            scanf("%d", &rbits);
            scanf("%d", &gbits);
            scanf("%d", &bbits);
            scanf("%d", &numBits);
            Posterize(R, G, B, rbits, gbits, bbits);
            printf("\"Posterize\" operation is done!\n");
            break;
        case 13: 
            printf("Enter the angle of rotation: ");
            double Angle;
            scanf("%lf", &Angle);
            printf("Enter the scaling factor: ");
            double ScaleFactor;
            scanf("%lf", &ScaleFactor);
            printf("Enter the x-coordinate of the center of rotation: ");
            int CenterX;
            scanf("%d", &CenterX);
            printf("Enter the y-coordinate of the center of rotation: ");
            int CenterY;
            scanf("%d", &CenterY);
            Rotate(R, G, B, Angle, ScaleFactor, CenterX, CenterY);
            printf("\"Rotate\" operation is done!\n");
            break;
        case 14:
            printf("Enter the length of the motion: ");
            int motion_length;
            scanf("%d", &motion_length);
            MotionBlur(R, G, B, motion_length);
            printf("\"Motion Blur\" operation is done!\n");
            break;
        case 15:
            AutoTest(R, G, B);
            break;
        case 16:
            printf("You exit the program.\n");
            exit(0);
            break;
        default:
                printf("Invalid choice. Please try again.\n");

        }
}
       return 0;
}