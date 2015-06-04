#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctime>

#include "Exception.h"
#include "MinpathUtils.h"

// Nieskonczonosc (jak widac)
#define INF (-1)

// Powyzej tej liczby wierzcholkow grafy nie beda wypisywane na ekran
#define MAX_PRINTABLE_V 10

using namespace std;

// Porownuje 2 liczby. A wszystko dlatego, 
// ze nieskonczonosc jest zapisywana jako -1
int Compare(long x, long y) {
	if (x == INF) return  1;
	if (y == INF) return -1;
	if (x == y)   return  0;
	if (x > y)    return  1;
	if (x < y)    return -1;
	return 0;
}

// Dodaje 2 liczby. A wszystko dlatego, 
// ze nieskonczonosc jest zapisywana jako -1
long Add(long x, long y) {
	if (x == INF || y == INF)	
		return INF;
	else
		return x + y;
}

// Konwertuje lancuch znakow na liczb calkowita (int).
int String2Int(const char *str) {
	for (unsigned int i = 0; i < strlen(str); i++) {
	 	if (isdigit(str[i]) == 0) {
			throw new Exception(NumberFormatException, str);
			break;
		}
	}
	return atoi(str);
}

// Zwraca biezacy czas w milisekundach
long CurrentTime(void) { return (1000*clock())/CLOCKS_PER_SEC; }
