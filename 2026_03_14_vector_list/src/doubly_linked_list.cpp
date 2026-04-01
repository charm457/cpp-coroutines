#include "doubly_linked_list.hpp"
#include <iostream>

using bdk::DoublyLinkedList;

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
void DoublyLinkedList<T>::push_back(const T& value) {
	Node* newNode = new Node(value);
	if (!begin) {
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

			if (current->next) current->next->prev = current->prev;
			else end = current->prev;

			delete current;
			size--;
			return true;
		}
		current = current->next;
	}
	return false;
}