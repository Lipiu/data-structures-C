#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>


struct Friends{
    char* name;
    char* favActivity;
    int age;
};
typedef struct Friends Friends;

struct Node{
    struct Node* next;
    struct Node* prev;
    Friends data;
};
typedef struct Node Node;

struct DoubleLinkedList{
    struct Node* head;
    struct Node* tail;
};
typedef struct DoubleLinkedList DoubleLinkedList;

//parse
void parse(DoubleLinkedList dlist){
    Node* temp = dlist.head;
    printf("Double list head to tail:\n");
    while(temp != NULL){
        printf("%s's favorite activity is %s and he is %d years old.\n", temp->data.name, temp->data.favActivity, temp->data.age);
        temp = temp->next;
    }
}

//insert beginning
DoubleLinkedList insertBeginning(DoubleLinkedList dlist, Friends data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    newNode->prev = NULL;

    if(dlist.head == NULL){
        dlist.head = dlist.tail = newNode;
    }
    else{
        newNode->next = dlist.head;
        dlist.head->prev = newNode;
        dlist.head = newNode;
    }
    return dlist;
}

//insert middle
DoubleLinkedList insertMiddle(DoubleLinkedList dlist, Friends data){
    Node* midNode = (Node*)malloc(sizeof(Node));
    midNode->next = NULL;
    midNode->data = data;
    midNode->prev = NULL;

    if(dlist.head == NULL){
        dlist.head = dlist.tail = midNode;
    }
    //insert at the end
    if(dlist.head->next == NULL){
        dlist.head->next = midNode;
        midNode->prev = dlist.head;
        dlist.tail = midNode;
    }
    else{
        int countNodes = 0;
        Node* temp = dlist.head;
        while(temp != NULL){
            countNodes++;
            temp = temp->next;
        }
        temp = dlist.head;
        int midPos = countNodes / 2;
        for(int i = 0; i < midPos - 1; i++){
            temp = temp->next;
        }
        midNode->next = temp->next;
        midNode->prev = temp;
        
        if(temp->next != NULL)
            temp->next->prev = midNode;
        else{
            dlist.tail = midNode;
        }
        temp->next = midNode;
    }
    return dlist;
}

//insert at end
DoubleLinkedList insertEnd(DoubleLinkedList dlist, Friends data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = data;
    newNode->prev = dlist.tail;

    if(dlist.head == NULL){
        dlist.head = dlist.tail = newNode;
    }
    else{
        dlist.tail->next = newNode;
        dlist.tail = newNode;
    }
    return dlist;
}

//delete beginning
DoubleLinkedList deleteBeginning(DoubleLinkedList dlist){
    Node* temp = dlist.head;
    temp = temp->next;
    temp->next = temp->next->next;
    temp->prev = NULL;

    return dlist;
}

int main(){
    FILE* f = fopen("data.txt", "r");
    char buffer[250];
    DoubleLinkedList dlist;
    dlist.head = NULL;
    dlist.tail = NULL;

    while(fgets(buffer, sizeof(buffer), f)){
        Friends friend;
        char seps[] = ",\n";
        char* token = strtok(buffer, seps);

        friend.name = malloc(strlen(token) + 1);
        strcpy(friend.name, token);
        token = strtok(NULL, seps);

        friend.favActivity = malloc(strlen(token) + 1);
        strcpy(friend.favActivity, token);
        token = strtok(NULL, seps);

        friend.age = atoi(token);

        dlist = insertEnd(dlist, friend);
    }
    parse(dlist);

    printf("\nTesting:\n");
    Friends f2;
    f2.name = "The lion";
    f2.favActivity = "snorting coke";
    f2.age = 0;

    printf("\nList after inserting in the beginning (The lion):\n");
    dlist = insertBeginning(dlist, f2);
    parse(dlist);
    Friends f3;
    f3.name = "The Wolf";
    f3.favActivity = "Gooning";
    f3.age = 1;

    printf("\nList after inserting in the middle (The Wolf):\n");
    dlist = insertMiddle(dlist, f3);
    parse(dlist);

    printf("\nList after deleting first node:\n");
    dlist = deleteBeginning(dlist);
    parse(dlist);

    fclose(f);
}
