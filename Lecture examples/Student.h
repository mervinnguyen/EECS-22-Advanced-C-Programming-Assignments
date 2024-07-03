#ifndef STUDENT_H
#define STUDENT_H

#define SLEN 40

struct Student {
    int ID;
    char name[SLEN + 1];
    char Grade;
};

typedef struct Student STUDENT;

//Allocate a new student record

STUDENT *NewStudent(int ID, char *Name, char Grade);

void DeleteStudent(STUDENT *s);

void PrintStudent(STUDENT *s);

#endif