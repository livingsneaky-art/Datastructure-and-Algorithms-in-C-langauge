#include <stdio.h>

#define MAX 10

typedef struct{
	char data[MAX];
	int count;
}ArrayList;

void initList(ArrayList *L);
void insertFront(ArrayList *L, char data);
void insertRear(ArrayList *L, char data);
void insertPosition(ArrayList *L, char data, int position);
void insertSorted(ArrayList *L, char data);
void deleteFront(ArrayList *L);
void deleteRear(ArrayList *L);
void deletePosition(ArrayList *L, int position);
void display(ArrayList L);

int main(){
	
	ArrayList L;
	initList(&L);
	display(L);
	insertFront(&L, 1);
	insertFront(&L, 2);
	insertFront(&L, 3);
	insertFront(&L, 4);
	display(L);
	insertRear(&L, 5);
	display(L);
	insertPosition(&L, 6, 0);
	display(L);
	insertSorted(&L, 1);
	display(L);
	deleteFront(&L);
	display(L);
	deleteRear(&L);
	display(L);
	deletePosition(&L, 4);
	display(L);
	
	return 0;
}

void initList(ArrayList *L){
	L->count = 0;
}

void insertFront(ArrayList *L, char data){
	int i;
	if(L->count < MAX){
		for(i = L->count; i > 0 ; --i){
			L->data[i] = L->data[i-1];
		}
		L->data[i] = data;
		L->count++;
	}
}

void insertRear(ArrayList *L, char data){
	
	if(L->count < MAX){
		L->data[L->count] = data;
		L->count++;
	}
}

void insertPosition(ArrayList *L, char data, int position){
	int i;
	if(L->count < MAX){
		for(i = L->count-1; i >= position; --i){
			L->data[i+1] = L->data[i];
		}
		L->data[i+1] = data;
		L->count++;
	}
}

void insertSorted(ArrayList *L, char data){
	int i;
	if(L->count < MAX){
		for(i = L->count-1; i >= 0 && data < L->data[i]; --i){
			L->data[i+1] = L->data[i];
		}
		L->data[i+1] = data;
		L->count++;
	}
}

void deleteFront(ArrayList *L){
	int i;
	if(L->count > 0){
		for(i = 0; i < L->count; i++){
			L->data[i] = L->data[i+1];
		}
		L->count--;
	}
}

void deleteRear(ArrayList *L){
	int i;
	if(L->count > 0){
		L->count--;
	}
}

void deletePosition(ArrayList *L, int position){
	int i;
	if(L->count > 0){
		for(i = position; i < L->count; i++){
			L->data[i] = L->data[i+1];
		}
		L->count--;
	}
}

void display(ArrayList L){
	int i;
	printf("[ ");
	for(i = 0; i < L.count; i++){
		printf("%d ", L.data[i]);
	}
	printf("]\n");
}
