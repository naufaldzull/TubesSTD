#include <iostream>
#include "graph.h"
using namespace std;

// Fungsi ini untuk membuat sebuah vertex baru dengan ID yang diberikan (newVertexID) dan
// menyimpannya dalam alamat yang ditunjuk oleh v
void createVertex(char newVertexID, adrVertex &v) {
    v = new vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
}

// Fungsi ini untuk menginisialisasi graph G memulai dengan keadaan kosong, tanpa vertex atau edge
void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

// Fungsi ini untuk menambahkan sebuah vertex baru ke dalam graph G dengan ID yang diberikan
// Vertex ini akan menjadi titik awal yang dapat digunakan untuk menambah edge penghubung
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

// Fungsi ini untuk membangun graph G dengan menambahkan vertex-vertex dan edge-edges yang diperlukan,
// sehingga membentuk hubungan antar gedung sesuai dengan sistem navigasi yang dibutuhkan
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
