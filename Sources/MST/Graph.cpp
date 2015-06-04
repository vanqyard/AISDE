#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "Graph.h"
#include "Exception.h"

using namespace std;

// Tworzy graf nieskierowany na podstawie opisu wczytanego z pliku
Graph::Graph(const char *filename) {
	int   v, w;    // Indeksy wierzcholkow 
	int   weight;  // Waga krawedzi 
	long  index;   // Indeks w tablicy krawedzi
	FILE* infile;

	cout << " Wczytywanie grafu z pliku '" << filename << "'...";
	try {		
		if ((infile = fopen(filename, "r")) == NULL)
			throw new Exception(FileOpenException, filename);
	} catch (Exception *e) {  HandleException(e); }
  	
  	V = 0; E = 0;
	
	// Na poczatku liczymy wierzcholki i krawedzie.
	// Indeksy wierzcholkow MUSZA byc kolejnymi liczbami poczynajac od zera
	while (fscanf(infile, "%d %d %d\n", &v, &w, &weight) != EOF) {
		if (v > V) V = v;
		if (w > V) V = w;
		E++;
	}

	V++;		// Numery wezlow powinny zaczynac sie od zera...	
	index = 0;
	edges = new Edge*[E];
	rewind(infile);
	
	while (fscanf(infile, "%d %d %d\n", &v, &w, &weight) != EOF)
		edges[index++] = new Edge(v, w, weight);
		
	fclose(infile);
	
	cout << " gotowe." << endl;
	cout << " Graf ma " << V << " wierzcholkow i " << E << " krawedzi." << endl << endl;	
}	


Graph::Graph(const Graph& g) {
	V = g.V;
	E = g.E;
	edges = new Edge*[E];
	
	for (long i = 0; i < E; i++)
		edges[i] = new Edge(*g.edges[i]);
}

Graph::~Graph(void) { delete[] edges; }

Edge** Graph::getEdges(void)     { return edges; }

long Graph::getNumVertices(void) { return V; }

long Graph::getNumEdges(void)    { return E; }

void Graph::print() {
	cout << " v\tw\twaga" << endl;
	cout << " --------------------" << endl;
	for (int i = 0; i < E; i++) 
		edges[i]->print();
	cout << " --------------------" << endl << endl;
}
