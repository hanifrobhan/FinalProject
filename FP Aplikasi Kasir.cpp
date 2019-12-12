#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct data 
{
	int ID_barang;
	char nama_barang[35];
	char kategori_barang[35];
	long int harga;
	int no_rak;
	int jumlah_barang;
	char satuan[10];
};
typedef struct data data;

int tambahBaru(data *gudang, int l);
void print_sebagian (data *barang,int i);
void print_semua (data *barang,int i); 
int tambah_array(data **array, int size);
int kurangi_array(data **array, int size);
int ukuran_array;
int gudang_array;
int mencari_ID(data *barang,int cari,int awal, int akhir, int s);
int mencari_Nama(data *barang,char cari[35],int awal, int akhir, int s);
void urutkan_ID(data *barang, int n);
void urutkan_Nama(data *barang, int n); 
void urutkan_Kategori_Barang(data *barang, int n);
void urutkan_Harga(data *barang, int n);
void urutkan_Nomor_Rak(data *barang, int n);
void urutkan_Jumlah_Barang(data *barang, int n);
int instan(data *barang, data *gudang);
void Bayar(data *barang);
int cek_ID(data *barang, int cari, int ukuranarray);
void gudang_data(data *gudang);
void print_belanja(data *barang, int size);

int main()
{
	ukuran_array = 1;
  	data *barang = (data *)malloc(ukuran_array*sizeof(data));
  	if(barang == NULL)
    {
        printf("Alokasi Memori Gagal\n");
        exit(1);
    }
    barang[0].ID_barang=0;
    gudang_array = 1;
    data *gudang = (data *)malloc(gudang_array*sizeof(data));
    if(gudang == NULL)
    {
        printf("Alokasi Memori Gagal\n");
        exit(1);
    }
	gudang_data(gudang);
	char pilihan;
	do{		
		system("cls");
		printf("\n============== APLIKASI KASIR ==============\n");
		printf("Masukkan Pilihan :\n");
		printf("1. Menu Belanja\n");
		printf("2. Data Barang\n");
		printf("q. Keluar\n");
		fflush(stdin);
		scanf("%c",&pilihan);
		if(pilihan=='1'){			
			char pilihan;
			do{
				system("cls");
				printf("\n============== MENU BELANJA ==============\n");	
				printf("\nMasukkan Pilihan :\n");
				printf("1. Tambah data barang belanja berdasarkan ID\n");
				printf("2. Ubah data belanja\n");
				printf("3. Pencarian data barang belanja\n");
				printf("4. Pengurutan data barang belanja\n");	
				printf("5. Bayar\n");
				printf("6. Tampilkan barang belanja\n");
				printf("q. Keluar\n");
				fflush(stdin);
				scanf("%c",&pilihan);
				if(pilihan=='1'){
					system("cls");
					print_belanja(gudang, gudang_array);
					ukuran_array=tambah_array(&barang,ukuran_array);			
					int i=instan(barang,gudang);
					if(barang[0].ID_barang==0 && i==1){	
						for(int j=0;j<ukuran_array-1;j++)		
							barang[j]=barang[j+1];								
							ukuran_array=kurangi_array(&barang,ukuran_array);
					}
					else if(i==0)
						ukuran_array=kurangi_array(&barang,ukuran_array);
					getch();
				}
				else if(pilihan=='2'){
					char pilihan;
					do{
						system("cls");
						printf("\nMasukkan Pilihan :\n");
						printf("1. Hapus barang belanja\n");
						printf("2. Ubah jumlah barang\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilihan);
						if(pilihan=='1'){
							int cari;
							urutkan_ID(barang,ukuran_array);
							system("cls");					
							printf("Masukkan ID Barang\n");
							fflush(stdin);
							scanf("%i",&cari);
							cari=mencari_ID(barang,cari,0,ukuran_array-1,ukuran_array);
							if(cari==-1){
								system("cls");
								printf("Tidak ditemukan\n");
								getch();
								break;
							}
							system("cls");
							for(int i=cari;i<ukuran_array-1;i++)		
								barang[i]=barang[i+1];
							if(ukuran_array>=2)	
								ukuran_array=kurangi_array(&barang,ukuran_array);
							else if(ukuran_array==1)
								barang[0].ID_barang=0;								
						}	
						else if(pilihan=='2'){
							int cari,jumlah;
							urutkan_ID(barang,ukuran_array);
							system("cls");					
							printf("Masukkan ID Barang\n");
							fflush(stdin);
							scanf("%i",&cari);
							cari=mencari_ID(barang,cari,0,ukuran_array-1,ukuran_array);
							if(cari==-1){
								system("cls");
								printf("Tidak ditemukan\n");
								getch();
								break;
							}							
							printf("Masukkan Jumlah Baru Barang\n");
							fflush(stdin);
							scanf("%i",&jumlah);
							barang[cari].jumlah_barang=jumlah;														
						}					
					}while(pilihan!='q');										
				}
				else if(pilihan=='3'){
					char pilih;
					do{
						system("cls");
						printf("Masukkan Pilihan :\n");
						printf("1. Cari berdasarkan ID Barang\n");
						printf("2. Cari berdasarkan Nama Barang\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilih);
						if(pilih=='1'){						
							int cari;
							urutkan_ID(barang,ukuran_array);
							system("cls");
							printf("Masukkan ID dari Barang yang ingin dicari\n");
							fflush(stdin);
							scanf("%i",&cari);
							system("cls");
							mencari_ID(barang,cari,0,ukuran_array-1,ukuran_array);
							getch();
						}
						else if(pilih=='2'){
							system("cls");	
							char cari[35];
							urutkan_Nama(barang,ukuran_array);
							system("cls");
							printf("Masukkan Nama dari Barang yang ingin dicari\n");
							fflush(stdin);
							gets(cari);
							system("cls");
							mencari_Nama(barang,cari,0,ukuran_array-1,ukuran_array);
							getch();					
						}											
			}while(pilih!='q');
					getch();					
				}	
				else if(pilihan=='4'){
					char pilih;
					do{
						system("cls");
						printf("Masukkan Pilihan :\n");
						printf("1. Urutkan berdasarkan ID Barang\n");
						printf("2. Urutkan berdasarkan Nama Barang\n");
						printf("3. Urutkan berdasarkan Kategori Barang\n");
						printf("4. Urutkan berdasarkan Harga Barang\n");
						printf("5. Urutkan berdasarkan Nomor Rak\n");
						printf("6. Urutkan berdasarkan Jumlah Barang\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilih);
						if(pilih=='1'){
							system("cls");	
							urutkan_ID(barang,ukuran_array);
							getch();
						}
						else if(pilih=='2'){
							system("cls");
							urutkan_Nama(barang,ukuran_array);
							getch(); 
						}
						else if(pilih=='3'){
							system("cls");
							urutkan_Kategori_Barang(barang,ukuran_array);
							getch();					
						}
						else if(pilih=='4'){
							system("cls");
							urutkan_Harga(barang,ukuran_array);
							getch();					
						}
						else if(pilih=='5'){
							system("cls");
							urutkan_Nomor_Rak(barang,ukuran_array);
							getch();					
						}
						else if(pilih=='6'){
							system("cls");
							urutkan_Jumlah_Barang(barang,ukuran_array);
							getch();
						}																											
					}while(pilih!='q');
					getch();								
				}	
				else if(pilihan=='5'){
					system("cls");
					Bayar(barang);
					getch();
				}
				else if(pilihan=='6'){
					system("cls");
					if(barang[0].ID_barang==0)
					{
						printf("Keranjang Kosong");
					}
					else
					{
						print_belanja(barang, ukuran_array);
					}	
					getch();
				}																									
			}while(pilihan!='q');			
		}
		else if(pilihan=='2'){
			char pilihan;
			do{
				system("cls");
				printf("\n============== MENU KELOLA DATA BARANG ==============\n");
				printf("Masukkan Pilihan :\n");
				printf("1. Tambah data\n");
				printf("2. Ubah data barang\n");
				printf("3. Pencarian data barang\n");
				printf("4. Pengurutan data barang\n");
				printf("5. Tampilkan seluruh Data Barang ter-registrasi\n");
				printf("q. Keluar\n");
				fflush(stdin);
				scanf("%c",&pilihan);
				if(pilihan=='1'){					
					tambahBaru(gudang,gudang_array);
				}
				else if(pilihan=='2'){
					char pilih;
					do{
						system("cls");
						printf("Masukkan Pilihan :\n");
						printf("1. Ubah Sebagian\n");
						printf("2. Ubah Total\n");
						printf("3. Hapus\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilih);
						if(pilih=='1'){
							int cari;
							urutkan_ID(gudang,gudang_array);
							system("cls");					
							printf("Masukkan ID Barang\n");
							fflush(stdin);
							scanf("%i",&cari);					
							cari=mencari_ID(gudang,cari,0,gudang_array-1,gudang_array);
							do{
								system("cls");
								printf("Masukkan Pilihan :\n");
								printf("1. Ubah ID Barang\n");
								printf("2. Ubah Nama Barang\n");
								printf("3. Ubah Kategori Barang\n");
								printf("4. Ubah Harga Barang\n");
								printf("5. Ubah Nomor Rak\n");
								printf("6. Ubah Jumlah Barang\n");
								printf("7. Ubah Satuan Barang\n");						
								printf("q. Keluar\n");
								fflush(stdin);
								scanf("%c",&pilih);
								if(pilih=='1'){
									system("cls");	
 	 	 	 	 			 	 	printf("Masukkan ID Barang yang Baru : ");
 	 	 	 	 	 			 	fflush(stdin);
 	 	 	 	 	 			 	scanf("%d", &gudang[cari].ID_barang);				
									getch();
								}
								else if(pilih=='2'){
									system("cls");
 	 	 			 	 	 	 	printf("Masukkan Nama Barang yang Baru : ");
 	 	 	 			 	 	 	fflush(stdin);
 	 	 	 	 			 	 	gets(gudang[cari].nama_barang);
									getch(); 
								}
								else if(pilih=='3'){
									system("cls");
	 	 			 	 	 	 	printf("Masukkan Kategori Barang yang Baru : ");
 	 	 	 			 	 	 	fflush(stdin);
 	 	 	 	 	 			 	gets(gudang[cari].kategori_barang);
									getch();					
								}
								else if(pilih=='4'){
									system("cls");
	 	 	 	 			 	 	printf("Masukkan Harga Barang yang Baru : ");
 	 	 	 	 	 	 			fflush(stdin);
 	 	 	 	 	 			 	scanf("%d", &gudang[cari].harga);
									getch();					
								}
								else if(pilih=='5'){
									system("cls");
	 	 	 	 	 	 			printf("Masukkan Nomor Rak yang Baru : ");
 	 	 	 	 	 			 	fflush(stdin);
 	 	 	 	 	 	 			scanf("%d", &gudang[cari].no_rak);
									getch();					
								}
								else if(pilih=='6'){
									system("cls");
	 	 	 	 	 			 	printf("Masukkan Jumlah Barang yang Baru : ");
 	 	 	 	 	 	 			fflush(stdin);
 	 	 	 	 	 	 			scanf("%d", &gudang[cari].jumlah_barang);
									getch();
								}
								else if(pilih=='7'){
									system("cls");
			 	 	 	 	 	 	printf("Masukkan Satuan Barang yang Baru : ");
 	 	 	 			 	 	 	fflush(stdin);
 	 	 	 	 			 	 	gets(gudang[cari].satuan);
									getch();
								}																																	
							}while(pilih!='q');										
						}
						else if(pilih=='2'){
							int cari;
							urutkan_ID(gudang,ukuran_array);
							system("cls");					
							printf("Masukkan ID Barang\n");
							fflush(stdin);
							scanf("%i",&cari);
							cari=mencari_ID(gudang,cari,0,gudang_array-1,gudang_array);
							system("cls");
							tambahBaru(gudang,cari);
							gudang_array=kurangi_array(&gudang,gudang_array);										
						}
						else if(pilih=='3'){
							int cari;
							urutkan_ID(barang,ukuran_array);
							system("cls");					
							printf("Masukkan ID Barang\n");
							fflush(stdin);
							scanf("%i",&cari);
							cari=mencari_ID(gudang,cari,0,gudang_array-1,gudang_array);
							if(cari==-1){
								system("cls"); 
								printf("Tidak ditemukan\n");
								break;
							}
							system("cls");
							for(int i=cari;i<gudang_array-1;i++)		
								gudang[i]=gudang[i+1];
							gudang_array=kurangi_array(&gudang,gudang_array);												
						}											
					}while(pilih!='q');
					getch();					
				}
				else if(pilihan=='3'){
					char pilih;
					do{
						system("cls");
						printf("Masukkan Pilihan :\n");
						printf("1. Cari berdasarkan ID Barang\n");
						printf("2. Cari berdasarkan Nama Barang\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilih);
						if(pilih=='1'){						
							int cari;
							urutkan_ID(gudang,gudang_array);
							system("cls");
							printf("Masukkan ID dari Barang yang ingin dicari\n");
							fflush(stdin);
							scanf("%i",&cari);
							system("cls");
							mencari_ID(gudang,cari,0,gudang_array-1,gudang_array);
							getch();
						}
						else if(pilih=='2'){
							system("cls");	
							char cari[35];
							urutkan_Nama(gudang,gudang_array);
							system("cls");
							printf("Masukkan Nama dari Barang yang ingin dicari\n");
							fflush(stdin);
							gets(cari);
							system("cls");
							mencari_Nama(gudang,cari,0,gudang_array-1,gudang_array);
							getch();					
						}											
					}while(pilih!='q');
					getch();								
				}	
				else if(pilihan=='4'){
					char pilih;
					do{
						system("cls");
						printf("Masukkan Pilihan :\n");
						printf("1. Urutkan berdasarkan ID Barang\n");
						printf("2. Urutkan berdasarkan Nama Barang\n");
						printf("3. Urutkan berdasarkan Kategori Barang\n");
						printf("4. Urutkan berdasarkan Harga Barang\n");
						printf("5. Urutkan berdasarkan Nomor Rak\n");
						printf("6. Urutkan berdasarkan Jumlah Barang\n");
						printf("q. Keluar\n");
						fflush(stdin);
						scanf("%c",&pilih);
						if(pilih=='1'){
							system("cls");	
							urutkan_ID(gudang,gudang_array);
							getch();
						}
						else if(pilih=='2'){
							system("cls");
							urutkan_Nama(gudang,gudang_array);
							getch(); 
						}
						else if(pilih=='3'){
							system("cls");
							urutkan_Kategori_Barang(gudang,gudang_array);
							getch();					
						}
						else if(pilih=='4'){
							system("cls");
							urutkan_Harga(gudang,gudang_array);
							getch();					
						}
						else if(pilih=='5'){
							system("cls");
							urutkan_Nomor_Rak(gudang,gudang_array);
							getch();					
						}
						else if(pilih=='6'){
							system("cls");
							urutkan_Jumlah_Barang(gudang,gudang_array);
							getch();
						}																											
					}while(pilih!='q');
					getch();								
				}
				else if(pilihan=='5'){
					print_semua(gudang,gudang_array);
					getch();
				}											
			}while(pilihan!='q');				
		}		
	}while(pilihan!='q');
	return 0;
}

int tambahBaru(data *gudang, int l)
{
	int cek,cari;
	system("cls");
 	printf("Masukkan ID Barang : ");		
 	fflush(stdin);
  	scanf("%d", &cari);
  	urutkan_ID(gudang,gudang_array);
 	cek=mencari_ID(gudang,cari,0,gudang_array-1,gudang_array);
 	printf("\n%i",cek);
 	system("cls");
 	if(cek!=-1)
	{			
 		system("cls");
 		printf("ID Telah terdaftar!");
		getch();
		return 0;	 	 		
	}
	gudang_array=tambah_array(&gudang,gudang_array);	 	 		 
	gudang[l].ID_barang=cari;	
 	printf("Masukkan Nama Barang : ");
 	fflush(stdin);
 	gets(gudang[l].nama_barang);
 	printf("Masukkan Kategori Barang : ");
 	fflush(stdin);
 	gets(gudang[l].kategori_barang);
 	printf("Masukkan Harga : ");
 	fflush(stdin);
 	scanf("%d", &gudang[l].harga); 
 	printf("Masukkan Nomor Rak : ");
 	fflush(stdin);
 	scanf("%d", &gudang[l].no_rak); 
 	printf("Masukkan Jumlah Barang : ");
 	fflush(stdin);
 	scanf("%d", &gudang[l].jumlah_barang);
 	printf("Masukkan Satuan : ");
 	fflush(stdin);
 	gets(gudang[l].satuan);
	return 1; 	 	
}

void gudang_data(data *gudang)
{    
	gudang[gudang_array-1].ID_barang=9000;
	strcpy(gudang[gudang_array-1].nama_barang,"Coca-Cola");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Minuman");
	gudang[gudang_array-1].harga=8000;
	gudang[gudang_array-1].no_rak=101;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"Botol");
	
	gudang_array=tambah_array(&gudang,gudang_array);
	gudang[gudang_array-1].ID_barang=9111;
	strcpy(gudang[gudang_array-1].nama_barang,"Mie Indomie");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Makanan");
	gudang[gudang_array-1].harga=2500;
	gudang[gudang_array-1].no_rak=102;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"PCS");	
	
	gudang_array=tambah_array(&gudang,gudang_array);
	gudang[gudang_array-1].ID_barang=9101;
	strcpy(gudang[gudang_array-1].nama_barang,"Teh Pucuk");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Minuman");
	gudang[gudang_array-1].harga=6000;
	gudang[gudang_array-1].no_rak=103;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"Botol");
	
	gudang_array=tambah_array(&gudang,gudang_array);
	gudang[gudang_array-1].ID_barang=9001;
	strcpy(gudang[gudang_array-1].nama_barang,"Khong Guan");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Makanan");
	gudang[gudang_array-1].harga=25000;
	gudang[gudang_array-1].no_rak=104;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"Kaleng");	
	
	gudang_array=tambah_array(&gudang,gudang_array);
 	gudang[gudang_array-1].ID_barang=9010;
	strcpy(gudang[gudang_array-1].nama_barang,"Pepsodent");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Peralatan");
	gudang[gudang_array-1].harga=12000;
	gudang[gudang_array-1].no_rak=105;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"PCS");	
	
	gudang_array=tambah_array(&gudang,gudang_array);
	gudang[gudang_array-1].ID_barang=9100;
	strcpy(gudang[gudang_array-1].nama_barang,"Obat Promag");	
	strcpy(gudang[gudang_array-1].kategori_barang,"Obat-obatan");
	gudang[gudang_array-1].harga=10000;
	gudang[gudang_array-1].no_rak=106;
	gudang[gudang_array-1].jumlah_barang=100;
	strcpy(gudang[gudang_array-1].satuan,"Tablet");			
}

void print_semua (data *barang,int i) 
{
	for(int j=0;j<i;j++){
		print_sebagian (barang,j);	
	}	
}

void print_sebagian (data *barang,int j)
{
	printf("\nData : %i",j+1);
	printf("\nID Barang 		: %d", barang[j].ID_barang);
	printf("\nNama Barang 		: %s", barang[j].nama_barang);	
	printf("\nKategori Barang 	: %s", barang[j].kategori_barang);
	printf("\nHarga 			: %d", barang[j].harga);
	printf("\nNomor Rak 		: %i", barang[j].no_rak);
	printf("\nJumlah Barang		: %d %s\n", barang[j].jumlah_barang, barang[j].satuan);		
}

