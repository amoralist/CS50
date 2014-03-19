#include <stdio.h>
#include <cs50.h>

/* Create a program to verify (and identify the issuer of ) credit
    card numbers (LongLong) as valid according to the inbuilt checksum.
    
    AMEX 15 digits; 34-, 37-
    MASTERCARD 16 digits; 51-.52-, 53-, 54-, 55-
    VISA 13 or 16 digits; 4-
    
    CHECKSUM Algorithm
    1.Multiply every other digit, starting with the number's
        second-to-last digit, by two.  Sum the digits of all the products.
    2. Add step 1's sum to the sum of the digits that are not used in
        step 1.
    
    If (total % 10 == 0), the CC number is valid. */
    
int main(void) {
    printf("Enter a potential credit-card number (no hyphens): ");
    long long cc_number = GetLongLong();          

    int count = 0;
    int checksum = 0;
    int ones = 0;
    for(int i = 0; cc_number > 0; i++) {
        ones = cc_number % 10;
        cc_number = cc_number / 10;
        if (i % 2 == 0) {
            checksum += ones;
            count++;
        }
        else {
            int product = ones * 2;
             if (product < 10) {
                checksum += product;
                count++;
             }
             else {
                checksum += product % 10;
                checksum += product / 10;
                count++;
            }            
        }
    }
    
    if (checksum % 10 != 0) {
        printf("INVALID\n");
        return 0;
    }
    
    if (ones == 3 && count == 15) {
        printf("AMEX\n");
    } 
    else if (ones == 4 && (count == 13 || count == 16)) {
        printf("VISA\n");
    } 
    else if (ones == 5 && count == 16) {
        printf("MASTERCARD\n");
    }
    else {
        printf("INVALID\n");
    }
    
    return 0;
}
