#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PASIEN_MAX 100
#define RIWAYAT_MAX 100

typedef struct {
    int id;
    char nama[50];
    char alamat[100];
    char kota[100];
    char tempat_lahir[100];
    char tanggal_lahir[50];
    int umur;
    char no_bpjs[20];
    char id_pasien[10];
} Pasien;

typedef struct {
    int id;
    char tanggal[50];
    char id_pasien[10];
    char diagnosis[100];
    char tindakan[100];
    char tanggal_kontrol[50];
    int biaya;
} RiwayatMedis;

Pasien pasien[PASIEN_MAX];
RiwayatMedis riwayat[RIWAYAT_MAX];
int jumlah_pasien = 0;
int jumlah_riwayat = 0;

void tambahPasien(char* id, char* nama) {
    if (jumlah_pasien < PASIEN_MAX) {
        strcpy(pasien[jumlah_pasien].id_pasien, id);
        strcpy(pasien[jumlah_pasien].nama, nama);
        jumlah_pasien++;
    } else {
        printf("Kapasitas data pasien sudah penuh.\n");
    }
}

void tambahRiwayat(char* tanggal, char* id_pasien) {
    if (jumlah_riwayat < RIWAYAT_MAX) {
        strcpy(riwayat[jumlah_riwayat].tanggal, tanggal);
        strcpy(riwayat[jumlah_riwayat].id_pasien, id_pasien);
        jumlah_riwayat++;
    } else {
        printf("Kapasitas data riwayat medis sudah penuh.\n");
    }
}

void informasiKontrolPasien() {
    bool found = false;
    printf("Pasien yang perlu kembali untuk kontrol:\n");
    for (int i = 0; i < jumlah_riwayat; i++) {
        if (strcmp(riwayat[i].tanggal_kontrol, "") != 0) {
            for (int j = 0; j < jumlah_pasien; j++) {
                if (strcmp(riwayat[i].id_pasien, pasien[j].id_pasien) == 0) {
                    printf("ID Pasien: %s\n", pasien[j].id_pasien);
                    printf("Nama: %s\n", pasien[j].nama);
                    printf("Tanggal Kontrol: %s\n", riwayat[i].tanggal_kontrol);
                    printf("---------------------------\n");
                    found = true;
                    break;
                }
            }
        }
    }
    if (!found) {
        printf("Tidak ada pasien yang perlu kembali kontrol.\n");
    }
}

void bacaDataPasien(const char* namaFile) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        perror("Tidak bisa membuka file pasien");
        return;
    }
    char baris[200];
    while (fgets(baris, sizeof(baris), file)) {
        char id[20], nama[100];
        sscanf(baris, "%[^,],%[^\n]", id, nama);
        tambahPasien(id, nama);
    }
    fclose(file);
}

void bacaDataRiwayat(const char* namaFile) {
    FILE* file = fopen(namaFile, "r");
    if (file == NULL) {
        perror("Tidak bisa membuka file riwayat");
        return;
    }
    char baris[200];
    while (fgets(baris, sizeof(baris), file)) {
        char tanggal[20], id_pasien[20];
        sscanf(baris, "%[^,],%[^\n]", tanggal, id_pasien);
        tambahRiwayat(tanggal, id_pasien);
    }
    fclose(file);
}

int main() {
    // Baca data dari file CSV
    bacaDataPasien("DataPMC20232024.csv");
    bacaDataRiwayat("Riwayat_Datang_Pasien.csv");

    // Tampilkan informasi kontrol pasien
    informasiKontrolPasien();

    return 0;
}
