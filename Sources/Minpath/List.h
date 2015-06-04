#ifndef LIST_H
#define LIST_H

#include "ListElement.h"


// Lista jednokierunkowa obiektow klasy szablonowej ListElement<Type>.
// Umozliwia dodawanie elementow na koncu, pobieranie kolejnych elementow 
// (wskazywanych przez 'current').

template <typename Type>
class List {

	public:
		List();
		~List();
		void append(ListElement<Type> *newElement);	// Dodaje element na koncu listy.
		void append(Type content); // 'Opakowanie' powyzszej funkcji.
		bool hasMoreElements();    // Zwraca true gdy 'current' wskazuje na ListElement. 
		Type getNext(); // Kolejne wywolania zwracaja kolejne elementy listy (nie usuwajac ich).
		void rewind();  // Powrot do poczatku listy. Umozliwia ponowne pobieranie kolejnych elementow.
		void print();
		
	private:
		// Wskazuje odpowiednio: element poczatkowy, ostatni i biezacy 
		// (zwracany przez getNext())
		ListElement<Type> *first, *last, *current;
};

template <typename Type>
List<Type>::List() {
	first   = NULL;
	current = NULL;
	last    = NULL;
}

template <typename Type>
List<Type>::~List() {
	ListElement<Type>* next = first;
	if (first != NULL) {
		current = first;
		while (next = current->getNext()) {
			delete current;
			current = next;
		} 
		delete current;
	}
}

template <typename Type>
void List<Type>::append(ListElement<Type> *newElement) {
	// Jesli lista jest pusta...
	if (first == NULL) {
		first   = newElement;
		current = newElement;
	}
	else
		last->setNext(newElement);
	last = newElement;
}

// Wersja powyzszej funkcji pozwalajaca zapomniec o klasie ListElement<Type>
// przy dodawaniu kolejnych elementow.
template <typename Type>
void List<Type>::append(Type content) {
	append(new ListElement<Type>(content));
}

template <typename Type>
bool List<Type>::hasMoreElements() {
	return current != NULL;
}

template <typename Type>
Type List<Type>::getNext() {
	ListElement<Type> *currentElement = current;
	if (currentElement == NULL)
		return NULL;
	current = currentElement->getNext();
	return currentElement->getContent();
}

template <typename Type>
void List<Type>::rewind() {
	current = first;
}

template <typename Type>
void List<Type>::print() {
	ListElement<Type> *currentElement = first;
	while (currentElement != NULL) {
		currentElement->print();
		currentElement = currentElement->getNext();
	}
}

#endif // LIST_H

