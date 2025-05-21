#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include "MyVector.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <random>
#include <list>
#include <deque>

#include "zmogus.h" // paveldėjimas

using std::cout;
using std::cin;
//using std::vector;
using std::setw;
using std::endl;
using std::string;
using std::fstream;
using std::fixed;
using std::setprecision;
using std::cerr;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::stringstream;
using std::numeric_limits;
using std::streamsize;
using namespace std::chrono;
using std::ostringstream;
using std::istringstream;
using std::move;
extern std::stringstream buffer;
using std::list;
using std::deque;
using std::istream;
using std::ostream;

// Galutinio balo apskaičiavimo funkcijos
float generuotiGalvid(const MyVector<float>& nd, int egz);
float generuotiGalmed(const MyVector<float>& nd, int egz);

class Studentas : public Zmogus {
private:
    int egzaminas_;
    MyVector<float> nd_;
    float galutinis_balas_;

public:
    Studentas();  // default konstruktorius
    Studentas(istream& is);  // konstruktorius su stream

    // Rule of Five
    Studentas(const Studentas& other);   // Copy konstruktorius
    Studentas& operator=(const Studentas& other);   // Copy priskyrimo operatorius
    Studentas(Studentas&& other) noexcept;   // Move konstruktorius
    Studentas& operator=(Studentas&& other) noexcept;  // Move priskyrimo operatorius
    ~Studentas();  // Destruktorius

    // Stream operatoriai
    friend ostream& operator<<(ostream& os, const Studentas& s);
    friend istream& operator>>(istream& is, Studentas& s);

    // Getteriai (įgyvendina Zmogus)
    inline string vardas() const override { return vardas_; }
    inline string pavarde() const override { return pavarde_; }
    inline int egzaminas() const { return egzaminas_; }
    inline const MyVector<float>& nd() const { return nd_; }
    inline float galutinisBalsas() const { return galutinis_balas_; }

    // Setteriai (įgyvendina Zmogus)
    void setVardas(const string& v) override { vardas_ = v; }
    void setPavarde(const string& p) override { pavarde_ = p; }
    void setEgzaminas(int e);
    void setNamudarbai(const MyVector<float>& nd);

    float galBalas(float (*balasFunkcija)(const MyVector<float>&, int));
    istream& readStudent(istream&);
    static int destruktoriuSk;

    static void rusiuotiStud(MyVector<Studentas>& grupe, char rusiavimoPas);
    static void nuskaitymasFile(MyVector<Studentas>& grupe, const string& filename);
    static void spausdintiRez(MyVector<Studentas>& grupe, bool iFaila, char pasirinkimas, const std::string& failoPavadinimas);
};

#endif  // STUDENTAS_H
