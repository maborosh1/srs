#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RECORDS_FILE_NAME "records.dat"
#define SORTED_RECORDS_FILE_NAME "sorted_records.dat"

record_arr continue_from_offset(FILE *file);

void sort_records() {
  FILE *ptr;

  if ((ptr = fopen(RECORDS_FILE_NAME, "rb")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fseek(ptr, 0L, SEEK_SET);

  record_arr records;
  initArray(&records, 1);
  records = continue_from_offset(ptr);

  bubbleSort(records, records.used);
  fclose(ptr);

  if ((ptr = fopen(SORTED_RECORDS_FILE_NAME, "wb")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  for(int i=0; i < records.used; ++i) {
    student_t student;
    student = records.array[i];

    // fprintf(stdout, "\t- %d, %s, %d, %s\n", student.id, student.name,
    //        student.age, student.sclass); 
   fwrite(&student, sizeof(student_t), 1, ptr);
  }

  freeArray(&records);
  fclose(ptr);
}

void writer(student_t stud) {
  FILE *fptr;

  if ((fptr = fopen(RECORDS_FILE_NAME, "ab")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fwrite(&stud, sizeof(student_t), 1, fptr);
  fclose(fptr);
}

void read_sorted_r() {
  student_t student;
  FILE *fptr;

  if ((fptr = fopen(SORTED_RECORDS_FILE_NAME, "rb")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fseek(fptr, 0L, SEEK_SET);

  printf("\t[R] READING SORTED RECORDS!\n");

  while (1) {

    fread(&student, sizeof(student_t), 1, fptr);

    if (feof(fptr)) {
      break;                                                                   }

    fprintf(stdout, "\t- %d, %s, %d, %s\n", student.id, student.name,
            student.age, student.sclass);                                    }

  fclose(fptr);
}

void readr() {
  student_t student;
  FILE *fptr;

  if ((fptr = fopen(RECORDS_FILE_NAME, "rb")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fseek(fptr, 0L, SEEK_SET);
  
  printf("\t[R] READING ALL RECORDS!\n");

  while (1) {

    fread(&student, sizeof(student_t), 1, fptr);

    if (feof(fptr)) {
      break;
    }

    fprintf(stdout, "\t- %d, %s, %d, %s\n", student.id, student.name,
            student.age, student.sclass);
  }

  fclose(fptr);
}

void modifyr(int id, int field) {
  student_t student;
  FILE *fptr;

  if ((fptr = fopen(RECORDS_FILE_NAME, "rb+")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }
  char *new_name;
  student = findr(fptr, id);
  switch (field) {
    case ID_FIELD:
      fprintf(stdout, "\t[+] ENTER NEW ID => ");
      scanf("%d", &student.id);
      break;
    case NAME_FIELD:
      fprintf(stdout, "\t[+] ENTER NEW NAME => ");
      char *new_name = (char*) malloc(NAME_FIELD_MAX_LEN);
      fgets(new_name, NAME_FIELD_MAX_LEN, stdin);
      // Only to strip new line (\n) character
      new_name[strcspn(new_name, "\n")] = '\0';
      student.name = new_name;
      break;
    case AGE_FIELD:
      fprintf(stdout, "\t[+] ENTER NEW AGE => ");
      scanf("%d", &student.age);
      break;
    case CLASS_FIELD:
      fprintf(stdout, "\t[+] ENTER NEW CLASS => ");
      char *new_class = (char*) malloc(CLASS_FIELD_MAX_LEN);
      fgets(new_class, CLASS_FIELD_MAX_LEN, stdin);
      // Only to strip new line (\n) character
      new_class[strcspn(new_class, "\n")] = '\0';
      student.sclass = new_class;
      break;
    default:
      fprintf(stderr, "[Err] UNKNOWN FIELD %d!\n", field);
      fclose(fptr);
      return;
  }

  fwrite(&student, sizeof(student_t), 1, fptr);
  fclose(fptr);
}

student_t findr(FILE *fptr, int id) {
  student_t student;

  fseek(fptr, 0L, SEEK_SET);

  while (!feof(fptr)) {
    fread(&student, sizeof(student_t), 1, fptr);
    if (student.id == id) {
      fseek(fptr, -sizeof(student_t), SEEK_CUR);
      break;
    }
  }

  return student;
}

void searchr() {
  int id;
  student_t student;
  FILE* fptr;

  if ((fptr = fopen(RECORDS_FILE_NAME, "rb+")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fprintf(stdout, "\t[P] ENTER STUDENT ID TO SEARCH FOR => ");
  scanf("%d", &id);
  flushi();
  student = findr(fptr, id);

  if (student.name) {
    fprintf(stdout, "\t- %d, %s, %d, %s\n", student.id, student.name,
            student.age, student.sclass);
    return;
  }

  fprintf(stderr, "\t[Err] ERROR! RECORD NOT FOUND!\n");
  return;

}

void deleter(int id) {
  record_arr records;
  student_t student;
  FILE *fptr;
  off_t offset;

  if ((fptr = fopen(RECORDS_FILE_NAME, "rb+")) == NULL) {
    printf("[Err] ERROR WHILE OPENING THE FILE!\n");
    exit(1);
  }

  fseek(fptr, 0l, SEEK_SET);

  while (!feof(fptr)) {
    fread(&student, sizeof(student_t), 1, fptr);
    if (student.id == id) {
      fseek(fptr, -sizeof(student_t), SEEK_CUR);
      offset = ftell(fptr);
      fseek(fptr, sizeof(student_t), SEEK_CUR);
      // read and save records after the deleted one
      records = continue_from_offset(fptr);
      // truncate the file into size equal to bytes from the beginning to the
      // last record before the deleted one
      if (truncate(RECORDS_FILE_NAME, offset) != 0) {
        fprintf(stderr, "Failed to truncate records file. offset: %ld", offset);
        exit(1);
      }
      // rewrite the truncated records
      // fprintf(stdout, "[+] REWRITING TRUNCATED RECORDS !\n");

      if (records.used == 0) {
        break;
      }

      // fprintf(stdout, "[+] REM: %zu!\n", records.used);
      for (int i = 0; i < records.used; ++i) {
        writer(records.array[i]);
      }
      freeArray(&records);
      break;
    }
  }
  fclose(fptr);
}

// Read from a specified offset to the end of file
record_arr continue_from_offset(FILE *file) {
  record_arr records;
  initArray(&records, sizeof(student_t));
  student_t record;
  while (1) {
    fread(&record, sizeof(student_t), 1, file);
    if (feof(file)) {
      break;
    }
    insertArray(&records, record);
  }
  return records;
}

void flushi() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
