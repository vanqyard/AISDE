#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Exception.h"

using namespace std;

Exception::Exception(ExceptionCode c, const char *p) {
	code = c;
	param = new char[strlen(p)];
	strcpy(param, p);
}

Exception::~Exception(void) { delete[] param; }

ExceptionCode Exception::getCode(void) { return code; }
	
char* Exception::getParam(void) { return param; }

// Obsluga sytuacji wyjatkowej
void HandleException(Exception* exception) {
	ExceptionCode code = exception->getCode();
	char *parameter    = exception->getParam();
	
	switch(code) {
		case ImproperMinpathCallException:
			cout << " Prawidlowe wywolanie:\n"; 
			cout << "   " << parameter << " plik_z_grafem zrodlo ujscie\n\n";
			cout << " lub (gdy chcesz badac odleglosci 'kazdy do kazdego'): \n";
			cout << "   " << parameter << " plik_z_grafem\n\n"; 
			break;		
		case ImproperMSTCallException:
			cout << " Prawidlowe wywolanie:\n"; 
			cout << "   " << parameter << " plik_z_grafem\n\n";
			break;
		case FileOpenException: 
			cout << "\n Nie moge otworzyc pliku '" << parameter << "'\n";
			break;
		case FileCreateException: 
			cout << "\n Nie moge stworzyc pliku '" << parameter << "'\n";
			break;
		case FileReadException:
			cout << "\n Nieprawidlowy format pliku '" << parameter << "'\n";
			break;
		case NumberFormatException: 
			cout << "\n Nieprawidlowy parametr '" << parameter << "'\n";
			break;
		case UnknownVertexException:
			cout << "\n W grafie nie ma wierzcholka o numerze " << parameter << "\n";
			break;
		default:
			cout << "\n Wystapila sytuacja wyjatkowa!\n";
	}
	exit (-1);
}
