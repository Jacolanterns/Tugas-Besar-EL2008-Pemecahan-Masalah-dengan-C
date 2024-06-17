#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"
#include "definisiFungsi.c"
// #define MAX_RECORDS 1000
// #define MAX_STRING 50
// #define PASIEN_MAX 100
// #define RIWAYAT_MAX 100

// typedef struct {
//     char tanggal[MAX_STRING];
//     char idPasien[MAX_STRING];
//     char diagnosis[MAX_STRING];
//     char tindakan[MAX_STRING];
//     char tindakLanjut[MAX_STRING];
//     int biaya;
// } RekamMedis;

// typedef struct {
//     int bulan;
//     int tahun;
//     char diagnosis[MAX_STRING];
//     int jumlah;
// } JumlahDiagnosisBulanan;

// typedef struct {
//     int tahun;
//     char diagnosis[MAX_STRING];
//     int jumlah;
// } JumlahDiagnosisTahunan;

// typedef struct {
//     int id;
//     char nama[MAX_STRING];
//     char alamat[MAX_STRING];
//     char kota[MAX_STRING];
//     char tempat_lahir[MAX_STRING];
//     char tanggal_lahir[MAX_STRING];
//     int umur;
//     char no_bpjs[MAX_STRING];
//     char id_pasien[MAX_STRING];
// } Pasien;   // Sama kayak justin

// typedef struct {
//     int id;
//     char tanggal[MAX_STRING];
//     char id_pasien[MAX_STRING];
//     char diagnosis[MAX_STRING];
//     char tindakan[MAX_STRING];
//     char tanggal_kontrol[MAX_STRING];
//     int biaya;
// } RiwayatMedis; // sama kayak justin

// Pasien pasien[PASIEN_MAX];  // sama kayak di definisiFungsi.c
// RiwayatMedis riwayat[RIWAYAT_MAX]; // sama kayak di definisiFungsi.c
// int jumlah_pasien = 0; // sama kayak di definisiFungsi.c
// int jumlah_riwayat = 0; // sama kayak di definisiFungsi.c

void parseRekamMedis(char* line, RekamMedis* rekam) {
    char* token = strtok(line, ",");
    int kolom = 0;

    while (token != NULL) {
        switch (kolom) {
            case 0: // Skip No
                break;
            case 1:
                strcpy(rekam->tanggal, token);
                break;
            case 2:
                strcpy(rekam->idPasien, token);
                break;
            case 3:
                strcpy(rekam->diagnosis, token);
                break;
            case 4:
                strcpy(rekam->tindakan, token);
                break;
            case 5:
                strcpy(rekam->tindakLanjut, token);
                break;
            case 6:
                rekam->biaya = atoi(token);
                break;
        }
        token = strtok(NULL, ",");
        kolom++;
    }
}

