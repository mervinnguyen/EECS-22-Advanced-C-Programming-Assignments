#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
int AutoTest(void);

/* Menu */
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
        printf("14: Add Motion Blur to an image\n");
        printf("15: Crop an image\n");
        printf("16: Resize an image\n");
        printf("17: Add Watermark to an image\n");
        printf("18: Rotate an image by 90 degrees\n");
        printf("19: Test all functions\n");
        printf("20: Exit\n");
}

int main(void)
{
#ifdef DEBUG
        AutoTest();
#else
        int r24;
        int option;                     /* user input option */
        char fname[SLEN];               /* input file name */
        char colorOption[SLEN];

        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
        r24 = -1;

        Image *image = NULL;

        /* ColorFilter() parameters */
        int target_r, target_g, target_b, threshold;
        double factor_r, factor_g, factor_b;

        /* AddBorder() parameter */
        int border_width;
        unsigned char rbits, gbits, bbits;

        /* FishEye() parameter */
        double distortion_factor, scaling_factor;

        /* Rotate() parameter */
        double Angle, ScaleFactor;
        int CenterX, CenterY;

        /* MotionBlur() parameter */
        int BlurAmount;

        /* Crop() parameter*/
        int x, y, W, H;

        /* Resize() parameter*/
        int newWidth, newHeight;

        /* Watermark() parameter*/
        Image *watermark_image;

        /* RotateBy90() parameter*/
        int rotateDirection;

        /* Autotest() parameter*/
        int rc;


        while (option != EXIT) {
                if (option == 1) {
                        printf("Please input the file name to load: ");
                        scanf("%s", fname);
                        Image *r24 = LoadImage(fname);
                }
                
                /* menu item 2 - 14 requires image is loaded first */
                else if (option >= 2 && option <= 14) {
                        if (r24 != SUCCESS)      {
                                printf("No image is read.\n");
                        }
                        /* now image is loaded */
                        else {
                                switch (option) {
                                        case 2:
                                                printf("Please input the file name to save: ");
                                                scanf("%s", fname);
                                                SaveImage(fname, image);
                                                break;
                                        case 3:
                                                BlackNWhite(image);
                                                printf("\"Black & White\" operation is done!\n");
                                                break;
                                        case 4:
                                                Negative(image);
                                                printf("\"Negative\" operation is done!\n");
                                                break;
                                        case 5:
                                                printf("Enter Red   component for the target color: ");
                                                scanf("%d", &target_r);
                                                printf("Enter Green component for the target color: ");
                                                scanf("%d", &target_g);
                                                printf("Enter Blue  component for the target color: ");
                                                scanf("%d", &target_b);
                                                printf("Enter threshold for the color difference: ");
                                                scanf("%d", &threshold);
                                                printf("Enter value for Red component in the target color: ");
                                                scanf("%lf", &factor_r);
                                                printf("Enter value for Green component in the target color: ");
                                                scanf("%lf", &factor_g);
                                                printf("Enter value for Blue  component in the target color: ");
                                                scanf("%lf", &factor_b);

                                                ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
                                                printf("\"Color Filter\" operation is done!\n");
                                                break;
                                        case 6:
                                                Edge(image);
                                                printf("\"Edge\" operation is done!\n");
                                                break;
                                        case 7:
                                                Shuffle(image);
                                                printf("\"Shuffle\" operation is done!\n");
                                                break;
                                        case 8:
                                                VFlip(image);
                                                printf("\"VFlip\" operation is done!\n");
                                                break;
                                        case 9:
                                                HMirror(image);
                                                printf("\"HMirror\" operation is done!\n");
                                                break;
                                        case 10:
                                                printf("Enter border width:");
                                                scanf("%d", &border_width);
                                                printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                                                printf("Select border color from the options: ");
                                                scanf("%s",colorOption);
                                                AddBorder(image, colorOption, border_width);
                                                printf("\"Border\" operation is done!\n");
                                                break;
                                        case 11:
                                                printf("Enter a value for distortion factor:");
                                                scanf("%lf", &distortion_factor);
                                                printf("Enter a value for scaling factor:");
                                                scanf("%lf", &scaling_factor);
                                                FishEye(image, distortion_factor, scaling_factor);
                                                printf("\"FishEye\" operation is done!\n");
                                                break;
                                        case 12:
                                                printf("Enter the number of posterization bits for R channel (1 to 8):");
                                                scanf("%hhu", &rbits);
                                                printf("Enter the number of posterization bits for G channel (1 to 8):");
                                                scanf("%hhu", &gbits);
                                                printf("Enter the number of posterization bits for B channel (1 to 8):");
                                                scanf("%hhu", &bbits);
                                                Posterize(image, rbits, gbits, bbits);
                                                printf("\"Posterize\" operation is done!\n");
                                                break;
                                        case 13:
                                                printf("Enter the angle of rotation:");
                                                scanf("%lf", &Angle);
                                                printf("Enter the scale of zooming:");
                                                scanf("%lf", &ScaleFactor);
                                                printf("Enter the X-axis coordinate of the center of rotation:");
                                                scanf("%d", &CenterX);
                                                printf("Enter the Y-axis coordinate of the center of rotation:");
                                                scanf("%d", &CenterY);
                                                Rotate(image, Angle, ScaleFactor, CenterX, CenterY);
                                                printf("\"Rotate\" operation is done!\n");
                                                break;
                                        case 14:
                                                printf("Please input motion blur amount: ");
                                                scanf("%d", &BlurAmount);
                                                MotionBlur(image, BlurAmount);
                                                printf("\"Motion Blur\" operation is done!\n");
                                                break;
                                        case 15:
                                                printf("Please enter the X offset value: ");
                                                scanf("%d", &x);
                                                printf("Please enter the Y offset value: ");
                                                scanf("%d", &y);
                                                printf("Please enter the crop width: ");
                                                scanf("%d", &W);
                                                printf("Please enter the crop height: ");
                                                scanf("%d", &H);
                                                Crop(image, x, y, W, H);
                                                printf("\"Crop\" operation is done!\n");
                                                break;
                                        case 16:
                                                printf("Please enter the new image width: ");
                                                scanf("%d", &newWidth);
                                                printf("Please enter the new image height: ");
                                                scanf("%d", &newHeight);
                                                Resize(image, newWidth, newHeight);
                                                printf("\"Resize\" operation is done!\n");
                                                break;
                                        case 17: 
                                                watermark_image = LoadImage("watermark");
                                                Watermark(image, watermark_image);
                                                printf("\"Watermark\" operation is done!\n");
                                                break;
                                        case 18:
                                                printf("Please enter the direction of rotation (0 = clockwise, 1 = counter-clockwise): ");
                                                scanf("%d", &rotateDirection);
                                                RotateBy90(image, rotateDirection);
                                                printf("\"RotateBy90\" operation is done!\n");
                                        case 19:
                                                int rc = AutoTest();
                                                if (rc != SUCCESS) {
                                                        printf("AutoTest failed, error code is %d\n", rc);
                                                } else{
                                                        printf("AutoTest passed!\n");
                                                }
                                                break;
                                        case 20:
                                                printf("You exit the program.\n");
                                                if (image != NULL) {
                                                        DeleteImage(image);
                                                }
                                                exit(0);
                                                break;
                                        default:
                                                printf("Invalid selection!\n");
                                        }
                        }

                else if (option == 15) {
                        AutoTest();
                        r24 = SUCCESS;  /* set returned code SUCCESS, since image is loaded */
                }
                else {
                        printf("Invalid selection!\n");
                }

                /* Process finished, waiting for another input */
                PrintMenu();
                printf("Please make your choice: ");
                scanf("%d", &option);
        }
        printf("You exit the program.\n");
#endif

        
}
return 0;
}

