#include <cs50.h>
#include <stdio.h>

/**
 * Generate a right-aligned pyramid according to 
 * user's required height.
 * 
 * @return int
 */
int main(void)
{
    // get height of pyramid from user
    int height;
    do {
        printf("height?\n");
        height = GetInt();
    } while (!(height >= 0 && height <= 23));
    
    // initiate spaces and has variables
    int spaces = height;
    int hash = 1;
    
    // loop through each pyramid row
    for (int i = 0; i < height; i++) {
        // increment
        spaces--;
        hash++;
        
        // print spaces
        for (int s = 1; s <= spaces; s++) {
            printf(" ");
        }
        
        // print hashes
        for (int h = 1; h <= hash; h++) {
            printf("#");
        }
        
        // print new line
        printf("\n");
    }
    
}