/***************************************************************/
/*                                                             */
/*                 AISD - ALGORYTMY GRAFOWE                    */
/*   POSZUKIWANIE NAJKROTSZEJ SCIEZKI W GRAFIE SKIEROWANYM     */
/*                                                             */
/*   Autor: Dominik Kasprowicz                                 */
/*   Ostatnia modyfikacja: 15 grudnia 2009                     */
/*                                                             */
/***************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>

#include "MinpathUtils.h"
#include "MinpathConfig.h"
#include "Exception.h"
#include "List.h"
#include "ListElement.h"
#include "PriorityQueue.h"
#include "DistanceTable.h"
#include "AbstractGraph.h"
#include "Digraph.h"
#include "DigraphL.h"

using namespace std;


// Znajduje najkrotsza droge od 'source' do 'destination' metoda pelnego przegladu przestrzeni rozwiazan.  
long BruteForce(Digraph *graph, int V, bool *visited, 
				int current, int dest, long currentCost, long &minCost) {

	long edgeCost, newCost = 0;		// koszt dojscia do obecnego wierzcholka, nowy 
	visited[current] = true;		// musimy oznaczac czy odwiedzilismy dany wierzcholek (w zasadzie czy odwiedzamy teraz)
	
	// wywolanie rekurencyjne w petli for
	for (int w = 0; w < V; w++) {
		edgeCost = graph->getWeight(current, w);
		newCost = currentCost + edgeCost;
		if (w != current && edgeCost != INF && visited[w] == false) {
			if (w != dest) 
   			BruteForce(graph, V, visited, w, dest, newCost, minCost);			
       	else {
				if (Compare(newCost, minCost) < 0)
					minCost = newCost;
			}
		}
	}
	visited[current] = false;
	return minCost;
}	

long RunBruteForce(AbstractGraph *graph, int source, int destination, bool findAllPaths) {
	long  minCost = INF;  // Koszt najkrotszej drogi od 'source' do 'destination'.
	bool *visited;        // 'true', jesli wierzcholek o odpowiednim indeksie zostal juz odwiedzony.

  	int  V             = graph->getNumVertices();	    	  
	long resultMatrix[V][V];		// macierz wynikowa
	
  	visited = new bool[V];
  	
 	for (int i = 0; i < V; visited[i++] = false);
	
	if (findAllPaths == false)    	
		return BruteForce((Digraph*)graph, V, visited, source, destination, 0, minCost);	
   
  	else {
 		for (int v = 0; v < V; v++) {
 			for (int w = 0; w < V; w++) {
 				// Czyscimy pomocnicze struktury danych
 				minCost = INF;
 				for (int i = 0; i < V; visited[i++] = false);
 				
 				long tmp = BruteForce((Digraph*)graph, V, visited, v, w, 0, minCost);	
 				resultMatrix[v][w] = tmp;
 				//cout << "minCost of [" << v << ", " << w << "]" << " is " << tmp << endl; 
			}
		}
		
		if(V <= MAX_PRINTABLE_V) {
			long weight;

			cout << endl;
			for (int i = 0; i < V; i++) {
				for (int j = 0; j < V; j++) {
					weight = resultMatrix[i][j];
					cout << "\t";
				
					if (weight != INF)
						cout << resultMatrix[i][j];
					else
						cout << "-";
				}
				cout << endl;
			}	
			cout << endl;
		}
	}
	// Do tego miejsca nigdy nie dochodzimy, ale trzeba cos zwrocic.
	return 0;
}


// Zwraca macierz odleglosci miedzy wierzcholkami wyznaczona za pomoca algorytmu Floyda - Warshalla.
// Kolejne wiersze odpowiadaja indeksom wierzcholkow poczatkowych najkrotszych sciezek,
// a kolumny - indeksom wierzcholkow koncowych. 

Digraph* Floyd(Digraph *graph) {
	int	 V;
	long pk, psk;
	
	V = graph->getNumVertices();			// Liczba wierzcholkow w grafie.
	  	
  	// Indeksy wierzcholkow: p - poczatek, k - koniec, s - ewentualny wierzcholek posredni
  	for(int s = 0; s < V; s++) {
  		for(int p = 0; p < V; p++) {
  			for(int k = 0; k < V; k++) {
  				pk = graph->getWeight(p, k);
  				psk = Add( graph->getWeight(p, s), graph->getWeight(s, k) );
 				// Jesli dotychczasowy dystans p-k jest wiekszy od sumy p-s i s-k,
 				// zapisywany jest ten nowy.
				if (Compare(psk, pk) < 0) {
					graph->setWeight(p, k, psk);
				}
			}
		}		
	}
	return graph;
} 

long RunFloyd(AbstractGraph *graph, int source, int destination, bool findAllPaths) {
 
 	Digraph* distanceMatrix = Floyd((Digraph*) graph);

	if (findAllPaths == false) 
		return distanceMatrix->getWeight(source, destination);
	else {
 		if(distanceMatrix->getNumVertices() <= MAX_PRINTABLE_V)
			distanceMatrix->print();
		return INF;
	}
}


// Znajduje najkrotsza droge od 'source' do 'destination' wykorzystujac algorytm Dijkstry.
// Odleglosci do wierzcholkow sa przechowywane w tablicy (obiekcie klasy DistanceTable).
// Sam graf jest zapisany jako macierz przyleglosci (sasiedztwa).

DistanceTable* Dijkstra(AbstractGraph* graph, int source, int destination, bool findAllPaths) {

	DistanceTable *distances;   // Tu pamietamy wagi wierzcholkow oraz to, czy
                            // sa to wagi tymczasowe, czy ustalone.
 	int	 lastFixed;        // Numer ostatniego wierzcholka, ktoremu  
                            // przypisalismy _stala_ wage.
	long distSrcToLastFixed; // Odleglosc od zrodla do ostatniego wierzcholka
	                         // o ustalonej wadze.
  	int V = graph->getNumVertices();
  	distances = new DistanceTable(V);
  	distances->setDist(source, 0);
  	
	for(int k = 0; k < V; k++) {
		// Jesli szukamy odleglosci tylko do wierzcholka 'destination'
		// i wlasnie go znalezlismy...
		if (findAllPaths == false && distances->isFixed(destination))
			break;
		long tempDist, weightOfEdgeToNext = INF;

		// Szukamy wierzcholka do ktorego najblizej jest ze stworzonego drzewa.
		// Ustalamy jego wage. Teraz on bedzie 'lastFixed'.
  		lastFixed = distances->getNearest();

		// Moze sie zdarzyc, ze sciezka sie urywa - zaden wierzcholek nie bedzie 'najblizszy'
		if (lastFixed == INF)
			break;
  		distances->fix(lastFixed);
  		distSrcToLastFixed = distances->getDist(lastFixed);
  		
  		for (int nextVertex = 0; nextVertex < V; nextVertex++) {
  			weightOfEdgeToNext = graph->getWeight(lastFixed, nextVertex);
			if (weightOfEdgeToNext == INF || distances->isFixed(nextVertex))
				continue;
			else
  				tempDist = distSrcToLastFixed + weightOfEdgeToNext;
  				
 			// Jesli nowo obliczony dystans source -> nextVertex jest mniejszy 
 			// od starego, dystans trzeba uaktualnić.
			if (Compare(tempDist, distances->getDist(nextVertex)) < 0)
				distances->setDist(nextVertex, tempDist);
		}	
	}
	return distances;
} 

// Znajduje najkrotsza droge od 'source' do 'destination' wykorzystujac algorytm Dijkstry. 
// Wagi wierzcholkow sa przechowywane w tablicy (obiekcie klasy DistanceTable).
// Sam graf jest zapisany jako tablica list wiazanych.

DistanceTable* DijkstraList(AbstractGraph* graph, int source, int destination, bool findAllPaths) {

	DistanceTable *distances;  // Wagi wierzcholkow oraz to, czy sa tymczasowe, czy ustalone.
 	int  lastFixed;     // Numer ostatniego wierzcholka, ktoremu przypisalismy _stala_ wage.
	long distSrcToLastFixed; // Odleglosc od zrodla do wierzcholka o ostatnio ustalonej wadze.
  	int  V = graph->getNumVertices();
	List<HalfEdge *> *edges = NULL;
	HalfEdge* edge;	

  	distances = new DistanceTable(V);
  	distances->setDist(source, 0);
  	
	for(int k = 0; k < V; k++) {
		// Jesli szukamy odleglosci tylko do wierzcholka 'destination'
		if (findAllPaths == false && distances->isFixed(destination))
			break;

		long tempDist, weightOfEdgeToNext = INF;
		int	 nextVertex;

		// Szukamy wierzcholka, do ktorego najblizej jest ze stworzonego drzewa.
		// Ustalamy jego wage.
  		lastFixed = distances->getNearest();

		// Moze sie zdarzyc, ze sciezka sie urywa - zaden wierzcholek nie bedzie 'najblizszy'
		if (lastFixed == INF)
			break;
  		distances->fix(lastFixed);
  		distSrcToLastFixed = distances->getDist(lastFixed);
  	  	edges = graph->getOutgoingEdges(lastFixed);
  	  	edges->rewind();
		while (edges->hasMoreElements()) {
			edge = edges->getNext();
			nextVertex = edge->getEndingVertexIndex();
     		weightOfEdgeToNext = edge->getWeight();				
				
			if (weightOfEdgeToNext == INF || distances->isFixed(nextVertex))
				continue;
			else
  				tempDist = distSrcToLastFixed + weightOfEdgeToNext;
  				
 			// Jesli nowo obliczony dystans source -> nextVertex jest mniejszy 
 			// od starego, dystans trzeba uaktualnić.
			if (Compare(tempDist, distances->getDist(nextVertex)) < 0)
				distances->setDist(nextVertex, tempDist);
		}
	}
	return distances;
} 


// Znajduje najkrotsza droge od 'source' do 'destination' wykorzystujac algorytm Dijkstry. 
// Odleglosci do wierzcholkow sa przechowywane w kolejce priorytetowej.
// Sam graf jest zapisany jako macierz przyleglosci (sasiedztwa).

DistanceTable* DijkstraPQ(AbstractGraph* graph, int source, int destination, bool findAllPaths) {

	int     V;              // Liczba wierzcholkow w grafie.
 	Vertex  lastFixed;         // Ostatni wierzcholek, ktoremu przypisalismy stala wage.
	DistanceTable *distances;   // Wagi wierzcholkow (tymczasowe i ustalone)
	long    weightOfEdgeToNext;	// Waga krawedzi od wierzcholka 'recent' do nastepnika
 	long    tempDist;		// Zmienna tymczasowa.
	PriorityQueue *pq;			// Kolejka priorytetowa z tymczasowymi wagami wierzcholkow.
   
	V = graph->getNumVertices();
	distances = new DistanceTable(V);
	distances->setDist(source, 0);
  
  	// Utworz kolejke wierzcholkow z waga jako priorytetem. Wszystkie wagi 
  	// sa nieskonczone, jedynie waga 'source' jest zerowa, jak to w algorytmie Dijkstry.
	(pq = new PriorityQueue(V))->decreaseKey(source, 0);
	  	
  	while (pq->notEmpty()) {
  		lastFixed = pq->removeNearest();
		// Moze sie zdarzyc, ze zaden wierzcholek nie jest osiagalny 
		if (lastFixed.dist == INF)
			break;
  		// Jesli szukamy odleglosci tylko do wierzcholka 'destination'
		if (findAllPaths == false && lastFixed.index == destination)
			break;
  		for (int nextVertex = 0; nextVertex < V; nextVertex++) {
  			weightOfEdgeToNext = graph->getWeight(lastFixed.index, nextVertex);

  			// *** Dla dociekliwych: jakim przypadkom odpowiadaja warunki w nawiasach? ***
  			if (weightOfEdgeToNext == INF || !(pq->contains(nextVertex)))
  				continue;
			else
				tempDist = lastFixed.dist + weightOfEdgeToNext;
				
 			// Jesli nowo obliczony dystans source -> nextVertex jest mniejszy 
 			// od starego, dystans trzeba uaktualnić.
			if (Compare(tempDist, pq->get(nextVertex).dist) < 0) {
				pq->decreaseKey(nextVertex, tempDist);
				distances->setDist(nextVertex, tempDist);
			}
		} 		
	}
	delete pq;
	
	return distances;
} 


// Znajduje najkrotsza droge od 'source' do 'destination' wykorzystujac algorytm Dijkstry. 
// Wagi wierzcholkow sa przechowywane w kolejce priorytetowej.
// Sam graf jest zapisany jako tablica list wiazanych.

DistanceTable* DijkstraListPQ(AbstractGraph* graph, int source, int destination, bool findAllPaths) {

 	Vertex	lastFixed;       // Ostatni wierzcholek, ktoremu przypisalismy _stala_ wage.
	PriorityQueue    *pq; // Kolejka priorytetowa z _tymczasowymi_ wagami wierzcholkow.
	DistanceTable    *distances;	// Wagi wierzcholkow (tymczasowe i ustalone)
	List<HalfEdge *> *edges;
	HalfEdge* edge;	

	long tempDist, weightOfEdgeToNext;
	int	 nextVertex;

  	int V = graph->getNumVertices();
	
	// Utworz kolejke wierzcholkow z waga jako priorytetem. Wszystkie wagi 
  	// sa nieskonczone, jedynie waga 'source' jest zerowa, jak to w algorytmie Dijkstry.
	(pq = new PriorityQueue(V))->decreaseKey(source, 0);

	// Inicjalizacja tablicy odleglosci
	distances = new DistanceTable(V);
	distances->setDist(source, 0);
  	
  	while(pq->notEmpty()) {
  		lastFixed = pq->removeNearest();

		// Moze sie zdarzyc, ze zaden wierzcholek nie jest osiagalny 
		if(lastFixed.dist == INF)
			break;
		
		// Jesli szukamy odleglosci tylko do wierzcholka 'destination'
		if (findAllPaths == false && lastFixed.index == destination)
			break;

		edges = graph->getOutgoingEdges(lastFixed.index);
  	  	edges->rewind();
  	  	
		while (edges->hasMoreElements()) {
			edge = edges->getNext();
			nextVertex = edge->getEndingVertexIndex();
     		weightOfEdgeToNext = edge->getWeight();				

     		// Jakim przypadkom odpowiadaja warunki w nawiasach?
			if (weightOfEdgeToNext == INF || !(pq->contains(nextVertex)))
				continue;
			else
  				tempDist = lastFixed.dist + weightOfEdgeToNext;
  				
 			// Jesli dotychczasowy dystans source -> nextVertex jest wiekszy od nowo
 			// obliczonego, zapisywany jest ten nowy.
			if (Compare(tempDist, pq->get(nextVertex).dist) < 0) {
				pq->decreaseKey(nextVertex, tempDist);
				distances->setDist(nextVertex, tempDist);
			}
		}
	}
	delete pq;

	return distances;
} 


void FindShortestPath(
		AbstractGraph *graph, 
		const MinpathConfig *config,						
		long (*algorithm) (AbstractGraph*,  int , int, bool)		
) {

 	long  time;															
	long  minCost = INF;  // Koszt najkrotszej drogi od 'source' do 'destination'.
  	int   source       = config->source;
  	int   destination  = config->destination;
	bool  findAllPaths = config->findAllPaths;


	time = CurrentTime(); 	
	// Wlasciwy algorytm wykonuje sie tutaj
  	minCost = algorithm(graph, source, destination, findAllPaths);			  	
 	time = CurrentTime() - time;
	if (findAllPaths == false) {
		if (minCost != INF) {
 			cout << "  Najkrotsza droga od " << source << " do " << destination;
  			cout << "  ma koszt " << minCost << endl;
		}
		else {
			cout << "  Nie istnieje droga z wierzcholka " << source << " do " << destination << endl;
		}
	}
  	cout << "\n  Obliczenia trwaly " << time << " ms.\n";
}


void FindShortestPathDijkstra(
		AbstractGraph *graph, 
		const MinpathConfig *config,
		DistanceTable* (*algorithm) (AbstractGraph*,  int , int, bool)		
) {

 	long  time;															
	long  minCost = INF;  // Koszt najkrotszej drogi od 'source' do 'destination'.
	DistanceTable* distances;

  	int  V            = graph->getNumVertices();	    	  
  	int  source       = config->source;
  	int  destination  = config->destination;
	bool findAllPaths = config->findAllPaths;


	if (findAllPaths == false) {		
		time = CurrentTime(); 			
		// Wlasciwy algorytm wykonuje sie tutaj
		distances = algorithm(graph, source, destination, findAllPaths);			  	
		time = CurrentTime() - time;
		minCost = distances->getDist(destination);

		if (minCost != INF) {
 			cout << "  Najkrotsza droga od " << source << " do " << destination;
  			cout << "  ma koszt " << minCost << endl;
		}
		else {
			cout << "  Nie istnieje droga z wierzcholka " << source << " do " << destination << endl;
		}
	} 	
	else {
		time = CurrentTime(); 	
		// Wlasciwy algorytm wykonuje sie tutaj
		for (source = 0; source < V; source++)
			algorithm(graph, source, destination, findAllPaths)->print();			  	
		time = CurrentTime() - time;			
	}
  	cout << "\n  obliczenia trwaly " << time << " ms.\n";
}

void present(const char* message) {
	cout << " ---------------------------------------------------------------\n";
	cout << " " << message << endl;
}

int main(int argc, char* argv[]) {

	// Identyczne grafy: 2x reprezentacja tablicowa i 1x listowa.
	AbstractGraph *graph, *graphForFloyd, *listGraph;
	
	try {
		// Struktura zawierajaca parametry wywolania algorytmow:
		// indeksy wierzcholka poczatkowego i koncowego oraz flage
		// 'findAllPaths' decydujaca o tym, czy szukane sa drogi
		// miedzy wszystkimi parami wierzcholkow.
		MinpathConfig *config = new MinpathConfig(argc, argv);	

		listGraph     = new DigraphL(config->graphFile);			
		graph         = new Digraph(*(DigraphL*)listGraph);		
		// Floyd modyfikuje wczytany graf, wiec wymaga wlasnej kopii.
		graphForFloyd = new Digraph(*(DigraphL*)listGraph);
		
 		if (config->source >= graph->getNumVertices())
 			throw new Exception(UnknownVertexException, argv[2]);
		if (config->destination >= graph->getNumVertices()) 
			throw new Exception(UnknownVertexException, argv[3]);
		
		printf ("\n Wczytano graf sierowany o %d wierzcholkach i %d krawedziach\n", 
		         graph->getNumVertices(), graph->getNumEdges());
		if (graph->getNumVertices() < MAX_PRINTABLE_V)
			graph->print();
		
		present("Dijkstra, graf jako tablica przyleglosci");
		FindShortestPathDijkstra(graph, config, Dijkstra);		
		
		present("Dijkstra, graf jako tablica przyleglosci + kolejka priorytetowa");
		FindShortestPathDijkstra(graph, config, DijkstraPQ);		
	  	
		present("Dijkstra, graf w postaci tablicy list");
		FindShortestPathDijkstra(listGraph, config, DijkstraList);			  	
	  	
		present("Dijkstra, graf w postaci tablicy list + kolejka priorytetowa");
		FindShortestPathDijkstra(listGraph, config, DijkstraListPQ);			  	

		present("Algorytm Floyda");
		FindShortestPath(graph, config, RunFloyd);			  	
  	  	
		present("Algorytm Brute Force porownujacy wszystkie mozliwe drogi");
		FindShortestPath(graph, config, RunBruteForce);			  	
             	  	
	} catch (Exception *e) { HandleException(e); }	
	
	delete graph;
}
