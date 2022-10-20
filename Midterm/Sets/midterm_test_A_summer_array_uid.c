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
setClass union_unsorted(setClass A, setClass B);
setClass union_sorted(setClass A, setClass B);
setClass getStudents(setClass A, setClass B);
setClass difference_unsorted(setClass A, setClass B);
setClass difference_sorted(setClass A, setClass B);
setClass getStudents_sorted(setClass A, setClass B);

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
	
//	C = union_sorted(A, B);
//	puts("\nUnion Sorted: ");display(C);
	
//	C = union_unsorted(A, B);
//	puts("\nUnion Unsorted: ");display(C);
	
//	C = getStudents(A, B);
//	puts("\nBoth enrolled: ");display(C);
	
//	C = getStudents_sorted(A, B);
//	puts("\nBoth enrolled in Sorted: ");display(C);
	
	C = difference_unsorted(A, B);
	puts("\nDifference Unsorted: ");display(C);

//	C = difference_sorted(A, B);
//	puts("\nDifference Sorted: ");display(C);
	
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

setClass union_unsorted(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	if(S.studs != NULL){
		for(x = 0; x < A.count; x++){
			S.studs[S.count++] = A.studs[x];
		}
		
		for(x = 0; x < B.count; x++){
			for(y = 0; y < S.count; y++){
				if((strcmp(B.studs[x].ID, S.studs[y].ID) == 0)){
					break;
				}	
			}
			if(y == S.count){
				S.studs[S.count++] = B.studs[x];
			}
		}
	}
	return S;
}

setClass union_sorted(setClass A, setClass B){
	setClass S;
	int x, y;
	x = 0; 
	y = 0;
	initSet(&S);
	
	if(S.studs != NULL){
		while(x < A.count && y < B.count){
			if(strcmp(A.studs[x].ID, B.studs[y].ID) < 0 ){
				S.studs[S.count] = A.studs[x];
				x++;
			}else{
				if(strcmp(A.studs[x].ID, B.studs[y].ID) == 0){
					x++;
				}
				S.studs[S.count] = B.studs[y];
				y++;
			}
			S.count++;
		}
		if(y < B.count){
			A = B;
			x = y;
		}
		while(x < A.count){
			S.studs[S.count] = A.studs[x];
			S.count++;
			x++;
		}
	}
	return S;
}

setClass getStudents(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	//if assumes acceding the ID 
	//Big O(n)
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

setClass getStudents_sorted(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	
	if(S.studs != NULL){
		for(x = 0; x < A.count; x++){
			for(y = 0; y < B.count && (strcmp(A.studs[x].ID, B.studs[y].ID) > 0); y++){}
				if(y < B.count && (strcmp(A.studs[x].ID, B.studs[y].ID) == 0)){
					S.studs[S.count] = A.studs[x];
					S.count++;
				}
		}
	}
	return S;
}

setClass difference_unsorted(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	
	if(S.studs != NULL){
		for(x = y = 0; x < A.count && y < B.count;){
			if(strcmp(A.studs[x].ID, B.studs[y].ID) > 0){
				y++;
				
			}else if(strcmp(A.studs[x].ID, B.studs[y].ID) == 0){
				x++;
				y++;
				
			}else{
				S.studs[S.count++] = A.studs[x];
				x++;
			}
		}
	}
	return S;
}

setClass difference_sorted(setClass A, setClass B){
	setClass S;
	int x, y;
	initSet(&S);
	
	if(S.studs != NULL){
		for(x = 0; x < A.count; x++){
			for(y = 0; y < B.count && (strcmp(A.studs[x].ID, B.studs[y].ID) > 0); y++){}
			if(y == B.count || (strcmp(A.studs[x].ID, B.studs[y].ID) != 0)){
				S.studs[S.count++] = A.studs[x];
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
