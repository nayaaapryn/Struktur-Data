#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "export.h"

int eksporData(masakan *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Gagal membuat file output!\n");
        return 0;
    }

    masakan *current = head;
    while (current != NULL) {
        fprintf(file, "%s, %d, %s\n", current->nama, current->harga, current->tanggal);
        current = current->next;
    }
    fclose(file);
    return 1;
}