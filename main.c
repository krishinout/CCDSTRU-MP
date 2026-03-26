 
#include <stdio.h>
#include <string.h>
#include "helper.c"


int main()
{
    int playerTurn = 1;
    int turn_end = 0;
    int game_end = 0;
    int rounds_elapsed = 0;
    int start = 1;
    int x;
    int y;
    gameSets position;
    
    emptyBoard(&position);

	printf("Current Board\n\n");
    printBoard(&position);

    inputCoords(&x,&y);

    nextPlayerMove(&position, &playerTurn, &turn_end, &game_end, &rounds_elapsed, &start);
    
    printf("Current Board\n\n");
	printBoard(&position);
	
	inputCoords(&x,&y);

    nextPlayerMove(&position, &playerTurn, &turn_end, &game_end, &rounds_elapsed, &start);
    
    printf("Current Board\n\n");
	printBoard(&position);
	
	printf("\n\n");
	
	printf("playerTurn : %d | turn_end : %d | game_end : %d | rounds_elapsed : %d | start : %d", playerTurn, turn_end, game_end, rounds_elapsed, start);
    
//currently after the start section palang

    return 0;
}
