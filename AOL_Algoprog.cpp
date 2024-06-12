#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define max_rows 100
#define max_cols 8
#define max_len 100
struct properti{
	char lokasi[max_len];
	char kota[max_len];
	long int harga;
	int rooms;
	int bathroom;
	int carpark;
	char type[max_len];
	char furnish[max_len];
};
struct properti prt[max_rows];
	int total = 0;
	
void readFile(const char *file){
	FILE *fp = fopen(file,"r");
	if(!fp){
		printf("file tidak bisa di buka!");
		exit(1);
	}
	char line[max_len];
	//untuk tidak membaca header
	fgets(line, sizeof(line),fp);
	while(fgets(line,sizeof(line),fp) && total < max_rows){
		properti *prp = &prt[total++];
		sscanf(line, "%[^,],%[^,],%ld,%d,%d,%d,%[^,],%s",
			prp->lokasi, prp->kota, &prp->harga, &prp->rooms, &prp->bathroom,
			&prp->carpark, prp->type, prp->furnish);
	}
	fclose(fp);
	
}

void printData(int row){
	if(row > total){
		row = total;
	}
	printf ("Location\tCity\t\tPrice\tRooms\tBathroom\tCarpark\tType\tFurnish\n");
	for(long int i=0; i<row;i++){
		properti *prp = &prt[i];
		printf("%s\t%s\t%ld\t%d\t%d\t%d\t%s\t%s\n",
			prp->lokasi, prp->kota, prp->harga, prp->rooms, prp->bathroom,
			prp->carpark, prp->type, prp->furnish);
	}
}

void cariData(const char *column, const char *value){
	long int target = 0;
	printf ("Location\tCity\t\tPrice\tRooms\tBathroom\tCarpark\tType\tFurnish\n");
	for(long int i=0;i<total;i++){
		properti *prp = &prt [i];
		if((strcmp (column, "lokasi") == 0 && strcmp (prp -> lokasi, value) == 0) ||
            (strcmp (column, "kota") == 0 && strcmp (prp -> kota, value) == 0) ||
            (strcmp (column, "harga") == 0 && prp -> harga == atoi (value)) ||
            (strcmp (column, "Rooms") == 0 && prp -> rooms == atoi (value)) ||
            (strcmp (column, "Bathroom") == 0 && prp -> bathroom == atoi (value)) ||
            (strcmp (column, "Carpark") == 0 && prp -> carpark == atoi (value)) ||
            (strcmp (column, "Type") == 0 && strcmp (prp -> type, value) == 0) ||
            (strcmp (column, "Furnish") == 0 && strcmp (prp -> furnish, value) == 0)
		){
			 printf ("%s\t%s\t%ld\t%ld\t%ld\t%ld\t%s\t%s\n",
			prp->lokasi, prp->kota, prp->harga, prp->rooms, prp->bathroom,
			prp->carpark, prp->type, prp->furnish);
            target = 1;
		}
	}
	 if (!target) 
	{
        printf ("Data tidak di temukan!\n");
    }
}

void mengurutkanData (const char *column,  int ascending) 
{
    for ( int i = 0; i < total - 1; i++) 
	{
        for ( int j = i + 1; j < total; j++) 
		{
            long int compare = 0;
            if (strcmp (column, "harga") == 0) 
			{
                compare = prt[i].harga - prt[j].harga;
            } 
			else if (strcmp (column, "Rooms") == 0) 
			{
                compare = prt[i].rooms - prt[j].rooms;
            } 
			else if (strcmp (column, "Bathroom") == 0) 
			{
                compare = prt[i].bathroom - prt[j].bathroom;
            } 
			else if (strcmp (column, "Carpark") == 0) 
			{
                compare = prt[i].carpark - prt[j].carpark;
            } 
			else if (strcmp (column, "lokasi") == 0) 
			{
                compare = strcmp (prt[i].lokasi, prt[j].lokasi);
            } 
			else if (strcmp (column, "kota") == 0) 
			{
                compare = strcmp (prt[i].kota, prt[j].kota);
            } 
			else if (strcmp (column, "Type") == 0) 
			{
                compare = strcmp (prt[i].type, prt[j].type);
            } 
			else if (strcmp (column, "Furnish") == 0) 
			{
                compare = strcmp (prt[i].furnish, prt[j].furnish);
            }
            if ((ascending && compare > 0) || (!ascending && compare < 0)) 
			{
                properti temp = prt [i];
                prt [i] = prt [j];
                prt [j] = temp;
            }
        }
    }
    printData(10);
}

void exportData (const char *file) 
{
    FILE *fp = fopen (file, "w");
    if (!fp) 
	{
        printf ("Error: tidak bisa membuka file %s\n", file);
        return;
    }
    fprintf (fp, "Location,City,Price,Rooms,Bathroom,Carpark,Type,Furnish\n");
    for (long int i = 0; i < total; i++) 
	{
        properti *prp = &prt[i];
        fprintf (fp, "%s,%s,%ld,%ld,%ld,%ld,%s,%s\n",
			prp->lokasi, prp->kota, prp->harga, prp->rooms, prp->bathroom,
			prp->carpark, prp->type, prp->furnish);
    }
    fclose (fp);
    printf ("Data berhasil di export: %s!\n", file);
}

void menu(){
	printf("1. Display data \n");
	printf("2. cari Data \n");
	printf("3. Urutkan berdasarkan \n");
	printf("4. Export Data \n");
	printf("5. exit \n");
}

int main(){
	readFile ("file.csv");

     int pilihan;
     	do{
		menu();
		printf("ketik pilihan: ");
		scanf("%d",&pilihan);
		
		switch(pilihan){
			case 1:
				printf("\n");
			int row;
            printf ("Number of rows: ");
            scanf ("%d", &row);
            printData (row);
            printf("\n");
				break;
				case 2:
			char column [max_len], value [max_len];
            printf ("pilih kolom, cont'lokasi': ");
            scanf ("%s", column);
            printf ("Data apa yang dicari, cont'Sentul'? ");
            scanf ("%s", value);
            cariData (column, value);
            printf("\n");
					break;
					case 3:
			char kolom [max_len], order [max_len];
            printf ("pilih column: ");
            scanf ("%s", column);
            printf ("urutan asc atau dsc? ");
            scanf ("%s", order);
            mengurutkanData (column, strcmp (order, "asc") == 0);
            printf("\n");
            		case 4:
             char file [max_len];
            printf ("nama File: ");
            scanf ("%s", file);
            exportData (file);
            printf("\n");
					break;	
					
		}
		
	}while(pilihan != 5);
 
	return 0;
}
