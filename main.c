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
    int freeSpaces;
    gameSets position;
   
    emptyBoard(&position);


    //loop
    while (!game_end)
    {
        freeSpaces = 9;
        freeSpaces = freeSpaces - (position.amtR + position.amtB);

        printf("Current Board\n\n");
        printBoard(&position);

        printf("\nplayerTurn : %d | turn_end : %d | game_end : %d \n", playerTurn, turn_end, game_end); //note: this for testing and debuggin
        printf("rounds_elapsed : %d | start : %d | freeSpaces : %d \n\n", rounds_elapsed, start, freeSpaces); // we can edit this to improve the U.I

        nextPlayerMove(&position, &playerTurn, &turn_end, &game_end, &rounds_elapsed, &start);


        if(freeSpaces == 3 || rounds_elapsed >= 20 || (!start && ((position.amtR > 0 && position.amtB == 0) || (position.amtR == 0 && position.amtB > 0))))
            game_end = 1;

    }

    gameOver(position,game_end);


    return 0;
}
