#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Produk {
    int id;
    string nama_barang;
    string kategori;
    int stok;
};

struct Pengguna {
    string username;
    string password;
    string status;
};

void tampilkanHeader(string statusUser = "", string userAktif = "") {
    system("cls || clear");
    cout << "===============================================\n";
    cout << "       INVENTARIS TOKO KACA & ALUMINIUM        \n";
    cout << "===============================================\n";
}

void jeda(string pesan) {
    cout << "\n " << pesan;
    cin.ignore();
    cin.get();
}

int prosesLogin(Pengguna *daftar, int jml, string &userAktif, string &statusAktif) {
    string nama, pass;
    cout << "\n Username: "; cin >> nama;
    cout << " Password: "; cin >> pass;

    for (int i = 0; i < jml; i++) {
        if ((daftar + i)->username == nama && (daftar + i)->password == pass) {
            userAktif = nama;
            statusAktif = (daftar + i)->status;
            return 1;
        }
    }
    return 0;
}

void menuRegistrasi(Pengguna daftar[], int &jml, int maks) {
    if (jml < maks) {
        cout << "\n Username Baru: "; cin >> daftar[jml].username;
        cout << " Password Baru: "; cin >> daftar[jml].password;
        daftar[jml].status = "user";
        jml++;
        cout << "\n Akun berhasil dibuat! Silakan Login.\n";
    } else {
        cout << "\n Memori user penuh!\n";
    }
    jeda("Tekan Enter untuk melanjutkan.");
}

void tampilkanStok(Produk *daftar, int jml) {
    system("cls || clear");
    cout << "\n+-----+----------------------+---------------+----------+\n";
    cout << "| ID  | Nama Barang          | Kategori      | Stok     |\n";
    cout << "+-----+----------------------+---------------+----------+\n";
    if (jml == 0) {
        cout << "|                ( Data Masih Kosong )                  |\n";
    } else {
        for (int i = 0; i < jml; i++) {
            cout << "| " << left << setw(4) << (daftar+i)->id 
                << "| " << setw(21) << (daftar+i)->nama_barang 
                << "| " << setw(14) << (daftar+i)->kategori 
                << "| " << setw(9) << (daftar+i)->stok << "|\n";
        }
    }
    cout << "+-----+----------------------+---------------+----------+\n";
}

string toLower(string teks) {
    for (int i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);
    }
    return teks;
}

void cariBarang(Produk *daftar, int jml) {
    system("cls || clear");
    string cari; 
    cout << "\n Masukkan Kategori/Nama: "; 
    cin >> cari;

    int ditemukan = 0;
    cout << "\n Hasil Pencarian:\n";

    for (int i = 0; i < jml; i++) {
        string cariLower = toLower(cari);
        string kategoriLower = toLower((daftar+i)->kategori);

        if (kategoriLower.find(cariLower) != string::npos) {
            cout << " - " << (daftar+i)->nama_barang 
                << " (ID: " << (daftar+i)->id 
                << ") Stok: " << (daftar+i)->stok << endl;
            ditemukan = 1;
        }
    }

    if (ditemukan == 0) cout << "Data tidak ditemukan.\n";
    jeda("Tekan Enter untuk kembali.");
}

void tambahBarang(Produk *daftar, int *jml, int *lastId, int maks) {
    if (*jml < maks) {
        (daftar + *jml)->id = (*lastId)++;

        cout << "\n Nama Barang: "; 
        cin.ignore(); 
        getline(cin, (daftar + *jml)->nama_barang);

        cout << " Kategori   : "; 
        getline(cin, (daftar + *jml)->kategori);

        int stokInput;
        do {
            cout << " Stok       : ";
            cin >> stokInput;

            if (stokInput < 0) {
                cout << " Stok tidak boleh negatif!\n";
            }

        } while (stokInput < 0);

        (daftar + *jml)->stok = stokInput;

        (*jml)++;

        cout << "\n Barang berhasil ditambahkan\n";
    } else {
        cout << "\n Gudang penuh\n";
    }
    jeda("Tekan Enter untuk kembali.");
}

