#include <cs50.h>
#include <stdio.h>

/**
 * Calculate the number of bottles a user uses
 * according to their length of shower.
 * 
 * @return int
 */
int main(void)
{
    // get length of shower from user
    printf("How many minutes do you shower for?\n");
    int minutes = GetInt();
    
    // calculate how many bottles used
    int onces = 192;
    int onces_total = onces * minutes;
    int bottles = onces_total / 16;
    
    // return result to user
    printf("minutes: %d \n", minutes);
    printf("bottles: %d \n", bottles);
}