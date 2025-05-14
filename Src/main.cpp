#include <iostream>
#include "MyVector.h"  // Įtraukiame antraštės failą

int main() {
    // Sukuriame MyVector objektą, kuris laikys int tipus
    MyVector<int> vec;

    // Pridedame elementų į vektorių
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Išvedame vektoriaus elementus
    std::cout << "Vektoriaus dydis: " << vec.get_size() << std::endl;
    std::cout << "Vektoriaus talpa: " << vec.get_capacity() << std::endl;

    std::cout << "Vektoriaus elementai: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";  // Pasiekiame elementus naudojant operator[]
    }
    std::cout << std::endl;

    // Pašaliname paskutinį elementą
    vec.pop_back();
    std::cout << "Po pop_back, vektoriaus dydis: " << vec.get_size() << std::endl;

    // Dar kartą išvedame vektoriaus elementus
    std::cout << "Vektoriaus elementai po pop_back: ";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        std::cout << vec[i] << " ";  // Pasiekiame elementus naudojant operator[]
    }
    std::cout << std::endl;

    return 0;
}
