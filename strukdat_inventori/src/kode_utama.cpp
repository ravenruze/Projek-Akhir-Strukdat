#include <iostream>
#include <map>
#include <string>
#include <iomanip>


using namespace std;


struct Produk {
    int ID;
    string nama;
    string kategori;
    int stok;
    double harga;
    string status;
};


void tampilkanProduk(Produk p) {
    cout << "ID       : " << p.ID << endl;
    cout << "Nama     : " << p.nama << endl;
    cout << "Kategori : " << p.kategori << endl;
    cout << "Stok     : " << p.stok << endl;
    cout << "Harga    : Rp " << fixed << setprecision(0) << p.harga << endl;
    cout << "Status   : " << p.status << endl;
    cout << "----------------------------" << endl;
}


map<int, Produk> dataDummy() {
    map<int, Produk> data;
    data[1] = {1, "Beras 5 kg",        "Bahan Pokok",            25, 75000, "tersedia"};
    data[2] = {2, "Gula Pasir 1kg",    "Bahan Pokok",            50, 15000, "tersedia"};
    data[3] = {3, "Minyak Goreng 2L",  "Bahan Pokok",            30, 32000, "tersedia"};
    data[4] = {4, "Sabun Cuci Piring", "Kebutuhan Rumah Tangga", 80, 10000, "tersedia"};
    data[5] = {5, "Tisu",              "Kebutuhan Rumah Tangga",  0, 15000, "habis"   };
    return data;
}


class InventoriMap {
public:
    map<int, Produk> data;


    void insert(Produk p) {
        data[p.ID] = p;
    }


    Produk* search(int ID) {
        if (data.count(ID)) return &data[ID];
        return nullptr;
    }


    void updateStok(int ID, int stokBaru) {
        Produk* p = search(ID);
        if (p != nullptr) {
            p->stok   = stokBaru;
            p->status = (stokBaru > 0) ? "tersedia" : "habis";
            cout << "Stok produk ID " << ID << " berhasil diperbarui." << endl;
        } else {
            cout << "Produk tidak ditemukan." << endl;
        }
    }


    void hapus(int ID) {
        if (data.count(ID)) {
            data.erase(ID);
            cout << "Produk ID " << ID << " berhasil dihapus." << endl;
        } else {
            cout << "Produk tidak ditemukan." << endl;
        }
    }
};


void menuUtama() {
    InventoriMap inv;
    map<int, Produk> awal = dataDummy();
    for (auto& pasangan : awal) inv.insert(pasangan.second);
    int pilihan;
    do {
        cout << "\n====== SISTEM INVENTORI GUDANG ======" << endl;
        cout << "1. Tambah Produk" << endl;
        cout << "2. Cari Produk" << endl;
        cout << "3. Update Stok" << endl;
        cout << "4. Hapus Produk" << endl;
        cout << "5. Tampilkan Semua Produk" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;


        if (pilihan == 1) {
            Produk p;
            cout << "ID Produk   : "; cin >> p.ID;
            cout << "Nama        : "; cin.ignore(); getline(cin, p.nama);
            cout << "Kategori    : "; getline(cin, p.kategori);
            cout << "Stok        : "; cin >> p.stok;
            cout << "Harga       : "; cin >> p.harga;
            p.status = (p.stok > 0) ? "tersedia" : "habis";
            inv.insert(p);
            cout << "Produk berhasil ditambahkan!" << endl;


        } else if (pilihan == 2) {
            int ID;
            cout << "Masukkan ID produk: "; cin >> ID;
            Produk* hasil = inv.search(ID);
            if (hasil != nullptr) tampilkanProduk(*hasil);
            else cout << "Produk tidak ditemukan." << endl;


        } else if (pilihan == 3) {
            int ID, stokBaru;
            cout << "ID Produk   : "; cin >> ID;
            cout << "Stok Baru   : "; cin >> stokBaru;
            inv.updateStok(ID, stokBaru);


        } else if (pilihan == 4) {
            int ID;
            cout << "ID Produk yang ingin dihapus: "; cin >> ID;
            inv.hapus(ID);


        } else if (pilihan == 5) {
            cout << "\n--- DAFTAR SEMUA PRODUK ---" << endl;
            for (auto& pasangan : inv.data)
                tampilkanProduk(pasangan.second);
        }


    } while (pilihan != 0);
}


int main() {
    menuUtama();
    return 0;
}
