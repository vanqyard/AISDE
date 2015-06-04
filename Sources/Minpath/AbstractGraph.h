#ifndef ABSTRACT_GRAPH_H
#define ABSTRACT_GRAPH_H

#include "List.h"
#include "HalfEdge.h"

// Graf - klasa abstrakcyjna. Pozwala zastosowac identyczny interfejs
// dla funkcji operujacych na obu reprezentacji grafu - tablicowej i listowej. 

class AbstractGraph {
	public:
		virtual      ~AbstractGraph(void){};
		virtual int   getNumVertices(void) const =0;
		virtual int   getNumEdges(void) const =0;
 		virtual long  getWeight(int, int) =0;
		virtual List<HalfEdge *>* getOutgoingEdges(int) =0;
 		virtual void  print(void) =0; // Wyswietla macierz przyleglosci 
};

#endif // ABSTRACT_GRAPH_H
