// ------------------------------------------------ graphl.cpp --------------------------------------------------------
// Karan Kumar CSS 343
// 5/3/24
// --------------------------------------------------------------------------------------------------------------------
// Purpose - represents a graph using an adjacency list. Each node in
// the graph is represented by an index in the list. The elements of
// the list include a list of nodes to which the indicated node is
// adjacent. The graph does not keep track of its size.
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h"

/**Default Constructor
 * Creates an empty graph and sets all pointers to NULL.
 * @pre None.
 * @post An empty graph exists. All pointers are NULL.
 */
GraphL::GraphL()
{
    size = 0;
    for (int i = 1; i < MAXNODES; i++)
    {
        nodes[i].visited = false;
        nodes[i].edgeHead = nullptr;
        nodes[i].data = nullptr;
    }
}

/**Destructor
 * Deletes all dynamically allocated memory and sets remaining pointers to
 * NULL.
 * @pre None.
 * @post All memory is freed and any pointers are NULL.
 */
GraphL::~GraphL()
{
    for (int i = 1; i <= size; i++)
    {
        delete nodes[i].data;
        nodes[i].data = nullptr;
        nodes[i].visited = false;

        EdgeNode *ptr = nodes[i].edgeHead;
        while (ptr)
        {
            nodes[i].edgeHead = nodes[i].edgeHead->nextEdge;
            delete ptr;
            ptr = nodes[i].edgeHead;
        }
    }
}

/**build Graph 
 * Constructs a graph from an input file.
 * @pre The ifstream input can be read.
 * @post This graph represents the graph described in input.
 */
void GraphL::buildGraph(ifstream &f)
{
    int source, dist;
    f >> size;
    string str;
    getline(f, str);

    for (int i = 1; i <= size; i++)
    {
        getline(f, str);
        NodeData *temp = new NodeData(str);
        nodes[i].data = temp;
    }

    while (f >> source >> dist)
    {
        if (source == 0 && dist == 0)
            return;

        EdgeNode *node = new EdgeNode;
        node->adjGraphNode = dist;

        if (nodes[source].edgeHead)
        {
            node->nextEdge = nodes[source].edgeHead;
            nodes[source].edgeHead = node;
        }
        else
        {
            nodes[source].edgeHead = node;
            nodes[source].edgeHead->nextEdge = nullptr;
        }
    }
}

/**display Graph 
 * Prints out the nodes and their edges.
 * @pre None.
 * @post None.
 */
void GraphL::displayGraph()
{
    cout << "Graph: " << endl;

    for (int i = 1; i <= size; i++)
    {
        cout << "Node #" << i << "\t\t" << *nodes[i].data << "\n\n";

        EdgeNode *curr = nodes[i].edgeHead;
        while (curr)
        {
            cout << "  "
                 << "Edge  " << i << "  " << curr->adjGraphNode << endl;
            curr = curr->nextEdge;
        }
        cout << endl;
    }
}

/**depth First Search 
 * Lists the nodes in depth-first-search order.
 * @pre None.
 * @post None.
 */
void GraphL::depthFirstSearch()
{
    cout << "Depth-First Search Ordering: ";

    for (int i = 1; i <= size; i++)
    {
        if (!nodes[i].visited)
            dfs(i);
    }
    cout << endl;
}

/**dfs 
 * Helper for depthFirstSearch().
 * @pre v is the proper node to search from.
 * @post All nodes from v have been visited.
 */
void GraphL::dfs(int v)
{
    cout << "  " << v;
    nodes[v].visited = true;
    EdgeNode *curr = nodes[v].edgeHead;

    while (curr)
    {
        if (!nodes[curr->adjGraphNode].visited)
            dfs(curr->adjGraphNode);

        curr = curr->nextEdge;
    }
}