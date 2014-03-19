/**
 * resize.c
 *
 * CS50x
 * Problem Set 5
 *
 * Copies a BMP piece by piece, incresing its width and height
 * by a factor of n.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember inputs
    int n = atoi(argv[1]); 
    char* infile = argv[2];
    char* outfile = argv[3];

    // check scale input
    if (n < 1 || n > 100) {
    	printf("First arguments must be a positive integer less than one hundred.");
	return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
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
        printf("Unsupported file format.\n");
        return 5;
    }

    // remember old width for later line array
    int old_width = bi.biWidth;
    int old_padding = (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine changes to bitmap headers
    // new width and height (no padding)
    bi.biWidth *= n;
    bi.biHeight *= n;  

    // new padding(?)
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // new total image size
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding) * abs(bi.biHeight);

    // new total bits (headers + image + padding)
    bf.bfSize = bi.biSizeImage + bi.biSize + sizeof(BITMAPFILEHEADER);   

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
	
	// copy each line n times    
        for (int j = 0; j < n; j++) {

		// iterate over line's pixels, reading and write n times
		for (int k = 0; k < old_width; k++) {
			RGBTRIPLE triple;
			fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
			for (int l = 0; l < n; l++) {
				fwrite(&triple, sizeof(triple), 1, outptr);
			}
		}

		// seek past old padding, add new to outfile
		fseek(inptr, old_padding, SEEK_CUR);
		for (int m = 0; m < padding; m++)
			fputc(0x00, outptr);

		// return to beginning of line for possible repeat
		fseek(inptr, -(old_width * 3 + old_padding), SEEK_CUR);
	}

	// seek past line already copied n times
	fseek(inptr, old_width * 3 + old_padding, SEEK_CUR);
    }

    // close files and return
    fclose(inptr);
    fclose(outptr);
    return 0;
}
