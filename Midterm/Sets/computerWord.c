#include <stdio.h>
#include <stdlib.h>

#define Max 8

typedef char SET;

int numOfBits(SET C);
SET Union(SET A, SET B);
SET Intersection(SET A, SET B);
SET Difference(SET A, SET B);
void insertSet(SET *C, int data);
void deleteSet(SET *C, int data);
SET *setToBitVector(SET data);
SET bitVectorToSet(SET *C);
void displayPlaceValue(SET C);
void display(SET C);

int main(){
	SET A = 10;
	SET B = 7;
	SET C;
	SET *U;
	int x;
	
	puts("\nSET A: ");display(A);
	puts("\nSET B: ");display(B);
	
	printf("\nNumber of Bits: %d", numOfBits(B));
	
	C = Union(A, B);
	puts("\nUnion: ");display(C);
	
	C = Intersection(A, B);
	puts("\nIntersection: ");display(C);
	
	C = Difference(A, B);
	puts("\nDifference: ");display(C);
	
	insertSet(&A, 7);
	puts("\nInsert: ");display(A);
	
	deleteSet(&A, 7);
	puts("\nDelete: ");display(A);
	
	U = setToBitVector(78);
	puts("\nSet to BitVector: ");
	for(x = 0; x < Max; x++){
		printf("%d ", U[x]);
		if(x == 3){
			printf(" ");
		}
	}
	
	C = bitVectorToSet(U);
	puts("\nBitVector to Set: ");printf("%d\n", C);
	
	return 0;
}

int numOfBits(SET C){
	int sum = 0;
	int bits = (sizeof(C) * 8)-1;
	unsigned int mask;
	
	for(mask = 1 << bits; mask > 0; mask >>= 1){
		sum += (C & mask) ? 1 : 0;
	}
	return sum;
}

SET Union(SET A, SET B){
	return A | B;
}

SET Intersection(SET A, SET B){
	return A & B;
}

SET Difference(SET A, SET B){
	return A & ~B;
}

void insertSet(SET *S, int data){
	if(data <= (sizeof(*S) * 8)){
		*S = *S | (1 << data);
	}
}

void deleteSet(SET *S, int data){
	if(data <= (sizeof(*S) * 8)){
		*S = (*S) & ~(1 << data);
	}
}

SET *setToBitVector(SET data){
	SET *S;
	S = (SET*)malloc(sizeof(SET));
	int bits = (sizeof(data) * 8)-1;
	unsigned int mask;
	int x;
	x = 0;
	
	if(S != NULL){
		for(mask = 1 << bits; mask > 0; mask >>= 1){
			S[x] = (data & mask) ? 1 : 0;
			x++;
		}
	}
	return S;
}

SET bitVectorToSet(SET *C){
	SET x;
	int y, bits = (sizeof(*C) * 8)-1;
	y = 0;
	x = 0;
	unsigned int mask;
	
	for(mask = 1 << bits; mask > 0; mask >>= 1){
		if(C[y] == 1){
			x = x | mask;
		}
		y++;
	}
	return x;
}

void displayPlaceValue(SET C){
	int x, bits = (sizeof(C) * 8)-1;
	unsigned int mask;
	x = 0;
	printf("{ ");
	for(mask = 1; x != Max; mask <<= 1){
		if((C & mask) != 0){
			printf("%d, ", x);
		}
		x++;
	}
	printf("}\n");
}

void display(SET C){
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


