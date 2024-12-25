#include <iostream>
#include "graph.h"
using namespace std;

// Inisialisasi graph
void initGraph(graph &G) {
    firstVertex(G) = NULL;
}

// Alokasi memori untuk gedung
adrGedung alokasiGedung(string gedung) {
    adrGedung V = new elmGedung;
    gedung(V) = gedung;
    nextVertex(V) = NULL;
    firstEdge(V) = NULL;
    return V;
}

// Menambahkan gedung ke graph
void addGedung(graph &G, string gedung) {
    if (findGedung(G, gedung) != NULL) {
        cout << "Gedung " << gedung << " sudah ada.\n";
        return;
    }
    adrGedung V = alokasiGedung(gedung);
    if (firstVertex(G) == NULL) {
        firstVertex(G) = V;
    } else {
        adrGedung temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = V;
    }
    cout << "Gedung " << gedung << " berhasil ditambahkan.\n";
}

// Mencari gedung di graph
adrGedung findGedung(graph G, string gedung) {
    adrGedung V = firstVertex(G);
    while (V != NULL) {
        if (gedung(V) == gedung) {
            return V;
        }
        V = nextVertex(V);
    }
    return NULL;
}

// Alokasi memori untuk jalan
adrJalan alokasiJalan(string destGedung, int jarak) {
    adrJalan E = new elmJalan;
    destGedung(E) = destGedung;
    jarak(E) = jarak;
    nextEdge(E) = NULL;
    return E;
}

// Menambahkan jalan antar gedung
void addJalan(graph &G, string fromGedung, string toGedung, int jarak) {
    adrGedung V = findGedung(G, fromGedung);
    if (V == NULL) {
        cout << "Gedung " << fromGedung << " tidak ditemukan.\n";
        return;
    }
    adrJalan E = findJalan(V, toGedung);
    if (E != NULL) {
        cout << "Jalan " << fromGedung << " -> " << toGedung
         << " : " << jarak << "m sudah ada.\n";
        return;
    }
    E = alokasiJalan(toGedung, jarak);
    if (firstEdge(V) == NULL) {
        firstEdge(V) = E;
    } else {
        adrJalan temp = firstEdge(V);
        while (nextEdge(temp) != NULL) {
            temp = nextEdge(temp);
        }
        nextEdge(temp) = E;
    }
    cout << "Jalan " << fromGedung << " -> " << toGedung
         << " : " << jarak << "m berhasil ditambahkan.\n";
}


// Mencari jalan yang menghubungkan dua gedung
adrJalan findJalan(adrGedung V, string toGedung) {
    adrJalan E = firstEdge(V);
    while (E != NULL) {
        if (destGedung(E) == toGedung) {
            return E;
        }
        E = nextEdge(E);
    }
    return NULL;
}

// Melihat rute
void showRute(graph G) {
    adrGedung V = firstVertex(G);
    while (V != NULL) {
        adrJalan E = firstEdge(V);
        while (E != NULL) {
            cout << gedung(V) << " -> " << destGedung(E) << " : " << jarak(E) << "m\n";
            E = nextEdge(E);
        }
        V = nextVertex(V);
    }
}

// Menemukan tetangga dari suatu gedung
void findTetangga(graph G, string gedung) {
    adrGedung V = findGedung(G, gedung);
    if (V != NULL) {
        adrJalan E = firstEdge(V);
        while (E != nullptr) {
            cout << destGedung(E) << " : " << jarak(E) << "m\n";
            E = nextEdge(E);
        }
    } else {
        cout << "Gedung " << gedung << " tidak ditemukan.\n";
    }
}

void delGedung(graph &G, string gedung) {
    // Cari gedung yang akan dihapus
    adrGedung prev = NULL;
    adrGedung curr = firstVertex(G);
    while (curr != NULL && gedung(curr) != gedung) {
        prev = curr;
        curr = nextVertex(curr);
    }

    if (curr != NULL) {
        // Hapus semua jalan yang berasal dari gedung ini
        adrJalan tempEdge;
        while (firstEdge(curr) != NULL) {
            tempEdge = firstEdge(curr);
            firstEdge(curr) = nextEdge(tempEdge);
            delete tempEdge;
        }

        // Hapus semua jalan yang menuju ke gedung ini
        adrGedung tempVertex = firstVertex(G);
        while (tempVertex != NULL) {
            adrJalan prevEdge = NULL, edge = firstEdge(tempVertex);
            while (edge != NULL) {
                if (destGedung(edge) == gedung) {
                    if (prevEdge == NULL) {
                        firstEdge(tempVertex) = nextEdge(edge);
                    } else {
                        nextEdge(prevEdge) = nextEdge(edge);
                    }
                    delete edge;
                    break;
                }
                prevEdge = edge;
                edge = nextEdge(edge);
            }
            tempVertex = nextVertex(tempVertex);
        }

        // Hapus gedung dari daftar gedung
        if (prev == NULL) {
            firstVertex(G) = nextVertex(curr);
        } else {
            nextVertex(prev) = nextVertex(curr);
        }
        delete curr;
        cout << "Gedung " << gedung << " dan semua rutenya telah dihapus.\n";
    } else {
        cout << "Gedung " << gedung << " tidak ditemukan.\n";
    }
}

void delJalan(graph &G, string fromGedung, string toGedung) {
    // Cari gedung fromGedung
    adrGedung V = findGedung(G, fromGedung);
    if (V != NULL) {
        // Cari jalan yang menuju ke toGedung dalam daftar jalan dari fromGedung
        adrJalan prev = NULL, curr = firstEdge(V);
        while (curr != NULL && destGedung(curr) != toGedung) {
            prev = curr;
            curr = nextEdge(curr);
        }
        if (curr != NULL) {
            // Hapus jalan yang ditemukan
            if (prev == NULL) {
                firstEdge(V) = nextEdge(curr); // Jika jalan pertama dalam daftar
            } else {
                nextEdge(prev) = nextEdge(curr); // Jika jalan di tengah atau akhir
            }
            delete curr;
            cout << "Rute dari " << fromGedung << " -> " << toGedung << " telah dihapus.\n";
        } else {
            cout << "Rute dari " << fromGedung << " -> " << toGedung << " tidak ditemukan.\n";
        }
    } else {
        cout << "Gedung " << fromGedung << " tidak ditemukan.\n";
    }
}
