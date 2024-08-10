// ------------------------------------------------ graphm.cpp --------------------------------------------------------
// Karan Kumar CSS 343
// 5/3/24
// --------------------------------------------------------------------------------------------------------------------
// Purpose - represents a graph using an adjacency matrix. A second
// matrix is used to store the shortest path from each node to every
// other node. This matrix is populated by using findShortestPath()
// on a graph. Dijkstra's algorithm is used to determine the shortest
// paths.
// --------------------------------------------------------------------------------------------------------------------

#include "graphm.h"

/** Default Constructor
 * Creates an empty graph and initializes matrixes to sane values.
 * @pre None.
 * @post An empty graph exists and none of the matrix nodes contain garbage values.
 */
GraphM::GraphM()
{
    size = 0;
    for (int i = 0; i < MAXNODES; i++)
    {
        for (int j = 0; j < MAXNODES; j++)
        {
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
            C[i][j] = INT_MAX;
        }
    }
}

/** build Graph
 * Builds a graph from data in an ifstream. The input file must be formatted so
 * that the first line contains only the number of nodes. The next lines should
 * contain text descriptions of the nodes, one per line, for as many lines as
 * were specified by the integer on the first line. All remaining lines should
 * contain three integers separated by white space that represent starting node,
 * destination node, and cost of edge.
 * @pre The ifstream is readable and contains a valid graph description.
 * @post This graph will represent the data from input.
 */
void GraphM::buildGraph(ifstream &f)
{
    int source, dest, cost;
    f >> size;
    string name;
    getline(f, name);

    for (int i = 1; i <= size; i++)
    {
        data[i].setData(f);
    }

    while (f >> source >> dest >> cost)
    {
        if (source == 0 && dest == 0 && cost == 0)
            break;
        C[source][dest] = cost;
    }
}

/**insert Edge
 * Inserts a single edge into the graph between two existing nodes.
 * @pre source and dest are within the limits of the adjacency matrix; cost is positive.
 * @post The edge now exists in this graph. Any shortest paths found are no longer valid.
 */
bool GraphM::insertEdge(int source, int dest, int cost)
{
    if (cost < 0 ||
        (cost != 0 && source == dest) ||
        source > size || dest > size ||
        source < 1 || dest < 1)
        return false;

    C[source][dest] = cost;
    findShortestPath();
    return true;
}

/**remove Edge
 * Removes a single existing edge from the graph.
 * @pre The specified edge exists within this graph.
 * @post The edge is removed from this graph. Any shortest paths found are no longer valid.
 */
bool GraphM::removeEdge(int source, int dest)
{
    if (dest > size || dest < 1 || source > size || source < 1)
        return false;

    C[source][dest] = INT_MAX;
    findShortestPath();
    return true;
}

/**find Shortest Path
 * Uses Dijkstra's Algorithm to find the shortest paths from every node to every
 * other node. A path matrix is used to store path descriptions.
 * @pre The graph is not empty.
 * @post All shortest paths are represented in the path matrix. A flag is set to indicate the matrix is valid.
 */
void GraphM::findShortestPath(void)
{
    int num, v;
    for (int i = 1; i <= size; ++i)
    {
        for (int j = 1; j <= size; ++j)
        {
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
            T[i][j].visited = false;
        }
    }

    for (int source = 1; source <= size; ++source)
    {
        num = 0;
        T[source][source].dist = 0;

        while (num < size)
        {
            v = findVector(source);
            T[source][v].visited = true;
            ++num;
            setShortestPath(source, v);
        }
    }
}

/**display All
 * Prints out a list of all nodes and their adjacencies. Requires that shortest
 * paths have been found. If this is not the case, findShortestPath() is invoked.
 * @pre The graph is not empty.
 * @post If paths were not valid, they have been updated.
 */
void GraphM::displayAll()
{
    findShortestPath();
    cout.width(26);
    cout << left << "Description";
    cout.width(11);
    cout << "From node";
    cout.width(9);
    cout << "To node";
    cout.width(12);
    cout << "Dijkstra's";
    cout.width();
    cout << "Path" << endl;

    for (int source = 1; source <= size; ++source)
    {
        displayFrom(source);
    }

    cout << endl;
}

/**display
 * Displays the full path and distance between two specified nodes.
 * Requires that shortest paths have been found.
 * @pre This graph is not empty.
 * @post If paths were not valid, they have been updated.
 */
void GraphM::display(int source, int dest)
{
    if (T[source][dest].dist < INT_MAX)
    {
        cout.width(4);
        cout << right << source;
        cout.width(8);
        cout << dest;
        cout.width(8);
        cout << T[source][dest].dist;
        cout << "        ";
        displayPath(source, dest);
        cout << source << endl
             << data[dest] << endl;
        pathDesc(source, dest);
    }
    else
    {
        cout << "No path from " << source << " to " << dest << '.' << endl;
    }

    cout << endl;
}

/**find Vector
 * Finds a vector to visit for the shortest path routine.
 * @pre This graph is not empty.
 * @post None.
 */
int GraphM::findVector(int source)
{
    int v = 0;

    for (int i = 1; i <= size; ++i)
    {
        if (!T[source][i].visited)
        {
            if (T[source][i].dist < T[source][v].dist)
            {
                v = i;
            }
        }
    }
    return v;
}

/** set Shortest Path
 * * Sets the current shortest path information on all nodes adjacent to the
 * visited node.
 * @pre v has been found and is the correct node to visit.
 * @post The path matrix is updated with the shortest distance currently known
 *       for all nodes adjacent to v.
 */
void GraphM::setShortestPath(int source, int v)
{
    for (int w = 1; w <= size; ++w)
    {
        if (!T[source][w].visited && C[v][w] < INT_MAX && T[source][v].dist < INT_MAX)
        {
            if (T[source][w].dist > (T[source][v].dist + C[v][w]))
            {
                T[source][w].dist = T[source][v].dist + C[v][w];
                T[source][w].path = v;
            }
        }
    }
}

/**display From
 * Displays all the nodes that have paths from a specified node. Requires that
 * shortest paths have been found.
 * @pre The graph is not empty. The path matrix is valid.
 * @post None.
 */
void GraphM::displayFrom(int source)
{
    cout.width(32);
    cout << left << data[source] << endl;

    for (int dest = 1; dest <= size; ++dest)
    {
        if (dest != source)
        {
            cout.width(35);
            cout << right << source;
            cout.width(5);
            cout << dest;
            cout.width(14);

            if (T[source][dest].dist == INT_MAX)
            {
                cout << "----" << endl;
            }
            else
            {
                cout << T[source][dest].dist;
                cout.width();
                cout << "    ";
                displayPath(source, dest);
                cout << dest << endl;
            }
        }
    }
}

/**path Desc
 * Displays the description of a path.
 * @pre Shortest paths have been found.
 * @post None.
 */
void GraphM::pathDesc(int source, int dest)
{
    if (T[source][dest].path != 0)
    {
        pathDesc(source, T[source][dest].path);
        cout << data[dest] << endl;
    }
}

/**display Path
 * Displays the full path and distance between two nodes.
 * Requires that shortest paths have been found.
 * @pre This graph is not empty.
 * @post None.
 */
void GraphM::displayPath(int source, int dest)
{
    findShortestPath();
    if (T[source][dest].path != 0)
    {
        displayPath(source, T[source][dest].path);
        cout << T[source][dest].path << ' ';
    }
}
