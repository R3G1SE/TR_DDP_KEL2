#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>   
#include <windows.h> 
//Isi disini bagian 1 
#define MAX_BUKU 10
#define MAX_PINJAM 20
#define BATAS_PINJAM_HARI 7
#define DENDA_PER_HARI 1000

struct Buku {
    int id;
    char kode[10];
    char judul[100];
    char penulis[50];
    int status; 
};

struct Peminjaman {
    int idBuku;
    char usernamePeminjam[50];
    time_t waktuPinjam;
    time_t waktuKembali;
    int statusPinjam; 
};

struct Buku daftarBuku[MAX_BUKU];
struct Peminjaman daftarPinjam[MAX_PINJAM];
int jumlahBuku = 0;
int jumlahPinjam = 0;
char currentUser[50];
void bersihLayar();
void tungguEnter();
void formatTanggal(time_t waktu, char *buffer);
void lihatDaftarBuku(); 

//Isi disini bagian 2
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
    printf("[");
    for (int i = 0; i < 20; i++) {
        printf("=");
        Sleep(50); 
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

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            strcpy(currentUser, username);
            loading();
            return 1; 
        } else {
            printf("\n[!] Username atau password salah.\n");
            percobaan++;
            Sleep(1500);
        }
    }
    printf("\n[!] Akses ditolak setelah 3x percobaan.\n");
    return 0; 
}


//Isi disini bagian 3 
void inisialisasiDataBuku() {
  
    daftarBuku[0] = (struct Buku){1, "C001", "Dasar Pemrograman C", "Budi Raharjo", 0};
    daftarBuku[1] = (struct Buku){2, "M002", "Matematika Diskrit", "Rinaldi Munir", 0};
    daftarBuku[2] = (struct Buku){3, "D003", "Sistem Basis Data", "Fathansyah", 0};
    daftarBuku[3] = (struct Buku){4, "A004", "Struktur Data", "Abdul Kadir", 0};
    
    jumlahBuku = 4;
}

void tampilkanMenuUtama() {
    bersihLayar();
    printf("==============================\n");
    printf("   DASHBOARD PERPUSTAKAAN\n");
    printf("==============================\n");
    printf("User Aktif: %s\n\n", currentUser);
    printf("[1] Lihat Daftar Buku\n");
    printf("[2] Pinjam Buku\n");
    printf("[3] Kembalikan Buku\n");
    printf("[4] Aturan & Denda\n");
    printf("[5] Logout\n");
    printf("\nPilih menu (1-5): ");
}

void lihatDaftarBuku() {
    bersihLayar();
    printf("===============================================================================\n");
    printf("                           KATALOG BUKU\n");
    printf("===============================================================================\n");
    printf("| No.| Kode | Judul Buku            | Penulis               | Status    |\n");
    printf("|====|======|=======================|=======================|===========|\n");

    if (jumlahBuku == 0) {
        printf("| Data buku kosong...                                                   |\n");
    } else {
        for (int i = 0; i < jumlahBuku; i++) {
            printf("| %-2d | %-4s | %-21s | %-21s | %-9s |\n",
                   (i + 1),
                   daftarBuku[i].kode,
                   daftarBuku[i].judul,
                   daftarBuku[i].penulis,
                   (daftarBuku[i].status == 0) ? "Tersedia" : "Dipinjam");
        }
    }
    printf("===============================================================================\n");
}

void lihatAturan() {
    bersihLayar();
    printf("=== ATURAN PERPUSTAKAAN ===\n\n");
    printf("1. Batas Peminjaman : %d hari\n", BATAS_PINJAM_HARI);
    printf("2. Denda Keterlambatan : Rp %d / hari\n", DENDA_PER_HARI);
    printf("3. Buku hilang wajib lapor admin.\n");
    tungguEnter();
}

