#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Pasien pasien[PASIEN_MAX];
RiwayatMedis riwayat[RIWAYAT_MAX];
RekamMedisPasien rekam[PASIEN_MAX];
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

// Fungsi untuk mengecek apakah tanggal mengandung strip
bool cekAdaStrip(char tanggal[]) {
    return strchr(tanggal, '-') != NULL;
}

// ubah format tanggal dari (1-Apr-98) ke (1 April 1998)
void ubahKeTanpaStrip(char* tanggalStrip) {
    char newTanggal[100];
    char* segment;
    int day;
    char month[10];
    int year;
    
    // baca jadi 3 segment
    sscanf(tanggalStrip, "%d-%3s-%2d", &day, month, &year);

    // cek bulan
    if (strcmp(month, "Jan") == 0) {
        strcpy(month, "Januari");
    } else if (strcmp(month, "Feb") == 0) {
        strcpy(month, "Februari");
    } else if (strcmp(month, "Mar") == 0) {
        strcpy(month, "Maret");
    } else if (strcmp(month, "Apr") == 0) {
        strcpy(month, "April");
    } else if (strcmp(month, "May") == 0) {
        strcpy(month, "Mei");
    } else if (strcmp(month, "Jun") == 0) {
        strcpy(month, "Juni");
    } else if (strcmp(month, "Jul") == 0) {
        strcpy(month, "Juli");
    } else if (strcmp(month, "Aug") == 0) {
        strcpy(month, "Agustus");
    } else if (strcmp(month, "Sep") == 0) {
        strcpy(month, "September");
    } else if (strcmp(month, "Oct") == 0) {
        strcpy(month, "Oktober");
    } else if (strcmp(month, "Nov") == 0) {
        strcpy(month, "November");
    } else if (strcmp(month, "Dec") == 0) {
        strcpy(month, "Desember");
    }

    // ngegabung
    sprintf(newTanggal, "%d %s 20%02d", day, month, year);
    strcpy(tanggalStrip, newTanggal);
}