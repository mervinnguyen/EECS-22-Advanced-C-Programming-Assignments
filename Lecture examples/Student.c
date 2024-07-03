//Student.c: maintaining student records

#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

STUDENT *NewStudent (int ID, char *Name, char Grade){
    STUDENT *s;
    s = malloc(sizeof(STUDENT));
    if (!s){
        perror("Out of memory! Aborting...");
        exit(10);
    }
    s->ID = ID;
    strncpy(s->Name, Name, SLEN);
    s->Grade = Grade;
    return s;
}

void DeleteStudent (STUDENT *s){
    free(s);
}

void PrintStudent (STUDENT *s){
    assert(s);
    printf("Student ID: %d\n", s->ID);
    printf("Student Name: %s\n", s->Name);
    printf("Student Grade: %c\n", s->Grade);

}

int main(void){
    STUDENT *s1 = NULL, *s2 = NULL;
    printf("Creating 2 student records...\n");
    s1 = NewStudent(1001, "Jane Doe", 'A');
    s2 = NewStudent(1002, "John Doe", 'C');
    
    printf("Printing student records...\n");
    PrintStudent(s1);
    PrintStudent(s2);

    printf("Deleting student records...\n");
    DeleteStudent(s1);
    s1 = NULL;
    DeleteStudent(s2);
    s2 = NULL;

    printf("Done!\n");
    return 0;

}