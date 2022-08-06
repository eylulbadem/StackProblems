//
// Eylül Badem - 22003079
// HW4 - 14.05.2022
//

#include "Stack.h"

Stack::Stack() {
    top = NULL;
    size = 0;
}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() {
    return size == 0;
}

bool Stack::push(string newValue) {
    StackNode* newTop = new StackNode();
    newTop->value = newValue;
    newTop->next = top;
    top = newTop;
    size++;
    return true;
}

bool Stack::pop(){
    if( size == 0){
        cout<<"empty"<<endl;
        return false;
    }
    StackNode* popPtr = top;
    top = top->next;
    popPtr->next = NULL;
    delete popPtr;
    size--;
    return true;
}
bool Stack::pop(string &topChar) {
    if( size == 0){
        return false;
    }

    topChar = top->value;

    StackNode* popPtr = top;
    top = top->next;
    popPtr->next = NULL;
    delete popPtr;
    size--;
    return true;

}

int Stack::getSize() {
    return size;
}