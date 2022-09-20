#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char *data;
	struct node *link;
}*LinkList;

void initList(LinkList *LL);
void insertFront(LinkList *LL, char data);
void insertRear(LinkList *LL, char data);
void insertPosition(LinkList *LL, char data, int position);
void insertSorted(LinkList *LL, char data);
void deleteFront(LinkList *LL);
void deleteRear(LinkList *LL);
void deletePosition(LinkList *LL, int position);
void display(LinkList LL);;

int main(){
	
	LinkList LL;
	initList(&LL);
	insertFront(&LL, 1);
	insertFront(&LL, 2);
	insertFront(&LL, 3);
	insertFront(&LL, 4);
	display(LL);
	insertRear(&LL, 5);
	display(LL);
	insertPosition(&LL, 6, 0);
	display(LL);
	insertSorted(&LL, 1);
	display(LL);
	deleteFront(&LL);
	display(LL);
	deleteRear(&LL);
	display(LL);
	deletePosition(&LL, 4);
	display(LL);
	
	return 0;
}

void initList(LinkList *LL){
	*LL = NULL;
}

void insertFront(LinkList *LL, char data){
	LinkList temp;
	temp = (LinkList)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = *LL;
		*LL = temp;
	}
}

void insertRear(LinkList *LL, char data){
	LinkList temp, *trav;
	for(trav = LL; *trav != NULL; trav = &(*trav)->link){}
	temp = (LinkList)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
	}
}

void insertPosition(LinkList *LL, char data, int position){
	LinkList temp, *trav;
	int i;
	trav = LL;
	for(i = 0; i < position; i++){
		trav = &(*trav)->link;
	}
	temp = (LinkList)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
	}
}

void insertSorted(LinkList *LL, char data){
	LinkList temp, *trav;
	for(trav = LL; *trav != NULL && data < (*trav)->data; trav = &(*trav)->link){}
	temp = (LinkList)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
	}
}

void deleteFront(LinkList *LL){
	LinkList temp;
	if(LL != NULL){
		temp = *LL;
		*LL = temp->link;
		free(temp);
	}
}

void deleteRear(LinkList *LL){
	LinkList temp, *trav;
	for(trav = LL; *trav != NULL && (*trav)->link != NULL; trav = &(*trav)->link){}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->link;
		free(temp);
	}
}

void deletePosition(LinkList *LL, int position){
	LinkList temp, *trav;
	int i;
	trav = LL;
	for(i = 0; i < position; i++){
		trav = &(*trav)->link;
	}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->link;
		free(temp);
	}
}

void display(LinkList LL){
	LinkList trav;
	printf("[ ");
	trav = LL;
	while(trav != NULL){
		printf("%d ", trav->data);
		trav = trav->link;
	}
	printf("]\n");
}
