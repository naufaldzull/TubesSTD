#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
    graph G;
    initGraph(G);

    // Gedung
    addGedung(G, "Manterawu");
    addGedung(G, "TUCH");
    addGedung(G, "BTP");
    addGedung(G, "TULT");
    addGedung(G, "Asrama");
    addGedung(G, "GKU");
    addGedung(G, "Rektorat");
    addGedung(G, "Cacuk");

    // Jalan
    addJalan(G, "Manterawu", "TUCH", 160);
    addJalan(G, "Manterawu", "BTP", 280);
    addJalan(G, "TUCH", "Manterawu", 160);
    addJalan(G, "TUCH", "BTP", 110);
    addJalan(G, "TUCH", "GKU", 160);
    addJalan(G, "BTP", "Manterawu", 280);
    addJalan(G, "BTP", "TUCH", 110);
    addJalan(G, "BTP", "TULT", 400);
    addJalan(G, "TULT", "BTP", 400);
    addJalan(G, "TULT", "Asrama", 550);
    addJalan(G, "Asrama", "TULT", 550);
    addJalan(G, "Asrama", "GKU", 20);
    addJalan(G, "GKU", "TUCH", 160);
    addJalan(G, "GKU", "Asrama", 20);
    addJalan(G, "GKU", "Rektorat", 190);
    addJalan(G, "Rektorat", "GKU", 190);
    addJalan(G, "Rektorat", "Cacuk", 140);
    addJalan(G, "Cacuk", "Rektorat", 140);

    int pilihan;
    string from, to;
    int distance;

    while (true) {
        cout << "==============================\n";
        cout << "              MENU            \n";
        cout << "==============================\n";
        cout << "1. Tambah Gedung\n";
        cout << "2. Tambah Jalan\n";
        cout << "3. Tampil Gedung\n";
        cout << "4. Tampil Jalan\n";
        cout << "5. Lihat Tetangga\n";
        cout << "6. Cari Rute Terdekat\n";
        cout << "7. Hapus Gedung\n";
        cout << "8. Hapus Jalan\n";
        cout << "9. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int jumlahGedung;
                cout << "Input jumlah gedung: ";
                cin >> jumlahGedung;
                for (int i = 1; i <= jumlahGedung; ++i) {
                    string gedung;
                    cout << "Input nama gedung ke-" << i << ": ";
                    cin >> gedung;
                    if (findGedung(G, gedung) == NULL) {
                        addGedung(G, gedung);
                        cout << "Gedung " << gedung << " berhasil ditambahkan." << endl;
                    } else {
                         cout << "Gedung " << gedung << " sudah ada." << endl;
                    }
                }
                break;
            }
            case 2: {
                int jumlahJalan;
                cout << "Input jumlah jalan: ";
                cin >> jumlahJalan;

                for (int i = 0; i < jumlahJalan; i++) {
                    cout << "Jalan ke-" << i + 1 << ":\n";
                    cout << "Input gedung asal: ";
                    cin >> from;
                    cout << "Input gedung tujuan: ";
                    cin >> to;
                    cout << "Input jarak: ";
                    cin >> distance;

                    adrGedung V_from = findGedung(G, from);
                    adrGedung V_to = findGedung(G, to);
                    if (V_from == NULL) {
                        cout << "Gedung " << from << " tidak ditemukan.\n";
                    } else if (V_to == NULL) {
                        cout << "Gedung " << to << " tidak ditemukan.\n";
                    } else {
                        if (findJalan(V_from, to) == NULL) {
                            addJalan(G, from, to, distance);
                            cout << "Jalan " << from << " -> " << to
                                 << " : " << distance << "m berhasil ditambahkan.\n";
                        } else {
                            cout << "Jalan " << from << " -> " << to << " sudah ada.\n";
                        }
                    }
                }
                break;
            }
            case 3:
                showGedung(G);
                break;
            case 4:
                showJalan(G);
                break;
            case 5: {
                cout << "Input gedung yang ingin dilihat tetangganya: ";
                cin >> from;
                findTetangga(G, from);
                break;
            }
            case 6: {
                cout << "Input gedung asal: ";
                cin >> from;
                cout << "Input gedung tujuan: ";
                cin >> to;
                // Implementasi cari rute terdekat bisa menggunakan algoritma graf seperti Dijkstra
                break;
            }
            case 7: {
                cout << "Input gedung yang ingin dihapus: ";
                cin >> from;
                delGedung(G, from);
                break;
            }
            case 8: {
                cout << "Input gedung asal yang ingin dihapus jalannya: ";
                cin >> from;
                cout << "Input gedung tujuan yang ingin dihapus jalannya: ";
                cin >> to;
                delJalan(G, from, to);
                break;
            }
            case 9:
                cout << "Program Selesai.";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
