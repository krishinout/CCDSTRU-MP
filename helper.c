#include <stdio.h>
#include <stdlib.h>
#define MAX_ROWS 3
#define MAX_COLS 3
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#include "defs.h"
#include "interface.c"

void displayHomeScreen()
{
    displayTitle();

    printf("\n\n\t\t\t     LEGEND\n");
    printf("\t\t--------------------------------\n");
    iSetColor(I_COLOR_RED);
    printf("\t\t  R");
    iSetColor(I_COLOR_WHITE);
    printf(" = PLAYER 1\n");

    iSetColor(I_COLOR_BLUE);
    printf("\t\t  B");
    iSetColor(I_COLOR_WHITE);
    printf(" = PLAYER 2\n");

    iSetColor(I_COLOR_YELLOW);
    printf("\t\t  +");
    iSetColor(I_COLOR_WHITE);
    printf(" = piece is reacting...\n");

    iSetColor(I_COLOR_YELLOW);
    printf("\t\t  !");
    iSetColor(I_COLOR_WHITE);
    printf(" = piece is exploding!\n");
    printf("\t\t--------------------------------\n\n\n");

    waitForEnter(1);

}

void displayTitle()
{
    iSetColor(I_COLOR_WHITE);
    printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    iSetColor(I_COLOR_YELLOW);
    printf("  _______ _____   _____  __  ___  _______  ___________________  _  __\n");
    printf(" / ___/ // / _ | /  _/ |/ / / _ \\/ __/ _ |/ ___/_  __/  _/ __ \\/ |/ /\n");
    printf("/ /__/ _  / __ |_/ //    / / , _/ _// __ / /__  / / _/ // /_/ /    / \n");
    printf("\\___/_//_/_/ |_/___/_/|_/ /_/|_/___/_/ |_\\___/ /_/ /___/\\____/_/|_/\n\n\n");
    iSetColor(I_COLOR_WHITE);
    printf("  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");

}

/*  This is a void function that asks the player where they would like to place their "charge"
    @param x is the left to right (horizonal) coordinates on the game board plane
    @param y is the up and down (vertical) coordinates on the game board plane
*/
void inputCoords(int *x, int *y)
{
    char input, extra;

    do
    {
        // scans it as a char first to avoid infinite loops
        iSetColor(I_COLOR_CYAN);
        printf("Enter X: ");
        scanf(" %c%c", &input, &extra);

        if(extra != '\n' || input < '1' || input > '3') {
            iSetColor(I_COLOR_RED);
            printf("Invalid Input, Please Press Enter And Try Again.\n");
            scanf("%*[^\n]");
            input = '0';
        }
    }while(input < '1' || input > '3');

    // once a valid input is entered, it's converted to its integer equivalent
    if(input == '1') {
        *x = 0;
    }
    else if(input == '2') {
        *x = 1;
    }
    else if(input == '3') {
        *x = 2;
    }


    do
    {
        iSetColor(I_COLOR_CYAN);
        printf("Enter Y: "); 
        scanf(" %c%c", &input, &extra);

       if(extra != '\n' || input < '1' || input > '3') {
            iSetColor(I_COLOR_RED);
            printf("Invalid Input, Please Press Enter And Try Again.\n");
            scanf("%*[^\n]");
            input = '0';
        }
    }while(input < '1' || input > '3');

    if(input == '1') {
        *y = 0;
    }
    else if(input == '2') {
        *y = 1;
    }
    else if(input == '3') {
        *y = 2;
    }

}


/*  This is a void function that is used to empty/reset the game board
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @param game is a pointer that sends ___ data to the gameSets structure
*/
void emptyBoard(gameSets *game)
{
    int i;
    int j;


    for (i = 0; i < MAX_ROWS; i++)
    {
        for (j = 0; j < MAX_COLS; j++)
        {
            game->R[i][j] = 0;
            game->B[i][j] = 0;
            game->S[i][j] = 0;
            game->T[i][j] = 0;
            game->I[i][j] = 0;
        }
    }
    game->amtR = 0;
    game->amtB = 0;
}




