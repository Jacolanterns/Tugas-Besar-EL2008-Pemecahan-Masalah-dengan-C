#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include "definisiFungsi.c"

// Pasien pasien[PASIEN_MAX];
// RiwayatMedis riwayat[RIWAYAT_MAX];
// int jumlah_pasien = 0;
// int jumlah_riwayat = 0;

// // Fungsi untuk membaca dan memparsing data pasien dari file CSV
// void readPasienFromCSV(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (!file) {
//         printf("Gagal membuka file %s.\n", filename);
//         return;
//     }
//     char line[256];
//     while (fgets(line, sizeof(line), file)) {
//         Pasien p;
//         sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,\n]",
//                &p.id, p.nama, p.alamat, p.kota, p.tempat_lahir, p.tanggal_lahir,
//                &p.umur, p.no_bpjs, p.id_pasien);
//         pasien[jumlah_pasien++] = p;
//     }
//     fclose(file);
// }

// // Fungsi untuk membaca dan memparsing data riwayat medis dari file CSV
// void readRiwayatMedisFromCSV(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (!file) {
//         printf("Gagal membuka file %s.\n", filename);
//         return;
//     }
//     char line[256];
//     while (fgets(line, sizeof(line), file)) {
//         RiwayatMedis r;
//         sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%d\n",
//                &r.id, r.tanggal, r.id_pasien, r.diagnosis, r.tindakan, r.tanggal_kontrol, &r.biaya);
//         riwayat[jumlah_riwayat++] = r;
//     }
//     fclose(file);
// }

// Fungsi untuk mengecek duplikasi data pasien berdasarkan nama atau nomor BPJS
bool isDuplicatePasien_nama(const char *nama) {
    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].nama, nama) == 0){
            return true; // Duplikat ditemukan
        }
    }
    return false; // Tidak ada duplikat
}

bool isDuplicatePasien_bpjs(const char *no_bpjs){
    for(int i=0; i< jumlah_pasien; i++){
        if(strcmp(pasien[i].no_bpjs, no_bpjs) == 0){
            return true;
        }
    }
    return false;
}

