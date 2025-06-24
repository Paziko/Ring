// Files
#include "ring.h"


// Libs
#include <cmath>





// Ctor default
template<typename T>
Ring<T>::Ring()
    : current(nullptr), size_(0)
{

}

// Ctor 1
template<typename T>
Ring<T>::Ring(const size_t& size, const T& value)
    : current(nullptr), size_(0)
{
    for (size_t i = 0; i < size; ++i) {
        pushB(value);
    }
}


// Dtor
template<typename T>
Ring<T>::~Ring()
{
    clear();
}



// вставка в кольцо назад (слева от текущего элемента)
template<typename T>
void Ring<T>::pushB(const T& value)
{
    if (current == nullptr) {
        current = new Element(value);
        current->last = current;
        current->next = current;
    } else {
        Element* new_element = new Element(value, current, current->last);
        current->last->next = new_element;
        current->last = new_element;
    }

    ++size_;
}

// вставка в кольцо вперед (справа от текущего элемента)
template<typename T>
void Ring<T>::pushF(const T& value)
{
    if (current == nullptr) {
        current = new Element(value);
        current->last = current;
        current->next = current;
    } else {
        Element* new_element = new Element(value, current->next, current);
        current->next->last = new_element;
        current->next = new_element;
    }

    ++size_;
}

// возврат значения в текущем элементе
template<typename T>
T& Ring<T>::top()
{
    if (size_ == 0) {
        throw "Segmentation fault. Dinamic ring is empty";
    }

    return current->value;
}

// удаление текущего элемента
template<typename T>
void Ring<T>::pop()
{
    if (size_ == 0) {
        return;
    }


    Element* tmp = current;

    if (size_ == 1) {
        current = nullptr;
    } else {
        current->next->last = current->last;
        current->last->next = current->next;
        current = current->next;
    }

    delete tmp;
    tmp = nullptr;

    --size_;
}

// вращение вперед (влево)
template<typename T>
void Ring<T>::spinF(size_t step)
{
    if (size_ == 0 || step == 0) {
        return;
    }

    for (auto i = 0; i < step % size_; ++i) {
        current = current->next;
    }
}

// вращение назад (вправо)
template<typename T>
void Ring<T>::spinB(size_t step)
{
    if (size_ == 0 || step == 0) {
        return;
    }

    for (auto i = 0; i < step % size_; ++i) {
        current = current->last;
    }
}

// вращение
template<typename T>
void Ring<T>::spin(int step)
{
    (step < 0) ? spinB(abs(step)) : spinF(step);
}

// размер кольца
template<typename T>
size_t Ring<T>::size()
{
    return size_;
}

// очистка кольца
template<typename T>
void Ring<T>::clear()
{
    if (size_ == 0) {
        return;
    }

    Element* tmp;
    for (size_t i = 0; i < size_ - 1; ++i) {
        tmp = current;
        current = current->next;
        delete tmp;
    }

    delete current;
    current = nullptr;
    size_ = 0;
}

// проверка на пустоту
template<typename T>
bool Ring<T>::isEmpty()
{
    return size_ == 0;
}








