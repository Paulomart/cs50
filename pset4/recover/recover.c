/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover input\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // detect size of imput
    fseek(inptr, 0L, SEEK_END);
    int size = ftell(inptr);
    rewind(inptr);
    
    if (size % 512 != 0) {
        fprintf(stderr, "Input is not of 512 bytes chunk size");
        return 3;
    }

    uint8_t *d = malloc(512);
    int count = 0;
    bool image = false;
    FILE *outptr;

    for (int chunk = 0, n = size / 512; chunk < n; chunk++) {
        fread(d, 512, 1, inptr);
        
        if (d[0] == 0xff && d[1] == 0xd8 && d[2] == 0xff) {
            if (d[3] >= 0xe0 && d[3] <= 0xef) {
                // still in image and found a new one
                // replace handle for file
                if (image) {
                    fclose(outptr);
                }
                char *filename = malloc(8 * sizeof(char));
                sprintf(filename, "%03i.jpg", count);
                outptr = fopen(filename, "w");
                free(filename);
                image = true;
                count++;
            }
        }
        if (image) {
            fwrite(d, 512, 1, outptr);
        }
    }
    fclose(inptr);
    free(d);
    // success
    return 0;
}