void editBarang(Produk *daftar, int jml) {
    tampilkanStok(daftar, jml);
    cout << "\n--- MENU EDIT STOK ---";
    
    if (jml > 0) {
        int id_edit; 
        cout << "\nMasukkan ID Barang yang akan diedit: "; 
        cin >> id_edit;

        int ketemu = 0;

        for (int i = 0; i < jml; i++) {
            if ((daftar+i)->id == id_edit) {
                cout << " Nama Barang: " << (daftar+i)->nama_barang << endl;

                int stokBaru;
                do {
                    cout << " Masukkan Stok Baru: ";
                    cin >> stokBaru;

                    if (stokBaru < 0) {
                        cout << " Stok tidak boleh negatif!\n";
                    }

                } while (stokBaru < 0);

                (daftar+i)->stok = stokBaru;

                ketemu = 1;
                cout << "\n Berhasil diupdate!\n";
                break;
            }
        }

        if (ketemu == 0) cout << "\nID tidak ditemukan.\n";
    }
    jeda("Tekan Enter untuk kembali.");
}

void hapusBarang(Produk *daftar, int *jml) {
    tampilkanStok(daftar, *jml);
    cout << "\n--- MENU HAPUS BARANG ---";
    
    if (*jml > 0) {
        int id_hapus; 
        cout << "\nMasukkan ID Barang yang akan dihapus: "; 
        cin >> id_hapus;

        int ketemu = 0;

        for (int i = 0; i < *jml; i++) {
            if ((daftar+i)->id == id_hapus) {
                for (int j = i; j < *jml - 1; j++) {
                    *(daftar + j) = *(daftar + j + 1);
                }
                (*jml)--; 
                ketemu = 1;
                cout << "\n Barang berhasil dihapus.\n";
                break;
            }
        }

        if (ketemu == 0) cout << "\nID tidak ditemukan.\n";
    }
    jeda("Tekan Enter untuk kembali.");
}

void insertionSort(Produk *daftar, int jml) {
    for (int i = 1; i < jml; i++) {
        Produk key = *(daftar + i);
        int j = i - 1;

        while (j >= 0 && toLower((daftar + j)->nama_barang) < toLower(key.nama_barang)) {
            *(daftar + j + 1) = *(daftar + j);
            j--;
        }
        *(daftar + j + 1) = key;
    }
}

void selectionSort(Produk *daftar, int jml) {
    for (int i = 0; i < jml - 1; i++) {
        int min = i;
        for (int j = i + 1; j < jml; j++) {
            if ((daftar + j)->stok < (daftar + min)->stok) {
                min = j;
            }
        }
        Produk temp = *(daftar + i);
        *(daftar + i) = *(daftar + min);
        *(daftar + min) = temp;
    }
}

int partitionID(Produk *daftar, int low, int high) {
    int pivot = (daftar + high)->id;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if ((daftar + j)->id < pivot) {
            i++;
            Produk temp = *(daftar + i);
            *(daftar + i) = *(daftar + j);
            *(daftar + j) = temp;
        }
    }

    Produk temp = *(daftar + i + 1);
    *(daftar + i + 1) = *(daftar + high);
    *(daftar + high) = temp;

    return i + 1;
}

void quickSort(Produk *daftar, int low, int high) {
    if (low < high) {
        int pi = partitionID(daftar, low, high);
        quickSort(daftar, low, pi - 1);
        quickSort(daftar, pi + 1, high);
    }
}

