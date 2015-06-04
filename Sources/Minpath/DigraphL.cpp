#include <iostream>
#include <fstream>
#include <cstdlib>

#include "DigraphL.h"
#include "Exception.h"

using namespace std;

DigraphL::DigraphL(const char *filename) {
	V = 0;			// Liczba wezlow
	E = 0;

	int 	  v, w;		// Wezly: poczatkowy i koncowy
 	long 	  wt;			// Waga krawedzi; 
	ifstream *ifstr;

	ifstr = new ifstream(filename); 
	
	if (!ifstr->good()) {
		cout << " Nie moge otworzyc pliku " << filename << endl;
		exit (-1);
	}

	while(*ifstr >> v >> w >> wt) {
		if (v > V) V = v;
		if (w > V) V = w;
	}
	
	V++;		// Numery wezlow powinny zaczynac sie od zera...
		
	edges = new List<HalfEdge *>*[V];	
	
	for (int i = 0; i < V; i++)
		edges[i] = new List<HalfEdge *>();		
	
	delete ifstr;
  	ifstr = new ifstream(filename);
 		
	while(*ifstr >> v >> w >> wt) {
		insertEdge(v, w, wt);
		E++;
	}
		
 	delete ifstr;
}	

DigraphL::DigraphL(Digraph& g){
	V     = g.getNumVertices();
	edges = new List<HalfEdge *>*[V];	
	for (int i = 0; i < V; i++)
		edges[i] = new List<HalfEdge *>();		
	
	for (int v = 0; v < V; v++) {
		for (int w = 0; w < V; w++) {
			long weight = g.getWeight(v, w);
			if (weight != INF)
				insertEdge(v, w, weight);
		}
	}
}	

DigraphL::~DigraphL(void) { delete[] edges; }

List<HalfEdge*>* DigraphL::getOutgoingEdges(int v) { return edges[v]; }

long DigraphL::getWeight(int v, int w) {
	if (v >= 0 && w >=0 && v < V && w < V) {
		HalfEdge* edge;		
		edges[v]->rewind();
		while (edges[v]->hasMoreElements()) {
			edge = edges[v]->getNext();
			if (edge->getEndingVertexIndex() == w)
				return edge->getWeight();
		}
		return INF;
	}
	else
		return INF;	
}

int DigraphL::getNumVertices(void) const { return V; }

int DigraphL::getNumEdges(void) const { return E; }

bool DigraphL::insertEdge(int v, int w, long weight) {
	if (v >= 0 && w >= 0 && v < V && w < V) {
		edges[v]->append(new HalfEdge(w, weight));
		return true;
	}
	return false;
}

void DigraphL::print(void) {
	// Wagi krawedzi od 'v' do kazdego z V wierzcholkow (moga byc nieskonczone)
	int matrix[V];	
	HalfEdge* edge;
			
 	for (int v = 0; v < V; v++) {
		edges[v]->rewind();
		// Inicjujemy tablice nieskonczonymi wagami
 		for (int w = 0; w < V; w++)
			matrix[w] = INF;	
		
		// Uaktualniamy wagi odpowadajace istniejacym krawedziom
		while (edges[v]->hasMoreElements()) {
			edge = edges[v]->getNext();
			matrix[edge->getEndingVertexIndex()] = edge->getWeight();
		}
		
		// Wypisujemy wagi na ekran
  		for (int w = 0; w < V; w++) {
			cout << "\t";
 			if (matrix[w] != INF)
				cout << matrix[w];
			else
				cout << "-";
		}
		cout << endl;
	}
	cout << endl;
}
