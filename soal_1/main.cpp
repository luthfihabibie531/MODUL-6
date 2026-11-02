//main.cpp (UNGUIDED) soal_1
#include "Buku.h"

void tampilSetelahHapus(List L) {
    address P = L.Last;
    while (P != Nil) {
        cout << "Kode Buku    : " << P->info.kodeBuku << endl;
        cout << "Judul        : " << P->info.judul << endl;
        cout << "Tahun Terbit : " << P->info.thnTerbit << endl;
        P = P->prev;
    }
}

int main() {
    List L;
    CreateList(L);

    // Soal 1: insert data dan cek duplikasi
    const int JUMLAH_INPUT = 4;
    for (int i = 0; i < JUMLAH_INPUT; i++) {
        infotype x;
        cout << "masukkan kode buku: ";
        cin >> x.kodeBuku;
        cout << "masukkan judul buku: ";
        cin >> x.judul;
        cout << "masukkan tahun terbit: ";
        cin >> x.thnTerbit;

        if (findElm(L, x) != Nil) {
            cout << "kode buku sudah terdaftar" << endl;
        } else {
            insertLast(L, alokasi(x));
        }
        cout << endl;
    }

    cout << "DATA LIST 1" << endl;
    printInfo(L);
    cout << endl;

    // Soal 2: searching
    infotype cari;
    cout << "Masukkan Kode Buku yang dicari : ";
    cin >> cari.kodeBuku;
    address hasil = findElm(L, cari);
    if (hasil != Nil) {
        cout << "Kode Buku    : " << hasil->info.kodeBuku << endl;
        cout << "Judul        : " << hasil->info.judul << endl;
        cout << "Tahun Terbit : " << hasil->info.thnTerbit << endl;
    } else {
        cout << "Data dengan kode buku " << cari.kodeBuku
             << " tidak ditemukan." << endl;
    }
    cout << endl;

    // Soal 3: delete
    infotype hapus;
    cout << "Masukkan Kode Buku yang akan dihapus : ";
    cin >> hapus.kodeBuku;
    address target = findElm(L, hapus);
    address P = Nil;

    if (target == Nil) {
        cout << "Data dengan kode buku " << hapus.kodeBuku
             << " tidak ditemukan." << endl;
    } else {
        if (target == L.First) {
            deleteFirst(L, P);
        } else if (target == L.Last) {
            deleteLast(L, P);
        } else {
            deleteAfter(target->prev, P);
        }
        dealokasi(P);
        cout << "Data dengan kode buku " << hapus.kodeBuku
             << " berhasil dihapus." << endl;
    }

    cout << endl << "DATA LIST 1" << endl;
    tampilSetelahHapus(L);
    return 0;
}