/*  This function gives a visual display of the game board for the player(s)
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @param game is a pointer that sends ___ data to the gameSets structure
*/
void printBoard(gameSets *game)
{
    int i, j, inSetS;
    char indicator;
    // column label
    iSetColor(I_COLOR_YELLOW);
    printf("          1           2           3\n");
    printf("    +===========+===========+===========+\n");

    for(i=0; i<3; i++)
    {
        printf("    |           |           |           |\n");
        printf("    |           |           |           |\n");
        printf("  %d |", i+1);

        for(j=0; j<3; j++)
        {
           // represents what set it's in, + for set S, ! for set T
            inSetS = game->S[i][j] + game->T[i][j];
            if(inSetS == 0)
                indicator = ' ';
            else if(inSetS == 1)
                indicator = '+';
            else
                indicator = '!';
            
            printf("    "); // the gaps sa table

            // for when placing the actual piece + their indicator
            if(game->R[i][j] == 1)
            {
                iSetColor(I_COLOR_RED);
                printf("R %c", indicator);
                iSetColor(I_COLOR_YELLOW);
            }
            else if(game->B[i][j] == 1)
            {
                iSetColor(I_COLOR_BLUE);
                printf("B %c", indicator);
                iSetColor(I_COLOR_YELLOW); // sets back to yellow because of the table
            }
            else
            {
                iSetColor(I_COLOR_WHITE);
                printf("___");
                iSetColor(I_COLOR_YELLOW);
            }

            printf("    |");
        }
         printf("\n");
         printf("    |           |           |           |\n");
         printf("    |           |           |           |\n");
         printf("    +===========+===========+===========+\n");
    }
        iSetColor(I_COLOR_WHITE); // so colors go back to usual after the table unless changed
       // printf("\n------------------------------------------------------------\n");
     //   printf("  R = no reaction  R + = reacting...  R ! = exploding!");
     //   printf("\n------------------------------------------------------------\n\n");
}

/* This function displays the player indicator
* @param turn is a char that represents a player's turn
*/
void displayTurn(char turn)
{
    iSetColor(I_COLOR_YELLOW);

     iSetColor(I_COLOR_WHITE);
    printf("\n\n  >>> ");

    if (turn == 'R'){
        iSetColor(I_COLOR_RED);
        printf("PLAYER R");
    }

    else {
        iSetColor(I_COLOR_BLUE);
        printf("PLAYER B");
    }

    iSetColor(I_COLOR_WHITE);
    printf(" IT'S YOUR MOVE <<<\n\n\n");
    //printf("\n------------------------------------------------------------\n\n");
}

/**/
void displayExpand(int turn, int row, int column)
{
    char player;

    iSetColor(I_COLOR_RED);
    printf(" \n !! BOOM !! ");
    iSetColor(I_COLOR_WHITE);
    
    if(turn == 1)
        player = 'R';
    else
        player = 'B';

    printf("PLAYER %c TRIGGERED AN EXPLOSION AT (%d, %d)\n", player, column+1, row+1);

    waitForEnter(0);
}

/*  This function removes a piece/charge's position from a set
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @struct location tracks the location of the current cell  
    @param position is a pointer that sends position data to the gameSets struct
    @param playerTurn is an integer that represents the player's turn, 1 for R and 0 for B
    @param pos sends data of the current position coordinates to the location struct
    @param row is an integer that represents the row position
    @param col is an integer that represents the column position
*/
void removeSet(gameSets *position, int playerTurn, location pos) //0-------------------------------------------------------------------------------0
{
    //int row, col;
   
    if(playerTurn == 1)
    {
        if(position->R[pos.row][pos.col] == 1) // just a safety net and doesn't immediately dencrement
        {
            position->R[pos.row][pos.col] = 0;
            position->amtR--;
        }
        
    }
    else
    {
        if(position->B[pos.row][pos.col] == 1) // just a safety net and doesn't immediately dencrement
        {
           position->B[pos.row][pos.col] = 0;
            position->amtB--; 
        }
    }

    position->S[pos.row][pos.col] = 0;
    position->T[pos.row][pos.col] = 0;

}


/*  This function simulates a chain reaction or explosion when the cell reaches the maximum limit of "charges" stored
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @struct location tracks the location of the current cell
    @param sets is a pointer that represents the sets where specific cells will be stored
    @param playerTurn is an integer that represents the player's turn, 1 for R and 0 for B
    @param pos sends data of the current position coordinates to the location struct
*/
void expand(gameSets *sets, int playerTurn, location pos) //0-------------------------------------------------------------------------------0
{
    location u, d, k, r;    // u = up, d = down, k = left, r = right
    //--
    u.row = pos.row - 1;
    u.col = pos.col;        
    //--
    d.row = pos.row + 1;
    d.col = pos.col;
    //--
    k.row = pos.row;
    k.col = pos.col - 1;
    //--
    r.row = pos.row;
    r.col = pos.col + 1;


    removeSet(sets, playerTurn, pos);    // clears the cell that triggered the expansion

    // this portion replaces the the selected neighboring cells + a chance of a chain reaction
    if(playerTurn==1) //if your player R you can split UPWARDS, LEFT, AND RIGHT
    {
        if (u.row >= 0)
            replace(sets, playerTurn, u);
    }
    else if(playerTurn==0) //if your player B you can split DOWNWARD, LEFT, RIGHT
    {
        if (d.row < 3)
            replace(sets, playerTurn, d);
    }
         
    if (k.col >= 0)
        replace(sets, playerTurn, k);
    if (r.col < 3)
        replace(sets, playerTurn, r);
    
    printBoard(sets);
    displayExpand(playerTurn, pos.row, pos.col);
}


