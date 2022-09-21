#include <stdio.h>

typedef struct node{
	char data;
	struct node *link;
}Stack;

void initStack(Stack *S);
void push(Stack *S, char data);
void pop(Stack *S);
int top(Stack S);
Boolean isEmpty(Stack S);
Boolean isFull(Stack S);
void display(Stack S);

int main(){
	
	
	return 0;
}

