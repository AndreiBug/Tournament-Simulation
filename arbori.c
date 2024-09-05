#include "arbori.h"

void printLevel2(AVLNode *root, FILE* output_file, int currentLevel) {
    if (root == NULL) {
        return;
    }

    if (currentLevel == 2) {
        fprintf(output_file, "%s", root->val->name);
        return;  // No need to go deeper once we find nodes at level 2
    }

    printLevel2(root->right, output_file, currentLevel + 1);
    printLevel2(root->left, output_file, currentLevel + 1);
}


void insertBSTIntoAVL(BSTNode* root, AVLNode** AVLroot) {
    if (root) {
        insertBSTIntoAVL(root->right, AVLroot);  // Traverse the left subtree
        *AVLroot = AVL_insert(*AVLroot, root->val);  // Insert current node into AVL
        insertBSTIntoAVL(root->left, AVLroot); // Traverse the right subtree
    }
}

void inorder(BSTNode* root, FILE* output_file){
    if (root){
        inorder(root->right, output_file);
        char* winners_line = (char*)malloc(sizeLineWinners * sizeof(char));
        if (winners_line == NULL) {
            perror("Failed to allocate memory for winners_line");
            exit(EXIT_FAILURE);
        }
        memset(winners_line, ' ', sizeLineWinners - 1);
        winners_line[34] = '-';
        winners_line[sizeLineWinners - 1] = '\0';
        strncpy(winners_line, root->val->name, strlen(root->val->name) - 1);

        float points = calculateTeamPoints(root->val);
        char char_points[6];
        snprintf(char_points, 6, "%.2f", points);

        fprintf(output_file, "%s%s\n", winners_line, char_points);
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
    if (node == NULL) return NULL;
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
        } else if (scoreOfTeam == scoreOfLeftChild) {
            if (strcmp(node->left->val->name, team->name) > 0) {
                *nodePtr = rightRotation(node);
            }
        }
    } else if (k < -1) {
        if (scoreOfTeam > scoreOfRightChild) {
            *nodePtr = leftRotation(node);
        } else if (scoreOfTeam == scoreOfRightChild) {
            if (strcmp(node->right->val->name, team->name) < 0) {
                *nodePtr = leftRotation(node);
            }
        }
    } else if (k > 1 && scoreOfTeam > scoreOfLeftChild) {
        *nodePtr = RLRotation(node);
    } else if (k < -1 && scoreOfTeam < scoreOfRightChild) {
        *nodePtr = LRRotation(node);
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
        if (strcmp(node->val->name, team->name) > 0) {
            node->left = AVL_insert(node->left, team);
        } else if (strcmp(node->val->name, team->name) < 0) {
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

    z->height = maximum(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = maximum(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

AVLNode *leftRotation(AVLNode *z) {
    AVLNode *y = z->right;
    AVLNode *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = maximum(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = maximum(nodeHeight(y->left), nodeHeight(y->right)) + 1;
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