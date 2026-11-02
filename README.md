# <h1 align="center">Laporan Praktikum Modul 6 - Doubly Linked List (Bagian Pertama)</h1>
<p align="center">AHMAD LUTHFI HABIBIE - 109082500190</p>

## Dasar Teori

### A. Konsep Doubly Linked List<br/>
*Doubly Linked List* adalah *linked list* yang setiap elemennya memiliki dua *successor*, yaitu pointer `prev` yang menunjuk ke elemen sebelumnya dan pointer `next` yang menunjuk ke elemen sesudahnya [1]. Dengan dua pointer ini, list bisa ditelusuri ke dua arah, baik maju maupun mundur, berbeda dengan *singly linked list* yang hanya bisa maju satu arah [1][2]. Selain pointer pada elemen, list juga memiliki dua pointer utama, yaitu `first` yang menunjuk elemen pertama dan `last` yang menunjuk elemen terakhir [1]. List dinyatakan kosong apabila `first` bernilai `Nil`. Karena `last` ikut disimpan, penambahan di akhir list tidak perlu lagi menelusuri seluruh elemen dari depan seperti pada singly linked list.

#### 1. Komponen dan Struktur Data
Komponen pada *doubly linked list* terdiri dari `first` dan `last` pada level list, serta `next` dan `prev` pada level elemen [1]. Pada modul, elemen dideklarasikan dengan `struct elmlist` yang berisi `info`, `next`, dan `prev`, sedangkan list dideklarasikan dengan `struct list` yang berisi `first` dan `last`. Ujung-ujung list ditandai dengan `Nil`: `prev` elemen pertama bernilai `Nil` dan `next` elemen terakhir juga bernilai `Nil` [1]. Seperti halnya singly linked list, elemen dialokasikan secara dinamis sehingga memori baru diminta ke sistem hanya ketika elemen itu dibutuhkan [3].

### B. Operasi pada Doubly Linked List<br/>

#### 1. Insert
Pada *insert first*, elemen baru `P` dibuat lebih dulu dengan `next` dan `prev` bernilai `Nil`, lalu `P->next` diarahkan ke `L.first`, `(L.first)->prev` diarahkan ke `P`, dan terakhir `L.first` dipindah ke `P` [1]. Pada *insert last*, langkahnya dibalik: `P->prev` diarahkan ke `L.last`, `(L.last)->next` diarahkan ke `P`, lalu `L.last` dipindah ke `P` [1]. Pada *insert after*, dengan `R` sebagai elemen acuan, `P->next = R->next` dan `P->prev = R` dilakukan lebih dulu, kemudian `(R->next)->prev = P` dan `R->next = P` [1]. Urutan ini penting supaya sambungan ke elemen sesudah `R` tidak hilang sebelum sempat disambungkan ke `P`. *Insert before* pada dasarnya kebalikan dari *insert after*, dan perbedaannya hanya terletak pada pencarian elemen acuannya [1]. Satu hal yang perlu diperhatikan, contoh kode `insertFirst` pada modul langsung mengakses `(L.first)->prev`, sehingga untuk list yang masih kosong perlu penanganan khusus agar tidak mengakses pointer `Nil`.

#### 2. Delete
Pada *delete first*, `P` diarahkan ke `L.first`, `L.first` digeser ke `(L.first)->next`, lalu `(L.first)->prev` dan `P->next` diputus menjadi `Nil` [1]. Pada *delete last*, `P` diarahkan ke `L.last`, `L.last` digeser mundur ke `(L.last)->prev`, lalu `(L.last)->next` dan `P->prev` diputus menjadi `Nil` [1]. Pada *delete after*, dengan `R` sebagai elemen acuan dan `P` sebagai elemen yang dihapus, `R->next` diarahkan ke `P->next` dan `(P->next)->prev` diarahkan kembali ke `R`, kemudian `P` diputus dari kedua pointernya [1]. Setelah diputus, elemen dapat dikembalikan ke pemanggil (`return P`) atau langsung didealokasi dengan `dealokasi(P)` agar tidak terjadi kebocoran memori [1][3]. Sama seperti *insert*, *delete before* merupakan kebalikan dari *delete after* [1].

