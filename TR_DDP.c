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

