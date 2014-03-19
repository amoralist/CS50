#include <stdio.h>
#include <cs50.h>

/* Takes as input an integer between 0 and 23.  Outputs a small 
    pyramid in the style Mario. */

int main(void) {
    
    // receive a non-negative integer height less than 23
        // and handle unsuitable inputs
    int height;
    do {
        printf("Enter a height (0-23): ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    // print the lines of the pyramid
    int num_hash = 1;
    
    for(int h = 0; h < height; h++) {
       int width = 0;
       while (width + num_hash < height) {
            printf(" ");
            width++;
       }
       while (width < height) {
            printf("#");
            width++;
       }
       printf("  ");
       for(int n = 0; n < num_hash; n++) {
            printf("#");
       }
       printf("\n");
       num_hash++;
    }
    
    return 0;
}
