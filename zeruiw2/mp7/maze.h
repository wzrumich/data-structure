/* Your code here! */
#ifndef maze_H
#define maze_H
#include "png.h"
#include <vector>
#include "dsets.h"
using namespace std;
class SquareMaze{

public:
SquareMaze();
void makeMaze(int width, int height );
bool canTravel(int x, int y, int dir) const;
void setWall(int x, int y, int dir, bool exists);
PNG* drawMaze() const;
PNG* drawMazeWithSolution();
vector<int> solveMaze();
private:
int w;
int h;
vector<vector<bool>> rightlist;
vector<vector<bool>> downlist;
DisjointSets walls;


};

#endif
