#include <stdio.h>
#include <stdlib.h>

#define CLASS_SIZE 5

typedef struct{
	char FN[24], MI, LN[16];
}Nametype;

typedef struct{
	char ID[10];
	Nametype name;
	char course[8];
	int yrLevel;
}Studtype;

//Definition of the class List
typedef struct{
	Studtype *studs;
	int count;
}setClass;

void initSet(setClass *C);
setClass populateSet(Studtype C[]);
setClass getStudents(setClass A, setClass B);
void display(setClass C);


int main(){
	
	setClass A, B, C;
	Studtype X[] = {
					{"1",{"ryan", 'b', "llamido"}, "bsit", 3},
					{"2",{"crisha", 'd', "macasero"}, "nursing", 4},
					{"3",{"kryshna", 'c', "jaye"}, "nursing", 4},
					{"5",{"christine", 'b', "bucag"}, "engineer", 3},
					{"6",{"Yu", 'e', "Na"}, "cusiness", 3}
					};	
					
	Studtype Y[] = {
					{"2",{"ryan", 'b', "llamido"}, "bsit", 3},
					{"3",{"crisha", 'd', "macasero"}, "nursing", 4},
					{"4",{"kryshna", 'c', "jaye"}, "nursing", 4},
					{"5",{"christine", 'b', "bucag"}, "engineer", 3},
					{"8",{"Yu", 'e', "Na"}, "cusiness", 3}
					};	
	initSet(&A);
	initSet(&B);
	initSet(&C);
	
	A = populateSet(X);
	B = populateSet(Y);
	puts("\nSET A: ");display(A);
	puts("\nSET B: ");display(B);
	
	C = getStudents(A, B);
	puts("\nBoth enrolled: ");display(C);
	
	return 0;
}

void initSet(setClass *C){
	C->count = 0;
	C->studs = (Studtype*)malloc(sizeof(Studtype)*CLASS_SIZE);
}

setClass populateSet(Studtype C[]){
	setClass S;
	int x;
	initSet(&S);
	
	for(x = 0; x < CLASS_SIZE; x++){
		S.studs[S.count++] = C[x]; 
	}
	return S;
}

setClass getStudents(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	
	if(S.studs != NULL){
		for(x = y = 0; x < A.count && y < B.count;){
			if(strcmp(A.studs[x].ID, B.studs[y].ID) < 0){
				x++;
			}else if(strcmp(A.studs[x].ID, B.studs[y].ID) > 0){
				y++;
			}else{
				S.studs[S.count++] = A.studs[x];
				x++;
				y++;
			}
		}
	}
	return S;
}

void display(setClass C){
	int x;
	printf("[ ");
	for(x = 0; x < C.count; x++){
		printf("%s ", C.studs[x].ID);
	}
	printf("]\n");
}
