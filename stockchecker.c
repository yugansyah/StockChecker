#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Panjang maksimum entry
#define MAX_LEN 255

//struct untuk menyimpan salah satu barang
typedef struct{
    char kategori[20];
    char subkategori[20];
    int stok;
    int harga;
    int diskon;
} Barang;

Barang* inputBarang(FILE* stream, int* jumlahbarang){
    // Fungsi untuk memasukkan data file eksternal kedalam array dinamis
	int i;
	Barang* toko = NULL;
	// Variabel penyimpan baris dari file sementara    
	char line[MAX_LEN];
	
	// Baca jumlah barang
	fgets(line, MAX_LEN, stream);
	*jumlahbarang = atoi(line);
	
	//membuat array dengan panjang sesuai
	toko = (Barang*) malloc(*jumlahbarang * sizeof(Barang));
	
	//membaca dari file ke array
	for(i = 0; i < *jumlahbarang; i++){
		fgets(line, MAX_LEN, stream);
		strcpy(toko[i].kategori, line);
		
		fgets(line, MAX_LEN, stream);
		strcpy(toko[i].subkategori, line);
		
		fgets(line, MAX_LEN, stream);
		toko[i].stok = atoi(line);
		
		fgets(line, MAX_LEN, stream);
		toko[i].harga = atoi(line);
	}
	
	//mengembalikan toko untuk menjadi struct yang diinginkan
	return toko;
}

void hargaDiskonTerendah(Barang* toko, int jumlahbarang){
    // Fungsi menghitung harga barang sesuai diskon dan mencari harga barang termurah
    int i, terendah, j = 0;
	int* harga = NULL;
	
	//membuat array yang menyimpan indeks harga terendah
	//inisialisasi nilai terendah
	terendah = toko[0].harga;
	
	//mencari nilai terendah
	for(i = 1; i < jumlahbarang; i++){
		if(toko[i].harga < terendah)
			terendah = toko[i].harga;
	}
	
	//menyimpan indeks array terendah
	for(i = 0; i < jumlahbarang; i++){
		if(toko[i].harga == terendah){
			j++;
			harga = (int*) realloc(harga, j*sizeof(int));
			harga[j-1] = i;
		}
	}
	
	//mencetak harga terendah
	for(i = 0; i < j; i++){
		printf("\n");
		printf("Kategori        : %s", toko[harga[i]].kategori);
		printf("Sub-Kategori    : %s", toko[harga[i]].subkategori);
		printf("Stok Barang     : %d\n", toko[harga[i]].stok);
		printf("Diskon Barang   : %d\n", toko[harga[i]].diskon);
		printf("Harga Barang    : %d\n", toko[harga[i]].harga);
	}
}

void cekStock(Barang* toko, int jumlahbarang){
    // Fungsi mengecek stok barang harus di restock atau tidak
    int i;
	int kategori[4] = {0,0,0,0};
	
	//melakukan pengecekan dengan kategori tertentu agar sesuai dengan spesifikasi
	for(i = 0; i < jumlahbarang; i++){
		if(!strcmp("Baju\n", toko[i].kategori)){
				kategori[0] += toko[i].stok;
		}
		else if(!strcmp("Celana\n", toko[i].kategori)){
				kategori[1] += toko[i].stok;
		}
		else if(!strcmp("Aksesoris\n", toko[i].kategori)){
				kategori[2] += toko[i].stok;
		}
		else if(!strcmp("Sepatu\n", toko[i].kategori)){
				kategori[3] += toko[i].stok;
		}
	}
	
	if(kategori[0] < 75){
		printf("\nButuh restock: Baju\n");
		printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", 150 - kategori[0]);
	}
	else if(kategori[1] < 50){
		printf("\nButuh restock: Celana\n");
		printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", 100 - kategori[1]);
	}
	else if(kategori[2] < 25){
		printf("\nButuh restock: Aksesoris\n");
		printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", 50 - kategori[2]);
	}
	else if(kategori[3] < 70){
		printf("\nButuh restock: Sepatu\n");
		printf("Setidaknya pesan %d barang lagi untuk mencapai batas persediaan minimal!\n", 175 - kategori[3]);
	}
	//jika tidak ada yang dibawah stok mencetak ini
	else
		printf("\nSemua persediaan barang masih banyak! Tidak perlu restock!");
}

int main() {
	//inisialisasi variabel
    char filename[MAX_LEN];
    Barang* toko = NULL;
	int jumlahbarang, i;
	char baju[] = "Baju\n";
	char celana[] = "Celana\n";
	char aksesoris[] = "Aksesoris\n";
	char sepatu[] = "Sepatu\n";
	int kategori[4] = {0,0,0,0};
	
	// Input nama file
	printf("Masukkan file toko : ");
	scanf("%s", &filename);
	
	FILE* stream;
	//membuka file
	stream = fopen(filename, "r");
	
	toko = inputBarang(stream, &jumlahbarang);
	
	printf("\nPengecekan Persedian...\n");
	
	// menghitung total stok pada kategori
	for(i = 0; i < jumlahbarang; i++){
		if(!strcmp("Baju\n", toko[i].kategori)){
				kategori[0] += toko[i].stok;
		}
		else if(!strcmp("Celana\n", toko[i].kategori)){
				kategori[1] += toko[i].stok;
		}
		else if(!strcmp("Aksesoris\n", toko[i].kategori)){
				kategori[2] += toko[i].stok;
		}
		else if(!strcmp("Sepatu\n", toko[i].kategori)){
				kategori[3] += toko[i].stok;
		}
	}
	
	//menghitung diskon
	for(i = 0; i < jumlahbarang; i++){
		if(!strcmp(baju, toko[i].kategori)){
			toko[i].diskon = 35;
			if(kategori[0] > 150)
				toko[i].harga = toko[i].harga*65/100;
		}
		else if(!strcmp(celana, toko[i].kategori)){
			toko[i].diskon = 50;
			if(kategori[1] > 100)
				toko[i].harga = toko[i].harga*50/100;
		}
		else if(!strcmp(aksesoris, toko[i].kategori)){
			toko[i].diskon = 10;
			if(kategori[2] > 50)
				toko[i].harga = toko[i].harga*90/100;
		}
		else if(!strcmp(sepatu, toko[i].kategori)){
			toko[i].diskon = 70;
			if(kategori[3] > 120)
				toko[i].harga = toko[i].harga*30/100;
		}
	}
	
	cekStock(toko, jumlahbarang);
	
	printf("\nHarga Barang Termurah:\n");
	
	hargaDiskonTerendah(toko, jumlahbarang);
    
	free(toko);
    return 0;
}
