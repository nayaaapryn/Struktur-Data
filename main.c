#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "import.h"
#include "export.h"

#define KAPASITAS_MAKSIMUM 100

void tampilkanMenu();
void inputData(masakan **head, masakan **tail, int *jumlah);
void browseData(masakan *head, masakan *tail);
void bersihkanMemori(masakan **head, masakan **tail);

int main() {
    masakan *head = NULL;
    masakan *tail = NULL;
    int jumlah = 0;
    int pilihan;

    do {
        tampilkanMenu();
        printf("\033[1;36mPilihan Anda: \033[0m");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                inputData(&head, &tail, &jumlah);
                break;
            case 2:
                if (importData(&head, &tail, &jumlah, "SB.csv") == 0) {
                    printf("Gagal mengimpor data.\n");
                } else {
                    printf("Berhasil mengimpor data dari SB.csv.\n");
                }
                break;
            case 3:
                browseData(head, tail);
                break;
            case 4:
                if (eksporData(head, "data.csv") == 0) {
                    printf("Gagal mengekspor data.\n");
                } else {
                    printf("Data berhasil diekspor ke data.csv.\n");
                }
                break;
            case 9:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan salah. Silakan coba lagi.\n");
        }
    } while (pilihan != 9);

    bersihkanMemori(&head, &tail);
    return 0;
}

void tampilkanMenu() {
    printf("\nMenu:\n");
    printf("\033[1;36m[1]\033[0m Input Data Baru\n");
    printf("\033[1;36m[2]\033[0m Import Data dari CSV\n");
    printf("\033[1;36m[3]\033[0m Browse Data\033[0m\n");
    printf("\033[4;36m[4]\033[0m Ekspor Data ke CSV\n");
    printf("\033[9;36m[9] \033[0m Keluar Program\n");
}

void inputData(masakan **head, masakan **tail, int *jumlah) {
    char nama[100];
    int harga;
    char tanggal[11];

    printf("\nInput Data Baru:\n");
    printf("Nama Masakan: ");
    scanf(" %99[^\n]", nama);
    printf("Harga: ");
    scanf("%d", &harga);
    printf("Tanggal Produksi (dd-mm-yy): ");
    scanf("%s", tanggal);

    tambahData(head, tail, jumlah, nama, harga, tanggal);
}

void browseData(masakan *head, masakan *tail) {
    if (head == NULL) {
        printf("Tidak ada data untuk ditampilkan.\n");
        return;
    }

    masakan *current = head;
    char command;
    do {
        char hargaRupiah[20];
        formatRupiah(hargaRupiah, current->harga);
        printf("\nData Masakan:\n");
        printf("Nama: %s\n", current->nama);
        printf("Harga: %s\n", hargaRupiah);
        printf("Tanggal: %s\n", current->tanggal);

        printf("\nTekan 'N' untuk data berikutnya, 'P' untuk data sebelumnya, 'Q' untuk keluar: ");
        scanf(" %c", &command);

        if (command == 'N' || command == 'n') {
            current = (current->next != NULL) ? current->next : head;
        } else if (command == 'P' || command == 'p') {
            current = (current->prev != NULL) ? current->prev : tail;
        }
    } while (command != 'Q' && command != 'q');
}

void bersihkanMemori(masakan **head, masakan **tail) {
    masakan *current = *head;
    while (current != NULL) {
        masakan *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
    *tail = NULL;
}

void formatRupiah(char *hasil, int harga) {
    int ribuan = harga / 1000;
    int sisa = harga % 1000;
    sprintf(hasil, "Rp. %d.%03d", ribuan, sisa);
}