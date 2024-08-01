#pragma once
#include <iostream>
#include <stdexcept> // For standard exceptions

// This stack class is taken from the slides in the cs300 which has been provided to us.


template <class Object>
class Stack {
private:
    struct ListNode {
        Object element;
        ListNode* next;

        ListNode(const Object& theElement, ListNode* n = nullptr)
            : element(theElement), next(n) {}
    };

    ListNode* topOfStack;

public:
    Stack() : topOfStack(nullptr) {}
    Stack(const Stack& rhs) { topOfStack = nullptr; *this = rhs; }
    ~Stack() { makeEmpty(); }

    bool isEmpty() const { return topOfStack == nullptr; }
    void makeEmpty();

    void pop();
    void push(const Object& x);
    Object topAndPop();
    const Object& top() const;

    const Stack& operator=(const Stack& rhs);
};

template <class Object>
void Stack<Object>::makeEmpty() {
    while (!isEmpty()) {
        pop();
    }
}

template <class Object>
void Stack<Object>::pop() {
    if (isEmpty())
        throw std::out_of_range("Underflow Exception");
    ListNode* oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}

template <class Object>
void Stack<Object>::push(const Object& x) {
    topOfStack = new ListNode(x, topOfStack);
}

template <class Object>
Object Stack<Object>::topAndPop() {
    Object topItem = top();
    pop();
    return topItem;
}

template <class Object>
const Object& Stack<Object>::top() const {
    if (isEmpty())
        throw std::out_of_range("Underflow Exception");
    return topOfStack->element;
}

template <class Object>
const Stack<Object>& Stack<Object>::operator=(const Stack<Object>& rhs) {
    if (this != &rhs) {
        makeEmpty();
        if (rhs.isEmpty()) return *this;

        ListNode* rptr = rhs.topOfStack;
        ListNode* ptr = new ListNode(rptr->element);
        topOfStack = ptr;

        for (rptr = rptr->next; rptr != nullptr; rptr = rptr->next) {
            ptr = ptr->next = new ListNode(rptr->element);
        }
    }
    return *this;
}