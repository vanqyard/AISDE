#ifndef VERTEX_H
#define VERTEX_H

// Wierzcholek jako element kopca (dla klasy PriorityQueue)

typedef struct {
	int   index; // Numer (indeks) wierzcholka.
	long  dist;  // Odleglosc wierzcholka od 'zrodla'.
} Vertex;

#endif // VERTEX_H
