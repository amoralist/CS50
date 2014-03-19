#define _XOPEN_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>

#define MAX_LENGTH 8

int main (int argc, char* argv[]) {  
    // check for proper usage
    if (argc != 2) {
        printf("usage: crack key\n");
        return 0;
    }
    
    // store input key as a salt and a hash
    char* salt = "50";
    
    // open the linux dictionary for hopeful brevity
    FILE* dictionary = fopen("words.txt", "r");
    // initialize char array to eventually store each line
        // of the dictionary
    char line[MAX_LENGTH];
    
    // check dictionary properly loaded
    if (dictionary == NULL) {
        printf("Error opening dictionary\n");
        return -1;
    }
    
    //iterate over each line of the dictionary
    while(fgets(line, sizeof(line), dictionary)) { 
        printf("The hashed result of \"%s\" and salt \"%s\" is: %s\n", line, salt, crypt(line, salt));
    }
    
    fclose(dictionary);
    printf("No obvious result found, try harder.\n");
    return 1;
}
