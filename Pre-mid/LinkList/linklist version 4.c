#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char *data;
	struct node *link;
}*LinkList;

void initList(LinkList *LL);
void insertFront(LinkList *LL, char data);
void display(LinkList LL);

int main(){
	
	LinkList LL;
	insertFront(&LL, 1);
	insertFront(&LL, 2);
	insertFront(&LL, 3);
	insertFront(&LL, 4);
	display(LL);
	
	return 0;
}

void initList(LinkList *LL){
	*LL = (LinkList)calloc(1, sizeof(LinkList));
}

void insertFront(LinkList *LL, char data){
	LinkList temp;
	temp = (LinkList)malloc(sizeof(LinkList));
	if(temp != NULL){
		temp->data = data;
		temp->link = *LL;
		*LL = temp;
	}
}

void display(LinkList LL){
	LinkList trav;
	trav = LL;
	while(trav != NULL){
		printf("%d ", trav->data);
		trav = trav->link;
	}
}
