#include <stdio.h>

#define MAX 10

typedef struct{
	char data;
	int next;
}StackSpace[MAX];

typedef struct{
	StackSpace SS;
	int Avail;
}StackHeap;

typedef int List;

typedef enum{
	TRUE = 1,
	FALSE = 0
}Boolean;

void initHeap(StackHeap *SH);
int allocStack(StackHeap *SH);
void dealloc(StackHeap *SH, int index);
void push(StackHeap *SH, List *L, char data);
void pop(StackHeap *SH, List *L);
int top(StackHeap SH, List L);
Boolean isEmpty(StackHeap SH, List L);
Boolean isFull(StackHeap SH, List L);
void visualizeHeap(StackHeap SH);
void display(StackHeap SH, List L);

int main(){
	
	StackHeap SH;
	List L = -1;
	initHeap(&SH);
	Boolean retVal3 = isEmpty(SH, L);
	printf("%d\n ", retVal3);
	visualizeHeap(SH);
	display(SH, L);
	push(&SH, &L, 1);
	push(&SH, &L, 2);
	push(&SH, &L, 3);
	push(&SH, &L, 4);
	visualizeHeap(SH);
	display(SH, L);
	pop(&SH, &L);
	visualizeHeap(SH);
	display(SH, L);
	List retVal = top(SH, L);
	printf("%d\n ", retVal);
	Boolean retVal1 = isEmpty(SH, L);
	printf("%d\n ", retVal1);
	Boolean retVal2 = isFull(SH, L);
	printf("%d\n ", retVal2);
	
	
	return 0;
}

void initHeap(StackHeap *SH){
	int i;
	
	for(i = MAX-1; i >= 0; --i){
		SH->SS[i].data = 0;
		SH->SS[i].next = i-1;
	}
	SH->Avail = MAX-1;
}

int allocStack(StackHeap *SH){
	int retAvail = SH->Avail;
	if(retAvail != -1){
		SH->Avail = SH->SS[SH->Avail].next;
	}
	return retAvail;
}

void dealloc(StackHeap *SH, int index){
	if(index < MAX && SH->Avail != -1){
		SH->SS[index].data = 0;
		SH->SS[index].next = SH->Avail;
		SH->Avail = index;
	}
}

void push(StackHeap *SH, List *L, char data){
	List temp;
	temp = allocStack(SH);
	if(temp != -1){
		SH->SS[temp].data = data;
		SH->SS[temp].next = *L;
		*L = temp;
	}
}

void pop(StackHeap *SH, List *L){
	List temp;
	if(*L != -1){
		temp = *L;
		*L = SH->SS[temp].next;
		dealloc(SH, temp);
	}
}

int top(StackHeap SH, List L){
	return (L != -1) ? SH.SS[L].data : -1;
}

Boolean isEmpty(StackHeap SH, List L){
	return (L == -1) ? TRUE : FALSE;
}

Boolean isFull(StackHeap SH, List L){
	return (L == MAX-1) ? TRUE : FALSE;
}

void visualizeHeap(StackHeap SH){
	int i;
	printf("%15s | %15s | %15s\n", "INDEX", "ELEM", "NEXT");
	for(i = 0; i < MAX; i++){
		printf("%15d | %15d | %15d\n", i, SH.SS[i].data, SH.SS[i].next);
	}
	printf("Avail: %d\n", SH.Avail);
	printf("\n");
}

void display(StackHeap SH, List L){
	List trav;
	printf("[ ");
	trav = L;
	while(trav != -1){
		printf("%d ", SH.SS[trav].data);
		trav = SH.SS[trav].next;
	}
	printf("]\n");
}
