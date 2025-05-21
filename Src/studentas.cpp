#include "studentas.h"
#include "zmogus.h"
#include "MyVector.h"
#include <numeric> // dėl accumulate

Studentas::Studentas() : egzaminas_(0), galutinis_balas_(0.0f) {}

Studentas::Studentas(istream& is) {
    readStudent(is);
}

Studentas::Studentas(const Studentas& other)
    : Zmogus(other.vardas(), other.pavarde()),
      egzaminas_(other.egzaminas_),
      nd_(other.nd_),
      galutinis_balas_(other.galutinis_balas_) {}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        setVardas(other.vardas());
        setPavarde(other.pavarde());
        egzaminas_ = other.egzaminas_;
        nd_ = other.nd_;
        galutinis_balas_ = other.galutinis_balas_;
    }
    return *this;
}

Studentas::Studentas(Studentas&& other) noexcept
    : Zmogus(std::move(other.vardas()), std::move(other.pavarde())),
      egzaminas_(other.egzaminas_),
      nd_(std::move(other.nd_)),
      galutinis_balas_(other.galutinis_balas_) {
    other.egzaminas_ = 0;
    other.galutinis_balas_ = 0.0f;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        setVardas(std::move(other.vardas()));
        setPavarde(std::move(other.pavarde()));
        egzaminas_ = other.egzaminas_;
        nd_ = std::move(other.nd_);
        galutinis_balas_ = other.galutinis_balas_;
        other.egzaminas_ = 0;
        other.galutinis_balas_ = 0.0f;
    }
    return *this;
}

int Studentas::destruktoriuSk = 0;

void Studentas::setEgzaminas(int e) { egzaminas_ = e; }
void Studentas::setNamudarbai(const MyVector<float>& nd) { nd_ = nd; }

float Studentas::galBalas(float (*balasFunkcija)(const MyVector<float>&, int)) {
    galutinis_balas_ = balasFunkcija(nd_, egzaminas_);
    return galutinis_balas_;
}

istream& Studentas::readStudent(istream& is) {
    is >> vardas_ >> pavarde_;
    float ndTemp;
    nd_.clear();
    for (int i = 0; i < 5; ++i) {
        is >> ndTemp;
        nd_.push_back(ndTemp);
    }
    is >> egzaminas_;
    galutinis_balas_ = generuotiGalvid(nd_, egzaminas_);
    return is;
}

ostream& operator<<(ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vardas_
       << std::setw(15) << s.pavarde_
       << std::setw(10) << s.egzaminas_
       << std::fixed << std::setprecision(2)
       << std::setw(10) << s.galutinis_balas_;
    return os;
}

istream& operator>>(istream& is, Studentas& s) {
    if (&is == &std::cin) {
        std::string vardas, pavarde;
        MyVector<float> nd;
        float paz;
        int egzaminas;

        std::cout << "Studento vardas: ";
        is >> vardas;
        std::cout << "Studento pavardė: ";
        is >> pavarde;

        std::cout << "Namu darbu pazymiai (iveskite po viena, ENTER uzbaigia): ";
        while (true) {
            is >> paz;
            if (is.fail()) {
                std::cout << "✘ Netinkama įvestis. Įveskite pažymį nuo 1 iki 10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (paz < 1 || paz > 10) {
                std::cout << "✘ Pažymys turi būti nuo 1 iki 10: ";
                continue;
            }
            nd.push_back(paz);
            if (is.peek() == '\n') break;
        }

        std::cout << "Egzamino pažymys: ";
        while (true) {
            is >> egzaminas;
            if (is.fail() || egzaminas < 1 || egzaminas > 10) {
                std::cout << "✘ Egzaminas turi būti nuo 1 iki 10: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }

        s.setVardas(vardas);
        s.setPavarde(pavarde);
        s.setNamudarbai(nd);
        s.setEgzaminas(egzaminas);
        s.galBalas(generuotiGalvid);

    } else {
        return s.readStudent(is);
    }

    return is;
}

void Studentas::rusiuotiStud(MyVector<Studentas>& grupe, char rusiavimoPas) {
    if (rusiavimoPas == 'v') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas() < b.vardas();
        });
    } else if (rusiavimoPas == 'p') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde() < b.pavarde();
        });
    } else if (rusiavimoPas == 'g') {
        std::sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinisBalsas() > b.galutinisBalsas();
        });
    }
}

void Studentas::nuskaitymasFile(MyVector<Studentas>& grupe, const std::string& filename) {
    std::ifstream failas(filename);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    std::string eilute;
    Studentas laik;
    while (std::getline(failas, eilute)) {
        std::istringstream ss(eilute);
        std::string vardas, pavarde;
        int egzaminas;
        MyVector<float> nd;
        float n;

        // Pirmiausia nuskaityti vardą ir pavardę
        if (!(ss >> vardas >> pavarde)) {
            std::cerr << "Klaida skaitant vardą ir pavardę: " << eilute << std::endl;
            continue;
        }

        // Tada 5 namų darbų pažymiai
        nd.clear();
        for (int i = 0; i < 5; ++i) {
            if (!(ss >> n)) {
                std::cerr << "Klaida skaitant namų darbų pažymius: " << eilute << std::endl;
                break;
            }
            nd.push_back(n);
        }

        // Galiausiai egzaminas
        if (!(ss >> egzaminas)) {
            std::cerr << "Klaida skaitant egzamino pažymį: " << eilute << std::endl;
            continue;
        }

        laik.setVardas(vardas);
        laik.setPavarde(pavarde);
        laik.setNamudarbai(nd);
        laik.setEgzaminas(egzaminas);
        laik.galBalas(generuotiGalvid);
        grupe.push_back(laik);

       // std::cout << "Nuskaitytas studentas: " << vardas << " " << pavarde << ", egzaminas: " << egzaminas << std::endl;
    }

    failas.close();
}

float generuotiGalvid(const MyVector<float>& nd, int egz) {
    float suma = 0;
    for (size_t i = 0; i < nd.get_size(); ++i) suma += nd[i];
    float vidurkis = suma / nd.get_size();
    return 0.4f * vidurkis + 0.6f * egz;
}

float generuotiGalmed(const MyVector<float>& nd, int egz) {
    MyVector<float> sorted = nd;
    std::sort(sorted.begin(), sorted.end());
    size_t size = sorted.get_size();
    float mediana = (size % 2 == 0) ?
        (sorted[size / 2 - 1] + sorted[size / 2]) / 2 :
        sorted[size / 2];
    return 0.4f * mediana + 0.6f * egz;
}

Studentas::~Studentas() {
    ++destruktoriuSk;
    nd_.clear();
    //std::cout << "[DESTRUKTORIUS] Išsikvietė. Iš viso: " << destruktoriuSk << "\n";
}
