#include <iostream>
#include <cstring>
#include <vector>


struct Node{
  char* value;
  Node* next;
  Node(char* newVal){
    value = newVal;
    next = NULL;
  }
};


using namespace std;

int main(){

  return 0;
}





//enqueues
void enqueue(char* num, Node* &head){
  if(head == NULL){
    Node* newNode = new Node(strdup(num));
    head = newNode;
    return;
  }else{
    enqueue(num, head->next);
    
  }
}

//dequeues
void dequeue(Node* &head){
  Node* temp = head->next;
  delete(head);
  head = temp;
}

//push function into a stack
void push(char* operation, Node* &head){

}

//pop function for a stack
Node* pop(Node* &sHead){

}


//peek function
char* peek(Node* head){
  return head->value;
}