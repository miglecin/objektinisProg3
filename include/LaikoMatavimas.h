#ifndef LAIKO_MATAVIMAS_H
#define LAIKO_MATAVIMAS_H

#include <chrono>
#include <iostream>

class LaikoMatavimas {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
    std::string veiksmoPavadinimas;

public:
    // Konstruktorius su veiksmo pavadinimu
    LaikoMatavimas(const std::string& pavadinimas);

    // Pradėti matavimą
    void pradeti();

    // Baigti matavimą ir parodyti laiką
    void baigti();

    // Gauti laiko skirtumą (ms)
    double gautiLaikoSkirtuma();
};

#endif