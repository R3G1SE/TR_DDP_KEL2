#include <stdio.h>
#include <stdlib.h> // Untuk system("cls") / system("clear")
#include <string.h> // Untuk strcmp() (membandingkan string)
#include <time.h>   // Untuk tanggal & waktu
#include <windows.h> // Untuk Sleep() dan karakter loading (khusus Windows)

Isi disini bagian 1 
  // --- KONSTANTA ---
#define MAX_BUKU 10
#define MAX_PINJAM 20
#define BATAS_PINJAM_HARI 7
#define DENDA_PER_HARI 1000

// --- STRUKTUR DATA ---
struct Buku {
    int id;
    char kode[10];
    char judul[100];
    char penulis[50];
    int status; // 0 = Tersedia, 1 = Dipinjam
};

struct Peminjaman {
    int idBuku;
    char usernamePeminjam[50];
    time_t waktuPinjam;
    time_t waktuKembali;
    int statusPinjam; // 0 = Masih Dipinjam, 1 = Sudah Kembali
};

// --- DATABASE GLOBAL ---
// Variabel ini diakses oleh semua anggota tim
struct Buku daftarBuku[MAX_BUKU];
struct Peminjaman daftarPinjam[MAX_PINJAM];
int jumlahBuku = 0;
int jumlahPinjam = 0;
char currentUser[50];

// --- PROTOTYPE FUNGSI (Agar urutan koding anggota lain tidak error) ---
void bersihLayar();
void tungguEnter();
void formatTanggal(time_t waktu, char *buffer);
void lihatDaftarBuku(); // Diperlukan oleh PinjamBuku

Isi disini bagian 2
Isi disini bagian 3 
Isi disini bagian 4


