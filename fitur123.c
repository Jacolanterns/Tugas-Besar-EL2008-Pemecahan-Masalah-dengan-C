#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "header.h"
#include "definisiFungsi.c"

#define PASIEN_MAX 100
#define RIWAYAT_MAX 100

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
bool isDuplicatePasien(const char *nama, const char *no_bpjs) {
    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(pasien[i].nama, nama) == 0 || strcmp(pasien[i].no_bpjs, no_bpjs) == 0) {
            return true; // Duplikat ditemukan
        }
    }
    return false; // Tidak ada duplikat
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
    printf("Masukkan alamat: ");
    scanf(" %[^\n]", pasien_baru.alamat);
    printf("Masukkan kota: ");
    scanf(" %[^\n]", pasien_baru.kota);
    printf("Masukkan tempat lahir: ");
    scanf(" %[^\n]", pasien_baru.tempat_lahir);
    printf("Masukkan tanggal lahir (YYYY-MM-DD): ");
    scanf(" %s", pasien_baru.tanggal_lahir);
    printf("Masukkan umur: ");
    scanf("%d", &pasien_baru.umur);
    printf("Masukkan nomor BPJS: ");
    scanf(" %s", pasien_baru.no_bpjs);
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", pasien_baru.id_pasien);

    if (isDuplicatePasien(pasien_baru.nama, pasien_baru.no_bpjs)) {
        printf("Pasien dengan nama atau nomor BPJS tersebut sudah ada.\n");
        return;
    }

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

// // Mencari pasien berdasarkan ID Pasien
// int cariPasienID(const char* id_pasien) {
//     for (int i = 0; i < jumlah_pasien; i++) {
//         if (strcmp(pasien[i].id_pasien, id_pasien) == 0) {
//             return i;
//         }
//     }
//     return -1;
// }

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
    printf("Masukkan tanggal lahir baru (YYYY-MM-DD): ");
    scanf(" %s", p->tanggal_lahir);
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

// Menambah riwayat medis baru
void tambahRiwayatMedis() {
    if (jumlah_riwayat >= RIWAYAT_MAX) {
        printf("Data riwayat medis penuh.\n");
        return;
    }
    RiwayatMedis riwayat_baru;
    riwayat_baru.id = jumlah_riwayat + 1;
    printf("Masukkan tanggal (YYYY-MM-DD): ");
    scanf(" %s", riwayat_baru.tanggal);
    printf("Masukkan ID pasien: ");
    scanf(" %[^\n]", riwayat_baru.id_pasien);
    printf("Masukkan diagnosis: ");
    scanf(" %[^\n]", riwayat_baru.diagnosis);
    printf("Masukkan tindakan: ");
    scanf(" %[^\n]", riwayat_baru.tindakan);
    printf("Masukkan tanggal kontrol (YYYY-MM-DD): ");
    scanf(" %s", riwayat_baru.tanggal_kontrol);
    printf("Masukkan biaya: ");
    scanf("%d", &riwayat_baru.biaya);
    riwayat[jumlah_riwayat++] = riwayat_baru;
    printf("Riwayat medis berhasil ditambahkan.\n");

    // Append the new medical record data to the CSV file
    FILE *file = fopen("Riwayat_Datang_Pasien.csv", "a");
    if (file == NULL) {
        printf("Gagal membuka file Riwayat_Datang_Pasien.csv.\n");
        return;
    }
    fprintf(file, "%d,%s,%s,%s,%s,%s,%d\n",
            riwayat_baru.id, riwayat_baru.tanggal, riwayat_baru.id_pasien, 
            riwayat_baru.diagnosis, riwayat_baru.tindakan, riwayat_baru.tanggal_kontrol, 
            riwayat_baru.biaya);
    fclose(file);
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
    printf("Masukkan tanggal baru (YYYY-MM-DD): ");
    scanf(" %s", r->tanggal);
    printf("Masukkan diagnosis baru: ");
    scanf(" %[^\n]", r->diagnosis);
    printf("Masukkan tindakan baru: ");
    scanf(" %[^\n]", r->tindakan);
    printf("Masukkan tanggal kontrol baru (YYYY-MM-DD): ");
    scanf(" %s", r->tanggal_kontrol);
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

    for (int i = 1; i < jumlah_riwayat+1; i++) {
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

int main() {
    // Read data from CSV files
    readPasienFromCSV("DataPMC20232024.csv");
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
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 0);
    return 0;
}