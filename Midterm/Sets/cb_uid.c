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

void initHeap(VirtualHeap *VH;
void initSet(SET *C);
SET populateSet(VirtualHeap *VH, char A[], int count);
SET union_unsorted(VirtualHeap *VH, SET A, SET B);
SET union_sorted(VirtualHeap *VH, SET A, SET B);
SET intersection_sorted(VirtualHeap *VH, SET A, SET B);
SET difference_sorted(VirtualHeap *VH, SET A, SET B);
SET merge(VirtualHeap *VH, SET A, SET B);
int isMember(VirtualHeap VH, SET C, char data);
SET insert(VirtualHeap *VH, SET *C, int position, char data);
int MIN(VirtualHeap VH, SET C);
int MAX(VirtualHeap VH, SET C);
void visualizeHeap(VirtualHeap VH);
void display(VirtualHeap VH, SET C);

int main(){
	
	
	return 0;
}


