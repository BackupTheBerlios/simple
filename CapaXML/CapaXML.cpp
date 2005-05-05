#include <iostream>
#include "elementos.h"
#include "parser.h"

//Evitar instanciaci�n de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>


//Otra cosa mas

using namespace std;

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif	


  

int main(int argc, char* argv[])
{
	char* nombre_fichero="proyecto.xml";
	
	vector<elemento*> v;
	
	Parser* elParser= new Parser ();
	
	if (elParser->esValido (nombre_fichero) ) 
		cout << "El fichero es XML valido" << endl;
	v=elParser->extraerElementos();
	
	cout << "El vector contiene " << v.capacity() << endl;
  // Poner aqui el resto de delete's, cuando sean necesarios
  return 0;
}

