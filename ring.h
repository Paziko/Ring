#ifndef RING_H
#define RING_H

//Libs
#include <cstddef>
#include <cstdint>
#include <cmath>



template<typename T>
class Ring {

    struct Element {
        T value;            // значение
        Element *next;      // следующий элемент (по часовой стрелке)
        Element *last;      // предыдущий элемент (против часовой стрелки)

        Element(const T& value, Element* next = nullptr, Element* last = nullptr);
        ~Element();
    };

    Element* current;
    size_t size_;

public:
    Ring();
    Ring(const size_t& size, const T& value);
    ~Ring();

    void pushB(const T& value);     // вставка в кольцо назад (слева от текущего элемента)
    void pushF(const T& value);     // вставка в кольцо вперед (справа от текущего элемента)
    T& top();                       // возврат значения в текущем элементе
    void pop();                     // удаление текущего элемента

    void spinF(size_t step = 1);    // вращение вперед (влево)
    void spinB(size_t step = 1);    // вращение назад (вправо)
    void spin(int step = 1);        // вращение (step > 0 - spinF) (step < 0 - spinB)

    size_t size();                  // размер кольца
    void clear();                   // очистка кольца. Важно: если кольцо хранит указатели, то их память не высвобождается
    bool isEmpty();                 // проверка на пустоту
};






// Element Ctor
template<typename T>
Ring<T>::Element::Element(const T& value, Element* next, Element* last)
    : value(value), next(next), last(last)
{}


// Element Dtor
template<typename T>
Ring<T>::Element::~Element()
{
    next = nullptr;
    last = nullptr;
}








// Ring Ctor default
template<typename T>
Ring<T>::Ring()
    : current(nullptr), size_(0)
{

}

// Ring Ctor 1
template<typename T>
Ring<T>::Ring(const size_t& size, const T& value)
    : current(nullptr), size_(0)
{
    for (size_t i = 0; i < size; ++i) {
        pushB(value);
    }
}


// Ring Dtor
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


#endif//RING_H