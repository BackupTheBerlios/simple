/*Fichero parser.h

	Contiene la declaraci�n de la clase parser, encargada de manipular
	ficheros XML, valid�ndolos y extrayendo de �l objetos que componen
	un sistema a simular
*/

#include <iostream>

//Evitar instanciaci�n de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif 

using namespace std;


class parser {
	public:
		parser (const XMLCh* fichero);
		~parser();
		/*Este metodo nos comprueba si un determinado fichero en XML
		 *es v�lido o no*/
		bool esValido ();
	private:
		XercesDOMParser* 	elParser;
		DOMDocument* 		documento;
		ErrorHandler* 		manejador;
};
