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
void bersihLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void tungguEnter() {
    printf("\nTekan Enter untuk melanjutkan...");
    while (getchar() != '\n');
    getchar();
}

void loading() {
    bersihLayar();
    printf("Memverifikasi data...\n\n");
    // Simulasi loading bar sederhana
    printf("[");
    for (int i = 0; i < 20; i++) {
        printf("=");
        Sleep(50); // Delay 50ms
    }
    printf("]\n");
    printf("\nLogin Berhasil! Selamat datang.\n");
    Sleep(1000);
}

void formatTanggal(time_t waktu, char *buffer) {
    strftime(buffer, 20, "%Y-%m-%d", localtime(&waktu));
}

int login() {
    char username[50], password[50];
    int percobaan = 0;

    while (percobaan < 3) {
        bersihLayar();
        printf("==============================\n");
        printf("    LOGIN SISTEM PERPUSTAKAAN\n");
        printf("==============================\n");
        printf("Username : "); scanf("%s", username);
        printf("Password : "); scanf("%s", password);

        // Hardcoded credential
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            strcpy(currentUser, username);
            loading();
            return 1; // Login Sukses
        } else {
            printf("\n[!] Username atau password salah.\n");
            percobaan++;
            Sleep(1500);
        }
    }
    printf("\n[!] Akses ditolak setelah 3x percobaan.\n");
    return 0; // Login Gagal
}


Isi disini bagian 3 
Isi disini bagian 4



