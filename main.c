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
   
    iClear(0, 0, 100, 60);
    emptyBoard(&position);
    displayHomeScreen();

    //loop
    while (!game_end)
    {
        freeSpaces = 9;
        freeSpaces = freeSpaces - (position.amtR + position.amtB);

        if(freeSpaces == 3 || rounds_elapsed >= 20 || (!start && ((position.amtR > 0 && position.amtB == 0) || (position.amtR == 0 && position.amtB > 0))))
            game_end = 1;
        
        if (!game_end)
        {
                // waitForEnter();
            iClear(0, 0, 100, 60);

            displayTitle();

            // display lang for rounds, max rounds, and open spaces
            displayInGame(rounds_elapsed, freeSpaces, position);

            iSetColor(I_COLOR_WHITE);
            printBoard(&position);

            nextPlayerMove(&position, &playerTurn, &turn_end, &game_end, &rounds_elapsed, &start);

        }
    }

    iClear(0, 0, 100, 60);
    gameOver(position,game_end, rounds_elapsed);


    return 0;
}
