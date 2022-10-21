#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

typedef enum{
	TRUE, FALSE
}Boolean;

//Definition of the Boolean array set
typedef Boolean bArray[SIZE];

//Definition of the computer word set
typedef char compWSet;

compWSet *setToBitVector(compWSet C);
compWSet bitVectorToSet(compWSet *C);
compWSet getDifference(bArray A, bArray B);
void displayPlaceValue(compWSet C);
void display(compWSet C);

int main(){
	compWSet C;
	compWSet *U;
	int x;
	bArray A = {0, 1, 0, 1, 1, 1, 0, 0};
	bArray B = {1, 0, 0, 1, 0, 1, 1, 1};
	
	/*U = setToBitVector(78);
	puts("\nSet to BitVector: ");
	for(x = 0; x < SIZE; x++){
		printf("%d ", U[x]);
		if(x == 3){
			printf(" ");
		}
	}
	
	C = bitVectorToSet(U);
	puts("\nBitVector to Set: ");printf("%d\n", C);*/
	C = getDifference(A, B);
	puts("\nDifference: ");printf("%d ", C);
	
	return 0;
	
}
void initSet(bArray *C){
	C = NULL;
}
compWSet *setToBitVector(compWSet C){
	compWSet *S;
	S = (compWSet*)malloc(sizeof(compWSet));
	int bits = (sizeof(C) * 8)-1;
	unsigned int mask;
	int x;
	x = 0;
	
	if(S != NULL){
		for(mask = 1 << bits; mask > 0; mask >>= 1){
			S[x] = (C & mask) ? 1 : 0;
			x++;
		}
	}
	return S;
}
compWSet bitVectorToSet(compWSet *C){
	compWSet x;
	int y, bits = (sizeof(*C) * 8)-1;
	x = 0;
	y = 0;
	unsigned int mask;
	for(mask = 1 << bits; mask > 0; mask >>= 1){
		if(C[y] == 1){
			x = x | mask;
		}
		y++;
	}
	
	return x;
}

compWSet getDifference(bArray A, bArray B){
	compWSet C;
	int x;
	unsigned int mask;
	int bits = (sizeof(C)*8)-1;
	
	for(x = 0; x < SIZE; x++){
		for(mask = 1 << bits; mask > 0; mask >>= 1){
			if(A[x] == 1 & ~B[x] == 0){
				C = C | mask;;
			}
		}
	}
	return C;
}


void displayPlaceValue(compWSet C){
	int x, bits = (sizeof(C) * 8)-1;
	unsigned int mask;
	x = 0;
	printf("{ ");
	for(mask = 1; x != SIZE; mask <<= 1){
		if((C & mask) != 0){
			printf("%d, ", x);
		}
		x++;
	}
	printf("}\n");
}

void display(compWSet C){
	int gap, x, bits = (sizeof(C) * 8)-1;
	unsigned int mask;
	x = 0;
	gap = 0;
	
	for(gap = 1, mask = 1 << bits; mask > 0; mask >>= 1, gap++){
		printf("%d ",(C & mask) ? 1: 0);
		if(gap % 4 == 0){
			printf(" ");
		}
	}
	displayPlaceValue(C);
	printf("\n");
}
