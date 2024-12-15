#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <string>
#define info(V) V->info
#define firstVertex(G) G.firstVertex
#define firstEdge(V) V->firstEdge
#define nextVertex(V) V->nextVertex
#define nextEdge(E) E->nextEdge
#define idVertex(V) V->idVertex
#define destVertexID(E) E->destVertexID
#define weight(E) E->weight
using namespace std;

struct infotypeGedung{
    string namaGedung;
};

struct infoTypeJalan{
    int weight; //jaraknya
};

typedef struct elmntGedung *adrGedung;
typedef struct edge *adrJalan;

struct elmntGedung {
    infotypeGedung info; // Informasi gedung
    adrGedung nextVertex;
    adrJalan firstEdge;
};

struct elmntJalan {
    infoTypeJalan info;
    string destVertexID;
    adrJalan nextEdge;
};

struct graph {
    adrGedung firstVertex;
};

// Fungsi dan Prosedur
void initGraph(graph &G); // Inisialisasi graph kosong
adrGedung allocateVertex(infotypeGedung info); // Alokasi memori untuk vertex
adrJalan allocateEdge(string destVertexID, int weight); // Alokasi memori untuk jalan
void addVertex(graph &G, string newVertexID); // Menambahkan vertex baru ke graph
void addEdge(graph &G, string fromVertexID, string toVertexID, int weight); // Menambahkan edge (jalan) ke graph
void buildGraph(graph &G); // Bangun graph dari input pengguna
void cetakNavigasi(graph G); // Cetak seluruh graph
adrGedung findVertex(graph G, string vertexID); // Mencari vertex berdasarkan ID
void cariTetangga(graph G, string vertexID); // Menampilkan tetangga vertex tertentu
void hapus(graph &G); // Menghapus semua vertex dan edge dalam graph
void ruteTerdekat(graph G, string startVertexID, string endVertexID);


#endif // GRAPH_H_INCLUDED
