#ifndef EXCEPTION_H
#define EXCEPTION_H

// Typy wyjatkow
typedef enum {
	ImproperMinpathCallException,
	ImproperMSTCallException,
	FileOpenException,
	FileCreateException,
	FileReadException,
	NumberFormatException,
	UnknownVertexException
} ExceptionCode;

// Implementacja wyjatku
class Exception {

	private:
		ExceptionCode code;  // Kod zalezny od rodzaju sytuacji wyjatkowej.
		char         *param; // Dodatkowy parametr - moze byc wykorzystany
		                     // przez metode obslugi sytuacji wyjatkowej.
	public:
		Exception(ExceptionCode c, const char *p);
		~Exception(void);
		ExceptionCode getCode(void);
		char* getParam(void);
};
	
void HandleException(Exception* exception);	
	
#endif // EXCEPTION_H