int namaBulanDanTahun(const char* tanggal, int* bulan, int* tahun) {
    char buffer[MAX_STRING];
    strcpy(buffer, tanggal);
    char* token = strtok(buffer, " -/");

    if (token == NULL) return 0;

    // Check if month is in "dd Month yyyy" format
    if (strchr(tanggal, ' ') != NULL) {
        // Format "dd Month yyyy"
        char day[MAX_STRING];
        char monthStr[MAX_STRING];
        char yearStr[MAX_STRING];
        sscanf(tanggal, "%s %s %s", day, monthStr, yearStr);

        if (strcmp(monthStr, "Januari") == 0) *bulan = 1;
        else if (strcmp(monthStr, "Februari") == 0) *bulan = 2;
        else if (strcmp(monthStr, "Maret") == 0) *bulan = 3;
        else if (strcmp(monthStr, "April") == 0) *bulan = 4;
        else if (strcmp(monthStr, "Mei") == 0) *bulan = 5;
        else if (strcmp(monthStr, "Juni") == 0) *bulan = 6;
        else if (strcmp(monthStr, "Juli") == 0) *bulan = 7;
        else if (strcmp(monthStr, "Agustus") == 0) *bulan = 8;
        else if (strcmp(monthStr, "September") == 0) *bulan = 9;
        else if (strcmp(monthStr, "Oktober") == 0) *bulan = 10;
        else if (strcmp(monthStr, "November") == 0) *bulan = 11;
        else if (strcmp(monthStr, "Desember") == 0) *bulan = 12;
        else *bulan = 0;

        *tahun = atoi(yearStr);
    } else { //4-Jan-22
        char tanggal2[255] = {0};
        strcpy(tanggal2, tanggal);
        ubahKeTanpaStrip(tanggal2);
        char* iterate = strtok(tanggal2, " ");
        iterate = strtok(NULL, " ");
        // printf("iterate1: %s\n", iterate);
        if (strcmp(iterate, "Januari") == 0) *bulan = 1;
        else if (strcmp(iterate, "Februari") == 0) *bulan = 2;
        else if (strcmp(iterate, "Maret") == 0) *bulan = 3;
        else if (strcmp(iterate, "April") == 0) *bulan = 4;
        else if (strcmp(iterate, "Mei") == 0) *bulan = 5;
        else if (strcmp(iterate, "Juni") == 0) *bulan = 6;
        else if (strcmp(iterate, "Juli") == 0) *bulan = 7;
        else if (strcmp(iterate, "Agustus") == 0) *bulan = 8;
        else if (strcmp(iterate, "September") == 0) *bulan = 9;
        else if (strcmp(iterate, "Oktober") == 0) *bulan = 10;
        else if (strcmp(iterate, "November") == 0) *bulan = 11;
        else if (strcmp(iterate, "Desember") == 0) *bulan = 12;
        else *bulan = 0;
        
        
        iterate = strtok(NULL, " ");
        // printf("iterate2: %s\n\n", iterate);
        *tahun = atoi(iterate);
        
        // // Format "dd-mm-yyyy" or "yyyy-mm-dd"
        // int dateParts[3];
        // int i = 0;
        // while (token != NULL && i < 3) {
        //     dateParts[i++] = atoi(token);
        //     token = strtok(NULL, " -/");
        // }

        // if (i == 3) {
        //     if (dateParts[2] > 1000) { // Assuming the format is dd-mm-yyyy
        //         *bulan = dateParts[1];
        //         *tahun = dateParts[2];
        //     } else if (dateParts[0] > 1000) { // Assuming the format is yyyy-mm-dd
        //         *bulan = dateParts[1];
        //         *tahun = dateParts[0];
        //     } else {
        //         return 0; // Invalid date format
        //     }
        // } else {
        //     return 0; // Invalid date format
        // }
    }

    if (*tahun < 1000 || *tahun > 9999 || *bulan < 1 || *bulan > 12) {
        return 0; // Invalid year or month
    }

    return 1;
}

const char* nomorBulanKeNama(int bulan) {
    switch (bulan) {
        case 1: return "Januari";
        case 2: return "Februari";
        case 3: return "Maret";
        case 4: return "April";
        case 5: return "Mei";
        case 6: return "Juni";
        case 7: return "Juli";
        case 8: return "Agustus";
        case 9: return "September";
        case 10: return "Oktober";
        case 11: return "November";
        case 12: return "Desember";
        default: return "Unknown";
    }
}

int temukanDiagnosisBulanan(JumlahDiagnosisBulanan* hitungan, int ukuranHitungan, int bulan, int tahun, const char* diagnosis) {
    for (int i = 0; i < ukuranHitungan; i++) {
        if (hitungan[i].tahun == tahun && hitungan[i].bulan == bulan && strcmp(hitungan[i].diagnosis, diagnosis) == 0) {
            return i;
        }
    }
    return -1;
}

int temukanDiagnosisTahunan(JumlahDiagnosisTahunan* hitungan, int ukuranHitungan, int tahun, const char* diagnosis) {
    for (int i = 0; i < ukuranHitungan; i++) {
        if (hitungan[i].tahun == tahun && strcmp(hitungan[i].diagnosis, diagnosis) == 0) {
            return i;
        }
    }
    return -1;
}

int bandingkanHitungan(const void* a, const void* b) {
    JumlahDiagnosisBulanan* hitunganA = (JumlahDiagnosisBulanan*)a;
    JumlahDiagnosisBulanan* hitunganB = (JumlahDiagnosisBulanan*)b;

    if (hitunganA->tahun != hitunganB->tahun) return hitunganA->tahun - hitunganB->tahun;
    if (hitunganA->bulan != hitunganB->bulan) return hitunganA->bulan - hitunganB->bulan;
    return hitunganB->jumlah - hitunganA->jumlah;
}

int bandingkanHitunganTahunan(const void* a, const void* b) {
    JumlahDiagnosisTahunan* hitunganA = (JumlahDiagnosisTahunan*)a;
    JumlahDiagnosisTahunan* hitunganB = (JumlahDiagnosisTahunan*)b;

    if (hitunganA->tahun != hitunganB->tahun) return hitunganA->tahun - hitunganB->tahun;
    return hitunganB->jumlah - hitunganA->jumlah;
}

