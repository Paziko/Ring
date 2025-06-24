// Files
#include "ring.h"


// Ctor
template<typename T>
Ring<T>::Element::Element(const T& value, Element* next, Element* last)
    : value(value), next(next), last(last)
{}


// Dtor
template<typename T>
Ring<T>::Element::~Element()
{
    next = nullptr;
    last = nullptr;
}