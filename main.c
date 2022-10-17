#include "record/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void modify_a_record() {
  fprintf(stdout, "[M] MODIFYING A RECORD!\n");
  int student_id, field;
  fprintf(stdout, "\t[+] ENTER STUDENT ID => ");
  scanf("%d", &student_id);
  fprintf(stdout, "\t[+] CHOOSE A FIELD TO MODIFY\n"
                  "\t\t[1] ID\n"
                  "\t\t[2] NAME\n"
                  "\t\t[3] AGE\n"
                  "\t\t[4] CLASS\n"
                  "\t[FIELD] => ");
  scanf("%d", &field);
  flushi();
  modifyr(student_id, field);
}

void write_a_record() {
  student_t new_student;

  fprintf(stdout, "[W] WRITEING A RECORD!\n");
  int student_id, field;

  fprintf(stdout, "\t[+] ENTER STUDENT ID => ");
  scanf("%d", &new_student.id);
  flushi();

  fprintf(stdout, "\t[+] ENTER STUDENT NAME => ");
  char* name = (char*) malloc(NAME_FIELD_MAX_LEN);
  fgets(name, NAME_FIELD_MAX_LEN, stdin);
  name[strcspn(name, "\n")] = '\0';
  new_student.name = name;

  fprintf(stdout, "\t[+] ENTER STUDENT AGE => ");
  scanf("%d", &new_student.age);
  flushi();

  fprintf(stdout, "\t[+] ENTER STUDENT CLASS => ");
  char* sclass =  (char*) malloc(CLASS_FIELD_MAX_LEN);
  fgets(sclass, CLASS_FIELD_MAX_LEN, stdin);
  sclass[strcspn(sclass, "\n")] = '\0';
  new_student.sclass = sclass;

  //fprintf(stdout, "\t- %d, %s, %d, %s\n", new_student.id, new_student.name,
  //          new_student.age, new_student.sclass);
  writer(new_student);
}

void delete_a_record() {
  int id;
  fprintf(stdout, "\t[P] ENTER STUDENT ID TO DELETE => ");
  scanf("%d", &id);
  flushi();
  deleter(id);
}

int main() {
  srand((unsigned int) time(NULL));
  int id = rand() % 20;
  student_t student = {id, "fortnite", 22, "is"};

  fprintf(stdout, "[W] WRITING TEMPORARY RECORDS!\n");
  for (int i = 0; i < 4; ++i) {
    writer(student);
    student.id = rand() % 20;
    student.age++;
  }

  fprintf(stdout, "[=] WELCOME TO STUDENT RECORD SYSTEM [=]\n");
  while(1) {
    int op;
    fprintf(stdout, "\n[+] SELECT AN OPERATION\n"
                  "[1] READ RECORDS\n"
                  "[2] READ SORTED RECORDS\n"
                  "[3] SEARCH FOR A RECORD\n"
                  "[4] WRITE A RECORD\n"
                  "[5] DELETE A RECORD\n"
                  "[6] MODIFY A RECORD\n"
                  "[7] SORT RECORDS\n"
                  "[8] EXIT\n"
                  "\n[OP] => ");
    scanf("%d", &op);
    flushi();
    
    switch(op) {
      case 1:
        readr();
        break;
      case 2:
        read_sorted_r();
        break;
      case 3:
        searchr();
        break;
      case 4:
        write_a_record();
        break;
      case 5:
        delete_a_record();
        break;
      case 6:
        modify_a_record();
        break;
      case 7:
        sort_records();
        break;
      case 8:
        exit(0);
        break;
      default:
        fprintf(stdout, "[Err] UNKNOWN OPERATION\n");
    }
  }
  
  return 0;
}
