#include <iostream>
#include "graph.h"
using namespace std;

int main() {
    graph G;
    initGraph(G);
    int pilihan;

    do {
        cout << "\nMENU" << endl;
        cout << "1. Tambah gedung" << endl;
        cout << "2. Tambah jarak" << endl;
        cout << "3. Print graf" << endl;
        cout << "4. Cari tetangga" << endl;
        cout << "5. Cari rute terdekat" << endl;
        cout << "6. Hapus Gedung" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int jumlahGedung;
                cout << "Berapa gedung: ";
                cin >> jumlahGedung;

                for (int i = 0; i < jumlahGedung; i++) {
                    string gedung;
                    cout << "Nama gedung: ";
                    cin >> gedung;

                    if (findGedung(G, gedung) == NULL) {
                        addGedung(G, gedung);
                        cout << "Gedung dengan nama " << gedung << " berhasil ditambahkan." << endl;
                    } else {
                        cout << "Gedung dengan nama " << gedung << " sudah ada." << endl;
                    }
                }
                break;
            }
            case 2: {
                string dari, ke;
                int jarak;
                cout << "Dari: ";
                cin >> dari;
                cout << "Ke: ";
                cin >> ke;
                cout << "Jarak (meter): ";
                cin >> jarak;
                addJalan(G, dari, ke, jarak);
                break;
            }
            case 3: {
                printNavigasi(G);
                break;
            }
            case 4: {
                string gedung;
                cout << "Cari tetangga dari gedung: ";
                cin >> gedung;
                findTetangga(G, gedung);
                break;
            }
            case 5: {
                //string start, endJ;
                //cout << "Dari: ";
                //cin >> start;
                //cout << "Ke: ";
                //cin >> end;
                //ruteTerdekat(G, start, endJ);
                break;
            }
            case 6: {
                  string gedung;
                  cout << "Nama gedung: ";
                  cin >> gedung;

                  adrGedung building = findGedung(G, gedung);
                  if (building != NULL) {
                    // Hapus semua rute yang menuju gedung ini
                    adrGedung tempGedung = firstVertex(G);
                    while (tempGedung != NULL) {
                        delJalan(G, gedung(tempGedung), gedung); // Menghapus rute ke gedung
                        tempGedung = nextVertex(tempGedung);
                    }
                    // Hapus gedung dari graf
                    delGedung(G, gedung);
                } else {
                    cout << "Gedung tidak ditemukan." << endl;
                }
                break;
            }
            case 7: {
                cout << "Keluar dari program." << endl;
                break;
            }
            default: {
                cout << "Pilihan tidak valid." << endl;
                break;
            }
        }
    } while (pilihan != 7);

    return 0;
}

