/*
	Binary Search Tree: is a node-based binary tree data structure which has the following properties:
		* The left subtree of a node contains only nodes with keys lesser than the node’s key.
		* The right subtree of a node contains only nodes with keys greater than the node’s key.
		* The left and right subtree each must also be a binary search tree.					(GeeksForGeeks)
*/

/*       Given Tree Structure:
*
*					  	  77
*					   /      \
*                    28        90 
*                  /   \      /   \
*                8    39     89   95
*                \   /  \   /    /  \
*                10 29 76  85   94  98
*
*		Pre-Order:      77 28 8 10 18 39 29 76 90 89 85 95 94 98
*		In-Order:       8 10 18 28 29 39 76 77 85 89 90 94 95 98
*		Post-Order:     18 10 8 29 76 39 28 85 89 94 98 95 90 77
*/


//insert delete member min max
#include <stdio.h>
#include <stdlib.h>

#define Max 14

typedef struct node{
	int elem;
	struct node *LC;
	struct node *RC;
}*BST;

typedef int SET[Max];

void initTree(BST *B); //Non-Recursive
void Insert(BST *B, int elem); //Non-Recursive
void Delete(BST *B, int elem); //Non-Recursive
int Member(BST B, int elem); //Non-Recursive
int MIN(BST B); //Non-Recursive
int MAX(BST B); //Non-Recursive

void preOrder(BST B);
void inOrder(BST B);
void postOrder(BST B);


int main(){
	
	BST B;
	SET D = {77, 28, 8, 10, 18, 39, 29, 76, 90, 89, 85, 95, 94, 98};
	int x;
	initTree(&B);
	
	
	for(x = 0; x < Max; x++) Insert(&B, D[x]);
	//Insert(&B, 10);
	//Insert(&B, 5);
	//Insert(&B, 7);
	//Insert(&B, 14);
	//Insert(&B, 12);
	//Insert(&B, 18);
	//Insert(&B, 15);
	
	printf("Pre-Order: \n");
	preOrder(B);
	printf("\n");
	
	Delete(&B, 28);
	preOrder(B);
	printf("\n");
	
	printf("In-Order: \n");
	inOrder(B);
	printf("\n");
	
	printf("Post-Order: \n");
	postOrder(B);
	printf("\n");
	printf("\n");
	
	printf("||1 Member 0 not\n");
	int result = Member(B, 76);
	printf("%d\n", result);
	
	int resultMin = MIN(B);
	printf("Min: %d\n", resultMin);
	
	int resultMax = MAX(B);
	printf("Max: %d\n", resultMax);
	return 0;
}

void initTree(BST *B){
	*B = NULL;
}

void Insert(BST *B, int elem){
	BST *trav;
	for(trav=B; *trav != NULL && elem != (*trav)->elem;){
		trav = ((*trav)->elem < elem) ? &(*trav)->RC : &(*trav)->LC;
	}
	
	if(*trav == NULL){
		*trav = (BST)calloc(1, sizeof(struct node));
		if(*trav != NULL){
			(*trav)->elem = elem;
		}
	}
}

void Delete(BST *B, int elem){
	BST *trav, *trav2, temp;
	
	for(trav = B; *trav != NULL && elem != (*trav)->elem;){
		trav = ((*trav)->elem < elem) ? &(*trav)->RC : &(*trav)->LC;
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
			(*trav)->elem = temp->elem;
			free(temp);
		}
	}
}

int Member(BST B, int elem){
	BST trav;
	for(trav = B; trav != NULL && elem != trav->elem;){
		trav = (trav->elem < elem) ? trav->RC : trav->LC;
	}
	return (trav != NULL) ? 1 : 0;
}

int MIN(BST B){
	BST trav;
	for(trav = B; trav->LC != NULL; trav = trav->LC){}
	return trav->elem;
}

int MAX(BST B){
	BST trav;
	for(trav = B; trav->RC != NULL; trav = trav->RC){}
	return trav->elem;
}

void preOrder(BST B){
	if(B != NULL){
		printf("%d ", B->elem);
		preOrder(B->LC);
		preOrder(B->RC);
	}
}

void inOrder(BST B){
	if(B != NULL){
		inOrder(B->LC);
		printf("%d ", B->elem);
		inOrder(B->RC);
	}
}

void postOrder(BST B){
	if(B != NULL){
		postOrder(B->LC);
		postOrder(B->RC);
		printf("%d ", B->elem);
	}
}
