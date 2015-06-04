#include "MST_Algorithms.h"
#include "MST_Utils.h"
#include "Graph.h"
#include "Exception.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	char *fileName;

	try {
		if (argc == 2)
			fileName = argv[1];
		else
			throw new Exception(ImproperMSTCallException, argv[0]);	
	}  catch (Exception *exception) { HandleException(exception); }	

	Graph* graph = new Graph(fileName);
	if (graph->getNumEdges() <= MAX_PRINTABLE_E)
		graph->print();
		
	FindMST(graph, Boruvka, "Algorytm Boruvki",  true);
	FindMST(graph, Kruskal, "Algorytm Kruskala", true);
	
	delete graph;		
	return 0;
}





