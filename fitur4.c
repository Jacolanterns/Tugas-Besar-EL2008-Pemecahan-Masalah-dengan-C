#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include "definisiFungsi.c"

#define MAX_PASIEN 1000

// Struktur untuk menyimpan tanggal
// typedef struct {
//     int hari;
//     int bulan;
//     int tahun;
// } Tanggal;

// Struktur untuk menyimpan rekam medis pasien
// typedef struct {
//     char id[20];
//     Tanggal tanggalKunjungan;
//     char diagnosis[50];
//     char tindakan[50];
//     Tanggal tanggalKontrol;
//     int biaya;
// } RekamMedisPasien;

// Deklarasi fungsi
int muatRekamMedisPasien(RekamMedisPasien rekam[], const char *namaFile);
void hitungPendapatanBulananDanTahunan(RekamMedisPasien rekam[], int jumlahRekam);
int bulanKeInt(char *bulan);
//void ubahKeTanpaStrip(char *tanggalStrip);
//bool cekAdaStrip(char tanggal[]);

// Fungsi utama
int main() {
    // RekamMedisPasien rekam[MAX_PASIEN];
    int jumlahRekam = muatRekamMedisPasien(rekam, "Riwayat_Datang_Pasien.csv");

    hitungPendapatanBulananDanTahunan(rekam, jumlahRekam);

    return 0;
}

// Fungsi untuk memuat rekam medis pasien dari file
int muatRekamMedisPasien(RekamMedisPasien rekam[], const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        perror("Gagal membuka file");
        exit(EXIT_FAILURE);
    }

    char baris[200];
    // int jumlah = 0;

    // Melewati header
    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file) && jumlah < MAX_PASIEN) {
        char tanggal[20], tanggalKontrol[20], bulan[10];
        sscanf(baris, "%*d,%19[^,],%19[^,],%49[^,],%49[^,],%19[^,],%d", tanggal, rekam[jumlah].id, rekam[jumlah].diagnosis, rekam[jumlah].tindakan, tanggalKontrol, &rekam[jumlah].biaya);

        // Mengubah format tanggal jika ada strip
        if (cekAdaStrip(tanggal)) {
            ubahKeTanpaStrip(tanggal);
        }
        sscanf(tanggal, "%d %s %d", &rekam[jumlah].tanggalKunjungan.hari, bulan, &rekam[jumlah].tanggalKunjungan.tahun);
        rekam[jumlah].tanggalKunjungan.bulan = bulanKeInt(bulan);

        if (cekAdaStrip(tanggalKontrol)) {
            ubahKeTanpaStrip(tanggalKontrol);
        }
        sscanf(tanggalKontrol, "%d %s %d", &rekam[jumlah].tanggalKontrol.hari, bulan, &rekam[jumlah].tanggalKontrol.tahun);
        rekam[jumlah].tanggalKontrol.bulan = bulanKeInt(bulan);

        jumlah++;
    }

    fclose(file);
    return jumlah;
}

// Fungsi untuk mengecek apakah tanggal mengandung strip
// bool cekAdaStrip(char tanggal[]) {
//     return strchr(tanggal, '-') != NULL;
// }

// Fungsi untuk mengubah tanggal dengan strip ke format tanpa strip
// void ubahKeTanpaStrip(char *tanggalStrip) {
//     char newTanggal[100];
//     char bulan[10];
//     int hari, tahun;

//     // Mengurai string tanggal menjadi hari, bulan, dan tahun
//     sscanf(tanggalStrip, "%d-%3s-%2d", &hari, bulan, &tahun);

