#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

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
    for (int i = 0; i < 30; i++) {
        printf("%c", 219);
        Sleep(70);
    }
    printf("\n\nLogin Berhasil!\n");
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
        printf("   LOGIN SISTEM PERPUSTAKAAN\n");
        printf("==============================\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            strcpy(currentUser, username);
            loading();
            return 1;
        } else {
            printf("\nUsername atau password salah.\n");
            percobaan++;
            Sleep(1500);
        }
    }
    printf("\nAnda telah gagal login 3 kali. Program berhenti.\n");
    return 0;
}

void inisialisasiDataBuku() {
    daftarBuku[0].id = 1;
    strcpy(daftarBuku[0].kode, "C001");
    strcpy(daftarBuku[0].judul, "Dasar Pemrograman C");
    strcpy(daftarBuku[0].penulis, "Budi Raharjo");
    daftarBuku[0].status = 0;

    daftarBuku[1].id = 2;
    strcpy(daftarBuku[1].kode, "M002");
    strcpy(daftarBuku[1].judul, "Matematika Diskrit");
    strcpy(daftarBuku[1].penulis, "Rinaldi Munir");
    daftarBuku[1].status = 0;

    daftarBuku[2].id = 3;
    strcpy(daftarBuku[2].kode, "D003");
    strcpy(daftarBuku[2].judul, "Sistem Basis Data");
    strcpy(daftarBuku[2].penulis, "Fathansyah");
    daftarBuku[2].status = 0;

    daftarBuku[3].id = 4;
    strcpy(daftarBuku[3].kode, "A004");
    strcpy(daftarBuku[3].judul, "Struktur Data");
    strcpy(daftarBuku[3].penulis, "Abdul Kadir");
    daftarBuku[3].status = 0;

    jumlahBuku = 4;
}

void tampilkanMenuUtama() {
    bersihLayar();
    printf("==============================\n");
    printf("   SISTEM PERPUSTAKAAN FTI\n");
    printf("==============================\n");
    printf("Selamat datang, %s!\n\n", currentUser);
    printf("Menu Utama:\n");
    printf("1. Lihat Daftar Buku\n");
    printf("2. Pinjam Buku\n");
    printf("3. Kembalikan Buku\n");
    printf("4. Lihat Aturan & Denda\n");
    printf("5. Logout\n");
    printf("\nMasukkan Pilihan Anda (1-5): ");
}

void lihatDaftarBuku() {
    bersihLayar();
    printf("=========================================================================\n");
    printf("                          DAFTAR BUKU PERPUSTAKAAN\n");
    printf("=========================================================================\n");
    printf("| No.| Kode | Judul Buku\t    | Penulis\t\t    | Status    |\n");
    printf("|====|======|=======================|=======================|===========|\n");

    if (jumlahBuku == 0) {
        printf("| Tidak ada data buku...                                                    |\n");
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
    printf("=========================================================================\n");
    tungguEnter();
}

void pinjamBuku() {
    char kodeBuku[10];
    int idBukuDitemukan = -1;
    char tglPinjamStr[20], tglKembaliStr[20];

    bersihLayar();
    printf("=== PINJAM BUKU ===\n");
    printf("=========================================================================\n");
    printf("| No.| Kode | Judul Buku\t    | Penulis\t\t    | Status    |\n");
    printf("|====|======|=======================|=======================|===========|\n");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("| %-2d | %-4s | %-21s | %-21s | %-9s |\n",
                (i + 1),
                daftarBuku[i].kode,
                daftarBuku[i].judul,
                daftarBuku[i].penulis,
                (daftarBuku[i].status == 0) ? "Tersedia" : "Dipinjam");
    }
    printf("=========================================================================\n");


    printf("\nMasukkan Kode Buku yang ingin dipinjam: ");
    scanf("%s", kodeBuku);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].kode, kodeBuku) == 0) {
            idBukuDitemukan = i;
            break;
        }
    }

    if (idBukuDitemukan == -1) {
        printf("\nError: Buku dengan kode '%s' tidak ditemukan.\n", kodeBuku);
    } else if (daftarBuku[idBukuDitemukan].status == 1) {
        printf("\nError: Buku '%s' sedang dipinjam.\n", daftarBuku[idBukuDitemukan].judul);
    } else {
        daftarBuku[idBukuDitemukan].status = 1;

        int i = jumlahPinjam;
        daftarPinjam[i].idBuku = daftarBuku[idBukuDitemukan].id;
        strcpy(daftarPinjam[i].usernamePeminjam, currentUser);
        daftarPinjam[i].waktuPinjam = time(NULL);
        daftarPinjam[i].waktuKembali = daftarPinjam[i].waktuPinjam + (BATAS_PINJAM_HARI * 24 * 60 * 60);
        daftarPinjam[i].statusPinjam = 0;

        jumlahPinjam++;

        formatTanggal(daftarPinjam[i].waktuPinjam, tglPinjamStr);
        formatTanggal(daftarPinjam[i].waktuKembali, tglKembaliStr);

        bersihLayar(); 
        printf("===========================================\n");
        printf("            RESI PEMINJAMAN BUKU\n");
        printf("===========================================\n");
        printf("  Peminjam   : %s\n", currentUser);
        printf("  Kode Buku  : %s\n", daftarBuku[idBukuDitemukan].kode);
        printf("  Judul Buku : %s\n", daftarBuku[idBukuDitemukan].judul);
        printf("  ---------------------------------------\n");
        printf("  Tgl Pinjam : %s\n", tglPinjamStr);
        printf("  Batas Tgl  : %s\n", tglKembaliStr);
        printf("  ---------------------------------------\n");
        printf("\n  Harap kembalikan buku tepat waktu.\n");
        printf("  Terima kasih!\n");
        printf("===========================================\n");
    }

    tungguEnter();
}

