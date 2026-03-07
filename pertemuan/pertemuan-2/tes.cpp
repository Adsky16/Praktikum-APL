#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Batas maksimal penyimpanan barang
const int MAKS_BARANG = 100;

// Struktur data untuk barang dalam bahasa Indonesia
struct Produk {
    int id;
    string nama_barang;
    string kategori;
    double harga;
    int stok;
};

// Menggunakan array statis sebagai pengganti vector
Produk daftar_produk[MAKS_BARANG];
int jumlah_sekarang = 0;
int id_terakhir = 1;

// --- Fungsi: Mencari indeks berdasarkan ID ---
int cari_indeks(int id_cari) {
    for (int i = 0; i < jumlah_sekarang; i++) {
        if (daftar_produk[i].id == id_cari) {
            return i;
        }
    }
    return -1;
}

// --- 1. TAMBAH (Create) ---
void tambah_barang() {
    if (jumlah_sekarang < MAKS_BARANG) {
        Produk p;
        p.id = id_terakhir++;
        
        cout << "\n--- Tambah Produk Toko ---\n";
        cout << "Nama Barang: ";
        cin.ignore();
        getline(cin, p.nama_barang);
        cout << "Kategori (Kaca/Aluminium): ";
        getline(cin, p.kategori);
        cout << "Harga Jual: ";
        cin >> p.harga;
        cout << "Jumlah Stok: ";
        cin >> p.stok;

        daftar_produk[jumlah_sekarang] = p;
        jumlah_sekarang++;
        cout << "\n[Sukses] Barang berhasil disimpan!\n";
    } else {
        cout << "\n[Error] Gudang penuh! Maksimal 100 barang.\n";
    }
}

// --- 2. TAMPILKAN (Read) ---
void tampilkan_barang() {
    if (jumlah_sekarang == 0) {
        cout << "\n[Info] Belum ada data barang di toko.\n";
        return;
    }

    cout << "\n" << setfill('=') << setw(65) << "=" << endl;
    cout << setfill(' ');
    cout << left << setw(5) << "ID" << setw(20) << "Nama Barang" << setw(15) << "Kategori" << setw(15) << "Harga" << "Stok" << endl;
    cout << setfill('-') << setw(65) << "-" << endl;
    cout << setfill(' ');

    for (int i = 0; i < jumlah_sekarang; i++) {
        cout << left << setw(5) << daftar_produk[i].id 
            << setw(20) << daftar_produk[i].nama_barang 
            << setw(15) << daftar_produk[i].kategori 
            << "Rp" << setw(13) << (long long)daftar_produk[i].harga 
            << daftar_produk[i].stok << endl;
    }
    cout << setfill('=') << setw(65) << "=" << endl;
}

// --- 3. UBAH (Update) ---
void ubah_barang() {
    int id_input;
    cout << "\nMasukkan ID barang yang akan diubah: ";
    cin >> id_input;

    int indeks = cari_indeks(id_input);
    if (indeks != -1) {
        cout << "Data ditemukan: " << daftar_produk[indeks].nama_barang << endl;
        cout << "Nama Baru: ";
        cin.ignore();
        getline(cin, daftar_produk[indeks].nama_barang);
        cout << "Harga Baru: ";
        cin >> daftar_produk[indeks].harga;
        cout << "Stok Baru: ";
        cin >> daftar_produk[indeks].stok;
        cout << "\n[Sukses] Data berhasil diperbarui!\n";
    } else {
        cout << "\n[Error] ID tidak ditemukan.\n";
    }
}

// --- 4. HAPUS (Delete) ---
void hapus_barang() {
    int id_input;
    cout << "\nMasukkan ID barang yang ingin dihapus: ";
    cin >> id_input;

    int indeks = cari_indeks(id_input);
    if (indeks != -1) {
        // Menggeser sisa elemen array ke kiri untuk mengisi celah yang kosong
        for (int i = indeks; i < jumlah_sekarang - 1; i++) {
            daftar_produk[i] = daftar_produk[i + 1];
        }
        jumlah_sekarang--;
        cout << "\n[Sukses] Barang berhasil dihapus dari sistem.\n";
    } else {
        cout << "\n[Error] ID tidak ditemukan.\n";
    }
}

int main() {
    int menu;
    do {
        cout << "\n>>> PROGRAM INVENTARIS TOKO KACA & ALUMINIUM <<<\n";
        cout << "1. Input Barang Baru\n";
        cout << "2. Cek Stok Barang\n";
        cout << "3. Edit Data Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Selesai\n";
        cout << "Pilih Menu: ";
        cin >> menu;

        switch (menu) {
            case 1: tambah_barang(); break;
            case 2: tampilkan_barang(); break;
            case 3: ubah_barang(); break;
            case 4: hapus_barang(); break;
            case 5: cout << "Menutup program. Terima kasih!\n"; break;
            default: cout << "Menu tidak tersedia.\n";
        }
    } while (menu != 5);

    return 0;
}