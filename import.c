#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "import.h"

void tambahData(masakan **head, masakan **tail, int *jumlah, const char *nama, int harga, const char *tanggal) {
    masakan *nodeBaru = (masakan *)malloc(sizeof(masakan));
    if (nodeBaru == NULL) {
        printf("Error: Alokasi memori gagal!\n");
        return;
    }

    strcpy(nodeBaru->nama, nama);
    nodeBaru->harga = harga;
    strcpy(nodeBaru->tanggal, tanggal);
    nodeBaru->next = NULL;
    nodeBaru->prev = NULL;

    if (*head == NULL) {
        *head = nodeBaru;
        *tail = nodeBaru;
    } else {
        (*tail)->next = nodeBaru;
        nodeBaru->prev = *tail;
        *tail = nodeBaru;
    }
    (*jumlah)++;
}

int importData(masakan **head, masakan **tail, int *jumlah, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File tidak ditemukan!\n");
        return 0;
    }

    char baris[250];
    while (fgets(baris, sizeof(baris), file)) {
        char *token = strtok(baris, ",");
        char nama[100];
        strcpy(nama, token);

        token = strtok(NULL, ",");
        int harga = atoi(token);

        token = strtok(NULL, ",");
        token[strcspn(token, "\n")] = '\0';
        char tanggal[11];
        strcpy(tanggal, token);

        tambahData(head, tail, jumlah, nama, harga, tanggal);
    }
    fclose(file);
    return 1;
}