#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts string using ROT13
 * 
 * @param int numOfPlaces
 * @return int
 */
int main(int argc, string argv[])
{
    // get string to encrypt
    if (argc == 2) {
        int k = atoi(argv[1]);
        // check not negative!
        if (k < 1) {
            return 0;
        }
        
        // get string from user to encrypt
        string s = GetString();
        
        // iterate through each character in string
        for (int i = 0, shift = 0, n = strlen(s); i < n; i++) {
            // check if is alpha character
            if (isalpha(s[i])) {
                if(isupper(s[i])) {
                    shift = (((s[i] + k) - 65) % 26) + 65;
                } else {
                    shift = (((s[i] + k) - 97) % 26) + 97;
                }
                
                // print out new character
                printf("%c", shift);
            } else {
                // print out non alpha character
                printf("%c", s[i]);
            }
        }
        
        // return success
        printf("\n");
        return 0;
    } else {
        // return error as no parameter passed!
        printf("Usage: <key>\n");
        return 1;
    }
//    
}