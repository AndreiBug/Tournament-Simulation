#pragma once
#include <limits.h>
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    Team* val;
    struct StackNode* next;
} StackNode;

Team* top(StackNode *top);

Team *pop(StackNode** top);

void push(StackNode**top, Team *v);

int isStackEmpty(StackNode *top);

void deleteStack(StackNode **top);