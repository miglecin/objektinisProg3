#include "versijos1Funkc.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>  // rand() funkcijai
#include <string> 
#include <numeric>

namespace fs = std::filesystem;

template <typename Container>
double generuotiGalvid(Container& nd, int egz) 
{
    double suma= 0;
    for (const auto& paz : nd) 
    {
        suma += paz;
    }
    double vidurkis=suma/ nd.size();
    return 0.4 * vidurkis + 0.6 * egz;
}

template <typename Container>
double generuotiGalmed(Container nd) 
{
    if constexpr (std::is_same_v<Container, list<float>>) 
    {
        // Jei konteineris yra LISTAS, naudojame .sort()
        nd.sort();
    } 
    else 
    {
        //jei konteineris yra VECTOR arba DEQUE, naudojame sort()
        sort(nd.begin(), nd.end());
    }
    size_t kiek=nd.size();
    auto it=nd.begin(); //pirmas elementas
    std::advance(it, kiek / 2); //perstumia per nurodyta sk elementu. Jis butina listui, nes jis neduoda random access ir neveiktu it+n

    if (kiek%2== 1) 
    {
        return *it;  // Jei nelyginis elementų kiekis, grazina ta sk
    } 
    else 
    {
        auto it2=it; //sukuria kopija it, kuris yra vidurinis elem
        std::advance(it2, -1); //perkialia 1 zingsniu atgal
        return (*it + *it2) / 2.0;  //Jei lyginis, grazina dvieju vid, * - kad gauti reiskmes o ne adresus
    }
}

//Funkcija pasirinktam galutiniam balui 
template <typename Container>
double pasirinktasGal(Container& nd, int egz, char kaip) 
{
    double Gal=0;
    if (kaip=='v') 
    {
        Gal=generuotiGalvid(nd, egz);
    } else if (kaip=='m') 
    {
        Gal=0.4 * generuotiGalmed(nd) + 0.6 * egz;
    }
    return Gal;
}

template <typename Container>
void randomPaz(Container& nd, int& egz, int kiek_nd)
{
    nd.clear(); //pasalina senus duomenis
    for (int i= 0; i<kiek_nd; i++) 
    {
        nd.push_back(rand() % 10 + 1); //atsitiktiniai paz nuo 1 iki 10
    }
    egz=rand() % 10 + 1; //egz paz
}

void generuotiVardPav(std::string& vardas, std::string& pavarde) 
{
    static const char* vardai[] = {"Jonas", "Petras", "Mantas", "Dovydas", "Rokas"};
    static const char* pavardes[] = {"Kazlauskas", "Petraitis", "Jankauskas", "Masiulis", "Paulauskas"};

    int varduKiekis = sizeof(vardai) / sizeof(vardai[0]);
    int pavardziuKiekis = sizeof(pavardes) / sizeof(pavardes[0]);

    vardas = vardai[rand() % varduKiekis];
    pavarde = pavardes[rand() % pavardziuKiekis];
}

//SABLONINĖ RUSIAVIMO FUNKCIJA
template <typename Container>
void rusiuotiStud(Container& grupe, char rusiavimoPas) {
    if constexpr (std::is_same_v<Container, list<typename Container::value_type>>) //kompiliavimo metu tikrina, ar konteineris yra listas
    { 
        //jei konteineris yra LIST, tada .sort() 
        if (rusiavimoPas=='v') {
            grupe.sort([](const auto& a, const auto& b) { return a.Vard < b.Vard; }); //[] – lambda capture list, tuščia, nes nereikia jokių kintamųjų iš išorės
        } else if (rusiavimoPas=='p') {
            grupe.sort([](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas=='g') {
            grupe.sort([](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    } 
    else 
    {
        //jei konteineris yra VECTOR arba DEQUE, tada sort
        if (rusiavimoPas=='v') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Vard < b.Vard; });
        } else if (rusiavimoPas=='p') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Pav < b.Pav; });
        } else if (rusiavimoPas=='g') {
            sort(grupe.begin(), grupe.end(), [](const auto& a, const auto& b) { return a.Gal > b.Gal; });
        }
    }
}

