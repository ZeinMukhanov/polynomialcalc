#include <iostream>
#include "polycalculator.h"

void PolyCalculator::input() {
  string exp1, exp2;
  cout << "Enter first Polynomial expression:";
  cin >> exp1;
  cout << endl;
  cout << "Enter second Polynomial expression:";
  cin>>exp2;
  cout << exp1 << endl << exp2 << endl;
  parse(exp1, list1);
  parse(exp2, list2);
}
void PolyCalculator::add(){ //add both polynomials (list1 and list2) and save the result in list3
Node* ptrList1 = this->list1.head;
Node* ptrList2 = this->list2.head;
list3.removeAll(); //clearing the third linked list prior adding 
while(ptrList1!=NULL){
  list3.insert(ptrList1->coef, ptrList1->expo); //inserting the elements of first linked list to the third one
  ptrList1 = ptrList1->next; //updating the ptrList1 to point to the next node
}
Node* ptrList3 = this->list3.head;
  while(ptrList3!=NULL && ptrList2!=NULL)
    { 
        if(ptrList3->expo == ptrList2->expo) //the case when the exponents of two terms are the same
        {
            ptrList3->coef = ptrList3->coef + ptrList2->coef; //adding the coefficients of the terms
            ptrList3 = ptrList3->next; //moving the pointer to the next node
            ptrList2 = ptrList2->next; //moving the pointer to the next node
        } 
        else if(ptrList3->expo > ptrList2->expo) //the case when the exponent of the term from the first list is greater than that of the second term
        { 
            ptrList3 = ptrList3->next; //moving the pointer to the next node
        } 
        else if(ptrList3->expo < ptrList2->expo) //the case when the exponent of the term from the first list is less than that of the second term
        {
         list3.insert(ptrList2->coef, ptrList2->expo); //insert the coefficient and the exponent
         ptrList3 = ptrList3->next; //moving the pointer to the next node
         ptrList2 = ptrList2->next; //moving the pointer to the next node
        }
    }

  cout << "Exp1 + Exp2 =";
  this->list3.display(); //displaying the addition of two polynomials
  cout << endl;
} 

void PolyCalculator::sub(){ //subtract list2 from list1 and save the results in list3
Node* ptrList1 = this->list1.head; //a pointer to the head of the first linked list
Node* ptrList2 = this->list2.head; //a pointer to the head of the second linked list
list3.removeAll(); //clearing the third linked list prior subtracting 
while(ptrList1!=NULL){
  list3.insert(ptrList1->coef, ptrList1->expo); //inserting the elements of first linked list to the third one
  ptrList1 = ptrList1->next; //updating the ptrList1 to point to the next node
}
Node* ptrList3 = this->list3.head; //a pointer to the head of the third linked list
  while(ptrList3!=NULL && ptrList2!=NULL)
    { 
        if(ptrList3->expo == ptrList2->expo) //the case when the exponents of two terms are the same
        {
            ptrList3->coef = ptrList3->coef - ptrList2->coef; //subtracting the coefficients of the terms from each other: Exp1-Exp2
            ptrList3 = ptrList3->next; //moving the pointer to the next node
            ptrList2 = ptrList2->next; //moving the pointer to the next node
        } 
        else if(ptrList3->expo > ptrList2->expo) //the case when the exponent of the term from the first list is greater than that of the second term
        { 
            ptrList3 = ptrList3->next; //moving the pointer to the next node
        } 
        else if(ptrList3->expo < ptrList2->expo) //the case when the exponent of the term from the first list is less than that of the second term
        {
         list3.insert(-ptrList2->coef, ptrList2->expo); //insert the negative coefficient and the exponent
         ptrList3 = ptrList3->next; //moving the pointer to the next node
         ptrList2 = ptrList2->next; //moving the pointer to the next node
        }
    }
  cout << "Exp1 - Exp2 =";
  this->list3.display(); //displaying the subtraction of two polynomials
  cout << endl;
} 

