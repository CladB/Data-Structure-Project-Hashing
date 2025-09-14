#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100

struct Data{
	char name[101]; // 3-50 characters
	int price; // Rp. 0 - Rp. 999.999
	int rating;  // 0 - 10 / 10
	char desc[201]; // 5 - 200 characters
	char id[11]; // first 3 letters of name + 2 random numbers
	Data* next;
}*hashtable[SIZE] = {NULL};

int numdish = 0;

Data* create(char name[], int price, int rating, char desc[], char id[]){
	Data* newnode = (Data*) malloc (sizeof(Data));
	strcpy(newnode->name,name);
	newnode->price = price;
	newnode->rating = rating;
	strcpy(newnode->desc,desc);
	strcpy(newnode->id,id);
	newnode->next = NULL;
	return newnode;
}

int hash(char id[]){
	int sum = 0;
	for(int i = 0; i < strlen(id); i++){
		sum += id[i];
	}
	return sum % SIZE;
}

void viewone(Data* dish){
	printf("\n");
	printf("Dish ID: %s\n", dish->id);
	printf("Dish name: %s\n", dish->name);
	if(dish->price == 0){
		printf("Price: FREE\n");
	}else{
		int temp = dish->price / 1000;
		int temp2 = dish->price % 1000;
		if(temp == 0){
			printf("Price: Rp. %d\n", temp2);
		}else{
			printf("Price: Rp. %d.%d\n", temp, temp2);
		}
	}
	printf("Rating: %d/10\n", dish->rating);
	printf("Description: %s\n", dish->desc);
	printf("\n");
}

void insertdish(Data* dish){
	int hashkey = hash(dish->id);
	if(hashtable[hashkey] == NULL){
		hashtable[hashkey] = dish;
	}else{
		Data* curr = hashtable[hashkey];
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = dish;
	}
	numdish++;
}

int confirmation(Data* dish){
	char confirm[5];
	viewone(dish);
	do{
		printf("Are you sure (yes/no)? ");
		gets(confirm);
	}while(strcmp(confirm,"yes") != 0 && strcmp(confirm,"no") != 0);
	
	
	if(strcmp(confirm, "yes") == 0){
		return 1;
	}else{
		return 0;
	}
}

void deletedish(char id[]){
	int hashkey = hash(id);
	
	Data* curr = hashtable[hashkey];
	if(hashtable[hashkey]==NULL){
		printf("Data not found!");
		return;
	}else if(strcmp(hashtable[hashkey]->id,id)==0){
		int flag = confirmation(hashtable[hashkey]);
		if(flag == 1){
			Data* todelete=hashtable[hashkey];
			hashtable[hashkey]=hashtable[hashkey]->next;
			printf("Dish ID %s is deleted!\b\n",todelete->id);
			free(todelete);
			numdish--;
			return;
		}else{
			printf("Deletion cancelled.\n");
			return;
		}
		
	}else{
		Data* temp=hashtable[hashkey];
		while(temp->next!=NULL){
			if(strcmp(temp->next->id,id)==0){
				int flag = confirmation(curr->next);
				if(flag == 1){
					Data* todelete=temp->next;
					printf("Dish ID %s is deleted!\b\n",todelete->id);
					temp->next=todelete->next;
					free(todelete);
					numdish--;
					return;
				}else{
					printf("Deletion cancelled.\n");
					return;
				}
				
			}
			temp=temp->next;
		}
		printf("Dish not found!\n");
	}
}

void searchdish(char id[]){
	int hashkey = hash(id);
	
	Data* curr = hashtable[hashkey];
	if(hashtable[hashkey]==NULL){
		printf("Data not found!");
		return;
	}else if(strcmp(hashtable[hashkey]->id,id)==0){
		viewone(hashtable[hashkey]);
		return;
	}else{
		Data* temp=hashtable[hashkey];
		while(temp->next!=NULL){
			if(strcmp(temp->next->id,id)==0){
				viewone(curr->next);
				return;
			}
			temp=temp->next;
		}
		printf("Dish not found!\n");
	}
}

void insertmenu(){
	char name[101]; // 3-50 characters
	int price; // Rp. 0 - Rp. 999.999
	int rating;  // 0 - 10 / 10
	char desc[201]; // 5 - 200 characters
	char id[11];
	int unique;
	
	do{
		printf("Input name (3 - 50 characters): ");
		gets(name);
	}while(strlen(name) < 3 || strlen(name) > 50);
	
	do{
		printf("Input price (0 - 999999): ");
		scanf("%d", &price);
	}while(price < 0 || price > 999999);
	
	do{
		printf("Input rating (0 - 10 out of 10): ");
		scanf("%d", &rating); getchar();
	}while(rating < 0 || rating > 10);
	
	do{
		printf("Input description (5 - 200 characters): ");
		gets(desc);
	}while(strlen(desc) < 5 || strlen(desc) > 200);
	
	int random = rand() % 100;
	sprintf(id, "%c%c%c%02d", name[0], name[1], name[2], random);
	
	Data* dish = create(name, price, rating, desc, id);
	insertdish(dish);
	viewone(dish);
	printf("Insert Success!\n");
	return;
}

void viewall(){
	if(numdish == 0){
		printf("No data yet.\n");
		return;
	}
	
	for(int i = 0; i < SIZE; i++){
		Data* curr = hashtable[i];
		while(curr != NULL){
			viewone(curr);
			curr = curr->next;
		}
	}
}

void deletemenu(){
	if(numdish == 0){
		printf("No data yet.\n");
		return;
	}
	viewall();
	char id[101];
	printf("\nDish ID to be deleted: ");
	gets(id);
	deletedish(id);
}

void searchmenu(){
	if(numdish == 0){
		printf("No data yet.\n");
		return;
	}
	char id[101];
	printf("\nSearch a dish based on ID: ");
	gets(id);
	searchdish(id);
}

int main(){
	int choice;
	do{
		printf("Restaurant Menu List\n");
		printf("1. Insert Dish\n");
		printf("2. View all dishes\n");
		printf("3. Delete Dish\n");
		printf("4. Search Dish\n");
		printf("5. Exit\n");
		printf(">> ");
		scanf("%d", &choice); getchar();
		
		if(choice == 1){
			insertmenu();
		}else if(choice == 2){
			viewall();
		}else if(choice == 3){
			deletemenu();
		}else if(choice == 4){
			searchmenu();
		}
	}while(choice != 5);
	return 0;
}
