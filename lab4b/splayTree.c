#include "splayTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Tree *treeBinaryCreate(void) {
    Tree *tree = calloc(1, sizeof(Tree));
    tree->root = NULL;
    return tree;
}

// Поиск

Node *searchTree(Tree *tree, char* key) {
    if(!tree) {
        return NULL;
    }
    Node *node = tree->root;
    while (node && strcmp(key, node->key)) {
        if(strcmp(key, node->key) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if(node) {
        splay(tree, node);
    }
    paintBinaryTree(tree);
    return node;
}

// Добавление

int addTree(Tree *tree, char *key, char *info) {
    if(!key) {
        if(info) {
            free(info);
        }
        return 2;
    }
    
    if(!info) {
        free(key);
        return 3;
    }
    
    Node *node = tree->root;
    Node *newnode = NULL;
    Node *place = NULL;
    
    if(searchTree(tree, key)) {
        free(key);
        free(info);
        return 1;
    } else {
        newnode = calloc(1, sizeof(Node));
        newnode->key = key;
        newnode->info = info;
        newnode->parent = NULL;
        newnode->left = NULL;
        newnode->right = NULL;
        
        while (node) {
            place = node;
            if(strcmp(key, node->key) < 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            
        }
        
        if(tree->root == NULL) {
            newnode->parent = NULL;
            tree->root = newnode;
        } else {
            
            newnode->parent = place;
            if(strcmp(key, place->key) < 0) {
                place->left = newnode;
            } else {
                place->right = newnode;
            }
        }
    }
    splay(tree, newnode);
    paintBinaryTree(tree);
    return 0;
}

// Поворот
    
void rotate(Tree *tree, Node *node) {
    Node* parent = node->parent;
    Node* grandParent = NULL;
    
    if(parent->left == node) {
        parent->left = node->right;
        if(node->right) {
            node->right->parent = parent;
        }
        node->right = parent;
    } else {
        parent->right = node->left;
        if(node->left) {
            node->left->parent = parent;
        }
        node->left = parent;
    }
    
    if(parent->parent == NULL) {
        node->parent = NULL;
        tree->root = node;
    } else {
        grandParent = node->parent->parent;
        node->parent = grandParent;
        if(grandParent->left == parent) {
            grandParent->left = node;
        } else {
            grandParent->right = node;
        }
    }
    parent->parent = node;
    
}

// Splay
    
int splay(Tree *tree, Node *node) {
    Node* parent = NULL;
    if(node == tree->root) {
        return 0;
    }
    while (node != tree->root) {
        if(node->parent == tree->root) {
            rotate(tree, node);
            continue;
        }
        parent = node->parent;
        if(node->parent->left == node) {
            if(node->parent->parent->left == node->parent) {
                rotate(tree, node->parent);
                rotate(tree, node);
            } else {
                rotate(tree, node);
                rotate(tree, node);
            }
        } else {
            if(node->parent->parent->left == node->parent) {
                rotate(tree, node);
                rotate(tree, node);
            } else {
                rotate(tree, node->parent);
                rotate(tree, node);
            }
        }
    }
    return 0;
}

// Печать
    
int depthN(Tree *tree, Node *node) {
    int depth = 0;
    Node *start = tree->root;
    if(start == node) {
        return 0;
    }
    while (start != node) {
        
        if(strcmp(node->key, start->key) < 0) {
            start = start->left;
            depth++;
        } else {
            start = start->right;
            depth++;
        }
        
    }
    return depth;
}

void printElement(Node *node, int *i, int *lr, Tree *tree) {
    if(node){
        *i = *i + 4;
        printElement(node->right, i, lr, tree);
        
        for (int b = 0; b < depthN(tree, node)*4; b++) {
            printf(" ");
        }
        
        printf("|- %s\n", node->key);
        printElement(node->left, i, lr, tree);
        
        *i = *i - 4;
    }
}

void printTree(Tree *tree) {
    if(tree) {
        int i = -4;
        int lr = 0;
        if(tree->root != NULL) {
            printElement(tree->root, &i, &lr, tree);
        }
    }
}

Node *findNext(Node *node) {
    if(node->right) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    return node;
}

int deleteKeyTree(Tree *tree, char* key, int isDeleteTree) {
    
    if(!tree) {
        return 1;
    }
    
    if(!key) {
        return 1;
    }
    Node *node = tree->root;
    Node *prev = NULL;
    Node *delNode = NULL;
    char* keySwap;
    
    while (node) {
        if(!strcmp(node->key, key)) {
            break;
        }
        prev = node;
        if(strcmp(key, node->key) < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    
    if(!node) {
        return 1;
    }
    
    if(node->left != NULL && node->right != NULL) {
        
        delNode = findNext(node);
        keySwap = strdup(delNode->key);
        free(node->info);
        node->info = NULL;
        node->info = strdup(delNode->info);
        deleteKeyTree(tree, delNode->key, isDeleteTree);
        free(node->key);
        node->key = NULL;
        node->key = keySwap;
        
        if(isDeleteTree == 0) {
            paintBinaryTree(tree);
        }
        
        return 0;
    }
    
    if(node->left == NULL || node->right == NULL) {
        if(tree->root == node) {
            if(node->left) {
                tree->root = node->left;
            } else if(node->right) {
                tree->root = node->right;
            } else {
                tree->root = NULL;
            }
            node->parent = NULL;
            
        } else if(prev->left == node) {
            if(node->left) {
                prev->left = node->left;
                if(node->left) {
                    node->left->parent = prev;
                }
            } else {
                prev->left = node->right;
                if(node->right) {
                    node->right->parent = prev;
                }
            }
        } else {
            if(node->left) {
                prev->right = node->left;
                if(node->left) {
                    node->left->parent = prev;
                }
            } else {
                prev->right = node->right;
                if(node->right) {
                    node->right->parent = prev;
                }
            }
        }
        
        free(node->key);
        free(node->info);
        free(node);
        
        if(isDeleteTree == 0) {
            paintBinaryTree(tree);
        }
        return 0;
    }
    
    return 1;
}

Node *specialSearchTree(Tree *tree) {
    Node *node = tree->root;
    Node *res = NULL;
    while (node) {
        res = node;
        node = node->left;
    }
    if(res) {
        splay(tree, res);
    }
    paintBinaryTree(tree);
    return res;
}

int checkString(char *first, char *second) {
    if(!first) {
        if(second){
            free(second);
        }
        return 1;
    }
    
    if(!second) {
        if(first){
            free(first);
        }
        return 1;
    }
    
    
    int flag = 0;
    if(strlen(second) < strlen(first)) {
        return 2;
    } else {
        for (int i = 0; i < strlen(first); i++) {
            if(first[i] != second[i]){
                flag++;
                break;
            }
        }
    }
    
    if(flag) {
        return 2;
    } else {
        return 0;
    }
    
}

void postorderIn(Node *node, char* string) {
    if(node) {
        postorderIn(node->left, string);
        postorderIn(node->right, string);
        if(!checkString(string, node->key)) {
            printf("key - %s, info - %s |", node->key, node->info);
        }
    }
}

void postorderTree(Tree *tree, char *string) {
    if(string) {
        if(tree) {
            postorderIn(tree->root, string);
        }
    }
}

// Graphviz

void preorderPaintPrint(Node *node, FILE *file) {
    if(node) {
        
        fprintf(file, "%s [shape=record,label = \"%s |{%s}\"]\n", node->key, node->key, node->info);
        
        preorderPaintPrint(node->left, file);
        preorderPaintPrint(node->right, file);
    }
}

void paintPrint(Node *node, FILE *file) {
    if(node) {
        if(node->left) {
            fprintf(file, "%s", node->key);
            fprintf(file, ":sw->%s;\n", node->left->key);
        }
        if(node->right){
            fprintf(file, "%s", node->key);
            fprintf(file, ":se->%s;\n", node->right->key);
        }
        paintPrint(node->left, file);
        paintPrint(node->right, file);
    }
}

void paintBinaryTree(Tree *tree) {
    FILE *file = fopen("test.dot", "w");
    fprintf(file, "digraph G {\n");
    if(tree) {
        preorderPaintPrint(tree->root, file);
        paintPrint(tree->root, file);
    }
    fprintf(file, "}");
    fclose(file);
}

void deleteBinaryTree(Tree *tree) {
    while (tree->root) {
        deleteKeyTree(tree, tree->root->key, 1);
    }
    free(tree);
}
