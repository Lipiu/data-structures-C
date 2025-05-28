#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DATE_FORMAT 5 // eg: 28/05 -> 4 characters for numbers and 1 for "/"

// define the command structure (comanda is order)
struct Comanda{
    unsigned int id;
    char* launch_date;
    char* delivery_date;
    char* client_name;
    float order_price;
};
typedef struct Comanda Comanda;

// define the node structure
struct BSTNode{
    Comanda data;
    struct BSTNode* left;
    struct BSTNode* right;
};
typedef struct BSTNode BSTNode;

// post order traversal
void post_order_traversal(BSTNode* root){
    if(root){
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf("ID: %u\nLaunch date: %s\nDelivery date: %s\nClient name: %s\nOrder price: %.2f\n\n", 
            root->data.id, root->data.launch_date, root->data.delivery_date, root->data.client_name, root->data.order_price);
    }
}

// insert node into BST
// for key we use the id of the order
BSTNode* insert_node(BSTNode* node, Comanda data, unsigned char* succes_flag){
    if(node != NULL){
        // if < 0 we insert left
        if(data.id < node->data.id){
            node->left = insert_node(node->left, data, succes_flag);
        }
        // if > 0 insert right
        else{
            if(data.id > node->data.id){
                node->right = insert_node(node->right, data, succes_flag);
            }
            // means we have a duplicate key in our BST
            // so we drop off the insertion
            else{
                *succes_flag = 0;
            }
        }
    }
    else{
        //create the new node to be inserted
        BSTNode* new_node = malloc(sizeof(BSTNode));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;

        *succes_flag = 1;
        return new_node;
    }
}

// method to get order value (price) by id
float get_order_value_by_id(BSTNode* node, unsigned int id){
    if(node != NULL){
        if(node->data.id == id){
            return node->data.order_price;
        }
        else if(id < node->data.id){
            return get_order_value_by_id(node->left, id);
        }
        else{
            return get_order_value_by_id(node->right, id);
        }
    }
}

// calculate the price
float calculate_avg_price(BSTNode* node, unsigned int order_ids[3]){ //because we are asked to only work with 3 orders
    float sum = 0;
    for(int i = 0; i < 3; i++){
        sum += get_order_value_by_id(node, order_ids[i]);
    }
    // constant number of orders
    float number_of_orders = 3;
    return sum / number_of_orders;
}

// deallocation method (post order)
BSTNode* deallocate_BST_postorder(BSTNode* node){
    if(node != NULL){
        deallocate_BST_postorder(node->left);
        deallocate_BST_postorder(node->right);

        printf("Order with id:%u is deallocating\n", node->data.id);
        free(node->data.launch_date);
        free(node->data.delivery_date);
        free(node->data.client_name);
        free(node);
        node = NULL;
    }
    return node;
}

int main(){
    FILE* f = fopen("dataBST.txt", "r");
    BSTNode* root = NULL;
    unsigned char buffer[200];

    // unsigned int id;
    // char* launch_date;
    // char* delivery_date;
    // char* client_name;
    // float order_price;

    while(fgets(buffer, sizeof(buffer), f)){
        Comanda order;
        char seps[] = ",\n";
        char* token = strtok(buffer, seps);
        order.id = atoi(token);

        token = strtok(NULL, seps);
        order.launch_date = malloc(strlen(token) + 1);
        strcpy(order.launch_date, token);

        token = strtok(NULL, seps);
        order.delivery_date = malloc(strlen(token) + 1);
        strcpy(order.delivery_date, token);

        token = strtok(NULL, seps);
        order.client_name = malloc(strlen(token) + 1);
        strcpy(order.client_name, token);

        token = strtok(NULL, seps);
        order.order_price = (float)atof(token);

        unsigned char insert_flag;
        root = insert_node(root, order, &insert_flag);

        if(insert_flag != 0){
            printf("Order with id: %u has been inserted!\n", order.id);
        }
        else{
            printf("No order with specified id!");
            free(order.launch_date);
            free(order.delivery_date);
            free(order.client_name);
        }
    }
    fclose(f);

    //should display orders with ids: 1,2,3,4,5
    post_order_traversal(root);

    printf("\nCalculating the average of 3 orders:\n");
    
    //testing calculate average
    unsigned int target_order_ids[3] = {1,2,3};
    float average = calculate_avg_price(root, target_order_ids);
    printf("Average value for orders with ID: {%u, %u, %u} is: %.2f\n", 
        target_order_ids[0], target_order_ids[1], target_order_ids[2], average);

    // deallocation
    printf("\nBST deallocation just started:\n");
    root = deallocate_BST_postorder(root);
    printf("BST after deallocation");
    post_order_traversal(root);
}