#### 3. Update, View, dan Searching
Proses pencarian, *update*, dan *view* pada *doubly linked list* pada dasarnya sama dengan pada *singly linked list*. Bedanya, akses elemen menjadi lebih mudah karena iterasi bisa dilakukan maju maupun mundur [1]. Penelusuran maju dimulai dari `first` lewat `next`, sedangkan penelusuran mundur dimulai dari `last` lewat `prev`. ADT yang dipakai juga pada dasarnya sama dengan ADT *singly linked list* [1].

### C. Perbandingan dengan Singly Linked List<br/>
Keunggulan *doubly linked list* adalah elemen sebelumnya bisa langsung diakses lewat `prev`, sehingga operasi seperti *delete last* tidak perlu menelusuri list dengan pointer bantu yang tertinggal satu langkah [2]. Harga yang dibayar adalah memori yang lebih besar karena setiap elemen menyimpan satu pointer tambahan, dan setiap operasi *insert* maupun *delete* harus memperbarui lebih banyak pointer [1][2]. Kesalahan urutan penyambungan pointer pada *doubly linked list* lebih mudah membuat list terputus, sehingga langkah-langkah pada modul perlu diikuti dengan urut [1].

## Guided 

### 1. Doublylist.h

```C++
//Doublylist.h (GUIDED)
#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>

#define Nil NULL

// Latihan 1
struct infotype {
    std::string nopol; 
    std::string warna; 
    int thnBuat;      
};
typedef struct elmlist *address;
struct elmlist {
    infotype info;  
    address next;   
    address prev;   
};
struct List {
    address First; 
    address Last;  
};


// Latihan 1
void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertLast(List &L, address P);

// Latihan 2

address findElm(List L, std::string nopol);

// Latihan 3
void deleteFirst(List &L, address &P);
void deleteLast(List &L, address &P);
void deleteAfter(List &L, address Prec, address &P);
void deleteElm(List &L, std::string nopol, bool &status);

#endif
```
File `Doublylist.h` berisi spesifikasi tipe data dan prototipe primitif untuk list kendaraan. `infotype` berupa `struct` yang menyimpan `nopol`, `warna`, dan `thnBuat`. `address` didefinisikan sebagai pointer ke `struct elmlist`, dan `struct elmlist` berisi `info` serta dua pointer, yaitu `next` dan `prev`. `struct List` memiliki dua field, `First` dan `Last`, yang menunjuk elemen paling depan dan paling belakang. Prototipe dikelompokkan sesuai latihan di modul: primitif dasar (`CreateList`, `alokasi`, `dealokasi`, `printInfo`, `insertLast`) untuk latihan 1, `findElm` untuk latihan 2, serta `deleteFirst`, `deleteLast`, `deleteAfter`, dan `deleteElm` untuk latihan 3. Fungsi `deleteElm` adalah tambahan yang membungkus pencarian dan penghapusan sekaligus, dengan parameter `status` sebagai penanda berhasil atau tidaknya penghapusan. Baris `#ifndef`, `#define`, dan `#endif` berfungsi sebagai *header guard*.

### 2. Doublylist.cpp

