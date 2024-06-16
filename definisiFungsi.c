#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Pasien pasien[PASIEN_MAX];
RiwayatMedis riwayat[RIWAYAT_MAX];
int jumlah_pasien = 0;
int jumlah_riwayat = 0;

// Fungsi untuk membaca dan memparsing data pasien dari file CSV
void readPasienFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Pasien p;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,\n]",
               &p.id, p.nama, p.alamat, p.kota, p.tempat_lahir, p.tanggal_lahir,
               &p.umur, p.no_bpjs, p.id_pasien);
        pasien[jumlah_pasien++] = p;
    }
    fclose(file);
}

// Fungsi untuk membaca dan memparsing data riwayat medis dari file CSV
void readRiwayatMedisFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        RiwayatMedis r;
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
               &r.id, r.tanggal, r.id_pasien, r.diagnosis, r.tindakan, r.tanggal_kontrol, &r.biaya);
        riwayat[jumlah_riwayat++] = r;
    }
    fclose(file);
}

// Mencari pasien berdasarkan ID Pasien
int cariPasienID(const char* id_pasien) {
    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].id_pasien, id_pasien) == 0) {
            return i;
        }
    }
    return -1;
}