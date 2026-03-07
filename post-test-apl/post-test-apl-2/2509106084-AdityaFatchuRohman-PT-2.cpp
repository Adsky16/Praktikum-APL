#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Produk {
    int id;
    string nama_barang;
    string kategori;
    double harga;
    int stok;
};

struct Pengguna {
    string username;
    string password;
    string status;
};

int main() {
    const int MAKS_BARANG = 100;
    const int MAKS_USER = 10;
    Produk daftar_produk[MAKS_BARANG];
    Pengguna daftar_user[MAKS_USER];
    
    int jumlah_produk = 0, jumlah_user = 0, id_produk_terakhir = 1;
    bool sedang_login = false;
    bool aplikasi_berjalan = true;
    string user_aktif = "", status = "";
    int pilihan_utama;
    int percobaan_login = 0;

    daftar_user[0] = {"adit", "1608", "admin"};
    jumlah_user = 1;

    do {
        system("cls || clear");

        if (!sedang_login) {
            cout << "===============================================\n";
            cout << "       INVENTARIS TOKO KACA & ALUMINIUM        \n";
            cout << "===============================================\n";
            cout << " 1. Login\n";
            cout << " 2. Registrasi\n";
            cout << " 3. Keluar\n";
            cout << "-----------------------------------------------\n";
            cout << " Pilih: "; cin >> pilihan_utama;

            if (pilihan_utama == 1) {
                if (percobaan_login >= 3) {
                    cout << "\nAkses ditolak. Anda telah salah login 3 kali.\n";
                    cout << " Silakan hubungi admin atau restart aplikasi.\n";
                } else {
                    string nama, pass;
                    cout << "\n Username: "; cin >> nama;
                    cout << " Password: "; cin >> pass;
                    
                    bool login_berhasil = false;
                    for (int i = 0; i < jumlah_user; i++) {
                        if (daftar_user[i].username == nama && daftar_user[i].password == pass) {
                            sedang_login = true;
                            user_aktif = nama;
                            status = daftar_user[i].status;
                            login_berhasil = true;
                            percobaan_login = 0; // Reset percobaan jika berhasil
                            break;
                        }
                    }

                    if (!login_berhasil) {
                        percobaan_login++;
                        cout << "\n Login Gagal (" << percobaan_login << "/3). Username/Password salah.\n";
                    }
                }
                cout << " Tekan Enter untuk melanjutkan"; 
                cin.ignore(); 
                cin.get();
            } 
            else if (pilihan_utama == 2) {
                if (jumlah_user < MAKS_USER) {
                    cout << "\n Username Baru: "; cin >> daftar_user[jumlah_user].username;
                    cout << " Password Baru: "; cin >> daftar_user[jumlah_user].password;
                    daftar_user[jumlah_user].status = "user"; 
                    jumlah_user++;
                    cout << "\n Akun berhasil dibuat! Silakan Login.\n";
                } else {
                    cout << "\n Memori user penuh!\n";
                }
                cout << " Tekan Enter untuk melanjutkan."; 
                cin.ignore(); 
                cin.get();
            }
            else if (pilihan_utama == 3) {
                aplikasi_berjalan = false;
                cout << "\n Terima kasih telah menggunakan aplikasi. Tekan Enter untuk keluar."; 
                cin.ignore(); 
                cin.get();
            }
            else {
                cout << "\n Pilihan tidak valid. Tekan Enter untuk mencoba lagi."; 
                cin.ignore(); 
                cin.get();
            }
        } else {
            cout << "===============================================\n";
            cout << "       INVENTARIS TOKO KACA & ALUMINIUM        \n";
            cout << "===============================================\n";
            
            if (status == "admin") {
                cout << " 1. Lihat Semua Stok\n";
                cout << " 2. Cari Berdasarkan Kategori\n";
                cout << " 3. Tambah Barang\n";
                cout << " 4. Edit Barang\n";
                cout << " 5. Hapus Barang\n";
                cout << " 6. Logout\n";
            }
            else {
                cout << " 1. Lihat Semua Stok\n";
                cout << " 2. Cari Berdasarkan Kategori\n";
                cout << " 3. Logout\n";
            }
            cout << "----------------------------------------------------------\n";
            cout << " Pilih Menu: "; cin >> pilihan_utama;

            if (pilihan_utama == 1) {
                cout << "\n+-----+----------------------+---------------+----------+\n";
                cout << "| ID  | Nama Barang          | Kategori      | Stok     |\n";
                cout << "+-----+----------------------+---------------+----------+\n";
                if (jumlah_produk == 0) {
                    cout << "|                ( Data Masih Kosong )                  |\n";
                } else {
                    for (int i = 0; i < jumlah_produk; i++) {
                        cout << "| " << left << setw(4) << daftar_produk[i].id 
                            << "| " << setw(21) << daftar_produk[i].nama_barang 
                            << "| " << setw(14) << daftar_produk[i].kategori 
                            << "| " << setw(9) << daftar_produk[i].stok << "|\n";
                    }
                }
                cout << "+-----+----------------------+---------------+----------+\n";
                cout << " Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            } 
            else if (pilihan_utama == 2) {
                string cari; cout << "\n Masukkan Kategori: "; cin >> cari;
                bool ditemukan = false;
                cout << "\n Hasil Pencarian:\n";
                for (int i = 0; i < jumlah_produk; i++) {
                    if (daftar_produk[i].kategori == cari) {
                        cout << " - " << daftar_produk[i].nama_barang << " (ID: " << daftar_produk[i].id << ") Stok: " << daftar_produk[i].stok << endl;
                        ditemukan = true;
                    }
                }
                if (!ditemukan) cout << "Kategori tidak ditemukan.\n";
                cout << "\n Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
            else if (pilihan_utama == 3 && status == "admin") {
                if (jumlah_produk < MAKS_BARANG) {
                    daftar_produk[jumlah_produk].id = id_produk_terakhir++;
                    cout << "\n Nama Barang: "; cin.ignore(); getline(cin, daftar_produk[jumlah_produk].nama_barang);
                    cout << " Kategori   : "; getline(cin, daftar_produk[jumlah_produk].kategori);
                    cout << " Stok       : "; cin >> daftar_produk[jumlah_produk].stok;
                    jumlah_produk++;
                    cout << "\n Barang berhasil ditambahkan\n";
                } else {
                    cout << "\n Gudang penuh\n";
                }
                cout << " Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
            else if (pilihan_utama == 4 && status == "admin") {
                cout << "\n--- Daftar Barang Saat Ini ---\n";
                if (jumlah_produk == 0) {
                    cout << " ( Data Kosong )\n";
                } else {
                    for (int i = 0; i < jumlah_produk; i++) {
                        cout << " ID: " << daftar_produk[i].id << " | " << daftar_produk[i].nama_barang << " (Stok: " << daftar_produk[i].stok << ")\n";
                    }
                }
                cout << "------------------------------\n";

                int id_edit; cout << " Masukkan ID Barang yang akan diedit: "; cin >> id_edit;
                bool ketemu = false;
                for (int i = 0; i < jumlah_produk; i++) {
                    if (daftar_produk[i].id == id_edit) {
                        cout << " Nama Barang: " << daftar_produk[i].nama_barang << endl;
                        cout << " Masukkan Stok Baru: "; cin >> daftar_produk[i].stok;
                        ketemu = true;
                        cout << "\n Berhasil diupdate\n";
                        break;
                    }
                }
                if (!ketemu) cout << "\n ID tidak ditemukan.\n";
                cout << " Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
            else if (pilihan_utama == 5 && status == "admin") {
                // Tampilkan daftar ringkas sebelum menghapus
                cout << "\n--- Daftar Barang Saat Ini ---\n";
                if (jumlah_produk == 0) {
                    cout << " ( Data Kosong )\n";
                } else {
                    for (int i = 0; i < jumlah_produk; i++) {
                        cout << " ID: " << daftar_produk[i].id << " | " << daftar_produk[i].nama_barang << "\n";
                    }
                }
                cout << "------------------------------\n";

                int id_hapus; cout << " Masukkan ID Barang yang akan dihapus: "; cin >> id_hapus;
                bool ketemu = false;
                for (int i = 0; i < jumlah_produk; i++) {
                    if (daftar_produk[i].id == id_hapus) {
                        for (int j = i; j < jumlah_produk - 1; j++) {
                            daftar_produk[j] = daftar_produk[j+1];
                        }
                        jumlah_produk--; 
                        ketemu = true;
                        cout << "\n Barang berhasil dihapus.\n";
                        break;
                    }
                }
                if (!ketemu) cout << "\n ID tidak ditemukan.\n";
                cout << " Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
            else if (pilihan_utama == 6 && status == "admin" || pilihan_utama == 3 && status != "admin") { 
                sedang_login = false;
                pilihan_utama = 0;
                cout << "\n Berhasil Logout. Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
            else { 
                cout << "\nPilihan tidak tersedia atau akses ditolak.\n"; 
                cout << " Tekan Enter untuk kembali."; 
                cin.ignore(); 
                cin.get();
            }
        }
    } while (aplikasi_berjalan);

    return 0;
}