#include <iostream>
#include <vector>
#include "sparta.h"
#include "MyVector.h"  

void matuotiSparta(unsigned int dydis);

int main() {
    MyVector<int> vec;

    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::cout << "Vektoriaus dydis: " << vec.get_size() << std::endl;
    std::cout << "Vektoriaus talpa: " << vec.get_capacity() << std::endl;

    std::cout << "Vektoriaus elementai: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    std::cout << "Po pop_back, vektoriaus dydis: " << vec.get_size() << std::endl;

    std::cout << "Vektoriaus elementai po pop_back: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;


    std::vector<unsigned int> dydziai = {10000, 100000, 1000000, 10000000};

    for (unsigned int d : dydziai) {
        matuotiSparta(d);
    }

    return 0;
}
