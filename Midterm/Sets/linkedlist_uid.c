#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *next;
}*SET;

void initSet(SET *C);
SET populateSet(char C[], int count);
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
	int count = 5;
	initSet(&A);
	initSet(&B);
	initSet(&C);
	
	A = populateSet(X, count);
	B = populateSet(Y, count);
	puts("\nSet A: ");display(A);
	puts("\nSet A: ");display(B);
	
	C = union_unsorted(A, B);
	puts("\nUnion Unsorted: ");display(C);
	
	C = union_sorted(A, B);
	puts("\nUnion Sorted: ");display(C);
	
	C = intersection_sorted(A, B);
	puts("\nIntersection Sorted: ");display(C);
	
	C = difference_sorted(A, B);
	puts("\nDiffrence Sorted: ");display(C);
	
	C = merge(A, B);
	puts("\nMerge: ");display(C);
	
	C = insert(A, 3, 7);
	puts("\nInsert New Data: ");display(C);
	
	int retVal = isMember(A, 6);
	printf("%d\n", retVal);
	
	int retVal1 = MIN(A);
	printf("%d\n", retVal1);
	
	int retVal2 = MAX(B);
	printf("%d\n", retVal2);
	
	return 0;
}

void initSet(SET *C){
	*C = NULL;
}

SET populateSet(char C[], int count){
	SET S, temp;
	initSet(&S);
	int x;
	
	for(x = 0; x < count; x++){
		temp = (SET)calloc(1, sizeof(struct node));
		if(temp != NULL){
			temp->data = C[x];
			temp->next = S;
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
	
	for(; travA != NULL; travA = travA->next){
		temp = (SET)calloc(1, sizeof(struct node));
		if(temp != NULL){
			temp->data = travA->data;
			temp->next = S;
			S = temp;
		}	
	}
	
	for(; travB != NULL; travB = travB->next){
		for(trav = S; trav != NULL && travB->data != trav->data; trav = trav->next){}
		if(trav == NULL){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travB->data;
				temp->next = S;
				S = temp;
			}
		}
	}
	return S;
}

SET union_sorted(SET A, SET B){
	SET S, temp;
	SET travA, travB, *trav;
	travA = A;
	travB = B;
	initSet(&S);
	
	while (travA != NULL && travB != NULL) {
        if (travA->data > travB->data) {
            temp = (SET)malloc(sizeof(struct node));
            if (temp != NULL) {
                temp->data = travA->data;
                temp->next = S;
                S = temp;
            }
            travA = travA->next;
        } else {
            if (travA->data == travB->data) {
                travA = travA->next;
            } 
            temp = (SET)malloc(sizeof(struct node));
            if (temp != NULL) {
                temp->data = travB->data;
                temp->next = S;
                S = temp;
            }
            travB = travB->next;
        }
    }

    if (travB != NULL) {
        travA = travB;
    }

    while (travA != NULL) {
        temp = (SET)malloc(sizeof(struct node));
        if (temp != NULL) {
            temp->data = travA->data;
            temp->next = S;
            S = temp;
        }
        travA = travA->next;
    }

    return S;
}

SET intersection_sorted(SET A, SET B){
	SET S, temp;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != NULL; travA = travA->next){
		for(; travB != NULL && travA->data < travB->data; travB = travB->next){}
		if(travB != NULL && travA->data == travB->data){
			temp =  (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travA->data;
				temp->next = S;
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
	
	for(; travA != NULL; travA = travA->next){
		for(; travB != NULL && travA->data < travB->data; travB = travB->next){}
		if(travB == NULL || travA->data != travB->data){
			temp = (SET)calloc(1, sizeof(struct node));
			if(temp != NULL){
				temp->data = travA->data;
				temp->next = S;
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

int isMember(SET C, char data){
	SET trav;
	int result = 0;
	for(trav = C; trav != NULL; trav = trav->next){
		if(trav->data == data){
			result = data;
		}
	}
	return result;
}

SET insert(SET C, int position, char data){
	SET temp;
	SET *trav;
	
	int x;
	trav = &C;
	for(x = 0; x < position; x++){
		trav = &(*trav)->next;
	}
	temp = (SET)calloc(1, sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->next = C;
		C = temp;
	}
	return C;
}

int MIN(SET C){
	SET trav;
	int MIN = 1000;
	
	for(trav = C; trav != NULL; trav = trav->next){
		if(trav->data < MIN){
			MIN = trav->data;
		}
	}
	return MIN;
}

int MAX(SET C){
	SET trav;
	int MAX = 0;
	
	for(trav = C; trav != NULL; trav = trav->next){
		if(trav->data > MAX){
			MAX = trav->data;
		}
	}
	return MAX;
}

void display(SET C){
	SET trav;
	trav = C;
	while(trav != NULL){
		printf("%d ", trav->data);
		trav = trav->next;
	}
	printf("\n");
}