void menuSorting(Produk *daftar, int jml) {
    int pilih;
    do {
        system("cls || clear");
        cout << "===== MENU SORTING =====\n";
        cout << "1. Urutkan Nama (Descending)\n";
        cout << "2. Urutkan Stok (Ascending)\n";
        cout << "3. Urutkan ID (Ascending)\n";
        cout << "4. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1:
                insertionSort(daftar, jml);
                tampilkanStok(daftar, jml);
                jeda("Berhasil Mengurutkan Nama");
                break;

            case 2:
                selectionSort(daftar, jml);
                tampilkanStok(daftar, jml);
                jeda("Berhasil Mengurutkan Stok");
                break;

            case 3:
                quickSort(daftar, 0, jml - 1);
                tampilkanStok(daftar, jml);
                jeda("Berhasil Mengurutkan ID");
                break;
        }

    } while (pilih != 4);
}

int main() {
    const int MAKS_BARANG = 100;
    const int MAKS_USER = 10;
    Produk daftar_produk[MAKS_BARANG];
    Pengguna daftar_user[MAKS_USER];
    
    int jumlah_produk = 0, jumlah_user = 1, id_produk_terakhir = 1;
    int sedang_login = 0;
    int aplikasi_berjalan = 1;
    int percobaan_login = 1;
    
    string user_aktif = "", status_aktif = "";
    int pilihan_utama;

    daftar_user[0] = {"adit", "084", "admin"};

    while (aplikasi_berjalan == 1) {
        if (sedang_login == 0) {
            tampilkanHeader();
            cout << " 1. Login\n 2. Registrasi\n 3. Keluar\n-----------------------------------------------\n Pilih: "; 
            cin >> pilihan_utama;

            switch(pilihan_utama) {
                case 1:
                    if (percobaan_login > 3) {
                        cout << "\n Akses ditolak.\n";
                        aplikasi_berjalan = 0; 
                        jeda("Program akan ditutup.");
                    } else {
                        cout << "\n (Percobaan " << percobaan_login << "/3)";
                        if (prosesLogin(daftar_user, jumlah_user, user_aktif, status_aktif) == 1) {
                            sedang_login = 1;
                            percobaan_login = 1;
                            jeda("Login Berhasil!");
                        } else {
                            cout << "\nLogin Gagal!\n";
                            percobaan_login++;
                            jeda("Coba lagi.");
                        }
                    }
                    break;

                case 2:
                    menuRegistrasi(daftar_user, jumlah_user, MAKS_USER);
                    break;

                case 3:
                    aplikasi_berjalan = 0;
                    break;
            }
        } else {
            tampilkanHeader(status_aktif, user_aktif);

            if (status_aktif == "admin") {
                cout << " 1. Lihat Stok\n 2. Cari Kategori\n 3. Sorting\n 4. Tambah Barang\n 5. Edit Barang\n 6. Hapus Barang\n 7. Logout\n";
            } else {
                cout << " 1. Lihat Stok\n 2. Cari Kategori\n 3. Sorting\n 4. Logout\n";
            }

            cout << "-----------------------------------------------\n Pilih Menu: "; 
            cin >> pilihan_utama;

            switch(pilihan_utama) {
                case 1:
                    tampilkanStok(daftar_produk, jumlah_produk);
                    jeda("Tekan Enter kembali.");
                    break;
                    
                case 2:
                    cariBarang(daftar_produk, jumlah_produk);
                break;
                    
                case 3:
                    menuSorting(daftar_produk, jumlah_produk);
                break;

                case 4:
                if (status_aktif == "admin")
                    tambahBarang(daftar_produk, &jumlah_produk, &id_produk_terakhir, MAKS_BARANG);
                else {
                    sedang_login = 0;
                    jeda("Logout berhasil.");
                }
                break;

                case 5:
                    if (status_aktif == "admin")
                        editBarang(daftar_produk, jumlah_produk);
                    break;

                case 6:
                    if (status_aktif == "admin")
                        hapusBarang(daftar_produk, &jumlah_produk);
                    break;
                
                case 7:
                    if (status_aktif == "admin") {
                        sedang_login = 0;
                        jeda("Logout berhasil.");
                    }
                break;
            }
        }
    }

    return 0;
}