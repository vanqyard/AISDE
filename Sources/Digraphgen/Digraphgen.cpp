/**********************************************************************************
*                                      DIGRAPHGEN	
*
*	Generator losowych grafow SKIEROWANYCH.
*	Tworzony jest graf o zadanej liczbie 'V' wierzcholkow i 'E' krawedzi.
*	Stopnie wejsciowe i wyjsciowe wszystkich wierzcholkow maja wartosci 
*  w przyblizeniu rowne E/V.
* 	Wagi krawedzi maja rozklad rownomierny na przedziale [1, MAXWEIGHT].
*
*	Autor: Dominik Kasprowicz
*	Ostatnia aktualizacja: 28 czerwca 2011
*
***********************************************************************************/

#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

const int MAXWEIGHT = 100;
const int SEED      = 243996;	// TU WPISUJEMY NUMER ALBUMU

class Edge {
	public:
		Edge(long _v, long _w, int _weight): v(_v), w(_w), weight(_weight), include(true) {}
		long v, w;    // Numery wierzcholkow
  		int  weight;  // Waga krawedzi
  		bool include;
};

// Lista sasiedztwa, czyli tablica list obiektow typu HalfEdge
class Graph {
	private:
		long	  V, E;       // Ile wierzcholkow? Ile krawedzi (docelowo)?
		long	  edgesLeft;  // Ile chwilowo krawedzi w strukturze?
		Edge  **edges;
	public:
		Graph(long V, long E);	// Konstruktor grafu o V wierzcholkach i E krawedziach
		~Graph(void);
		long getV(void) { return V; }
		long getActualE(void) { return edgesLeft; }
		long RemoveRandomEdges(long);
		bool Save(char *file);
};

Graph::Graph(long aV, long anE) {
	V = aV;
	E = anE;
	edgesLeft = V*(V-1);
  	edges = new Edge*	[edgesLeft];
  	int 	weight;

	if (E > edgesLeft)
		E = edgesLeft;
  	
  	// Konstruujemy pelny digraf o V wierzcholkach
 	for (long v = 0; v < V; v++) {
 		for (long w = 0; w < V; w++) {
 			weight = (int)((double)MAXWEIGHT * rand()/(double)RAND_MAX + 1);
 			if (w < v)
 				edges[v*(V-1) + w] = new Edge(v, w, weight);
			if (w > v)
				edges[v*(V-1) + w-1] = new Edge(v, w, weight);
		}
	}
	
	// Wycinamy z niego tyle krawedzi, by zostalo ich E
	while (edgesLeft > E)
		RemoveRandomEdges(edgesLeft - E);
}

Graph::~Graph(void) { delete[] edges; }

long Graph::RemoveRandomEdges(long m) {
	long		totalEdges = V*(V-1);
	double	rate = (double)(m/(double)edgesLeft); // 'Co ktora' krawedz trzeba usunac.
	double	choice;
	long 		cnt = 0;

	for (long n = 0; n < totalEdges; n++) {
		choice = rand()/(double)RAND_MAX;
		if (edgesLeft-cnt == E)
			break;
 		if (choice < rate && edges[n]->include == true) {
 			edges[n]->include = false;
 			cnt++;
		}
	}
	return (edgesLeft-=cnt);
}

bool Graph::Save(char * file) {
	long 		 v, w;
 	int 		 weight;
 	long		 totalEdges = V*(V-1);
	ofstream	*outfile = new ofstream(file);
	
	if (outfile == NULL) {
		cout << " Nie moge utworzyc pliku!" << endl;
		return false;
	}
		
	for (long i = 0; i < totalEdges; i++) {
		v = edges[i]->v;
		w = edges[i]->w;
		weight = edges[i]->weight;
		if (edges[i]->include)
			*outfile << v << " " << w << " " << weight << endl;
	}
	delete outfile;
	return true;
}

int main(int argc, char* argv[]) {
	long 	v, e;	// Liczba wierzcholkow i krawedzi
	char  filename[256];

	strcpy(filename, "digraf.txt"); // Domyslna nazwa pliku wynikowego
	
	if (argc < 3 || atol(argv[1]) < 2 || atol(argv[2]) < 1) {
		cout << " Prawidlowe wywolanie: " << argv[0]; 
  		cout << " ile_wierzcholkow ile_krawedzi [plik_wynikowy]" << endl;
  		exit(-1);
	}	
 	if (argc > 3)
 		strcpy(filename, argv[3]);

	if (SEED == 0) {
		cout << "Prosze nadac stalej SEED wartosc swojego numeru albumu" << endl;
		exit(-1);
	} 

	v = atol(argv[1]);
	e = atol(argv[2]);
	srand(SEED);	

	if (e > v*(v-1)) {
		cout << "\n UWAGA! Zadeklarowana liczba krawedzi (" << e << ") przekracza" << endl;
		cout << " liczbe krawedzi digrafu pelnego " << v << " x (" << v << " - 1) = " << v*(v-1) << "." << endl;
	}

	cout << "\n Generacja ";
 	if (e >= v*(v-1))
 		cout << "PELNEGO ";
	Graph *g = new Graph(v, e);
 	cout << "grafu skierowanego o " << v << " wierzcholkach i " << g->getActualE() << " krawedziach" << endl;
	cout << " Zapisywanie do pliku '" << filename << "'...";
	g->Save(filename);
	cout << " gotowe\n" << endl;

	delete g;	
	return 0;
}
