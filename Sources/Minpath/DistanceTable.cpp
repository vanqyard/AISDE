#include <iostream>

#include "DistanceTable.h"
#include "MinpathUtils.h"

using namespace std;

DistanceTable::DistanceTable(int s) {
	size = s;
	dists = new long[s];
	fixed = new bool[s];
	
	for(int i = 0; i < size; i++) {
		dists[i] = INF;
		fixed[i] = false;
	}
}

DistanceTable::~DistanceTable(void) { 
	delete[] dists; 
	delete[] fixed;
}

int  DistanceTable::getSize(void) { return size; }

long DistanceTable::getDist(int n) { return dists[n]; }

bool DistanceTable::setDist(int n, long d) { 
	if (fixed[n] == false) {
		dists[n] = d; 
  		return true;
 	}
 	return false;
}

// Znajduje numer wierzcholka o najmniejszej wadze (odleglosci od wierzch. poczatkowego).
int DistanceTable::getNearest(void) {
	long tempMinDist = INF;
	int  nearest = INF;
	for (int i = 0; i < size; i++) {
		if (fixed[i] == false && Compare(dists[i], tempMinDist) < 0) {
     		nearest = i;
  			tempMinDist = dists[i];
		}
	}
	return nearest;
} 		 

// Czy waga wierzcholka 'n' jest ustalona?
bool DistanceTable::isFixed(int n) { return fixed[n]; }

// Ustala wage wierzcholka 'n'
bool DistanceTable::fix(int n) { 
	if(n >= size || fixed[n])
		return false;
	else {
 		fixed[n] = true; 
 		return true;
   }
}

void DistanceTable::print(void) {
	if (size > MAX_PRINTABLE_V)
		return;
	else {
		for (int i = 0; i < size; i++) {
			if (dists[i] != INF)
				cout << "\t" << dists[i];
			else
				cout << "\t-";
		}
		cout << endl;
	}
}

void DistanceTable::check(void) {
	for (int i = 0; i < size; i++) {
		cout << "Num: " << i << ", distance: " << dists[i];
  		cout << ", fixed: " << fixed[i] << endl;
	}
}
