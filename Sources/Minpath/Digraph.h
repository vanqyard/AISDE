#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>

#include "List.h"
#include "HalfEdge.h"
#include "AbstractGraph.h"
#include "DigraphL.h"

// Graf skierowany. Implementacja tablicowa - macierz przyleglosci (sasiedztwa).

class Digraph : public AbstractGraph {

	private:
		int   V, E;		// Liczba wierzcholkow i krawedzi.
		long *weights;	// Tablica wag krawedzi (jednowymiarowa, lecz o dlugosci V*V).
	
	public:
		Digraph(const char *filename);
		Digraph(const Digraph &);
		Digraph(class DigraphL &);
		~Digraph(void);
 		int   getNumVertices(void) const;
 		int   getNumEdges(void) const;
 		long  getWeight(int v, int w);  // Zwraca wage krawedzi od wierzch. 'v' do 'w'.
    	void  setWeight(int v, int w, long dist);			
		List<HalfEdge*>* getOutgoingEdges(int v);
 		void  print(void); // Wyswietla macierz przyleglosci  		 		
};

#endif // DIGRAPH_H
