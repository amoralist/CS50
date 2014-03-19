/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
      
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool binary_search(int key, int values[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // linear search 
 /* if (value < 0)
    	return false;
    
    for (int i = 0; i < n; i++) {
    	if (values[i] == value)
    		return true;
   	}	
   	
   	return false; */
   	
   	// binary search call
   	return binary_search(value, values, 0, n - 1);
    
}

/**
 * Sorts array of n values in memory (arrays passed by reference, not value)
 		using bubblesort.
 */
void sort(int values[], int n)
{
    // declare a flips counting int
    int flips = 0;
    
    // pass through the values of the array
    do {
    	flips = 0;
    	for (int i = 0; i < n; i++) {
    		
    		// flip values and incremement counter if "left" 
    			// number is larger than "right"
    		if (values[i] > values[i + 1]) {
    			int larger = values[i];
    			values[i] = values[i+1];
    			values[i+1] = larger;
    			flips ++;
    		}
    	}
    }
    while (flips != 0);

    return;
}

bool binary_search(int key, int values[], int min, int max) {
	
	// base case
	if (min > max) {
		return false;
	}
	
	// find the midpoint
	int mid = min + ((max - min) / 2.0);
	
	// check "right half" of list
	if (values[mid] < key) {
		return binary_search(key, values, mid + 1, max);
	}
	
	// check "left half"
	else if (values[mid] > key) {
		return binary_search(key, values, min, mid - 1);
	}
	
	// must be the midpoint
	else
		return true;
		
}


