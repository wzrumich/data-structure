/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include <vector>
#include <algorithm>

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{   std::vector<Point<3>> totree;
    std::map<Point<3>, TileImage> m;
    for(auto lookup : theTiles){
      RGBAPixel average = lookup.getAverageColor();
    Point<3> toinsert(average.red, average.green, average.blue);
    m[toinsert]=lookup;
    totree.push_back(toinsert);
    }
    int wide = theSource.getColumns();
    int height = theSource.getRows();
    KDTree<3> findtree(totree);
    MosaicCanvas *ret = new MosaicCanvas(wide, height);
    for(int i=0; i<wide; i++){
      for (int j=0; j<height; j++){
        RGBAPixel region = theSource.getRegionColor(i,j);
        Point<3> tocompare(region.red, region.green, region.blue);
      Point<3> value =   findtree.findNearestNeighbor(tocompare);
      TileImage retT = m[value];
      ret->setTile(i,j,retT);

      }
    }
    return ret;


    /**
     * @todo Implement this function!
     */
    return NULL;
}