/*  This function checks the neighboring cells after expansion and determines whether a chain reaction will continue
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @struct location tracks the location of the current cell
    @param sets is a pointer that sends ___ data to the gameSets structure
    @param playerTurn is an integer that represents the player's turn, 1 for R and 0 for B
    @param pos sends data of the current position coordinates to the location struct
*/
void replace(gameSets *sets, int playerTurn, location pos) //0-------------------------------------------------------------------------------0
{
    int found = 0; // like a flag that determines if there will be a second explosion or expansion


/*  This portion checks what neighboring pieces are taken and sets found to 1. It checks if:
    (1) The other player's
    (2) Their own
    (3) A free slot
*/
    if(playerTurn == 1) // player R's turn
    {
        if(sets->B[pos.row][pos.col] == 1) // if in set B, remove and found = 1
        {
            sets->B[pos.row][pos.col] = 0;
            sets->amtB--;
            found = 1;
        }
        else if(sets->R[pos.row][pos.col] == 1) // if in set R, found = 1
            found = 1;
       
        else if(sets->R[pos.row][pos.col] == 0) // not in set R, add to set R
        {
            sets->R[pos.row][pos.col] = 1;
            sets->amtR++;
        }
    }


    else // player B's turn
    {
        if(sets->R[pos.row][pos.col] == 1) // if in set R, remove and found = 1
        {
            sets->R[pos.row][pos.col] = 0;
            sets->amtR--;
            found = 1;
        }

        else if(sets->B[pos.row][pos.col] == 1) // if in set B, found = 1
            found = 1;
       
        else if(sets->B[pos.row][pos.col] == 0) // if not in set B, add to set B
        {
            sets->B[pos.row][pos.col] = 1;
            sets->amtB++;
        }
    }


    // After a piece is found, it gets stored to S and T
    if (found && sets->S[pos.row][pos.col] == 0) //changed
    {
        sets->S[pos.row][pos.col] = 1;
        found = 0;
    }
    else if (found && sets->S[pos.row][pos.col] == 1 && sets->T[pos.row][pos.col] == 0) //changed
    {
        sets->T[pos.row][pos.col]= 1;
        expand(sets, playerTurn, pos);
    }
 

}


/*  This function is used when a player chooses their own cell/piece
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @struct location represents the location of the current cell
    @param sets is a pointer that represents where specific cells will be stored
    @param check_charge is an integer that acts as a flag that determines if if a cell was already chosen once and stored in set S
    @param playerTurn is an integer that represents the player's turn, 1 for R and 0 for B
    @param pos sends data of the current position coordinates to the location struct
 */
void update(gameSets *sets, location pos, int *check_charge, int playerTurn) //0-------------------------------------------------------------------------------0
{
    *check_charge = 0;                  // initializes the current "charge level"


    if(sets->S[pos.row][pos.col] == 0)  // if not in set S, stores it and action is validated
    {
        sets->S[pos.row][pos.col] = 1;
        *check_charge = !*(check_charge);
    }

    else if(*check_charge == 0 && sets->S[pos.row][pos.col] == 1 && sets->T[pos.row][pos.col] == 0) // if in S but not in T
    {
        sets->T[pos.row][pos.col] = 1; // adds to set S and cell reacts, possible chain reaction
        expand(sets, playerTurn, pos);
    }
}


