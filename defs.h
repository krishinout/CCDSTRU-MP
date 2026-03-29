#define MAX_ROWS 3
#define MAX_COLS 3
#define MAX_ROUNDS 20

/*	This is a structure that keeps track of important data sets that are used within the game
	@param R 
	@param B
	@param S
	@param T
	@param I
	@param amtR
	@param amtB
*/
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

/*	This is a structure is utilized to access/update the informations of cells on the game board
	@param row is used
	@param col is used
*/
typedef struct
{
    int row;
    int col;
}location;


// Function Prototypes
void displayTitle();
void displayHomeScreen();
void displayInGame(int val, int freeSpaces, gameSets position);
void replace(gameSets *sets, int go, location pos);
void expand(gameSets *sets, int go, location pos);
void inputCoords(int *x, int *y);
void emptyBoard(gameSets *game);
void printBoard(gameSets *game);
void removeSet(gameSets *position, int playerTurn, location pos);
void expand(gameSets *sets, int playerTurn, location pos);
void update(gameSets *sets, location pos, int *check_charge, int playerTurn);
void nextPlayerMove(gameSets *position, int *playerTurn, int *turn_end, int *game_end, int *rounds_elapsed, int *start);
void gameOver(gameSets positions, int over, int val);
void waitForEnter();
void displayEndStats(gameSets pos, int val);

