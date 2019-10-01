#include "Stack.h"
#include <iostream>
using namespace std;
int stack::size(){
    return this->Size;
}
bool stack::isEmpty(){
    if(this->size() == 0){
        return true;
    }
    return false;
}
void stack::push(int posx){
    if(isEmpty()){
        Node* newnode = new Node(posx,0);
        this->topNode = newnode;
        this->Size++;
    }
    Node* newnode = new Node(posx,topNode);//point to the current top address
    topNode = newnode; //Update the top address to newnode
    this->Size++;
}

int stack::top(){
    if(isEmpty()){
        cout<<"it's Empty"<<endl;
        return -1;
    }
    return topNode->store;
}