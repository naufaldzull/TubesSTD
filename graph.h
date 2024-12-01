#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <string>
#define firstVertex(G) G.firstVertex
#define firstEdge(V) V->firstEdge
#define nextVertex(V) V->nextVertex
#define nextEdge(E) E->nextEdge
#define idVertex(V) V->idVertex
#define destVertexID(E) E->destVertexID
#define weight(E) E->weight
using namespace std;
typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;
struct vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};
struct edge {
    char destVertexID;
    int weight;
    adrEdge nextEdge;
};
struct graph {
    adrVertex firstVertex;
};

void createVertex(char newVertexID, adrVertex &v);
void initGraph(graph &G);
void addVertex(graph &G, char newVertexID);
// void addEdge(Graph &G, char fromVertexID, char toVertexID, int weight);
void buildGraph(graph &G);

#endif // GRAPH_H_INCLUDED
