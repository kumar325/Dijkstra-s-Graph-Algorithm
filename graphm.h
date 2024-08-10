// ------------------------------------------------ graphm.h ----------------------------------------------------------
// Karan Kumar CSS 343
// 5/3/24
// --------------------------------------------------------------------------------------------------------------------
// Purpose - represents a graph using an adjacency matrix. A second
// matrix is used to store the shortest path from each node to every
// other node. This matrix is populated by using findShortestPath()
// on a graph. Dijkstra's algorithm is used to determine the shortest
// paths.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <string>
using namespace std;

const int MAXNODES = 100;

struct TableType
{
    bool visited; // whether node has been visited
    int dist;     // shortest distance from source known so far
    int path;     // previous node in path of min dist
};

class GraphM
{
public:
    // Constructor
    GraphM();

    // Functions
    void buildGraph(ifstream &f);

    bool insertEdge(int source, int dest, int cost);

    bool removeEdge(int source, int dest);

    void findShortestPath();

    void displayAll();

    void display(int source, int dest);

private:
    NodeData data[MAXNODES];         // data for graph nodes
    int C[MAXNODES][MAXNODES];       // Cost array, the adjacency matrix
    int size;                        // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path

    // Helper Functions
    int findVector(int source);

    void setShortestPath(int source, int v);

    void displayFrom(int source);

    void pathDesc(int source, int dest);

    void displayPath(int source, int dest);
};

#endif