/*  This function determines if it's either Player R or Player B's turn
    @struct gameSets tracks which player is occupying certain cells and the current "charge states" of a cell to see if the cell will "explode" or "overflow"
    @param position is a pointer that sends ___ data to the gameSets struct
    @param playerTurn is an integer that represents the player's turn, 1 for R and 0 for B
    @param turn_end is a pointer that represents if the current player's turn is over
    @param game_end is a pointer that represents if the game is over or not
    @param rounds_elapsed is a pointer that represents how many rounds have happened throughout the game
    @param start is a pointer that indicates if both players have already done their first turn
    @param row is an integer that represent the row position
    @param col is an integer that represent the column position
*/
void nextPlayerMove(gameSets *position, int *playerTurn, int *turn_end, int *game_end, int *rounds_elapsed, int *start)
{
    int valid = 0;
    int x;
    int y;
    location input;

   // STARTING PHASE 
    if (*game_end == 0 && *start == 1 && *playerTurn == 1) // Player R's first turn
    {
       // printf("Player R it's your move\n\n"); //BIG NOTE [row] == Y [col] == X ==>[row][col] == [y][x]
       displayTurn('R');

       iSetColor(I_COLOR_WHITE);
        while(!valid)
        {
            inputCoords(&x,&y);
            if (position->I[y][x] == 0)
            {
                position->I[y][x] = 1;
                position->R[y][x] = 1;
                position->amtR++;
                position->S[y][x]= 1;
                *turn_end = 1;
                valid = 1;  
            }
            else {
                iSetColor(I_COLOR_RED);
                printf("\nInvalid move, cell is already occupied!\n\n");
                iSetColor(I_COLOR_WHITE);
            }
        }
    }
    else if (*game_end == 0 && *start == 1 && *playerTurn == 0) // Player B's first turn
    {
        // printf("Player B it's your move\n\n");
        displayTurn('B');

       iSetColor(I_COLOR_WHITE);
        while(!valid)
        {
            inputCoords(&x,&y);
            if (position->I[y][x] == 0)
            {
                position->I[y][x] = 1;
                position->B[y][x] = 1;
                position->amtB++;
                position->S[y][x] = 1;
                *turn_end = 1;
                valid = 1;
            }
            else {
                iSetColor(I_COLOR_RED);
                printf("\nInvalid move, cell is already occupied!\n\n");
                iSetColor(I_COLOR_WHITE);
            }
        }
    }
    //------------------------------------------------------------------------//
    // BATTLE/IN-GAME PHASE
    if (*game_end == 0 && *start == 0 && *playerTurn == 1 )
    {
        displayTurn('R');

            while(!valid)
            {
                inputCoords(&x,&y);
                if (position->R[y][x] == 1)
                    valid = 1;
                else {
                    iSetColor(I_COLOR_RED);
                    printf("\nNo piece there! Choose one of your own cells.\n\n"); // shows if player R chooses player B's cell or anything random
                    iSetColor(I_COLOR_WHITE);
                }
            }
            input.row = y;
            input.col = x;
            update(position, input, turn_end, *playerTurn);
            *turn_end = 1;
    }
    else if (*game_end == 0 && *start == 0 && *playerTurn == 0 )
    {
        displayTurn('B');

            while(!valid)
            {
                inputCoords(&x,&y);
                if (position->B[y][x] == 1)
                    valid = 1;
                else {
                    iSetColor(I_COLOR_RED);
                    printf("\nNo piece there! Choose one of your own cells.\n\n"); // shows if player R chooses player B's cell or anything random
                    iSetColor(I_COLOR_WHITE);
                }
            }
            input.row = y;
            input.col = x;
            update(position, input, turn_end, *playerTurn);
            *turn_end = 1;
    }
    //------------------------------------------------------------------------//
    if (*start == 1 && position->amtR == 1 && position->amtB == 1) // if both player already took their first turn
            *start = 0;
    //------------------------------------------------------------------------//
    if (*game_end == 0 && *turn_end == 1) //if the player is done with their move
        {
            *turn_end = !(*turn_end);
            *playerTurn = !(*playerTurn);
            (*rounds_elapsed)++;
        }


}

void gameOver(gameSets positions, int game_end, int val)
{
    // 1 for red, 2 for blue, 0 for tie

    iSetColor(I_COLOR_RED);
    printf("\tGAME OVER\n\n");

    if (game_end && positions.amtR > positions.amtB) {
        printf(" >> PLAYER R <<  ");
        iSetColor(I_COLOR_WHITE);
        printf("WINS!\n\n");
    }
    else if (game_end && positions.amtR < positions.amtB) {
        iSetColor(I_COLOR_BLUE);
        printf(" >> PLAYER B <<  ");
        iSetColor(I_COLOR_WHITE);
        printf("WINS!\n\n");
    }
        
    else if (game_end && positions.amtR == positions.amtB) {
        printf("IT'S A DRAW!\n\n");
    }

    displayEndStats(positions, val);
       
}

void displayEndStats(gameSets pos, int val)
{
    iSetColor(I_COLOR_WHITE);
    printf("FINAL SCORE\n\n");
    printf("-----------------------------\n\n");
      iSetColor(I_COLOR_RED);
    printf("PLAYER R : %02d\n", pos.amtR);
    iSetColor(I_COLOR_BLUE);
    printf("PLAYER B : %02d\n\n", pos.amtB);
    iSetColor(I_COLOR_WHITE);
    printf("-----------------------------\n\n");
    iSetColor(I_COLOR_WHITE);
    printf("ROUNDS PLAYED :");
    iSetColor(I_COLOR_YELLOW);
    printf(" %02d\n\n\n", val);

    waitForEnter(2);
}

void waitForEnter(int spacing)
{
    char c;
    if(spacing == 0)
        printf("\nPress Enter To Continue...");
    else if(spacing == 1) {
        iSetColor(I_COLOR_GREEN);
        printf("\t\t> > > PRESS ENTER TO START < < <");
        iSetColor(I_COLOR_WHITE);
    }
    else if(spacing == 2)
        printf("\t\tPress Enter To Exit...");

    c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}
