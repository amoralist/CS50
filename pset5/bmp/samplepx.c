/**
 *  samplepx.c
 *  B Gieseler
 *  CS50x
 *
 *  Creates a 1x1 BMP file for testing
 *  resize in pset 5.
**/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{ 
	// open file to steal header from 
    FILE* inptr = fopen("small.bmp", "r");
    if (inptr == NULL)
    {
        printf("Could not open small.bmp\n");
        return 2;
    }
		
	// set up stream pointer for output file
	char* outfile = "onepx.bmp";
	FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
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
    
    bi.biWidth = 1;
    bi.biHeight = 1;
  	int padding = 1;
  	bi.biSizeImage = 4;
  	bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
  	
  	fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
  	fwrite(&bi, sizeof(BITMAPINFOHEADER),1, outptr);
  	
  	RGBTRIPLE triple;
  	triple.rgbtBlue = 0x00;
  	triple.rgbtRed = 0x00;
  	triple.rgbtGreen = 0x00;
  	fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
  	fputc(0x00, outptr);
  	
  	fclose(inptr);
  	fclose(outptr);
  	
  	return 0;
}
    
