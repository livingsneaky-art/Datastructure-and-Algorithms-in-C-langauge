#include <stdio.h>
#include <stdlib.h>


struct LNode{
	char data;
	struct LNode *link;
};

typedef struct node{
	struct LNode *elemPtr;
	int count;
}LinkList;



void initList(LinkList *LL);
void insertFront(LinkList *LL, char data);
void insertRear(LinkList *LL, char data);
void insertPosition(LinkList *LL, char data, int position);
void insertSorted(LinkList *LL, char data);
void deleteFront(LinkList *LL);
void deleteRear(LinkList *LL);
void deletePosition(LinkList *LL, int position);
void display(LinkList LL);

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
	LL->count = 0;
}

void insertFront(LinkList *LL, char data){
	struct LNode *temp;
	temp = (struct LNode*)malloc(sizeof(struct LNode));
	if(temp != NULL){
		temp->data = data;
		temp->link = LL->elemPtr;
		LL->elemPtr = temp;
		LL->count++;
	}
}

void insertRear(LinkList *LL, char data){
	struct LNode *temp, **trav;
	for(trav = &LL->elemPtr; *trav != NULL; trav = &(*trav)->link){}
	temp = (struct LNode*)malloc(sizeof(struct LNode));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
		LL->count++;
	}
}

void insertPosition(LinkList *LL, char data, int position){
	struct LNode *temp, **trav;
	int x;
	trav = &LL->elemPtr;
	for(x = 0; x < position; x++){
		trav = &(*trav)->link;
	}
	temp = (struct LNode*)malloc(sizeof(struct LNode));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
		LL->count++;
	}
}

void insertSorted(LinkList *LL, char data){
	struct LNode *temp, **trav;
	for(trav = &LL->elemPtr; *trav != NULL && data < (*trav)->data; trav = &(*trav)->link){}
	temp = (struct LNode*)malloc(sizeof(struct LNode));
	if(temp != NULL){
		temp->data = data;
		temp->link = *trav;
		*trav = temp;
		LL->count++;
	}
}

void deleteFront(LinkList *LL){
	struct LNode *temp;
	if(LL->count > 0){
		temp = LL->elemPtr;
		LL->elemPtr = temp->link;
		free(temp);
		LL->count--;
	}
}

void deleteRear(LinkList *LL){
	struct LNode *temp, **trav;
	if(LL->count > 0){
		for(trav = &LL->elemPtr; *trav != NULL && (*trav)->link != NULL; trav = &(*trav)->link){}
		if(*trav != NULL){
			temp = *trav;
			*trav = temp->link;
			free(temp);
			LL->count--;
		}
	}
}

void deletePosition(LinkList *LL, int position){
	struct LNode *temp, **trav;
	int x;
	if(LL->count > 0){
		trav = &LL->elemPtr;
		for(x = 0; x < position; x++){
			trav = &(*trav)->link;
		}
		if(*trav != NULL){
			temp = *trav;
			*trav = temp->link;
			free(temp);
			LL->count--;
		}
	}
}

void display(LinkList LL){
	struct LNode *trav;
	printf("[ ");
	trav = LL.elemPtr;
	while(trav != 0){
		printf("%d ", trav->data);
		trav = trav->link;
	}
	printf("]\n");
}

