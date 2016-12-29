#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts string using Vigenere
 * 
 * @param string x
 * @return int
 */
int main(int argc, string argv[])
{
    // get encryption string
    if (argc == 2) {
        string p = (argv[1]);

        // check key is alpha!
        for (int i = 0, pLen = strlen(p); i < pLen; i++) {
            if (!isalpha(p[i])) {
                // return error as key contains non-alpha characters
                printf("Usage: <key>\n");
                return 1;
            }
        }
        
        // get string from user to encrypt
        string k = GetString();
        
        // iterate through each character in string and key
        for (int i = 0, j = 0, pLen = strlen(p) - 1, kLen = strlen(k), shiftBy = 0, shift = 0; j < kLen; j++) {
            // calculate how many char to shift using key
            if (isupper(p[i])) {
                shiftBy = (p[i]- 65); 
                //printf("%c:%i", p[i],shiftBy );
            } else {
                shiftBy = (p[i]- 97);
                //printf("%c:%i", p[i],shiftBy );
            }
            
            // check if character is alpha character
            if (isalpha(k[j])) {
                if (isupper(k[j])) {
                    shift = (((k[j] + shiftBy) - 65) % 26) + 65;
                } else {
                    shift = (((k[j] + shiftBy) - 97) % 26) + 97;
                }
                
                // print encrypted character
                printf("%c", shift);
                
                // check if i is at pLen (i.e. looped through each char in key)
                if (i < pLen) {
                    i++;
                } else {
                    i = 0;
                }
                
                
            } else {
                // non alpha char. print without processing
                printf("%c", k[j]);
            }
        //
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