void cetakHasilBulanan(JumlahDiagnosisBulanan* hitungan, int ukuranHitungan) {
    int tahunSaatIni = -1;
    int bulanSaatIni = -1;
    int peringkat = 1;

    for (int i = 0; i < ukuranHitungan; i++) {
        if (hitungan[i].tahun != tahunSaatIni) {
            tahunSaatIni = hitungan[i].tahun;
            printf("\nTahun %d\n", tahunSaatIni);
            bulanSaatIni = -1;
        }

        if (hitungan[i].bulan != bulanSaatIni) {
            bulanSaatIni = hitungan[i].bulan;
            peringkat = 1;
            printf("Bulan %s:\n", nomorBulanKeNama(bulanSaatIni));
        }

        printf("%d. %s (%d orang)\n", peringkat++, hitungan[i].diagnosis, hitungan[i].jumlah);
    }
}

void cetakHasilTahunan(JumlahDiagnosisTahunan* hitungan, int ukuranHitungan) {
    int tahunSaatIni = -1;
    int peringkat = 1;

    for (int i = 0; i < ukuranHitungan; i++) {
        if (hitungan[i].tahun != tahunSaatIni) {
            tahunSaatIni = hitungan[i].tahun;
            printf("\nTahun %d\n", tahunSaatIni);
            peringkat = 1;
        }

        printf("%d. %s (%d orang)\n", peringkat++, hitungan[i].diagnosis, hitungan[i].jumlah);
    }
}

void analisisDiagnosisBulanan() {
    FILE* file = fopen("Riwayat_Datang_Pasien.csv", "r");
    if (!file) {
        printf("Gagal membuka file\n");
        return;
    }

    char line[256];
    RekamMedis rekam[MAX_RECORDS];
    int jumlahRekam = 0;

    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file) && jumlahRekam < MAX_RECORDS) {
        parseRekamMedis(line, &rekam[jumlahRekam]);
        jumlahRekam++;
    }
    fclose(file);

    JumlahDiagnosisBulanan hitungan[MAX_RECORDS];
    int ukuranHitungan = 0;

    for (int i = 0; i < jumlahRekam; i++) {
        int bulan;
        int tahun;

        if (namaBulanDanTahun(rekam[i].tanggal, &bulan, &tahun)) {
            int index = temukanDiagnosisBulanan(hitungan, ukuranHitungan, bulan, tahun, rekam[i].diagnosis);
            if (index >= 0) {
                hitungan[index].jumlah++;
            } else {
                hitungan[ukuranHitungan].bulan = bulan;
                hitungan[ukuranHitungan].tahun = tahun;
                strcpy(hitungan[ukuranHitungan].diagnosis, rekam[i].diagnosis);
                hitungan[ukuranHitungan].jumlah = 1;
                ukuranHitungan++;
            }
        }
    }

    qsort(hitungan, ukuranHitungan, sizeof(JumlahDiagnosisBulanan), bandingkanHitungan);

    cetakHasilBulanan(hitungan, ukuranHitungan);
}

void analisisDiagnosisTahunan() {
    FILE* file = fopen("Riwayat_Datang_Pasien.csv", "r");
    if (!file) {
        printf("Gagal membuka file\n");
        return;
    }

    char line[256];
    RekamMedis rekam[MAX_RECORDS];
    int jumlahRekam = 0;

    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file) && jumlahRekam < MAX_RECORDS) {
        parseRekamMedis(line, &rekam[jumlahRekam]);
        jumlahRekam++;
    }
    fclose(file);

    JumlahDiagnosisTahunan hitungan[MAX_RECORDS];
    int ukuranHitungan = 0;

    printf("\nAAAAAAAAajumlah rekam: %d\n", jumlahRekam);
    for (int i = 0; i < jumlahRekam; i++) {
        int bulan;
        int tahun;

        if (namaBulanDanTahun(rekam[i].tanggal, &bulan, &tahun)) {
            int index = temukanDiagnosisTahunan(hitungan, ukuranHitungan, tahun, rekam[i].diagnosis);
            if (index >= 0) {
                hitungan[index].jumlah++;
            } else {
                hitungan[ukuranHitungan].tahun = tahun;
                strcpy(hitungan[ukuranHitungan].diagnosis, rekam[i].diagnosis);
                hitungan[ukuranHitungan].jumlah = 1;
                ukuranHitungan++;
            }
        }
    }

    qsort(hitungan, ukuranHitungan, sizeof(JumlahDiagnosisTahunan), bandingkanHitunganTahunan);
    
    cetakHasilTahunan(hitungan, ukuranHitungan);
}

int main(void){
    analisisDiagnosisBulanan();
    analisisDiagnosisTahunan();
    return 0;
}