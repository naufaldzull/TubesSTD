#include <iostream>
#include "graph.h"
using namespace std;

void createVertex(char newVertexID, adrVertex &v) {
    v = new vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
}

void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

void addVertex(graph &G, char newVertexID) {
    adrVertex v, temp;

    createVertex(newVertexID, v);
    if (firstVertex(G) == NULL) {
        firstVertex(G) = v;
    } else {
        temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = v;
    }

}

void buildGraph(graph &G) {
    initGraph(G);

    char vertexID;
    cout << "ID Vertex: ";
    while (cin >> vertexID) {
        if (vertexID >= 'A' && vertexID <= 'Z') {
            addVertex(G, vertexID);
            cout << "ID Vertex: ";
        } else {
            cout << "Program selesai.\n";
            break;
        }
    }
}
