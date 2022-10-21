#include <stdio.h>

#define Max 10
#define EMPTY -1
#define DELETED 0

typedef struct{
	int data[Max];
	int count;
}Dictionary;

typedef int SET[6];

void initDictionary(Dictionary *D);
int hashValue(int data);
void insertDictionary(Dictionary *D, int data);
void deleteDictionary(Dictionary *D, int data);
int isMember(Dictionary D, int data);
void display(Dictionary D);

int main(){
	SET data = {31, 32, 33, 43, 39, 99};
	Dictionary D;
	initDictionary(&D);
	int x;
	for(x = 0; x < 6; x ++) insertDictionary(&D, data[x]);
	display(D);
	
	deleteDictionary(&D, 43);
	puts("\nDelete: [43]");display(D);
	
	int retVal = isMember(D, 99);
	printf("%d\n", retVal);
	
	return 0;
}

void initDictionary(Dictionary *D){
	int x;
	for(x = 0; x < Max; x++){
		D->data[x] = EMPTY;
	}
	D->count = 0;
}

int hashValue(int data){
	return data%10;
}

void insertDictionary(Dictionary *D, int data){
	int hash, location;
	if(D->count < Max){
		hash = hashValue(data);
		if(D->data[hash] == EMPTY){
			D->data[hash] = data;
		}else{
			for(location = (hash+1)%Max; D->data[location] != EMPTY && D->data[location] != DELETED; location = (location+1)%Max){}
			D->data[location] = data;
		}
		D->count++;
	}
}

void deleteDictionary(Dictionary *D, int data){
	int hash, location;
	
	hash = hashValue(data);
	if(D->data[hash] == data){
		D->data[hash] = DELETED;
	}else{
		for(location = (hash+1)%Max; D->data[location] != data; location = (location+1)%Max){}
		D->data[location] = D->data[D->count];
		D->count--;
	}
}

int isMember(Dictionary D, int data){
	int hash, x;
	
	hash = hashValue(data);
	for(x = 1; D.data[hash] != EMPTY && data != D.data[hash]; x++){
		hash = (hash+x)%Max;
	}
	return (D.data[hash] != EMPTY) ? data : -1;
}

void display(Dictionary D){
	char hash, x, sl = 0;
	float asl = 0;
	
	printf("DATA:\t");
	for(x = 0; x < Max; x++){
		printf("%d\t", D.data[x]);
	}
	
	printf("\nINDEX:\t");
	for(x = 0; x < Max; x++){
		printf("[%d]\t", x);
	}
	
	printf("\nSL:\t");
	for(x = 0; x < Max; x++){
		if(D.data[x] != EMPTY){
			hash = hashValue(D.data[x]);
			sl = ((x+Max)-hash+1)%Max;
			asl += sl;
			printf("%d\t", sl);
		}else{
			printf("--\t");
		}
	}
	printf("\nAverage SL: %.2f\n\n", asl/D.count);
}
