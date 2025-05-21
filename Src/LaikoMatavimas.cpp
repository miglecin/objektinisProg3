#include "LaikoMatavimas.h"

using namespace std::chrono;

// Konstruktorius su pavadinimu
LaikoMatavimas::LaikoMatavimas(const std::string& pavadinimas) {
    veiksmoPavadinimas = pavadinimas;
}

// Pradėti matavima
void LaikoMatavimas::pradeti() {
    start = high_resolution_clock::now();
}

// Baigti matavima ir parodyti laika
void LaikoMatavimas::baigti() {
    end = high_resolution_clock::now();
    std::cout << "---> " << veiksmoPavadinimas << " uztruko: " << gautiLaikoSkirtuma() << " ms\n";
}

// Grąžina laiko skirtumą (ms)
double LaikoMatavimas::gautiLaikoSkirtuma() {
    return duration<double, std::milli>(end - start).count();
}