// Menambah pasien baru
void tambahPasien() {
    if (jumlah_pasien >= PASIEN_MAX) {
        printf("Data pasien penuh.\n");
        return;
    }
    Pasien pasien_baru;
    pasien_baru.id = jumlah_pasien + 1;
    printf("Masukkan nama pasien: ");
    scanf(" %[^\n]", pasien_baru.nama);
    if(isDuplicatePasien_nama(pasien_baru.nama)){
        printf("Pasien dengan nama tersebut sudah ada.\n");
        return;
    }
    printf("Masukkan alamat: ");
    scanf(" %[^\n]", pasien_baru.alamat);
    printf("Masukkan kota: ");
    scanf(" %[^\n]", pasien_baru.kota);
    printf("Masukkan tempat lahir: ");
    scanf(" %[^\n]", pasien_baru.tempat_lahir);
    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal lahir: ");
    scanf(" %[^\n]", pasien_baru.tanggal_lahir);
    printf("Masukkan umur: ");
    scanf("%d", &pasien_baru.umur);
    printf("Masukkan nomor BPJS: ");
    scanf(" %s", pasien_baru.no_bpjs);
    if(isDuplicatePasien_bpjs(pasien_baru.no_bpjs)){
        printf("Pasien dengan nomor BPJS tersebut sudah ada\n.");
        return;
    }
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", pasien_baru.id_pasien);

    pasien[jumlah_pasien++] = pasien_baru;
    printf("Pasien berhasil ditambahkan.\n");

    // Append the new patient data to the CSV file
    FILE *file = fopen("DataPMC20232024.csv", "a");
    if (file == NULL) {
        printf("Gagal membuka file DataPMC20232024.csv.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%s,%s,%s,%d,%s,%s\n",
            pasien_baru.id, pasien_baru.nama, pasien_baru.alamat, pasien_baru.kota,
            pasien_baru.tempat_lahir, pasien_baru.tanggal_lahir, pasien_baru.umur, 
            pasien_baru.no_bpjs, pasien_baru.id_pasien);
    fclose(file);
}

// Mengubah data pasien
void updatePasien() {
    char id_pasien[15];
    printf("Masukkan ID pasien yang ingin diubah: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariPasienID(id_pasien);
    if (index == -1) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    Pasien *p = &pasien[index];
    printf("Masukkan nama baru: ");
    scanf(" %[^\n]", p->nama);
    printf("Masukkan alamat baru: ");
    scanf(" %[^\n]", p->alamat);
    printf("Masukkan kota baru: ");
    scanf(" %[^\n]", p->kota);
    printf("Masukkan tempat lahir baru: ");
    scanf(" %[^\n]", p->tempat_lahir);
    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal lahir baru: ");
    scanf(" %[^\n]", p->tanggal_lahir);
    printf("Masukkan umur baru: ");
    scanf("%d", &p->umur);
    printf("Masukkan nomor BPJS baru: ");
    scanf(" %s", p->no_bpjs);
    printf("Data pasien berhasil diubah.\n");
}

// Menghapus pasien
void hapusPasien() {
    char id_pasien[15];
    printf("Masukkan ID pasien yang ingin dihapus: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariPasienID(id_pasien);
    if (index == -1) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    for (int i = index; i < jumlah_pasien - 1; i++) {
        pasien[i] = pasien[i + 1];
    }
    jumlah_pasien--;
    printf("Pasien berhasil dihapus.\n");
}

// Menampilkan informasi pasien
void tampilkanPasien() {
    char id_pasien[15];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariPasienID(id_pasien);
    if (index == -1) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    Pasien p = pasien[index];
    printf("ID: %d\n", p.id);
    printf("Nama: %s\n", p.nama);
    printf("Alamat: %s\n", p.alamat);
    printf("Kota: %s\n", p.kota);
    printf("Tempat Lahir: %s\n", p.tempat_lahir);
    printf("Tanggal Lahir: %s\n", p.tanggal_lahir);
    printf("Umur: %d\n", p.umur);
    printf("No BPJS: %s\n", p.no_bpjs);
    printf("ID Pasien: %s\n", p.id_pasien);
}

// Mencari riwayat medis berdasarkan ID Pasien
int cariRiwayatMedisID(const char* id_pasien) {
    for (int i = 1; i < jumlah_riwayat+1; i++) {
        char temp[100];
        strcpy(temp, riwayat[i].id_pasien);
        temp[10] = '\0';
        // printf("Pencarian ke-%d: %s ... %s\n", i, temp, id_pasien);
        if (strcmp(temp, id_pasien) == 0) {
            return i;
        }
    }
    return -1;
}

// Mengubah riwayat medis
void updateRiwayatMedis() {
    char id_pasien[15];
    printf("Masukkan ID pasien yang riwayat medisnya ingin diubah: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariRiwayatMedisID(id_pasien);
    if (index == -1) {
        printf("Riwayat medis tidak ditemukan.\n");
        return;
    }
    RiwayatMedis *r = &riwayat[index];
    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal kedatangan baru: ");
    scanf(" %[^\n]", r->tanggal);
    printf("Masukkan diagnosis baru: ");
    scanf(" %[^\n]", r->diagnosis);
    printf("Masukkan tindakan baru: ");
    scanf(" %[^\n]", r->tindakan);
    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal kontrol baru: ");
    scanf(" %[^\n]", r->tanggal_kontrol);
    printf("Masukkan biaya baru: ");
    scanf("%d", &r->biaya);
    printf("Riwayat medis berhasil diubah.\n");
}

// Menghapus riwayat medis
void hapusRiwayatMedis() {
    char id_pasien[15];
    printf("Masukkan ID pasien yang riwayat medisnya ingin dihapus: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariRiwayatMedisID(id_pasien);
    if (index == -1) {
        printf("Riwayat medis tidak ditemukan.\n");
        return;
    }
    for (int i = index; i < jumlah_riwayat - 1; i++) {
        riwayat[i] = riwayat[i + 1];
    }
    jumlah_riwayat--;
    printf("Riwayat medis berhasil dihapus.\n");
}

// Menampilkan riwayat medis berdasarkan ID pasien
void tampilkanRiwayatMedis(char dummy[10]) {
    char id_pasien[15];
    if(dummy[0] == 'K'){
        strcpy(id_pasien, dummy);
    }
    else{
        printf("Masukkan ID pasien: ");
        scanf(" %[^\n]", id_pasien);
    }

    for (int i = 1; i < jumlah_riwayat; i++) {
        char tempString[25];
        strcpy(tempString, riwayat[i].id_pasien);
        tempString[10] = '\0';
        //printf("Pencarian ke-%d (riwayat[i].id_pasien=%s) ... (%s)\n", i, riwayat[i].id_pasien, id_pasien);
        if (strcmp(tempString, id_pasien) == 0) {
            printf("ID: %d\n", riwayat[i].id);
            printf("Tanggal: %s\n", riwayat[i].tanggal);
            printf("Diagnosis: %s\n", riwayat[i].diagnosis);
            printf("Tindakan: %s\n", riwayat[i].tindakan);
            printf("Tanggal Kontrol: %s\n", riwayat[i].tanggal_kontrol);
            printf("Biaya: %d\n", riwayat[i].biaya);
            printf("\n");
        }
    }
}

// Menampilkan pasien berserta dengan riwayat medisnya
void displayPatientWithMedicalRecords() {
    char id_pasien[15];
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", id_pasien);
    int index = cariPasienID(id_pasien);
    if (index == -1) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }
    Pasien p = pasien[index];
    printf("ID: %d\n", p.id);
    printf("Nama: %s\n", p.nama);
    printf("Alamat: %s\n", p.alamat);
    printf("Kota: %s\n", p.kota);
    printf("Tempat Lahir: %s\n", p.tempat_lahir);
    printf("Tanggal Lahir: %s\n", p.tanggal_lahir);
    printf("Umur: %d\n", p.umur);
    printf("No BPJS: %s\n", p.no_bpjs);
    printf("ID Pasien: %s\n", p.id_pasien);
    printf("\nRiwayat Medis:\n");
    tampilkanRiwayatMedis(p.id_pasien);
}

// menu 12
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

// menu 10
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

// Fungsi untuk memuat rekam medis pasien dari file
int muatRekamMedisPasien(RekamMedisPasien rekam[], const char *namaFile) {
    FILE *file = fopen(namaFile, "r");
    if (!file) {
        perror("Gagal membuka file");
        exit(EXIT_FAILURE);
    }

    char baris[500];

    // Melewati header
    fgets(baris, sizeof(baris), file);

    while (fgets(baris, sizeof(baris), file) && jumlah < PASIEN_MAX) {
        char tanggal[20], tanggalKontrol[20], bulan[10];
        sscanf(baris, "%*d,%200[^,],%19[^,],%49[^,],%49[^,],%19[^,],%d", tanggal, rekam[jumlah].id, rekam[jumlah].diagnosis, rekam[jumlah].tindakan, tanggalKontrol, &rekam[jumlah].biaya);
        
        //printf("Sebelum: %s ", rekam[jumlah].id);
        //rekam[jumlah].id[10] = '\0';
        //printf("--- Sesudah: %s\n", rekam[jumlah].id);
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

// Menambah riwayat medis baru
void tambahRiwayatMedis() {
    if (jumlah_riwayat >= RIWAYAT_MAX) {
        printf("Data riwayat medis penuh.\n");
        return;
    }
    RiwayatMedis riwayat_baru;
    riwayat_baru.id = jumlah_riwayat + 1;
    char tanggal[20], tanggalKontrol[20], bulan[10];

    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal kedatangan: ");
    scanf(" %[^\n]", riwayat_baru.tanggal);
    // strcpy(tanggal, riwayat_baru.tanggal);
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", riwayat_baru.id_pasien);
    // strcpy(rekam[jumlah].id, riwayat_baru.id_pasien);
    printf("Masukkan diagnosis: ");
    scanf(" %[^\n]", riwayat_baru.diagnosis);
    //strcpy(rekam[jumlah].diagnosis, riwayat_baru.diagnosis);
    printf("Masukkan tindakan: ");
    scanf(" %[^\n]", riwayat_baru.tindakan);
    //strcpy(rekam[jumlah].tindakan, riwayat_baru.tindakan);
    printf("(*contoh input tanggal: 18-Jun-22 atau 18 Juni 2022)\n");
    printf("Masukkan tanggal kontrol: ");
    scanf(" %[^\n]", riwayat_baru.tanggal_kontrol);
    //strcpy(tanggalKontrol, riwayat_baru.tanggal_kontrol);
    printf("Masukkan biaya: ");
    scanf("%d", &riwayat_baru.biaya);
    //rekam[jumlah].biaya = riwayat_baru.biaya;
    riwayat[jumlah_riwayat++] = riwayat_baru;
    printf("Riwayat medis berhasil ditambahkan.\n");

    // handle bug diagnosis dan id_pasien yang kegabung stringnya
    char temp[255] = {0};
    int j = 0;
    for(int i=10;riwayat_baru.id_pasien[i] != '\0';i++){

            temp[j] = riwayat_baru.id_pasien[i];
            j++;
        
    }
    temp[j] = '\0';
    
    strcpy(riwayat_baru.diagnosis, temp);
    riwayat_baru.id_pasien[10] = '\0';

    // Append the new medical record data to the CSV file
    FILE *file = fopen("Riwayat_Datang_Pasien.csv", "a");
    if (file == NULL) {
        printf("Gagal membuka file Riwayat_Datang_Pasien.csv.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%s,%s,%s,%d\n",
            riwayat_baru.id, riwayat_baru.tanggal, riwayat_baru.id_pasien, 
            temp, riwayat_baru.tindakan, riwayat_baru.tanggal_kontrol, 
            riwayat_baru.biaya);
    fclose(file);
}

void kosongkanRekam() {
    memset(rekam, 0, sizeof(rekam));
    jumlah = 0;
}

// Fitur 5
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

void distribusiPenyakit(){
    analisisDiagnosisBulanan();
    analisisDiagnosisTahunan();
}

int main() {
    // Read data from CSV files
    readPasienFromCSV("DataPMC20232024.csv");

    int jumlahRekam_4;
    readRiwayatMedisFromCSV("Riwayat_Datang_Pasien.csv");
    

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Tambah Pasien\n");
        printf("2. Ubah Pasien\n");
        printf("3. Hapus Pasien\n");
        printf("4. Tampilkan Pasien\n");
        printf("5. Tambah Riwayat Medis\n");
        printf("6. Ubah Riwayat Medis\n");
        printf("7. Hapus Riwayat Medis\n");
        printf("8. Tampilkan Riwayat Medis\n");
        printf("9. Tampilkan Pasien dan Riwayat Medis\n");
        printf("10. Laporan Pendapatan Bulanan dan Tahunan\n");
        printf("11. Jenis Penyakit dan Jumlah Pasiennya (perbulan dan pertahun)\n");
        printf("12. Tampilkan Pasien yang Perlu Kontrol\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                tambahPasien();
                break;
            case 2:
                updatePasien();
                break;
            case 3:
                hapusPasien();
                break;
            case 4:
                tampilkanPasien();
                break;
            case 5:
                tambahRiwayatMedis();
                break;
            case 6:
                updateRiwayatMedis();
                break;
            case 7:
                hapusRiwayatMedis();
                break;
            case 8:
                tampilkanRiwayatMedis("abc");
                break;
            case 9:
                displayPatientWithMedicalRecords();
                break;
            case 10:
                kosongkanRekam();
                jumlahRekam_4 = muatRekamMedisPasien(rekam, "Riwayat_Datang_Pasien.csv");
                hitungPendapatanBulananDanTahunan(rekam, jumlahRekam_4);
                break;
            case 11:
                distribusiPenyakit();
                break;
            case 12:
                informasiKontrolPasien();
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0);
    return 0;
}
