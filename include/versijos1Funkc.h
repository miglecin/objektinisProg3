#ifndef VERSIJOSFUNKC_H
#define VERSIJOSFUNKC_H

#include <iostream>
#include "MyVector.h"
//#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cstdlib>  // srand(), rand()
#include <ctime> 
#include <sstream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <random>
#include <list>
#include <deque>

using std::cout;
using std::cin;
using std::vector;
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
using std::string;

// Studentas struktūra su `MyVector` konteineriu
template <typename T = MyVector<float>>  // Jei T nepateikta, bus MyVector<float>
struct studentas {
    using nd_type = T;  // Automatiškai priskiriamas konteineris iš T

    string Vard;
    string Pav;
    nd_type nd;  // Čia gali būti MyVector, std::vector, list, deque
    int egz;
    double Gal;
};

// **Generuoti Galutinį Balą pagal Vidurkį**
template <typename Container>
double generuotiGalvid(Container& nd, int egz);

// **Generuoti Galutinį Balą pagal Mediana**
template <typename Container>
double generuotiGalmed(Container nd);

// Funkcija pasirinktam galutiniam balui
template <typename Container>
double pasirinktasGal(Container& nd, int egz, char kaip);

// Atsitiktinių pažymių generavimas
template <typename Container>
void randomPaz(Container& nd, int& egz, int kiek_nd);

// Generuoja studentų vardus ir pavardes
void generuotiVardPav(std::string& vardas, std::string& pavarde);

// SABLONINĖ RŪŠIAVIMO FUNKCIJA
template <typename Container>
void rusiuotiStud(Container& grupe, char rusiavimoPas);

// Nuskaityti studentų duomenis iš failo
template <typename Container>
void nuskaitymasFile(Container& grupe, const string& filename);

// Rezultatų spausdinimas
void spausdintiRez2(MyVector<studentas<MyVector<float>>>& grupe, bool iFaila, char pasirinkimas, char rusiavimoPas);

//template<typename Container>
//void spausdintiRez(Container& grupe, bool iFaila, char pasirinkimas, const string& failoPavadinimas);

#endif  // VERSIJOSFUNKC_H
