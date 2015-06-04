/**********************************************************************************
*                                     GRAPHGEN	
*
*	Generator losowych grafow NIESKIEROWANYCH. 
*	Tworzony jest graf o zadanej liczbie 'V' wierzcholkow i 'E' krawedzi.
*	Stopnie wierzcholkow maja wartosci w przyblizeniu rowne 2E/V.
*	Wagi wierzcholkow to wartosci bezwzgledne zmiennej losowej 
*	o rozkladzie normalnym o wartosci oczekiwanej 0 i odchyleniu standardowym STDDEV.
*
*	Autor: Dominik Kasprowicz
*	Ostatnia aktualizacja: 28 czerwca 2011
*
***********************************************************************************/

#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

const int STDDEV = 100;
const int SEED   = 243996;	// TU WPISUJEMY NUMER ALBUMU


class Edge {
	public:
		Edge(long _v, long _w, int _weight): v(_v), w(_w), weight(_weight) {}
		long v, w;    // Numery wierzcholkow
  		int  weight;  // Waga krawedzi
};

// Lista sasiedztwa, czyli tablica list obiektow typu HalfEdge
class Graph {
	private:
		long    V, E;		//	Ile wierzcholkow? Ile krawedzi (docelowo)?
		long    edgesLeft;	// Ile chwilowo krawedzi w strukturze?
		Edge  **edges;
		bool   *include;	// Ktore krawedzie grafu pelnego zostawic w koncowym grafie
		long    getK(int v, int w);	// Indeks tablicy, pod ktorym znajduje sie
 									// waga krawedzi (v,w).
	public:
		Graph(long V, long E);	// Konstruktor grafu o V wierzcholkach i E krawedziach
		~Graph(void);
		long getV(void) { return V; }
		long getActualE(void) { return edgesLeft; }
		long RemoveRandomEdges(long);
		bool Save(char *file);
};

// Graf prosty
Graph::Graph(long _V, long _E) {
	V = _V;
	E = _E;
	edgesLeft = V*(V-1)/2;
  	edges   = new Edge*[edgesLeft];
  	include = new bool[edgesLeft];
  	double  x1, x2, r, x; 

	if (E > edgesLeft)
		E = edgesLeft;
  	
  	for (int i = 0; i < edgesLeft; i++)
  		include[i] = true;
  	
  	// Przypisywanie krawedziom losowych wag. Sa one wartosciami bezwzglednymi
  	// zmiennej pseudolosowej o rozkladzie normalnym generowanej
  	// za pomoca algorytmu Boxa-Mullera
 	for (long v = 0; v < V-1; v++) {
 		for (long w = v+1; w < V; w++) {
 			do {
 				x1 = 2*rand()/(double)RAND_MAX-1;
 				x2 = 2*rand()/(double)RAND_MAX-1;
 				r = x1*x1 + x2*x2;
			} while (r >= 1);
			r = sqrt((-2*log(r))/r);
			x = x1*r;			
			edges[getK(v, w)] = new Edge(v, w, (int)(STDDEV*fabs(x)+1));
		}
	}
	
	// Z grafu wycinamy tyle krawedzi, by zostalo ich E
	while (edgesLeft > E)
		RemoveRandomEdges(edgesLeft - E);
}

Graph::~Graph(void) { delete[] edges; }

// Na podstawie numerow wierzcholkow 'v' i 'w' zwraca indeks tablicy,
// pod ktorym mozna znalezc wage krawedzi miedzy 'v' a 'w'
// (graf NIE jest skierowany).
long Graph::getK(int v, int w) {
	if (v >= V || w >= V || v == w)
		return -1;
	if (w > v)
		return (long)(v*(V-0.5*v-1.5)) + w-1;
	if (w < v)
		return (long)(w*(V-0.5*w-1.5)) + v-1;
	return -1;
}


// Usuwa 'm' losowo wybranych krawedzi.
long Graph::RemoveRandomEdges(long m) {
	long    totalEdges = V*(V-1)/2;
	double  rate = (double)(m/(double)edgesLeft); // 'Co ktora' krawedz trzeba usunac.
	double  choice;
	long    cnt = 0;

	for (long n = 0; n < totalEdges; n++) {
		choice = rand()/(double)RAND_MAX;
		if (edgesLeft-cnt == E)
			break;
 		if (choice < rate && include[n] == true) {
 			include[n] = false;
 			cnt++;
		}
	}
	return (edgesLeft-=cnt);
}

// Zapisuje graf do pliku.
bool Graph::Save(char * file) {
	long       v, w;
 	int        weight;
 	long       totalEdges = V*(V-1)/2;
	ofstream  *outfile = new ofstream(file);
	
	if (outfile == NULL) {
		cout << " Nie moge utworzyc pliku!" << endl;
		return false;
	}
		
	for (long i = 0; i < totalEdges; i++) {
		v = edges[i]->v;
		w = edges[i]->w;
		weight = edges[i]->weight;
		if (include[i])
			*outfile << v << " " << w << " " << weight << endl;
	}
	delete outfile;
	return true;
}

int main(int argc, char* argv[]) {
	long    v, e;
	Graph  *g;	
	char   filename[256];

	strcpy(filename, "graf.txt"); // Domyslna nazwa pliku wynikowego

	if (argc < 3) {
		cout << " Prawidlowe wywolanie: " << argv[0]; 
  		cout << " ile_wierzcholkow ile_krawedzi [plik_wynikowy]" << endl;
  		return 0;
	}	
	
	v = atol(argv[1]);
	e = atol(argv[2]);
		
	if (v <= 0 || e <= 0) {
		cout << " Nieprawidlowe argumenty!" << endl;
		return 0;
	}

 	if (argc > 3)
		strcpy(filename, argv[3]);

	if (SEED == 0) {
		cout << "Prosze nadac stalej SEED wartosc swojego numeru albumu" << endl;
		exit(-1);
	} 

	srand(SEED);
 			
 	if (e > v*(v-1)/2) {
		cout << "\n UWAGA! Zadeklarowana liczba krawedzi (" << e << ") przekracza" << endl;
		cout << " liczbe krawedzi grafu pelnego " << v << " x (" << v << " - 1)/2 = " << v*(v-1)/2 << "." << endl;
	}		
 		
	cout << "\n Generacja ";
 	if (e >= v*(v-1)/2)
 		cout << "PELNEGO ";
 		
	g = new Graph(v, e);
 	cout << "grafu nieskierowanego o " << v << " wierzcholkach i " << g->getActualE() << " krawedziach" << endl;
	cout << " Zapisywanie do pliku '" << filename << "'...";
	g->Save(filename);
	cout << " gotowe\n" << endl;
	delete g;
	return 0;
}
