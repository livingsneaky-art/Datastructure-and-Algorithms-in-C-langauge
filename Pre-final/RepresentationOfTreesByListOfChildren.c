//Representation Of Trees By List Of Chilren
#include <stdio.h>
#include <stdlib.h>

#define Max 10

typedef struct node{
	int data;
	struct node *link;
}*LinkList;

typedef int root;
typedef LinkList Header[Max];

void initNodes(Header H);
void insertNodes(Header H, char data, int index);
void display(Header H);

int main(){
	
	Header H;
	initNodes(H);
	
	
	insertNodes(H, 4, 1);
	insertNodes(H, 7, 1);
	insertNodes(H, 8, 2);
	insertNodes(H, 0, 5);
	insertNodes(H, 6, 5);
	insertNodes(H, 2, 5);
	insertNodes(H, 3, 6);
	insertNodes(H, 1, 6);
	display(H);
	
}

void initNodes(Header H){
	int x;
	for(x = 0; x < Max; x++){
		H[x] = NULL;
	}
}


void insertNodes(Header H, char data, int index){
	LinkList *trav;
	int x;
	char hash;
	
	
	for(trav = &H[index]; *trav != NULL && data != (*trav)->data; trav = &(*trav)->link){}
	*trav = (LinkList)calloc(1, sizeof(struct node));
	if(*trav != NULL){
		(*trav)->data = data;
		(*trav)->link = NULL;
	}
}

void display(Header H){
	LinkList trav;
	int x;
	
	printf("[Header]\n");
	for(x = 0; x < Max; x++){
		printf("%3s[%d] => ", "H", x);
		
		for(trav = H[x]; trav != NULL; trav = trav->link){
			printf("%4d", trav->data);
			printf("%4s", "->");
		}
		if(trav == NULL) printf("%4c", 254);
		printf("\n");
	}
	printf("\n");
}
