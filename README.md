# Objektinis Programavimas – ObjektinisProg3 projektas
# MyVector – std::vector alternatyva

Šis projektas įgyvendina `MyVector` šabloninę klasę, kuri funkcionalumu siekia atkartoti `std::vector`. Klasė parašyta naudojant C++11 ir palaiko didžiąją dalį `std::vector` metodų bei operatorių.

##  Tikslas

- Sukurti pilnavertę `std::vector` alternatyvą.
- Užtikrinti, kad bent **80% `std::vector` funkcionalumo** būtų padengta.
- Parašyti **vienodus testus** abiem klasėms (`std::vector` ir `MyVector`), kad būtų galima palyginti rezultatus.

---

# MyVector klasės funkcionalumas

## Pagrindinės modifikavimo funkcijos

| Funkcija                     | Aprašymas                                              |
|-----------------------------|--------------------------------------------------------|
| `push_back(const T&)`       | Prideda elementą į vektoriaus galą                    |
| `pop_back()`                | Pašalina paskutinį elementą                           |
| `clear()`                   | Išvalo vektorių (dydis = 0)                           |
| `resize(size_t)`            | Keičia vektoriaus dydį                                 |
| `reserve(size_t)`           | Rezervuoja nurodytą atminties kiekį                    |
| `shrink_to_fit()`           | Sumažina talpą iki dabartinio dydžio                  |
| `assign(size_t, const T&)`  | Priskiria n elementų su ta pačia reikšme              |

---

##  Iteratoriai

| Funkcija           | Aprašymas                                  |
|--------------------|---------------------------------------------|
| `begin()`          | Grąžina rodyklę į pirmą elementą            |
| `end()`            | Grąžina rodyklę į paskutinį + 1 elementą    |
| `begin() const`    | Const versija                               |
| `end() const`      | Const versija                               |

---

## Prieigos funkcijos

| Funkcija                | Aprašymas                                              |
|-------------------------|---------------------------------------------------------|
| `operator[](size_t)`    | Tiesioginė prieiga pagal indeksą                       |
| `at(size_t)`            | Saugus pasiekimas, meta `std::out_of_range` jei klaida |
| `front()`               | Grąžina pirmą elementą                                 |
| `back()`                | Grąžina paskutinį elementą                             |

---

## Valdymo funkcijos

| Funkcija             | Aprašymas                              |
|----------------------|-----------------------------------------|
| `empty() const`      | Patikrina, ar vektorius tuščias         |
| `get_size() const`   | Grąžina elementų kiekį (dydį)           |
| `get_capacity() const`| Grąžina rezervuotą atminties kiekį     |

---

## Rule of Five metodai

| Funkcija                        | Aprašymas                                   |
|---------------------------------|----------------------------------------------|
| `MyVector(const MyVector&)`     | Kopijavimo konstruktorius                   |
| `MyVector& operator=(const MyVector&)` | Kopijavimo operatorius             |
| `MyVector(MyVector&&)` noexcept | Perkėlimo konstruktorius                    |
| `MyVector& operator=(MyVector&&)` noexcept | Perkėlimo operatorius         |
| `~MyVector()`                   | Destruktorius                                |

---

## Papildomos funkcijos

| Funkcija                      | Aprašymas                                       |
|-------------------------------|--------------------------------------------------|
| `swap(MyVector& other)`       | Sukeičia du vektorius (naudojant `std::swap`)   |
| `insert(size_t pos, const T&)`| Įterpia elementą nurodytoje pozicijoje          |
| `erase(size_t pos)`           | Pašalina elementą nurodytoje pozicijoje         |

---

## Testavimas

Naudota **Catch2** biblioteka automatizuotiems testams.

Testų failas: `catchTests.cpp`

Žemiau pateiktas sąrašas funkcijų, kurios buvo ištestuotos Catch2 pagalba, siekiant užtikrinti, kad `MyVector` elgiasi taip pat kaip `std::vector`.

| Nr. | Funkcija           | Tikslas                                                                 |
|-----|--------------------|-------------------------------------------------------------------------|
| 1️ | `push_back()`       | Patikrina, ar elementai teisingai pridedami į vektoriaus galą           |
| 2️ | `pop_back()`        | Patikrina, ar paskutinis elementas pašalinamas                          |
| 3️ | `resize()`          | Tikrinama, ar dydis tinkamai keičiasi                                   |
| 4️ | `reserve()`         | Patikrinama, ar rezervuojama atmintis teisingai                         |
| 5️ | `clear()`           | Patikrina, ar vektorius tampa visiškai tuščias                         |
| 6️ | `empty()`           | Lygina, ar abu vektoriai (`std::vector` ir `MyVector`) atpažįsta tuštumą vienodai |
| 7️ | **Kopijavimas**     | Patikrina, ar `MyVector` gali būti teisingai kopijuotas (copy constructor ir operator=) |
| 8️ | `shrink_to_fit()`   | Tikrina, ar vektoriaus talpa sumažėja iki dabartinio dydžio             |
| 9️ | `insert(pos, val)`  | Lygina įterpimo funkcijos rezultatą su `std::vector::insert()`         |
| 10 | `erase(pos)`         | Lygina trynimo funkcijos rezultatą su `std::vector::erase()`           |

>  Šios funkcijos padengia esminį `std::vector` funkcionalumo spektrą (daugiau nei 80 %), todėl `MyVector` klasė yra tinkama kaip alternatyva.

