#include <iostream>
#include "image.h"
#include "png.h"
using namespace std;
#include <cstdint>
void Image :: flipleft(){
     int width = this->width();
     int height = this->height();
     for(int i=0; i<width/2;i++){
       for(int j=0; j<height; j++){

         RGBAPixel* up = (*this)(i,j);
         RGBAPixel* in = (*this)(width-i-1,j);
         RGBAPixel mid = *(*this)(i,j);
         *up=*in;
         *in=mid;

       }
     }
}

void Image :: adjustbrightness(int r, int g, int b){
int width = this->width();
int height= this->height();
for(int i=0; i<width; i++){
  for(int j=0; j<height; j++){
if((*this)(i,j)->red+r<0)
   (*this)(i,j)->red=0;
   else if ((*this)(i,j)->red+r>255)
   (*this)(i,j)->red=255;
   else
    (*this)(i,j)->red +=r;
  if((*this)(i,j)->green+g<0)
    (*this)(i,j)->green=0;
    else if ((*this)(i,j)->green+g>255)
    (*this)(i,j)->green =255;
    else
    (*this)(i,j)->green +=g;
    if((*this)(i,j)->blue+b<0)
    (*this)(i,j)->blue=0;
    else if ((*this)(i,j)->blue+b>255)
    (*this)(i,j)->blue=255;
    else (*this)(i,j)->blue  +=b;

  }
}
}

void Image:: invertcolors(){
int width=this->width();
int height=this->height();
for(int i=0; i<width ;i++){
  for(int j=0; j<height; j++){
    (*this)(i,j)->red=255-(*this)(i,j)->red;
    (*this)(i,j)->green=255-(*this)(i,j)->green;
    (*this)(i,j)->blue=255-(*this)(i,j)->blue;

  }
}

}
