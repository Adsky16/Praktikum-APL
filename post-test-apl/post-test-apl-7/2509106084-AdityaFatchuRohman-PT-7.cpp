#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>
#include <limits>

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
    try {
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

        throw runtime_error("Username atau password salah!");

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
        return 0;
    }
}

void menuRegistrasi(Pengguna daftar[], int &jml, int maks) {
    try {
        if (jml >= maks)
            throw runtime_error("Memori user penuh!");

        cout << "\n Username Baru: "; cin >> daftar[jml].username;
        cout << " Password Baru: "; cin >> daftar[jml].password;
        daftar[jml].status = "user";
        jml++;

        cout << "\n Akun berhasil dibuat! Silakan Login.\n";

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
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
    cout << "Masukkan Kategori: ";
    cin >> cari;

    int ditemukan = 0;

    cout << "\nHasil Pencarian:\n";

    for (int i = 0; i < jml; i++) {
        if (toLower((daftar+i)->kategori) == toLower(cari)) {
            cout << "ID   : " << (daftar+i)->id << endl;
            cout << "Nama : " << (daftar+i)->nama_barang << endl;
            cout << "Stok : " << (daftar+i)->stok << endl;
            cout << "----------------------\n";
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        cout << "Data tidak ditemukan.\n";

    jeda("Tekan Enter kembali.");
}

void tambahBarang(Produk *daftar, int *jml, int *lastId, int maks) {
    try {
        if (*jml >= maks)
            throw runtime_error("Gudang penuh!");

        (daftar + *jml)->id = (*lastId)++;

        cout << "\n Nama Barang: "; 
        cin.ignore(); 
        getline(cin, (daftar + *jml)->nama_barang);

        cout << " Kategori   : "; 
        getline(cin, (daftar + *jml)->kategori);

        int stokInput;
        cout << " Stok       : ";
        cin >> stokInput;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Stok harus angka!");
        }

        if (stokInput < 0)
            throw invalid_argument("Stok tidak boleh negatif!");

        (daftar + *jml)->stok = stokInput;
        (*jml)++;

        cout << "\n Barang berhasil ditambahkan\n";

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
    }

    jeda("Tekan Enter untuk kembali.");
}

void editBarang(Produk *daftar, int jml) {
    tampilkanStok(daftar, jml);
    cout << "\n--- MENU EDIT STOK ---";
    
    try {
        if (jml == 0)
            throw runtime_error("Data kosong!");

        int id_edit; 
        cout << "\nMasukkan ID Barang yang akan diedit: "; 
        cin >> id_edit;

        bool ketemu = false;

        for (int i = 0; i < jml; i++) {
            if ((daftar+i)->id == id_edit) {
                cout << " Nama Barang: " << (daftar+i)->nama_barang << endl;

                int stokBaru;
                cout << " Masukkan Stok Baru: ";
                cin >> stokBaru;

                if (stokBaru < 0)
                    throw invalid_argument("Stok tidak boleh negatif!");

                (daftar+i)->stok = stokBaru;

                ketemu = true;
                cout << "\n Berhasil diupdate!\n";
                break;
            }
        }

        if (!ketemu)
            throw runtime_error("ID tidak ditemukan!");

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
    }

    jeda("Tekan Enter untuk kembali.");
}

void hapusBarang(Produk *daftar, int *jml) {
    tampilkanStok(daftar, *jml);
    cout << "\n--- MENU HAPUS BARANG ---";
    
    try {
        if (*jml == 0)
            throw runtime_error("Data kosong!");

        int id_hapus; 
        cout << "\nMasukkan ID Barang yang akan dihapus: "; 
        cin >> id_hapus;

        bool ketemu = false;

        for (int i = 0; i < *jml; i++) {
            if ((daftar+i)->id == id_hapus) {
                for (int j = i; j < *jml - 1; j++) {
                    *(daftar + j) = *(daftar + j + 1);
                }
                (*jml)--; 
                ketemu = true;
                cout << "\n Barang berhasil dihapus.\n";
                break;
            }
        }

        if (!ketemu)
            throw runtime_error("ID tidak ditemukan!");

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
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

bool sudahTerurutID(Produk *daftar, int jml) {
    for (int i = 0; i < jml - 1; i++) {
        if ((daftar+i)->id > (daftar+i+1)->id) {
            return false;
        }
    }
    return true;
}

int interpolationSearch(Produk *daftar, int jml, int idCari) {
    int low = 0;
    int high = jml - 1;

    while (low <= high && 
        idCari >= (daftar+low)->id && 
        idCari <= (daftar+high)->id) {

        if (low == high) {
            if ((daftar+low)->id == idCari)
                return low;
            return -1;
        }

        int pos = low + ((double)(high - low) /
                ((daftar+high)->id - (daftar+low)->id)) *
                (idCari - (daftar+low)->id);

        if ((daftar+pos)->id == idCari)
            return pos;

        if ((daftar+pos)->id < idCari)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1;
}

void cariID(Produk *daftar, int jml) {
    system("cls || clear");

    try {
        if (jml == 0)
            throw runtime_error("Data kosong!");

        if (!sudahTerurutID(daftar, jml))
            throw runtime_error("Data belum terurut berdasarkan ID!");

        int idCari;
        cout << "Masukkan ID Barang: ";
        cin >> idCari;

        int hasil = interpolationSearch(daftar, jml, idCari);

        if (hasil == -1)
            throw runtime_error("Data tidak ditemukan!");

        cout << "\nData ditemukan:\n";
        cout << "ID       : " << (daftar+hasil)->id << endl;
        cout << "Nama     : " << (daftar+hasil)->nama_barang << endl;
        cout << "Kategori : " << (daftar+hasil)->kategori << endl;
        cout << "Stok     : " << (daftar+hasil)->stok << endl;

    } catch (exception &e) {
        cout << "\nError: " << e.what() << endl;
    }

    jeda("Tekan Enter kembali.");
}

int main() {
    const int MAKS_BARANG = 100;
    const int MAKS_USER = 10;
    Produk daftar_produk[MAKS_BARANG];
    Pengguna daftar_user[MAKS_USER];

    int jumlah_produk = 0, jumlah_user = 1, id_produk_terakhir = 1;

    daftar_produk[0] = {1, "Kaca Bening 5mm", "Kaca", 20};
    daftar_produk[1] = {2, "Kaca Tempered 8mm", "Kaca", 15};
    daftar_produk[2] = {3, "Aluminium Putih", "Aluminium", 30};
    daftar_produk[3] = {4, "Aluminium Hitam", "Aluminium", 18};
    daftar_produk[4] = {5, "Engsel Pintu Kaca", "Aksesoris", 25};
    daftar_produk[5] = {6, "Handle Pintu", "Aksesoris", 10};
    daftar_produk[6] = {7, "Karet Kaca", "Aksesoris", 40};
    daftar_produk[7] = {8, "Rel Sliding", "Aluminium", 12};

    jumlah_produk = 8;
    id_produk_terakhir = 9;

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
                cout << " 1. Lihat Stok\n 2. Cari Kategori\n 3. Sorting\n 4. Cari ID barang\n 5. Tambah Barang\n 6. Edit Barang\n 7. Hapus Barang\n 8. Logout\n";
            } else {
                cout << " 1. Lihat Stok\n 2. Cari Kategori\n 3. Sorting\n 4. Cari ID barang\n 5. Logout\n";
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
                    cariID(daftar_produk, jumlah_produk);
                    break;

                case 5:
                if (status_aktif == "admin")
                    tambahBarang(daftar_produk, &jumlah_produk, &id_produk_terakhir, MAKS_BARANG);
                else {
                    sedang_login = 0;
                    jeda("Logout berhasil.");
                }
                break;

                case 6:
                    if (status_aktif == "admin")
                        editBarang(daftar_produk, jumlah_produk);
                    break;

                case 7:
                    if (status_aktif == "admin")
                        hapusBarang(daftar_produk, &jumlah_produk);
                    break;
                
                case 8:
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