#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

// Iterative insertion in the Binary Search Tree
Node* iterativeInsert(Node* root, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;

    if (root == NULL) {
        root = newNode;
    } else {
        Node* temp = root;
        Node* parent;

        while (temp != NULL) {
            parent = temp;
            if (key < temp->key) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }

        if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    return root;
}

// Recursive insertion in the Binary Search Tree
Node* recursiveInsert(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->key) {
        root->left = recursiveInsert(root->left, key);
    } else if (key > root->key) {
        root->right = recursiveInsert(root->right, key);
    }

    return root;
}

// Inorder traversal of the Binary Search Tree
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    Node* root1 = NULL;
    int arrays[][6] = {{10, 5, 15, 3, 7, 18}, {20, 10, 30, 5, 15, 35}, {30, 20, 40, 10, 25, 45}, {40, 30, 50, 20, 35, 55}, {50, 40, 60, 30, 45, 65}, {60, 50, 70, 40, 55, 75}};

    for (int i = 0; i < 6; i++) {
        root = NULL;
        root1 = NULL; 
        clock_t start = clock();
        for (int j = 0; j < 6; j++) {
            root = iterativeInsert(root, arrays[i][j]);
            root1 = recursiveInsert(root1, arrays[i][j]);
        }
        clock_t end = clock();
        double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("Array %d: \n", i + 1);
        printf("Iterative Insertion: %d", i + 1);
        inorder(root);
        printf("\nTime taken: %f seconds", time_taken);

        clock_t start1 = clock();
        for (int j = 0; j < 6; j++) {
            root1 = recursiveInsert(root1, arrays[i][j]);
        }
        clock_t end1 = clock();
        double time_taken1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;

        printf("\nRecursive Insertion: %d", i + 1);
        inorder(root);
        printf("\nTime taken: %f seconds\n\n", time_taken1);
    }
    return 0;
}