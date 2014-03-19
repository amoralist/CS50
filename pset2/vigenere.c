#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

/* A program which takes as command-line input ONE alpha only
    string and uses that to convert input plain text to cypher
    text.  The cypher text is output to the console.
    
    VIGENERE'S CYPHER
    
    c(i) = (p(i) + k(j) % 26) */

int AlphaToCount(char letter);

int main(int argc, string argv[]) {
    
    // check for one command-line arg
    if ( argc != 2 ) {
        printf("This program requires one and only one command line arg.");
        return 1;
    }
    
    // check that it is an alpha-only string
    for (int n = 0; n < strlen(argv[1]); n++) {
        char test = argv[1][n];
        if (isalpha(test) == 0) {
            printf("Command line input must be an alpha only string.");
            return 1;
        }
    }
    // store offset and plain text as strings, initialize crypt
    string off_string = argv[1];
    string plain_text = GetString();
    char crypt[strlen(plain_text) + 1];
    int off_len = strlen(off_string);
    
    // increment through plain text
    int letter_count = 0;
    for (int n = 0; n < strlen(plain_text); n++) {
        // convert ascii values to 0-25 and apply the cypher
        char plain = plain_text[n];
        if (isalpha(plain)) {
            if (isupper(plain)){
                int letter_num = AlphaToCount(plain);
                int offset = AlphaToCount(off_string[letter_count % off_len]);
                char cypher = ((letter_num + offset) % 26) + 65;
                crypt[n] = cypher;
            }
            else {
                int letter_num = AlphaToCount(plain);
                int offset = AlphaToCount(off_string[letter_count % off_len]);
                char cypher = ((letter_num + offset) % 26) + 97;
                crypt[n] = cypher;
            }
            letter_count++;
        }
        else
            crypt[n] = plain;
    }
    // insert null termination, output cypher text
    crypt[strlen(plain_text)] = 0;
    printf("%s\n", (string) crypt);

}

int AlphaToCount(char letter) {   
    if (isupper(letter)){
        int letter_num = (int) letter - 65;
        return letter_num;
    } else {
        int letter_num = (int) letter - 97;
        return letter_num;
    }
}



