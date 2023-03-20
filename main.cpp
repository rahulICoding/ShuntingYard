//Rahul Iyer
//March 19
//shunting yard: changing equations to postfix, prefix, and infix using expression tree

#include <iostream>
#include <cstring>
#include <vector>

//node struct for stack and queue
struct Node{
  char* value;
  Node* next;
  Node(char* val){
    value = val;
    next = NULL;
  }
};

//node struct for expressions tree
struct TreeNode{
  char* value;
  TreeNode* right;
  TreeNode* left;
  TreeNode(char* val){
    value = val;
    right = NULL;
    left = NULL;
  }
};

//func prototypes
void enqueue(char* num, Node* &head);
void dequeue(Node* &head);
void push(char* operation, Node* &head);
Node* pop(Node* &sHead);
char* peek(Node* head);
int pemdas(char sign);

void postTree(Node* head, TreeNode* &root);
void postInfix(TreeNode* root);
void treePre(TreeNode* root);
void treePost(TreeNode* root);

using namespace std;

int main(){
  
  //init
  Node* queueh = NULL;
  Node* stackh = NULL;
  cout << "enter an equation with spaces between each numbers and add an equal sign" << endl;
  cout << "example: ( 3 + 4 ) / 5 =" << endl;
  char* input = new char[80];

  while(cin >> input){
    
    if(strcmp(input, "=")==0){
      break;
    }
    
    if(isdigit(input[0])){//check if char is an int
      char* intchar = strdup(input);

      //enqueue the numbers
      enqueue(intchar, queueh);
      
    }
    else if(strcmp(input, "(")== 0){//if open paren
      char* paren = strdup(input);

      //put in stack
      push(paren, stackh);
      
    }
    else if(strcmp(input, ")") == 0){//if closing paren
      Node* current = stackh;
      while(strcmp(peek(stackh), "(") !=0){//until reach open
	enqueue(pop(stackh)->value, queueh); //pop out
	
      }
      //remove open paren
      pop(stackh);
      
    }else if(isdigit(input[0]) == 0){//if op
      while((stackh !=NULL) &&//something in stack?
	    ((pemdas(stackh->value[0]) > pemdas(input[0])) ||
	     ((pemdas(stackh->value[0]) == pemdas(input[0])) && input[0] != '^')) &&
	    (stackh->value[0] != '(')){//no opening parentheses

	//remove from stack and queue
	enqueue(pop(stackh)->value, queueh);
      }
      char* op = strdup(input);
      push(op, stackh);
	   
    }
  }
  //insert op to the queue
  while(stackh != NULL){
    enqueue(pop(stackh)->value, queueh);
  }

  //create tree with the root
  TreeNode* treeRoot = NULL;
  postTree(queueh, treeRoot);

  //what do you want to change to
  char* input1 = new char[20];
  cout << "would you like to print to [infix, postfix, prefix]" << endl;
  cin >> input1;
  if(strcmp(input1, "infix") == 0){
    postInfix(treeRoot); //infix
  }
  else if(strcmp(input1, "postfix") == 0){
    treePost(treeRoot);//postfix
  }
  else if(strcmp(input1, "prefix") == 0){
    treePre(treeRoot); //prefix
  }
  else{
    cout << "try again" << endl;
  }
  return 0;
}

//convert queue to tree expression
void postTree(Node* head, TreeNode* &root){
  vector<TreeNode*> treeStack;
  Node* current = head;
  while(current != NULL){
    if(isdigit(current->value[0])){
      treeStack.push_back(new TreeNode(current->value));
    }else{
      TreeNode* newTreeNode = new TreeNode(current->value);
      newTreeNode->right = treeStack.back();
      treeStack.pop_back();
      newTreeNode->left = treeStack.back();
      treeStack.pop_back();
      treeStack.push_back(newTreeNode);
    }
    current = current->next;
  }
  root = treeStack[0];  
      
}

//tree to infix
void postInfix(TreeNode* root){
  if(root != NULL){
    if(!isdigit(root->value[0])){
      cout << "(";
    }
    postInfix(root->left);
    cout << root->value;
    postInfix(root->right);
    if(!isdigit(root->value[0])){
      cout << ")";
    }
  }

}

//tree to prefix
void treePre(TreeNode* root){
  if(root != NULL){
    cout << root->value << " "; //order values
    treePre(root->left);
    treePre(root->right);
  }
}

//tree to postfix
void treePost(TreeNode* root){
  if(root!= NULL){ //order values
    treePost(root->left);
    treePost(root->right);
    cout << root->value << " ";
    
  }
}

//finds sign order based off of pemdas
int pemdas(char sign){ //ordering based on priority
  if(sign == '-'){
    return 1;
  }else if(sign == '+'){
    return 1;
  }else if(sign == '*'){
    return 2;
  }else if(sign == '/'){
    return 2;
  }else if(sign == '^'){
    return 3;
  }
  return 5;
}

//enqueue
void enqueue(char* num, Node* &head){ 
  if(head == NULL){
    Node* newNode = new Node(strdup(num));
    head = newNode;
    return;
  }else{
    enqueue(num, head->next);
    
  }
}

//dequeue
void dequeue(Node* &head){
  Node* temp = head->next;
  delete(head);
  head = temp;
}


void push(char* operation, Node* &head){ //stack push func
  Node* newNode = new Node(strdup(operation));
  if(head == NULL){
    head = newNode;
    
  }else{
    Node* temp = head;
    newNode->next = temp;
    head = newNode;
  }
}


Node* pop(Node* &sHead){ //pop stack func
  Node* newNext = sHead->next;
  Node* moved = sHead;
  moved->next= NULL;
  sHead = newNext; //remove and pop moved
  return moved;
}


//peek function
char* peek(Node* head){ //return val
  return head->value;
}