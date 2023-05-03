
#ifndef splayTree_h
#define splayTree_h

#include <stdio.h>

typedef struct Node {
    char *key;
    char *info;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct Tree {
    Node* root;
} Tree;

Tree *treeBinaryCreate(void);
void deleteBinaryTree(Tree *tree);
int splay(Tree *tree, Node *node);

// Основные и специальные функции

int addTree(Tree *tree, char* key, char* info);
int deleteKeyTree(Tree *tree, char* key, int isDeleteTree);
Node *searchTree(Tree *tree, char *key);
Node *specialSearchTree(Tree *tree);
void printTree(Tree *tree);
void postorderTree(Tree *tree, char *string);

void paintBinaryTree(Tree *tree);

#endif 
