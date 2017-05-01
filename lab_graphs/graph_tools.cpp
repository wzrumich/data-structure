/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */
#include "edge.h"
#include "graph_tools.h"
#include <map>
#include <vector>
/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    vector<Edge> edgelist = graph.getEdges();
    Edge edgemin = edgelist[0];
    for(size_t i=0; i<edgelist.size(); i++){
      if(edgelist[i]<edgemin){
        edgemin=edgelist[i];
      }
    }
    graph.setEdgeLabel(edgemin.source, edgemin.dest, "MIN");
    /* Your code here! */
    return edgemin.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> vertexlist = graph.getVertices();
    for(size_t i=0; i<vertexlist.size(); i++){
      graph.setVertexLabel(vertexlist[i], "Unexplored");
    }
    vector<Edge> edgelist = graph.getEdges();
    for(size_t i=0; i<edgelist.size(); i++){
      graph.setEdgeLabel(edgelist[i].source,edgelist[i].dest, "Unexplored" );
    }
    queue<Vertex> q;
    std::map<Vertex, int> dist;
    std::map<Vertex, Vertex> path;
    Vertex next;
    graph.setVertexLabel(start, "Visited");
    q.push(start);
    dist[start]=0;
    while(!q.empty()){
      next =q.front();
      if(next ==end) break;

    else {
      vector<Vertex> adj = graph.getAdjacent(next);
      q.pop();
      for(size_t i=0; i<adj.size(); i++){
        Vertex temp =adj[i];
        if(graph.getVertexLabel(temp)=="Unexplored"){
          q.push(temp);
          dist[temp]= dist[next]+1;
          graph.setVertexLabel(temp, "Visited");
          path[temp] = next;
        }
      }
    }
  }
  Vertex temp = next;
  while(path[temp]!=start){
    graph.setEdgeLabel(path[temp], temp, "MINPATH");
    temp=path[temp];
  }
  graph.setEdgeLabel(start, temp, "MINPATH");
  return dist[next];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    vector<Edge> edgelist = graph.getEdges();
    vector<Vertex> vertrxlist = graph.getVertices();
    std::sort(edgelist.begin(), edgelist.end());
    DisjointSets disj;
    std::map<Vertex, int> index;
    disj.addelements((int)vertrxlist.size());
    int count =0;
    for(size_t i=0; i<edgelist.size()&&count<vertrxlist.size()-1; i++){
     Vertex vsource = edgelist[i].source;
     Vertex vdest = edgelist[i].dest;
     if(disj.find(vsource)!=disj.find(vdest)){
       disj.setunion(vsource, vdest);
       graph.setEdgeLabel(vsource, vdest, "MST");
       count++;
          }

    }






    /* Your code here! */
}
