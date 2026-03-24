#include <stdlib.h>
#define MAX_ROWS 3
#define MAX_COLS 3
#define RED "\x1b[31m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#include "defs.h"

void inputCords(int *x, int *y)
{
    do
    {
        printf("Enter your X coordinate: ");
        scanf("%d",x);
    }while (*x < 1 || *x > 3);
    do
    {
        printf("Enter your Y coordinate: ");
        scanf("%d",y);
    }while (*y < 1 || *y > 3);

    (*x)--;
    (*y)--;
    
}

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


/*This function displays the board
* @param game is a pointer to the gameSets struct*/
void printBoard(gameSets *game)
{
    int i;
    int j;

    printf("     1     2     3\n");
    for (i = 0; i < 3 ; i++)
    {
        printf("  -------------------\n");
        printf("%d ", i + 1);
        for (j = 0; j < 3; j++)
        {
            printf("| ");
            if (game->R[i][j] == 1)
            {
                printf(RED "R" RESET);
                if (game->S[i][j] == 1)
                    printf(RED "S" RESET);
                else
                    printf(RED "_" RESET);

                if (game->T[i][j] == 1)
                    printf(RED "T" RESET);
                else
                    printf(RED "_" RESET);
            }
                
            else if (game->B[i][j] == 1)
            {
                printf(BLUE "B" RESET);
                if (game->S[i][j] == 1)
                    printf(BLUE "S" RESET);
                else
                    printf(BLUE "_" RESET);

                if (game->T[i][j] == 1)
                    printf(BLUE "T" RESET);
                else
                    printf(BLUE "_" RESET);
            }
            else
            {
                printf("_");
                if (game->S[i][j] == 1)
                    printf("S");
                else
                    printf("_");

                if (game->T[i][j] == 1)
                    printf("T");
                else
                    printf("_");
            }

            printf(" ");

        }
        printf("|\n");
    }
    printf("  -------------------\n\n");
}

/*This function removes a piece's position from a set
* @param position is a pointer to the gameSets struct
* @param go is an integer that represents a player's turn, 1 for R and 0 for B
* @param row is an integer that represents the row position
* @param col is an integer that represents the column position*/
void Remove(gameSets *position, int go, location pos)
{
    if(go)
    {
        position->R[pos.row][pos.col] = 0;
        position->amtR--;
    }

    else
    {
        position->B[pos.row][pos.col] = 0;
        position->amtB--;
    }

    position->S[row][col] = 0;
    position->T[row][col] = 0;
}

/* This function simulates a chain reaaction or explosion
 * @param sets is a pointer that represents the sets where specific cells will be stored
 * @param go determines a player's turn
 * @param pos is the location of the triggered cell*/
void Expand(gameSets *sets, int go, location pos) //note: still has bugs?? when i was testing
{
    location u, d, k, r;
    //--
    u.row = pos.row - 1;
    u.col = pos.col; //nakalimutan initialize yun mga col/row (prev garbage value lang sila)
    //--
    d.row = pos.row + 1;
    d.col = pos.col;
    //--
    k.row = pos.row;
    k.col = pos.col - 1;
    //--
    r.row = pos.row;
    r.col = pos.col + 1;

    remove(sets, go, pos); // removes the cell that triggered the expansion

    // this portion replaces the the selected neighboring cells + a chance of a chain reaction
    if(go==1)
        if (u.row >= 0)
            Replace(sets, go, u);
    else if(go==0)
        if (d.row < 3)
            Replace(sets, go, d);
    
    if (k.col >= 0)
        Replace(sets, go, k);
    if (r.col < 3)
        Replace(sets, go, r);
}

/*This function checks the neighboring cells after expansion and determines whether a 
 chain reaction will continue
 * @param sets is a pointer to the gameSets struct
 * @param go is a flag that determines a player's turn
 * @param pos is a struct that represents a specific cell's coordinates
  */
