#include "parser.h"

using namespace std;
/*Se construye un parser a partir de un fichero dado*/
parser::parser (const XMLCh* fichero) 
{
	
	/*Se intenta inicializar el subsistema XML*/
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& tocatch) {
		cout << "Error!" <<endl ;
	}
	//Creamos el parser
	XercesDOMParser *parser= new XercesDOMParser;
	
	//Queremos que sea un parser validador
	elParser->setValidationScheme (XercesDOMParser::Val_Always);
	
	//Queremos ce�irnos al espacio de nombre
	elParser->setDoNamespaces (true);
	
	//Activamos el soporta para XMLSchemas 
	elParser->setDoSchema (true);
	elParser->setValidationSchemaFullChecking (true);
	
	/*El gestor de errores (errores de an�lisis es el proporcionado
	 *por defecto*/
	 manejador= (ErrorHandler *) new HandlerBase;
	 elParser->setErrorHandler (manejador);
	 
	 
	 try {
			cout<< "Parseando" ;
			elParser->parse (fichero);
		}
	catch (XMLException &excepcion) {
		char *mensaje=XMLString::transcode (excepcion.getMessage());
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        exit (-1);
	}
	catch (DOMException &excepcion)
	{
        char *mensaje=XMLString::transcode (excepcion.msg);
        cout << "Excepcion: " << mensaje;
        XMLString::release(&mensaje);
        exit (-1);
	}
	catch (...)
	{
		cout << "Excepcion inesperada" << endl;
        cout << "Error!";
        exit (-1);
	}
}

/*Este metodo nos comprueba si un determinado fichero en XML
		 *es v�lido o no*/
bool parser::esValido ()
{
	DOMNode* nodoactual;
	//Extraemos el documento
	documento=elParser->getDocument();
	
	int codigo_igualdad;
	nodoactual= nodoactual->getFirstChild();
	//Recorremos todos los elementos hijo creando elementos...
	if (nodoactual->getNodeType() == DOMNode::ELEMENT_NODE)
	{

	}
}

parser::~parser()
{
	delete elParser;
	delete manejador;
	XMLPlatformUtils::Terminate();
}
