#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define FILE_NAME "sales.txt"
#define FILE_EVENT "event.txt"
#define MAX_NAMA_PELANGGAN 100
#define MAX_NAMA_EVENT 100
#define MAX_JENIS_TIKET 100
#define MAX_TIKET_EVENT 5

//struct untuk tanggal
typedef struct{
    int yyyy;
    int mm;
    int dd;
} tanggal;

//struct dalam event.txt
typedef struct{
	tanggal tanggalEvent;
	char namaEvent[MAX_NAMA_EVENT];
	int jenisTiket[MAX_TIKET_EVENT];
	int totalTiket;
} dataevent;

//struct dalam sales.txt
typedef struct{
	tanggal tanggalTransaksi;
	char namaPelanggan[MAX_NAMA_PELANGGAN];
	char jenisTiket[MAX_JENIS_TIKET];
	char namaEvent[MAX_NAMA_EVENT];
	int jumlahTiket;
	float hargaTiket;
	float total;
} datasales;

//menghapus newline pada fgets
void fgetsRemove(char * restrict buf, int n,FILE * restrict stream){
    if(fgets(buf, n, stream) == NULL){
        printf("Fail to read the input stream");
    }
    else{
    	//mendapatkan panjang string sebelum newline dan mengganti newline menjadi \0
        buf[strcspn(buf, "\n")] = '\0'; 
    }
}

