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

// Menambahkan gedung
void addGedung(graph &G, string gedung) {
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
}

// Mencari gedung
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

// Menampilkan gedung
void showGedung(graph G) {
    adrGedung V = firstVertex(G);
    cout << "Daftar Gedung:\n";
    if (V == NULL) {
        cout << "Tidak ada gedung dalam graf.\n";
    } else {
        int num = 1;
        while (V != NULL) {
            cout << num << ". " << gedung(V) << "\n";
            V = nextVertex(V);
            num++;
        }
    }
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
    adrJalan E = alokasiJalan(toGedung, jarak);
    if (firstEdge(V) == NULL) {
        firstEdge(V) = E;
    } else {
        adrJalan temp = firstEdge(V);
        while (nextEdge(temp) != NULL) {
            temp = nextEdge(temp);
        }
        nextEdge(temp) = E;
    }
}


// Mencari jalan antar gedung
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

// Menampilkan jalan
void showJalan(graph G) {
    adrGedung V = firstVertex(G);
    cout << "Daftar Jalan:\n";
    if (V == NULL) {
        cout << "Tidak ada jalan dalam graf.\n";
    } else {
        int num = 1;
        while (V != NULL) {
            adrJalan E = firstEdge(V);
            while (E != NULL) {
                cout << num << ". " << gedung(V) << " -> " << destGedung(E)
                     << " : " << jarak(E) << "m\n";
                E = nextEdge(E);
                num++;
            }
            V = nextVertex(V);
        }
    }
}


// Melihat tetangga dari suatu gedung
void findTetangga(graph G, string gedung) {
    adrGedung V = findGedung(G, gedung);
    int num = 1;
    if (V == NULL) {
        cout << "Gedung " << gedung << " tidak ditemukan.\n";
    } else {
        adrJalan E = firstEdge(V);
        if (E == NULL) {
            cout << "Gedung " << gedung << " tidak memiliki hubungan dengan gedung lain.\n";
        } else {
            while (E != NULL) {
                cout << num << ". " << destGedung(E) << " : " << jarak(E) << "m\n";
                E = nextEdge(E);
                num++;
            }
        }
    }
}

// Meghapus gedung dan semua rutenya
void delGedung(graph &G, string gedung) {
    // Cari gedung yang akan dihapus
    adrGedung prev = NULL;
    adrGedung curr = firstVertex(G);
    while (curr != NULL && gedung(curr) != gedung) {
        prev = curr;
        curr = nextVertex(curr);
    }

    if (curr == NULL) {
        cout << "Gedung " << gedung << " tidak ditemukan.\n";
    } else {
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
    }
}

// Menghapus jalan antar gedung
void delJalan(graph &G, string fromGedung, string toGedung) {
    // Mencari fromGedung
    adrGedung V = findGedung(G, fromGedung);
    if (V == NULL) {
        cout << "Gedung " << fromGedung << " tidak ditemukan dalam graf.\n";
    } else {
        // Mencari toGedung
        adrGedung W = findGedung(G, toGedung);
        if (W == NULL) {
            cout << "Gedung " << toGedung << " tidak ditemukan dalam graf.\n";
        } else if (fromGedung == toGedung) {
            cout << "Gedung asal dan tujuan tidak boleh sama.\n";
        } else {
            // Mencari jalan menuju toGedung dalam daftar jalan fromGedung
            adrJalan prev = NULL, curr = firstEdge(V);
            while (curr != NULL && destGedung(curr) != toGedung) {
                prev = curr;
                curr = nextEdge(curr);
            }
            if (curr == NULL) {
                cout << "Rute dari " << fromGedung << " -> " << toGedung << " tidak ditemukan.\n";
            } else {
                // Hapus jalan yang ditemukan
                if (prev == NULL) {
                    firstEdge(V) = nextEdge(curr); // Jika jalan pertama dalam daftar
                } else {
                    nextEdge(prev) = nextEdge(curr); // Jika jalan di tengah atau akhir
                }
                delete curr;
                cout << "Rute dari " << fromGedung << " -> " << toGedung << " telah dihapus.\n";
            }
        }
    }
}

