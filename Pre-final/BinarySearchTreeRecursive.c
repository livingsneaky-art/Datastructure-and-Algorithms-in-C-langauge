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

void initTree(BST *B);

void Insert(BST *B, int elem); //Recursive
void Delete(BST *B, int elem); //Recursive
int DeleteMin(BST *B); //Recursive
int Member(BST B, int elem); //Recursive
int MIN(BST B); //Recursive
int MAX(BST B); //Recursive

void preOrder(BST B); //Recursive
void inOrder(BST B); //Recursive
void postOrder(BST B); //Recursive

int main(){
	
	BST B;
	SET D = {77, 28, 8, 10, 18, 39, 29, 76, 90, 89, 85, 95, 94, 98};
	int x;
	
	initTree(&B);
	for(x = 0; x < Max; x++) Insert(&B, D[x]);
	
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
	printf("\n\n");
	
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
	trav = B;
	
	if(*trav == NULL){
		*trav = (BST)calloc(1, sizeof(struct node));
		if(*trav != NULL){
			(*trav)->elem = elem;
		}
	}else if((*trav)->elem == elem){
		printf("%d is not unique", elem);
	}else if(elem < (*trav)->elem){
		Insert(&(*trav)->LC, elem);
	}else {
		Insert(&(*trav)->RC, elem);
	}
}

void Delete(BST *B, int elem){
	BST *trav, temp;
	trav = B;
	
	if(*trav == NULL){
		printf("Elem/Node not found");
	}else if(elem == (*trav)->elem){
		if((*trav)->RC == NULL){
			temp = *trav;
			*trav = temp->LC;
			free(temp);
		}else if((*trav)->LC == NULL){
			temp = *trav;
			*trav = temp->RC;
			free(temp);
		}else {
			(*trav)->elem = DeleteMin(&(*trav)->RC);
		}
	}else if(elem < (*trav)->elem){
		Delete(&(*trav)->LC, elem);
	}else{
		Delete(&(*trav)->RC, elem);
	}
}

int DeleteMin(BST *B){
	BST *trav, temp;
	trav = B;
	int ret;
	
	if((*trav)->LC == NULL){
		temp = *trav;
		*trav = temp->RC;
		ret = temp->elem;
		free(temp);
		return ret;
	}else{
		return DeleteMin(&(*trav)->LC);
	}
}

int Member(BST B, int elem){
	if(B == NULL){
		return 0;
	}else if(elem == B->elem){
		return 1;
	}else if(elem < B->elem){
		return Member(B->LC, elem);
	}else {
		return Member(B->RC, elem);
	}
}

int MIN(BST B){
	BST trav;
	trav = B;
	if(trav->LC == NULL){
		return trav->elem;
	}else if(trav->LC != NULL){
		MIN(trav->LC);
	}
}

int MAX(BST B){
	BST trav;
	trav = B;
	if(trav->RC == NULL){
		return trav->elem;
	}else if(trav->RC != NULL){
		MAX(trav->RC);
	}
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
