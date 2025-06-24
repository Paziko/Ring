// Files
#include "ring.h"
#include "ring_element.cpp"
#include "ring_methods.cpp"

// Lids
#include <iomanip>
#include <iostream>

using namespace std;




enum Direction {FORWARD, BACKWARD};     // перечисление "Направление"




// Вывод колец. Принимает строку сообщения (если нужно), кольцо и направление вращения
template<typename T>
void printRing(const string& message, Ring<T>& ring, Direction dir = FORWARD)
{
    printf("%s", message.c_str());
    
    for (int i = 0; i < ring.size(); ++i) {
        cout << setw(2) << ring.top() << ' ';
        (dir == FORWARD) ? ring.spinF() : ring.spinB();
    }
}




int main() {

    // Для демонстрации различия вставки слева и вставки справа
    // создается два пустых кольца:

    Ring<int> ring_1;
    Ring<int> ring_2;



    // 1. Заполнение колец по 10 элементов
    for (int i = 0; i < 10; ++i) {
        ring_1.pushB(i);    // вставка слева
        ring_2.pushF(i);    // вставка справа
    }



    // 2. Вывод колец по часовой стрелке (вывод начинается с текущего элемента - top)
    printf("The output of the rings is clockwise: \n");

    printRing("ring_1 : ", ring_1, FORWARD); putchar('\n');
    printRing("ring_2 : ", ring_2, FORWARD); putchar('\n');

    putchar('\n');



    // 3. Вывод колец против часовой стрелки (вывод начинается с текущего элемента - top)
    printf("The output of the rings is counterclockwise: \n");
    
    printRing("ring_1 : ", ring_1, BACKWARD); putchar('\n');
    printRing("ring_2 : ", ring_2, BACKWARD); putchar('\n');

    putchar('\n');



    // 4. Некоторое тесты
    printf("<<< Some tests >>> \n\n");

    ring_1.top() = 28;
    printf("ring_1.top() = 28 -> current = %d \n", ring_1.top());    
    printRing("ring_1 : ", ring_1); printf("\n\n");

    ring_1.spin(14);    
    printf("ring_1.spin(14) -> current = %d \n", ring_1.top());    
    printRing("ring_1 : ", ring_1); printf("\n\n");

    ring_1.pop();    
    printf("ring_1.pop() -> current = %d \n", ring_1.top());
    printRing("ring_1 : ", ring_1); printf("\n\n");

    ring_1.spin(-3);
    printf("ring_1.spin(-3) -> current = %d \n", ring_1.top());
    printRing("ring_1 : ", ring_1); printf("\n\n");

    printf("ring_1.size() -> size = %lu \n\n", ring_1.size());

    ring_1.clear();
    try {
        printf("ring_1.clear() -> current = %d \n\n", ring_1.top());
    } catch (char const* error_message) {
        printf("ring_1.clear() -> current = %s \n\n", error_message);
    }

    // 5. Очистка
    ring_1.clear();
    ring_2.clear();

    return 0;
}