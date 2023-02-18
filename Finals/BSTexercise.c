#include <stdio.h>

typedef struct cell{
	int elem;
	struct cell *LC;
	struct cell *RC;
}ctype, *BST;

BST S;
 int Member(BST B, int elem);
 
 int main(){
 	
 	return 0;
 }
 
 int Member(BST B, int elem){
 	BST trav;
 	for(trav=B; trav!=NULL && elem!=trav->elem;){
 		trav=(elem < trav->elem)?trav->LC : trav->RC;
	 }
	 return (trav!=NULL)?1:0;
 }
