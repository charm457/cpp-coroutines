#include "doubly_linked_list.hpp"
#include <iostream>

namespace bdk {

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node* current = begin;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
    Node* current = begin;
    while (current) {
        if (current->value == value) return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
    Node* current = begin;
    while (current) {
        std::cout << current->value << (current->next ? " " : "");
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
bool DoublyLinkedList<T>::insert(std::size_t position, const T& value) {
    if (position > size) return false;

    if (position == 0) {
        Node* newNode = new Node(value); // новый узел в памяти 
        newNode->next = begin;
        
        if (begin) {
            begin->prev = newNode;
        }
        
        begin = newNode;
        
        if (size == 0) {
            end = newNode;
        }
        
        size++;
        return true;
    }

    Node* current = begin;
    for (std::size_t i = 0; i < position - 1; ++i) {
        current = current->next;
    }

    Node* newNode = new Node(value);
    newNode->next = current->next;
    newNode->prev = current;
    
    if (current->next) {
        current->next->prev = newNode;
    } else {
        end = newNode;
    }
    
    current->next = newNode;
    size++;
    return true;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    
    if (size == 0) {
        begin = end = newNode;
    } else {
        end->next = newNode;
        newNode->prev = end;
        end = newNode;
    }
    size++;
}

template<typename T>
bool DoublyLinkedList<T>::remove_first(const T& value) noexcept {
    Node* current = begin;
    
    while (current) {
        if (current->value == value) {
            if (current->prev) current->prev->next = current->next;
			else begin = current->next;


            if (current->next) 
                current->next->prev = current->prev;
            else 
                end = current->prev;

            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false;
}

}