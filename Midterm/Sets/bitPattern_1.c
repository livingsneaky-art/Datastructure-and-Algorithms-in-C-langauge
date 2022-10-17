#include <stdio.h>

void display(char value);

int main(){
	unsigned char value = 255;
	
	display(value);
	
	return 0;
}

void display(char value){
	int gap, bits = (sizeof(value) * 8)-1;
	unsigned int mask;
	
	for(gap = 1, mask = 1<< bits; mask > 0; mask >>= 1, gap++){
		printf("%d ",(value & mask) ? 1 : 0);
		if(gap % 4 == 0){
			printf(" ");
		}
	}
}
