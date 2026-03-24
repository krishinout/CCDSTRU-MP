
#define MAX_ROWS 3
#define MAX_COLS 3

typedef struct
{
    int R[MAX_ROWS][MAX_COLS];
    int B[MAX_ROWS][MAX_COLS];
    int S[MAX_ROWS][MAX_COLS];
    int T[MAX_ROWS][MAX_COLS];
    int I[MAX_ROWS][MAX_COLS]; //important during starting phase so the the other player cant chose the R/B already placed
    int amtR;
    int amtB;
} gameSets;


typedef struct
{
    int row;
    int col;
}location;


void Expand(gameSets *sets, int go, location pos);
void Replace(gameSets *sets, int go, location pos);
// necessary for recurssion




/*
--------------

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
        }
    }
    game->amtR = 0;
    game->amtB = 0;
}

--------------------------------------
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
                printf("R");
            else if (game->B[i][j] == 1)
                printf("B");
            else
                printf("_");

            if (game->S[i][j] == 1)
                printf("S");
            else
                printf("_");

            if (game->T[i][j] == 1)
                printf("T");
            else
                printf("_");

            printf(" ")

        }
        printf("|\n");
    }
    printf("  -------------------\n");
}

--------------------------BELOW HERE ARE THE OLD FUNCTIONS THEY HERE TEMP
/* This function removes the garbage values of the set (idk what u call it)
 @param s is a pointer to a set
void emptySet(struct Set *s)
{
    int i;
    int j;

    for (i = 0; i < MAX_ROWS; i++)
    {
        for (j = 0; j < MAX_COLS; j++)
        {
            s->position[i][j].contents = ' ';
            s->position[i][j].occupied = 0;
        }
    }
    s->size = 0;
}

/* This function adds a specific ball/piece (idk what u call it) to set S and T
 @param s is a pointer to a set
 @ param a and b are js the coordinates of a specific cell on the board

void addToSet(Set *s, int a, int b)
{
    s->position[a-1][b-1].occupied = 1; // indicates that it's occupied
    s->size++;
};



*/
/*
 //---variables--- (more to be added)
    int good = 0; // indicates if the players turn is done
    int go = 1; // 1 == player RED; 0 == player BLUE
    int start = 1; // indicates if the player has done or not done their first turn
    int over = 0; // indicates if the game is over
    int rounds = 1; // initially call "val" indicates how many round were elapsed
    int setF;
    //---------------

    while (!over) // the whole game??
    {
        // F = 9; at the very beggining of the round




        // F = F -(|R| +|B|) both at the very end of the round <---this and this v 
         /* if(|F| == 3 || rounds >= 20 || !start && 
                ( (|R| > 3 && |B| = 0) || (|R| == 0 && |B| > 3) ) ) wait im getting confused with this one
                over = 1;*/ //will always check this condition every end of turn/loop
