#include <stdio.h>
#include <stdlib.h>

typedef struct item{
	int item_id;
	char item_name[16];
	int item_qty;
}itemType;

typedef struct node{
	itemType record;
	struct node *LC;
	struct node *RC;
}*BSTree;

void initTree(BSTree *B);
void Insert(BSTree *B, itemType detail);
BSTree *findMemberPos(BSTree *B, int itemID);
int decreaseInventory(BSTree *B, itemType rec);

int MIN(BSTree B);
BSTree *deleteMinProd(BSTree *B, int elem);

void preOrder(BSTree B); //Recursive
void inOrder(BSTree B); //Recursive
void postOrder(BSTree B); //Recursive

int main(){
	BSTree B;
	BSTree *result, *retBST;
	itemType a = {5, "Ryan", 3},
			 b = {3, "Jonalyn", 15},
			 c = {8, "Yu", 4},
			 d = {6, "Cristine", 3},
			 e = {4, "Crisha", 6},
			 f = {9, "Kryshna", 5},
			 g = {7, "Ching", 7};
			 
	initTree(&B);
	Insert(&B, a);
	Insert(&B, b);
	Insert(&B, c);
	Insert(&B, d);
	Insert(&B, e);
	Insert(&B, f);
	Insert(&B, g);
	
	printf("Pre-Order: \n");
	preOrder(B);
	printf("\n");
	/*
	Delete(&B, 28);
	preOrder(B);
	printf("\n");
	*/
	printf("In-Order: \n");
	inOrder(B);
	printf("\n");
	
	printf("Post-Order: \n");
	postOrder(B);
	printf("\n");
	printf("\n");
	
	result = findMemberPos(&B, 5);
	printf("Find: %s\n", (*result)->record.item_name);
	
	int retVal = decreaseInventory(&B, b);
	printf("return available stocks: %d\n", retVal);
	
	printf("Pre-Order: \n");
	preOrder(B);
	printf("\n");
	
	int retMin = MIN(B);
	printf("MIN: %d\n", retMin);
	
	retBST = deleteMinProd(&B, retMin);
	printf("%d\n", &(*retBST)->record.item_qty);
	
	printf("Pre-Order: \n");
	preOrder(B);
	printf("\n");
	return 0;
}
void initTree(BSTree *B){
	*B = NULL;
}

void Insert(BSTree *B, itemType detail){
	BSTree *trav;
	for(trav=B; *trav != NULL && detail.item_id != (*trav)->record.item_id;){
		trav = ((*trav)->record.item_id < detail.item_id) ? &(*trav)->RC : &(*trav)->LC;
	}
	
	if(*trav == NULL){
		*trav = (BSTree)calloc(1, sizeof(struct node));
		if(*trav != NULL){
			(*trav)->record = detail;
		}
	}
}

BSTree *deleteMinProd(BSTree *B, int elem){
	BSTree *trav, *trav2, temp, *ret;
	
	for(trav = B; *trav != NULL && elem != (*trav)->record.item_id;){
		trav = ((*trav)->record.item_id < elem) ? &(*trav)->RC : &(*trav)->LC;
	}
	if(*trav != NULL){
		if((*trav)->LC == NULL){
			temp = *trav;
			*trav = temp->RC;
			free(temp);
		}else if((*trav)->RC == NULL){
			temp = *trav;
			*trav = temp->LC;
			free(temp);
		}else{
			for(trav2 = &(*trav)->RC; (*trav2)->LC != NULL; trav2 = &(*trav2)->LC){}
			temp = *trav2;
			*trav2 = temp->RC;
			(*trav)->record = temp->record;
			free(temp);
		}
		
	}
	
	return trav;
}

BSTree *findMemberPos(BSTree *B, int itemID){
	BSTree *trav;
	for(trav = B; *trav != NULL && itemID != (*trav)->record.item_id;){
		trav = (itemID < (*trav)->record.item_id) ? &(*trav)->LC : &(*trav)->RC;
	}
	return trav;
}

int decreaseInventory(BSTree *B, itemType rec){
	BSTree *trav, temp, *trav2;
	int ret = 0;
	
	trav = findMemberPos(B, rec.item_id);
	if(*trav != NULL){
		ret = rec.item_qty;
		if((*trav)->record.item_qty > ret){
			(*trav)->record.item_qty -= ret;
		}else{
			temp = *trav;
			ret = (*trav)->record.item_qty;
			if(temp->LC == NULL){
				*trav = temp->RC;
			}else if(temp->RC == NULL){
				*trav = temp->LC;
			}else{
				for(trav2 = &(*trav)->RC; (*trav2)->LC != NULL; trav2 = &(*trav2)->LC){}
				temp = *trav2;
				*trav2 = temp->RC;
				(*trav)->record = temp->record;
			}
			free(temp);
		}
	}
	return ret;
}

int MIN(BSTree B){
	BSTree trav;
	for(trav = B; trav->LC != NULL; trav = trav->LC){}
	return trav->record.item_id;
}

void preOrder(BSTree B){
	if(B != NULL){
		printf("%d ", B->record.item_id);
		preOrder(B->LC);
		preOrder(B->RC);
	}
}

void inOrder(BSTree B){
	if(B != NULL){
		inOrder(B->LC);
		printf("%d ", B->record.item_id);
		inOrder(B->RC);
	}
}

void postOrder(BSTree B){
	if(B != NULL){
		postOrder(B->LC);
		postOrder(B->RC);
		printf("%d ", B->record.item_id);
	}
}
