#ifndef DISTANCE_TABLE_H
#define DISTANCE_TABLE_H

// Tablica 'wag' wierzcholkow, czyli ich odleglosci od zrodla, 
// wraz z informacja o tym, czy waga jest ustalona, czy tymczasowa. 
// Ta informacja jest wykorzystywana przez algorytm Dijkstry.
 
class DistanceTable {

	private:
		long  *dists;  // Tablica odleglosci wierzcholka od zrodla
		bool  *fixed;  // Czy waga jest ustalona forever?
		int    size;   // Rozmiar powyzszych tablic, czyli liczba wierzcholkow.
	public:
		DistanceTable(int size);
 		~DistanceTable(void);
		long  getDist(int n);         // Zwraca wage wierzcholka 'n'.
		bool  setDist(int n, long d); // Przypisuje (tymczasowa!) wage 'd' wierzcholkowi 'n'.
		int   getNearest(void); // Pobiera najmniejsza sposrod wag w tablicy.
		bool  isFixed(int n);   // Czy waga wierzcholka 'n' jest juz ustalona?
		bool  fix(int n);       // Ustala dotychczasowa wage wierzcholka 'n'.
		int   getSize(void); 
		void  print(void);		
		void  check(void);
};

#endif // DISTANCE_TABLE_H
