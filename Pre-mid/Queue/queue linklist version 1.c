#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *link;
}*LinkList;


typedef struct{
	LinkList front;
	LinkList rear;
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
void display(Queue Q);

int main(){
	
	Queue Q;
	initQueue(&Q);
	enqueue(&Q, 1);
	enqueue(&Q, 2);
	enqueue(&Q, 3);
	enqueue(&Q, 4);
	display(Q);
	dequeue(&Q);
	display(Q);
	Boolean retVal = isEmpty(Q);
	printf("%d ", retVal);
	printf("\n");
	Boolean retVal1 = isFull(Q);
	printf("%d ", retVal1);
	
	return 0;
}

void initQueue(Queue *Q){
	Q->front = NULL;
	Q->rear = NULL;
}

void enqueue(Queue *Q, char data){
	LinkList temp;
	temp = (LinkList)calloc(1, sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		if(Q->rear == NULL){
			Q->front = temp;
		}else{
			Q->rear->link = temp;
		}
		Q->rear = temp;
	}
}

void dequeue(Queue *Q){
	LinkList temp;
	if(Q->front != NULL){
		temp = Q->front;
		Q->front = temp->link;
		if(Q->front == NULL){
			Q->rear = NULL;
		}
		free(temp);
	}
}

int front(Queue Q){
	return (Q.front != NULL) ? Q.front->data : -1;
}

Boolean isEmpty(Queue Q){
	return (Q.front == NULL) ? TRUE : FALSE;
}

Boolean isFull(Queue Q){
	return (Q.front != NULL) ? TRUE : FALSE;
}

void display(Queue Q){
	LinkList temp;
	Queue QQ;
	initQueue(&QQ);
	
	while(Q.front != NULL){
		printf("%d ", Q.front->data);
		temp = Q.front;
		Q.front = temp->link;
		if(QQ.front == NULL){
			QQ.front = temp;
		}else{
			QQ.rear->link = temp;
		}
		QQ.rear = temp;
	}
	
	while(QQ.front!= NULL){
		temp = QQ.front;
		QQ.front = temp->link;
		if(Q.front == NULL){
			Q.front = temp;
		}else{
			Q.rear->link = temp;
		}
		Q.rear = temp;
	}
	printf("\n");
	printf("Front: %d\nRear: %d\n", Q.front->data, Q.rear->data);
}