### Paleidimas

```bash
mkdir build && cd build
cmake ..
make
./tests
```
-----------------------------------------------------------
### Efektyvumo analizė: `std::vector` vs `MyVector`

Buvo atliktas eksperimentas, kurio metu matuotas laikas (milisekundėmis), kiek užtrunka `std::vector` ir `MyVector` užpildymas `push_back()` metodu su skirtingais `int` elementų kiekiais:

| Elementų skaičius | `std::vector` (ms) | `MyVector` (ms) |
|-------------------|--------------------|------------------|
| 10,000            | 0.623              | 0.073            |
| 100,000           | 5.667              | 0.676            |
| 1,000,000         | 47.516             | 5.243            |
| 10,000,000        | 454.014            | 65.103           |

###  Išvados

- `MyVector` yra akivaizdžiai spartesnis nei `std::vector` testavimo sąlygomis.
- Skirtumas ypač išryškėja su didesniais duomenų kiekiais.
- `std::vector` naudoja papildomas saugumo ir optimizavimo strategijas (tokias kaip exception safety, iterator compatibility ir pan.), tuo tarpu `MyVector` realizuotas supaprastintu būdu, leidžiančiu pasiekti geresnį našumą.

###  Testavimo metodika

Eksperimentas atliktas naudojant `std::chrono::high_resolution_clock`:

```cpp
auto start = high_resolution_clock::now();
for (unsigned int i = 1; i <= N; ++i)
    v.push_back(i);
auto end = high_resolution_clock::now();
```

-----------------------------------------------
### Atminties perskirstymų palyginimas

Atliekant testą su (`100000000`) `int` tipo elementų:

| Konteineris     | Perskirstymų skaičius |
|------------------|------------------------|
| `std::vector`    | 28                     |
| `MyVector`       | 27                     |

### Išvados:
- Abi struktūros elgiasi labai panašiai.
- `MyVector` naudoja `capacity *= 2` metodą, kuris lemia mažą kiekį perskirstymų.
- `std::vector` gali naudoti šiek tiek kitokį augimo algoritmą, todėl kartais perskirstymų daugiau.

Šis testas parodo, kad `MyVector` klasė yra efektyviai įgyvendinta ir savo elgsena artima standartinei `std::vector` klasei.

-----------------------------------------------
### Spartos analizė
## Pagrindinės funkcijos:
- **Skaitymo, rūšiavimo, skaidymo į grupes ir spausdinimo operacijų laiko matavimas**: Išmatuoti laikai kiekvienam žingsniui naudojant tiek `std::vector`, tiek `MyVector` konteinerį.

---

## Testavimo duomenys

Testavimo metu buvo naudojami šie duomenų dydžiai:

- **100 000 studentų** įrašų
- **1 000 000 studentų** įrašų
- **10 000 000 studentų** įrašų

### Laiko matavimai
**Vidurkiai**:

#### 100 000 studentų

| Testuojamas konteineris | Failo nuskaitymas (ms) | Studentų rūšiavimas (ms) | Studentų skaidymas į grupes (ms) | Studentų spausdinimas (ms) |
|-------------------------|------------------------|--------------------------|---------------------------------|----------------------------|
| **`std::vector`**        | 513.8                  | 63.70                    | 77.80                           | 377.19                     |
| **`MyVector`**           | 579.83                 | 31.13                    | 94.89                           | 368.35                     |


#### 1 000 000 studentų

| Testuojamas konteineris | Failo nuskaitymas (ms) | Studentų rūšiavimas (ms) | Studentų skaidymas į grupes (ms) | Studentų spausdinimas (ms) |
|-------------------------|------------------------|--------------------------|---------------------------------|----------------------------|
| **`std::vector`**        | 4658.68                | 599.11                   | 994.08                          | 3732.36                    |
| **`MyVector`**           | 5766.71                | 293.35                   | 1223.88                         | 3791.07                    |


#### 10 000 000 studentų

| Testuojamas konteineris | Failo nuskaitymas (ms) | Studentų rūšiavimas (ms) | Studentų skaidymas į grupes (ms) | Studentų spausdinimas (ms) |
|-------------------------|------------------------|--------------------------|---------------------------------|----------------------------|
| **`std::vector`**        | 48272.5                | 5947.90                  | 10545.80                        | 39308.10                   |
| **`MyVector`**           | 59547.2                | 2888.69                  | 11184.10                        | 37175.10                   |

---

## Išvados

1. **Spartos skirtumai**: Palyginus laikus su **`std::vector`** ir **`MyVector`** konteineriais, skirtumai buvo minimalių dydžių. **`std::vector`** užtrunka šiek tiek daugiau laiko, tačiau tai gali būti dėl optimizacijų, kurias teikia C++ standartinė biblioteka. **`MyVector`** turi šiek tiek mažesnį laiką rūšiavimui ir spausdinimui, tačiau kitose operacijose skirtumai nėra dideli.

2. **Atminties naudojimas**: Tiek **`std::vector`**, tiek **`MyVector`** naudoja panašias atminties valdymo technikas, todėl atminties sąnaudos yra panašios.

3. **Veikimo stabilumas**: Abi realizacijos gerai veikia su dideliais duomenų kiekiais, nes didėjant duomenų kiekiui (iki 10 milijonų studentų) laikai auga, tačiau neproporcingai didėja, kas rodo stabilų veikimą.

---
