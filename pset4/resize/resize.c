/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy factor infile outfile\n");
        return 1;
    }

    int factor = atoi(argv[1]);    

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int oldWidth = bi.biWidth;
    
    printf("pre:\n");
    printf("size: %u\n", bi.biSizeImage);
    printf("biWidth: %d\n", bi.biWidth);
    printf("biHeight: %d\n", bi.biHeight);
    printf("padding: %i\n", oldPadding);
    

    bi.biWidth = bi.biWidth * factor;
    bi.biHeight = bi.biHeight * factor;
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * abs(bi.biWidth)) + newPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + bf.bfOffBits;

    printf("after:\n");
    printf("size: %u\n", bi.biSizeImage);
    printf("biWidth: %d\n", bi.biWidth);
    printf("biHeight: %d\n", bi.biHeight);
    printf("padding: %i\n", newPadding);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile n times horizontally
            for(int k = 0; k < factor; k++)
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);
        
        // then add it back (to demonstrate how)
        for (int k = 0; k < newPadding; k++)
            fputc(0x00, outptr);

        // if i % n is 0, write a new row, else repeat the last row
        long offset = oldWidth * sizeof(RGBTRIPLE) + oldPadding;
        if((i+1) % factor != 0)
            fseek(inptr, -offset, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
