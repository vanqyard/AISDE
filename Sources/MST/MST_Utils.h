#ifndef MST_UTILS_H
#define MST_UTILS_H

#include "Edge.h"
#include "Graph.h"

// Powyzej tej liczby krawedzi grafy nie beda wypisywane na ekran
#define MAX_PRINTABLE_E 10

using namespace std;

// Zwraca biezacy czas w milisekundach
long CurrentTime(void);

// Uruchamia wybrany algorytm, mierzy czas i ewentualnie wypisuje drzewo
void FindMST (
	Graph* graph,
	Edge** (* algorithm) (Graph *),
	const char *message,
	bool printTree
);

// Wypisuje drzewo
void printMST(Edge** mst, int mstSize);

#endif // MST_UTILS_H
