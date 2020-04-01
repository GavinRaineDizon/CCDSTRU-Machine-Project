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
		printf("[%d]\n");
	}
		
}
//made changes
void GameOver(String state[][3], int * over){
	
	char result[20] = {'\0'};
	char who[5];
	
	//DIAGONAL 1 WIN CONDITION
	if(strcmp(state[0][0], state[1][1]) == 0 && strcmp(state[1][1], state[2][2]) == 0 && strcmp(state[2][2], "FREE") != 0)
		strcpy(who, state[0][0]);
	else if(strcmp(state[2][0], state[1][1]) == 0 && strcmp(state[1][1], state[2][0]) == 0 && strcmp(state[2][0], "FREE") != 0)
		strcpy(who, state[2][0]);
	else if(strcmp(state[0][1], state[1][1]) == 0 && strcmp(state[1][1], state[2][1]) == 0 && strcmp(state[2][1], "FREE") != 0)
		strcpy(who, state[0][1]);
	else if(strcmp(state[0][1], state[1][1]) == 0 && strcmp(state[1][1], state[2][1]) == 0 && strcmp(state[2][1], "FREE") != 0)
		strcpy(who, state[0][1]);
	else if(strcmp(state[1][0], state[1][1]) == 0 && strcmp(state[1][1], state[1][2]) == 0 && strcmp(state[1][2], "FREE") != 0)
		strcpy(who, state[1][0]);
	else
		strcpy(who, "FREE");
	if(strcmp(who, "FREE") == 0){	
	}
	else{
		if(strcmp(who, "UNO") == 0){
			strcpy(result, "UNO wins");
			printf("\n%s\n\n", result);}
		else{
			strcpy(result, "DOS wins");
			printf("\n%s\n\n", result);
		}
		*over = 1;
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
	
	initBoard(state);
	do{
		turn = !turn;
		if(turn)
			turnCntPtr = &Dos;
		else
			turnCntPtr = &Uno;
		
		printBoard(state);
		printf("\nIt is %s turn\n", turn ? "Dos's": "Uno's");
		
		do{
			do{
				printf("\nEnter row coordinate [1-3]: ");
				scanf("%d", &posRow);				
			}while(posRow <= 0 || posRow >= 4);
			do{
				printf("\nEnter column coordinate[1-3]: ");
				scanf("%d", &posCol);					
			}while(posCol <= 0 || posCol >= 4);
		
		}while(!isCoordinateValid(state, posRow, posCol, turn, turnCntPtr));
	
		NextPlayerMove(state, posRow, posCol, turnCntPtr, turn);
		//changed this
	    GameOver(state, &over);
	
	    	system("pause");
			system("cls");
		
		//until here
	}while(!over);
	
    return 0;
}