//     if (strcmp(bulan, "Jan") == 0) {
//         strcpy(bulan, "Januari");
//     } else if (strcmp(bulan, "Feb") == 0) {
//         strcpy(bulan, "Februari");
//     } else if (strcmp(bulan, "Mar") == 0) {
//         strcpy(bulan, "Maret");
//     } else if (strcmp(bulan, "Apr") == 0) {
//         strcpy(bulan, "April");
//     } else if (strcmp(bulan, "May") == 0) {
//         strcpy(bulan, "Mei");
//     } else if (strcmp(bulan, "Jun") == 0) {
//         strcpy(bulan, "Juni");
//     } else if (strcmp(bulan, "Jul") == 0) {
//         strcpy(bulan, "Juli");
//     } else if (strcmp(bulan, "Aug") == 0) {
//         strcpy(bulan, "Agustus");
//     } else if (strcmp(bulan, "Sep") == 0) {
//         strcpy(bulan, "September");
//     } else if (strcmp(bulan, "Oct") == 0) {
//         strcpy(bulan, "Oktober");
//     } else if (strcmp(bulan, "Nov") == 0) {
//         strcpy(bulan, "November");
//     } else if (strcmp(bulan, "Dec") == 0) {
//         strcpy(bulan, "Desember");
//     }

//     // Menggabungkan hari, bulan, dan tahun ke string baru
//     sprintf(newTanggal, "%d %s 20%02d", hari, bulan, tahun);

//     // Menyalin string baru kembali ke tanggalStrip
//     strcpy(tanggalStrip, newTanggal);
// }

// Fungsi untuk mengubah bulan dalam string ke integer
int bulanKeInt(char *bulan) {
    if (strcmp(bulan, "Januari") == 0) return 1;
    if (strcmp(bulan, "Februari") == 0) return 2;
    if (strcmp(bulan, "Maret") == 0) return 3;
    if (strcmp(bulan, "April") == 0) return 4;
    if (strcmp(bulan, "Mei") == 0) return 5;
    if (strcmp(bulan, "Juni") == 0) return 6;
    if (strcmp(bulan, "Juli") == 0) return 7;
    if (strcmp(bulan, "Agustus") == 0) return 8;
    if (strcmp(bulan, "September") == 0) return 9;
    if (strcmp(bulan, "Oktober") == 0) return 10;
    if (strcmp(bulan, "November") == 0) return 11;
    if (strcmp(bulan, "Desember") == 0) return 12;
    return 0;
}

// Fungsi untuk menghitung pendapatan bulanan dan tahunan
void hitungPendapatanBulananDanTahunan(RekamMedisPasien rekam[], int jumlahRekam) {
    int pendapatanTahunan[MAX_TAHUN] = {0};
    int pendapatanBulanan[MAX_TAHUN][12] = {{0}};
    int tahun[MAX_TAHUN];
    int jumlahTahun = 0;

    for (int i = 0; i < jumlahRekam; i++) {
        int tahunKunjungan = rekam[i].tanggalKunjungan.tahun;
        int bulanKunjungan = rekam[i].tanggalKunjungan.bulan;
        int biaya = rekam[i].biaya;

        // Validasi tahun dan bulan
        if (tahunKunjungan < 2000 || bulanKunjungan < 1 || bulanKunjungan > 12) {
            printf("Data tidak valid ditemukan: %d-%d-%d\n", rekam[i].tanggalKunjungan.hari, bulanKunjungan, tahunKunjungan);
            continue;
        }

        // Mencari indeks untuk tahun
        int indeksTahun = -1;
        for (int j = 0; j < jumlahTahun; j++) {
            if (tahun[j] == tahunKunjungan) {
                indeksTahun = j;
                break;
            }
        }

        // Jika tahun tidak ditemukan, tambahkan ke daftar
        if (indeksTahun == -1) {
            indeksTahun = jumlahTahun;
            tahun[jumlahTahun++] = tahunKunjungan;
        }

        // Tambahkan biaya ke bulan dan tahun yang sesuai
        pendapatanBulanan[indeksTahun][bulanKunjungan - 1] += biaya;
        pendapatanTahunan[indeksTahun] += biaya;
    }

    // Cetak hasil
    for (int i = 0; i < jumlahTahun; i++) {
        printf("Pendapatan Bulanan %d\n", tahun[i]);
        for (int j = 0; j < 12; j++) {
            printf("%s: %d\n", (char*[]){ "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember" }[j], pendapatanBulanan[i][j]);
        }
        printf("Pendapatan Tahunan %d: %d\n", tahun[i], pendapatanTahunan[i]);
        printf("\n");
    }
}