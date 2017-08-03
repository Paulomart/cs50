/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
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
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int x;
    int y;
    int c = d * d - 1;
    for (x = 0; x < d; x++) {
        for (y = 0; y < d; y++) {
            board[x][y] = c;
            
            // if the board is even we need to swap 2 and 1
            if (d % 2 == 0) {
                if (c == 2) {
                    board[x][y] = 1;
                } else if (c == 1) {
                    board[x][y] = 2;
                }
            }
            c--;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    int x;
    int y;
    int n;
    for (x = 0; x < d; x++) {
        for (y = 0; y < d; y++) {
            n = board[x][y];
            if (n > 0) {
                if (n < 10) {
                    printf(" ");
                }
               printf("%i ", n);
            } else {
                printf("__ ");
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    if ((d * d) - 1 < tile || tile < 0) {
        return false;
    }
    
    int tileX, tileY, x, y;
    for (x = 0; x < d; x++) {
        for (y = 0; y < d; y++) {
            if (board[x][y] == tile) {
                tileX = x;
                tileY = y;
                break;
            }
        }
    }
    
    // search for empty
    int emptyX, emptyY;
    for (x = 0; x < d; x++) {
        for (y = 0; y < d; y++) {
            if (board[x][y] == 0) {
                emptyX = x;
                emptyY = y;
                break;
            }
        }
    }
    
    // a valid move is when the sum of the
    // difference between the two tiles
    // is equal to 1
    int modX = abs(emptyX - tileX);
    int modY = abs(emptyY - tileY);

    if (modX + modY != 1) {
        return false;
    }
    
    // swap
    board[emptyX][emptyY] = tile;
    board[tileX][tileY] = 0;
    
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int x;
    int y;
    int c = 1;
    for (x = 0; x < d; x++) {
        for (y = 0; y < d; y++) {
           
            if (board[x][y] != c) {
                return false;
            }
            c++;
            if (c >= d * d) {
                break;
            }
        }
    }
    return true;
}
