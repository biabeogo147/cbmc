#ifndef LIB_MEM_H
#define LIB_MEM_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_list(int count);
int find_sum_recursive(Node* head, int n);
void destroy_list(Node* head);
int find_max_in_array(int* arr, int size);
void reverse_array(int* arr, int size);

#endif