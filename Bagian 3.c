// BAGIAN 3: USER INTERFACE & DATA INIT
// Dikerjakan oleh: ANGGOTA C
// Tugas: Menyiapkan data awal buku, Tampilan Menu, dan Tampilan Tabel
// ============================================================================

void inisialisasiDataBuku() {
    // Data Dummy untuk testing
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
    // Fungsi ini tidak memanggil tungguEnter() di sini agar bisa dipakai ulang oleh fungsi Pinjam
}

void lihatAturan() {
    bersihLayar();
    printf("=== ATURAN PERPUSTAKAAN ===\n\n");
    printf("1. Batas Peminjaman : %d hari\n", BATAS_PINJAM_HARI);
    printf("2. Denda Keterlambatan : Rp %d / hari\n", DENDA_PER_HARI);
    printf("3. Buku hilang wajib lapor admin.\n");
    tungguEnter();
}
