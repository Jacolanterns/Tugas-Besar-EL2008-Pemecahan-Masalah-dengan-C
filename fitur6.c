#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include "definisiFungsi.c"

#define PASIEN_MAX 100
#define RIWAYAT_MAX 100

// typedef struct {
//     int id;
//     char nama[50];
//     char alamat[100];
//     char kota[100];
//     char tempat_lahir[100];
//     char tanggal_lahir[50];
//     int umur;
//     char no_bpjs[20];
//     char id_pasien[10];
// } Pasien;

// typedef struct {
//     int id;
//     char tanggal[50];
//     char id_pasien[10];
//     char diagnosis[100];
//     char tindakan[100];
//     char tanggal_kontrol[50];
//     int biaya;
// } RiwayatMedis;

// Pasien pasien[PASIEN_MAX];
// RiwayatMedis riwayat[RIWAYAT_MAX];
// int jumlah_pasien = 0;
// int jumlah_riwayat = 0;

// bool cekAdaStrip(char tanggal[50]){
//     int i=0;
//     for(i=0;i<11;i++){
//         if('-' == tanggal[i]){
//             return true;
//         }
//     }
//     return false;
// }

// void ubahKeTanpaStrip(char* tanggalStrip) {
//     char newTanggal[100];
//     int day;
//     char month[10];
//     int year;
    
// // ubah format tanggal dari (1-Apr-98) ke (1 April 1998)
// void ubahKeTanpaStrip(char* tanggalStrip) {
//     char newTanggal[100];
//     char* segment;
//     int day;
//     char month[10];
//     int year;
    
//     // baca jadi 3 segment
//     sscanf(tanggalStrip, "%d-%3s-%2d", &day, month, &year);

//     // cek bulan
//     if (strcmp(month, "Jan") == 0) {
//         strcpy(month, "Januari");
//     } else if (strcmp(month, "Feb") == 0) {
//         strcpy(month, "Februari");
//     } else if (strcmp(month, "Mar") == 0) {
//         strcpy(month, "Maret");
//     } else if (strcmp(month, "Apr") == 0) {
//         strcpy(month, "April");
//     } else if (strcmp(month, "May") == 0) {
//         strcpy(month, "Mei");
//     } else if (strcmp(month, "Jun") == 0) {
//         strcpy(month, "Juni");
//     } else if (strcmp(month, "Jul") == 0) {
//         strcpy(month, "Juli");
//     } else if (strcmp(month, "Aug") == 0) {
//         strcpy(month, "Agustus");
//     } else if (strcmp(month, "Sep") == 0) {
//         strcpy(month, "September");
//     } else if (strcmp(month, "Oct") == 0) {
//         strcpy(month, "Oktober");
//     } else if (strcmp(month, "Nov") == 0) {
//         strcpy(month, "November");
//     } else if (strcmp(month, "Dec") == 0) {
//         strcpy(month, "Desember");
//     }

//     // ngegabung
//     sprintf(newTanggal, "%d %s 20%02d", day, month, year);
//     strcpy(tanggalStrip, newTanggal);
// }

void informasiKontrolPasien() {
    bool found = false;
    printf("Masukkan tanggal kontrol (DD-MMM-YY): ");
    char inputTanggalKontrol[100];
    scanf(" %[^\n]", inputTanggalKontrol);

    if(cekAdaStrip(inputTanggalKontrol)){
        ubahKeTanpaStrip(inputTanggalKontrol);
    }

    int indexPasien;
    char temp[255];
    int count=0;

    for(int i=0; i<jumlah_riwayat; i++){
        if(cekAdaStrip(riwayat[i].tanggal_kontrol)){
            ubahKeTanpaStrip(riwayat[i].tanggal_kontrol);
        }
        strcpy(temp, riwayat[i].id_pasien);
        temp[10] = '\0';
        indexPasien = cariPasienID(temp);

        //printf("%s ... %s\n", riwayat[i].tanggal_kontrol, inputTanggalKontrol);
        if(strcmp(riwayat[i].tanggal_kontrol, inputTanggalKontrol) == 0){
            found = true;
            count++;
            printf("Pada tanggal %s, pasien ke-%d yang perlu kontrol adalah\nNama: %s\nUmur: %d\nDiagnosis: %s\nTindakan: %s\nBiaya: %d\nAlamat: %s\n\n",
            inputTanggalKontrol, count, pasien[indexPasien].nama, pasien[indexPasien].umur, 
            riwayat[i].diagnosis, riwayat[i].tindakan, riwayat[i].biaya, pasien[indexPasien].alamat);
        }
    }

    if (!found) {
        printf("Tidak ada pasien yang perlu kembali kontrol.\n");
    }
}

int main() {
    // Baca data dari file CSV
    readPasienFromCSV("DataPMC20232024.csv");
    readRiwayatMedisFromCSV("Riwayat_Datang_Pasien.csv");

    informasiKontrolPasien();

    return 0;
}