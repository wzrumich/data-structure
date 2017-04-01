/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
/*default constructor
*/
Quadtree::Quadtree(){
  root = NULL;
  resolution=0;
}
/*
*build a Quadtree representing the upper-left d by d block of the source image.
*/
Quadtree::Quadtree(PNG const & source, int resolution){
if((int)source.width()>=resolution&&(int)source.height()>=resolution){
  root=NULL;
  this->resolution=resolution;
  buildTree(source,resolution);
}
}
/*
*destructor
*/
Quadtree::~Quadtree(){
  clear(root);
}
/*
*helper function clear
*/
void Quadtree::clear(QuadtreeNode * & node){
  if(node!=NULL){
    clear(node->nwChild);
    clear(node->neChild);
    clear(node->swChild);
    clear(node->seChild);
    delete node;
    node=NULL;
  }
}
/*
*helper function
*/
void Quadtree::copy(QuadtreeNode * & change, QuadtreeNode *  source){
     if(change==NULL||source==NULL)
       return ;
       change->element=source->element;
     if(source->nwChild==NULL);// no child
     else{
        change->nwChild=new QuadtreeNode();
        copy(change->nwChild,source->nwChild);
        change->neChild=new QuadtreeNode();
        copy(change->neChild,source->neChild);
        change->swChild=new QuadtreeNode();
        copy(change->swChild,source->swChild);
        change->seChild=new QuadtreeNode();
        copy(change->seChild,source->seChild);
}//recursively copy children
}
//constructor for QuadtreeNode
Quadtree::QuadtreeNode::QuadtreeNode(){
  element=RGBAPixel();
  nwChild=NULL;
  neChild=NULL;
  swChild=NULL;
  seChild=NULL;
}
Quadtree::Quadtree( const Quadtree & other){
    if(other.root==NULL){
      root=NULL;
      resolution=0;
    }
    else{
      root=new QuadtreeNode();
     copy(root,other.root);
     resolution=other.resolution;
}
}// cctor for Quadtree
Quadtree const & Quadtree::operator=(Quadtree const & other){
          if(other.root==NULL){
            clear(root);
            root=NULL;
          }
        else if(this!=&other){
           clear(root);
           root=new QuadtreeNode();
           copy(root,other.root);
           resolution=other.resolution;
         }
         return * this;
}//operator= for Quadtree

void Quadtree::buildTree(PNG const & source, int resolution){
// make sure the width and height at least d
if((int)source.width()>=resolution&&(int)source.height()>=resolution){
//delete content
  if(root!=NULL){
    clear(root);
    root=NULL;
  }
  this->resolution=resolution;
  build(root,0,0,resolution,source);
}
}
//helper function
void Quadtree::build(QuadtreeNode * & subroot, int x, int y, int resolution,PNG const & source ){

if(subroot==NULL)
subroot=new QuadtreeNode();
//base case
if(resolution<=1){
  subroot->element=*source(x,y);
}
// recursively color
else {
  resolution=resolution/2;
  build(subroot->nwChild,2*x,2*y,resolution,source);
  build(subroot->neChild,2*x+1,2*y,resolution,source);
  build(subroot->swChild,2*x,2*y+1,resolution,source);
  build(subroot->seChild,2*x+1,2*y+1,resolution,source);
//You may want to ensure that, at all times, the element field of each interior (i.e. non-leaf) node of your quadtree stores the average of its children’s element fields
  subroot->element.red=(subroot->nwChild->element.red+
                        subroot->neChild->element.red+
                        subroot->swChild->element.red+
                        subroot->seChild->element.red)/4;
  subroot->element.green=(subroot->nwChild->element.green+
                        subroot->neChild->element.green+
                        subroot->swChild->element.green+
                        subroot->seChild->element.green)/4;
  subroot->element.blue=(subroot->nwChild->element.blue+
                        subroot->neChild->element.blue+
                        subroot->swChild->element.blue+
                        subroot->seChild->element.blue)/4;

}
}
//returns the RGBApixel corresponding to the pixel at coordinates (x,y)(x,y)
// it will return the element of the nonexistent leaf’s deepest surviving ancestor.) If the supplied coordinates fall outside of the bounds of the underlying bitmap, or if the current Quadtree is empty (i.e., it was created by the default constructor) then the returned RGBApixel should be the one which is created by the default RGBApixel constructor.
RGBAPixel Quadtree::getPixel(int x, int y) const{
//nonnegatvie non null
if(x<0||x>resolution||y<0||y>=resolution||root==NULL){
  RGBAPixel spret;
  return spret;
}
else {
  return getpoint(root,x,y,resolution);

}
}
//helper
RGBAPixel Quadtree::getpoint(QuadtreeNode* subroot, int x, int y, int resolution)const{
 if(subroot==NULL){
   return RGBAPixel();
 }
 else if(resolution<=1){
   if(x==0&&y==0){
     return subroot->element;
   }
   else  return RGBAPixel();

 }
 //find the point
else{
if(subroot->nwChild==NULL){
  return subroot->element;
}
//recursively find the point
  resolution=resolution/2;
  if(x>=resolution&&y>=resolution){
    return getpoint(subroot->seChild,x-resolution,y-resolution,resolution);
  }
  else if(x<resolution&&y>=resolution){
    return getpoint(subroot->swChild,x,y-resolution,resolution);
  }
  else if(x>=resolution&&y<resolution){
    return getpoint(subroot->neChild,x-resolution,y,resolution);
  }
  else   return  getpoint(subroot->nwChild,x,y,resolution);

}
}
//The return value should be the underlying PNG object represented by the Quadtree. If the current Quadtree is empty (i.e., it was created by the default constructor) then the returned PNG should be the one which is created by the default PNG constructor.
PNG Quadtree::decompress() const{
if(root==NULL){
  return PNG();
}
else{
  //return png
PNG::PNG source(resolution,resolution);
decom(root,0,0,resolution,source);
  return source;
}
}
//helper
void Quadtree::decom(QuadtreeNode* subroot, int x, int y, int resolution, PNG & source)const{
  if(subroot==NULL){}
  //when it reaches leaves
  if(subroot->nwChild==NULL||resolution<=1){
    for(int i=0; i<resolution ; i++){
      for(int j=0; j<resolution ; j++){
        *source(x*resolution+i,y*resolution+j)=subroot->element;
      }
    }
  }
  else {
    resolution=resolution/2;

decom(subroot->nwChild,2*x,2*y,resolution,source);
decom(subroot->neChild,2*x+1,2*y,resolution,source);
decom(subroot->swChild,2*x,2*y+1,resolution,source);
decom(subroot->seChild,2*x+1,2*y+1,resolution,source);



  }
}

