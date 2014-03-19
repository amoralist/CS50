#include <stdio.h>
#include <cs50.h>

/* Takes as input an integer between 0 and 23.  Outputs a half-pyramid
    in the style of the stairs to the flag in Mario. */

int main(void) {
    
    // receive a non-negative integer height less than 23
    printf("Enter a height (0-23): ");
    int height = GetInt();
    
    // handle unsuitable inputs
    while (height < 0 || height > 23) {
        printf("Enter an integer between 0 and 23: ");
        height = GetInt();
    }
    
    // print the lines of the half-pyramid
    int num_hash = 2;
    
    for(int h = 0; h < height; h++) {
       int width = 0;
       while (width + num_hash < height + 1) {
            printf(" ");
            width++;
       }
       while (width <= height) {
            printf("#");
            width++;
       }
       printf("\n");
       num_hash++;
    }
    
    return 0;
}
