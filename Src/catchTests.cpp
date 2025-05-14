#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "MyVector.h"

TEST_CASE("Testuojame MyVector funkcijas") {

    SECTION("Testuojame push_back() ir operator[]") {
        MyVector<int> v;
        v.push_back(10);
        v.push_back(20);

        std::vector<int> stdVec;
        stdVec.push_back(10);
        stdVec.push_back(20);

        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 20);
        REQUIRE(v[0] == stdVec[0]);
        REQUIRE(v[1] == stdVec[1]);
    }

    SECTION("Testuojame pop_back()") {
        MyVector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.pop_back();

        std::vector<int> stdVec;
        stdVec.push_back(10);
        stdVec.push_back(20);
        stdVec.pop_back();
        
        REQUIRE(v.get_size() == 1);
        REQUIRE(v[0] == 10);
        REQUIRE(v.get_size() == stdVec.size());
        REQUIRE(v[0] == stdVec[0]);
    }

    SECTION("Testuojame resize() ir reserve()") {
        MyVector<int> v;
        v.push_back(10);
        v.push_back(20);

        std::vector<int> stdVec;
        stdVec.push_back(10);
        stdVec.push_back(20);

        v.resize(5);
        stdVec.resize(5);
        REQUIRE(v.get_size() == 5);  // Patikriname, kad dydis buvo pakeistas į 5
        v.reserve(10);
        REQUIRE(v.get_capacity() >= 10);  // Patikriname, kad kapasitetas buvo padidintas
        REQUIRE(v.get_size() == stdVec.size());
        REQUIRE(v.get_capacity() >= stdVec.capacity());
    }

    SECTION("Testuojame clear() ir empty()") {
        MyVector<int> v;
        v.push_back(10);
        v.push_back(20);

        std::vector<int> stdVec;
        stdVec.push_back(10);
        stdVec.push_back(20);

        v.clear();
        stdVec.clear();

        REQUIRE(v.empty() == true);  // Patikriname, kad vektorius yra tuščias
        REQUIRE(v.empty() == stdVec.empty());
    }

    SECTION("Testuojame kopijavimo operatorių") {
        MyVector<int> v;
        v.push_back(10);
        v.push_back(20);

        std::vector<int> stdVec;
        stdVec.push_back(10);
        stdVec.push_back(20);

        MyVector<int> v2 = v;
        std::vector<int> stdVecCopy = stdVec;

        REQUIRE(v2[0] == 10);  // Patikriname, kad vektorius buvo teisingai nukopijuotas
        REQUIRE(v2[1] == 20);

        REQUIRE(v2[0] == stdVecCopy[0]);
        REQUIRE(v2[1] == stdVecCopy[1]);
    }

      SECTION("Testuojame shrink_to_fit()") {
        MyVector<int> v;
        for (int i = 0; i < 10; ++i) v.push_back(i);
        size_t before = v.get_capacity();

        for (int i = 0; i < 5; ++i) v.pop_back();
        v.shrink_to_fit();

        REQUIRE(v.get_capacity() == v.get_size());
        REQUIRE(v.get_capacity() < before);
    }

    SECTION("Testuojame insert()") {
        MyVector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.insert(1, 2);

        std::vector<int> stdVec = {1, 3};
        stdVec.insert(stdVec.begin() + 1, 2);

        REQUIRE(v.get_size() == stdVec.size());
        for (size_t i = 0; i < v.get_size(); ++i)
            REQUIRE(v[i] == stdVec[i]);
    }


    SECTION("Testuojame erase()") {
        MyVector<int> v = {1, 2, 3};
        std::vector<int> stdVec = {1, 2, 3};

        v.erase(1);  // Šalina elementą 2
        stdVec.erase(stdVec.begin() + 1);

        REQUIRE(v.get_size() == stdVec.size());
        for (size_t i = 0; i < v.get_size(); ++i)
            REQUIRE(v[i] == stdVec[i]);
    }
}
