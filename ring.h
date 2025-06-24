#ifndef RING_H
#define RING_H

//Libs
#include <cstddef>
#include <cstdint>



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

#endif//RING_H