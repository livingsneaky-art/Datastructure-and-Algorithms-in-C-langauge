#include <stdio.h>

#define MAX 10

typedef struct{
	char data[MAX];
	int top;
}Stack;

typedef enum{
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
	printf("%d\n", retVal);
	Boolean retVal1 = isFull(S);
	printf("%d\n", retVal1);
	
	return 0;
}

void initStack(Stack *S){
	S->top = -1;
}

void push(Stack *S, char data){
	if(S->top != MAX-1){
		S->top++;
		S->data[S->top] = data;
	}
}

void pop(Stack *S){
	if(S->top != -1){
		S->top--;
	}
}

int top(Stack S){
	return (S.top != -1) ? S.data[S.top] : -1;
}

Boolean isEmpty(Stack S){
	return (S.top == -1) ? TRUE : FALSE;
}

Boolean isFull(Stack S){
	return (S.top == MAX-1) ? TRUE : FALSE;
}

void display(Stack S){
	Stack temp;
	initStack(&temp);
	while(S.top != -1){
		push(&temp, top(S));
		pop(&S);
	}
	
	while (temp.top != -1){
		printf("%d ", temp.data[temp.top]);
		push(&S, top(temp));
		pop(&temp);
		
	}
	printf("\n");
	
}
