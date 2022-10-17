#include "types.h"
#include <stdio.h>
#include <stdlib.h>

void initArray(record_arr *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(student_t));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(record_arr *records, student_t element) {
  // a->used is the number of used entries, because a->array[a->used++] updates
  // a->used only *after* the array has been accessed. Therefore a->used can go
  // up to a->size
  if (records->used == records->size) {
    records->size *= 2;
    records->array = realloc(records->array, records->size * sizeof(student_t));
  }
  records->array[records->used++] = element;
}

void freeArray(record_arr *records) {
  free(records->array);
  records->array = NULL;
  records->used = records->size = 0;
}