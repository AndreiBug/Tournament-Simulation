#include "functions.h"
#pragma once

typedef struct BSTNode {
    Team *val;
    struct BSTNode *left, *right; 
} BSTNode;

typedef struct AVLNode {
    Team *val;
    int height;
    struct AVLNode *left, *right; 
} AVLNode;

void printLevel(AVLNode* root, FILE* output_file, int level);

void AVLinorder(AVLNode* root, FILE* output_file);

void printLevel2(AVLNode *root, FILE* output_file, int level);

//void insertBSTIntoAVL(BSTNode* root, AVLNode** AVLroot);

void inorder(BSTNode* root, FILE* output_file);

int maximum(int h1, int h2);

int nodeHeight(AVLNode *node);

BSTNode *BST_newNode(Team *data);

BSTNode *BST_insert(BSTNode *root, Team *team);

void createBSTTree(BSTNode **root, Team_list *teams);

AVLNode *createNode(Team *team);

AVLNode *rightRotation(AVLNode *z);

AVLNode *leftRotation(AVLNode *z);

AVLNode *LRRotation(AVLNode *z);

AVLNode *RLRotation(AVLNode *z);

AVLNode *AVL_insert(AVLNode *node, Team *team);

void updateScore(float *scoreOfLeftChild, float *scoreOfRightChild, AVLNode *node);

void decideRotation(AVLNode **nodePtr, int k, float scoreOfTeam, float scoreOfLeftChild, float scoreOfRightChild, Team *team);

void deleteBSTTree(BSTNode *root);

void deleteAVLTree(AVLNode *root);

