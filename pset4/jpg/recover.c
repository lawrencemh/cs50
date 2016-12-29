/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from .raw file
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    // open card file
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("Could not open card.raw :(\n");
        return 2;
    }
    
    /**
     * Init variables
     */
    uint8_t buffer[512] = {0};  // buffer 512 bytes array
    int fileNo = 0;             // counter for files starting at 0
    char title[8];              // title to hold filename of next jpeg
    FILE* newJpeg = 0;          // FILE var to create/write to new JPEG

    // read until end of card is reached
    while (feof(card) == 0)
    {
        // read 512 bytes into a buffer
        // validBytes returns the valid bytes in the buffer that can be used until EOF
        // is reached
        int validBytes = fread(&buffer, 1, 512, card);
        
        // Do the first 4 bytes match the signiture of a JPEG?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // close newJpeg if is open as new JPEG marks end of previous JPEG
            if (newJpeg)
            {
                fclose(newJpeg);
            }
            
            // create new JPEG file name and open file stream with write access
            sprintf(title, "%03d.jpg", fileNo);
            newJpeg = fopen(title, "w");
            
            // increment filename for next JPEG
            fileNo += 1;
            
            // write all the bytes in buffer until validBytes is reached
            // (this avoids writing past the EOF in our new JPEG which could corrupt it)
            fwrite(&buffer, 1, validBytes, newJpeg);
        }
        else if (newJpeg)
        {
            // This block isn't a new JPEG. If newJpeg is already open, append this
            // block to newJpeg
            fwrite(&buffer, 1, validBytes, newJpeg);
        }
        
    }
    
    // close remaining jpeg if one is open
    if(newJpeg)
    {
        fclose (newJpeg);
    }
        
    // close card.raw and return 0
    fclose(card);        
    return 0;
}
