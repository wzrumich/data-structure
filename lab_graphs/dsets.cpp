/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;
void DisjointSets::addelements(int num){

  for(int i=0; i<(int)num ; i++){
    data.push_back(-1);
  }
}
int DisjointSets::find(int elem){
if(data.size()<=0||elem>(int)data.size()){
  return -1;
}
else if(data[elem]<0)
  return elem;
  else return data[elem]=find(data[elem]);

}

void DisjointSets::setunion(int a, int b){
if(a>(int)data.size()||b>(int)data.size()) return ;
int newsize;
int root1 = find(a);
int root2 = find(b);
if(root1==root2){
  return ;
}

else   if(data[root1]<=data[root2]){
   newsize = data[root1]+data[root2];
    data[root2]=root1;
    data[root1]=newsize;
  }
  else {
  newsize = data[root1]+data[root2];
  data[root1]=root2;
  data[root2]=newsize;
}

}
