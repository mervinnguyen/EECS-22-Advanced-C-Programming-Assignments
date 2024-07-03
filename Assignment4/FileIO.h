#ifndef FILE_IO_H
#define FILE_IO_H

#include "Image.h"

Image* LoadImage(const char *fname);

int SaveImage(const char *fname, const Image *image);

#endif