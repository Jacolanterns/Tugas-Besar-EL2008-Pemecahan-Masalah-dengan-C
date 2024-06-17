#ifndef HEADER_H
#define HEADER_H

#define PASIEN_MAX 100
#define RIWAYAT_MAX 100
#define MAX_TAHUN 10
#define MAX_RECORDS 1000
#define MAX_STRING 50

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

// Struktur untuk menyimpan tanggal
typedef struct {
    int hari;
    int bulan;
    int tahun;
} Tanggal;

// Struktur untuk menyimpan rekam medis pasien
typedef struct {
    char id[200];
    Tanggal tanggalKunjungan;
    char diagnosis[50];
    char tindakan[50];
    Tanggal tanggalKontrol;
    int biaya;
} RekamMedisPasien;

typedef struct {
    char tanggal[MAX_STRING];
    char idPasien[MAX_STRING];
    char diagnosis[MAX_STRING];
    char tindakan[MAX_STRING];
    char tindakLanjut[MAX_STRING];
    int biaya;
} RekamMedis;

typedef struct {
    int bulan;
    int tahun;
    char diagnosis[MAX_STRING];
    int jumlah;
} JumlahDiagnosisBulanan;

typedef struct {
    int tahun;
    char diagnosis[MAX_STRING];
    int jumlah;
} JumlahDiagnosisTahunan;

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