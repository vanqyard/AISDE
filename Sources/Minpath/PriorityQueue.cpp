#include <iostream>

#include "MinpathUtils.h"
#include "PriorityQueue.h"

using namespace std;

PriorityQueue::PriorityQueue(int cap) {
	if (cap < 1)
  		return;		
  		
	else {
		capacity = cap;
		size = cap;
  		vertices = new Vertex[capacity+1];
    	offsets = new int[capacity];

     	for (int i = 0; i < size; i++) {
            vertices[i+1].index = i;
     		vertices[i+1].dist  = INF;
            offsets[i] = i+1;
		}
   	    vertices[0].index = -1;
     	vertices[0].dist = INF;
	}
}

PriorityQueue::~PriorityQueue(void) {
	delete[] vertices;
	delete[] offsets;
}

bool PriorityQueue::notEmpty(void) { return (size > 0); } 

int  PriorityQueue::getSize(void) { return size; } 

// Zmieniamy wage wierzcholka o indeksie 'ind' na 'newWeight'. 
void PriorityQueue::decreaseKey(int ind, long newWeight) {
	int n = offsets[ind];
	while (n > 1 && Compare(newWeight, vertices[PARENT(n)].dist) < 0) {
  		vertices[n] = vertices[PARENT(n)];
  		offsets[vertices[n].index] = n;
 		n = PARENT(n);
	}
	
 	vertices[n].dist = newWeight;
 	vertices[n].index = ind;
 	offsets[ind] = n;
}

// Zwraca wierzcholek o najmniejszej wadze i jednoczesnie usuwa go z kolejki.
// ZAGADKA DLA DOCIEKLIWYCH: co sie dzieje z ostatnim wierzcholkiem kopca ('last')
// podczas odtwarzania jego struktury?
Vertex PriorityQueue::removeNearest(void) { 
	int n, next;	
	Vertex nearest, last;
	
	if (size == 1) {
		offsets[vertices[size].index] = -1;
		return vertices[size--];
	}
		
	nearest = vertices[1];       // To jest wezel o najmniejszej wadze...
	offsets[nearest.index] = -1; // ...kasujemy go z kolejki
	last = vertices[size--];     // A to ostatni wezel w kolejce. Przyda sie przy odtwarzaniu kopca.   
   	   	
   // Odtwarzamy strukture kopca   	   	
	for (n = 1; LEFT(n) <= size; n = next) {
		next = LEFT(n);
		if (RIGHT(n) <= size && Compare(vertices[RIGHT(n)].dist, vertices[LEFT(n)].dist) < 0)
			next = RIGHT(n);					
		if (Compare(vertices[next].dist, last.dist) < 0) {
			vertices[n] = vertices[next];
			offsets[vertices[n].index] = n;
		}
		else
			break;
	}

	vertices[n] = last;
	offsets[vertices[n].index] = n; 	
	return nearest; 
}

Vertex PriorityQueue::get(int index) { return vertices[offsets[index]]; }

bool PriorityQueue::contains(int ind) { return (offsets[ind] > 0); }

void PriorityQueue::print(void) {
	for (int i = 1; i <= size; i++) {
		if (vertices[i].dist != INF)
			cout << vertices[i].dist << "\t";
		else
			cout << "-\t";
	}
	cout << endl;
}
