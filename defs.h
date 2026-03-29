/******************************************************************************
 *  Description     : Header file for the C-based version of the game 
 *                    Chain Reaction, containing definitions, structures, and
 *                    function prototypes.
 *  Author/s        : FABIALA, MATTHEW MIGUEL SABIO
 *                    OLVINA, LENARD MATTHEW CABANGON
 *                    SUAZON, KRISHA GEANE AQUINO
 *  Section         : S01
 ******************************************************************************/


#define MAX_ROWS 3
#define MAX_COLS 3
#define MAX_ROUNDS 20

/*	
 * Represents the important data sets that are used within the game
 */
typedef struct
{
    int R[MAX_ROWS][MAX_COLS];  // R represents cells occupied by player R
    int B[MAX_ROWS][MAX_COLS];  // B represents cells occupied by player B
    int S[MAX_ROWS][MAX_COLS];  // S represents cells in reacting state
    int T[MAX_ROWS][MAX_COLS];  // T represents cells triggered to expand
    int I[MAX_ROWS][MAX_COLS];  // Represents already selected cells during starting phase, to determine valid inputs
    int amtR;                   // The number of cells owned by player R
    int amtB;                   // The number of cells owned by player B
} gameSets;

/*	
 * Represents the (x,y) coordinates of specific cells on the board
 */
typedef struct
{
    int row; // Y coordinate of a cell on the board
    int col; // X coordinate of a cell on the board
}location;


// Function Prototypes

// Display functions
void displayTitle();
void displayHomeScreen();
void displayInGame(int val, int freeSpaces, gameSets position);
void printBoard(gameSets *game);
void displayEndStats(gameSets pos, int val);

// Main/Spec functions
void replace(gameSets *sets, int go, location pos);
void removeSet(gameSets *position, int playerTurn, location pos);
void expand(gameSets *sets, int playerTurn, location pos);
void update(gameSets *sets, location pos, int *check_charge, int playerTurn);
void nextPlayerMove(gameSets *position, int *playerTurn, int *turn_end, int *game_end, int *rounds_elapsed, int *start);
void gameOver(gameSets positions, int over, int val);

// Additional functions
void inputCoords(int *x, int *y);
void emptyBoard(gameSets *game);
void waitForEnter();