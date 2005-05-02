/*Fichero parser.h

	Contiene la declaración de la clase parser, encargada de manipular
	ficheros XML, validándolos y extrayendo de él objetos que componen
	un sistema a simular
*/


//Evitar instanciación de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif 



class parser {
	public:
		parser ();
		
		/*Este metodo nos comprueba si un determinado fichero en XML
		 *es válido o no*/
		bool esValido ();
	private:
		XercesDOMParser* elParser;
};
