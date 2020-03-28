#include <stdio.h>
#include <string.h>
//HEADER FILES

typedef char String[5];

void initBoard(String state[]){
	
	int i;	
	for(i = 0; i < 9; i++)
		strcpy(state[i], "FREE");

}

void printBoard(String state[]){

	int i, j;
	
	for(i = 1; i < 12; i++){
		if(i % 4 == 0){
			for(j = 1; j < 21; j++){
				if(j % 7 == 0)
					printf("%c",219);
				else
					printf("%c", 220);
			}
			printf("\n");
		}else if(i % 2 == 0)
			printf(" %-4s %c %-4s %c %-4s\n", state[i / 2 - 1], 219, state[i/2], 219, state[i/2 + 1]);
		else
			printf(" %-4s %c %-4s %c %-4s\n", " ", 219, " ", 219, " ");	
	}
	

}


int main(){

	String state[9];
	
	initBoard(state);
	printBoard(state);
	
	
	



    return 0;
}


