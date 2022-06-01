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
|           INT          |       10000      |      100000     |     1000000    |   10000000   |   100000000   |
| ------------------- | --------------- | -------------- | ------------- | ----------- | ----------- |
|  std::vector |  0   s   | 0.0007633   s  |  0.0078678  s  | 0.0460187  s  | 0.4934236  s  |
| vector  |  0.0009341  s   |  0.0004318  s  |  0.0044205 s  | 0.0368311 s  |  0.33419s  |

### Programos veikimo laiko analizė su 100 000 studentų
|                     |     std::vector      |      vector     |
| ------------------- | --------------- | -------------- |
|  Skaitymas is failo |   0.720192  s   |  0.5979107  s  |
| Studentu dalinimas  |  0.0447068  s   |  0.0240774  s  |
| Studentu spausdinimas i du failus  |  0.2274246   s   |  0.2208481   s  |

