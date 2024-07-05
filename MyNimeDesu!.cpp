#include<stdio.h>
#include<string.h>
struct anime{
	char ID[15];
	char judul[31];
	char genre[31];
	int rating;
};

void inputData(struct anime *list, int n){
	int i;
	for(i=0;i<n;i++){
		printf("Input ID anime: ");
		scanf("%s",list[i].ID);
		getchar();
		printf("Input judul anime: ");
		scanf("%[^\n]",list[i].judul);
		getchar();
		printf("Input genre anime: ");
		scanf("%s",list[i].genre);
		getchar();
		printf("Input rating anime: ");
		scanf("%d",&list[i].rating);
	}
}
void printToFile(FILE *fp, struct anime *list, int n){
	int i;
	fp = fopen("MyNimeDesu.txt","w");
	for(i=0;i<n;i++){
	fprintf(fp,"%s#%s#%s#%d\n",list[i].ID,list[i].judul,list[i].genre,list[i].rating);
	}
	fclose(fp);
}

void readFromFile(FILE *fp, struct anime *list, int n){
	fp = fopen("MyNimeDesu.txt","r");
	int i;
	char buffer[100];
	i=0;
	while(fgets(buffer, sizeof(buffer),fp)){
		sscanf(buffer,"%[^#]#%[^#]#%[^#]#%d",list[i].ID,list[i].judul,list[i].genre,&list[i].rating);
		i++;
	}
	fclose(fp);
}
void printToConsole(struct anime *list, int n){
	int i;
	for(i=0;i<n;i++){
		printf("ID anime: %s \n",list[i].ID);
		printf("Judul anime: %s \n",list[i].judul);
		printf("Genre anime: %s \n",list[i].genre);
		printf("rating anime: %d \n",list[i].rating);
	}
}

void sortDataASC(struct anime *list, int n){
	int i,j;
	anime temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(list[j].rating > list[j+1].rating){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}
void sortDataDSC(struct anime *list, int n){
	int i,j;
	anime temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-i-1;j++){
			if(list[j].rating < list[j+1].rating){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}
void sortDataStrASC(struct anime *list, int n){
	int i,j;
	anime temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(strcmp(list[j].ID,list[j+1].ID) > 0){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}
void sortDataStrDSC(struct anime *list, int n){
	int i,j;
	anime temp;
	for(i=0;i<n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(strcmp(list[j].ID,list[j+1].ID) < 0){
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

int searchData(struct anime *list, int target,int n){
	 int left = 0;
    int right = n - 1;
	int found = 0;
	int mid;
	while(left<=right){
		 mid = left + (right - left)/2;
		if(list[mid].rating == target){
			found =1;
			break;
		}
		if(list[mid].rating < target){
			left = mid + 1;
		}else{
			right = mid - 1;
		}
	}
	 if (found) {
        // Display the found element
        printf("ID anime: %s \n", list[mid].ID);
        printf("Judul anime: %s \n", list[mid].judul);
        printf("Genre anime: %s \n", list[mid].genre);
        printf("Rating anime: %d \n", list[mid].rating);

        // Check elements to the left of mid
        int i = mid - 1;
        while (i >= 0 && list[i].rating == target) {
            printf("ID anime: %s \n", list[i].ID);
            printf("Judul anime: %s \n", list[i].judul);
            printf("Genre anime: %s \n", list[i].genre);
            printf("Rating anime: %d \n", list[i].rating);
            i--;
        }
        
        // Check elements to the right of mid
        i = mid + 1;
        while (i < n && list[i].rating == target) {
            printf("ID anime: %s \n", list[i].ID);
            printf("Judul anime: %s \n", list[i].judul);
            printf("Genre anime: %s \n", list[i].genre);
            printf("Rating anime: %d \n", list[i].rating);
            i++;
        }
    } else {
        printf("Anime dengan rating %d tidak ditemukan\n", target);
    }
}
void menu(){
	printf("=================================\n");
	printf("SELAMAT DATANG DI MYnimedesu!\n");
	printf("=================================\n");
	printf("Silahkan pilih menunya: \n");
	printf("1.Input data: \n ");
	printf("2.Display data: \n");
	printf("3.Sort data: \n");
	printf("4.Search data(by rating[1-10]): \n");
	printf("5.Exit: \n");
}
int main(){
	int n,pilihan;
	printf("berapa datanya? ");
	scanf("%d",&n);

	struct anime list[n];
	FILE *fp;
	do{
		menu();
		printf("pilihan: ");
		scanf("%d",&pilihan);
		switch(pilihan){
			case 1:
				inputData(list,n);
				printToFile(fp,list,n);
				printf("Data Berhasil diInput! \n");
				break;
				case 2:
					readFromFile(fp,list,n);
					printToConsole(list,n);
					printf("Data Berhasil ditampilkan! \n");
					break;
					case 3:
						char str[10];
						char str2[10];
						char str3[10];
						readFromFile(fp,list,n);
						printf("mau sort by rating atau by ID?: ");
						scanf("%s",str2);
						
						if(strlen(str2) == 2){
							printf("mau urutan menaik atau menurun?: ");
							scanf("%s",str3);
							if(strlen(str3) == 6){
							sortDataStrASC(list,n);
							printToConsole(list,n);
							printf("data berhasil diSort! \n");
							}
							if(strlen(str3) == 7){
							sortDataStrDSC(list,n);
							printToConsole(list,n);
							printf("data berhasil diSort! \n");
							}
						}
						
						if(strlen(str2) == 6){
						printf("mau urutan menaik atau menurun?: ");
						scanf("%s",str);
						getchar();
						if(strlen(str) == 6){
							sortDataASC(list,n);
							printToConsole(list,n);
							printf("data berhasil diSort! \n");
						}if(strlen(str) == 7){
						sortDataDSC(list,n);
						printToConsole(list,n);
						printf("data berhasil diSort! \n");
						
						}
					}
						break;

						case 4:
							int target;
							readFromFile(fp,list,n);
							sortDataASC(list,n);
							printf("Anime Rating brapa mau di cari?: ");
							scanf("%d",&target);
							searchData(list,target,n);
							break;		
		}
		
	}while(pilihan != 5);
	return 0;
}
