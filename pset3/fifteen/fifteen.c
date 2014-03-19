/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    
    // begin overall count at board's max value
    int count = d * d - 1;
    
    // check if board has odd number of tiles, 
    	// set flip bool for later
    bool flip = false;
    if (count % 2 != 0)
    	flip = true;
    
    // loop through values of board array storing count
    for (int n = 0; n < d; n++) {
    	for (int i = 0; i < d; i++) {
    	board[n][i] = count;
    	count--;
    	}
    }
    // reverse 1 and 2 tiles if board has odd tiles
    if (flip) {
    	board[d - 1][d - 2] = 2;
    	board[d - 1][d - 3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop through rows, print array's contents
    printf("\n");
    for (int n = 0; n < d; n++) {
    	for (int i = 0; i < d; i++) {
    		if (board[n][i] == 0)
    			printf("  _ ");
    		else	
    			printf(" %2d ", board[n][i]);
    	}
    	printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile) {

    // check for valid input
    if (tile > d*d-1 || tile < 1) {
    	return false;
    }
    
    // declare variables
    int blank_x, blank_y, move_x, move_y;
    
    // iterate over the board and save tile coordinates as
    	// the blank and sought tiles are encountered
    for (int n = 0; n < d; n++) {
    	for (int o = 0; o < d; o++) {
    		if (board[n][o] == 0) {
    			blank_x = n;
    			blank_y = o;
    		}
    		else if(board[n][o] == tile) {
    			move_x = n;
    			move_y = o;
    		}
    	}
    }
    
    // if ((bx == mx and by == my +- 1) 
    	// OR (bx == mx +- 1 and by == my))
	if ((blank_x == move_x && (blank_y == move_y + 1 || blank_y == move_y - 1)) ||
		((blank_x == move_x + 1 || blank_x == move_x - 1) && blank_y == move_y)) {
		
		// swap move tile and blank tile, return true
		board[blank_x][blank_y] = tile;
		board[move_x][move_y] = 0;
		return true;
		}	
      
    // otherwise no move, return false
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // create a count beginning at one
    int count = 1;
    
    // iterate over board checking that values == increasing count
    for (int i = 0; i < d; i++) {
    	for(int o = 0; o < d; o++) {
    	if (board[i][o] == count)
    		count++;
    	// special case for zero tile at the end
    	else if (count == d * d && board[i][o] == 0)
    		return true; 
    	}
    }
    
    // else return false
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