//header untuk tiap menu
void header(){
	system("cls");
    printf("\t\t\t===========================================================================");
	printf("\n\t\t\t=x=x=x=x=x=x                                                   x=x=x=x=x=x=");
    printf("\n\t\t\t=x=x=x=x=x=x               <3 Decode Ticketing <3              x=x=x=x=x=x=");
    printf("\n\t\t\t=x=x=x=x=x=x                                                   x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
}

//display welcome message
void welcomeMessage(){
    printf("\n\n\n\n\n");
    printf("\n\t\t\t        =x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =                 WELCOME TO                =");
    printf("\n\t\t\t        =             Decode  Ticketing             =");
    printf("\n\t\t\t        =            'your concert buddy'           =");
    printf("\n\t\t\t        =                                           =");
    printf("\n\t\t\t        =x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=x=");
    printf("\n\n\n\t\t\t Tekan tombol enter untuk lanjut.....");
    getch();
}

// cek jika tahun kabisat, return 1
int kabisat(int tahun){
    return (((tahun % 4 == 0) &&
             (tahun % 100 != 0)) ||
            (tahun % 400 == 0));
}

// cek jika tanggal valid, return 1
int cekTanggal(tanggal *validDate){
    //cek rentang hari, bulan, tahun
    if (validDate->yyyy > 9999 ||validDate->yyyy < 1900)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //untuk bulan februari di tahun kabisat
    if (validDate->mm == 2){
        if (kabisat(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    //untuk bulan dengan 30 hari
    if (validDate->mm == 4 || validDate->mm == 6 || validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}

//cek jika nama valid, return 1
int cekNama(const char *name){
    int validName = 1;
    int len = 0;
    len = strlen(name);
    for(int i = 0; i < len ; ++i){
    	//function isalpha untuk cek sebuah karakter adalah alfabet atau bukan
        if(!(isalpha(name[i])) && (name[i] != '\n') && (name[i] != ' ')){
            validName = 0;
            break;
        }
    }
    return validName;
}

// entry data event
void entryEvent(){
	system("cls");
    dataevent dataEvent = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_EVENT,"a+");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x                Entry data event                   x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
	do{
        //input tanggal event
		printf("\n\t\t\tMasukkan tanggal event (dd/mm/yyyy)= ");
        scanf("%d/%d/%d", &dataEvent.tanggalEvent.dd, &dataEvent.tanggalEvent.mm, &dataEvent.tanggalEvent.yyyy);
        //cek tanggal valid atau tidak
        status = cekTanggal(&dataEvent.tanggalEvent);
        if(!status){ //jika tanggal tidak valid
            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
        }
    }while(!status);
    do{
        printf("\n\t\t\tNama event = ");
        fflush(stdin);
        fgetsRemove(dataEvent.namaEvent,MAX_NAMA_EVENT,stdin);
        status = cekNama(dataEvent.namaEvent);
        if (!status)
        {
            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
        }
    }while(!status);
    do{
	    printf("\n\t\t\tMasukkan stok tiket = ");
	    printf("\n\t\t\t1. Festival = ");
	    scanf("%d", &dataEvent.jenisTiket[0]);
	    printf("\n\t\t\t2. Reguler = ");
	    scanf("%d", &dataEvent.jenisTiket[1]);
	    printf("\n\t\t\t3. VIP = ");
	    scanf("%d", &dataEvent.jenisTiket[2]);
		printf("\n\t\t\t4. Meet&Greet = ");
		scanf("%d", &dataEvent.jenisTiket[3]);
	    printf("\n\t\t\t5. Virtual = ");
	    scanf("%d", &dataEvent.jenisTiket[4]);
    }while(!status);
    dataEvent.totalTiket = dataEvent.jenisTiket[0] + dataEvent.jenisTiket[1] + dataEvent.jenisTiket[2] + dataEvent.jenisTiket[3] + dataEvent.jenisTiket[4];
	fprintf(fp, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", dataEvent.tanggalEvent.dd, dataEvent.tanggalEvent.mm, dataEvent.tanggalEvent.yyyy, dataEvent.namaEvent, dataEvent.jenisTiket[0], dataEvent.jenisTiket[1], dataEvent.jenisTiket[2], dataEvent.jenisTiket[3], dataEvent.jenisTiket[4], dataEvent.totalTiket);
	fclose(fp);
	printf("\n\n\t\tData berhasil ditambahkan!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

// entry data penjualan tiket
void entryData(){
	system("cls");
    datasales dataBase = {0};
    dataevent dataEvent[100];
    FILE *fp = NULL;
    FILE *fptr = NULL;
    int status = 0;
    int tiketUser, jumlahTiket, inputEvent;
	float total;
    fp = fopen(FILE_NAME,"a+");
    fptr = fopen(FILE_EVENT,"r+");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    if(fptr == NULL){
        printf("\n\t\t\tData event tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x           Entry data penjualan tiket              x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    do{
        //input tanggal transaksi
		printf("\n\t\t\tMasukkan tanggal transaksi (dd/mm/yyyy)= ");
        scanf("%d/%d/%d", &dataBase.tanggalTransaksi.dd, &dataBase.tanggalTransaksi.mm, &dataBase.tanggalTransaksi.yyyy);
        //cek tanggal valid atau tidak
        status = cekTanggal(&dataBase.tanggalTransaksi);
        if(!status){ //jika tanggal tidak valid
            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
        }
    }while(!status);
    do{
        printf("\n\t\t\tNama pelanggan = ");
        fflush(stdin);
        fgetsRemove(dataBase.namaPelanggan,MAX_NAMA_PELANGGAN,stdin);
        status = cekNama(dataBase.namaPelanggan);
        if (!status)
        {
            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
        }
    }while(!status);
    int i = 0;
	do{
		// membaca seluruh data dalam file
		while(!feof(fptr)){
			fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, &dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
			i++; // menghitung jumlah data
		}
		printf("\n\n\n\t\t\t=x=x=x=x=x=x                   List Event                      x=x=x=x=x=x=");
		for(int k=0; k<i; k++){
			printf("\n\n\t\t\t---------------------------------------------------------------------------");
			printf("\n\t\t\tNomor\t\t= %d", k+1);
			printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
			printf("\n\t\t\tNama Event\t= %s", dataEvent[k].namaEvent);
			printf("\n\t\t\t---------------------------------------------------------------------------");
		}
		printf("\n\n\t\t\tMasukkan nomor event = ");
		scanf("%d", &inputEvent);
		inputEvent-=1;
		strcpy(dataBase.namaEvent, dataEvent[inputEvent].namaEvent);
    }while(!status);
    do{
		status = 1;
		printf("\n\t\t\tMasukkan jenis tiket: ");
	    printf("\n\t\t\t1. Festival - Rp. 250.000,00");
	    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[0]);
		printf("\n\t\t\t2. Reguler - Rp. 750.000,00");
	    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[1]);
	    printf("\n\t\t\t3. VIP - Rp. 1.500.000,00");
	    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[2]);
	    printf("\n\t\t\t4. Meet&Greet - Rp. 3.500.000,00");
	    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[3]);
	    printf("\n\t\t\t5. Virtual - Rp. 150.000,00");
	    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[4]);
	    printf("\n\n\t\t\tPilih nomor jenis tiket = ");
		scanf("%d", &tiketUser);
		if(dataEvent[inputEvent].jenisTiket[tiketUser-1]<1){
			printf("\n\t\t\tMaaf, stok habis.\n");
			status = 0;
		}
	}while(!status);	
	do{
	    status = 1;
		printf("\n\t\t\tMasukkan jumlah tiket = ");
	    scanf("%d", &jumlahTiket);
	    getchar();
	    if(dataEvent[inputEvent].jenisTiket[tiketUser-1] < jumlahTiket){
	    	printf("\n\t\t\tMaaf, stok tidak mencukupi.\n");
	    	status = 0;
		}
	}while(!status);
	dataBase.jumlahTiket = jumlahTiket;
	fclose(fptr);
	fptr = fopen(FILE_EVENT,"w");
	for(int k=0; k<i; k++){
		if(k == inputEvent){
			dataEvent[k].jenisTiket[tiketUser-1] = dataEvent[k].jenisTiket[tiketUser-1] - jumlahTiket;
		}
		fprintf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy, dataEvent[k].namaEvent, dataEvent[k].jenisTiket[0], dataEvent[k].jenisTiket[1], dataEvent[k].jenisTiket[2], dataEvent[k].jenisTiket[3], dataEvent[k].jenisTiket[4], dataEvent[k].totalTiket);
	}
	fclose(fptr);
    do{
		status = 1;
		switch(tiketUser){
	        case 1:
				strcpy(dataBase.jenisTiket, "Festival");
				total = jumlahTiket * 250000;
	        	dataBase.total = total;
	        	dataBase.hargaTiket = 250000;
	        	break;
	        case 2:
	        	strcpy(dataBase.jenisTiket, "Reguler");
	       		total = jumlahTiket * 750000;
	        	dataBase.total = total;
	       		dataBase.hargaTiket = 750000;
	       		break;
	       	case 3:
	       		strcpy(dataBase.jenisTiket, "VIP");
				total = jumlahTiket * 1500000;
	       		dataBase.total = total;
	       		dataBase.hargaTiket = 1500000;
	       		break;
	       	case 4:
	       		strcpy(dataBase.jenisTiket, "Meet&Greet");
	       		total = jumlahTiket * 3500000;
	       		dataBase.total = total;
	       		dataBase.hargaTiket = 3500000;
	       		break;
	       	case 5:
	       		strcpy(dataBase.jenisTiket, "Virtual");
	       		total = jumlahTiket * 150000;
	       		dataBase.total = total;
	        	dataBase.hargaTiket = 150000;
	        	break;
	        default:
	       		printf("\n\t\t\tMaaf, pilihan anda salah\n");
	       		status = 0;
	      	 	break;
		}
	}while(!status);
    printf("\n\t\t\tTotal = Rp.%.0f,00", total);
	fprintf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%.0f\t%.0f\n", dataBase.tanggalTransaksi.dd, dataBase.tanggalTransaksi.mm, dataBase.tanggalTransaksi.yyyy, dataBase.namaPelanggan, dataBase.namaEvent, dataBase.jenisTiket, dataBase.jumlahTiket, dataBase.hargaTiket, dataBase.total);
	fclose(fp);
	printf("\n\n\t\t\tData berhasil ditambahkan!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

//mengurutkan data event berdasarkan tanggal event terdekat
void listDateEvent(){
	system("cls");
    dataevent dataEvent[100];
    FILE *fptr = NULL;
    fptr = fopen(FILE_EVENT,"r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    int counter = 1;
	int i = 0;
	while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, &dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai tanggal event terdekat
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			int dateK = (dataEvent[k].tanggalEvent.yyyy * 10000) + (dataEvent[k].tanggalEvent.mm * 100) + dataEvent[k].tanggalEvent.dd;
			int dateJ = (dataEvent[j].tanggalEvent.yyyy * 10000) + (dataEvent[j].tanggalEvent.mm * 100) + dataEvent[j].tanggalEvent.dd;
			if(dateK > dateJ){
				dataevent temp;
				temp = dataEvent[k];
				dataEvent[k] = dataEvent[j];
				dataEvent[j] = temp;
			}
		}
	}
	header();
    printf("\n\t\t\t=x=x=x=x=x=x     List berdasarkan tanggal event terdekat       x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    printf("\n\n\n --------------------------------------------------------------------------------------------------");
	printf("\n|     Tanggal     |      Event     |    Tiket    |    Tiket    |  Tiket  |   Tiket    |    Tiket   |" );
	printf("\n|                 |                |   Festival  |   Reguler   |   VIP   | Meet&Greet |   Virtual  |" );
	printf("\n --------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|    %2d/%2d/%d   | ", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("%12s   |     ", dataEvent[k].namaEvent);
		printf("%4d    |     ", dataEvent[k].jenisTiket[0]);
		printf("%4d    |  ", dataEvent[k].jenisTiket[1]);
		printf("%4d   |   ", dataEvent[k].jenisTiket[2]);
		printf("%4d     |    ", dataEvent[k].jenisTiket[3]);
		printf("%4d    | ", dataEvent[k].jenisTiket[4]);
	}
	printf("\n --------------------------------------------------------------------------------------------------");
	fclose(fptr);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan data event berdasarkan alfabet nama event
void listEventNama(){
	system("cls");
    dataevent dataEvent[100];
    FILE *fptr = NULL;
    fptr = fopen(FILE_EVENT,"r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
	int i = 0;
	while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, &dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai alfabet nama event
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			if(strcmp(dataEvent[k].namaEvent, dataEvent[j].namaEvent)>0){
				dataevent temp;
				temp = dataEvent[k];
				dataEvent[k] = dataEvent[j];
				dataEvent[j] = temp;
			}
		}
	}

	header();
    printf("\n\t\t\t=x=x=x=x=x=x          List berdasarkan nama event              x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    printf("\n\n\n --------------------------------------------------------------------------------------------------");
	printf("\n|     Tanggal     |      Event     |    Tiket    |    Tiket    |  Tiket  |   Tiket    |    Tiket   |" );
	printf("\n|                 |                |   Festival  |   Reguler   |   VIP   | Meet&Greet |   Virtual  |" );
	printf("\n --------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|    %2d/%2d/%d   | ", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("%12s   |     ", dataEvent[k].namaEvent);
		printf("%4d    |     ", dataEvent[k].jenisTiket[0]);
		printf("%4d    |  ", dataEvent[k].jenisTiket[1]);
		printf("%4d   |   ", dataEvent[k].jenisTiket[2]);
		printf("%4d     |    ", dataEvent[k].jenisTiket[3]);
		printf("%4d    | ", dataEvent[k].jenisTiket[4]);
	}
	printf("\n --------------------------------------------------------------------------------------------------");
	fclose(fptr);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan data event berdasarkan total stok terbanyak
void listStock(){
	system("cls");
    dataevent dataEvent[100];
    FILE *fptr = NULL;
    fptr = fopen(FILE_EVENT,"r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
	int i = 0;
	while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, &dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	//bubble sort untuk mengurutkan berdasarkan total stok terbanyak
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			int dataK = dataEvent[k].jenisTiket[0] + dataEvent[k].jenisTiket[1] + dataEvent[k].jenisTiket[2] + dataEvent[k].jenisTiket[3] + dataEvent[k].jenisTiket[4];
			int dataJ = dataEvent[j].jenisTiket[0] + dataEvent[j].jenisTiket[1] + dataEvent[j].jenisTiket[2] + dataEvent[j].jenisTiket[3] + dataEvent[j].jenisTiket[4];
			if(dataK < dataJ){
				dataevent temp;
				temp = dataEvent[k];
				dataEvent[k] = dataEvent[j];
				dataEvent[j] = temp;
			}
		}
	}
	header();
    printf("\n\t\t\t=x=x=x=x=x=x      List berdasarkan total stok terbanyak        x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    printf("\n\n\n -------------------------------------------------------------------------------------------------------------");
	printf("\n|     Tanggal     |      Event     |    Tiket    |    Tiket    |  Tiket  |   Tiket    |    Tiket   |   Total  |" );
	printf("\n|                 |                |   Festival  |   Reguler   |   VIP   | Meet&Greet |   Virtual  |   Stok   |" );
	printf("\n -------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|    %2d/%2d/%d   | ", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("%12s   |     ", dataEvent[k].namaEvent);
		printf("%4d    |     ", dataEvent[k].jenisTiket[0]);
		printf("%4d    |  ", dataEvent[k].jenisTiket[1]);
		printf("%4d   |   ", dataEvent[k].jenisTiket[2]);
		printf("%4d     |    ", dataEvent[k].jenisTiket[3]);
		printf("%4d    | ", dataEvent[k].jenisTiket[4]);
		printf("%5d    |", dataEvent[k].jenisTiket[0] + dataEvent[k].jenisTiket[1] + dataEvent[k].jenisTiket[2] + dataEvent[k].jenisTiket[3] + dataEvent[k].jenisTiket[4]);
	}
	printf("\n -------------------------------------------------------------------------------------------------------------");
	fclose(fptr);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan data event berdasarkan total tiket terjual
void listSold(){
	system("cls");
    dataevent dataEvent[100];
    FILE *fptr = NULL;
    fptr = fopen(FILE_EVENT,"r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
	int i = 0;
	while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, &dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	//bubble sort untuk mengurutkan berdasarkan total tiket terjual
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			int dataK = dataEvent[k].totalTiket - (dataEvent[k].jenisTiket[0] + dataEvent[k].jenisTiket[1] + dataEvent[k].jenisTiket[2] + dataEvent[k].jenisTiket[3] + dataEvent[k].jenisTiket[4]);
			int dataJ = dataEvent[k].totalTiket - (dataEvent[j].jenisTiket[0] + dataEvent[j].jenisTiket[1] + dataEvent[j].jenisTiket[2] + dataEvent[j].jenisTiket[3] + dataEvent[j].jenisTiket[4]);
			if(dataK < dataJ){
				dataevent temp;
				temp = dataEvent[k];
				dataEvent[k] = dataEvent[j];
				dataEvent[j] = temp;
			}
		}
	}
	header();
    printf("\n\t\t\t=x=x=x=x=x=x       List berdasarkan total tiket terjual        x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    printf("\n\n\n -------------------------------------------------------------------------------------------------------------");
	printf("\n|     Tanggal     |      Event     |    Tiket    |    Tiket    |  Tiket  |   Tiket    |    Tiket   |   Total  |" );
	printf("\n|                 |                |   Festival  |   Reguler   |   VIP   | Meet&Greet |   Virtual  |  Terjual |" );
	printf("\n -------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|    %2d/%2d/%d   | ", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("%12s   |     ", dataEvent[k].namaEvent);
		printf("%4d    |     ", dataEvent[k].jenisTiket[0]);
		printf("%4d    |  ", dataEvent[k].jenisTiket[1]);
		printf("%4d   |   ", dataEvent[k].jenisTiket[2]);
		printf("%4d     |    ", dataEvent[k].jenisTiket[3]);
		printf("%4d    | ", dataEvent[k].jenisTiket[4]);
		printf("%5d    |", dataEvent[k].totalTiket - (dataEvent[k].jenisTiket[0] + dataEvent[k].jenisTiket[1] + dataEvent[k].jenisTiket[2] + dataEvent[k].jenisTiket[3] + dataEvent[k].jenisTiket[4]));
	}
	printf("\n -------------------------------------------------------------------------------------------------------------");
	fclose(fptr);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan laporan penjualan berdasarkan tanggal transaksi terbaru
void listDate(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x       List berdasarkan tanggal transaksi          x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			int dateK = (dataBase[k].tanggalTransaksi.yyyy * 10000) + (dataBase[k].tanggalTransaksi.mm * 100) + dataBase[k].tanggalTransaksi.dd;
			int dateJ = (dataBase[j].tanggalTransaksi.yyyy * 10000) + (dataBase[j].tanggalTransaksi.mm * 100) + dataBase[j].tanggalTransaksi.dd;
			if(dateK < dateJ){
				datasales temp;
				temp = dataBase[k];
				dataBase[k] = dataBase[j];
				dataBase[j] = temp;
			}
		}
	}
	printf("\n\n\n ---------------------------------------------------------------------------------------------------------------");
	printf("\n|    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan laporan penjualan berdasarkan alfabet nama pelanggan
void listNamaUser(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x         List berdasarkan nama pelanggan           x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai alfabet nama pelanggan
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			if(strcmp(dataBase[k].namaPelanggan, dataBase[j].namaPelanggan)>0){
				datasales temp;
				temp = dataBase[k];
				dataBase[k] = dataBase[j];
				dataBase[j] = temp;
			}
		}
	}
	printf("\n\n\n ---------------------------------------------------------------------------------------------------------------");
	printf("\n|    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan laporan penjualan berdasarkan alfabet nama event
void listNamaEvent(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x           List berdasarkan nama event             x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai alfabet nama event
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			if(strcmp(dataBase[k].namaEvent, dataBase[j].namaEvent)>0){
				datasales temp;
				temp = dataBase[k];
				dataBase[k] = dataBase[j];
				dataBase[j] = temp;
			}
		}
	}
	printf("\n\n\n ---------------------------------------------------------------------------------------------------------------");
	printf("\n|    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan laporan penjualan berdasarkan jumlah tiket terbanyak
void listJumlah(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x          List berdasarkan jumlah tiket            x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai jumlah tiket yang terbanyak
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			if(dataBase[k].jumlahTiket < dataBase[j].jumlahTiket){
				datasales temp;
				temp = dataBase[k];
				dataBase[k] = dataBase[j];
				dataBase[j] = temp;
			}
		}
	}
	printf("\n\n\n ---------------------------------------------------------------------------------------------------------------");
	printf("\n|    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

//mengurutkan laporan penjualan berdasarkan total pembelian terbanyak
void listTotal(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp = fopen(FILE_NAME,"r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x        List berdasarkan total pembayaran          x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int counter = 1;
	int i = 0;
	while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	//bubble sort untuk mengurutkan sesuai total pembelian terbanyak
	for(int k=0; k<i; k++){
		for(int j=k; j<i; j++){
			if(dataBase[k].total < dataBase[j].total){
				datasales temp;
				temp = dataBase[k];
				dataBase[k] = dataBase[j];
				dataBase[j] = temp;
			}
		}
	}
	printf("\n\n\n ---------------------------------------------------------------------------------------------------------------");
	printf("\n|    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ---------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getch();
}

// search penjualan berdasarkan nama pelanggan
void searchNamaUser(){
    system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp=fopen(FILE_NAME, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x        Search berdasarkan nama pelanggan          x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    char nama[20];
    printf("\n\n\n\t\t\tMasukkan nama pelanggan: ");
    fflush(stdin);
    scanf("%s", &nama);
    int flag = 0, i = 0;
    //linear search
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, dataBase[i].namaPelanggan, dataBase[i].namaEvent, dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	for(int k = 0; k < i; k++){
		if(strcmpi(nama, dataBase[k].namaPelanggan) == 0){
            flag = 1;
	        printf("\n\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|     Tanggal     |     Pelanggan     |      Event     |     Tiket     |  Jumlah  |    Harga    |     Total    |" );
			printf("\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|    %2d/%2d/%d   |   ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
			printf("%12s    | ", dataBase[k].namaPelanggan);
			printf("%12s   |  ", dataBase[k].namaEvent);
			printf("%10s   |    ", dataBase[k].jenisTiket);
			printf("%2d    |  ", dataBase[k].jumlahTiket);
			printf("%10.2f | ", dataBase[k].hargaTiket);
			printf("%12.2f |", dataBase[k].total);
			printf("\n --------------------------------------------------------------------------------------------------------------");
        }
    }
    if(flag==0)
        printf("\n\t\t\tData tidak ditemukan.\n");
    else{
    }
    fclose(fp);
    printf("\n\n\n\t\t\tEnter untuk kembali ke menu.....");
	getch();
}

// search penjualan berdasarkan nama Event
void searchNamaEvent(){
    system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp=fopen(FILE_NAME, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x          Search berdasarkan nama event            x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    char nama[20];
    printf("\n\n\n\t\t\tMasukkan nama event: ");
    fflush(stdin);
    scanf("%s", &nama);
    int flag = 0, i = 0;
    //linear search
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, dataBase[i].namaPelanggan, dataBase[i].namaEvent, dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	for(int k = 0; k < i; k++){
		if(strcmpi(nama, dataBase[k].namaEvent) == 0){
            flag = 1;
	        printf("\n\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|     Tanggal     |     Pelanggan     |      Event     |     Tiket     |  Jumlah  |    Harga    |     Total    |" );
			printf("\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|    %2d/%2d/%d   |   ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
			printf("%12s    | ", dataBase[k].namaPelanggan);
			printf("%12s   |  ", dataBase[k].namaEvent);
			printf("%10s   |    ", dataBase[k].jenisTiket);
			printf("%2d    |  ", dataBase[k].jumlahTiket);
			printf("%10.2f | ", dataBase[k].hargaTiket);
			printf("%12.2f |", dataBase[k].total);
			printf("\n --------------------------------------------------------------------------------------------------------------");
        }
    }
    if(flag==0)
        printf("\n\t\t\tData tidak ditemukan.\n");
    else{
    }
    fclose(fp);
    printf("\n\n\n\t\t\tEnter untuk kembali ke menu.....");
	getch();
}

void searchJenisTiket(){
	system("cls");
    datasales dataBase[100];
    FILE *fp = NULL;
    fp=fopen(FILE_NAME, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x          Search berdasarkan jenis tiket           x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    int choice;
    char jenis[20];
    printf("\n\n\n\t\t\tPilih jenis tiket: ");
    printf("\n\t\t\t1. Festival");
    printf("\n\t\t\t2. Reguler");
    printf("\n\t\t\t3. VIP");
	printf("\n\t\t\t4. Meet&Greet");
    printf("\n\t\t\t5. Virtual");
    printf("\n\n\n\t\t\tPilihan anda -> ");
    fflush(stdin);
	scanf("%d", &choice);
    switch(choice){
		case 1:
			strcpy(jenis, "Festival");
        	break;
        case 2:
        	strcpy(jenis, "Reguler");
       		break;
       	case 3:
       		strcpy(jenis, "VIP");
       		break;
       	case 4:
       		strcpy(jenis, "Meet&Greet");
       		break;
       	case 5:
       		strcpy(jenis, "Virtual");
        	break;
        default:
       		printf("\n\t\t\tMaaf, pilihan anda salah\n");
      	 	break;
	}
    int flag = 0, i = 0;
    //linear search
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, dataBase[i].namaPelanggan, dataBase[i].namaEvent, dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	for(int k = 0; k < i; k++){
		if(strcmp(jenis, dataBase[k].jenisTiket) == 0){
            flag = 1;
	        printf("\n\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|     Tanggal     |     Pelanggan     |      Event     |     Tiket     |  Jumlah  |    Harga    |     Total    |" );
			printf("\n --------------------------------------------------------------------------------------------------------------");
			printf("\n|    %2d/%2d/%d   |   ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
			printf("%12s    | ", dataBase[k].namaPelanggan);
			printf("%12s   |  ", dataBase[k].namaEvent);
			printf("%10s   |    ", dataBase[k].jenisTiket);
			printf("%2d    |  ", dataBase[k].jumlahTiket);
			printf("%10.2f | ", dataBase[k].hargaTiket);
			printf("%12.2f |", dataBase[k].total);
			printf("\n --------------------------------------------------------------------------------------------------------------");
        }
    }
    if(flag==0)
        printf("\n\t\t\tData tidak ditemukan.\n");
    fclose(fp);
    printf("\n\n\n\t\t\tEnter untuk kembali ke menu.....");
	getch();
}

// search data event berdasarkan nama Event
void cariEvent(){
    system("cls");
    dataevent dataEvent[100];
    FILE *fp = NULL;
    fp=fopen(FILE_EVENT, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    header();
    printf("\n\t\t\t=x=x=x=x=x=x          Search berdasarkan nama event            x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
    char nama[20];
    printf("\n\n\n\t\t\tMasukkan nama event: ");
    fflush(stdin);
    scanf("%s", &nama);
    int flag = 0, i = 0;
    //linear search
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	for(int k = 0; k < i; k++){
		if(strcmpi(nama, dataEvent[k].namaEvent) == 0){
            flag = 1;
		    printf("\n\n\n --------------------------------------------------------------------------------------------------");
			printf("\n|     Tanggal     |      Event     |    Tiket    |    Tiket    |  Tiket  |   Tiket    |    Tiket   |" );
			printf("\n|                 |                |   Festival  |   Reguler   |   VIP   | Meet&Greet |   Virtual  |" );
			printf("\n --------------------------------------------------------------------------------------------------");
			printf("\n|    %2d/%2d/%d   | ", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
			printf("%12s   |     ", dataEvent[k].namaEvent);
			printf("%4d    |     ", dataEvent[k].jenisTiket[0]);
			printf("%4d    |  ", dataEvent[k].jenisTiket[1]);
			printf("%4d   |   ", dataEvent[k].jenisTiket[2]);
			printf("%4d     |    ", dataEvent[k].jenisTiket[3]);
			printf("%4d    | ", dataEvent[k].jenisTiket[4]);
			printf("\n --------------------------------------------------------------------------------------------------");
    	}
    }
    if(flag==0)
        printf("\n\t\t\tData tidak ditemukan.\n");
    fclose(fp);
    printf("\n\n\n\t\t\tEnter untuk kembali ke menu.....");
	getch();
}

void editData(){
	system("cls");
    datasales dataBase[100];
    dataevent dataEvent[100];
    header();
    printf("\n\t\t\t=x=x=x=x=x=x               Update data penjualan               x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
	FILE *fp;
	FILE *fptr;
    int i = 0, status = 0, userInput;
    int inputEvent, tiketUser, jumlahTiket, total;
    fp = fopen(FILE_NAME, "r");
    fptr = fopen(FILE_EVENT, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	printf("\n\n\n ----------------------------------------------------------------------------------------------------------------------");
	printf("\n|  No  |    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ----------------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n| %3d  ", k+1);
		printf("|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ----------------------------------------------------------------------------------------------------------------------");
	fclose(fp);
	do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor data yang ingin diupdate = ");
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fp = fopen(FILE_NAME, "w");
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			do{
		        //input tanggal transaksi
				printf("\n\t\t\tMasukkan tanggal transaksi (dd/mm/yyyy)= ");
		        scanf("%d/%d/%d", &dataBase[k].tanggalTransaksi.dd, &dataBase[k].tanggalTransaksi.mm, &dataBase[k].tanggalTransaksi.yyyy);
		        //cek tanggal valid atau tidak
		        status = cekTanggal(&dataBase[k].tanggalTransaksi);
		        if(!status){ //jika tanggal tidak valid
		            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
		        }
		    }while(!status);
		    do{
		        printf("\n\t\t\tNama pelanggan = ");
		        fflush(stdin);
		        fgetsRemove(dataBase[k].namaPelanggan,MAX_NAMA_PELANGGAN,stdin);
		        status = cekNama(dataBase[k].namaPelanggan);
		        if (!status)
		        {
		            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
		        }
		    }while(!status);
		    int j = 0;
			do{
				// membaca seluruh data dalam file
				while(!feof(fptr)){
					fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[j].tanggalEvent.dd, &dataEvent[j].tanggalEvent.mm, &dataEvent[j].tanggalEvent.yyyy, &dataEvent[j].namaEvent, &dataEvent[j].jenisTiket[0], &dataEvent[j].jenisTiket[1], &dataEvent[j].jenisTiket[2], &dataEvent[j].jenisTiket[3], &dataEvent[j].jenisTiket[4], &dataEvent[j].totalTiket);
					j++; // menghitung jumlah data
				}
				printf("\n\n\n\t\t\t=x=x=x=x=x=x                   List Event                      x=x=x=x=x=x=");
				for(int k=0; k<j; k++){
					printf("\n\n\t\t\t---------------------------------------------------------------------------");
					printf("\n\t\t\tNomor\t\t= %d", k+1);
					printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
					printf("\n\t\t\tNama Event\t= %s", dataEvent[k].namaEvent);
					printf("\n\t\t\t---------------------------------------------------------------------------");
				}
				do{
					status = 1;
					printf("\n\n\t\t\tMasukkan nomor event = ");
					scanf("%d", &inputEvent);
					if(inputEvent > i || inputEvent < 1){
			    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
			    		status = 0;
					}
				}while(!status);
				inputEvent-=1;
				strcpy(dataBase[k].namaEvent, dataEvent[inputEvent].namaEvent);
		    }while(!status);
		    do{
				status = 1;
				printf("\n\t\t\tMasukkan jenis tiket: ");
			    printf("\n\t\t\t1. Festival - Rp. 250.000,00");
			    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[0]);
				printf("\n\t\t\t2. Reguler - Rp. 750.000,00");
			    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[1]);
			    printf("\n\t\t\t3. VIP - Rp. 1.500.000,00");
			    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[2]);
			    printf("\n\t\t\t4. Meet&Greet - Rp. 3.500.000,00");
			    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[3]);
			    printf("\n\t\t\t5. Virtual - Rp. 150.000,00");
			    printf("\n\t\t\t   Stok tersisa = %d", dataEvent[inputEvent].jenisTiket[4]);
			    printf("\n\n\t\t\tPilih nomor jenis tiket = ");
				scanf("%d", &tiketUser);
			}while(!status);	
			do{
			    status = 1;
				printf("\n\t\t\tMasukkan jumlah tiket = ");
			    scanf("%d", &jumlahTiket);
			    getchar();
			    if(jumlahTiket <= 0){
					printf("\n\t\t\tJumlah tiket tidak bisa bernilai kurang dari 1.\n");
					status = 0;
				}
			}while(!status);
			dataBase[k].jumlahTiket = jumlahTiket;
		    do{
				status = 1;
				switch(tiketUser){
			        case 1:
						strcpy(dataBase[k].jenisTiket, "Festival");
						total = jumlahTiket * 250000;
			        	dataBase[k].total = total;
			        	dataBase[k].hargaTiket = 250000;
			        	break;
			        case 2:
			        	strcpy(dataBase[k].jenisTiket, "Reguler");
			       		total = jumlahTiket * 750000;
			        	dataBase[k].total = total;
			       		dataBase[k].hargaTiket = 750000;
			       		break;
			       	case 3:
			       		strcpy(dataBase[k].jenisTiket, "VIP");
						total = jumlahTiket * 1500000;
			       		dataBase[k].total = total;
			       		dataBase[k].hargaTiket = 1500000;
			       		break;
			       	case 4:
			       		strcpy(dataBase[k].jenisTiket, "Meet&Greet");
			       		total = jumlahTiket * 3500000;
			       		dataBase[k].total = total;
			       		dataBase[k].hargaTiket = 3500000;
			       		break;
			       	case 5:
			       		strcpy(dataBase[k].jenisTiket, "Virtual");
			       		total = jumlahTiket * 150000;
			       		dataBase[k].total = total;
			        	dataBase[k].hargaTiket = 150000;
			        	break;
			        default:
			       		printf("\n\t\t\tMaaf, pilihan anda salah\n");
			       		status = 0;
			      	 	break;
				}
			}while(!status);
		}
		fprintf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%.0f\t%.0f\n", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy, dataBase[k].namaPelanggan, dataBase[k].namaEvent, dataBase[k].jenisTiket, dataBase[k].jumlahTiket, dataBase[k].hargaTiket, dataBase[k].total);
	}
	fclose(fp);
	fclose(fptr);
    printf("\n\n\t\t\tData berhasil diupdate!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void editEvent(){
    system("cls");
    dataevent dataEvent[100];
    header();
    printf("\n\t\t\t=x=x=x=x=x=x                Update data event                  x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
	FILE *fptr;
    int userInput, dd, mm, yy, total;
	char nama[MAX_NAMA_EVENT];
	int jenis[MAX_TIKET_EVENT];
    int i = 0, status = 0;
    fptr = fopen(FILE_EVENT, "r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	printf("\n\n\t\t\t=x=x=x=x=x=x                   List Event                      x=x=x=x=x=x=");
	for(int k=0; k<i; k++){
		printf("\n\n\t\t\t---------------------------------------------------------------------------");
		printf("\n\t\t\tNomor\t\t= %d", k+1);
		printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("\n\t\t\tNama Event\t= %s", dataEvent[k].namaEvent);
		printf("\n\t\t\t---------------------------------------------------------------------------");
	}
	fclose(fptr);
    do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor event yang ingin diubah = ");
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fptr = fopen(FILE_EVENT, "w");
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			do{
		        //input tanggal event
				printf("\n\t\t\tMasukkan tanggal event yang baru (dd/mm/yyyy)= ");
		        scanf("%d/%d/%d", &dataEvent[k].tanggalEvent.dd, &dataEvent[k].tanggalEvent.mm, &dataEvent[k].tanggalEvent.yyyy);
		        //cek tanggal valid atau tidak
		        status = cekTanggal(&dataEvent[k].tanggalEvent);
		        if(!status){ //jika tanggal tidak valid
		            printf("\n\t\t\tTanggal yang dimasukkan salah. Tolong ulangi.\n");
		        }
		    }while(!status);
		    do{
		        printf("\n\t\t\tMasukkan nama event yang baru = ");
		        fflush(stdin);
		        fgetsRemove(dataEvent[k].namaEvent,MAX_NAMA_EVENT,stdin);
		        status = cekNama(dataEvent[k].namaEvent);
		        if (!status)
		        {
		            printf("\n\t\t\tNama tidak valid. Tolong ulangi.\n");
		        }
		    }while(!status);
		    do{
			    printf("\n\t\t\tMasukkan stok tiket yang baru = ");
			    printf("\n\t\t\t1. Festival = ");
			    scanf("%d", &dataEvent[k].jenisTiket[0]);
			    printf("\n\t\t\t2. Reguler = ");
			    scanf("%d", &dataEvent[k].jenisTiket[1]);
			    printf("\n\t\t\t3. VIP = ");
			    scanf("%d", &dataEvent[k].jenisTiket[2]);
				printf("\n\t\t\t4. Meet&Greet = ");
				scanf("%d", &dataEvent[k].jenisTiket[3]);
			    printf("\n\t\t\t5. Virtual = ");
			    scanf("%d", &dataEvent[k].jenisTiket[4]);
		    }while(!status);
		    dataEvent[k].totalTiket = dataEvent[k].jenisTiket[0] + dataEvent[k].jenisTiket[1] + dataEvent[k].jenisTiket[2] + dataEvent[k].jenisTiket[3] + dataEvent[k].jenisTiket[4];
		}
		fprintf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy, dataEvent[k].namaEvent, dataEvent[k].jenisTiket[0], dataEvent[k].jenisTiket[1], dataEvent[k].jenisTiket[2], dataEvent[k].jenisTiket[3], dataEvent[k].jenisTiket[4], dataEvent[k].totalTiket);
    }
    fclose(fptr);
    printf("\n\n\t\t\tData berhasil diupdate!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void hapusData(){
	system("cls");
    datasales dataBase[100];
    header();
    printf("\n\t\t\t=x=x=x=x=x=x               Hapus data penjualan                x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
	FILE *fp;
    int i = 0, status = 0, userInput;
    fp = fopen(FILE_NAME, "r");
    if(fp == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    while(!feof(fp)){
		fscanf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%f\t%f\n", &dataBase[i].tanggalTransaksi.dd, &dataBase[i].tanggalTransaksi.mm, &dataBase[i].tanggalTransaksi.yyyy, &dataBase[i].namaPelanggan, &dataBase[i].namaEvent, &dataBase[i].jenisTiket, &dataBase[i].jumlahTiket, &dataBase[i].hargaTiket, &dataBase[i].total);
		i++;
	}
	printf("\n\n\n ----------------------------------------------------------------------------------------------------------------------");
	printf("\n|  No  |    Tanggal     |     Pelanggan    |      Event      |     Tiket     |  Jumlah  |     Harga     |     Total    |" );
	printf("\n ----------------------------------------------------------------------------------------------------------------------");
	for(int k=0; k<i; k++){
		printf("\n| %3d  ", k+1);
		printf("|   %2d/%2d/%d   |  ", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy);
		printf("%12s    | ", dataBase[k].namaPelanggan);
		printf("%12s    |  ", dataBase[k].namaEvent);
		printf("%10s   |    ", dataBase[k].jenisTiket);
		printf("%2d    |  ", dataBase[k].jumlahTiket);
		printf("%10.2f   | ", dataBase[k].hargaTiket);
		printf("%12.2f |", dataBase[k].total);
	}
	printf("\n ----------------------------------------------------------------------------------------------------------------------");
	fclose(fp);
    do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor data yang ingin dihapus = ");
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fp = fopen(FILE_NAME, "w");
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			continue;
		}
		fprintf(fp, "%d/%d/%d\t%s\t%s\t%s\t%d\t%.0f\t%.0f\n", dataBase[k].tanggalTransaksi.dd, dataBase[k].tanggalTransaksi.mm, dataBase[k].tanggalTransaksi.yyyy, dataBase[k].namaPelanggan, dataBase[k].namaEvent, dataBase[k].jenisTiket, dataBase[k].jumlahTiket, dataBase[k].hargaTiket, dataBase[k].total);
    }
    fclose(fp);
    printf("\n\n\t\t\tData berhasil dihapus!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void hapusEvent(){
	system("cls");
    dataevent dataEvent[100];
    header();
    printf("\n\t\t\t=x=x=x=x=x=x                 Hapus data event                  x=x=x=x=x=x=");
    printf("\n\t\t\t===========================================================================");
	FILE *fptr;
    int userInput, dd, mm, yy, total;
	char nama[MAX_NAMA_EVENT];
	int jenis[MAX_TIKET_EVENT];
    int i = 0, status = 0;
    fptr = fopen(FILE_EVENT, "r");
    if(fptr == NULL){
        printf("\n\t\t\tData tidak tersedia\n");
        exit(1);
    }
    while(!feof(fptr)){
		fscanf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", &dataEvent[i].tanggalEvent.dd, &dataEvent[i].tanggalEvent.mm, &dataEvent[i].tanggalEvent.yyyy, dataEvent[i].namaEvent, &dataEvent[i].jenisTiket[0], &dataEvent[i].jenisTiket[1], &dataEvent[i].jenisTiket[2], &dataEvent[i].jenisTiket[3], &dataEvent[i].jenisTiket[4], &dataEvent[i].totalTiket);
		i++;
	}
	printf("\n\n\t\t\t=x=x=x=x=x=x                   List Event                      x=x=x=x=x=x=");
	for(int k=0; k<i; k++){
		printf("\n\n\t\t\t---------------------------------------------------------------------------");
		printf("\n\t\t\tNomor\t\t= %d", k+1);
		printf("\n\t\t\tTanggal Event\t= %2d/%2d/%d", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy);
		printf("\n\t\t\tNama Event\t= %s", dataEvent[k].namaEvent);
		printf("\n\t\t\t---------------------------------------------------------------------------");
	}
	fclose(fptr);
	do{
    	status = 1;
		printf("\n\n\t\t\tMasukkan nomor event yang ingin dihapus = ");
    	scanf("%d", &userInput);
    	getchar();
    	if(userInput > i || userInput < 1){
    		printf("\n\n\t\t\tTolong masukkan data yang tersedia");
    		status = 0;
		}
	}while(!status);
    userInput-=1;
	fptr = fopen(FILE_EVENT, "w");
    for (int k = 0; k<i; k++){
	    if(k == userInput){
			continue;
		}
		fprintf(fptr, "%d/%d/%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", dataEvent[k].tanggalEvent.dd, dataEvent[k].tanggalEvent.mm, dataEvent[k].tanggalEvent.yyyy, dataEvent[k].namaEvent, dataEvent[k].jenisTiket[0], dataEvent[k].jenisTiket[1], dataEvent[k].jenisTiket[2], dataEvent[k].jenisTiket[3], dataEvent[k].jenisTiket[4], dataEvent[k].totalTiket);
    }
    fclose(fptr);
    printf("\n\n\t\t\tData berhasil dihapus!");
	printf("\n\n\n\t\t\t Enter untuk kembali ke menu.....");
	getchar();
}

void menuUser();
void menuPenjualan();
void menuEvent();

//menu cetak data event
void cetakEvent(){
	int choice = 0;
	do{
		header();
		printf("\n\t\t\t=x=x=x=x=x=x                 Sort data event                   x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
		printf("\n\n\n\t\t\tCetak data berdasarkan:");
		printf("\n\t\t\t1. Tanggal Event terdekat");
	    printf("\n\t\t\t2. Nama Event");
	    printf("\n\t\t\t3. Total tiket tersisa");
	    printf("\n\t\t\t4. Total tiket terjual");
	    printf("\n\n\t\t\t9. Kembali");
	    printf("\n\t\t\t0. Exit");
	    printf("\n\n\n\t\t\tPilihan anda -> ");
	    scanf("%d",&choice);
	    switch(choice){
	    case 1:
	        listDateEvent();
	        break;
	    case 2:
	        listEventNama();
	        break;
	    case 3:
	        listStock();
	        break;
	    case 4:
	        listSold();
	        break;
	    case 9:
	        menuEvent();
	        break;
	    case 0:
	        printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
	        exit(1);
	        break;
	    default:
	        printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
	    }
    }while(choice!=0);  
}

//menu cetak data penjualan
void cetakData(){
	int choice = 0;
	do{
		header();
		printf("\n\t\t\t=x=x=x=x=x=x          Sort laporan penjualan tiket             x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
		printf("\n\n\n\t\t\tCetak data berdasarkan:");
		printf("\n\t\t\t1. Tanggal transaksi");
	    printf("\n\t\t\t2. Nama pelanggan");
	    printf("\n\t\t\t3. Nama event");
	    printf("\n\t\t\t4. Jumlah tiket terbanyak");
	    printf("\n\t\t\t5. Total pembelian terbesar");
	    printf("\n\n\t\t\t9. Kembali");
		printf("\n\t\t\t0. Exit");
	    printf("\n\n\n\t\t\tPilihan anda -> ");
	    scanf("%d",&choice);
	    switch(choice){
	    case 1:
	        listDate();
	        break;
	    case 2:
	        listNamaUser();
	        break;
	    case 3:
	        listNamaEvent();
	        break;
	    case 4:
	        listJumlah();
	        break;
	    case 5:
	        listTotal();
	        break;
	    case 9:
	        menuPenjualan();
	        break;
	    case 0:
	        printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
	        exit(1);
	        break;
	    default:
	        printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
	    }
    }while(choice!=0);  
}

//pilihan menu search penjualan
void cariData(){
	int choice = 0;
	do{
		header();
    	printf("\n\t\t\t=x=x=x=x=x=x          Search laporan penjualan tiket           x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
		printf("\n\n\n\t\t\tCari data berdasarkan:");
	    printf("\n\t\t\t1. Nama pelanggan");
	    printf("\n\t\t\t2. Nama event");
	    printf("\n\t\t\t3. Jenis tiket");
	    printf("\n\n\t\t\t9. Kembali");
	    printf("\n\t\t\t0. Exit");
	    printf("\n\n\n\t\t\tPilihan anda -> ");
	    scanf("%d",&choice);
	    switch(choice){
	    case 1:
	        searchNamaUser();
	        break;
	    case 2:
	        searchNamaEvent();
	        break;
	    case 3:
	        searchJenisTiket();
	        break;
	    case 9:
	        menuPenjualan();
	        break;
	    case 0:
	        printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
	        exit(1);
	        break;
	    default:
	        printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
	    }
    }while(choice!=0);  
}

//pilihan menu penjualan
void menuPenjualan(){
	int choice = 0;
	do{
        header();
        printf("\n\t\t\t=x=x=x=x=x=x             <3   Menu Penjualan   <3              x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
        printf("\n\n\n\t\t\t1. Entry Penjualan");
        printf("\n\t\t\t2. Cetak Penjualan");
        printf("\n\t\t\t3. Cari Penjualan");
        printf("\n\t\t\t4. Edit Penjualan");
        printf("\n\t\t\t5. Hapus Penjualan");
        printf("\n\n\t\t\t9. Kembali");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tPilihan anda -> ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            entryData();
            break;
        case 2:
        	cetakData();
        	break;
        case 3:
            cariData();
            break;
        case 4:
            editData();
            break;
        case 5:
            hapusData();
            break;
        case 9:
            menuUser();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
        }
    }
    while(choice!=0);  
}

//pilihan menu event
void menuEvent(){
	int choice = 0;
	do{
        header();
        printf("\n\t\t\t=x=x=x=x=x=x               <3   Menu Event   <3                x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
        printf("\n\n\n\t\t\t1. Entry Event");
        printf("\n\t\t\t2. Cetak Event");
        printf("\n\t\t\t3. Cari Event");
        printf("\n\t\t\t4. Edit Event");
        printf("\n\t\t\t5. Hapus Event");
        printf("\n\n\t\t\t9. Kembali");
        printf("\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tPilihan anda -> ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            entryEvent();
            break;
        case 2:
        	cetakEvent();
        	break;
        case 3:
            cariEvent();
            break;
        case 4:
            editEvent();
            break;
        case 5:
            hapusEvent();
            break;
        case 9:
            menuUser();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
        }
    }
    while(choice!=0);  
}

//pilihan menu utama
void menuUser(){
	int choice = 0;
    do{
        header();
        printf("\n\t\t\t=x=x=x=x=x=x                 <3 Menu Utama <3                  x=x=x=x=x=x=");
    	printf("\n\t\t\t===========================================================================");
        printf("\n\n\n\t\t\t1. Menu Data Penjualan");
        printf("\n\t\t\t2. Menu Data Event");
        printf("\n\n\t\t\t0. Exit");
        printf("\n\n\n\t\t\tPilihan anda -> ");
        scanf("%d",&choice);
        switch(choice){
        case 1:
            menuPenjualan();
            break;
        case 2:
        	menuEvent();
        	break;
        case 0:
            printf("\n\n\n\t\t\t\tTerima kasih!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tMaaf, pilihan anda salah");
        }
    }
    while(choice!=0);  
}

int checkFile(const char *path){ // cek file sudah ada atau belum
	FILE *fp = fopen(path, "r");
    int status = 0; // default jika file tidak ada, return 0
    if (fp != NULL){
        status = 1; // jika file ada, return 1
        fclose(fp);
    }
    return status;
}

void createFile(){ //buat file jika file belum ada
	FILE *fp = NULL;
    int status = 0;
    status = checkFile(FILE_NAME);
    if(!status) {
        //membuat file
		fp = fopen(FILE_NAME,"w");
		if(fp == NULL){
        	printf("Error dalam pembuatan file.\n");
        	exit(1);
    	}
	}
	status = 0;
	status = checkFile(FILE_EVENT);
	if(!status) {
    	fp = fopen(FILE_EVENT,"w");
		if(fp == NULL){
        	printf("Error dalam pembuatan file event.\n");
        	exit(1);
    	}
        fclose(fp);
    }
}

void login(){
	//default login
	header();
	const char defaultUsername[] = "admin";
	const char defaultPassword[] = "admin";
	char username[20];
    char password[20];
    int tryL = 0;
    do{
        printf("\n\n\n\t\t\t\tUsername: ");
        fgetsRemove(username, sizeof(username),stdin);
        printf("\n\t\t\t\tPassword: ");
        fgetsRemove(password, sizeof(password),stdin);
		if((!strcmp(username, defaultUsername)) && (!strcmp(password, defaultPassword))){
            menuUser();
        }
        else{
            printf("\t\t\t\tMaaf, informasi yang Anda masukkan salah");
            tryL++;
        }
    }
    while(tryL<=3);
    if(tryL>3){	//jika percobaan gagal lebih dari 3 kali
        header();
        printf("\n\t\t\t\tLogin Gagal");
        printf("\n\t\t\t\tMaaf, Anda belum terdaftar.");
        getchar();
        exit(1);
    }
}

int main(){
    createFile();
    welcomeMessage();
    login();
    return 0;
}
