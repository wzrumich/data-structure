/* Your code here! */
#ifndef DisjointSets_H
#define DisjointSets_H

#include <vector>
using namespace std;
class DisjointSets{


public:
void addelements(int num);
int  find(int elem);
void setunion(int a, int b);
std::vector<int> data;
};

#endif
