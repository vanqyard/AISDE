#ifndef EDGE_H
#define EDGE_H

// Krawedz grafu. Funkcja 'compareEdgeWeigths()' ma postac
// wymagana przez funkcje standardowa 'qsort()'

class Edge {
	public:
		Edge(long _v, long _w, int _weight): v(_v), w(_w), weight(_weight) {}
		Edge(const Edge& e);
  		void print(void);
  		static int compareEdgeWeigths(const void *, const void *);
  		
		long  v, w;    // Numery wierzcholkow
  		int   weight;  // Waga krawedzi
};
	
#endif // EDGE_H