//clockwiseRotate rotates the Quadtree object’s underlying image clockwise by 90 degrees.
void Quadtree::clockwiseRotate(){

rotatehelper(root,resolution);
}
//rotatehelper
void Quadtree::rotatehelper(QuadtreeNode* subroot, int resolution){
  if(subroot->nwChild==NULL||resolution<1){}
  else{
    QuadtreeNode* temp1 = new QuadtreeNode();
    temp1=subroot->nwChild;
    QuadtreeNode* temp2 = new QuadtreeNode();
    temp2=subroot->neChild;
    QuadtreeNode* temp3 = new QuadtreeNode();
    temp3=subroot->swChild;
    QuadtreeNode* temp4 = new QuadtreeNode();
    temp4=subroot->seChild;
    subroot->nwChild=temp3;
    subroot->neChild=temp1;
    subroot->swChild=temp4;
    subroot->seChild=temp2;
    resolution=resolution/2;
    rotatehelper(subroot->nwChild,resolution);
    rotatehelper(subroot->neChild,resolution);
    rotatehelper(subroot->swChild,resolution);
    rotatehelper(subroot->seChild,resolution);
  }
}

void Quadtree::prune(int tolerance){

     doprune(root,tolerance);
}
//clear the root after chek
void Quadtree::doprune( QuadtreeNode* & subroot, int tolerance){
    if(subroot==NULL||subroot->nwChild==NULL){return;}
    if(isprune(subroot,subroot,tolerance)){
      clear(subroot->nwChild);
      clear(subroot->neChild);
      clear(subroot->swChild);
      clear(subroot->seChild);
      subroot->nwChild=NULL;
      subroot->neChild=NULL;
      subroot->swChild=NULL;
      subroot->seChild=NULL;
    }
    else{
      doprune(subroot->nwChild,tolerance);
      doprune(subroot->neChild,tolerance);
      doprune(subroot->swChild,tolerance);
      doprune(subroot->seChild,tolerance);
    }
}
//check whether there is one childen in  four children of the root differ more than the tolerance
bool Quadtree::isprune(QuadtreeNode* root, QuadtreeNode* subroot, int tolerance) const{
    if(subroot==NULL){
      return  false;
    }
    if(subroot->nwChild==NULL){
     int diff =(root->element.red-subroot->element.red)*(root->element.red-subroot->element.red)+
    (root->element.green-subroot->element.green)*(root->element.green-subroot->element.green)+
    (root->element.blue-subroot->element.blue)*(root->element.blue-subroot->element.blue);
     if(diff<=tolerance)
    {
      return true;
    }
    else   return false;
    }
    else {
      return isprune(root,subroot->nwChild,tolerance)&&isprune(root,subroot->neChild,tolerance)&&
      isprune(root,subroot->swChild,tolerance)&&isprune(root,subroot->seChild,tolerance);
    }


  }


// it returns a count of the total number of leaves the Quadtree would have if it were pruned as in the prune function.


int Quadtree::pruneSize(int tolerance) const{

return   pruneCount(root,tolerance);

}
//helper
int Quadtree::pruneCount(QuadtreeNode* subroot, int tolerance) const{
  if(subroot==NULL){
    return 0;
  }
  else  if(isprune(subroot,subroot,tolerance)){
    return 1;
  }
  else if(subroot->nwChild==NULL){
    return 1;
  }
  else return pruneCount(subroot->nwChild,tolerance)+pruneCount(subroot->neChild, tolerance)+
  pruneCount(subroot->swChild, tolerance)+pruneCount(subroot->seChild, tolerance);
}
//reverse of the pruneSize
int Quadtree::idealPrune(int numLeaves) const{
if(root==NULL){return 0;}
return tolerancefind(0 , 3*255*255, numLeaves);
}
//helper function
int Quadtree::tolerancefind(int small, int big, int numLeaves)const{
    if(small>big){
      return small;
    }
    else{
    int mid=(small+big)/2;
    if(pruneSize(mid)<=numLeaves){
      return       tolerancefind(small, mid-1, numLeaves);

    }
    else{
      return tolerancefind(mid+1, big, numLeaves);
    }
  }

}
