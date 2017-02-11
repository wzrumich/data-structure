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
  if(other.layers[i]!=NULL){
  this->layers[i]=new Image(*(other.layers[i]));
  x[i]=other.x[i];
  y[i]=other.y[i];}
  else{
    layers[i]=NULL;
    x[i]=0;
    y[i]=0;
  }
}
}

void Scene::clear(){

for(int i=0; i<max ; i++){
  if(layers[i]!=NULL){
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

  if(max>newmax){
    for(int i=newmax-1; i<max ; i++){
      if(layers[i]!=NULL){
  cout<< "invalid newmax"<<endl;
  return;}
  }
  }
  if(max==newmax){

      return;
  }

  Image ** change = new Image*[newmax];
  int * xnew=new int[newmax];
  int * ynew=new int[newmax];

for(int j=0; j<newmax; j++){
  change[j]=NULL;
  xnew[j]=0;
  ynew[j]=0;
}


  for(int i=0; i<max; i++){
  if(layers[i]!=NULL){
(change[i])=(this->layers[i]);
xnew[i]=x[i];
ynew[i]=y[i];}

}


for(int i=0; i<max ; i++){
  if(layers[i]!=NULL){

    layers[i]=NULL;
  }
  }


  delete[] layers;
  delete[] x;
  delete[] y;
  max=newmax;
 layers=change;
 change=NULL;
 x=xnew;
 xnew=NULL;
 y=ynew;
 ynew=NULL;




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
       if(layers[newindex]!=NULL){
         delete layers[newindex];
         layers[newindex]=NULL;
       }
  layers[newindex]=layers[index];
  x[newindex]=x[index];
  y[newindex]=y[index];
  layers[index]=NULL;
  x[index]=0;
  y[index]=0;
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
  if(index<0||index>max-1||layers[index]==NULL){
    cout<<"invalid index"<<endl;
  }
  else{
  delete layers[index];
  layers[index]=NULL;
  x[index]=0;
  y[index]=0;
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
