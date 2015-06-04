#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Vertex.h"

#define PARENT(n) (n/2)
#define LEFT(n)   (2*n)
#define RIGHT(n)  (2*n+1)

// Kolejka priorytetowa. Zaimplementowana jako kopiec minimalny.
// Dodatkowa tablica 'offsets' pozwala w czasie O(1) zlokalizowac w kopcu
// wierzcholek o podanym indeksie.   

class PriorityQueue {

	private:
		Vertex *vertices;		// Kopiec minimalny wierzcholkow.
		int    *offsets;		// 'offsets[n]' to pozycja n-go wierzcholka w tablicy 'vertices'.
		int     capacity;		// Maksymalna pojemnosc kolejki.
  		int     size;			// Obecna liczba elementow w kolejce.
       
	public:
		PriorityQueue(int capacity);
 		~PriorityQueue(void);
 		bool    notEmpty(void);			
		bool    contains(int index);  // Czy kolejka zawiera wierzcholek 'index'?
		int     getSize(void); 
		Vertex  get(int index);       // Zwraca wierzcholek 'index'.
		Vertex  removeNearest(void);  // Zwraca wierzcholek o najmniejszej wadze.
		void    print(void);          // Wypisuje zawartosc kolejki.
		void    decreaseKey(int index, long newWeight);	// Uaktualnia wage wierzcholka 		
};

#endif // PRIORITY_QUEUE_H
