#ifndef data_h
#define data_h

typedef struct masakan {
    char nama[100];
    int harga;
    char tanggal[11];
    struct masakan *next; 
    struct masakan *prev;
} masakan;

void tambahData(masakan **head, masakan **tail, int *jumlah, const char *nama, int harga, const char *tanggal);
void hapusSemuaData(masakan **head, masakan **tail);
void formatRupiah(char *hasil, int harga);

#endif
