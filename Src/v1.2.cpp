#include "studentas.h"
#include "LaikoMatavimas.h"
#include "strategija3.h"
#include "versijos1Funkc.h"
#include "testRuleOf5.h"
#include "catch_amalgamated.hpp" 
#include "sparta.h"
#include "perskirstymai.h"
#include "MyVector.h"


// Jūsų kitos įtrauktos reikalingos bibliotekos
void vykdytiPrograma(){
    srand(time(0)); //pradinis seed nustatymas
    
    vector<studentas<vector<float>>> grupe;
    char pasirinkimas;
    char rusiavimoPas;
    char isvedimoPasirinkimas;
    int meniu;
    
    LaikoMatavimas programa("Bendras programos vykdymas");
    programa.pradeti();
    
    do
    {
        studentas<vector<float>> laik;
        int kiek_nd;
    
    cout<<"Pasirinkite meniu veiksma: \n";
    cout<<"1 - Ivesti ranka\n2 - Generuoti pazymius\n3 - Generuoti vardus, pavardes ir pazymius\n4 - Nuskaityti is failo\n5 - Baigti\n ";
    cin>>meniu;
    
    if (cin.fail() || meniu < 1 || meniu > 5) {
            cout << "Klaida! Pasirinkite skaičių nuo 1 iki 5.\n";
            cin.clear();  // Išvalome klaidos būseną
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Pašaliname blogą įvestį
            continue;  // Praleidžiame likusią ciklo iteraciją ir grįžtame prie meniu
        }
    
        if (meniu==5) break;
    
        if(meniu==4) 
        {

            LaikoMatavimas failoNuskaitymas("Failo nuskaitymas");
            failoNuskaitymas.pradeti();
        try
        {
            nuskaitymasFile(grupe, "../test_files/studentai_1000.txt");
        } 
        catch (const std::exception& e)
        {
            cerr << "Klaida nuskaitant failą: " << e.what() <<endl;
            continue;
        }
    
            failoNuskaitymas.baigti();
            continue;
        }
    
        if (meniu==1 || meniu==3 || meniu==2)
        {
            if(meniu==3) generuotiVardPav(laik.Vard, laik.Pav);
            else if(meniu==2 || meniu==1)
            {
                cout<<"Studento vardas: ";
                cin>>laik.Vard;
        
                cout<<"Studento pavarde: ";
                cin>>laik.Pav;
            }
        }
        if(meniu==2 || meniu==3)
        {
            cout<<"Kiek nd pazymiu generuoti? ";
            cin>>kiek_nd;
            randomPaz(laik.nd, laik.egz, kiek_nd);
        }
        else 
        {
            cout<<"Namu darbu pazymiai ";
            float paz;
        while (true) 
        {
            cin >> paz;
    
        if (cin.fail())  //Netinkamas input
        {   
            cout<< "Iveskite pazymi nuo 1 iki 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //isvaloma bloga ivestis
            continue; //tesiam cikla
        }
        if(paz<1 || paz>10)
        {
            cout<<"Iveskite pazymi nuo 1 iki 10: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; //tesiam cikla
        }
    
        laik.nd.push_back(paz); //idedame i vektoriu
        if (cin.peek() == '\n') break; //kai enter, baigiama ivestis
        }
            
        cout<<"Studento egzaminas: ";
        while (true)
        {
            cin>>laik.egz;
            if(cin.fail() || laik.egz < 1 || laik.egz > 10) {
            cout << "Egzamino pazymys turi būti nuo 1 iki 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
            }
        break;
        }
    }
    grupe.push_back(laik);
    
    } while(true);
    
    cout<<"Koki metoda renkates gal. balui skaiciuoti?\n";
    cout<<" [v] - vidurki\n [m] - mediana\n";
    cin>>pasirinkimas;
    while (pasirinkimas != 'v' && pasirinkimas != 'm') {
            cout << "Neteisingas pasirinkimas! Įveskite v arba m: ";
            cin >> pasirinkimas;
    }
    
    cout<<"Pagal ka rusiuoti studentus?:\n [v] - varda\n [p] - pavarde\n [g] - galutini bala\n";
    cin>>rusiavimoPas;
    
     cout<<"Kur vesti rezultatus?\n [e] - ekrane\n [f] - i faila\n ";
     cin>>isvedimoPasirinkimas;
    
     bool iFaila=(isvedimoPasirinkimas=='f'); //jei f -true, jei e-false
    
    try
    {
        LaikoMatavimas rezultatuIsvedimas("Rezultatu isvedimas");
        rezultatuIsvedimas.pradeti();
        spausdintiRez2( grupe, iFaila, pasirinkimas, rusiavimoPas);
        rezultatuIsvedimas.baigti();
    }
    catch(const std::exception& e)
    {
        cerr << "Klaida išvedant rezultatus: " << e.what() <<endl;
    }
       
     programa.baigti();
    
    }