```C++
//Doublylist.cpp (GUIDED)
#include "Doublylist.h"

// Latihan 1
void CreateList(List &L) {
    L.First = Nil;
    L.Last = Nil;
}

address alokasi(infotype x) {
    address P = new elmlist;
    P->info = x;
    P->next = Nil;
    P->prev = Nil; 
    return P;
}

void dealokasi(address &P) {
    delete P;
}

void printInfo(List L) {
    address P = L.Last;
    if (P == Nil) {
        std::cout << "List kosong." << std::endl;
        return;
    }
    while (P != Nil) {
        std::cout << "no polisi : " << P->info.nopol << std::endl;   
        std::cout << "warna     : " << P->info.warna << std::endl;   
        std::cout << "tahun     : " << P->info.thnBuat << std::endl; 
        P = P->prev;
    }
}

void insertLast(List &L, address P) {
    if (L.First == Nil) { 
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;         
        (L.Last)->next = P;     
        L.Last = P;               
    }
}

// Latihan 2
address findElm(List L, std::string nopol) {
    address P = L.First;
    while (P != Nil) {
        if (P->info.nopol == nopol) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

// Latihan 3
void deleteFirst(List &L, address &P) {
    if (L.First == Nil) return;

    P = L.First; 
    if (L.First == L.Last) { 
        L.First = Nil;
        L.Last = Nil;
    } else {
        L.First = P->next;     
        (L.First)->prev = Nil; 
        P->next = Nil;         
    }
}

void deleteLast(List &L, address &P) {
    if (L.First == Nil) return;

    P = L.Last; 
    if (L.First == L.Last) { 
        L.First = Nil;
        L.Last = Nil;
    } else {
        L.Last = P->prev;      
        (L.Last)->next = Nil; 
        P->prev = Nil;         
    }
}

void deleteAfter(List &L, address Prec, address &P) {
    if (Prec == Nil || Prec->next == Nil) return;

    P = Prec->next;
    if (P == L.Last) {
        deleteLast(L, P);
    } else {
        Prec->next = P->next;     
        (P->next)->prev = Prec; 
        P->next = Nil;            
        P->prev = Nil;           
    }
}

void deleteElm(List &L, std::string nopol, bool &status) {
    address P = findElm(L, nopol);
    status = false;

    if (P != Nil) {
        if (P == L.First) {
            deleteFirst(L, P);
        } else if (P == L.Last) {
            deleteLast(L, P);
        } else {
            address Prec = P->prev;
            deleteAfter(L, Prec, P);
        }
        dealokasi(P); 
        status = true;
    }
}
```
File `Doublylist.cpp` berisi realisasi semua primitif yang dideklarasikan di header. `CreateList` mengisi `First` dan `Last` dengan `Nil`, sedangkan `alokasi` membuat elemen baru dengan `new`, menyalin data ke `info`, lalu mengatur `next` dan `prev` ke `Nil`. `dealokasi` mengembalikan memori dengan `delete`. `printInfo` menelusuri list **mundur**, mulai dari `Last` lalu bergerak lewat `prev`, sehingga data yang dimasukkan paling akhir tampil paling atas. Ini memperlihatkan keunggulan *doubly linked list* yang bisa ditelusuri dari belakang [1].

`insertLast` menangani dua kasus. Kalau list kosong, elemen baru langsung menjadi `First` sekaligus `Last`. Kalau tidak kosong, langkahnya mengikuti modul: `P->prev = L.Last`, lalu `(L.Last)->next = P`, dan terakhir `L.Last = P` [1]. `findElm` menelusuri list maju dari `First` sambil membandingkan `nopol` tiap elemen, dan mengembalikan alamat elemen yang cocok atau `Nil` jika tidak ada.

Untuk operasi hapus, `deleteFirst` dan `deleteLast` sama-sama membedakan kasus list yang hanya berisi satu elemen, di mana `First` dan `Last` dikembalikan menjadi `Nil`. Kalau elemennya lebih dari satu, `deleteFirst` menggeser `First` ke `next` lalu memutus `prev` elemen baru tersebut, sedangkan `deleteLast` menggeser `Last` ke `prev` lalu memutus `next` elemen baru tersebut. `deleteAfter` menghapus elemen setelah `Prec`. Kalau elemen itu ternyata `Last`, penghapusan dilimpahkan ke `deleteLast`. Selain itu, `Prec->next` diarahkan ke `P->next` dan `(P->next)->prev` diarahkan ke `Prec`, persis seperti langkah *delete after* pada modul [1]. `deleteElm` menggabungkan semuanya: elemen dicari dengan `findElm`, lalu dipilih `deleteFirst`, `deleteLast`, atau `deleteAfter` (dengan `Prec = P->prev`) sesuai posisinya, kemudian elemen didealokasi dan `status` diisi `true`.

### 3. main.cpp

