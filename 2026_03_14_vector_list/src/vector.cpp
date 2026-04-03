#include "vector.hpp"
#include <iostream>

using bdk::Vector;

template<typename T>
Vector<T>::Vector() {
    arr = new T[capacity];
}

template<typename T>
Vector<T>::~Vector() {
    delete[] arr;
}

// Приватный метод для управления памятью
template<typename T>
void Vector<T>::reserve(std::size_t new_capacity) {
    T* new_arr = new T[new_capacity];
    for (std::size_t i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    capacity = new_capacity;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
    return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) return true;
    }
    return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
    if (position > size) return false;

    // Если место закончилось, расширяем массив
    if (size >= capacity) {
        reserve(capacity * 2);
    }

    // Сдвигаем элементы вправо
    for (std::size_t i = size; i > position; --i) {
        arr[i] = arr[i - 1];
    }

    arr[position] = value;
    size++;
    return true;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    insert(size, value);
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
    for (std::size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
            // Сдвигаем элементы влево
            for (std::size_t j = i; j < size - 1; ++j) {
                arr[j] = arr[j + 1];
            }
            size--;

            // Логика сужения: используем reserve для уменьшения памяти
            if (size < (capacity / 4) && (capacity / 2) >= START_CAPACITY) {
                reserve(capacity / 2);
            }
            return true;
        }
    }
    return false;
}

template<typename T>
void Vector<T>::print() const noexcept {
    for (std::size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << (i == size - 1 ? "" : " ");
    }
    std::cout << std::endl;
}