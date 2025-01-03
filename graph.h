#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <string>
#include <map>
#include <climits>
#define firstVertex(G) G.firstVertex
#define firstEdge(V) V->firstEdge
#define nextVertex(V) V->nextVertex
#define nextEdge(E) E->nextEdge
#define gedung(V) V->gedung
#define destGedung(E) E->destGedung
#define jarak(E) E->jarak
#define priority(N) N->priority
#define next(N) N->next
using namespace std;

typedef struct elmGedung *adrGedung;
typedef struct elmJalan *adrJalan;
struct elmGedung {
    string gedung;
    adrGedung nextVertex;
    adrJalan firstEdge;
};
struct elmJalan {
    int jarak;
    string destGedung;
    adrJalan nextEdge;
};
struct graph {
    adrGedung firstVertex;
};

typedef struct node *adrNode;
struct node {
    adrGedung gedung;
    int priority;
    adrNode next;
};
struct PQ {
    adrNode head;
};

void initGraph(graph &G);
adrGedung alokasiGedung(string gedung);
void addGedung(graph &G, string gedung);
adrGedung findGedung(graph G, string gedung);
void showGedung(graph G);
adrJalan alokasiJalan(string destGedung, int jarak);
void addJalan(graph &G, string fromGedung, string toGedung, int jarak);
adrJalan findJalan(adrGedung V, string toGedung);
void showJalan(graph G);
void findTetangga(graph G, string gedung);
void delGedung(graph &G, string gedung);
void delJalan(graph &G, string fromGedung, string toGedung);

void initPQ(PQ &pq);
void pushPQ(PQ &pq, adrGedung gedung, int priority);
adrGedung popPQ(PQ &pq);
bool isEmptyPQ(PQ pq);
void cetakRute(adrGedung gedung, map<adrGedung, adrGedung> &prev);
void ruteTerpendek(graph G, string fromGedung, string toGedung);

#endif // GRAPH_H_INCLUDED
