#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"

// Graf nieskierowany jako tablica krawedzi
class Graph {	
	private:
		long   V, E;	// Liczba wierzcholkow i krawedzi
		Edge **edges;			
	public:
		Graph(const char *filename);
		Graph(const Graph& g);
		~Graph(void);
		Edge** getEdges(void);
		long   getNumVertices(void);
		long   getNumEdges(void);
		void   print();
};

#endif // GRAPH_H
