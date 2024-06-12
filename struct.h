#ifndef STRUCT_H
#define STRUCT_H

#define PASIEN_MAX 100
#define RIWAYAT_MAX 100

typedef struct {
    int id;
    char nama[50];
    char alamat[100];
    char kota[100];
    char tempat_lahir[100];
    char tanggal_lahir[50]; //DD-MM-YYYY
    int umur;
    char no_bpjs[20]; //exp: 1234567890
    char id_pasien[10]; //exp: 1230123
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

void parsingData();
void tambahPasien();
void updatePasien();
void deletePasien();
void cariPasien();
void tambahRiwayat();
void updateRiwayat();
void deleteRiwayat();
void cariRiwayat();
void informasiPasienDanRiwayat();


#endif