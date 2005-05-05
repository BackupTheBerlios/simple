/*Fichero parser.h

	Contiene la declaraci�n de la clase parser, encargada de manipular
	ficheros XML, valid�ndolos y extrayendo de �l objetos que componen
	un sistema a simular
*/

#include <iostream>
#include <vector>
#include "elementos.h"

//Evitar instanciaci�n de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif 

using namespace std;

#ifndef _parser_
#define _parser_
class Parser {
	public:
		Parser ();
		~Parser();
		/*Este metodo nos comprueba si un determinado fichero en XML
		 *es v�lido o no*/
		bool esValido (const char* fichero);
		
		/*Este metodo extrae del fichero XML los elementos
		 *del sistema que queremos simular*/
		vector <elemento> extraerElementos ();
		
	private:
		XercesDOMParser* 	elParser;
		DOMBuilder* 		parser;
		DOMDocument* 		documento;
		ErrorHandler* 		manejador;
};
#endif
