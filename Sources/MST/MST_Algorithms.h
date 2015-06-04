#ifndef MST_ALGORITHMS_H
#define MST_ALGORITHMS_H

#include "Edge.h"
#include "Graph.h"

// Algorytm Kruskala znajdujacy najmniejsze drzewo rozpinajace
Edge** Kruskal(Graph* g);

// Algorytm Boruvki znajdujacy najmniejsze drzewo rozpinajace
Edge** Boruvka(Graph* g);

#endif // MST_ALGORITHMS_H
