/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Swaps two values in array
 */
void arraySwap(int values[], int i, int j);

/**
 * Searches a sorted array using Binary Search and returns true if
 * value found in the range specified (lBound & hBound)
 */
bool BinarySearch(int value, int values[], int lBound, int hBound);