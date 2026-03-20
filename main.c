 
#include <stdio.h>
#include <string.h>
#include "helper.c"


int main()
{
    int go = 1;
    int good = 0;
    int over = 0;
    int val = 0;
    int start = 1;
    int x;
    int y;
    gameSets position;
    
    emptyBoard(&position);

	printf("Current Board\n\n");
    printBoard(&position);

    inputCords(&x,&y);

    nextPlayerMove(&position, &go, &good, &over, &val, &start, x, y);
    
    printf("Current Board\n\n");
	printBoard(&position);
	
	inputCords(&x,&y);

    nextPlayerMove(&position, &go, &good, &over, &val, &start, x, y);
    
    printf("Current Board\n\n");
	printBoard(&position);
	
	printf("\n\n");
	
	printf("go : %d | good : %d | over : %d | val : %d | start : %d", go, good, over, val, start);
    
//currently after the start section palang

    return 0;
}