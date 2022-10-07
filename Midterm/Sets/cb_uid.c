#include <stdio.h>

#define Max 50

typedef struct{
	char data;
	int next;
}HeapSpace[Max];

typedef struct{
	HeapSpace HS;
	int Avail;
}VirtualHeap;

typedef int SET;

void initHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void initSet(SET *C);
SET populateSet(VirtualHeap *VH, char C[], int count);
SET union_unsorted(VirtualHeap *VH, SET A, SET B);
SET union_sorted(VirtualHeap *VH, SET A, SET B);
SET intersection_sorted(VirtualHeap *VH, SET A, SET B);
SET difference_sorted(VirtualHeap *VH, SET A, SET B);
SET merge(VirtualHeap *VH, SET A, SET B);
int isMember(VirtualHeap VH, SET C, char data);
SET insert(VirtualHeap *VH, SET C, int position, char data);
int MIN(VirtualHeap VH, SET C);
int MAX(VirtualHeap VH, SET C);
void visualizeHeap(VirtualHeap VH);
void display(VirtualHeap VH, SET C);

int main(){
	VirtualHeap VH;
	SET A, B, C;
	char X[] = {1, 2, 3, 5, 6};
	char Y[] = {2, 3, 4, 5, 8};
	int count = 5;
	
	initHeap(&VH);
	initSet(&A);
	initSet(&B);
	initSet(&C);
	//visualizeHeap(VH);
	A = populateSet(&VH, X, count);
	B = populateSet(&VH, Y, count);
	
	puts("\nSET A: ");display(VH, A);
	puts("\nSET B: ");display(VH, B);
	
	C = union_unsorted(&VH, A, B);
	puts("\nUnion Unsorted: ");display(VH, C);
	
	C = union_sorted(&VH, A, B);
	puts("\nUnion Sorted: ");display(VH, C);
	
	C = intersection_sorted(&VH, A, B);
	puts("\nIntersection Sorted: ");display(VH, C);
	
	C = difference_sorted(&VH, A, B);
	puts("\nDifference Sorted: ");display(VH, C);
	
	C = merge(&VH, A, B);
	puts("\nMerge: ");display(VH, C);
	
	C = insert(&VH, A, 0, 7);
	puts("\nNew Data Insert: ");display(VH, C);
	
	int retVal = isMember(VH, A, 6);
	printf("%d\n", retVal);
	
	int retVal1 = MIN(VH, A);
	printf("%d\n", retVal1);
	
	int retVal2 = MAX(VH, B);
	printf("%d\n", retVal2);
	return 0;
}

void initHeap(VirtualHeap *VH){
	int x, LIM = Max-1;
	
	for(x = 0; x < LIM; x++){
		VH->HS[x].data = 0;
		VH->HS[x].next = x+1;
	}
	VH->HS[Max-1].data = 0;
	VH->HS[Max-1].next = -1;
	VH->Avail = 0; 
}

int allocSpace(VirtualHeap *VH){
	int retVal = VH->Avail;
	if(retVal != -1){
		VH->Avail = VH->HS[VH->Avail].next;
	}
	return retVal;
}

void initSet(SET *C){
	*C = -1;
}

SET populateSet(VirtualHeap *VH, char C[], int count){
	SET temp, x, S;
	initSet(&S);
	
	for(x = 0; x < count; x++){
		temp = allocSpace(VH);
		if(temp != -1){
			VH->HS[temp].data = C[x];
			VH->HS[temp].next = S;
			S = temp;
		}
	}
	return S;
}

SET union_unsorted(VirtualHeap *VH, SET A, SET B){
	SET temp, S;
	SET trav, travA, travB;
	initSet(&S);
	
	for(travA = A; travA != -1; travA = travA = VH->HS[travA].next){
		temp = allocSpace(VH);
		if(temp != -1){
			VH->HS[temp].data = VH->HS[travA].data;
			VH->HS[temp].next = S;
			S = temp;
		}
	}
	for(travB = B; travB != -1; travB = VH->HS[travB].next){
		for(trav = S; trav != -1 && VH->HS[travB].data !=  VH->HS[trav].data; trav = VH->HS[trav].next){}
		if(trav == -1){
			temp = allocSpace(VH);
			if(temp != -1){
				VH->HS[temp].data = VH->HS[travB].data;
				VH->HS[temp].next = S;
				S = temp;
			}
		}
	}
	return S;
}

