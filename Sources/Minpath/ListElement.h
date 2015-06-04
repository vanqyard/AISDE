#ifndef LIST_ELEMENT_H
#define LIST_ELEMENT_H

#include <iostream>

using namespace std;

// Element listy jednokierunkowej (np. klasy szablonowej List<>).
// Sklada sie z zawartosci dowolnego typu 'Type' i wskaznika
// na kolejny element listy. Jesli mamy do czynienia z ostatnim elementem
// listy, wskaznik przyjmuje wartosc NULL.

template <typename Type> 
class ListElement {

	public:
		ListElement(Type c) : content (c), nextElement(NULL) {} ;
		Type getContent() { return content; }
		ListElement *getNext() { return nextElement; }
		void setNext(ListElement* element) { nextElement = element; }
		void print() { cout << content << endl; } 
		
	private:
		Type content;
		ListElement<Type> *nextElement;
};

#endif // LIST_ELEMENT_H
