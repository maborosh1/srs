#include "types.h"
#include <stdio.h>

void swap(student_t* xp, student_t* yp)
{
    student_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// A function to implement bubble sort
void bubbleSort(record_arr arr, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++){
            if (arr.array[j].id > arr.array[j + 1].id) {
                swap(&arr.array[j], &arr.array[j + 1]);
            }
        }
    }
}
 
/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
