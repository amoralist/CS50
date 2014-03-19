#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

/* A program which must take only one command line argument.  If provided
    an appropriate argument the program will ask the user for a string to
    encrypt and then print to the screen the text encrypted by the caesar
    cypher with an offset of the number provided in the command line. 
    
    CAESAR CYPHER
    
    c = encrypted text
    p = plain text
    k = offset
    
    c(i) = (p(i) + k) % 26 */

int main(int argc, char* argv[]) {
    // check for appropriate c-line args
    if (argc != 2) {
        printf("This program can and must receive only one non-negative integer.\n");
        return 1;
    }
    
    // access argv array and convert that char to int for offset, 
        // check for positive
    int offset = atoi(argv[1]);
    if (offset < 0) {
        printf("Offset must be a non-negative integer.");
        return 1;
    }
    
    // receive a plaintext string to encrypt, make note of its length
    // printf("Enter text to be encrypted please: ");
    string plain = GetString();
    int length = strlen(plain);
    
    // create an array long enough to hold encrypted text
    unsigned char cypher[length];
    
    // iterate over the characters, change and save the offset letter
        // characters without changing punctuation, spaces, \n, etc
    for (int n = 0; n < length; n++) {
        unsigned char character = plain[n];
				if (isalpha(character)) {
						if (isupper(character)){
								// convert ascii to 0-25
								int letter_num = (int) character - 65;
								// offset the letter and return to ascii value in array
								cypher[n] = ((letter_num + offset) % 26) + 65;
						}
						else {
								int letter_num = (int) character - 97;
								cypher[n] = ((letter_num + offset) % 26) + 97;
						}
				}		            
        else
            cypher[n] = character;
    }
    
    // print the characters of the cyphered character array to the screen
    
    for (int n = 0; n < length; n++){
        printf("%c", cypher[n]);
    }  
    printf("\n");
    return 0;
    
}
