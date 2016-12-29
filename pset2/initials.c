#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Print user's initials to screen
 * 
 * @return int
 */
int main(void)
{
    // Get user's name
    string fName = GetString();
    
    // Loop through each letter in fName
    for (int i = 0, n = strlen(fName), lastBlank = 0; i < n; i++) {
        // if lastBlank is true print character or first iteration
        if (lastBlank == 1 || i == 0) {
            // check if char is lower and convert, else print character
            if ( islower(fName[i])) {
                printf("%c", toupper(fName[i])); 
            } else {
                printf("%c", fName[i]); 
            }
        }
        
        
        // check if current char is empty and set lastBlank for next iteration
        if (fName[i] == ' ') {
            // set lastBlank to true
            lastBlank = 1;
        } else {
            // last blank is false
            lastBlank = 0;  
        }

        
    }
    
    // print new line
    printf("\n");
}