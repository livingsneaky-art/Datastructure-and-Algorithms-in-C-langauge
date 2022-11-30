//Minheap
/*
	Formula:
	Left 	= (P*2)+1
	Right 	= (P*2)+2			Alternatives: LC+1 / (P*2+1)+1
	
	Parent  = (child-1)/2
*/

//Maxheap
/*
	Formula:
	Left 	= (P*2)+1
	Right 	= (P*2)+2			Alternatives: LC+1 / (P*2+1)+1
	
	Parent  = (child-1)/2
	
	x = digit
	x x + = postfix	= Reversed Polish Notation
	x + x = infix
	+ x x = prefix	= Polish Notation
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 15


typedef struct{
    int data[SIZE];
    int lastNdx;
}Heap;

typedef int LIST[SIZE];

typedef enum{
	TRUE = 1,
	FALSE = 0
}boolean;

void initializeHeap(Heap *H);
void insertMin(Heap *H, int num);
void insertMax(Heap *H, int num);

int is_minheap(Heap H);
int is_maxheap(Heap H);

void minHeapify(Heap *H);
void maxHeapify(Heap *H);

void display(Heap H);

int main(){
    Heap H;
    LIST D = {20, 5, 9, 8, 6, 9, 10, 10, 18, 9};
    int i, len = 10, toFind;
    
    initializeHeap(&H);
    
    //printf("Min Heap\n");
    //for(i = 0; i < len; i++) insertMin(&H, D[i]);
	//display(H);
	
	printf("Max Heap\n");
	for(i = 0; i < len; i++) insertMax(&H, D[i]);
	display(H);
    
    //printf("\n%s", is_minheap(H) == 1 ? "array is in minheap" : "array is not in minheap");
    printf("\n%s", is_maxheap(H) == 1 ? "array is in maxheap" : "array is not in maxheap");
	
    return 0;
}

void initializeHeap(Heap *H){
    H->lastNdx = -1;
}

//minHeap
void insertMin(Heap *H, int num){
    int childndx = 0, parentndx = 0;
	
    if (H->lastNdx < SIZE-1){
        H->lastNdx++;
        childndx = H->lastNdx;
        parentndx = (childndx-1)/2;

        while (childndx > 0 && H->data[parentndx] > num){
            H->data[childndx] = H->data[parentndx];
            childndx = parentndx;
            parentndx = (childndx-1)/2;
        }
        H->data[childndx] = num;
    }
}

//maxHeap
void insertMax(Heap *H, int num){
    int childndx = 0, parentndx = 0;
	
    if (H->lastNdx < SIZE-1){
        H->lastNdx++;
        childndx = H->lastNdx;
        parentndx = (childndx-1)/2;

        while (childndx > 0 && H->data[parentndx] < num){
            H->data[childndx] = H->data[parentndx];
            childndx = parentndx;
            parentndx = (childndx-1)/2;
        }
        H->data[childndx] = num;
    }
}


int is_minheap(Heap H){
	int parent;
	
	//root to last interval node
	int child = 0;
	boolean flag = TRUE;
	for(parent = 0; parent < (H.lastNdx-1)/2 && flag == TRUE; parent++){
		child = (parent*2)+1;
		// If left child is greater than its parent then return false
		if (H.data[child] < H.data[parent]){
			flag = FALSE;
			break;			
		}
		// If right child is greater its parent then return false
		if(child+1 <= H.lastNdx && H.data[child+1] < H.data[parent]){
			flag = FALSE;
			break;			
		}
	}
	
	/*
	*			Given min-heap : 
	*		
	*		       10 - root is the minimum element
	*		      /  \
	*		     15   30
	*		    /  \  /  \		
	*		   40  50 100 40 - There is no condition where child is greater than its parent, So it is a min-heap.
	*/
	
	return flag;
}

int is_maxheap(Heap H){
	int parent;
	
	//root to last interval node
	int child = 0, flag = 1;
	for(parent = 0; parent < (H.lastNdx-1)/2; parent++){
		child = (parent*2)+1;
		// If left child is greater than its parent then 0
		if (H.data[child] > H.data[parent]){
			flag = 0;
			break;
		}
		// If right child is greater its parent then 0
		if(child+1 <= H.lastNdx && H.data[child+1] > H.data[parent]){
			flag = 0;
			break;
		}
	}
	
    return flag;
}

void minHeapify(Heap *H){
	int lowPar, down, child, swap;
	
	if(H->lastNdx != -1){
		lowPar = (H->lastNdx-1)/2;
		while(lowPar >= 0){
			down = lowPar;
			child = (down*2)+1;

			while(child <= H->lastNdx){
				if(child+1 <= H->lastNdx && H->data[child] > H->data[child+1]){
					child++;
				}
				if(H->data[down] > H->data[child]){
					swap = H->data[down];
					H->data[down] = H->data[child];
					H->data[child] = swap;
					down = child;
					child = (down*2)+1;
				} else{
					child = H->lastNdx+1;
				}
			}
			lowPar--;
		}
	}
}

void maxHeapify(Heap *H){
	int lowPar, down, child, swap;
	
	if(H->lastNdx != -1){
		lowPar = (H->lastNdx-1)/2;
		while(lowPar >= 0){
			down = lowPar;
			child = (down*2)+1;

			while(child <= H->lastNdx){
				if(child+1 <= H->lastNdx && H->data[child+1] > H->data[child]){
					child++;
				}
				if(H->data[down] < H->data[child]){
					swap = H->data[down];
					H->data[down] = H->data[child];
					H->data[child] = swap;
					down = child;
					child = (down*2)+1;
				} else{
					child = H->lastNdx+1;
				}
			}
			lowPar--;
		}
	}
}


void display(Heap H){
    int x;
    for (x = 0; x < H.lastNdx+1; x++){
        printf("[%d]\t", H.data[x]);
    }
    printf("\n");
    for (x = 0; x < H.lastNdx+1; x++){
        printf(" %d\t", x);
    }
    printf("\nLast Index: %d\n", H.lastNdx);
}
