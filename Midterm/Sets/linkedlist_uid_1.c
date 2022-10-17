#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *link;
}*SET;

void initSet(SET *C);
SET populateSet(char C[], int count);
SET union_unsorted(SET A, SET B);
SET union_sorted(SET A, SET B);
SET intersection_sorted(SET A, SET B);
SET difference_sorted(SET A, SET B);
SET merge(SET A, SET B);
SET insert(SET C, int position, char data);
int isMember(SET C, char data);
int MIN(SET C);
int MAX(SET C);
void display(SET C);

int main(){
	SET A, B, C;
	char X[] = {1, 2, 3, 5, 6};
	char Y[] = {2, 3, 4, 5, 8};
	int count = 5;
	initSet(&A);
	initSet(&B);
	initSet(&C);
	
	A = populateSet(X, count);
	B = populateSet(Y, count);
	puts("\nSET A: ");display(A);
	puts("\nSET B: ");display(B);
	
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
	
	C = insert(A, 0, 7);
	puts("\nInsert: ");display(C);
	
	int retVal = isMember(A, 6);
	puts("\nIsMember: ");printf("%d\n", retVal);
	
	int retVal1 = MIN(A);
	puts("\nMIN: ");printf("%d\n", retVal1);
	
	int retVal2 = MAX(B);
	puts("\nMAX: ");printf("%d\n", retVal2);
	
	
	return 0;
}

void initSet(SET *C){
	*C = NULL;
}

SET populateSet(char C[], int count){
	SET S, temp;
	int x;
	initSet(&S);
	
	for(x = 0; x < count; x++){
		temp = (SET)calloc(1, sizeof(struct node));;
		if(temp != NULL){
			temp->data = C[x];
			temp->link = S;
			S = temp;
		}
	}
	return S;
}

SET union_unsorted(SET A, SET B){
	SET S, temp;
	SET travA, travB, trav;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != NULL; travA = travA->link){
		temp = (SET)calloc(1, sizeof(struct node));
		if(temp != NULL){
			temp->data = travA->data;
			temp->link = S;
			S = temp;
		}
	}
	
	for(; travB != NULL; travB = travB->link){
		for(trav = S; trav != NULL && travB->data != trav->data; trav = trav->link){}
		if(trav == NULL){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travB->data;
				temp->link = S;
				S = temp;
			}
		}
	}
	return S;
}

SET union_sorted(SET A, SET B){
	SET S, temp;
	SET travA, travB, trav;
	travA = A;
	travB = B;
	initSet(&S);
	
	while(travA != NULL && travB != NULL){
		if(travA->data > travB->data){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travA->data;
				temp->link = S;
				S = temp;
			}
			travA = travA->link;
		}else{
			if(travA->data == travB->data){
				travA = travA->link;
			}
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travB->data;
				temp->link = S;
				S = temp;
			}
			travB = travB->link;
		}
	}
	
	if(travB != NULL){
		travA = travB;
	}
	
	while(travA != NULL){
		temp = (SET)calloc(1, sizeof(struct node));
		if(temp != NULL){
			temp->data = travA->data;
			temp->link = S;
			S = temp;
		}
		travA = travA->link;
	}
	return S;
}

SET intersection_sorted(SET A, SET B){
	SET S, temp;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != NULL; travA = travA->link){
		for(; travB != NULL && travA->data < travB->data;  travB = travB->link){}
		if(travB != NULL && travA->data == travB->data){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travA->data;
				temp->link = S;
				S = temp;
			}
		}
	}
	return S;
}

SET difference_sorted(SET A, SET B){
	SET S, temp;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != NULL; travA = travA->link){
		for(; travB != NULL && travA->data < travB->data; travB = travB->link){}
		if(travB == NULL || travA->data != travB->data){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travA->data;
				temp->link = S;
				S = temp;
			}
		}
	}
	return S;
}

SET merge(SET A, SET B){
	SET S;
	initSet(&S);
	S = intersection_sorted(A, B);
	
	if(S == NULL){
		S = union_sorted(A, B);
	}else{
		puts("Sets aren't disjoint\n");
		S = NULL;
	}
	return S;
}

SET insert(SET C, int position, char data){
	SET temp;
	SET *trav;
	int x;
	trav = &C;
	
	for(x = 0; x < position; x++){
		trav = &(*trav)->link;
	}
	temp = (SET)calloc(1, sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = C;
		C = temp;
	}
	return C;
}

int isMember(SET C, char data){
	SET trav;
	int result = 0;
	
	for(trav = C; trav != NULL; trav = trav->link){
		if(trav->data == data){
			result = data;
		}
	}
	return result;
}

int MIN(SET C){
	SET trav;
	int MIN = 1000;
	
	for(trav = C; trav != NULL; trav = trav->link){
		if(trav->data < MIN){
			MIN = trav->data;
		}
	}
	return MIN;
}

int MAX(SET C){
	SET trav;
	int MAX = 0;
	
	for(trav = C; trav != NULL; trav = trav->link){
		if(trav->data > MAX){
			MAX = trav->data;
		}
	}
	return MAX;
}

void display(SET C){
	SET trav;
	printf("[ ");
	trav = C;
	while(trav != NULL){
		printf("%d ", trav->data);
		trav = trav->link;
	}
	printf("]\n");
}
