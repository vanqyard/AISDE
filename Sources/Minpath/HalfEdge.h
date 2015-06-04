#ifndef HALF_EDGE
#define HALF_EDGE

#include "MinpathUtils.h"

using namespace std;

// Krawedz skierowanego grafu wazonego. Reprezentacja pozwalajaca
// przechowywac graf jako tablice list tego typu obiektow. 
// v-tym elementem tablicy jest kolekcja (np. lista) obiektow HalfEdge 
// reprezentujacych krawedzie wychodzace z wierzcholka 'v'.

class HalfEdge {
	private:
		int	w;			// Numer wierzcholka koncowego.
  		long weight;	// Waga krawedzi.
  		
	public:
		HalfEdge(int aw, long aweight): w(aw), weight(aweight) {}
		HalfEdge(): w(0), weight(INF) {}
		int 	getEndingVertexIndex(void) { return w; }
		long 	getWeight(void) { return weight; }
		void	setWeight(long wt) { weight = wt; }
};

#endif // HALF_EDGE
