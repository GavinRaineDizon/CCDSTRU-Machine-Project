#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char String[5];

void initBoard(String state[][3]){
	
	int i, j;	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			strcpy(state[i][j], "FREE");
		
}

void printBoard(String state[][3]){

	int i, j, k = 0;
	//i, j intended for border formatting
	// i, k intended for coordinates
	for(i = 1; i < 12; i++){
		if(i % 4 == 0){
			for(j = 1; j < 21; j++){
				if(j % 7 == 0)
					printf("%c",219);
				else
					printf("%c", 220);
			}
			printf("\n");
			
		}else if(i % 2 == 0){
			printf(" %-4s %c %-4s %c %-4s\n", state[k][i % 2], 219, state[k][i % 2 + 1], 219, state[k][i % 2 + 2]);
			k++;
		}	
		else
			printf(" %-4s %c %-4s %c %-4s\n", " ", 219, " ", 219, " ");	
	}	
}

void NextPlayerMove(String state[][3], int row, int col, int * cardinality, int turn){
		
	if(*cardinality < 3){
		if(turn)
			strcpy(state[row-1][col-1], "DOS");
		else
			strcpy(state[row-1][col-1], "UNO");
		(*cardinality)++;
	}else{
		strcpy(state[row-1][col-1], "FREE");
		(*cardinality)--;
	}
		
}

int isCoordinateValid(String state[][3], int posRow, int posCol, int turn, int *turnCntPtr){
	
	if(turn && strcmp(state[posRow - 1][posCol - 1],"UNO") == 0 || !turn && strcmp(state[posRow - 1][posCol - 1], "DOS") == 0 || 
	*turnCntPtr == 3 && strcmp(state[posRow - 1][posCol - 1], "FREE") == 0 || 
	((!turn && strcmp(state[posRow - 1][posCol - 1], "UNO") == 0 || turn && strcmp(state[posRow - 1][posCol - 1],"DOS") == 0) && *turnCntPtr < 3))
		return  0;
	else
		return 1;
}

int main(){
	//Variable Initialization
	String state[3][3]; //x
	int over = 0;
	int turn = 1;
	
//Turn Cardinalities
	int Uno = 0; 
	int Dos = 0;
	int *turnCntPtr; 

	int posRow = 0;
	int posCol = 0;
	int valid;
	int valid2;
	initBoard(state);
	
	do{
		turn = !turn;
		valid = 1;
		
		if(turn)
			turnCntPtr = &Dos;
		else
			turnCntPtr = &Uno;
		
		printBoard(state);

		printf("\nIt is %s's turn\n", turn ? "Dos": "Uno");
		
		do{
			do{	
				if(!valid)
					printf("INVALID");

				printf("\nEnter row coordinate [1-3]: ");
				scanf("%d", &posRow);				
			}while(posRow <= 0 || posRow >= 4);
			do{
				printf("\nEnter column coordinate[1-3]: ");
				scanf("%d", &posCol);									
			}while(posCol <= 0 || posCol >= 4);
				valid = 0;
		}while(!isCoordinateValid(state, posRow, posCol, turn, turnCntPtr));
	
		//GameOver();
		NextPlayerMove(state, posRow, posCol, turnCntPtr, turn);
		system("cls");
	}while(!over);
	
    return 0;
}


