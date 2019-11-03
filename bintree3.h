#define MAX 50

typedef struct node{
	char cdata;
	int idata;
	struct node* left;
	struct node* right;
	bool complete ;
};

typedef struct tree{
	struct node* root;
};

typedef struct queue{
    char data[MAX]; //priority queue array
    int front=-1;
    int rear=-1;
};

struct stack {
	char data[MAX] = {};
	int top = 0;
};

bool isEmptyqueue(queue* varq);
bool isFullqueue(queue* varq);
void enqueue (queue* varq, char add_data);
void dequeue (struct queue* varq);
void peek (queue varq[]);
bool isOperator(char varc);
struct node* insert(struct node* root, struct node* new_node);
struct tree* create (struct queue* prefix);
bool isComplete(struct tree* var_t);
void displayinfix(struct node* root);
void displayprefix(struct node* root);
void displaypostfix(struct node* root);
bool isFull(struct stack* varst);
void pushc(char newelem, struct stack* varst);
bool isEmpty(struct stack* varst);
void popc(struct stack* varst);

bool isFull(struct stack* varst){
	if (sizeof(varst->data) == varst->top)
		return (1 == 1);
	else 
		return (1 == 0);
}

void pushc(char newelem, struct stack* varst) {
	if(isFull(varst)) {
		cout<< endl  <<"STACK OVERFLOW" << endl;
		exit(0);
	}
	else {
		varst->data[varst->top] = newelem; 
		varst->top++;
	}
}

bool isEmpty(struct stack* varst) {
	if (varst->top == 0)
		return (1 == 1);
	else
		return (0==1);
}

void popc(struct stack* varst) {
	if(isEmpty(varst)) {
		cout<< endl  <<"STACK EMPTY" << endl; 
		exit(0);
	}
	else {
		varst->data[varst->top-1] = '\0';
		varst->top = varst->top-1;
	}
}

bool isEmptyqueue(queue* varq){
	return (varq->rear==-1);
}

bool isFullqueue(queue* varq){
	if ( (varq->front !=0) && (varq->rear==varq->front-1)  || ( (varq->front==0) && (varq->rear==MAX-1) ) ) {
		return ( 1==1 );
	}
	else
		return ( 0==1 );
}

void enqueue (queue* varq, char add_data) {
	if( isFullqueue(varq) ) 
		return;
    else if(varq->front==-1 && varq->rear==-1)
        {
        varq->front=varq->rear=0;
        varq->data[0] = add_data;
        }
    else if(varq->rear==MAX-1 && varq->front!=0)
        {
        varq->rear=0;
        varq->data[varq->rear] = add_data;
        }
    else
        {
        varq->rear++;
        varq->data[varq->rear] = add_data;
        }
}

void dequeue (struct queue* varq) {
	if (isEmptyqueue(varq))
		return;
	else if(varq->front!=-1 && varq->front==varq->rear) {
		varq->front=varq->rear=-1;
	}
	else {
		if(varq->front==MAX-1) {
			varq->front=0;
		}
		else {
			varq->front++;
		}
	}
}

void peek (queue varq[]) {
    if(isEmptyqueue(varq))
        {
        cout <<"\n QUEUE IS EMPTY" <<endl;
        return;
        }
    else
        {
        cout << varq->data[varq->front];
		return;
        }
}

bool isOperator(char varc){
	if(varc ==  '^' || varc ==  '*' || varc ==  '/' || varc ==  '+' || varc ==  '-' || varc ==  '%' ) {
		return ( 1==1);
	}
	else return (1==0);
}

struct node* insert(struct node* root, struct node* new_node){
	if (root == NULL) {
		root = new_node;
	}
	
	else if (root->right == NULL) {
		root->right = new_node;
	}
	
	else if (root->right->cdata != NULL &&  !root->right->complete){
		root->right = insert (root->right, new_node);
	}
	
	else if (root->right->idata != NULL && root->left == NULL) {
		root->left = new_node;
		root->complete = 1;
	}
	
	else if(root->right->complete){
		root->left = insert(root->left,new_node);
		root->complete = 1;
	}
	return root;
}

struct tree* create (struct queue* prefix){ 
	char str[MAX];
	int len, k=0, i, num;
	struct tree* var_t= (struct tree*)malloc(sizeof(struct tree));
	var_t->root = NULL;
	
	while(!isEmptyqueue(prefix) ) {
		struct node* new_node = (struct node*)malloc(sizeof(struct node));
		new_node->cdata = NULL;
		new_node->idata = NULL;
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->complete = 0;
		if (isOperator(prefix->data[prefix->front])) {
			new_node->cdata = prefix->data[prefix->front];
			dequeue(prefix);
			var_t->root = insert(var_t->root, new_node);
		}
		else {
			char c = prefix->data[prefix->front];
			char* str = &c;
			num = atoi(str);
			new_node->idata = num;
			var_t->root = insert(var_t->root, new_node);
			dequeue(prefix);
		}
	}
	//maybe make it based on a stack insead of a character array.
	return (var_t);
}

bool isComplete(struct tree* var_t){
	if(var_t->root->complete)
		return (1==1);
	else return (1 == 0);
}

void displayinfix(struct node* root){
	if(root->right != NULL) {
		if (root->complete) cout << "(" ;
		displayinfix(root->right);
	}
	if (root->idata != NULL){
		cout << root->idata;
	}
	else {
		cout << root->cdata;
	}
	if (root->left != NULL) {
		displayinfix(root->left);
		if (root->complete) cout << ")" ;
	}
}

void displayprefix(struct node* root){
	if (root->idata != NULL){
		cout << root->idata;
	}
	else {
		cout << root->cdata;
	}
	if(root->right != NULL) {
		displayprefix(root->right);
	}
	if (root->left != NULL) {
		displayprefix(root->left);
	}
}

void displaypostfix(struct node* root){
	if(root->right != NULL) {
		displaypostfix(root->right);
	}
	if (root->left != NULL) {
		displaypostfix(root->left);
	}
	if (root->idata != NULL){
		cout << root->idata;
	}
	else {
		cout << root->cdata;
	}
}