void PolyCalculator::mul(){
  Node* ptrList1 = this->list1.head; //a pointer to the head of the first linked list
  list3.removeAll();
    while (ptrList1)
    {
      Node* ptrList2 = this->list2.head; //a pointer to the head of the second linked list
        while (ptrList2)
        {
            int resultantCoef, resultantExpo;
            resultantCoef = ptrList1->coef * ptrList2->coef; //multiplying coefficients
            resultantExpo = ptrList1->expo + ptrList2->expo; //adding exponents
            list3.insert(resultantCoef, resultantExpo); //inserting the resultant coefficents and exponents into the third linked list
            ptrList2 = ptrList2->next; // updating the ptrList2 so it will point to the next node
        }
        ptrList2 = ptrList2; // reseting the ptrList2
        ptrList1 = ptrList1->next; // updating the ptrList1 so it will point to the next node
    }
  cout << "Exp1 * Exp2 =";
  this->list3.display(); //displaying the multiplication of two polynomials
  cout << endl;

  
} //multiply both polynomials (list1 and list2) and save the result in list3
void PolyCalculator::readData(string path) {
   ifstream inputFile;
    string exp1,exp2;
    
    inputFile.open(path);
    if (inputFile.fail())
    {
        cerr << "Can't open the file\n";
        exit (-1);
    }

    inputFile >> exp1;
    inputFile >> exp2;
    parse(exp1, list1); //parsing the first expression from the file prior for the further insertion of it into the linked list
    parse(exp2, list2); //parsing the second expression from the file prior for the further insertion of it into the linked list
    inputFile.close();
  
} //read a file and load the data into the linked lists (list1 and list2)
void PolyCalculator::writeData(string path){
  ofstream fout(path);  
	if(!fout)
	{
		cout<<"Can't open file: "<<endl;
		return;
	}
  if (fout) {
    fout << "Exp1 = "; //writing the first polynomial expression into the new file
    write(list1, fout);
    fout << endl;
      
    fout << "Exp2 = "; //writing the second polynomial expression into the new file
    write(list2, fout);
    fout << endl;
  
    fout << "Exp1 + Exp2 = "; //writing the sum of two polynomials into the new file
    add();
    write(list3,fout);
    fout << endl;
  
    fout << "Exp1 - Exp2 = "; //writing the subtraction of two polynomials into the new file
    sub();
    write(list3,fout);
    fout << endl;
      
    fout << "Exp1 * Exp2 = "; //writing the multiplication of two polynomials into the new file
    mul();
    write(list3, fout);
    fout << endl;
  }
  
	fout.close();
} //write the polynomial expressions and the results of addition,subtraction and multiplication to a file
void PolyCalculator::parse(string str, LinkedList& list) {
  int currentCoefficient = 0;
  int currentDegree = 0;
  bool isPositive = true;
  bool isCoefficient = true;
  for(int i = 0; i < str.size(); i++) { //iterating over the size of the string
    //converting the string to integer
    if (str[i] >= '0' && str[i] <= '9') {
      if (isCoefficient) { 
        currentCoefficient *= 10; 
        currentCoefficient += ((int)str[i] - 48); 
      }
      else {
        currentDegree *= 10;
        currentDegree += ((int)str[i] - 48);
      }
    }
    else if(str[i] == '+' || str[i] == '-') {
      // add to linked list
      if(!isPositive)
        currentCoefficient *= (-1);
      list.insert(currentCoefficient, currentDegree); 
      //resetting the values of coefficient and exponent
      currentCoefficient = 0;
      currentDegree = 0;
      isCoefficient = true; //the case when the coefficient exists
      if(str[i] == '-') //the case when the term is negative
        isPositive = false;
      else
        isPositive = true;
    }
    else if(str[i] == '^') { //the case when there exists an exponent
      isCoefficient = false; //the case when there is no coefficient, starts writing the exponent part
    }
    else if(str[i] == 'x') { //the case when there is no coefficient before x
      if(i == 0) {
        currentCoefficient = 1; //setting the coefficient value to 1. E.g. x = 1x
      }
      else if(!(str[i-1] >= '0' && str[i-1] <= '9')) { //the case of encountering a number: //a plain number has an exponent of 1
        currentCoefficient = 1;
      }
      if(i == str.size() - 1) 
        currentDegree = 1;
      else if(str[i+1] != '^') 
        currentDegree = 1;
    }
  }
 
  list.insert(currentCoefficient, currentDegree); //inserting the extracted coefficient and exponent value into the linked list
  cout << endl;
}

void PolyCalculator::display(){ //display both polynomials (list1 and list2)
  cout << "Exp1:";
  list1.display(); //calling the display function for the first polynomial expression
  cout << endl;
  cout << "Exp2:";
  list2.display(); //calling the display function for the first polynomial expression
  cout << endl;
} 

void PolyCalculator::write(LinkedList& list, ofstream& fout){ //Optional helper function to write a polynomial expression (List) to a file;

  //adapting the display function for writing the singly linked list into the file
  Node* ptr = list.head;
  while(ptr) {
    if(ptr->coef == 0) {
      ptr=ptr->next;
      continue;
    }
    if(ptr->coef > 0) {
      fout << "+";
    }
    fout << ptr->coef;
    if(ptr->expo > 0)
      fout << "x" << "^" << ptr->expo;
    ptr=ptr->next;
  }
 }