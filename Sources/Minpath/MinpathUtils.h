#ifndef MINPATH_UTILS_H
#define MINPATH_UTILS_H

// Nieskonczonosc (jak widac)
#define INF (-1)

// Powyzej tej liczby wierzcholkow grafy nie beda wypisywane na ekran
#define MAX_PRINTABLE_V 10

// Prototypy funkcji (dokladniejsze komentarze w pliku MinpathUtils.cpp)
int  Compare(long, long);      // Porownuje wagi 2 galezi - moga byc 'nieskonczone'.
long Add(long, long);          // Dodaje wagi 2 galezi - moga byc 'nieskonczone'.
int  String2Int(const char *); // Konwertuje lancuch na liczbe calkowita.
long CurrentTime(void);        // Zwraca biezacy czas w milisekundach.

#endif // MINPATH_UTILS_H
