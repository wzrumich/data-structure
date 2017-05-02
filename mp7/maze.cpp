/* Your code here! */
#include "maze.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <queue>
#include <sys/time.h>
SquareMaze::SquareMaze(){
w=0;
h=0;
}

void SquareMaze::makeMaze(int width, int height){
//clear
rightlist.clear();
downlist.clear();
w = width;
h = height;
DisjointSets cell;
cell.addelements(width*height);
//set all grid with walls
  std::vector<bool> v;
for(int i=0; i<width; i++){
v.clear();
  for(int j=0; j<height; j++){
v.push_back(true);
  }
  rightlist.push_back(v);
  downlist.push_back(v);
}
//random delete wall w/o cycle
srand (time(NULL));
int randomdir, randomxc, randomyc = 0;
int loop = width*height-1;
while(loop>0){
  randomxc = rand() %w;
  randomyc = rand() %h;
  //right or down
randomdir = rand() %2;
//right
if(randomdir%2==0){
  int index = w*randomyc+randomxc;
  int move = index+1;
 if(cell.find(index)!=cell.find(move)&&randomxc!=w-1){
  rightlist[randomxc][randomyc]= false;
  cell.setunion(index, move);
  loop--;
}
}
//down
   else if(randomdir%2 ==1){
  int index2 = randomyc+randomxc;
  int move2 = w*(randomyc+1)+randomxc;
  if(cell.find(index2)!=cell.find(move2)&&randomyc!=h-1){
    downlist[randomxc][randomyc] = false;
    cell.setunion(index2, move2);
    loop--;
  }
}
}
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
if(x<0||y<0||x>w||y>h)  return;
if(dir!=1&&dir!=0) return;
if(dir==0&&x!=w-1){
rightlist[x][y]=exists;
}
else if(dir==1&&y!=h-1){
  downlist[x][y]=exists;
}




}
bool SquareMaze::canTravel(int x, int y, int dir) const{
if(x<0||y<0||x>w||x>h||dir>3||dir<0)  return false;
// rightward
if(dir==0) {
  return rightlist[x][y];
}
else if(dir == 1){
  return downlist[x][y];
}
else if(dir == 2){
  return rightlist[x-1][y];
}
else if(dir ==3){
  return downlist[x][y-1];
}

return false;
}

PNG* SquareMaze::drawMaze() const{
  int pw = w*10;
  int ph = h*10;
PNG * ret = new PNG(pw+1, ph+1);
(*ret)(0,0)->red = 0;
(*ret)(0,0)->green =0;
(*ret)(0,0)->blue=0;
for(int i=1; i<pw;i++){
  (*ret)(0,i)->red = 0;
  (*ret)(0,i)->green =0;
  (*ret)(0,i)->blue=0;
}
for(int i=10; i<ph ; i++){
  (*ret)(i,0)->red = 0;
  (*ret)(i,0)->green =0;
  (*ret)(i,0)->blue=0;
}
for(int x=0; x<w; x++){
  for(int y=0; y<h ; y++){
    if(rightlist[x][y]){
      for(int k=0; k<11;k++){
        (*ret)((x+1)*10, y*10+k)->red=0;
          (*ret)((x+1)*10, y*10+k)->green=0;
            (*ret)((x+1)*10, y*10+k)->blue=0;
      }
    }
    if(downlist[x][y]){
      for(int t=0; t<11;t++){
        (*ret)(x*10+t, (y+1)*10)->red=0;
          (*ret)(x*10+t, (y+1)*10)->green=0;
            (*ret)(x*10+t, (y+1)*10)->blue=0;
      }
    }
  }
}

return ret;


}

PNG* SquareMaze::drawMazeWithSolution(){
 PNG* ret = new PNG(100,100);
 return ret;


}

vector<int> SquareMaze::solveMaze(){
std::vector<int> v;
v.push_back(1);
return v;
}
