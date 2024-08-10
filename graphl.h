// ------------------------------------------------ graphl.h ----------------------------------------------------------
// Karan Kumar CSS 343
// 5/3/24
// --------------------------------------------------------------------------------------------------------------------
// Purpose - represents a graph using an adjacency list. Each node in
// the graph is represented by an index in the list. The elements of
// the list include a list of nodes to which the indicated node is
// adjacent. The graph does not keep track of its size.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include "graphm.h"
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
using namespace std;

//const int MAXNODES = 100;

struct EdgeNode // forward reference for the compiler
{ 
    int adjGraphNode; /// subscript of the adjacent graph node
    EdgeNode *nextEdge;
};

struct GraphNode // structs used for simplicity, use classes if desired
{                       
    EdgeNode *edgeHead; // head of the list of edges
    NodeData *data;     // data information about each node
    bool visited;
};

class GraphL
{
public:
    //Constructor and Destructor 
    GraphL();

    ~GraphL();

    //Functions
    void buildGraph(ifstream &f);

    void displayGraph();

    void depthFirstSearch();

private:
    int size;
    GraphNode nodes[MAXNODES];

    // Helper Function
    void dfs(int v);
};
#endif