template <typename Container>
void nuskaitymasFile(Container& grupe, const string& filename)
{
    ifstream failas(filename);
     if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    string eilute;
    getline(failas, eilute); //praleidziam pirma eilute (antrastes eilute)

    using T = typename Container::value_type::nd_type; //automatinis konteinerio tipas (vector, list, deque)
    studentas<T> laik; //automatinis prisitaikymas pagal tipa
    
    while(getline(failas, eilute)) //skaito kiekviena eil atskirai
    
    {
        istringstream ss(eilute); //naudojame string stream duom skaitymui is eilutes
        ss>>laik.Vard>>laik.Pav;

        int paz;
        laik.nd.clear(); //isvalom ankstesnius duom is vekt jei ju buvo

        T laikiniPaz; //naudoja toki konteineri, kokia yra grupe, (value_type - studentas, nd_type - konteinerio tipas kur saugomi paz)
         while (ss>>paz) //nuskaitom visus sk is eilutes ir dedam i laikiniPaz
        {
            laikiniPaz.push_back(paz);
        }

        //Paskutinis nuskaitytas sk. yra egzamino pazymys
        if (!laikiniPaz.empty()) {
            laik.egz = laikiniPaz.back();
            laikiniPaz.pop_back();  //Pasaliname egzamina is ND saraso
        } 
        laik.nd=move(laikiniPaz); //perkeliamia visus pazymius i stud struktura
        grupe.push_back(laik); //pridedam studenta i studentu sarasa
    }
    failas.close();
}
void spausdintiRez2( vector<studentas<vector<float>>> grupe, bool iFaila, char pasirinkimas, char rusiavimoPas)
{
    //pirma- apskaiciuoti galutinius balus
    for (auto& stud : grupe) 
    {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    //antra- sursiuoti studentus
    rusiuotiStud(grupe, rusiavimoPas);
    
if (iFaila) //jei i faila
{
    vector<string> eilutes; //vektorius eilutems kaupti
    eilutes.reserve(grupe.size()); //rezervuojam vieta is anksto visiems studentams

    for(const auto& stud : grupe) //sukaupiam visus rezultatus i vektoriu (kad veliau vienu metu atspausdint)
    {
        ostringstream ss; //naudjam ostringstream kad surinktumevisus stud duom i eil
        ss<<setw(15)<<std::left<<stud.Vard<<setw(20)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
        eilutes.push_back(ss.str()); //irasom suformuota eil i vekt
    }
        
     //Sukuriam kataloga results, jei jo nėra
     string results_dir = "results";
     if (!fs::exists(results_dir)) {
         fs::create_directory(results_dir);
     }

     // Sukuriam faila
     string failoPavadinimas = results_dir + "/rezultatai.txt";
     ofstream failas(failoPavadinimas);
     if(!failas)
        {
            cerr<<"nepavyko sukurti failo rezultatams";
            return;
        }

    for (const auto& eil : eilutes) //Rašome visas eilutes į failą vienu kartu (taip išvengiame lėto spausdinimo per `<<`)
    {
        failas.write(eil.c_str(), eil.size()); //Rašoma tiesiogiai iš `c_str()` į failą
    }
    failas.close();
    cout<<"Rezultatai issaugoti faile `rezultatai.txt`.\n";
}
else //jei i ekrana
{
    //optimizuotas isvedimas i ekrana
    ostringstream buffer;

    buffer<<setw(15)<<std::left<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<((pasirinkimas =='v') ? "Galutinis (Vid.)" : "Galutinis (Med.)")<<endl;
    buffer<<"--------------------------------------------------------------"<< endl;

    for (const auto& stud : grupe) //visi duom i bufferi, kad isvengt leto cout
    {
        buffer<<setw(15)<<std::left<<stud.Vard<<setw(15)<<stud.Pav<<setw(20)<<fixed<<setprecision(2)<<stud.Gal<< endl;
    }
    std::cout.write(buffer.str().c_str(), buffer.str().size()); //Galutinis `cout.write()`, kuris leidžia išvesti viską iš karto ir pagreitina procesą
}
}

template <typename Container>
void spausdintiRez(Container& grupe, bool iFaila, char pasirinkimas, const string& failoPavadinimas)
{
    //pirma- apskaiciuoti galutinius balus
    for (auto& stud : grupe) 
    {
        stud.Gal = pasirinktasGal(stud.nd, stud.egz, pasirinkimas);
    }

    //antra- sursiuoti studentus
    rusiuotiStud(grupe, 'g');
    
if (iFaila) //jei i faila
{
    vector<string> eilutes; //vektorius eilutems kaupti
    eilutes.reserve(grupe.size()); //rezervuojam vieta is anksto visiems studentams

    for(const auto& stud : grupe) //sukaupiam visus rezultatus i vektoriu (kad veliau vienu metu atspausdint)
    {
        ostringstream ss; //naudjam ostringstream kad surinktumevisus stud duom i eil
        ss<<setw(15)<<std::left<<stud.Vard<<setw(20)<<stud.Pav<<setw(17)<<fixed<<setprecision(2)<<stud.Gal<< endl;
        eilutes.push_back(ss.str()); //irasom suformuota eil i vekt
    }
        
    ofstream failas(failoPavadinimas);
        if (!failas) {
            cerr << "Nepavyko sukurti failo: " << failoPavadinimas << endl;
            return;
        }

    for (const auto& eil : eilutes) //Rašome visas eilutes į failą vienu kartu (taip išvengiame lėto spausdinimo per `<<`)
    {
        failas.write(eil.c_str(), eil.size()); //Rašoma tiesiogiai iš `c_str()` į failą
    }
    failas.close();
    cout<<"Rezultatai issaugoti faile" << failoPavadinimas << "`.\n";
    }
else //jei i ekrana
{
    //optimizuotas isvedimas i ekrana
    ostringstream buffer;

    buffer<<setw(15)<<std::left<<"Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<((pasirinkimas =='v') ? "Galutinis (Vid.)" : "Galutinis (Med.)")<<endl;
    buffer<<"--------------------------------------------------------------"<< endl;

    for (const auto& stud : grupe) //visi duom i bufferi, kad isvengt leto cout
    {
        buffer<<setw(15)<<std::left<<stud.Vard<<setw(15)<<stud.Pav<<setw(20)<<fixed<<setprecision(2)<<stud.Gal<< endl;
    }
    std::cout.write(buffer.str().c_str(), buffer.str().size()); //Galutinis `cout.write()`, kuris leidžia išvesti viską iš karto ir pagreitina procesą
}
}

// Explicit instantiation of templates to avoid linker issues
template double pasirinktasGal<std::vector<float>>(std::vector<float>&, int, char);
template double pasirinktasGal<std::list<float>>(std::list<float>&, int, char);
template double pasirinktasGal<std::deque<float>>(std::deque<float>&, int, char);

template void randomPaz<std::vector<float>>(std::vector<float>&, int&, int);
template void randomPaz<std::list<float>>(std::list<float>&, int&, int);
template void randomPaz<std::deque<float>>(std::deque<float>&, int&, int);

template void rusiuotiStud<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, char);
template void rusiuotiStud<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, char);
template void rusiuotiStud<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, char);


// Aiškiai instancijuojame nuskaitymo funkciją
template void nuskaitymasFile<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, const std::string&);
template void nuskaitymasFile<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, const std::string&);
template void nuskaitymasFile<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, const std::string&);

template void spausdintiRez<std::vector<studentas<std::vector<float>>>>(std::vector<studentas<std::vector<float>>>&, bool, char, const std::string&);
template void spausdintiRez<std::list<studentas<std::list<float>>>>(std::list<studentas<std::list<float>>>&, bool, char, const std::string&);
template void spausdintiRez<std::deque<studentas<std::deque<float>>>>(std::deque<studentas<std::deque<float>>>&, bool, char, const std::string&);
