#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define idVertex(V) V->idVertex
#define nextVertex(V) V->nextVertex
#define firstVertex(G) G.firstVertex
#define firstEdge(E)  E->firstEdge
#define nextEdge(E) E->nextEdge

#include <iostream>

using namespace std;

struct Edge;
struct Vertex;
typedef Vertex *adrVertex;
typedef edge *adrEdge;

struct Vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct Edge {
    char destVertexID;
    int weight;
    adrEdge nextEdge;
};

struct Graph {
    adrVertex firstVertex;
};


void createVertex(char newVertexID, adrVertex &V);
void initGraph(Graph &G);
void addVertex(Graph &G, char newVertexID);
void buildGraph(Graph &G);
void addEdge(Graph &G, char fromVertexID, char toVertexID, int weight);



#endif // GRAPH_H_INCLUDED
