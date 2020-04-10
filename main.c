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

void displayError (String state[][3], int turn, int *turnCntPtr, int posRow, int posCol){
	if (*turnCntPtr==3 && !turn && strcmp(state[posRow-1][posCol-1], "FREE")==0)
		printf ("\n[INVALID] Please choose a tile that you own.\n");
	else if(*turnCntPtr==3 && !turn && strcmp (state[posRow-1][posCol-1], "DOS")==0)
		printf ("\n[INVALID] That's not your tile!\n");
	else if(*turnCntPtr == 3 && turn && strcmp(state[posRow-1][posCol-1], "FREE")==0)
		printf ("\n[INVALID] Please choose a tile that you own.\n");
	else if (*turnCntPtr==3 && turn && strcmp (state[posRow-1][posCol-1], "UNO")==0)
		printf ("\n[INVALID] That's not your tile!\n");
	else if (!turn && *turnCntPtr<3 && strcmp (state[posRow-1][posCol-1], "UNO") == 0)
		printf ("\n[INVALID] Please choose a free tile.\n");
	else if (!turn && *turnCntPtr<3 && strcmp (state[posRow-1][posCol-1], "DOS") == 0)
		printf ("\n[INVALID] Please choose a free tile.\n");
	else if (turn && *turnCntPtr<3 && strcmp (state[posRow-1][posCol-1], "DOS") == 0)
		printf ("\n[INVALID] Please choose a free tile.\n");
	else if (turn && *turnCntPtr<3 && strcmp (state[posRow-1][posCol-1], "UNO") == 0)
		printf ("\n[INVALID] Please choose a free tile.\n");
}

void printBoard(String state[][3]){

	int i, j, k = 0;
	//i, j intended for border formatting

	// i, k intended for coordinates for thr row
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
//made changes
void GameOver(String state[][3], int * over){
	
	char result[20] = {'\0'};
	char who[5];
	
	if(strcmp(state[0][0], state[1][1]) == 0 && strcmp(state[1][1], state[2][2]) == 0 && strcmp(state[2][2], "FREE") != 0)
		strcpy(who, state[0][0]);
	else if(strcmp(state[0][2], state[1][1]) == 0 && strcmp(state[1][1], state[2][0]) == 0 && strcmp(state[2][0], "FREE") != 0)
		strcpy(who, state[2][0]);
	else if(strcmp(state[0][1], state[1][1]) == 0 && strcmp(state[1][1], state[2][1]) == 0 && strcmp(state[2][1], "FREE") != 0)
		strcpy(who, state[0][1]);
	else if(strcmp(state[1][0], state[1][1]) == 0 && strcmp(state[1][1], state[1][2]) == 0 && strcmp(state[1][2], "FREE") != 0)
		strcpy(who, state[1][0]);
	else
		strcpy(who, "FREE");
	if(strcmp(who, "FREE") != 0){	
		if(strcmp(who, "UNO") == 0)
			strcpy(result, "UNO wins");
		else
			strcpy(result, "DOS wins");
			
		printf("%s\n\n", result);
		*over = 1;
	}
}

int isCoordinateValid(String state[][3], int posRow, int posCol, int turn, int *turnCntPtr){
	
	if((turn && strcmp(state[posRow - 1][posCol - 1],"UNO") == 0) || (!turn && strcmp(state[posRow - 1][posCol - 1], "DOS") == 0) || 
	(*turnCntPtr == 3 && strcmp(state[posRow - 1][posCol - 1], "FREE") == 0) ||
	(((!turn && strcmp(state[posRow - 1][posCol - 1], "UNO") == 0) || (turn && strcmp(state[posRow - 1][posCol - 1], "DOS") == 0)) && *turnCntPtr < 3))
		return 0;
	else
		return 1;
}

int main(){
//Variable Initialization
	String state[3][3]; //Matrix [BOARD VALUES]
	int over = 0; // Initilalizes that the game is not over
	int turn = 1; // Initializes that it is Dos's turn
	
//Turn Cardinalities
	int Uno = 0;
	int Dos = 0;
// Turn Pointer	
	int *turnCntPtr;
// Move Handler	 
	int posRow = 0;
	int posCol = 0;
	
	initBoard(state);
		
	do{
		turn = !turn; //Shifts from true or false every iteration

		if(turn)
			turnCntPtr = &Dos;
		else
			turnCntPtr = &Uno;
		
		printBoard(state);
		
		printf("\nIt is %s turn\n", turn ? "Dos's": "Uno's");
		printf("\n[%s]\n", *turnCntPtr == 3 ? "Please select a tile that you own to remove it": "Please select a free tile");
			
		do{
			do{
				printf("\nEnter row coordinate [1-3]: ");
				scanf("%d", &posRow);				
				if (!(posRow>0 && posRow<4))
					printf("\n[INVALID] Enter a valid number from 1-3!\n");
			}while(posRow <= 0 || posRow >= 4);
			do{
				printf("\nEnter column coordinate[1-3]: ");
				scanf("%d", &posCol);		
					if (!(posCol>0 && posCol<4))
				printf ("\n[INVALID]Enter a valid number from 1-3!\n");		
			}while(posCol <= 0 || posCol >= 4);
			displayError (state, turn, turnCntPtr, posRow, posCol);
		}while(!isCoordinateValid(state, posRow, posCol, turn, turnCntPtr));
	
		NextPlayerMove(state, posRow, posCol, turnCntPtr, turn);
		
		system("cls");
	    GameOver(state, &over);
		if(over)
			printBoard(state);
		
	}while(!over);
	
    return 0;
}

