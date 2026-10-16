/*
 * Mini Project P4 - Pointer & Struct
 * Aplikasi CLI Minimarket & Membership
 *
 * Modifikasi dari TUTORIAL.md (Step 4):
 *   [Tantangan Wajib 1] void updateHarga(Barang *b, int hargaBaru)
 *   [Tantangan Wajib 2] void updateNama(Barang *b, char namaBaru[])
 *   [Tantangan Wajib 3] Diskon 10% + potong 1000 poin jika poin >= 1000
 *   [Tantangan Bonus ] Menu interaktif (while + switch-case, sampai "Keluar")
 */
#include <stdio.h>
#include <string.h>

typedef struct {
    char nama[50];
    int harga;
    int stock;
} Barang;

typedef struct {
    char nama[50];
    int poin;
} Member;

/* ---------- Fungsi Tampilan ---------- */
void cekBarang(Barang db[], int ukuran) {
    printf("\n--- Katalog Barang ---\n");
    for (int i = 0; i < ukuran; i++) {
        printf("%d. %s - Rp%d (Stok: %d)\n", i + 1, db[i].nama, db[i].harga, db[i].stock);
    }
}

void cekMember(Member db[], int ukuran) {
    printf("\n--- Data Member ---\n");
    for (int i = 0; i < ukuran; i++) {
        printf("%d. %s - Poin: %d\n", i + 1, db[i].nama, db[i].poin);
    }
}

/* ---------- Tantangan Wajib 1: Update Harga ---------- */
void updateHarga(Barang *b, int hargaBaru) {
    printf("[UPDATE HARGA] %s: Rp%d", b->nama, b->harga);
    b->harga = hargaBaru;   // reassignment lewat pointer -> merubah data asli
    printf(" -> Rp%d\n", b->harga);
}

/* ---------- Tantangan Wajib 2: Update Nama ---------- */
void updateNama(Barang *b, char namaBaru[]) {
    printf("[UPDATE NAMA] %s", b->nama);
    strcpy(b->nama, namaBaru);  // char array TIDAK BISA pakai =
    printf(" -> %s\n", b->nama);
}

/* ---------- Fungsi Transaksi (Pointer Beraksi!) ---------- */
void beliBarang(Barang *b, Member *m, int qty) {
    if (b->stock >= qty) {
        int total = b->harga * qty;

        /* Tantangan Wajib 3: Tukar poin = diskon 10% */
        if (m != NULL && m->poin >= 1000) {
            printf("  [DISKON] Poin %s mencukupi! Diskon 10%% dari Rp%d", m->nama, total);
            total = total - (total * 10 / 100);
            m->poin -= 1000;
            printf(" -> Rp%d (-1000 poin)\n", total);
        }

        b->stock -= qty;  // manipulasi memori asli via ->
        printf("\n[TRANSAKSI] %d %s Terjual. Total: Rp%d\n", qty, b->nama, total);

        /* Poin normal: belanja >= 20000 dapat +100 poin */
        if (total >= 20000 && m != NULL) {
            m->poin += 100;
            printf("  -> Member %s mendapat +100 Poin! (Total poin: %d)\n", m->nama, m->poin);
        }
    } else {
        printf("\n[GAGAL] Stok %s (Tersisa: %d) tidak cukup untuk dibeli sebanyak %d!\n",
               b->nama, b->stock, qty);
    }
}

int main() {
    /* 1. Setup Database */
    Barang dbBarang[5] = {
        {"Sabun", 5000, 10},
        {"Sampo", 15000, 5},
        {"Roti", 12000, 8},
        {"Susu", 25000, 15},
        {"Kopi", 22000, 20}
    };
    Member dbMember[2] = {
        {"Anisa", 500},
        {"Budi", 1000}   // Budi mulai dengan 1000 poin agar tantangan 3 bisa diuji
    };
    int pilihan, idx, qty, hargaBaru;
    char namaBaru[50];

    printf("=== SELAMAT DATANG DI MINIMARKET CLI ===\n");

    /* Tantangan Bonus: Menu interaktif (looping sampai pengguna keluar) */
    do {
        printf("\n+------------------------------------+\n");
        printf("| [1] Lihat Barang                  |\n");
        printf("| [2] Beli Barang                   |\n");
        printf("| [3] Lihat Member                  |\n");
        printf("| [4] Admin: Update Harga Barang    |\n");
        printf("| [5] Admin: Update Nama Barang     |\n");
        printf("| [6] Keluar                        |\n");
        printf("+------------------------------------+\n");
        printf("Pilihan kamu: ");
        if (scanf("%d", &pilihan) != 1) {
            // cegah infinite loop jika input bukan angka
            while (getchar() != '\n');
            printf("[ERROR] Input harus berupa angka!\n");
            continue;
        }

        switch (pilihan) {
            case 1:
                cekBarang(dbBarang, 5);
                break;

            case 2:
                cekBarang(dbBarang, 5);
                cekMember(dbMember, 2);
                printf("\nNomor barang (1-5): ");
                scanf("%d", &idx);
                printf("Jumlah: ");
                scanf("%d", &qty);
                if (idx < 1 || idx > 5) {
                    printf("[ERROR] Nomor barang tidak valid!\n");
                    break;
                }
                printf("Pakai member? [1] Anisa  [2] Budi  [0] Bukan member: ");
                int pilihMember;
                scanf("%d", &pilihMember);
                if (pilihMember == 1) {
                    // INGAT! & untuk mengirimkan alamat struct dalam array
                    beliBarang(&dbBarang[idx - 1], &dbMember[0], qty);
                } else if (pilihMember == 2) {
                    beliBarang(&dbBarang[idx - 1], &dbMember[1], qty);
                } else {
                    beliBarang(&dbBarang[idx - 1], NULL, qty);
                }
                break;

            case 3:
                cekMember(dbMember, 2);
                break;

            case 4:  // Tantangan Wajib 1
                cekBarang(dbBarang, 5);
                printf("\nNomor barang (1-5): ");
                scanf("%d", &idx);
                if (idx < 1 || idx > 5) {
                    printf("[ERROR] Nomor barang tidak valid!\n");
                    break;
                }
                printf("Harga baru: Rp");
                scanf("%d", &hargaBaru);
                updateHarga(&dbBarang[idx - 1], hargaBaru);
                break;

            case 5:  // Tantangan Wajib 2
                cekBarang(dbBarang, 5);
                printf("\nNomor barang (1-5): ");
                scanf("%d", &idx);
                if (idx < 1 || idx > 5) {
                    printf("[ERROR] Nomor barang tidak valid!\n");
                    break;
                }
                printf("Nama baru: ");
                scanf("%s", namaBaru);
                updateNama(&dbBarang[idx - 1], namaBaru);
                break;

            case 6:
                printf("\nTerima kasih sudah belanja!\n");
                break;

            default:
                printf("[ERROR] Pilihan tidak ada di menu!\n");
        }
    } while (pilihan != 6);

    /* Buktikan data termodifikasi setelah sesi berakhir */
    printf("\n=== UPDATE DATA SETELAH SESI ===");
    cekBarang(dbBarang, 5);
    cekMember(dbMember, 2);

    return 0;
}
