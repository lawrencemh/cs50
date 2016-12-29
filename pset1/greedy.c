#include <cs50.h>
#include <stdio.h>

/**
 * Calculate min number of coins that are required to give
 * customer change.
 * 
 * @return int
 */
int main(void)
{
    // get change due from user
    float changef = 0;
    
    do {
        printf("How much change is due? e.g. $ 0.84\n");
        changef = GetFloat();
    } while ( !(changef > 0) );
    
    // Initiate change_due and coins variables
    int change_due = changef * 1000;
    int coins = 0;

    // Return max quaters (25¢)
    coins = coins + (change_due / 250);
    change_due = (change_due % 250);

    // Return max dimes (10¢)
    coins = coins + (change_due / 100);
    change_due = (change_due % 100);

    // Return max nickels (5¢)
    coins = coins + (change_due / 50);
    change_due = (change_due % 50);

    // Return max pennies (1¢)
    coins = coins + (change_due / 10);
    change_due = (change_due % 10);

    // return coin count to user    
    printf("%d\n", coins);
}