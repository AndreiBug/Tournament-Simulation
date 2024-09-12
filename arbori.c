#include "arbori.h"

void printLevel(AVLNode* root, FILE* output_file, int level){
    if (root != NULL){
        printLevel(root->right, output_file, level-1);
        if (level == 1) {
            fprintf(output_file,"%s\n", root->val->name);
        }
        printLevel(root->left, output_file, level-1);
    }
}

void AVLinorder(AVLNode* root, FILE* output_file){
    if (root){
        
        /*for(int i = 0; i < nodeHeight(root); i++){
            fprintf(output_file, "\t");
        }*/

        //if(nodeHeight(root) == 0) fprintf(output_file, "%s\n", root->left->left->val->name);
        //AVLinorder(root->left, output_file);
        //AVLinorder(root->right, output_file);
        //fprintf(output_file, "%d\n", root->height);
        fprintf(output_file, "%s\n", root->right->right->val->name);
        fprintf(output_file, "%s\n", root->right->left->val->name);
        fprintf(output_file, "%s\n", root->left->right->val->name);
        fprintf(output_file, "%s\n", root->left->left->val->name);
        
        
        
        
        //fprintf(output_file, "%s\n", root->val->name);
        
    }
}

/*void insertBSTIntoAVL(BSTNode* root, AVLNode** AVLroot) {
    if (root) {
        insertBSTIntoAVL(root->right, AVLroot);  // Traverse the left subtree
        *AVLroot = AVL_insert(*AVLroot, root->val);  // Insert current node into AVL
        insertBSTIntoAVL(root->left, AVLroot); // Traverse the right subtree
    }
}*/

void inorder(BSTNode* root, FILE* output_file){
    if (root){
        inorder(root->right, output_file);
        char* winners_line = (char*)malloc(sizeLineWinners * sizeof(char));
        if (winners_line == NULL) malloc_error();
        for(int i = 0; i < sizeLineWinners; i++){
                winners_line[i] = ' '; 
        }
        winners_line[34] = '-';
        winners_line[sizeLineWinners - 1] = '\0';
        strncpy(winners_line, root->val->name, strlen(root->val->name));

        float points = calculateTeamPoints(root->val);

        fprintf(output_file, "%s%.2f\n", winners_line, points);
        free(winners_line);
        inorder(root->left, output_file);
    }
}

int maximum(int h1, int h2){
    if(h1 > h2){
        return h1;
    } else {
        return h2;
    }
}

int nodeHeight(AVLNode *node) {
    if(node == NULL) {
        return -1;
    } else {
        return node->height;
    }
}

BSTNode *BST_newNode(Team *data) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
    if (newNode == NULL) return NULL;
    newNode->val = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode *BST_insert(BSTNode *root, Team *team) {
    if(root == NULL) {
        return BST_newNode(team);
    }
    float score = calculateTeamPoints(team);
    float rootScore = calculateTeamPoints(root->val);
    if(score < rootScore) {
        root->left = BST_insert(root->left, team);
    } else if(score > rootScore) {
        root->right = BST_insert(root->right, team);
    } else {
        if(strcmp(team->name, root->val->name) > 0) {
            root->right = BST_insert(root->right, team);
        } else if(strcmp(team->name, root->val->name) <  0){
            root->left = BST_insert(root->left, team);
        }
    }
    return root;
}

void createBSTTree(BSTNode **root, Team_list *teams) {
    while(teams != NULL) {
        *root = BST_insert(*root, teams->team);
        teams = teams->next;
    }
}

AVLNode *createNode(Team *team) {
    AVLNode *node = malloc(sizeof(AVLNode));
    if (node == NULL) malloc_error();
    node->val = team;
    node->height = 0;
    node->left = node->right = NULL;
    return node;
}

void updateScore(float *scoreOfLeftChild, float *scoreOfRightChild, AVLNode *node) {
    if (node->left != NULL) {
        *scoreOfLeftChild = calculateTeamPoints(node->left->val);
    } else {
        *scoreOfLeftChild = 0;
    }
    if (node->right != NULL) {
        *scoreOfRightChild = calculateTeamPoints(node->right->val);
    } else {
        *scoreOfRightChild = 0;
    }
}

void decideRotation(AVLNode **nodePtr, int k, float scoreOfTeam, float scoreOfLeftChild, float scoreOfRightChild, Team *team) {
    AVLNode *node = *nodePtr;
    if (k > 1) {
        if (scoreOfTeam < scoreOfLeftChild) {
            *nodePtr = rightRotation(node);
        } else if (scoreOfTeam > scoreOfLeftChild) {
        *nodePtr = LRRotation(node);
        } else if (scoreOfTeam == scoreOfLeftChild) {
            if (strcmp(node->left->val->name, team->name) < 0) {
                *nodePtr = rightRotation(node);
            } else if (strcmp(node->left->val->name, team->name) > 0){
                *nodePtr = LRRotation(node);
            }
        } 
    
    } else if (k < -1) {
        if (scoreOfTeam > scoreOfRightChild) {
            *nodePtr = leftRotation(node);
        } else if (k < -1 && scoreOfTeam < scoreOfRightChild) {
        *nodePtr = RLRotation(node);
        } else if (scoreOfTeam == scoreOfRightChild) {
            if (strcmp(node->right->val->name, team->name) > 0) {
                *nodePtr = leftRotation(node);
            } else if (strcmp(node->right->val->name, team->name) < 0){
                *nodePtr = RLRotation(node);
            }
        }
    }  
}

AVLNode *AVL_insert(AVLNode *node, Team *team) {
    if (node == NULL) {
        return createNode(team);
    }

    float scoreOfNode = calculateTeamPoints(node->val);
    float scoreOfTeam = calculateTeamPoints(team);

    if (scoreOfTeam < scoreOfNode) {
        node->left = AVL_insert(node->left, team);
    } else if (scoreOfTeam > scoreOfNode) {
        node->right = AVL_insert(node->right, team);
    } else {
        if (strcmp(node->val->name, team->name) < 0) {
            node->left = AVL_insert(node->left, team);
        } else if (strcmp(node->val->name, team->name) > 0) {
            node->right = AVL_insert(node->right, team);
        }
    }

    node->height = 1 + maximum(nodeHeight(node->left), nodeHeight(node->right));
    int k = nodeHeight(node->left) - nodeHeight(node->right);
    
    float scoreOfLeftChild, scoreOfRightChild;
    updateScore(&scoreOfLeftChild, &scoreOfRightChild, node);

    decideRotation(&node, k, scoreOfTeam, scoreOfLeftChild, scoreOfRightChild, team);

    return node;
}

AVLNode *rightRotation(AVLNode *z) {
    AVLNode *y = z->left;
    AVLNode *T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = (maximum(nodeHeight(z->left), nodeHeight(z->right))) + 1;
    y->height = (maximum(nodeHeight(y->left), nodeHeight(y->right))) + 1;
    return y;
}

AVLNode *leftRotation(AVLNode *z) {
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = (maximum(nodeHeight(z->left), nodeHeight(z->right))) + 1;
    y->height = (maximum(nodeHeight(y->left), nodeHeight(y->right))) + 1;
    return y;
}

AVLNode *LRRotation(AVLNode *z) {
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

AVLNode *RLRotation(AVLNode *z) {
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

void deleteBSTTree(BSTNode *root) {
    if(root) {
        deleteBSTTree(root->left);
        deleteBSTTree(root->right);
        free(root);
    }
}

void deleteAVLTree(AVLNode *root) {
    if(root) {
        deleteAVLTree(root->left);
        deleteAVLTree(root->right);
        free(root);
    }
}