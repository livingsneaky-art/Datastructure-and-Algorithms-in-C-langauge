#include <stdio.h>
#include <stdlib.h>

#define Max 8

typedef char SET[Max];

void initSet(SET *C);
void createSet(SET C, SET data);
void insertSet(SET C, int position);
void deleteSet(SET C, int position);
SET *getUnion(SET A, SET B);
SET *getIntersection(SET A, SET B);
SET *getDifference(SET A, SET B);
void display(SET C);

int main(){
	SET A = {0, 1, 0, 1, 1, 1, 0, 0};
	SET B = {1, 0, 0, 1, 0, 1, 1, 1};
	SET *C;
	initSet(C);
	
	puts("\nSET A: ");display(A);
	puts("\nSET B: ");display(B);
	
	insertSet(A, 2);
	puts("\nInsert: ");display(A);
	
	deleteSet(A, 2);
	puts("\nDelete: ");display(A);
	
	C = getUnion(A, B);
	puts("\nUnion: ");display(*C);
	
	C = getIntersection(A, B);
	puts("\nIntersection: ");display(*C);
	
	C = getDifference(A, B);
	puts("\nDifference: ");display(*C);
	
	return 0;
}

void initSet(SET *C){
	C = NULL;
}

void createSet(SET C, SET data){
	int x;
	
	for(x = 0; x < Max; x++){
		C[data[x]] = 1;
	}
}

void insertSet(SET C, int position){
	if(position < Max){
		C[position] = C[position] | 1;
	}
}

void deleteSet(SET C, int position){
	if(position < Max){
		C[position] = C[position] & 0;
	}
}

SET *getUnion(SET A, SET B){
	SET *C;
	int x;
	initSet(C);
	
	C = (SET*)malloc(sizeof(SET)*Max);
	if(C != NULL){
		for(x = 0; x < Max; x++){
			(*C)[x] = A[x] | B[x];
		}
	}
	return C;
}

SET *getIntersection(SET A, SET B){
	SET *C;
	int x;
	initSet(C);
	
	C = (SET*)malloc(sizeof(SET)*Max);
	if(C != NULL){
		for(x = 0; x < Max; x++){
			(*C)[x] = A[x] & B[x];
		}
	}
	return C;
}

SET *getDifference(SET A, SET B){
	SET *C;
	int x;
	initSet(C);
	
	C = (SET*)malloc(sizeof(SET) *Max);
	if(C != NULL){
		for(x = 0; x < Max; x++){
			(*C)[x] = A[x] & ~B[x];
		}
	}
	return C;
}

void display(SET C){
	int x;
	printf("[ ");
	for(x = 0; x < Max; x++){
		printf("%d ", C[x]);
	}
	printf("]\n");
}
