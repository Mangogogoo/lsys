//  stack container
#ifndef GSTACK_H_INCLUDED
#define GSTACK_H_INCLUDED

#include <cassert>

using namespace std;

template <typename T>
struct gnode {
    T value;
    gnode *prev;
};

template <typename T>
class gstack {
    struct gnode<T> *top;
public:
    gstack();
    void push(T value);
    T pop();
    void show();
};

template <typename T>
inline gstack<T>::gstack() {
    top = 0;
}

template <typename T>
inline void gstack<T>::push(T value) {
    if (top == 0) {
        top = new gnode<T>;
        top->value = value;
        top->prev = 0;
    } else {
        gnode<T> *temp = top;
        top = new gnode<T>;
        assert(top);
        top->value = value;
        top->prev = temp;
    }
}

template <typename T>
inline T gstack<T>::pop() {
    T value = top->value;
    gnode<T> *temp = top->prev;
    delete top;
    top = temp;
    return value;
}

template <typename T>
inline void gstack<T>::show() {
    gnode<T> *temp = top;
    while (temp) {
        cout << temp->value;
        temp = temp->prev;
    }
}



#endif // GSTACK_H_INCLUDED
