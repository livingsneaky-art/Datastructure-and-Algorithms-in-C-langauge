#include <stdio.h>

#define MAX 10

typedef struct{
	char data;
	int next;
}HeapQueue[MAX];

typedef struct{
	HeapQueue HQ;
	int Avail;
}VirtualQueue;

typedef struct {
	int front;
	int rear;
}Queue;

typedef enum {
	TRUE = 1,
	FALSE = 0
}Boolean;

void initHeap(VirtualQueue *VQ){
	int i;
	for(i = MAX-1; i >= 0; --i){
		VQ->HQ[i].data = 0;
		VQ->HQ[i].next = i-1;
	}
	VQ->Avail = MAX-1;
}

int allocSpace(VirtualQueue *VQ){
	int retAvail = VQ->Avail;
	if(retAvail != -1){
		VQ->Avail = VQ->HQ[VQ->Avail].next;
	}
	return retAvail;
}

void deallocSpace(VirtualQueue *VQ, int index){
	if(index < MAX && VQ->Avail != -1){
		VQ->HQ[index].data = 0;
		VQ->HQ[index].next = VQ->Avail;
		VQ->Avail = index;
	}
}

void initQueue(Queue *Q){
	Q->front = -1;
	Q->rear = -1;
}

void enqueue(VirtualQueue *VQ, Queue *Q, char data){
	int temp;
	temp = allocSpace(VQ);
	if(temp != -1){
		VQ->HQ[temp].data = data;
		VQ->HQ[temp].next = -1;
		
		if(Q->front == -1){
			Q->front = temp;
		}else{
			VQ->HQ[Q->rear].next = temp;
		}
		Q->rear = temp;
	}
}

void dequeue(VirtualQueue *VQ, Queue *Q){
	int temp;
	if(Q->front != -1){
		temp = Q->front;
		Q->front = VQ->HQ[temp].next;
		deallocSpace(VQ, temp);
	}
}

int front(VirtualQueue VQ, Queue Q){
	return (Q.front != -1) ? VQ.HQ[Q.front].data : -1;
}

Boolean isEmpty(VirtualQueue VQ, Queue Q){
	return (Q.front == -1 && VQ.Avail != -1) ? TRUE : FALSE;
}

Boolean isFull(VirtualQueue VQ, Queue Q){
	return (Q.rear == MAX-1 && VQ.Avail != -1) ? TRUE : FALSE;
}

void visualizeQueue(VirtualQueue VQ){
	int i;
	printf("%15s | %15s | %15s\n", "INDEX", "ELEM", "NEXT");
	for(i = 0; i < MAX; i++){
		printf("%15d | %15d | %15d\n", i, VQ.HQ[i].data, VQ.HQ[i].next);
	}
	printf("Avail: %d\n", VQ.Avail);
}

void display(VirtualQueue VQ, Queue Q){
	for(; Q.front != -1; Q.front = VQ.HQ[Q.front].next){
		printf("%d ", VQ.HQ[Q.front].data);
	}
	printf("\n");
	
}

int main(){
	
	VirtualQueue VQ;
	Queue Q;
	initQueue(&Q);
	initHeap(&VQ);
	visualizeQueue(VQ);
	display(VQ, Q);
	enqueue(&VQ, &Q, 1);
	enqueue(&VQ, &Q, 2);
	enqueue(&VQ, &Q, 3);
	enqueue(&VQ, &Q, 4);
	visualizeQueue(VQ);
	display(VQ, Q);
	dequeue(&VQ, &Q);
	visualizeQueue(VQ);
	display(VQ, Q);
	int retVal = front(VQ, Q);
	printf("%d\n ", retVal);
	Boolean retVal1 = isEmpty(VQ, Q);
	printf("%d\n ", retVal1);
	Boolean retVal2 = isFull(VQ, Q);
	printf("%d\n ", retVal2);
	
	return 0;
}
