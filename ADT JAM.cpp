#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// ADT Jam
struct Jam {
    long hari;
    long jam;
    long menit;
    long detik;
};

// Fungsi untuk konversi detik ke ADT Jam
Jam konversiDetik(long totalDetik) {
    Jam hasil;
    hasil.hari = totalDetik / 86400;
    hasil.jam = (totalDetik % 86400) / 3600;
    hasil.menit = (totalDetik % 3600) / 60;
    hasil.detik = totalDetik % 60;
    return hasil;
}

// Fungsi untuk mencetak ADT Jam
void cetakJam(const Jam& waktu) {
    cout << "===> " << waktu.hari << " hari\n";
    cout << "===> " << waktu.jam << " jam\n";
    cout << "===> " << waktu.menit << " menit\n";
    cout << "===> " << waktu.detik << " detik\n";
}

// Fungsi untuk menyimpan hasil ke file CSV
void simpanKeCSV(const Jam& waktu, long totalDetik) {
    ofstream file("hasil_konversi.csv");
    if (file.is_open()) {
        file << "Total Detik,Hari,Jam,Menit,Detik\n"; // Header
        file << totalDetik << "," 
             << waktu.hari << "," 
             << waktu.jam << "," 
             << waktu.menit << "," 
             << waktu.detik << "\n";
        file.close();
        cout << "Hasil telah disimpan ke 'hasil_konversi.csv'\n";
    } else {
        cout << "Gagal membuka file untuk menyimpan data.\n";
    }
}

// Fungsi untuk membaca data dari file teks
void bacaDariFile(const string& namaFile) {
    ifstream file(namaFile);
    if (file.is_open()) {
        long detik;
        while (file >> detik) {
            Jam waktu = konversiDetik(detik);
            cout << detik << " detik sama dengan:\n";
            cetakJam(waktu);
        }
        file.close();
    } else {
        cout << "Gagal membuka file.\n";
    }
}

// Fungsi untuk menampilkan menu interaktif
void tampilkanMenu() {
    cout << "Pilih opsi:\n";
    cout << "1. Konversi Detik\n";
    cout << "2. Simpan ke CSV\n";
    cout << "3. Baca dari File\n";
    cout << "4. Keluar\n";
    cout << "Pilihan Anda: ";
}

// Fungsi untuk pengujian unit
void testKonversiDetik() {
    Jam hasil = konversiDetik(90061);
    assert(hasil.hari == 1);
    assert(hasil.jam == 1);
    assert(hasil.menit == 1);
    assert(hasil.detik == 1);
    cout << "Semua pengujian berhasil.\n";
}

int main() {
    testKonversiDetik(); // Jalankan pengujian unit

    while (true) {
        tampilkanMenu();
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            long detik;
            cout << "Masukan satuan detik: ";
            cin >> detik;
            Jam waktu = konversiDetik(detik);
            cout << detik << " detik sama dengan:\n";
            cetakJam(waktu);
        } else if (pilihan == 2) {
            long detik;
            cout << "Masukan satuan detik untuk disimpan ke CSV: ";
            cin >> detik;
            Jam waktu = konversiDetik(detik);
            simpanKeCSV(waktu, detik);
        } else if (pilihan == 3) {
            string namaFile;
            cout << "Masukan nama file teks: ";
            cin >> namaFile;
            bacaDariFile(namaFile);
        } else if (pilihan == 4) {
            cout << "Keluar dari program.\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