//BAGIAN 4
void pinjamBuku() {
    char kodeBuku[10];
    int idBukuDitemukan = -1;
    char tglPinjamStr[20], tglKembaliStr[20];

    lihatDaftarBuku(); 
    
    printf("\n[INPUT] Masukkan Kode Buku: ");
    scanf("%s", kodeBuku);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].kode, kodeBuku) == 0) {
            idBukuDitemukan = i;
            break;
        }
    }
    if (idBukuDitemukan == -1) {
        printf("\n[ERROR] Buku dengan kode '%s' tidak ditemukan.\n", kodeBuku);
    } else if (daftarBuku[idBukuDitemukan].status == 1) {
        printf("\n[ERROR] Buku '%s' sedang dipinjam.\n", daftarBuku[idBukuDitemukan].judul);
    } else {
        daftarBuku[idBukuDitemukan].status = 1; 

        int idx = jumlahPinjam;
        daftarPinjam[idx].idBuku = daftarBuku[idBukuDitemukan].id;
        strcpy(daftarPinjam[idx].usernamePeminjam, currentUser);
        daftarPinjam[idx].waktuPinjam = time(NULL);
        daftarPinjam[idx].waktuKembali = daftarPinjam[idx].waktuPinjam + (BATAS_PINJAM_HARI * 24 * 60 * 60);
        daftarPinjam[idx].statusPinjam = 0;

        jumlahPinjam++;

        formatTanggal(daftarPinjam[idx].waktuPinjam, tglPinjamStr);
        formatTanggal(daftarPinjam[idx].waktuKembali, tglKembaliStr);

        bersihLayar(); 
        printf("    BUKTI PEMINJAMAN\n");
        printf("--------------------------\n");
        printf("Judul  : %s\n", daftarBuku[idBukuDitemukan].judul);
        printf("Tgl    : %s\n", tglPinjamStr);
        printf("Tempo  : %s\n", tglKembaliStr);
        printf("--------------------------\n");
        printf("Status : BERHASIL\n");
    }
    tungguEnter();
}

void kembalikanBuku() {
    char kodeBuku[10];
    int idBukuDiDaftar = -1;
    int idPinjam = -1;

    bersihLayar();
    printf("=== PENGEMBALIAN BUKU ===\n");
    printf("Kode Buku: "); scanf("%s", kodeBuku);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].kode, kodeBuku) == 0) {
            idBukuDiDaftar = i;
            break;
        }
    }

    if (idBukuDiDaftar == -1) {
        printf("\n[ERROR] Kode buku salah/tidak terdaftar.\n");
        tungguEnter();
        return;
    }

    for (int i = 0; i < jumlahPinjam; i++) {
        if (daftarPinjam[i].idBuku == daftarBuku[idBukuDiDaftar].id && 
            daftarPinjam[i].statusPinjam == 0) {
            idPinjam = i;
            break;
        }
    }

    if (idPinjam == -1) {
        printf("\n[INFO] Anda tidak sedang meminjam buku ini.\n");
    } else {
     
        daftarPinjam[idPinjam].statusPinjam = 1;
        daftarBuku[idBukuDiDaftar].status = 0;

        double selisih = difftime(time(NULL), daftarPinjam[idPinjam].waktuKembali);
        long denda = 0;
        int hariTelat = 0;

        if (selisih > 0) {
            hariTelat = (int)(selisih / (24 * 3600)) + 1;
            denda = hariTelat * DENDA_PER_HARI;
        }

        printf("\n--- RINGKASAN PENGEMBALIAN ---\n");
        printf("Judul      : %s\n", daftarBuku[idBukuDiDaftar].judul);
        if (denda > 0) {
            printf("Terlambat  : %d Hari\n", hariTelat);
            printf("Total Denda: Rp %ld\n", denda);
            printf("Silakan lakukan pembayaran denda di meja admin.\n");
        } else {
            printf("Status     : Tepat Waktu. Tidak ada denda.\n");
        }
    }
    tungguEnter();
}
int main() {
    inisialisasiDataBuku();
    if (login() == 0) {
        return 1;
    }
    int pilihan;
    do {
        tampilkanMenuUtama();
        scanf("%d", &pilihan);
        while (getchar() != '\n'); 

        switch (pilihan) {
            case 1:
                lihatDaftarBuku(); 
                tungguEnter();
                break;
            case 2:
                pinjamBuku();
                break;
            case 3:
                kembalikanBuku();
                break;
            case 4:
                lihatAturan();
                break;
            case 5:
                printf("\nLogout...\n");
                Sleep(1000);
                break;
            default:
                printf("\nPilihan tidak tersedia.\n");
                Sleep(1000);
        }
    } while (pilihan != 5);

    return 0;
}




