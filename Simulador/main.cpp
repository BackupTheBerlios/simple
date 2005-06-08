#include <cstdlib>
#include <iostream>
#include "sistema.h"
#include "parser.h"


#include "funciones.h"
//Evitar instanciación de plantillas
#define XERCES_TMPLSINC

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>


using namespace std;

int main(int argc, char *argv[])
{
	char* nombre_fichero="test.xml";
	Sistema *s;
	vector<Elemento*> elementos;
	vector<Relacion*> relaciones;
	Parser* elParser= new Parser ();
	
	if (!elParser->esValido (nombre_fichero) ) 
	{
		cout << "El fichero no es XML valido" << endl;
		return -1;
	}
	
	elementos=elParser->extraerElementos();
	relaciones=elParser->extraerRelaciones();
	
	
	s=new Sistema();
	for (int i=0;i<elementos.size();i++)
	{
		s->anadirComponente(elementos.at(i));
	}
	for (int i=0;i<relaciones.size();i++)
	{
		s->anadirRelacion(relaciones.at(i));
	}
	
	escribe_componentes (s);	
    system("PAUSE");
    return EXIT_SUCCESS;
}
