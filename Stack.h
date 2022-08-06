//
// Eylül Badem - 22003079
// HW4 - 14.05.2022
//

#ifndef UNTITLED3_STACK_H
#define UNTITLED3_STACK_H
#include <iostream>

using namespace std;

class Stack {
public:
    Stack();
    ~Stack();

    bool isEmpty();
    bool push( string newValue);
    bool pop();
    bool pop( string& topChar);
    int getSize();

private:
    struct StackNode{
        string value;
        StackNode* next;
    };

    StackNode* top;
    int size;
};


#endif //UNTITLED3_STACK_H
