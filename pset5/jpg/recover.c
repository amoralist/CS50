/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>



int main(int argc, char* argv[]) {
  // open CF Card file image, initialize count
  FILE* card = fopen("card.raw", "r");
  int count = 0;
  int in_file = 0;

   // set up 512 byte buffer
   unsigned char buffer[512];
    
   // initialize first jpg names
   char filename[sizeof("000.jpg")];
   sprintf(filename, "%03i.jpg", count);
   FILE* jpg = fopen(filename, "a");

   while(fread(&buffer, sizeof(unsigned char), 512, card) > 1) {    
       // compare the first four bytes with 0xff 0xd8
           // 0xff 0xe(0/1) 
       if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)) {
           // if == close old file if open, open new file
                // append the current buffer 
           if (in_file == 1) {
                fclose(jpg);
                count++;
                sprintf(filename, "%03i.jpg", count);
		        jpg = fopen(filename, "a");
           }
           in_file = 1; 
       }
       if (in_file == 1) {
           fwrite(&buffer, sizeof(unsigned char), 512, jpg);
       }
   }
   fclose(card);
   fclose(jpg);

   return 0;
}
