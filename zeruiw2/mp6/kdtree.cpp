/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <vector>
#include <algorithm>
#include <cmath>
#include "point.h"
#include "kdtree.h"
#include "math.h"


template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{


  if(curDim<0 || curDim>Dim){
    return false;
  }
    /**
     * @todo Implement this function!
     */
    else {
       if(first[curDim]==second[curDim]){
       return first<second;
     }
    else return first[curDim]<second[curDim];
}

}
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{    int sumC=0;
     int sumP=0;
     for(int i=0; i<Dim ; i++){
       sumC= sumC + pow((currentBest[i]-target[i]),2);
       sumP= sumP + pow((potential[i]-target[i]),2);
     }
     if(sumC==sumP){
       return  currentBest>potential;
     }
     else {
       return sumC>sumP;
     }
    /**
     * @todo Implement this function!
     */


}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    points = newPoints;
    KDTreebuild(points, 0, points.size()-1, 0);
    /**
     * @todo Implement this function!
     */
}
template <int Dim>
void KDTree<Dim>::KDTreebuild(std::vector<Point<Dim>> &Points, int left, int right, int di){
  if(left>=right){
return ;
  }
  int mid = (left+right)/2;
  quickselect(Points, di ,left, right, mid);
  KDTreebuild(Points, left, mid-1, (di+1)%Dim);
  KDTreebuild(Points, mid+1, right, (di+1)%Dim);
}

template <int Dim>
int KDTree<Dim>::partiton( vector<Point<Dim>>& Points, int left, int right, int di, int pivot){
Point<Dim> pivotval = Points[pivot];
swap(Points, pivot, right);
 int storeindex = left;
for( int  i=left  ; i<right ; i++){
  if(smallerDimVal(Points[i], pivotval , di)){
    swap(Points, storeindex, i);
    storeindex++;
  }
}

    swap(Points, storeindex, right);
return storeindex;

}
template<int Dim>
void KDTree<Dim>::swap(std::vector<Point<Dim>> & Points,int a, int b){

  Point<Dim> temp = Points[a];
  Points[a]=Points[b];
  Points[b]=temp;
}

template <int Dim>
void KDTree<Dim>::quickselect( vector<Point<Dim>>& Points, int di , int left, int right, int k){
if(left>=right){
  return ;
}
else {
  int pivotindex = (left+right)/2;
  pivotindex=partiton(Points, left,right,di, pivotindex);

if(k==pivotindex){
  return ;
}
else {
  if(k<pivotindex){
    quickselect(Points, di, left, pivotindex-1,k);
  }
  else {
    quickselect(Points,di, pivotindex+1, right, k);
  }
}
}

}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
  int index = findhelper(query,points, 0,points.size()-1, 0);
  return points[index];
}
template <int Dim>
int KDTree<Dim>::findhelper(const Point<Dim>& query, const vector<Point<Dim>>  &points,  int lower, int upper, int di)const{
  if(lower==upper||lower>upper)  return lower;
  int mid = (lower+upper)/2;
  int index;

  if(smallerDimVal(query , points[mid] , di)){
    index = findhelper(query,points, lower, mid-1, (di+1)%Dim );
  }
  else {
    index = findhelper(query,points,  mid+1, upper,(di+1)%Dim);
  }
if(shouldReplace(query, points[index], points[mid])){
  index = mid;
}
int radius  = 0;
for(int i= 0; i<Dim ; i++){
  radius= radius + pow(query[i]-points[index][i],2);
}
if(pow(points[mid][di]-query[di],2)<=radius){
  if(smallerDimVal(query,points[mid],di)){
int temp1 = findhelper(query, points, mid+1, upper, (di+1)%Dim);
if(shouldReplace(query, points[index], points[temp1])){
  index =temp1;

}
}
else {
  int temp2 = findhelper(query,points, lower, mid-1, (di+1)%Dim);
    if(shouldReplace(query, points[index], points[temp2])){
      index = temp2;
    }
  }
}

return index;
}
