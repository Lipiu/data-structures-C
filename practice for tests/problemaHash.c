#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Book{
    unsigned int id;
    char* title; 
    char* author;
    char* genre;
    float price;
};
typedef struct Book Book;

struct BSTNode{
    Book data;
    struct BSTNode* left;
    struct BSTNode* right;
};
typedef struct BSTNode BSTNode;

// in order traversal
void in_order_traversal(BSTNode* root){
    if(root){
        in_order_traversal(root->left);
        printf("ID: %u\nTitle: %s\nAuthor: %s\nGenre: %s\nPrice: %.2f\n\n", 
            root->data.id, root->data.title, root->data.author, root->data.genre, root->data.price);
        in_order_traversal(root->right);
    }
}

// insertion
BSTNode* insert_node(BSTNode* node, Book data, unsigned char* success_flag){
    if(node != NULL){
        // insert left
        if(data.id < node->data.id){
            node->left = insert_node(node->left, data, success_flag);
        }
        // insert right
        else{
            if(data.id > node->data.id){
                node->right = insert_node(node->right, data, success_flag);
            }
            // duplicate
            else{
                *success_flag = 0;
            }
        }
    }
    else{
        BSTNode* new_node = malloc(sizeof(BSTNode));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;

        *success_flag = 1;
        return new_node;
    }
}

// searching
BSTNode* search_BST(BSTNode* node, unsigned int id){
    if(node != NULL){
        if(id == node->data.id){
            return &(node->data);
        }
        else if(id < node->data.id){
            return search_BST(node->left, id);
        }
        else{
            return search_BST(node->right, id);
        }
    }
    return NULL;
}

// get book by id
float get_book_price_by_id(BSTNode* node, unsigned int id){
    if(node != NULL){
        if(id == node->data.id){
            return node->data.price;
        }
        else if(id < node->data.id){
            return get_book_price_by_id(node->left, id);
        }
        else{
            return get_book_price_by_id(node->right, id);
        }
    }
    return 0.0f; // id not found
}

// calculate average
float calculate_average_price(BSTNode* node, unsigned int book_ids[3]){
    float sum = 0;
    for(int i = 0; i < 3; i++){
        sum += get_book_price_by_id(node, book_ids[i]);
    }
    float number_of_orders = 3;
    return sum / number_of_orders;
}

// deallocation
BSTNode* deallocate(BSTNode* node){
    if(node != NULL){
        deallocate(node->left);
        deallocate(node->right);

        printf("Book with id: %u is being deallocated\n", node->data.id);
        free(node->data.title);
        free(node->data.author);
        free(node->data.genre);
        free(node);
        node = NULL;
    }
}

int main(){
    FILE* f = fopen("bookData.txt", "r");
    BSTNode* root = NULL;
    unsigned char buffer[200];

    while(fgets(buffer, sizeof(buffer), f)){
        Book book;
        char seps[] = ",\n";
        char* token = strtok(buffer, seps);
        book.id = atoi(token);

        token = strtok(NULL, seps);
        book.title = malloc(strlen(token) + 1);
        strcpy(book.title, token);

        token = strtok(NULL, seps);
        book.author = malloc(strlen(token) + 1);
        strcpy(book.author, token);

        token = strtok(NULL, seps);
        book.genre = malloc(strlen(token) + 1);
        strcpy(book.genre, token);

        token = strtok(NULL,seps);
        book.price = (float)atof(token);

        unsigned char insert_flag;
        root = insert_node(root, book, &insert_flag);
        
        if(insert_flag != 0){
            printf("Order with id %u has been successfully inserted!\n", book.id);
        }
        else{
            printf("Book with id: %u has NOT been inserted!\n", book.id);
            free(book.title);
            free(book.author);
            free(book.genre);
        }
    }
    fclose(f);

    in_order_traversal(root);
    
    unsigned int target_book_ids[3] = {101,102,103};
    float average = calculate_average_price(root, target_book_ids);
    printf("Average of books with ids: [%u, %u, %u] is %.2f\n", target_book_ids[0], target_book_ids[1],target_book_ids[2], average);

    printf("\nBST deallocation started!\n");
    root = deallocate(root);
    printf("BST after deallocation:\n");
    in_order_traversal(root);
}