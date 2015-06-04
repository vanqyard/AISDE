/************************************************************************************************
*                                          FOREST
*
*   Implementacja abstrakcyjnej struktury danych operujacej na rozlacznych podzbiorach,
*   znanej jako 'Disjoint Subsets' lub 'Union-Find'.
*   Umozliwia ona dwie operacje: zlaczenie podzbiorow (Union)  oraz okreslenie indeksu podzbioru, 
*   do ktorego nalezy dany element (Find).
*
*   W tej implementacji operujemy na podzbiorach wierzcholkow grafu tworzacych drzewa. 
*   Funkcja addEdge(edge) probuje dodac krawedz 'edge', o ile polaczy ona dwa drzewa. 
*   W przeciwnym wypadku krawedz nie jest dodawana (utworzylaby ona cykl w ktoryms 
*   z istniejacych drzew) i funkcja zwraca 'false'.
*
*   Funkcja getSubsetIndex(v) zwraca indeks poddrzewa, do ktorego nalezy wierzcholek 'v'.
*
************************************************************************************************/

#ifndef FOREST_H
#define FOREST_H

#include "Edge.h"

class Forest {   
	public:
		Forest(long size);
		~Forest(void);
		bool  addEdge(Edge *);
		long  getSubsetIndex(long v);

	private:
		long   size;
		long  *subsetIndex;
		long  *successor;
		long  *subsetSize;		
		void   exchange(long &x, long &y); 	
		bool   inTheSameSubset(long v, long w);
		long   getSubsetSize(long v);
		void   setSubsetSize(long v, long new_size);
};

#endif // FOREST_H
