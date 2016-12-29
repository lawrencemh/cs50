/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Searches a sorted array using Binary Search and returns true if
 * value found in the range specified (lBound & hBound)
 * 
 * @param int needle
 * @param array haystack
 * @param int lBount
 * @param int hBound
 * @return Bool
 */
bool BinarySearch(int value, int values[], int lBound, int hBound)
{
    // get middle key index in range
    int mid = ((hBound - lBound) / 2) + lBound;
    
    // check if middle value == value
    if( values[mid] == value)
    {
        // needle found in haystack
        return true;
    }
    else if (lBound >= hBound)
    {
        // checked last key in range return false as value wasn't found
        return false;
    }
    else if (values[mid] < value)
    {
        // search right half of range
        return BinarySearch(value, values, mid + 1, hBound);
    }
    else
    {
        // search left half of range
        return BinarySearch(value, values, lBound, mid - 1);
    }
    
}


/**
 * Swaps two variables by pointer
 * 
 * @param Array haystack
 * @param Int key1
 * @param Int key2
 * @return Void
 */
 void arraySwap(int values[], int i, int j)
 {
     int tmp = values[j];
     values[j] = values[i];
     values[i] = tmp;
 }

/**
 * Returns true if value is in a sorted array of n values, else false.
 * 
 * @param Int needle
 * @param Array haystack
 * @param Int size
 * @return Boolean
 */
bool search(int value, int values[], int n)
{
    // search whole range of array using Binary Search
    return BinarySearch(value, values, 0, n);
}

/**
 * Sorts array of n values (BubbleSort)
 * 
 * @param Array haystack
 * @param Int size
 * @return Void
 */
void sort(int values[], int n)
{
    // init changes int
    int c;
    
    // do until no changes were made in previous iteration
    do
    {
        // reset swaps this iteration
        c = 0;

        // loop through each value in array
        for (int i = 0; i < n - 1; i++)
        {
            // check if values[i] is higher than values[i+1] and swap if necessary
            if(values[i] > values[i+1])
            {
                // swap values and increment changes
                arraySwap(values, i, i+1);
                c++;
            }

        }
        
        // decrement n as far most right element is now sorted
        n--;
        
    } while (c > 0);
    
    // array sorted return
    return;
}

 
 