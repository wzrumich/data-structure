#include <iostream>
#include <cstdint>
#include "scene.h"
#include <string>
#include <cstdint>
#include "png.h"
#include "rgbapixel.h"


using namespace std;

Scene::Scene(int maxium){
max=maxium;
layers=new Image*[max];

 x=new int[max];
 y=new int[max];

 for(int i=0; i<max; i++){
   x[i]=0;
   y[i]=0;
   layers[i]=NULL;
 }


}

Scene::~Scene()
{
clear();
}
Scene::Scene(const Scene & source){
  copy(source);
}
void Scene::copy(const Scene & other){
max=other.max;
x=new int[max];
y=new int[max];
layers=new Image*[max];
for(int i=0; i<max; i++){
  layers[i]=NULL;
  x[i]=0;
  y[i]=0;
}
for(int i=0; i<max; i++){
  if(other.layers[i]!=NULL){
  this->layers[i]=new Image(*(other.layers[i]));
  x[i]=other.x[i];
  y[i]=other.y[i];
}
}
}
void Scene::clear(){

for(int i=0; i<max ; i++){
  if(layers!=NULL){
    delete layers[i];
    layers[i]=NULL;
  }
  }
  delete[] layers;
  if(x!=NULL){
    delete[] x;
    x=NULL;
  }
  if(y!=NULL){
    delete[] y;
    y=NULL;
  }
}
const Scene& Scene::operator=(const Scene & source){
  if(this!=&source){
    clear();
    copy(source);
  }
  return *this;
}
void Scene::changemaxlayers(int newmax){
if(max<newmax){
Image ** change = new Image*[newmax];
  for(int i=0; i<newmax ; i++){
    if(i<max)
change[i]=layers[i];
else if (i>=max&&i<newmax)
change[i]=NULL;
  }
}
if(max==newmax){
  Image ** change = new Image*[newmax];
    for(int i=0; i<newmax ; i++){
  change[i]=layers[i];
}
}
if(max>newmax)
cout<<
"invalid newmax"<<endl;
}
void Scene::addpicture(const char* FileName, int index, int xcoo, int ycoo){

if(index>max){
  cout<< "index out of bounds"<<endl;
}
else{
Image* newone = new Image();
newone->readFromFile(FileName);
for(int i=0; i<max; i++){
  if(i==index)
  layers[i]=newone;
  x[index]=xcoo;
  y[index]=ycoo;
}
}
}

void Scene::changelayer(int index, int newindex){
     if(index>max||newindex>max||index<0||newindex<0){
       cout<<"invalid index"<<endl;}
     else    if(index==newindex){

     }
     else{
     Image* mid=new Image;
     mid = layers[index];
     layers[index]=layers[newindex];
     layers[newindex]=mid;
     int midx=x[index];
     x[index]=x[newindex];
     x[newindex]=midx;
     int midy=y[index];
     y[index]=y[newindex];
     y[newindex]=midy;
   }
}


void Scene::translate(int index, int xcoord, int ycoord){

if(index<0||index>max){
  cout<<"invalid index"<<endl;
}
else
 x[index]=xcoord;
 y[index]=ycoord;

}

void Scene::deletepicture(int index){
  if(index<0||index>max||layers[index]==NULL){
    cout<<"invalid index"<<endl;
  }
  else{
  delete layers[index];
  layers[index]=NULL;
}
  }



Image * Scene::getpicture(int index){

  if(index<0||index>max){
    cout<<"invalid index"<<endl;
  }

  return layers[index];
}


Image Scene::drawscene(){

int realwidth=1;
int realheight=1;
Image result;
int testwidth=1;
int testheight=1;
int fitwidth =0;
int fitheight=0;
for(int i=0; i<max; i++){
  if(layers[i]!=NULL){
  testwidth  = layers[i]->width()+x[i];
  testheight = layers[i]->height()+y[i];
  realheight=(testheight>realheight)?(testheight):(realheight);
  realwidth= (testwidth>realwidth)?(testwidth):(realwidth);
}

}
  result.resize(realwidth,realheight);

  for(int i=0; i<max;i++){
    if(layers[i]!=NULL){
    fitwidth=layers[i]->width()+x[i];
    fitheight=layers[i]->height()+y[i];
   for(int j=x[i]; j<fitwidth; j++){
    for (int k=y[i]; k<fitheight; k++){

    result(j,k)->red=(*layers[i])(j-x[i],k-y[i])->red;
    result(j,k)->green=(*layers[i])(j-x[i],k-y[i])->green;
    result(j,k)->blue=(*layers[i])(j-x[i],k-y[i])->blue;


    }

  }

}

}
return result;
}
