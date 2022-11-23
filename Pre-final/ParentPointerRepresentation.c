//Parent Pointer Representation (Array of Parents)
#include <stdio.h>


#define Max 10

typedef int Tree[Max];

int parent(int node, Tree T);

int main(){
	
	Tree T;
	
	T[0] = 5;
	T[1] = 6;
	T[2] = 5;
	T[3] = 6;
	T[4] = 1;
	T[5] = -1;
	T[6] = 5;
	T[7] = 1;
	T[8] = 2;
	T[9] = -2;
	
	int x;
	
	printf("Tree in array:\n");
	for(x = 0; x < Max; x++){
		printf("%d ", T[x]);
	}
	printf("\n\n");
	int node;
	node = 8;
	printf("Parent of node is: %d\n", node);
	int result = parent(node, T);
	printf("%d\n", result);
	
	return 0;
}

int parent(int node, Tree T){
	return (T[node] != -1 && T[node] != -2) ? T[node] : -1;
}



