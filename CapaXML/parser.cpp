#include "parser.h"

using namespace std;
/*Se construye un parser a partir de un fichero dado*/
Parser::Parser () 
{
	/*Se intenta inicializar el subsistema XML*/
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& tocatch) {
		cout << "Error!" <<endl ;
	}
	//Creamos el parser
	XercesDOMParser *elParser= new XercesDOMParser;
	
	//Queremos que sea un parser validador
	elParser->setValidationScheme (XercesDOMParser::Val_Always);
	
	//Queremos ceñirnos al espacio de nombre
	elParser->setDoNamespaces (true);
	
	//Activamos el soporta para XMLSchemas 
	elParser->setDoSchema (true);
	elParser->setValidationSchemaFullChecking (true);
	
	/*El gestor de errores (errores de análisis es el proporcionado
	 *por defecto*/
	 manejador= (ErrorHandler *) new HandlerBase;
	 elParser->setErrorHandler (manejador);	
}

/*Este metodo nos comprueba si un determinado fichero en XML
		 *es válido o no*/
bool Parser::esValido (const char* fichero)
{
	try {
		elParser->parse ("file://proyecto.xml");
		}
	catch (XMLException &excepcion) {
		char *mensaje=XMLString::transcode (excepcion.getMessage());
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        return (false);
	}
	catch (DOMException &excepcion)
	{
        char *mensaje=XMLString::transcode (excepcion.msg);
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        return (false);
	}
	catch (...)
	{
		cout << "Excepcion inesperada" << endl;
        cout << "Error!";
        return false;
	}
}

Parser::~Parser()
{
	delete elParser;
	delete manejador;
	XMLPlatformUtils::Terminate();
}
