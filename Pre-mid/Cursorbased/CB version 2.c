#include <stdio.h>

#define MAX 10

typedef struct{
	char elem;
	int next;
}HeapSpace[MAX];

typedef struct{
	HeapSpace HS;
	int Avail;
	int count;
}VirtualHeap;

typedef int List;

void initHeap(VirtualHeap *VH);
int allocSpace(VirtualHeap *VH);
void deallocSpace(VirtualHeap *VH, int index);
void insertFront(VirtualHeap  *VH, List *L, char elem);
void insertRear(VirtualHeap *VH, List *L, char elem);
void insertPosition(VirtualHeap *VH, List *L, char elem, int position);
void insertSorted(VirtualHeap *VH, List *L, char elem);
void deleteFront(VirtualHeap *VH, List *L);
void deleteRear(VirtualHeap *VH, List *L);
void deletePosition(VirtualHeap *VH, List *L, int position);
void visualizeHeap(VirtualHeap VH);
void display(VirtualHeap VH, List L);

int main(){
	
	VirtualHeap VH;
	List L = -1;
	initHeap(&VH);
	visualizeHeap(VH);
	display(VH, L);
	insertFront(&VH, &L, 1);
	insertFront(&VH, &L, 2);
	insertFront(&VH, &L, 3);
	insertFront(&VH, &L, 4);
	visualizeHeap(VH);
	display(VH, L);
	insertRear(&VH, &L, 5);
	visualizeHeap(VH);
	display(VH, L);
	deleteFront(&VH, &L);
	visualizeHeap(VH);
	display(VH, L);
	deleteRear(&VH, &L);
	visualizeHeap(VH);
	display(VH, L);
	insertPosition(&VH, &L, 6, 0);
	visualizeHeap(VH);
	display(VH, L);
	insertSorted(&VH, &L, 7);
	visualizeHeap(VH);
	display(VH, L);
	deletePosition(&VH, &L, 0);
	visualizeHeap(VH);
	display(VH, L);
	
	return 0;
}
//version 2
void initHeap(VirtualHeap *VH){
	int i;
	
	for(i = MAX-1; i >= 0; --i){
		VH->HS[i].elem = 0;
		VH->HS[i].next = i-1;
	}
	VH->count = 0;
	VH->HS[0].elem = 0;
	VH->Avail = MAX-1;
}

int allocSpace(VirtualHeap *VH){
	int retAvail = VH->Avail;
	if(retAvail != -1){
		VH->Avail = VH->HS[VH->Avail].next;
	}
	return retAvail;
}

void deallocSpace(VirtualHeap *VH, int index){
	if(index < MAX && VH->Avail != -1){
		VH->HS[index].elem = 0;
		VH->HS[index].next = VH->Avail;
		VH->Avail = index;
	}
}

void insertFront(VirtualHeap *VH, List *L, char elem){
	List temp;
	temp = allocSpace(VH);
	if(temp != -1){
		VH->HS[temp].elem = elem;
		VH->HS[temp].next = *L;
		*L = temp;
		VH->count++;
	}
}

void insertRear(VirtualHeap *VH, List *L, char elem){
	List temp, *trav;
	for(trav = L; *trav != -1; trav = &VH->HS[*trav].next){}
	temp = allocSpace(VH);
	if(temp != -1){
		VH->HS[temp].elem = elem;
		VH->HS[temp].next = *trav;
		*trav = temp;
		VH->count++;
	}
}

void insertPosition(VirtualHeap *VH, List *L, char elem, int position){
	List temp, *trav;
	int i;
	trav = L;
	for(i = 0; i < position; i++){
		trav = &VH->HS[*trav].next;
	}
	temp = allocSpace(VH);
	if(temp != -1){
		VH->HS[temp].elem = elem;
		VH->HS[temp].next = *trav;
		*trav = temp;
		VH->count++;
	}
}

void insertSorted(VirtualHeap *VH, List *L, char elem){
	List temp, *trav;
	for(trav = L; *trav != -1 && elem < VH->HS[*trav].elem; trav = &VH->HS[*trav].next){}
	temp = allocSpace(VH);
	if(temp != -1){
		VH->HS[temp].elem = elem;
		VH->HS[temp].next = *trav;
		*trav = temp;
		VH->count++;
	}
}

void deleteFront(VirtualHeap *VH, List *L){
	List temp;
	if(*L != -1){
		temp = *L;
		*L = VH->HS[temp].next;
		deallocSpace(VH, temp);
		VH->count--;
	}
}

void deleteRear(VirtualHeap *VH, List *L){
	List temp, *trav;
	for(trav = L; *trav != -1 && VH->HS[*trav].next != -1; trav = &VH->HS[*trav].next){}
	if(*trav != -1){
		temp = *trav;
		*trav = VH->HS[temp].next;
		deallocSpace(VH, temp);
		VH->count--;
	}
}

void deletePosition(VirtualHeap *VH, List *L, int position){
	List temp, *trav;
	int i;
	trav = L;
	for(i = 0; i < position; i++){
		trav = &VH->HS[*trav].next;
	}
	if(*trav != -1){
		temp = *trav;
		*trav = VH->HS[temp].next;
		deallocSpace(VH, temp);
		VH->count--;
	}
}

void visualizeHeap(VirtualHeap VH){
	int i;
	printf("%15s | %15s | %15s\n", "INDEX", "ELEM", "NEXT");
	for(i = 0; i < MAX; i++){
		printf("%15d | %15d | %15d\n", i, VH.HS[i].elem, VH.HS[i].next);
	}
	printf("Avail: %d\n", VH.Avail);
	printf("\n");
}

void display(VirtualHeap VH, List L){
	List trav;
	printf("[ ");
	trav = L;
	while(trav != -1){
		printf("%d ", VH.HS[trav].elem);
		trav = VH.HS[trav].next;
	}
	printf("]\n");
}
