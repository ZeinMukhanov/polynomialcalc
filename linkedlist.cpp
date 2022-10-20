#include <iostream>
#include "linkedlist.h"
using namespace std;

LinkedList::LinkedList () //constructor
{
    this->head = NULL;
}

void LinkedList::insert(int coef,int expo) {  
  Node* node = new Node(coef, expo); //inserting a new term of the polynomial expression into the linked list
  if ((this->head == nullptr)|| (node->expo > this->head->expo))
  {
    node->next = this->head;
    this->head = node;
    return;
  }
  
  Node* ptr = this->head; //pointer to the head of the node
  while(ptr->next) 
    {
      if (ptr->next->expo > node->expo)  //the case when the exponent of the first list is greater than that of the second
      {
        ptr = ptr->next;
      }
      else if (ptr->next->expo == node->expo) //the case when exponents of two terms are the same
      {
        ptr->next->coef = ptr->next->coef + node->coef; //merge two terms into one by adding their coefficients
        return;
      }
      else { //the case when the exponent of the first list is less than that of the second
        node->next = ptr->next; 
        ptr->next = node; //moving to the next node
        return; 
      } 
    }
  ptr->next = node; //moving to the next node
}

void LinkedList::display() const { //displaying the linked list in the formatted form
  Node* ptr = this->head; //pointer to the head of the node
  while(ptr) {
    if(ptr->coef == 0) { //the case when the coefficient of the term is zero
      ptr=ptr->next; //move to the next node
      continue; //skip
    }
    if(ptr->coef > 0) { //the case when the coefficient of the term is positive
      cout << "+"; //put + before the coefficient
    }
    cout << ptr->coef; //printing the coefficient
    if(ptr->expo > 0) //the case when there is an exponent present in the term
      cout << "x" << "^" << ptr->expo; //printing x^ and the exponent
    ptr=ptr->next; //moving to the next node
  }
}

void LinkedList::removeAll() {
  while(this->head) // removing the first node from the list until it does not reach its end
  {
    Node* old = this->head;
    this->head = old->next;
    delete old;
  }   
}

LinkedList::~LinkedList() //destructor
{
  removeAll();
}
