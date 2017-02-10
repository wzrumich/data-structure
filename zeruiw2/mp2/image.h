#ifndef MYFILE_H
#define MYFILE_H
#include <stddef.h>
#include <stdlib.h>
#include "rgbapixel.h"
#include "png.h"
#include <iostream>

#include <stdio.h>
class Image : public PNG{
public:
  void flipleft();
  void adjustbrightness(int r, int g, int b);
  void invertcolors();



};

#endif
