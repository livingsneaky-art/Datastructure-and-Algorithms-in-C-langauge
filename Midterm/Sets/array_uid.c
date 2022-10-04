#include <stdio.h>

#define Max 5

typedef struct{
	char data[Max];
	int count;
}SET;

void initSet(SET *C);
SET populateSet(char C[]);
SET union_unsorted(SET A, SET B);
SET union_sorted(SET A, SET B);
SET intersection_sorted(SET A, SET B);
SET difference_sorted(SET A, SET B);
SET merge(SET A, SET B);
int isMember(SET C, char data);
SET insert(SET C, int position, char data);
int MIN(SET C);
int MAX(SET C);
void display(SET C);

int main(){
	
	SET A, B, C;
	char X[] = {1, 2, 3, 5, 6};
	char Y[] = {2, 3, 4, 5, 8};
	
	initSet(&A);
	initSet(&B);
	initSet(&C);
	
	A = populateSet(X);
	B = populateSet(Y);
	display(A);
	display(B);
	
	C = union_unsorted(A, B);
	puts("\nUnion Unsorted: ");display(C);
	
	C = union_sorted(A, B);
	puts("\nUnion Sorted: ");display(C);
	
	C = intersection_sorted(A, B);
	puts("\nIntersection Sorted: ");display(C);
	
	C = difference_sorted(A, B);
	puts("\nDifference Sorted: ");display(C);
	
	C = merge(A, B);
	puts("\nMerge: ");display(C);
	
	int retVal = isMember(A, 3);
	printf("%d", retVal);
	
	C = insert(A, 0, 7);
	puts("\nInserted Data:  ");display(C);
	
	int retVal1 = MIN(A);
	printf("%d\n", retVal1);
	
	int retVal2 = MAX(B);
	printf("%d\n", retVal2);
	
	
	return 0;
}

void initSet(SET *C){
	C->count = 0;
}

SET populateSet(char C[]){
	SET S;
	initSet(&S);
	int x;
	
	for(x = 0; x < Max; x++){
		S.data[S.count] = C[x];
		S.count++;
	}
	return S;
}

SET union_unsorted(SET A, SET B){
	SET S;
	initSet(&S);
	int x, y;
	
	for(x = 0; x < A.count; x++){
		S.data[S.count++] = A.data[x];
	}
	
	for(x = 0; x < B.count; x++){
		for(y = 0; y < S.count; y++){
			if(B.data[x] == S.data[y])
				break;
		}
		if(y == S.count)
			S.data[S.count++] = B.data[x];
	}
	return S;
}

SET union_sorted(SET A, SET B){
	SET S;
	initSet(&S);
	int x, y;
	
	for(x = 0, y = 0; x < A.count && y < B.count;){
		if(A.data[x] < B.data[y]){
			S.data[S.count] = A.data[x];
			x++;
		}else{
			if(A.data[x] == B.data[y]){
				x++;
			}
			S.data[S.count] = B.data[y];
			y++;
		}
		S.count++;
	}
	if(y < B.count){
		A = B;
		x = y;
	}
	while(x < A.count){
		S.data[S.count] = A.data[x];
		x++;
		S.count++;
	}
	return S;
}

SET intersection_sorted(SET A, SET B){
	SET S;
	initSet(&S);
	int x, y;
	
	for(x = 0; x < A.count; x++){
		for(y = 0; y < B.count && A.data[x] > B.data[y]; y++){}
			if(y < B.count && A.data[x] == B.data[y]){
				S.data[S.count] = A.data[x];
				S.count++;
			}
	}
	return S;
}

SET difference_sorted(SET A, SET B){
	SET S;
	initSet(&S);
	int x, y;
	
	for(x = 0; x < A.count; x++){
		for(y = 0; y < B.count && A.data[x] > B.data[y]; y++){}
		if(y == B.count || A.data[x] != B.data[y]){
			S.data[S.count] = A.data[x];
			S.count++;
		}
	}
	return S;
}

SET merge(SET A, SET B){
	SET S;
	initSet(&S);
	S = intersection_sorted(A, B);
	
	if(S.count == 0){
		S = union_sorted(A, B);
	}else{
		puts("Sets aren't disjoint\n");
		S.count;
	}
	return S;
}

int isMember(SET C, char data){
	int x, result = 0;
	for(x = 0; x < C.count; x++){
		if(C.data[x] == data){
			result = data;
		}
	}
	return result;
}

SET insert(SET C, int position, char data){
	int x;
	if(C.count != 0){
		for(x = C.count-1; x >= position; --x){
			C.data[x+1] = C.data[x];
		}
		C.data[x+1] =data;
		C.count++;
	}
	return C;
}

int MIN(SET C){
	int x, MIN = 1000;
	for(x = 0; x < C.count; x++){
		if(C.data[x] < MIN){
			MIN = C.data[x];
		}
	}
	return MIN;
}

int MAX(SET C){
	int x, MAX = 0;
	for(x = 0; x < C.count; x++){
		if(C.data[x] > MAX){
			MAX = C.data[x];
		}
	}
	return MAX;
}

void display(SET C){
	int x;
	for(x = 0; x < C.count; x++){
		printf("%d ", C.data[x]);
	}
	printf("\n");
}


