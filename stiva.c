#include "stiva.h"

Team *pop(StackNode** top){
StackNode *temp = (*top);
Team *aux = temp->val;
*top=(*top)->next; 
free (temp);
return aux;
}

Team *top(StackNode *top){
	return top->val;
} 

void push(StackNode **top, Team *v) {
	StackNode *newNode = malloc(sizeof(StackNode));
	newNode->val = v;
	newNode->next = *top;
	*top = newNode;
}

int isStackEmpty(StackNode *top){
	return top == NULL;
}
	
void deleteStack(StackNode **top){
	StackNode *temp;
	while (!isStackEmpty(*top)) {
		temp = *top;
		*top = (*top)->next;
		free(temp);
	}
}