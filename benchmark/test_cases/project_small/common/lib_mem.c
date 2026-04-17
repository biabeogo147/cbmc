#include "lib_mem.h"
#include <stddef.h>
#include <stdlib.h>

Node* create_list(int count) {
    if (count <= 0) return NULL;
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    Node* current = head;
    for (int i = 1; i < count; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->data = i;
        node->next = NULL;
        current->next = node;
        current = node;
    }
    return head;
}

int find_sum_recursive(Node* head, int n) {
    if (head == NULL || n <= 0) return 0;
    return head->data + find_sum_recursive(head->next, n - 1);
}

void destroy_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int find_max_in_array(int* arr, int size) {
    if (arr == NULL || size <= 0) return 0;
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }
    return max_val;
}

void reverse_array(int* arr, int size) {
    if (arr == NULL || size <= 1) return;
    int left = 0, right = size - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}