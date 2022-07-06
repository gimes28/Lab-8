#ifndef DOUBLELINKED_h
#define DOUBLELINKED_h
#include <iostream>
#include "Exception.h"
#include "Part.h"
//#include "Part.cpp"
using namespace std;

template <class T>
class DoubleLinked {
private:
    struct Node {
        T* data = nullptr;
        struct Node* next = nullptr;
        struct Node* prev = nullptr;
    };
    Node* head;
    int size;
    int searchPos = 0; //for SeeAt
public:
    DoubleLinked();
    ~DoubleLinked();
    void AddItem(T*);
    T* GetItem(T*);
    bool IsInList(T*);
    bool IsEmpty();
    int Size();
    T* SeeNext();
    T* SeePrev();
    T* SeeAt(int);
    void Reset();
    void DisplayList();

    bool operator == (const Part&);
    bool operator < (const Part&);
    bool operator > (const Part&);
};

template<class T>
DoubleLinked<T>::DoubleLinked() {
    int size = 0;
    head = nullptr;
}

template<class T>
DoubleLinked<T>::~DoubleLinked() {
    Node* nn = new Node;
    Node* np;

    nn = head;

    while (nn != nullptr) {
        np = nn->next;
        delete nn;
        nn = np;
    }
}

template<class T>
void DoubleLinked<T>::AddItem(T* item) {
    Node* nn = new Node;
    Node* np;

    nn->data = item;

    if (!head) {
        head = nn;
    }
    else {
        if (*item < *head->data) {
            nn->next = head;
            head->prev = nn;
            head = nn;
            size++;
            return;
        }
        np = head;
        while (np->next != NULL && *np->next->data < *item) {
            np = np->next;
        }
        nn->next = np->next;
        np->next = nn;
        nn->prev = np;
        if (size >= 3 && nn->next != nullptr) {
            np = nn->next;
            np->prev = nn;
        }
    }
    size++;
}

template<class T>
T* DoubleLinked<T>::GetItem(T* item) {
    if (IsEmpty()) {
        return nullptr;
    }
    Node* np = head;
    if (head->data == item) {
        Node* oh = head;// node of old head
        T* retval = head->data;// return val set to val being removed
        head = head->next;//head is set to the next node in the list
        delete oh;//delete old head to prevent memory leak
        size--;
        return retval;
    }
    while (np->next != NULL && np->next->data != item) {
        np = np->next;
    }
    if (np->next == nullptr) {//if end is reached and item not found, return nullptr
        cout << "--Item not found--" << endl;
        return nullptr;
    }
    Node* dp = np->next;//sets a delete pointer to the next spot from where np stops
    np->next = dp->next;//assigns the pointer(currently pointing to next) to the next next value(just skips the value being removed)
    if (dp->next != nullptr) {
        np = dp->next;
        np->prev = dp->prev;
    }
    else {
        np->next = nullptr;
    }
    T* retval = dp->data; //assigns the value 
    delete dp;
    size--;
    return retval;
}

template<class T>
bool DoubleLinked<T>::IsInList(T* item) {
    Node *np = head;
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (head->data == item) {
        return true;
    }
    while (np->next != NULL && np->next->data != item) {
        np = np->next;
    }
    if (np->next == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

template<class T>
bool DoubleLinked<T>::IsEmpty() {
    return size == 0;
}

template<class T>
int DoubleLinked<T>::Size() {
    return size;
}

template<class T>
T* DoubleLinked<T>::SeeNext() {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos >= size - 1 || searchPos < 0) {
        throw Exception("Index out of bounds");
    }
    Node *np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != searchPos + 1) {
        np = np->next;
        posCount++;
    }
    searchPos++;
    return np->data;
}

template<class T>
T* DoubleLinked<T>::SeePrev() {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos > size || searchPos <= 0) {
        throw Exception("Index out of bounds");
    }
    Node *np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != searchPos - 1) {
        np = np->next;
        posCount++;
    }
    searchPos--;
    return np->data;
}

template<class T>
T* DoubleLinked<T>::SeeAt(int pos) {
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (searchPos > size || searchPos < 0) {
        throw Exception("Index out of bounds");
    }
    Node *np = head;
    int posCount = 0;
    while (np->next != NULL && posCount != pos) {
        np = np->next;
        posCount++;
    }
    searchPos = posCount;
    return np->data;
}

template<class T>
void DoubleLinked<T>::Reset() {
    searchPos = 0;
}

template<class T>
void DoubleLinked<T>::DisplayList() {
    int posCount = 0;
    Node* np = head;
    if (IsEmpty()) {
        throw Exception("List Underflow Error");
    }
    if (head->next == NULL) {
        np->data->Display();
    }
    else {
        while (np->next != NULL && posCount <= size) {
            np->data->Display();
            cout << "\t   /\\ \n";
            cout << "\t   ||  \n";
            cout << "\t   ||  \n";
            cout << "\t   ||  \n";
            cout << "\t   \\/  \n";
            np = np->next;
            posCount++;
        }
        np->data->Display();
    }
    cout << endl;
}

template<class T>
bool DoubleLinked<T>::operator == (const Part& item) {
    return item.getSKU() == this->item.getSKU();
}

template<class T>
bool DoubleLinked<T>::operator < (const Part& item) {
    return item.getSKU() < this->item.getSKU();
}

template<class T>
bool DoubleLinked<T>::operator > (const Part& item) {
    return item.getSKU() > this->item.getSKU();
}

#endif
