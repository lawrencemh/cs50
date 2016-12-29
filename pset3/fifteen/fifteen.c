/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
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

// _ location [0] is y position [1] is x position
int loc_[2];

// init tile search
int tile_y = 0;
int tile_x = 0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void set_(int y, int x);
int get_y();
int get_x();
bool getTile(int tile);

/**
 * Game of fifteen
 * 
 * @param int d
 */
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
    FILE* file = fopen("log.txt", "w");
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
        int tile = GetInt();
        
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
            usleep(500);
        }

        // sleep thread for animation's sake
        usleep(500);
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
 * board[row][column]
 */
void init(void)
{
    // For each row as y
    for (int i = d*d - 1, max_size = d*d -1 , y = 0; y < d; y++)
    {
        // for each col as x
        for (int x = 0; x < d; x++, i--)
        {
            board[y][x] = i;
            
            // check if max_size is odd
            if( (max_size % 2) != 0)
            {
                if (i == 2)
                {
                    // override to 1 from 2
                    board[y][x] = 1;
                }
                
                // check if max_size is odd & i is 2
                if (i == 1)
                {
                    // override to 2 from 1
                    board[y][x] = 2;
                }
            }
            
            
            // check if i is 0 i.e. _
            if (i == 0)
            {
                set_(y, x);
            }
        }
        
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // For each row as y
    for (int i = 0, y = 0; y < d; y++)
    {
        // for each col as x
        for (int x = 0; x < d; x++, i++)
        {
            if (!board[y][x] == 0)
            {
                printf(" %2d ", board[y][x]);
            }
            else
            {
                printf("  _ ");
            }
            
        }
        printf("\n\n");
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // get _ position
    int _x = get_x();
    int _y = get_y();
    
    
    // find file or return false
    if (getTile(tile) == false)
    {
        return false;
    }
    
    // validate tile position
    bool valid = false;
    // check if right or left of _
    if (tile_y == _y && ( tile_x == _x -1 || tile_x == _x +1 ))
    {
        valid = true;
    }
    // check if top or bottom of _x
    else if (tile_x == _x && ( tile_y == _y -1 || tile_y == _y +1 ))
    {
        valid = true;
    }
    
    if (valid == false)
    {
        // tile not valid to move
        return false;
    }
    
    // do move
    board[tile_y][tile_x] = board[_y][_x];
    board[_y][_x] = tile;
    set_(tile_y, tile_x);
    
    return true;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // loop through board and check if it increments to d*d starting from 1 tp d*d
    // For each row as y
    for (int i = 1, max = d*d - 1, y = 0; y < d && i <= max; y++)
    {
        // for each col as x
        for (int x = 0; x < d && i <= max; x++, i++)
        {
            if(!(board[y][x] == i))
            {
                return false;
            }
        }
        
    }
    
    return true;
}

/**
* Set position of _
*/
void set_(int y, int x)
{
loc_[0] = y;
 loc_[1] = x;
}
 
/**
* Get position of _ y
*/
int get_y()
{
  return loc_[0];
}

/**
* Get position of _ x
*/
int get_x()
{
  return loc_[1];
}

/**
 * Get tile's location
 */
 bool getTile(int tile)
 {
     // For each row as y
    for (int i = d*d - 1, y = 0; y < d; y++)
    {
        // for each col as x
        for (int x = 0; x < d; x++, i--)
        {
            /// check if tile = tile to find
            if(board[y][x] == tile) {
                tile_y = y;
                tile_x = x;
                return true;
            }
            
            // check if i is 0 i.e. _
            if (i == 0)
            {
                set_(y, x);
            }
        }
        
    }
    
    // not found return false
    return false;
 }