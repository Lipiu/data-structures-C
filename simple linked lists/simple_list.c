#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Student{
    char* name;
    char* id;
    float gpa;
};
typedef struct Student Student;

struct Node{
    struct Node* next;
    Student data;
};
typedef struct Node Node;

//parse and print the list
void parse(Node* list){
    Node* temp = list;
    while(temp != NULL){
        printf("%s has the id %s and the gpa %.1f\n", temp->data.name, temp->data.id, temp->data.gpa);
        temp = temp->next;
    }
}

//insert at first position
Node* insertFirst(Node* list, Student data) {
    Node* firstNode = (Node*)malloc(sizeof(Node));
    firstNode->data = data;

    if(list != NULL){
        firstNode->next = list;
    }
    else{
        firstNode->next = NULL;
    }

    return firstNode;
}

//insert node in the middle
Node* insertMiddle(Node* list, Student data){
    Node* midNode = (Node*)malloc(sizeof(Node)); //allocate data for middle node
    midNode->data = data;
    midNode->next = NULL;

    if(list == NULL){ //if list is empty
        return midNode;
    }

    Node* temp = list; //temporary node that points to head
    int countNodes = 0; //variable to count nodes
    while(temp != NULL){
        countNodes++;
        temp = temp->next;
    }

    int midPos = countNodes / 2; //calculate the middle position
    temp = list;
    if(midPos == 0){
        midNode->next = list;
        return midNode;
    }

    //iterate to mid - 1 position
    for(int i = 0; i < midPos - 1; i++){
        temp = temp->next;
    }
    //link the middle node to the list
    midNode->next = temp->next;
    temp->next = midNode;

    return list;
}

//insert at last position
Node* insertLast(Node* list, Student data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        printf("Could not allocate memory!\n");
        return list;
    }
    newNode->data = data;
    newNode->next = NULL;

    if(list == NULL){
        return newNode;
    }

    Node* temp = list;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;

    return list;
}

//delete first node
Node* deleteFirstNode(Node* list){
    Node* temp = list;
    list = list->next; //move the head

    temp->next = NULL; //break the link
    //free the memory
    free(temp->data.id);
    free(temp->data.name);
    free(temp);

    return list;
}

//delete last element
Node* deleteLastNode(Node* list){
    if(list == NULL){
        return NULL;
    }
    if(list->next == NULL){
        free(list->data.name);
        free(list->data.id);
        free(list);
        return NULL;
    }

    Node* temp = list;
    //iterate to the second to last node
    while(temp->next->next != NULL){
        temp = temp->next;
    }

    Node* nodeToDelete = temp->next;
    temp->next = NULL;
    //free the memory
    free(nodeToDelete->data.name);
    free(nodeToDelete->data.id);
    free(nodeToDelete);
    
    return list;
}

//delete by name -> not working for now
Node* deleteByName(Node* list, char* name) {
    while (list != NULL && strcmp(list->data.name, name) == 0) {
        Node* temp = list;
        list = list->next;
        free(temp->data.name);
        free(temp->data.id);
        free(temp);
    }

    Node* temp2 = list;
    while (temp2 != NULL && temp2->next != NULL) {
        if (strcmp(temp2->next->data.name, name) == 0) {
            Node* temp = temp2->next;
            temp2->next = temp->next;
            free(temp->data.name);
            free(temp->data.id);
            free(temp);
        } else {
            temp2 = temp2->next;
        }
    }
    return list;
}


int main(){
    
    FILE* f = fopen("data.txt", "r");
    Node* head = NULL;
    unsigned char buffer[200];

    while(fgets(buffer, sizeof(buffer),f)){
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

        head = insertLast(head, stud);
    }

    printf("\nInitial list:\n");
    parse(head);

    //creating middle student for testing
    Student midStud;
    midStud.name = "Rosu Liviu";
    midStud.gpa = 0.f;
    midStud.id = "2";

    //creating first position student for testing
    Student firstStud = midStud;
    firstStud.name = "Rosu Liviu";
    firstStud.gpa = 1.f;
    firstStud.id = "3";

    printf("\nTesting:\n");

    printf("\nList after inserting in the middle:\n"); //middle holder will be added in the middle
    head = insertMiddle(head, midStud);
    parse(head);

    printf("\nList after deleting first element:\n"); //Rosu Liviu will be deleted
    head = deleteFirstNode(head);
    parse(head);

    printf("\nList after deleting last element:\n"); //Suto Mara will be deleted
    head = deleteLastNode(head);
    parse(head);

    printf("\nList after inserting at first position:\n"); //middle holder will be added again
    head = insertFirst(head, firstStud);
    parse(head);


    //delete by name does not work for now
    printf("\nList after deleting all nodes named 'Rosu Liviu':\n");
    head = deleteByName(head, "Rosu Liviu");
    parse(head);

    fclose(f);

    //TO DO
    //delete by name
    //delete if GPA is lower than a certain value

    return 0;
}