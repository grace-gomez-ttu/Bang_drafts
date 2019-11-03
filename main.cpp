#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <iostream>
#include <fstream> 
#include <string.h>

using namespace std;

#include "bintree3.h"

struct queue* prefix(char[], struct queue*);
bool isBalanced(char array[MAX]);
int math( int a, int b, char opr);
struct node* compute(struct node* root);
//struct queue* prefix(char array[MAX], struct queue* theprefix);

int main() {
	struct stack temp;
	temp.top = 0;
	struct stack* theprefix = &temp;
	theprefix->top = 0;
	
	struct queue tempq;
	struct queue* theprefixq = &tempq;
	theprefixq->front = -1;
	theprefixq->rear = -1;
	
	char index[MAX] = {'*',  '+',  '1',  '2', '-', '7', '5'};
	
	for (int i = 0; index[i] != '\0'; i++ ) {
		enqueue(theprefixq,index[i]);
	}
	//struct queue temp;
	//struct queue* theprefix = &temp;
	//theprefix->front = -1;
	//theprefix->rear = -1;
	//struct queue* prefixstack = (prefix(infix, theprefix));
	struct tree* donetree = create(theprefixq);
	 cout << "\nInfix: ";
	 displayinfix(donetree->root);
	  cout << "\nPostfix: ";
	 displaypostfix(donetree->root);
	  cout << "\nPrefix: ";
	 displayprefix(donetree->root);
	 
	 struct node* eval = compute(donetree->root);
	 cout << "\n The evaluation of this is " << eval->idata;
	 
}

bool isBalanced(char array[MAX]) {
	int i;
	struct stack balstack;
	struct stack* bstack = &balstack;
	bstack->top = 0;
	for(i = 0; array[i] != '\0' ;i++) {
		if ( array[i] == '{' || array[i] == '[' || array[i] == '(') {
			pushc(array[i], bstack);
		}
		//print_arraystack();
		if ( array[i] == '}') {
			if (bstack->data[bstack->top] == '{') {
				popc(bstack);
			}
			else {
				cout << "Not Balanced\n" ;
				return (bstack->top == '{');
			}
		}
		else if ( array[i] == ']') {
			if (bstack->data[bstack->top] == '[') {
				popc(bstack);
			}
			else {
				cout << "Not Balanced\n" ;
				return (bstack->top == '[');
			}
		}
		else if ( array[i] == ')') {
			if (bstack->data[bstack->top] == '(') {
				popc(bstack);
			}
			else {
				cout << "Not Balanced\n" ;
				return (bstack->top == '(');
			}
		}
	}
	if (isEmpty(bstack)) cout << "Is balanced\n" ;
	else { 
		cout << "Not Balanced\n" ; 
		return (0 == 1) ; }
	return (1 == 1);
}

struct node* compute(struct node* root) {
	if (isOperator(root->right->cdata))
		compute(root->right);
	if (isOperator(root->left->cdata))
		compute(root->left);
	if ( (!isOperator(root->right->cdata) && !isOperator(root->left->cdata))) {
		root->idata = math(root->right->idata, root->left->idata, root->cdata);
		root->right = root->left = NULL;
		root->cdata = NULL;
	}
	return root;
}

int math( int a, int b, char opr) {
	int var;
	if (opr == '+' ) var = 1;
	else if (opr == '-' ) var = 2;
	else if (opr == '*' ) var = 3;
	else if (opr == '/' ) var = 4;
	else if (opr == '^' ) var = 5;
	else if (opr == '%' ) var = 6;
	switch(var) {
		case 1: 
			return (a+b); 
			break;
		case 2:
			return (a-b);
			break;
		case 3:
			return (a*b);
			break;
		case 4:
			return (a/b);
			break;
		case 5:
			return (a^b);
			break;
		case 6:
			return (a%b);
			break;
	}
}