void meniu() {
    cout<<"      PASIRINKITE VEIKSMA      \n";
    cout<<" [A] - Vykdyti programa\n";
    cout<<" [B] - Tyrimas 6 (3 strategija)\n";
    cout<<" [T] - Testuoti Rule of Five ir IO operatorius\n";
    cout<<" [V] - Testuoti MyVector spartą ir perskirstymus\n";
    cout<<" [0] - Baigti\n";
    cout<<" PASIRINKIMAS: ";
}

string pasirinktiFaila(){
    string failas;
    int pasirinkimas2;
    cout<<" \n Pasirinkite testavimo FAILA: \n";
    cout << "[1] - 1000 studentų\n";
    cout << "[2] - 10 000 studentų\n";
    cout << "[3] - 100 000 studentų\n";
    cout << "[4] - 1 000 000 studentų\n";
    cout << "[5] - 10 000 000 studentų\n";
    cout<<" PASIRINKIMAS: ";

    cin>>pasirinkimas2;

    switch (pasirinkimas2) {
        case 1: failas= "../test_files/studentai_1000.txt"; break;
        case 2: failas= "../test_files/studentai_10000.txt"; break;
        case 3: failas= "../test_files/studentai_100000.txt"; break;
        case 4: failas= "../test_files/studentai_1000000.txt"; break;
        case 5: failas= "../test_files/studentai_10000000.txt"; break;
        default:
            cout<<"NETEISINGAS pasirinkimas!! Naudojamas failas su 1000 studentu \n";
            failas= "test_files/studentai_1000.txt"; 
    }
    return failas;
   
}

int main(){
    string failas;
    string rezultataiAplankas= "rezultatai";

    char pasirinkimas;
    do {
        meniu();
        cin>>pasirinkimas;
         
        switch(pasirinkimas){
            case 'A':
                cout<<"Vykdoma programa....\n";
                vykdytiPrograma();
                break;

            case 'B':
                cout<<"Vykdomas Tyrimas 6...\n";
                failas = pasirinktiFaila();
                testuotiSkaidymoStrategija3(failas, rezultataiAplankas);
                break;

            case 'T':
                cout<<"Vykdomi Rule of Five testai...\n";
                testuotiRuleOfFive();  
                break;

            case 'V':
                cout << "Testuojama MyVector sparta ir perskirstymų skaičius:\n";
                {
                std::vector<unsigned int> dydziai = {10000, 100000, 1000000, 10000000};
                for (unsigned int d : dydziai) matuotiSparta(d);
                skaiciuotiPerskirstymus(100000000);
                }
                break;

             case '0':
                cout<<"PROGRAMA BAIGTA.\n";
                break;

             default:
                cout<<"NETEISINGAS Pasirinkimas!! Bandyti dar karta (A ARBA B).\n";
               break;
            } 

        } while(pasirinkimas!='0');

    return 0;
}
