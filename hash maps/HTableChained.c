#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

// defining constants
#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY
#define HASH_TABLE_SIZE 50

struct BankCard{
    char* holder;
    char card_no[CARD_NUMBER_LENGTH];
    float balance;
    char exp_date[EXPIRING_DATE_FORMAT_LENGTH];
    char* currency;
};
typedef struct BankCard BankCard;

struct Node{
    BankCard data;
    struct Node* next;
};
typedef struct Node Node;

// insert node method
Node* insert_node(Node* list, BankCard bc){
    Node* temp = list;
    if(temp != NULL){
        while(temp->next != NULL){
            temp = temp->next;
        }
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->data = bc;
    new_node->next = NULL;

    if(temp != NULL){
        //there is one single node at least
        // temp is the last node in the list
        temp->next = new_node;
        return list;
    }
    else{
        return new_node;
    }
}

// hashing method
unsigned int hash_function(char* key, unsigned int htable_size){
    unsigned int sum = 0;
    for(unsigned int i = 0; i < strlen(key); i++){
        // sum up the ASCII values of each character in the input string key
        sum += key[i];
    }
    // take the remainder of dividing that sum by the size of the hash table (htable_size)
    // the return value is an index suitable for placing the key in a hash table
    return (sum % htable_size);
}

// insert data into hashtable
void insert_data_htable(Node** htable, unsigned int htable_size, BankCard data){
    // 1. call the hash function to get the offset of the simple list where data will be insterted into
    unsigned int offset = hash_function(data.card_no, htable_size);

    // 2. insert the data in the list established at 1
    htable[offset] = insert_node(htable[offset], data);
}

BankCard* search_card_data(Node** htable, unsigned int htable_size, char* card_number){
    // 1. call the hash function to get the simple list where data should be stored
    unsigned int offset = hash_function(card_number, htable_size);

    // 2. compare the card_number with each card_no stored in the nodes of the simple list
    Node* temp = htable[offset];
    while(temp != NULL){
        if(strcmp(card_number, temp->data.card_no) == 0)
            return &(temp->data);
        temp = temp->next;
    }
    return NULL;
}

// create array of card data for a currency specified as paramater of the function
BankCard* new_array(Node** hash_table, unsigned int size, char* currency, unsigned int* no_matches){
    *no_matches = 0;
    for(unsigned int i = 0; i < size; i++){
        Node* temp = hash_table[i];
        while(temp){
            if(strcmp(temp->data.currency, currency) == 0)
                *no_matches += 1;
            temp = temp->next;
        }
    }

    if(*no_matches > 0){
        BankCard* new_verified_array = malloc(sizeof(BankCard) * *no_matches);
        unsigned int temp_index = 0;
        for(unsigned int i = 0; i < size; i++){
            Node* temp = hash_table[i];
            while(temp){
                if(strcmp(temp->data.currency, currency) == 0){
                    new_verified_array[temp_index] = temp->data;
                    temp_index += 1;
                }
                temp = temp->next;
            }
        }
        return new_verified_array;
    }
    else{
        return NULL;
    }
}

int main(){
    FILE* f = fopen("data.txt", "r");
    Node** HTable = NULL; // hash table support as array of simple linked lists
    HTable = malloc(HASH_TABLE_SIZE * sizeof(Node*)); // allocation of the array as support for the hash table
    for(unsigned int i = 0; i < HASH_TABLE_SIZE; i++){
        HTable[i] = NULL; // each simple list HTable[i] is marked as null/empty list
    }

    unsigned char buffer[200];
    while(fgets(buffer, sizeof(buffer), f)){
        BankCard card;
        char seps[] = ",\n";
        
        char* token = strtok(buffer, seps);
        strcpy(card.card_no, token);

        token = strtok(NULL, seps);
        card.holder = malloc(strlen(token) + 1);
        strcpy(card.holder, token);

        token = strtok(NULL, seps);
        card.currency = malloc(strlen(token) + 1);
        strcpy(card.currency, token);

        token = strtok(NULL, seps);
        card.balance = (float)atof(token);

        token = strtok(NULL, seps);
        strcpy(card.exp_date, token);

        insert_data_htable(HTable, HASH_TABLE_SIZE, card);
    }
    fclose(f);

    BankCard* p_data = search_card_data(HTable, HASH_TABLE_SIZE, "6523667711220099");
	if (p_data != NULL)
	{
		printf("Card data info: %s %s\n", p_data->holder, p_data->card_no);
	}
	else
	{
		printf("The card data does not exist in hash table.\n");
	}
	unsigned int temp_size;
	BankCard* card_array = new_array(HTable, HASH_TABLE_SIZE, "Romanian Leu", &temp_size);

	
	printf("Array of Card Data with same currency: \n");
	for (unsigned int i = 0; i < temp_size; i++) {
		printf("Card data info: %s %s\n", card_array[i].card_no, card_array[i].currency);
	}

	//Deallocation of the hashtable.
	for (unsigned int i = 0; i < HASH_TABLE_SIZE; i++) {
		while (HTable[i]) {
			Node* temp = HTable[i];
			HTable[i] = HTable[i]->next;
			free(temp->data.currency);
			free(temp->data.holder);
			free(temp);
		}
	}
	//Deallocation of card_array.
	free(card_array);

	return 0;
}