```C++
//main.cpp (GUIDED)
#include <iostream>
#include "Doublylist.h"
using namespace std;

void inputData(List &L) {
    infotype data;
    address P;

    cout << "masukkan nomor polisi: "; cin >> data.nopol;
    cout << "masukkan warna kendaraan: "; cin >> data.warna;
    cout << "masukkan tahun kendaraan: "; cin >> data.thnBuat;
    if (findElm(L, data.nopol) == Nil) {
        P = alokasi(data); 
        insertLast(L, P);  
    } else {
        cout << "nomor polisi sudah terdaftar" << endl; 
    }
}

int main() {
    List L;
    CreateList(L); 
    address P;

    // Latihan 1
    inputData(L); 
    inputData(L); 
    inputData(L); 
    inputData(L); 

    cout << "\nDATA LIST 1" << endl; 
    printInfo(L); 

    // Latihan 2
    string nopolCari;
    cout << "\nMasukkan Nomor Polisi yang dicari : "; 
    cin >> nopolCari; 
    
    P = findElm(L, nopolCari); 
    if (P != Nil) {
        cout << "Nomor Polisi : " << P->info.nopol << endl; 
        cout << "Warna        : " << P->info.warna << endl; 
        cout << "Tahun        : " << P->info.thnBuat << endl; 
    } else {
        cout << "Data dengan nomor polisi " << nopolCari << " tidak ditemukan." << endl;
    }

    // Latihan 3
    string nopolHapus;
    bool hapusBerhasil;
    cout << "\nMasukkan Nomor Polisi yang akan dihapus : ";
    cin >> nopolHapus;

    deleteElm(L, nopolHapus, hapusBerhasil); 

    if (hapusBerhasil) {
        cout << "Data dengan nomor polisi " << nopolHapus << " berhasil dihapus." << endl; 
    } else {
        cout << "Data dengan nomor polisi " << nopolHapus << " tidak ditemukan." << endl;
    }
    cout << "\nDATA LIST 1" << endl; 
    printInfo(L); 

    return 0;
}
```
File `main.cpp` berperan sebagai *driver* untuk tiga latihan pada modul. Fungsi `inputData` membaca nomor polisi, warna, dan tahun dari keyboard, lalu memeriksa duplikasi dengan `findElm`. Kalau nomor polisi belum ada, data dialokasikan dan dimasukkan lewat `insertLast`; kalau sudah ada, ditampilkan pesan "nomor polisi sudah terdaftar" dan data tidak dimasukkan. Fungsi ini dipanggil empat kali pada `main`. Dengan input D001, D003, D001 (duplikat), dan D004, list akhirnya berisi tiga elemen berurutan D001, D003, D004 dari `First` ke `Last`. Karena `printInfo` menelusuri dari `Last`, tampilan "DATA LIST 1" berurutan D004, D003, D001, sesuai contoh output pada modul.

Pada latihan 2, pengguna memasukkan nomor polisi yang dicari, lalu `findElm` dipanggil. Jika hasilnya bukan `Nil`, nomor polisi, warna, dan tahun elemen tersebut dicetak, dan jika `Nil` dicetak pesan bahwa data tidak ditemukan. Pada latihan 3, pengguna memasukkan nomor polisi yang akan dihapus (D003) lalu `deleteElm` dipanggil. Karena D003 berada di tengah list, penghapusan dilakukan lewat `deleteAfter` dengan elemen sebelumnya (D001) sebagai `Prec`. Setelah berhasil, pesan konfirmasi dicetak dan list ditampilkan ulang dengan isi D004 lalu D001.

## Unguided 

### 1. ADT Doubly Linked List pada "Buku.h", implementasi pada "Buku.cpp", dan percobaan pada "main.cpp" meliputi insert dengan pengecekan duplikasi kodeBuku, pencarian kode buku B001, dan penghapusan kode buku B003

**Buku.h**
```C++
//Buku.h (UNGUIDED) soal_1
/* file : Buku.h */
/* ADT Doubly Linked List dengan representasi fisik pointer */
#ifndef BUKU_H
#define BUKU_H

#include <iostream>
#include <string>
using namespace std;

#define Nil NULL

struct buku {
    string kodeBuku;
    string judul;
    int thnTerbit;
};
typedef buku infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address First;
    address Last;
};

// Primitif dasar
void CreateList(List &L);
address alokasi(infotype x);
void dealokasi(address &P);
void printInfo(List L);
void insertLast(List &L, address P);

// Pencarian
address findElm(List L, infotype x);

// Penghapusan
void deleteFirst(List &L, address &P);
void deleteLast(List &L, address &P);
void deleteAfter(address Prec, address &P);

#endif
```

