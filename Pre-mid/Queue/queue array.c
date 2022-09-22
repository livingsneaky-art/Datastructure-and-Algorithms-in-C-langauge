#include <stdio.h>

#define MAX 10

typedef struct{
	char data[MAX];
	int front;
	int rear;
}Queue;

typedef enum{
	TRUE = 1,
	FALSE = 0
}Boolean;

void initQueue(Queue *Q);
void enqueue(Queue *Q, char data);
void dequeue(Queue *Q);
int front(Queue Q);
Boolean isEmpty(Queue Q);
Boolean isFull(Queue Q);
void visualizeQueue(Queue Q);
void display(Queue Q);

int main(){
	
	Queue Q;
	initQueue(&Q);
	visualizeQueue(Q);
	display(Q);
	enqueue(&Q, 1);
	visualizeQueue(Q);
	display(Q);
	enqueue(&Q, 2);
	visualizeQueue(Q);
	display(Q);
	enqueue(&Q, 3);
	visualizeQueue(Q);
	display(Q);
	
	return 0;
}
//version 1
void initQueue(Queue *Q){
	int i;
	for(i = 0; i < MAX; i++){
		Q->data[i] = 0;
	}
	Q->front = 1;
	Q->rear = 0;
}
//clockwise
void enqueue(Queue *Q, char data){
	if((Q->rear+2)%MAX != Q->front){
		Q->rear = (Q->rear+1)%MAX;
		Q->data[Q->rear] = data;
	}
}

void visualizeQueue(Queue Q){
	int i;
	for(i = 0; i < MAX; i++){
		printf("%5d", Q.data[i]);
	}
	printf("\n");
	for(i = 0; i < MAX; i++){
		printf("%5d", i);
	}
	printf("\n");
	printf("Front: %d\nRear: %d\n", Q.front, Q.rear);
}

void display(Queue Q){
	printf("{ ");
	for(; Q.front!=(Q.rear + 1)%MAX; Q.front = (Q.front + 1)%MAX){
		printf("%d ", Q.data[Q.front]);
	}
	printf(" }\n");
}
