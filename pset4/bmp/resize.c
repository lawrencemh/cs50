/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bmp based on n.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

/**
 * main
 * 
 * @param int n
 * @param char fileIn
 * @param char fileOut
 * @return int
 */
int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy resizeBy infile outfile\n");
        return 1;
    }
    
    // get size of n
    int n = atoi(argv[1]);
    
    // ensure n > 0 & < 100
    if (!(n > 0 && n < 100)) 
    {
        printf("Resize factor must be between 0 and 100.\n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // store old file's width in oldWidth
    int oldWidth = bi.biWidth;
    
    // calculate new width & height based on *n
    bi.biWidth *= n;
    bi.biHeight *= n;
    int newWidth = bi.biWidth;
    int newHeight = abs(bi.biHeight);   // use abs to get absolute value (this prevents negative heights)
    
    // calculate new padding
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calculate new bi.sizeImage
    bi.biSizeImage = ( (bi.biWidth * sizeof(RGBTRIPLE)) + newPadding) * newHeight;
    
    // calculate new bfSize
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int oldPadding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // calculate bytes in one line of old image
    int lLen = (oldWidth * sizeof(RGBTRIPLE)) + oldPadding;
    
    // allocate memory for array to hold one scanline of pixels from old image at a time
    RGBTRIPLE* scanline = malloc(lLen);
    
    // iterate over outfile's scanlines
    for (int i = 0, sLine = 0, oldSLine = 0; i < newHeight; i++)
    {
        // get line of infile to use
        sLine = (int) floor(i / n);
        
        /** as we know length of inline's scaline in bytes we can use fseek
         * to get to the correct scanline using scanline var
         * e.g. line x = sizeof(scanline) * x;
         */
        
        // Populate the scanline array based on sLine
        // check if the new sLine is greater than oldSline otherwise
        // unless i is 0 there is no need to re-read the scanline for this iteration.
        if (sLine > oldSLine || i == 0) 
        {
            // we need to find the start in bytes of the scanline we need
            // remembering that the first 54 bytes consist of the info and file headers
            fseek(inptr, ((sLine * lLen) + 54), SEEK_SET);
            // copy the scanline's bytes into our buffer
            for (int k = 0; k < oldWidth; k++) 
            {
                // read RGB triple strut from the infile
                fread((scanline + k), sizeof(RGBTRIPLE), 1, inptr);
            }
        }
        
        // write to new output file
        // for each pixel in our outptr current line
        for (int j = 0, k = 0; j < newWidth; j++) 
        {
            
            // temporary storage
            RGBTRIPLE triple;

            // set k as what pixel to write to on new file's scanline
            k = (int)floor(j / n);
            triple = scanline[k];
            
            // write pixel to the target file
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // add new padding, if required.
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }
        
        // set oldSLine for next iteration
        oldSLine = sLine;
    }
    
    // free scanline from memory
    free(scanline);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // return 0 for success
    return 0;
}