SET union_sorted(VirtualHeap *VH, SET A, SET B){
	SET temp, S;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S); 
	
	
	while(travA != -1 && travB != -1){
		if(VH->HS[travA].data > VH->HS[travB].data){
			temp = allocSpace(VH);
			if(temp != -1){
				VH->HS[temp].data = VH->HS[travA].data;
				VH->HS[temp].next = S;
				S = temp;
			}
			travA = VH->HS[travA].next;
		}else{
			if(VH->HS[travA].data == VH->HS[travB].data){
				travA = VH->HS[travA].next;
			}
			temp = allocSpace(VH);
			if(temp != -1){
				VH->HS[temp].data = VH->HS[travB].data;
				VH->HS[temp].next = S;
				S = temp;
			}
			travB = VH->HS[travB].next;
		}
	}
	if(travB != -1){
		travA = travB;
	}
	while(travA != -1){
		temp = allocSpace(VH);
		if(temp != -1){
			VH->HS[temp].data = VH->HS[travA].data;
			VH->HS[temp].next = S;
			S = temp;
		}
		travA = VH->HS[travA].next;
	}
	return S;
}

SET intersection_sorted(VirtualHeap *VH, SET A, SET B){
	SET S, temp;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != -1; travA = VH->HS[travA].next){
		for(; travB != -1 && VH->HS[travA].data < VH->HS[travB].data; travB = VH->HS[travB].next){}
		if(travB != -1 && VH->HS[travA].data == VH->HS[travB].data){
			temp = allocSpace(VH);
			if(temp != -1){
				VH->HS[temp].data = VH->HS[travA].data;
				VH->HS[temp].next = S;
				S = temp;
			}
		}
	}
	return S;
}

SET difference_sorted(VirtualHeap *VH, SET A, SET B){
	SET S, temp;
	SET travA, travB;
	travA = A;
	travB = B;
	initSet(&S);
	
	for(; travA != -1; travA = VH->HS[travA].next){
		for(; travB != -1 && VH->HS[travA].data < VH->HS[travB].data; travB = VH->HS[travB].next){}
		if(travB == -1 || VH->HS[travA].data != VH->HS[travB].data){
			temp = allocSpace(VH);
			if(temp != -1){
				VH->HS[temp].data = VH->HS[travA].data;
				VH->HS[temp].next = S;
				S = temp;
			}
		}
	}
	return S;
}

SET merge(VirtualHeap *VH, SET A, SET B){
	SET S;
	initSet(&S);
	S = intersection_sorted(VH, A, B);
	
	if(S == -1){
		S = union_sorted(VH, A, B);
	}else{
		puts("Sets aren't disjoint\n");
		S = -1;
	}
	return S;
}

int isMember(VirtualHeap VH, SET C, char data){
	SET trav, result = 0;
	for(trav = C; trav != -1; trav = VH.HS[trav].next){
		if(VH.HS[trav].data == data){
			result = data;
		}
	}
	return result;
}

SET insert(VirtualHeap *VH, SET C, int position, char data){
	SET x, temp;
	SET *trav;
	
	if(C != -1 && position < Max){
		trav = &C;
		for(x = 0; x < position; x++){
			trav = &VH->HS[*trav].next;
		}
		temp = allocSpace(VH);
		if(temp != -1){
			VH->HS[temp].data = data;
			VH->HS[temp].next = *trav;
			*trav = temp;
		}
	}
	return C;
}

int MIN(VirtualHeap VH, SET C){
	SET trav, MIN = 1000;
	for(trav = C; trav != -1; trav = VH.HS[trav].next){
		if(VH.HS[trav].data < MIN){
			MIN = VH.HS[trav].data;
		}
	}
	return MIN;
}

int MAX(VirtualHeap VH, SET C){
	SET trav, MAX = 0;
	for(trav = C;  trav != -1; trav = VH.HS[trav].next){
		if(VH.HS[trav].data > MAX){
			MAX = VH.HS[trav].data;
		}
	}
	return MAX;
}

void visualizeHeap(VirtualHeap VH){
	int x;
	printf("%15s | %15s | %15s\n", "INDEX", "ELEM", "NEXT");
	for(x = 0; x < Max; x++){
		printf("%15d | %15d | %15d\n", x, VH.HS[x].data, VH.HS[x].next);
	}
	printf("Avail: %d\n", VH.Avail);
}

void display(VirtualHeap VH, SET C){
	SET trav;
	printf("[ ");
	trav = C;
	while(trav != -1){
		printf("%d ", VH.HS[trav].data);
		trav = VH.HS[trav].next;
	}
	printf("]\n");
}



