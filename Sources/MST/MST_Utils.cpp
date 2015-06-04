#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "MST_Utils.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

// Zwraca biezacy czas w milisekundach
long CurrentTime(void) { return 1000*clock()/CLOCKS_PER_SEC; }

// Wypisuje drzewo
void printMST(Edge** mst, int mstSize) {
	if (mst == NULL)
		return;
	cout << " v\tw\twaga" << endl;
	cout << " --------------------" << endl;
	for (int i = 0; i < mstSize; i++)
		mst[i]->print();
	cout << " --------------------" << endl << endl;		
}

// Uruchamia wybrany algorytm, mierzy czas i ewentualnie wypisuje drzewo
void FindMST (
	Graph* graph,
	Edge** (* algorithm) (Graph *),
	const char *message,
	bool printTree
) {
	long   time;
	Edge** mst;
	long   V = graph->getNumVertices();
	
	cout << " " << message << "...";
	time = CurrentTime();
		// Wlasciwe wywolanie algorytmu tworzacego MST
		mst = algorithm(graph);
	time = CurrentTime() - time;
	cout << " gotowe" << endl;
  	cout << "  Obliczenia trwaly " << time << " ms.\n\n";
	
	if (printTree == true && V <= MAX_PRINTABLE_E+1)
		printMST(mst, V-1);	
}

