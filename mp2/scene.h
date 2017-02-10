#ifndef Scene_H
#define Scene_H
#include <string>
#include "png.h"
#include "rgbapixel.h"
#include "image.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
class Scene
{
public:
  int* x;
  int* y;
  Scene(int maxium);
  Scene(const Scene &source);
  ~Scene();
  void clear();
  const Scene& operator=(const Scene &source);
  void addpicture(const char* FileName, int index, int xcoo, int ycoo);
  void changelayer(int index, int newindex);
  void changemaxlayers(int newmax);
  void deletepicture(int index);
  Image drawscene();
  Image* getpicture(int index);
  void translate(int index, int xcoord, int ycoord);
  void copy(const Scene &other);
  int max;
  Image** layers;

};

#endif