void kembalikanBuku() {
    char kodeBuku[10];
    int idBukuDiDaftar = -1;
    int idPinjamDitemukan = -1;

    bersihLayar();
    printf("=== KEMBALIKAN BUKU ===\n");
    printf("Masukkan Kode Buku yang ingin dikembalikan: ");
    scanf("%s", kodeBuku);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].kode, kodeBuku) == 0) {
            idBukuDiDaftar = i;
            break;
        }
    }

    if (idBukuDiDaftar == -1) {
        printf("\nError: Buku dengan kode '%s' tidak terdaftar.\n", kodeBuku);
        tungguEnter();
        return;
    }

    for (int i = 0; i < jumlahPinjam; i++) {
        if (daftarPinjam[i].idBuku == daftarBuku[idBukuDiDaftar].id &&
            daftarPinjam[i].statusPinjam == 0) {
            idPinjamDitemukan = i;
            break;
        }
    }

    if (idPinjamDitemukan == -1) {
        printf("\nError: Anda tidak sedang meminjam buku ini.\n");
    } else {

        daftarPinjam[idPinjamDitemukan].statusPinjam = 1;
        daftarBuku[idBukuDiDaftar].status = 0;

        time_t waktuSekarang = time(NULL);
        double selisihDetik = difftime(waktuSekarang, daftarPinjam[idPinjamDitemukan].waktuKembali);
        int hariTerlambat = 0;
        long totalDenda = 0;

        if (selisihDetik > 0) {
            hariTerlambat = (selisihDetik / (60 * 60 * 24)) + 1;
            totalDenda = hariTerlambat * DENDA_PER_HARI;
        }

        printf("\n--- BUKU BERHASIL DIKEMBALIKAN ---\n");
        printf("Judul: %s\n", daftarBuku[idBukuDiDaftar].judul);
        if (totalDenda > 0) {
            printf("Keterlambatan: %d hari\n", hariTerlambat);
            printf("Total Denda  : Rp %ld\n", totalDenda);
            printf("Silakan lakukan pembayaran denda di meja admin.\n");
        } else {
            printf("Pengembalian tepat waktu. Tidak ada denda.\n");
        }
    }
    tungguEnter();
}

void lihatAturan() {
    bersihLayar();
    printf("========================================================\n");
    printf("                  ATURAN & KETENTUAN\n");
    printf("========================================================\n");
    printf("1. Mahasiswa wajib memiliki akun untuk login.\n");
    printf("2. Batas maksimal peminjaman buku adalah %d hari.\n", BATAS_PINJAM_HARI);
    printf("3. Keterlambatan pengembalian akan dikenakan denda.\n");
    printf("4. Denda per hari adalah: Rp %d.\n", DENDA_PER_HARI);
    printf("5. Jaga kondisi buku yang dipinjam.\n");
    printf("6. Buku yang hilang wajib diganti dengan buku yang sama.\n");
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
                bersihLayar();
                printf("Logout berhasil. Terima kasih telah menggunakan sistem ini!\n");
                Sleep(2000);
                break;
            default:
                printf("\nPilihan tidak valid. Silakan masukkan angka 1-5.\n");
                Sleep(1500);
        }

    } while (pilihan != 5);

    return 0;
}
