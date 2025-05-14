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

