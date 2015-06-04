#include <iostream>
#include <fstream>

#include "Digraph.h"
#include "Exception.h"

using namespace std;

Digraph::Digraph(const char *filename) {
	V = 0;			// Liczba wezlow
	E = 0;			// Liczba krawedzi
	int v, w;		// Wezly: poczatkowy i koncowy 
 	long wt;			// Waga krawedzi 
	ifstream *ifstr;

	cout << " Wczytywanie grafu z pliku '" << filename << "'...";
  	ifstr = new ifstream(filename); 
	if (ifstr->good() == false)
		throw new Exception(FileOpenException, filename);

	while(*ifstr >> v >> w >> wt) {
		if (v > V) V = v;
		if (w > V) V = w;
		E++;
	}

	V++;		// Numery wezlow powinny zaczynac sie od zera...
	
	weights = new long[V*V];
	for (int i = 0; i < V; i++) 
 		for (int j = 0; j < V; j++)
			weights[V*i+j] = INF;

	delete ifstr;
  	ifstr = new ifstream(filename); 
    	
	while(*ifstr >> v >> w >> wt)
		weights[V*v+w] = wt;

	cout << " gotowe\n";		
 	delete ifstr;
}	

Digraph::Digraph(const Digraph& g) {
	V = g.getNumVertices();
	E = g.getNumEdges();
	weights = new long[V*V];

	for (int i = 0; i < V; i++) 
 		for (int j = 0; j < V; j++)
			weights[V*i+j] = g.weights[V*i+j];
}


Digraph::Digraph(DigraphL& g) {
	List<HalfEdge *> *outgoingEdges; 
	HalfEdge *edge;
	int w;
	
	V = g.getNumVertices();
	E = g.getNumEdges();
	weights = new long[V*V];
		
	for (int i = 0; i < V*V; i++)
		weights[i] = INF;

	for (int v = 0; v < V; v++)  {
		outgoingEdges = g.getOutgoingEdges(v);
		outgoingEdges->rewind(); 
		while (outgoingEdges->hasMoreElements()) {
			edge = outgoingEdges->getNext();
			w    = edge->getEndingVertexIndex();										
			weights[V*v+w] = edge->getWeight();
		}
	}
}


Digraph::~Digraph(void) { delete[] weights; }

long Digraph::getWeight(int v, int w) {
	if (v >= 0 && w >= 0 && v < V && w < V) {
		return weights[V*v + w];
	}
	else
		return INF;
}

void Digraph::setWeight(int v, int w, long weight) {
	weights[V*v + w] = weight;
}

int Digraph::getNumVertices(void) const { return V; }

int Digraph::getNumEdges(void) const { return E; }

void Digraph::print(void) {
	long weight;

	cout << endl;
 	for (int i = 0; i < V; i++) {
 		for (int j = 0; j < V; j++) {
 			weight = weights[V*i+j];
 			cout << "\t";
 			if (weight != INF)
				cout << weights[V*i+j];
			else
				cout << "-";
		}
		cout << endl;
	}	
	cout << endl;
}

// To w zasadzie tylko dlatego, ze klasa bazowa AbstractGraph
// wymaga takiej funkcji. Tak naprawde jest ona uzyteczna
// w grafie zaimplementowanym jako tablica 

List<HalfEdge *>* Digraph::getOutgoingEdges(int v) {
	long weight;
	List<HalfEdge *> *edgeList = new List<HalfEdge *>();
	if (v < 0 || v >= V)
		return NULL;

	for (int w = 0; w < V; w++) {
		weight = weights[V*v+w];
		if (weight != INF) // Dodajemy tylko istniejace galezie		
			edgeList->append(new HalfEdge(w, weight));
	}
	return edgeList;
}
