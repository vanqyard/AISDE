#ifndef DIGRAPH_L_H
#define DIGRAPH_L_H

#include "List.h"
#include "HalfEdge.h"
#include "AbstractGraph.h"
#include "Digraph.h"

// Graf skierowany zaimplementowany jako tablica list.
// v-tym elementem tablicy jest lista obiektow HalfEdge 
// reprezentujacych krawedzie wychodzace z wierzcholka 'v'.

class DigraphL : public AbstractGraph {
	private:
		int 	V, E;             // Liczba wierzcholkow i krawedzi
		List<HalfEdge *> **edges; // Rzeczona tablica.
		bool	insertEdge(int v, int w, long weight); // Wstawia krawedz.
	
	public:
		DigraphL(const char *); // Konstruuje graf na podstawie opisu w pliku.
		DigraphL(class Digraph &);    // A tu - na podstawie grafu w postaci tablicy przyleglosci.
		~DigraphL(void);
		List<HalfEdge *> *getOutgoingEdges(int v); // Zwraca liste krawedzi wychodzacych z wierzch. 'v'.
 		int   getNumVertices(void) const;					
 		int   getNumEdges(void) const;
 		long  getWeight(int v, int w); // Zwraca wage krawedzi skierowanej od wierzch. 'v' do 'w'.
 		void  print(void);
};

#endif // DIGRAPH_L_H