**Buku.cpp**
```C++
//Buku.cpp (UNGUIDED) soal_1
#include "Buku.h"

void CreateList(List &L) {
    L.First = Nil;
    L.Last = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = Nil;
    P->prev = Nil;
    return P;
}

void dealokasi(address &P) {
    delete P;
    P = Nil;
}

void printInfo(List L) {
    address P = L.Last;
    while (P != Nil) {
        cout << "kode buku : " << P->info.kodeBuku << endl;
        cout << "judul     : " << P->info.judul << endl;
        cout << "tahun     : " << P->info.thnTerbit << endl;
        P = P->prev;
    }
}

void insertLast(List &L, address P) {
    if (L.First == Nil) {
        L.First = P;
        L.Last = P;
    } else {
        P->prev = L.Last;
        (L.Last)->next = P;
        L.Last = P;
    }
}

address findElm(List L, infotype x) {
    address P = L.First;
    while (P != Nil) {
        if (P->info.kodeBuku == x.kodeBuku) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

void deleteFirst(List &L, address &P) {
    if (L.First == Nil) {
        P = Nil;
    } else if (L.First == L.Last) {
        P = L.First;
        L.First = Nil;
        L.Last = Nil;
    } else {
        P = L.First;
        L.First = (L.First)->next;
        P->next = Nil;
        (L.First)->prev = Nil;
    }
}

void deleteLast(List &L, address &P) {
    if (L.First == Nil) {
        P = Nil;
    } else if (L.First == L.Last) {
        P = L.Last;
        L.First = Nil;
        L.Last = Nil;
    } else {
        P = L.Last;
        L.Last = (L.Last)->prev;
        P->prev = Nil;
        (L.Last)->next = Nil;
    }
}

void deleteAfter(address Prec, address &P) {
    if (Prec == Nil || Prec->next == Nil) {
        P = Nil;
    } else {
        P = Prec->next;
        Prec->next = P->next;
        if (P->next != Nil) {
            (P->next)->prev = Prec;
        }
        P->prev = Nil;
        P->next = Nil;
    }
}
```

