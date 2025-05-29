#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define NUMBER_OF_STUDENTS 5

struct Student{
    char* name;
    char* id;
    float gpa;
};
typedef struct Student Student;

struct BSTNode{
    Student data;
    struct BSTNode* left;
    struct BSTNode* right;
};
typedef struct BSTNode BSTNode;

// insert method
BSTNode* insert_node(BSTNode* node, Student data, unsigned char* success_flag){
    if(node != NULL){
        if(strcmp(data.id, node->data.id) < 0){
            node->left = insert_node(node->left, data, success_flag);
        }
        else{
            if(strcmp(data.id, node->data.id) > 0){
                node->right = insert_node(node->right, data, success_flag);
            }
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

//in order parsing
void in_order_parsing(BSTNode* node){
    if(node != NULL){
        in_order_parsing(node->left);
        printf("Student name: %s\nStudent ID: %s\nStudent GPA: %.2f\n", node->data.name, node->data.id, node->data.gpa);
        in_order_parsing(node->right);
    }
}

//post order parsign
void post_order_parsing(BSTNode* node){
    if(node != NULL){
        post_order_parsing(node->left);
        post_order_parsing(node->right);
        printf("Student name: %s\nStudent ID: %s\nStudent GPA: %.2f\n", node->data.name, node->data.id, node->data.gpa);
    }
}

//searching
Student* search_BST(BSTNode* node, char* id){
    if(node != NULL){
        if(strcmp(id, node->data.id) == 0){
            return &(node->data);
        }
        else if(strcmp(id, node->data.id) < 0){
            return search_BST(node->left, id);
        }
        else{
            return search_BST(node->right, id);
        }
    }
    return NULL;
}

//deallocate method (post order)
BSTNode* deallocate_BST_post_order(BSTNode* node){
    if(node != NULL){
        node->left = deallocate_BST_post_order(node->left);
        node->right = deallocate_BST_post_order(node->right);
        printf("Student with ID: %s is deallocating!\n", node->data.id);
        free(node->data.name);
        free(node->data.id);
        free(node);
        node = NULL;
    }
}

//deallocate method (in order)
BSTNode* deallocate_BST_in_order(BSTNode* node){
    if(node != NULL){
        node->left = deallocate_BST_in_order(node->left);
        printf("Student with ID: %s is deallocating!\n", node->data.id);
        node->right = deallocate_BST_in_order(node->right);
        free(node->data.name);
        free(node->data.id);
        free(node);
        node = NULL;
    }
}

//count nodes on a certain level
unsigned char count_nodes_level_with_return(BSTNode* node, unsigned char target_level){
    if(node != NULL){
        if(target_level > 0){
            if(target_level == 1){
                return 1;
            }
            else{
                return count_nodes_level_with_return(node->left, target_level - 1) +
                       count_nodes_level_with_return(node->right, target_level - 1);
            }
        }
    }
    return 0;
}

//calculate average GPA
float get_student_by_id(BSTNode* node, char* id){
    if(node != NULL){
        if(strcmp(id, node->data.id) == 0){
            return node->data.gpa;
        }
        else if(strcmp(id, node->data.id) < 0){
            return get_student_by_id(node->left, id);
        }
        else{
            return get_student_by_id(node->right, id); 
        }
    }
    return -1.0f;
}

float calculate_average_GPA(BSTNode* node, char* student_ids[NUMBER_OF_STUDENTS]){
    float sum = 0;
    for(int i = 0; i < NUMBER_OF_STUDENTS; i++){
        sum += get_student_by_id(node, student_ids[i]);
    }
    return sum / NUMBER_OF_STUDENTS;
}

int main(){
    FILE* f = fopen("student.txt", "r");
    BSTNode* root = NULL;
    unsigned char buffer[200];

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

        unsigned char success_flag;
        root = insert_node(root, stud, &success_flag);

        if(success_flag != 0){
            printf("Student with id: %s has been successfully inserted!\n", stud.id);
        }
        else{
            printf("Student has NOT been inserted into BST!\n");
            free(stud.name);
            free(stud.id);
        }
    }
    fclose(f);

    post_order_parsing(root);
    printf("Getting a student by id:\n");
    
    char* student_ids[NUMBER_OF_STUDENTS] = {"1001394", "1039485", "3001567", "2101397", "235605"};
    float avg_gpa = calculate_average_GPA(root, student_ids);
    printf("Average GPA: %.2f", avg_gpa);
}