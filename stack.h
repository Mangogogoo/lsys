//  stack container
#ifndef GSTACK_H_INCLUDED
#define GSTACK_H_INCLUDED

#include <cassert>
#include "node.h"

using namespace std;

template <typename T>
class stack {
    struct node<T> *top;
public:
    stack();
    void push(T value);
    T pop();
    void dump();
};

template <typename T>
inline stack<T>::stack() {
    top = 0;
}

template <typename T>
inline void stack<T>::push(T value) {
    if (top == 0) {
        top = new node<T>;
        top->value = value;
        top->prev = 0;
    } else {
        node<T> *temp = top;
        top = new node<T>;
        assert(top);
        top->value = value;
        top->prev = temp;
    }
}

template <typename T>
inline T stack<T>::pop() {
    T value = top->value;
    node<T> *temp = top->prev;
    delete top;
    top = temp;
    return value;
}

template <typename T>
inline void stack<T>::dump() {
    node<T> *temp = top;
    while (temp) {
        cout << temp->value;
        temp = temp->prev;
    }
}



#endif // GSTACK_H_INCLUDED
