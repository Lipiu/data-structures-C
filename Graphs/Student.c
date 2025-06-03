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