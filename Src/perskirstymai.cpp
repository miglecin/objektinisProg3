#include <iostream>
#include <vector>
#include "MyVector.h"
#include "perskirstymai.h"

void skaiciuotiPerskirstymus(unsigned int dydis) {
    std::cout << "Testavimas su " << dydis << " elementų:\n";

    // std::vector
    std::vector<int> v1;
    size_t std_realloc_count = 0;
    size_t prev_cap = v1.capacity();

    for (unsigned int i = 0; i < dydis; ++i) {
        v1.push_back(i);
        if (v1.capacity() != prev_cap) {
            ++std_realloc_count;
            prev_cap = v1.capacity();
        }
    }
    std::cout << "std::vector perskirstymų: " << std_realloc_count << "\n";

    // MyVector
    MyVector<int> v2;
    size_t myvec_realloc_count = 0;
    size_t prev_mycap = v2.get_capacity();

    for (unsigned int i = 0; i < dydis; ++i) {
        v2.push_back(i);
        if (v2.get_capacity() != prev_mycap) {
            ++myvec_realloc_count;
            prev_mycap = v2.get_capacity();
        }
    }
    std::cout << "MyVector perskirstymų:    " << myvec_realloc_count << "\n\n";
}
