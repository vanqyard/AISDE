#include <cstdlib>
#include <climits>
#include <iostream>
#include <fstream>

#include "MST_Algorithms.h"
#include "MST_Utils.h"
#include "Edge.h"
#include "Graph.h"
#include "Forest.h"

using namespace std;

// Algorytm Kruskala znajdujacy najmniejsze drzewo rozpinajace
Edge** Kruskal(Graph* g) {
	Edge** edges = g->getEdges();
	long V       = g->getNumVertices();
	long E       = g->getNumEdges();
	int  mstSize = 0;		
	
	// Zwracana tablica krawedzi tworzacych drzewo rozpinajace
	Edge** mst = new Edge*[V-1];

	Forest *forest = new Forest(V);
			
	qsort(edges, E, sizeof(Edge*), Edge::compareEdgeWeigths);
		
	for (int i = 0; i < E; i++) {
		// Jesli kolejna krawedz nie tworzy cyklu z zadnym ze stworzonych dotychczas drzew...
		if (forest->addEdge(edges[i]) == true)
		
			// ...to dodaj ja do drzewa rozpinajacego.
			mst[mstSize++] = edges[i];
	}
	delete forest;
	
	return mst;
}


// Algorytm Boruvki znajdujacy najmniejsze drzewo rozpinajace
Edge** Boruvka(Graph* g) {
	Edge** edges = g->getEdges();
	long V       = g->getNumVertices();
	long E       = g->getNumEdges();
	
	// Na poczatku mamy V drzew - pojedynczych wierzcholkow.
	long  numOfSubsets = V;		

	// Dlugosci najkrotszych krawedzi laczacych kazde z drzew z reszta grafu.
	long *shortestOuterEdgeInSubset = new long[V]; 

	// Indeksy tych krawedzi. 
	long *edgeToAddToSubset = new long[V]; 

	// Zwracana tablica krawedzi tworzacych drzewo rozpinajace
	Edge** mst = new Edge*[V-1];

	// Zmienne tymczasowe
	Edge *candidateEdge; 
	long  firstVertexIndex, secondVertexIndex;
	long  firstSubsetIndex, secondSubsetIndex;
	int   candidateEdgeWeight;	
	int   mstSize = 0;		

	Forest *forest = new Forest(V);
 
	while (numOfSubsets > 1) {
	 
		for (int i = 0; i < V; i++) {
			shortestOuterEdgeInSubset[i] = LONG_MAX;
			edgeToAddToSubset[i] = -1;
		}
		
		for (int i = 0; i < E; i++) {
			candidateEdge = edges[i];
			firstVertexIndex    = candidateEdge->v;			  			
			secondVertexIndex   = candidateEdge->w;			  			
			candidateEdgeWeight = candidateEdge->weight;			

			// Indeksy podzbiorow, do ktorych naleza wierzcholki polaczone 'candidateEdge'
			firstSubsetIndex  = forest->getSubsetIndex(firstVertexIndex); 
			secondSubsetIndex = forest->getSubsetIndex(secondVertexIndex); 
			
			// Jesli 'candidateEdge' laczylaby wierzcholki nalezace do tego samego 
			// podzbioru, to oczywiscie jej nie dodajemy
			if (firstSubsetIndex == secondSubsetIndex)
				continue;

			// Uaktualnij wage najkrotszej galezi wychodzacej z podzbioru,
			// do ktorego nalezy pierwszy wierzcholek.		
			if(candidateEdgeWeight < shortestOuterEdgeInSubset[firstSubsetIndex]) {
				shortestOuterEdgeInSubset[firstSubsetIndex]  = candidateEdgeWeight;	
				edgeToAddToSubset[firstSubsetIndex] = i;
			}											

			// Zrob to samo z podzbiorem, do ktorego nalezy drugi wierzcholek.
			if(candidateEdgeWeight < shortestOuterEdgeInSubset[secondSubsetIndex]) {
				shortestOuterEdgeInSubset[secondSubsetIndex] = candidateEdgeWeight;	
				edgeToAddToSubset[secondSubsetIndex] = i;
			}											
		}

 		for (int i = 0; i < V; i++) {
 			// Moze sie okazac, ze "i" nie jest indeksem zadnego podzbioru
 			if (edgeToAddToSubset[i] == -1)
 				continue;
 			candidateEdge = edges[edgeToAddToSubset[i]];
 
 			// Jesli udalo sie dodac najkrotsza galaz (tzn. jesli nie stworzy ona cyklu),
 			// to polaczylismy dwa podzbiory.
 			if (forest->addEdge(candidateEdge) == true) {
 				mst[mstSize++] = candidateEdge;
 				numOfSubsets--;
 			}
 		}	
	}	
	delete forest;
	
	return mst;
}
