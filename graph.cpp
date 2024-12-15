#include <iostream>
#include "graph.h"
using namespace std;

// Fungsi ini untuk membuat sebuah vertex baru dengan ID yang diberikan (newVertexID) dan
// menyimpannya dalam alamat yang ditunjuk oleh v
adrGedung allocateVertex(infotypeGedung info) {
    adrGedung newVertex = new elmntGedung;
    info(newVertex) = info;       // Set informasi gedung
    nextVertex(newVertex) = NULL; // Awalnya tidak ada nextVertex
    firstEdge(newVertex) = NULL;  // Awalnya tidak ada edge
    return newVertex;
}

adrJalan allocateEdge(string destVertexID, int weight) {
    adrJalan newEdge = new elmntJalan;
    weight(newEdge) = weight;  // Set jarak/jalan
    destVertexID(newEdge) = destVertexID; // Set tujuan edge
    nextEdge(newEdge) = NULL;  // Awalnya tidak ada nextEdge
    return newEdge;
}

// Fungsi ini untuk menginisialisasi graph G memulai dengan keadaan kosong, tanpa vertex atau edge
void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

// Fungsi ini untuk menambahkan sebuah vertex baru ke dalam graph G dengan ID yang diberikan
// Vertex ini akan menjadi titik awal yang dapat digunakan untuk menambah edge penghubung
void addVertex(graph &G, string newVertexID) {
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

void addEdge(graph &G, string fromVertexID, string toVertexID, int weight) {
    adrGedung fromVertex = findVertex(G, fromVertexID);
    adrGedung toVertex = findVertex(G, toVertexID);

    if (fromVertex == nullptr || toVertex == nullptr) {
        cout << "Salah satu atau kedua vertex tidak ditemukan." << endl;
        return;
    }

    adrJalan newEdge = allocateEdge(toVertexID, weight);

    if (firstEdge(fromVertex) == nullptr) {
        firstEdge(fromVertex) = newEdge;
    } else {
        adrJalan currentEdge = firstEdge(fromVertex);
        while (nextEdge(currentEdge) != nullptr) {
            currentEdge = nextEdge(currentEdge);
        }
        nextEdge(currentEdge) = newEdge;
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





void cetakNavigasi(graph G) {
    if (firstVertex(G) == NULL) {
        cout << "Graph kosong." << endl;
        return;
    }

    adrGedung currentVertex = firstVertex(G);

    while (currentVertex != NULL) {
        cout << "Vertex: " << idVertex(currentVertex) << " (" << info(currentVertex).namaGedung << ")" << endl;

        adrJalan currentEdge = firstEdge(currentVertex);
        if (currentEdge == NULL) {
            cout << "  Tidak ada edge." << endl;
        } else {
            cout << "  Edges: " << endl;
            while (currentEdge != NULL) {
                cout << "    -> " << destVertexID(currentEdge)
                     << " (Weight: " << weight(currentEdge) << ")" << endl;
                currentEdge = nextEdge(currentEdge);
            }
        }

        currentVertex = nextVertex(currentVertex);
    }
}


