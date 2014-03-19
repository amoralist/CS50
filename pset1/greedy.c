#include <stdio.h>
#include <cs50.h>

int main(void) {
    // ask user how much change is owed
    double change = 0;
    
    do {
        printf("How much change do I owe you?\n");
        change = GetDouble();
    }
    while(change < 0);
    
    // convert the dollar input to cents for rounding safety
    change = change * 100;
    int cents = change;
    
    // count minimum necessary coins (quarters 
        // through pennies) to provide change
    int coins = 0;
    
    while(cents >= 25) {
        coins++;
        cents = cents - 25;
    }
    while(cents >= 10) {
        coins++;
        cents = cents - 10;
    }
    while(cents >= 5) {
        coins++;
        cents = cents - 5;
    }
    while(cents >= 1) {
        coins++;
        cents = cents - 1;
    }
    
    // print the minimum amount of coins necessary
        // to provide change
    printf("%d\n", coins);
    
    return 0;
}