**main.cpp**
```C++
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
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](soal_1(1).png)

##### Output 2
![Screenshot Output Unguided 1_2](soal_1(2).png)


Program ini mengerjakan tiga soal latihan modul 6 sekaligus dengan satu ADT *Doubly Linked List* untuk data buku. Pada `Buku.h`, `struct buku` menyimpan `kodeBuku`, `judul`, dan `thnTerbit`, lalu diberi alias `infotype`. `address` adalah pointer ke `ElmList`, dan `ElmList` berisi `info`, `next`, serta `prev`. `struct List` memiliki `First` dan `Last` sesuai definisi pada modul [1]. Prototipe yang dideklarasikan adalah lima primitif dasar dari soal 1 (`CreateList`, `alokasi`, `dealokasi`, `printInfo`, `insertLast`), fungsi `findElm` untuk soal 2, serta tiga prosedur hapus (`deleteFirst`, `deleteLast`, `deleteAfter`) untuk soal 3. Sesuai spesifikasi soal, `deleteAfter` hanya menerima `Prec` dan `P` tanpa parameter list, karena elemen yang dihapus selalu berada di tengah list sehingga `First` dan `Last` tidak berubah.

Di `Buku.cpp`, `CreateList` mengisi `First` dan `Last` dengan `Nil`, `alokasi` membuat elemen baru dengan `new` dan mengatur `next` serta `prev` ke `Nil`, dan `dealokasi` menghapus elemen lalu mengembalikan pointer ke `Nil`. `printInfo` menelusuri list mundur dari `Last` lewat `prev`, sehingga data yang terakhir dimasukkan tampil paling atas. `insertLast` mengikuti langkah modul, yaitu `P->prev = L.Last`, `(L.Last)->next = P`, lalu `L.Last = P`, dengan penanganan khusus saat list masih kosong [1]. Fungsi `findElm` menerima `infotype` sebagai parameter dan mencocokkan `kodeBuku` setiap elemen sambil menelusuri list maju dari `First`. Alamat elemen dikembalikan begitu cocok, dan `Nil` dikembalikan kalau sampai akhir belum ketemu. Karena pencocokan hanya memakai `kodeBuku`, fungsi yang sama dipakai untuk mengecek duplikasi pada soal 1, pencarian pada soal 2, dan menemukan elemen yang akan dihapus pada soal 3.

Prosedur hapus pada `Buku.cpp` mengikuti langkah-langkah di modul [1]. `deleteFirst` dan `deleteLast` membedakan tiga kondisi, yaitu list kosong (`P` diisi `Nil`), list berisi satu elemen (`First` dan `Last` dikembalikan menjadi `Nil`), dan list berisi lebih dari satu elemen (`First` atau `Last` digeser lalu pointer yang menghubungkan ke elemen yang dihapus diputus). `deleteAfter` mengambil `P = Prec->next`, menyambungkan `Prec->next` ke `P->next`, lalu mengarahkan `(P->next)->prev` kembali ke `Prec` bila elemen sesudahnya ada, kemudian memutus `prev` dan `next` milik `P`.

Pada `main.cpp`, bagian soal 1 membaca empat kali input kode buku, judul, dan tahun terbit lewat perulangan. Sebelum dimasukkan, `findElm` dipakai untuk mengecek duplikasi. Kalau kode sudah ada, dicetak "kode buku sudah terdaftar" dan data diabaikan, kalau belum ada, data dialokasikan dan dimasukkan lewat `insertLast`. Dengan input B001, B003, B001 (duplikat), dan B004, list berisi B001, B003, B004 dari `First` ke `Last`, sehingga `printInfo` menampilkannya berurutan B004, B003, B001. Judul dibaca dengan `cin >>` sehingga penulisannya memakai garis bawah, misalnya `Struktur_Data`, seperti pada contoh output soal. Pada soal 2, kode yang dicari (B001) dicari dengan `findElm` dan, jika ketemu, kode buku, judul, dan tahun terbit dicetak. Pada soal 3, kode B003 dicari lebih dulu, lalu cabang `if` memilih `deleteFirst` bila elemen berada di `First`, `deleteLast` bila di `Last`, dan `deleteAfter(target->prev, P)` bila di tengah. Karena B003 berada di tengah, `deleteAfter` yang dipakai. Elemen hasil hapus kemudian didealokasi dan pesan keberhasilan dicetak. Fungsi `tampilSetelahHapus` menampilkan sisa list dengan format label seperti pada contoh output soal, yaitu B004 lalu B001.

Pada screenshot, program dikompilasi di terminal dengan `g++ .\Buku.cpp .\main.cpp -o Buku.exe` lalu dijalankan dengan `.\Buku.exe`. Output yang muncul sesuai contoh soal: daftar buku setelah *insert* menampilkan B004, B003, dan B001 (data duplikat B001 yang kedua ditolak), pencarian B001 menampilkan buku "Algoritma" tahun 2020, dan setelah B003 dihapus, list tersisa B004 "Jaringan_Komputer" tahun 2022 dan B001 "Algoritma" tahun 2020.

## Kesimpulan
Dari praktikum Modul 6 dapat disimpulkan bahwa *doubly linked list* adalah pengembangan dari *singly linked list* yang setiap elemennya memiliki pointer `next` dan `prev`, serta list yang menyimpan `first` dan `last`, sehingga elemen bisa ditelusuri dua arah dan penambahan di akhir list bisa dilakukan langsung lewat `last`. Pada bagian guided, ADT diterapkan untuk data kendaraan lengkap dengan *insert last*, pencarian berdasarkan nomor polisi, dan penghapusan elemen di awal, di akhir, maupun setelah elemen tertentu, di mana setiap operasi harus memperbarui pointer `next` dan `prev` secara berurutan agar list tidak terputus. Pada bagian unguided, ADT *Doubly Linked List* untuk data buku berhasil dibuat dengan pengecekan duplikasi `kodeBuku` sebelum *insert*, fungsi `findElm` untuk mencari kode B001, serta prosedur `deleteFirst`, `deleteLast`, dan `deleteAfter` untuk menghapus kode B003, dengan hasil sesuai contoh output pada soal.

## Referensi
[1] Laboratorium Informatika, Fakultas Informatika, Telkom University. (t.t.). "Modul 6: Doubly Linked List (Bagian Pertama)", Modul Praktikum Struktur Data. Bandung: Telkom University.
<br>[2] Wijoyo, A., Prayudi, L. A., Fiqih, M., Santoso, R. D., Putra, R. T. S., Arifin, T., & Farhan, A. "Penggunaan Algoritma Doubly Linked List Untuk Insertion Dan Deletion". JRIIN: Jurnal Riset Informatika dan Inovasi, 1(12), 1329–1331. Universitas Pamulang. Diakses melalui https://jurnalmahasiswa.com/index.php/jriin/article/view/1282.
<br>[3] Shaffer, C. A. "Data Structures and Algorithm Analysis" (Bab 4: Lists, Stacks, and Queues). Virginia Tech. Diakses melalui https://learn.saylor.org/pluginfile.php/591887/mod_resource/content/1/Shaffer-103-120.pdf.
<br>[4] Universitas Esa Unggul. "Struktur Data Pertemuan 4: Konsep Pointer dan Linked List". Diakses melalui https://bahan-ajar.esaunggul.ac.id/ccs120/wp-content/uploads/sites/1532/2019/12/Struktur-Data-Pertemuan-4.pdf.