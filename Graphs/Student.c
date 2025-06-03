#include "Shared.h"


Student* createStudent(const char* name, short group, float income, short id){
    PStudent stud = NULL;
    stud = (Student*)malloc(sizeof(Student));

    if(stud != NULL){
        stud->name = (char*)malloc(strlen(name) + 1);
        if(stud->name != NULL){
            strcpy(stud->name, strlen(name) + 1);
        }
        stud->group = group;
        stud->income = income;
        stud->id = id;
    }
    return stud;
}


void deleteStudent(PStudent pStud){
    if(pStud != NULL){
        if(pStud->name != NULL){
            free(pStud->name);
        }
        free(pStud);
    }
}


void printStudent(PStudent pStud){
    if(pStud != NULL){
        printf("Student ID: %d\n", pStud->id);
        if(pStud->name != NULL){
            printf("Student name: %s\n", pStud->name);
        }
        printf("Student income: %.2f\n", pStud->income);
        printf("Student Group: %d\n", pStud->group);
    }
}