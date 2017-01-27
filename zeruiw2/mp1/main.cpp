#include "png.h"

PNG rotate(PNG origin)
{
  int width=origin.width();
  int height=origin.height();
  PNG result= PNG(width, height);
  for(int i=0; i<width; i++){
    for(int j=0; j<height ;j++){


 RGBAPixel * in =origin(i,j);
 RGBAPixel * out  =result(width-i-1,height-j-1);
 *out=*in;

    }
  }
  return result;
}

 int main() {
 PNG inimage("in.png");
 inimage = rotate(inimage);
  inimage.writeToFile("out.png");
  return 0;
}