void Replace(gameSets *sets, int go, location pos)
{
    int found = 0; // like a flag that determines if may second explosion or expansion

    /* This portion checks what neighboring pieces are taken and sets found to 1. It checks if: 
    (1) The other player's
    (2) Their own 
    (3) A free slot */

    if(go) // player R's turn
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

    /* After a piece is found, it gets stored to S and T */
    if(found == 1)
    {
       if(sets->S[pos.row][pos.col] == 0) // If not in set S, it's added there
       {
            sets->S[pos.row][pos.col] = 1;
            found = 0; 
       }

       else if(sets->S[pos.row][pos.col] == 1 && sets->T[pos.row][pos.col] == 0) // if in set S, but in set T, another explosion/expansion will happen
       {
            sets->T[pos.row][pos.col]= 1;
            expand(&sets, go, pos);
       }  
    }
    
}

/* This function is used when a player chooses their own cell/piece
 * @param sets is a pointer that represents where specific cells will be stored
 * @param pos is a struct that represents the position of the selected cell
 * @Param good is an integer that acts as a flag that determines if if a cell was already chosen once and stored in set S
 * @param go is the flag that determines a player's turn 
 */
void Update(gameSets *sets, location pos, int *good, int go)
{
    *good = 0; // resets it

    if(sets->S[pos.row][pos.col] == 0)  // if not in set S, stores it and action is validated
    {
        sets->S[pos.row][pos.col] = 1;
        *good = 1;
    }

    else if(*good == 0 && sets->S[pos.row][pos.col] == 1 && sets->T[pos.row][pos.col] == 0) // if in S but not in T
    {
        sets->T[pos.row][pos.col] = 1; // adds to set S and cell reacts, possible chain reaction
        Expand(sets, go, pos);
    }
}

/*This function determines the players' movement on the board
    * @param position is a pointer to the gameSets struct
    * @param go is a pointer that represents the player's turn, 1 for R and 0 for B
    * @param good is a pointer that represents if the player's turn is done
    * @param over is a pointer that represents if the game is over or not
    * @param val is a pointer that represent how many rounds had elapsed
    * @param start is a pointer that indicates if both players had done their first turn
    * @param row is an integer that represent the row position
    * @param col is an integer that represent the column position*/
void nextPlayerMove(gameSets *position, int *go, int *good, int *over, int *val, int *start)
{
    int valid = 0;
    int x;
    int y;
    location input;


    if (*over == 0 && *start == 1 && *go == 1) // Player R's first turn
    {
        printf("Player R it's your move\n\n");
        while(!valid)
        {
            inputCords(&x,&y);
            if (position->I[x][y] == 0)
            {
                position->I[x][y] = 1;
                position->R[x][y] = 1;
                position->amtR++;
                position->S[x][y] = 1;
                *good = 1;
                valid = 1;  
            }
            else
                printf("\nPosistion is already taken\n\n");
        }
    }
    else if (*over == 0 && *start == 1 && *go == 0) // Player B's first turn
    {
        printf("Player B it's your move\n\n");
        while(!valid)
        {


            inputCords(&x,&y);
            if (position->I[x][y] == 0)
            {
                position->I[x][y] = 1;
                position->B[x][y] = 1;
                position->amtB++;
                position->S[x][y] = 1;
                *good = 1;
                valid = 1;
            }
            else
                printf("\nPosistion is already taken\n\n");
        }
    }
    //------------------------------------------------------------------------//
    if (*over == 0 && *start == 0 && *go == 1 )
    {
        printf("Player R it's your move\n\n");
            while(!valid)
            {
                inputCords(&x,&y);
                if (position->R[x][y] == 1)
                    valid = 1;
                else
                    printf("\nPosistion invalid\n\n");
            }
            input.row = x;
            input.col = y;
            Update(position,input,good,*go);
            printf("Hey you chose your taken spot Player R\n");
            *good = 1;
    }
    else if (*over == 0 && *start == 0 && *go == 0 )
    {
        printf("Player B it's your move\n\n");
        while(!valid)
        {
            inputCords(&x,&y);
            if (position->B[x][y] == 1)
                valid = 1;
            else
                printf("\nPosistion invalid\n\n");
        }
        input.row = x;
        input.col = y;
        Update(position,input,good,*go);
        printf("Hey you chose your taken spot Player B\n");
        *good = 1;
    }
    //------------------------------------------------------------------------//
    if (*start == 1 && position->amtR == 1 && position->amtB == 1) // if both player already took their first turn
            *start = 0;
    //------------------------------------------------------------------------//
    if (*over == 0 && *good == 1) //if the player is done with their move
        {
            *good = !(*good);
            *go = !(*go);
            (*val)++;
        }


}
