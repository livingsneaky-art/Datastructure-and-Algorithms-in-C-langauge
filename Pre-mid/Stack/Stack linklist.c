#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *link;
}*Stack;

typedef enum {
	TRUE = 1, 
	FALSE = 0
}Boolean;

void initStack(Stack *S);
void push(Stack *S, char data);
void pop(Stack *S);
int top(Stack S);
Boolean isEmpty(Stack S);
Boolean isFull(Stack S);
void display(Stack S);

int main(){
	
	Stack S;
	initStack(&S);
	push(&S, 1);
	push(&S, 2);
	push(&S, 3);
	push(&S, 4);
	display(S);
	pop(&S);
	display(S);
	Boolean retVal = isEmpty(S);
	printf("%d\n ",retVal);
	Boolean retVal1 = isFull(S);
	printf("%d ", retVal1);
	
	return 0;
}

void initStack(Stack *S){
	*S = NULL;
}

void push(Stack *S, char data){
	Stack temp;
	temp = (Stack)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = *S;
		*S = temp;
	}	
}

void pop(Stack *S){
	Stack temp;
	if(S != NULL){
		temp = *S;
		*S = temp->link;
		free(temp);
	}
}

int top(Stack S){
	return (S!=NULL) ? S->data : -1;
}

Boolean isEmpty(Stack S){
	return (S==NULL) ? TRUE : FALSE;
}

Boolean isFull(Stack S){
	return (S!=NULL) ? TRUE : FALSE;
}

void display(Stack S){
	Stack trav;
	printf("[ ");
	trav = S;
	while(trav != NULL){
		printf("%d ", trav->data);
		trav = trav->link;
	}
	printf("]\n");
}

