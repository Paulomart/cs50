/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

bool searchIntern(int value, int values[], int n, int s);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n) {
    return searchIntern(value, values, 0, n);
}

bool searchIntern(int value, int values[], int s, int n) {
    if (s > n) {
        return false;
    }
    int mid = (s + n) / 2;
    int k = values[mid];

    if (k == value) {
        return true;
    } else if (value < k) {
        // value is to the left
        return searchIntern(value, values, s, mid - 1);
    } else if (value > k) {
        // value is to the right
        return searchIntern(value, values, mid + 1, n);
    } else {
        // lolz
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n) {
    for (int i = 0; i < n; i++) {
        int k = i;
        int j = i + 1;
        while (j < n) {
            if (values[j] < values[k]) {
                k = j;
            }
            j++;
        }
        int tmp = values[k];
        values[k] = values[i];
        values[i] = tmp;
    }
}
