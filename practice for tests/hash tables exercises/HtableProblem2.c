#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define HASH_TABLE_SIZE 50

struct Hotel{
    char* id;
    char* name;
    char* location;
    float rating;
    unsigned int rooms;
    float price_per_night;
};
typedef struct Hotel Hotel;

struct Node{
    Hotel data;
    struct Node* next;
};
typedef struct Node Node;

// insert node method
Node* insert_node(Node* list, Hotel data){
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

// method for hashing
unsigned int hash_function(char* key, unsigned int htable_size){
    unsigned int sum = 0;
    for(int i = 0; i < strlen(key); i++){
        sum += key[i];
    }
    return (sum % htable_size);
}

// insert data hash table
void insert_data_htable(Node** htable, unsigned int htable_size, Hotel data){
    unsigned int offset = hash_function(data.id, htable_size);
    htable[offset] = insert_node(htable[offset], data);
}

// search method
Hotel* search_hotel_data(Node** htable, unsigned int htable_size, char* id){
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
    FILE* f = fopen("HtableProblem2.txt", "r");
    Node** HTable = NULL;
    HTable = malloc(HASH_TABLE_SIZE * sizeof(Node*));
    for(unsigned int i = 0; i < HASH_TABLE_SIZE; i++){
        HTable[i] = NULL;
    }
    unsigned char buffer[200];

    while(fgets(buffer, sizeof(buffer), f)){
        Hotel hotel;
        char seps[] = ",\n";
        char* token = strtok(buffer, seps);
        hotel.id = malloc(strlen(token) + 1);
        strcpy(hotel.id, token);

        token = strtok(NULL, seps);
        hotel.name = malloc(strlen(token) + 1);
        strcpy(hotel.name, token);

        token = strtok(NULL, seps);
        hotel.location = malloc(strlen(token) + 1);
        strcpy(hotel.location, token);

        token = strtok(NULL, seps);
        hotel.rating = (float)atof(token);

        token = strtok(NULL, seps);
        hotel.rooms = atoi(token);

        token = strtok(NULL, seps);
        hotel.price_per_night = (float)atof(token);

        insert_data_htable(HTable, HASH_TABLE_SIZE, hotel);
    }

    fclose(f);

    // char* id;
    // char* name;
    // char* location;
    // float rating;
    // unsigned int rooms;
    // float price_per_night;

    Hotel* h_data = search_hotel_data(HTable, HASH_TABLE_SIZE, "1");
    if(h_data != NULL){
        printf("Hotel ID: %s\nHotel name: %s\nHotel location: %s\nHotel rating: %.1f\nHotel rooms: %u\nHotel price per night: %.2f\n", 
            h_data->id, h_data->name, h_data->location, h_data->rating, h_data->rooms, h_data->price_per_night);
    }
    else{
        printf("No such hotel in our database!");
    }

    // deallocation of hash tables
    for(unsigned int i = 0; i < HASH_TABLE_SIZE; i++){
        while(HTable[i]){
            Node* temp = HTable[i];
            HTable[i] = HTable[i]->next;
            free(temp->data.id);
            free(temp->data.name);
            free(temp->data.location);
            free(temp);
            temp = NULL;
        }
    }
    return 0;
}