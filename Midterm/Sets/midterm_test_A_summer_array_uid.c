#include <stdio.h>
#include <stdlib.h>

#define CLASS_SIZE 4

typedef struct{
	char FN[24], MI, LN[16];
}Nametype;

typedef struct{
	char ID[10];
	//Nametype name;
	char course[8];
	int yrLevel;
}Studtype;

//Definition of the class List
typedef struct{
	Studtype *studs;
	int count;
}setClass;

void initSet(setClass *C);
setClass getStudents(setClass A, setClass B);
setClass populateSet(char C[]);
//void display(setClass C);


int main(){
	
	setClass A, B, C;
	//Studtype a = {1, "bsit", 3};
		//Nametype a = {"Ching", 'Q', "Mendoza"};
		Studtype a = {'1', "bsit", '3'};		
	initSet(&A);
	initSet(&B);
	initSet(&C);
	
//	A = populateSet(X);
	puts("\nSET A: ");display(A);
	
	
	return 0;
}

void initSet(setClass *C){
	C->count = 0;
	C->studs = (Studtype*)malloc(sizeof(Studtype)*CLASS_SIZE);
}

setClass populateSet(char C[]){
	setClass S;
	int x;
	initSet(&S);
	
	for(x = 0; x < CLASS_SIZE; x++){
	//	S.studs[S.count++] = C[x]; 
	}
	return S;
}
