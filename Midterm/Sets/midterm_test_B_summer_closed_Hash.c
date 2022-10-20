#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CLASS_SIZE 5
#define EMPTY -1
#define DELETED 0

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
	Studtype studs[CLASS_SIZE];
	int count;
}*classList;

typedef enum{
	TRUE = 1,
	FALSE = 0
}Boolean;

//Definition of the Boolean array
typedef Boolean bArray[CLASS_SIZE];

void initDictionary(classList *C);
classList populateSet(Studtype C[]);
//int map(Boolean data);
//void insertDictionary(classList A, Boolean C);
void display(classList C);

int main(){
	classList A, B, C;
	//bArray data = {31, 32, 33, 43, 39, 99};
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
	initDictionary(&A);
	initDictionary(&B);
	initDictionary(&C);
	char x;
	
	A = populateSet(X);
	puts("\nSET A: ");display(A);
	
	//for(x = 0; x < 5; x++) insertDictionary(A, data[x]);
	//display(D);
	
	return 0;
}

void initDictionary(classList *C){
	*C = (classList)calloc(1, sizeof(classList));
	//int x;
	//for(x = 0; x < CLASS_SIZE; x++){
	//	(*C)->studs[x].yrLevel = EMPTY;
//	}
}

classList populateSet(Studtype C[]){
	classList S;
	int x;
	initDictionary(&S);
	
	for(x = 0; x < CLASS_SIZE; x++){
		S->studs[S->count++] = C[x]; 
	}
	return S;
}

void display(classList C){
	int x;
	printf("[ ");
	for(x = 0; x < C->count; x++){
		printf("%s ", C->studs[x].yrLevel);
	}
	printf("]\n");
}
/*
int map(Boolean data){
	//return toupper(data.name.FN[0])-65;
	return data%10;
}

void insertDictionary(classList A, Boolean C){
	int hash, location;
		hash = map(C);
		if(A->studs[hash].yrLevel == EMPTY){
			A->studs[hash] = C;
		}else{
			for(location = (hash+1)%CLASS_SIZE; A->studs[location].yrLevel != EMPTY && A->studs[location].yrLevel != DELETED; location = (location+1)%CLASS_SIZE){}
			A->studs[location] = C;
		}
		A->count++;
	}
}

void display(classList A){
	int hash, x, sl = 0;
	float asl = 0;
	
	printf("DATA:\t");
	for(x = 0; x < CLASS_SIZE; x++){
		printf("%s\t", A->studs[x].course);
	}
	
	printf("\nINDEX:\t");
	for(x = 0; x < CLASS_SIZE; x++){
		printf("[%A]\t", x);
	}
	
	printf("\nSL:\t");
	for(x = 0; x < CLASS_SIZE; x++){
		if(A->studs[x].yrLevel != EMPTY){
			hash = map(A->studs[x]);
			sl = ((x+CLASS_SIZE)-hash+1)%CLASS_SIZE;
			asl += sl;
			printf("%A\t", sl);
		}else{
			printf("--\t");
		}
	}
	printf("\nAverage SL: %.2f\n\n", asl/A->count);
}*/

