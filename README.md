# vectors

vector klasė kurta remiantis cplusplus.com vector dokumentacija: https://www.cplusplus.com/reference/vector/vector/

### Funkcijos:
1. Iterators: begin(), end(), rbegin(), rend()
2. Capacity: size(), max_size(), resize(), capacity(), empty(), reserve(), shrink_to_fit()
3. Element access: operator[], at(), front(), back(), data()
4. Modifiers: assign(), push_back(), pop_back(), insert(), erase(), swap(), clear(), emplace(), emplace_back()
5. Bool operators: ==, !=, <, >, <=, >=
6. ReAlloc funkcija

### Programoje dažniausiai naudotos funkcijos:
1. begin() - grąžina iteratorių į vektoriaus pirmą elementą
2. end() - grąžina iteratorių į vektoriaus paskutinį elementą
3. size() - grąžina vektoriaus elementų skaičių
4. resize() - pakeičia vektoriaus dydį
5. empty() - patikrina ar vektorius yra tuščias
6. reserve() - pakeičia vektoriaus talpą (capacity)
7. shrink_to_fit() - sulygina vektoriaus dydį ir talpą
8. operator[] - leidžia pasirinkti i-ąjį vektoriaus elementą
9. push_back() - įdedą elementą į vektoriaus galą
10. pop_back() - ištrina paskutinįjį vektoriaus elementą
11. clear() - išvalo vektorių
12. ReAlloc() - pakeičia vektoriaus talpą

### Įvykdyti atminties perskirtymai:
std::vector - 
vector - 

### Užpildymo spartos analizė su Int
|           INT          |       10000      |      100000     |     1000000    |   10000000   |
| ------------------- | --------------- | -------------- | ------------- | ----------- |
|  std::vector |     s   |    s  |    s  |   s  |
| vector  |    s   |    s  |   s  |  s  |

### Programos veikimo laiko analizė su 100 000 studentų
|                     |     std::vector      |      vector     |
| ------------------- | --------------- | -------------- |
|   |     s   |    s  |
|   |    s   |    s  |
|   |     s   |    s  |
|   |    s   |    s  |
|   |     s   |    s  |
|   |    s   |    s  |