// Inisialisasi priority queue
void initPQ(PQ &pq) {
    pq.head = NULL;
}

// Menambahkan elemen baru ke dalam priority queue
void pushPQ(PQ &pq, adrGedung gedung, int priority) {
    adrNode newNode = new node{gedung, priority, NULL};
    if (!pq.head || priority(pq.head) > priority) {
        next(newNode) = pq.head;
        pq.head = newNode;
    } else {
        adrNode curr = pq.head;
        while (next(curr) && priority(next(curr)) <= priority) {
            curr = next(curr);
        }
        next(newNode) = next(curr);
        next(curr) = newNode;
    }
}

// Menghapus elemen dengan prioritas tertinggi
adrGedung popPQ(PQ &pq) {
    if (!pq.head) return NULL;

    adrNode temp = pq.head;
    pq.head = next(pq.head);

    adrGedung topGedung = temp->gedung;
    delete temp;
    return topGedung;
}

bool isEmptyPQ(PQ pq) {
    return pq.head == NULL;
}

// Mencetak rute dari asal ke tujuan
void cetakRute(adrGedung gedung, map<adrGedung, adrGedung> &prev) {
    if (gedung == NULL) {
        return; // Basis rekursi: hentikan jika gedung kosong
    }
    cetakRute(prev[gedung], prev); // Menetak gedung sebelumnya terlebih dahulu
    if (prev[gedung] != NULL) {
        cout << " -> ";
    }
    cout << gedung(gedung); // Menetak gedung saat ini
}

// Mencari ruteTerpendek antarGedung
void ruteTerpendek(graph G, string fromGedung, string toGedung) {
    if (fromGedung == toGedung) {  // Mengecek jika gedung asal dan tujuan sama
        cout << "Gedung asal dan tujuan tidak boleh sama.\n";
        return;
    }

    adrGedung V1 = findGedung(G, fromGedung);
    adrGedung V2 = findGedung(G, toGedung);

    if (!V1 || !V2) {
        if (!V1) cout << "Gedung " << fromGedung << " tidak ditemukan.\n";
        if (!V2) cout << "Gedung " << toGedung << " tidak ditemukan.\n";
        return;
    }

    map<adrGedung, int> dist;
    map<adrGedung, adrGedung> prev;
    PQ pq;
    initPQ(pq);

    // Inisialisasi jarak dan prev
    adrGedung currGedung = firstVertex(G);
    while (currGedung != NULL) {
        dist[currGedung] = INT_MAX; // Set jarak awal ke infinity
        prev[currGedung] = NULL; // Tidak ada gedung sebelumnya
        currGedung = nextVertex(currGedung);
    }

    dist[V1] = 0; // Jarak ke gedung awal adalah 0
    pushPQ(pq, V1, 0);

    // Algoritma Dijkstra
    while (!isEmptyPQ(pq)) {
        adrGedung currGedung = popPQ(pq);
        adrJalan jalan = firstEdge(currGedung);
        while (jalan != NULL) {
            adrGedung tetangga = findGedung(G, destGedung(jalan));
            int newDist = dist[currGedung] + jarak(jalan);

            if (newDist < dist[tetangga]) {
                dist[tetangga] = newDist;      // Update jarak
                prev[tetangga] = currGedung;   // Update gedung sebelumnya
                pushPQ(pq, tetangga, newDist); // Masukkan tetangga ke PQ
            }
            jalan = nextEdge(jalan);
        }
    }

    // Mencetak rute
    if (dist[V2] == INT_MAX) {
        cout << "Tidak ada rute dari " << fromGedung << " ke " << toGedung << ".\n";
    } else {
        cout << "Rute terpendek dari " << fromGedung << " ke " << toGedung << ":\n";
        cetakRute(V2, prev);
        cout << "\nJarak total: " << dist[V2] << "m\n";
    }
}
