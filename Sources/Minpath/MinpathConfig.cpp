#include "MinpathConfig.h"

MinpathConfig::MinpathConfig(int argc, char** argv) {
	if (argc == 2)
		findAllPaths = true;
	else if (argc == 4)	
		findAllPaths = false;
	else 
		throw new Exception(ImproperMinpathCallException, argv[0]);
		
	graphFile = argv[1];
			
	// Jezeli w linii wywolania podalismy wierzcholek poczatkowy i docelowy...
 	if (argc == 4) {
		source      = String2Int(argv[2]);
		destination = String2Int(argv[3]);
	}
	// Jesli nie, to wyznaczamy dlugosc najkrotszych drog "od kazdego do kazdego innego"
	else
		source = destination = 0;
}
