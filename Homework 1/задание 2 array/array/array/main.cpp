#include "array.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Array arr(5);

        for (int i = 0; i < 5; i++) {
            arr.insert(i * 10);
        }

        std::cout << arr << std::endl;

        arr.remove(2);
        std::cout << "After removing index 2:" << std::endl;
        std::cout << arr << std::endl;

    }
    catch (const ArrayException& e) {
        std::cerr << "Error: index out of bounds" << std::endl;
    }

    return 0;
}