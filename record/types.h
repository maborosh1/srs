#include <stddef.h>
#include <stdio.h>

#define ID_FIELD 1
#define ID_FIELD_MAX_SIZE sizeof(int)
#define NAME_FIELD 2
#define NAME_FIELD_MAX_LEN 255
#define AGE_FIELD 3
#define AGE_FIELD_MAX_SIZE sizeof(unsigned short)
#define CLASS_FIELD 4
#define CLASS_FIELD_MAX_LEN 255

struct student_r {
  int id;
  const char *name;
  int age;
  const char *sclass;
};

typedef struct student_r student_t;

typedef struct {
  student_t *array;
  size_t used;
  size_t size;
} record_arr;

extern void initArray(record_arr *a, size_t initialSize);

extern void insertArray(record_arr *a, student_t element);

extern void freeArray(record_arr *a);

extern void writer(student_t stud);

extern void readr();

extern void read_sorted_r();

extern student_t findr(FILE* fptr, int id);

extern void modifyr(int id, int field);

extern void deleter(int id);

extern void searchr();

extern void flushi();

extern void bubbleSort(record_arr arr, int n);

extern void sort_records();
