#include <iostream>
#include <vector>
#include <chrono>
#include "sparta.h"
#include "MyVector.h"  // Tavo klasė

void matuotiSparta(unsigned int dydis) {
    using namespace std::chrono;

    std::cout << "Testuojama su " << dydis << " elementų:\n";

    // std::vector
    auto start1 = high_resolution_clock::now();
    std::vector<int> v1;
    for (unsigned int i = 1; i <= dydis; ++i) v1.push_back(i);
    auto end1 = high_resolution_clock::now();
    auto trukme1 = duration<double, std::milli>(end1 - start1).count();
    std::cout << "std::vector: " << trukme1 << " ms\n";

    // MyVector
    auto start2 = high_resolution_clock::now();
    MyVector<int> v2;
    for (unsigned int i = 1; i <= dydis; ++i) v2.push_back(i);
    auto end2 = high_resolution_clock::now();
    auto trukme2 = duration<double, std::milli>(end2 - start2).count();
    std::cout << "MyVector:    " << trukme2 << " ms\n\n";
}
