#include <stdio.h>

typedef struct node{
	char data;
	struct node *link;
}*LinkList;


typedef struct{
	LinkList front,
	LinkLIst rear
}Queue;
