#include "studentas.h"
#include "testRuleOf5.h"
#include "MyVector.h"
#include <cassert>

void testuotiRuleOfFive() {
    // === 1. Originalus objektas ===
    std::cout << "\n[TEST 1] Originalaus objekto sukurimas\n";
    Studentas s1;
    s1.setVardas("Testas");
    s1.setPavarde("Kopija");
    s1.setEgzaminas(9);
    s1.setNamudarbai(MyVector<float>{10, 9, 8, 7, 6});
    s1.galBalas(generuotiGalvid);
    std::cout << "Sukurtas s1: " << s1 << "\n";

    // === 2. Kopijavimo konstruktorius ===
    std::cout << "\n[TEST 2] Kopijavimo konstruktorius (s2 kopija is s1)\n";
    Studentas s2(s1);
    std::cout << "Kopijuotas s2: " << s2 << "\n";
    assert(s2.vardas() == s1.vardas());

    // === 3. Kopijavimo operatorius ===
    std::cout << "\n[TEST 3] Kopijavimo operatorius (s3 = s1)\n";
    Studentas s3;
    s3 = s1;
    std::cout << "Kopijuotas s3: " << s3 << "\n";
    assert(s3.pavarde() == s1.pavarde());

    // === 4. Perkelimo konstruktorius ===
    std::cout << "\n[TEST 4] Move konstruktorius (s4 = move(s1))\n";
    Studentas s4(std::move(s1));
    std::cout << "Perkeltas s4: " << s4 << "\n";
    assert(s4.egzaminas() == 9);

    // === 5. Perkelimo operatorius ===
    std::cout << "\n[TEST 5] Move operatorius (s5 = move(s2))\n";
    Studentas s5;
    s5 = std::move(s2);
    std::cout << "Perkeltas s5: " << s5 << "\n";
    assert(!s5.nd().empty());

    // === 6. Išvesties operatorius ===
    std::cout << "\n[TEST 6] Isvesties operatorius (<<)\n";
    std::ostringstream oss;
    oss << s5;
    std::cout << "Isvestas s5: " << oss.str() << "\n";
    assert(oss.str().find("Kopija") != std::string::npos);

    // === 7. Įvestis iš stringstream ===
    std::cout << "\n[TEST 7] Ivesties operatorius (>> is istringstream)\n";
    std::istringstream iss("Vardenis Pavardenis 10 10 10 10 10 10");
    Studentas s6;
    iss >> s6;
    std::cout << "Ivestas s6: " << s6 << "\n";
    assert(s6.vardas() == "Vardenis");

    // === 8. Failo nuskaitymas su Studentas::nuskaitymasFile ===
    std::cout << "\n[TEST 8] Failo nuskaitymas su nuskaitymasFile()\n";
    std::ofstream testFailas("studentai.txt");
    testFailas << "Jonas Jonaitis 10 9 8 7 6 8\n";
    testFailas << "Petras Petrauskas 8 9 7 10 5 7\n";
    testFailas.close();

    MyVector<Studentas> grupe;
    Studentas::nuskaitymasFile(grupe, "studentai.txt");
    std::cout << "Gauta studentu: " << grupe.get_size() << "\n";
    assert(grupe.get_size() == 2);
    assert(grupe[0].vardas() == "Jonas");
    assert(grupe[1].vardas() == "Petras");

    // === 9. Išvedimas į ekraną ir į failą ===
    std::cout << "\n[TEST 9] Isvedimas i ekrana ir i faila\n";

    std::cout << "Studentu rezultatai:\n";
    for (const auto& s : grupe) std::cout << s << "\n";

    std::ofstream out("rezultataiT.txt");
    for (const auto& s : grupe) out << s << "\n";
    out.close();

    // === 10. Destruktoriaus testas ===
    //std::cout << "\n[TEST 10] Destruktoriaus kvietimo testas\n";
    {
        //Studentas laikinas;
    }
    //std::cout << "Destruktoriaus kvietimu skaicius: " << Studentas::destruktoriuSk << "\n";

    std::cout << "\n Visi testai su MyVector praėjo sėkmingai!\n\n";
}
