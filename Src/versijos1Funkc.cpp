#include "MyVector.h"
#include "versijos1Funkc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>  // rand() funkcijai
#include <string> 
#include <numeric>

namespace fs = std::filesystem;

// **Generuoti Galutinį Balą pagal Vidurkį**
template <typename Container>
double generuotiGalvid(Container& nd, int egz) {
    double suma = 0;
    for (const auto& paz : nd) {
        suma += paz;
    }
    double vidurkis = suma / nd.get_size();
    return 0.4 * vidurkis + 0.6 * egz;
}

// **Generuoti Galutinį Balą pagal Mediana**
template <typename Container>
double generuotiGalmed(Container nd) {
    // Jei konteineris yra LIST, naudojame .sort()
    if constexpr (std::is_same_v<Container, std::list<float>>) {
        nd.sort();
    } else {
        // Jei konteineris yra MyVector arba Deque, naudojame sort()
        std::sort(nd.begin(), nd.end());
    }

    size_t kiek = nd.get_size();
    auto it = nd.begin(); // Pirmas elementas
    std::advance(it, kiek / 2); // Perstumiam per nurodytą sk. elementų

    if (kiek % 2 == 1) {
        return *it;  // Jei nelyginis elementų kiekis, grąžina tą skaičių
    } else {
        auto it2 = it;
        std::advance(it2, -1); // Perkeliame 1 žingsnį atgal
        return (*it + *it2) / 2.0;  // Jei lyginis, grąžina dviejų vidurkius
    }
}

// Funkcija pasirinktam galutiniam balui
template <typename Container>
double pasirinktasGal(Container& nd, int egz, char kaip) {
    double Gal = 0;
    if (kaip == 'v') {
        Gal = generuotiGalvid(nd, egz);
    } else if (kaip == 'm') {
        Gal = 0.4 * generuotiGalmed(nd) + 0.6 * egz;
    }
    return Gal;
}

// Atsitiktinių pažymių generavimas
template <typename Container>
void randomPaz(Container& nd, int& egz, int kiek_nd) {
    nd.clear(); // Pašalina senus duomenis
    for (int i = 0; i < kiek_nd; i++) {
        nd.push_back(rand() % 10 + 1); // Atsitiktiniai pažymiai nuo 1 iki 10
    }
    egz = rand() % 10 + 1; // Egzamino pažymys
}

// Generuoja studentų vardus ir pavardes
void generuotiVardPav(std::string& vardas, std::string& pavarde) {
    static const char* vardai[] = {"Jonas", "Petras", "Mantas", "Dovydas", "Rokas"};
    static const char* pavardes[] = {"Kazlauskas", "Petraitis", "Jankauskas", "Masiulis", "Paulauskas"};

    int varduKiekis = sizeof(vardai) / sizeof(vardai[0]);
    int pavardziuKiekis = sizeof(pavardes) / sizeof(pavardes[0]);

    vardas = vardai[rand() % varduKiekis];
    pavarde = pavardes[rand() % pavardziuKiekis];
}

// SABLONINĖ RŪŠIAVIMO FUNKCIJA
template <typename Container>
void rusiuotiStud(Container& grupe, char rusiavimoPas) {
    if constexpr (std::is_same_v<Container, std::list<typename Container::value_type>>) {
        // Jei konteineris yra LIST, naudojame .sort()
        if (rusiavimoPas == 'v') {
            grupe.sort([](const auto& a, const auto& b) { return a.Vard < b.Vard; });
        } else if (rusiavimoPas == 'p') {
            grupe.sort([](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas == 'g') {
            grupe.sort([](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    } else {
        // Jei konteineris yra MyVector, naudojame sort
        if (rusiavimoPas == 'v') {
            std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Vard < b.Vard; });
        } else if (rusiavimoPas == 'p') {
            std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas == 'g') {
            std::sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    }
}

// Nuskaityti studentų duomenis iš failo
template <typename Container>
void nuskaitymasFile(Container& grupe, const std::string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::string eilute;
    std::getline(failas, eilute);  // Praleidžiame pirmą eilutę (antraštės eilutė)

    using T = typename Container::value_type::nd_type;  // Automatinis konteinerio tipas
    studentas<T> laik;

    while (std::getline(failas, eilute)) {
        std::istringstream ss(eilute); // String stream duomenims iš eilutės
        ss >> laik.Vard >> laik.Pav;

        T laikiniPaz;
        int paz;
        while (ss >> paz) {
            laikiniPaz.push_back(paz); // Pridedame naują pažymį
        }

        if (!laikiniPaz.empty()) {
            laik.egz = laikiniPaz.back();
            laikiniPaz.pop_back();  // Pašaliname egzamino pažymį
        }

        laik.nd = std::move(laikiniPaz);  // Perkeliame visus pažymius į studijų struktūrą
        grupe.push_back(laik);  // Pridedame studentą į grupę
    }
    failas.close();
}

// Rezultatų spausdinimas
void spausdintiRez2(MyVector<studentas<MyVector<float>>>& grupe, bool iFaila, char pasirinkimas, char rusiavimoPas) {
    for (auto& stud : grupe) {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    rusiuotiStud(grupe, rusiavimoPas);

    if (iFaila) {
        MyVector<std::string> eilutes;
        eilutes.reserve(grupe.get_size());

        for (const auto& stud : grupe) {
            std::ostringstream ss;
            ss << std::setw(15) << std::left << stud.Vard << std::setw(20) << stud.Pav << std::setw(17) << std::fixed << std::setprecision(2) << stud.Gal << std::endl;
            eilutes.push_back(ss.str());
        }

        std::string results_dir = "results";
        if (!fs::exists(results_dir)) {
            fs::create_directory(results_dir);
        }

        std::string failoPavadinimas = results_dir + "/rezultatai.txt";
        std::ofstream failas(failoPavadinimas);
        if (!failas) {
            std::cerr << "Nepavyko sukurti failo rezultatams" << std::endl;
            return;
        }

        for (const auto& eil : eilutes) {
            failas.write(eil.c_str(), eil.size());
        }
        failas.close();
        std::cout << "Rezultatai issaugoti faile `rezultatai.txt`.\n";
    } else {
        std::ostringstream buffer;

        buffer << std::setw(15) << std::left << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << ((pasirinkimas == 'v') ? "Galutinis (Vid.)" : "Galutinis (Med.)") << std::endl;
        buffer << "--------------------------------------------------------------" << std::endl;

        for (const auto& stud : grupe) {
            buffer << std::setw(15) << std::left << stud.Vard << std::setw(15) << stud.Pav << std::setw(20) << std::fixed << std::setprecision(2) << stud.Gal << std::endl;
        }

        std::cout.write(buffer.str().c_str(), buffer.str().size());
    }
}

// Explicit instancijavimas su MyVector
template double pasirinktasGal<MyVector<float>>(MyVector<float>&, int, char);
template void randomPaz<MyVector<float>>(MyVector<float>&, int&, int);
template void rusiuotiStud<MyVector<studentas<MyVector<float>>>>(MyVector<studentas<MyVector<float>>>&, char);
template void nuskaitymasFile<MyVector<studentas<MyVector<float>>>>(MyVector<studentas<MyVector<float>>>&, const std::string&);
//template void spausdintiRez<MyVector<studentas<MyVector<float>>>>(MyVector<studentas<MyVector<float>>>&, bool, char, const std::string&);
