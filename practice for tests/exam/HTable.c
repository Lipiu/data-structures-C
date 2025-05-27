#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define HASH_TABLE_SIZE 50
#define MAX_ID_SIZE 10

//student structure
struct Student{
    char* name;
    char* id;
    float gpa;
};
typedef struct Student Student;

//node structure
struct Node{
    Student data;
    struct Node* next;
};
typedef struct Node Node;

//method to insert node
Node* insert_node(Node* list, Student data){
    Node* temp = list;
    if(temp){
        while(temp->next != NULL){
            temp = temp->next;
        }
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if(temp != NULL){
        temp->next = new_node;
        return list;
    }
    else{
        return new_node;
    }
}

//method for hash function
unsigned int hash_function(char* key, unsigned int hash_table_size){
    unsigned int sum = 0;
    for(int i = 0; i < strlen(key); i++){
        sum += key[i];
    }
    return (sum % hash_table_size);
}

//insert data in table
void insert_data_table(Node** htable, unsigned int htable_size, Student data){
    unsigned int offset = hash_function(data.id, htable_size);
    htable[offset] = insert_node(htable[offset], data);
}

//search a student by id
Student* search_student_id(Node** htable, unsigned int htable_size, char* id){
    unsigned int offset = hash_function(id, htable_size);
    Node* temp = htable[offset];

    while(temp != NULL){
        if(strcmp(id, temp->data.id) == 0){
            return &(temp->data);
        }
        temp = temp->next;
    }
    return NULL;
}

int main(){
    FILE* f = fopen("data.txt", "r");
    Node** HTable = NULL;
    HTable = malloc(HASH_TABLE_SIZE * sizeof(Node*));
    for(unsigned int i = 0; i < HASH_TABLE_SIZE; i++){
        HTable[i] = NULL;
    }
    unsigned char buffer[256];
    while(fgets(buffer, sizeof(buffer), f)){
        Student stud;
        char seps[] = ",\n";
        
        char* token = strtok(buffer, seps);
        stud.name = malloc(strlen(token) + 1);
        strcpy(stud.name, token);

        token = strtok(NULL, seps);
        stud.id = malloc(strlen(token) + 1);
        strcpy(stud.id, token);

        token = strtok(NULL, seps);
        stud.gpa = (float)atof(token);

        insert_data_table(HTable, HASH_TABLE_SIZE, stud);
    }
    fclose(f);

    Student* data = search_student_id(HTable, HASH_TABLE_SIZE, "3001567");
    if(data != NULL){
        printf("Student with id %s is named %s and has gpa: %.1f", data->id, data->name, data->gpa);
    }
    else{
        printf("The student data does not exist!");
    }
}