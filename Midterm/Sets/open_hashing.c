#include <stdio.h>
#include <stdlib.h>

#define Max 10

typedef struct node{
	int data;
	struct node *next;
}*LinkList;

typedef int SET[Max];
typedef LinkList Dictionary[Max];

void initDictionary(Dictionary D);
int hashValue(int data);
void insertDictionary(Dictionary D, int data);
void insertSortedDictionary(Dictionary D, int data);
void deleteDictionary(Dictionary D, int data);
void display(Dictionary D);

int main(){
	SET data = {99, 25, 16, 263, 75, 43, 72, 78, 45, 10};
	Dictionary D;
	initDictionary(D);
	int x;
	display(D);
	for(x = 0; x < Max; x++)insertDictionary(D, data[x]);
	display(D);
	
	insertSortedDictionary(D, 35);
	puts("\nInsert Sorted: [35]");display(D);
	
	deleteDictionary(D, 75);
	puts("\nDelete: [75]");display(D);
	
	return 0;
}

void initDictionary(Dictionary D){
	int x;
	for(x = 0; x < Max; x++){
		D[x] = NULL;
	}
}

int hashValue(int data){
	return data%10;
}

void insertDictionary(Dictionary D, int data){
	LinkList *trav;
	int x;
	char hash;
	
	hash = hashValue(data);
	for(trav = &D[hash]; *trav != NULL && data != (*trav)->data; trav = &(*trav)->next){}
	*trav = (LinkList)calloc(1, sizeof(struct node));
	if(*trav != NULL){
		(*trav)->data = data;
		(*trav)->next = NULL;
	}
}

void insertSortedDictionary(Dictionary D, int data){
	LinkList *trav, temp;
	
	char hash = hashValue(data);
	for(trav = &D[hash]; *trav != NULL && data > (*trav)->data; trav = &(*trav)->next){}
	if(*trav == NULL || data != (*trav)->data){
		temp = (LinkList)calloc(1, sizeof(struct node));
		if(temp != NULL){
			temp->data = data;
			temp->next = *trav;
			*trav = temp;
		}
	}
}

void deleteDictionary(Dictionary D, int data){
	LinkList *trav, temp;
	
	char hash = hashValue(data);
	for(trav = &D[hash]; *trav != NULL && data != (*trav)->data; trav = &(*trav)->next){}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->next;
		free(temp);
	}
}

void display(Dictionary D){
	LinkList trav;
	int x;
	
	printf("[index]\n");
	for(x = 0; x < Max; x++){
		printf("%3s[%d] =>", "D", x);
		
		for(trav = D[x]; trav != NULL; trav = trav->next){
			printf("%4d", trav->data);
			printf("%4s", "->");
		}
		if(trav == NULL) printf("%4c", 254);
		printf("\n");
	}
	printf("\n");
}
