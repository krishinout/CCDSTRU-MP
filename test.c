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

        // waitForEnter();
        iClear(0, 0, 100, 60);

       iSetColor(I_COLOR_WHITE);
        printf("============================================================\n");
      //  iSetColor(I_COLOR_YELLOW);
        printf("\t\tC H A I N  R E A C T I O N\n");
       // iSetColor(I_COLOR_CYAN);
        printf("============================================================\n\n");

        // display lang for rounds, max rounds, and open spaces
        iSetColor(I_COLOR_WHITE);
        printf("  ROUND ");
        iSetColor(I_COLOR_YELLOW);
        printf("%02d", rounds_elapsed);
        iSetColor(I_COLOR_WHITE);
        printf(" / %d", MAX_ROUNDS);

        iSetColor(I_COLOR_WHITE);
        printf("\t\tFREE SPACE : ");
        iSetColor(I_COLOR_YELLOW);
        printf("%d\n\n", freeSpaces);

        iSetColor(I_COLOR_WHITE);
        printf("------------------------------------------------------------\n\n");

        // for player stats naman
        iSetColor(I_COLOR_RED);
        printf("  Player R: [ %d pieces ]\n\n", position.amtR);
        iSetColor(I_COLOR_BLUE);
        printf("  Player B: [ %d pieces ]\n\n", position.amtB);

        iSetColor(I_COLOR_WHITE);
        printf("------------------------------------------------------------\n\n");

        iSetColor(I_COLOR_WHITE);
        printBoard(&position);

        nextPlayerMove(&position, &playerTurn, &turn_end, &game_end, &rounds_elapsed, &start);


        if(freeSpaces == 3 || rounds_elapsed >= 20 || (!start && ((position.amtR > 0 && position.amtB == 0) || (position.amtR == 0 && position.amtB > 0))))
            game_end = 1;

    }

    iClear(0, 0, 100, 60);
    gameOver(position,game_end, rounds_elapsed);


    return 0;
}
